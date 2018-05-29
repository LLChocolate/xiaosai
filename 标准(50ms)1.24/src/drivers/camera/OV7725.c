#include "define.h"
#include "common.h"
#include "gpio.h"
#include "port.h"
#include "dma.h"
#include "SCCB.h"
#include "OV7725.h"
#include "OV7725_REG.h"
#include "include.h"

u8 Memory_use_Flag=1;
u8 Image_fire_Memory1[CAMERA_H+1][CAMERA_DMA_NUM]={{0}};
u8 Image_fire_Memory2[CAMERA_H+1][CAMERA_DMA_NUM]={{0}};
u8 (*Image_fire)[CAMERA_DMA_NUM];//ָ��
//u8 Image_fire_extract[CAMERA_H+1][CAMERA_W]={{0}};


volatile u8 img_flag = IMG_FINISH;		//ͼ��״̬



void Ov7725_exti_Init()
{
    //FIFO�˿ڳ�ʼ��  PC8~15
    gpio_init(PORTC,8, GPI, HIGH);
    gpio_init(PORTC,9, GPI, HIGH);
    gpio_init(PORTC,10, GPI, HIGH);
    gpio_init(PORTC,11, GPI, HIGH);
    gpio_init(PORTC,12, GPI, HIGH);
    gpio_init(PORTC,13, GPI, HIGH);
    gpio_init(PORTC,14, GPI, HIGH);
    gpio_init(PORTC,15, GPI, HIGH);
    //DMAͨ��0��ʼ����PTB22�½��ش���DMA���䣬Դ��ַΪPTC_BYTE1_IN��Ŀ�ĵ�ַΪ��Image_fire ��ÿ�δ���1Byte������CAMERA_SIZE�κ�ֹͣ����
    DMA_PORTx2BUFF_Init(CAMERA_DMA_CH, (void *)&PTC_BYTE1_IN, (void *)(Image_fire_Memory1), PTB22, DMA_BYTE1, CAMERA_SIZE , DMA_falling);//KEEPON,DMA_falling
    Image_fire=&Image_fire_Memory1[0];
    DMA_DIS(CAMERA_DMA_CH); 
	
    DMA_IRQ_CLEAN(CAMERA_DMA_CH);
    DMA_IRQ_EN(CAMERA_DMA_CH);
    port_init(PTB22,DMA_FALLING | PULLUP );    //PCLK
    port_init(PTD2, IRQ_FALLING| PULLUP | PF);    //���жϣ��������½��ش����жϣ����˲�
    disable_irq(90);						//�ر�PTD���ж�
}

void ov7725_get_img()
{
    img_flag = IMG_START;		//��ʼ�ɼ�ͼ��
    PORTD_ISFR=~0;			//д1���жϱ�־λ(����ģ���Ȼ�ص���һ���жϾ����ϴ����ж�)
    enable_irq(90); 			//����PTD���ж�
//    while(img_flag != IMG_FINISH)       //�ȴ�ͼ��ɼ����
//    {
//        if(img_flag == IMG_FAIL)        //����ͼ��ɼ����������¿�ʼ�ɼ�
//        {
//            Image_Flag=0;
//            img_flag = IMG_START;	//��ʼ�ɼ�ͼ��
//            PORTD_ISFR=~0;		//д1���жϱ�־λ(����ģ���Ȼ�ص���һ���жϾ����ϴ����ж�)
//            enable_irq(90); 		//����PTD���ж�
//        }
//    }
//    Image_Flag=1;
}


