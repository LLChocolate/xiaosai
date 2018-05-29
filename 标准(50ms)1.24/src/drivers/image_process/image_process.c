#include "image_process.h"
#include "include.h"
int centre[ALL_LINE];
u8 ImageData[320];
u8 halfwidth[ALL_LINE];
//int black_L[ALL_LINE];
//int black_R[ALL_LINE];
//u16 Right_count[ALL_LINE];
//u16 Left_count[ALL_LINE];
u8 getLeft_flag[ALL_LINE];
u8 getRight_flag[ALL_LINE];
u8 Black_Lock=0;
u8 Image_Weight[Available_Num]={1};
u8 Three_lie_end[3]={0};

void image_process(void)
{
  u8 max_temp;
  u8 min_temp;
//  static int centre_temp=CENTER_;
  get_three_lie();
  min_temp=min_u8(Three_lie_end,3);
  max_temp=max_u8(Three_lie_end,3);
  if(Cross_Test()==1)
  {
    Road_Status_Flag=Cross;
  }
  if(min_temp<=100)
  {
//    BEEP=0;
    Slow_Flag=0;
    if(Road_Status_Flag==Cross)
    {
      get_black_line(Image_fire[Far_Point],Far_Point,HALF_WIDTH);//45cm�����ĵ�
      CenterlineToDiff(centre[Far_Point]);
    }
    else 
    {
      Slow_Flag=1;
      get_black_line(Image_fire[Start_Point],Start_Point,HALF_WIDTH);//45cm�����ĵ�
//    centre[Near_Point]=centre[Start_Point];
      CenterlineToDiff(centre[Start_Point]);
    }
    DIFF_PID_CHANGE_FLAG=0;//ʹ��ֱ��PID
    Road_Status_Flag=Straight;
  }
  
  else
  {
//    BEEP=1;
      get_black_line(Image_fire[Near_Point],Near_Point,HALF_NEAR);
//      centre[Start_Point]=centre[Near_Point];
      CenterlineToDiff(centre[Near_Point]);
//  centre_temp=centre[Start_Point];
//  get_black_line(Image_fire[],);
      DIFF_PID_CHANGE_FLAG=1;//ʹ�����PID
  }
  if(Three_lie_end[1]<=75)//ֱ��
  {
//    BEEP=1;
    Speed_max_to_min_diff=(75-Three_lie_end[1])*Acc_K;
    DIFF_PID_CHANGE_FLAG=0;//ʹ��ֱ��PID
  }
  else 
  {
    BEEP=0;
    Speed_max_to_min_diff=0;
    DIFF_PID_CHANGE_FLAG=1;//ʹ��ֱ��PID
  }
  if(Speed_max_to_min_diff>Acc_Limit)
    Speed_max_to_min_diff=Acc_Limit;
}


