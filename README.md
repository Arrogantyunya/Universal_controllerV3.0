# 易种OS 其他适配器端程序模板

> 该模板提供Redis与串口适配器交互的接口，可通过发送Redis消息来驱动串口直接发送CMD，也可将指令加入到串口发送指令池，排队发送。

### 1、串口指令直接发送

**channel：`SERIAL_CMD`**

**message**:

```json
{
    "method":"Direct",
    "cmd":"610C114509000100FEA01506C001000101011B0D0A0D0A0D0A"
}
```
#### 调用库函数：Redis.PubSerialDirectCmd(cmd)

### 2、串口加入队列直接发送

**channel：`SERIAL_CMD`**

**message**:

```json
{
    "method":"Pool",
    "position":"REPLACE'",
    "packet":{
        "deviceType":"Actuator",
        "deviceTypeId":"C001",
        "confTyp":"ROLLER",
        "method":"RESET_SLAVER",
        "qryId":"13577612570",
        "statusId":"09",
        "deviceAddr":"0c4241A4",
        "deviceChannel":"01",
        "cmd":"610C114509000100FEA01506C001000101011B0D0A0D0A0D0A",
        "status":false,
        "isBroadcast":false,
        "retries":0,
        "maxRetries":4,
        "timeOut":5000
    }
}
```
#### 调用库函数：`Redis.PubSerialPoolCmd(position, packet)`

#### packet打包函数：`Redis.PackCmdPacket(deviceType, deviceTypeId, confTyp, method, qryId, statusId, deviceAddr, deviceChannel, cmd, isBroadcast)`

3、串口消息返回

**channel:`SERIAL_CMD_ACK`**

**message**:

```json
{
    "isRight":true, 
    "msg":"CRC8 OK",
    "recvData":"4100000071000100FEA0250CC002000101062000000101062000000143CA07"
}
```



## **`使用方法`**

### 1、设置本微服务设备类型Id及Redis交互的conftyp

```javascript
//例如：卷膜机
const privateDeviceTypeId = "C001";
const privateDeviceConfTyp = "ROLLER";
```

### 2、在下列解析函数里完成私有指令解析合成与发送功能

```javascript
/**
 * 设备串口私有数据帧解析函数，数据来源于设备上报
 * @param {string} addr 设备地址
 * @param {Array} frameData 帧数据
 */
function __privateSerialCmdParser(addr,frameData){
    
}
```

```javascript
/**
 * 设备来自于网页的指令帧，数据来源于其他服务发送
 * @param {string} method 方法 
 * @param {object} para 参数 
 */
function __privateWebCmdParser(method, para){
    
}
```

### 3、公共方法（申请入网、设置SN、设置执行器工作组）

**公共方法在`RedisReciveCmdParser`方法内实现，由@sharpqian实现与维护，使用者需要自行pull合并冲突项目**

## 测试代码使用方法
### 1、安装redis,安装mysql并修改密码为settings/mysql_settings.json内所示参数、导入test文件夹mydb.sql数据表
```bash
$ sudo apt install mysql-server
#切换用户
$ su root
#登录mysql
$ mysql -u root -p  #无密码
#修改密码
mysql> use mysql;
mysql> update mysql.user set authentication_string=password('1q2w3e4r5t6y') where user='root' and Host ='localhost';
mysql> update user set plugin="mysql_native_password"; 
mysql> flush privileges;
#新建数据库
mysql> create database mydb;
#退出
mysql> quit;
#切换用户
$ su gateway
#导入数据库
$ mysql -u root -p mydb<mydb.sql
#安装redis
$ sudo apt install redis-server

```
### 2、运行主程序，取消test.js里边注释掉的要测试的功能保存并运行
```bash
#1、VsCode打开代码文件夹

#2、安装依赖
$npm install

#3、F5运行主程序

#4、TERMINAL运行测试代码
node test/test.js

#5、DEBUG CONSOLE 及TEMRMINAL查看调试结果

```

# 通用指令定义
## 一、执行器主控通用指令

### 1、执行器申请入网（SERIAL_CMD_ACK：E011）
* 执行器通过串口发送入网指令，loRaAdapter服务通过channel-->`SERIAL_CMD_ACK`返回入网指令到本服务，帧Id为`E011`;正确解析为本服务所属类型设备上报则调用`Common.ActuatorApplyForNetworkAccess(addr,freameData, deviceTypeInfo)`函数执行入网操作，存储设备信息到数据库

#### **1.1、执行器申请入网数据帧格式**（E011）

|   字节索引   |     0     |  1\|2   |    3    |     4\|5     |      6      |   7    |     8-12     |       13-21        |   22    |  23-24   |     25-31      |      32-39       |  40  |       41-46       |
| :----------: | :-------: | :-----: | :-----: | :----------: | :---------: | :----: | :----------: | :----------------: | :-----: | :------: | :------------: | :--------------: | :--: | :---------------: |
|    数据域    | FrameHead | FrameId | DataLen | DeviceTypeId | IsBroadcast | ZoneId | GroupIdArray |      DeviceSn      | channel | Interval |    NewTime     |     Allocate     | CRC8 |     FrameEnd      |
| 长度（byte） |     1     |    2    |    1    |      2       |      1      |   1    |      5       |         9          |    1    |    2     |       7        |        8         |  1   |         2         |
|   示例数据   |    FE     |  E011   |   24    |     C001     |     55      |   55   |   01020306   | XXXXXXXXXXXXXXXXXX |   00    |  00 3C   | 20180824141702 | 0000000000000000 |  00  | 0D 0A 0D 0A 0D 0A |

协议帧各字段域说明：

| 字段域       | 说明                   | 长度（byte） | 备注                                                         |
| ------------ | :--------------------- | :----------: | :----------------------------------------------------------- |
| FrameHead    | 帧头                   |      2       | FE                                                           |
| FrameId      | 帧ID                   |      2       | E011                                                         |
| DataLen      | 数据长度               |      1       | 从此位后开始计算（不包含自身），一直到`CRCR8`位结束（不包括CRC8位） |
| DeviceTypeId | 设备类型ID             |      2       | 查看设备类型对照表                                           |
| IsBroadcast  | 是否广播指令           |      1       | 0x55是，00否                                                 |
| ZoneId       | 所属区域Id             |      1       | 0x55表示所有区域                                             |
| channel      | 子设备路数             |      1       | 0x00表示主设备（无子设备情况），其他表示相应路数             |
| GroupIdArray | 组编号数组             |      5       | 最多5个组，组id(2byte)不为00时有效                           |
| Interval     | LoRa设备的采集时间间隔 |      2       | 十六进制整数，单位为秒                                       |
| NewTime      | 新设置的RTC时间        |      7       | BCD码值，如`20180824141702`代表`2018年8月24日14点17分零2秒`  |
| Allocate     | 预留字段               |      8       | 预留做他用                                                   |
| CRC8         | CRC8校验码             |      1       | 用于进行CRC8计算的数据DataLen指代的长度                      |
| FrameEnd     | 帧尾                   |      6       | 0d 0a 0d 0a 0d 0a                                            |

