// user_lorainit.h

#ifndef _USER_LORAINIT_h
#define _USER_LORAINIT_h


#if defined(ARDUINO) && ARDUINO >= 100
#include <arduino.h>//���ñ�׼���ͷ�ļ�
#else
#include "WProgram.h"
#endif

#include "user_initialization.h"	//����ͷ�ļ�
//#include ""

//���Ŷ���


//ȫ�ֺ�������
int LORA_Initialization(void);//��ʼ������
void LORA_Receive_information(void);//LORA���պ���
String addr_write();

//ȫ�ֱ���
static unsigned char lora_data[200];
static unsigned char lora_len = 0;
static unsigned int lora_Completion_Degree = 0;

static unsigned char Receive_Data[128];//������Ž��յ�������
static int Receive_Length = 0;//�������ݵĳ���
static int CRC_Check_num = 0x00;//CRCУ�����ֵ

//��ṹ����



#endif