void get_black_line(unsigned char *ImageData_in,int hang,int half_width)//��׽����  
{
  static int Middle=160;  //�����м�Ĭ��ΪCENNTER
  int ccd_start=10,ccd_end=310;  //ccdɨ�����10���յ�310   
  int Left_Count=0,Right_Count=0;//���Ҽ���Ϊ0
  int getleft_flag=0,getright_flag=0;//�ҵ����ұ�־0
  int _black_R,_black_L;//�������Ҷ�
  static int _halfwidth=HALF_WIDTH;//����һ����Ĭ��80
  static unsigned char first_run=0;//���ܵ�0
  int i=0;
  if(first_run==0)  //���ܵ���0��
  {
    first_run++;//���ܵ��1
  }
  else//���first_run!=0
  {
    Middle = centre[hang];//centre[hang];//�м�Ϊcentre[hang]
    _halfwidth = half_width;//halfwidth[hang];//һ��Ϊhalfwidth[hang]
  }
  for(i=0;i<40;i++)
    for(int k=0;k<8;k++)
      ImageData[i*8+k] = (ImageData_in[i]>>(7-k))&0x01;
  
  Right_Count = Middle;//�Ѻ����м�ֵ�����Ҽ������
  while(!(ImageData[Right_Count+3]==1 
          && ImageData[Right_Count+2]==1
            && ImageData[Right_Count+1]==1)
        && Right_Count < ccd_end)//�������Ч����û���ҵ����������ڵ�
    Right_Count++;//���м�λ�ÿ�ʼ���������������������㶼�Ǻڵ�ͣ
  
  if(Right_Count<ccd_end)//�������Ч��Χ��
  {
    _black_R = Right_Count;
    getRight_flag[hang]=1;
    getright_flag=1;
  }
  else
  {
    getright_flag=0;
    getRight_flag[hang]=0;
  }
  

  Left_Count = Middle;
  while(!(ImageData[Left_Count-3]==1 
          && ImageData[Left_Count-2]==1
            && ImageData[Left_Count-1]==1)
        && Left_Count > ccd_start)	  
    Left_Count--;
  if(Left_Count > ccd_start)
  {
    _black_L = Left_Count; 
    getLeft_flag[hang]=1;
    getleft_flag=1;
  } 
  else
  {
    getleft_flag=0;
    getLeft_flag[hang]=0;
  }
  if(Left_Count==Middle||Right_Count==Middle)//�м䲿��Ϊ��ɫ
  {
    getright_flag=0;
    getRight_flag[hang]=0;
    getleft_flag=0;
    getLeft_flag[hang]=0;//flag������
    
    Right_Count = Middle;//
    while(!(ImageData[Right_Count-3]==0 
            && ImageData[Right_Count-2]==0
              && ImageData[Right_Count-1]==0)
          && Right_Count > ccd_start)	  
      Right_Count--;
    if(Right_Count > ccd_start)
    {
      _black_R = Right_Count; 
      getRight_flag[hang]=1;
      getright_flag=1;
    } 
    else
    {
      Left_Count = Middle;//�Ѻ����м�ֵ�����Ҽ������
      while(!(ImageData[Left_Count+3]==0 
              && ImageData[Left_Count+2]==0
                && ImageData[Left_Count+1]==0)
            && Left_Count < ccd_end)//�������Ч����û���ҵ����������ڵ�
        Left_Count++;//���м�λ�ÿ�ʼ���������������������㶼�Ǻڵ�ͣ

      if(Left_Count<ccd_end)//�������Ч��Χ��
      {
        _black_L = Left_Count;
        getLeft_flag[hang]=1;
        getleft_flag=1;
      }
    }
  }
  

  if(getleft_flag==0 && getright_flag==0)//���ұ߽綼û���ҵ�
  {
    if(sum_s16((int*)ImageData_in,40)>310)//��Ұȫ��
    {
      if(centre[hang-1]<160&&Black_Lock==Unlock)
      {
        Black_Lock=Left_Lock;
      }
      else if(centre[hang-1]>160&&Black_Lock==Unlock)
      {
        Black_Lock=Right_Lock;
      }
    }//�����κζ���
    else 
    {
      Black_Lock=Unlock;
    }
  }
  else if(getleft_flag!=1 && getright_flag==1)//�ҵ��ұ߽�
  {
    Black_Lock=Unlock;
    Middle = _black_R-_halfwidth;//�����м�λ��Ϊ�ұ߽�-���߿��һ��
    _black_L = _black_R - _halfwidth*2;//�������λ��Ϊ�ұ߽�-���߿�
  }
  else if(getleft_flag==1 && getright_flag!=1)//�ҵ���߽�
  {
    Black_Lock=Unlock;
    Middle = _black_L+_halfwidth;
    _black_R = _black_L + _halfwidth*2;
  }
  else if(getleft_flag==1 && getright_flag==1) //���ұ߽綼�ҵ�
  {
    Black_Lock=Unlock;
      if((_black_R - _black_L)<150)
        ;
      else
      _halfwidth=(int)((_black_R - _black_L)/2.0); //�����⵽�����Ҳ�ֵ����160��ȡ�м�λ��
    if(_halfwidth < 80)//����޷� 
      _halfwidth = 80;
    else if(_halfwidth >120)
      _halfwidth = 120; 
    Middle = (int)((_black_R + _black_L)/2.0);
  }
  if(Middle<20) //���ĵ��޷� 
    Middle=20;
  else if(Middle>300)
    Middle=300;
  
  //data record ��¼������������
  centre[hang] = Middle;
//  black_L[hang] = _black_L;
//  black_R[hang] = _black_R;
  halfwidth[hang] = _halfwidth;
  
// Right_count[hang]=Right_Count;
//  Left_count[hang]=Left_Count;

}