**执行器申请入网数据帧应用示例：**

ID为`14052A0C`的LoRa设备重新上报设置参数：

```javascript
41 0C256514 000500 FE E011 24 C001 55 01 0100000000 C00120190304150001 00 0000 FFFFFFFFFFFFFF 0000000000000000 23 0D0A0D0A0D0A
```

#### 1.2、(Redis)=>`SERIAL_CMD_ACK`  接收数据格式

```json
{
    "isRight":true,
    "msg":"CRC8 OK",
    "addr":"0C2143A4",                 		"recvData":"FEE01124C00155010100000000000000000000000000000000FFFFFFFFFFFFFF0000000000000000"
}
```

* `isRight`: 数据帧CRC8校验是否通过
* `msg`：提示信息
* `addr`：设备硬件地址
* `recvData`：串口接收到的数据帧

***

### 2、执行器请求设置工作组及区域编号（SERIAL_CMD_ACK：E012）

`设备工作组丢失重新请求`

#### 2.1、执行器请求设置工作组及区域编号数据帧格式（E012）

|   字节索引   |     0     |  1\|2   |    3    |     4\|5     |      6      |   7    |    8    |  9   |       9-14        |
| :----------: | :-------: | :-----: | :-----: | :----------: | :---------: | :----: | :-----: | :--: | :---------------: |
|    数据域    | FrameHead | FrameId | DataLen | DeviceTypeId | IsBroadcast | ZoneId | channel | CRC8 |     FrameEnd      |
| 长度（byte） |     1     |    2    |    1    |      2       |      1      |   1    |    1    |  1   |         2         |
|   示例数据   |    FE     |  E012   |   05    |     C001     |     55      |   01   |   00    |  00  | 0D 0A 0D 0A 0D 0A |

协议帧各字段域说明：

| 字段域       | 说明         | 长度（byte） | 备注                                                         |
| ------------ | :----------- | :----------: | :----------------------------------------------------------- |
| FrameHead    | 帧头         |      2       | FE                                                           |
| FrameId      | 帧ID         |      2       | E012                                                         |
| DataLen      | 数据长度     |      1       | 从此位后开始计算（不包含自身），一直到`CRCR8`位结束（不包括CRC8位） |
| DeviceTypeId | 设备类型ID   |      2       | 查看设备类型对照表                                           |
| IsBroadcast  | 是否广播指令 |      1       | 0x55是，00否                                                 |
| ZoneId       | 所属区域Id   |      1       | 0x55表示所有区域                                             |
| channel      | 设备路数     |      1       | 0x00表示主设备，其他表示相应路数                             |
| CRC8         | CRC8校验码   |      1       | 用于进行CRC8计算的数据DataLen指代的长度                      |
| FrameEnd     | 帧尾         |      6       | 0d 0a 0d 0a 0d 0a                                            |

**应用示例：**

```javascript
41 0C2A4314 00BB00    FE E012 04 C001 01 00 E1 0D0A0D0A0D0A
```

#### 2.2、(Redis)=>`SERIAL_CMD_ACK`  接收数据格式

```json
{
    "isRight":true,
    "msg":"CRC8 OK",
    "addr":"0C2143A4",                 		
    "recvData":"FEE01204C0010100"
}
```

- `isRight`: 数据帧CRC8校验是否通过
- `msg`：提示信息
- `addr`：设备硬件地址
- `recvData`：串口接收到的数据帧

***

### 3、执行器请求设置SN及设备路数（SERIAL_CMD_ACK：E013）
* `设备重新请求Sn`——设备Sn丢失重新请求获取，正确入网后，交互指令数据不需要Sn

#### 3.1、执行器请求设置SN及设备路数数据帧格式（E013）

|   字节索引   |     0     |  1\|2   |    3    |     4\|5     |      6      |   7    |       8       |  9   |                   |
| :----------: | :-------: | :-----: | :-----: | :----------: | :---------: | :----: | :-----------: | :--: | :---------------: |
|    数据域    | FrameHead | FrameId | DataLen | DeviceTypeId | IsBroadcast | ZoneId | DeviceChannel | CRC8 |     FrameEnd      |
| 长度（byte） |     1     |    2    |    1    |      2       |      1      |   1    |       1       |  1   |         2         |
|   示例数据   |    FE     |  E013   |   05    |     C001     |     55      |   01   |      01       |  00  | 0D 0A 0D 0A 0D 0A |

协议帧各字段域说明：

| 字段域        | 说明         | 长度（byte） | 备注                                                         |
| ------------- | :----------- | :----------: | :----------------------------------------------------------- |
| FrameHead     | 帧头         |      2       | FE                                                           |
| FrameId       | 帧ID         |      2       | E013                                                         |
| DataLen       | 数据长度     |      1       | 从此位后开始计算（不包含自身），一直到`CRCR8`位结束（不包括CRC8位） |
| DeviceTypeId  | 设备类型ID   |      2       | 查看设备类型对照表                                           |
| IsBroadcast   | 是否广播指令 |      1       | 0x55是，00否                                                 |
| ZoneId        | 所属区域Id   |      1       | 0x55表示所有区域                                             |
| DeviceChannel | 设备路数     |      1       | 主设备：0x00                                                 |
| CRC8          | CRC8校验码   |      1       | 用于进行CRC8计算的数据DataLen指代的长度                      |
| FrameEnd      | 帧尾         |      6       | 0d 0a 0d 0a 0d 0a                                            |

**应用示例：**

```javascript
41 0C2A4314 004A00 FE E013 04 C001 01 00 E1 0D0A0D0A0D0A
```

#### 3.2、(Redis)=>`SERIAL_CMD_ACK`  接收数据格式

```json
{
    "isRight":true,
    "msg":"CRC8 OK",
    "addr":"0C2143A4",                 		
    "recvData":"FEE01304C0010100"
}
```

- `isRight`: 数据帧CRC8校验是否通过
- `msg`：提示信息
- `addr`：设备硬件地址
- `recvData`：串口接收到的数据帧

***

### 4、执行器上报实时工作状态（SERIAL_CMD_ACK：E014）

**每种执行器单独定义预留字段内容，子设备设备状态单独定义帧类型帧功能格式**

#### 4.1、执行器通用回执数据帧格式（E014）

