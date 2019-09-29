// user_Public_directive.h
/*
*版权
*
* 文件名称:user_Public_directive.h
* 文件标识:配置管理计划书
* 摘要:
*
* 当前版本:V1.0
* 作者:刘家辉
* 完成日期:
* 修改者:
* 修改日期:
*
* 取代版本:
* 原作者:刘家辉
* 完成日期:
 */

#ifndef _USER_PUBLIC_DIRECTIVE_h
#define _USER_PUBLIC_DIRECTIVE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include<arduino.h>	//引用标准库的头文件
#include"user_initialization.h"//初始化
#include"user_crc8.h"//CRC校验
#include"user_judgement.h"//判断
#include "user_Set_Correlation.h"
#include "user_initialization.h"



//宏定义
//定义在此处的宏定义为存储位置对应的名称
#define A_LORA_SetOK_flag					0	//LORA初始化完成的标志位
#define A_EEP_SetOK_flag					1	//EEPROM初始化完成的标志位
#define A_Register_OK_flag					2	//已经完成申号的标志位

#define A_SN_1								3	//存储LORA主设备的SN第1位
#define A_SN_2								4	//存储LORA主设备的SN第2位
#define A_SN_3								5	//存储LORA主设备的SN第3位
#define A_SN_4								6	//存储LORA主设备的SN第4位
#define A_SN_5								7	//存储LORA主设备的SN第5位
#define A_SN_6								8	//存储LORA主设备的SN第6位
#define A_SN_7								9	//存储LORA主设备的SN第7位
#define A_SN_8								10	//存储LORA主设备的SN第8位
#define A_SN_9								11	//存储LORA主设备的SN第9位

#define A_ZoneID							12	//存储LORA主设备所在的区域

#define A_Policy_Relevance_flag				13	//策略语句的个数，大于0代表存在自动策略

#define A_C003_Channel_1_SlaverTypeId_1		14	//数字输出【C003】路数1的子设备类型第1位
#define A_C003_Channel_1_SlaverTypeId_2		15	//数字输出【C003】路数1的子设备类型第2位
#define A_C003_Channel_1_GroupID_1			16	//数字输出【C003】路数1的工作组数组第1位
#define A_C003_Channel_1_GroupID_2			17	//数字输出【C003】路数1的工作组数组第2位
#define A_C003_Channel_1_GroupID_3			18	//数字输出【C003】路数1的工作组数组第3位
#define A_C003_Channel_1_GroupID_4			19	//数字输出【C003】路数1的工作组数组第4位
#define A_C003_Channel_1_GroupID_5			20	//数字输出【C003】路数1的工作组数组第5位

#define A_C003_Channel_2_SlaverTypeId_1		21	//数字输出【C003】路数2的子设备类型第1位
#define A_C003_Channel_2_SlaverTypeId_2		22	//数字输出【C003】路数2的子设备类型第2位
#define A_C003_Channel_2_GroupID_1			23	//数字输出【C003】路数2的工作组数组第1位
#define A_C003_Channel_2_GroupID_2			24	//数字输出【C003】路数2的工作组数组第2位
#define A_C003_Channel_2_GroupID_3			25	//数字输出【C003】路数2的工作组数组第3位
#define A_C003_Channel_2_GroupID_4			26	//数字输出【C003】路数2的工作组数组第4位
#define A_C003_Channel_2_GroupID_5			27	//数字输出【C003】路数2的工作组数组第5位

#define A_C003_Channel_3_SlaverTypeId_1		28	//数字输出【C003】路数3的子设备类型第1位
#define A_C003_Channel_3_SlaverTypeId_2		29	//数字输出【C003】路数3的子设备类型第2位
#define A_C003_Channel_3_GroupID_1			30	//数字输出【C003】路数3的工作组数组第1位
#define A_C003_Channel_3_GroupID_2			31	//数字输出【C003】路数3的工作组数组第2位
#define A_C003_Channel_3_GroupID_3			32	//数字输出【C003】路数3的工作组数组第3位
#define A_C003_Channel_3_GroupID_4			33	//数字输出【C003】路数3的工作组数组第4位
#define A_C003_Channel_3_GroupID_5			34	//数字输出【C003】路数3的工作组数组第5位

