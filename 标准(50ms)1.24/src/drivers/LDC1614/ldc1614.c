#include "LDC1614.h"

//H =12.59uH
//H = 27.305uH
//H = 35.18uH
u16 I_drive_temp=30;
void LDC1614_i2c_INIT(void)
{
    // ʹ��LDC1614ʹ�õ�io����˿�
    delayms(1);
    // ʹ��I2C1����
    LDC_IIC_Init();
//    exti_init(PORTD,12,falling_up);
    delayms(1);
    // ����LDC1614ʹ�õ�io����˿�Ϊ������©�˿�
    //GPIOPadConfigSet(PORT_PT2314, CLK_PT2314|SDA_PT2314 , GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPD);
//    ROM_GPIOPinTypeI2C(PORT_LDC1614_BASE, SDA_LDC1614);
//    ROM_GPIOPinTypeI2CSCL(PORT_LDC1614_BASE, CLK_LDC1614);
    // ����I2CЭ��ʱ���źš������ź�
//    ROM_GPIOPinConfigure(LDC1614_HW_IIC_CLK);
//    ROM_GPIOPinConfigure(LDC1614_HW_IIC_SDA);

    // ��ʼ��I2C����ģ�顣���������ٶȺ�ʹ������ģ��
//    I2CMasterInitExpClk(LDC1614_HW_IIC_BASE, 80000000, false); //����100k
    //I2CMasterInitExpClk(ADS1115_HW_IIC_BASE, SysCtlClockGet(), true);//����400k

////�������´������л���3.4M�����ٶ�
//        ui32TPR = ((80000000 + (2 * 3 * 3400000) - 1) /
//                   (2 * 3 * 3400000)) - 1;
//        HWREG(ADS1115_HW_IIC_BASE + 0x00C) = I2C_MTPR_HS | ui32TPR;
////��������������л���3.4M�����ٶ�


// ʹ��I2C����ģ��
//    I2CMasterEnable(LDC1614_HW_IIC_BASE);	
}

//i2c��LDC1614����һ��16λ����

u8 LDC1614_send_u8(u8 reg,u8 data)
{
    LDC_IIC_Start(); 
    LDC_IIC_Send_Byte((ADRESS_LDC1614<<1)|0);//����������ַ+д����	
    if(LDC_IIC_Wait_Ack())	//�ȴ�Ӧ��
    {
      LDC_IIC_Stop();		 
      return 1;		
    }
    LDC_IIC_Send_Byte(reg);	//д�Ĵ�����ַ
    LDC_IIC_Wait_Ack();		//�ȴ�Ӧ�� 
    LDC_IIC_Send_Byte(data);//��������
    if(LDC_IIC_Wait_Ack())	//�ȴ�ACK
    {
            LDC_IIC_Stop();	 
            return 1;		 
    }		 
    LDC_IIC_Stop();	 
    return 0;
}


u8 LDC1614_send_word(uint8_t reg,uint16_t data)
{
    LDC_IIC_Start(); 
    LDC_IIC_Send_Byte((ADRESS_LDC1614<<1)|0);//����������ַ+д����	
    if(LDC_IIC_Wait_Ack())	//�ȴ�Ӧ��
    {
      LDC_IIC_Stop();		 
      return 1;		
    }
    LDC_IIC_Send_Byte(reg);	//д�Ĵ�����ַ
    LDC_IIC_Wait_Ack();		//�ȴ�Ӧ�� 
    LDC_IIC_Send_Byte((u8)(data>>8));//���͸߰�λ
    if(LDC_IIC_Wait_Ack())	//�ȴ�ACK
    {
      LDC_IIC_Stop();	 
      return 1;		 
    }
    LDC_IIC_Send_Byte((u8)(data));//���͵Ͱ�λ
    if(LDC_IIC_Wait_Ack())	//�ȴ�ACK
    {
      LDC_IIC_Stop();	 
      return 1;		 
    }		 
    LDC_IIC_Stop();	 
    return 0;
}


