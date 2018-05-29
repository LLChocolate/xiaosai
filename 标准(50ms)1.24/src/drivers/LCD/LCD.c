#include "include.h"
#include "8X16.h"
#include "GB1616.h"	//16*16������ģ
#include "GB3232.h"	//32*32������ģ
#include "lcd.h"

/******************** (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� ********************
* �ļ���       ��LCD.c
* ����         ������240*320LCD��ʾ���ĵײ���������
* ʵ��ƽ̨     ������ӡ�󿪷���
* ��汾       ������Ұ���
* Ƕ��ϵͳ     ��
* ����         ��xuxu
**********************************************************************************/

u16 Brush_Color; 
u16 Back_Color;

/************************************************
*  �������ƣ�LCD_PORT_init
*  ����˵����240*320��SPI LCD���ų�ʼ��
*  ����˵������
*  �������أ���0
*  �޸�ʱ�䣺2014-1-14    �Ѿ�����
*************************************************/
void LCD_PORT_init()
{
  gpio_init(PORTE,12, GPO, HIGH);//dc
  gpio_init(PORTE,11, GPO, HIGH);//rst
  gpio_init(PORTE,10, GPO, HIGH);//sdi
  gpio_init(PORTE,9, GPO, HIGH);//scl
}

/************************************************
*  �������ƣ�LCD_Reset
*  ����˵����240*320��SPI LCD��λ
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2014-1-14    �Ѿ�����
*************************************************/
void LCD_Reset()
{
  reset = 0;
  delayms(20);
  reset = 1;
  delayms(20);
}


/************************************************
*  �������ƣ�LCD_Reset
*  ����˵����240*320��SPI LCDģ���ʼ��
*  ����˵����directionȡTRUE��FALSE����Ļ����֮��
*  �������أ���
*  �޸�ʱ�䣺2014-1-14    �Ѿ�����
*************************************************/
void LCD_init(unsigned char direction)
{
  //�ȶ˿������������
  LCD_PORT_init();
  
  reset=0;
  delayms(20);
  reset=1;
  delayms(20);
  //------------------------------------------------------------------//
  //-------------------Software Reset-------------------------------//
  write_command(0xCB);
  write_data(0x39);
  write_data(0x2C);
  write_data(0x00);
  write_data(0x34);
  write_data(0x02);
  
  write_command(0xCF);
  write_data(0x00);
  write_data(0XC1);
  write_data(0X30);
  
  write_command(0xE8);
  write_data(0x85);
  write_data(0x00);
  write_data(0x78);
  
  write_command(0xEA);
  write_data(0x00);
  write_data(0x00);
  
  write_command(0xED);
  write_data(0x64);
  write_data(0x03);
  write_data(0X12);
  write_data(0X81);
  
  write_command(0xF7);
  write_data(0x20);
  
  write_command(0xC0);    //Power control
  write_data(0x23);   //VRH[5:0]
  
  write_command(0xC1);    //Power control
  write_data(0x10);   //SAP[2:0];BT[3:0]
  
  write_command(0xC5);    //VCM control
  write_data(0x3e); //�Աȶȵ���
  write_data(0x28);
  
  write_command(0xC7);    //VCM control2
  write_data(0x86);  //--
  
  write_command(0x36);    // Memory Access Control
  if(direction)
    write_data(0xE8); //C8	   //48 68����//28 E8 ����
  else
    write_data(0x28);//0b00101000
  
  
  write_command(0x3A);
  write_data(0x55);
  
  write_command(0xB1);
  write_data(0x00);
  write_data(0x18);
  
  write_command(0xB6);    // Display Function Control
  write_data(0x08);
  write_data(0x82);
  write_data(0x27);
  
  write_command(0xF2);    // 3Gamma Function Disable
  write_data(0x00);
  
  write_command(0x26);    //Gamma curve selected
  write_data(0x01);
  
  write_command(0xE0);    //Set Gamma
  write_data(0x0F);
  write_data(0x31);
  write_data(0x2B);
  write_data(0x0C);
  write_data(0x0E);
  write_data(0x08);
  write_data(0x4E);
  write_data(0xF1);
  write_data(0x37);
  write_data(0x07);
  write_data(0x10);
  write_data(0x03);
  write_data(0x0E);
  write_data(0x09);
  write_data(0x00);
  
  write_command(0XE1);    //Set Gamma
  write_data(0x00);
  write_data(0x0E);
  write_data(0x14);
  write_data(0x03);
  write_data(0x11);
  write_data(0x07);
  write_data(0x31);
  write_data(0xC1);
  write_data(0x48);
  write_data(0x08);
  write_data(0x0F);
  write_data(0x0C);
  write_data(0x31);
  write_data(0x36);
  write_data(0x0F);
  
  write_command(0x11);    //Exit Sleep
  delayms(20);
  
  write_command(0x29);    //Display on
  write_command(0x2c);
}