#define A_C003_Channel_4_SlaverTypeId_1		35	//数字输出【C003】路数4的子设备类型第1位
#define A_C003_Channel_4_SlaverTypeId_2		36	//数字输出【C003】路数4的子设备类型第2位
#define A_C003_Channel_4_GroupID_1			37	//数字输出【C003】路数4的工作组数组第1位
#define A_C003_Channel_4_GroupID_2			38	//数字输出【C003】路数4的工作组数组第2位
#define A_C003_Channel_4_GroupID_3			39	//数字输出【C003】路数4的工作组数组第3位
#define A_C003_Channel_4_GroupID_4			40	//数字输出【C003】路数4的工作组数组第4位
#define A_C003_Channel_4_GroupID_5			41	//数字输出【C003】路数4的工作组数组第5位

#define A_C004_Channel_1_SlaverTypeId_1		42	//模拟输出【C004】路数1的子设备类型第1位
#define A_C004_Channel_1_SlaverTypeId_2		43	//模拟输出【C004】路数1的子设备类型第2位
#define A_C004_Channel_1_GroupID_1			44	//模拟输出【C004】路数1的工作组数组第1位
#define A_C004_Channel_1_GroupID_2			45	//模拟输出【C004】路数1的工作组数组第2位
#define A_C004_Channel_1_GroupID_3			46	//模拟输出【C004】路数1的工作组数组第3位
#define A_C004_Channel_1_GroupID_4			47	//模拟输出【C004】路数1的工作组数组第4位
#define A_C004_Channel_1_GroupID_5			48	//模拟输出【C004】路数1的工作组数组第5位

#define A_C004_Channel_2_SlaverTypeId_1		49	//模拟输出【C004】路数2的子设备类型第1位
#define A_C004_Channel_2_SlaverTypeId_2		50	//模拟输出【C004】路数2的子设备类型第2位
#define A_C004_Channel_2_GroupID_1			51	//模拟输出【C004】路数2的工作组数组第1位
#define A_C004_Channel_2_GroupID_2			52	//模拟输出【C004】路数2的工作组数组第2位
#define A_C004_Channel_2_GroupID_3			53	//模拟输出【C004】路数2的工作组数组第3位
#define A_C004_Channel_2_GroupID_4			54	//模拟输出【C004】路数2的工作组数组第4位
#define A_C004_Channel_2_GroupID_5			55	//模拟输出【C004】路数2的工作组数组第5位

#define A_bool_type_reserved_field			56	//bool类型预留字段，8个

#define A_int_type_reserved_field_1			57	//int类型预留字段，8个,1/8
#define A_int_type_reserved_field_2			58	//int类型预留字段，8个,2/8
#define A_int_type_reserved_field_3			59	//int类型预留字段，8个,3/8
#define A_int_type_reserved_field_4			60	//int类型预留字段，8个,4/8
#define A_int_type_reserved_field_5			61	//int类型预留字段，8个,5/8
#define A_int_type_reserved_field_6			62	//int类型预留字段，8个,6/8
#define A_int_type_reserved_field_7			63	//int类型预留字段，8个,7/8
#define A_int_type_reserved_field_8			64	//int类型预留字段，8个,8/8

#define A_T_Timer_Reserved_Field_1			65	//T定时器预留字段，8个,1/8
#define A_T_Timer_Reserved_Field_2			66	//T定时器预留字段，8个,2/8
#define A_T_Timer_Reserved_Field_3			67	//T定时器预留字段，8个,3/8
#define A_T_Timer_Reserved_Field_4			68	//T定时器预留字段，8个,4/8
#define A_T_Timer_Reserved_Field_5			69	//T定时器预留字段，8个,5/8
#define A_T_Timer_Reserved_Field_6			70	//T定时器预留字段，8个,6/8
#define A_T_Timer_Reserved_Field_7			71	//T定时器预留字段，8个,7/8
#define A_T_Timer_Reserved_Field_8			72	//T定时器预留字段，8个,8/8

#define A_C_Counter_reserved_field_1		73	//C计数器预留字段，8个,1/8
#define A_C_Counter_reserved_field_2		74	//C计数器预留字段，8个,2/8
#define A_C_Counter_reserved_field_3		75	//C计数器预留字段，8个,3/8
#define A_C_Counter_reserved_field_4		76	//C计数器预留字段，8个,4/8
#define A_C_Counter_reserved_field_5		77	//C计数器预留字段，8个,5/8
#define A_C_Counter_reserved_field_6		78	//C计数器预留字段，8个,6/8
#define A_C_Counter_reserved_field_7		79	//C计数器预留字段，8个,7/8
#define A_C_Counter_reserved_field_8		80	//C计数器预留字段，8个,8/8

