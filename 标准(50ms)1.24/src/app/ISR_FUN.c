#include "ISR_FUN.h"
#include "include.h"
void Speed_Control(void)
{
  static unsigned char speed_Period=0;//�ٶȿ������ڱ���
  static int L_50ms[speed_Period_Constant]={0},
              R_50ms[speed_Period_Constant]={0};//100ms�ڵ��ٶ�ֵ
//  static float speed_Delta=0;
//  static float Tmp_Speed_P =0; 
//  float SpeedRate = 0;
  //float SpeedRate;  
  //�����ٶȣ�ǰ20ms���ۼ�ֵ��
  if(speed_Period > 9)   
  speed_Period = 0;    
  Speed_L_50ms-=L_50ms[speed_Period];
  Speed_R_50ms-=R_50ms[speed_Period];
  L_50ms[speed_Period]=Motor1.Speed;
  R_50ms[speed_Period]=Motor2.Speed;
  Speed_L_50ms+=L_50ms[speed_Period];
  Speed_R_50ms+=R_50ms[speed_Period];
  speed_Period++;   
}