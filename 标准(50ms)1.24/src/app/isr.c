/*
* �жϴ������
*/
#include "common.h"
#include "include.h"
#include "define.h"
#include "ISR_FUN.h"
extern signed int Speed_goal1_TEMP;//���ת��Ŀ��ֵ
extern signed int Speed_goal2_TEMP;//���ת��Ŀ��ֵ
/*************************************************************************
*                             Ұ��Ƕ��ʽ����������
*
*  �������ƣ�HardFault_Handler
*  ����˵����Ӳ���Ϸ��жϷ�����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-2-4    �Ѳ���
*  ��    ע��������LED��˸��ָʾ������Ӳ���Ϸ�
*************************************************************************/

/*************************************************************************
*  �������ƣ�VSYNC_IRQ
*  ����˵����PORTD�˿��жϷ�����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-1-25    �Ѳ���
*  ��    ע�����ź���Ҫ�Լ���ʼ�������
*************************************************************************/
void VSYNC_IRQ(void)
{
    static u32 flag;
    //Clear Interrupt flag
    flag = PORTD_ISFR;
    PORTD_ISFR = flag;
//    Image_Flag=0;//����������������0����
    if((flag>>2)&1)
    if(img_flag == IMG_START)	//��Ҫ��ʼ�ɼ�ͼ��
    {
      //����洢��ѭ��ʹ��
      //���֮ǰͼ����ʹ�õĴ洢����2����DMA�����λ����1�����ʱ�Ѵ���λ�ø�Ϊ2
      if(Memory_use_Flag==2)
      {
        Memory_use_Flag=1;
        DMA_PORTx2BUFF_Init(CAMERA_DMA_CH, (void *)&PTC_BYTE1_IN, (void *)Image_fire_Memory2, PTB22, DMA_BYTE1, CAMERA_SIZE , DMA_falling);
        DMA_DADDR(CAMERA_DMA_CH) = (u32)Image_fire_Memory2; //�ָ���ַ
      }
      //���֮ǰͼ����ʹ�õĴ洢����1����DMA�����λ����2�����ʱ�Ѵ���λ�ø�Ϊ1
      else if(Memory_use_Flag==1)
      {
        Memory_use_Flag=2;
        DMA_PORTx2BUFF_Init(CAMERA_DMA_CH, (void *)&PTC_BYTE1_IN, (void *)Image_fire_Memory1, PTB22, DMA_BYTE1, CAMERA_SIZE , DMA_falling);
        DMA_DADDR(CAMERA_DMA_CH) = (u32)Image_fire_Memory1; //�ָ���ַ
      }
        DMA_EN(CAMERA_DMA_CH);            		//ʹ��ͨ��CHn Ӳ������
        disable_irq(90);  
        img_flag=IMG_GATHER;
    }
    else					//ͼ��ɼ�����
    {
        img_flag = IMG_START;	//��ʼ�ɼ�ͼ��
        PORTD_ISFR=~0;		//д1���жϱ�־λ(����ģ���Ȼ�ص���һ���жϾ����ϴ����ж�)
        enable_irq(90); 
    }
//  if(PORTD_ISFR & (1<<11))//��ȡLDC1314����
//  {
////�����ж�1���жϷ���
//    LdcRead();
//    PORTD_ISFR |=(1<<11);//д��1����жϱ�־λ
//  }
}

/*************************************************************************
*  �������ƣ�DMA0_IRQHandler
*  ����˵����DMA0
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2012-1-25    �Ѳ���
*  ��    ע�����ź���Ҫ�����Լ���ʼ�����޸�
*************************************************************************/
void DMA0_IRQHandler()
{
  if(Memory_use_Flag==1)
  {
    Image_fire=&Image_fire_Memory2[0];
  }
  else if(Memory_use_Flag==2)
  {
    Image_fire=&Image_fire_Memory1[0];
  }
    DMA_DIS(CAMERA_DMA_CH);            	//�ر�ͨ��CHn Ӳ������
    DMA_IRQ_CLEAN(CAMERA_DMA_CH);           //���ͨ�������жϱ�־λ
    img_flag = IMG_FINISH ; 
    Image_Flag=1;
}

