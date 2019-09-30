//user_Public_directive.cpp
/*
*版权
*
* 文件名称:user_Public_directive.cpp
* 文件标识:配置管理计划书
* 摘要:
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

#include "user_Public_directive.h"


//函 数 名：Receive_A011() 
//功能描述：A011的执行函数
//函数说明：查询LORA主设备的参数(当前区域以及SN)
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
void Receive_A011(unsigned char* Judgement_Data, int Judgement_Length)//A011函数
{

	//--------------------------------------------------------
	//该区域为测试传输进Receive_A011函数的数据是否正确的测试代码块
	//需要测试时请取消注释
	if (debug_print == 1)
	{
		Serial.println("进入Receive_A011函数");
		for (int i = 0; i < Judgement_Length + 1; i++)
		{
			Serial.print("A011Judgement_Data ");
			Serial.print(i);
			Serial.print(" :");
			Serial.println(Judgement_Data[i], HEX);
			delay(1);
		}
		delay(500);
		Serial.print("Judgement_Length = ");
		Serial.println(Judgement_Length);
	}
	//--------------------------------------------------------
	//int ZoneID = Judgement_Data[7];
	//if (debug_print == 1)
	//{
	//	Serial.println(ZoneID, HEX);
	//}
	//AT24CXX_WriteOneByte(12, ZoneID);//将区域ID写入数组
	//for (size_t i = 8; i <= 16; i++)
	//{
	//	AT24CXX_WriteOneByte(i - 5, Judgement_Data[i]);
	//	if (debug_print == 1)
	//	{
	//		Serial.print(String("AT24CXX_ReadOneByte[ ") + String(i-5) + String(" ]="));
	//		Serial.println(AT24CXX_ReadOneByte(i - 5), HEX);
	//	}
	//}
	//判断区域
	if (Judgement_Data[7] == AT24CXX_ReadOneByte(A_ZoneID))
	{
		//是否广播指令
		Receive_IsBroadcast = Judgement_Data[6];

		//进行状态的回执
		Send_E011(Receive_IsBroadcast);
	}
	else
	{
		//E020_status = Incorrect_information_error;
		if (debug_print == 1)
		{
			Serial.println("区域信息不正确");
			//Serial.println(String("E020_status = Incorrect_information_error") + String(E020_status));
		}
		//进行状态的回执
		//Send_E020(Receive_IsBroadcast, E020_status);
	}

	if (debug_print == 1)
	{
		Serial.println("完成A011状态回执");
		Serial.println("结束Receive_A011函数");
	}
}

//函 数 名：Receive_A012() 
//功能描述：A012的执行函数
//函数说明：基地服务器设置LORA设备的工作组编号
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
void Receive_A012(unsigned char* Judgement_Data, int Judgement_Length)
{
	for (size_t i = 0; i < 5; i++)
	{
		Serial.println("没有用到的指令A012！！！");
	}
}

//函 数 名：Receive_A013() 
//功能描述：A013的执行函数
//函数说明：基地服务器设置设备SN，区域及子设备总路数
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
void Receive_A013(unsigned char* Judgement_Data, int Judgement_Length)
{
	//--------------------------------------------------------
	//该区域为测试传输进Receive_A013函数的数据是否正确的测试代码块
	//需要测试时请取消注释
	if (debug_print == 1)
	{
		Serial.println("进入Receive_A013函数");
		for (int i = 0; i < Judgement_Length + 1; i++)
		{
			Serial.print("A013Judgement_Data ");
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
	int ZoneID = Judgement_Data[7];
	if (debug_print == 1)
	{
		Serial.print("ZoneID = ");
		Serial.println(ZoneID, HEX);
	}
	AT24CXX_WriteOneByte(A_ZoneID, ZoneID);	//将区域ID写入EEPROM
	for (size_t i = A_SN_1; i <= A_SN_9; i++)	//将SN写入EEPROM
	{
		AT24CXX_WriteOneByte(i, Judgement_Data[i+7]);
		if (debug_print == 1)
		{
			Serial.print(String("AT24CXX_ReadOneByte[ ") + String(i) + String(" ]="));
			Serial.println(AT24CXX_ReadOneByte(i), HEX);
		}
	}

	//是否广播指令
	Receive_IsBroadcast = Judgement_Data[6];

	if (SN_ZoneISOK(Judgement_Data, Judgement_Length) == 1)
	{
		E015_status = SetSnAndSlaverCountOk;
		if (debug_print == 1)
		{
			//Serial.println("ZoneISOK!!!");
			Serial.println(String("E015_status = SetSnAndSlaverCountOk") + String(E015_status));
		}
	}
	else
	{
		E015_status = SetSnAndSlaverCountErr;
		if (debug_print == 1)
		{
			//Serial.println("ZoneISNOTOK!!!");
			Serial.println(String("E015_status = SetSnAndSlaverCountErr") + String(E015_status));
		}
	}


	//进行状态的回执
	Send_E015(Receive_IsBroadcast, E015_status);
	if (debug_print == 1)
	{
		Serial.println("完成A013状态的回执函数Send_E015");
		Serial.println("结束Receive_A013函数");
	}
}

//函 数 名：Receive_A014() 
//功能描述：A014的执行函数
//函数说明：查询LORA设备的工作状态
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
void Receive_A014(unsigned char* Judgement_Data, int Judgement_Length)
{
	//--------------------------------------------------------
	//该区域为测试传输进Receive_A014函数的数据是否正确的测试代码块
	//需要测试时请取消注释
	if (debug_print == 1)
	{
		Serial.println("进入Receive_A014函数");
		for (int i = 0; i < Judgement_Length + 1; i++)
		{
			Serial.print("A014Judgement_Data ");
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
	if (Judgement_Data[7] == AT24CXX_ReadOneByte(A_ZoneID))
	{
		// 防止数据冲突，增加延时随机函数
		debug == 0x01 ? delay(1) : delay(random(0, 5000));
		//delay(random(0, 5000));

		//是否广播指令
		Receive_IsBroadcast = Judgement_Data[6];

		//进行状态的回执
		Send_E014(Receive_IsBroadcast);//各路数状态的回执
		Send_E022(Receive_IsBroadcast);//各路数时间的回执
	}
	else
	{
		//E020_status = Incorrect_information_error;
		if (debug_print == 1)
		{
			Serial.println("区域信息不正确");
			//Serial.println(String("E020_status = Incorrect_information_error") + String(E020_status));
		}
		//进行状态的回执
		//Send_E020(Receive_IsBroadcast, E020_status);
	}

	if (debug_print == 1)
	{
		Serial.println("完成A014状态回执");
		Serial.println("结束Receive_A014函数");
	}
}


//函 数 名：Receive_A015() 
//功能描述：A015的执行函数
//函数说明：强制停止工作指令
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
void Receive_A015(unsigned char* Judgement_Data, int Judgement_Length)
{
	//--------------------------------------------------------
//该区域为测试传输进Receive_A015函数的数据是否正确的测试代码块
//需要测试时请取消注释
	if (debug_print == 1)
	{
		Serial.println("进入Receive_A015函数");
		for (int i = 0; i < Judgement_Length + 1; i++)
		{
			Serial.print("A015Judgement_Data ");
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
	if (Judgement_Data[7] == AT24CXX_ReadOneByte(A_ZoneID))
	{
		// 防止数据冲突，增加延时随机函数
		//debug == 0x01 ? delay(1) : delay(random(0, 5000));
		//delay(random(0, 5000));

		//是否广播指令
		Receive_IsBroadcast = Judgement_Data[6];
		Allclose();//全关函数

		//进行状态的回执
		Send_E021(Receive_IsBroadcast);//各路数状态的回执
		//Send_E015(Receive_IsBroadcast, E015_status);
	}
	else
	{
		//E015_status = Incorrect_information_error;
		if (debug_print == 1)
		{
			Serial.println("区域信息不正确");
			//Serial.println(String("E015_status = Incorrect_information_error") + String(E015_status));
		}
		//进行状态的回执
		//Send_E015(Receive_IsBroadcast, E015_status);
	}

	if (debug_print == 1)
	{
		Serial.println("完成A015状态回执");
		Serial.println("结束Receive_A015函数");
	}
}


//函 数 名：Send_E011() 
//功能描述：按键上报当前参数
//函数说明：E011帧的函数
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
unsigned char Send_E011(int Receive_IsBroadcast)//E011函数
{

	E011_init();//E011初始化函数

	E011_IsBroadcast = Receive_IsBroadcast;//E011的是否广播指令

	E011[0] = E011_FrameHead;
	E011[1] = E011_FrameId1;
	E011[2] = E011_FrameId2;
	E011[3] = E011_DataLen;
	E011[4] = E011_DeviceTypeID1;
	E011[5] = E011_DeviceTypeID2;
	E011[6] = E011_IsBroadcast;
	E011[7] = E011_ZoneId;
	E011[8] = E011_GroupIDArray1;
	E011[9] = E011_GroupIDArray2;
	E011[10] = E011_GroupIDArray3;
	E011[11] = E011_GroupIDArray4;
	E011[12] = E011_GroupIDArray5;

	E011[13] = E011_DeviceSN1;
	E011[14] = E011_DeviceSN2;
	E011[15] = E011_DeviceSN3;
	E011[16] = E011_DeviceSN4;
	E011[17] = E011_DeviceSN5;
	E011[18] = E011_DeviceSN6;
	E011[19] = E011_DeviceSN7;
	E011[20] = E011_DeviceSN8;
	E011[21] = E011_DeviceSN9;

	E011[22] = E011_channel;
	E011[23] = E011_interval1;
	E011[24] = E011_interval2;

	E011[25] = E011_NewTime1;
	E011[26] = E011_NewTime2;
	E011[27] = E011_NewTime3;
	E011[28] = E011_NewTime4;
	E011[29] = E011_NewTime5;
	E011[30] = E011_NewTime6;
	E011[31] = E011_NewTime7;

	E011[32] = E011_Allocate1;
	E011[33] = E011_Allocate2;
	E011[34] = E011_Allocate3;
	E011[35] = E011_Allocate4;
	E011[36] = E011_Allocate5;
	E011[37] = E011_Allocate6;
	E011[38] = E011_Allocate7;
	E011[39] = E011_Allocate8;

	for (size_t i = 4; i <= E011_DataLen + 0x03; i++)
	{
		Check_Data[Check_Length] = E011[i];
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
		E011_CRC8 = GetCrc8(Check_Data, Check_Length);//得到CRC数据
		if (debug_print == 1)
		{
			Serial.print("CRC8计算的值E011_CRC8 = 0x");
			Serial.println(E011_CRC8, HEX);
		}
		Check_Length = 0;
	}
	E011[40] = E011_CRC8;
	E011[41] = E011_FrameEnd1;
	E011[42] = E011_FrameEnd2;
	E011[43] = E011_FrameEnd3;
	E011[44] = E011_FrameEnd4;
	E011[45] = E011_FrameEnd5;
	E011[46] = E011_FrameEnd6;

	//该区域为串口查看E011回执的信息
	if (debug_print == 1)
	{
		for (int i = 0; i < 47; i++)
		{
			Serial.print(i);
			Serial.print("/");
			Serial.println(E011[i], HEX);
			delay(1);
		}
	}

	Serial3.write(E011, 47);
	Serial3.flush();
	Send_Data_Lamp();//发送数据灯
	return 0;
}


//函 数 名：E011_init() 
//功能描述：
//函数说明：E011初始化函数
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
unsigned char E011_init()
{
	E011_FrameHead = 0xFE;                  //E011的帧头

	E011_FrameId1 = 0xE0;                   //E011的帧ID1
	E011_FrameId2 = 0x11;                   //E011的帧ID2

	E011_DataLen = 0x24;                    //E011的数据长度

	E011_DeviceTypeID1 = 0xC0;				//E011的设备类型1
	E011_DeviceTypeID2 = 0x02;				//E011的设备类型2

	E011_IsBroadcast = Receive_IsBroadcast;//E011的是否广播指令

	E011_ZoneId = AT24CXX_ReadOneByte(A_ZoneID);         //E011的区域

	E011_GroupIDArray1 = 0x01;		//E011的组ID数组1
	E011_GroupIDArray2 = 0x00;		//E011的组ID数组2	
	E011_GroupIDArray3 = 0x00;		//E011的组ID数组3	
	E011_GroupIDArray4 = 0x00;		//E011的组ID数组4	
	E011_GroupIDArray5 = 0x00;		//E011的组ID数组5	

	E011_DeviceSN1 = AT24CXX_ReadOneByte(A_SN_1);       //E011的SN1
	E011_DeviceSN2 = AT24CXX_ReadOneByte(A_SN_2);       //E011的SN2
	E011_DeviceSN3 = AT24CXX_ReadOneByte(A_SN_3);       //E011的SN3
	E011_DeviceSN4 = AT24CXX_ReadOneByte(A_SN_4);       //E011的SN4
	E011_DeviceSN5 = AT24CXX_ReadOneByte(A_SN_5);       //E011的SN5
	E011_DeviceSN6 = AT24CXX_ReadOneByte(A_SN_6);       //E011的SN6
	E011_DeviceSN7 = AT24CXX_ReadOneByte(A_SN_7);       //E011的SN7
	E011_DeviceSN8 = AT24CXX_ReadOneByte(A_SN_8);      //E011的SN8
	E011_DeviceSN9 = AT24CXX_ReadOneByte(A_SN_9);      //E011的SN9

	E011_channel = 0x01;			//E011的路数

	E011_interval1 = 0x00;			//E011的采集时间间隔1
	E011_interval2 = 0x00;			//E011的采集时间间隔2

	E011_NewTime1 = 0x00;		//E011的时间1
	E011_NewTime2 = 0x00;		//E011的时间2
	E011_NewTime3 = 0x00;		//E011的时间3
	E011_NewTime4 = 0x00;		//E011的时间4
	E011_NewTime5 = 0x00;		//E011的时间5
	E011_NewTime6 = 0x00;		//E011的时间6
	E011_NewTime7 = 0x00;		//E011的时间7

	E011_Allocate1 = 0x00;		//E011的预留字段1
	E011_Allocate2 = 0x00;		//E011的预留字段2
	E011_Allocate3 = 0x00;		//E011的预留字段3
	E011_Allocate4 = 0x00;		//E011的预留字段4
	E011_Allocate5 = 0x00;		//E011的预留字段5
	E011_Allocate6 = 0x00;		//E011的预留字段6
	E011_Allocate7 = 0x00;		//E011的预留字段7
	E011_Allocate8 = 0x00;		//E011的预留字段8

	E011_CRC8 = 0x00;           //E011的CRC8校验码

	E011_FrameEnd1 = 0x0D;      //E011的帧尾1
	E011_FrameEnd2 = 0x0A;      //E011的帧尾2
	E011_FrameEnd3 = 0x0D;      //E011的帧尾3
	E011_FrameEnd4 = 0x0A;      //E011的帧尾4
	E011_FrameEnd5 = 0x0D;      //E011的帧尾5
	E011_FrameEnd6 = 0x0A;      //E011的帧尾6
}

//函 数 名：Send_E012() 
//功能描述：LORA设备请求设置工作组编号
//函数说明：E012帧的函数
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
unsigned char Send_E012(int Receive_IsBroadcast)
{
	return 0;
}

//函 数 名：E012_init() 
//功能描述：
//函数说明：E012初始化函数
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
unsigned char E012_init()
{
	return 0;
}

//函 数 名：Send_E013() 
//功能描述：LORA设备请求设置SN、区域、设备类型及子设备路数
//函数说明：E013帧的函数
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
unsigned char Send_E013(int Receive_IsBroadcast)
{
	return 0;
}

//函 数 名：E013_init() 
//功能描述：
//函数说明：E013初始化函数
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
unsigned char E013_init()
{
	return 0;
}

//函 数 名：Send_E014() 
//功能描述：LORA设备上报实时工作状态
//函数说明：E014帧的函数
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
unsigned char Send_E014(int Receive_IsBroadcast)
{
	E014_init();

	E014_IsBroadcast = Receive_IsBroadcast;//E014的是否广播指令

	E014[0] = E014_FrameHead;
	E014[1] = E014_FrameId1;
	E014[2] = E014_FrameId2;
	E014[3] = E014_DataLen;
	E014[4] = E014_DeviceTypeID1;
	E014[5] = E014_DeviceTypeID2;
	E014[6] = E014_IsBroadcast;
	E014[7] = E014_ZoneId;
	E014[8] = E014_channel;
	E014[9] = E014_Status;
	E014[10] = E014_Vol1;
	E014[11] = E014_Vol2;
	E014[12] = E014_Rssi;
	E014[13] = E014_Csq;
	E014[14] = E014_Allocate1;
	E014[15] = E014_Allocate2;
	E014[16] = E014_Allocate3;
	E014[17] = E014_Allocate4;
	E014[18] = E014_Allocate5;
	E014[19] = E014_Allocate6;
	E014[20] = E014_Allocate7;
	E014[21] = E014_Allocate8;
	E014[22] = E014_Allocate9;
	E014[23] = E014_Allocate10;
	E014[24] = E014_Allocate11;
	E014[25] = E014_Allocate12;
	E014[26] = E014_Allocate13;
	E014[27] = E014_Allocate14;
	E014[28] = E014_Allocate15;
	E014[29] = E014_Allocate16;
	for (size_t i = 4; i <= E014_DataLen + 0x03; i++)
	{
		Check_Data[Check_Length] = E014[i];
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
		E014_CRC8 = GetCrc8(Check_Data, Check_Length);//得到CRC数据
		if (debug_print == 1)
		{
			Serial.print("CRC8计算的值E014_CRC8 = 0x");
			Serial.println(E014_CRC8, HEX);
		}
		Check_Length = 0;
	}
	E014[30] = E014_CRC8;
	E014[31] = E014_FrameEnd1;
	E014[32] = E014_FrameEnd2;
	E014[33] = E014_FrameEnd3;
	E014[34] = E014_FrameEnd4;
	E014[35] = E014_FrameEnd5;
	E014[36] = E014_FrameEnd6;

	//该区域为串口查看E014回执的信息
	if (debug_print == 1)
	{
		for (int i = 0; i < 37; i++)
		{
			Serial.print(i);
			Serial.print("/");
			Serial.println(E014[i], HEX);
			delay(1);
		}
	}

	Serial3.write(E014, 37);
	Serial3.flush();
	Send_Data_Lamp();//发送数据灯
	return 0;
}

//函 数 名：E014_init() 
//功能描述：
//函数说明：E014初始化函数
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
unsigned char E014_init()
{
	E014_FrameHead = 0xFE;                  //E014的帧头

	E014_FrameId1 = 0xE0;                   //E014的帧ID1
	E014_FrameId2 = 0x14;                   //E014的帧ID2

	E014_DataLen = 0x1A;                    //E014的数据长度

	E014_DeviceTypeID1 = 0xC0;				//E014的设备类型1
	E014_DeviceTypeID2 = 0x02;				//E014的设备类型2

	E014_IsBroadcast = Receive_IsBroadcast;//E014的是否广播指令

	E014_ZoneId = AT24CXX_ReadOneByte(A_ZoneID);         //E014的区域

	E014_Status = 0x01;		//E014的设备当前状态	

	E014_Vol1 = 0xFF;	//E014的电压
	E014_Vol2 = 0xFF;	//E014的电压
	Signal_query();		//信号查询
	//E014_Rssi = ;		//E014的信噪比
	//E014_Csq = ;		//E014的信号强度

	E014_Allocate1 = 0x00;		//E014的预留字段1
	E014_Allocate2 = 0x00;		//E014的预留字段2
	E014_Allocate3 = 0x00;		//E014的预留字段3
	E014_Allocate4 = 0x00;		//E014的预留字段4
	E014_Allocate5 = 0x00;		//E014的预留字段5
	E014_Allocate6 = 0x00;		//E014的预留字段6
	E014_Allocate7 = 0x00;		//E014的预留字段7
	E014_Allocate8 = 0x00;		//E014的预留字段8
	E014_Allocate9 = 0x00;		//E014的预留字段9
	E014_Allocate10 = 0x00;		//E014的预留字段10
	E014_Allocate11 = 0x00;		//E014的预留字段11
	E014_Allocate12 = 0x00;		//E014的预留字段12
	E014_Allocate13 = 0x00;		//E014的预留字段13
	E014_Allocate14 = 0x00;		//E014的预留字段14
	E014_Allocate15 = 0x00;		//E014的预留字段15
	E014_Allocate16 = 0x00;		//E014的预留字段16

	E014_CRC8 = 0x00;           //E014的CRC8校验码

	E014_FrameEnd1 = 0x0D;      //E014的帧尾1
	E014_FrameEnd2 = 0x0A;      //E014的帧尾2
	E014_FrameEnd3 = 0x0D;      //E014的帧尾3
	E014_FrameEnd4 = 0x0A;      //E014的帧尾4
	E014_FrameEnd5 = 0x0D;      //E014的帧尾5
	E014_FrameEnd6 = 0x0A;      //E014的帧尾6
	return 0;
}

//函 数 名：Send_E015() 
//功能描述：LORA设备通用回执帧
//函数说明：A015帧的函数
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
unsigned char Send_E015(int Receive_IsBroadcast, int E015_status)
{
	E015_init();//将E015的值重置为初始值

	E015_IsBroadcast = Receive_IsBroadcast;//E015的是否广播指令
	E015_Status = E015_status;

	E015[0] = E015_FrameHead;
	E015[1] = E015_FrameId1;
	E015[2] = E015_FrameId2;
	E015[3] = E015_DataLen;
	E015[4] = E015_DeviceTypeID1;
	E015[5] = E015_DeviceTypeID2;
	E015[6] = E015_IsBroadcast;
	E015[7] = E015_ZoneId;
	E015[8] = E015_channel;
	E015[9] = E015_Status;
	E015[10] = E015_Allocate1;
	E015[11] = E015_Allocate2;
	E015[12] = E015_Allocate3;
	E015[13] = E015_Allocate4;
	E015[14] = E015_Allocate5;
	E015[15] = E015_Allocate6;
	E015[16] = E015_Allocate7;
	E015[17] = E015_Allocate8;

	for (size_t i = 4; i <= E015_DataLen + 0x03; i++)
	{
		Check_Data[Check_Length] = E015[i];
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
		E015_CRC8 = GetCrc8(Check_Data, Check_Length);//得到CRC数据
		if (debug_print == 1)
		{
			Serial.print("CRC8计算的值E015_CRC8 = 0x");
			Serial.println(E015_CRC8, HEX);
		}
		Check_Length = 0;
	}

	E015[18] = E015_CRC8;
	E015[19] = E015_FrameEnd1;
	E015[20] = E015_FrameEnd2;
	E015[21] = E015_FrameEnd3;
	E015[22] = E015_FrameEnd4;
	E015[23] = E015_FrameEnd5;
	E015[24] = E015_FrameEnd6;

	//该区域为串口查看E015回执的信息
	if (debug_print == 1)
	{
		for (int i = 0; i < 25; i++)
		{
			Serial.print(i);
			Serial.print("/");
			Serial.println(E015[i], HEX);
			delay(1);
		}
	}

	Serial3.write(E015, 25);
	Serial3.flush();
	Send_Data_Lamp();//发送数据灯

	return 0;
}

//函 数 名：E015_init() 
//功能描述：
//函数说明：E015初始化函数
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
unsigned char E015_init()
{
	E015_FrameHead = 0xFE;

	E015_FrameId1 = 0xE0;
	E015_FrameId2 = 0x15;

	E015_DataLen = 0x0E;

	E015_DeviceTypeID1 = 0xC0;
	E015_DeviceTypeID2 = 0x02;

	E015_IsBroadcast = 0x00;

	E015_ZoneId = AT24CXX_ReadOneByte(A_ZoneID);

	E015_channel = 0x01;

	E015_Status = 0x00;

	E015_Allocate1 = 0x00;
	E015_Allocate2 = 0x00;
	E015_Allocate3 = 0x00;
	E015_Allocate4 = 0x00;
	E015_Allocate5 = 0x00;
	E015_Allocate6 = 0x00;
	E015_Allocate7 = 0x00;
	E015_Allocate8 = 0x00;

	E015_CRC8 = 0x00;

	E015_FrameEnd1 = 0x0D;
	E015_FrameEnd2 = 0x0A;
	E015_FrameEnd3 = 0x0D;
	E015_FrameEnd4 = 0x0A;
	E015_FrameEnd5 = 0x0D;
	E015_FrameEnd6 = 0x0A;
	return 0;
}


//函 数 名：SN_ZoneISOK() 
//功能描述：判断SN以及ZoneID是否写入成功的函数
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
unsigned char SN_ZoneISOK(unsigned char* Judgement_Data, int Judgement_Length)
{
	int A013_Checknum = 0;
	if (AT24CXX_ReadOneByte(A_SN_1) == Judgement_Data[10])//7,8-16
	{
		A013_Checknum++;
		if (debug_print == 1)
		{
			Serial.println(String("A013_Checknum = ") + String(A013_Checknum));
		}
	}
	if (AT24CXX_ReadOneByte(A_SN_2) == Judgement_Data[11])
	{
		A013_Checknum++;
		if (debug_print == 1)
		{
			Serial.println(String("A013_Checknum = ") + String(A013_Checknum));
		}
	}
	if (AT24CXX_ReadOneByte(A_SN_3) == Judgement_Data[12])
	{
		A013_Checknum++;
		if (debug_print == 1)
		{
			Serial.println(String("A013_Checknum = ") + String(A013_Checknum));
		}
	}
	if (AT24CXX_ReadOneByte(A_SN_4) == Judgement_Data[13])
	{
		A013_Checknum++;
		if (debug_print == 1)
		{
			Serial.println(String("A013_Checknum = ") + String(A013_Checknum));
		}
	}
	if (AT24CXX_ReadOneByte(A_SN_5) == Judgement_Data[14])
	{
		A013_Checknum++;
		if (debug_print == 1)
		{
			Serial.println(String("A013_Checknum = ") + String(A013_Checknum));
		}
	}
	if (AT24CXX_ReadOneByte(A_SN_6) == Judgement_Data[15])
	{
		A013_Checknum++;
		if (debug_print == 1)
		{
			Serial.println(String("A013_Checknum = ") + String(A013_Checknum));
		}
	}
	if (AT24CXX_ReadOneByte(A_SN_7) == Judgement_Data[16])
	{
		A013_Checknum++;
		if (debug_print == 1)
		{
			Serial.println(String("A013_Checknum = ") + String(A013_Checknum));
		}
	}
	if (AT24CXX_ReadOneByte(A_SN_8) == Judgement_Data[17])
	{
		A013_Checknum++;
		if (debug_print == 1)
		{
			Serial.println(String("A013_Checknum = ") + String(A013_Checknum));
		}
	}
	if (AT24CXX_ReadOneByte(A_SN_9) == Judgement_Data[18])
	{
		A013_Checknum++;
		if (debug_print == 1)
		{
			Serial.println(String("A013_Checknum = ") + String(A013_Checknum));
		}
	}
	if (AT24CXX_ReadOneByte(A_ZoneID) == Judgement_Data[7])
	{
		A013_Checknum++;
		if (debug_print == 1)
		{
			Serial.println(String("A013_Checknum = ") + String(A013_Checknum));
		}
	}
	if (A013_Checknum == 10)
	{
		if (debug_print == 1)
		{
			Serial.println("SN_ZoneISOK");
			Serial.println("SN与区域信息校验成功");
		}
		return 1;
	}
	else
	{
		if (debug_print == 1)
		{
			Serial.println("SN_ZoneISERROR");
			Serial.println("SN与区域信息校验错误");
		}
		return 0;
	}
	//判断是否写入成功
	/*static union DEVICE_SN
	{
		String str_SN;
		byte SN[9];
	};
	DEVICE_SN Device_SN1, Device_SN2;;*/
	//for (size_t i = 0; i < 9; i++)
	//{
	//	Device_SN1.SN[i] = AT24CXX_ReadOneByte(i + 3);
	//	if (debug_print == 1)
	//	{
	//		Serial.print(String("Device_SN1.SN[ ") + String(i) + String(" ]="));
	//		Serial.println(Device_SN1.SN[i], HEX);
	//	}
	//}
	//Serial.println(String("Device_SN1.str_SN = ") + Device_SN1.str_SN);

	//for (size_t i = 0; i < 9; i++)
	//{
	//	Device_SN1.SN[i] = Judgement_Data[i + 8];
	//	if (debug_print == 1)
	//	{
	//		Serial.print(String("Device_SN1.SN[ ") + String(i) + String(" ]="));
	//		Serial.println(Device_SN1.SN[i], HEX);
	//	}
	//}
	//Serial.println(String("Device_SN1.str_SN = ") + Device_SN1.str_SN);
}



