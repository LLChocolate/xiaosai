/******************** (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� ********************
 * �ļ���       ��i2c.h
 * ����         ��I2Cͷ�ļ�
 *
 * ʵ��ƽ̨     ��Ұ��kinetis������
 * ��汾       ��
 * Ƕ��ϵͳ     ��
 *
 * ����         ��
 * �Ա���       ��http://firestm32.taobao.com
 * ����֧����̳ ��http://www.ourdev.cn/bbs/bbs_list.jsp?bbs_id=1008
**********************************************************************************/
#ifndef __I2C_H__
#define __I2C_H__
#include "i2c_cfg.h"

typedef enum I2Cn
{
    I2C0  = 0,
    I2C1  = 1
} I2Cn;

typedef enum MSmode
{
    MWSR =   0x00,  /* Master write  */
    MRSW =   0x01   /* Master read */
} MSmode;


void  I2C_init(I2Cn);                                         //��ʼ��I2C
void  I2C_WriteAddr(I2Cn, unsigned char SlaveID, unsigned char Addr, unsigned char Data);      //��ȡ��ַ�������
unsigned char    I2C_ReadAddr(I2Cn, unsigned char SlaveID, unsigned char Addr);                //����ַ��д������





void  I2C_StartTransmission (I2Cn, unsigned char SlaveID, MSmode);       //��������
#endif