// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       Universal_controllerV3.0.ino
    Created:	2019/9/23 23:40:40
    Author:     刘家辉
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

//全局变量
//static unsigned long rtc_oldtime;
//----------------------------------------------------------------------------------------------



//函 数 名：setup() 
//功能描述：起始代码
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：
///////////////////////////////////////////////////////
void setup()
{
	Initialization();//初始化函数

	/*Serial.println("初始化执行结束");*/
	Serial.println("End of Initialization Execution");

	if (AT24CXX_ReadOneByte(0) == 0x01 && AT24CXX_ReadOneByte(1) == 0x01)
	{
		/*Serial.println("初始化程序执行成功！");*/
		Serial.println("Successful execution of initializer!!!");

		//初始化完成状态灯1红绿交替闪烁5次
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

		Button_Waiting_report();//按键等待上报函数
	}
	else
	{
		Initialization_exception();//初始化异常函数
	}
}

//函 数 名：loop() 
//功能描述：循环执行的代码
//函数说明：循环执行的代码
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
// Add the main program code into the continuous loop() function
void loop()
{
	//RTC_request();//RTC请求函数

	RTC_Clock();//RTC时钟函数

	LORA_Receive_information();	//LORA的接收函数

	Automated_strategy();//自动策略函数

	Automatic_execution_test();//自动执行测试函数

	forswitch();//执行函数

	//Timely_reporting();//定时上报状态函数

	Heartbeat();//心跳函数

	Forced_Start_Relay();//强制启动继电器

	Restore_factory_settings();//恢复出厂设置函数
}


//强制启动继电器
void Forced_Start_Relay(void)
{
	//这是强制启动继电器
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

void Timely_reporting(void)//定时上报状态函数
{
	if (millis() - Get_Delivery_oldtime() >= Delivery_time * 1000 && Get_Delivery_oldtime() > 0)
	{
		if (debug_print == 1)
		{
			Serial.println("定时自动上报");
			//delay(1000);
		}
		//进行状态的回执
		Send_E021(Receive_IsBroadcast);
		Send_E022(Receive_IsBroadcast);
	}
}

void Heartbeat(void)//心跳函数
{
	if (millis() - Get_HeartBeat_oldtime() >= Heartbeat_time * 1000 && Get_HeartBeat_oldtime() > 0)
	{
		if (debug_print == 1)
		{
			Serial.println("心跳上报");
			//delay(1000);
		}
		//进行心跳的回执
		Send_E023(Receive_IsBroadcast);
	}
}

void Restore_factory_settings(void)//恢复出厂设置函数
{
	//这是恢复为出厂设置，请慎用
	if (digitalRead(K1) == LOW)
	{
		delay(2000);
		if (digitalRead(K1) == LOW)
		{
			////-------------------------------------------
			////======测试时所用代码块，实际使用请注释=====
			////将所有的标志位都清为0
			//AT24CXX_WriteOneByte(0, 0x00);//lora初始化的标志位
			//AT24CXX_WriteOneByte(1, 0x00);//EEPROM设置的标志位
			//AT24CXX_WriteOneByte(2, 0x00);//申号的标志位
			//AT24CXX_WriteOneByte(13, 0x00);//自动策略的标志位
			////-------------------------------------------
			//Serial.println("开始进行恢复出厂设置");

			//Initialization();//重新进行初始化的设置
			//setup();//重新进入setup()进行申号


			//进入E011函数上报请求当前参数
			Send_E011(Receive_IsBroadcast);//这里的Receive_IsBroadcast是否有值？
		}
	}
}

void Initialization_exception(void)//初始化异常函数
{
	while (1)
	{
		digitalWrite(LED1, HIGH);
		//Serial.println("初始化程序执行失败");
		Serial.println("Initializer failed to execute!");
		delay(2000);
	}
}

void Button_Waiting_report(void)//按键等待上报函数
{
	while (AT24CXX_ReadOneByte(2) == 0x00)//Register_OK_flag	已经完成申号的标志位
	{
		//代表未设置工作参数
		//Serial.println("未设置工作参数,如需要设置工作参数，请长按按键1");
		Serial.println("No working parameters are set.If you need to set working parameters, press the key 1 for a long time.");
		digitalWrite(LED2, HIGH);
		delay(1500);
		//等待按键1按下
		if (digitalRead(K1) == LOW)
		{
			delay(2000);
			if (digitalRead(K1) == LOW)
			{
				digitalWrite(LED2, LOW);
				//Serial.println("K1按下");
				//Serial.println("本设备开始上报当前的设置参数");
				Serial.println("K1 press");
				Serial.println("The device starts to report the current setting parameters...");

				delay(250);
				//进入E011函数上报请求当前参数
				Send_E011(Receive_IsBroadcast);//这里的Receive_IsBroadcast是否有值？
				AT24CXX_WriteOneByte(2, 0X01);
			}
		}
	}
}

void RTC_request(void)//RTC时间请求函数
{
	if (Get_RTC_Flag() == 0x00)//RTC_Flag	RTC时间是否拥有的标志
	{
		int RTC_Wait_time = 5;
		unsigned long RTCtime_old;

		//代表没有RTC时间
		Serial.println("RTC时间未设置,等待服务器设置RTC时间...");

		//进行RTC时间的请求
		Send_E024(Receive_IsBroadcast);

		RTCtime_old = millis();
		while (millis() - RTCtime_old <= RTC_Wait_time * 1000)
		{
			LORA_Receive_information();	//LORA的接收函数

			//Automated_strategy();//自动策略函数

			//forswitch();//执行函数

			//Timely_reporting();//定时上报状态函数

			//Heartbeat();//心跳函数

			Forced_Start_Relay();//强制启动继电器

			Restore_factory_settings();//恢复出厂设置函数
		}
	}
	else
	{
		/*if (debug == 1)
		{
			if (debug_print == 1)
			{
				Serial.println("RTC时间已经设置完成");
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
