//user_initialization.cpp
/*
*��Ȩ
*
* �ļ�����:user_initialization.cpp
* �ļ���ʶ:���ù���ƻ���
* ժҪ:�����Ž��г�ʼ��
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


#include "user_initialization.h"


//�� �� ����Initialization() 
//������������ʼ���ĺ���
//����˵����
//���ú�����
//ȫ�ֱ�����
//�� �룺
//�� �أ�
/////////////////////////////////////////////////////////////////////
void Initialization()//��ʼ������
{
	//��ʼ������
	afio_cfg_debug_ports(AFIO_DEBUG_SW_ONLY);//��Ϊ���Ÿ���
	pinMode(RESETN, OUTPUT);//��λ��·�����ߵ�ƽ���и�λ
	pinMode(KCZJ1, OUTPUT);//�̵���1
	pinMode(KCZJ2, OUTPUT);//�̵���2
	pinMode(LED1, OUTPUT);//LED1����1��
	pinMode(LED2, OUTPUT);//LED2����1��
	pinMode(LED3, OUTPUT);//LED3����2��
	pinMode(LED4, OUTPUT);//LED4����2��
	pinMode(K1, INPUT);//����1
	pinMode(K2, INPUT);//����2
	pinMode(LORA_PWR, OUTPUT);//LORA��Դ
	pinMode(RESETN, OUTPUT);//LORA��λ
	pinMode(AT_CMD, OUTPUT);//LORA����
	pinMode(WAKE_UP, OUTPUT);//LORA����
	pinMode(VIN1, INPUT_ANALOG);//ģ�������ѹ1
	pinMode(VIN2, INPUT_ANALOG);//ģ�������ѹ2
	pinMode(AO1, PWM);//ģ�����1
	pinMode(AO2, PWM);//ģ�����2
	pinMode(DI1, INPUT_PULLDOWN);//��������1
	pinMode(DI2, INPUT_PULLDOWN);//��������2
	pinMode(DO1, OUTPUT);//�������1
	pinMode(DO2, OUTPUT);//�������2
	pinMode(WP, OUTPUT);//EEPROM��д���


	//��ʼ������
	Serial.begin(9600);		//USB����
	Serial2.begin(9600);	//485�Ĵ���
	Serial3.begin(9600);	//LORA�Ĵ���

	//�̵�����ʼ��//
	digitalWrite(KCZJ1, HIGH);
	digitalWrite(KCZJ2, HIGH);

	//LED��ʼ��
	digitalWrite(LED1, LOW);
	digitalWrite(LED2, LOW);
	digitalWrite(LED3, LOW);
	digitalWrite(LED4, LOW);

	//lora��س�ʼ��//
	digitalWrite(LORA_PWR, HIGH);
	digitalWrite(RESETN, HIGH);
	digitalWrite(AT_CMD, LOW);

	//EEPROM
	i2cInit();


	if (debug == 0)
	{
		delay(1000);
	}

	//�����ʼ������ʱ״̬��1�̵���˸5��
	for (size_t i = 0; i < 5; i++)
	{
		digitalWrite(LED2, HIGH);
		delay(200);
		digitalWrite(LED2, LOW);
		delay(200);
	}


	Serial.println("===============");
	Serial.println(String("debug = ") + String(debug));
	Serial.println(String("debug_crc = ") + String(debug_crc));
	Serial.println(String("debug_print = ") + String(debug_print));
	Serial.println(String("LORA_reset = ") + String(LORA_reset));
	Serial.println(String("LORA_NET = ") + String(LORA_NET));
	Serial.println("===============");


	//-------------------------------------------
	if (debug == 1)
	{
		//======����ʱ���ô����=====
		//�����еı�־λ����Ϊ0
		Serial.println("debug == 1");
		if (LORA_reset == 1)
		{
			Serial.println("LORA_reset == 1");
			AT24CXX_WriteOneByte(0, 0x00);//LORA��ʼ����ɵı�־λ
		}
		//else
		//{
		//	AT24CXX_WriteOneByte(0, 0x01);//LORA��ʼ����ɵı�־λ
		//}
		AT24CXX_WriteOneByte(1, 0x00);//EEPROM��ʼ����ɵı�־λ
		AT24CXX_WriteOneByte(2, 0x00);//�����ɵı�־λ
	}

	//����EEPROM�ĳ�ʼ��
	if (AT24CXX_ReadOneByte(1) == 0x01)
	{
		//˵�����й�EEPROM�ĳ�ʼ��
		Serial.println("EEPROM�ѽ��й���ʼ��");
		Serial.println("EEPROM already setup");
		if (debug == 1)
		{
			delay(500);
		}
	}
	else
	{
		if (LORA_reset == 1 || AT24CXX_ReadOneByte(0) != 0x01)
		{
			Serial.println("LORA���г�ʼ��");
			AT24CXX_WriteOneByte(0, 0x00);//LORA��ʼ����ɵı�־λ
		}
		//else
		//{
		//	AT24CXX_WriteOneByte(0, 0x01);//LORA��ʼ����ɵı�־λ
		//}
		AT24CXX_WriteOneByte(1, 0x00);//EEPROM��ʼ����ɵı�־λ
		AT24CXX_WriteOneByte(2, 0x00);//�����ɵı�־λ
		for (size_t i = 3; i <= 11; i++)//SN�Ĵ洢
		{
			AT24CXX_WriteOneByte(i, 0x00);
		}
		AT24CXX_WriteOneByte(12, 0x01);//LORA���豸����ID�Ĵ洢
		AT24CXX_WriteOneByte(13, 0x00);//LORA�Զ����Թ����ı�־λ
		for (size_t i = 14; i <= 55; i++)//����������ĳ�ʼ��
		{
			AT24CXX_WriteOneByte(i, 0x01);
		}
		for (size_t i = 56; i <= 88; i++)//Ԥ���ֶεĳ�ʼ��
		{
			AT24CXX_WriteOneByte(i, 0x00);
		}

		AT24CXX_WriteOneByte(89, 100);//�洢�ֽڵı�־λ

		for (size_t i = 90; i <= 99; i++)//�Զ�������俪ʼ����λ�õĳ�ʼ��
		{
			AT24CXX_WriteOneByte(i, 0x00);
		}

		for (size_t i = 100; i < AT24C02_bytes; i++)//�Զ��������������ĳ�ʼ��
		{
			AT24CXX_WriteOneByte(i, 0x00);
		}



		//---------------------------------------------------------
		AT24CXX_WriteOneByte(1, 0x01);//EEPROM��ʼ����ɵı�־λ
		//Serial.println(EEPROM.read(1),HEX);
		Serial.println("EEPROM�洢�ռ�ĳ�ʼ�����");
		Serial.println("EEPROM Successful setup");
		if (debug == 1)
		{
			delay(1000);
		}
	}

	//����Ͷ�ȡLORA��־λ�Ƿ�������ɣ�δ������ɾͽ���LORAģ�������
	if (AT24CXX_ReadOneByte(0) == 0x01)
	{
		Serial.println("LORA�ѽ��й���ʼ��");
		Serial.println("LORA already setup");
		if (debug == 1)
		{
			delay(1000);
		}
	}
	else
	{
		Serial.println("LORA��ʼ����......");
		Serial.println("LORA Setup Begin");
		Serial.println(AT24CXX_ReadOneByte(0), HEX);//0
		if (debug == 1)
		{
			delay(1000);
		}
		//����LORA���õĺ���
		LORA_Initialization();
	}


	if (debug == 1)
	{
		Serial.println("����Initialization����");
	}

}

//�������ݵ�
void Send_Data_Lamp(void)
{
	digitalWrite(LED3, HIGH);
	delay(250);
	digitalWrite(LED3, LOW);
}

//�������ݵ�
void Receive_data_lamp(void)
{
	digitalWrite(LED4, HIGH);
	delay(250);
	digitalWrite(LED4, LOW);
}

//�ָ��������õ�
void Restore_actory_setting_lamp(void)
{
	//���г������õ�
	for (size_t i = 0; i < 10; i++)
	{
		digitalWrite(LED1, HIGH);
		digitalWrite(LED4, HIGH);
		digitalWrite(LED2, LOW);
		digitalWrite(LED3, LOW);
		delay(250);
		digitalWrite(LED1, LOW);
		digitalWrite(LED4, LOW);
		digitalWrite(LED2, HIGH);
		digitalWrite(LED3, HIGH);
		delay(250);
	}
	digitalWrite(LED1, LOW);
	digitalWrite(LED4, LOW);
	digitalWrite(LED2, LOW);
	digitalWrite(LED3, LOW);
}