#define A_D_Delay_Reserved_Field_1			81	//D延时预留字段，8个,1/8
#define A_D_Delay_Reserved_Field_2			82	//D延时预留字段，8个,2/8
#define A_D_Delay_Reserved_Field_3			83	//D延时预留字段，8个,3/8
#define A_D_Delay_Reserved_Field_4			84	//D延时预留字段，8个,4/8
#define A_D_Delay_Reserved_Field_5			85	//D延时预留字段，8个,5/8
#define A_D_Delay_Reserved_Field_6			86	//D延时预留字段，8个,6/8
#define A_D_Delay_Reserved_Field_7			87	//D延时预留字段，8个,7/8
#define A_D_Delay_Reserved_Field_8			88	//D延时预留字段，8个,8/8

#define A_Storage_bytes_Flag				89	//存储字节的标志位，如果存储超范围，将不进行存储

#define A_Begin_policy_statement_1			90	//策略语句1的开始处
#define A_End_policy_statement_1			91	//策略语句1的结尾处
#define A_Begin_policy_statement_2			92	//策略语句2的开始处
#define A_End_policy_statement_2			93	//策略语句2的结尾处
#define A_Begin_policy_statement_3			94	//策略语句3的开始处
#define A_End_policy_statement_3			95	//策略语句3的结尾处
#define A_Begin_policy_statement_4			96	//策略语句4的开始处
#define A_End_policy_statement_4			97	//策略语句4的结尾处
#define A_Begin_policy_statement_5			98	//策略语句5的开始处
#define A_End_policy_statement_5			99	//策略语句5的结尾处

#define A_policy_statement 					100	//策略语句


 //引脚定义



 //全局变量
//static unsigned char Receive_IsBroadcast = 0x00; //是否广播指令
//--------------------------------------------------------------------
static unsigned char E011[47];//用来存放E011发送出去的数组

static int E011_FrameHead = 0xFE;		//E011的帧头

static int E011_FrameId1 = 0xE0;		//E011的帧ID1
static int E011_FrameId2 = 0x11;		//E011的帧ID2

static int E011_DataLen = 0x24;			//E011的数据长度

static int E011_DeviceTypeID1 = 0xC0;	//E011的设备类型1
static int E011_DeviceTypeID2 = 0x02;	//E011的设备类型2

static int E011_IsBroadcast = 0x00;		//E011的是否广播指令

static int E011_ZoneId = 0x01;			//E011的区域

static int E011_GroupIDArray1 = 0x01;	//E011的组ID数组1
static int E011_GroupIDArray2 = 0x00;	//E011的组ID数组2
static int E011_GroupIDArray3 = 0x00;	//E011的组ID数组3
static int E011_GroupIDArray4 = 0x00;	//E011的组ID数组4
static int E011_GroupIDArray5 = 0x00;	//E011的组ID数组5

static int E011_DeviceSN1 = 0x00;		//E011的SN1
static int E011_DeviceSN2 = 0x00;		//E011的SN2
static int E011_DeviceSN3 = 0x00;		//E011的SN3
static int E011_DeviceSN4 = 0x00;		//E011的SN4
static int E011_DeviceSN5 = 0x00;		//E011的SN5
static int E011_DeviceSN6 = 0x00;		//E011的SN6
static int E011_DeviceSN7 = 0x00;		//E011的SN7
static int E011_DeviceSN8 = 0x00;		//E011的SN8
static int E011_DeviceSN9 = 0x00;		//E011的SN9

static int E011_channel = 0x01;			//E011的路数

static int E011_interval1 = 0x00;			//E011的采集时间间隔1
static int E011_interval2 = 0x00;			//E011的采集时间间隔2

static int E011_NewTime1 = 0x00;		//E011的时间1
static int E011_NewTime2 = 0x00;		//E011的时间2
static int E011_NewTime3 = 0x00;		//E011的时间3
static int E011_NewTime4 = 0x00;		//E011的时间4
static int E011_NewTime5 = 0x00;		//E011的时间5
static int E011_NewTime6 = 0x00;		//E011的时间6
static int E011_NewTime7 = 0x00;		//E011的时间7

