// 
// 
// 

#include "user_HEXtoDEC.h"

//���ַ�'0' ~ 'D'ת��Ϊ��Ӧ������
//����ֵ���ַ�ת�����һ���Ӧ����ֵ
u8 chrtodec(char chr)
{
	u8 value = 0;

	//��ȫ����Сдת��Ϊ��д
	if ((chr >= 'a') && (chr <= 'z'))
		chr = chr - 32;

	//���ַ�ת������Ӧ������
	if ((chr >= '0') && (chr <= '9'))
		value = chr - 48;
	else if ((chr >= 'A') && (chr <= 'Z'))
		value = chr - 65 + 10;

	return value;
}

//����n��16���
//n:16��ƵĴ���
//����ֵ����������Ľ��
int cal16match(u8 n)
{
	u8 i = 0;
	int value = 1;

	for (i = 0; i < n; i++)
		value *= 16;

	return value;
}


//���ַ�����ʽ��ʮ������ת��Ϊ�����ͣ�
//���ַ�����0x16��ת��Ϊint�͵�22��
//���� chr: Ҫת�����ַ����������ִ�Сд��������
//����ֵ������chrת������Ժ��ʮ������ֵ
int charhex_to_dec(char *chr)
{
	u8 i, chrlen;
	u8 sta = 0; //���Ҫת�����ַ����Ƿ���0x,����0X��ͷ
	int chrtoint = 0;
	int value = 0;

	chrlen = strlen(chr);//�Զ���ȡ��Ҫת�����ַ�����
	//chrlen = 3;//���Ǵ�����ַ�������������Ҫ����

	//����ַ����Ƿ�����0x����0X��ͷ�ġ�
	if ((chr[0] == '0') && ((chr[1] == 'x') || (chr[1] == 'X')))
	{
		sta = 2;        //�����0x��0X��ͷ
		chrlen = chrlen - 2;
	}

	//����
	for (i = 0; i < chrlen; i++)
	{
		chrtoint = chrtodec(chr[sta + i]);
		if (i != (chrlen - 1))                //�������һλ
			value += chrtoint * cal16match(chrlen - 1 - i);
		else if (i == (chrlen - 1))         //���һλ
			value += chrtoint;
	}
	//Serial.print("value = ");
	//Serial.println(value);
	return value;
}
