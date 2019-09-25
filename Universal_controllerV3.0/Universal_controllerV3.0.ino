// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       Universal_controllerV3.0.ino
    Created:	2019/9/23 23:40:40
    Author:     ���һ�
*/

// Define User Types below here or use a .h file
//


// Define Function Prototypes that use User Types below here or use a .h file
//


// Define Functions below here or use other .ino or cpp files
//#include <A_STM32_Examples.h>
//#include <ArduinoJson.hpp>
//#include <ArduinoJson.h>
#include <arduino.h>
#include "user_Set_Correlation.h"
#include "user_A025_E025.h"
#include "user_A021_E021.h"
#include "user_crc8.h"
#include "user_judgement.h"
#include "user_A011_E011.h"
#include "user_lorainit.h"
#include "user_initialization.h"
#include "AT24CXX.h"
#include "i2c.h"
#include "user_HEXtoDEC.h"
#include "user_filter.h"
//#include "RTClock.h"
//----------------------------------------------------------------------------------------------

//ȫ�ֱ���
//static unsigned long rtc_oldtime;
//----------------------------------------------------------------------------------------------



//�� �� ����setup() 
//������������ʼ����
//����˵����
//���ú�����
//ȫ�ֱ�����
//�� �룺
//�� �أ�
///////////////////////////////////////////////////////
void setup()
{
	Initialization();//��ʼ������

	/*Serial.println("��ʼ��ִ�н���");*/
	Serial.println("End of Initialization Execution");

	if (AT24CXX_ReadOneByte(0) == 0x01 && AT24CXX_ReadOneByte(1) == 0x01)
	{
		/*Serial.println("��ʼ������ִ�гɹ���");*/
		Serial.println("Successful execution of initializer!!!");

		//��ʼ�����״̬��1���̽�����˸5��
		for (size_t i = 0; i < 5; i++)
		{
			digitalWrite(LED1, HIGH);
			digitalWrite(LED2, LOW);
			delay(200);
			digitalWrite(LED1, LOW);
			digitalWrite(LED2, HIGH);
			delay(200);
			digitalWrite(LED1, LOW);
			digitalWrite(LED2, LOW);
		}

		Button_Waiting_report();//�����ȴ��ϱ�����
	}
	else
	{
		Initialization_exception();//��ʼ���쳣����
	}
}

//�� �� ����loop() 
//����������ѭ��ִ�еĴ���
//����˵����ѭ��ִ�еĴ���
//���ú�����
//ȫ�ֱ�����
//�� �룺
//�� �أ�
/////////////////////////////////////////////////////////////////////
// Add the main program code into the continuous loop() function
void loop()
{
	//RTC_request();//RTC������

	RTC_Clock();//RTCʱ�Ӻ���

	LORA_Receive_information();	//LORA�Ľ��պ���

	Automated_strategy();//�Զ����Ժ���

	Automatic_execution_test();//�Զ�ִ�в��Ժ���

	forswitch();//ִ�к���

	//Timely_reporting();//��ʱ�ϱ�״̬����

	Heartbeat();//��������

	Forced_Start_Relay();//ǿ�������̵���

	Restore_factory_settings();//�ָ��������ú���
}


//ǿ�������̵���
void Forced_Start_Relay(void)
{
	//����ǿ�������̵���
	if (digitalRead(K2) == LOW)
	{
		delay(500);
		if (digitalRead(K2) == LOW)
		{
			digitalWrite(KCZJ1, LOW);
			digitalWrite(KCZJ2, LOW);
		}
		else
		{
			digitalWrite(KCZJ1, HIGH);
			digitalWrite(KCZJ2, HIGH);
		}
	}
}

void Timely_reporting(void)//��ʱ�ϱ�״̬����
{
	if (millis() - Get_Delivery_oldtime() >= Delivery_time * 1000 && Get_Delivery_oldtime() > 0)
	{
		if (debug_print == 1)
		{
			Serial.println("��ʱ�Զ��ϱ�");
			//delay(1000);
		}
		//����״̬�Ļ�ִ
		Send_E021(Receive_IsBroadcast);
		Send_E022(Receive_IsBroadcast);
	}
}