/************************************************
*  �������ƣ�write_command
*  ����˵����LCDдָ���
*  ����˵����cΪָ��
*  �������أ���
*  �޸�ʱ�䣺2014-1-14    �Ѿ�����
*************************************************/
void  write_command(unsigned char  c)
{
  dcx=0;
  sdi=(GET_BITFIELD(c))->bit7;scl=0;scl=1;
  sdi=(GET_BITFIELD(c))->bit6;scl=0;scl=1;
  sdi=(GET_BITFIELD(c))->bit5;scl=0;scl=1;
  sdi=(GET_BITFIELD(c))->bit4;scl=0;scl=1;
  sdi=(GET_BITFIELD(c))->bit3;scl=0;scl=1;
  sdi=(GET_BITFIELD(c))->bit2;scl=0;scl=1;
  sdi=(GET_BITFIELD(c))->bit1;scl=0;scl=1;
  sdi=(GET_BITFIELD(c))->bit0;scl=0;scl=1;
}

/************************************************
*  �������ƣ�write_data
*  ����˵����LCDд���ݺ���
*  ����˵����dΪ���ݣ�Ϊһ��BYTE������
*  �������أ���
*  �޸�ʱ�䣺2014-1-14    �Ѿ�����
*************************************************/
void  write_data(unsigned char  d)
{
  dcx=1;
  sdi=(GET_BITFIELD(d))->bit7;scl=0;scl=1;
  sdi=(GET_BITFIELD(d))->bit6;scl=0;scl=1;
  sdi=(GET_BITFIELD(d))->bit5;scl=0;scl=1;
  sdi=(GET_BITFIELD(d))->bit4;scl=0;scl=1;
  sdi=(GET_BITFIELD(d))->bit3;scl=0;scl=1;
  sdi=(GET_BITFIELD(d))->bit2;scl=0;scl=1;
  sdi=(GET_BITFIELD(d))->bit1;scl=0;scl=1;
  sdi=(GET_BITFIELD(d))->bit0;scl=0;scl=1;
}

/************************************************
*  �������ƣ�write_word
*  ����˵����LCDд���ݺ���
*  ����˵����datΪ���ݣ�Ϊ����BYTE������
*  �������أ���
*  �޸�ʱ�䣺2014-1-14    �Ѿ�����
*************************************************/
void write_word(unsigned int dat)
{
  write_data(dat>>8);
  write_data(dat);
}






/************************************************
*  �������ƣ�RamAdressSet
*  ����˵����LCD������RAM��ַ
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2014-1-14    �Ѿ�����
*************************************************/
void  RamAdressSet()
{
  write_command(0x2A);
  write_data(0x00);
  write_data(0x00);
  write_data(0x00);
  write_data(0xaf);
  
  write_command(0x2B);
  write_data(0x00);
  write_data(0x00);
  write_data(0x00);
  write_data(0xdb);		
}


/************************************************
*  �������ƣ�LCD_SetPos
*  ����˵����LCD������д����Ļ�ĵ�ַ
*  ����˵����������X0~X1��������ΪY0~Y1
*  �������أ���
*  �޸�ʱ�䣺2014-1-14    �Ѿ�����
*************************************************/
void LCD_SetPos(unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1)
{
  write_command(0x2A);
  write_data(x0>>8);
  write_data(x0);
  write_data(x1>>8);
  write_data(x1);
  
  write_command(0x2B);
  write_data(y0>>8);
  write_data(y0);
  write_data(y1>>8);
  write_data(y1);
  write_command(0x2c);
}


/************************************************
*  �������ƣ�LCD_PutChar
*  ����˵����LCD��дһ��Char��Ĭ��Ϊ8*16����ģ
*  ����˵����������x��������Ϊy��cΪ���ݣ�fColorΪ����ɫ��bColorΪ������ɫ
*  �������أ���
*  �޸�ʱ�䣺2014-1-14    �Ѿ�����
*************************************************/
void LCD_PutChar(unsigned int x, unsigned int y,unsigned char c, unsigned int fColor, unsigned int bColor)
{
  LCD_PutChar8x16( x, y, c, fColor, bColor );
}


/************************************************
*  �������ƣ�LCD_PutString
*  ����˵����LCD��д�ַ���
*  ����˵����������x��������Ϊy��sΪ�ַ���ָ�룬fColorΪ����ɫ��bColorΪ������ɫ
*  �������أ���
*  �޸�ʱ�䣺2014-1-14    �Ѿ�����
*************************************************/
void LCD_PutString(unsigned int x, unsigned int y, unsigned char *s, unsigned int fColor, unsigned int bColor)
{
  unsigned char l=0;
  while(*s) {
    if( *s < 0x80)
    {
      LCD_PutChar(x+l*8,y,*s,fColor,bColor);
      s++;l++;
    }
    else
    {
      PutGB1616(x+l*8,y,(unsigned char*)s,fColor,bColor);
      s+=2;l+=2;
    }
  }
}


