//user_judgement.cpp
/*
*版权
*
* 文件名称:user_judgement.cpp
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

#include "user_judgement.h"//引用头文件
#include "user_A011_E011.h"
#include "user_A021_E021.h"
#include "user_A025_E025.h"
#include "user_Set_Correlation.h"



//函 数 名：Judgement_function() 
//功能描述：判断的函数
//函数说明：
//调用函数：
//全局变量：
//输 入：
//返 回：
/////////////////////////////////////////////////////////////////////
unsigned char Judgement_function(unsigned char * Judgement_Data, int Judgement_Length, int CRC_Check_num)//判断函数
{
	//判断帧头是否是0xFE
	if (Judgement_Data[0] == 0xFE)
	{
		//判断帧尾
		if (Judgement_Data[Judgement_Length - 5] == 0x0D && Judgement_Data[Judgement_Length - 4] == 0x0A &&
			Judgement_Data[Judgement_Length - 3] == 0x0D && Judgement_Data[Judgement_Length - 2] == 0x0A &&
			Judgement_Data[Judgement_Length - 1] == 0x0D && Judgement_Data[Judgement_Length - 0] == 0x0A)
		{
			//CRC8校验位的判断
			if (Judgement_Data[Judgement_Length - 6] == CRC_Check_num || debug_crc == 1)
			{
				//判断数据长度
				//Judgement_Data总长度为28（0x1C），但是Judgement_Length的值为27（0x1B）
				//所以需要将Judgement_Length加上0x01
				//实际数据长度为17（0x11）
				if (Judgement_Data[3] == Judgement_Length + 0x01 - 0x0B)
				{
					//判断设备类型
					if (Judgement_Data[4] == 0xC0 && Judgement_Data[5] == 0x02)
					{
						//判断帧ID
						if (Judgement_Data[1] == 0xA0 && Judgement_Data[2] == 0x11)//帧ID为A011
						{
							//帧ID为A011
							//进入A011的判断函数
							if (debug_print == 1)
							{
								Serial.println("帧ID为A011");
							}
							Receive_A011(Judgement_Data, Judgement_Length);
						}
						else if (Judgement_Data[1] == 0xA0 && Judgement_Data[2] == 0x12)//帧ID为A012
						{
							//帧ID为A012
							//进入A012的判断函数
							if (debug_print == 1)
							{
								Serial.println("帧ID为A012");
							}
							//Receive_A012(Judgement_Data, Judgement_Length);
						}
						else if (Judgement_Data[1] == 0xA0 && Judgement_Data[2] == 0x13)//帧ID为A013
						{
							//帧ID为A013
							//进入A013的判断函数
							if (debug_print == 1)
							{
								Serial.println("帧ID为A013");
							}
							Receive_A013(Judgement_Data, Judgement_Length);
						}
						else if (Judgement_Data[1] == 0xA0 && Judgement_Data[2] == 0x14)//帧ID为A014
						{
							//帧ID为A014
							//进入A014的判断函数
							if (debug_print == 1)
							{
								Serial.println("帧ID为A014");
							}
							Receive_A014(Judgement_Data, Judgement_Length);
						}
						else if (Judgement_Data[1] == 0xA0 && Judgement_Data[2] == 0x15)//帧ID为A015
						{
							//帧ID为A015
							//进入A015的判断函数
							if (debug_print == 1)
							{
								Serial.println("帧ID为A015");
							}
							//Receive_A015(Judgement_Data, Judgement_Length);
						}
						else if (Judgement_Data[1] == 0xA0 && Judgement_Data[2] == 0x18)//帧ID为A018
						{
							//帧ID为A018
							//进入A018的判断函数
							if (debug_print == 1)
							{
								Serial.println("帧ID为A018");
							}
							//Receive_A018(Judgement_Data, Judgement_Length);
						}
						else if (Judgement_Data[1] == 0xA0 && Judgement_Data[2] == 0x19)//帧ID为A019
						{
							//帧ID为A019
							//进入A019的判断函数
							if (debug_print == 1)
							{
								Serial.println("帧ID为A019");
							}
							//Receive_A019(Judgement_Data, Judgement_Length);
						}

						else if (Judgement_Data[1] == 0xA0 && Judgement_Data[2] == 0x20)//帧ID为A020
						{
							//帧ID为A020
							//进入A020的判断函数
							if (debug_print == 1)
							{
								Serial.println("帧ID为A020");
							}
							//Receive_A020(Judgement_Data, Judgement_Length);
						}
						else if (Judgement_Data[1] == 0xA0 && Judgement_Data[2] == 0x21)//帧ID为A021
						{
							//帧ID为A021
							//进入A021的判断函数
							if (debug_print == 1)
							{
								Serial.println("帧ID为A021");
							}
							//Receive_A021(Judgement_Data, Judgement_Length);
						}
						else if (Judgement_Data[1] == 0xA0 && Judgement_Data[2] == 0x22)//帧ID为A022
						{
							//帧ID为A022
							//进入A022的判断函数
							if (debug_print == 1)
							{
								Serial.println("帧ID为A022");
							}
							//Receive_A022(Judgement_Data, Judgement_Length);
						}
						else if (Judgement_Data[1] == 0xA0 && Judgement_Data[2] == 0x23)//帧ID为A023
						{
							//帧ID为A023
							//进入A023的判断函数
							if (debug_print == 1)
							{
								Serial.println("帧ID为A023");
							}
							//Receive_A023(Judgement_Data, Judgement_Length);
						}
						else if (Judgement_Data[1] == 0xA0 && Judgement_Data[2] == 0x24)//帧ID为A024
						{
							//帧ID为A024
							//进入A024的判断函数
							if (debug_print == 1)
							{
								Serial.println("帧ID为A024");
							}
							//Receive_A024(Judgement_Data, Judgement_Length);
						}
						else if (Judgement_Data[1] == 0xA0 && Judgement_Data[2] == 0x25)//帧ID为A025
						{
							//帧ID为A025
							//进入A025的判断函数
							if (debug_print == 1)
							{
								Serial.println("帧ID为A025");
							}
							//Receive_A025(Judgement_Data, Judgement_Length);
						}
						else
						{
							//帧ID错误
							Serial.println("Frame_ID_error帧ID错误");
							Serial.flush();
							Serial.println("该条指令被无视");
						}

					}
					else
					{
						//不存在的设备类型ID
						Serial.println("Nonexistent_device_type_ID不存在的设备类型ID");
						Serial.flush();
						Serial.println("该条指令被无视");
					}
				}
				else
				{
					//数据长度错误
					Serial.println("Data_Length_Error数据长度错误");
					Serial.flush();
					Serial.println("该条指令被无视");
				}
			}
			else
			{
				//CRC校验失败，数据不对
				Serial.println("CRC8_Check_FailureCRC8的校验失败");
				Serial.flush();
				Serial.println("该条指令被无视");
			}
		}
		else
		{
			//帧尾错误
			Serial.println("Frame_tail_error帧尾错误");
			Serial.flush();
			Serial.println("该条指令被无视");
		}
	}
	else if (Judgement_Data[0] == 0x00)
	{
		//正常清空导致的Judgement_Data[0] = 0x00进入，就不上报错误信息
		//我为什么会清空数组？？？？
		Serial.println("正常清空数组Normal Cleanup Array");
		Serial.flush();
	}
	else if (Judgement_Data[0] == 0x4C)
	{
		Serial.println("LORA已经自启动成功，以上数据为LORA信息");
		Serial.flush();
	}
	else
	{
		//帧头不对，数据错误
		Serial.println("Frame_header_error帧头错误");
		Serial.flush();
		Serial.println("该条指令被无视");
	}
}


/***
 *
 *   █████?█    ██  ▄████▄   ██ ▄█?       ██████╗ ██╗   ██╗ ██████╗
 * ▓██   ? ██  ▓██??██? ?█   ██▄█?        ██╔══██╗██║   ██║██╔════╝
 * ?████ ?▓██  ?██??▓█    ▄ ▓███▄?        ██████╔╝██║   ██║██║  ███╗
 * ?▓█?  ?▓▓█  ?██??▓▓▄ ▄██?▓██ █▄        ██╔══██╗██║   ██║██║   ██║
 * ??█?   ??█████▓ ? ▓███? ??██? █▄       ██████╔╝╚██████╔╝╚██████╔╝
 *  ? ?   ??▓? ? ? ? ?? ?  ?? ?? ▓?       ╚═════╝  ╚═════╝  ╚═════╝
 *  ?     ???? ? ?   ?  ?   ? ?? ??
 *  ? ?    ??? ? ? ?        ? ?? ?
 *           ?     ? ?      ?  ?
 */