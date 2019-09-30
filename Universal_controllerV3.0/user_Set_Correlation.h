// user_Set_Correlation.h

#ifndef _USER_SET_CORRELATION_h
#define _USER_SET_CORRELATION_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif


#include <arduino.h>	//引用标准库的头文件
#include "user_initialization.h"//初始化
#include "user_crc8.h"//CRC校验
#include "user_judgement.h"//判断
#include "user_A021_E021.h"
#include "user_Public_directive.h"
#include "user_HEXtoDEC.h"


//引脚定义



//全局变量
static int Storage_bytes_Flag = 100;			//存储字节的标志位

static unsigned char Out_State[6];              //用来存放状态值rd1
static unsigned long duration[6];               //用来存放持续时间值Duration_time
static unsigned long remaining[6];              //用来存放剩余时间值Remaining
static unsigned long ot[6];                     //用来存放旧时间值oldtime
static unsigned long CurrentWorkSec[6];			//用来存放已工作时长

static unsigned long time_huns = 0;             //时间百位
static unsigned long time_tens = 0;             //时间十位
static unsigned long time_ones = 0;             //时间个位

static unsigned long Duration_time = 0;         //持续时间
static unsigned long Remaining = 0;             //剩余时间
static unsigned long oldtime = 0;				//旧时间

static int Heartbeat_time = 5;		//用于处理定时发送的新时间变量
static unsigned long HeartBeat_oldtime;

static int DO1_SetWorkSec1, DO1_SetWorkSec2, DO1_SetWorkSec3;//DO1的设定工作时长
static int DO2_SetWorkSec1, DO2_SetWorkSec2, DO2_SetWorkSec3;//DO2的设定工作时长
static int DO3_SetWorkSec1, DO3_SetWorkSec2, DO3_SetWorkSec3;//DO3的设定工作时长
static int DO4_SetWorkSec1, DO4_SetWorkSec2, DO4_SetWorkSec3;//DO4的设定工作时长
static int AO1_SetWorkSec1, AO1_SetWorkSec2, AO1_SetWorkSec3;//AO1的设定工作时长
static int AO2_SetWorkSec1, AO2_SetWorkSec2, AO2_SetWorkSec3;//AO2的设定工作时长

static int DO1_CurrentWorkSec1, DO1_CurrentWorkSec2, DO1_CurrentWorkSec3;//DO1的已工作时长
static int DO2_CurrentWorkSec1, DO2_CurrentWorkSec2, DO2_CurrentWorkSec3;//DO2的已工作时长
static int DO3_CurrentWorkSec1, DO3_CurrentWorkSec2, DO3_CurrentWorkSec3;//DO3的已工作时长
static int DO4_CurrentWorkSec1, DO4_CurrentWorkSec2, DO4_CurrentWorkSec3;//DO4的已工作时长
static int AO1_CurrentWorkSec1, AO1_CurrentWorkSec2, AO1_CurrentWorkSec3;//AO1的已工作时长
static int AO2_CurrentWorkSec1, AO2_CurrentWorkSec2, AO2_CurrentWorkSec3;//AO2的已工作时长

static int DO1_RemainWorkSec1, DO1_RemainWorkSec2, DO1_RemainWorkSec3;//DO1的剩余工作时长
static int DO2_RemainWorkSec1, DO2_RemainWorkSec2, DO2_RemainWorkSec3;//DO2的剩余工作时长
static int DO3_RemainWorkSec1, DO3_RemainWorkSec2, DO3_RemainWorkSec3;//DO3的剩余工作时长
static int DO4_RemainWorkSec1, DO4_RemainWorkSec2, DO4_RemainWorkSec3;//DO4的剩余工作时长
static int AO1_RemainWorkSec1, AO1_RemainWorkSec2, AO1_RemainWorkSec3;//AO1的剩余工作时长
static int AO2_RemainWorkSec1, AO2_RemainWorkSec2, AO2_RemainWorkSec3;//AO2的剩余工作时长
//------------------------------------------------------------------------
//RTC时钟全局变量
static unsigned long RTC_oldtime;//RTC时间的旧值
//static unsigned long RTC_Dvalue;//RTC时间的差值
static int Mode_implementation = 0x00;//执行方式
static bool RTC_Flag = 0;	//RTC时钟的标志位，如果为0则请求RTC时钟，为1不请求
static int RTC_Year = 19;	//RTC时钟的年份
static int RTC_Month = 9;	//RTC时钟的月份
static int RTC_Day = 30;		//RTC时钟的日期
static int RTC_Hour = 23;	//RTC时钟的小时
static int RTC_Minute = 59;	//RTC时钟的分钟
static int RTC_Second = 40;	//RTC时钟的秒钟
//------------------------------------------------------------------------
//各路数的自动执行时间
static bool DO1_AutoFlag, DO2_AutoFlag, DO3_AutoFlag, DO4_AutoFlag, AO1_AutoFlag, AO2_AutoFlag;
static int DO1_AutoBegin[2][6], DO2_AutoBegin[2][6], DO3_AutoBegin[2][6], DO4_AutoBegin[2][6], AO1_AutoBegin[2][6], AO2_AutoBegin[2][6];
static int DO1_AutoEnd[2][6], DO2_AutoEnd[2][6], DO3_AutoEnd[2][6], DO4_AutoEnd[2][6], AO1_AutoEnd[2][6], AO2_AutoEnd[2][6];
//------------------------------------------------------------------------