//i2c��ȡLDC1614��һ���Ĵ���
u8 LDC1614_read_u8(u8 reg)
{
    u8 res;
    LDC_IIC_Start(); 
    LDC_IIC_Send_Byte((ADRESS_LDC1614<<1)|0);//����������ַ+д����	
    LDC_IIC_Wait_Ack();		//�ȴ�Ӧ�� 
    LDC_IIC_Send_Byte(reg);	//д�Ĵ�����ַ
    LDC_IIC_Wait_Ack();		//�ȴ�Ӧ��
    LDC_IIC_Start();
    LDC_IIC_Send_Byte((ADRESS_LDC1614<<1)|1);//����������ַ+������	
    LDC_IIC_Wait_Ack();		//�ȴ�Ӧ�� 
    res=LDC_IIC_Read_Byte(0);//��ȡ����,����nACK 
    LDC_IIC_Stop();			//����һ��ֹͣ���� 
    return res;		
}


uint16_t LDC1614_read_word(uint8_t reg)
{
  uint8_t data_H=0,data_L=0;
  LDC_IIC_Start(); 
  LDC_IIC_Send_Byte((ADRESS_LDC1614<<1)|0);//����������ַ+д����	
  LDC_IIC_Wait_Ack();		//�ȴ�Ӧ�� 
  LDC_IIC_Send_Byte(reg);	//д�Ĵ�����ַ
  LDC_IIC_Wait_Ack();		//�ȴ�Ӧ��
  LDC_IIC_Start();
  LDC_IIC_Send_Byte((ADRESS_LDC1614<<1)|1);//����������ַ+������	
  LDC_IIC_Wait_Ack();		//�ȴ�Ӧ�� 
  data_H = LDC_IIC_Read_Byte(1);//��ȡ����,����nACK 
  data_L = LDC_IIC_Read_Byte(0);//��ȡ����,����nACK 
  LDC_IIC_Stop();			//����һ��ֹͣ���� 	
  return ( (data_H<<8) | (data_L) );
}


