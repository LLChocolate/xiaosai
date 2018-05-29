#include "mykey.h"

void myKEY_Init(void)
{
  gpio_init(PORTB,1,GPI,HIGH);
  port_init_NoALT(PTB1,PULLUP);
  gpio_init(PORTA,17,GPI,HIGH);
  port_init_NoALT(PTA17,PULLUP);
  gpio_init(PORTA,15,GPI,HIGH);
  port_init_NoALT(PTA15,PULLUP);

}

void myKEY_Exti_Init(void)
{
   exti_init(PORTB,1,falling_up);
   exti_init(PORTA,17,falling_up);
   exti_init(PORTA,15,falling_up);
}

u8 KEY_Scan(void)
{
  static u8 key_up=1;//�������ɿ���־	  
  if(key_up&&(KEY1==0||KEY2==0||KEY3==0))
  {
    delayms(10);//ȥ���� 
    key_up=0;
    if(KEY1==0)                  return KEY1_PRES;
    else if(KEY2==0)            return KEY2_PRES;
    else if(KEY3==0)            return KEY3_PRES;
  }
  else if(KEY1==1&&KEY2==1&&KEY3==1)
  {
    key_up=1; 	    
  }
  return 0;// �ް�������
}