|   字节索引   |     0     |  1\|2   |    3    |     4\|5     |      6      |   7    |    8    |   9    | 10-11 |  12  |  13  |              14-29               |  30  |       31-36       |
| :----------: | :-------: | :-----: | :-----: | :----------: | :---------: | :----: | :-----: | :----: | :---: | :--: | :--: | :------------------------------: | :--: | :---------------: |
|    数据域    | FrameHead | FrameId | DataLen | DeviceTypeId | IsBroadcast | ZoneId | channel | status |  Vol  | Rssi | Csq  |             Allocate             | CRC8 |     FrameEnd      |
| 长度（byte） |     1     |    2    |    1    |      2       |      1      |   1    |    1    |   1    |   2   |  1   |  1   |                16                |  1   |         2         |
|   示例数据   |    FE     |  E014   |   12    |     C001     |     55      |   01   |   00    |   00   | 2EE0  |  FF  |  FF  | 00000000000000000000000000000000 |  00  | 0D 0A 0D 0A 0D 0A |

协议帧各字段域说明：

| 字段域       | 说明             | 长度（byte） | 备注                                                         |
| ------------ | :--------------- | :----------: | :----------------------------------------------------------- |
| FrameHead    | 帧头             |      2       | FE                                                           |
| FrameId      | 帧ID             |      2       | E014                                                         |
| DataLen      | 数据长度         |      1       | 从此位后开始计算（不包含自身），一直到`CRCR8`位结束（不包括CRC8位） |
| DeviceTypeId | 设备类型ID       |      2       | 查看设备类型对照表（5555：所有类型）                         |
| IsBroadcast  | 是否广播指令     |      1       | 0x55是，00否                                                 |
| ZoneId       | 所属区域Id       |      1       | 0x55表示所有区域                                             |
| Addr         | 设备地址         |      4       | 设备地址（全部为55555555）                                   |
| status       | 设备当前工作状态 |      1       | 对应回执状态表                                               |
| Vol          | 电压             |      2       |                                                              |
| Rssi         | 性噪比           |      1       |                                                              |
| Csq          | 信号强度         |      1       |                                                              |
| Allocate     | 预留字段         |      16      | 预留做他用                                                   |
| CRC8         | CRC8校验码       |      1       | 用于进行CRC8计算的数据DataLen指代的长度                      |
| FrameEnd     | 帧尾             |      6       | 0d 0a 0d 0a 0d 0a                                            |

**应用示例：**

ID为`14052A0C`的LoRa设备上报实时工作状态：

```
41 0C2A4314 00BF00 FE E014 29 C001 01 00 01 2EE0 FFFF 00000000000000000000000000000000 69 0D0A0D0A0D0A
```



#### 4.2、(Redis)=>`SERIAL_CMD_ACK`  接收数据格式

```json
{
    "isRight":true,
    "msg":"CRC8 OK",
    "addr":"0C2143A4",                 		
    "recvData":"FEE01429C0010100012EE0FFFF00000000000000000000000000000000"
}
```

- `isRight`: 数据帧CRC8校验是否通过
- `msg`：提示信息
- `addr`：设备硬件地址
- `recvData`：串口接收到的实时状态数据帧

#### 4.3、####################

#### **私有实时状态上报字段在此处定义**

####  #########################



 **预留字段实际使用说明举例子**

|   字节索引   |     14      |    15-16    |        17-18         |      19-20       |         21         |      22-29       |
| :----------: | :---------: | :---------: | :------------------: | :--------------: | :----------------: | :--------------: |
|    数据域    | CurrentOpen | LowVolLimit | MaxMotorCurrentLimit | RealTime Current | StatusSendInterval |     Allocate     |
| 长度（byte） |      1      |      2      |          2           |        2         |         1          |        8         |
|   示例数据   |     00      |    2EE0     |         000A         |       003C       |         01         | 0000000000000000 |

* **CurrentOpen**:当前开度

* **LowVolLimit**:低电压阈值

* **MaxMotorCurrentLimit**:最大工作电流百分比

* **RealTime Current**:实时工作电流

* **StatusSendInterval**:上报数据间隔



***

### 5、执行器通用回执（SERIAL_CMD_ACK：E015）

#### 5.1、执行器通用回执数据帧格式（E015）

|   字节索引   |     0     |  1\|2   |    3    |     4\|5     |      6      |   7    |    8    |   9    |      10-17       |  18  |       19-24       |
| :----------: | :-------: | :-----: | :-----: | :----------: | :---------: | :----: | :-----: | :----: | :--------------: | :--: | :---------------: |
|    数据域    | FrameHead | FrameId | DataLen | DeviceTypeId | IsBroadcast | ZoneId | channel | status |     Allocate     | CRC8 |     FrameEnd      |
| 长度（byte） |     1     |    2    |    1    |      2       |      1      |   1    |    1    |   1    |        8         |  1   |         2         |
|   示例数据   |    FE     |  E015   |   0E    |     C001     |     55      |   01   |   00    |   00   | 0000000000000000 |  00  | 0D 0A 0D 0A 0D 0A |

协议帧各字段域说明：

| 字段域       | 说明             | 长度（byte） | 备注                                                         |
| ------------ | :--------------- | :----------: | :----------------------------------------------------------- |
| FrameHead    | 帧头             |      2       | FE                                                           |
| FrameId      | 帧ID             |      2       | E012                                                         |
| DataLen      | 数据长度         |      1       | 从此位后开始计算（不包含自身），一直到`CRCR8`位结束（不包括CRC8位） |
| DeviceTypeId | 设备类型ID       |      2       | 查看设备类型对照表（5555：所有类型）                         |
| IsBroadcast  | 是否广播指令     |      1       | 0x55是，00否                                                 |
| ZoneId       | 所属区域Id       |      1       | 0x55表示所有区域                                             |
| Addr         | 设备地址         |      4       | 设备地址（全部为55555555）                                   |
| status       | 设备当前工作状态 |      1       | 对应回执状态表                                               |
| Allocate     | 预留字段         |      8       | 预留做他用                                                   |
| CRC8         | CRC8校验码       |      1       | 用于进行CRC8计算的数据DataLen指代的长度                      |
| FrameEnd     | 帧尾             |      6       | 0d 0a 0d 0a 0d 0a                                            |

**应用示例：**

ID为`14052A0C`的LoRa设备通用回执（收到查询参数指令）：

```
410C2A4314006100  FE E015 0D C001 01 00 01 0000000000000000 16 0D0A0D0A0D0A
```

#### 5.2、(Redis)=>`SERIAL_CMD_ACK`  接收数据格式

```json
{
    "isRight":true,
    "msg":"CRC8 OK",
    "addr":"0C2143A4",                 		
    "recvData":"FEE0150DC0010100010000000000000000"
}
```

- `isRight`: 数据帧CRC8校验是否通过
- `msg`：提示信息
- `addr`：设备硬件地址
- `recvData`：串口接收到的通用回执数据帧

#### 5.3、执行器公共通用回执定义

