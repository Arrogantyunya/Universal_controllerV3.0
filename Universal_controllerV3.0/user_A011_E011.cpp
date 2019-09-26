//user_A011_E011.cpp
/*
*版权
*
* 文件名称:user_A011_E011.cpp
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

#include "user_A011_E011.h"
#include "user_initialization.h"


//函 数 名：Receive_A011() 
//功能描述：A011的执行函数
//函数说明：查询LORA主设备的区域以及SN
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

//函 数 名：Receive_A013() 
//功能描述：A013的执行函数
//函数说明：设置LORA主设备的区域以及SN以及子设备总路数
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


//函 数 名：Send_E011() 
//功能描述：
//函数说明：A011帧的函数
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

//函 数 名：Send_E015() 
//功能描述：
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
		return 1;
	}
	else
	{
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