/************************************************
*  �������ƣ�LCD_PutChar8x16
*  ����˵����LCD��д�ַ���8*16��ģ
*  ����˵����������x��������Ϊy��cΪASCII�룬fColorΪ����ɫ��bColorΪ������ɫ
*  �������أ���
*  �޸�ʱ�䣺2014-1-14    �Ѿ�����
*************************************************/
void LCD_PutChar8x16(unsigned int x, unsigned int y,unsigned char c, unsigned int fColor, unsigned int bColor)
{
  unsigned int i,j;
  LCD_SetPos(x,x+8-1,y,y+16-1);
  for(i=0; i<16;i++)
  {
    unsigned char m=Font8x16[c*16+i];
    for(j=0;j<8;j++)
    {
      if((m&0x80)==0x80)
        write_word(fColor);
      else
      {
          write_word(bColor);
      }
      m<<=1;
    }
  }
}

/************************************************
*  �������ƣ�PutGB1616
*  ����˵����LCD��д����16*16��ģ
*  ����˵����������x��������Ϊy��c[2]Ϊ���ӵĻ����룬fColorΪ����ɫ��bColorΪ������ɫ
*  �������أ���
*  �޸�ʱ�䣺2014-1-14    �Ѿ�����
*  ��ע    ����Ҫ�Խ����ӿ�codeGB_16
*************************************************/
void PutGB1616(unsigned int x, unsigned int  y, unsigned char c[2], unsigned int fColor,unsigned int bColor)
{
  unsigned int i,j,k;
  LCD_SetPos(x,  x+16-1,y, y+16-1);
  for (k=0;k<64;k++)
  { //64��ʾ�Խ����ֿ��еĸ�����ѭ����ѯ����
    if ((codeGB_16[k].Index[0]==c[0])&&(codeGB_16[k].Index[1]==c[1]))
    {
      for(i=0;i<32;i++)
      {
        unsigned short m=codeGB_16[k].Msk[i];
        for(j=0;j<8;j++)
        {
          if((m&0x80)==0x80)
            write_word(fColor);
          else
            write_word(bColor);
          m<<=1;
        }
      }
    }
  }
}

/************************************************
*  �������ƣ�PutGB3232
*  ����˵����LCD��д����32*32��ģ
*  ����˵����������x��������Ϊy��c[2]Ϊ���ӵĻ����룬fColorΪ����ɫ��bColorΪ������ɫ
*  �������أ���
*  �޸�ʱ�䣺2014-1-14    �Ѿ�����
*  ��ע    ����Ҫ�Խ����ӿ�codeGB_32
*************************************************/
void PutGB3232(unsigned int x, unsigned int  y, unsigned char c[2], unsigned int fColor,unsigned int bColor)
{
  unsigned int i,j,k;
  LCD_SetPos(x,  x+32-1,y, y+32-1);
  for (k=0;k<15;k++) { //15��ʾ�Խ����ֿ��еĸ�����ѭ����ѯ����
    if ((codeGB_32[k].Index[0]==c[0])&&(codeGB_32[k].Index[1]==c[1])){
      for(i=0;i<128;i++) {
        unsigned short m=codeGB_32[k].Msk[i];
        for(j=0;j<8;j++) {
          if((m&0x80)==0x80) {
            write_word(fColor);
          }
          else {
            write_word(bColor);
          }
          m<<=1;
        }
      }
    }
  }	
}


/************************************************
*  �������ƣ�Disp_single_colour
*  ����˵����LCD��ˢ������
*  ����˵����ColorΪ������ɫ
*  �������أ���
*  �޸�ʱ�䣺2014-1-14    �Ѿ�����
*************************************************/
void Disp_single_colour(unsigned int color)
{
  unsigned int i,j;
  LCD_SetPos(0,320-1,0,240-1);
  for (i=0;i<240;i++)
    for (j=0;j<320;j++)
      write_word(color);
}

void LCD_Fill_onecolor(u16 xx1 ,u16 yy1,u16 xx2, u16 yy2,u16 color)
{
  unsigned int i,j;
  LCD_SetPos(xx1,xx2-1,yy1,240-1);
  for (i=0;i<(yy2-yy1);i++)
    for (j=0;j<(xx2-xx1);j++)
      write_word(color);
}


/************************************************
*  �������ƣ�Draw_single_line
*  ����˵����LCD�Ļ����ߺ���
*  ����˵����axisΪ�л����У�ȡ'H'����'L'��lineΪ�ڼ��л��ߵڼ��У�ColorΪ��ɫ
*  �������أ���
*  �޸�ʱ�䣺2014-1-14    �Ѿ�����
*************************************************/
void Draw_single_line(unsigned char axis,unsigned int line,unsigned int color)
{
  unsigned int i;
  if(axis=='L')
  {
    LCD_SetPos(line,line,0,240-1);
    for (i=0;i<240;i++)
      write_word(color);
  }
  else if(axis=='H')
  {
    LCD_SetPos(0,320-1,line,line);
    for (i=0;i<320;i++)
      write_word(color);
  }
}

void Draw_line(unsigned int line,unsigned int color)
{
  unsigned int i;
  LCD_SetPos(10,10,128-line/2,128+line/2);
  for (i=0;i<line;i++)
    write_word(color);
}