void Heartbeat(void)//��������
{
	if (millis() - Get_HeartBeat_oldtime() >= Heartbeat_time * 1000 && Get_HeartBeat_oldtime() > 0)
	{
		if (debug_print == 1)
		{
			Serial.println("�����ϱ�");
			//delay(1000);
		}
		//���������Ļ�ִ
		Send_E023(Receive_IsBroadcast);
	}
}

void Restore_factory_settings(void)//�ָ��������ú���
{
	//���ǻָ�Ϊ�������ã�������
	if (digitalRead(K1) == LOW)
	{
		delay(2000);
		if (digitalRead(K1) == LOW)
		{
			////-------------------------------------------
			////======����ʱ���ô���飬ʵ��ʹ����ע��=====
			////�����еı�־λ����Ϊ0
			//AT24CXX_WriteOneByte(0, 0x00);//lora��ʼ���ı�־λ
			//AT24CXX_WriteOneByte(1, 0x00);//EEPROM���õı�־λ
			//AT24CXX_WriteOneByte(2, 0x00);//��ŵı�־λ
			//AT24CXX_WriteOneByte(13, 0x00);//�Զ����Եı�־λ
			////-------------------------------------------
			//Serial.println("��ʼ���лָ���������");

			//Initialization();//���½��г�ʼ��������
			//setup();//���½���setup()�������


			//����E011�����ϱ�����ǰ����
			Send_E011(Receive_IsBroadcast);//�����Receive_IsBroadcast�Ƿ���ֵ��
		}
	}
}

void Initialization_exception(void)//��ʼ���쳣����
{
	while (1)
	{
		digitalWrite(LED1, HIGH);
		//Serial.println("��ʼ������ִ��ʧ��");
		Serial.println("Initializer failed to execute!");
		delay(2000);
	}
}

void Button_Waiting_report(void)//�����ȴ��ϱ�����
{
	while (AT24CXX_ReadOneByte(2) == 0x00)//Register_OK_flag	�Ѿ������ŵı�־λ
	{
		//����δ���ù�������
		//Serial.println("δ���ù�������,����Ҫ���ù����������볤������1");
		Serial.println("No working parameters are set.If you need to set working parameters, press the key 1 for a long time.");
		digitalWrite(LED2, HIGH);
		delay(1500);
		//�ȴ�����1����
		if (digitalRead(K1) == LOW)
		{
			delay(2000);
			if (digitalRead(K1) == LOW)
			{
				digitalWrite(LED2, LOW);
				//Serial.println("K1����");
				//Serial.println("���豸��ʼ�ϱ���ǰ�����ò���");
				Serial.println("K1 press");
				Serial.println("The device starts to report the current setting parameters...");

				delay(250);
				//����E011�����ϱ�����ǰ����
				Send_E011(Receive_IsBroadcast);//�����Receive_IsBroadcast�Ƿ���ֵ��
				AT24CXX_WriteOneByte(2, 0X01);
			}
		}
	}
}

void RTC_request(void)//RTCʱ��������
{
	if (Get_RTC_Flag() == 0x00)//RTC_Flag	RTCʱ���Ƿ�ӵ�еı�־
	{
		int RTC_Wait_time = 5;
		unsigned long RTCtime_old;

		//����û��RTCʱ��
		Serial.println("RTCʱ��δ����,�ȴ�����������RTCʱ��...");

		//����RTCʱ�������
		Send_E024(Receive_IsBroadcast);

		RTCtime_old = millis();
		while (millis() - RTCtime_old <= RTC_Wait_time * 1000)
		{
			LORA_Receive_information();	//LORA�Ľ��պ���

			//Automated_strategy();//�Զ����Ժ���

			//forswitch();//ִ�к���

			//Timely_reporting();//��ʱ�ϱ�״̬����

			//Heartbeat();//��������

			Forced_Start_Relay();//ǿ�������̵���

			Restore_factory_settings();//�ָ��������ú���
		}
	}
	else
	{
		/*if (debug == 1)
		{
			if (debug_print == 1)
			{
				Serial.println("RTCʱ���Ѿ��������");
			}
			delay(1500);
		}*/
	}
}

