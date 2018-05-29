/******************** (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� ********************
 * �ļ���       ��include.h
 * ����         ������ģ��ͷ�ļ�
 *
 * ʵ��ƽ̨     ��Ұ��kinetis������
 * ��汾       ��
 * Ƕ��ϵͳ     ��
 *
 * ����         ��Ұ��Ƕ��ʽ����������
 * �Ա���       ��http://firestm32.taobao.com
 * ����֧����̳ ��http://www.ourdev.cn/bbs/bbs_list.jsp?bbs_id=1008
**********************************************************************************/

#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#include  "common.h"
#include  "define.h"
/*
 * Include �û��Զ����ͷ�ļ�
 */
#include "MK60DZ10.h"
#include  "gpio.h"      //IO�ڲ���
#include  "port.h" 
#include  "uart.h"      //����
#include  "adc.h"       //ADCģ��
#include  "FTM.h"       //FTMģ�飨FTM0��������� / ͨ�� /PWM     FTM1��2���������� / ͨ�� /PWM ��
#include  "PIT.h"       //�����жϼ�ʱ��
#include  "lptmr.h"
#include  "exti.h"      //EXTI�ⲿGPIO�ж�
#include  "common.h"
#include  "arm_math.h"  //DSP��
#include  "MK60_spi.h"
#include  "Car_init.h"
#include  "define.h"
#include  "i2c.h"
#include  "dma.h"
#include  "PIT.h"   
#include  "fire_drivers_cfg.h"   //�ܽŸ�������
#include  "isr.h"
#include  "math.h"
#include  "mymath.h"
#include  "delay.h"
#include  "led.h"
#include  "mykey.h"
#include  "beep.h"
#include  "dial_switch.h"
#include  "myPWM.h"
#include  "getspeed.h"
#include  "lcd.h"
#include  "pid.h"
#include  "OV7725.h"
#include  "OV7725_REG.h"
#include  "SCCB.h"
#include  "image_process.h"
//#include "mpu6050.h"
//#include "inv_mpu.h"
//#include "inv_mpu_dmp_motion_driver.h" 
//#include "pacman.h"
#include  "ldc1314.h"
#include "ldc1000.h"

/*************************************************************************
*  ģ�����ƣ��ṹ��ͱ���ģ��
*  ����˵����Include �û��Զ���Ľṹ��ͱ���
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-2-14
*************************************************************************/
//extern u8 B_f;
extern u16 Brush_Color; 
extern u16 Back_Color;

extern Motor_Status Motor1;//���״̬�ṹ��
extern Motor_Status Motor2;//���״̬�ṹ��
extern u32 Duty_Motor1;//���ռ�ձ�
extern u32 Duty_Motor2;//���ռ�ձ�
extern PID_Struct Motor1_PID;//pid�ṹ��
extern PID_Struct Motor2_PID;//pid�ṹ��
extern PID_Struct Diff_PID;//����PID
extern float Speed_goal1;//���ת��Ŀ��ֵ
extern float Speed_goal2;//���ת��Ŀ��ֵ
extern u16 Diff_goal;
extern int Diff_error;
extern u16 Master_Speed;
extern u16 ADC_Value;//ADCֵ
extern u16 Speed_stand;
extern int Weight_mean;
extern float stand_p;
extern float stand_d;
//***************************��ʱ����־λ*************************
extern u8 button_timeout;//����ʱ���־
extern long int Time_1ms;//ʱ����
//****************************************************************

extern u8 Road_Status_Flag;//��·��״�жϱ�־
extern u8 Switch_Status;//����״̬
extern u8 Key_status;//����״̬
extern u8 LCD_DISPLAY_FLAG;
extern u8 Image_Flag;
extern u8 Black_Lock;
extern int DIFF_UP;
extern int DIFF_DOWN;
//***********************************����ͷ**********************************
extern u8 Memory_use_Flag;
extern u8 Image_fire_Memory1[CAMERA_H+1][CAMERA_DMA_NUM];
extern u8 Image_fire_Memory2[CAMERA_H+1][CAMERA_DMA_NUM];
extern u8 (*Image_fire)[CAMERA_DMA_NUM];//ָ��
//extern u8 Image_fire_extract[CAMERA_H+1][CAMERA_W];
extern volatile u8 img_flag;		//ͼ��״̬
extern int centre[ALL_LINE];
extern u8 halfwidth[ALL_LINE];
//extern int black_L[ALL_LINE];
//extern int black_R[ALL_LINE];
//extern u16 Right_count[ALL_LINE];
//extern u16 Left_count[ALL_LINE];
extern u8 getLeft_flag[ALL_LINE];
extern u8 getRight_flag[ALL_LINE];
extern u8 LED_timeout;
extern u16 hang;
extern u8 DIFF_PID_CHANGE_FLAG;
extern long int  temp_cnt;
extern u16 temp_CNT_WATCH;
extern u8 Three_lie_end[3];
extern u8 Speed_max_to_min_diff;
extern u8 Motor_enable_Flag;
extern u8 Slow_Flag;
extern u8 Reduct_Flag;
extern u8 Blue_Start_Flag;//��������
extern u8 Key_Start_Flag;
extern u8 Acc_Limit;
extern float Acc_K;
extern int Speed_L_50ms;
extern int Speed_R_50ms;
extern uint16_t ldc1314_readbuf[8];
extern uint16_t ldc1314_result[4];
extern u16 I_drive_temp;
#endif  //__INCLUDE_H__
