#include "include.h"
#include "getspeed.h"

void getspeed1_init()
{
  PORTA_PCR10= PORT_PCR_MUX(6); // ��������A12����ΪFTM2_PHA����  
  PORTA_PCR11= PORT_PCR_MUX(6); // ��������A13����ΪFTM2_PHB����  

  SIM_SCGC3|=SIM_SCGC3_FTM2_MASK;//ʹ��FTM2ʱ��    
  FTM2_CNT = 0;
  FTM2_MOD = 10000;
  FTM2_CNTIN = 0;
  FTM2_CNT = 0;
  FTM2_MODE |= FTM_MODE_WPDIS_MASK;
  FTM2_MODE |= FTM_MODE_FTMEN_MASK;
  FTM2_QDCTRL |= FTM_QDCTRL_QUADEN_MASK;
  FTM2_CONF |= FTM_CONF_BDMMODE(3);
  FTM2_SC |= FTM_SC_PS(0);//��ʱ��ʱ��Ԥ��Ƶ����Ϊ 1
  FTM2_SC |= FTM_SC_TOIE_MASK;
  (void)FTM2_SC;
  FTM2_SC &= ~FTM_SC_TOF_MASK;
  FTM2_SC |= FTM_SC_CLKS(1);
  
}

void getspeed2_init()
{
  PORTA_PCR8= PORT_PCR_MUX(6); // ��������A12����ΪFTM1_PHA����  
  PORTA_PCR9= PORT_PCR_MUX(6); // ��������A13����ΪFTM1_PHB����  

  SIM_SCGC6|=SIM_SCGC6_FTM1_MASK;//ʹ��FTM2ʱ��    
  FTM1_CNT = 0;
  FTM1_MOD = 10000;
  FTM1_CNTIN = 0;
  FTM1_CNT = 0;
  FTM1_MODE |= FTM_MODE_WPDIS_MASK;
  FTM1_MODE |= FTM_MODE_FTMEN_MASK;
  FTM1_QDCTRL |=FTM_QDCTRL_QUADEN_MASK;
  FTM1_CONF |= FTM_CONF_BDMMODE(3);
  FTM1_SC |= FTM_SC_PS(0);//��ʱ��ʱ��Ԥ��Ƶ����Ϊ 1
  FTM1_SC |= FTM_SC_TOIE_MASK;
  (void)FTM1_SC;
  FTM1_SC &= ~FTM_SC_TOF_MASK;
  FTM1_SC |= FTM_SC_CLKS(1);
}

void Get_speed1(Motor_Status* Motor)//����
{
    Motor->Dir = (FTM2_QDCTRL & FTM_QDCTRL_QUADIR_MASK);//�ⷽ��
    //����
    if(Motor->Dir==0)//��ת
    {
        if(10000 - FTM2_CNT < 9000)
          Motor->Speed = FTM2_CNT-10000;
    }
    else//��ת
    {
        if(FTM2_CNT < 9000)
          Motor->Speed = (FTM2_CNT);
    }
    
    //���
    FTM2_CNT = 0;
}

void Get_speed2(Motor_Status* Motor)//����
{
    Motor->Dir = (FTM1_QDCTRL & FTM_QDCTRL_QUADIR_MASK);//�ⷽ��
    //����
    if(Motor->Dir==0)//��ת
    {
        if(10000 - FTM1_CNT < 9000)
          Motor->Speed =10000- FTM1_CNT;
    }
    else//��ת
    {
        if(FTM1_CNT < 9000)
          Motor->Speed = -(FTM1_CNT);
    }
    
    //���
    FTM1_CNT = 0;
}