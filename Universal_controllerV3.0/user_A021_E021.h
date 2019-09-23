// user_A021_E021.h

#ifndef _USER_A021_E021_h
#define _USER_A021_E021_h

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



//引脚定义



//全局变量
static unsigned char E021[31];//用来存放E021发送出去的数组

static int E021_FrameHead = 0xFE;		//E021的帧头

static int E021_FrameId1 = 0xE0;		//E021的帧ID1
static int E021_FrameId2 = 0x21;		//E021的帧ID2

static int E021_DataLen = 0x14;			//E021的数据长度

static int E021_DeviceTypeID1 = 0xC0;	//E021的设备类型1
static int E021_DeviceTypeID2 = 0x02;	//E021的设备类型2

static int E021_IsBroadcast = 0x00;		//E021的是否广播指令

static int E021_ZoneId = 0x00;			//E021的区域

static int E021_digIn1= 0x00;			//E021的数字输入1
static int E021_digIn2 = 0x00;			//E021的数字输入2

static int E021_digOut1 = 0x00;			//E021的数字输出1
static int E021_digOut2 = 0x00;			//E021的数字输出2

static int E021_anaIn1_1 = 0x00;		//E021的模拟输入1_1
static int E021_anaIn1_2 = 0x00;		//E021的模拟输入1_2
static int E021_anaIn1_3 = 0xE2;		//E021的模拟输入1_3

static int E021_anaIn2_1 = 0x00;		//E021的模拟输入2_1
static int E021_anaIn2_2 = 0x00;		//E021的模拟输入2_2
static int E021_anaIn2_3 = 0xE2;		//E021的模拟输入2_3

static int E021_anaOut1_1 = 0x00;		//E021的模拟输出1_1
static int E021_anaOut1_2 = 0x00;		//E021的模拟输出1_2
static int E021_anaOut1_3 = 0x00;		//E021的模拟输出1_3

static int E021_anaOut2_1 = 0x00;		//E021的模拟输出2_1
static int E021_anaOut2_2 = 0x00;		//E021的模拟输出2_2
static int E021_anaOut2_3 = 0x00;		//E021的模拟输出2_3

static int E021_CRC8 = 0x00;			//E021的CRC8校验码

static int E021_FrameEnd1 = 0x0D;		//E021的帧尾1
static int E021_FrameEnd2 = 0x0A;		//E021的帧尾2
static int E021_FrameEnd3 = 0x0D;		//E021的帧尾3
static int E021_FrameEnd4 = 0x0A;		//E021的帧尾4
static int E021_FrameEnd5 = 0x0D;		//E021的帧尾5
static int E021_FrameEnd6 = 0x0A;		//E021的帧尾6

static unsigned char E021_Check_Data[50];   //用来存放接收到的数据
static int E021_Check_Length = 0;

static int Delivery_time = 30;		//用于处理定时发送的新时间变量
static unsigned long Delivery_oldtime = 0;		//用于处理定时发送的旧时间变量



//全局函数声明
void Receive_A021(unsigned char * Judgement_Data, int Judgement_Length);  //A013函数
unsigned char Send_E021(int Receive_IsBroadcast);  //E021函数
unsigned char E021_init();	//E021初始化函数
int E021_GetDigitalStatus();//E021得到数字状态
int E021_GetAnalogStatus();	//E021得到模拟状态
unsigned long Get_Delivery_oldtime();//得到旧时间


//类结构声明





#endif

