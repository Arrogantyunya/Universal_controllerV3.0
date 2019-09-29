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

		//Send_E022(Receive_IsBroadcast);//各路数剩余时间的回执
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
					//Send_E022(Receive_IsBroadcast);//各路数时间的回执
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
					//Send_E022(Receive_IsBroadcast);//各路数时间的回执
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
					//Send_E022(Receive_IsBroadcast);//各路数时间的回执
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
					//Send_E022(Receive_IsBroadcast);//各路数时间的回执
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
					//Send_E022(Receive_IsBroadcast);//各路数时间的回执
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
					//Send_E022(Receive_IsBroadcast);//各路数时间的回执
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



//函 数 名：Receive_A023() 
//功能描述：A023的执行函数
//函数说明：设置某类型接口挂载的某一路子设备类型及工作组
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
//void Receive_A023(unsigned char* Judgement_Data, int Judgement_Length)
//{
//
//}

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
