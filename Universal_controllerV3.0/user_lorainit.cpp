//user_lorainit.cpp
/*
*��Ȩ
*
* �ļ�����:user_lorainit.cpp
* �ļ���ʶ:���ù���ƻ���
* ժҪ:�����Ž��г�ʼ��
*
* ��ǰ�汾:V2.0
* ����:���һ�
* �������:2019-8-13
* �޸���:���һ�
* �޸�����:2019-8-13
* �޸�:�������鲥��ַ��Ȼ�������˶�ȡADDR�ĵ�ַ����д��ADDR���Ż��������߼�
*
* ȡ���汾:V1.0
* ԭ����:���һ�
* �������:
*/

#include "user_lorainit.h"
//#include <EEPROM.h>
#include "user_Set_Correlation.h"
#include "user_A025_E025.h"
#include "user_A021_E021.h"
#include "user_crc8.h"
#include "user_judgement.h"
#include "user_A011_E011.h"
#include <arduino.h>
#include "user_initialization.h"
#include "AT24CXX.h"
#include "i2c.h"
#include "user_HEXtoDEC.h"


//�� �� ����LORA_Initialization() 
//����������
//����˵����LORA��ʼ���ĺ���
//���ú�����
//ȫ�ֱ�����
//�� �룺
//�� �أ�
/////////////////////////////////////////////////////////////////////
int LORA_Initialization()//LORA��ʼ������
{
	//��δ���ù���LORA��������
	//����TFREQ��RFREQ��TSF��RSF

	//������LORA���ŵĳ�ʼ��
	// digitalWrite(LORA_PWR,HIGH);			//����LORA�ĵ�Դ
	// digitalWrite(RESETN,HIGH);			//��ֹLORA���и�λ
	// digitalWrite(AT_CMD,LOW);			//��LORA����Ϊ͸��

	if (debug_print == 1)
	{
		Serial.println("����LORA_Initialization����");
	}

	Serial.println("M-HL9:LORA Setup Begin");
	digitalWrite(AT_CMD, HIGH);
	delay(500);

	//�Ȳ���ATָ���Ƿ�OK
	delay(100);
	Serial3.print("AT\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len] = Serial3.read();
		lora_len++;
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		/*for (size_t i = 0; i < lora_len; i++)
		{
			Serial.println(String("lora_data [") + String(i) + String("]=") + String(lora_data[i]));
		}*/
		lora_len = 0;
		if (lora_data[48] == 79 && lora_data[49] == 75)
		{
			Serial.println("AT Successful setup");
			lora_Completion_Degree = 0;//0
		}
		else
		{
			Serial.println("AT Setup failed");
		}
	}
	//Ȼ������NET
	//00Ϊ	Node to Node;	01Ϊ	Node to Gateway
	delay(100);
	if (LORA_NET == 0)
	{
		Serial3.print(String("AT+NET=00\r\n"));
	}
	else if (LORA_NET == 1)
	{
		Serial3.print(String("AT+NET=01\r\n"));
	}
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len] = Serial3.read();
		lora_len++;
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		/*for (size_t i = 0; i < lora_len; i++)
		{
			Serial.println(String("lora_data [") + String(i) + String("]=") + String(lora_data[i]));
		}*/
		lora_len = 0;
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("NET Successful setup");
			lora_Completion_Degree++;//1
			Serial.println(String("lora_Completion_Degree = ") + String(lora_Completion_Degree));
		}
		else
		{
			Serial.println("NET Setup failed");
		}
	}
	//Ȼ������TFREQ��RFREQ����Ƶ���Լ�����Ƶ��
	delay(100);
	Serial3.print(String("AT+TFREQ=1C578DE0\r\n"));
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len] = Serial3.read();
		lora_len++;
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("TFREQ Successful setup");
			lora_Completion_Degree++;//2
			Serial.println(String("lora_Completion_Degree = ") + String(lora_Completion_Degree));
		}
		else
		{
			Serial.println("TFREQ Setup failed");
		}
	}
	//����RRFREQ
	delay(100);
	Serial3.print("AT+RFREQ=1C03A180\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("RFREQ Successful setup");
			lora_Completion_Degree++;//3
			Serial.println(String("lora_Completion_Degree = ") + String(lora_Completion_Degree));
		}
		else
		{
			Serial.println("RFREQ Setup failed");
		}
	}
	//���÷��͹���
	//14Ϊ20dbm
	delay(100);
	Serial3.print("AT+POW=14\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("POW Successful setup");
			lora_Completion_Degree++;//4
			Serial.println(String("lora_Completion_Degree = ") + String(lora_Completion_Degree));
		}
		else
		{
			Serial.println("POW Setup failed");
		}
	}
	//���õ��ƴ���
	//07Ϊ125KHZ
	delay(100);
	Serial3.print("AT+BW=07\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("BW Successful setup");
			lora_Completion_Degree++;//5
			Serial.println(String("lora_Completion_Degree = ") + String(lora_Completion_Degree));
		}
		else
		{
			Serial.println("BW Setup failed");
		}
	}
	//����TSF������Ƶ
	//09����09
	delay(100);
	Serial3.print("AT+TSF=09\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("TSF Successful setup");
			lora_Completion_Degree++;//6
			Serial.println(String("lora_Completion_Degree = ") + String(lora_Completion_Degree));
		}
		else
		{
			Serial.println("TSF Setup failed");
		}
	}

	//����RSF������Ƶ
	//09����09
	delay(100);
	Serial3.print("AT+RSF=09\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("RSF Successful setup");
			lora_Completion_Degree++;//7
			Serial.println(String("lora_Completion_Degree = ") + String(lora_Completion_Degree));
		}
		else
		{
			Serial.println("RSF Setup failed");
		}
	}

	//����CR��������
	//01����4/5
	delay(100);
	Serial3.print("AT+CR=01\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("CR Successful setup");
			lora_Completion_Degree++;//8
			Serial.println(String("lora_Completion_Degree = ") + String(lora_Completion_Degree));
		}
		else
		{
			Serial.println("CR Setup failed");
		}
	}

	//����MODE���Ʒ�ʽ
	//01ΪLORA���Ʒ�ʽ
	delay(100);
	Serial3.print("AT+MODE=01\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("MODE Successful setup");
			lora_Completion_Degree++;//9
			Serial.println(String("lora_Completion_Degree = ") + String(lora_Completion_Degree));
		}
		else
		{
			Serial.println("MODE Setup failed");
		}
	}

	//����SYNCͬ����
	//12����0x12
	delay(100);
	Serial3.print("AT+SYNC=12\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("SYNC Successful setup");
			lora_Completion_Degree++;//10
			Serial.println(String("lora_Completion_Degree = ") + String(lora_Completion_Degree));
		}
		else
		{
			Serial.println("SYNC Setup failed");
		}
	}

	/*//-------------------------------------------------------
	//����PREM���ò��ˣ��ظ�ER00
	//����PREMǰ����
	//08����Ĭ��ֵ
	Serial3.print("AT+PREM=08\r\n");
	while(Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data,lora_len);
		lora_len = 0;
		delay(500);
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("�Ƿ����óɹ�");
		}
	}
	//-------------------------------------------------------*/

	//����CRCӲ��CRC
	//01������CRCУ��
	delay(100);
	Serial3.print("AT+CRC=01\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("CRC Successful setup");
			lora_Completion_Degree++;//11
			Serial.println(String("lora_Completion_Degree = ") + String(lora_Completion_Degree));
		}
		else
		{
			Serial.println("CRC Setup failed");
		}
	}

	//����TIQ���ͷ�ת
	//00Ϊ����ת
	delay(100);
	Serial3.print("AT+TIQ=00\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("TIQ Successful setup");
			lora_Completion_Degree++;//12
			Serial.println(String("lora_Completion_Degree = ") + String(lora_Completion_Degree));
		}
		else
		{
			Serial.println("TIQ Setup failed");
		}
	}

	//����RIQ���շ�ת
	//00Ϊ����ת
	delay(100);
	Serial3.print("AT+RIQ=00\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("RIQ Successful setup");
			lora_Completion_Degree++;//13
			Serial.println(String("lora_Completion_Degree = ") + String(lora_Completion_Degree));
		}
		else
		{
			Serial.println("RIQ Setup failed");
		}
	}

	//����SEQ���ݰ���š�����IPģ���ַ����
	//01Ϊ����ַ��������
	delay(100);
	Serial3.print("AT+SIP=01\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("SIP Successful setup");
			lora_Completion_Degree++;//14
			Serial.println(String("lora_Completion_Degree = ") + String(lora_Completion_Degree));
		}
		else
		{
			Serial.println("SIP Setup failed");
		}
	}

	/*//-------------------------------------------------------
	//���ò��ɹ�
	//����AESģ��AESͨ�ż���
	//
	Serial3.print("AT+AES=00000000000000000000000000000000\r\n");
	while(Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data,lora_len);
		lora_len = 0;
		delay(500);
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("�Ƿ����óɹ�");
		}
	}
	//-------------------------------------------------------*/

	//����ACK���ݰ�Ӧ����
	//00����Ӧ��
	delay(100);
	Serial3.print("AT+ACK=00\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("ACK Successful setup");
			lora_Completion_Degree++;//15
			Serial.println(String("lora_Completion_Degree = ") + String(lora_Completion_Degree));
		}
		else
		{
			Serial.println("ACK Setup failed");
		}
	}
	//����LDR�������Ż�
	//00����AUTO
	delay(100);
	Serial3.print("AT+LDR=00\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("LDR Successful setup");
			lora_Completion_Degree++;//16
			Serial.println(String("lora_Completion_Degree = ") + String(lora_Completion_Degree));
		}
		else
		{
			Serial.println("LDR Setup failed");
		}
	}

	//����MADDR�鲥��ַ
	delay(100);
	Serial3.print("AT+MADDR=71000000\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		if (lora_data[2] == 79 && lora_data[3] == 75)
		{
			Serial.println("MADDR Successful setup");
			lora_Completion_Degree++;//17
			Serial.println(String("lora_Completion_Degree = ") + String(lora_Completion_Degree));
		}
		else
		{
			Serial.println("MADDR Setup failed");
		}
	}
	else
	{
		Serial.println("MADDR Setting up no receipt");
	}


	//��ѯ
	delay(500);
	Serial3.print("AT+TFREQ?\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		delay(100);
	}
	delay(100);

	Serial3.print("AT+RFREQ?\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		lora_len = 0;
		delay(100);
	}
	delay(100);

	Serial3.print("AT+SYNC?\r\n");
	Serial3.flush();
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		delay(100);
	}
	delay(100);

	Serial3.print("AT+POW?\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		delay(100);
	}
	delay(100);

	Serial3.print("AT+BW?\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		delay(100);
	}
	delay(100);

	Serial3.print("AT+CR?\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		delay(100);
	}
	delay(100);

	Serial3.print("AT+CRC?\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		delay(100);
	}
	delay(100);

	Serial3.print("AT+TSF?\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		delay(100);
	}
	delay(100);

	Serial3.print("AT+RSF?\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		delay(100);
	}
	delay(100);

	Serial3.print("AT+ADDR?\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		if (debug == 1)
		{
			/*for (size_t i = 0; i < lora_len; i++)
			{
				Serial.println(lora_data[i]);
			}*/
		}
		delay(100);
		Serial3.print(String("AT+ADDR=") + String(addr_write()) + String("\r\n"));
		//addr_write();
		Serial3.flush();
		lora_len = 0;
		delay(100);
		while (Serial3.available() > 0)
		{
			lora_data[lora_len++] = Serial3.read();
			delay(5);
		}
		if (lora_len > 0)
		{
			Serial.write(lora_data, lora_len);
			Serial.flush();
			lora_len = 0;
			if (lora_data[2] == 79 && lora_data[3] == 75)
			{
				Serial.println("ADDR Write Successful");
				lora_Completion_Degree++;//19
				Serial.println(String("lora_Completion_Degree = ") + String(lora_Completion_Degree));
			}
			else
			{
				Serial.println("ADDR Write failed");
			}
		}
	}
	delay(100);

	Serial3.print("AT+MADDR?\r\n");
	Serial3.flush();
	lora_len = 0;
	delay(100);
	while (Serial3.available() > 0)
	{
		lora_data[lora_len++] = Serial3.read();
		delay(5);
	}
	if (lora_len > 0)
	{
		Serial.write(lora_data, lora_len);
		Serial.flush();
		lora_len = 0;
		delay(100);
	}
	delay(100);


	digitalWrite(AT_CMD, LOW);		//��LORA����Ϊ͸��
	delay(10);

	if (lora_Completion_Degree == 18)
	{
		Serial.println("LORA��ʼ�����");
		Serial.println("LORA Initialization Setup completed");
		AT24CXX_WriteOneByte(0, 0x01);

		if (debug_print == 1)
		{
			Serial.println("����LORA_Initialization����");
		}

		return 1;
	}
	else
	{
		Serial.println("LORA��ʼ��ʧ��");
		Serial.println("LORA Initialization Setup failed");
		AT24CXX_WriteOneByte(0, 0x00);

		if (debug_print == 1)
		{
			Serial.println("����LORA_Initialization����");
		}

		return 0;
	}
}