**0x00~0x08所有执行器都有下表状态**

```json
{
"00":"出厂模式",
"01":"查询LoRa设备参数成功",
"02":"查询LoRa设备参数失败",
"03":"设置组Id数组成功",
"04":"设置组Id数组失败",
"05":"设置SN及子设备路数成功",
"06":"设置SN及子设备路数失败",
"07":"强制停止设备成功",
"08":"强制停止设备成功失败"
}
```

#### 5.4、####################

#### **私有通用回执状态表在此处定义**

####  #########################

**私有状态0x09~0xFF，每种执行器单独定义**

```json

```



***



### 6、设置执行器Sn及设备路数（SYS_CMD：SET_SN_COUNT）
* Redis接收到Web端设置指令，通过**channel-->`SYS_CMD`**返回，**method**为**`SET_SN_COUNT`**;正确解析为本服务所属类型设备上报则调用**`Common.ActuatorSetDeviceSnAndChannel(deviceTypeAlias, setSnDeviceAddr, deviceTypeId, channel, zoneId, newdeviceSn)`**函数执行设置操作，该function将合成串口设备指令，发送给指定设备配置新设备SN及路数
* 执行器主控设备接收到设置指令，完成入网设置操作，通过通用回执回复状态到`ACTUATOR_ACK`

#### 6.1、(Redis)=>`SYS_CMD`  接收数据格式

```json
{
    "confTyp": "LORA_COMMON_CMD",
    "method": "SET_SN_COUNT",
    "para": {
        "deviceAddr": "0C2A4314",
        "deviceType":"LoRa_Roller",
        "channel":0,
        "zoneId":2,
        "newdeviceSn":"C00120190304150001"
    }
}
```

- `confTyp`: 配置类型
- `method`：指令方法
- `para`：参数
  * `para.deviceAddr`：设备硬件地址
  * `para.deviceType`:设备类型
  * `para.zoneId`：区域Id
  * `para.newdeviceSn`:设置的新SN

#### 6.2、设置执行器Sn及设备路数指令帧格式（A013）

|   字节索引   |       N/A       |   N/A    |     N/A      |     0     |  1\|2   |    3    |     4\|5     |      6      |   7    |       8       |      9      |       10-18        |  19  |       20-25       |
| :----------: | :-------------: | :------: | :----------: | :-------: | :-----: | :-----: | :----------: | :---------: | :----: | :-----------: | :---------: | :----------------: | :--: | :---------------: |
|    数据域    | DeviceFrameHead |   Addr   | DeviceOthers | FrameHead | FrameId | DataLen | DeviceTypeId | IsBroadcast | ZoneId | DeviceChannel | SlaverCount |      DeviceSn      | CRC8 |     FrameEnd      |
| 长度（byte） |        1        |    4     |      3       |     1     |    2    |    1    |      2       |      1      |   1    |       1       |      1      |         9          |  1   |         2         |
|   示例数据   |       61        | 14052A0C |   00 XXXX    |    FE     |  A013   |   0F    |     C001     |     55      |   01   |      00       |     00      | 000000000000000000 |  00  | 0D 0A 0D 0A 0D 0A |

协议帧各字段域说明：

| 字段域          | 说明             | 长度（byte） | 备注                                                         |
| --------------- | :--------------- | :----------: | :----------------------------------------------------------- |
| DeviceFrameHead | 硬件帧头         |      1       | 仁钰LoRa M-KL9按地址发送时需要                               |
| Addr            | 设备地址         |      4       | 00000071(广播，所有设备上报自己的ID和SN)                     |
| DeviceOthers    | 控制字等         |      3       | 仁钰LoRa M-KL9按地址发送时需要                               |
| FrameHead       | 帧头             |      1       | FE                                                           |
| FrameId         | 帧ID             |      2       | A013                                                         |
| DataLen         | 数据长度         |      1       | 从此位后开始计算（不包含自身），一直到`CRCR8`位结束（不包括CRC8位） |
| DeviceTypeId    | 设备类型ID       |      2       | 查看设备类型对照表                                           |
| IsBroadcast     | 是否广播指令     |      1       | 0x55是，00否                                                 |
| ZoneId          | 所属区域Id       |      1       | 0x55表示所有区域                                             |
| DeviceChannel   | 设备路数         |      1       | 主设备：0x00                                                 |
| SlaverCount     | 子设备总路数     |      1       | 子设备总数                                                   |
| DeviceSn        | 设置的LoRa设备SN |      9       |                                                              |
| CRC8            | CRC8校验码       |      1       | 用于进行CRC8计算的数据DataLen指代的长度                      |
| FrameEnd        | 帧尾             |      6       | 0d 0a 0d 0a 0d 0a                                            |

**应用示例：**

```javascript
61 14432A0C 000100 FE A013 0E C001 01 00 02 C00120190304150001 15 0D0A0D0A0D0A
```

#### 6.3、(Redis)=>`SERIAL_CMD`发送数据格式

* 调用**`Common.ActuatorSetDeviceSnAndChannel(deviceTypeAlias, setSnDeviceAddr, deviceTypeId, channel, zoneId, newdeviceSn)`**函数实现数据发送功能

***

### 7、设置执行器组Id数组（SYS_CMD:SET_GROUP）
- Redis接收到Web端设置指令，通过**channel-->`SYS_CMD`**返回，**method**为**`SET_GROUP`**;正确解析为本服务所属类型设备上报则调用**` Common.ActuatorSetGroupIdArray(setGroupIdArrayDeviceType,deviceTypeAlias, deviceTypeId, groupId, deviceSn, groupIdArray)`**函数执行设置操作，该function将合成串口设备指令，发送给指定执行器组Id数组
- 执行器主控设备接收到设置指令，完成入网设置操作，通过通用回执回复状态到`ACTUATOR_ACK`

#### 7.1、(Redis)=>`SYS_CMD`  接收数据格式

```json
{
    "confTyp": "LORA_COMMON_CMD",
    "method": "SET_GROUP",
    "para": {
        "groupId": 1,
        "actuator_type":"LoRa_Roller",
        "deviceSn":["C00120190304150001"，"C00120190304150002"],
        "groupIdArray":"0102000000"
    }
}
```

- `confTyp`: 配置类型
- `method`：指令方法
- `para`：参数
  - `para.groupId`：设置的组id
  - `para.actuator_type`:执行器设备类型
  - `para.deviceSn`：待设置设备sn
  - `para.groupIdArray`:设置的组id数组

#### 7.2、设置设置执行器主设备工作组编号协议帧格式(A012)

`channel==0x00表示设置主设备参数，channel==0x55表示设置所有子设备参数，等于其他表示设置其下属的某路子设备参数`

协议格式如下`表1-1-1`