/************************************************
*  �������ƣ�LCD_Put_Unsigned_Int
*  ����˵����LCD����ʾUnsigned_Int
*  ����˵����x��yΪ���꣬s0ΪҪ��д���ַ�����pnumΪ��ֵ��fColor��bColorΪ�ֺ͵�ɫ
*  �������أ���
*  �޸�ʱ�䣺2014-1-14    �Ѿ�����
*************************************************/
void LCD_Put_Unsigned_Int(unsigned int x,unsigned int y,unsigned char s0[],unsigned int pnum,unsigned int fColor, unsigned int bColor)
{
  unsigned char l=0;
  unsigned char s[30];
  unsigned char count=0;
  //copy
  count=0;
  while(s0[count])
  {
    s[count] = s0[count];
    count++;
  }
  //strcat
  if(pnum<10)
  {  s[count]=pnum+'0';s[count+1]='\0';}
  else if((10<=pnum)&&(pnum<100))
  {  s[count]=pnum/10+'0';s[count+1]=pnum%10+'0';s[count+2]='\0';}
  else if(pnum<=999)
  {
    s[count]=pnum/100+'0';
    s[count+1]=pnum/10%10+'0';
    s[count+2]=pnum%10+'0';
    s[count+3]='\0';
  }
  else if(pnum<=9999)
  {
    s[count]=pnum/1000+'0';
    s[count+1]=pnum/100%10+'0';
    s[count+2]=pnum/10%10+'0';
    s[count+3]=pnum%10+'0';
    s[count+4]='\0';
  }
  else if(pnum<=99999)
  {
    s[count]=pnum/10000+'0';
    s[count+1]=pnum/1000%10+'0';
    s[count+2]=pnum/100%10+'0';
    s[count+3]=pnum/10%10+'0';
    s[count+4]=pnum%10+'0';
    s[count+5]='\0';
  }
  
  
  for(char i=0 ; i<7;i++)//�����ʷֵ
  {
    
    LCD_PutChar(x+i*8,y,'0',bColor,bColor);
    
  }
  
  count=0;
  while(s[count])
  {
    if( s[count] < 0x80)
    {
      LCD_PutChar(x+l*8,y,s[count],fColor,bColor);
      count++;
      l++;
    }
    else
    {
      PutGB1616(x+l*8,y,(unsigned char*)s[count],fColor,bColor);
      count+=2;
      l+=2;
    }
  }
}


/************************************************
*  �������ƣ�LCD_Put_Int
*  ����˵����LCD����ʾUnsigned_Int
*  ����˵����x��yΪ���꣬s0ΪҪ��д���ַ�����pnumΪ��ֵ��fColor��bColorΪ�ֺ͵�ɫ
*  �������أ���
*  �޸�ʱ�䣺2014-1-14    �Ѿ�����
*************************************************/
void LCD_Put_Int(unsigned int x,unsigned int y,unsigned char s0[],int pnum,unsigned int fColor, unsigned int bColor)
{
  unsigned char l=0;
  unsigned char s[30];
  unsigned char count=0;
  
  //copy
  count=0;
  while(s0[count])
  {
    s[count] = s0[count];
    count++;
  }
  s[count] = ' ';count++;  //yuanlong
  //strcat
  if(pnum < 0)
  {
    s[count] = '-';
    count++;
    pnum = (-1) * pnum;
  }
  if(pnum < 10)
  {  s[count]=pnum+'0';s[count+1]='\0';}
  else if((10<=pnum)&&(pnum<100))
  {  s[count]=pnum/10+'0';s[count+1]=pnum%10+'0';s[count+2]='\0';}
  else if(pnum<=999)
  {
    s[count]=pnum/100+'0';
    s[count+1]=pnum/10%10+'0';
    s[count+2]=pnum%10+'0';
    s[count+3]='\0';
  }
  else if(pnum<=9999)
  {
    s[count]=pnum/1000+'0';
    s[count+1]=pnum/100%10+'0';
    s[count+2]=pnum/10%10+'0';
    s[count+3]=pnum%10+'0';
    s[count+4]='\0';
  }
  else if(pnum<=99999)
  {
    s[count]=pnum/10000+'0';
    s[count+1]=pnum/1000%10+'0';
    s[count+2]=pnum/100%10+'0';
    s[count+3]=pnum/10%10+'0';
    s[count+4]=pnum%10+'0';
    s[count+5]='\0';
  }
  
  for(char i=0 ; i<7;i++)//�����ʷֵ
  {
    
    LCD_PutChar(x+i*8,y,' ',bColor,bColor);
    
  }
  
  count=0;
  while(s[count])
  {
    if( s[count] < 0x80)
    {
      LCD_PutChar(x+l*8,y,s[count],fColor,bColor);
      count++;
      l++;
    }
    else
    {
      PutGB1616(x+l*8,y,(unsigned char*)s[count],fColor,bColor);
      count+=2;
      l+=2;
    }
    LCD_PutChar(x+l*8,y,' ',bColor,bColor);
  }
}


