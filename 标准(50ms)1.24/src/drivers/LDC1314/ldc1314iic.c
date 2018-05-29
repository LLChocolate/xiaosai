#include "ldc1314iic.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK��ӢSTM32������V3
//LDC6050 IIC���� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/1/17
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
 
  //LDC IIC ��ʱ����
void LDC_IIC_Delay(void)
{
  delayus(2);
}

//��ʼ��IIC
void LDC_IIC_Init(void)
{		
  gpio_init(PORTD,14,GPO,1);                  //SCL
  gpio_init(PORTE,7,GPO,1);                  //SDA
}
//����IIC��ʼ�ź�
void LDC_IIC_Start(void)
{
	LDC_SDA_OUT();     //sda�����
	LDC_IIC_SDA=1;	  	  
	LDC_IIC_SCL=1;
	LDC_IIC_Delay();
 	LDC_IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	LDC_IIC_Delay();
	LDC_IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void LDC_IIC_Stop(void)
{
	LDC_SDA_OUT();//sda�����
	LDC_IIC_SCL=0;
	LDC_IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	LDC_IIC_Delay();
	LDC_IIC_SCL=1; 
	LDC_IIC_SDA=1;//����I2C���߽����ź�
	LDC_IIC_Delay();							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 LDC_IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	LDC_SDA_IN();      //SDA����Ϊ����  
	LDC_IIC_SDA=1;//LDC_IIC_Delay();	   
	LDC_IIC_SCL=1;//LDC_IIC_Delay();	 
	while(LDC_READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			LDC_IIC_Stop();
			return 1;
		}
	}
	LDC_IIC_SCL=0;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void LDC_IIC_Ack(void)
{
	LDC_IIC_SCL=0;
	LDC_SDA_OUT();
	LDC_IIC_SDA=0;
	LDC_IIC_Delay();
	LDC_IIC_SCL=1;
	LDC_IIC_Delay();
	LDC_IIC_SCL=0;
}
//������ACKӦ��		    
void LDC_IIC_NAck(void)
{
	LDC_IIC_SCL=0;
	LDC_SDA_OUT();
	LDC_IIC_SDA=1;
	LDC_IIC_Delay();
	LDC_IIC_SCL=1;
	LDC_IIC_Delay();
	LDC_IIC_SCL=0;
}
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void LDC_IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	LDC_SDA_OUT(); 	    
    LDC_IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        LDC_IIC_SDA=(txd&0x80)>>7;
        txd<<=1; 	  
		    LDC_IIC_SCL=1;
		    LDC_IIC_Delay(); 
		    LDC_IIC_SCL=0;	
		    LDC_IIC_Delay();
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 LDC_IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	LDC_SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        LDC_IIC_SCL=0; 
        LDC_IIC_Delay();
		LDC_IIC_SCL=1;
        receive<<=1;
        if(LDC_READ_SDA)receive++;   
		LDC_IIC_Delay(); 
    }					 
    if (!ack)
        LDC_IIC_NAck();//����nACK
    else
        LDC_IIC_Ack(); //����ACK   
    return receive;
}