void LDC1614_AUTO_INIT(void)
{
	LDC1614_i2c_INIT();
	LDC1614_send_word(RESET_DEV,0x8800);
	delayms(100);
	while(ldc1614_readbuf[0]!=0x3055)
		ldc1614_readbuf[0]=LDC1614_read_word(DEVICE_ID);//�ȴ���I2C����
//WordWrite1614��RESET_DEV��0x8800��;
/*����LDC1614*/
//	LDC1614_send_word(MUX_CONFIG,0x8209);//2451����ch3
/*Ĭ��ֵ��˯��ģʽ������������*/
	LDC1614_send_word(CLOCK_DIVIDERS_CH0,0X1005);//fSENSOR 1��Ƶ��fCLK 1��Ƶ
	LDC1614_send_word(CLOCK_DIVIDERS_CH1,0X1005);//fSENSOR 1��Ƶ��fCLK 1��Ƶ
	LDC1614_send_word(CLOCK_DIVIDERS_CH2,0X1005);//fSENSOR 1��Ƶ��fCLK 1��Ƶ
	LDC1614_send_word(CLOCK_DIVIDERS_CH3,0X1005);//fSENSOR 1��Ƶ��fCLK 1��Ƶ
/* ʱ��Դ��Ƶѡ�񣬷�Ƶϵ��1��
����Using L and C�� ��fSENSOR = 1/2��*sqrt��L*C��
����ע��fSENSOR��С��8.75 MHz��fSENSOR��Ƶϵ��������1
����ע��fREF0�����ٴ��� 4 �� fSENSOR���Ծ���fREF0��Ƶϵ��
����fin0 = fSENSOR0/CH0_FIN_DIVIDER
����fREF0 = fCLK / CH0_FREF_DIVIDER
*/
	LDC1614_send_word(SETTLECOUNT_CH0,0xf060);//0x0A60
	LDC1614_send_word(SETTLECOUNT_CH1,0xf060);
	LDC1614_send_word(SETTLECOUNT_CH2,0xf060);
	LDC1614_send_word(SETTLECOUNT_CH3,0xf060);
/* ������Settling��ʱ������
���������Q=Rp*sqrt��C/L��
�����Ĵ���ֵС��10ȡ10������10ȡ��ֵ����Ӧ��������������
����CHx_SETTLECOUNT �� QSENSORx �� fREFx / ��16 �� fSENSORx�� ��10���ƣ�
������1��fSENSORx:xͨ��������Ƶ��
������2��fREFx:xͨ���ο�Ƶ��
������3��QSENSORx��Ʒ��������Q=Rp ��sqrt��C/L��
����ע�⣬����ʽ�ұ������С��������ȡ��
��������ʱ��tSx = ��CH0_SETTLECOUNT*16�� / fREF0
����ͨ���л�ʱ��tCsd = Channel Switch Delay = 692 ns + 5 / fref ��us��
*/
	LDC1614_send_word(RCOUNT_CH0,0xffFF);//ffff
	LDC1614_send_word(RCOUNT_CH1,0xffFF);
	LDC1614_send_word(RCOUNT_CH2,0xffFF);
	LDC1614_send_word(RCOUNT_CH3,0xffFF);
/*ת��ʱ������
������ת��ʱ��tCx = TSAMPLE������ʱ�䣩 �C tSx �C tCsd ��us��
��������ʽ����Ĵ�����ֵ����С��������ȡ������ȥ������
����ת��ʱ��tCx = ��CHx_RCOUNT �� 16�� / fREFx ��10���ƣ�
����ע��Ĵ�����ֵ��Ϊ16����
*/
/*ʹ��ERROR_CONFIGĬ��ֵ�������жϹر�*/
//	LDC1614_send_word(DRIVE_CURRENT_CH0,i_temp<<11);//0x9800
//	LDC1614_send_word(DRIVE_CURRENT_CH1,0xffc0);
//	LDC1614_send_word(DRIVE_CURRENT_CH2,0xffc0);
//	LDC1614_send_word(DRIVE_CURRENT_CH3,i_temp<<11);
/*�����������������ã�ʹ����ͬʱע��CONFIG�Ĵ����������
�����������ֲ��Figure 15����IDRIVEֵ��10���ƣ���INIT_DRIVEֵ��ʹ�ã�����Ĭ��
����ʹ��CH0_IDRIVE��15:11��ʱ��Rp Override���
����ʹ��CH0_INIT_IDRIVE��10:6��ʱ����֤AUTO_AMP_DISλ����λ
*/
LDC1614_send_word(MUX_CONFIG,0xC20D);//801
/* ��ͨ��ת��ѡ�������������˲�������ѡ��ʹ����ͬʱע��CONFIG�Ĵ���������ã�
������a����AUTOSCAN_ENλΪb1ʹ������ģʽ��sequential mode��
������b����RR_SEQUENCEλΪb00ʹ������ͨ��������ת����channel 0��channel 1��
������c����DEGLITCHλΪb100�趨�����������˲���������ֵ�������г��Ƶ��fTank��
*/
//LDC1614_send_word(OFFSET_CH0,0x00);
/*Ƶ��ƫ�ƣ�����������
�����������ô�ÿ������ֵ�м�ȥƫ��ֵ���Բ���Ƶ��ƫ�ƻ���󻯶�̬��Χ����������
����fOFFSET0 = CH0_OFFSET * ��fREF0/2^16��
������ƫ��ֵӦС�� fSENSORx_MIN / fREFx
*/
//	LDC1614_send_word(RESET_DEV,2<<9);
/*����������ã���10:9�ݣ�������ͨ����Ч
�������ڴ������źű仯��С��������25����ϵͳ�����������������ṩ���ߵķֱ��ʣ����ȣ�
*/
/*
״̬�Ĵ�����STATUS��ERROR_CONFIG
*/
	LDC1614_send_word(CONFIG,0xD481&(~(1<<12))&(~(1<<10)));//1501
	delayms(1);
	LDC1614_send_word(CONFIG,0xD481&(~(1<<12))&(~(1<<10)));//1501
/*Ĭ������ת��������ͨ��0��˯��ģʽ�أ�Rp Override��
�͹���ģʽ�أ��������Զ�����У����AUTO_AMP���أ�Refʱ��Դѡ�ⲿʱ��Դ
INTB�жϿ����ߵ���������*/
}

