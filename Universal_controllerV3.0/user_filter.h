// user_filter.h
/*
*��Ȩ
*
* �ļ�����:user_filter.h
* �ļ���ʶ:���ù���ƻ���
* ժҪ:�����˲�
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

#ifndef _USER_FILTER_h
#define _USER_FILTER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include<arduino.h>	//���ñ�׼���ͷ�ļ�
//#include<EEPROM.h>//
#include"user_initialization.h"//��ʼ��
#include"user_crc8.h"//CRCУ��
#include"user_judgement.h"//�ж�
#include"user_filter.h"//�˲�



//���Ŷ���


//ȫ�ֱ���
//static float average;	//ƽ��ֵ
//static float mode;		//����
//static float median;	//��λ��
//static float maximum;	//���ֵ
//static float minimum;	//��Сֵ
//static float sum;		//��
//static float nomaxmin_avr;	//ȥ�������Сֵ��ƽ����
//static float filter_result;	//�˲����
static float filterData[50];
static int filterData_length;
static int num[50];


//ȫ�ֺ�������
float Filter(float * filterData, int filterData_length);  //�˲�����
float Filter(int* filterData, int filterData_length);


//��ṹ����


#endif