|   字节索引   |       N/A       |   N/A    |     N/A      |     0     |  1\|2   |    3    |     4\|5     |      6      |   7    |     8-12     |   13    |  14  |       15-20       |
| :----------: | :-------------: | :------: | :----------: | :-------: | :-----: | :-----: | :----------: | :---------: | :----: | :----------: | :-----: | :--: | :---------------: |
|    数据域    | DeviceFrameHead |   Addr   | deviceOthers | FrameHead | FrameId | DataLen | DeviceTypeId | IsBroadcast | ZoneId | GroupIdArray | channel | CRC8 |     FrameEnd      |
| 长度（byte） |        1        |    4     |      3       |     1     |    2    |    1    |      2       |      1      |   1    |      5       |    1    |  1   |         2         |
|   示例数据   |       61        | 00000071 |   00 XXXX    |    FE     |  A012   |   10    |     C001     |     00      |   01   |  0000000000  |   00    |  00  | 0D 0A 0D 0A 0D 0A |

协议帧各字段域说明：

| 字段域          | 说明         | 长度（byte） | 备注                                                         |
| --------------- | :----------- | :----------: | :----------------------------------------------------------- |
| DeviceFrameHead | 硬件帧头     |      1       | 仁钰LoRa M-KL9按地址发送时需要                               |
| Addr            | 设备地址     |      4       | 00000071(广播，所有设备上报自己的ID和SN)                     |
| deviceOthers    | 控制字等     |      3       | 仁钰LoRa M-KL9按地址发送时需要                               |
| FrameHead       | 帧头         |      2       | FE                                                           |
| FrameId         | 帧ID         |      2       | A012                                                         |
| DataLen         | 数据长度     |      1       | 从此位后开始计算（不包含自身），一直到`CRCR8`位结束（不包括CRC8位） |
| DeviceTypeId    | 设备类型ID   |      2       | 查看设备类型对照表（5555：所有类型）                         |
| IsBroadcast     | 是否广播指令 |      1       | 0x55是，00否                                                 |
| ZoneId          | 所属区域Id   |      1       | 0x55表示所有区域                                             |
| channel         | 设备路数     |      1       | 0x00设置主设备（无子设备情况），0x55设置所有子设备，其他设置相应路数的子设备 |
| GroupIdArray    | 组编号数组   |      5       | 最多5个组，组id(2byte)不为00时有效                           |
| CRC8            | CRC8校验码   |      1       | 用于进行CRC8计算的数据DataLen指代的长度                      |
| FrameEnd        | 帧尾         |      6       | 0d 0a 0d 0a 0d 0a                                            |

**应用示例：**

设置ID为`0C3B6214`的设备组编号数组为0100000000

```shell
61 0C3B6214 000100 FE A012 0A C001 00 01 0100000000 00 57 0D0A0D0A0D0A
```

#### 7.3、(Redis)=>`SERIAL_CMD`发送数据格式

- 调用**`Common.ActuatorSetGroupIdArray(setGroupIdArrayDeviceType,deviceTypeAlias, deviceTypeId, groupId, deviceSn, groupIdArray)`**函数实现数据发送实现设置SN功能

***

### 8、查询执行器实时工作状态（SYS_CMD:QUERY_STATUS）

- Redis接收到Web端设置指令，通过**channel-->`SYS_CMD`**返回，**method**为**`QUERY_STATUS`**;正确解析为本服务所属类型设备上报则调用**` Common.QueryCurrentRealtimeWorkingStatus = function (sendAddr, type, deviceTypeId, zoneId, groupId, channel, isBroadcast)`**函数执行查询操作，该function将合成串口设备指令，发送给指定执行器查询实时工作状态
- 执行器主控设备接收到设置指令，完成入网设置操作，通过通用回执回复状态到`ACTUATOR_ACK`

#### 8.1、(Redis)=>`SYS_CMD`  接收数据格式

```json
 {
    "confTyp": "LORA_COMMON_CMD",
    "method": "QUERY_STATUS",
    "para": {
        "zoneId": 1,
        "deviceType": "LoRa_Roller",
        "groupId": 1,
        "deviceSn": ["C00120190304150001"]
    }
}
```

- `confTyp`: 配置类型
- `method`：指令方法
- `para`：参数
  - `para.zoneId`：查询的区域Id
  - `para.deviceType`:执行器设备类型
  - `para.groupId`：查询的组d
  - `para.deviceSn`：待查询设备sn

#### 8.2、查询执行器实时工作状态协议帧格式(A014)

|   字节索引   |       N/A       |   N/A    |     N/A      |     0     |  1\|2   |    3    |     4\|5     |      6      |   7    |    8    |    9    |  10  |       11-16       |
| :----------: | :-------------: | :------: | :----------: | :-------: | :-----: | :-----: | :----------: | :---------: | :----: | :-----: | :-----: | :--: | :---------------: |
|    数据域    | DeviceFrameHead |   Addr   | deviceOthers | FrameHead | FrameId | DataLen | DeviceTypeId | IsBroadcast | ZoneId | GroupId | channel | CRC8 |     FrameEnd      |
| 长度（byte） |        1        |    4     |      3       |     1     |    2    |    1    |      2       |      1      |   1    |    1    |    1    |  1   |         2         |
|   示例数据   |       61        | 00000071 |   00 XXXX    |    FE     |  A014   |   06    |     5555     |     55      |   01   |   01    |   00    |  00  | 0D 0A 0D 0A 0D 0A |

协议帧各字段域说明：

| 字段域          | 说明       | 长度（byte） | 备注                                                         |
| --------------- | :--------- | :----------: | :----------------------------------------------------------- |
| DeviceFrameHead | 硬件帧头   |      1       | 仁钰LoRa M-KL9按地址发送时需要                               |
| Addr            | 设备地址   |      4       | 00000071(广播，所有设备上报自己的ID和SN)                     |
| deviceOthers    | 控制字等   |      3       | 仁钰LoRa M-KL9按地址发送时需要                               |
| FrameHead       | 帧头       |      2       | FE                                                           |
| FrameId         | 帧ID       |      2       | A011                                                         |
| DataLen         | 数据长度   |      1       | 从此位后开始计算（不包含自身），一直到`CRCR8`位结束（不包括CRC8位） |
| DeviceTypeId    | 设备类型ID |      2       | 查看设备类型对照表（5555：所有类型）                         |
| ZoneId          | 所属区域Id |      1       | 0x55表示所有区域                                             |
| GroupId         | 组id       |      1       |                                                              |
| channel         | 查询角色   |      1       | 0x00：表示主控，0x55表示所有，其他表示相应路数的子设备       |
| CRC8            | CRC8校验码 |      1       | 用于进行CRC8计算的数据DataLen指代的长度                      |
| FrameEnd        | 帧尾       |      6       | 0d 0a 0d 0a 0d 0a                                            |

**应用示例：**

