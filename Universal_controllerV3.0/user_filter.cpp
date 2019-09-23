// user_filter.cpp
/*
*��Ȩ
*
* �ļ�����:user_filter.cpp
* �ļ���ʶ:���ù���ƻ���
* ժҪ:�����˲�
*
* ��ǰ�汾:V1.0
* ����:���һ�
* �������:
* �޸���:
* �޸�����:
*
* ȡ���汾:
* ԭ����:���һ�
* �������:
*/

#include "user_filter.h"


//�� �� ����Filter() 
//�����������˲�����
//����˵����������Ķ���������������˲�������
//���ú�����
//ȫ�ֱ�����
//�� �룺�����������Լ����鳤��
//�� �أ����������˲�ֵ
/////////////////////////////////////////////////////////////////////
float Filter(float * filterData, int filterData_length)
{
	float average = 0.00;		//ƽ��ֵ
	float mode = 0.00;			//����
	float median = 0.00;		//��λ��
	float maximum = 0.00;		//���ֵ
	float minimum = 999999.99;	//��Сֵ
	float sum = 0.00;			//��
	float nomaxmin_avr = 0.00;	//ȥ�������Сֵ��ƽ����
	float filter_result = 0.00;	//�˲����

	int temp = 0;				//һ��Ͱ
	int a_count = 0;			//�ڶ���Ͱ
	int count = 0;				//����ֵ
	int b_count = 0;			//


	//for (int i = 0; i < filterData_length; i++)//�鿴���������ֵ
	//{
	//	Serial.print("Filter");
	//	Serial.println(filterData[i]);
	//	delay(5);
	//}
	for (int i = 0; i < filterData_length; i++)//���򣬷������
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

	for (int i = 0; i < filterData_length; i++)//�������Ľ��
	{
		Serial.print("����");
		Serial.println(filterData[i]);
		delay(1);
	}

	for (int i = 0; i < filterData_length; i++)
	{
		if (maximum < filterData[i])
		{
			maximum = filterData[i];//���ֵ
		}
		if (minimum > filterData[i])
		{
			minimum = filterData[i];//��Сֵ
		}
		sum = sum + filterData[i];//��
	}
	average = sum / filterData_length;//ƽ����
	nomaxmin_avr = (sum - maximum - minimum) / (filterData_length - 2);//ȥ�������С��ƽ����

	if (filterData_length % 2 == 0)//�õ���λ��
	{
		median = (filterData[filterData_length / 2 - 1] + filterData[filterData_length / 2]) / 2.0;
	}
	else
	{
		median = filterData[filterData_length / 2];
	}

	//for (int i = 0; i < filterData_length; i++)//α��������
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

	//������
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
			mode = filterData[i];//�õ�����

			//----------����������ӵ����ݣ���Ϊ˽�п�ʹ����ɾ���ÿ�-----------------------
			if (count >= 4)//����������������ڻ���ڣ��������������/2�� -1����ô�˲����Ϊ����
			{
				filter_result = mode;
			}
			else//��������������Ϸ����������˲����Ϊȥ��һ�����ֵ�Լ�һ����Сֵ��ƽ��ֵ
			{
				mode = count;//������ֵ
				filter_result = nomaxmin_avr;
			}
			//----------------------------------------------------------------------
		}
		count = 0;
		a_count = 0;
	}
//---------------����Ϊ�˲�������ݣ�����Ϊ������Ҫ���ӵ�����-------------------------------------------------------------

	//if (count >= (filterData_length / 2) - 1)//����������������ڻ���ڣ��������������/2�� -1����ô�˲����Ϊ����
	//{
	//	filter_result = mode;
	//}
	//else//��������������Ϸ����������˲����Ϊȥ��һ�����ֵ�Լ�һ����Сֵ��ƽ��ֵ
	//{
	//	mode = 1.11;//������ֵ
	//	filter_result = nomaxmin_avr;
	//}




	//������еĽ��
	Serial.print("maximum = ");//���ֵ
	Serial.println(maximum);
	Serial.print("minimum = ");//��Сֵ
	Serial.println(minimum);
	Serial.print("mode = ");//����
	Serial.println(mode);
	Serial.print("median = ");//��λ��
	Serial.println(median);
	Serial.print("sum = ");//��
	Serial.println(sum);
	Serial.print("nomaxmin_avr = ");//ȥ��һ�����ֵ�Լ���Сֵ��ƽ��ֵ
	Serial.println(nomaxmin_avr);

	//��filter_result�Ľ����������һ���������ֵ
	//filter_result = nomaxmin_avr;


	return filter_result;
}


