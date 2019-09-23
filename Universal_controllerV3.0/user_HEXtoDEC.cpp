// 
// 
// 

#include "user_HEXtoDEC.h"

//将字符'0' ~ 'D'转换为相应的数字
//返回值：字符转换完成一会对应的数值
u8 chrtodec(char chr)
{
	u8 value = 0;

	//先全部将小写转换为大写
	if ((chr >= 'a') && (chr <= 'z'))
		chr = chr - 32;

	//将字符转化成相应的数字
	if ((chr >= '0') && (chr <= '9'))
		value = chr - 48;
	else if ((chr >= 'A') && (chr <= 'Z'))
		value = chr - 65 + 10;

	return value;
}

//计算n个16相乘
//n:16相称的次数
//返回值：计算出来的结果
int cal16match(u8 n)
{
	u8 i = 0;
	int value = 1;

	for (i = 0; i < n; i++)
		value *= 16;

	return value;
}


//将字符串格式的十六进制转换为数字型，
//如字符串“0x16”转换为int型的22。
//参数 chr: 要转换的字符串，不区分大小写！！！！
//返回值：参数chr转换完成以后的十进制数值
int charhex_to_dec(char *chr)
{
	u8 i, chrlen;
	u8 sta = 0; //标记要转换的字符串是否以0x,或者0X开头
	int chrtoint = 0;
	int value = 0;

	chrlen = strlen(chr);//自动获取需要转换的字符个数
	//chrlen = 3;//这是传入的字符个数，根据需要更改

	//检查字符串是否是以0x或者0X开头的。
	if ((chr[0] == '0') && ((chr[1] == 'x') || (chr[1] == 'X')))
	{
		sta = 2;        //标记以0x，0X开头
		chrlen = chrlen - 2;
	}

	//计算
	for (i = 0; i < chrlen; i++)
	{
		chrtoint = chrtodec(chr[sta + i]);
		if (i != (chrlen - 1))                //不是最后一位
			value += chrtoint * cal16match(chrlen - 1 - i);
		else if (i == (chrlen - 1))         //最后一位
			value += chrtoint;
	}
	//Serial.print("value = ");
	//Serial.println(value);
	return value;
}
