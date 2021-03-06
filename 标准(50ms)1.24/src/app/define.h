#ifndef _DEFINE_H
#define _DEFINE_H

#include  "common.h"
/*************************************************************************
*  模块名称：define模块
*  功能说明：Include 用户自定义的宏
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-14
*************************************************************************/

//#define LCD_DISPLAY

//道路状态标志
typedef enum
{
  Nstart,//未开始状态
  Straight,//走直线
  Left_turn,//左转
  Right_turn,//右转
  Cross,//十字
  Uphill,//坡道
  Island//环岛
  
  
}Road_Status;




//电机舵机
#define MOTOR_1                         FTM0,CH4//电机接口
#define MOTOR_2                         FTM0,CH3//电机接口
//#define STEER_                          FTM1,CH0//舵机接口
#define MOTOR1_DIR                       PTA13_OUT//电机方向控制
#define MOTOR2_DIR                       PTA12_OUT//电机方向控制
typedef struct{
  u8 Dir;
  s16 Speed;
}Motor_Status;          //电机状态结构体




//ADC

#define MYADC_1                          ADC1,AD14
#define MYADC_2                          ADC1,AD12
#define MYADC_3                          ADC1,AD11
#define MYADC_4                          ADC0,AD13
#define MYADC_5                          ADC1,AD15
#define MYADC_6                          ADC1,AD13
#define MYADC_7                          ADC1,AD10
#define MYADC_8                          ADC0,AD12
//拨码
#define SW1              PTB0_IN
#define SW2              PTA29_IN
#define SW3              PTA28_IN
#define SW4              PTA27_IN
#define SW5              PTA26_IN
#define SW6              PTA25_IN
#define SW7              PTA24_IN
#define SW8              PTA19_IN

//按键
#define KEY1             PTB1_IN
#define KEY1_PRES        1
#define KEY2             PTA17_IN
#define KEY2_PRES        2
#define KEY3             PTA15_IN
#define KEY3_PRES        3   

//蜂鸣器
#define BEEP PTD6_OUT

//流水灯
#define LED1             PTD5_OUT
#define LED2             PTD3_OUT


//PID结构体
typedef struct                    //结构体，存放PID相关变量
{
  float P;                        //参数P
  float I;                        //参数I
  float D;                        //参数D
  float error[3];                 //误差存储数组
  float delat;                    //每次的调节结果
  float derr;                     //一阶误差
  float dderr;                    //二阶误差
  float result;                      //PID的输出，由于是增量式的所以初值请设为导轨平衡时的输出值，重要！不能是0要不就炸了
  
  float target;                   //PID调节的目标值     
  float feedback;
  float UP_Limit;
  float LOW_Limit;
}PID_Struct;

////系统状态结构体
//typedef struct
//{
//  long int Time_1ms;
//  
//}System_Status

#define     pit_delay_ms(PITn,ms)          pit_delay(PITn,ms * bus_clk_khz);        //PIT延时 ms
#define     pit_delay_us(PITn,us)          pit_delay(PITn,us * bus_clk_khz/1000);   //PIT延时 us

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