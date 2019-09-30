// 
// 
// 

#include "user_A021_E021.h"


//函 数 名：Receive_A021() 
//功能描述：A021的执行函数
//函数说明：设置某类型接口挂载的某一路子设备类型及工作组
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
void Receive_A021(unsigned char* Judgement_Data, int Judgement_Length)
{
	//--------------------------------------------------------
	//该区域为测试传输进Receive_A021函数的数据是否正确的测试代码块
	//需要测试时请取消注释
	if (debug_print == 1)
	{
		Serial.println("进入Receive_A021函数");
		for (int i = 0; i < Judgement_Length + 1; i++)
		{
			Serial.print("A021Judgement_Data ");
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
		// 防止数据冲突，增加延时随机函数
		delay(random(0, 5000));

		//是否广播指令
		Receive_IsBroadcast = Judgement_Data[6];

		//进行状态的回执
		Send_E021(Receive_IsBroadcast);//各路数状态的回执
		Send_E022(Receive_IsBroadcast);//各路数时间的回执
	}
	else
	{
		E015_status = Incorrect_information_error;
		if (debug_print == 1)
		{
			Serial.println("区域信息不正确");
			//Serial.println(String("E015_status = Incorrect_information_error") + String(E015_status));
		}
		//进行状态的回执
		Send_E015(Receive_IsBroadcast, E015_status);
	}

	if (debug_print == 1)
	{
		Serial.println("完成A021状态回执");
		Serial.println("结束Receive_A021函数");
	}
}

//函 数 名：Send_E021() 
//功能描述：E021的的回执函数
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
unsigned char Send_E021(int Receive_IsBroadcast)
{
	E021_init();

	E021_IsBroadcast = Receive_IsBroadcast;//E021的是否广播指令

	E021[0] = E021_FrameHead;
	E021[1] = E021_FrameId1;
	E021[2] = E021_FrameId2;
	E021[3] = E021_DataLen;
	E021[4] = E021_DeviceTypeID1;
	E021[5] = E021_DeviceTypeID2;
	E021[6] = E021_IsBroadcast;
	E021[7] = E021_ZoneId;
	E021[8] = E021_digIn1;
	E021[9] = E021_digIn2;
	E021[10] = E021_digOut1;
	E021[11] = E021_digOut2;
	E021[12] = E021_anaIn1_1;
	E021[13] = E021_anaIn1_2;
	E021[14] = E021_anaIn1_3;
	E021[15] = E021_anaIn2_1;
	E021[16] = E021_anaIn2_2;
	E021[17] = E021_anaIn2_3;
	E021[18] = E021_anaOut1_1;
	E021[19] = E021_anaOut1_2;
	E021[20] = E021_anaOut1_3;
	E021[21] = E021_anaOut2_1;
	E021[22] = E021_anaOut2_2;
	E021[23] = E021_anaOut2_3;
	for (size_t i = 4; i <= E021_DataLen + 0x03; i++)
	{
		Check_Data[Check_Length] = E021[i];
		// Check_Data[Check_Length] = 0x55;
		if (debug_print == 1)
		{
			Serial.print("Check_Data ");
			Serial.print(Check_Length);
			Serial.print(" :");
			Serial.println(Check_Data[Check_Length], HEX);
		}
		Check_Length++;
		delay(1);
	}
	Serial.print("Check_Length = ");
	Serial.println(Check_Length);

	if (Check_Length > 0)
	{
		E021_CRC8 = GetCrc8(Check_Data, Check_Length);//得到CRC数据
		if (debug_print == 1)
		{
			Serial.print("CRC8计算的值E021_CRC8 = 0x");
			Serial.println(E021_CRC8, HEX);
		}
		Check_Length = 0;
	}
	E021[24] = E021_CRC8;
	E021[25] = E021_FrameEnd1;
	E021[26] = E021_FrameEnd2;
	E021[27] = E021_FrameEnd3;
	E021[28] = E021_FrameEnd4;
	E021[29] = E021_FrameEnd5;
	E021[30] = E021_FrameEnd6;

	//该区域为串口查看E011回执的信息
	if (debug_print == 1)
	{
		for (int i = 0; i < 31; i++)
		{
			Serial.print(i);
			Serial.print("/");
			Serial.println(E021[i], HEX);
			delay(1);
		}
	}

	Serial3.write(E021, 31);
	Serial3.flush();
	Send_Data_Lamp();//发送数据灯
	return 0;
}

//函 数 名：E021_init() 
//功能描述：E021的的初始化函数
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
unsigned char E021_init()
{

	Delivery_oldtime = millis();//定时上报状态，在这里进行赋值

	E021_FrameHead = 0xFE;		//E021的帧头

	E021_FrameId1 = 0xE0;		//E021的帧ID1
	E021_FrameId2 = 0x21;		//E021的帧ID2

	E021_DataLen = 0x14;		//E021的数据长度

	E021_DeviceTypeID1 = 0xC0;	//E021的设备类型1
	E021_DeviceTypeID2 = 0x02;	//E021的设备类型2

	E021_IsBroadcast = 0x00;		//E021的是否广播指令

	E021_ZoneId = AT24CXX_ReadOneByte(12);			//E021的区域

	E021_GetDigitalStatus();
	E021_GetAnalogStatus();

	return 0;
}


//E021得到数字状态
int E021_GetDigitalStatus()
{
	byte DI_1[8] = { 0,0,0,0,0,0,0,0 }; String Str_DI1; int DIBin_1 = 0;
	byte DI_2[8] = { 0,0,0,0,0,0,0,0 }; String Str_DI2; int DIBin_2 = 0;
	byte DO_1[8] = { 0,0,0,0,0,0,0,0 }; String Str_DO1; int DOBin_1 = 0;
	byte DO_2[8] = { 0,0,0,0,0,0,0,0 }; String Str_DO2; int DOBin_2 = 0;

	DI_2[0] = 0;
	DI_2[1] = 0;
	DI_2[2] = 0;
	DI_2[3] = 0;
	DI_2[4] = 0;
	DI_2[5] = 0;
	DI_2[6] = digitalRead(DI2);	//digitalRead(DI2)
	DI_2[7] = digitalRead(DI1);	//digitalRead(DI1)

	for (int i = 7; i >= 0; i--)
	{
		DIBin_1 = DIBin_1 | (DI_1[7 - i] << i);
		DIBin_2 = DIBin_2 | (DI_2[7 - i] << i);
		if (debug_print == 1)
		{
			Serial.print(String("DIBin_1 = "));
			Serial.println(DIBin_1, BIN);
			Serial.print(String("DIBin_2 = "));
			Serial.println(DIBin_2, BIN);
		}
	}

	//Str_DI1 = String(DIBin_1,HEX); Str_DI2 = String(DIBin_2, HEX);

	/*if (debug_print == 1)
	{
		Serial.print("Str_DI1 = 0x");
		Serial.println(Str_DI1);
		Serial.print("Str_DI2 = 0x");
		Serial.println(Str_DI2);
	}

	long DI1_long = Str_DI1.toInt();
	long DI2_long = Str_DI2.toInt();
	if (debug_print == 1)
	{
		Serial.print("DI1_long = ");
		Serial.println(DI1_long,HEX);
		Serial.print("DI2_long = ");
		Serial.println(DI2_long,HEX);
	}*/

	E021_digIn1 = DIBin_1;
	E021_digIn2 = DIBin_2;

	if (debug_print == 1)
	{
		Serial.print("E021_digIn1,E021_digIn2 = ");
		Serial.println(E021_digIn1, HEX);
		Serial.print(" , ");
		Serial.println(E021_digIn2, HEX);
	}
	//--------------------------------------------------
	DO_2[0] = 0;
	DO_2[1] = 0;
	DO_2[2] = 0;
	DO_2[3] = 0;
	DO_2[4] = 0;
	DO_2[5] = 0;
	DO_2[4] = digitalRead(KCZJ2);	//digitalRead(KCZJ2);
	DO_2[4] == 0 ? DO_2[4] = 1 : DO_2[4] = 0;//对继电器2取反
	DO_2[5] = digitalRead(KCZJ1);	//digitalRead(KCZJ1);
	DO_2[5] == 0 ? DO_2[5] = 1 : DO_2[5] = 0;//对继电器1取反
	DO_2[6] = digitalRead(DO2);		//digitalRead(D02);
	DO_2[7] = digitalRead(DO1);		//digitalRead(D01);

	for (int i = 7; i >= 0; i--)
	{
		DOBin_1 = DOBin_1 | (DO_1[7 - i] << i);
		DOBin_2 = DOBin_2 | (DO_2[7 - i] << i);
		if (debug_print == 1)
		{
			Serial.print(String("DOBin_1 = "));
			Serial.println(DOBin_1, BIN);
			Serial.print(String("DOBin_2 = "));
			Serial.println(DOBin_2, BIN);
		}
	}

	//Str_DO1 = String(DOBin_1, HEX); Str_DO2 = String(DOBin_2, HEX);

	/*if (debug_print == 1)
	{
		Serial.print("Str_DO1 = 0x");
		Serial.println(Str_DO1);
		Serial.print("Str_DO2 = 0x");
		Serial.println(Str_DO2);
	}
	long DO1_long = Str_DO1.toInt();
	long DO2_long = Str_DO2.toInt();
	if (debug_print == 1)
	{
		Serial.print("DI1_long = ");
		Serial.println(DI1_long, HEX);
		Serial.print("DI2_long = ");
		Serial.println(DI2_long, HEX);
	}*/
	E021_digOut1 = DOBin_1;
	E021_digOut2 = DOBin_2;

	if (debug_print == 1)
	{
		Serial.print("E021_digOut1,E021_digOut2 = ");
		Serial.println(E021_digOut1, HEX);
		Serial.print(" , ");
		Serial.println(E021_digOut2, HEX);
	}

	return 0;
}


//E021得到模拟状态
int E021_GetAnalogStatus()
{
	int analogReadx[10];
	float ar1, ar2, ao1, ao2;

	//模拟输入1
	if (floor(ar1) >= 0 && floor(ar1) <= 99)//[0],(0,99]
	{
		//连续对该值采集10次
		for (size_t i = 0; i < 10; i++)
		{
			if (analogRead(VIN1) <= 2)
			{
				analogReadx[i] = 0;
			}
			else
			{
				analogReadx[i] = analogRead(VIN1);
			}
			delay(10);
			Serial.println(String("analogRead1[") + i + "]" + analogReadx[i]);
		}
		if (debug == 1)
		{
			//delay(1500);
		}

		ar1 = (((Filter(analogReadx, 10)) * 0.8056) * 11) / 1000;//进行滤波
		if (debug_print == 1)
		{
			Serial.println(String("ar1 = ") + ar1 + "V");
			//delay(1500);
		}

		E021_anaIn1_1 = floor(ar1);
		E021_anaIn1_2 = (ar1 - E021_anaIn1_1) * 100;
		E021_anaIn1_3 = 0xE2;
		if (debug_print == 1)
		{
			Serial.println(String("E021_anaIn1_1 = ") + E021_anaIn1_1);
			Serial.println(String("E021_anaIn1_2 = ") + E021_anaIn1_2);
			Serial.println(String("E021_anaIn1_3 = ") + E021_anaIn1_3);
		}
	}
	else//超出量程
	{
		Serial.println("模拟输入1超出量程");
		/*E021_anaIn1_1 = floor(ar1);
		E021_anaIn1_2 = (ar1 - E021_anaIn1_1) * 100;
		E021_anaIn1_3 = 0xE2;*/
		if (debug_print == 1)
		{
			Serial.println(String("E021_anaIn1_1 = ") + E021_anaIn1_1);
			Serial.println(String("E021_anaIn1_2 = ") + E021_anaIn1_2);
			Serial.println(String("E021_anaIn1_3 = ") + E021_anaIn1_3);
		}
	}

	//模拟输入2
	if (floor(ar2) >= 0 && floor(ar2) <= 99)//[0],(0,99]
	{
		//连续对该值采集10次
		for (size_t i = 0; i < 10; i++)
		{
			if (analogRead(VIN2) <= 2)
			{
				analogReadx[i] = 0;
			}
			else
			{
				analogReadx[i] = analogRead(VIN2);
			}
			delay(10);
			Serial.println(String("analogRead2[") + i + "]" + analogReadx[i]);
		}
		if (debug == 1)
		{
			//delay(1500);
		}

		ar2 = (((Filter(analogReadx, 10)) * 0.8056) * 11) / 1000;//进行滤波
		if (debug_print == 1)
		{
			Serial.println(String("ar2 = ") + ar2 + "V");
			//delay(1500);
		}

		E021_anaIn2_1 = floor(ar2);
		E021_anaIn2_2 = (ar2 - E021_anaIn2_1) * 100;
		E021_anaIn2_3 = 0xE2;
		if (debug_print == 1)
		{
			Serial.println(String("E021_anaIn2_1 = ") + E021_anaIn2_1);
			Serial.println(String("E021_anaIn2_2 = ") + E021_anaIn2_2);
			Serial.println(String("E021_anaIn2_3 = ") + E021_anaIn2_3);
		}
	}
	else//超出量程
	{
		Serial.println("模拟输入2超出量程");
		/*E021_anaIn2_1 = floor(ar2);
		E021_anaIn2_2 = (ar2 - E021_anaIn2_1) * 100;
		E021_anaIn2_3 = 0xE2;*/
		if (debug_print == 1)
		{
			Serial.println(String("E021_anaIn2_1 = ") + E021_anaIn2_1);
			Serial.println(String("E021_anaIn2_2 = ") + E021_anaIn2_2);
			Serial.println(String("E021_anaIn2_3 = ") + E021_anaIn2_3);
		}
	}

	//模拟输出1
	if (floor(ao1) >= 0 && floor(ao1) <= 99)//[0],(0,99]
	{
		//连续对该值采集10次
		for (size_t i = 0; i < 10; i++)
		{
			if (analogRead(AO1) <= 2)
			{
				analogReadx[i] = 0;
			}
			else
			{
				analogReadx[i] = analogRead(AO1);
			}
			delay(10);
			Serial.println(String("analogRead3[") + i + "]" + analogReadx[i]);
		}
		if (debug == 1)
		{
			//delay(1500);
		}

		ao1 = (((Filter(analogReadx, 10)) * 0.8056) * 11) / 1000;//进行滤波
		if (debug_print == 1)
		{
			Serial.println(String("ao1 = ") + ao1 + "V");
			//delay(1500);
		}

		E021_anaOut1_1 = floor(ao1);
		E021_anaOut1_2 = (ao1 - E021_anaOut1_1) * 100;
		E021_anaOut1_3 = 0xE2;
		if (debug_print == 1)
		{
			Serial.println(String("E021_anaOut1_1 = ") + E021_anaOut1_1);
			Serial.println(String("E021_anaOut1_2 = ") + E021_anaOut1_2);
			Serial.println(String("E021_anaOut1_3 = ") + E021_anaOut1_3);
		}
	}
	else//超出量程
	{
		Serial.println("模拟输入2超出量程");
		/*E021_anaOut1_1 = floor(ao1);
		E021_anaOut1_2 = (ao1 - E021_anaOut1_1) * 100;
		E021_anaOut1_3 = 0xE2;*/
		if (debug_print == 1)
		{
			Serial.println(String("E021_anaOut1_1 = ") + E021_anaOut1_1);
			Serial.println(String("E021_anaOut1_2 = ") + E021_anaOut1_2);
			Serial.println(String("E021_anaOut1_3 = ") + E021_anaOut1_3);
		}
	}

	//模拟输出2
	if (floor(ao2) >= 0 && floor(ao2) <= 99)//[0],(0,99]
	{
		//连续对该值采集10次
		for (size_t i = 0; i < 10; i++)
		{
			if (analogRead(AO2) <= 2)
			{
				analogReadx[i] = 0;
			}
			else
			{
				analogReadx[i] = analogRead(AO2);
			}
			delay(10);
			Serial.println(String("analogRead4[") + i + "]" + analogReadx[i]);
		}
		if (debug == 1)
		{
			//delay(1500);
		}

		ao2 = (((Filter(analogReadx, 10)) * 0.8056) * 11) / 1000;//进行滤波
		if (debug_print == 1)
		{
			Serial.println(String("ao2 = ") + ao2 + "V");
			//delay(1500);
		}

		E021_anaOut2_1 = floor(ao2);
		E021_anaOut2_2 = (ao2 - E021_anaOut2_1) * 100;
		E021_anaOut2_3 = 0xE2;
		if (debug_print == 1)
		{
			Serial.println(String("E021_anaOut2_1 = ") + E021_anaOut2_1);
			Serial.println(String("E021_anaOut2_2 = ") + E021_anaOut2_2);
			Serial.println(String("E021_anaOut2_3 = ") + E021_anaOut2_3);
		}
	}
	else//超出量程
	{
		Serial.println("模拟输入2超出量程");
		/*E021_anaOut2_1 = floor(ao2);
		E021_anaOut2_2 = (ao2 - E021_anaOut2_1) * 100;
		E021_anaOut2_3 = 0xE2;*/
		if (debug_print == 1)
		{
			Serial.println(String("E021_anaOut2_1 = ") + E021_anaOut2_1);
			Serial.println(String("E021_anaOut2_2 = ") + E021_anaOut2_2);
			Serial.println(String("E021_anaOut2_3 = ") + E021_anaOut2_3);
		}
	}
	return 0;
}


//函 数 名：Get_Delivery_oldtime() 
//功能描述：得到Delivery_oldtime的时间值
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
unsigned long Get_Delivery_oldtime()
{
	if (debug_print == 1)
	{
		//Serial.println(String("Delivery_oldtime = ") + Delivery_oldtime);
	}
	return Delivery_oldtime;
}