static float Set_AOVoltage1 = 0;			//设置模拟输出电压值1
static float Set_AOVoltage2 = 0;			//设置模拟输出电压值2
static int Analog_Value1 = 0;				//analogwrite时输出的值1
static int Analog_Value2 = 0;				//analogwrite时输出的值2


//------------------------------------------------------------------------

//------------------------------------------------------------------------
static unsigned char E022[51];//用来存放E022发送出去的数组

static int E022_FrameHead = 0xFE;		//E022的帧头

static int E022_FrameId1 = 0xE0;		//E022的帧ID1
static int E022_FrameId2 = 0x22;		//E022的帧ID2

static int E022_DataLen = 0x28;			//E022的数据长度

static int E022_DeviceTypeID1 = 0xC0;	//E022的设备类型1
static int E022_DeviceTypeID2 = 0x02;	//E022的设备类型2

static int E022_IsBroadcast = 0x00;		//E022的是否广播指令

static int E022_ZoneId = 0x00;			//E022的区域

static int E022_DO1_SetTime1 = 0x00;	//E022数字输出1设定时间1
static int E022_DO1_SetTime2 = 0x00;	//E022数字输出1设定时间2
static int E022_DO1_SetTime3 = 0x00;	//E022数字输出1设定时间3

static int E022_DO1_RemainTime1 = 0x00;	//E022数字输出1剩余时间1
static int E022_DO1_RemainTime2 = 0x00;	//E022数字输出1剩余时间2
static int E022_DO1_RemainTime3 = 0x00;	//E022数字输出1剩余时间3


static int E022_DO2_SetTime1 = 0x00;	//E022数字输出2设定时间1
static int E022_DO2_SetTime2 = 0x00;	//E022数字输出2设定时间2
static int E022_DO2_SetTime3 = 0x00;	//E022数字输出2设定时间3

static int E022_DO2_RemainTime1 = 0x00;	//E022数字输出2剩余时间1
static int E022_DO2_RemainTime2 = 0x00;	//E022数字输出2剩余时间2
static int E022_DO2_RemainTime3 = 0x00;	//E022数字输出2剩余时间3

static int E022_DO3_SetTime1 = 0x00;	//E022数字输出3设定时间1
static int E022_DO3_SetTime2 = 0x00;	//E022数字输出3设定时间2
static int E022_DO3_SetTime3 = 0x00;	//E022数字输出3设定时间3

static int E022_DO3_RemainTime1 = 0x00;	//E022数字输出3剩余时间1
static int E022_DO3_RemainTime2 = 0x00;	//E022数字输出3剩余时间2
static int E022_DO3_RemainTime3 = 0x00;	//E022数字输出3剩余时间3

static int E022_DO4_SetTime1 = 0x00;	//E022数字输出4设定时间1
static int E022_DO4_SetTime2 = 0x00;	//E022数字输出4设定时间2
static int E022_DO4_SetTime3 = 0x00;	//E022数字输出4设定时间3

static int E022_DO4_RemainTime1 = 0x00;	//E022数字输出4剩余时间1
static int E022_DO4_RemainTime2 = 0x00;	//E022数字输出4剩余时间2
static int E022_DO4_RemainTime3 = 0x00;	//E022数字输出4剩余时间3

