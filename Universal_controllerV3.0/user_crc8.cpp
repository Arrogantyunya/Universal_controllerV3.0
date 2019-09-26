//user_crc8.cpp
/*
*版权
*
* 文件名称:user_crc8.cpp
* 文件标识:配置管理计划书
* 摘要:crc8校验值的计算对比
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

#include "user_crc8.h"


//函 数 名：GetCrc8() 
//功能描述：
//函数说明：CRC8的函数
//调用函数：
//全局变量：
//输 入：需要CRC8校验的数组段
//返 回：CRC8计算得到的数值
/////////////////////////////////////////////////////////////////////
unsigned char GetCrc8(unsigned char * Check_Data, int Check_Length)
{
	unsigned char cFcs = 0;
	int i, j;

	for (i = 0; i < Check_Length; i++)
	{
		//   Serial.print(data[i], HEX);
		//   Serial.print(" ");
		cFcs ^= Check_Data[i];
		for (j = 0; j < 8; j++)
		{
			if (cFcs & 1)
			{
				cFcs = (unsigned char)((cFcs >> 1) ^ AL2_FCS_COEF);
			}
			else
			{
				cFcs >>= 1;
			}
		}
	}
	return cFcs;
}