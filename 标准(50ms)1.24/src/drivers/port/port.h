/******************** (C) COPYRIGHT 2011 Ұ��Ƕ��ʽ���������� ********************
 * �ļ���       ��port.h
 * ����         ���ⲿ�жϺ�������ͷ�ļ�
 *
 * ʵ��ƽ̨     ��Ұ��kinetis������
 * ��汾       ��
 * Ƕ��ϵͳ     ��
 *
 * ����         ��Ұ��Ƕ��ʽ����������
 * �Ա���       ��http://firestm32.taobao.com
 * ����֧����̳ ��http://www.ourdev.cn/bbs/bbs_list.jsp?bbs_id=1008
**********************************************************************************/

#ifndef _PORT_H_
#define _PORT_H_

typedef enum 
{
    
    
    //�жϷ�ʽѡ��
    IRQ_ZERO     = 0x08<<16,     //�͵�ƽ����
    IRQ_RISING   = 0x09<<16,     //�����ش���
    IRQ_FALLING  = 0x0A<<16,     //�½��ش���
    IRQ_EITHER   = 0x0B<<16,     //�����ش���
    IRQ_ONE      = 0x0C<<16,     //�ߵ�ƽ����
    
    //DMA��ʽ
    DMA_RISING   = 0x01<<16,     //�����ش���
    DMA_FALLING  = 0x02<<16,     //�½��ش���
    DMA_EITHER   = 0x03<<16,     //�����ش���
    
    HDS          = 0x01<<6,      //�������������
    ODO          = 0x01<<5,      //©�����
    PF           = 0x01<<4,      //����Դ�˲���
    SSR          = 0x01<<2,      //������仯��          Slow slew rate
    
    //��������ѡ��
    PULLDOWN     = 0x02<<0,        //����
    PULLUP       = 0x03<<0,        //����
        //���ܸ���ѡ��(�������Ҫ�ı书�ܸ���ѡ�񣬱���ԭ�ȵĹ��ܸ��ã�ֱ��ѡ��ALT0 )
    //��Ҫ�� K60 Signal Multiplexing and Pin Assignments
    ALT0         = 0x00 << PORT_PCR_MUX_SHIFT,
    ALT1         = 0x01 << PORT_PCR_MUX_SHIFT,    //GPIO
    ALT2         = 0x02 << PORT_PCR_MUX_SHIFT,
    ALT3         = 0x03 << PORT_PCR_MUX_SHIFT,
    ALT4         = 0x04 << PORT_PCR_MUX_SHIFT,
    ALT5         = 0x05 << PORT_PCR_MUX_SHIFT,
    ALT6         = 0x06 << PORT_PCR_MUX_SHIFT,
    ALT7         = 0x07 << PORT_PCR_MUX_SHIFT,
    
}port_cfg;

    
void  port_initMUX(PTxn ptxn, u32 cfg );
void  port_init(PTxn ptxn, u32 cfg );
void  port_init_NoALT(PTxn ptxn, uint32 cfg);


#endif
