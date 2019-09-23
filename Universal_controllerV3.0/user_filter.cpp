// user_filter.cpp
/*
*版权
*
* 文件名称:user_filter.cpp
* 文件标识:配置管理计划书
* 摘要:进行滤波
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

#include "user_filter.h"


//函 数 名：Filter() 
//功能描述：滤波函数
//函数说明：对输入的多个浮点数，进行滤波操作，
//调用函数：
//全局变量：
//输 入：浮点数数组以及数组长度
//返 回：浮点数的滤波值
/////////////////////////////////////////////////////////////////////
float Filter(float * filterData, int filterData_length)
{
	float average = 0.00;		//平均值
	float mode = 0.00;			//众数
	float median = 0.00;		//中位数
	float maximum = 0.00;		//最大值
	float minimum = 999999.99;	//最小值
	float sum = 0.00;			//和
	float nomaxmin_avr = 0.00;	//去掉最大最小值得平均数
	float filter_result = 0.00;	//滤波结果

	int temp = 0;				//一个桶
	int a_count = 0;			//第二个桶
	int count = 0;				//计数值
	int b_count = 0;			//


	//for (int i = 0; i < filterData_length; i++)//查看输入进来的值
	//{
	//	Serial.print("Filter");
	//	Serial.println(filterData[i]);
	//	delay(5);
	//}
	for (int i = 0; i < filterData_length; i++)//排序，方便计算
	{ 
		float temp;
		for (int j = i + 1; j < filterData_length; j++)
		{
			if (filterData[i] > filterData[j])
			{
				temp = filterData[i];
				filterData[i] = filterData[j];
				filterData[j] = temp;
			}
		}
	}

	for (int i = 0; i < filterData_length; i++)//输出排序的结果
	{
		Serial.print("排序");
		Serial.println(filterData[i]);
		delay(1);
	}

	for (int i = 0; i < filterData_length; i++)
	{
		if (maximum < filterData[i])
		{
			maximum = filterData[i];//最大值
		}
		if (minimum > filterData[i])
		{
			minimum = filterData[i];//最小值
		}
		sum = sum + filterData[i];//和
	}
	average = sum / filterData_length;//平均数
	nomaxmin_avr = (sum - maximum - minimum) / (filterData_length - 2);//去掉最大最小的平均数

	if (filterData_length % 2 == 0)//得到中位数
	{
		median = (filterData[filterData_length / 2 - 1] + filterData[filterData_length / 2]) / 2.0;
	}
	else
	{
		median = filterData[filterData_length / 2];
	}

	//for (int i = 0; i < filterData_length; i++)//伪众数计算
	//{
	//	for (int j = i + 1; j < filterData_length; j++)
	//	{
	//		if (filterData[i] == filterData[j])
	//		{
	//			count++;
	//		}
	//		if (count >= (filterData_length/2) - 1)
	//		{
	//			mode = filterData[i];
	//			filter_result = mode;
	//		}
	//		else
	//		{
	//			mode = 1.11;
	//			filter_result = nomaxmin_avr;
	//		}
	//	}
	//	count = 0;
	//}

	//求众数
	for (int i = 0; i < filterData_length; i++)
	{
		/*for (int j = i + 1; j < filterData_length; j++)*/
		for (int j = 0; j < filterData_length; j++)
		{
			if (filterData[i] == filterData[j])
			{
				count++;
			}
		}
		if (count > b_count)
		{
			b_count = count;
			mode = filterData[i];//得到众数

			//----------这是自行添加的内容，作为私有库使用请删除该块-----------------------
			if (count >= 4)//如果众数的数量大于或等于（整个数组的数量/2） -1，那么滤波结果为众数
			{
				filter_result = mode;
			}
			else//如果众数不满足上方条件，则滤波结果为去掉一个最大值以及一个最小值的平均值
			{
				mode = count;//代表无值
				filter_result = nomaxmin_avr;
			}
			//----------------------------------------------------------------------
		}
		count = 0;
		a_count = 0;
	}