/***
 *
 *
 *          .,:,,,                                        .::,,,::.
 *        .::::,,;;,                                  .,;;:,,....:i:
 *        :i,.::::,;i:.      ....,,:::::::::,....   .;i:,.  ......;i.
 *        :;..:::;::::i;,,:::;:,,,,,,,,,,..,.,,:::iri:. .,:irsr:,.;i.
 *        ;;..,::::;;;;ri,,,.                    ..,,:;s1s1ssrr;,.;r,
 *        :;. ,::;ii;:,     . ...................     .;iirri;;;,,;i,
 *        ,i. .;ri:.   ... ............................  .,,:;:,,,;i:
 *        :s,.;r:... ....................................... .::;::s;
 *        ,1r::. .............,,,.,,:,,........................,;iir;
 *        ,s;...........     ..::.,;:,,.          ...............,;1s
 *       :i,..,.              .,:,,::,.          .......... .......;1,
 *      ir,....:rrssr;:,       ,,.,::.     .r5S9989398G95hr;. ....,.:s,
 *     ;r,..,s9855513XHAG3i   .,,,,,,,.  ,S931,.,,.;s;s&BHHA8s.,..,..:r:
 *    :r;..rGGh,  :SAG;;G@BS:.,,,,,,,,,.r83:      hHH1sXMBHHHM3..,,,,.ir.
 *   ,si,.1GS,   sBMAAX&MBMB5,,,,,,:,,.:&8       3@HXHBMBHBBH#X,.,,,,,,rr
 *   ;1:,,SH:   .A@&&B#&8H#BS,,,,,,,,,.,5XS,     3@MHABM&59M#As..,,,,:,is,
 *  .rr,,,;9&1   hBHHBB&8AMGr,,,,,,,,,,,:h&&9s;   r9&BMHBHMB9:  . .,,,,;ri.
 *  :1:....:5&XSi;r8BMBHHA9r:,......,,,,:ii19GG88899XHHH&GSr.      ...,:rs.
 *  ;s.     .:sS8G8GG889hi.        ....,,:;:,.:irssrriii:,.        ...,,i1,
 *  ;1,         ..,....,,isssi;,        .,,.                      ....,.i1,
 *  ;h:               i9HHBMBBHAX9:         .                     ...,,,rs,
 *  ,1i..            :A#MBBBBMHB##s                             ....,,,;si.
 *  .r1,..        ,..;3BMBBBHBB#Bh.     ..                    ....,,,,,i1;
 *   :h;..       .,..;,1XBMMMMBXs,.,, .. :: ,.               ....,,,,,,ss.
 *    ih: ..    .;;;, ;;:s58A3i,..    ,. ,.:,,.             ...,,,,,:,s1,
 *    .s1,....   .,;sh,  ,iSAXs;.    ,.  ,,.i85            ...,,,,,,:i1;
 *     .rh: ...     rXG9XBBM#M#MHAX3hss13&&HHXr         .....,,,,,,,ih;
 *      .s5: .....    i598X&&A&AAAAAA&XG851r:       ........,,,,:,,sh;
 *      . ihr, ...  .         ..                    ........,,,,,;11:.
 *         ,s1i. ...  ..,,,..,,,.,,.,,.,..       ........,,.,,.;s5i.
 *          .:s1r,......................       ..............;shs,
 *          . .:shr:.  ....                 ..............,ishs.
 *              .,issr;,... ...........................,is1s;.
 *                 .,is1si;:,....................,:;ir1sr;,
 *                    ..:isssssrrii;::::::;;iirsssssr;:..
 *                         .,::iiirsssssssssrri;;:.
 *
 *
 *
 */
