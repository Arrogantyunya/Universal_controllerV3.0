// 
// 
// 

#include "user_A025_E025.h"

//函 数 名：Receive_A025() 
//功能描述：A025的执行函数
//函数说明：485设备通讯
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
void Receive_A025(unsigned char * Judgement_Data, int Judgement_Length)
{
	//--------------------------------------------------------
	//该区域为测试传输进Receive_A025函数的数据是否正确的测试代码块
	//需要测试时请取消注释
	if (debug_print == 1)
	{
		Serial.println("进入Receive_A025函数");
		for (int i = 0; i < Judgement_Length + 1; i++)
		{
			Serial.print("A025Judgement_Data ");
			Serial.print(i);
			Serial.print(" :");
			Serial.println(Judgement_Data[i], HEX);
			delay(1);
		}
		delay(200);
		Serial.print("Judgement_Length = ");
		Serial.println(Judgement_Length);
	}
	//--------------------------------------------------------
	//判断区域
	if (Judgement_Data[7] == AT24CXX_ReadOneByte(12))
	{
		int a = 0;
		for (size_t i = 8; i < Judgement_Length + 1 - 7; i++)
		{
			RS485[a] = Judgement_Data[i];
			a++;
		}
		if (a > 0)
		{
			for (int v = 0; v < a; v++)
			{
				if (debug_print == 1)
				{
					Serial.print(String("RS485[ ") + String(v) + String(" ]= "));
					Serial.println(RS485[v], HEX);
				}
			}
		}
		Serial2.write(RS485, 8);//发送485的指令
		Serial2.flush();
		a = 0;//清空

		//是否广播指令
		Receive_IsBroadcast = Judgement_Data[6];

		//进行状态的回执
		Send_E025(Receive_IsBroadcast);
	}
	else
	{
		E020_status = Incorrect_information_error;
		if (debug_print == 1)
		{
			Serial.println("区域信息不正确");
			Serial.println(String("E020_status = Incorrect_information_error") + String(E020_status));
		}
		//进行状态的回执
		Send_E020(Receive_IsBroadcast, E020_status);
	}

	if (debug_print == 1)
	{
		Serial.println("完成A025状态回执");
		Serial.println("结束Receive_A025函数");
	}
}

//函 数 名：Send_E025() 
//功能描述：E025的的回执函数
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
unsigned char Send_E025(int Receive_IsBroadcast)
{
	delay(500);
	while (Serial2.available() > 0)//RS485串口接收到数据
	{
		RS485[RS485_length++] = Serial2.read();
		/*RS485REceive_Length++;*/
		delay(5);
	}
	if (RS485_length > 0)
	{
		Receive_data_lamp();
		if (debug_print == 1)
		{
			Serial.print("RS485_length = ");
			Serial.println(RS485_length);
		}
		for (int i = 0; i < RS485_length; i++)
		{
			if (debug_print == 1)
			{
				Serial.print(String("RS485") + "[" + i + "]");
				Serial.println(RS485[i], HEX);
			}
		}
		E025_need_485length = RS485_length;
		RS485_length = 0;
	}
	unsigned char E025[50];
	unsigned char E025CRC[50];
	int E025_length = 15 + E025_need_485length;//数据的总长度，例如15+8 = 23,从1开始数为23
	Serial.println(String("E025_length = ") + String(E025_length));
	E025[0] = 0xFE;
	E025[1] = 0xE0;
	E025[2] = 0x25;
	E025[3] = E025_length - 11;
	E025[4] = 0xC0;
	E025[5] = 0x02;
	E025[6] = Judgement_Data[6];
	E025[7] = Judgement_Data[7];

	for (size_t i = 0; i < E025_need_485length; i++)//E025[15]
	{
		E025[8 + i] = RS485[i];
		if (debug_print == 1)
		{
			Serial.print(String("RS485") + "[" + i + "] = ");
			Serial.println(RS485[i], HEX);
			Serial.print(String("E025") + "[" + (i + 8) + "] = ");
			Serial.println(E025[i + 8], HEX);
		}
	}
	for (size_t i = 0; i < 16; i++)
	{
		if (debug_print == 1)
		{
			Serial.print(String("E025") + "[" + i + "] = ");
			Serial.println(E025[i], HEX);
		}
	}

	Check_Length = 0;
	for (size_t i = 0; i < 4 + E025_need_485length; i++)
	{
		E025CRC[i] = E025[i + 4];
		if (debug_print == 1)
		{
			Serial.print(String("E025CRC") + "[" + i + "]");
			Serial.println(E025CRC[i], HEX);
		}
		Check_Length++;
	}
	if (debug_print == 1)
	{
		Serial.println("Check_Length" + String(Check_Length));
	}
	if (Check_Length > 0)
	{
		if (debug_print == 1)
		{
			Serial.print("CRC8计算的值为：0x");
			Serial.println(GetCrc8(E025CRC, Check_Length), HEX);
		}
		E025_CRC8 = GetCrc8(E025CRC, Check_Length);
		Check_Length = 0;
	}

	E025[E025_length - 7] = E025_CRC8;//E025[16],CRC
	E025[E025_length - 6] = 0x0D;//E025[17]
	E025[E025_length - 5] = 0x0A;//E025[18]
	E025[E025_length - 4] = 0x0D;//E025[19]
	E025[E025_length - 3] = 0x0A;//E025[20]
	E025[E025_length - 2] = 0x0D;//E025[21]
	E025[E025_length - 1] = 0x0A;//E025[22]
	for (size_t i = 0; i < E025_length; i++)
	{
		if (debug_print == 1)
		{
			Serial.print(String("E025[") + String(i) + String("]="));
			Serial.println(E025[i], HEX);
		}
	}
	Serial3.write(E025, E025_length);
	Send_Data_Lamp();
	Serial.println("已发送E025的回执");
}

//函 数 名：E025_init() 
//功能描述：E025的的初始化函数
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
unsigned char E025_init()
{
	return 0;
}