void PendSV_Handler(void)
{
  
}
void HardFault_Handler(void)
{

}
void SysTick_Handler(void)
{
  
}
void USART1_IRQHandler()
{
  
}

void USART2_IRQHandler()
{

  
}
  

void USART3_IRQHandler()
{

}
void USART5_IRQHandler()
{
    static u8 b_cnt=0;
enum
  {
    Motor,
    Diff
  }Mode;
  u8 Debug_Mode=Motor;
  const u8 i=0;
  
  u8 j;
  int Sum=0;
  char c;
  char Res_Temp[10]={0};
  static char Res[5];
  DisableInterrupts;
  uart_pendstr(UART5,Res_Temp);
//  uart_sendStr(UART5,Res_Temp);
  c=Res_Temp[0];
  switch(c)
  {
//  case 'n':
//    {
//      for(j=0;j<i;j++)
//      {
//        Res[j]=0;
//      }
//      i=0;              //�������
//      break;
//    }
  case 'm':
    {
      Debug_Mode=Motor;//�����PID
      LED2=!LED2;
      break;
    }
  case 's':
    {
      Debug_Mode=Diff;//������PD
      break;
    }
  case 'p':
    {
      for(j=0;j<i;j++)//��P
      {
        Sum+=Res[j]*power_s16(10,i-j-1);
      }
      if(Debug_Mode==Motor)
      {
        Motor1_PID.P=Sum;
        Motor2_PID.P=Sum;
      }
      else if(Debug_Mode==Diff)
      {
        Diff_PID.P=Sum;
      }
      break;
    }
  case 'i':
    {
      for(j=0;j<i;j++)//��I
      {
        Sum+=Res[j]*power_s16(10,i-j-1);
      }
      if(Debug_Mode==Motor)
      {
        Motor1_PID.I=Sum;
        Motor2_PID.I=Sum;
      }
      else if(Debug_Mode==Diff)
      {
        Diff_PID.I=Sum;
      }
      break;
    }
  case 'd':
    {
      for(j=0;j<i;j++)//��D
      {
        Sum+=Res[j]*power_s16(10,i-j-1);
      }
      if(Debug_Mode==Motor)
      {
        Motor1_PID.D=Sum;
        Motor2_PID.D=Sum;
      }
      else if(Debug_Mode==Diff)
      {
        Diff_PID.D=Sum;
      }
      break;
    }
  case 'b':
    {
      if(b_cnt==0)
      {
        Blue_Start_Flag=1;
//        Speed_Start_Flag=1;
        b_cnt++;
      }
      else
      {
        Speed_goal1=0;
        Speed_goal2=0;
        Speed_stand=0;
        stand_p=0;
        stand_d=0;
        Motor_enable_Flag=0;
      }
      break;
    }
  case 'a'://ͣ��
    {
      Speed_goal1_TEMP=Speed_goal1;
      Speed_goal2_TEMP=Speed_goal2;
      Speed_goal1=0;
      Speed_goal2=0;
      Speed_stand=0;
      stand_p=0;
      stand_d=0;
      Motor_enable_Flag=0;
      
//      disable()
      break;
//      FTM_PWM_Duty(MOTOR_1,0);
//      FTM_PWM_Duty(MOTOR_2,0);
    }
  case '1':
    {
      Speed_goal1+=100;
      break;
    }
  case '2':
    {
      Speed_goal1-=100;
      break;
    }
  case '3':
    {
      Speed_goal2+=100;
      break;
    }
  case '4':
    {
      Speed_goal2-=100;
      break;
    }
    
  default:
  {
    if(c>=48&&c<=57)//��������֣�����Ч
    {
//      i=strlen(Res_Temp);
      for(j=0;j<i;j++)
      {
        Res[j]=Res_Temp[j]-48;
      }
//      printf("\r\n%d\r\n",i);
    }
    
    break;
  }
  }
  if(Debug_Mode==Motor)
  {
    printf("\r\nMode:Motor\r\n");
  }
  else if(Debug_Mode==Diff)
  {
    printf("\r\nMode:Diff\r\n");
  }
  printf("\r\nRes:");
  
  for(j=0;j<i;j++)
  {
    uart_putchar(UART5,Res[j]+48);
  }
  printf("\r\n");
  LED1=!LED1;
  EnableInterrupts;
}