//函 数 名：Signal_query() 
//功能描述：信号质量查询函数
//函数说明：查询LORA的信号质量，以及信噪比
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
unsigned char Signal_query()
{
	if (debug_print == 1)
	{
		Serial.println("AT_CMD,HIGH");
	}
	digitalWrite(AT_CMD, HIGH);      //外部输入高电平到AT引脚，模块即可进入AT配置模式
	delay(500);//此处延时不能删
	Serial3.print("AT+CSQ?\r\n");   //查询信号质量
	delay(500);//此处延时不能删
	while (Serial3.available() > 0)
	{
		LORA_Re_Data[LORA_Re_Length++] = Serial3.read();
		delay(1);
	}
	if (LORA_Re_Length > 0)
	{
		if (debug_print == 1)
		{
			Serial.write(LORA_Re_Data, LORA_Re_Length);
			delay(100);
			for (int i = 0; i < LORA_Re_Length; ++i)
			{
				Serial.print(i);
				Serial.print(":");
				Serial.println(LORA_Re_Data[i]);
				delay(1);
			}
		}
		LORA_Re_Length = 0;
	}

	//这里得到信号强度以及信噪比的10进制
	if (LORA_Re_Data[6] == 58 && LORA_Re_Data[8] == 44)//第6位是冒号以及第8位是逗号说明信号强度为1位
	{
		E014_Csq = LORA_Re_Data[7] - 48;         //E014的信号强度

		//这里得到信噪比的10进制
		if (LORA_Re_Data[11] == 13)//结合前面的条件以及第11位是\r说明信噪比为1位
		{
			E014_Rssi = LORA_Re_Data[10] - 48;
		}
		else if (LORA_Re_Data[12] == 13)//结合前面的条件以及第12位是\r说明信噪比为2位
		{
			E014_Rssi = ((LORA_Re_Data[10] - 48) * 10) + (LORA_Re_Data[11] - 48);
		}
		else if (LORA_Re_Data[13] == 13)//结合前面的条件以及第13位是\r说明信噪比为3位
		{
			E014_Rssi = ((LORA_Re_Data[10] - 48) * 100) + (LORA_Re_Data[11] - 48) * 10 + (LORA_Re_Data[12] - 48);
		}
	}
	else if (LORA_Re_Data[6] == 58 && LORA_Re_Data[9] == 44)//第6位是冒号以及第9位是逗号说明信号强度为2位
	{
		E014_Csq = (LORA_Re_Data[7] - 48) * 10 + (LORA_Re_Data[8] - 48);         //E014的信号强度

		//这里得到信噪比的10进制
		if (LORA_Re_Data[12] == 13)//结合前面的条件以及第12位是\r说明信噪比为1位
		{
			E014_Rssi = LORA_Re_Data[11] - 48;
		}
		else if (LORA_Re_Data[13] == 13)//结合前面的条件以及第13位是\r说明信噪比为2位
		{
			E014_Rssi = ((LORA_Re_Data[11] - 48) * 10) + (LORA_Re_Data[12] - 48);
		}
		else if (LORA_Re_Data[14] == 13)//结合前面的条件以及第14位是\r说明信噪比为3位
		{
			E014_Rssi = ((LORA_Re_Data[11] - 48) * 100) + (LORA_Re_Data[12] - 48) * 10 + (LORA_Re_Data[13] - 48);
		}
	}
	else if (LORA_Re_Data[6] == 58 && LORA_Re_Data[10] == 44)//第6位是冒号以及第10位是逗号说明信号强度为3位
	{
		E014_Csq = (LORA_Re_Data[7] - 48) * 100 + (LORA_Re_Data[8] - 48) * 10 + (LORA_Re_Data[9] - 48);

		//这里得到信噪比的10进制
		if (LORA_Re_Data[13] == 13)//结合前面的条件以及第12位是\r说明信噪比为1位
		{
			E014_Rssi = LORA_Re_Data[12] - 48;
		}
		else if (LORA_Re_Data[14] == 13)//结合前面的条件以及第13位是\r说明信噪比为2位
		{
			E014_Rssi = ((LORA_Re_Data[12] - 48) * 10) + (LORA_Re_Data[13] - 48);
		}
		else if (LORA_Re_Data[15] == 13)//结合前面的条件以及第14位是\r说明信噪比为3位
		{
			E014_Rssi = ((LORA_Re_Data[12] - 48) * 100) + (LORA_Re_Data[13] - 48) * 10 + (LORA_Re_Data[14] - 48);
		}
	}
	if (debug_print == 1)
	{
		Serial.print("E014_Csq = ");
		Serial.println(E014_Csq);
		Serial.print("E014_Rssi = ");
		Serial.println(E014_Rssi);
	}
	
	//delay(500);
	digitalWrite(AT_CMD, LOW);       //外部输入低电平即可进入透传模式
	//Serial.println("AT_CMD,LOW");
	delay(500);
	return 0;
}