/************************************************
*  �������ƣ�LCD_Put_Int
*  ����˵����LCD����ʾUnsigned_Int
*  ����˵����x��yΪ���꣬s0ΪҪ��д���ַ�����fΪ��ֵ��fColor��bColorΪ�ֺ͵�ɫ
*  �������أ���
*  �޸�ʱ�䣺2014-1-14    �Ѿ�����
*************************************************/
void LCD_Put_Float(unsigned int x,unsigned int y,unsigned char s0[],float f,unsigned int fColor, unsigned int bColor)
{
  unsigned char l=0;
  unsigned char s[30];
  unsigned char count=0;
  int pnum;
  //copy
  
  count=0;
  while(s0[count])
  {
    s[count] = s0[count];
    count++;
  }
  //strcat
  pnum = (int)(f);
  if(pnum < 0)
  {
    s[count++] = '-';
    pnum = (-1) * pnum;
  }
  if(pnum <= 9)
  {
    s[count++]=pnum+'0';
  }
  else if(pnum <= 99)
  {
    s[count++]=pnum/10+'0';
    s[count++]=pnum%10+'0';
  }
  else if(pnum<=999)
  {
    s[count++]=pnum/100+'0';
    s[count++]=pnum/10%10+'0';
    s[count++]=pnum%10+'0';
  }
  else if(pnum<=9999)
  {
    s[count++]=pnum/1000+'0';
    s[count++]=pnum/100%10+'0';
    s[count++]=pnum/10%10+'0';
    s[count++]=pnum%10+'0';
  }
  else if(pnum<=99999)
  {
    s[count++]=pnum/10000+'0';
    s[count++]=pnum/1000%10+'0';
    s[count++]=pnum/100%10+'0';
    s[count++]=pnum/10%10+'0';
    s[count++]=pnum%10+'0';
  }
  //С���������λ
  if(f<0)
    f=(-1)*f;
  s[count++] = '.';
  s[count++] = ((int)(f*10))%10 + '0';
  s[count++] = ((int)(f*100))%10 + '0';
  s[count++] = ((int)(f*1000))%10 + '0';
  s[count++] = '\0';
  
  for(char i = 0 ; i < 7;i++)//�����ʷֵ
  {
    
    LCD_PutChar(x+i*8,y,'_',bColor,bColor);
    
  }
  //print
  count=0;
  while(s[count])
  {
    if( s[count] < 0x80)
    {
      LCD_PutChar(x+l*8,y,s[count],fColor,bColor);
      count++;
      l++;
    }
    else
    {
      PutGB1616(x+l*8,y,(unsigned char*)s[count],fColor,bColor);
      count+=2;
      l+=2;
    }
  }
}

