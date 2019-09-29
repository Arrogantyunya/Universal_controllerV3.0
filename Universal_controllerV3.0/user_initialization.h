// user_initialization.h
/*
*版权
*
* 文件名称:user_initialization.h
* 文件标识:配置管理计划书
* 摘要:定义了需要初始化的引脚
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

#ifndef _USER_INITIALIZATION_h
#define _USER_INITIALIZATION_h	//防止头文件user_initialization.h被重复调用

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>//引用标准库的头文件
#else
#include "WProgram.h"
#endif

#include <arduino.h>
#include "user_lorainit.h"
#include "AT24CXX.h"
#include "i2c.h"
#include "user_Public_directive.h"


#define debug			0		//debug为1进入测试模式，每次重启所有标志位都清零;为0进入正常使用模式，不会清空标志位
#define debug_crc		1		//debug_crc为1进入CRC不需要校验的模式，将CRC位发送D6将校验通过；为0时为正常校验CRC
#define debug_print		1		//debug_print为1进入测试输出模式，将会打印信息；为0时将不打印输出

#define LORA_reset		0		//LORA_reset为1进入LORA测试，每次重启后LORA的标志位都清零
#define LORA_NET		0		//LORA_NET为0代表lora的NET为节点，为1代表为网关,为0代表节点

#define AT24C01_bytes	127		//代表最大的存储空间
#define AT24C02_bytes	255		//代表最大的存储空间
#define AT24C04_bytes	511		//代表最大的存储空间
#define AT24C08_bytes	1023	//代表最大的存储空间
#define AT24C16_bytes	2047	//代表最大的存储空间
#define AT24C32_bytes	4095	//代表最大的存储空间
#define AT24C64_bytes	8191	//代表最大的存储空间
#define AT24C128_bytes	16383	//代表最大的存储空间
#define AT24C256_bytes	32767	//代表最大的存储空间



 //引脚定义
#define K1			PC0		//按键1
#define K2			PC1		//按键2
#define AO1			PC2		//模拟输出1
#define AO2			PC3		//模拟输出2
#define VIN1		PA0		//模拟输入1
#define VIN2		PA1		//模拟输入2
#define TX_485		PA2		//485TX
#define	RX_485		PA3		//485RX
#define	DI1			PA6		//数字输入1
#define	DI2			PA7		//数字输入2
#define	DO1			PC4		//数字输出1
#define	DO2			PC5		//数字输出2
#define	KCZJ1		PB0		//继电器1
#define	KCZJ2		PB1		//继电器2
#define	BOOT1		PB2		//boot1
#define	LORA_RX		PB10	//LORA_TX
#define	LORA_TX		PB11	//LORA_RX
#define	LED4		PC6		//LED4
#define	LED3		PC7		//LED3
#define	LED2		PC8		//LED2
#define	LED1		PC9		//LED1
#define	MCU_TX		PA9		//MCU_TX
#define	MCU_RX		PA10	//MCU_RX
#define	USBDM		PA11	//USB接口
#define	USBDP		PA12	//USB接口
#define	SWDIO		PA13	//程序下载接口
#define SWCLK		PA14	//程序下载接口
#define	RESETN		PC12	//LORA模块RESETn
#define	WAKE_UP		PD2		//LORA模块Wake_UP
#define	AT_CMD		PB3		//LORA模块AT_CMD
#define	LORA_PWR	PB4		//LORA模块LORA_PWR
//#define	WP			PB5		//FLASH模块WP
//#define	EEPROM_SCL	PB6		//FLASH模块EEPROM_SCL
//#define	EEPROM_SDA	PB7		//FLASH模块EEPROM_SDA
#define	BOOT0		BOOT0	//BOOT0


//全局函数声明
void Initialization(void);				//初始化函数
void Send_Data_Lamp(void);				//发送数据灯
void Receive_data_lamp(void);			//接收数据灯
void Restore_actory_setting_lamp(void);	//恢复出厂设置灯


//全局变量
static unsigned char Receive_IsBroadcast = 0x00; //是否广播指令


//类结构声明



#endif