void get_three_lie(void)
{
  u16 left_lie=90,right_lie=230;
  u8 Left_flag=0,Right_flag=0,middle_flag=0;
  u8 Left_point,Middle_point,Right_point;
  Left_point=239;
  while(!(Image_Point(Left_point,left_lie)==1
          &&Image_Point(Left_point-1,left_lie)==1
            &&Image_Point(Left_point-2,left_lie)==1)&&Left_point>=2)
    Left_point--;
  if(Left_point!=239)//���߳�ʼ��Ϊ��
  {
    Left_flag=1;
  }
  Three_lie_end[0]=Left_point;
  Middle_point=239;
  while(!(Image_Point(Middle_point,160)==1
          &&Image_Point(Middle_point-1,160)==1
            &&Image_Point(Middle_point-2,160)==1)&&Middle_point>=2)
    Middle_point--;
  if(Middle_point!=239)//���߳�ʼ��Ϊ��
  {
    middle_flag=1;
  }
  Three_lie_end[1]=Middle_point;
  Right_point=239;
  while(!(Image_Point(Right_point,right_lie)==1
          &&Image_Point(Right_point-1,right_lie)==1
            &&Image_Point(Right_point-2,right_lie)==1)&&Right_point>=2)
    Right_point--;
  if(Right_point!=239)//���߳�ʼ��Ϊ��
  {
    Right_flag=1;
  }
  Three_lie_end[2]=Right_point;
  if(Left_flag==0)
    Road_Status_Flag=Right_turn;
  else if(Right_flag==0)
    Road_Status_Flag=Left_turn;
  else 
  {
    if(Left_point<Middle_point&&Middle_point<Right_point)
    {
      Road_Status_Flag=Left_turn;
    }
    else if(Left_point>Middle_point&&Middle_point>Right_point)
    {
      Road_Status_Flag=Right_turn;
    }
  }
 
}

void CenterlineToDiff(int center)
{
  Weight_mean=center;
//***************************************************ʹ�ü�Ȩƽ��ֵ��ת��*************************************  
  if(Weight_mean-CAMERA_W/2>=0)//��ת�ж�
  {
//      Road_Status_Flag=Right_turn; 
      if(LCD_DISPLAY_FLAG==1)
      LCD_PutChar(300,10,'R',Red,White);
  }
  else                       //��ת�ж�   
  {
//      Road_Status_Flag=Left_turn;
      if(LCD_DISPLAY_FLAG==1)
      LCD_PutChar(300,10,'L',Red,White);
      
      
  }
  Diff_error=CAMERA_W/2-Weight_mean;

}

//void TenPoint_Line(void)
//{
//  if(Start_Point)
//  Start_Point
//    HALF_WIDTH
//}


//void StoreDate(void)
//{
//  arm_copy_q7(Image_fire_Store[0],Image_fire[0],CAMERA_H*CAMERA_DMA_NUM);
//}

u8 Cross_Test(void)
{
  u8 i,cnt=0;
  for(i=0;i<5;i++)
  {
    if(sum_u8(Image_fire[Start_Point+i],40)<=5)
      cnt++;
  }
  if(cnt>3)
  {//BEEP=1;
  return 1;}
  else 
  {//BEEP=0;
  return 0;}
}