/************************************************
*  �������ƣ�draw_double
*  ����˵����LCD����ʾ00000.0
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2014-1-14    �Ѿ�����
*************************************************/
void draw_double(unsigned short x,unsigned short y,double pnum,unsigned int color)
{
  if(pnum<0)
  {
    LCD_PutChar(x, y, '-', color,Black);
    pnum=-pnum;
    x+=8;
  }
  else if(pnum==0)
  {
    LCD_PutChar(x, y, '0', color,Black);
    x+=8;
  }  
  
  if((int)pnum/10000){LCD_PutChar(x, y, (int)(pnum/10000)+'0', color ,Black);x+=8;}
  if((int)pnum/1000){LCD_PutChar(x, y, (int)(pnum/1000)%10+'0', color ,Black);x+=8;} //pnum=pnum%1000;
  if((int)pnum/100){LCD_PutChar(x, y, (int)(pnum/100)%10+'0', color ,Black);x+=8;}  //pnum=pnum%100;
  if((int)pnum/10){LCD_PutChar(x, y, (int)(pnum/10)%10+'0', color ,Black);x+=8;}  // pnum=pnum%10;
  if((int)pnum/1){LCD_PutChar(x, y, (int)(pnum)%10+'0', color ,Black);x+=8;} 
  if((int)((pnum-(int)pnum)/.1))
  {
    LCD_PutChar(x, y, '.', color ,Black);x+=8;
    LCD_PutChar(x, y, (int)((pnum-(int)pnum)/.1)+'0', color ,Black);x+=8;
  }      
  LCD_PutChar(x, y,' ', White ,Black);
}
/************************************************
*  �������ƣ�Print_child
*  ����˵����LCD����ʾһ��С�ƺ�ͼƬ
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2014-1-14    �Ѿ�����
*************************************************/
void Print_child()
{
  unsigned int i=0;
  LCD_SetPos(0,320-1,0,221-1);
  for (i=0;i<7480;i++)
  {
    if((GET_BITFIELD(Logo[i]))->bit7)write_word(Black);else write_word(Yellow);
    if((GET_BITFIELD(Logo[i]))->bit6)write_word(Black);else write_word(Yellow);
    if((GET_BITFIELD(Logo[i]))->bit5)write_word(Black);else write_word(Yellow);
    if((GET_BITFIELD(Logo[i]))->bit4)write_word(Black);else write_word(Yellow);
    if((GET_BITFIELD(Logo[i]))->bit3)write_word(Black);else write_word(Yellow);
    if((GET_BITFIELD(Logo[i]))->bit2)write_word(Black);else write_word(Yellow);
    if((GET_BITFIELD(Logo[i]))->bit1)write_word(Black);else write_word(Yellow);
    if((GET_BITFIELD(Logo[i]))->bit0)write_word(Black);else write_word(Yellow);
  }
}
/*********************************************************** 
�������ƣ� SendPixel
�������ܣ� LCD��ʾccdͼ��
��ڲ����� Pixel
���ڲ����� ��
�� ע��    ��
�޸�ʱ�䣺2015-1-3
***********************************************************/ 
//void SendPixel(unsigned char n)
//{
//  unsigned char i=0;
//  unsigned int tmp=0;
//  unsigned int color=0;
//  static unsigned int ImageLine[3][256]={0};//��ʷֵ
//  static unsigned int Lcd_Pixel[128]={0};//���λ���ֵ
//  
//  if(n==1)  
//  {
//    for(i=0;i<128;i++)
//    {
//      Lcd_Pixel[i]=Image1.Pixel[i];
//    }
//    color = Black;
//  }
//  else if(n==2)
//  {
//    for(i=0;i<128;i++)
//    {
//      Lcd_Pixel[i]=Image2.Pixel[i];
//    }
//    color = Blue;
//  } 
//  else if(n==3)
//  {
//    for(i=0;i<128;i++)
//    {
//      Lcd_Pixel[i]=Image3.Pixel[i];
//    }
//    color = Red;
//  }
//  //����ǰ��һ����
//  
//  for(i=0;i<128;i++)
//  {
//    tmp=2*i;
//    //��ԭ
//    LCD_SetPos(tmp,tmp,239 - ImageLine[n-1][tmp],239 - ImageLine[n-1][tmp]);
//    write_word(Yellow);
//    if(Lcd_Pixel[i] > 235)
//      ImageLine[n-1][tmp] = 235;
//    else
//      ImageLine[n-1][tmp] = Lcd_Pixel[i];
//    //��ɫ
//    LCD_SetPos(tmp,tmp,239 - ImageLine[n-1][tmp],239 -ImageLine[n-1][tmp]);
//    write_word(color);
//    
//    tmp++;
//    //��ԭ
//    LCD_SetPos(tmp,tmp,239 - ImageLine[n-1][tmp],239 - ImageLine[n-1][tmp]);
//    write_word(Yellow);
//    if(Lcd_Pixel[i] > 235)
//      ImageLine[n-1][tmp] = 235;
//    else
//      ImageLine[n-1][tmp] = Lcd_Pixel[i];
//    //��ɫ
//    LCD_SetPos(tmp,tmp,239 - ImageLine[n-1][tmp],239 -ImageLine[n-1][tmp]);
//    write_word(color);
//  }
//}
/************************************************
*  �������ƣ�Parameters_On_LCD
*  ����˵��������ʾ������ʾ�ؼ�����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2014-8-4    
*************************************************/
char cUart0_temp[20] = "UART0 is E!";
char cUart2_temp[20] = "UART2 is E!";
char cUart5_temp[20] = "UART5 is E!";
//void Parameters_On_LCD(unsigned char n )
//{
//  int x=0,y=0;
//  char t=16;
//  cUart0_temp[9] = cUart2_temp[9] = cUart5_temp[9] = 'E';
//  LCD_Put_Float(x , y , "1.SW:" , ElementMode , Red , Green);             y=y+t;
//  LCD_Put_Float(x , y , "2.AdNum1:" , AdNum1 , Red , Green);              y=y+t; 
//  LCD_Put_Float(x , y , "3.AdNum2:" , AdNum2 , Red , Green);              y=y+t;
//  LCD_Put_Float(x , y , "4.AdNum3:" , AdNum3 , Red , Green);              y=y+t;
//  LCD_Put_Float(x , y , "5.AdNum4:" , AdNum4 , Red , Green);              y=y+t;
//  LCD_Put_Float(x , y , "6.AdVresNum:" , AdVresNum , Red , Green);        y=y+t;
//  LCD_Put_Float(x , y , "7.AdBatNum:" , AdBatNum , Red , Green);          y=y+t;
//  LCD_Put_Float(x , y , "8.AD_QNum:" , AD_QNum , Red , Green);          y=y+t;
//  LCD_Put_Float(x , y , "9.m_angle:" , Angle.m_angle , Red , Green);          y=y+t;
//  LCD_Put_Float(x , y , "10.Gyro:" , Angle.Gyro , Red , Green);          y=y+t;
//  LCD_Put_Float(x , y , "11.Speed.:" , Speed.L_5ms , Red , Green);          y=y+t;
//  x= 150;
//  y = 0 ;
//  LCD_Put_Int(x , y , cUart0_temp , 0, Red , Green);          y=y+t;
//  LCD_Put_Int(x , y , cUart2_temp , 0, Red , Green);          y=y+t;
//  LCD_Put_Int(x , y , cUart5_temp , 0, Red , Green);          y=y+t;
//  
//}
/************************************************
*  �������ƣ�void Print_runway()
*  ����˵��������ʾ������ʾ�����ͳ�������ͼ��
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2014-12-15    �Ѿ�����
*************************************************/
//void Print_runway(unsigned char CCD)
//{  
//  static unsigned char lcd_black_centre_0ld=0, lcd_black_centre_0ld_0ld=0;
//  static unsigned char lcd_black_R_0ld=0, lcd_black_R_0ld_0ld=0; 
//  static unsigned char lcd_black_L_0ld=0, lcd_black_L_0ld_0ld=0; 
//  switch(CCD)
//  {
//  case 1:
//    if(lcd_black_R_0ld != Image1.black_R[0] )
//    {
//      Draw_single_line('L',2*lcd_black_R_0ld_0ld,Yellow);//������ұ�
//      Draw_single_line('L',2*lcd_black_R_0ld,Red);//�����ұ�
//      lcd_black_R_0ld_0ld = lcd_black_R_0ld;
//      lcd_black_R_0ld = Image1.black_R[0];
//    } 
//    if(lcd_black_L_0ld != Image1.black_L[0])
//    {
//      Draw_single_line('L',2*lcd_black_L_0ld_0ld,Yellow);//��������
//      Draw_single_line('L',2*lcd_black_L_0ld,Red);//�������
//      lcd_black_L_0ld_0ld = lcd_black_L_0ld;
//      lcd_black_L_0ld = Image1.black_L[0];
//    } 
//    break;
//  case 2:if(lcd_black_centre_0ld != Image2.RoadCenter[0])
//  {
//    Draw_single_line('L',2*lcd_black_centre_0ld_0ld,Yellow);//�����������
//    Draw_single_line('L',2*lcd_black_centre_0ld,White);//����������
//    lcd_black_centre_0ld_0ld=lcd_black_centre_0ld;
//    lcd_black_centre_0ld = Image2.RoadCenter[0];
//  } 
//  if(lcd_black_R_0ld != Image2.black_R[0] )
//  {
//    Draw_single_line('L',2*lcd_black_R_0ld_0ld,Yellow);//������ұ�
//    Draw_single_line('L',2*lcd_black_R_0ld,Red);//�����ұ�
//    lcd_black_R_0ld_0ld = lcd_black_R_0ld;
//    lcd_black_R_0ld = Image2.black_R[0];
//  } 
//  if(lcd_black_L_0ld != Image2.black_L[0])
//  {
//    Draw_single_line('L',2*lcd_black_L_0ld_0ld,Yellow);//��������
//    Draw_single_line('L',2*lcd_black_L_0ld,Red);//�������
//    lcd_black_L_0ld_0ld = lcd_black_L_0ld;
//    lcd_black_L_0ld = Image2.black_L[0];
//  } 
//  break;
//  case 3:if(lcd_black_centre_0ld != Image3.RoadCenter[0])
//  {
//    Draw_single_line('L',2*lcd_black_centre_0ld_0ld,Yellow);//�����������
//    Draw_single_line('L',2*lcd_black_centre_0ld,White);//����������
//    lcd_black_centre_0ld_0ld=lcd_black_centre_0ld;
//    lcd_black_centre_0ld = Image3.RoadCenter[0];
//  } 
//  if(lcd_black_R_0ld != Image3.black_R[0] )
//  {
//    Draw_single_line('L',2*lcd_black_R_0ld_0ld,Yellow);//������ұ�
//    Draw_single_line('L',2*lcd_black_R_0ld,Red);//�����ұ�
//    lcd_black_R_0ld_0ld = lcd_black_R_0ld;
//    lcd_black_R_0ld = Image3.black_R[0];
//  } 
//  if(lcd_black_L_0ld != Image3.black_L[0])
//  {
//    Draw_single_line('L',2*lcd_black_L_0ld_0ld,Yellow);//��������
//    Draw_single_line('L',2*lcd_black_L_0ld,Red);//�������
//    lcd_black_L_0ld_0ld = lcd_black_L_0ld;
//    lcd_black_L_0ld = Image3.black_L[0];
//  } 
//  break;
//  }  
//  Draw_single_line('L',0,Black);//��߽�
//  Draw_single_line('L',128,Black);//����������
//  Draw_single_line('L',256,Black);//�ұ߽�
//  
//  LCD_Put_Unsigned_Int(0 , 225 , "0" , 0,Black , Yellow);//����������
//  LCD_Put_Unsigned_Int(56 , 225 , "3" , 2,Black , Yellow);
//  LCD_Put_Unsigned_Int(120 , 225 , "6" , 4,Black , Yellow);
//  LCD_Put_Unsigned_Int(184 , 225 , "9" , 6,Black , Yellow);
//  LCD_Put_Unsigned_Int(232 , 225 , "1" , 28,Black , Yellow);
//  
//  Draw_single_line('H',240-Image2.WHITE_BLACK_DIVIDE,Black);//��ֵ��ʾ
//  Draw_line(100,Yellow);
//  Draw_line(Image1.WHITE_BLACK_ERROR,Red);  
//}