static int E011_Allocate1 = 0x00;		//E011的预留字段1
static int E011_Allocate2 = 0x00;		//E011的预留字段2
static int E011_Allocate3 = 0x00;		//E011的预留字段3
static int E011_Allocate4 = 0x00;		//E011的预留字段4
static int E011_Allocate5 = 0x00;		//E011的预留字段5
static int E011_Allocate6 = 0x00;		//E011的预留字段6
static int E011_Allocate7 = 0x00;		//E011的预留字段7
static int E011_Allocate8 = 0x00;		//E011的预留字段8

static int E011_CRC8 = 0x00;			//E011的CRC8校验码

static int E011_FrameEnd1 = 0x0D;		//E011的帧尾1
static int E011_FrameEnd2 = 0x0A;		//E011的帧尾2
static int E011_FrameEnd3 = 0x0D;		//E011的帧尾3
static int E011_FrameEnd4 = 0x0A;		//E011的帧尾4
static int E011_FrameEnd5 = 0x0D;		//E011的帧尾5
static int E011_FrameEnd6 = 0x0A;		//E011的帧尾6

static unsigned char E011_Check_Data[50];   //用来存放接收到的数据
static int E011_Check_Length = 0;
//--------------------------------------------------------------------

//--------------------------------------------------------------------
static unsigned char E014[37];//用来存放E014发送出去的数组

static unsigned char LORA_Re_Data[50];		//查询信号时接收的数组
static int LORA_Re_Length = 0;				//查询信号时数组的长度

static int E014_FrameHead = 0xFE;		//E014的帧头

static int E014_FrameId1 = 0xE0;		//E014的帧ID1
static int E014_FrameId2 = 0x14;		//E014的帧ID2

static int E014_DataLen = 0x1A;			//E014的数据长度

static int E014_DeviceTypeID1 = 0xC0;	//E014的设备类型1
static int E014_DeviceTypeID2 = 0x02;	//E014的设备类型2

static int E014_IsBroadcast = 0x00;		//E014的是否广播指令

static int E014_ZoneId = 0x00;			//E014的区域

static int E014_channel = 0x00;			//E014的子设备路数

static int E014_Status = 0x00;			//E014的状态值被声明成了枚举

static int E014_Vol1 = 0x00;
static int E014_Vol2 = 0x00;

static int E014_Rssi = 0x00;

static int E014_Csq = 0x00;

static int E014_Allocate1 = 0x00;		//E014的Allocate1
static int E014_Allocate2 = 0x00;		//E014的Allocate2
static int E014_Allocate3 = 0x00;		//E014的Allocate3
static int E014_Allocate4 = 0x00;		//E014的Allocate4
static int E014_Allocate5 = 0x00;		//E014的Allocate5
static int E014_Allocate6 = 0x00;		//E014的Allocate6
static int E014_Allocate7 = 0x00;		//E014的Allocate7
static int E014_Allocate8 = 0x00;		//E014的Allocate8
static int E014_Allocate9 = 0x00;		//E014的Allocate9
static int E014_Allocate10 = 0x00;		//E014的Allocate10
static int E014_Allocate11 = 0x00;		//E014的Allocate11
static int E014_Allocate12 = 0x00;		//E014的Allocate12
static int E014_Allocate13 = 0x00;		//E014的Allocate13
static int E014_Allocate14 = 0x00;		//E014的Allocate14
static int E014_Allocate15 = 0x00;		//E014的Allocate15
static int E014_Allocate16 = 0x00;		//E014的Allocate16

static int E014_CRC8 = 0x00;			//E014的CRC8校验码

static int E014_FrameEnd1 = 0x0D;		//E014的帧尾1
static int E014_FrameEnd2 = 0x0A;		//E014的帧尾2
static int E014_FrameEnd3 = 0x0D;		//E014的帧尾3
static int E014_FrameEnd4 = 0x0A;		//E014的帧尾4
static int E014_FrameEnd5 = 0x0D;		//E014的帧尾5
static int E014_FrameEnd6 = 0x0A;		//E014的帧尾6
//--------------------------------------------------------------------
static unsigned char E015[25];//用来存放E015发送出去的数组

static int E015_FrameHead = 0xFE;		//E015的帧头

static int E015_FrameId1 = 0xE0;		//E015的帧ID1
static int E015_FrameId2 = 0x15;		//E015的帧ID2

static int E015_DataLen = 0x0E;			//E015的数据长度

static int E015_DeviceTypeID1 = 0xC0;	//E015的设备类型1
static int E015_DeviceTypeID2 = 0x02;	//E015的设备类型2

static int E015_IsBroadcast = 0x00;		//E015的是否广播指令

static int E015_ZoneId = 0x00;			//E015的区域