static int E022_AO1_SetTime1 = 0x00;	//E022模拟输出1设定时间1
static int E022_AO1_SetTime2 = 0x00;	//E022模拟输出1设定时间2
static int E022_AO1_SetTime3 = 0x00;	//E022模拟输出1设定时间3

static int E022_AO1_RemainTime1 = 0x00;	//E022模拟输出1剩余时间1
static int E022_AO1_RemainTime2 = 0x00;	//E022模拟输出1剩余时间2
static int E022_AO1_RemainTime3 = 0x00;	//E022模拟输出1剩余时间3

static int E022_AO2_SetTime1 = 0x00;	//E022模拟输出2设定时间1
static int E022_AO2_SetTime2 = 0x00;	//E022模拟输出2设定时间2
static int E022_AO2_SetTime3 = 0x00;	//E022模拟输出2设定时间3

static int E022_AO2_RemainTime1 = 0x00;	//E022模拟输出2剩余时间1
static int E022_AO2_RemainTime2 = 0x00;	//E022模拟输出2剩余时间2
static int E022_AO2_RemainTime3 = 0x00;	//E022模拟输出2剩余时间3	36

static int E022_CRC8 = 0x00;			//E022的CRC8校验码

static int E022_FrameEnd1 = 0x0D;		//E022的帧尾1
static int E022_FrameEnd2 = 0x0A;		//E022的帧尾2
static int E022_FrameEnd3 = 0x0D;		//E022的帧尾3
static int E022_FrameEnd4 = 0x0A;		//E022的帧尾4
static int E022_FrameEnd5 = 0x0D;		//E022的帧尾5
static int E022_FrameEnd6 = 0x0A;		//E022的帧尾6

//------------------------------------------------------------------------
static unsigned char E023[21];//用来存放E023发送出去的数组

static int E023_FrameHead = 0xFE;		//E023的帧头

static int E023_FrameId1 = 0xE0;		//E023的帧ID1
static int E023_FrameId2 = 0x23;		//E023的帧ID2

static int E023_DataLen = 0x0A;			//E023的数据长度

static int E023_DeviceTypeID1 = 0xC0;	//E023的设备类型1
static int E023_DeviceTypeID2 = 0x02;	//E023的设备类型2

static int E023_IsBroadcast = 0x00;		//E023的是否广播指令

static int E023_ZoneId = 0x00;			//E023的区域

static int E023_Year = 0x00;			//E023的年份
static int E023_Month = 0x00;			//E023月份
static int E023_Day = 0x00;				//E023日期
static int E023_Hour = 0x00;			//E023小时
static int E023_Minute = 0x00;			//E023分钟
static int E023_Second = 0x00;			//E023秒钟

static int E023_CRC8 = 0x00;			//E023的CRC8校验码

static int E023_FrameEnd1 = 0x0D;		//E023的帧尾1
static int E023_FrameEnd2 = 0x0A;		//E023的帧尾2
static int E023_FrameEnd3 = 0x0D;		//E023的帧尾3
static int E023_FrameEnd4 = 0x0A;		//E023的帧尾4
static int E023_FrameEnd5 = 0x0D;		//E023的帧尾5
static int E023_FrameEnd6 = 0x0A;		//E023的帧尾6


//------------------------------------------------------------------------
static unsigned char E024[23];//用来存放E024发送出去的数组

static int E024_FrameHead = 0xFE;		//E024的帧头

static int E024_FrameId1 = 0xE0;		//E024的帧ID1
static int E024_FrameId2 = 0x24;		//E024的帧ID2

static int E024_DataLen = 0x0C;			//E024的数据长度

static int E024_DeviceTypeID1 = 0xC0;	//E024的设备类型1
static int E024_DeviceTypeID2 = 0x02;	//E024的设备类型2

static int E024_IsBroadcast = 0x00;		//E024的是否广播指令

static int E024_ZoneId = 0x00;			//E024的区域

static int E024_Allocate1 = 0x00;		//E024的预留字段1
static int E024_Allocate2 = 0x00;		//E024的预留字段2
static int E024_Allocate3 = 0x00;		//E024的预留字段3
static int E024_Allocate4 = 0x00;		//E024的预留字段4
static int E024_Allocate5 = 0x00;		//E024的预留字段5
static int E024_Allocate6 = 0x00;		//E024的预留字段6
static int E024_Allocate7 = 0x00;		//E024的预留字段7
static int E024_Allocate8 = 0x00;		//E024的预留字段8