/*************************************************************************
*  �������ƣ�Send_Image_to_LCD
*  ����˵��������ʾ������ʾӥ��ͼ��
*  ����˵����imgΪָ��
*  �������أ���
*  �޸�ʱ�䣺2012-2-14    �Ѳ���
*************************************************************************/
void Send_Image_to_LCD(unsigned char img[CAMERA_H][CAMERA_DMA_NUM])
{
  int i,j,k;
  LCD_SetPos(0,319,0,239);
  for(i=0;i < CAMERA_H ;i++)
  {
    for(j = 0;j < CAMERA_DMA_NUM; j++)
      for(k = 0;k < 8; k++)
        if(img[i][j]&(0x80>>k))              
          write_word(Black);	//дͼ������
        else
          write_word(White);		//дͼ������     
  }
}
#define Ypoint 185
void ShowStart(void)
{
  char cNextPoint = 0;
  Print_child();  
  
  cNextPoint = 45;
  PutGB3232(cNextPoint,Ypoint, "��", Black,Yellow);
  cNextPoint +=32;
  PutGB3232(cNextPoint,Ypoint, "��", Black,Yellow);
    cNextPoint +=32;
  PutGB3232(cNextPoint,Ypoint, "��", Black,Yellow);
    cNextPoint +=32;
  PutGB3232(cNextPoint,Ypoint, "��", Black,Yellow);
    cNextPoint +=32;
  PutGB3232(cNextPoint,Ypoint, "��", Black,Yellow);
    cNextPoint +=32;
  PutGB3232(cNextPoint,Ypoint, "ƽ", Black,Yellow);
    cNextPoint +=32;
  PutGB3232(cNextPoint,Ypoint, "̨", Black,Yellow);
  

}