static int E015_channel = 0x00;			//E015的子设备路数

static int E015_Status = 0x00;			//E015的状态值被声明成了枚举

static int E015_Allocate1 = 0x00;		//E015的Allocate1
static int E015_Allocate2 = 0x00;		//E015的Allocate2
static int E015_Allocate3 = 0x00;		//E015的Allocate3
static int E015_Allocate4 = 0x00;		//E015的Allocate4
static int E015_Allocate5 = 0x00;		//E015的Allocate5
static int E015_Allocate6 = 0x00;		//E015的Allocate6
static int E015_Allocate7 = 0x00;		//E015的Allocate7
static int E015_Allocate8 = 0x00;		//E015的Allocate8

static int E015_CRC8 = 0x00;			//E015的CRC8校验码

static int E015_FrameEnd1 = 0x0D;		//E015的帧尾1
static int E015_FrameEnd2 = 0x0A;		//E015的帧尾2
static int E015_FrameEnd3 = 0x0D;		//E015的帧尾3
static int E015_FrameEnd4 = 0x0A;		//E015的帧尾4
static int E015_FrameEnd5 = 0x0D;		//E015的帧尾5
static int E015_FrameEnd6 = 0x0A;		//E015的帧尾6
//--------------------------------------------------------------------



//全局函数声明
void Receive_A011(unsigned char* Judgement_Data, int Judgement_Length);  //A011函数(查询LORA主设备的参数(当前区域以及SN))
void Receive_A012(unsigned char* Judgement_Data, int Judgement_Length);  //A012函数(基地服务器设置LORA设备的工作组编号)
void Receive_A013(unsigned char* Judgement_Data, int Judgement_Length);  //A013函数(基地服务器设置设备SN，区域及子设备总路数)
void Receive_A014(unsigned char* Judgement_Data, int Judgement_Length);  //A014函数(查询LORA设备的工作状态)
void Receive_A015(unsigned char* Judgement_Data, int Judgement_Length);  //A015函数(强制停止工作指令)

unsigned char Send_E011(int Receive_IsBroadcast);  //E011函数(按键上报当前参数)
unsigned char E011_init();	//E011初始化函数
unsigned char Send_E012(int Receive_IsBroadcast);  //E012函数(LORA设备请求设置工作组编号)
unsigned char E012_init();	//E012初始化函数
unsigned char Send_E013(int Receive_IsBroadcast);  //E013函数(LORA设备请求设置SN、区域、设备类型及子设备路数)
unsigned char E013_init();	//E013初始化函数
unsigned char Send_E014(int Receive_IsBroadcast);	//E014函数(LORA设备上报实时工作状态)
unsigned char E014_init();	//E014初始化函数
unsigned char Send_E015(int Receive_IsBroadcast, int E015_status);		//E015函数(LORA设备通用回执帧)
unsigned char E015_init();	//E015初始化函数

unsigned char SN_ZoneISOK(unsigned char* Judgement_Data, int Judgement_Length);	//测试SN区域是否写入成功函数
unsigned char Signal_query();//信号查询函数


//类结构声明
//LORA开关型设备的通用回执状态(结构类型，枚举)
static enum E015_Device_status
{
	E015_FactoryMode = 0x00,//出厂模式
	AskUploadParamsOk = 0x01,//查询LoRa设备参数成功
	AskUploadParamsErr = 0x02,//查询LoRa设备参数失败
	AssignGroupIdArrayOk = 0x03,//设置组Id数组成功
	AssignGroupIdArrayErr = 0x04,//设置组Id数组失败
	SetSnAndSlaverCountOk = 0x05,//设置主设备区域、SN及子设备路数成功
	SetSnAndSlaverCountErr = 0x06,//设置主设备区域、SN及子设备路数失败
	TrunOffOk = 0x07,//强制停止设备成功
	TrunOffErr = 0x08,//强制停止设备失败
	SetParamsOk = 0x09,//设置参数成功
	SetParamsErr = 0x0A,//设置参数失败
	Set_association_status_succeed = 0x0B,//设置关联状态成功
	Set_association_status_failed = 0x0C,//设置关联状态失败
	State_Storage_Exceeding_the_Upper_Limit = 0x0D,//设置关联状态失败，存储超上限
	Data_loss_due_to_abnormal_power_off = 0x0E,//异常断电数据丢失
	Incorrect_information_error = 0x0F,//区域信息错误
}E015_status = E015_FactoryMode;


#endif

