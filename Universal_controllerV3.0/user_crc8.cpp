//user_crc8.cpp
/*
*��Ȩ
*
* �ļ�����:user_crc8.cpp
* �ļ���ʶ:���ù���ƻ���
* ժҪ:crc8У��ֵ�ļ���Ա�
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

#include "user_crc8.h"


//�� �� ����GetCrc8() 
//����������
//����˵����CRC8�ĺ���
//���ú�����
//ȫ�ֱ�����
//�� �룺��ҪCRC8У��������
//�� �أ�CRC8����õ�����ֵ
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