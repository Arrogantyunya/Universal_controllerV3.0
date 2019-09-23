// user_A025_E025.h

#ifndef _USER_A025_E025_h
#define _USER_A025_E025_h

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
static int E025_CRC8 = 0;
static int E025_need_485length = 0;
static unsigned char RS485[20];//
static int RS485_length = 0;//
//--------------------------------------------------------
//static unsigned char E025[24];//用来存放E025发送出去的数组
//
//static int E025_FrameHead = 0xFE;		//E025的帧头
//
//static int E025_FrameId1 = 0xE0;		//E025的帧ID1
//static int E025_FrameId2 = 0x25;		//E025的帧ID2
//
//static int E025_DataLen = 0x0D;			//E025的数据长度
//
//static int E025_DeviceTypeID1 = 0xC0;	//E025的设备类型1
//static int E025_DeviceTypeID2 = 0x02;	//E025的设备类型2
//
//static int E025_IsBroadcast = 0x00;		//E025的是否广播指令
//
//static int E025_ZoneId = 0x00;			//E025的区域
//
//static int E025_Status = 0x00;			//E025的状态值被声明成了枚举
//
//static int E025_Allocate1 = 0x00;		//E025的Allocate1
//static int E025_Allocate2 = 0x00;		//E025的Allocate2
//static int E025_Allocate3 = 0x00;		//E025的Allocate3
//static int E025_Allocate4 = 0x00;		//E025的Allocate4
//static int E025_Allocate5 = 0x00;		//E025的Allocate5
//static int E025_Allocate6 = 0x00;		//E025的Allocate6
//static int E025_Allocate7 = 0x00;		//E025的Allocate7
//static int E025_Allocate8 = 0x00;		//E025的Allocate8
//
//static int E025_CRC8 = 0x00;			//E025的CRC8校验码
//
//static int E025_FrameEnd1 = 0x0D;		//E025的帧尾1
//static int E025_FrameEnd2 = 0x0A;		//E025的帧尾2
//static int E025_FrameEnd3 = 0x0D;		//E025的帧尾3
//static int E025_FrameEnd4 = 0x0A;		//E025的帧尾4
//static int E025_FrameEnd5 = 0x0D;		//E025的帧尾5
//static int E025_FrameEnd6 = 0x0A;		//E025的帧尾6
//
//static unsigned char E025_Check_Data[50];   //用来存放接收到的数据
//static int E025_Check_Length = 0;



//全局函数声明
void Receive_A025(unsigned char * Judgement_Data, int Judgement_Length);  //A013函数
unsigned char Send_E025(int Receive_IsBroadcast);  //E020函数
unsigned char E025_init();	//E011初始化函数


//类结构声明






#endif

