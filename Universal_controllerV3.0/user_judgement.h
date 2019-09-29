// user_judgement.h
/*
*版权
*
* 文件名称:user_judgement.h
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

#ifndef _USER_JUDGEMENT_h
#define _USER_JUDGEMENT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <arduino.h>	                            //引用标准库的头文件
#include "user_initialization.h"	                //引用非标准库的头文件
#include "user_crc8.h"
#include "user_Public_directive.h"
#include "user_A021_E021.h"
#include "user_A025_E025.h"
#include "user_Set_Correlation.h"

 //全局变量
static unsigned char Judgement_Data[128];   	//用来存放接收到的数据
static int Judgement_Length = 0;
static int Judgement_flag = 0;
//static int Judgement_DeviceTypeID1 = 0xC0;	//这里设置了设备类型
//static int Judgement_DeviceTypeID2 = 0x02;


//全局函数声明
unsigned char Judgement_function(unsigned char * Judgement_Data, int Judgement_Length, int CRC_Check_num);


//类结构声明


#endif