//---------------以上为滤波库的内容，下面为自行需要增加的内容-------------------------------------------------------------

	//if (count >= (filterData_length / 2) - 1)//如果众数的数量大于或等于（整个数组的数量/2） -1，那么滤波结果为众数
	//{
	//	filter_result = mode;
	//}
	//else//如果众数不满足上方条件，则滤波结果为去掉一个最大值以及一个最小值的平均值
	//{
	//	mode = 1.11;//代表无值
	//	filter_result = nomaxmin_avr;
	//}




	//输出所有的结果
	Serial.print("maximum = ");//最大值
	Serial.println(maximum);
	Serial.print("minimum = ");//最小值
	Serial.println(minimum);
	Serial.print("mode = ");//众数
	Serial.println(mode);
	Serial.print("median = ");//中位数
	Serial.println(median);
	Serial.print("sum = ");//和
	Serial.println(sum);
	Serial.print("nomaxmin_avr = ");//去掉一个最大值以及最小值的平均值
	Serial.println(nomaxmin_avr);

	//将filter_result的结果等于任意一个求出来的值
	//filter_result = nomaxmin_avr;


	return filter_result;
}


//函 数 名：Filter() 
//功能描述：滤波函数
//函数说明：对输入的多个整型数，进行滤波操作，
//调用函数：
//全局变量：
//输 入：整型数组以及数组长度
//返 回：整型数的滤波值
/////////////////////////////////////////////////////////////////////
float Filter(int* filterData, int filterData_length)
{
	float average = 0.00;		//平均值
	float mode = 0.00;			//众数
	float median = 0.00;		//中位数
	float maximum = 0.00;		//最大值
	float minimum = 999999.99;	//最小值
	float sum = 0.00;			//和
	float nomaxmin_avr = 0.00;	//去掉最大最小值得平均数
	float filter_result = 0.00;	//滤波结果

	int temp = 0;				//一个桶
	int a_count = 0;			//第二个桶
	int count = 0;				//计数值
	int b_count = 0;			//


	//for (int i = 0; i < filterData_length; i++)//查看输入进来的值
	//{
	//	Serial.print("Filter");
	//	Serial.println(filterData[i]);
	//	delay(5);
	//}
	for (int i = 0; i < filterData_length; i++)//排序，方便计算
	{
		float temp;
		for (int j = i + 1; j < filterData_length; j++)
		{
			if (filterData[i] > filterData[j])
			{
				temp = filterData[i];
				filterData[i] = filterData[j];
				filterData[j] = temp;
			}
		}
	}

	for (int i = 0; i < filterData_length; i++)//输出排序的结果
	{
		Serial.print("排序");
		Serial.println(filterData[i]);
		delay(1);
	}

	for (int i = 0; i < filterData_length; i++)
	{
		if (maximum < filterData[i])
		{
			maximum = filterData[i];//最大值
		}
		if (minimum > filterData[i])
		{
			minimum = filterData[i];//最小值
		}
		sum = sum + filterData[i];//和
	}
	average = sum / filterData_length;//平均数
	nomaxmin_avr = (sum - maximum - minimum) / (filterData_length - 2);//去掉最大最小的平均数

	if (filterData_length % 2 == 0)//得到中位数
	{
		median = (filterData[filterData_length / 2 - 1] + filterData[filterData_length / 2]) / 2.0;
	}
	else
	{
		median = filterData[filterData_length / 2];
	}

	//for (int i = 0; i < filterData_length; i++)//伪众数计算
	//{
	//	for (int j = i + 1; j < filterData_length; j++)
	//	{
	//		if (filterData[i] == filterData[j])
	//		{
	//			count++;
	//		}
	//		if (count >= (filterData_length/2) - 1)
	//		{
	//			mode = filterData[i];
	//			filter_result = mode;
	//		}
	//		else
	//		{
	//			mode = 1.11;
	//			filter_result = nomaxmin_avr;
	//		}
	//	}
	//	count = 0;
	//}

	//求众数
	for (int i = 0; i < filterData_length; i++)
	{
		/*for (int j = i + 1; j < filterData_length; j++)*/
		for (int j = 0; j < filterData_length; j++)
		{
			if (filterData[i] == filterData[j])
			{
				count++;
			}
		}
		if (count > b_count)
		{
			b_count = count;
			mode = filterData[i];//得到众数

			//----------这是自行添加的内容，作为私有库使用请删除该块-----------------------
			if (count >= 4)//如果众数的数量大于或等于（整个数组的数量/2） -1，那么滤波结果为众数
			{
				filter_result = mode;
			}
			else//如果众数不满足上方条件，则滤波结果为去掉一个最大值以及一个最小值的平均值
			{
				mode = count;//代表无值
				filter_result = nomaxmin_avr;
			}
			//----------------------------------------------------------------------
		}
		count = 0;
		a_count = 0;
	}
	//---------------以上为滤波库的内容，下面为自行需要增加的内容-------------------------------------------------------------

		//if (count >= (filterData_length / 2) - 1)//如果众数的数量大于或等于（整个数组的数量/2） -1，那么滤波结果为众数
		//{
		//	filter_result = mode;
		//}
		//else//如果众数不满足上方条件，则滤波结果为去掉一个最大值以及一个最小值的平均值
		//{
		//	mode = 1.11;//代表无值
		//	filter_result = nomaxmin_avr;
		//}




		//输出所有的结果
	Serial.print("maximum = ");//最大值
	Serial.println(maximum);
	Serial.print("minimum = ");//最小值
	Serial.println(minimum);
	Serial.print("mode = ");//众数
	Serial.println(mode);
	Serial.print("median = ");//中位数
	Serial.println(median);
	Serial.print("sum = ");//和
	Serial.println(sum);
	Serial.print("nomaxmin_avr = ");//去掉一个最大值以及最小值的平均值
	Serial.println(nomaxmin_avr);

	//将filter_result的结果等于任意一个求出来的值
	//filter_result = nomaxmin_avr;


	return filter_result;
}