```javascript
61 14432A0C 000100 FE A014 04 C001 01 01 00 E1 0D0A0D0A0D0A
```

#### 8.3、(Redis)=>`SERIAL_CMD`发送数据格式

- 调用**`Common.ActuatorSetGroupIdArray(setGroupIdArrayDeviceType,deviceTypeAlias, deviceTypeId, groupId, deviceSn, groupIdArray)`**函数实现数据发送实现设置SN功能

***

## 一、传感器主控通用指令

### 1、传感器申请入网（SERIAL_CMD_ACK：E011）

- 传感器通过串口发送入网指令，loRaAdapter服务通过channel-->`SERIAL_CMD_ACK`返回入网指令到本服务，帧Id为`E011`;正确解析为本服务所属类型设备上报则调用`Common.ActuatorApplyForNetworkAccess(addr,freameData, deviceTypeInfo)`函数执行入网操作，存储设备信息到数据库

#### **1.1、传感器申请入网数据帧格式**

|   字节索引   |     0     |  1\|2   |    3    |     4\|5     |      6      |   7    |     8-12     |       13-21        |   22    |  23-24   |     25-31      |      32-39       |  40  |       41-46       |
| :----------: | :-------: | :-----: | :-----: | :----------: | :---------: | :----: | :----------: | :----------------: | :-----: | :------: | :------------: | :--------------: | :--: | :---------------: |
|    数据域    | FrameHead | FrameId | DataLen | DeviceTypeId | IsBroadcast | ZoneId | GroupIdArray |      DeviceSn      | channel | Interval |    NewTime     |     Allocate     | CRC8 |     FrameEnd      |
| 长度（byte） |     1     |    2    |    1    |      2       |      1      |   1    |      5       |         9          |    1    |    2     |       7        |        8         |  1   |         2         |
|   示例数据   |    FE     |  E011   |   24    |     0001     |     55      |   55   |   01020306   | XXXXXXXXXXXXXXXXXX |   00    |  00 3C   | 20180824141702 | 0000000000000000 |  00  | 0D 0A 0D 0A 0D 0A |

协议帧各字段域说明：

| 字段域       | 说明                   | 长度（byte） | 备注                                                         |
| ------------ | :--------------------- | :----------: | :----------------------------------------------------------- |
| FrameHead    | 帧头                   |      2       | FE                                                           |
| FrameId      | 帧ID                   |      2       | E011                                                         |
| DataLen      | 数据长度               |      1       | 从此位后开始计算（不包含自身），一直到`CRCR8`位结束（不包括CRC8位） |
| DeviceTypeId | 设备类型ID             |      2       | 查看设备类型对照表                                           |
| IsBroadcast  | 是否广播指令           |      1       | 0x55是，00否                                                 |
| ZoneId       | 所属区域Id             |      1       | 0x55表示所有区域                                             |
| channel      | 子设备路数             |      1       | 0x00表示主设备（无子设备情况），其他表示相应路数             |
| GroupIdArray | 组编号数组             |      5       | 最多5个组，组id(2byte)不为00时有效                           |
| Interval     | LoRa设备的采集时间间隔 |      2       | 十六进制整数，单位为秒                                       |
| NewTime      | 新设置的RTC时间        |      7       | BCD码值，如`20180824141702`代表`2018年8月24日14点17分零2秒`  |
| Allocate     | 预留字段               |      8       | 预留做他用                                                   |
| CRC8         | CRC8校验码             |      1       | 用于进行CRC8计算的数据DataLen指代的长度                      |
| FrameEnd     | 帧尾                   |      6       | 0d 0a 0d 0a 0d 0a                                            |

**传感器申请入网数据帧应用示例：**

ID为`14052A0C`的LoRa设备重新上报设置参数：

```javascript
41 0C256514 000500 FE E011 24 C001 55 01 0100000000 C00120190304150001 00 0000 FFFFFFFFFFFFFF 0000000000000000 23 0D0A0D0A0D0A
```

#### 1.2、(Redis)=>`SERIAL_CMD_ACK`  接收数据格式

```json
{
    "isRight":true,
    "msg":"CRC8 OK",
    "addr":"0C2143A4",                 		"recvData":"FEE01124000155010100000000000000000000000000000000FFFFFFFFFFFFFF0000000000000000"
}
```

- `isRight`: 数据帧CRC8校验是否通过
- `msg`：提示信息
- `addr`：设备硬件地址
- `recvData`：串口接收到的数据帧

------

### 2、传感器请求设置SN及设备路数（SERIAL_CMD_ACK：E013）

- `设备重新请求Sn`——设备Sn丢失重新请求获取，正确入网后，交互指令数据不需要Sn

#### 2.1、传感器请求设置SN及设备路数数据帧格式

|   字节索引   |     0     |  1\|2   |    3    |     4\|5     |      6      |   7    |       8       |  9   |                   |
| :----------: | :-------: | :-----: | :-----: | :----------: | :---------: | :----: | :-----------: | :--: | :---------------: |
|    数据域    | FrameHead | FrameId | DataLen | DeviceTypeId | IsBroadcast | ZoneId | DeviceChannel | CRC8 |     FrameEnd      |
| 长度（byte） |     1     |    2    |    1    |      2       |      1      |   1    |       1       |  1   |         2         |
|   示例数据   |    FE     |  E013   |   05    |     0001     |     55      |   01   |      01       |  00  | 0D 0A 0D 0A 0D 0A |

协议帧各字段域说明：

| 字段域        | 说明         | 长度（byte） | 备注                                                         |
| ------------- | :----------- | :----------: | :----------------------------------------------------------- |
| FrameHead     | 帧头         |      2       | FE                                                           |
| FrameId       | 帧ID         |      2       | E013                                                         |
| DataLen       | 数据长度     |      1       | 从此位后开始计算（不包含自身），一直到`CRCR8`位结束（不包括CRC8位） |
| DeviceTypeId  | 设备类型ID   |      2       | 查看设备类型对照表                                           |
| IsBroadcast   | 是否广播指令 |      1       | 0x55是，00否                                                 |
| ZoneId        | 所属区域Id   |      1       | 0x55表示所有区域                                             |
| DeviceChannel | 设备路数     |      1       | 主设备：0x00                                                 |
| CRC8          | CRC8校验码   |      1       | 用于进行CRC8计算的数据DataLen指代的长度                      |
| FrameEnd      | 帧尾         |      6       | 0d 0a 0d 0a 0d 0a                                            |

**应用示例：**

```javascript
41 0C2A4314 004A00 FE E013 04 0001 01 00 E1 0D0A0D0A0D0A
```

#### 3.2、(Redis)=>`SERIAL_CMD_ACK`  接收数据格式

```json
{
    "isRight":true,
    "msg":"CRC8 OK",
    "addr":"0C2143A4",                 		
    "recvData":"FEE01304C0010100"
}
```

