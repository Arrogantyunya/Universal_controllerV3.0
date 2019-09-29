//user_lorainit.cpp
/*
*版权
*
* 文件名称:user_lorainit.cpp
* 文件标识:配置管理计划书
* 摘要:
*
* 当前版本:V2.0
* 作者:刘家辉
* 完成日期:2019-8-13
* 修改者:刘家辉
* 修改日期:2019-8-13
* 修改:设置了组播地址，然后增加了读取ADDR的地址重新写入ADDR，优化了运行逻辑
*
* 取代版本:V1.0
* 原作者:刘家辉
* 完成日期:
*/

#include "user_lorainit.h"



//函 数 名：LORA_Initialization() 
//功能描述：
//函数说明：LORA初始化的函数
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
int LORA_Initialization()//LORA初始化函数
{
	//对未设置过的LORA进行设置
	//更改TFREQ，RFREQ、TSF，RSF

	//先设置LORA引脚的初始化
	// digitalWrite(LORA_PWR,HIGH);			//开启LORA的电源
	// digitalWrite(RESETN,HIGH);			//防止LORA进行复位
	// digitalWrite(AT_CMD,LOW);			//将LORA设置为透传

	if (debug_print == 1)
	{
		Serial.println("进入LORA_Initialization函数");
	}

	Serial.println("M-HL9:LORA Setup Begin");
	digitalWrite(AT_CMD, HIGH);
	delay(500);

	//先测试AT指令是否OK
	delay(100);
	Serial3.print("AT\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len] = Serial3.read();
		lora_len++;
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		/*for (size_t i = 0; i < lora_len; i++)
		{
			Serial.println(String("lora_data [") + String(i) + String("]=") + String(lora_data[i]));
		}*/
		lora_len = 0;
		if (lora_data[48] == 79 && lora_data[49] == 75)
		{
			Serial.println("AT Successful setup");
			lora_Completion_Degree = 0;//0
		}
		else
		{
			Serial.println("AT Setup failed");
		}
	}
	//然后设置NET
	//00为	Node to Node;	01为	Node to Gateway
	delay(100);
	if (LORA_NET == 0)
	{
		Serial3.print(String("AT+NET=00\r\n"));
	}
	else if (LORA_NET == 1)
	{
		Serial3.print(String("AT+NET=01\r\n"));
	}
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len] = Serial3.read();
		lora_len++;
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		/*for (size_t i = 0; i < lora_len; i++)
		{
			Serial.println(String("lora_data [") + String(i) + String("]=") + String(lora_data[i]));
		}*/
		lora_len = 0;
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("NET Successful setup");
			lora_Completion_Degree++;//1
			Serial.println(String("lora_Completion_Degree = ") + String(lora_Completion_Degree));
		}
		else
		{
			Serial.println("NET Setup failed");
		}
	}
	//然后设置TFREQ、RFREQ发送频点以及接收频点
	delay(100);
	Serial3.print(String("AT+TFREQ=1C578DE0\r\n"));
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len] = Serial3.read();
		lora_len++;
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("TFREQ Successful setup");
			lora_Completion_Degree++;//2
			Serial.println(String("lora_Completion_Degree = ") + String(lora_Completion_Degree));
		}
		else
		{
			Serial.println("TFREQ Setup failed");
		}
	}
	//设置RRFREQ
	delay(100);
	Serial3.print("AT+RFREQ=1C03A180\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("RFREQ Successful setup");
			lora_Completion_Degree++;//3
			Serial.println(String("lora_Completion_Degree = ") + String(lora_Completion_Degree));
		}
		else
		{
			Serial.println("RFREQ Setup failed");
		}
	}
	//设置发送功率
	//14为20dbm
	delay(100);
	Serial3.print("AT+POW=14\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("POW Successful setup");
			lora_Completion_Degree++;//4
			Serial.println(String("lora_Completion_Degree = ") + String(lora_Completion_Degree));
		}
		else
		{
			Serial.println("POW Setup failed");
		}
	}
	//设置调制带宽
	//07为125KHZ
	delay(100);
	Serial3.print("AT+BW=07\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("BW Successful setup");
			lora_Completion_Degree++;//5
			Serial.println(String("lora_Completion_Degree = ") + String(lora_Completion_Degree));
		}
		else
		{
			Serial.println("BW Setup failed");
		}
	}
	//设置TSF发送扩频
	//09代表09
	delay(100);
	Serial3.print("AT+TSF=09\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("TSF Successful setup");
			lora_Completion_Degree++;//6
			Serial.println(String("lora_Completion_Degree = ") + String(lora_Completion_Degree));
		}
		else
		{
			Serial.println("TSF Setup failed");
		}
	}

	//设置RSF接收扩频
	//09代表09
	delay(100);
	Serial3.print("AT+RSF=09\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("RSF Successful setup");
			lora_Completion_Degree++;//7
			Serial.println(String("lora_Completion_Degree = ") + String(lora_Completion_Degree));
		}
		else
		{
			Serial.println("RSF Setup failed");
		}
	}

	//设置CR编码速率
	//01代表4/5
	delay(100);
	Serial3.print("AT+CR=01\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("CR Successful setup");
			lora_Completion_Degree++;//8
			Serial.println(String("lora_Completion_Degree = ") + String(lora_Completion_Degree));
		}
		else
		{
			Serial.println("CR Setup failed");
		}
	}

	//设置MODE调制方式
	//01为LORA调制方式
	delay(100);
	Serial3.print("AT+MODE=01\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("MODE Successful setup");
			lora_Completion_Degree++;//9
			Serial.println(String("lora_Completion_Degree = ") + String(lora_Completion_Degree));
		}
		else
		{
			Serial.println("MODE Setup failed");
		}
	}

	//设置SYNC同步字
	//12代表0x12
	delay(100);
	Serial3.print("AT+SYNC=12\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("SYNC Successful setup");
			lora_Completion_Degree++;//10
			Serial.println(String("lora_Completion_Degree = ") + String(lora_Completion_Degree));
		}
		else
		{
			Serial.println("SYNC Setup failed");
		}
	}

	/*//-------------------------------------------------------
	//这里PREM设置不了，回复ER00
	//设置PREM前导码
	//08代表默认值
	Serial3.print("AT+PREM=08\r\n");
	while(Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data,lora_len);
		lora_len = 0;
		delay(500);
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("是否设置成功");
		}
	}
	//-------------------------------------------------------*/

	//设置CRC硬件CRC
	//01代表有CRC校验
	delay(100);
	Serial3.print("AT+CRC=01\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("CRC Successful setup");
			lora_Completion_Degree++;//11
			Serial.println(String("lora_Completion_Degree = ") + String(lora_Completion_Degree));
		}
		else
		{
			Serial.println("CRC Setup failed");
		}
	}

	//设置TIQ发送反转
	//00为不反转
	delay(100);
	Serial3.print("AT+TIQ=00\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("TIQ Successful setup");
			lora_Completion_Degree++;//12
			Serial.println(String("lora_Completion_Degree = ") + String(lora_Completion_Degree));
		}
		else
		{
			Serial.println("TIQ Setup failed");
		}
	}

	//设置RIQ接收反转
	//00为不反转
	delay(100);
	Serial3.print("AT+RIQ=00\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("RIQ Successful setup");
			lora_Completion_Degree++;//13
			Serial.println(String("lora_Completion_Degree = ") + String(lora_Completion_Degree));
		}
		else
		{
			Serial.println("RIQ Setup failed");
		}
	}

	//设置SEQ数据包编号、设置IP模块地址功能
	//01为带地址不带包序
	delay(100);
	Serial3.print("AT+SIP=01\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("SIP Successful setup");
			lora_Completion_Degree++;//14
			Serial.println(String("lora_Completion_Degree = ") + String(lora_Completion_Degree));
		}
		else
		{
			Serial.println("SIP Setup failed");
		}
	}

	/*//-------------------------------------------------------
	//设置不成功
	//设置AES模块AES通信加密
	//
	Serial3.print("AT+AES=00000000000000000000000000000000\r\n");
	while(Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data,lora_len);
		lora_len = 0;
		delay(500);
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("是否设置成功");
		}
	}
	//-------------------------------------------------------*/

	//设置ACK数据包应答功能
	//00代表不应答
	delay(100);
	Serial3.print("AT+ACK=00\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("ACK Successful setup");
			lora_Completion_Degree++;//15
			Serial.println(String("lora_Completion_Degree = ") + String(lora_Completion_Degree));
		}
		else
		{
			Serial.println("ACK Setup failed");
		}
	}
	//设置LDR低速率优化
	//00代表AUTO
	delay(100);
	Serial3.print("AT+LDR=00\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("LDR Successful setup");
			lora_Completion_Degree++;//16
			Serial.println(String("lora_Completion_Degree = ") + String(lora_Completion_Degree));
		}
		else
		{
			Serial.println("LDR Setup failed");
		}
	}

	//设置MADDR组播地址
	delay(100);
	Serial3.print("AT+MADDR=71000000\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("MADDR Successful setup");
			lora_Completion_Degree++;//17
			Serial.println(String("lora_Completion_Degree = ") + String(lora_Completion_Degree));
		}
		else
		{
			Serial.println("MADDR Setup failed");
		}
	}
	else
	{
		Serial.println("MADDR Setting up no receipt");
	}


	//查询
	delay(500);
	Serial3.print("AT+TFREQ?\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		delay(100);
	}
	delay(100);

	Serial3.print("AT+RFREQ?\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		lora_len = 0;
		delay(100);
	}
	delay(100);

	Serial3.print("AT+SYNC?\r\n");
	Serial3.flush();
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		delay(100);
	}
	delay(100);

	Serial3.print("AT+POW?\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		delay(100);
	}
	delay(100);

	Serial3.print("AT+BW?\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		delay(100);
	}
	delay(100);

	Serial3.print("AT+CR?\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		delay(100);
	}
	delay(100);

	Serial3.print("AT+CRC?\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		delay(100);
	}
	delay(100);

	Serial3.print("AT+TSF?\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		delay(100);
	}
	delay(100);

	Serial3.print("AT+RSF?\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		delay(100);
	}
	delay(100);

	Serial3.print("AT+ADDR?\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		if (debug == 1)
		{
			/*for (size_t i = 0; i < lora_len; i++)
			{
				Serial.println(lora_data[i]);
			}*/
		}
		delay(100);
		Serial3.print(String("AT+ADDR=") + String(addr_write()) + String("\r\n"));
		//addr_write();
		Serial3.flush();
		lora_len = 0;
		delay(100);
		while (Serial3.available() > 0)
		{
			lora_data[lora_len++] = Serial3.read();
			delay(5);
		}
		if (lora_len > 0)
		{
			Serial.write(lora_data, lora_len);
			Serial.flush();
			lora_len = 0;
			if (lora_data[2] == 79 && lora_data[3] == 75)
			{
				Serial.println("ADDR Write Successful");
				lora_Completion_Degree++;//19
				Serial.println(String("lora_Completion_Degree = ") + String(lora_Completion_Degree));
			}
			else
			{
				Serial.println("ADDR Write failed");
			}
		}
	}
	delay(100);

	Serial3.print("AT+MADDR?\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		delay(100);
	}
	delay(100);


	digitalWrite(AT_CMD, LOW);		//将LORA设置为透传
	delay(10);

	if (lora_Completion_Degree == 18)
	{
		Serial.println("LORA初始化完成");
		Serial.println("LORA Initialization Setup completed");
		AT24CXX_WriteOneByte(0, 0x01);

		if (debug_print == 1)
		{
			Serial.println("结束LORA_Initialization函数");
		}

		return 1;
	}
	else
	{
		Serial.println("LORA初始化失败");
		Serial.println("LORA Initialization Setup failed");
		AT24CXX_WriteOneByte(0, 0x00);

		if (debug_print == 1)
		{
			Serial.println("结束LORA_Initialization函数");
		}

		return 0;
	}
}

