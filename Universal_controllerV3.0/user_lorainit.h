// user_lorainit.h

#ifndef _USER_LORAINIT_h
#define _USER_LORAINIT_h


#if defined(ARDUINO) && ARDUINO >= 100
#include <arduino.h>//引用标准库的头文件
#else
#include "WProgram.h"
#endif

#include "user_initialization.h"	//引用头文件
//#include <EEPROM.h>
#include "user_Set_Correlation.h"
#include "user_A025_E025.h"
#include "user_A021_E021.h"
#include "user_crc8.h"
#include "user_judgement.h"
#include "user_Public_directive.h"
#include <arduino.h>
#include "AT24CXX.h"
#include "i2c.h"
#include "user_HEXtoDEC.h"

//引脚定义


//全局函数声明
int LORA_Initialization(void);//初始化函数
void LORA_Receive_information(void);//LORA接收函数
String addr_write();

//全局变量
static unsigned char lora_data[200];
static unsigned char lora_len = 0;
static unsigned int lora_Completion_Degree = 0;

static unsigned char Receive_Data[128];//用来存放接收到的数据
static int Receive_Length = 0;//接收数据的长度
static int CRC_Check_num = 0x00;//CRC校验的数值

//类结构声明



#endif