String addr_write()
{
	String addr_data;
	unsigned long _addr_data;
	unsigned long x[8];
	String y[8];
	Serial.println("-------");

	for (size_t i = 8; i < lora_len - 2; i++)
	{
		if (debug_print == 1)
		{
			//Serial.println(lora_data[i]);//���ֵ
		}

		//���ֵ��0~9֮��
		if (lora_data[i] >= 48 && lora_data[i] <= 57)
		{
			x[i - 8] = lora_data[i] - 48;
			if (lora_data[i] == 48)
			{
				y[i - 8] = String(0, HEX);
			}
			else if (lora_data[i] == 49)
			{
				y[i - 8] = String(1, HEX);
			}
			else if (lora_data[i] == 50)
			{
				y[i - 8] = String(2, HEX);
			}
			else if (lora_data[i] == 51)
			{
				y[i - 8] = String(3, HEX);
			}
			else if (lora_data[i] == 52)
			{
				y[i - 8] = String(4, HEX);
			}
			else if (lora_data[i] == 53)
			{
				y[i - 8] = String(5, HEX);
			}
			else if (lora_data[i] == 54)
			{
				y[i - 8] = String(6, HEX);
			}
			else if (lora_data[i] == 55)
			{
				y[i - 8] = String(7, HEX);
			}
			else if (lora_data[i] == 56)
			{
				y[i - 8] = String(8, HEX);
			}
			else if (lora_data[i] == 57)
			{
				y[i - 8] = String(9, HEX);
			}
		}
		//���ֵ��A~F֮��
		else if (lora_data[i] >= 65 && lora_data[i] <= 70)
		{
			x[i - 8] = lora_data[i] - 55;
			if (lora_data[i] == 65)
			{
				y[i - 8] = String(10, HEX);
			}
			else if (lora_data[i] == 66)
			{
				y[i - 8] = String(11, HEX);
			}
			else if (lora_data[i] == 67)
			{
				y[i - 8] = String(12, HEX);
			}
			else if (lora_data[i] == 68)
			{
				y[i - 8] = String(13, HEX);
			}
			else if (lora_data[i] == 69)
			{
				y[i - 8] = String(14, HEX);
			}
			else if (lora_data[i] == 70)
			{
				y[i - 8] = String(15, HEX);
			}
		}
	}

	if (debug_print == 1)
	{
		/*for (size_t i = 0; i < 8; i++)
		{
			Serial.println(String("x[") + String(i) + String("] = ") + String(x[i]));
		}*/
	}

	for (size_t i = 0; i < 8; i++)
	{
		addr_data.concat(String(y[i]));//�����ַ���
		if (debug_print == 1)
		{
			Serial.println(String(y[i]));
			Serial.println(addr_data);
		}
	}
	if (debug_print == 1)
	{
		Serial.println("-------");
	}
	addr_data.toUpperCase();//��дת��
	if (debug_print == 1)
	{
		Serial.println(addr_data);
	}

	//15 * (16 ^ 2) + 15 * (16 ^ 1) + 15 * (16 ^ 0)
	//_addr_data = x[7] * (16 ^ 0) + x[6] * (16 ^ 6) + x[5] * (16 ^ 5) +...
	//for (int i = 7; i >= 0; i--)
	//{
	//	_addr_data = _addr_data + (x[i] * (pow(16, (7 - i))));
	//	delay(5);
	//	if (debug_print == 1)
	//	{
	//		//Serial.println(x[i] * (pow(16, (7 - i))));
	//	}
	//}
	//if (debug_print == 1)
	//{
	//	Serial.println(_addr_data);
	//	Serial.println(_addr_data,HEX);
	//	addr_data = String(_addr_data, HEX);
	//}
	//addr_data.toUpperCase();//��дת��
	//Serial.println(addr_data);

	//addr_data = String("18240E0C");

	return addr_data;
}