//�� �� ����Filter() 
//�����������˲�����
//����˵����������Ķ���������������˲�������
//���ú�����
//ȫ�ֱ�����
//�� �룺���������Լ����鳤��
//�� �أ����������˲�ֵ
/////////////////////////////////////////////////////////////////////
float Filter(int* filterData, int filterData_length)
{
	float average = 0.00;		//ƽ��ֵ
	float mode = 0.00;			//����
	float median = 0.00;		//��λ��
	float maximum = 0.00;		//���ֵ
	float minimum = 999999.99;	//��Сֵ
	float sum = 0.00;			//��
	float nomaxmin_avr = 0.00;	//ȥ�������Сֵ��ƽ����
	float filter_result = 0.00;	//�˲����

	int temp = 0;				//һ��Ͱ
	int a_count = 0;			//�ڶ���Ͱ
	int count = 0;				//����ֵ
	int b_count = 0;			//


	//for (int i = 0; i < filterData_length; i++)//�鿴���������ֵ
	//{
	//	Serial.print("Filter");
	//	Serial.println(filterData[i]);
	//	delay(5);
	//}
	for (int i = 0; i < filterData_length; i++)//���򣬷������
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

	for (int i = 0; i < filterData_length; i++)//�������Ľ��
	{
		Serial.print("����");
		Serial.println(filterData[i]);
		delay(1);
	}

	for (int i = 0; i < filterData_length; i++)
	{
		if (maximum < filterData[i])
		{
			maximum = filterData[i];//���ֵ
		}
		if (minimum > filterData[i])
		{
			minimum = filterData[i];//��Сֵ
		}
		sum = sum + filterData[i];//��
	}
	average = sum / filterData_length;//ƽ����
	nomaxmin_avr = (sum - maximum - minimum) / (filterData_length - 2);//ȥ�������С��ƽ����

	if (filterData_length % 2 == 0)//�õ���λ��
	{
		median = (filterData[filterData_length / 2 - 1] + filterData[filterData_length / 2]) / 2.0;
	}
	else
	{
		median = filterData[filterData_length / 2];
	}

	//for (int i = 0; i < filterData_length; i++)//α��������
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

	//������
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
			mode = filterData[i];//�õ�����

			//----------����������ӵ����ݣ���Ϊ˽�п�ʹ����ɾ���ÿ�-----------------------
			if (count >= 4)//����������������ڻ���ڣ��������������/2�� -1����ô�˲����Ϊ����
			{
				filter_result = mode;
			}
			else//��������������Ϸ����������˲����Ϊȥ��һ�����ֵ�Լ�һ����Сֵ��ƽ��ֵ
			{
				mode = count;//������ֵ
				filter_result = nomaxmin_avr;
			}
			//----------------------------------------------------------------------
		}
		count = 0;
		a_count = 0;
	}
	//---------------����Ϊ�˲�������ݣ�����Ϊ������Ҫ���ӵ�����-------------------------------------------------------------

		//if (count >= (filterData_length / 2) - 1)//����������������ڻ���ڣ��������������/2�� -1����ô�˲����Ϊ����
		//{
		//	filter_result = mode;
		//}
		//else//��������������Ϸ����������˲����Ϊȥ��һ�����ֵ�Լ�һ����Сֵ��ƽ��ֵ
		//{
		//	mode = 1.11;//������ֵ
		//	filter_result = nomaxmin_avr;
		//}




		//������еĽ��
	Serial.print("maximum = ");//���ֵ
	Serial.println(maximum);
	Serial.print("minimum = ");//��Сֵ
	Serial.println(minimum);
	Serial.print("mode = ");//����
	Serial.println(mode);
	Serial.print("median = ");//��λ��
	Serial.println(median);
	Serial.print("sum = ");//��
	Serial.println(sum);
	Serial.print("nomaxmin_avr = ");//ȥ��һ�����ֵ�Լ���Сֵ��ƽ��ֵ
	Serial.println(nomaxmin_avr);

	//��filter_result�Ľ����������һ���������ֵ
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