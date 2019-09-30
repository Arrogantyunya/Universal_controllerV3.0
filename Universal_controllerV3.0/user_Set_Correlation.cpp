//user_Set_Correlation.cpp
/*
*版权
*
* 文件名称:user_Set_Correlation.cpp
* 文件标识:配置管理计划书
* 摘要:
*
* 当前版本:V1.0
* 作者:刘家辉
* 完成日期:2019-9-24
* 修改者:刘家辉
* 修改日期:
* 修改:
*
* 取代版本:
* 原作者:刘家辉
* 完成日期:
*/

#include "user_Set_Correlation.h"


//函 数 名：Receive_A018() 
//功能描述：A018的执行函数
//函数说明：设置LORA主设备的RTC时间
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
//void Receive_A018(unsigned char* Judgement_Data, int Judgement_Length)
//{
//
//}

//函 数 名：Receive_A019() 
//功能描述：A019的执行函数
//函数说明：设置LORA主设备定时执行的时间段
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
//void Receive_A019(unsigned char* Judgement_Data, int Judgement_Length)
//{
//
//}

//函 数 名：Receive_A018() 
//功能描述：A018的执行函数
//函数说明：设置LORA主设备的RTC时间
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
void Receive_A018(unsigned char* Judgement_Data, int Judgement_Length)
{
	//--------------------------------------------------------
	//该区域为测试传输进Receive_A018函数的数据是否正确的测试代码块
	//需要测试时请取消注释
	if (debug_print == 1)
	{
		Serial.println("进入Receive_A018函数");
		for (int i = 0; i < Judgement_Length + 1; i++)
		{
			Serial.print("A018Judgement_Data ");
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

	if (Judgement_Data[7] == AT24CXX_ReadOneByte(12))//判断区域ID是否是12
	{
		RTC_oldtime = millis();//当每次被设置RTC时间时都更新旧时间

		RTC_Year = Judgement_Data[8];
		RTC_Month = Judgement_Data[9];
		RTC_Day = Judgement_Data[10];
		RTC_Hour = Judgement_Data[11];
		RTC_Minute = Judgement_Data[12];
		RTC_Second = Judgement_Data[13];

		if (debug_print == 1)
		{
			Serial.println(String("RTC时间为："));
			Serial.println(String(RTC_Year) + "年" + RTC_Month + "月" + RTC_Day + "日" + RTC_Hour + "时" + RTC_Minute + "分" + RTC_Second + "秒");
			if (debug == 1)
			{
				delay(1500);
			}
		}

		if (RTC_Year == Judgement_Data[8] && RTC_Month == Judgement_Data[9] && RTC_Day == Judgement_Data[10] &&
			RTC_Hour == Judgement_Data[11] && RTC_Minute == Judgement_Data[12] && RTC_Second == Judgement_Data[13])
		{
			E015_status = SetParamsOk;
			if (debug_print == 1)
			{
				Serial.println(String("E015_status = Set_RTC_clock_success") + String(E015_status));
			}

			RTC_Flag = 0x01;//设置RTC时钟成功后，将RTC的标志位置1
		}
		else
		{
			E015_status = SetParamsErr;
			if (debug_print == 1)
			{
				Serial.println(String("E015_status = Set_RTC_clock_failed") + String(E015_status));
			}

			RTC_Flag = 0x00;//设置RTC时钟失败后，将RTC的标志位置0
		}

		//进行状态的回执
		Send_E015(Receive_IsBroadcast, E015_status);

		Send_E023(Receive_IsBroadcast);//心跳回执
	}
	else
	{
		E015_status = Incorrect_information_error;
		if (debug_print == 1)
		{
			Serial.println("区域信息不正确");
			Serial.println(String("E015_status = Incorrect_information_error") + String(E015_status));
		}
		//进行状态的回执
		Send_E015(Receive_IsBroadcast, E015_status);
	}

	if (debug_print == 1)
	{
		Serial.println("完成A018状态回执");
		Serial.println("结束Receive_A018函数");
	}
}

//函 数 名：Receive_A019() 
//功能描述：A019的执行函数
//函数说明：设置LORA主设备定时执行的时间段
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
void Receive_A019(unsigned char* Judgement_Data, int Judgement_Length)
{
	//--------------------------------------------------------
	//该区域为测试传输进Receive_A019函数的数据是否正确的测试代码块
	//需要测试时请取消注释
	if (debug_print == 1)
	{
		Serial.println("进入Receive_A019函数");
		for (int i = 0; i < Judgement_Length + 1; i++)
		{
			Serial.print("A019Judgement_Data ");
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

	if (Judgement_Data[7] == AT24CXX_ReadOneByte(12))//判断区域ID是否是12
	{
		Mode_implementation = Judgement_Data[8];//得到执行方式
		if (debug_print == 1)
		{
			if (Mode_implementation == 0x01)
			{
				Serial.println("每天执行");
			}
			else if (Mode_implementation == 0x00)
			{
				Serial.println("不执行");
			}
		}

		//数字输出
		if (Judgement_Data[9] == 0xC0 && Judgement_Data[10] == 0x03)
		{
			//DO1
			if (Judgement_Data[11] == 0x01)
			{
				//判断设定参数
				if (Judgement_Data[13] == 0x01)
				{
					DO1_AutoFlag = 0x01;
					if (DO1_AutoFlag == 0x01)
					{
						if (debug_print == 1)
						{
							Serial.println("D01的自动开启");
						}
					}
					//判断时间段序号
					if (Judgement_Data[12] == 0x01)
					{
						if (debug_print == 0x01)
						{
							Serial.println("DO1的时间段1:");
						}
						for (size_t i = 0; i < 6; i++)
						{
							DO1_AutoBegin[0][i] = Judgement_Data[i + 14];
							DO1_AutoEnd[0][i] = Judgement_Data[i + 20];
							if (debug == 1)
							{
								Serial.println(String("DO1开始时间：") + i + "/" + DO1_AutoBegin[0][i]);
								Serial.println(String("DO1结束时间：") + i + "/" + DO1_AutoEnd[0][i]);
							}
						}

						if (DO1_AutoBegin[0][0] == Judgement_Data[14] && DO1_AutoEnd[0][0] == Judgement_Data[20])
						{
							E015_status = SetParamsOk;
							if (debug_print == 1)
							{
								Serial.println("设置时间段成功");
								Serial.println(String("E015_status = SetParamsOk") + String(E015_status));
							}
						}
						else
						{
							E015_status = SetParamsErr;
							if (debug_print == 1)
							{
								Serial.println("设置时间段失败");
								Serial.println(String("E015_status = SetParamsErr") + String(E015_status));
							}
						}
					}
					else if (Judgement_Data[12] == 0x02)
					{
						if (debug_print == 0x01)
						{
							Serial.println("DO1的时间段2:");
						}
						for (size_t i = 0; i < 6; i++)
						{
							DO1_AutoBegin[1][i] = Judgement_Data[i + 14];
							DO1_AutoEnd[1][i] = Judgement_Data[i + 20];
							if (debug_print == 1)
							{
								Serial.println(String("DO1开始时间：") + i + "/" + DO1_AutoBegin[1][i]);
								Serial.println(String("DO1结束时间：") + i + "/" + DO1_AutoEnd[1][i]);
							}
						}

						if (DO1_AutoBegin[1][0] == Judgement_Data[14] && DO1_AutoEnd[1][0] == Judgement_Data[20])
						{
							E015_status = SetParamsOk;
							if (debug_print == 1)
							{
								Serial.println("设置时间段成功");
								Serial.println(String("E015_status = SetParamsOk") + String(E015_status));
							}
						}
						else
						{
							E015_status = SetParamsErr;
							if (debug_print == 1)
							{
								Serial.println("设置时间段失败");
								Serial.println(String("E015_status = SetParamsErr") + String(E015_status));
							}
						}
					}
					else
					{

					}
				}
			}
			//DO2
			else if (Judgement_Data[11] == 0x02)
			{

			}
			//DO3
			else if (Judgement_Data[11] == 0x03)
			{
				//判断设定参数
				if (Judgement_Data[13] == 0x01)
				{
					DO3_AutoFlag = 0x01;
					if (DO3_AutoFlag == 0x01)
					{
						if (debug_print == 1)
						{
							Serial.println("DO3的自动开启");
						}
					}
					//判断时间段序号
					if (Judgement_Data[12] == 0x01)
					{
						if (debug_print == 0x01)
						{
							Serial.println("DO3的时间段1:");
						}
						for (size_t i = 0; i < 6; i++)
						{
							DO3_AutoBegin[0][i] = Judgement_Data[i + 14];
							DO3_AutoEnd[0][i] = Judgement_Data[i + 20];
							if (debug == 1)
							{
								Serial.println(String("DO3开始时间：") + i + "/" + DO3_AutoBegin[0][i]);
								Serial.println(String("DO3结束时间：") + i + "/" + DO3_AutoEnd[0][i]);
							}
						}

						if (DO3_AutoBegin[0][0] == Judgement_Data[14] && DO3_AutoEnd[0][0] == Judgement_Data[20])
						{
							E015_status = SetParamsOk;
							if (debug_print == 1)
							{
								Serial.println("设置时间段成功");
								Serial.println(String("E015_status = SetParamsOk") + String(E015_status));
							}
						}
						else
						{
							E015_status = SetParamsErr;
							if (debug_print == 1)
							{
								Serial.println("设置时间段失败");
								Serial.println(String("E015_status = SetParamsErr") + String(E015_status));
							}
						}
					}
					else if (Judgement_Data[12] == 0x02)
					{
						if (debug_print == 0x01)
						{
							Serial.println("DO3的时间段2:");
						}
						for (size_t i = 0; i < 6; i++)
						{
							DO3_AutoBegin[1][i] = Judgement_Data[i + 14];
							DO3_AutoEnd[1][i] = Judgement_Data[i + 20];
							if (debug_print == 1)
							{
								Serial.println(String("DO3开始时间：") + i + "/" + DO3_AutoBegin[1][i]);
								Serial.println(String("DO3结束时间：") + i + "/" + DO3_AutoEnd[1][i]);
							}
						}

						if (DO3_AutoBegin[1][0] == Judgement_Data[14] && DO3_AutoEnd[1][0] == Judgement_Data[20])
						{
							E015_status = SetParamsOk;
							if (debug_print == 1)
							{
								Serial.println("设置时间段成功");
								Serial.println(String("E015_status = SetParamsOk") + String(E015_status));
							}
						}
						else
						{
							E015_status = SetParamsErr;
							if (debug_print == 1)
							{
								Serial.println("设置时间段失败");
								Serial.println(String("E015_status = SetParamsErr") + String(E015_status));
							}
						}
					}
					else
					{

					}
				}
			}
			//DO4
			else if (Judgement_Data[11] == 0x04)
			{

			}
			else
			{

			}
		}
		//模拟输出
		else if (Judgement_Data[9] == 0xC0 && Judgement_Data[10] == 0x04)
		{
			//AO1
			if (Judgement_Data[11] == 0x01)
			{

			}
			//AO2
			else if (Judgement_Data[11] == 0x02)
			{

			}
			else
			{

			}
		}

		//进行状态的回执
		Send_E015(Receive_IsBroadcast, E015_status);
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
		Send_E015(Receive_IsBroadcast, E015_status);
	}

	if (debug_print == 1)
	{
		Serial.println("完成A019状态回执");
		Serial.println("结束Receive_A019函数");
	}
}

//函 数 名：Receive_A020() 
//功能描述：A020的执行函数
//函数说明：设置某类型接口挂载的某一路子设备类型及工作组
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
void Receive_A020(unsigned char* Judgement_Data, int Judgement_Length)
{
	//--------------------------------------------------------
	//该区域为测试传输进Receive_A020函数的数据是否正确的测试代码块
	//需要测试时请取消注释
	if (debug_print == 1)
	{
		Serial.println("进入Receive_A020函数");
		for (int i = 0; i < Judgement_Length + 1; i++)
		{
			Serial.print("A020Judgement_Data ");
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

	if (Judgement_Data[7] == AT24CXX_ReadOneByte(A_ZoneID))//判断区域ID是否是12
	{
		if (Judgement_Data[8] == 0xC0 && Judgement_Data[9] == 0x03)
		{
			//判断设备路数
			if (Judgement_Data[10] == 0x01)
			{
				//这里是数字输出【C003】的第1路设备,子设备类型ID14-15，工作组数组ID16-20
				for (size_t i = 11; i <= 17; i++)//将子设备类型以及工作组数组写入EEPROM
				{
					AT24CXX_WriteOneByte(i + 3, Judgement_Data[i]);
					if (debug_print == 1)
					{
						Serial.print(String("AT24CXX_ReadOneByte[ ") + String(i + 3) + String(" ]="));
						Serial.println(AT24CXX_ReadOneByte(i + 3), HEX);
					}
				}

				E015_status = SetParamsOk;//设置参数成功
			}
			else if (Judgement_Data[10] == 0x02)
			{
				//这里是数字输出【C003】的第2路设备，子设备类型ID21-22，工作组数组ID23-27
				for (size_t i = 11; i <= 17; i++)//将子设备类型以及工作组数组写入EEPROM
				{
					AT24CXX_WriteOneByte(i + 10, Judgement_Data[i]);
					if (debug_print == 1)
					{
						Serial.print(String("AT24CXX_ReadOneByte[ ") + String(i + 10) + String(" ]="));
						Serial.println(AT24CXX_ReadOneByte(i + 10), HEX);
					}
				}

				E015_status = SetParamsOk;//设置参数成功
			}
			else if (Judgement_Data[10] == 0x01)
			{
				//这里是模拟输出【C003】的第3路设备，子设备类型ID28-29，工作组数组ID30-34
				for (size_t i = 11; i <= 17; i++)//将子设备类型以及工作组数组写入EEPROM
				{
					AT24CXX_WriteOneByte(i + 17, Judgement_Data[i]);
					if (debug_print == 1)
					{
						Serial.print(String("AT24CXX_ReadOneByte[ ") + String(i + 17) + String(" ]="));
						Serial.println(AT24CXX_ReadOneByte(i + 17), HEX);
					}
				}

				E015_status = SetParamsOk;//设置参数成功
			}
			else if (Judgement_Data[10] == 0x02)
			{
				//这里是模拟输出【C003】的第4路设备，子设备类型ID35-36，工作组数组ID37-41
				for (size_t i = 11; i <= 17; i++)//将子设备类型以及工作组数组写入EEPROM
				{
					AT24CXX_WriteOneByte(i + 24, Judgement_Data[i]);
					if (debug_print == 1)
					{
						Serial.print(String("AT24CXX_ReadOneByte[ ") + String(i + 24) + String(" ]="));
						Serial.println(AT24CXX_ReadOneByte(i + 24), HEX);
					}
				}

				E015_status = SetParamsOk;//设置参数成功
			}
			else
			{
				E015_status = SetParamsOk;//设置参数成功
				if (debug_print == 1)
				{
					Serial.println("C003所不存在的设备路数");
				}
			}
		}
		else if (Judgement_Data[8] == 0xC0 && Judgement_Data[9] == 0x04)
		{
			if (Judgement_Data[10] == 0x01)
			{
				//这里是模拟输出【C004】的第一路设备，子设备类型ID28-29，工作组数组ID30-34
				for (size_t i = 11; i <= 17; i++)//将子设备类型以及工作组数组写入EEPROM
				{
					AT24CXX_WriteOneByte(i + 17, Judgement_Data[i]);
					if (debug_print == 1)
					{
						Serial.print(String("AT24CXX_ReadOneByte[ ") + String(i + 17) + String(" ]="));
						Serial.println(AT24CXX_ReadOneByte(i + 31), HEX);
					}
				}

				E015_status = SetParamsOk;//设置参数成功
			}
			else if (Judgement_Data[10] == 0x02)
			{
				//这里是模拟输出【C004】的第二路设备，子设备类型ID35-36，工作组数组ID37-41
				for (size_t i = 11; i <= 17; i++)//将子设备类型以及工作组数组写入EEPROM
				{
					AT24CXX_WriteOneByte(i + 24, Judgement_Data[i]);
					if (debug_print == 1)
					{
						Serial.print(String("AT24CXX_ReadOneByte[ ") + String(i + 24) + String(" ]="));
						Serial.println(AT24CXX_ReadOneByte(i + 38), HEX);
					}
				}

				E015_status = SetParamsOk;//设置参数成功
			}
			else
			{
				if (debug_print == 1)
				{
					Serial.println("C004所不存在的设备路数");
				}
				E015_status = SetParamsErr;//设置参数失败
			}
		}
		else
		{
			if (debug_print == 1)
			{
				Serial.println("不存在的控制器设备类型ID");
			}
			E015_status = SetParamsErr;//设置参数失败
		}
		//是否广播指令
		Receive_IsBroadcast = Judgement_Data[6];

		//进行状态的回执
		Send_E015(Receive_IsBroadcast, E015_status);
	}
	else
	{//区域对不上
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
		Serial.println("完成A020状态回执");
		Serial.println("结束Receive_A020函数");
	}
}


//函 数 名：Receive_A022() 
//功能描述：A022的执行函数
//函数说明：A022函数(设置某路（或某组）输出设备状态)
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
void Receive_A022(unsigned char* Judgement_Data, int Judgement_Length)//A022函数
{
	//--------------------------------------------------------
	//该区域为测试传输进Receive_A022函数的数据是否正确的测试代码块
	//需要测试时请取消注释
	if (debug_print == 1)
	{
		Serial.println("进入Receive_A022函数");
		for (int i = 0; i < Judgement_Length + 1; i++)
		{
			Serial.print("A022Judgement_Data ");
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
		//判断为单播
		if (Judgement_Data[6] == 0x00)
		{
			//判断为数字输出【C003】
			if (Judgement_Data[9] == 0xC0 && Judgement_Data[10] == 0x03)
			{
				//判断数据长度是否正确
				if (Judgement_Data[3] == 0x0E)
				{
					//判断路数为1路
					if (Judgement_Data[11] == 0x01)
					{
						//1路开
						if (Judgement_Data[14] == 0x01)
						{
							//digitalWrite(DO1, HIGH);

							//将1路开的状态值写入
							out_state = DO1_ON;
							Out_State[0] = out_state;

							//决定在这里赋时间值，先赋持续时间的值到数组
							Duration_time = Judgement_Data[15] * 0x10000 + Judgement_Data[16] * 0x100 + Judgement_Data[17];
							duration[0] = Duration_time;
							if (debug == 1)
							{
								Serial.print("Duration_time=");
								Serial.println(Duration_time);
								Serial.print("duration[0]=");
								Serial.println(duration[0]);
							}

							//然后赋旧时间的值到数组
							oldtime = millis();
							ot[0] = oldtime;
							if (debug == 1)
							{
								Serial.print("oldtime=");
								Serial.println(oldtime);
								Serial.print("ot[0]=");
								Serial.println(ot[0]);
							}

							if (Out_State[0] == DO1_ON)
							{
								E015_status = SetParamsOk;
							}
							else
							{
								E015_status = SetParamsErr;
							}

							//是否广播指令
							Receive_IsBroadcast = Judgement_Data[6];

							//进行状态的回执
							Send_E015(Receive_IsBroadcast, E015_status);

							forswitch();

						}
						//1路关
						else if (Judgement_Data[14] == 0x00)
						{
							//将1路关的状态值写入
							out_state = Stateless;
							Out_State[0] = out_state;
							digitalWrite(DO1, LOW);

							//将所有的设定时间，已工作时间，剩余时间清零
							duration[0] = 0x00;
							CurrentWorkSec[0] = 0x00;
							remaining[0] = 0x00;
							DO1_SetWorkSec1 = 0x00;
							DO1_SetWorkSec2 = 0x00;
							DO1_SetWorkSec3 = 0x00;
							DO1_CurrentWorkSec1 = 0x00;
							DO1_CurrentWorkSec2 = 0x00;
							DO1_CurrentWorkSec3 = 0x00;
							DO1_RemainWorkSec1 = 0x00;
							DO1_RemainWorkSec2 = 0x00;
							DO1_RemainWorkSec3 = 0x00;

							if (debug == 1)
							{
								Serial.println("数字输出1关");
							}

							if (Out_State[0] == Stateless)
							{
								E015_status = SetParamsOk;
							}
							else
							{
								E015_status = SetParamsErr;
							}

							//是否广播指令
							Receive_IsBroadcast = Judgement_Data[6];

							//进行状态的回执
							Send_E015(Receive_IsBroadcast, E015_status);

							forswitch();
						}
						else
						{
							if (debug == 1)
							{
								Serial.println("不存在的开度");
							}
						}
					}
					//判断路数为2路
					else if (Judgement_Data[11] == 0x02)
					{
						//2路开
						if (Judgement_Data[14] == 0x01)
						{
							//digitalWrite(DO2, HIGH);

							//将2路开的状态值写入
							out_state = DO2_ON;
							Out_State[1] = out_state;

							//决定在这里赋时间值，先赋持续时间的值到数组
							Duration_time = Judgement_Data[15] * 0x10000 + Judgement_Data[16] * 0x100 + Judgement_Data[17];
							duration[1] = Duration_time;
							if (debug == 1)
							{
								Serial.print("Duration_time=");
								Serial.println(Duration_time);
								Serial.print("duration[1]=");
								Serial.println(duration[1]);
							}

							//然后赋旧时间的值到数组
							oldtime = millis();
							ot[1] = oldtime;
							if (debug == 1)
							{
								Serial.print("oldtime=");
								Serial.println(oldtime);
								Serial.print("ot[1]=");
								Serial.println(ot[1]);
							}

							if (Out_State[1] == DO2_ON)
							{
								E015_status = SetParamsOk;
							}
							else
							{
								E015_status = SetParamsErr;
							}

							//是否广播指令
							Receive_IsBroadcast = Judgement_Data[6];

							//进行状态的回执
							Send_E015(Receive_IsBroadcast, E015_status);

							forswitch();
						}
						//2路关
						else if (Judgement_Data[14] == 0x00)
						{
							//将2路关的状态值写入
							out_state = Stateless;
							Out_State[1] = out_state;
							digitalWrite(DO2, LOW);

							//将所有的设定时间，已工作时间，剩余时间清零
							duration[1] = 0x00;
							CurrentWorkSec[1] = 0x00;
							remaining[1] = 0x00;
							DO2_SetWorkSec1 = 0x00;
							DO2_SetWorkSec2 = 0x00;
							DO2_SetWorkSec3 = 0x00;
							DO2_CurrentWorkSec1 = 0x00;
							DO2_CurrentWorkSec2 = 0x00;
							DO2_CurrentWorkSec3 = 0x00;
							DO2_RemainWorkSec1 = 0x00;
							DO2_RemainWorkSec2 = 0x00;
							DO2_RemainWorkSec3 = 0x00;

							if (debug == 1)
							{
								Serial.println("数字输出2关");
							}

							if (Out_State[1] == Stateless)
							{
								E015_status = SetParamsOk;
							}
							else
							{
								E015_status = SetParamsErr;
							}

							//是否广播指令
							Receive_IsBroadcast = Judgement_Data[6];

							//进行状态的回执
							Send_E015(Receive_IsBroadcast, E015_status);

							forswitch();
						}
						else
						{
							if (debug == 1)
							{
								Serial.println("不存在的开度");
							}
						}
					}
					//判断路数为3路
					else if (Judgement_Data[11] == 0x03)
					{
						//3路开
						if (Judgement_Data[14] == 0x01)
						{
							//digitalWrite(KCZJ1, );

							//将3路开的状态值写入
							out_state = DO3_ON;
							Out_State[2] = out_state;

							//决定在这里赋时间值，先赋持续时间的值到数组
							Duration_time = Judgement_Data[15] * 0x10000 + Judgement_Data[16] * 0x100 + Judgement_Data[17];
							duration[2] = Duration_time;
							if (debug_print == 1)
							{
								Serial.print("Duration_time=");
								Serial.println(Duration_time);
								Serial.print("duration[2]=");
								Serial.println(duration[2]);
							}

							//然后赋旧时间的值到数组
							oldtime = millis();
							ot[2] = oldtime;
							if (debug_print == 1)
							{
								Serial.print("oldtime=");
								Serial.println(oldtime);
								Serial.print("ot[2]=");
								Serial.println(ot[2]);
							}

							if (Out_State[2] == DO3_ON)
							{
								E015_status = SetParamsOk;
							}
							else
							{
								E015_status = SetParamsErr;
							}

							//是否广播指令
							Receive_IsBroadcast = Judgement_Data[6];

							//进行状态的回执
							Send_E015(Receive_IsBroadcast, E015_status);

							forswitch();
						}
						//3路关
						else if (Judgement_Data[14] == 0x00)
						{
							//将3路关的状态值写入
							out_state = Stateless;
							Out_State[2] = out_state;
							digitalWrite(KCZJ1, HIGH);

							//将所有的设定时间，已工作时间，剩余时间清零
							duration[2] = 0x00;
							CurrentWorkSec[2] = 0x00;
							remaining[2] = 0x00;
							DO3_SetWorkSec1 = 0x00;
							DO3_SetWorkSec2 = 0x00;
							DO3_SetWorkSec3 = 0x00;
							DO3_CurrentWorkSec1 = 0x00;
							DO3_CurrentWorkSec2 = 0x00;
							DO3_CurrentWorkSec3 = 0x00;
							DO3_RemainWorkSec1 = 0x00;
							DO3_RemainWorkSec2 = 0x00;
							DO3_RemainWorkSec3 = 0x00;

							if (debug_print == 1)
							{
								Serial.println("数字输出3关");
							}

							if (Out_State[1] == Stateless)
							{
								E015_status = SetParamsOk;
							}
							else
							{
								E015_status = SetParamsErr;
							}

							//是否广播指令
							Receive_IsBroadcast = Judgement_Data[6];

							//进行状态的回执
							Send_E015(Receive_IsBroadcast, E015_status);

							forswitch();
						}
						else
						{
							if (debug_print == 1)
							{
								Serial.println("不存在的开度");
							}
						}
					}
					//判断路数为4路
					else if (Judgement_Data[11] == 0x04)
					{
						//4路开
						if (Judgement_Data[14] == 0x01)
						{
							//digitalWrite(KCZJ2, LOW);

							//将4路开的状态值写入
							out_state = DO4_ON;
							Out_State[3] = out_state;

							//决定在这里赋时间值，先赋持续时间的值到数组
							Duration_time = Judgement_Data[15] * 0x10000 + Judgement_Data[16] * 0x100 + Judgement_Data[17];
							duration[3] = Duration_time;
							if (debug_print == 1)
							{
								Serial.print("Duration_time=");
								Serial.println(Duration_time);
								Serial.print("duration[3]=");
								Serial.println(duration[3]);
							}

							//然后赋旧时间的值到数组
							oldtime = millis();
							ot[3] = oldtime;
							if (debug_print == 1)
							{
								Serial.print("oldtime=");
								Serial.println(oldtime);
								Serial.print("ot[3]=");
								Serial.println(ot[3]);
							}

							if (Out_State[3] == DO4_ON)
							{
								E015_status = SetParamsOk;
							}
							else
							{
								E015_status = SetParamsErr;
							}

							//是否广播指令
							Receive_IsBroadcast = Judgement_Data[6];

							//进行状态的回执
							Send_E015(Receive_IsBroadcast, E015_status);

							forswitch();
						}
						//4路关
						else if (Judgement_Data[14] == 0x00)
						{
							//将4路关的状态值写入
							out_state = Stateless;
							Out_State[3] = out_state;
							digitalWrite(KCZJ2, HIGH);

							//将所有的设定时间，已工作时间，剩余时间清零
							duration[3] = 0x00;
							CurrentWorkSec[3] = 0x00;
							remaining[3] = 0x00;
							DO4_SetWorkSec1 = 0x00;
							DO4_SetWorkSec2 = 0x00;
							DO4_SetWorkSec3 = 0x00;
							DO4_CurrentWorkSec1 = 0x00;
							DO4_CurrentWorkSec2 = 0x00;
							DO4_CurrentWorkSec3 = 0x00;
							DO4_RemainWorkSec1 = 0x00;
							DO4_RemainWorkSec2 = 0x00;
							DO4_RemainWorkSec3 = 0x00;

							if (debug_print == 1)
							{
								Serial.println("数字输出4关");
							}

							if (Out_State[3] == Stateless)
							{
								E015_status = SetParamsOk;
							}
							else
							{
								E015_status = SetParamsErr;
							}

							//是否广播指令
							Receive_IsBroadcast = Judgement_Data[6];

							//进行状态的回执
							Send_E015(Receive_IsBroadcast, E015_status);

							forswitch();
						}
						else
						{
							if (debug_print == 1)
							{
								Serial.println("不存在的开度");
							}
						}
					}
					//判断路数为全部路
					else if (Judgement_Data[11] == 0x55)
					{
						//全部路开
						if (Judgement_Data[14] == 0x01)
						{

							//将全部路开的状态值写入
							out_state = DO1_ON;
							Out_State[0] = out_state;
							out_state = DO2_ON;
							Out_State[1] = out_state;
							out_state = DO3_ON;
							Out_State[2] = out_state;
							out_state = DO4_ON;
							Out_State[3] = out_state;

							//决定在这里赋时间值，先赋持续时间的值到数组
							Duration_time = Judgement_Data[15] * 0x10000 + Judgement_Data[16] * 0x100 + Judgement_Data[17];
							duration[0] = Duration_time;
							duration[1] = Duration_time;
							duration[2] = Duration_time;
							duration[3] = Duration_time;
							if (debug_print == 1)
							{
								Serial.print("Duration_time=");
								Serial.println(Duration_time);
								Serial.print("duration[0,1,2,3]=");
								Serial.println(duration[0]);
							}

							//然后赋旧时间的值到数组
							oldtime = millis();
							ot[0] = oldtime;
							ot[1] = oldtime;
							ot[2] = oldtime;
							ot[3] = oldtime;
							if (debug_print == 1)
							{
								Serial.print("oldtime=");
								Serial.println(oldtime);
								Serial.print("ot[0,1,2,3]=");
								Serial.println(ot[0]);
							}

							if (Out_State[0] == DO1_ON && Out_State[1] == DO2_ON &&
								Out_State[2] == DO3_ON && Out_State[3] == DO4_ON)
							{
								E015_status = SetParamsOk;
							}
							else
							{
								E015_status = SetParamsErr;
							}

							//是否广播指令
							Receive_IsBroadcast = Judgement_Data[6];

							//进行状态的回执
							Send_E015(Receive_IsBroadcast, E015_status);

							forswitch();
						}
						//全部路关
						else if (Judgement_Data[14] == 0x00)
						{
							//将4路关的状态值写入
							out_state = Stateless;
							Out_State[0] = out_state;
							Out_State[1] = out_state;
							Out_State[2] = out_state;
							Out_State[3] = out_state;
							digitalWrite(DO1, LOW);
							digitalWrite(DO2, LOW);
							digitalWrite(KCZJ1, HIGH);
							digitalWrite(KCZJ2, HIGH);

							//将所有的设定时间，已工作时间，剩余时间清零
							for (size_t i = 0; i < 4; i++)
							{
								duration[i] = 0x00;
								CurrentWorkSec[i] = 0x00;
								remaining[i] = 0x00;

							}
							DO1_SetWorkSec1 = 0x00;
							DO1_SetWorkSec2 = 0x00;
							DO1_SetWorkSec3 = 0x00;
							DO1_CurrentWorkSec1 = 0x00;
							DO1_CurrentWorkSec2 = 0x00;
							DO1_CurrentWorkSec3 = 0x00;
							DO1_RemainWorkSec1 = 0x00;
							DO1_RemainWorkSec2 = 0x00;
							DO1_RemainWorkSec3 = 0x00;

							DO2_SetWorkSec1 = 0x00;
							DO2_SetWorkSec2 = 0x00;
							DO2_SetWorkSec3 = 0x00;
							DO2_CurrentWorkSec1 = 0x00;
							DO2_CurrentWorkSec2 = 0x00;
							DO2_CurrentWorkSec3 = 0x00;
							DO2_RemainWorkSec1 = 0x00;
							DO2_RemainWorkSec2 = 0x00;
							DO2_RemainWorkSec3 = 0x00;

							DO3_SetWorkSec1 = 0x00;
							DO3_SetWorkSec2 = 0x00;
							DO3_SetWorkSec3 = 0x00;
							DO3_CurrentWorkSec1 = 0x00;
							DO3_CurrentWorkSec2 = 0x00;
							DO3_CurrentWorkSec3 = 0x00;
							DO3_RemainWorkSec1 = 0x00;
							DO3_RemainWorkSec2 = 0x00;
							DO3_RemainWorkSec3 = 0x00;

							DO4_SetWorkSec1 = 0x00;
							DO4_SetWorkSec2 = 0x00;
							DO4_SetWorkSec3 = 0x00;
							DO4_CurrentWorkSec1 = 0x00;
							DO4_CurrentWorkSec2 = 0x00;
							DO4_CurrentWorkSec3 = 0x00;
							DO4_RemainWorkSec1 = 0x00;
							DO4_RemainWorkSec2 = 0x00;
							DO4_RemainWorkSec3 = 0x00;

							if (debug_print == 1)
							{
								Serial.println("数字输出全关");
							}

							if (Out_State[0] == Stateless && Out_State[1] == Stateless &&
								Out_State[2] == Stateless && Out_State[3] == Stateless)
							{
								E015_status = SetParamsOk;
							}
							else
							{
								E015_status = SetParamsErr;
							}

							//是否广播指令
							Receive_IsBroadcast = Judgement_Data[6];

							//进行状态的回执
							Send_E015(Receive_IsBroadcast, E015_status);

							forswitch();
						}
						else
						{
							if (debug_print == 1)
							{
								Serial.println("不存在的开度");
							}
						}
					}
					//不存在的设备路数
					else
					{
						Serial.println("不存在的设备路数");
					}
				}
				else
				{
					//数据长度不正确
					Serial.println("数据长度不正确");
				}
			}
			//判断为模拟输出【C004】
			else if (Judgement_Data[9] == 0xC0 && Judgement_Data[10] == 0x04)
			{
				//判断数据长度是否正确
				if (Judgement_Data[3] == 0x10)
				{
					//判断路数为模拟输出1路
					if (Judgement_Data[11] == 0x01)
					{
						//模拟输出1路开
						if (Judgement_Data[14] != 0x00 && Judgement_Data[15] != 0x00 && Judgement_Data[16] != 0x00)
						{
							//analogWrite
							//将1路开的状态值写入
							out_state = AO1_ON;
							Out_State[4] = out_state;

							//在这里得到需要设定的电压值
							if (Judgement_Data[16] == 0xE2)
							{
								Set_AOVoltage1 = (Judgement_Data[14] + Judgement_Data[15] * 0.01);
								if (debug_print == 1)
								{
									Serial.println("Set_AOVoltage1 = " + String(Set_AOVoltage1) + "V");
								}
							}
							//float ar1 = ((analogRead1 * 0.8056) * 11;//4537.65
							//float ar1 = ((analogRead1 * 0.8056) * 0.011;//4537.65
							float AV1 = (Set_AOVoltage1 / 0.011) / 0.8056;
							if (AV1 - floor(AV1) >= 0.5)
							{
								Analog_Value1 = floor(AV1) + 1;
							}
							else if (AV1 - floor(AV1) < 0.5)
							{
								Analog_Value1 = floor(AV1);
							}
							else
							{
								if (debug_print == 1)
								{
									Serial.println("意外BUG区");
								}
							}
							if (debug_print == 1)
							{
								Serial.println("AV1 = " + String(AV1));
								Serial.println("Analog_Value1 = " + String(Analog_Value1));
							}

							//决定在这里赋时间值，先赋持续时间的值到数组
							Duration_time = Judgement_Data[17] * 0x10000 + Judgement_Data[18] * 0x100 + Judgement_Data[19];
							duration[4] = Duration_time;
							if (debug_print == 1)
							{
								Serial.print("Duration_time=");
								Serial.println(Duration_time);
								Serial.print("duration[4]=");
								Serial.println(duration[4]);
							}

							//然后赋旧时间的值到数组
							oldtime = millis();
							ot[4] = oldtime;
							if (debug_print == 1)
							{
								Serial.print("oldtime=");
								Serial.println(oldtime);
								Serial.print("ot[4]=");
								Serial.println(ot[4]);
							}

							if (Out_State[4] == AO1_ON)
							{
								E015_status = SetParamsOk;
							}
							else
							{
								E015_status = SetParamsErr;
							}

							//是否广播指令
							Receive_IsBroadcast = Judgement_Data[6];

							//进行状态的回执
							Send_E015(Receive_IsBroadcast, E015_status);

							forswitch();
						}
						//模拟输出1路关
						else if (Judgement_Data[14] == 0x00 && Judgement_Data[15] == 0x00 && Judgement_Data[16] == 0x00)
						{
							//将模拟输出1路关的状态值写入
							out_state = Stateless;
							Out_State[4] = out_state;
							analogWrite(AO1, 0);

							//将所有的设定时间，已工作时间，剩余时间清零
							duration[4] = 0x00;
							CurrentWorkSec[4] = 0x00;
							remaining[4] = 0x00;
							AO1_SetWorkSec1 = 0x00;
							AO1_SetWorkSec2 = 0x00;
							AO1_SetWorkSec3 = 0x00;
							AO1_CurrentWorkSec1 = 0x00;
							AO1_CurrentWorkSec2 = 0x00;
							AO1_CurrentWorkSec3 = 0x00;
							AO1_RemainWorkSec1 = 0x00;
							AO1_RemainWorkSec2 = 0x00;
							AO1_RemainWorkSec3 = 0x00;

							if (debug_print == 1)
							{
								Serial.println("模拟输出1关");
							}

							if (Out_State[4] == Stateless)
							{
								E015_status = SetParamsOk;
							}
							else
							{
								E015_status = SetParamsErr;
							}

							//是否广播指令
							Receive_IsBroadcast = Judgement_Data[6];

							//进行状态的回执
							Send_E015(Receive_IsBroadcast, E015_status);

							forswitch();
						}
						else
						{
							if (debug_print == 1)
							{
								Serial.println("意外BUG区");
							}
						}
					}
					//判断路数为模拟输出2路
					else if (Judgement_Data[11] == 0x02)
					{
						//模拟输出2路开
						if (Judgement_Data[14] != 0x00 && Judgement_Data[15] != 0x00 && Judgement_Data[16] != 0x00)
						{
							//analogWrite
							//将2路开的状态值写入
							out_state = AO2_ON;
							Out_State[5] = out_state;

							//在这里得到需要设定的电压值
							if (Judgement_Data[16] == 0xE2)
							{
								Set_AOVoltage2 = (Judgement_Data[14] + Judgement_Data[15] * 0.01);
								if (debug_print == 1)
								{
									Serial.println("Set_AOVoltage2 = " + String(Set_AOVoltage2) + "V");
								}
							}
							//float ar1 = ((analogRead1 * 0.8056) * 11;//4537.65
							//float ar1 = ((analogRead1 * 0.8056) * 0.011;//4537.65
							float AV2 = (Set_AOVoltage2 / 0.011) / 0.8056;
							if (AV2 - floor(AV2) >= 0.5)
							{
								Analog_Value2 = floor(AV2) + 1;
							}
							else if (AV2 - floor(AV2) < 0.5)
							{
								Analog_Value2 = floor(AV2);
							}
							else
							{
								if (debug_print == 1)
								{
									Serial.println("意外BUG区");
								}
							}
							if (debug_print == 1)
							{
								Serial.println("AV2 = " + String(AV2));
								Serial.println("Analog_Value2 = " + String(Analog_Value2));
							}

							//决定在这里赋时间值，先赋持续时间的值到数组
							Duration_time = Judgement_Data[17] * 0x10000 + Judgement_Data[18] * 0x100 + Judgement_Data[19];
							duration[5] = Duration_time;
							if (debug_print == 1)
							{
								Serial.print("Duration_time=");
								Serial.println(Duration_time);
								Serial.print("duration[5]=");
								Serial.println(duration[5]);
							}

							//然后赋旧时间的值到数组
							oldtime = millis();
							ot[5] = oldtime;
							if (debug_print == 1)
							{
								Serial.print("oldtime=");
								Serial.println(oldtime);
								Serial.print("ot[5]=");
								Serial.println(ot[5]);
							}

							if (Out_State[5] == AO2_ON)
							{
								E015_status = SetParamsOk;
							}
							else
							{
								E015_status = SetParamsErr;
							}

							//是否广播指令
							Receive_IsBroadcast = Judgement_Data[6];

							//进行状态的回执
							Send_E015(Receive_IsBroadcast, E015_status);

							forswitch();
						}
						//模拟输出2路关
						else if (Judgement_Data[14] == 0x00 && Judgement_Data[15] == 0x00 && Judgement_Data[16] == 0x00)
						{
							//将模拟输出2路关的状态值写入
							out_state = Stateless;
							Out_State[5] = out_state;
							analogWrite(AO2, 0);

							//将所有的设定时间，已工作时间，剩余时间清零
							duration[5] = 0x00;
							CurrentWorkSec[5] = 0x00;
							remaining[5] = 0x00;
							AO2_SetWorkSec1 = 0x00;
							AO2_SetWorkSec2 = 0x00;
							AO2_SetWorkSec3 = 0x00;
							AO2_CurrentWorkSec1 = 0x00;
							AO2_CurrentWorkSec2 = 0x00;
							AO2_CurrentWorkSec3 = 0x00;
							AO2_RemainWorkSec1 = 0x00;
							AO2_RemainWorkSec2 = 0x00;
							AO2_RemainWorkSec3 = 0x00;

							if (debug_print == 1)
							{
								Serial.println("模拟输出2关");
							}

							if (Out_State[5] == Stateless)
							{
								E015_status = SetParamsOk;
							}
							else
							{
								E015_status = SetParamsErr;
							}

							//是否广播指令
							Receive_IsBroadcast = Judgement_Data[6];

							//进行状态的回执
							Send_E015(Receive_IsBroadcast, E015_status);

							forswitch();
						}
						else
						{
							if (debug_print == 1)
							{
								Serial.println("意外BUG区");
							}
						}
					}
					//判断路数为模拟输出全部路
					else if (Judgement_Data[11] == 0x55)
					{
						//模拟输出全部路开
						if (Judgement_Data[14] != 0x00 && Judgement_Data[15] != 0x00 && Judgement_Data[16] != 0x00)
						{
							//analogWrite
							//将全部路开的状态值写入
							out_state = AO1_ON;
							Out_State[4] = out_state;
							out_state = AO2_ON;
							Out_State[5] = out_state;

							//在这里得到需要设定的电压值
							if (Judgement_Data[16] == 0xE2)
							{
								Set_AOVoltage1 = Judgement_Data[14] + Judgement_Data[15] * 0.01;
								Set_AOVoltage2 = Judgement_Data[14] + Judgement_Data[15] * 0.01;
								if (debug_print == 1)
								{
									Serial.println("Set_AOVoltage1,2 = " + String(Set_AOVoltage2) + "mv");
								}
							}
							//float ar1 = ((analogRead1 * 0.8056) * 11;//4537.65
							//float ar1 = ((analogRead1 * 0.8056) * 0.011;//4537.65
							float AV1 = (Set_AOVoltage1 / 0.011) / 0.8056;
							float AV2 = (Set_AOVoltage2 / 0.011) / 0.8056;
							if (AV2 - floor(AV2) >= 0.5)
							{
								Analog_Value1 = floor(AV1) + 1;
								Analog_Value2 = floor(AV2) + 1;
							}
							else if (AV2 - floor(AV2) < 0.5)
							{
								Analog_Value1 = floor(AV1);
								Analog_Value2 = floor(AV2);
							}
							else
							{
								if (debug_print == 1)
								{
									Serial.println("意外BUG区");
								}
							}
							if (debug_print == 1)
							{
								Serial.println("AV1,2 = " + String(AV2));
								Serial.println("Analog_Value1,2 = " + String(Analog_Value2));
							}

							//决定在这里赋时间值，先赋持续时间的值到数组
							Duration_time = Judgement_Data[17] * 0x10000 + Judgement_Data[18] * 0x100 + Judgement_Data[19];
							duration[4] = Duration_time;
							duration[5] = Duration_time;
							if (debug_print == 1)
							{
								Serial.print("Duration_time=");
								Serial.println(Duration_time);
								Serial.print("duration[4，5]=");
								Serial.println(duration[5]);
							}

							//然后赋旧时间的值到数组
							oldtime = millis();
							ot[4] = oldtime;
							ot[5] = oldtime;
							if (debug_print == 1)
							{
								Serial.print("oldtime=");
								Serial.println(oldtime);
								Serial.print("ot[4，5]=");
								Serial.println(ot[5]);
							}

							if (Out_State[4] == AO1_ON && Out_State[5] == AO2_ON)
							{
								E015_status = SetParamsOk;
							}
							else
							{
								E015_status = SetParamsErr;
							}

							//是否广播指令
							Receive_IsBroadcast = Judgement_Data[6];

							//进行状态的回执
							Send_E015(Receive_IsBroadcast, E015_status);

							forswitch();
						}
						//模拟输出全部路关
						else if (Judgement_Data[14] == 0x00 && Judgement_Data[15] == 0x00 && Judgement_Data[16] == 0x00)
						{
							//将模拟输出2路关的状态值写入
							out_state = Stateless;
							Out_State[4] = out_state;
							Out_State[5] = out_state;
							analogWrite(AO1, 0);
							analogWrite(AO2, 0);

							//将所有的设定时间，已工作时间，剩余时间清零
							duration[4] = 0x00;
							CurrentWorkSec[4] = 0x00;
							remaining[4] = 0x00;
							duration[5] = 0x00;
							CurrentWorkSec[5] = 0x00;
							remaining[5] = 0x00;

							AO1_SetWorkSec1 = 0x00;
							AO1_SetWorkSec2 = 0x00;
							AO1_SetWorkSec3 = 0x00;
							AO1_CurrentWorkSec1 = 0x00;
							AO1_CurrentWorkSec2 = 0x00;
							AO1_CurrentWorkSec3 = 0x00;
							AO1_RemainWorkSec1 = 0x00;
							AO1_RemainWorkSec2 = 0x00;
							AO1_RemainWorkSec3 = 0x00;

							AO2_SetWorkSec1 = 0x00;
							AO2_SetWorkSec2 = 0x00;
							AO2_SetWorkSec3 = 0x00;
							AO2_CurrentWorkSec1 = 0x00;
							AO2_CurrentWorkSec2 = 0x00;
							AO2_CurrentWorkSec3 = 0x00;
							AO2_RemainWorkSec1 = 0x00;
							AO2_RemainWorkSec2 = 0x00;
							AO2_RemainWorkSec3 = 0x00;

							if (debug_print == 1)
							{
								Serial.println("模拟输出全部路关");
							}

							if (Out_State[4] == Stateless && Out_State[5] == Stateless)
							{
								E015_status = SetParamsOk;
							}
							else
							{
								E015_status = SetParamsErr;
							}

							//是否广播指令
							Receive_IsBroadcast = Judgement_Data[6];

							//进行状态的回执
							Send_E015(Receive_IsBroadcast, E015_status);

							forswitch();
						}
						else
						{
							if (debug_print == 1)
							{
								Serial.println("意外BUG区");
							}
						}
					}
					//不存在的设备路数
					else
					{
						if (debug_print == 1)
						{
							Serial.println("不存在的设备路数");
						}
					}
				}
				else
				{
					if (debug_print == 1)
					{
						Serial.println("数据长度不正确");
					}
				}
			}
			//不存在的设备类型
			else
			{
				if (debug_print == 1)
				{
					Serial.println("不存在的设备类型");
				}
			}
		}
		//判断为组播
		else if (Judgement_Data[6] == 0x55)
		{
			//判断是否属于DO1的组
			if (Judgement_Data[8] == AT24CXX_ReadOneByte(16) || Judgement_Data[8] == AT24CXX_ReadOneByte(17) ||
				Judgement_Data[8] == AT24CXX_ReadOneByte(18) || Judgement_Data[8] == AT24CXX_ReadOneByte(19) ||
				Judgement_Data[8] == AT24CXX_ReadOneByte(20))
			{
				//判断是否属于DO1的子设备类型
				if (Judgement_Data[12] == AT24CXX_ReadOneByte(14) && Judgement_Data[13] == AT24CXX_ReadOneByte(15))
				{
					//1路开
					if (Judgement_Data[14] == 0x01)
					{
						//digitalWrite(DO1, HIGH);

						//将1路开的状态值写入
						out_state = DO1_ON;
						Out_State[0] = out_state;

						//决定在这里赋时间值，先赋持续时间的值到数组
						Duration_time = Judgement_Data[15] * 0x1000 + Judgement_Data[16] * 0x100 + Judgement_Data[17];
						duration[0] = Duration_time;
						if (debug_print == 1)
						{
							Serial.print("Duration_time=");
							Serial.println(Duration_time);
							Serial.print("duration[0]=");
							Serial.println(duration[0]);
						}

						//然后赋旧时间的值到数组
						oldtime = millis();
						ot[0] = oldtime;
						if (debug_print == 1)
						{
							Serial.print("oldtime=");
							Serial.println(oldtime);
							Serial.print("ot[0]=");
							Serial.println(ot[0]);
						}

						if (Out_State[0] == DO1_ON)
						{
							E015_status = SetParamsOk;
						}
						else
						{
							E015_status = SetParamsErr;
						}

						//是否广播指令
						Receive_IsBroadcast = Judgement_Data[6];

						//进行状态的回执
						Send_E015(Receive_IsBroadcast, E015_status);
					}
					//1路关
					else if (Judgement_Data[14] == 0x00)
					{
						//将1路关的状态值写入
						out_state = Stateless;
						Out_State[0] = out_state;
						digitalWrite(DO1, LOW);

						//将所有的设定时间，已工作时间，剩余时间清零
						CurrentWorkSec[0] = 0x00;
						DO1_CurrentWorkSec1 = 0x00;
						DO1_CurrentWorkSec2 = 0x00;
						DO1_CurrentWorkSec3 = 0x00;
						DO1_RemainWorkSec1 = 0x00;
						DO1_RemainWorkSec2 = 0x00;
						DO1_RemainWorkSec3 = 0x00;

						if (debug_print == 1)
						{
							Serial.println("数字输出1关");
						}

						if (Out_State[0] == Stateless)
						{
							E015_status = SetParamsOk;
						}
						else
						{
							E015_status = SetParamsErr;
						}

						//是否广播指令
						Receive_IsBroadcast = Judgement_Data[6];

						//进行状态的回执
						Send_E015(Receive_IsBroadcast, E015_status);
					}
					else
					{
						if (debug_print == 1)
						{
							Serial.println("不存在的开度");
						}
					}
				}
			}
			//判断是否属于DO2的组
			else if (Judgement_Data[8] == AT24CXX_ReadOneByte(23) || Judgement_Data[8] == AT24CXX_ReadOneByte(24) ||
				Judgement_Data[8] == AT24CXX_ReadOneByte(25) || Judgement_Data[8] == AT24CXX_ReadOneByte(26) ||
				Judgement_Data[8] == AT24CXX_ReadOneByte(27))
			{
				if (Judgement_Data[12] == AT24CXX_ReadOneByte(21) && Judgement_Data[13] == AT24CXX_ReadOneByte(22))
				{
					//2路开
					if (Judgement_Data[14] == 0x01)
					{
						//digitalWrite(DO2, HIGH);

						//将2路开的状态值写入
						out_state = DO2_ON;
						Out_State[1] = out_state;

						//决定在这里赋时间值，先赋持续时间的值到数组
						Duration_time = Judgement_Data[15] * 0x1000 + Judgement_Data[16] * 0x100 + Judgement_Data[17];
						duration[1] = Duration_time;
						if (debug_print == 1)
						{
							Serial.print("Duration_time=");
							Serial.println(Duration_time);
							Serial.print("duration[1]=");
							Serial.println(duration[1]);
						}

						//然后赋旧时间的值到数组
						oldtime = millis();
						ot[1] = oldtime;
						if (debug_print == 1)
						{
							Serial.print("oldtime=");
							Serial.println(oldtime);
							Serial.print("ot[1]=");
							Serial.println(ot[1]);
						}

						if (Out_State[1] == DO2_ON)
						{
							E015_status = SetParamsOk;
						}
						else
						{
							E015_status = SetParamsErr;
						}

						//是否广播指令
						Receive_IsBroadcast = Judgement_Data[6];

						//进行状态的回执
						Send_E015(Receive_IsBroadcast, E015_status);
					}
					//2路关
					else if (Judgement_Data[14] == 0x00)
					{
						//将2路关的状态值写入
						out_state = Stateless;
						Out_State[1] = out_state;
						digitalWrite(DO2, LOW);

						//将所有的设定时间，已工作时间，剩余时间清零
						CurrentWorkSec[1] = 0x00;
						DO2_CurrentWorkSec1 = 0x00;
						DO2_CurrentWorkSec2 = 0x00;
						DO2_CurrentWorkSec3 = 0x00;
						DO2_RemainWorkSec1 = 0x00;
						DO2_RemainWorkSec2 = 0x00;
						DO2_RemainWorkSec3 = 0x00;

						if (debug_print == 1)
						{
							Serial.println("数字输出2关");
						}

						if (Out_State[1] == Stateless)
						{
							E015_status = SetParamsOk;
						}
						else
						{
							E015_status = SetParamsErr;
						}

						//是否广播指令
						Receive_IsBroadcast = Judgement_Data[6];

						//进行状态的回执
						Send_E015(Receive_IsBroadcast, E015_status);
					}
					else
					{
						if (debug_print == 1)
						{
							Serial.println("不存在的开度");
						}
					}
				}
			}
			//判断是否属于DO3的组
			else if (Judgement_Data[8] == AT24CXX_ReadOneByte(30) || Judgement_Data[8] == AT24CXX_ReadOneByte(31) ||
				Judgement_Data[8] == AT24CXX_ReadOneByte(32) || Judgement_Data[8] == AT24CXX_ReadOneByte(33) ||
				Judgement_Data[8] == AT24CXX_ReadOneByte(34))
			{
				if (Judgement_Data[12] == AT24CXX_ReadOneByte(28) && Judgement_Data[13] == AT24CXX_ReadOneByte(29))
				{
					//3路开
					if (Judgement_Data[14] == 0x01)
					{
						//digitalWrite(KCZJ1, );

						//将3路开的状态值写入
						out_state = DO3_ON;
						Out_State[2] = out_state;

						//决定在这里赋时间值，先赋持续时间的值到数组
						Duration_time = Judgement_Data[15] * 0x1000 + Judgement_Data[16] * 0x100 + Judgement_Data[17];
						duration[2] = Duration_time;
						if (debug_print == 1)
						{
							Serial.print("Duration_time=");
							Serial.println(Duration_time);
							Serial.print("duration[2]=");
							Serial.println(duration[2]);
						}

						//然后赋旧时间的值到数组
						oldtime = millis();
						ot[2] = oldtime;
						if (debug_print == 1)
						{
							Serial.print("oldtime=");
							Serial.println(oldtime);
							Serial.print("ot[2]=");
							Serial.println(ot[2]);
						}

						if (Out_State[2] == DO3_ON)
						{
							E015_status = SetParamsOk;
						}
						else
						{
							E015_status = SetParamsErr;
						}

						//是否广播指令
						Receive_IsBroadcast = Judgement_Data[6];

						//进行状态的回执
						Send_E015(Receive_IsBroadcast, E015_status);
					}
					//3路关
					else if (Judgement_Data[14] == 0x00)
					{
						//将3路关的状态值写入
						out_state = Stateless;
						Out_State[2] = out_state;
						digitalWrite(KCZJ1, HIGH);

						//将所有的设定时间，已工作时间，剩余时间清零
						CurrentWorkSec[2] = 0x00;
						DO3_CurrentWorkSec1 = 0x00;
						DO3_CurrentWorkSec2 = 0x00;
						DO3_CurrentWorkSec3 = 0x00;
						DO3_RemainWorkSec1 = 0x00;
						DO3_RemainWorkSec2 = 0x00;
						DO3_RemainWorkSec3 = 0x00;

						if (debug_print == 1)
						{
							Serial.println("数字输出3关");
						}

						if (Out_State[1] == Stateless)
						{
							E015_status = SetParamsOk;
						}
						else
						{
							E015_status = SetParamsErr;
						}

						//是否广播指令
						Receive_IsBroadcast = Judgement_Data[6];

						//进行状态的回执
						Send_E015(Receive_IsBroadcast, E015_status);
					}
					else
					{
						if (debug_print == 1)
						{
							Serial.println("不存在的开度");
						}
					}
				}
			}
			//判断是否属于DO4的组
			else if (Judgement_Data[8] == AT24CXX_ReadOneByte(37) || Judgement_Data[8] == AT24CXX_ReadOneByte(38) ||
				Judgement_Data[8] == AT24CXX_ReadOneByte(39) || Judgement_Data[8] == AT24CXX_ReadOneByte(40) ||
				Judgement_Data[8] == AT24CXX_ReadOneByte(41))
			{
				if (Judgement_Data[12] == AT24CXX_ReadOneByte(35) && Judgement_Data[13] == AT24CXX_ReadOneByte(36))
				{
					//4路开
					if (Judgement_Data[14] == 0x01)
					{
						//digitalWrite(KCZJ2, LOW);

						//将4路开的状态值写入
						out_state = DO4_ON;
						Out_State[3] = out_state;

						//决定在这里赋时间值，先赋持续时间的值到数组
						Duration_time = Judgement_Data[15] * 0x1000 + Judgement_Data[16] * 0x100 + Judgement_Data[17];
						duration[3] = Duration_time;
						if (debug_print == 1)
						{
							Serial.print("Duration_time=");
							Serial.println(Duration_time);
							Serial.print("duration[3]=");
							Serial.println(duration[3]);
						}

						//然后赋旧时间的值到数组
						oldtime = millis();
						ot[3] = oldtime;
						if (debug_print == 1)
						{
							Serial.print("oldtime=");
							Serial.println(oldtime);
							Serial.print("ot[3]=");
							Serial.println(ot[3]);
						}

						if (Out_State[3] == DO4_ON)
						{
							E015_status = SetParamsOk;
						}
						else
						{
							E015_status = SetParamsErr;
						}

						//是否广播指令
						Receive_IsBroadcast = Judgement_Data[6];

						//进行状态的回执
						Send_E015(Receive_IsBroadcast, E015_status);
					}
					//4路关
					else if (Judgement_Data[14] == 0x00)
					{
						//将4路关的状态值写入
						out_state = Stateless;
						Out_State[3] = out_state;
						digitalWrite(KCZJ2, HIGH);

						//将所有的设定时间，已工作时间，剩余时间清零
						CurrentWorkSec[3] = 0x00;
						DO4_CurrentWorkSec1 = 0x00;
						DO4_CurrentWorkSec2 = 0x00;
						DO4_CurrentWorkSec3 = 0x00;
						DO4_RemainWorkSec1 = 0x00;
						DO4_RemainWorkSec2 = 0x00;
						DO4_RemainWorkSec3 = 0x00;

						if (debug_print == 1)
						{
							Serial.println("数字输出4关");
						}

						if (Out_State[3] == Stateless)
						{
							E015_status = SetParamsOk;
						}
						else
						{
							E015_status = SetParamsErr;
						}

						//是否广播指令
						Receive_IsBroadcast = Judgement_Data[6];

						//进行状态的回执
						Send_E015(Receive_IsBroadcast, E015_status);
					}
					else
					{
						if (debug_print == 1)
						{
							Serial.println("不存在的开度");
						}
					}
				}
			}
			//判断是否属于AO1的组
			else if (Judgement_Data[8] == AT24CXX_ReadOneByte(44) || Judgement_Data[8] == AT24CXX_ReadOneByte(45) ||
				Judgement_Data[8] == AT24CXX_ReadOneByte(46) || Judgement_Data[8] == AT24CXX_ReadOneByte(47) ||
				Judgement_Data[8] == AT24CXX_ReadOneByte(48))
			{
				if (Judgement_Data[12] == AT24CXX_ReadOneByte(42) && Judgement_Data[13] == AT24CXX_ReadOneByte(43))
				{
					//模拟输出1路开
					if (Judgement_Data[14] != 0x00 && Judgement_Data[15] != 0x00 && Judgement_Data[16] != 0x00)
					{
						//analogWrite
						//将1路开的状态值写入
						out_state = AO1_ON;
						Out_State[4] = out_state;

						//在这里得到需要设定的电压值
						if (Judgement_Data[16] == 0xE2)
						{
							Set_AOVoltage1 = (Judgement_Data[14] + Judgement_Data[15] * 0.01);
							if (debug_print == 1)
							{
								Serial.println("Set_AOVoltage1 = " + String(Set_AOVoltage1) + "V");
							}
						}
						//float ar1 = ((analogRead1 * 0.8056) * 11;//4537.65
						//float ar1 = ((analogRead1 * 0.8056) * 0.011;//4537.65
						float AV1 = (Set_AOVoltage1 / 0.011) / 0.8056;
						if (AV1 - floor(AV1) >= 0.5)
						{
							Analog_Value1 = floor(AV1) + 1;
						}
						else if (AV1 - floor(AV1) < 0.5)
						{
							Analog_Value1 = floor(AV1);
						}
						else
						{
							if (debug_print == 1)
							{
								Serial.println("意外BUG区");
							}
						}
						if (debug_print == 1)
						{
							Serial.println("AV1 = " + String(AV1));
							Serial.println("Analog_Value1 = " + String(Analog_Value1));
						}

						//决定在这里赋时间值，先赋持续时间的值到数组
						Duration_time = Judgement_Data[17] * 0x1000 + Judgement_Data[18] * 0x100 + Judgement_Data[19];
						duration[4] = Duration_time;
						if (debug_print == 1)
						{
							Serial.print("Duration_time=");
							Serial.println(Duration_time);
							Serial.print("duration[4]=");
							Serial.println(duration[4]);
						}

						//然后赋旧时间的值到数组
						oldtime = millis();
						ot[4] = oldtime;
						if (debug_print == 1)
						{
							Serial.print("oldtime=");
							Serial.println(oldtime);
							Serial.print("ot[4]=");
							Serial.println(ot[4]);
						}

						if (Out_State[4] == AO1_ON)
						{
							E015_status = SetParamsOk;
						}
						else
						{
							E015_status = SetParamsErr;
						}

						//是否广播指令
						Receive_IsBroadcast = Judgement_Data[6];

						//进行状态的回执
						Send_E015(Receive_IsBroadcast, E015_status);
					}
					//模拟输出1路关
					else if (Judgement_Data[14] == 0x00 && Judgement_Data[15] == 0x00 && Judgement_Data[16] == 0x00)
					{
						//将模拟输出1路关的状态值写入
						out_state = Stateless;
						Out_State[4] = out_state;
						analogWrite(AO1, 0);

						//将所有的设定时间，已工作时间，剩余时间清零
						CurrentWorkSec[4] = 0x00;
						AO1_CurrentWorkSec1 = 0x00;
						AO1_CurrentWorkSec2 = 0x00;
						AO1_CurrentWorkSec3 = 0x00;
						AO1_RemainWorkSec1 = 0x00;
						AO1_RemainWorkSec2 = 0x00;
						AO1_RemainWorkSec3 = 0x00;

						if (debug_print == 1)
						{
							Serial.println("模拟输出2关");
						}

						if (Out_State[4] == Stateless)
						{
							E015_status = SetParamsOk;
						}
						else
						{
							E015_status = SetParamsErr;
						}

						//是否广播指令
						Receive_IsBroadcast = Judgement_Data[6];

						//进行状态的回执
						Send_E015(Receive_IsBroadcast, E015_status);
					}
					else
					{
						if (debug_print == 1)
						{
							Serial.println("意外BUG区");
						}
					}
				}
			}
			//判断是否属于AO2的组
			else if (Judgement_Data[8] == AT24CXX_ReadOneByte(51) || Judgement_Data[8] == AT24CXX_ReadOneByte(52) ||
				Judgement_Data[8] == AT24CXX_ReadOneByte(53) || Judgement_Data[8] == AT24CXX_ReadOneByte(54) ||
				Judgement_Data[8] == AT24CXX_ReadOneByte(55))
			{
				if (Judgement_Data[12] == AT24CXX_ReadOneByte(49) && Judgement_Data[13] == AT24CXX_ReadOneByte(50))
				{
					//模拟输出2路开
					if (Judgement_Data[14] != 0x00 && Judgement_Data[15] != 0x00 && Judgement_Data[16] != 0x00)
					{
						//analogWrite
						//将2路开的状态值写入
						out_state = AO2_ON;
						Out_State[5] = out_state;

						//在这里得到需要设定的电压值
						if (Judgement_Data[16] == 0xE2)
						{
							Set_AOVoltage2 = Judgement_Data[14] + Judgement_Data[15] * 0.01;
							if (debug_print == 1)
							{
								Serial.println("Set_AOVoltage1 = " + String(Set_AOVoltage2) + "mv");
							}
						}
						//float ar1 = ((analogRead1 * 0.8056) * 11;//4537.65
						//float ar1 = ((analogRead1 * 0.8056) * 0.011;//4537.65
						float AV2 = (Set_AOVoltage2 / 0.011) / 0.8056;
						if (AV2 - floor(AV2) >= 0.5)
						{
							Analog_Value2 = floor(AV2) + 1;
						}
						else if (AV2 - floor(AV2) < 0.5)
						{
							Analog_Value2 = floor(AV2);
						}
						else
						{
							if (debug_print == 1)
							{
								Serial.println("意外BUG区");
							}
						}
						if (debug_print == 1)
						{
							Serial.println("AV2 = " + String(AV2));
							Serial.println("Analog_Value2 = " + String(Analog_Value2));
						}

						//决定在这里赋时间值，先赋持续时间的值到数组
						Duration_time = Judgement_Data[17] * 0x1000 + Judgement_Data[18] * 0x100 + Judgement_Data[19];
						duration[5] = Duration_time;
						if (debug_print == 1)
						{
							Serial.print("Duration_time=");
							Serial.println(Duration_time);
							Serial.print("duration[5]=");
							Serial.println(duration[5]);
						}

						//然后赋旧时间的值到数组
						oldtime = millis();
						ot[5] = oldtime;
						if (debug_print == 1)
						{
							Serial.print("oldtime=");
							Serial.println(oldtime);
							Serial.print("ot[5]=");
							Serial.println(ot[5]);
						}

						if (Out_State[5] == AO2_ON)
						{
							E015_status = SetParamsOk;
						}
						else
						{
							E015_status = SetParamsErr;
						}

						//是否广播指令
						Receive_IsBroadcast = Judgement_Data[6];

						//进行状态的回执
						Send_E015(Receive_IsBroadcast, E015_status);
					}
					//模拟输出2路关
					else if (Judgement_Data[14] == 0x00 && Judgement_Data[15] == 0x00 && Judgement_Data[16] == 0x00)
					{
						//将模拟输出2路关的状态值写入
						out_state = Stateless;
						Out_State[5] = out_state;
						analogWrite(AO2, 0);

						//将所有的设定时间，已工作时间，剩余时间清零
						CurrentWorkSec[5] = 0x00;
						AO2_CurrentWorkSec1 = 0x00;
						AO2_CurrentWorkSec2 = 0x00;
						AO2_CurrentWorkSec3 = 0x00;
						AO2_RemainWorkSec1 = 0x00;
						AO2_RemainWorkSec2 = 0x00;
						AO2_RemainWorkSec3 = 0x00;

						if (debug_print == 1)
						{
							Serial.println("模拟输出2关");
						}

						if (Out_State[5] == Stateless)
						{
							E015_status = SetParamsOk;
						}
						else
						{
							E015_status = SetParamsErr;
						}

						//是否广播指令
						Receive_IsBroadcast = Judgement_Data[6];

						//进行状态的回执
						Send_E015(Receive_IsBroadcast, E015_status);
					}
					else
					{
						if (debug_print == 1)
						{
							Serial.println("意外BUG区");
						}
					}
				}
			}
			else
			{
				//不存在的任何组
				if (debug_print == 1)
				{
					Serial.println("不存在的任何组");
				}
			}
		}
		//不存在的广播功能
		else
		{
			if (debug_print == 1)
			{
				Serial.println("不存在的广播功能");
			}
		}

		//是否广播指令
		Receive_IsBroadcast = Judgement_Data[6];


		//进行状态的回执
		Send_E021(Receive_IsBroadcast);//各路数状态的回执

		Send_E022(Receive_IsBroadcast);//各路数剩余时间的回执
	}
	else
	{
		E015_status = Incorrect_information_error;
		if (debug_print == 1)
		{
			Serial.println("区域信息不正确");
			Serial.println(String("E015_status = Incorrect_information_error") + String(E015_status));
		}
		//进行状态的回执
		Send_E015(Receive_IsBroadcast, E015_status);
	}

	if (debug_print == 1)
	{
		Serial.println("完成A022状态回执");
		Serial.println("结束Receive_A022函数");
	}
}

//函 数 名：Verification_Reserved_field() 
//功能描述：验证预留字段是否写入成功的函数
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
int Verification_Reserved_field(unsigned char* Judgement_Data, int Initial)
{
	int Check_Value = 0;
	if (debug_print == 1)
	{
		Serial.println("Initial = " + String(Initial));
	}
	for (size_t i = 0; i < 8; i++)
	{
		if (AT24CXX_ReadOneByte(Initial + i) == Judgement_Data[9 + i])
		{
			Check_Value++;
			if (debug_print == 1)
			{
				Serial.println("AT24CXX_ReadOneByte[ " + String(Initial + i) + " ] = " + String(Check_Value));
				Serial.println("Check_Value = " + String(Check_Value));
			}
		}
	}
	if (Check_Value == 8)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//函 数 名：forswitch() 
//功能描述：执行片轮询的函数
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
void forswitch()
{
	if (Out_State[0] == Stateless && Out_State[1] == Stateless &&
		Out_State[2] == Stateless && Out_State[3] == Stateless &&
		Out_State[4] == Stateless && Out_State[5] == Stateless)
	{

	}
	else
	{
		for (int i = 0; i < 6; i++)
		{
			switch (Out_State[i])
			{
				/*状态：无状态
				 *在此状态中需要不断检测接收的值，
				 *接收到值后进行判断进入下一个状态。*/
			case Stateless:
				//无状态
				//无状态指令
				//--------------------------------------
				if (debug == 1)
				{
					delay(500);
					if (debug_print == 1)
					{
						Serial.print(i);
						Serial.println("进入case：Stateless");
					}
				}
				//--------------------------------------
				break;

				/*状态：DO1开
				*在此状态中需要不断检测接收的值，
				*接收到值后进行判断进入下一个状态。*/
			case DO1_ON:
				//--------------------------------------
				if (debug == 1)
				{
					delay(500);
					if (debug_print == 1)
					{
						Serial.print(i);
						Serial.println("进入case：DO1_ON");
					}
				}
				//--------------------------------------
				digitalWrite(DO1, HIGH);

				CurrentWorkSec[i] = (millis() - ot[i]) / 1000;//得到DO1的已工作时长
				remaining[i] = (duration[i] > CurrentWorkSec[i]) ? (duration[i] - CurrentWorkSec[i]) : 0;//得到DO1的剩余工作时长
				if (debug_print == 1)
				{
					//Serial.println(String("DO1的设定工作时长 = ") + duration[i]);
					//Serial.println(String("DO1的已工作时长 = ") + CurrentWorkSec[i]);
					//Serial.println(String("DO1的剩余工作时长 = ") + remaining[i]);
				}
				//---------------------------这一段代码将已工作的数值和剩余工作数值拆位-------------------------------------------------------------------------------
				if (duration[i] <= 0xFF)
				{
					DO1_SetWorkSec1 = 0x00;
					DO1_SetWorkSec2 = 0x00;
					DO1_SetWorkSec3 = duration[i];
				}
				else if (duration[i] > 0xFF && duration[i] <= 0xFFFF)
				{
					DO1_SetWorkSec1 = 0x00;
					DO1_SetWorkSec2 = duration[i] / 0x100;
					DO1_SetWorkSec3 = (duration[i] - DO1_SetWorkSec2 * 0x100);
				}
				else if (duration[i] > 0xFFFF)
				{
					DO1_SetWorkSec1 = duration[i] / 0x10000;
					DO1_SetWorkSec2 = duration[i] - (DO1_SetWorkSec1 * 0x10000) / 0x100;
					DO1_SetWorkSec3 = duration[i] - (DO1_SetWorkSec1 * 0x10000) - (DO1_SetWorkSec2 * 0x100);
				}
				else
				{
					Serial.println("读取DO1设定工作时间错误");
					//这里应该需要回执错误？？？
				}

				if (CurrentWorkSec[i] <= 0xFF)
				{
					DO1_CurrentWorkSec1 = 0x00;
					DO1_CurrentWorkSec2 = 0x00;
					DO1_CurrentWorkSec3 = CurrentWorkSec[i];
				}
				else if (CurrentWorkSec[i] > 0xFF && CurrentWorkSec[i] <= 0xFFFF)
				{
					DO1_CurrentWorkSec1 = 0x00;
					DO1_CurrentWorkSec2 = CurrentWorkSec[i] / 0x100;
					DO1_CurrentWorkSec3 = (CurrentWorkSec[i] - DO1_CurrentWorkSec2 * 0x100);
				}
				else if (CurrentWorkSec[i] > 0xFFFF)
				{
					DO1_CurrentWorkSec1 = CurrentWorkSec[i] / 0x10000;
					DO1_CurrentWorkSec2 = CurrentWorkSec[i] - (DO1_CurrentWorkSec1 * 0x10000) / 0x100;
					DO1_CurrentWorkSec3 = CurrentWorkSec[i] - (DO1_CurrentWorkSec1 * 0x10000) - (DO1_CurrentWorkSec2 * 0x100);
				}
				else
				{
					Serial.println("读取DO1已工作时间错误");
					//这里应该需要回执错误？？？
				}

				if (remaining[i] <= 0xFF)
				{
					DO1_RemainWorkSec1 = 0x00;
					DO1_RemainWorkSec2 = 0x00;
					DO1_RemainWorkSec3 = remaining[i];
				}
				else if (remaining[i] > 0xFF && remaining[i] <= 0xFFFF)
				{
					DO1_RemainWorkSec1 = 0x00;
					DO1_RemainWorkSec2 = remaining[i] / 0x100;
					DO1_RemainWorkSec3 = (remaining[i] - DO1_RemainWorkSec2 * 0x100);
				}
				else if (remaining[i] > 0xFFFF)
				{
					DO1_RemainWorkSec1 = remaining[i] / 0x10000;
					DO1_RemainWorkSec2 = remaining[i] - (DO1_RemainWorkSec1 * 0x10000) / 0x100;
					DO1_RemainWorkSec3 = remaining[i] - (DO1_RemainWorkSec1 * 0x10000) - (DO1_RemainWorkSec2 * 0x100);
				}
				else
				{
					Serial.println("读取DO1剩余工作时间错误");
					//这里应该需要回执错误？？？
				}

				if (debug_print == 1)
				{
					//Serial.println(String("设定工作时间拆位结果为：") + DO1_SetWorkSec1 + "/" + DO1_SetWorkSec2 + "/" + DO1_SetWorkSec3);
					//Serial.println(String("已工作时间拆位结果为：") + DO1_CurrentWorkSec1 + "/" + DO1_CurrentWorkSec2 + "/" + DO1_CurrentWorkSec3);
					//Serial.println(String("剩余工作时间拆位结果为：") + DO1_RemainWorkSec1 + "/" + DO1_RemainWorkSec2 + "/" + DO1_RemainWorkSec3);
					if (debug == 1)
					{
						delay(500);
					}
				}
				//-------------------------------------------------------------------------------------------------------------------------------------------


				if (millis() - ot[i] >= duration[i] * 1000)
				{
					//时间到了需要清空这个数组的东西
					if (debug_print == 1)
					{
						Serial.println("DO1设定的时间到了呀");
					}
					digitalWrite(DO1, LOW);
					Out_State[i] = Stateless;

					//将所有的设定时间，已工作时间，剩余时间清零
					duration[i] = 0x00;
					CurrentWorkSec[i] = 0x00;
					remaining[i] = 0x00;
					DO1_SetWorkSec1 = 0x00;
					DO1_SetWorkSec2 = 0x00;
					DO1_SetWorkSec3 = 0x00;
					DO1_CurrentWorkSec1 = 0x00;
					DO1_CurrentWorkSec2 = 0x00;
					DO1_CurrentWorkSec3 = 0x00;
					DO1_RemainWorkSec1 = 0x00;
					DO1_RemainWorkSec2 = 0x00;
					DO1_RemainWorkSec3 = 0x00;

					//进行已经关闭状态的回执
					Send_E021(Receive_IsBroadcast);//各路数状态的回执
					Send_E022(Receive_IsBroadcast);//各路数时间的回执
				}
				break;

				/*状态：DO2开
				*在此状态中需要不断检测接收的值，
				*接收到值后进行判断进入下一个状态。*/
			case DO2_ON:
				//--------------------------------------
				if (debug == 1)
				{
					delay(500);
					if (debug_print == 1)
					{
						Serial.print(i);
						Serial.println("进入case：DO2_ON");
					}
				}
				//--------------------------------------
				digitalWrite(DO2, HIGH);

				CurrentWorkSec[i] = (millis() - ot[i]) / 1000;//得到DO2的已工作时长
				remaining[i] = (duration[i] > CurrentWorkSec[i]) ? (duration[i] - CurrentWorkSec[i]) : 0;//得到DO2的剩余工作时长
				if (debug_print == 1)
				{
					//Serial.println(String("DO2的设定工作时长 = ") + duration[i]);
					//Serial.println(String("DO2的已工作时长 = ") + CurrentWorkSec[i]);
					//Serial.println(String("DO2的剩余工作时长 = ") + remaining[i]);
				}
				//-----------------------------------这一段代码将已工作的数值拆位-------------------------------------------------------------------------------
				if (duration[i] <= 0xFF)
				{
					DO2_SetWorkSec1 = 0x00;
					DO2_SetWorkSec2 = 0x00;
					DO2_SetWorkSec3 = duration[i];
				}
				else if (duration[i] > 0xFF && duration[i] <= 0xFFFF)
				{
					DO2_SetWorkSec1 = 0x00;
					DO2_SetWorkSec2 = duration[i] / 0x100;
					DO2_SetWorkSec3 = (duration[i] - DO2_SetWorkSec2 * 0x100);
				}
				else if (duration[i] > 0xFFFF)
				{
					DO2_SetWorkSec1 = duration[i] / 0x10000;
					DO2_SetWorkSec2 = duration[i] - (DO2_SetWorkSec1 * 0x10000) / 0x100;
					DO2_SetWorkSec3 = duration[i] - (DO2_SetWorkSec1 * 0x10000) - (DO2_SetWorkSec2 * 0x100);
				}
				else
				{
					Serial.println("读取DO2设定工作时间错误");
					//这里应该需要回执错误？？？
				}

				if (CurrentWorkSec[i] <= 0xFF)
				{
					DO2_CurrentWorkSec1 = 0x00;
					DO2_CurrentWorkSec2 = 0x00;
					DO2_CurrentWorkSec3 = CurrentWorkSec[i];
				}
				else if (CurrentWorkSec[i] > 0xFF && CurrentWorkSec[i] <= 0xFFFF)
				{
					DO2_CurrentWorkSec1 = 0x00;
					DO2_CurrentWorkSec2 = CurrentWorkSec[i] / 0x100;
					DO2_CurrentWorkSec3 = (CurrentWorkSec[i] - DO2_CurrentWorkSec2 * 0x100);
				}
				else if (CurrentWorkSec[i] > 0xFFFF)
				{
					DO2_CurrentWorkSec1 = CurrentWorkSec[i] / 0x10000;
					DO2_CurrentWorkSec2 = CurrentWorkSec[i] - (DO2_CurrentWorkSec1 * 0x10000) / 0x100;
					DO2_CurrentWorkSec3 = CurrentWorkSec[i] - (DO2_CurrentWorkSec1 * 0x10000) - (DO2_CurrentWorkSec2 * 0x100);
				}
				else
				{
					Serial.println("读取DO2已工作时间错误");
					//这里应该需要回执错误？？？
				}

				if (remaining[i] <= 0xFF)
				{
					DO2_RemainWorkSec1 = 0x00;
					DO2_RemainWorkSec2 = 0x00;
					DO2_RemainWorkSec3 = remaining[i];
				}
				else if (remaining[i] > 0xFF && remaining[i] <= 0xFFFF)
				{
					DO2_RemainWorkSec1 = 0x00;
					DO2_RemainWorkSec2 = remaining[i] / 0x100;
					DO2_RemainWorkSec3 = (remaining[i] - DO2_RemainWorkSec2 * 0x100);
				}
				else if (remaining[i] > 0xFFFF)
				{
					DO2_RemainWorkSec1 = remaining[i] / 0x10000;
					DO2_RemainWorkSec2 = remaining[i] - (DO2_RemainWorkSec1 * 0x10000) / 0x100;
					DO2_RemainWorkSec3 = remaining[i] - (DO2_RemainWorkSec1 * 0x10000) - (DO2_RemainWorkSec2 * 0x100);
				}
				else
				{
					Serial.println("读取DO2剩余工作时间错误");
					//这里应该需要回执错误？？？
				}

				if (debug_print == 1)
				{
					//Serial.println(String("已工作时间拆位结果为：") + DO2_CurrentWorkSec1 + "/" + DO2_CurrentWorkSec2 + "/" + DO2_CurrentWorkSec3);
					//Serial.println(String("剩余工作时间拆位结果为：") + DO2_RemainWorkSec1 + "/" + DO2_RemainWorkSec2 + "/" + DO2_RemainWorkSec3);
					if (debug == 1)
					{
						delay(500);
					}
				}
				//-------------------------------------------------------------------------------------------------------------------------------------------


				if (millis() - ot[i] >= duration[i] * 1000)
				{
					//时间到了需要清空这个数组的东西
					if (debug_print == 1)
					{
						Serial.println("DO2设定的时间到了呀");
					}
					digitalWrite(DO2, LOW);
					Out_State[i] = Stateless;

					//将所有的设定时间，已工作时间，剩余时间清零
					duration[i] = 0x00;
					CurrentWorkSec[i] = 0x00;
					remaining[i] = 0x00;
					DO2_SetWorkSec1 = 0x00;
					DO2_SetWorkSec2 = 0x00;
					DO2_SetWorkSec3 = 0x00;
					DO2_CurrentWorkSec1 = 0x00;
					DO2_CurrentWorkSec2 = 0x00;
					DO2_CurrentWorkSec3 = 0x00;
					DO2_RemainWorkSec1 = 0x00;
					DO2_RemainWorkSec2 = 0x00;
					DO2_RemainWorkSec3 = 0x00;

					//进行已经关闭状态的回执
					Send_E021(Receive_IsBroadcast);//各路数状态的回执
					Send_E022(Receive_IsBroadcast);//各路数时间的回执
				}
				break;

				/*状态：DO3开
				*在此状态中需要不断检测接收的值，
				*接收到值后进行判断进入下一个状态。*/
			case DO3_ON:
				//--------------------------------------
				if (debug == 1)
				{
					delay(500);
					if (debug_print == 1)
					{
						Serial.print(i);
						Serial.println("进入case：DO3_ON");
					}
				}
				//--------------------------------------
				digitalWrite(KCZJ1, LOW);

				CurrentWorkSec[i] = (millis() - ot[i]) / 1000;//得到DO3的已工作时长
				remaining[i] = (duration[i] > CurrentWorkSec[i]) ? (duration[i] - CurrentWorkSec[i]) : 0;//得到DO3的剩余工作时长
				if (debug_print == 1)
				{
					//Serial.println(String("DO3的设定工作时长 = ") + duration[i]);
					//Serial.println(String("DO3的已工作时长 = ") + CurrentWorkSec[i]);
					//Serial.println(String("DO3的剩余工作时长 = ") + remaining[i]);
				}
				//-----------------------------------这一段代码将已工作的数值拆位-------------------------------------------------------------------------------
				if (duration[i] <= 0xFF)
				{
					DO3_SetWorkSec1 = 0x00;
					DO3_SetWorkSec2 = 0x00;
					DO3_SetWorkSec3 = duration[i];
				}
				else if (duration[i] > 0xFF && duration[i] <= 0xFFFF)
				{
					DO3_SetWorkSec1 = 0x00;
					DO3_SetWorkSec2 = duration[i] / 0x100;
					DO3_SetWorkSec3 = (duration[i] - DO3_SetWorkSec2 * 0x100);
				}
				else if (duration[i] > 0xFFFF)
				{
					DO3_SetWorkSec1 = duration[i] / 0x10000;
					DO3_SetWorkSec2 = duration[i] - (DO3_SetWorkSec1 * 0x10000) / 0x100;
					DO3_SetWorkSec3 = duration[i] - (DO3_SetWorkSec1 * 0x10000) - (DO3_SetWorkSec2 * 0x100);
				}
				else
				{
					Serial.println("读取DO3设定工作时间错误");
					//这里应该需要回执错误？？？
				}

				if (CurrentWorkSec[i] <= 0xFF)
				{
					DO3_CurrentWorkSec1 = 0x00;
					DO3_CurrentWorkSec2 = 0x00;
					DO3_CurrentWorkSec3 = CurrentWorkSec[i];
				}
				else if (CurrentWorkSec[i] > 0xFF && CurrentWorkSec[i] <= 0xFFFF)
				{
					DO3_CurrentWorkSec1 = 0x00;
					DO3_CurrentWorkSec2 = CurrentWorkSec[i] / 0x100;
					DO3_CurrentWorkSec3 = (CurrentWorkSec[i] - DO3_CurrentWorkSec2 * 0x100);
				}
				else if (CurrentWorkSec[i] > 0xFFFF)
				{
					DO3_CurrentWorkSec1 = CurrentWorkSec[i] / 0x10000;
					DO3_CurrentWorkSec2 = CurrentWorkSec[i] - (DO3_CurrentWorkSec1 * 0x10000) / 0x100;
					DO3_CurrentWorkSec3 = CurrentWorkSec[i] - (DO3_CurrentWorkSec1 * 0x10000) - (DO3_CurrentWorkSec2 * 0x100);
				}
				else
				{
					Serial.println("读取DO3已工作时间错误");
					//这里应该需要回执错误？？？
				}

				if (remaining[i] <= 0xFF)
				{
					DO3_RemainWorkSec1 = 0x00;
					DO3_RemainWorkSec2 = 0x00;
					DO3_RemainWorkSec3 = remaining[i];
				}
				else if (remaining[i] > 0xFF && remaining[i] <= 0xFFFF)
				{
					DO3_RemainWorkSec1 = 0x00;
					DO3_RemainWorkSec2 = remaining[i] / 0x100;
					DO3_RemainWorkSec3 = (remaining[i] - DO3_RemainWorkSec2 * 0x100);
				}
				else if (remaining[i] > 0xFFFF)
				{
					DO3_RemainWorkSec1 = remaining[i] / 0x10000;
					DO3_RemainWorkSec2 = remaining[i] - (DO3_RemainWorkSec1 * 0x10000) / 0x100;
					DO3_RemainWorkSec3 = remaining[i] - (DO3_RemainWorkSec1 * 0x10000) - (DO3_RemainWorkSec2 * 0x100);
				}
				else
				{
					Serial.println("读取DO3剩余工作时间错误");
					//这里应该需要回执错误？？？
				}

				if (debug_print == 1)
				{
					//Serial.println(String("已工作时间拆位结果为：") + DO3_CurrentWorkSec1 + "/" + DO3_CurrentWorkSec2 + "/" + DO3_CurrentWorkSec3);
					//Serial.println(String("剩余工作时间拆位结果为：") + DO3_RemainWorkSec1 + "/" + DO3_RemainWorkSec2 + "/" + DO3_RemainWorkSec3);
					if (debug == 1)
					{
						delay(500);
					}
				}
				//-------------------------------------------------------------------------------------------------------------------------------------------


				if (millis() - ot[i] >= duration[i] * 1000)
				{
					//时间到了需要清空这个数组的东西
					if (debug_print == 1)
					{
						Serial.println("DO3设定的时间到了呀");
					}
					digitalWrite(KCZJ1, HIGH);
					Out_State[i] = Stateless;

					//将所有的设定时间，已工作时间，剩余时间清零
					duration[i] = 0x00;
					CurrentWorkSec[i] = 0x00;
					remaining[i] = 0x00;
					DO3_SetWorkSec1 = 0x00;
					DO3_SetWorkSec2 = 0x00;
					DO3_SetWorkSec3 = 0x00;
					DO3_CurrentWorkSec1 = 0x00;
					DO3_CurrentWorkSec2 = 0x00;
					DO3_CurrentWorkSec3 = 0x00;
					DO3_RemainWorkSec1 = 0x00;
					DO3_RemainWorkSec2 = 0x00;
					DO3_RemainWorkSec3 = 0x00;

					//进行已经关闭状态的回执
					Send_E021(Receive_IsBroadcast);//各路数状态的回执
					Send_E022(Receive_IsBroadcast);//各路数时间的回执
				}
				break;

				/*状态：DO4开
				*在此状态中需要不断检测接收的值，
				*接收到值后进行判断进入下一个状态。*/
			case DO4_ON:
				//--------------------------------------
				if (debug == 1)
				{
					delay(500);
					if (debug_print == 1)
					{
						Serial.print(i);
						Serial.println("进入case：DO4_ON");
					}
				}
				//--------------------------------------
				digitalWrite(KCZJ2, LOW);

				CurrentWorkSec[i] = (millis() - ot[i]) / 1000;//得到DO4的已工作时长
				remaining[i] = (duration[i] > CurrentWorkSec[i]) ? (duration[i] - CurrentWorkSec[i]) : 0;//得到DO4的剩余工作时长
				if (debug_print == 1)
				{
					//Serial.println(String("DO4的设定工作时长 = ") + duration[i]);
					//Serial.println(String("DO4的已工作时长 = ") + CurrentWorkSec[i]);
					//Serial.println(String("DO4的剩余工作时长 = ") + remaining[i]);
				}
				//-----------------------------------这一段代码将已工作的数值拆位-------------------------------------------------------------------------------
				if (duration[i] <= 0xFF)
				{
					DO4_SetWorkSec1 = 0x00;
					DO4_SetWorkSec2 = 0x00;
					DO4_SetWorkSec3 = duration[i];
				}
				else if (duration[i] > 0xFF && duration[i] <= 0xFFFF)
				{
					DO4_SetWorkSec1 = 0x00;
					DO4_SetWorkSec2 = duration[i] / 0x100;
					DO4_SetWorkSec3 = (duration[i] - DO4_SetWorkSec2 * 0x100);
				}
				else if (duration[i] > 0xFFFF)
				{
					DO4_SetWorkSec1 = duration[i] / 0x10000;
					DO4_SetWorkSec2 = duration[i] - (DO4_SetWorkSec1 * 0x10000) / 0x100;
					DO4_SetWorkSec3 = duration[i] - (DO4_SetWorkSec1 * 0x10000) - (DO4_SetWorkSec2 * 0x100);
				}
				else
				{
					Serial.println("读取DO4设定工作时间错误");
					//这里应该需要回执错误？？？
				}

				if (CurrentWorkSec[i] <= 0xFF)
				{
					DO4_CurrentWorkSec1 = 0x00;
					DO4_CurrentWorkSec2 = 0x00;
					DO4_CurrentWorkSec3 = CurrentWorkSec[i];
				}
				else if (CurrentWorkSec[i] > 0xFF && CurrentWorkSec[i] <= 0xFFFF)
				{
					DO4_CurrentWorkSec1 = 0x00;
					DO4_CurrentWorkSec2 = CurrentWorkSec[i] / 0x100;
					DO4_CurrentWorkSec3 = (CurrentWorkSec[i] - DO4_CurrentWorkSec2 * 0x100);
				}
				else if (CurrentWorkSec[i] > 0xFFFF)
				{
					DO4_CurrentWorkSec1 = CurrentWorkSec[i] / 0x10000;
					DO4_CurrentWorkSec2 = CurrentWorkSec[i] - (DO4_CurrentWorkSec1 * 0x10000) / 0x100;
					DO4_CurrentWorkSec3 = CurrentWorkSec[i] - (DO4_CurrentWorkSec1 * 0x10000) - (DO4_CurrentWorkSec2 * 0x100);
				}
				else
				{
					Serial.println("读取DO4已工作时间错误");
					//这里应该需要回执错误？？？
				}

				if (remaining[i] <= 0xFF)
				{
					DO4_RemainWorkSec1 = 0x00;
					DO4_RemainWorkSec2 = 0x00;
					DO4_RemainWorkSec3 = remaining[i];
				}
				else if (remaining[i] > 0xFF && remaining[i] <= 0xFFFF)
				{
					DO4_RemainWorkSec1 = 0x00;
					DO4_RemainWorkSec2 = remaining[i] / 0x100;
					DO4_RemainWorkSec3 = (remaining[i] - DO4_RemainWorkSec2 * 0x100);
				}
				else if (remaining[i] > 0xFFFF)
				{
					DO4_RemainWorkSec1 = remaining[i] / 0x10000;
					DO4_RemainWorkSec2 = remaining[i] - (DO4_RemainWorkSec1 * 0x10000) / 0x100;
					DO4_RemainWorkSec3 = remaining[i] - (DO4_RemainWorkSec1 * 0x10000) - (DO4_RemainWorkSec2 * 0x100);
				}
				else
				{
					Serial.println("读取DO4剩余工作时间错误");
					//这里应该需要回执错误？？？
				}

				if (debug_print == 1)
				{
					//Serial.println(String("已工作时间拆位结果为：") + DO4_CurrentWorkSec1 + "/" + DO4_CurrentWorkSec2 + "/" + DO4_CurrentWorkSec3);
					//Serial.println(String("剩余工作时间拆位结果为：") + DO4_RemainWorkSec1 + "/" + DO4_RemainWorkSec2 + "/" + DO4_RemainWorkSec3);
					if (debug == 1)
					{
						delay(500);
					}
				}
				//-------------------------------------------------------------------------------------------------------------------------------------------


				if (millis() - ot[i] >= duration[i] * 1000)
				{
					//时间到了需要清空这个数组的东西
					if (debug_print == 1)
					{
						Serial.println("DO4设定的时间到了呀");
					}
					digitalWrite(KCZJ2, HIGH);
					Out_State[i] = Stateless;

					//将所有的设定时间，已工作时间，剩余时间清零
					duration[i] = 0x00;
					CurrentWorkSec[i] = 0x00;
					remaining[i] = 0x00;
					DO4_SetWorkSec1 = 0x00;
					DO4_SetWorkSec2 = 0x00;
					DO4_SetWorkSec3 = 0x00;
					DO4_CurrentWorkSec1 = 0x00;
					DO4_CurrentWorkSec2 = 0x00;
					DO4_CurrentWorkSec3 = 0x00;
					DO4_RemainWorkSec1 = 0x00;
					DO4_RemainWorkSec2 = 0x00;
					DO4_RemainWorkSec3 = 0x00;

					//进行已经关闭状态的回执
					Send_E021(Receive_IsBroadcast);//各路数状态的回执
					Send_E022(Receive_IsBroadcast);//各路数时间的回执
				}
				break;

				/*状态：AO1开
				*在此状态中需要不断检测接收的值，
				*接收到值后进行判断进入下一个状态。*/
			case AO1_ON:
				//--------------------------------------
				if (debug == 1)
				{
					delay(500);
					if (debug_print == 1)
					{
						Serial.print(i);
						Serial.println("进入case：AO1_ON");
					}
				}
				//--------------------------------------
				analogWrite(AO1, Analog_Value1);

				CurrentWorkSec[i] = (millis() - ot[i]) / 1000;//得到AO1的已工作时长
				remaining[i] = (duration[i] > CurrentWorkSec[i]) ? (duration[i] - CurrentWorkSec[i]) : 0;//得到AO的剩余工作时长
				if (debug_print == 1)
				{
					//Serial.println(String("AO1的设定工作时长 = ") + duration[i]);
					//Serial.println(String("AO1的已工作时长 = ") + CurrentWorkSec[i]);
					//Serial.println(String("AO1的剩余工作时长 = ") + remaining[i]);
				}
				//-----------------------------------这一段代码将已工作的数值拆位-------------------------------------------------------------------------------
				if (duration[i] <= 0xFF)
				{
					AO1_SetWorkSec1 = 0x00;
					AO1_SetWorkSec2 = 0x00;
					AO1_SetWorkSec3 = duration[i];
				}
				else if (duration[i] > 0xFF && duration[i] <= 0xFFFF)
				{
					AO1_SetWorkSec1 = 0x00;
					AO1_SetWorkSec2 = duration[i] / 0x100;
					AO1_SetWorkSec3 = (duration[i] - AO1_SetWorkSec2 * 0x100);
				}
				else if (duration[i] > 0xFFFF)
				{
					AO1_SetWorkSec1 = duration[i] / 0x10000;
					AO1_SetWorkSec2 = duration[i] - (AO1_SetWorkSec1 * 0x10000) / 0x100;
					AO1_SetWorkSec3 = duration[i] - (AO1_SetWorkSec1 * 0x10000) - (AO1_SetWorkSec2 * 0x100);
				}
				else
				{
					Serial.println("读取AO1设定工作时间错误");
					//这里应该需要回执错误？？？
				}

				if (CurrentWorkSec[i] <= 0xFF)
				{
					AO1_CurrentWorkSec1 = 0x00;
					AO1_CurrentWorkSec2 = 0x00;
					AO1_CurrentWorkSec3 = CurrentWorkSec[i];
				}
				else if (CurrentWorkSec[i] > 0xFF && CurrentWorkSec[i] <= 0xFFFF)
				{
					AO1_CurrentWorkSec1 = 0x00;
					AO1_CurrentWorkSec2 = CurrentWorkSec[i] / 0x100;
					AO1_CurrentWorkSec3 = (CurrentWorkSec[i] - AO1_CurrentWorkSec2 * 0x100);
				}
				else if (CurrentWorkSec[i] > 0xFFFF)
				{
					AO1_CurrentWorkSec1 = CurrentWorkSec[i] / 0x10000;
					AO1_CurrentWorkSec2 = CurrentWorkSec[i] - (AO1_CurrentWorkSec1 * 0x10000) / 0x100;
					AO1_CurrentWorkSec3 = CurrentWorkSec[i] - (AO1_CurrentWorkSec1 * 0x10000) - (AO1_CurrentWorkSec2 * 0x100);
				}
				else
				{
					Serial.println("读取AO1已工作时间错误");
					//这里应该需要回执错误？？？
				}

				if (remaining[i] <= 0xFF)
				{
					AO1_RemainWorkSec1 = 0x00;
					AO1_RemainWorkSec2 = 0x00;
					AO1_RemainWorkSec3 = remaining[i];
				}
				else if (remaining[i] > 0xFF && remaining[i] <= 0xFFFF)
				{
					AO1_RemainWorkSec1 = 0x00;
					AO1_RemainWorkSec2 = remaining[i] / 0x100;
					AO1_RemainWorkSec3 = (remaining[i] - AO1_RemainWorkSec2 * 0x100);
				}
				else if (remaining[i] > 0xFFFF)
				{
					AO1_RemainWorkSec1 = remaining[i] / 0x10000;
					AO1_RemainWorkSec2 = remaining[i] - (AO1_RemainWorkSec1 * 0x10000) / 0x100;
					AO1_RemainWorkSec3 = remaining[i] - (AO1_RemainWorkSec1 * 0x10000) - (AO1_RemainWorkSec2 * 0x100);
				}
				else
				{
					Serial.println("读取AO1剩余工作时间错误");
					//这里应该需要回执错误？？？
				}

				if (debug_print == 1)
				{
					//Serial.println(String("已工作时间拆位结果为：") + AO1_CurrentWorkSec1 + "/" + AO1_CurrentWorkSec2 + "/" + AO1_CurrentWorkSec3);
					//Serial.println(String("剩余工作时间拆位结果为：") + AO1_RemainWorkSec1 + "/" + AO1_RemainWorkSec2 + "/" + AO1_RemainWorkSec3);
					if (debug == 1)
					{
						delay(500);
					}
				}
				//-------------------------------------------------------------------------------------------------------------------------------------------


				if (millis() - ot[i] >= duration[i] * 1000)
				{
					//时间到了需要清空这个数组的东西
					if (debug_print == 1)
					{
						Serial.println("AO1设定的时间到了呀");
					}
					analogWrite(AO1, 0);
					Out_State[i] = Stateless;

					//将所有的设定时间，已工作时间，剩余时间清零
					duration[i] = 0x00;
					CurrentWorkSec[i] = 0x00;
					remaining[i] = 0x00;
					AO1_SetWorkSec1 = 0x00;
					AO1_SetWorkSec2 = 0x00;
					AO1_SetWorkSec3 = 0x00;
					AO1_CurrentWorkSec1 = 0x00;
					AO1_CurrentWorkSec2 = 0x00;
					AO1_CurrentWorkSec3 = 0x00;
					AO1_RemainWorkSec1 = 0x00;
					AO1_RemainWorkSec2 = 0x00;
					AO1_RemainWorkSec3 = 0x00;

					//进行已经关闭状态的回执
					Send_E021(Receive_IsBroadcast);//各路数状态的回执
					Send_E022(Receive_IsBroadcast);//各路数时间的回执
				}
				break;

				/*状态：AO2开
				*在此状态中需要不断检测接收的值，
				*接收到值后进行判断进入下一个状态。*/
			case AO2_ON:
				//--------------------------------------
				if (debug == 1)
				{
					delay(500);
					if (debug_print == 1)
					{
						Serial.print(i);
						Serial.println("进入case：AO2_ON");
					}
				}
				//--------------------------------------
				analogWrite(AO2, Analog_Value2);

				CurrentWorkSec[i] = (millis() - ot[i]) / 1000;//得到AO2的已工作时长
				remaining[i] = (duration[i] > CurrentWorkSec[i]) ? (duration[i] - CurrentWorkSec[i]) : 0;//得到AO2的剩余工作时长
				if (debug_print == 1)
				{
					//Serial.println(String("AO2的设定工作时长 = ") + duration[i]);
					//Serial.println(String("AO2的已工作时长 = ") + CurrentWorkSec[i]);
					//Serial.println(String("AO2的剩余工作时长 = ") + remaining[i]);
				}
				//-----------------------------------这一段代码将已工作的数值拆位-------------------------------------------------------------------------------
				if (duration[i] <= 0xFF)
				{
					AO2_SetWorkSec1 = 0x00;
					AO2_SetWorkSec2 = 0x00;
					AO2_SetWorkSec3 = duration[i];
				}
				else if (duration[i] > 0xFF && duration[i] <= 0xFFFF)
				{
					AO2_SetWorkSec1 = 0x00;
					AO2_SetWorkSec2 = duration[i] / 0x100;
					AO2_SetWorkSec3 = (duration[i] - AO2_SetWorkSec2 * 0x100);
				}
				else if (duration[i] > 0xFFFF)
				{
					AO2_SetWorkSec1 = duration[i] / 0x10000;
					AO2_SetWorkSec2 = duration[i] - (AO2_SetWorkSec1 * 0x10000) / 0x100;
					AO2_SetWorkSec3 = duration[i] - (AO2_SetWorkSec1 * 0x10000) - (AO2_SetWorkSec2 * 0x100);
				}
				else
				{
					Serial.println("读取AO2设定工作时间错误");
					//这里应该需要回执错误？？？
				}

				if (CurrentWorkSec[i] <= 0xFF)
				{
					AO2_CurrentWorkSec1 = 0x00;
					AO2_CurrentWorkSec2 = 0x00;
					AO2_CurrentWorkSec3 = CurrentWorkSec[i];
				}
				else if (CurrentWorkSec[i] > 0xFF && CurrentWorkSec[i] <= 0xFFFF)
				{
					AO2_CurrentWorkSec1 = 0x00;
					AO2_CurrentWorkSec2 = CurrentWorkSec[i] / 0x100;
					AO2_CurrentWorkSec3 = (CurrentWorkSec[i] - AO2_CurrentWorkSec2 * 0x100);
				}
				else if (CurrentWorkSec[i] > 0xFFFF)
				{
					AO2_CurrentWorkSec1 = CurrentWorkSec[i] / 0x10000;
					AO2_CurrentWorkSec2 = CurrentWorkSec[i] - (AO2_CurrentWorkSec1 * 0x10000) / 0x100;
					AO2_CurrentWorkSec3 = CurrentWorkSec[i] - (AO2_CurrentWorkSec1 * 0x10000) - (AO2_CurrentWorkSec2 * 0x100);
				}
				else
				{
					Serial.println("读取AO2已工作时间错误");
					//这里应该需要回执错误？？？
				}

				if (remaining[i] <= 0xFF)
				{
					AO2_RemainWorkSec1 = 0x00;
					AO2_RemainWorkSec2 = 0x00;
					AO2_RemainWorkSec3 = remaining[i];
				}
				else if (remaining[i] > 0xFF && remaining[i] <= 0xFFFF)
				{
					AO2_RemainWorkSec1 = 0x00;
					AO2_RemainWorkSec2 = remaining[i] / 0x100;
					AO2_RemainWorkSec3 = (remaining[i] - AO2_RemainWorkSec2 * 0x100);
				}
				else if (remaining[i] > 0xFFFF)
				{
					AO2_RemainWorkSec1 = remaining[i] / 0x10000;
					AO2_RemainWorkSec2 = remaining[i] - (AO2_RemainWorkSec1 * 0x10000) / 0x100;
					AO2_RemainWorkSec3 = remaining[i] - (AO2_RemainWorkSec1 * 0x10000) - (AO2_RemainWorkSec2 * 0x100);
				}
				else
				{
					Serial.println("读取AO2剩余工作时间错误");
					//这里应该需要回执错误？？？
				}

				if (debug_print == 1)
				{
					//Serial.println(String("已工作时间拆位结果为：") + AO2_CurrentWorkSec1 + "/" + AO2_CurrentWorkSec2 + "/" + AO2_CurrentWorkSec3);
					//Serial.println(String("剩余工作时间拆位结果为：") + AO2_RemainWorkSec1 + "/" + AO2_RemainWorkSec2 + "/" + AO2_RemainWorkSec3);
					if (debug == 1)
					{
						delay(500);
					}
				}
				//-------------------------------------------------------------------------------------------------------------------------------------------


				if (millis() - ot[i] >= duration[i] * 1000)
				{
					//时间到了需要清空这个数组的东西
					if (debug_print == 1)
					{
						Serial.println("AO2设定的时间到了呀");
					}
					analogWrite(AO2, 0);
					Out_State[i] = Stateless;

					//将所有的设定时间，已工作时间，剩余时间清零
					duration[i] = 0x00;
					CurrentWorkSec[i] = 0x00;
					remaining[i] = 0x00;
					AO2_SetWorkSec1 = 0x00;
					AO2_SetWorkSec2 = 0x00;
					AO2_SetWorkSec3 = 0x00;
					AO2_CurrentWorkSec1 = 0x00;
					AO2_CurrentWorkSec2 = 0x00;
					AO2_CurrentWorkSec3 = 0x00;
					AO2_RemainWorkSec1 = 0x00;
					AO2_RemainWorkSec2 = 0x00;
					AO2_RemainWorkSec3 = 0x00;

					//进行已经关闭状态的回执
					Send_E021(Receive_IsBroadcast);//各路数状态的回执
					Send_E022(Receive_IsBroadcast);//各路数时间的回执
				}
				break;

			default:
				//--------------------------------------
				delay(500);
				Serial.println("Instruction error指令错误");
				//--------------------------------------
				break;
			}
		}
	}
}


//函 数 名：Allclose() 
//功能描述：状态值全关函数
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
void Allclose()
{
	//将4路关的状态值写入
	out_state = Stateless;
	Out_State[0] = out_state;
	Out_State[1] = out_state;
	Out_State[2] = out_state;
	Out_State[3] = out_state;
	Out_State[4] = out_state;
	Out_State[5] = out_state;
	digitalWrite(DO1, LOW);
	digitalWrite(DO2, LOW);
	digitalWrite(KCZJ1, HIGH);
	digitalWrite(KCZJ2, HIGH);
	analogWrite(AO1, 0);
	analogWrite(AO2, 0);


	//将所有的设定时间，已工作时间，剩余时间清零
	for (size_t i = 0; i < 6; i++)
	{
		duration[i] = 0x00;
		CurrentWorkSec[i] = 0x00;
		remaining[i] = 0x00;

	}
	DO1_SetWorkSec1 = 0x00;
	DO1_SetWorkSec2 = 0x00;
	DO1_SetWorkSec3 = 0x00;
	DO1_CurrentWorkSec1 = 0x00;
	DO1_CurrentWorkSec2 = 0x00;
	DO1_CurrentWorkSec3 = 0x00;
	DO1_RemainWorkSec1 = 0x00;
	DO1_RemainWorkSec2 = 0x00;
	DO1_RemainWorkSec3 = 0x00;

	DO2_SetWorkSec1 = 0x00;
	DO2_SetWorkSec2 = 0x00;
	DO2_SetWorkSec3 = 0x00;
	DO2_CurrentWorkSec1 = 0x00;
	DO2_CurrentWorkSec2 = 0x00;
	DO2_CurrentWorkSec3 = 0x00;
	DO2_RemainWorkSec1 = 0x00;
	DO2_RemainWorkSec2 = 0x00;
	DO2_RemainWorkSec3 = 0x00;

	DO3_SetWorkSec1 = 0x00;
	DO3_SetWorkSec2 = 0x00;
	DO3_SetWorkSec3 = 0x00;
	DO3_CurrentWorkSec1 = 0x00;
	DO3_CurrentWorkSec2 = 0x00;
	DO3_CurrentWorkSec3 = 0x00;
	DO3_RemainWorkSec1 = 0x00;
	DO3_RemainWorkSec2 = 0x00;
	DO3_RemainWorkSec3 = 0x00;

	DO4_SetWorkSec1 = 0x00;
	DO4_SetWorkSec2 = 0x00;
	DO4_SetWorkSec3 = 0x00;
	DO4_CurrentWorkSec1 = 0x00;
	DO4_CurrentWorkSec2 = 0x00;
	DO4_CurrentWorkSec3 = 0x00;
	DO4_RemainWorkSec1 = 0x00;
	DO4_RemainWorkSec2 = 0x00;
	DO4_RemainWorkSec3 = 0x00;

	AO1_SetWorkSec1 = 0x00;
	AO1_SetWorkSec2 = 0x00;
	AO1_SetWorkSec3 = 0x00;
	AO1_CurrentWorkSec1 = 0x00;
	AO1_CurrentWorkSec2 = 0x00;
	AO1_CurrentWorkSec3 = 0x00;
	AO1_RemainWorkSec1 = 0x00;
	AO1_RemainWorkSec2 = 0x00;
	AO1_RemainWorkSec3 = 0x00;

	AO2_SetWorkSec1 = 0x00;
	AO2_SetWorkSec2 = 0x00;
	AO2_SetWorkSec3 = 0x00;
	AO2_CurrentWorkSec1 = 0x00;
	AO2_CurrentWorkSec2 = 0x00;
	AO2_CurrentWorkSec3 = 0x00;
	AO2_RemainWorkSec1 = 0x00;
	AO2_RemainWorkSec2 = 0x00;
	AO2_RemainWorkSec3 = 0x00;

	if (debug_print == 1)
	{
		Serial.println("数字输出全关");
	}

	if (Out_State[0] == Stateless && Out_State[1] == Stateless &&
		Out_State[2] == Stateless && Out_State[3] == Stateless &&
		Out_State[4] == Stateless && Out_State[5] == Stateless)
	{
		E015_status = SetParamsOk;
	}
	else
	{
		E015_status = SetParamsErr;
	}

	//是否广播指令
	Receive_IsBroadcast = Judgement_Data[6];

	//进行状态的回执
	Send_E015(Receive_IsBroadcast, E015_status);

	forswitch();
}

//函 数 名：int data_processing(String AssStat)
//功能描述：数据处理函数，分割#,分成condition，implement
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
int data_processing(String AssStat)
{
	String AssStat_dp = AssStat;
	if (debug_print == 1)
	{
		Serial.println("data_processing:");
	}
	condition_1 = AssStat.substring(0, AssStat.indexOf("#"));//截取#前的语句，为条件语句condition_1
	implement_1 = AssStat.substring(AssStat.indexOf("#") + 1, AssStat.length());//截取#前的语句，为执行语句implement_1

	if (debug_print == 1)
	{
		Serial.println(String("condition_1: ") + condition_1);
		Serial.println(String("implement_1: ") + implement_1);
		Serial.flush();
	}

	//将condition_1传入处理判断语句的函数，返回值赋给ret_condition_test
	int ret_condition_test = condition_test(condition_1);
	if (debug_print == 1)
	{
		Serial.println(String("condition_test() = ") + ret_condition_test);
	}

	if (debug_print == 1)
	{
		array_print_test();//数组打印输出
	}

	//定义一个存放返回值的数组，0代表假，1代表真，2代表与，3代表或
	int Return_value[5];

	//这里的for循环是为了处理条件语句块的真假
	for (size_t i = 0; i < ret_condition_test; i++)
	{
		LORA_Receive_information();	//LORA的接收函数

		//将条件判断函数Condition_Judgment的返回值传入返回值数组Return_value[]
		//0代表假，1代表真，2代表与，3代表或
		Return_value[i] = Condition_Judgment(i, ret_condition_test);

		if (debug_print == 1)
		{
			Serial.println("========");
			Serial.println(String("Return_value[") + i + "]=" + Return_value[i]);
			Serial.println("========");
		}
	}

	if (debug_print == 1)
	{
		ret_condition_test = 3;
		Return_value[0] = 1;//真
		Return_value[1] = 2;//与
		Return_value[2] = 1;//真
		Return_value[3] = 2;//与
		Return_value[4] = 1;//真

		Serial.println("--------");
		for (size_t i = 0; i < 5; i++)
		{
			Serial.println(String("Return_value[") + i + "]=" + Return_value[i]);
		}
		Serial.println("--------");
	}

	//这里就是判断与，或逻辑条件是否成立
	if (ret_condition_test == 0)
	{
		if (debug_print == 1)
		{
			Serial.println("ret_condition_test == 0");
		}

		if (Return_value[0] == 1)
		{
			Serial.println("Return_value[0] == 1");
		}
		else
		{
			return 0;
		}
	}
	else if (ret_condition_test == 3)
	{
		if (debug_print == 1)
		{
			Serial.println("ret_condition_test == 3");
		}

		if (Return_value[1] == 2)//判断为与
		{
			if (Return_value[0] == 1 && Return_value[2] == 1)
			{
				Serial.println("Return_value[0] == 1 && Return_value[2] == 1");
			}
			else
			{
				return 0;
			}
		}
		else if (Return_value[1] == 3)//判断为或
		{
			if (Return_value[0] == 1 || Return_value[2] == 1)
			{
				Serial.println("Return_value[0] == 1 || Return_value[2] == 1");
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return 0;
		}
	}
	else if (ret_condition_test == 5)
	{
		if (debug_print == 1)
		{
			Serial.println("ret_condition_test == 5");
		}

		if (Return_value[1] == 2)//判断为与
		{
			if (Return_value[3] == 2)//判断为与
			{
				if (Return_value[0] == 1 && Return_value[2] == 1 && Return_value[4] == 1)
				{
					Serial.println("Return_value[0] == 1 && Return_value[2] == 1 && Return_value[5] == 1");
				}
				else
				{
					return 0;
				}
			}
			else if (Return_value[3] == 3)//判断为或
			{
				if (Return_value[0] == 1 && Return_value[2] == 1 || Return_value[4] == 1)
				{
					Serial.println("Return_value[0] == 1 && Return_value[2] == 1 && Return_value[5] == 1");
				}
				else
				{
					return 0;
				}
			}

		}
		else if (Return_value[1] == 3)//判断为或
		{
			if (Return_value[3] == 2)//判断为与
			{
				if (Return_value[0] == 1 || Return_value[2] == 1 && Return_value[4] == 1)
				{
					Serial.println("Return_value[0] == 1 && Return_value[2] == 1 && Return_value[5] == 1");
				}
				else
				{
					return 0;
				}
			}
			else if (Return_value[3] == 3)//判断为或
			{
				if (Return_value[0] == 1 || Return_value[2] == 1 || Return_value[4] == 1)
				{
					Serial.println("Return_value[0] == 1 && Return_value[2] == 1 && Return_value[5] == 1");
				}
				else
				{
					return 0;
				}
			}
			else
			{
				return 0;
			}
		}
	}

	//输出这里表示逻辑成立
	Serial.println("逻辑关系成立！！！");

	//implement_test(implement_1);//将implement_1执行语句传入处理执行语句的函数
	int ret_implement_test = implement_test(implement_1);//得到执行语句的语句段数

	if (debug_print == 1)
	{
		Serial.println(String("ret_implement_test = ") + ret_implement_test);
	}

	//这里的for循环是为了去执行 执行语句。
	for (size_t i = 0; i < ret_implement_test; i++)
	{
		LORA_Receive_information();	//LORA的接收函数

		if (Implement_Handle(i, ret_implement_test) == 0)
		{
			//这里应该有错误处理
		}
		//Implement_Handle(i, ret_implement_test);
	}


	//------------------------------------------------
	//------这里应该需要将所有的数组清零，防止下次冲突-------
	array_empty_test();//数组清空函数
	//------这里应该需要将所有的数组清零，防止下次冲突-------
	//------------------------------------------------

	if (debug_print == 1)
	{
		array_print_test();
	}
	return 0;
}

//函 数 名：int condition_test(String con1)
//功能描述：条件语句分割的函数
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：条件语句的语句段数
/////////////////////////////////////////////////////////////////////
int condition_test(String condition_1)
{
	String con_1 = condition_1;//condition_1的备份
	String CON[5];//条件语句块数组
	String coni;//CON[i]的备份
	int semicolon_num_con = 0;//分号的个数
	int comma_num_con = 0;//逗号的个数 
	int for_num1_con = 0, for_num2_con = 0;//
	//----------------------------------------


	semicolon_num_con = 0;//将分号个数清零

	//得到分号;的个数
	for (size_t i = 0; i < con_1.length(); i++)
	{
		LORA_Receive_information();	//LORA的接收函数

		if (con_1.indexOf(";") != -1)
		{
			con_1 = con_1.substring(con_1.indexOf(";") + 1, con_1.length());
			Serial.println(String("con1: ") + con_1);
			semicolon_num_con++;
		}
		else
		{
			//Serial.println("没有分号;");
		}
	}

	if (debug_print == 1)
	{
		Serial.println("分号个数semicolon_num = " + String(semicolon_num_con));
	}

	for_num1_con = 0;

	//通过分号的个数判断需要截取几段
	if (semicolon_num_con == 0)
	{
		for_num1_con = 0;
		//---------------------------------------------------
		//因为当fornum1 = 0时，后面的循环体不执行，所以需要单独写出来
		CON[0] = condition_1;
		coni = CON[0];//CON[i]的备份
		Serial.println(String("CON[0]: ") + CON[0]);

		//将con[i]拆分成coni[i]
		for (size_t i = 0; i < CON[0].length(); i++)
		{
			LORA_Receive_information();	//LORA的接收函数

			//得到逗号,的个数comma_num
			if (CON[i_0].indexOf(",") != -1)
			{
				/*coni_i[i] = coni.substring(coni.indexOf(",") + 1, coni.length());
				Serial.println(String("coni_ ") + i + " :  " + coni_i[i]);*/
				CON[i_0].remove(0, CON[i_0].indexOf(",") + 1);//将CON[i]删减一部分
				//Serial.println(con[i]);
				comma_num_con++;
			}
			else
			{
				//Serial.println("没有逗号,");
			}
		}
		if (debug_print == 1)
		{
			Serial.println(String("逗号个数comma_num = ") + comma_num_con);
		}

		for_num2_con = 0;

		//通过分号的个数判断需要截取几段
		if (comma_num_con == 0)
		{
			for_num2_con = 0;
		}
		else if (comma_num_con == 2)
		{
			for_num2_con = 3;
		}
		else if (comma_num_con == 4)
		{
			for_num2_con = 5;
		}
		else
		{
			Serial.println("超出个数");
		}

		if (debug_print == 1)
		{
			Serial.println(String("fornum2 = ") + for_num2_con);
		}

		for (size_t i = 0; i < for_num2_con; i++)
		{
			LORA_Receive_information();	//LORA的接收函数

			con0[i] = coni.substring(0, coni.indexOf(","));
			if (debug_print == 1)
			{
				Serial.println(String("con0[ ") + i + " ]:  " + con0[i]);//输出第一条判断语句
			}
			coni.remove(0, coni.indexOf(",") + 1);//将con1删减一部分
		}
		Serial.println("");

		//---------------------------------------------------
	}
	else if (semicolon_num_con == 2)
	{
		for_num1_con = 3;
	}
	else if (semicolon_num_con == 4)
	{
		for_num1_con = 5;
	}
	else
	{
		Serial.println("超出个数");
	}

	if (debug_print == 1)
	{
		Serial.println("for_num1 = " + String(for_num1_con));
	}

	//截取段数，并且输出
	for (i_0 = 0; i_0 < for_num1_con; i_0++)
	{
		LORA_Receive_information();	//LORA的接收函数

		CON[i_0] = condition_1.substring(0, condition_1.indexOf(";"));//截取出CON[i]
		coni = CON[i_0];//CON[i]的备份
		if (debug_print == 1)
		{
			Serial.println(String("CON[ ") + i_0 + " ]:  " + CON[i_0]);//输出判断语句
		}
		condition_1.remove(0, condition_1.indexOf(";") + 1);//将condition_1删减一部分

		comma_num_con = 0;//将逗号个数清零

		//将CON[i]拆分成coni[i]
		for (i_1 = 0; i_1 < CON[i_0].length(); i_1++)
		{
			LORA_Receive_information();	//LORA的接收函数

			//得到逗号,的个数comma_num
			if (CON[i_0].indexOf(",") != -1)
			{
				/*coni_i[i] = coni.substring(coni.indexOf(",") + 1, coni.length());
				Serial.println(String("coni_ ") + i + " :  " + coni_i[i]);*/
				CON[i_0].remove(0, CON[i_0].indexOf(",") + 1);//将CON[i]删减一部分
				//Serial.println(con[i]);
				comma_num_con++;
			}
			else
			{
				//Serial.println("没有逗号,");
			}
		}
		if (debug_print == 1)
		{
			Serial.println(String("逗号个数comma_num = ") + comma_num_con);
		}

		for_num2_con = 0;

		//通过分号的个数判断需要截取几段
		if (comma_num_con == 0)
		{
			for_num2_con = 0;
		}
		else if (comma_num_con == 2)
		{
			for_num2_con = 3;
		}
		else if (comma_num_con == 4)
		{
			for_num2_con = 5;
		}
		else
		{
			Serial.println("超出个数");
		}

		if (debug_print == 1)
		{
			Serial.println(String("fornum2 = ") + for_num2_con);
		}

		//通过逗号的个数截取出coni_i
		if (for_num2_con == 0)
		{
			if (i_0 == 0)
			{
				con0[0] = coni;
				Serial.println(String("con0[0]") + " :  " + con0[0]);//输出第一条判断语句
				Serial.println("");
			}
			else if (i_0 == 1)
			{
				con1[0] = coni;
				Serial.println(String("con1[0]") + " :  " + con1[0]);//输出第一条判断语句
				Serial.println("");
			}
			else if (i_0 == 2)
			{
				con2[0] = coni;
				Serial.println(String("con2[0]") + " :  " + con2[0]);//输出第一条判断语句
				Serial.println("");
			}
			else if (i_0 == 3)
			{
				con3[0] = coni;
				Serial.println(String("con1[0]") + " :  " + con1[0]);//输出第一条判断语句
				Serial.println("");
			}
			else
			{
				Serial.println("----------");
			}
		}
		else
		{
			if (i_0 == 0)
			{
				for (size_t i = 0; i < 5; i++)
				{
					LORA_Receive_information();	//LORA的接收函数

					if (i < for_num2_con)
					{
						con0[i] = coni.substring(0, coni.indexOf(","));
						Serial.println(String("con0[ ") + i + " ]:  " + con0[i]);//输出第一条判断语句
						coni.remove(0, coni.indexOf(",") + 1);//将con1删减一部分
					}
					else
					{
						con0[i] = String('\0');
					}
				}
				Serial.println("");
			}
			else if (i_0 == 1)
			{
				for (size_t i = 0; i < 5; i++)
				{
					LORA_Receive_information();	//LORA的接收函数

					if (i < for_num2_con)
					{
						con1[i] = coni.substring(0, coni.indexOf(","));
						Serial.println(String("con1[ ") + i + " ]:  " + con1[i]);//输出第一条判断语句
						coni.remove(0, coni.indexOf(",") + 1);//将con1删减一部分
					}
					else
					{
						con1[i] = String('\0');
					}
				}
				Serial.println("");
			}
			else if (i_0 == 2)
			{
				for (size_t i = 0; i < 5; i++)
				{
					LORA_Receive_information();	//LORA的接收函数

					if (i < for_num2_con)
					{
						con2[i] = coni.substring(0, coni.indexOf(","));
						Serial.println(String("con2[ ") + i + " ]:  " + con2[i]);//输出第一条判断语句
						coni.remove(0, coni.indexOf(",") + 1);//将con1删减一部分
					}
					else
					{
						con2[i] = String('\0');
					}
				}
				Serial.println("");
			}
			else if (i_0 == 3)
			{
				for (size_t i = 0; i < 5; i++)
				{
					LORA_Receive_information();	//LORA的接收函数

					if (i < for_num2_con)
					{
						con3[i] = coni.substring(0, coni.indexOf(","));
						Serial.println(String("con3[ ") + i + " ]:  " + con3[i]);//输出第一条判断语句
						coni.remove(0, coni.indexOf(",") + 1);//将con1删减一部分
					}
					else
					{
						con3[i] = String('\0');
					}
				}
				Serial.println("");
			}
			else if (i_0 == 4)
			{
				for (size_t i = 0; i < 5; i++)
				{
					LORA_Receive_information();	//LORA的接收函数

					if (i < for_num2_con)
					{
						con4[i] = coni.substring(0, coni.indexOf(","));
						Serial.println(String("con4[ ") + i + " ]:  " + con4[i]);//输出第一条判断语句
						coni.remove(0, coni.indexOf(",") + 1);//将con1删减一部分
					}
					else
					{
						con4[i] = String('\0');
					}
				}
				Serial.println("");
			}
			else
			{
				Serial.println("=====");
			}
		}

		//调用函数开始进行判断
	}

	return i_0;
}

//函 数 名：int implement_test(String imp1)
//功能描述：处理执行语句的函数
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：执行语句的语句段数
/////////////////////////////////////////////////////////////////////
int implement_test(String implement_1)
{
	String imp_1 = implement_1;//implement_1的备份
	if (debug_print == 1)
	{
		Serial.println("int implement_test(String implement_1)");
		Serial.println(String("implement_1 = ") + implement_1);
	}
	String IMP[5];//执行语句块数组
	String impi;//IMP[i]的备份
	int semicolon_num_imp = 0;//分号的个数
	int comma_num_imp = 0;//逗号的个数 
	int for_num1_imp = 0, for_num2_imp = 0;//
	//-----------------------------------------------------

	semicolon_num_imp = 0;//将分号个数清零

	//得到分号;的个数
	for (size_t i = 0; i < imp_1.length(); i++)
	{
		LORA_Receive_information();	//LORA的接收函数

		if (imp_1.indexOf(";") != -1)
		{
			imp_1 = imp_1.substring(imp_1.indexOf(";") + 1, imp_1.length());
			Serial.println(String("imp_1: ") + imp_1);
			semicolon_num_imp++;
		}
		else
		{
			//Serial.println("没有分号;");
		}
	}

	if (debug_print == 1)
	{
		Serial.println("分号个数semicolon_num_imp = " + String(semicolon_num_imp));
	}

	for_num1_imp = 0;

	//通过分号的个数判断需要截取几段
	if (semicolon_num_imp == 0)
	{
		for_num1_imp = 0;
		//---------------------------------------------------
		//因为当fornum1 = 0时，后面的循环体不执行，所以需要单独写出来
		IMP[0] = condition_1;
		impi = IMP[0];//CON[i]的备份
		Serial.println(String("IMP[0]: ") + IMP[0]);

		//将con[i]拆分成coni[i]
		for (size_t i = 0; i < IMP[0].length(); i++)
		{
			LORA_Receive_information();	//LORA的接收函数

			//得到逗号,的个数comma_num
			if (IMP[i_0].indexOf(",") != -1)
			{
				/*impi_i[i] = impi.substring(impi.indexOf(",") + 1, impi.length());
				Serial.println(String("impi_ ") + i + " :  " + impi_i[i]);*/
				IMP[i_0].remove(0, IMP[i_0].indexOf(",") + 1);//将IMP[i]删减一部分
				//Serial.println(con[i]);
				comma_num_imp++;
			}
			else
			{
				//Serial.println("没有逗号,");
			}
		}
		if (debug_print == 1)
		{
			Serial.println(String("逗号个数comma_num = ") + comma_num_imp);
		}

		for_num2_imp = 0;

		//通过分号的个数判断需要截取几段
		if (comma_num_imp == 0)
		{
			for_num2_imp = 0;
		}
		else if (comma_num_imp == 2)
		{
			for_num2_imp = 3;
		}
		else if (comma_num_imp == 4)
		{
			for_num2_imp = 5;
		}
		else
		{
			Serial.println("超出个数");
		}

		if (debug_print == 1)
		{
			Serial.println(String("fornum2 = ") + for_num2_imp);
		}

		for (size_t i = 0; i < for_num2_imp; i++)
		{
			LORA_Receive_information();	//LORA的接收函数

			imp0[i] = impi.substring(0, impi.indexOf(","));
			Serial.println(String("imp0[ ") + i + " ]:  " + imp0[i]);//输出第一条判断语句
			impi.remove(0, impi.indexOf(",") + 1);//将imp1删减一部分
		}
		Serial.println("");

		//---------------------------------------------------
	}
	else if (semicolon_num_imp == 1)
	{
		for_num1_imp = 2;
	}
	else if (semicolon_num_imp == 2)
	{
		for_num1_imp = 3;
	}
	else if (semicolon_num_imp == 3)
	{
		for_num1_imp = 4;
	}

	//截取段数，并且输出
	for (i_2 = 0; i_2 < for_num1_imp; i_2++)
	{
		LORA_Receive_information();	//LORA的接收函数

		IMP[i_2] = implement_1.substring(0, implement_1.indexOf(";"));//截取出IMP[i]
		impi = IMP[i_2];//IMP[i]的备份
		if (debug_print == 1)
		{
			Serial.println(String("IMP[ ") + i_2 + " ]:  " + IMP[i_2]);//输出判断语句
		}
		implement_1.remove(0, implement_1.indexOf(";") + 1);//将implement_1删减一部分

		comma_num_imp = 0;//将逗号个数清零

		//将CON[i]拆分成coni[i]
		for (i_3 = 0; i_3 < IMP[i_2].length(); i_3++)
		{
			LORA_Receive_information();	//LORA的接收函数

			//得到逗号,的个数comma_num
			if (IMP[i_2].indexOf(",") != -1)
			{
				IMP[i_2].remove(0, IMP[i_2].indexOf(",") + 1);//将CON[i]删减一部分
				//Serial.println(con[i]);
				comma_num_imp++;
			}
			else
			{
				//Serial.println("没有逗号,");
			}
		}

		if (debug_print == 1)
		{
			Serial.println(String("逗号个数comma_num_imp = ") + comma_num_imp);
		}

		for_num2_imp = 0;

		//通过逗号的个数判断需要截取几段
		if (comma_num_imp == 0)
		{
			for_num2_imp = 0;
		}
		else if (comma_num_imp == 2)
		{
			for_num2_imp = 3;
		}
		else if (comma_num_imp == 4)
		{
			for_num2_imp = 5;
		}
		else
		{
			Serial.println("超出个数");
		}

		if (debug_print == 1)
		{
			Serial.println(String("for_num2_imp = ") + for_num2_imp);
		}

		//通过逗号的个数截取出impi_i
		if (for_num2_imp == 0)
		{
			if (i_2 == 0)
			{
				con0[0] = impi;
				Serial.println(String("imp0[0]") + " :  " + imp0[0]);//输出第一条判断语句
				Serial.println("");
			}
			else if (i_2 == 1)
			{
				imp1[0] = impi;
				Serial.println(String("imp1[0]") + " :  " + imp1[0]);//输出第一条判断语句
				Serial.println("");
			}
			else if (i_2 == 2)
			{
				imp2[0] = impi;
				Serial.println(String("imp2[0]") + " :  " + imp2[0]);//输出第一条判断语句
				Serial.println("");
			}
			else if (i_2 == 3)
			{
				imp3[0] = impi;
				Serial.println(String("imp3[0]") + " :  " + imp3[0]);//输出第一条判断语句
				Serial.println("");
			}
			else
			{
				Serial.println("----------");
			}
		}
		else
		{
			if (i_2 == 0)
			{
				for (size_t i = 0; i < 5; i++)
				{
					if (i < for_num2_imp)
					{
						imp0[i] = impi.substring(0, impi.indexOf(","));
						Serial.println(String("imp0[ ") + i + " ]:  " + imp0[i]);//输出第一条判断语句
						impi.remove(0, impi.indexOf(",") + 1);//将con1删减一部分
					}
					else
					{
						imp0[i] = String('\0');
					}
				}
				Serial.println("");
			}
			else if (i_2 == 1)
			{
				for (size_t i = 0; i < 5; i++)
				{
					if (i < for_num2_imp)
					{
						imp1[i] = impi.substring(0, impi.indexOf(","));
						Serial.println(String("imp1[ ") + i + " ]:  " + imp1[i]);//输出第一条判断语句
						impi.remove(0, impi.indexOf(",") + 1);//将con1删减一部分
					}
					else
					{
						imp1[i] = String('\0');
					}
				}
				Serial.println("");
			}
			else if (i_2 == 2)
			{
				for (size_t i = 0; i < 5; i++)
				{
					if (i < for_num2_imp)
					{
						imp2[i] = impi.substring(0, impi.indexOf(","));
						Serial.println(String("imp2[ ") + i + " ]:  " + imp2[i]);//输出第一条判断语句
						impi.remove(0, impi.indexOf(",") + 1);//将con1删减一部分
					}
					else
					{
						imp2[i] = String('\0');
					}
				}
				Serial.println("");
			}
			else if (i_2 == 3)
			{
				for (size_t i = 0; i < 5; i++)
				{
					if (i < for_num2_imp)
					{
						imp3[i] = impi.substring(0, impi.indexOf(","));
						Serial.println(String("imp3[ ") + i + " ]:  " + imp3[i]);//输出第一条判断语句
						impi.remove(0, impi.indexOf(",") + 1);//将con1删减一部分
					}
					else
					{
						imp3[i] = String('\0');
					}
				}
				Serial.println("");
			}
			else if (i_2 == 4)
			{
				for (size_t i = 0; i < 5; i++)
				{
					if (i < for_num2_imp)
					{
						imp4[i] = impi.substring(0, impi.indexOf(","));
						Serial.println(String("imp4[ ") + i + " ]:  " + imp4[i]);//输出第一条判断语句
						impi.remove(0, impi.indexOf(",") + 1);//将con1删减一部分
					}
					else
					{
						imp4[i] = String('\0');
					}
				}
				Serial.println("");
			}
			else
			{
				Serial.println("=====");
			}
		}

	}
	return i_2;
}

//函 数 名：int Condition_Judgment(int conx, int ret_condition_test)
//功能描述：条件语句的判断函数
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：为真返回1，为假返回0
/////////////////////////////////////////////////////////////////////
int Condition_Judgment(int conx, int ret_condition_test)
{
	//array_print_test();//输出测试

	if (conx == 0)
	{
		for (int i = 0; i < 5; i++)
		{
			LORA_Receive_information();	//LORA的接收函数

			Strcon[i] = con0[i];
			if (debug_print == 1)
			{
				Serial.println(String("Strcon[") + i + "]:" + Strcon[i]);
			}
		}
		if (debug_print == 1)
		{
			Serial.println("Strcon[i] = con0[i]");
		}
	}
	else if (conx == 1)
	{
		for (int i = 0; i < 5; i++)
		{
			LORA_Receive_information();	//LORA的接收函数

			Strcon[i] = con1[i];
			if (debug_print == 1)
			{
				Serial.println(String("Strcon[") + i + "]:" + Strcon[i]);
			}
		}
		if (debug_print == 1)
		{
			Serial.println("Strcon[i] = con1[i]");
		}
	}
	else if (conx == 2)
	{
		for (int i = 0; i < 5; i++)
		{
			LORA_Receive_information();	//LORA的接收函数

			Strcon[i] = con2[i];
			if (debug_print == 1)
			{
				Serial.println(String("Strcon[") + i + "]:" + Strcon[i]);
			}
		}
		if (debug_print == 1)
		{
			Serial.println("Strcon[i] = con2[i]");
		}
	}
	else if (conx == 3)
	{
		for (int i = 0; i < 5; i++)
		{
			LORA_Receive_information();	//LORA的接收函数

			Strcon[i] = con3[i];
			if (debug_print == 1)
			{
				Serial.println(String("Strcon[") + i + "]:" + Strcon[i]);
			}
		}
		if (debug_print == 1)
		{
			Serial.println("Strcon[i] = con3[i]");
		}
	}
	else if (conx == 4)
	{
		for (int i = 0; i < 5; i++)
		{
			LORA_Receive_information();	//LORA的接收函数

			Strcon[i] = con4[i];
			if (debug_print == 1)
			{
				Serial.println(String("Strcon[") + i + "]:" + Strcon[i]);
			}
		}
		if (debug_print == 1)
		{
			Serial.println("Strcon[i] = con4[i]");
		}
	}

	//conx为0,2,4时代表是条件判断语句
	if (conx == 0 || conx == 2 || conx == 4)
	{
		//判断是否是X1数字输入1
		if (Strcon[0] == String("X1"))
		{
			if (Strcon[1] == String("="))
			{
				//判断是否为高电平
				if (Strcon[2] == String("1"))
				{
					if (digitalRead(DI1) == HIGH)
					{
						Serial.println("X1=1");
						return 1;
					}
					if (debug_print == 1)
					{
						Serial.println("X1不为高电平");
					}
				}
				//判断是否为低电平
				else if (Strcon[2] == String("0"))
				{
					if (digitalRead(DI1) == LOW)
					{
						Serial.println("X1=0");
						return 1;
					}
					if (debug_print == 1)
					{
						Serial.println("X1不为低电平");
					}
				}
			}
		}
		//判断是否是X2数字输入2
		else if (Strcon[0] == String("X2"))
		{
			if (Strcon[1] == String("="))
			{
				//判断是否为高电平
				if (Strcon[2] == String("1"))
				{
					if (digitalRead(DI2) == HIGH)
					{
						Serial.println("X2=1");
						return 1;
					}
					if (debug_print == 1)
					{
						Serial.println("X2不为高电平");
					}
				}
			}
			//判断是否为低电平
			else if (Strcon[2] == String("0"))
			{
				if (digitalRead(DI2) == LOW)
				{
					Serial.println("X2=0");
					return 1;
				}
				if (debug_print == 1)
				{
					Serial.println("X2不为低电平");
				}
			}
		}
		//判断是否是模拟输入1
		else if (Strcon[0] == String("U1"))
		{
			//判断模拟输入是否大于带电压值
			if (Strcon[1] == String(">"))
			{
				if (debug_print == 1)
				{
					Serial.println(Strcon[2]);
				}

				//处理电压值的函数，将设定的电压值转换为analogRead的值
				//Voltage_Value_Processing(Strcon[3]);
				if (analogRead(VIN1) > Voltage_Value_Processing(Strcon[3]))
				{
					Serial.println("U1 > Voltage_Value_Processing(Strcon[3])");
					return 1;
				}
				Serial.println("U1 < Voltage_Value_Processing(Strcon[3])不符合要求");
			}
			else if (Strcon[1] == String("<"))
			{
				if (debug_print == 1)
				{
					Serial.println(Strcon[2]);
				}

				//处理电压值的函数，将设定的电压值转换为analogRead的值
				//Voltage_Value_Processing(Strcon[3]);
				if (analogRead(VIN1) < Voltage_Value_Processing(Strcon[3]))
				{
					Serial.println("U1 < Voltage_Value_Processing(Strcon[3])");
					return 1;
				}
				if (debug_print == 1)
				{
					Serial.println("U1 > Voltage_Value_Processing(Strcon[3])不符合要求");
				}
			}
		}
		//判断是否是模拟输入2
		else if (Strcon[0] == String("U2"))
		{
			//判断模拟输入是否大于带电压值
			if (Strcon[1] == String(">"))
			{
				if (debug_print == 1)
				{
					Serial.println(Strcon[2]);
				}

				//处理电压值的函数，将设定的电压值转换为analogRead的值
				//Voltage_Value_Processing(Strcon[3]);
				if (analogRead(VIN2) > Voltage_Value_Processing(Strcon[3]))
				{
					Serial.println("U2 > Voltage_Value_Processing(Strcon[3])");
					return 1;
				}
				Serial.println("U2 < Voltage_Value_Processing(Strcon[3])不符合要求");
			}
			else if (Strcon[1] == String("<"))
			{
				if (debug_print == 1)
				{
					Serial.println(Strcon[2]);
				}

				//处理电压值的函数，将设定的电压值转换为analogRead的值
				//Voltage_Value_Processing(Strcon[3]);
				if (analogRead(VIN2) < Voltage_Value_Processing(Strcon[3]))
				{
					Serial.println("U2 < Voltage_Value_Processing(Strcon[3])");
					return 1;
				}
				if (debug_print == 1)
				{
					Serial.println("U2 > Voltage_Value_Processing(Strcon[3])不符合要求");
				}
			}
		}

	}
	//conx为1,3时代表是逻辑语句
	else if (conx == 1 || conx == 3)
	{
		if (Strcon[0] == String("&&"))
		{
			Serial.println(Strcon[0]);
			return 2;
		}
		else if (Strcon[0] == String("||"))
		{
			Serial.println(Strcon[0]);
			return 3;
		}
	}
	return 0;
}

//函 数 名：int Implement_Handle(int impx, int ret_Implement_test)
//功能描述：执行语句的执行函数
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：为真返回1，为假返回0
/////////////////////////////////////////////////////////////////////
int Implement_Handle(int impx, int ret_Implement_test)
{
	String TOP[2];//Trinomial Operational Processing三项式操作处理
	long top_Int[2];//Trinomial Operational Processing三项式操作处理
	float top_Float[2];//Trinomial Operational Processing三项式操作处理
	int imp_time;
	unsigned long imptime_old;
	//---------------------------------
	if (impx == 0)
	{
		for (int i = 0; i < 5; i++)
		{
			LORA_Receive_information();	//LORA的接收函数

			Strimp[i] = imp0[i];
			if (debug_print == 1)
			{
				Serial.println(String("Strimp[") + i + "]:" + Strimp[i]);
			}
		}
		if (debug_print == 1)
		{
			Serial.println("Strimp[i] = imp0[i]");
		}
	}
	else if (impx == 1)
	{
		for (int i = 0; i < 5; i++)
		{
			LORA_Receive_information();	//LORA的接收函数

			Strimp[i] = imp1[i];
			if (debug_print == 1)
			{
				Serial.println(String("Strimp[") + i + "]:" + Strimp[i]);
			}
		}
		if (debug_print == 1)
		{
			Serial.println("Strimp[i] = imp1[i]");
		}
	}
	else if (impx == 2)
	{
		for (int i = 0; i < 5; i++)
		{
			LORA_Receive_information();	//LORA的接收函数

			Strimp[i] = imp2[i];
			if (debug_print == 1)
			{
				Serial.println(String("Strimp[") + i + "]:" + Strimp[i]);
			}
		}
		if (debug_print == 1)
		{
			Serial.println("Strimp[i] = imp2[i]");
		}
	}
	else if (impx == 3)
	{
		for (int i = 0; i < 5; i++)
		{
			LORA_Receive_information();	//LORA的接收函数

			Strimp[i] = imp3[i];
			if (debug_print == 1)
			{
				Serial.println(String("Strimp[") + i + "]:" + Strimp[i]);
			}
		}
		if (debug_print == 1)
		{
			Serial.println("Strimp[i] = imp3[i]");
		}
	}
	else if (impx == 4)
	{
		for (int i = 0; i < 5; i++)
		{
			LORA_Receive_information();	//LORA的接收函数

			Strimp[i] = imp4[i];
			if (debug_print == 1)
			{
				Serial.println(String("Strimp[") + i + "]:" + Strimp[i]);
			}
		}
		if (debug_print == 1)
		{
			Serial.println("Strimp[i] = imp4[i]");
		}
	}
	else
	{
		return 0;
	}
	//判断是否是数字输出1
	if (Strimp[0] == String("Y1"))
	{
		//这是对Y1直接赋值
		if (Strimp[1] == String("="))
		{
			//判断数字输出Y1为高电平
			if (Strimp[2] == String("1"))
			{
				digitalWrite(DO1, HIGH);
			}
			//判断数字输出Y1为低电平
			else if (Strimp[2] == String("0"))
			{
				digitalWrite(DO1, LOW);
			}
		}
		//三目运算符
		else if (Strimp[1].indexOf(":") != -1)
		{
			//截取：冒号前的语句为TOP[0],并转换为真正的数字
			TOP[0] = Strimp[1].substring(0, Strimp[1].indexOf(":"));
			top_Int[0] = TOP[0].toInt();
			//截取：冒号后的语句为TOP[1],并转换为真正的数字
			TOP[1] = Strimp[1].substring(Strimp[1].indexOf(":") + 1, Strimp[1].length());
			top_Int[1] = TOP[1].toInt();

			if (debug_print == 1)
			{
				Serial.println(String("TOP[0] = ") + TOP[0]);
				Serial.println(String("TOP[1] = ") + TOP[1]);
				Serial.println(top_Int[0]);
				Serial.println(top_Int[1]);
			}

			//执行三项式的前半段
			if (top_Int[0] == 0x01)
			{
				digitalWrite(DO1, HIGH);
				//Serial.println("digitalWrite(DO1, HIGH)");
			}
			else if (top_Int[0] == 0x00)
			{
				digitalWrite(DO1, LOW);
			}

			//--------得到延时的时间值--------
			char* c = (char*)Strimp[2].c_str();//得到字符串的指针

			imp_time = charhex_to_dec(c);//将16进制字符串转换为10进制数字
			imptime_old = millis();

			if (debug_print == 1)
			{
				Serial.print("imp_time = ");
				Serial.println(imp_time);
				Serial.print("imptime_old = ");
				Serial.println(imptime_old);
			}

			if (debug == 1)
			{
				imp_time = 1;
			}
			while (millis() - imptime_old <= imp_time * 1000)
			{
				LORA_Receive_information();
			}
			//delay(imp_time * 1000);//持续时间
			//------------------------------

			//执行三项式的后半段
			if (top_Int[1] == 0x01)
			{
				digitalWrite(DO1, HIGH);
			}
			else if (top_Int[1] == 0x00)
			{
				digitalWrite(DO1, LOW);
				//Serial.println("digitalWrite(DO1, LOW)");
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return 0;
		}
	}
	//判断是否是数字输出2
	else if (Strimp[0] == String("Y2"))
	{
		//这是对Y2直接赋值
		if (Strimp[1] == String("="))
		{
			//判断数字输出Y2为高电平
			if (Strimp[2] == String("1"))
			{
				digitalWrite(DO2, HIGH);
			}
			//判断数字输出Y2为低电平
			else if (Strimp[2] == String("0"))
			{
				digitalWrite(DO2, LOW);
			}
		}
		//三目运算符
		else if (Strimp[1].indexOf(":") != -1)
		{
			//截取：冒号前的语句为TOP[0],并转换为真正的数字
			TOP[0] = Strimp[1].substring(0, Strimp[1].indexOf(":"));
			top_Int[0] = TOP[0].toInt();
			//截取：冒号后的语句为TOP[1],并转换为真正的数字
			TOP[1] = Strimp[1].substring(Strimp[1].indexOf(":") + 1, Strimp[1].length());
			top_Int[1] = TOP[1].toInt();

			if (debug_print == 1)
			{
				Serial.println(String("TOP[0] = ") + TOP[0]);
				Serial.println(String("TOP[1] = ") + TOP[1]);
				Serial.println(top_Int[0]);
				Serial.println(top_Int[1]);
			}

			//执行三项式的前半段
			if (top_Int[0] == 0x01)
			{
				digitalWrite(DO2, HIGH);
				//Serial.println("digitalWrite(DO1, HIGH)");
			}
			else if (top_Int[0] == 0x00)
			{
				digitalWrite(DO2, LOW);
			}

			//--------得到延时的时间值--------
			char* c = (char*)Strimp[2].c_str();//得到字符串的指针

			imp_time = charhex_to_dec(c);//将16进制字符串转换为10进制数字
			imptime_old = millis();

			if (debug_print == 1)
			{
				Serial.print("imp_time = ");
				Serial.println(imp_time);
				Serial.print("imptime_old = ");
				Serial.println(imptime_old);
			}

			if (debug == 1)
			{
				imp_time = 1;
			}
			while (millis() - imptime_old <= imp_time * 1000)
			{
				LORA_Receive_information();
			}
			//delay(imp_time * 1000);//持续时间
			//------------------------------

			//执行三项式的后半段
			if (top_Int[1] == 0x01)
			{
				digitalWrite(DO2, HIGH);
			}
			else if (top_Int[1] == 0x00)
			{
				digitalWrite(DO2, LOW);
				//Serial.println("digitalWrite(DO1, LOW)");
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return 0;
		}
	}
	//判断是否是数字输出3
	else if (Strimp[0] == String("Y3"))
	{
		//这是对Y3直接赋值
		if (Strimp[1] == String("="))
		{
			//判断数字输出Y3为高电平
			if (Strimp[2] == String("1"))
			{
				digitalWrite(KCZJ1, LOW);
			}
			//判断数字输出Y3为低电平
			else if (Strimp[2] == String("0"))
			{
				digitalWrite(KCZJ1, HIGH);
			}
		}
		//三目运算符
		else if (Strimp[1].indexOf(":") != -1)
		{
			//截取：冒号前的语句为TOP[0],并转换为真正的数字
			TOP[0] = Strimp[1].substring(0, Strimp[1].indexOf(":"));
			top_Int[0] = TOP[0].toInt();
			//截取：冒号后的语句为TOP[1],并转换为真正的数字
			TOP[1] = Strimp[1].substring(Strimp[1].indexOf(":") + 1, Strimp[1].length());
			top_Int[1] = TOP[1].toInt();

			if (debug_print == 1)
			{
				Serial.println(String("TOP[0] = ") + TOP[0]);
				Serial.println(String("TOP[1] = ") + TOP[1]);
				Serial.println(top_Int[0]);
				Serial.println(top_Int[1]);
			}

			//执行三项式的前半段
			if (top_Int[0] == 0x01)
			{
				digitalWrite(KCZJ2, LOW);
				//Serial.println("digitalWrite(DO1, HIGH)");
			}
			else if (top_Int[0] == 0x00)
			{
				digitalWrite(KCZJ1, HIGH);
			}

			//--------得到延时的时间值--------
			char* c = (char*)Strimp[2].c_str();//得到字符串的指针

			imp_time = charhex_to_dec(c);//将16进制字符串转换为10进制数字
			imptime_old = millis();

			if (debug_print == 1)
			{
				Serial.print("imp_time = ");
				Serial.println(imp_time);
				Serial.print("imptime_old = ");
				Serial.println(imptime_old);
			}

			if (debug == 1)
			{
				imp_time = 1;
			}
			while (millis() - imptime_old <= imp_time * 1000)
			{
				LORA_Receive_information();
			}
			//delay(imp_time * 1000);//持续时间
			//------------------------------

			//执行三项式的后半段
			if (top_Int[1] == 0x01)
			{
				digitalWrite(KCZJ1, LOW);
			}
			else if (top_Int[1] == 0x00)
			{
				digitalWrite(KCZJ1, HIGH);
				//Serial.println("digitalWrite(DO1, LOW)");
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return 0;
		}
	}
	//判断是否是数字输出4
	else if (Strimp[0] == String("Y4"))
	{
		//这是对Y4直接赋值
		if (Strimp[1] == String("="))
		{
			//判断数字输出Y4为高电平
			if (Strimp[2] == String("1"))
			{
				digitalWrite(KCZJ2, LOW);
			}
			//判断数字输出Y4为低电平
			else if (Strimp[2] == String("0"))
			{
				digitalWrite(KCZJ2, HIGH);
			}
		}
		//三目运算符
		else if (Strimp[1].indexOf(":") != -1)
		{
			//截取：冒号前的语句为TOP[0],并转换为真正的数字
			TOP[0] = Strimp[1].substring(0, Strimp[1].indexOf(":"));
			top_Int[0] = TOP[0].toInt();
			//截取：冒号后的语句为TOP[1],并转换为真正的数字
			TOP[1] = Strimp[1].substring(Strimp[1].indexOf(":") + 1, Strimp[1].length());
			top_Int[1] = TOP[1].toInt();

			if (debug_print == 1)
			{
				Serial.println(String("TOP[0] = ") + TOP[0]);
				Serial.println(String("TOP[1] = ") + TOP[1]);
				Serial.println(top_Int[0]);
				Serial.println(top_Int[1]);
			}

			//执行三项式的前半段
			if (top_Int[0] == 0x01)
			{
				digitalWrite(KCZJ2, LOW);
				//Serial.println("digitalWrite(DO1, HIGH)");
			}
			else if (top_Int[0] == 0x00)
			{
				digitalWrite(KCZJ2, HIGH);
			}

			//--------得到延时的时间值--------
			char* c = (char*)Strimp[2].c_str();//得到字符串的指针

			imp_time = charhex_to_dec(c);//将16进制字符串转换为10进制数字
			imptime_old = millis();

			if (debug_print == 1)
			{
				Serial.print("imp_time = ");
				Serial.println(imp_time);
				Serial.print("imptime_old = ");
				Serial.println(imptime_old);
			}

			if (debug == 1)
			{
				imp_time = 1;
			}
			while (millis() - imptime_old <= imp_time * 1000)
			{
				LORA_Receive_information();
			}
			//delay(imp_time * 1000);//持续时间
			//------------------------------

			//执行三项式的后半段
			if (top_Int[1] == 0x01)
			{
				digitalWrite(KCZJ2, LOW);
			}
			else if (top_Int[1] == 0x00)
			{
				digitalWrite(KCZJ2, HIGH);
				//Serial.println("digitalWrite(DO1, LOW)");
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return 0;
		}
	}
	//判断是否是模拟输出1
	else if (Strimp[0] == String("V1"))
	{
		//三目运算符
		if (Strimp[1].indexOf(":") != -1)
		{
			//截取：冒号前的语句为TOP[0],并转换为真正的数字
			TOP[0] = Strimp[1].substring(0, Strimp[1].indexOf(":"));
			Serial.println(String("TOP[0] = ") + TOP[0]);

			//toInt()不会处理数字后字母，例如0050E2，处理结果为50
			top_Int[0] = TOP[0].toInt();

			if (TOP[0].indexOf("E1") != -1)
			{
				top_Float[0] = float(top_Int[0]) / 10;
			}
			else if (TOP[0].indexOf("E2") != -1)
			{
				top_Float[0] = float(top_Int[0]) / 100;
			}
			else
			{
				return 0;
			}

			//截取：冒号后的语句为TOP[1],并转换为真正的数字
			TOP[1] = Strimp[1].substring(Strimp[1].indexOf(":") + 1, Strimp[1].length());
			Serial.println(String("TOP[1] = ") + TOP[1]);

			top_Int[1] = TOP[1].toInt();

			if (TOP[1].indexOf("E1") != -1)
			{
				top_Float[1] = float(top_Int[1]) / 10;
			}
			else if (TOP[1].indexOf("E2") != -1)
			{
				top_Float[1] = float(top_Int[1]) / 100;
			}
			else
			{
				return 0;
			}

			if (debug_print == 1)
			{
				Serial.println(String("TOP[0] = ") + TOP[0]);
				Serial.println(String("TOP[1] = ") + TOP[1]);
				Serial.println(top_Int[0]);
				Serial.println(top_Int[1]);
				Serial.println(top_Float[0]);
				Serial.println(top_Float[1]);
			}

			float AV1 = (top_Float[0] / 0.011) / 0.8056;
			if (AV1 - floor(AV1) >= 0.5)
			{
				Analog_Value1 = floor(AV1) + 1;
			}
			else if (AV1 - floor(AV1) < 0.5)
			{
				Analog_Value1 = floor(AV1);
			}

			analogWrite(AO1, Analog_Value1);

			//--------得到延时的时间值--------
			char* c = (char*)Strimp[2].c_str();//得到字符串的指针

			imp_time = charhex_to_dec(c);//将16进制字符串转换为10进制数字
			imptime_old = millis();

			if (debug_print == 1)
			{
				Serial.print("imp_time = ");
				Serial.println(imp_time);
				Serial.print("imptime_old = ");
				Serial.println(imptime_old);
			}

			if (debug == 1)
			{
				imp_time = 1;
			}
			while (millis() - imptime_old <= imp_time * 1000)
			{
				LORA_Receive_information();
			}
			//delay(imp_time * 1000);//持续时间
			//------------------------------

			AV1 = (top_Float[1] / 0.011) / 0.8056;
			if (AV1 - floor(AV1) >= 0.5)
			{
				Analog_Value1 = floor(AV1) + 1;
			}
			else if (AV1 - floor(AV1) < 0.5)
			{
				Analog_Value1 = floor(AV1);
			}

			analogWrite(AO1, Analog_Value1);
		}
		else if (Strimp[1] == String("="))
		{

			top_Int[0] = Strimp[2].toInt();

			if (Strimp[2].indexOf("E1") != -1)
			{
				top_Float[0] = float(top_Int[0]) / 10;
			}
			else if (Strimp[2].indexOf("E2") != -1)
			{
				top_Float[0] = float(top_Int[0]) / 100;
			}
			else
			{
				return 0;
			}
			if (debug_print == 1)
			{
				Serial.println(top_Int[0]);
				Serial.println(top_Float[0]);
			}

			float AV1 = (top_Float[1] / 0.011) / 0.8056;
			if (AV1 - floor(AV1) >= 0.5)
			{
				Analog_Value1 = floor(AV1) + 1;
			}
			else if (AV1 - floor(AV1) < 0.5)
			{
				Analog_Value1 = floor(AV1);
			}

			analogWrite(AO1, Analog_Value1);
		}
		else
		{
			return 0;
		}
	}
	//判断是否是模拟输出2
	else if (Strimp[0] == String("V2"))
	{
		//三目运算符
		if (Strimp[1].indexOf(":") != -1)
		{
			//截取：冒号前的语句为TOP[0],并转换为真正的数字
			TOP[0] = Strimp[1].substring(0, Strimp[1].indexOf(":"));
			Serial.println(String("TOP[0] = ") + TOP[0]);

			//toInt()不会处理数字后字母，例如0050E2，处理结果为50
			top_Int[0] = TOP[0].toInt();

			if (TOP[0].indexOf("E1") != -1)
			{
				top_Float[0] = float(top_Int[0]) / 10;
			}
			else if (TOP[0].indexOf("E2") != -1)
			{
				top_Float[0] = float(top_Int[0]) / 100;
			}
			else
			{
				return 0;
			}

			//截取：冒号后的语句为TOP[1],并转换为真正的数字
			TOP[1] = Strimp[1].substring(Strimp[1].indexOf(":") + 1, Strimp[1].length());
			Serial.println(String("TOP[1] = ") + TOP[1]);

			top_Int[1] = TOP[1].toInt();

			if (TOP[1].indexOf("E1") != -1)
			{
				top_Float[1] = float(top_Int[1]) / 10;
			}
			else if (TOP[1].indexOf("E2") != -1)
			{
				top_Float[1] = float(top_Int[1]) / 100;
			}
			else
			{
				return 0;
			}

			if (debug_print == 1)
			{
				Serial.println(String("TOP[0] = ") + TOP[0]);
				Serial.println(String("TOP[1] = ") + TOP[1]);
				Serial.println(top_Int[0]);
				Serial.println(top_Int[1]);
				Serial.println(top_Float[0]);
				Serial.println(top_Float[1]);
			}

			float AV1 = (top_Float[0] / 0.011) / 0.8056;
			if (AV1 - floor(AV1) >= 0.5)
			{
				Analog_Value1 = floor(AV1) + 1;
			}
			else if (AV1 - floor(AV1) < 0.5)
			{
				Analog_Value1 = floor(AV1);
			}

			analogWrite(AO2, Analog_Value1);

			//--------得到延时的时间值--------
			char* c = (char*)Strimp[2].c_str();//得到字符串的指针

			imp_time = charhex_to_dec(c);//将16进制字符串转换为10进制数字
			imptime_old = millis();

			if (debug_print == 1)
			{
				Serial.print("imp_time = ");
				Serial.println(imp_time);
				Serial.print("imptime_old = ");
				Serial.println(imptime_old);
			}

			if (debug == 1)
			{
				imp_time = 1;
			}
			while (millis() - imptime_old <= imp_time * 1000)
			{
				LORA_Receive_information();
			}
			//delay(imp_time * 1000);//持续时间
			//------------------------------

			AV1 = (top_Float[1] / 0.011) / 0.8056;
			if (AV1 - floor(AV1) >= 0.5)
			{
				Analog_Value1 = floor(AV1) + 1;
			}
			else if (AV1 - floor(AV1) < 0.5)
			{
				Analog_Value1 = floor(AV1);
			}

			analogWrite(AO2, Analog_Value1);
		}
		else if (Strimp[1] == String("="))
		{

			top_Int[0] = Strimp[2].toInt();

			if (Strimp[2].indexOf("E1") != -1)
			{
				top_Float[0] = float(top_Int[0]) / 10;
			}
			else if (Strimp[2].indexOf("E2") != -1)
			{
				top_Float[0] = float(top_Int[0]) / 100;
			}
			else
			{
				return 0;
			}
			if (debug == 1)
			{
				Serial.println(top_Int[0]);
				Serial.println(top_Float[0]);
			}

			float AV1 = (top_Float[1] / 0.011) / 0.8056;
			if (AV1 - floor(AV1) >= 0.5)
			{
				Analog_Value1 = floor(AV1) + 1;
			}
			else if (AV1 - floor(AV1) < 0.5)
			{
				Analog_Value1 = floor(AV1);
			}

			analogWrite(AO1, Analog_Value1);
		}
		else
		{
			return 0;
		}
	}
	//判断是否是延时
	else if (Strimp[0] == String("D0"))
	{
		if (Strimp[1] == String("="))
		{
			//--------得到延时的时间值--------
			char* c = (char*)Strimp[2].c_str();//得到字符串的指针

			imp_time = charhex_to_dec(c);//将16进制字符串转换为10进制数字
			imptime_old = millis();

			if (debug_print == 1)
			{
				Serial.print("imp_time = ");
				Serial.println(imp_time);
				Serial.print("imptime_old = ");
				Serial.println(imptime_old);
			}

			if (debug == 1)
			{
				imp_time = 1;
			}
			while (millis() - imptime_old <= imp_time * 1000)
			{
				LORA_Receive_information();
			}
			//delay(imp_time * 1000);//持续时间
			//------------------------------
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}

//函 数 名：array_empty_test()
//功能描述：数组清空函数
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
void array_empty_test()
{
	if (debug_print == 1)
	{
		Serial.println("array_empty_test数组清空开始");
	}
	for (size_t i = 0; i < 5; i++)
	{
		LORA_Receive_information();

		//清空判断数组
		for (size_t i = 0; i < 5; i++)
		{
			Strcon[i] == 0;
			Strimp[i] == 0;
		}

		if (i == 0)
		{
			//Serial.print("con0[0-5] = ");
			for (size_t ii = 0; ii < 5; ii++)
			{
				con0[ii] = String('\0');
				imp0[ii] = String('\0');
			}
			//Serial.println("");
		}
		else if (i == 1)
		{
			//Serial.print("con1[0-5] = ");
			for (size_t ii = 0; ii < 5; ii++)
			{
				con1[ii] = String('\0');
				imp1[ii] = String('\0');
			}
			//Serial.println("");
		}
		else if (i == 2)
		{
			//Serial.print("con2[0-5] = ");
			for (size_t ii = 0; ii < 5; ii++)
			{
				con2[ii] = String('\0');
				imp2[ii] = String('\0');
			}
			//Serial.println("");
		}
		else if (i == 3)
		{
			//Serial.print("con3[0-5] = ");
			for (size_t ii = 0; ii < 5; ii++)
			{
				con3[ii] = String('\0');
				imp3[ii] = String('\0');
			}
			//Serial.println("");
		}
		else if (i == 4)
		{
			//Serial.print("con4[0-5] = ");
			for (size_t ii = 0; ii < 5; ii++)
			{
				con4[ii] = String('\0');
				imp4[ii] = String('\0');
			}
			//Serial.println("");
		}
		else
		{
			Serial.println("输出错误");
		}
	}
}

//函 数 名：array_print_test()
//功能描述：数组打印测试函数
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
void array_print_test()
{
	if (debug_print == 1)
	{
		Serial.println("array_print_test数组打印测试开始");
	}
	for (size_t i = 0; i < 5; i++)
	{
		LORA_Receive_information();

		if (i == 0)
		{
			Serial.print("con0[0-5] = ");
			for (size_t ii = 0; ii < 5; ii++)
			{
				Serial.print(con0[ii]);
				Serial.print("[]");
				Serial.flush();
			}
			Serial.println("");
			Serial.print("imp0[0-5] = ");
			for (size_t ii = 0; ii < 5; ii++)
			{
				Serial.print(imp0[ii]);
				Serial.print("[]");
				Serial.flush();
			}
			Serial.println("");
		}
		else if (i == 1)
		{
			Serial.print("con1[0-5] = ");
			for (size_t ii = 0; ii < 5; ii++)
			{
				Serial.print(con1[ii]);
				Serial.print("[]");
				Serial.flush();
			}
			Serial.println("");
			Serial.print("imp1[0-5] = ");
			for (size_t ii = 0; ii < 5; ii++)
			{
				Serial.print(imp1[ii]);
				Serial.print("[]");
				Serial.flush();
			}
			Serial.println("");
		}
		else if (i == 2)
		{
			Serial.print("con2[0-5] = ");
			for (size_t ii = 0; ii < 5; ii++)
			{
				Serial.print(con2[ii]);
				Serial.print("[]");
				Serial.flush();
			}
			Serial.println("");
			Serial.print("imp2[0-5] = ");
			for (size_t ii = 0; ii < 5; ii++)
			{
				Serial.print(imp2[ii]);
				Serial.print("[]");
				Serial.flush();
			}
			Serial.println("");
		}
		else if (i == 3)
		{
			Serial.print("con3[0-5] = ");
			for (size_t ii = 0; ii < 5; ii++)
			{
				Serial.print(con3[ii]);
				Serial.print("[]");
				Serial.flush();
			}
			Serial.println("");
			Serial.print("imp3[0-5] = ");
			for (size_t ii = 0; ii < 5; ii++)
			{
				Serial.print(imp3[ii]);
				Serial.print("[]");
				Serial.flush();
			}
			Serial.println("");
		}
		else if (i == 4)
		{
			Serial.print("con4[0-5] = ");
			for (size_t ii = 0; ii < 5; ii++)
			{
				Serial.print(con4[ii]);
				Serial.print("[]");
				Serial.flush();
			}
			Serial.println("");
			Serial.print("imp4[0-5] = ");
			for (size_t ii = 0; ii < 5; ii++)
			{
				Serial.print(imp4[ii]);
				Serial.print("[]");
				Serial.flush();
			}
			Serial.println("");
		}
		else
		{
			Serial.println("输出错误");
		}
		//delay(50);
	}
}

//函 数 名：Automated_strategy()
//功能描述：自动化策略函数，包括读取，判断，执行
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
void Automated_strategy()
{
	//读取设置的自动策略
	if (AT24CXX_ReadOneByte(13) > 0)
	{
		unsigned char EEPROM_Data[200];//用来存放接收到的数据
		String AssStat;//Association_statement，关联语句
		int ED_Indexes = 0;//EEPROM_Data的索引值ED_Indexes
		int Sentence_num = AT24CXX_ReadOneByte(13);//策略语句的个数
		int Sentence_begin;//策略语句的开始处
		int Sentence_end;//策略语句的开始处
		//int Sentence_begin[5];//策略语句的开始处
		//int Sentence_end[5];//策略语句的开始处
		//------------------------------------

		for (size_t i = 0; i < Sentence_num; i++)
		{
			LORA_Receive_information();	//LORA的接收函数

			if (i == 0)
			{
				Sentence_begin = AT24CXX_ReadOneByte(90);
				Sentence_end = AT24CXX_ReadOneByte(91);
				if (debug_print == 1)
				{
					Serial.println("策略语句1的起始结束位置赋值1111111111111111111111111");
					//delay(1500);
				}
			}
			else if (i == 1)
			{
				Sentence_begin = AT24CXX_ReadOneByte(92);
				Sentence_end = AT24CXX_ReadOneByte(93);
				if (debug_print == 1)
				{
					Serial.println("策略语句2的起始结束位置赋值2222222222222222222222222");
					//delay(1500);
				}
			}
			else if (i == 2)
			{
				Sentence_begin = AT24CXX_ReadOneByte(94);
				Sentence_end = AT24CXX_ReadOneByte(95);
				if (debug_print == 1)
				{
					Serial.println("策略语句3的起始结束位置赋值3333333333333333333333333333");
				}
			}
			else if (i == 3)
			{
				Sentence_begin = AT24CXX_ReadOneByte(96);
				Sentence_end = AT24CXX_ReadOneByte(97);
				if (debug_print == 1)
				{
					Serial.println("策略语句4的起始结束位置赋值444444444444444444444");
				}
			}
			else if (i == 4)
			{
				Sentence_begin = AT24CXX_ReadOneByte(98);
				Sentence_end = AT24CXX_ReadOneByte(99);
				if (debug_print == 1)
				{
					Serial.println("策略语句5的起始结束位置赋值555555555555555555555555");
					//delay(1000);
				}
			}

			ED_Indexes = 0;//清空ED_Indexes的值
			//这里将EEPROM语句的值赋给EEPROM_Data数组
			for (size_t ix = Sentence_begin; ix <= Sentence_end; ix++)
			{
				LORA_Receive_information();	//LORA的接收函数

				EEPROM_Data[ED_Indexes] = AT24CXX_ReadOneByte(ix);
				if (debug_print == 1)
				{
					/*Serial.println(String("EEPROM_Data[") + ED_Indexes + "] = " + String(EEPROM_Data[ED_Indexes], HEX));
					Serial.flush();*/
				}
				ED_Indexes++;
			}

			//delay(1000);
			AssStat.remove(0);//删除AssStat
			//将EEPROM_Data数组的值赋给一个string
			for (size_t i = 8; i < ED_Indexes - 7; i++)
			{
				//强制转换为char类型
				AssStat.concat(String(char(EEPROM_Data[i])));//拼接成关联语句，AssStat
			}
			if (debug_print == 1)
			{
				Serial.println(AssStat);
				/*delay(3500);*/
			}

			if (debug_print == 1)
			{
				array_print_test();//数组打印测试
			}

			//先分割#，分割为条件语句以及执行语句
			data_processing(AssStat);

			AssStat.remove(0);//删除AssStat
		}
	}
}


//函 数 名：Receive_A023() 
//功能描述：电压值处理函数
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
int Voltage_Value_Processing(String str_V)
{
	int int_Voltage = 0;
	float float_Voltage = 0.00, F_V = 0.00;

	int_Voltage = str_V.toInt();//将str_V转换为数字

	if (str_V.indexOf("E1") != -1)
	{
		float_Voltage = float(int_Voltage) / 10;//将数字转换为对应的进制的小数
	}
	else if (str_V.indexOf("E2") != -1)
	{
		float_Voltage = float(int_Voltage) / 100;//将数字转换为对应的进制的小数
	}

	F_V = (float_Voltage / 0.011) / 0.8056;

	if (F_V - floor(F_V) >= 0.5)
	{
		int_Voltage = floor(F_V) + 1;
	}
	else
	{
		int_Voltage = floor(F_V);
	}

	if (debug_print == 1)
	{
		Serial.println(String("str_V = ") + str_V);
		Serial.println(String("F_V = ") + F_V);
		Serial.println(String("int_Voltage = ") + int_Voltage);
	}

	return int_Voltage;
}

//函 数 名：Get_HeartBeat_oldtime() 
//功能描述：得到Delivery_oldtime的时间值
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
unsigned long Get_HeartBeat_oldtime()
{
	if (debug_print == 1)
	{
		//Serial.println(String("Delivery_oldtime = ") + Delivery_oldtime);
	}
	return HeartBeat_oldtime;
}

//函 数 名：Get_RTC_Flag() 
//功能描述：得到RTC_Flag的状态值
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
bool Get_RTC_Flag()
{
	return RTC_Flag;
}

//函 数 名：Automatic_execution_test() 
//功能描述：根据设定的时间段自动执行
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
void Automatic_execution_test()
{
	if (Mode_implementation == 0x01)
	{
		if (debug_print == 0x01)
		{
			//Serial.println("Mode_implementation == 0x01,进入自动执行函数");
		}

		if (DO1_AutoFlag == 1)
		{
			if (debug_print == 0x01)
			{
				//Serial.println("DO1_AutoFlag == 1");
			}

		}
		else if (DO2_AutoFlag == 1)
		{

		}
		else if (DO3_AutoFlag == 1)
		{
			if (debug_print == 0x01)
			{
				Serial.println("DO3_AutoFlag == 1");
			}

			if (RTC_Hour >= DO3_AutoBegin[0][3] && RTC_Hour <= DO3_AutoEnd[0][3] &&
				RTC_Minute >= DO3_AutoBegin[0][4] && RTC_Minute <= DO3_AutoEnd[0][4] &&
				RTC_Second >= DO3_AutoBegin[0][5] && RTC_Second <= DO3_AutoEnd[0][5])
			{
				digitalWrite(KCZJ1, LOW);
			}
			else if (RTC_Hour >= DO3_AutoBegin[1][3] && RTC_Hour <= DO3_AutoEnd[1][3] &&
				RTC_Minute >= DO3_AutoBegin[1][4] && RTC_Minute <= DO3_AutoEnd[1][4] &&
				RTC_Second >= DO3_AutoBegin[1][5] && RTC_Second <= DO3_AutoEnd[1][5])
			{
				digitalWrite(KCZJ1, LOW);
			}
			else
			{
				digitalWrite(KCZJ1, HIGH);
				Serial.println("DO3时间不匹配");
				delay(1000);
			}
		}
		else if (DO4_AutoFlag == 1)
		{

		}
		else if (AO1_AutoFlag == 1)
		{

		}
		else if (AO2_AutoFlag == 1)
		{

		}
		else
		{

		}
	}
}

//函 数 名：RTC_Clock() 
//功能描述：根据设定的时间段自动执行
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
void RTC_Clock()
{
	int Senod_count = 0;//得到经过了多少秒
	float Senod_count_F;

	Senod_count_F = float((millis() - RTC_oldtime)) / 1000;
	//Serial.println(String("Senod_count_F = ") + Senod_count_F);
	Senod_count = (millis() - RTC_oldtime) / 1000;
	Senod_count = (Senod_count_F - Senod_count > 0.5) ? Senod_count + 1 : Senod_count;



	RTC_oldtime = millis();
	if (debug_print == 0x01)
	{
		/*Serial.println(String("millis = ") + millis());
		Serial.println(String("RTC_oldtime = ") + RTC_oldtime);
		Serial.println(String("Senod_count = ") + Senod_count);
		Serial.println(String("RTC_Second = ") + RTC_Second);*/
	}

	RTC_Second = RTC_Second + Senod_count;
	if (debug_print == 1)
	{
		//Serial.println(String("RTC_Second = ") + RTC_Second);
	}


	if (RTC_Second == 60)
	{
		RTC_Minute = RTC_Minute + 1;
		RTC_Second = 0;
	}
	else if (RTC_Second > 60 && RTC_Second <= 119)
	{
		RTC_Minute = RTC_Minute + 1;
		RTC_Second = RTC_Second - 60;
	}
	else if (RTC_Second > 119 && RTC_Second <= 179)
	{
		RTC_Minute = RTC_Minute + 2;
		RTC_Second = RTC_Second - 120;
	}


	if (RTC_Minute == 60)
	{
		RTC_Hour = RTC_Hour + 1;
		RTC_Minute = 0;
	}
	else if (RTC_Minute > 60 && RTC_Minute <= 119)
	{
		RTC_Hour = RTC_Hour + 1;
		RTC_Minute = RTC_Minute - 60;
	}
	else if (RTC_Minute > 119 && RTC_Minute <= 179)
	{
		RTC_Hour = RTC_Hour + 2;
		RTC_Minute = RTC_Minute - 120;
	}
	else if (RTC_Minute > 179 && RTC_Minute <= 239)
	{
		RTC_Hour = RTC_Hour + 3;
		RTC_Minute = RTC_Minute - 180;
	}
	else if (RTC_Minute > 239 && RTC_Minute <= 299)
	{
		RTC_Hour = RTC_Hour + 4;
		RTC_Minute = RTC_Minute - 240;
	}
	else
	{
		//这里应该有报错处理？
	}

	if (RTC_Hour == 24)
	{
		RTC_Day = RTC_Day + 1;
		RTC_Hour = 0;
	}
	else if (RTC_Hour > 24 && RTC_Hour <= 47)
	{
		RTC_Day = RTC_Day + 1;
		RTC_Hour = RTC_Hour - 24;
	}
	else if (RTC_Hour > 48 && RTC_Hour <= 71)
	{
		RTC_Day = RTC_Day + (RTC_Hour % 24);
		RTC_Hour = RTC_Hour - ((RTC_Hour % 24) * 24);
	}


	if (RTC_Month == 1 || RTC_Month == 3 || RTC_Month == 5 || RTC_Month == 7 || RTC_Month == 8 || RTC_Month == 10 || RTC_Month == 12)
	{
		if (RTC_Day == 32)
		{
			RTC_Month = RTC_Month + 1;
			RTC_Day = 1;
		}
		else if (RTC_Day > 32 && RTC_Day <= 60)
		{
			RTC_Month = RTC_Month + 1;
			RTC_Day = RTC_Day - 31;
		}
	}
	else if (RTC_Month == 2 || RTC_Month == 4 || RTC_Month == 6 || RTC_Month == 9 || RTC_Month == 11)
	{
		if (RTC_Day == 31)
		{
			RTC_Month = RTC_Month + 1;
			RTC_Day = 1;
		}
		else if (RTC_Day > 31 && RTC_Day <= 59)
		{
			RTC_Month = RTC_Month + 1;
			RTC_Day = RTC_Day - 30;
		}
	}


	if (RTC_Month == 13)
	{
		RTC_Year = RTC_Year + 1;
		RTC_Month = 1;
	}
	else if (RTC_Month > 13 && RTC_Month <= 24)
	{
		RTC_Year = RTC_Year + 1;
		RTC_Month = RTC_Month - 12;
	}
	else if (RTC_Month > 24 && RTC_Month <= 35)
	{
		RTC_Year = RTC_Year + 2;
		RTC_Month = RTC_Month - 24;
	}

	if (RTC_Year == 99)
	{
		RTC_Year = 0;
	}

	if (debug_print == 0x01)
	{
		if (Get_RTC_Flag() == 0x01)
		{
			Serial.println(String("RTC时间为："));
			Serial.println(String(RTC_Year) + "年" + RTC_Month + "月" + RTC_Day + "日" + RTC_Hour + "时" + RTC_Minute + "分" + RTC_Second + "秒");
			if (debug == 1)
			{
				delay(3500);
			}
		}
	}
}



//函 数 名：Receive_A023() 
//功能描述：A023的执行函数
//函数说明：设置某类型接口挂载的某一路子设备类型及工作组
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
void Receive_A023(unsigned char* Judgement_Data, int Judgement_Length)//A023函数
{
	//String AssStat, AssStat1, AssStat2;//Association_statement，关联语句1
	//--------------------------------------------------------
	//该区域为测试传输进Receive_A023函数的数据是否正确的测试代码块
	//需要测试时请取消注释
	if (debug_print == 1)
	{
		Serial.println("进入Receive_A023函数");
		for (int i = 0; i < Judgement_Length + 1; i++)
		{
			Serial.print("A023Judgement_Data ");
			Serial.print(i);
			Serial.print(" :");
			Serial.println(Judgement_Data[i], HEX);
			Serial.flush();
			delay(1);
		}
		delay(200);
		Serial.print("Judgement_Length = ");
		Serial.println(Judgement_Length);
	}
	//--------------------------------------------------------
	//这里还要记得改回来
	//区域正确并且存储的语句小于5句
	if (Judgement_Data[7] == 0x01/*AT24CXX_ReadOneByte(12)*/ && AT24CXX_ReadOneByte(A_Policy_Relevance_flag) < 5)
	{
		Storage_bytes_Flag = AT24CXX_ReadOneByte(A_Storage_bytes_Flag);
		if (debug_print == 1)
		{
			Serial.println(String("Storage_bytes_Flag = ") + Storage_bytes_Flag);
		}
		if (Storage_bytes_Flag + Judgement_Length <= AT24C02_bytes)
		{
			int Storage_bytes_Flag_1 = Storage_bytes_Flag;//开始存储的位置值
			int JD_x = 0;//for循环增量
			int Storage_Check = 0;//存储校验
			int Sentence_num = 0;//策略语句的个数
			int Sentence_begin[5];//策略语句的开始处
			int Sentence_end[5];//策略语句的开始处
			//========================================

			//将Storage_bytes_Flag的值更新为结尾
			Storage_bytes_Flag = Storage_bytes_Flag + Judgement_Length;
			int Storage_bytes_Flag_2 = Storage_bytes_Flag;//将结尾的值赋给Storage_bytes_Flag_2
			if (debug_print == 1)
			{
				Serial.println(String("Storage_bytes_Flag = ") + Storage_bytes_Flag);
			}
			//将Storage_bytes_Flag的值+1写入EEPROM，作为下一次语句存储的初始值
			AT24CXX_WriteOneByte(A_Storage_bytes_Flag, Storage_bytes_Flag + 1);

			Sentence_num = AT24CXX_ReadOneByte(A_Policy_Relevance_flag);//先读取出已经存在的策略语句的个数
			Sentence_num = Sentence_num + 1;//然后增加一句策略语句
			AT24CXX_WriteOneByte(A_Policy_Relevance_flag, Sentence_num);//在将这个值重新写入到EEPROM
			if (debug_print == 1)
			{
				Serial.println(String("AT24CXX[") + A_Policy_Relevance_flag + "] = " + String(AT24CXX_ReadOneByte(A_Policy_Relevance_flag)));
			}

			//这里是将策略帧写入EEPROM，并输出校验位Storage_Check
			for (size_t i = Storage_bytes_Flag_1; i <= Storage_bytes_Flag_2; i++)
			{
				AT24CXX_WriteOneByte(i, Judgement_Data[JD_x]);
				if (debug_print == 1)
				{
					Serial.println(String("Judgement_Data[") + JD_x + "] = " + String(Judgement_Data[JD_x], HEX));
					Serial.println(String("AT24CXX[") + i + "] = " + String(AT24CXX_ReadOneByte(i), HEX));
					Serial.flush();
				}
				if (AT24CXX_ReadOneByte(i) == Judgement_Data[JD_x])
				{
					Storage_Check++;
				}
				JD_x++;
			}

			if (debug_print == 1)
			{
				Serial.println(String("Storage_Check = ") + Storage_Check);
			}

			if (Storage_Check == Judgement_Length + 1)
			{
				E015_status = Set_association_status_succeed;
				if (debug_print == 1)
				{
					Serial.println(String("E015_status = Set_association_status_succeed") + String(E015_status));
				}
			}
			else
			{
				E015_status = Set_association_status_failed;
				if (debug_print == 1)
				{
					Serial.println(String("E015_status = Set_association_status_failed") + String(E015_status));
				}
			}

			//--------这里是将开始与结束位置的值写入对应的EEPROM----------
			if (Sentence_num == 1)
			{
				AT24CXX_WriteOneByte(A_Begin_policy_statement_1, Storage_bytes_Flag_1);//开始位置1的写入
				AT24CXX_WriteOneByte(A_End_policy_statement_1, Storage_bytes_Flag);//结束位置1的写入
				if (debug_print == 1)
				{
					Serial.println(String("AT24CXX[") + A_Begin_policy_statement_1 + "] = " + String(AT24CXX_ReadOneByte(A_Begin_policy_statement_1)));
					Serial.println(String("AT24CXX[") + A_End_policy_statement_1 + "] = " + String(AT24CXX_ReadOneByte(A_End_policy_statement_1)));
				}
			}
			else if (Sentence_num == 2)
			{
				AT24CXX_WriteOneByte(A_Begin_policy_statement_2, Storage_bytes_Flag_1);//开始位置2的写入
				AT24CXX_WriteOneByte(A_End_policy_statement_2, Storage_bytes_Flag);//结束位置2的写入
				if (debug_print == 1)
				{
					Serial.println(String("AT24CXX[") + A_Begin_policy_statement_2 + "] = " + String(AT24CXX_ReadOneByte(A_Begin_policy_statement_2)));
					Serial.println(String("AT24CXX[") + A_End_policy_statement_2 + "] = " + String(AT24CXX_ReadOneByte(A_End_policy_statement_2)));
				}
			}
			else if (Sentence_num == 3)
			{
				AT24CXX_WriteOneByte(A_Begin_policy_statement_3, Storage_bytes_Flag_1);//开始位置2的写入
				AT24CXX_WriteOneByte(A_End_policy_statement_3, Storage_bytes_Flag);//结束位置2的写入
				if (debug_print == 1)
				{
					Serial.println(String("AT24CXX[") + A_Begin_policy_statement_3 + "] = " + String(AT24CXX_ReadOneByte(A_Begin_policy_statement_3)));
					Serial.println(String("AT24CXX[") + A_End_policy_statement_3 + "] = " + String(AT24CXX_ReadOneByte(A_End_policy_statement_3)));
				}
			}
			else if (Sentence_num == 4)
			{
				AT24CXX_WriteOneByte(A_Begin_policy_statement_4, Storage_bytes_Flag_1);//开始位置2的写入
				AT24CXX_WriteOneByte(97, Storage_bytes_Flag);//结束位置2的写入
				if (debug_print == 1)
				{
					Serial.println(String("AT24CXX[") + A_Begin_policy_statement_4 + "] = " + String(AT24CXX_ReadOneByte(A_Begin_policy_statement_4)));
					Serial.println(String("AT24CXX[") + A_End_policy_statement_4 + "] = " + String(AT24CXX_ReadOneByte(A_End_policy_statement_4)));
				}
			}
			else if (Sentence_num == 5)
			{
				AT24CXX_WriteOneByte(A_Begin_policy_statement_5, Storage_bytes_Flag_1);//开始位置2的写入
				AT24CXX_WriteOneByte(A_End_policy_statement_5, Storage_bytes_Flag);//结束位置2的写入
				if (debug_print == 1)
				{
					Serial.println(String("AT24CXX[") + A_Begin_policy_statement_5 + "] = " + String(AT24CXX_ReadOneByte(A_Begin_policy_statement_5)));
					Serial.println(String("AT24CXX[") + A_End_policy_statement_5 + "] = " + String(AT24CXX_ReadOneByte(A_End_policy_statement_5)));
				}
			}
			else
			{
				//这里是因为存储的语句超过上限
				E015_status = State_Storage_Exceeding_the_Upper_Limit;
				if (debug_print == 1)
				{
					Serial.println(String("E015_status = State_Storage_Exceeding_the_Upper_Limit") + String(E015_status));
				}
			}
			//------------------------------------------------------
		}
		else
		{
			//代表存储空间不足
			E015_status = State_Storage_Exceeding_the_Upper_Limit;
			if (debug_print == 1)
			{
				Serial.println(String("E015_status = State_Storage_Exceeding_the_Upper_Limit") + String(E015_status));
			}
		}

		//是否广播指令
		Receive_IsBroadcast = Judgement_Data[6];

		//进行状态的回执
		Send_E015(Receive_IsBroadcast, E015_status);
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
		Serial.println("完成A023状态回执");
		Serial.println("结束Receive_A023函数");
	}


	//将自动策略开启
	//if (Judgement_Data[7] == 0x01/*AT24CXX_ReadOneByte(12)*/)
	//{
	//	//先将字符串数组拼接成Strring字符串，读取出来
	//	for (size_t i = 8; i <= Judgement_Length-7; i++)
	//	{
	//		//强制转换为char类型
	//		AssStat.concat(String(char(Judgement_Data[i])));//拼接成关联语句，AssStat
	//	}
	//	if (debug_print == 1)
	//	{
	//		Serial.println(AssStat);
	//	}
	//}

	//array_print_test();
	////先分割#，分割为条件语句以及执行语句
	//data_processing(AssStat);
}

//函 数 名：Receive_A024() 
//功能描述：A024的执行函数
//函数说明：(设置预留字段（B\I\T\C\D）值)
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
void Receive_A024(unsigned char* Judgement_Data, int Judgement_Length)//A024函数
{
	//--------------------------------------------------------
	//该区域为测试传输进Receive_A024函数的数据是否正确的测试代码块
	//需要测试时请取消注释
	if (debug_print == 1)
	{
		Serial.println("进入Receive_A024函数");
		for (int i = 0; i < Judgement_Length + 1; i++)
		{
			Serial.print("A024Judgement_Data ");
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
		//设置Bool类型的预留字段
		if (Judgement_Data[8] == 0x01)
		{
			//判断数据长度
			if (Judgement_Data[3] == 0x06)
			{
				AT24CXX_WriteOneByte(A_bool_type_reserved_field, Judgement_Data[9]);
				if (AT24CXX_ReadOneByte(A_bool_type_reserved_field) == Judgement_Data[9])
				{
					E015_status = SetParamsOk;

				}
				else
				{
					E015_status = SetParamsErr;
				}
			}
		}
		//设置Int类型预留字段
		else if (Judgement_Data[8] == 0x02)
		{
			//判断数据长度
			if (Judgement_Data[3] == 0x0D)
			{
				//Serial.println("...........");
				//57-64,9-16
				AT24CXX_WriteOneByte(A_int_type_reserved_field_1, Judgement_Data[9]);
				AT24CXX_WriteOneByte(A_int_type_reserved_field_2, Judgement_Data[10]);
				AT24CXX_WriteOneByte(A_int_type_reserved_field_3, Judgement_Data[11]);
				AT24CXX_WriteOneByte(A_int_type_reserved_field_4, Judgement_Data[12]);
				AT24CXX_WriteOneByte(A_int_type_reserved_field_5, Judgement_Data[13]);
				AT24CXX_WriteOneByte(A_int_type_reserved_field_6, Judgement_Data[14]);
				AT24CXX_WriteOneByte(A_int_type_reserved_field_7, Judgement_Data[15]);
				AT24CXX_WriteOneByte(A_int_type_reserved_field_8, Judgement_Data[16]);
				if (Verification_Reserved_field(Judgement_Data, A_int_type_reserved_field_1) == 1)
				{
					E015_status = SetParamsOk;
				}
				else
				{
					E015_status = SetParamsErr;
				}
			}
			else
			{
				if (debug_print == 1)
				{
					Serial.println("数据长度错误");
				}
			}
		}
		//设置T定时器预留字段
		else if (Judgement_Data[8] == 0x03)
		{
			//判断数据长度
			if (Judgement_Data[3] == 0x0D)
			{
				//65-72,9-16
				AT24CXX_WriteOneByte(A_T_Timer_Reserved_Field_1, Judgement_Data[9]);
				AT24CXX_WriteOneByte(A_T_Timer_Reserved_Field_2, Judgement_Data[10]);
				AT24CXX_WriteOneByte(A_T_Timer_Reserved_Field_3, Judgement_Data[11]);
				AT24CXX_WriteOneByte(A_T_Timer_Reserved_Field_4, Judgement_Data[12]);
				AT24CXX_WriteOneByte(A_T_Timer_Reserved_Field_5, Judgement_Data[13]);
				AT24CXX_WriteOneByte(A_T_Timer_Reserved_Field_6, Judgement_Data[14]);
				AT24CXX_WriteOneByte(A_T_Timer_Reserved_Field_7, Judgement_Data[15]);
				AT24CXX_WriteOneByte(A_T_Timer_Reserved_Field_8, Judgement_Data[16]);
				if (Verification_Reserved_field(Judgement_Data, A_T_Timer_Reserved_Field_1) == 1)
				{
					E015_status = SetParamsOk;
				}
				else
				{
					E015_status = SetParamsErr;
				}
			}
			else
			{
				if (debug_print == 1)
				{
					Serial.println("数据长度错误");
				}
			}
		}
		//设置C计数器预留字段
		else if (Judgement_Data[8] == 0x04)
		{
			//判断数据长度
			if (Judgement_Data[3] == 0x0D)
			{
				//73-80,9-16
				AT24CXX_WriteOneByte(A_C_Counter_reserved_field_1, Judgement_Data[9]);
				AT24CXX_WriteOneByte(A_C_Counter_reserved_field_2, Judgement_Data[10]);
				AT24CXX_WriteOneByte(A_C_Counter_reserved_field_3, Judgement_Data[11]);
				AT24CXX_WriteOneByte(A_C_Counter_reserved_field_4, Judgement_Data[12]);
				AT24CXX_WriteOneByte(A_C_Counter_reserved_field_5, Judgement_Data[13]);
				AT24CXX_WriteOneByte(A_C_Counter_reserved_field_6, Judgement_Data[14]);
				AT24CXX_WriteOneByte(A_C_Counter_reserved_field_7, Judgement_Data[15]);
				AT24CXX_WriteOneByte(A_C_Counter_reserved_field_8, Judgement_Data[16]);
				if (Verification_Reserved_field(Judgement_Data, A_C_Counter_reserved_field_1) == 1)
				{
					E015_status = SetParamsOk;
				}
				else
				{
					E015_status = SetParamsErr;
				}
			}
			else
			{
				if (debug_print == 1)
				{
					Serial.println("数据长度错误");
				}

			}
		}
		//设置D延时预留字段
		else if (Judgement_Data[8] == 0x05)
		{
			//判断数据长度
			if (Judgement_Data[3] == 0x0D)
			{
				//81-88,9-16
				AT24CXX_WriteOneByte(A_D_Delay_Reserved_Field_1, Judgement_Data[9]);
				AT24CXX_WriteOneByte(A_D_Delay_Reserved_Field_2, Judgement_Data[10]);
				AT24CXX_WriteOneByte(A_D_Delay_Reserved_Field_3, Judgement_Data[11]);
				AT24CXX_WriteOneByte(A_D_Delay_Reserved_Field_4, Judgement_Data[12]);
				AT24CXX_WriteOneByte(A_D_Delay_Reserved_Field_5, Judgement_Data[13]);
				AT24CXX_WriteOneByte(A_D_Delay_Reserved_Field_6, Judgement_Data[14]);
				AT24CXX_WriteOneByte(A_D_Delay_Reserved_Field_7, Judgement_Data[15]);
				AT24CXX_WriteOneByte(A_D_Delay_Reserved_Field_8, Judgement_Data[16]);
				if (Verification_Reserved_field(Judgement_Data, A_D_Delay_Reserved_Field_1) == 1)
				{
					E015_status = SetParamsOk;
				}
				else
				{
					E015_status = SetParamsErr;
				}
			}
			else
			{
				if (debug_print == 1)
				{
					Serial.println("数据长度错误");
				}
			}
		}
		else
		{
			if (debug_print == 1)
			{
				Serial.println("不存在的字段");
			}
		}

		//是否广播指令
		Receive_IsBroadcast = Judgement_Data[6];

		//进行状态的回执
		Send_E015(Receive_IsBroadcast, E015_status);
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
		Serial.println("完成A024状态回执");
		Serial.println("结束Receive_A024函数");
	}
}

//函 数 名：Send_E022() 
//功能描述：回执剩余时间E022的函数
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
unsigned char Send_E022(int Receive_IsBroadcast)
{
	E022_init();//将E022的值重置为初始值

	E022_IsBroadcast = Receive_IsBroadcast;//E022的是否广播指令

	E022[0] = E022_FrameHead;
	E022[1] = E022_FrameId1;
	E022[2] = E022_FrameId2;
	E022[3] = E022_DataLen;
	E022[4] = E022_DeviceTypeID1;
	E022[5] = E022_DeviceTypeID2;
	E022[6] = E022_IsBroadcast;
	E022[7] = E022_ZoneId;

	E022[8] = E022_DO1_SetTime1;
	E022[9] = E022_DO1_SetTime2;
	E022[10] = E022_DO1_SetTime3;
	E022[11] = E022_DO1_RemainTime1;
	E022[12] = E022_DO1_RemainTime2;
	E022[13] = E022_DO1_RemainTime3;

	E022[14] = E022_DO2_SetTime1;
	E022[15] = E022_DO2_SetTime2;
	E022[16] = E022_DO2_SetTime3;
	E022[17] = E022_DO2_RemainTime1;
	E022[18] = E022_DO2_RemainTime2;
	E022[19] = E022_DO2_RemainTime3;

	E022[20] = E022_DO3_SetTime1;
	E022[21] = E022_DO3_SetTime2;
	E022[22] = E022_DO3_SetTime3;
	E022[23] = E022_DO3_RemainTime1;
	E022[24] = E022_DO3_RemainTime2;
	E022[25] = E022_DO3_RemainTime3;

	E022[26] = E022_DO4_SetTime1;
	E022[27] = E022_DO4_SetTime2;
	E022[28] = E022_DO4_SetTime3;
	E022[29] = E022_DO4_RemainTime1;
	E022[30] = E022_DO4_RemainTime2;
	E022[31] = E022_DO4_RemainTime3;

	E022[32] = E022_AO1_SetTime1;
	E022[33] = E022_AO1_SetTime2;
	E022[34] = E022_AO1_SetTime3;
	E022[35] = E022_AO1_RemainTime1;
	E022[36] = E022_AO1_RemainTime2;
	E022[37] = E022_AO1_RemainTime3;

	E022[38] = E022_AO2_SetTime1;
	E022[39] = E022_AO2_SetTime2;
	E022[40] = E022_AO2_SetTime3;
	E022[41] = E022_AO2_RemainTime1;
	E022[42] = E022_AO2_RemainTime2;
	E022[43] = E022_AO2_RemainTime3;

	for (size_t i = 4; i <= E022_DataLen + 0x03; i++)
	{
		Check_Data[Check_Length] = E022[i];
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
		E022_CRC8 = GetCrc8(Check_Data, Check_Length);//得到CRC数据
		if (debug_print == 1)
		{
			Serial.print("CRC8计算的值E022_CRC8 = 0x");
			Serial.println(E022_CRC8, HEX);
		}
		Check_Length = 0;
	}

	E022[44] = E022_CRC8;
	E022[45] = E022_FrameEnd1;
	E022[46] = E022_FrameEnd2;
	E022[47] = E022_FrameEnd3;
	E022[48] = E022_FrameEnd4;
	E022[49] = E022_FrameEnd5;
	E022[50] = E022_FrameEnd6;

	//该区域为串口查看E020回执的信息
	if (debug_print == 1)
	{
		for (int i = 0; i < 51; i++)
		{
			Serial.print(i);
			Serial.print("/");
			Serial.println(E022[i], HEX);
			delay(1);
		}
	}

	Serial3.write(E022, 51);
	Serial3.flush();
	Send_Data_Lamp();//发送数据灯

	return 0;
}

//函 数 名：E022_init() 
//功能描述：E022的初始化函数
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
unsigned char E022_init()
{
	E022_FrameHead = 0xFE;		//E022的帧头

	E022_FrameId1 = 0xE0;		//E022的帧ID1
	E022_FrameId2 = 0x22;		//E022的帧ID2

	E022_DataLen = 0x28;		//E022的数据长度

	E022_DeviceTypeID1 = 0xC0;	//E022的设备类型1
	E022_DeviceTypeID2 = 0x02;	//E022的设备类型2

	E022_IsBroadcast = 0x00;		//E022的是否广播指令

	E022_ZoneId = AT24CXX_ReadOneByte(12);			//E022的区域

	E022_DO1_SetTime1 = DO1_SetWorkSec1;
	E022_DO1_SetTime2 = DO1_SetWorkSec2;
	E022_DO1_SetTime3 = DO1_SetWorkSec3;

	E022_DO1_RemainTime1 = DO1_RemainWorkSec1;
	E022_DO1_RemainTime2 = DO1_RemainWorkSec2;
	E022_DO1_RemainTime3 = DO1_RemainWorkSec3;

	E022_DO2_SetTime1 = DO2_SetWorkSec1;
	E022_DO2_SetTime2 = DO2_SetWorkSec2;
	E022_DO2_SetTime3 = DO2_SetWorkSec3;

	E022_DO2_RemainTime1 = DO2_RemainWorkSec1;
	E022_DO2_RemainTime2 = DO2_RemainWorkSec2;
	E022_DO2_RemainTime3 = DO2_RemainWorkSec3;

	E022_DO2_SetTime1 = DO2_SetWorkSec1;
	E022_DO2_SetTime2 = DO2_SetWorkSec2;
	E022_DO2_SetTime3 = DO2_SetWorkSec3;

	E022_DO2_RemainTime1 = DO2_RemainWorkSec1;
	E022_DO2_RemainTime2 = DO2_RemainWorkSec2;
	E022_DO2_RemainTime3 = DO2_RemainWorkSec3;

	E022_DO3_SetTime1 = DO3_SetWorkSec1;
	E022_DO3_SetTime2 = DO3_SetWorkSec2;
	E022_DO3_SetTime3 = DO3_SetWorkSec3;

	E022_DO3_RemainTime1 = DO3_RemainWorkSec1;
	E022_DO3_RemainTime2 = DO3_RemainWorkSec2;
	E022_DO3_RemainTime3 = DO3_RemainWorkSec3;

	E022_DO4_SetTime1 = DO4_SetWorkSec1;
	E022_DO4_SetTime2 = DO4_SetWorkSec2;
	E022_DO4_SetTime3 = DO4_SetWorkSec3;

	E022_DO4_RemainTime1 = DO4_RemainWorkSec1;
	E022_DO4_RemainTime2 = DO4_RemainWorkSec2;
	E022_DO4_RemainTime3 = DO4_RemainWorkSec3;

	E022_AO1_SetTime1 = AO1_SetWorkSec1;
	E022_AO1_SetTime2 = AO1_SetWorkSec2;
	E022_AO1_SetTime3 = AO1_SetWorkSec3;

	E022_AO1_RemainTime1 = AO1_RemainWorkSec1;
	E022_AO1_RemainTime2 = AO1_RemainWorkSec2;
	E022_AO1_RemainTime3 = AO1_RemainWorkSec3;

	E022_AO2_SetTime1 = AO2_SetWorkSec1;
	E022_AO2_SetTime2 = AO2_SetWorkSec2;
	E022_AO2_SetTime3 = AO2_SetWorkSec3;

	E022_AO2_RemainTime1 = AO2_RemainWorkSec1;
	E022_AO2_RemainTime2 = AO2_RemainWorkSec2;
	E022_AO2_RemainTime3 = AO2_RemainWorkSec3;

	E022_CRC8 = 0x00;

	E022_FrameEnd1 = 0x0D;
	E022_FrameEnd2 = 0x0A;
	E022_FrameEnd3 = 0x0D;
	E022_FrameEnd4 = 0x0A;
	E022_FrameEnd5 = 0x0D;
	E022_FrameEnd6 = 0x0A;

	return 0;
}

//函 数 名：Send_E023() 
//功能描述：心跳帧
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
unsigned char Send_E023(int Receive_IsBroadcast)
{
	E023_init();//将E023的值重置为初始值

	E023_IsBroadcast = Receive_IsBroadcast;//E023的是否广播指令

	E023[0] = E023_FrameHead;
	E023[1] = E023_FrameId1;
	E023[2] = E023_FrameId2;
	E023[3] = E023_DataLen;
	E023[4] = E023_DeviceTypeID1;
	E023[5] = E023_DeviceTypeID2;
	E023[6] = E023_IsBroadcast;
	E023[7] = E023_ZoneId;
	E023[8] = E023_Year;
	E023[9] = E023_Month;
	E023[10] = E023_Day;
	E023[11] = E023_Hour;
	E023[12] = E023_Minute;
	E023[13] = E023_Second;

	for (size_t i = 4; i <= E023_DataLen + 0x03; i++)
	{
		Check_Data[Check_Length] = E023[i];
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
	if (debug_print == 1)
	{
		Serial.print("Check_Length = ");
		Serial.println(Check_Length);
	}

	if (Check_Length > 0)
	{
		E023_CRC8 = GetCrc8(Check_Data, Check_Length);//得到CRC数据
		if (debug_print == 1)
		{
			Serial.print("CRC8计算的值E023_CRC8 = 0x");
			Serial.println(E023_CRC8, HEX);
		}
		Check_Length = 0;
	}

	E023[14] = E023_CRC8;
	E023[15] = E023_FrameEnd1;
	E023[16] = E023_FrameEnd2;
	E023[17] = E023_FrameEnd3;
	E023[18] = E023_FrameEnd4;
	E023[19] = E023_FrameEnd5;
	E023[20] = E023_FrameEnd6;

	//该区域为串口查看E020回执的信息
	if (debug_print == 1)
	{
		for (int i = 0; i < 21; i++)
		{
			Serial.print(i);
			Serial.print("/");
			Serial.println(E023[i], HEX);
			delay(1);
		}
	}

	Serial3.write(E023, 21);
	Serial3.flush();
	Send_Data_Lamp();//发送数据灯

	return 0;
}

//函 数 名：E023_init() 
//功能描述：E023的初始化函数
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
unsigned char E023_init()
{
	HeartBeat_oldtime = millis();//定时上报状态，在这里进行赋值

	E023_FrameHead = 0xFE;

	E023_FrameId1 = 0xE0;
	E023_FrameId2 = 0x23;

	E023_DataLen = 0x0D;

	E023_DeviceTypeID1 = 0xC0;
	E023_DeviceTypeID2 = 0x02;

	E023_IsBroadcast = 0x00;

	E023_ZoneId = AT24CXX_ReadOneByte(12);;

	E023_Year = RTC_Year;
	E023_Month = RTC_Month;
	E023_Day = RTC_Day;
	E023_Hour = RTC_Hour;
	E023_Minute = RTC_Minute;
	E023_Second = RTC_Second;

	E023_CRC8 = 0x00;

	E023_FrameEnd1 = 0x0D;
	E023_FrameEnd2 = 0x0A;
	E023_FrameEnd3 = 0x0D;
	E023_FrameEnd4 = 0x0A;
	E023_FrameEnd5 = 0x0D;
	E023_FrameEnd6 = 0x0A;
	return 0;
}

//函 数 名：Send_E024() 
//功能描述：请求RTC时间
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
unsigned char Send_E024(int Receive_IsBroadcast)
{
	E024_init();//将E024的值重置为初始值

	E024[0] = E024_FrameHead;
	E024[1] = E024_FrameId1;
	E024[2] = E024_FrameId2;
	E024[3] = E024_DataLen;
	E024[4] = E024_DeviceTypeID1;
	E024[5] = E024_DeviceTypeID2;
	E024[6] = E024_IsBroadcast;
	E024[7] = E024_ZoneId;
	E024[8] = E024_Allocate1;
	E024[9] = E024_Allocate2;
	E024[10] = E024_Allocate3;
	E024[11] = E024_Allocate4;
	E024[12] = E024_Allocate5;
	E024[13] = E024_Allocate6;
	E024[14] = E024_Allocate7;
	E024[15] = E024_Allocate8;

	for (size_t i = 4; i <= E024_DataLen + 0x03; i++)
	{
		Check_Data[Check_Length] = E024[i];
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
	if (debug_print == 1)
	{
		Serial.print("Check_Length = ");
		Serial.println(Check_Length);
	}

	if (Check_Length > 0)
	{
		E024_CRC8 = GetCrc8(Check_Data, Check_Length);//得到CRC数据
		if (debug_print == 1)
		{
			Serial.print("CRC8计算的值E020_CRC8 = 0x");
			Serial.println(E024_CRC8, HEX);
		}
		Check_Length = 0;
	}

	E024[17] = E024_CRC8;
	E024[18] = E024_FrameEnd1;
	E024[19] = E024_FrameEnd2;
	E024[20] = E024_FrameEnd3;
	E024[21] = E024_FrameEnd4;
	E024[22] = E024_FrameEnd5;
	E024[23] = E024_FrameEnd6;

	//该区域为串口查看E024回执的信息
	if (debug_print == 1)
	{
		for (int i = 0; i < 23; i++)
		{
			Serial.print(i);
			Serial.print("/");
			Serial.println(E024[i], HEX);
			delay(1);
		}
	}

	Serial3.write(E024, 23);
	Serial3.flush();
	Send_Data_Lamp();//发送数据灯

	return 0;
}


//函 数 名：E024_init() 
//功能描述：E024的初始化函数
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
unsigned char E024_init()
{
	E024_FrameHead = 0xFE;

	E024_FrameId1 = 0xE0;
	E024_FrameId2 = 0x24;

	E024_DataLen = 0x0C;

	E024_DeviceTypeID1 = 0xC0;
	E024_DeviceTypeID2 = 0x02;

	E024_IsBroadcast = 0x00;

	E024_ZoneId = AT24CXX_ReadOneByte(12);;

	E024_Allocate1 = 0x00;
	E024_Allocate2 = 0x00;
	E024_Allocate3 = 0x00;
	E024_Allocate4 = 0x00;
	E024_Allocate5 = 0x00;
	E024_Allocate6 = 0x00;
	E024_Allocate7 = 0x00;
	E024_Allocate8 = 0x00;

	E024_CRC8 = 0x00;

	E024_FrameEnd1 = 0x0D;
	E024_FrameEnd2 = 0x0A;
	E024_FrameEnd3 = 0x0D;
	E024_FrameEnd4 = 0x0A;
	E024_FrameEnd5 = 0x0D;
	E024_FrameEnd6 = 0x0A;
	return 0;
}