void LDC1614_INIT(u8 i_temp)
{
	LDC1614_i2c_INIT();
	LDC1614_send_word(RESET_DEV,0x8800);
	delayms(100);
	while(ldc1614_readbuf[0]!=0x3055)
		ldc1614_readbuf[0]=LDC1614_read_word(DEVICE_ID);//�ȴ���I2C����
//WordWrite1614��RESET_DEV��0x8800��;
/*����LDC1614*/
//	LDC1614_send_word(MUX_CONFIG,0x8209);//2451����ch3
/*Ĭ��ֵ��˯��ģʽ������������*/
	LDC1614_send_word(CLOCK_DIVIDERS_CH0,0X2009);//fSENSOR 1��Ƶ��fCLK 1��Ƶ
	LDC1614_send_word(CLOCK_DIVIDERS_CH1,0X1014);//fSENSOR 1��Ƶ��fCLK 1��Ƶ
	LDC1614_send_word(CLOCK_DIVIDERS_CH2,0X1014);//fSENSOR 1��Ƶ��fCLK 1��Ƶ
	LDC1614_send_word(CLOCK_DIVIDERS_CH3,0X2009);//fSENSOR 1��Ƶ��fCLK 1��Ƶ
/* ʱ��Դ��Ƶѡ�񣬷�Ƶϵ��1��1
����Using L and C�� ��fSENSOR = 1/2��*sqrt��L*C��
����ע��fSENSOR��С��8.75 MHz��fSENSOR��Ƶϵ��������1
����ע��fREF0�����ٴ��� 4 �� fSENSOR���Ծ���fREF0��Ƶϵ��
����fin0 = fSENSOR0/CH0_FIN_DIVIDER
����fREF0 = fCLK / CH0_FREF_DIVIDER
*/
	LDC1614_send_word(SETTLECOUNT_CH0,0xf060);//0x0A60
	LDC1614_send_word(SETTLECOUNT_CH1,0xf060);
	LDC1614_send_word(SETTLECOUNT_CH2,0xf060);
	LDC1614_send_word(SETTLECOUNT_CH3,0xf060);
/* ������Settling��ʱ������
���������Q=Rp*sqrt��C/L��
�����Ĵ���ֵС��10ȡ10������10ȡ��ֵ����Ӧ��������������
����CHx_SETTLECOUNT �� QSENSORx �� fREFx / ��16 �� fSENSORx�� ��10���ƣ�
������1��fSENSORx:xͨ��������Ƶ��
������2��fREFx:xͨ���ο�Ƶ��
������3��QSENSORx��Ʒ��������Q=Rp ��sqrt��C/L��
����ע�⣬����ʽ�ұ������С��������ȡ��
��������ʱ��tSx = ��CH0_SETTLECOUNT*16�� / fREF0
����ͨ���л�ʱ��tCsd = Channel Switch Delay = 692 ns + 5 / fref ��us��
*/
	LDC1614_send_word(RCOUNT_CH0,0xffFF);//ffff
	LDC1614_send_word(RCOUNT_CH1,0xffFF);
	LDC1614_send_word(RCOUNT_CH2,0xffFF);
	LDC1614_send_word(RCOUNT_CH3,0xffFF);
/*ת��ʱ������
������ת��ʱ��tCx = TSAMPLE������ʱ�䣩 �C tSx �C tCsd ��us��
��������ʽ����Ĵ�����ֵ����С��������ȡ������ȥ������
����ת��ʱ��tCx = ��CHx_RCOUNT �� 16�� / fREFx ��10���ƣ�
����ע��Ĵ�����ֵ��Ϊ16����
*/
/*ʹ��ERROR_CONFIGĬ��ֵ�������жϹر�*/
	LDC1614_send_word(DRIVE_CURRENT_CH0,i_temp<<11);//0x9800
	LDC1614_send_word(DRIVE_CURRENT_CH1,0xffc0);
	LDC1614_send_word(DRIVE_CURRENT_CH2,0xffc0);
	LDC1614_send_word(DRIVE_CURRENT_CH3,i_temp<<11);
/*�����������������ã�ʹ����ͬʱע��CONFIG�Ĵ����������
�����������ֲ��Figure 15����IDRIVEֵ��10���ƣ���INIT_DRIVEֵ��ʹ�ã�����Ĭ��
����ʹ��CH0_IDRIVE��15:11��ʱ��Rp Override���
����ʹ��CH0_INIT_IDRIVE��10:6��ʱ����֤AUTO_AMP_DISλ����λ
*/
LDC1614_send_word(MUX_CONFIG,0xC20D);//801
/* ��ͨ��ת��ѡ�������������˲�������ѡ��ʹ����ͬʱע��CONFIG�Ĵ���������ã�
������a����AUTOSCAN_ENλΪb1ʹ������ģʽ��sequential mode��
������b����RR_SEQUENCEλΪb00ʹ������ͨ��������ת����channel 0��channel 1��
������c����DEGLITCHλΪb100�趨�����������˲���������ֵ�������г��Ƶ��fTank��
*/
//LDC1614_send_word(OFFSET_CH0,0x00);
/*Ƶ��ƫ�ƣ�����������
�����������ô�ÿ������ֵ�м�ȥƫ��ֵ���Բ���Ƶ��ƫ�ƻ���󻯶�̬��Χ����������
����fOFFSET0 = CH0_OFFSET * ��fREF0/2^16��
������ƫ��ֵӦС�� fSENSORx_MIN / fREFx
*/
//	LDC1614_send_word(RESET_DEV,0x00);
/*����������ã���10:9�ݣ�������ͨ����Ч
�������ڴ������źű仯��С��������25����ϵͳ�����������������ṩ���ߵķֱ��ʣ����ȣ�
*/
/*
״̬�Ĵ�����STATUS��ERROR_CONFIG
*/
	LDC1614_send_word(CONFIG,0xD481);//1501
	delayms(1);
	LDC1614_send_word(CONFIG,0xD481);//1501
/*Ĭ������ת��������ͨ��0��˯��ģʽ�أ�Rp Override��
�͹���ģʽ�أ��������Զ�����У����AUTO_AMP���أ�Refʱ��Դѡ�ⲿʱ��Դ
INTB�жϿ����ߵ���������*/
}

/*��ȡLDC1614ת��������������Ϊѡ��ͨ����*/
uint32_t LDC1614_Result(uint8_t Channal)
{
  uint32_t result = 0;
  uint16_t msb = 0;
  uint16_t lsb = 0;
  switch(Channal)
  {
    case 0x00:
            msb=LDC1614_read_word(DATA0_MSB); //ͨ��0
            lsb=LDC1614_read_word(DATA0_LSB);
            break;
    case 0x01:
            msb=LDC1614_read_word(DATA1_MSB); //ͨ��1
            lsb=LDC1614_read_word(DATA1_LSB);
            break;
    case 0x02:
            msb=LDC1614_read_word(DATA2_MSB); //ͨ��2
            lsb=LDC1614_read_word(DATA2_LSB);
            break;
    case 0x03:
            msb=LDC1614_read_word(DATA3_MSB); //ͨ��3
            lsb=LDC1614_read_word(DATA3_LSB);
            break;
    default:
            break;
  }
//	while((temp&0xF000)!=0);

/*�д���Flag�������������ʱע��˾䣬���ܳ���
����0x000 = under range��0xfff = over range
����*/
//	return (temp&0x0fff);//���Դ����־
  result = (msb<<16) | lsb;
        return (result);
}