- `isRight`: 数据帧CRC8校验是否通过
- `msg`：提示信息
- `addr`：设备硬件地址
- `recvData`：串口接收到的数据帧



------

### 3、传感器通用回执（SERIAL_CMD_ACK：E015）

#### 3.1、传感器通用回执数据帧格式

|   字节索引   |     0     |  1\|2   |    3    |     4\|5     |      6      |   7    |    8    |   9    |      10-17       |  18  |       19-24       |
| :----------: | :-------: | :-----: | :-----: | :----------: | :---------: | :----: | :-----: | :----: | :--------------: | :--: | :---------------: |
|    数据域    | FrameHead | FrameId | DataLen | DeviceTypeId | IsBroadcast | ZoneId | channel | status |     Allocate     | CRC8 |     FrameEnd      |
| 长度（byte） |     1     |    2    |    1    |      2       |      1      |   1    |    1    |   1    |        8         |  1   |         2         |
|   示例数据   |    FE     |  E015   |   0E    |     C001     |     55      |   01   |   00    |   00   | 0000000000000000 |  00  | 0D 0A 0D 0A 0D 0A |

协议帧各字段域说明：

| 字段域       | 说明             | 长度（byte） | 备注                                                         |
| ------------ | :--------------- | :----------: | :----------------------------------------------------------- |
| FrameHead    | 帧头             |      2       | FE                                                           |
| FrameId      | 帧ID             |      2       | E012                                                         |
| DataLen      | 数据长度         |      1       | 从此位后开始计算（不包含自身），一直到`CRCR8`位结束（不包括CRC8位） |
| DeviceTypeId | 设备类型ID       |      2       | 查看设备类型对照表（5555：所有类型）                         |
| IsBroadcast  | 是否广播指令     |      1       | 0x55是，00否                                                 |
| ZoneId       | 所属区域Id       |      1       | 0x55表示所有区域                                             |
| Addr         | 设备地址         |      4       | 设备地址（全部为55555555）                                   |
| status       | 设备当前工作状态 |      1       | 对应回执状态表                                               |
| Allocate     | 预留字段         |      8       | 预留做他用                                                   |
| CRC8         | CRC8校验码       |      1       | 用于进行CRC8计算的数据DataLen指代的长度                      |
| FrameEnd     | 帧尾             |      6       | 0d 0a 0d 0a 0d 0a                                            |

**应用示例：**

ID为`14052A0C`的LoRa设备通用回执（收到查询参数指令）：

```
410C2A4314006100  FE E015 0D 0001 01 00 01 0000000000000000 16 0D0A0D0A0D0A
```

#### 3.2、(Redis)=>`SERIAL_CMD_ACK`  接收数据格式

```json
{
    "isRight":true,
    "msg":"CRC8 OK",
    "addr":"0C2143A4",                 		
    "recvData":"FEE0150D00010100010000000000000000"
}
```

- `isRight`: 数据帧CRC8校验是否通过
- `msg`：提示信息
- `addr`：设备硬件地址
- `recvData`：串口接收到的通用回执数据帧

#### 3.3、传感器公共通用回执定义

**0x00~0x08所有传感器都有下表状态**

```json
{
"00":"出厂模式",
"01":"查询LoRa设备参数成功",
"02":"查询LoRa设备参数失败",
"03":"设置组Id数组成功",
"04":"设置组Id数组失败",
"05":"设置SN及子设备路数成功",
"06":"设置SN及子设备路数失败",
"07":"设置上报时间间隔成功",
"08":"设置上报时间间隔失败"
}
```

#### 3.4、####################

#### **私有通用回执状态表在此处定义**

####  #########################

**私有状态0x09~0xFF，每种传感器单独定义**

```json

```

------



### 4、设置传感器Sn（SYS_CMD：SET_SN_COUNT）

- Redis接收到Web端设置指令，通过**channel-->`SYS_CMD`**返回，**method**为**`SET_SN_COUNT`**;正确解析为本服务所属类型设备上报则调用**`Common.ActuatorSetDeviceSnAndChannel(deviceTypeAlias, setSnDeviceAddr, deviceTypeId, channel, zoneId, newdeviceSn)`**函数执行设置操作，该function将合成串口设备指令，发送给指定设备配置新设备SN及路数
- 传感器主控设备接收到设置指令，完成入网设置操作，通过通用回执回复状态到`ACTUATOR_ACK`

#### 4.1、(Redis)=>`SYS_CMD`  接收数据格式

```json
{
    "confTyp": "LORA_COMMON_CMD",
    "method": "SET_SN_COUNT",
    "para": {
        "deviceAddr": "0C2A4314",
        "deviceType":"LoRa_11Factor_Type_A",
        "channel":0,
        "zoneId":2,
        "newdeviceSn":"000120190304150001"
    }
}
```

- `confTyp`: 配置类型
- `method`：指令方法
- `para`：参数
  - `para.deviceAddr`：设备硬件地址
  - `para.deviceType`:设备类型
  - `para.zoneId`：区域Id
  - `para.newdeviceSn`:设置的新SN



#### 4.2、设置传感器Sn数据帧格式（A013）

|   字节索引   |       N/A       |   N/A    |     N/A      |     0     |  1\|2   |    3    |     4\|5     |      6      |   7    |       8       |      9      |       10-18        |  19  |       20-25       |
| :----------: | :-------------: | :------: | :----------: | :-------: | :-----: | :-----: | :----------: | :---------: | :----: | :-----------: | :---------: | :----------------: | :--: | :---------------: |
|    数据域    | DeviceFrameHead |   Addr   | DeviceOthers | FrameHead | FrameId | DataLen | DeviceTypeId | IsBroadcast | ZoneId | DeviceChannel | SlaverCount |      DeviceSn      | CRC8 |     FrameEnd      |
| 长度（byte） |        1        |    4     |      3       |     1     |    2    |    1    |      2       |      1      |   1    |       1       |      1      |         9          |  1   |         2         |
|   示例数据   |       61        | 14052A0C |   00 XXXX    |    FE     |  A013   |   0F    |     0001     |     55      |   01   |      00       |     00      | 000000000000000000 |  00  | 0D 0A 0D 0A 0D 0A |

协议帧各字段域说明：