static int E024_CRC8 = 0x00;			//E024的CRC8校验码

static int E024_FrameEnd1 = 0x0D;		//E024的帧尾1
static int E024_FrameEnd2 = 0x0A;		//E024的帧尾2
static int E024_FrameEnd3 = 0x0D;		//E024的帧尾3
static int E024_FrameEnd4 = 0x0A;		//E024的帧尾4
static int E024_FrameEnd5 = 0x0D;		//E024的帧尾5
static int E024_FrameEnd6 = 0x0A;		//E024的帧尾6

//------------------------------------------------------------------------

//static String AssStat, AssStat1, AssStat2;//Association_statement，关联语句1
static String condition_1, implement_1;//判断语句以及执行语句
static String con0[5], con1[5], con2[5], con3[5], con4[5];//条件语句块数组
static String imp0[5], imp1[5], imp2[5], imp3[5], imp4[5];//执行语句块数组
static String Strcon[5], Strimp[5];//实际使用到的条件语句块以及执行语句块，用来充当变量的数组赋值
static size_t i_0 = 0, i_1 = 0, i_2 = 0, i_3 = 0;//循环次数函数


//全局函数声明
//void LORA_Receive_information(void);//LORA接收函数
void Receive_A018(unsigned char* Judgement_Data, int Judgement_Length);	//A018函数(设置LORA主设备的RTC时间)
void Receive_A019(unsigned char* Judgement_Data, int Judgement_Length);	//A019函数(设置LORA主设备定时执行的时间段)
void Receive_A020(unsigned char* Judgement_Data, int Judgement_Length);	//A020函数(设置某类型接口挂载的某一路子设备类型及工作组)
void Receive_A022(unsigned char* Judgement_Data, int Judgement_Length);	//A022函数(设置某路（或某组）输出设备状态)
void Receive_A023(unsigned char* Judgement_Data, int Judgement_Length);	//A023函数(设置数字输入关联输出状态)
void Receive_A024(unsigned char* Judgement_Data, int Judgement_Length);	//A024函数(设置预留字段（B\I\T\C\D）值)

unsigned char Send_E022(int Receive_IsBroadcast);	//E022函数
unsigned char E022_init();	//E022初始化函数
unsigned char Send_E023(int Receive_IsBroadcast);	//E023函数
unsigned char E023_init();	//E023初始化函数
unsigned char Send_E024(int Receive_IsBroadcast);	//E024函数
unsigned char E024_init();	//E024初始化函数
int Verification_Reserved_field(unsigned char* Judgement_Data, int Initial);
void forswitch();//轮询函数
void Allclose();//全关函数
//void Analog1_Write();
//void Analog2_Write();
int data_processing(String data_1);//数据处理函数，分割# 处理判断以及执行
int condition_test(String con1);//处理判断语句的函数
int implement_test(String imp1);//处理执行语句的函数
int Condition_Judgment(int conx, int ret_condition_test);//条件语句判断函数
int Implement_Handle(int impx, int ret_Implement_test);
void array_empty_test();//数组清空函数
void array_print_test();//数组打印测试函数
void Automated_strategy();//策略函数
int Voltage_Value_Processing(String str_V);//电压值处理函数
unsigned long Get_HeartBeat_oldtime();//得到eartBeat_oldtime的值
bool Get_RTC_Flag();//得到RTC_Flag的值
void Automatic_execution_test();//自动执行测试函数
void RTC_Clock();//RTC时钟

//类结构声明

//输出状态(结构类型，枚举)
static enum OUT_STATES
{
	DO1_ON = 1,//数字输出1开
	DO2_ON = 2,//数字输出2开
	DO3_ON = 3,//数字输出3开
	DO4_ON = 4,//数字输出4开
	AO1_ON = 5,//模拟输出1开
	AO2_ON = 6,//模拟输出2开

	Stateless = 0//无状态指令
}out_state = Stateless;

//union DEVICE_SN
//{
//	String str_SN;
//	byte SN[9];
//};
//DEVICE_SN Device_SN1, Device_SN2;

#endif

