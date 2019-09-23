#include "i2c.h"

void i2cInit(void)
{
    pinMode(SCL, OUTPUT);
    pinMode(SDA, OUTPUT);
    I2C_SCL_H;
    I2C_SDA_H;
}

void SDA_Out(void)
{
    pinMode(SDA, OUTPUT);
}

void SDA_In(void)
{
    pinMode(SDA, INPUT_PULLUP);
}

void Start(void)
{
    SDA_Out();
    I2C_SDA_H;
    I2C_SCL_H;
    delayMicroseconds(5);
    I2C_SDA_L;
    delayMicroseconds(6);
    I2C_SCL_L;
}

void Stop(void)
{
    SDA_Out();
    I2C_SCL_L;
    I2C_SDA_L;
    I2C_SCL_H;
    delayMicroseconds(6);
    I2C_SDA_H;
    delayMicroseconds(6);
}

// 主机数据线拉低应答
void Ack(void)
{
    I2C_SCL_L;
    SDA_Out();
    I2C_SDA_L;
    delayMicroseconds(2);
    I2C_SCL_H;
    delayMicroseconds(5);
    I2C_SCL_L;
}

//主机数据线拉高非应答
void NAck(void)
{
    I2C_SCL_L;
    SDA_Out();
    I2C_SDA_H;
    delayMicroseconds(2);
    I2C_SCL_H;
    delayMicroseconds(5);
    I2C_SCL_L;
}

//等待从机应答， 从机返回1接收应答失败，返回0接收应答成功

unsigned char Wait_Ack(void)
{
    unsigned char tempTime = 0;
    SDA_In();
    I2C_SDA_H;
    delayMicroseconds(1);
    I2C_SCL_H;
    delayMicroseconds(1);

    while (digitalRead(SDA)){
        tempTime++;
        if (tempTime > 250){ //等待从机返回0失败
            Stop();
            return 1;
        }
    }
    I2C_SCL_L;
    return 0;
}

//I2C 写一个字节
void Send_Byte(unsigned char data)
{
    unsigned char i = 0;
    SDA_Out();
    I2C_SCL_L; //拉低时钟线，允许数据线上电平变化

    for (i = 0; i < 8; i++){
        (data & 0x80) > 0 ? I2C_SDA_H : I2C_SDA_L;//从一个字节的高位开始传送
        data <<= 1;
        I2C_SCL_H; //时钟线拉高，这时数据线电平不能变化，让从机读取线上的电平
        delayMicroseconds(2);
        I2C_SCL_L;
        delayMicroseconds(2);
    }
}

//I2C读一个字节
unsigned char Read_Byte(unsigned char ack)
{
    unsigned char i = 0, receive = 0;
    SDA_In();

    for (i = 0; i < 8; i++){
        I2C_SCL_L;
        delayMicroseconds(2);
        I2C_SCL_H; //拉高时钟线，去读从机回过来的数据
        receive <<= 1;

        if (digitalRead(SDA))
            receive++;
        delayMicroseconds(1);
    }
    ack == 0 ? NAck() : Ack();

    return receive;
}