// user_crc8.h
/*
*版权
*
* 文件名称:user_crc8.h
* 文件标识:配置管理计划书
* 摘要:crc8校验值的计算对比
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


#ifndef _USER_CRC8_h
#define _USER_CRC8_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

//#include <arduino.h>	//引用标准库的头文件


#define AL2_FCS_COEF ((1 << 7) + (1 << 6) + (1 << 5))


typedef unsigned long  DWORD;
typedef unsigned short WORD;

static unsigned char Check_Data[128];   //用来存放接收到的数据
static int Check_Length = 0;


//全局函数声明
unsigned char GetCrc8(unsigned char * Check_Data, int Check_Length);

//类结构声明



#endif