/*OV7725��ʼ�����ñ�*/
Register_Info ov7727_reg[] =
{
    //�Ĵ������Ĵ���ֵ��
    {COM4         ,0xC1},//PLL 8x  
    {CLKRC        ,0x00},//ʹ���ڲ�ʱ��
    {COM2         ,0x03},//�����������
    {COM3         ,0xD0},//��ֱ��תͼ��ѡ�� ˮƽ����ͼ��ѡ�� ת��YUV���˳����ɫ���뷽ʽ��
    {COM7         ,0x40},//QVGA���ֱ���320*240��
    {HSTART       ,0x3F},//QVGA
    {HSIZE        ,0x50},//QVGA
    {VSTRT        ,0x03},//QVGA
    {VSIZE        ,0x78},//QVGA
    {HREF         ,0x00},//Ĭ��ֵ��������
    {SCAL0        ,0x0A},//����ͨ��д�����ʿ��ƣ�1/4��ֱ��ȡ����1/4ˮƽ��ȡ����
    {AWB_Ctrl0    ,0xE0},//��ƽ�����治ʹ�� ����ʹ��
    {DSPAuto      ,0xff},//��ƽ���Զ�����
    {DSP_Ctrl2    ,0x0C},
    {DSP_Ctrl3    ,0x00},
    {DSP_Ctrl4    ,0x00},
    
#if (CAMERA_W == 80)
{HOutSize     ,0x14},
#elif (CAMERA_W == 160)  
{HOutSize     ,0x28},
#elif (CAMERA_W == 240)  
{HOutSize     ,0x3c},
#elif (CAMERA_W == 320)  
{HOutSize     ,0x50}, 
#else

#endif

#if (CAMERA_H == 60 )
{VOutSize     ,0x1E},
#elif (CAMERA_H == 120 )
{VOutSize     ,0x3c},
#elif (CAMERA_H == 180 )
{VOutSize     ,0x5a},
#elif (CAMERA_H == 240 )
{VOutSize     ,0x78},
#else

#endif 

{EXHCH        ,0x00},
{GAM1         ,0x0c},
{GAM2         ,0x16},
{GAM3         ,0x2a},
{GAM4         ,0x4e},
{GAM5         ,0x61},
{GAM6         ,0x6f},
{GAM7         ,0x7b},
{GAM8         ,0x86},
{GAM9         ,0x8e},
{GAM10        ,0x97},
{GAM11        ,0xa4},
{GAM12        ,0xaf},
{GAM13        ,0xc5},
{GAM14        ,0xd7},
{GAM15        ,0xe8},
{SLOP         ,0x20},
{LC_RADI      ,0x00},
{LC_COEF      ,0x13},
{LC_XC        ,0x08},
{LC_COEFB     ,0x14},
{LC_COEFR     ,0x17},
{LC_CTR       ,0x05},
{BDBase       ,0x99},
{BDMStep      ,0x03},
{SDE          ,0x04},
{BRIGHT       ,0x00},                              
{CNST         ,70},//150:¥��¥�¶����ܣ���һ�����ȣ�70
{SIGN         ,0x06},
{UVADJ0       ,0x11},
{UVADJ1       ,0x02},
};

u8 cfgnum = sizeof(ov7727_reg)/sizeof(ov7727_reg[0]);   /*�ṹ�������Ա��Ŀ*/



/************************************************
* ��������Ov7725_Init
* ����  ��Sensor��ʼ��
* ����  ����
* ���  ������1�ɹ�������0ʧ��
* ע��  ����
************************************************/
u8 Ov7725_Init()
{
    while(Ov7725_reg_Init() == 0);
    Ov7725_exti_Init();
    return 0;
}

/************************************************
* ��������Ov7725_reg_Init
* ����  ��Sensor �Ĵ��� ��ʼ��
* ����  ����
* ���  ������1�ɹ�������0ʧ��
* ע��  ����
************************************************/
u8 Ov7725_reg_Init(void)
{
    u16 i = 0;
    u8 Sensor_IDCode = 0;
    SCCB_GPIO_init();
    OV7725_Delay_ms(50);
    while( 0 == SCCB_WriteByte ( 0x12, 0x80 ) ) /*��λsensor */
    {
        i++;
        if(i == 20)
        {
            printf("����:SCCBд���ݴ���");
            //OV7725_Delay_ms(50);
            return 0 ;
        }
    }
    OV7725_Delay_ms(50);
    if( 0 == SCCB_ReadByte( &Sensor_IDCode, 1, 0x0b ) )	 /* ��ȡsensor ID��*/
    {
        printf("����:��ȡIDʧ��");
        return 0;
    }
    printf("Get ID success��SENSOR ID is 0x%x", Sensor_IDCode);
    printf("Config Register Number is %d ", cfgnum);
    if(Sensor_IDCode == OV7725_ID)
    {
        for( i = 0 ; i < cfgnum ; i++ )
        {
            if( 0 == SCCB_WriteByte(ov7727_reg[i].Address, ov7727_reg[i].Value) )
            {
                printf("����:д�Ĵ���0x%xʧ��", ov7727_reg[i].Address);
                return 0;
            }
        }
    }
    else
    {
        return 0;
    }
    printf("OV7725 Register Config Success!");
    return 1;
}
//******************************************************************ͼ���ѹ
void img_extract(u8 Fire[][CAMERA_DMA_NUM],u8 Extract[][CAMERA_W])//ֻ��ѹһ��
{
  u16 i,j;
  u8 k;
  i=Start_Point;
  for(j = 0;j < CAMERA_DMA_NUM; j++)
  {
    for(k = 0;k < 8; k++)
    {
      Extract[i][j*8+k]=(Fire[i][j]>>(7-k))&1;
    }
  }

}