| 字段域          | 说明             | 长度（byte） | 备注                                                         |
| --------------- | :--------------- | :----------: | :----------------------------------------------------------- |
| DeviceFrameHead | 硬件帧头         |      1       | 仁钰LoRa M-KL9按地址发送时需要                               |
| Addr            | 设备地址         |      4       | 00000071(广播，所有设备上报自己的ID和SN)                     |
| DeviceOthers    | 控制字等         |      3       | 仁钰LoRa M-KL9按地址发送时需要                               |
| FrameHead       | 帧头             |      1       | FE                                                           |
| FrameId         | 帧ID             |      2       | A013                                                         |
| DataLen         | 数据长度         |      1       | 从此位后开始计算（不包含自身），一直到`CRCR8`位结束（不包括CRC8位） |
| DeviceTypeId    | 设备类型ID       |      2       | 查看设备类型对照表                                           |
| IsBroadcast     | 是否广播指令     |      1       | 0x55是，00否                                                 |
| ZoneId          | 所属区域Id       |      1       | 0x55表示所有区域                                             |
| DeviceChannel   | 设备路数         |      1       | 主设备：0x00                                                 |
| SlaverCount     | 子设备总路数     |      1       | 子设备总数                                                   |
| DeviceSn        | 设置的LoRa设备SN |      9       |                                                              |
| CRC8            | CRC8校验码       |      1       | 用于进行CRC8计算的数据DataLen指代的长度                      |
| FrameEnd        | 帧尾             |      6       | 0d 0a 0d 0a 0d 0a                                            |

**应用示例：**

```javascript
61 14432A0C 000100 FE A013 0E C001 01 00 02 C00120190304150001 15 0D0A0D0A0D0A
```

#### 4.3、(Redis)=>`SERIAL_CMD`发送数据格式

- 调用**`Common.SensorSetDeviceSnAndChannel(deviceTypeAlias, setSnDeviceAddr, deviceTypeId, channel, zoneId, newdeviceSn)`**函数实现数据发送功能



### 6、设置传感器RTC时间和采集时间间隔(SYS_CMD：SET_RTC_INTERVAL)

- Redis接收到Web端设置指令，通过**channel-->`SYS_CMD`**返回，**method**为**`SET_SN_COUNT`**;正确解析为本服务所属类型设备上报则调用**`Common.ActuatorSetDeviceSnAndChannel(deviceTypeAlias, setSnDeviceAddr, deviceTypeId, channel, zoneId, newdeviceSn)`**函数执行设置操作，该function将合成串口设备指令，发送给指定设备配置新设备SN及路数
- 传感器主控设备接收到设置指令，完成入网设置操作，通过通用回执回复状态到`ACTUATOR_ACK`

#### 4.1、(Redis)=>`SYS_CMD`  接收数据格式

```json
{
    "confTyp": "LORA_COMMON_CMD",
    "method": "SET_SN_COUNT",
    "para": {
        "deviceAddr": "0C2A4314",
        "deviceType":"LoRa_11Factor_Type_A",
        "channel":0,
        "zoneId":2,
        "newdeviceSn":"000120190304150001"
    }
}
```

- `confTyp`: 配置类型
- `method`：指令方法
- `para`：参数
  - `para.deviceAddr`：设备硬件地址
  - `para.deviceType`:设备类型
  - `para.zoneId`：区域Id
  - `para.newdeviceSn`:设置的新SN



#### 4.2、设置传感器Sn（A013）

**ZoneId=0x55,intent=0x00,channel=0x00设置参数**,地址为广播地址，设置某类型所有设备

#### 协议帧格式

|   字节索引   |       N/A       |   N/A    |     N/A      |     0     |  1\|2   |    3    |     4\|5     |   6    |   7    |    8    |   9-10   |     11-17      |      18-25       |  26  |       27-31       |
| :----------: | :-------------: | :------: | :----------: | :-------: | :-----: | :-----: | :----------: | :----: | :----: | :-----: | :------: | :------------: | :--------------: | :--: | :---------------: |
|    数据域    | DeviceFrameHead |   Addr   | deviceOthers | FrameHead | FrameId | DataLen | DeviceTypeId | ZoneId | intent | channel | Interval |    NewTime     |     Allocate     | CRC8 |     FrameEnd      |
| 长度（byte） |        1        |    4     |      3       |     1     |    2    |    1    |      2       |   1    |   1    |    1    |    2     |       7        |        8         |  1   |         2         |
|   示例数据   |       61        | 00000071 |   00 XXXX    |    FE     |  A011   |   1A    |     C001     |   01   |   00   |   00    |  00 3C   | 20180824141702 | 0000000000000000 |  00  | 0D 0A 0D 0A 0D 0A |

协议帧各字段域说明：

| 字段域          | 说明                     | 长度（byte） | 备注                                                         |
| --------------- | :----------------------- | :----------: | :----------------------------------------------------------- |
| DeviceFrameHead | 硬件帧头                 |      1       | LoRa 按地址发送时需要                                        |
| Addr            | 设备地址                 |      4       | 00000071(广播，所有设备上报自己的ID和SN)                     |
| deviceOthers    | 控制字等                 |      3       | LoRa 按地址发送时需要                                        |
| FrameHead       | 帧头                     |      2       | FE                                                           |
| FrameId         | 帧ID                     |      2       | A011                                                         |
| DataLen         | 数据长度                 |      1       | 从此位后开始计算（不包含自身），一直到`CRCR8`位结束（不包括CRC8位） |
| DeviceTypeId    | 设备类型ID               |      2       | 查看设备类型对照表（5555：所有类型）                         |
| ZoneId          | 所属区域Id               |      1       | 0x55表示所有区域                                             |
| intent          | 要求LoRa设备重新请求分号 |      1       | 0x00：不请求只设置参数，0x55：重新请求                       |
| channel         | 查询角色                 |      1       | 0x00：表示主控，0x55:表示所有设备参数，其他表示相应路数的子设备 |
| Interval        | LoRa设备的采集时间间隔   |      2       | 十六进制整数，单位为秒                                       |
| NewTime         | 新设置的RTC时间          |      7       | BCD码值，如`20180824141702`代表`2018年8月24日14点17分零2秒`  |
| Allocate        | 预留字段                 |      8       | 预留做他用                                                   |
| CRC8            | CRC8校验码               |      1       | 用于进行CRC8计算的数据DataLen指代的长度                      |
| FrameEnd        | 帧尾                     |      6       | 0d 0a 0d 0a 0d 0a                                            |

**应用示例：**

设置类型为11因素传感器的所有传感器采集间隔为`60`秒，新设置的RTC时间为`2018年8月24日15时20分12秒`，其指令如下：

```shell
61 00000071 000100 FE A011 1A 0001 01 00 00 003C 20190307114315 0000000000000000 ED 0D0A0D0A0D0A
```



# 问题反馈

### 请在gitee的issue提交发现的BUG,如果您已经解决该问题比进行了充分的测试，可提交Pull Requests到主仓库，我将及时处理您的合并请求

**仓库地址：** https://gitee.com/SHHOO_ARGRICULTRUE/otherAdapterTemplate.git

**Email:** 474667749@qq.com ;  sharpqian@hotmail.com

**Tel:** 13577612570

**微信:** wx474667749

