// user_initialization.h
/*
*��Ȩ
*
* �ļ�����:user_initialization.h
* �ļ���ʶ:���ù���ƻ���
* ժҪ:��������Ҫ��ʼ��������
*
* ��ǰ�汾:V1.0
* ����:���һ�
* �������:
* �޸���:
* �޸�����:
*
* ȡ���汾:
* ԭ����:���һ�
* �������:
 */

#ifndef _USER_INITIALIZATION_h
#define _USER_INITIALIZATION_h	//��ֹͷ�ļ�user_initialization.h���ظ�����

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>//���ñ�׼���ͷ�ļ�
#else
#include "WProgram.h"
#endif

#include <arduino.h>
#include "user_lorainit.h"
#include "AT24CXX.h"
#include "i2c.h"


#define debug			1		//debugΪ1�������ģʽ��ÿ���������б�־λ������;Ϊ0��������ʹ��ģʽ��������ձ�־λ
#define debug_crc		1		//debug_crcΪ1����CRC����ҪУ���ģʽ����CRCλ����D6��У��ͨ����Ϊ0ʱΪ����У��CRC
#define debug_print		1		//debug_printΪ1����������ģʽ�������ӡ��Ϣ��Ϊ0ʱ������ӡ���

#define LORA_reset		0		//LORA_resetΪ1����LORA���ԣ�ÿ��������LORA�ı�־λ������
#define LORA_NET		0		//LORA_NETΪ0����lora��NETΪ�ڵ㣬Ϊ1����Ϊ����,Ϊ0����ڵ�

#define AT24C01_bytes	127		//�������Ĵ洢�ռ�
#define AT24C02_bytes	255		//�������Ĵ洢�ռ�
#define AT24C04_bytes	511		//�������Ĵ洢�ռ�
#define AT24C08_bytes	1023	//�������Ĵ洢�ռ�
#define AT24C16_bytes	2047	//�������Ĵ洢�ռ�
#define AT24C32_bytes	4095	//�������Ĵ洢�ռ�
#define AT24C64_bytes	8191	//�������Ĵ洢�ռ�
#define AT24C128_bytes	16383	//�������Ĵ洢�ռ�
#define AT24C256_bytes	32767	//�������Ĵ洢�ռ�



 //���Ŷ���
#define K1			PC0		//����1
#define K2			PC1		//����2
#define AO1			PC2		//ģ�����1
#define AO2			PC3		//ģ�����2
#define VIN1		PA0		//ģ������1
#define VIN2		PA1		//ģ������2
#define TX_485		PA2		//485TX
#define	RX_485		PA3		//485RX
#define	DI1			PA6		//��������1
#define	DI2			PA7		//��������2
#define	DO1			PC4		//�������1
#define	DO2			PC5		//�������2
#define	KCZJ1		PB0		//�̵���1
#define	KCZJ2		PB1		//�̵���2
#define	BOOT1		PB2		//boot1
#define	LORA_RX		PB10	//LORA_TX
#define	LORA_TX		PB11	//LORA_RX
#define	LED4		PC6		//LED4
#define	LED3		PC7		//LED3
#define	LED2		PC8		//LED2
#define	LED1		PC9		//LED1
#define	MCU_TX		PA9		//MCU_TX
#define	MCU_RX		PA10	//MCU_RX
#define	USBDM		PA11	//USB�ӿ�
#define	USBDP		PA12	//USB�ӿ�
#define	SWDIO		PA13	//�������ؽӿ�
#define SWCLK		PA14	//�������ؽӿ�
#define	RESETN		PC12	//LORAģ��RESETn
#define	WAKE_UP		PD2		//LORAģ��Wake_UP
#define	AT_CMD		PB3		//LORAģ��AT_CMD
#define	LORA_PWR	PB4		//LORAģ��LORA_PWR
//#define	WP			PB5		//FLASHģ��WP
//#define	EEPROM_SCL	PB6		//FLASHģ��EEPROM_SCL
//#define	EEPROM_SDA	PB7		//FLASHģ��EEPROM_SDA
#define	BOOT0		BOOT0	//BOOT0


//ȫ�ֺ�������
void Initialization(void);				//��ʼ������
void Send_Data_Lamp(void);				//�������ݵ�
void Receive_data_lamp(void);			//�������ݵ�
void Restore_actory_setting_lamp(void);	//�ָ��������õ�


//ȫ�ֱ���
static unsigned char Receive_IsBroadcast = 0x00; //�Ƿ�㲥ָ��


//��ṹ����



#endif