//void number_input(u8 xx,u8 yy,u16* number)
//{
//  u16 result=*number;
//  u8 strtemp[15];
//  signed char num_temp[5]={0};
//  signed char i=0;
//  u8 j;
//  u8 Key=0;
//  LCD_PutString(xx,yy,"in num",Black,White);
//  while(1)
//  {
//    Key=KEY_Scan();
//    if(Key==KEY0_PRES)//ȷ�����
//    {
//      *number=num_temp[0]+num_temp[1]*10+num_temp[2]*100+num_temp[3]*1000+num_temp[4]*10000;
//      break;
//    }
//    else if(Key==KEY1_PRES)//�����޸�
//    {
//      *number=result;
//      break;
//    }
//    else if(Key==KEY_UP_PRES)
//    {
//      num_temp[i]++;
//      for(j=0;j<5;j++)
//      {
//        if(num_temp[j]==10)//��λ
//        {
//          num_temp[j]=0;
//          if((j+1)<5)
//          num_temp[j+1]++;
//        }
//      }
//    }
//    else if(Key==KEY_DOWM_PRES)
//    {
//      num_temp[i]--;
//      for(j=0;j<5;j++)
//      {
//        if(num_temp[j]==-1)//��λ
//        {
//          num_temp[j]=9;
//          if((j+1)<5)
//          num_temp[j+1]--;
//        }
//      }
//    }
//    else if(Key==KEY_LEFT_PRES)
//    {
//      i++;
//      if(i>4)
//      {
//        i=4;
//      }
//      Brush_Color=White;
//      LCD_Draw_Line(xx,yy+33,xx+80,yy+33);
//      Brush_Color=Black;
//      LCD_Draw_Line(xx+80-(2*i+2)*8,yy+33,xx+80-(2*i+1)*8,yy+33);
//    }
//    else if(Key==KEY_RIGHT_PRES)
//    {
//      i--;
//      if(i<0)
//      {
//        i=0;
//      }
//      Brush_Color=White;
//      LCD_Draw_Line(xx,yy+33,xx+80,yy+33);
//      Brush_Color=Black;
//      LCD_Draw_Line(xx+80-(2*i+2)*8,yy+33,xx+80-(2*i+1)*8,yy+33);
//    }
//    sprintf(strtemp,"%d %d %d %d %d",num_temp[4],num_temp[3],num_temp[2],num_temp[1],num_temp[0]);
//    LCD_PutString(xx,yy+16,strtemp,Black,White);
//  }
//}

void LCD_Draw_Line(u16 x1, u16 y1, u16 x2, u16 y2)
{
  u16 i; 
  int xm1=0,ym2=0,model_x,model_y,model,  mcx,mcy,mRow,mCol;  

  model_x=x2-x1;                 
  model_y=y2-y1; 
  mRow=x1; 
  mCol=y1; 
  if(model_x>0)mcx=1;       
  else if(model_x==0)mcx=0;      
  else {mcx=-1;model_x=-model_x;} 
  if(model_y>0)mcy=1; 
  else if(model_y==0)mcy=0;    
  else{mcy=-1;model_y=-model_y;} 
  if( model_x>model_y)model=model_x;  
  else model=model_y; 
  for(i=0;i<=model+1;i++ )     
  {  
    LCD_DrawPoint(mRow,mCol);     
    xm1+=model_x ; 
    ym2+=model_y ; 
    if(xm1>model) 
    { 
      xm1-=model; 
      mRow+=mcx; 
    } 
    if(ym2>model) 
    { 
      ym2-=model; 
      mCol+=mcy; 
    } 
  }  
}

void LCD_DrawPoint(u16 x,u16 y)
{
  LCD_SetPos(x,x,y,y);		  
//  LCD_WriteRAM_Prepare();	 
  write_word(Red);
}