/***
 *            .,,       .,:;;iiiiiiiii;;:,,.     .,,
 *          rGB##HS,.;iirrrrriiiiiiiiiirrrrri;,s&##MAS,
 *         r5s;:r3AH5iiiii;;;;;;;;;;;;;;;;iiirXHGSsiih1,
 *            .;i;;s91;;;;;;::::::::::::;;;;iS5;;;ii:
 *          :rsriii;;r::::::::::::::::::::::;;,;;iiirsi,
 *       .,iri;;::::;;;;;;::,,,,,,,,,,,,,..,,;;;;;;;;iiri,,.
 *    ,9BM&,            .,:;;:,,,,,,,,,,,hXA8:            ..,,,.
 *   ,;&@@#r:;;;;;::::,,.   ,r,,,,,,,,,,iA@@@s,,:::;;;::,,.   .;.
 *    :ih1iii;;;;;::::;;;;;;;:,,,,,,,,,,;i55r;;;;;;;;;iiirrrr,..
 *   .ir;;iiiiiiiiii;;;;::::::,,,,,,,:::::,,:;;;iiiiiiiiiiiiri
 *   iriiiiiiiiiiiiiiii;;;::::::::::::::::;;;iiiiiiiiiiiiiiiir;
 *  ,riii;;;;;;;;;;;;;:::::::::::::::::::::::;;;;;;;;;;;;;;iiir.
 *  iri;;;::::,,,,,,,,,,:::::::::::::::::::::::::,::,,::::;;iir:
 * .rii;;::::,,,,,,,,,,,,:::::::::::::::::,,,,,,,,,,,,,::::;;iri
 * ,rii;;;::,,,,,,,,,,,,,:::::::::::,:::::,,,,,,,,,,,,,:::;;;iir.
 * ,rii;;i::,,,,,,,,,,,,,:::::::::::::::::,,,,,,,,,,,,,,::i;;iir.
 * ,rii;;r::,,,,,,,,,,,,,:,:::::,:,:::::::,,,,,,,,,,,,,::;r;;iir.
 * .rii;;rr,:,,,,,,,,,,,,,,:::::::::::::::,,,,,,,,,,,,,:,si;;iri
 *  ;rii;:1i,,,,,,,,,,,,,,,,,,:::::::::,,,,,,,,,,,,,,,:,ss:;iir:
 *  .rii;;;5r,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,sh:;;iri
 *   ;rii;:;51,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,.:hh:;;iir,
 *    irii;::hSr,.,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,.,sSs:;;iir:
 *     irii;;:iSSs:.,,,,,,,,,,,,,,,,,,,,,,,,,,,..:135;:;;iir:
 *      ;rii;;:,r535r:...,,,,,,,,,,,,,,,,,,..,;sS35i,;;iirr:
 *       :rrii;;:,;1S3Shs;:,............,:is533Ss:,;;;iiri,
 *        .;rrii;;;:,;rhS393S55hh11hh5S3393Shr:,:;;;iirr:
 *          .;rriii;;;::,:;is1h555555h1si;:,::;;;iirri:.
 *            .:irrrii;;;;;:::,,,,,,,,:::;;;;iiirrr;,
 *               .:irrrriiiiii;;;;;;;;iiiiiirrrr;,.
 *                  .,:;iirrrrrrrrrrrrrrrrri;:.
 *                        ..,:::;;;;:::,,.
 */