String addr_write()
{
	String addr_data;
	unsigned long _addr_data;
	unsigned long x[8];
	String y[8];
	Serial.println("-------");

	for (size_t i = 8; i < lora_len - 2; i++)
	{
		if (debug_print == 1)
		{
			//Serial.println(lora_data[i]);//输出值
		}

		//如果值在0~9之间
		if (lora_data[i] >= 48 && lora_data[i] <= 57)
		{
			x[i - 8] = lora_data[i] - 48;
			if (lora_data[i] == 48)
			{
				y[i - 8] = String(0, HEX);
			}
			else if (lora_data[i] == 49)
			{
				y[i - 8] = String(1, HEX);
			}
			else if (lora_data[i] == 50)
			{
				y[i - 8] = String(2, HEX);
			}
			else if (lora_data[i] == 51)
			{
				y[i - 8] = String(3, HEX);
			}
			else if (lora_data[i] == 52)
			{
				y[i - 8] = String(4, HEX);
			}
			else if (lora_data[i] == 53)
			{
				y[i - 8] = String(5, HEX);
			}
			else if (lora_data[i] == 54)
			{
				y[i - 8] = String(6, HEX);
			}
			else if (lora_data[i] == 55)
			{
				y[i - 8] = String(7, HEX);
			}
			else if (lora_data[i] == 56)
			{
				y[i - 8] = String(8, HEX);
			}
			else if (lora_data[i] == 57)
			{
				y[i - 8] = String(9, HEX);
			}
		}
		//如果值在A~F之间
		else if (lora_data[i] >= 65 && lora_data[i] <= 70)
		{
			x[i - 8] = lora_data[i] - 55;
			if (lora_data[i] == 65)
			{
				y[i - 8] = String(10, HEX);
			}
			else if (lora_data[i] == 66)
			{
				y[i - 8] = String(11, HEX);
			}
			else if (lora_data[i] == 67)
			{
				y[i - 8] = String(12, HEX);
			}
			else if (lora_data[i] == 68)
			{
				y[i - 8] = String(13, HEX);
			}
			else if (lora_data[i] == 69)
			{
				y[i - 8] = String(14, HEX);
			}
			else if (lora_data[i] == 70)
			{
				y[i - 8] = String(15, HEX);
			}
		}
	}

	if (debug_print == 1)
	{
		/*for (size_t i = 0; i < 8; i++)
		{
			Serial.println(String("x[") + String(i) + String("] = ") + String(x[i]));
		}*/
	}

	for (size_t i = 0; i < 8; i++)
	{
		addr_data.concat(String(y[i]));//连接字符串
		if (debug_print == 1)
		{
			Serial.println(String(y[i]));
			Serial.println(addr_data);
		}
	}
	if (debug_print == 1)
	{
		Serial.println("-------");
	}
	addr_data.toUpperCase();//大写转换
	if (debug_print == 1)
	{
		Serial.println(addr_data);
	}

	//15 * (16 ^ 2) + 15 * (16 ^ 1) + 15 * (16 ^ 0)
	//_addr_data = x[7] * (16 ^ 0) + x[6] * (16 ^ 6) + x[5] * (16 ^ 5) +...
	//for (int i = 7; i >= 0; i--)
	//{
	//	_addr_data = _addr_data + (x[i] * (pow(16, (7 - i))));
	//	delay(5);
	//	if (debug_print == 1)
	//	{
	//		//Serial.println(x[i] * (pow(16, (7 - i))));
	//	}
	//}
	//if (debug_print == 1)
	//{
	//	Serial.println(_addr_data);
	//	Serial.println(_addr_data,HEX);
	//	addr_data = String(_addr_data, HEX);
	//}
	//addr_data.toUpperCase();//大写转换
	//Serial.println(addr_data);

	//addr_data = String("18240E0C");

	return addr_data;
}

