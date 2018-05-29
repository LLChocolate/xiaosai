#ifndef _DEFINE_H
#define _DEFINE_H

#include  "common.h"
/*************************************************************************
*  ģ�����ƣ�defineģ��
*  ����˵����Include �û��Զ���ĺ�
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-2-14
*************************************************************************/

//#define LCD_DISPLAY

//��·״̬��־
typedef enum
{
  Nstart,//δ��ʼ״̬
  Straight,//��ֱ��
  Left_turn,//��ת
  Right_turn,//��ת
  Cross,//ʮ��
  Uphill,//�µ�
  Island//����
  
  
}Road_Status;




//������
#define MOTOR_1                         FTM0,CH4//����ӿ�
#define MOTOR_2                         FTM0,CH3//����ӿ�
//#define STEER_                          FTM1,CH0//����ӿ�
#define MOTOR1_DIR                       PTA13_OUT//����������
#define MOTOR2_DIR                       PTA12_OUT//����������
typedef struct{
  u8 Dir;
  s16 Speed;
}Motor_Status;          //���״̬�ṹ��




//ADC

#define MYADC_1                          ADC1,AD14
#define MYADC_2                          ADC1,AD12
#define MYADC_3                          ADC1,AD11
#define MYADC_4                          ADC0,AD13
#define MYADC_5                          ADC1,AD15
#define MYADC_6                          ADC1,AD13
#define MYADC_7                          ADC1,AD10
#define MYADC_8                          ADC0,AD12
//����
#define SW1              PTB0_IN
#define SW2              PTA29_IN
#define SW3              PTA28_IN
#define SW4              PTA27_IN
#define SW5              PTA26_IN
#define SW6              PTA25_IN
#define SW7              PTA24_IN
#define SW8              PTA19_IN

//����
#define KEY1             PTB1_IN
#define KEY1_PRES        1
#define KEY2             PTA17_IN
#define KEY2_PRES        2
#define KEY3             PTA15_IN
#define KEY3_PRES        3   

//������
#define BEEP PTD6_OUT

//��ˮ��
#define LED1             PTD5_OUT
#define LED2             PTD3_OUT


//PID�ṹ��
typedef struct                    //�ṹ�壬���PID��ر���
{
  float P;                        //����P
  float I;                        //����I
  float D;                        //����D
  float error[3];                 //���洢����
  float delat;                    //ÿ�εĵ��ڽ��
  float derr;                     //һ�����
  float dderr;                    //�������
  float result;                      //PID�����������������ʽ�����Գ�ֵ����Ϊ����ƽ��ʱ�����ֵ����Ҫ��������0Ҫ����ը��
  
  float target;                   //PID���ڵ�Ŀ��ֵ     
  float feedback;
  float UP_Limit;
  float LOW_Limit;
}PID_Struct;

////ϵͳ״̬�ṹ��
//typedef struct
//{
//  long int Time_1ms;
//  
//}System_Status

#define     pit_delay_ms(PITn,ms)          pit_delay(PITn,ms * bus_clk_khz);        //PIT��ʱ ms
#define     pit_delay_us(PITn,us)          pit_delay(PITn,us * bus_clk_khz/1000);   //PIT��ʱ us

typedef enum{
  Unlock,
  Left_Lock,
  Right_Lock
}Black_View_Run_Status;

typedef struct 
{
  float x_mid;
  float x_now;
  float p_mid ;
  float p_now;
  float kg;
  float ProcessNoise_Q;
  float MeasureNoise_R;
  float x_last1;
  float p_last1;
}Kalman_Date;

typedef struct
{
  float m_filter;
  float ResrcData_mem[2];
  float output_mem[2];
}Filter_1st_Str;

#endif //_DEFINE_H