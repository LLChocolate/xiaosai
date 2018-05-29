#ifndef __LDCIIC_H
#define __LDCIIC_H
//#include "sys.h"
#include "common.h"
#include "gpio.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������V3
//MPU6050 IIC���� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/1/17
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
 	   		   
#define LDC_SDA_IN()    DDRD14 = 0
#define LDC_SDA_OUT()   DDRD14 = 1


#define LDC_IIC_SCL     PTE7_OUT		//SCL
#define LDC_IIC_SDA     PTD14_OUT		//SDA	 
#define LDC_READ_SDA    PTD14_IN		//??SDA 


//IIC���в�������
//void LDC_IIC_Delay(void);				//LDC IIC��ʱ����
void LDC_IIC_Init(void);                //��ʼ��IIC��IO��				 
void LDC_IIC_Start(void);				//����IIC��ʼ�ź�
void LDC_IIC_Stop(void);	  			//����IICֹͣ�ź�
void LDC_IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 LDC_IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 LDC_IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void LDC_IIC_Ack(void);					//IIC����ACK�ź�
void LDC_IIC_NAck(void);				//IIC������ACK�ź�

void ILDC_IC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 LDC_IIC_Read_One_Byte(u8 daddr,u8 addr);	  
#endif
