void PIT0_IRQHandler()
{
  static u8 TimeCnt_Start_Reduct_Flag = 1 ;
  static unsigned char TimeCnt_20ms = 0,TimeCnt_5ms=0;	  //5ms,20msʱ�������    
  static unsigned int  TimeCnt_2000ms = 0;
  static unsigned int  TimeCnt_Key_Start_ms = 0;
  static unsigned int  TimeCnt_Key__ms = 0;
  static unsigned int  TimeCnt_Start_Reduct_ms = 0;
  //ʱ���߸��� 
  Time_1ms++; 
  TimeCnt_5ms++;
  TimeCnt_20ms++;
  if(Reduct_Flag==1&&Blue_Start_Flag==1)
    TimeCnt_2000ms++;
  if(Key_Start_Flag==1)
    TimeCnt_Key_Start_ms++;
  if(Blue_Start_Flag==1&&TimeCnt_Start_Reduct_ms<1002)
  {
    TimeCnt_Start_Reduct_ms++;
    if(TimeCnt_Start_Reduct_ms==1000)
    TimeCnt_Start_Reduct_Flag=0;
  }
  if(TimeCnt_5ms >= 5)
    TimeCnt_5ms = 0;
  if(TimeCnt_20ms >= 20)
    TimeCnt_20ms = 0;
  if(TimeCnt_2000ms >= 2000)
  {
    TimeCnt_2000ms = 0;
    Speed_stand--;
  }
  if(TimeCnt_Key_Start_ms >= 3000)
  {
    Blue_Start_Flag=1;
    Key_Start_Flag=0;
  }
if(Time_1ms==2000)
{
  temp_CNT_WATCH=temp_cnt;
}
//PIT0������
//��������
    if(button_timeout<16)
    {
      button_timeout--;
    }
  if(button_timeout==0)//��ʱ10ms��ⰴ��״̬
  {
      if(KEY1==0)
      {
        Reduct_Flag=1;
        Key_status=KEY1_PRES;
//        BEEP=1;
        LED1=0;
      }
      else if(KEY2==0)
      {
        Key_Start_Flag=1;
        Key_status=KEY2_PRES;
        LED2=0;
      }
      else if(KEY3==0)
      {
        Key_status=KEY3_PRES;
      }
  }

//����������������
//**********************************************����ͷͼ����
//  if
  
  
//***************************************************���ٺ���
  if(TimeCnt_5ms==1)
  {
    Diff_PID.feedback=Diff_error;
    if(DIFF_PID_CHANGE_FLAG==0)
    {
      Diff_PID.P=stand_p;
      Diff_PID.D=stand_d;
      Master_Speed=Speed_stand+Speed_max_to_min_diff;
    }
    else 
    {
        Diff_PID.P=stand_p*1.05;
        Diff_PID.D=stand_d*1.05;
      if(Slow_Flag==1)
      {
        Master_Speed=Speed_stand;
      }
      else 
      {
        Master_Speed=Speed_stand;
      }
    }
    Diff_PID_Process(&Diff_PID);
    if(Black_Lock==Left_Lock)
    {
      Diff_PID.result=DIFF_UP;
    }
    else if(Black_Lock==Right_Lock)
    {
      Diff_PID.result=DIFF_DOWN;
    }
    Speed_goal1=Master_Speed-Diff_PID.result;
    Speed_goal2=Master_Speed+Diff_PID.result;
  }
  
//****************************************************���ٺ���
  if(TimeCnt_5ms==2&&Blue_Start_Flag==1)//20msִ��һ��
  {
    Get_speed1(&Motor1);
    Get_speed2(&Motor2);
    Speed_Control();
    
//  }
//  if(TimeCnt_5ms==7)
//  {
    if(TimeCnt_Start_Reduct_Flag==1)
      Motor1_PID.feedback=Motor1.Speed;
    else 
      Motor1_PID.feedback=Speed_L_50ms*1.0/10;
    PID_process(&Motor1_PID);
    if(Motor1_PID.result<0)
    {
      MOTOR1_DIR=0;//���result<0���������
      Duty_Motor1=-Motor1_PID.result;
      FTM_PWM_Duty(MOTOR_1,Duty_Motor1);
    }
    else
    {
      MOTOR1_DIR=1;
      Duty_Motor1=Motor1_PID.result;
      FTM_PWM_Duty(MOTOR_1,0xffff-Duty_Motor1);
    }
    
    if(TimeCnt_Start_Reduct_Flag==1)
      Motor2_PID.feedback=Motor2.Speed;
    else
      Motor2_PID.feedback=Speed_R_50ms*1.0/10;
    PID_process(&Motor2_PID);
    if(Motor2_PID.result<0)
    {
      MOTOR2_DIR=0;//���result<0���������
      Duty_Motor2=-Motor2_PID.result;
      FTM_PWM_Duty(MOTOR_2,Duty_Motor2);
    }
    else
    {
      MOTOR2_DIR=1;
      Duty_Motor2=Motor2_PID.result;
      FTM_PWM_Duty(MOTOR_2,0xffff-Duty_Motor2);
    }
  }
  
  if(TimeCnt_20ms==3)
  {
    ldc1314_result[0]=LDC1314_Result(0);
    ldc1314_result[1]=LDC1314_Result(1);
    ldc1314_result[2]=LDC1314_Result(2);
    ldc1314_result[3]=LDC1314_Result(3);
//    LdcRead();
  }
    //*****************************************************adc���
  if((Time_1ms%10)==0)//ѡ����ģʽ1��ADCʹ��
  {
//    ADC_Value=ad_mid(MYADC_,ADC_16bit);
  }
//���ٺ�������
  PIT_Flag_Clear(PIT0);
}
void PIT3_IRQHandler()
{
//  Delay_Mark=1;                 //������ʱѭ����־λ��1
//  disable_irq(71);             //�жϴ�һ�κ󱻹ر�
  PIT_Flag_Clear(PIT3);
}

void PIT2_IRQHandler()
{
//  TEMP_OF_MARK=1;
  PIT_Flag_Clear(PIT2);
}
void PORTC_IRQHandler()
{

}
void PORTA_IRQHandler()
{
  u8 n=0;
  n=17;
  if(PORTA_ISFR & (1<<n))
  {
//�����ж�1���жϷ���
    button_timeout=15;//��־��15
    PORTA_ISFR |=(1<<n);//д��1����жϱ�־λ
  }
  n=15;
  if(PORTA_ISFR & (1<<n))
  {
//�����ж�1���жϷ���
    button_timeout=15;//��־��15
    PORTA_ISFR |=(1<<n);//д��1����жϱ�־λ
  }
}

void PORTB_IRQHandler()
{
  u8 n=0;
  n=1;
  if(PORTB_ISFR & (1<<n))
  {
//�����ж�1���жϷ���
    button_timeout=15;//��־��15
    PORTB_ISFR |=(1<<n);//д��1����жϱ�־λ
  }
}

void PORTE_IRQHandler()
{

}
void FTM0_IRQHandler()
{
  
}
void FTM1_IRQHandler()
{
  
}