//�� �� ����LORA_Receive_information() 
//�����������������LORA���յ�����ϢȻ�󴫸�Judgement_function()
//����˵����
//���ú�����Judgement_function()
//ȫ�ֱ�����
//�� �룺
//�� �أ�
/////////////////////////////////////////////////////////////////////
void LORA_Receive_information(void)
{
	//do {
	//		while (Serial3.available() > 0)//���մ����յ�������
	//		{
	//			if (Receive_Length >= 200) break;
	//			Receive_Data[Receive_Length++] = Serial3.read();
	//			Serial.print(Receive_Data[Receive_Length - 1], HEX);
	//			Serial.print(" ");
	//			delay(5);
	//		}
	//	if (Receive_Length >= 60) Receive_Length = 0;

	//} while (1);
	/*if (Serial3.available() > 0)
	{
		delay(5000);
	}*/
	Receive_Length = 0;
	while (Serial3.available() > 0)//���մ����յ�������
	{
		if (Receive_Length >= 127) break;
		Receive_Data[Receive_Length++] = Serial3.read();
		/*Serial.print(Receive_Data[Receive_Length - 1], HEX);
		Serial.print(" ");*/
		delay(5);
	}
	if (Receive_Length > 0)
	{
		//Serial.write(Receive_Data,Receive_Length);//��16���ƣ��Զ�ת��ASCII��
		//Judgement_Length = 0;//�յ�����Ϣ����ж�����ĳ���ֵ
		Check_Length = 0;//�յ�����Ϣ���У������ĳ���ֵ
		Receive_data_lamp();
		if (debug_print == 1)
		{
			Serial.print("Receive_Length = ");//������յ������ݳ���
			Serial.println(Receive_Length);
		}

		//--------------------------------------------------------
		//��Receive_Data��ֵ����õ�Check_Data
		Check_Length = 0;
		for (int i = 4; i < Receive_Length - 0x07; i++)
		{
			if (Check_Length >= 127)
			{
				Serial.println("!!!Check_Length >= 200!!!");
				break;
			}
			Check_Data[Check_Length] = Receive_Data[i];
			if (debug_print == 1)
			{
				Serial.print("Check_Data ");
				Serial.print(Check_Length);
				Serial.print(" :");
				Serial.println(Check_Data[Check_Length], HEX);
			}
			Check_Length++;
			delay(5);
		}
		Serial.print("Check_Length = ");
		Serial.println(Check_Length);
		//--------------------------------------------------------

		if (Check_Length > 0)
		{
			CRC_Check_num = GetCrc8(Check_Data, Check_Length);
			if (debug_print == 1)
			{
				Serial.print("CRC8�����ֵCRC_Check_numΪ��0x");
				Serial.println(CRC_Check_num, HEX);
			}
		}

		//--------------------------------------------------------
		if (debug_crc == 1)
		{
			CRC_Check_num = 0xD6;//���д�����Ϊ�˲�����ÿ�ζ�����CRC��ʵ��ʹ����ע��
		}
		//--------------------------------------------------------

		Judgement_function(Receive_Data, Receive_Length - 1, CRC_Check_num);//�жϺ���

		Receive_Length = 0;	//��Receive_Length����
		Check_Length = 0;	//��Check_Length����
	}


	//-----------------------------------------------------------------------------------------------------
	//if (Serial3.available())
	//{
	//	LORA_RecData1 = Serial3.readString();
	//}
	//if (LORA_RecData1.length() > 0)
	//{
	//	LORA_RecData2 = LORA_RecData1;
	//	Receive_data_lamp();
	//	// void remove (index,count)
	//	//indexΪ��ѡ��������ʾ�����￪ʼɾ����ֻ����һ���������Ὣ�ַ���������ֵ��ʼһֱ����β�������ַ�ɾ��
	//	//�ڶ�������count��ʾɾ�����ٸ��ַ�
	//	//���õ��ַ����ı���
	//	LORA_RecData1.remove(0, LORA_RecData1.length());
	//	Judgement_Length = 0;//�յ�����Ϣ����ж�����ĳ���ֵ
	//	Check_Length = 0;//�յ�����Ϣ���У������ĳ���ֵ

	//	char const *c = LORA_RecData2.c_str();

	//	if (debug_print == 1)
	//	{
	//		Serial.println(String("LORA_RecData2.length()= ") + String(LORA_RecData2.length()));
	//		Serial.println("���յ�������Ϊ��");
	//		//Serial.write(c);
	//		//int shuzu_length = LORA_RecData2.length();
	//		byte shuzu[50];
	//		LORA_RecData2.getBytes(shuzu, (LORA_RecData2.length()+1));
	//		//LORA_RecData2.toCharArray(shuzu, (LORA_RecData2.length() + 1));
	//		for (size_t i = 0; i < LORA_RecData2.length(); i++)
	//		{
	//			Serial.print(String(i) + String(" / "));
	//			Serial.println(shuzu[i]);
	//		}
	//	}
	//}
}