//函 数 名：LORA_Receive_information() 
//功能描述：负责接收LORA接收到的信息然后传给Judgement_function()
//函数说明：
//调用函数：Judgement_function()
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
void LORA_Receive_information(void)
{
	//do {
	//		while (Serial3.available() > 0)//接收串口收到的数据
	//		{
	//			if (Receive_Length >= 200) break;
	//			Receive_Data[Receive_Length++] = Serial3.read();
	//			Serial.print(Receive_Data[Receive_Length - 1], HEX);
	//			Serial.print(" ");
	//			delay(5);
	//		}
	//	if (Receive_Length >= 60) Receive_Length = 0;

	//} while (1);
	/*if (Serial3.available() > 0)
	{
		delay(5000);
	}*/
	Receive_Length = 0;
	while (Serial3.available() > 0)//接收串口收到的数据
	{
		if (Receive_Length >= 127) break;
		Receive_Data[Receive_Length++] = Serial3.read();
		Serial.print(Receive_Data[Receive_Length - 1], HEX);
		Serial.print(" ");
		delay(5);
	}
	if (Receive_Length > 0)
	{
		//Serial.write(Receive_Data,Receive_Length);//发16进制，自动转成ASCII码
		//Judgement_Length = 0;//收到新消息清空判断数组的长度值
		Check_Length = 0;//收到新消息清空校验数组的长度值
		Receive_data_lamp();
		if (debug_print == 1)
		{
			Serial.println("");
			Serial.print("Receive_Length = ");//输出接收到的数据长度
			Serial.println(Receive_Length);
		}

		//--------------------------------------------------------
		//将Receive_Data的值处理得到Check_Data
		Check_Length = 0;
		for (int i = 4; i < Receive_Length - 0x07; i++)
		{
			if (Check_Length >= 127)
			{
				Serial.println("!!!Check_Length >= 200!!!");
				break;
			}
			Check_Data[Check_Length] = Receive_Data[i];
			if (debug_print == 1)
			{
				//Serial.print("Check_Data ");
				//Serial.print(Check_Length);
				//Serial.print(" :");
				//Serial.println(Check_Data[Check_Length], HEX);
			}
			Check_Length++;
			delay(5);
		}
		Serial.print("Check_Length = ");
		Serial.println(Check_Length);
		//--------------------------------------------------------

		if (Check_Length > 0)
		{
			CRC_Check_num = GetCrc8(Check_Data, Check_Length);
			if (debug_print == 1)
			{
				Serial.print("CRC8计算的值CRC_Check_num为：0x");
				Serial.println(CRC_Check_num, HEX);
			}
		}

		//--------------------------------------------------------
		//if (debug_crc == 1)
		//{
		//	CRC_Check_num = 0xD6;//这行代码是为了不让我每次都计算CRC，实际使用请注释
		//}
		//--------------------------------------------------------

		Judgement_function(Receive_Data, Receive_Length - 1, CRC_Check_num);//判断函数

		Receive_Length = 0;	//将Receive_Length清零
		Check_Length = 0;	//将Check_Length清零
	}


	//-----------------------------------------------------------------------------------------------------
	//if (Serial3.available())
	//{
	//	LORA_RecData1 = Serial3.readString();
	//}
	//if (LORA_RecData1.length() > 0)
	//{
	//	LORA_RecData2 = LORA_RecData1;
	//	Receive_data_lamp();
	//	// void remove (index,count)
	//	//index为必选参数，表示从哪里开始删除，只填这一个参数，会将字符串从索引值开始一直到结尾的所有字符删除
	//	//第二个参数count表示删除多少个字符
	//	//作用到字符串的本身
	//	LORA_RecData1.remove(0, LORA_RecData1.length());
	//	Judgement_Length = 0;//收到新消息清空判断数组的长度值
	//	Check_Length = 0;//收到新消息清空校验数组的长度值

	//	char const *c = LORA_RecData2.c_str();

	//	if (debug_print == 1)
	//	{
	//		Serial.println(String("LORA_RecData2.length()= ") + String(LORA_RecData2.length()));
	//		Serial.println("接收到的数据为：");
	//		//Serial.write(c);
	//		//int shuzu_length = LORA_RecData2.length();
	//		byte shuzu[50];
	//		LORA_RecData2.getBytes(shuzu, (LORA_RecData2.length()+1));
	//		//LORA_RecData2.toCharArray(shuzu, (LORA_RecData2.length() + 1));
	//		for (size_t i = 0; i < LORA_RecData2.length(); i++)
	//		{
	//			Serial.print(String(i) + String(" / "));
	//			Serial.println(shuzu[i]);
	//		}
	//	}
	//}
}
