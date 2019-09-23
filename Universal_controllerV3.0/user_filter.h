// user_filter.h
/*
*版权
*
* 文件名称:user_filter.h
* 文件标识:配置管理计划书
* 摘要:进行滤波
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

#ifndef _USER_FILTER_h
#define _USER_FILTER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include<arduino.h>	//引用标准库的头文件
//#include<EEPROM.h>//
#include"user_initialization.h"//初始化
#include"user_crc8.h"//CRC校验
#include"user_judgement.h"//判断
#include"user_filter.h"//滤波



//引脚定义


//全局变量
//static float average;	//平均值
//static float mode;		//众数
//static float median;	//中位数
//static float maximum;	//最大值
//static float minimum;	//最小值
//static float sum;		//和
//static float nomaxmin_avr;	//去掉最大最小值得平均数
//static float filter_result;	//滤波结果
static float filterData[50];
static int filterData_length;
static int num[50];


//全局函数声明
float Filter(float * filterData, int filterData_length);  //滤波函数
float Filter(int* filterData, int filterData_length);


//类结构声明


#endif

