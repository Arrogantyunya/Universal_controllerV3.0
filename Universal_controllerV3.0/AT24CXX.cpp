/************************************************************************************
 * Code and comments : KeeganLu
 * Date：2019/3/14
 * 
 * The main function of this file is to operate EEPROM chip, provide I2C bus 
 * initialization, read a byte, write a byte and other function interface.
 * 
 * If you have any questions, please send an email to me： idlukeqing@163.com
*************************************************************************************/

/************************************************************************************
 * 
 * 代码与注释：卢科青
 * 日期：2019/3/14
 * 
 * 该文件主要功能是操作EEPROM储存芯片，提供了初始化I2C总线，读取一个字节、写一个字节等函数接口。
 * 
 * 如有任何疑问，请发送邮件到： idlukeqing@163.com
*************************************************************************************/

#include "AT24CXX.h"


/*
 @brief     : 从EEPROM读取一个字节
              Read a byte from EEPROM
 @para      : None
 @return    : a byte
 */
unsigned char AT24CXX_ReadOneByte(unsigned int addr)
{
    unsigned char temp = 0;
    Start();

    if (EE_TYPE > AT24C16){
        Send_Byte(0xA0);
        Wait_Ack();
        Send_Byte(addr >> 8);
    }else{
        Send_Byte(0xA0 + ((addr / 256) << 1)); //device address + data address
    }

    Wait_Ack();
    Send_Byte(addr % 256);
    Wait_Ack();

    Start();
    Send_Byte(0xA1);
    Wait_Ack();

    temp = Read_Byte(0); 
    NAck();
    Stop();
    return temp;
}

/*
 @brief     : 写一个字节到EEPROM
 @para      : write addr
              1 byte data
 @return    : None
 */
void AT24CXX_WriteOneByte(unsigned int addr, unsigned char dt)
{
	digitalWrite(WP, LOW);
    Start();

    if (EE_TYPE > AT24C16){
        Send_Byte(0xA0);
        Wait_Ack();
        Send_Byte(addr >> 8);
    }else{
        Send_Byte(0xA0 + ((addr / 256) << 1));
    }

    Wait_Ack();
    Send_Byte(addr % 256);
    Wait_Ack();

    Send_Byte(dt);
    Wait_Ack();
    Stop();
    delay(10);
	digitalWrite(WP, HIGH);
}