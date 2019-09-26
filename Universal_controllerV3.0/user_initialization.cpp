//user_initialization.cpp
/*
*版权
*
* 文件名称:user_initialization.cpp
* 文件标识:配置管理计划书
* 摘要:对引脚进行初始化
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


#include "user_initialization.h"


//函 数 名：Initialization() 
//功能描述：初始化的函数
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
void Initialization()//初始化函数
{
	//初始化引脚
	afio_cfg_debug_ports(AFIO_DEBUG_SW_ONLY);//因为引脚复用
	pinMode(RESETN, OUTPUT);//复位电路，给高电平进行复位
	pinMode(KCZJ1, OUTPUT);//继电器1
	pinMode(KCZJ2, OUTPUT);//继电器2
	pinMode(LED1, OUTPUT);//LED1，灯1红
	pinMode(LED2, OUTPUT);//LED2，灯1绿
	pinMode(LED3, OUTPUT);//LED3，灯2绿
	pinMode(LED4, OUTPUT);//LED4，灯2红
	pinMode(K1, INPUT);//按键1
	pinMode(K2, INPUT);//按键2
	pinMode(LORA_PWR, OUTPUT);//LORA电源
	pinMode(RESETN, OUTPUT);//LORA复位
	pinMode(AT_CMD, OUTPUT);//LORA设置
	pinMode(WAKE_UP, OUTPUT);//LORA唤醒
	pinMode(VIN1, INPUT_ANALOG);//模拟输入电压1
	pinMode(VIN2, INPUT_ANALOG);//模拟输入电压2
	pinMode(AO1, PWM);//模拟输出1
	pinMode(AO2, PWM);//模拟输出2
	pinMode(DI1, INPUT_PULLDOWN);//数字输入1
	pinMode(DI2, INPUT_PULLDOWN);//数字输入2
	pinMode(DO1, OUTPUT);//数字输出1
	pinMode(DO2, OUTPUT);//数字输出2
	pinMode(WP, OUTPUT);//EEPROM的写入脚


	//初始化串口
	Serial.begin(9600);		//USB串口
	Serial2.begin(9600);	//485的串口
	Serial3.begin(9600);	//LORA的串口

	//继电器初始化//
	digitalWrite(KCZJ1, HIGH);
	digitalWrite(KCZJ2, HIGH);

	//LED初始化
	digitalWrite(LED1, LOW);
	digitalWrite(LED2, LOW);
	digitalWrite(LED3, LOW);
	digitalWrite(LED4, LOW);

	//lora相关初始化//
	digitalWrite(LORA_PWR, HIGH);
	digitalWrite(RESETN, HIGH);
	digitalWrite(AT_CMD, LOW);

	//EEPROM
	i2cInit();


	if (debug == 0)
	{
		delay(1000);
	}

	//进入初始化程序时状态灯1绿灯闪烁5次
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
		//======测试时所用代码块=====
		//将所有的标志位都清为0
		Serial.println("debug == 1");
		if (LORA_reset == 1)
		{
			Serial.println("LORA_reset == 1");
			AT24CXX_WriteOneByte(0, 0x00);//LORA初始化完成的标志位
		}
		//else
		//{
		//	AT24CXX_WriteOneByte(0, 0x01);//LORA初始化完成的标志位
		//}
		AT24CXX_WriteOneByte(1, 0x00);//EEPROM初始化完成的标志位
		AT24CXX_WriteOneByte(2, 0x00);//申号完成的标志位
	}

	//设置EEPROM的初始化
	if (AT24CXX_ReadOneByte(1) == 0x01)
	{
		//说明进行过EEPROM的初始化
		//Serial.println("EEPROM已进行过初始化");
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
			//Serial.println("LORA进行初始化");
			Serial.println("LORA begin init");
			AT24CXX_WriteOneByte(0, 0x00);//LORA初始化完成的标志位
		}
		//else
		//{
		//	AT24CXX_WriteOneByte(0, 0x01);//LORA初始化完成的标志位
		//}
		AT24CXX_WriteOneByte(1, 0x00);//EEPROM初始化完成的标志位
		AT24CXX_WriteOneByte(2, 0x00);//申号完成的标志位
		for (size_t i = 3; i <= 11; i++)//SN的存储
		{
			AT24CXX_WriteOneByte(i, 0x00);
		}
		AT24CXX_WriteOneByte(12, 0x01);//LORA主设备区域ID的存储
		AT24CXX_WriteOneByte(13, 0x00);//LORA自动策略关联的标志位
		for (size_t i = 14; i <= 55; i++)//工作组数组的初始化
		{
			AT24CXX_WriteOneByte(i, 0x01);
		}
		for (size_t i = 56; i <= 88; i++)//预留字段的初始化
		{
			AT24CXX_WriteOneByte(i, 0x00);
		}

		AT24CXX_WriteOneByte(89, 100);//存储字节的标志位

		for (size_t i = 90; i <= 99; i++)//自动策略语句开始结束位置的初始化
		{
			AT24CXX_WriteOneByte(i, 0x00);
		}

		for (size_t i = 100; i < AT24C02_bytes; i++)//自动策略语句存放区域的初始化
		{
			AT24CXX_WriteOneByte(i, 0x00);
		}



		//---------------------------------------------------------
		AT24CXX_WriteOneByte(1, 0x01);//EEPROM初始化完成的标志位
		//Serial.println(EEPROM.read(1),HEX);
		Serial.println("EEPROM存储空间的初始化完成");
		Serial.println("EEPROM Successful setup");
		if (debug == 1)
		{
			delay(1000);
		}
	}

	//这里就读取LORA标志位是否设置完成，未设置完成就进行LORA模块的设置
	if (AT24CXX_ReadOneByte(0) == 0x01)
	{
		Serial.println("LORA已进行过初始化");
		Serial.println("LORA already setup");
		if (debug == 1)
		{
			delay(1000);
		}
	}
	else
	{
		Serial.println("LORA开始设置......");
		Serial.println("LORA Setup Begin......");
		Serial.println(AT24CXX_ReadOneByte(0), HEX);//0
		if (debug == 1)
		{
			delay(1000);
		}
		//进入LORA设置的函数
		LORA_Initialization();
	}


	if (debug == 1)
	{
		Serial.println("结束初始化函数");
		Serial.println("End Initialization function");
	}

}

//发送数据灯
void Send_Data_Lamp(void)
{
	digitalWrite(LED3, HIGH);
	delay(250);
	digitalWrite(LED3, LOW);
}

//接收数据灯
void Receive_data_lamp(void)
{
	digitalWrite(LED4, HIGH);
	delay(250);
	digitalWrite(LED4, LOW);
}

//恢复出厂设置灯
void Restore_actory_setting_lamp(void)
{
	//进行出厂设置灯
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
