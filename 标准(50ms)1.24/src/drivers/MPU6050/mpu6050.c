#include "mpu6050.h"

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK��ӢSTM32������V3
//MPU6050 ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2015/1/17
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
 
//��ʼ��MPU6050
//����ֵ:0,�ɹ�
//    ����,�������
u8 MPU_Init(void)
{ 
	u8 res;
	
	MPU_IIC_Init();//��ʼ��IIC����
	MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X80);	//��λMPU6050
        delayms(100);
	MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X00);	//����MPU6050 
	MPU_Set_Gyro_Fsr(3);					//�����Ǵ�����,��2000dps
	MPU_Set_Accel_Fsr(0);					//���ٶȴ�����,��2g
	MPU_Set_Rate(50);						//���ò�����50Hz
	MPU_Write_Byte(MPU_INT_EN_REG,0X00);	//�ر������ж�
	MPU_Write_Byte(MPU_USER_CTRL_REG,0X00);	//I2C��ģʽ�ر�
	MPU_Write_Byte(MPU_FIFO_EN_REG,0X00);	//�ر�FIFO
	MPU_Write_Byte(MPU_INTBP_CFG_REG,0X80);	//INT���ŵ͵�ƽ��Ч
	res=MPU_Read_Byte(MPU_DEVICE_ID_REG);
	if(res==MPU_ADDR)//����ID��ȷ  MPU_ADDR
	{
		MPU_Write_Byte(MPU_PWR_MGMT1_REG,0X01);	//����CLKSEL,PLL X��Ϊ�ο�
		MPU_Write_Byte(MPU_PWR_MGMT2_REG,0X00);	//���ٶ��������Ƕ�����
		MPU_Set_Rate(50);						//���ò�����Ϊ50Hz
 	}else return 1;
	return 0;
}
//����MPU6050�����Ǵ����������̷�Χ
//fsr:0,��250dps;1,��500dps;2,��1000dps;3,��2000dps
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
u8 MPU_Set_Gyro_Fsr(u8 fsr)
{
	return MPU_Write_Byte(MPU_GYRO_CFG_REG,fsr<<3);//���������������̷�Χ  
}
//����MPU6050���ٶȴ����������̷�Χ
//fsr:0,��2g;1,��4g;2,��8g;3,��16g
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
u8 MPU_Set_Accel_Fsr(u8 fsr)
{
	return MPU_Write_Byte(MPU_ACCEL_CFG_REG,fsr<<3);//���ü��ٶȴ����������̷�Χ  
}
//����MPU6050�����ֵ�ͨ�˲���
//lpf:���ֵ�ͨ�˲�Ƶ��(Hz)
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
u8 MPU_Set_LPF(u16 lpf)
{
	u8 data=0;
	if(lpf>=188)data=1;
	else if(lpf>=98)data=2;
	else if(lpf>=42)data=3;
	else if(lpf>=20)data=4;
	else if(lpf>=10)data=5;
	else data=6; 
	return MPU_Write_Byte(MPU_CFG_REG,data);//�������ֵ�ͨ�˲���  
}
//����MPU6050�Ĳ�����(�ٶ�Fs=1KHz)
//rate:4~1000(Hz)
//����ֵ:0,���óɹ�
//    ����,����ʧ�� 
u8 MPU_Set_Rate(u16 rate)
{
	u8 data;
	if(rate>1000)rate=1000;
	if(rate<4)rate=4;
	data=1000/rate-1;
	data=MPU_Write_Byte(MPU_SAMPLE_RATE_REG,data);	//�������ֵ�ͨ�˲���
 	return MPU_Set_LPF(rate/2);	//�Զ�����LPFΪ�����ʵ�һ��
}

//�õ��¶�ֵ
//����ֵ:�¶�ֵ(������100��)
short MPU_Get_Temperature(void)
{
    u8 buf[2]; 
    short raw;
	float temp;
	MPU_Read_Len(MPU_ADDR,MPU_TEMP_OUTH_REG,2,buf); 
    raw=((u16)buf[0]<<8)|buf[1];  
    temp=36.53+((double)raw)/340;  
    return temp*100;;
}
//�õ�������ֵ(ԭʼֵ)
//gx,gy,gz:������x,y,z���ԭʼ����(������)
//����ֵ:0,�ɹ�
//    ����,�������
u8 MPU_Get_Gyroscope(short *gx,short *gy,short *gz)
{
    u8 buf[6],res;  
	res=MPU_Read_Len(MPU_ADDR,MPU_GYRO_XOUTH_REG,6,buf);
	if(res==0)
	{
		*gx=((u16)buf[0]<<8)|buf[1];  
		*gy=((u16)buf[2]<<8)|buf[3];  
		*gz=((u16)buf[4]<<8)|buf[5];
	} 	
    return res;;
}
//�õ����ٶ�ֵ(ԭʼֵ)
//gx,gy,gz:������x,y,z���ԭʼ����(������)
//����ֵ:0,�ɹ�
//    ����,�������
u8 MPU_Get_Accelerometer(short *ax,short *ay,short *az)
{
    u8 buf[6],res;  
	res=MPU_Read_Len(MPU_ADDR,MPU_ACCEL_XOUTH_REG,6,buf);
	if(res==0)
	{
		*ax=((u16)buf[0]<<8)|buf[1];  
		*ay=((u16)buf[2]<<8)|buf[3];  
		*az=((u16)buf[4]<<8)|buf[5];
	} 	
    return res;;
}
//IIC����д
//addr:������ַ 
//reg:�Ĵ�����ַ
//len:д�볤��
//buf:������
//����ֵ:0,����
//    ����,�������
u8 MPU_Write_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{
	u8 i; 
    MPU_IIC_Start(); 
	MPU_IIC_Send_Byte((addr<<1)|0);//����������ַ+д����	
	if(MPU_IIC_Wait_Ack())	//�ȴ�Ӧ��
	{
		MPU_IIC_Stop();		 
		return 1;		
	}
    MPU_IIC_Send_Byte(reg);	//д�Ĵ�����ַ
    MPU_IIC_Wait_Ack();		//�ȴ�Ӧ��
	for(i=0;i<len;i++)
	{
		MPU_IIC_Send_Byte(buf[i]);	//��������
		if(MPU_IIC_Wait_Ack())		//�ȴ�ACK
		{
			MPU_IIC_Stop();	 
			return 1;		 
		}		
	}    
    MPU_IIC_Stop();	 
	return 0;	
} 
//IIC������
//addr:������ַ
//reg:Ҫ��ȡ�ļĴ�����ַ
//len:Ҫ��ȡ�ĳ���
//buf:��ȡ�������ݴ洢��
//����ֵ:0,����
//    ����,�������
u8 MPU_Read_Len(u8 addr,u8 reg,u8 len,u8 *buf)
{ 
 	MPU_IIC_Start(); 
	MPU_IIC_Send_Byte((addr<<1)|0);//����������ַ+д����	
	if(MPU_IIC_Wait_Ack())	//�ȴ�Ӧ��
	{
		MPU_IIC_Stop();		 
		return 1;		
	}
    MPU_IIC_Send_Byte(reg);	//д�Ĵ�����ַ
    MPU_IIC_Wait_Ack();		//�ȴ�Ӧ��
    MPU_IIC_Start();
	MPU_IIC_Send_Byte((addr<<1)|1);//����������ַ+������	
    MPU_IIC_Wait_Ack();		//�ȴ�Ӧ�� 
	while(len)
	{
		if(len==1)*buf=MPU_IIC_Read_Byte(0);//������,����nACK 
		else *buf=MPU_IIC_Read_Byte(1);		//������,����ACK  
		len--;
		buf++; 
	}    
    MPU_IIC_Stop();	//����һ��ֹͣ���� 
	return 0;	
}
//IICдһ���ֽ� 
//reg:�Ĵ�����ַ
//data:����
//����ֵ:0,����
//    ����,�������
u8 MPU_Write_Byte(u8 reg,u8 data) 				 
{ 
    MPU_IIC_Start(); 
	MPU_IIC_Send_Byte((MPU_ADDR<<1)|0);//����������ַ+д����	
	if(MPU_IIC_Wait_Ack())	//�ȴ�Ӧ��
	{
		MPU_IIC_Stop();		 
		return 1;		
	}
    MPU_IIC_Send_Byte(reg);	//д�Ĵ�����ַ
    MPU_IIC_Wait_Ack();		//�ȴ�Ӧ�� 
	MPU_IIC_Send_Byte(data);//��������
	if(MPU_IIC_Wait_Ack())	//�ȴ�ACK
	{
		MPU_IIC_Stop();	 
		return 1;		 
	}		 
    MPU_IIC_Stop();	 
	return 0;
}
//IIC��һ���ֽ� 
//reg:�Ĵ�����ַ 
//����ֵ:����������
u8 MPU_Read_Byte(u8 reg)
{
	u8 res;
    MPU_IIC_Start(); 
	MPU_IIC_Send_Byte((MPU_ADDR<<1)|0);//����������ַ+д����	
	MPU_IIC_Wait_Ack();		//�ȴ�Ӧ�� 
    MPU_IIC_Send_Byte(reg);	//д�Ĵ�����ַ
    MPU_IIC_Wait_Ack();		//�ȴ�Ӧ��
    MPU_IIC_Start();
	MPU_IIC_Send_Byte((MPU_ADDR<<1)|1);//����������ַ+������	
    MPU_IIC_Wait_Ack();		//�ȴ�Ӧ�� 
	res=MPU_IIC_Read_Byte(0);//��ȡ����,����nACK 
    MPU_IIC_Stop();			//����һ��ֹͣ���� 
	return res;		
}

void mix_gyrAcc_crossMethod(float * attitude,short gyr[3],short acc[3])
{
const static float FACTOR = 0.001;//��������ʸ����������˵�ϵ��p�����ں������ǻ��ֽǶ�����������������ǣ�����ֻ���˱���p��û�û���i����
//FACTOR Ϊ1������ȫ���μ��ٶȼƣ�Ϊ0������ȫ����������
float w_q = attitude[0];//w=cos(alpha/2)
float x_q = attitude[1];//x=ax*sin(alpha/2)
float y_q = attitude[2];//y=ay*sin(alpha/2)
float z_q = attitude[3];//z=az*sin(alpha/2)
float x_q_2 = x_q * 2;
float y_q_2 = y_q * 2;
float z_q_2 = z_q * 2;
//
// ���ٶȼƵĶ�������λ����
float norm = sqrt((acc[0]*acc[0]+acc[1]*acc[1]+acc[2]*acc[2])*1.0);
float x_aa = acc[0]*1.0 * norm;
float y_aa = acc[1]*1.0 * norm;
float z_aa = acc[2]*1.0 * norm;
//
// ���������µ��������ٶȳ�������λ����//����ת������������ϵ�ĵ�λ������ʸ��(0,0,1�����ǣ�0,0��-1��,mpu6050 ֻ��Ӧ���������ٶ�)ת������������ϵ�С�
//���������µ�����ʸ����ת��������ϵת������������Ҳ����ת�þ�����Ϊŷ���ǽ�õ���ת������������� ���������µ�����ʸ��
// x cos(T)cos(K) cos(T)sin(C) -sin(C) 0
// [ y ] = [ sin(F)sin(T)cos(K)-cos(F)sin(K) sin(F)sin(T)sin(K)+cos(F)cos(K) sin(F)cos(T) ] * [ 0 ]
// z cos(F)sin(T)cos(K)+sin(F)sin(K) cos(F)sin(T)sin(K)-sin(F)cos(K) cos(F)cos(T) 1
//K ��yaw,T ��pitch,F ��roll,��ת˳��ΪZYX
// w^2+x^2-y^2-z^2 2*(x*y+w*z) 2*(x*z-w*y)
//��ʽ�е���ת��������Ԫ����ʾ��Ϊ��[ 2*(x*y-w*z) w^2-x^2+y^2-z^2 2*(y*z+w*x) ]
// 2*(x*z+w*y) 2*��y*z-w*x�� w^2-x^2-y^2+z^2
//
float x_ac = x_q*z_q_2 - w_q*y_q_2;// 2*(x*z-w*y) =ax*az(1-cos(alpha))-ay*sin(alpha)
float y_ac = y_q*z_q_2 + w_q*x_q_2;// 2*(y*z+w*x) =az*ay(1-cos(alpha))+ax*sin(alpha)
float z_ac = 1 - x_q*x_q_2 - y_q*y_q_2;// w^2+x^2-y^2-z^2 =1-2*x^2-2*y^2 = cos(alpha)+(1-cos(alpha)*z^2)
//
// ����ֵ�볣���Ĳ����//����ֵ��˳���ֵ,���Դ�������ʾ���Ƕȴ�С��ת�᷽���������������ǻ��ֽǶ�
float x_ca = y_aa * z_ac - z_aa * y_ac;
float y_ca = z_aa * x_ac - x_aa * z_ac;
float z_ca = x_aa * y_ac - y_aa * x_ac;
//
// ����������ת��//�ɿ��ɷֱ���xyz ���������ת�ĵ��ӡ�sin(delta/2)����Ϊdelta/2,cos(delta/2)����Ϊ0
float delta_x = gyr[0]*1.0 * halfT + x_ca * FACTOR;//��x ����ת�Ƕȵ�һ�룬��d_x ������x ���һ����ת��w=1,x=d_x,y=0,z=0
float delta_y = gyr[1]*1.0 * halfT + y_ca * FACTOR;//��y ����ת�Ƕȵ�һ�룬��d_y ������y ���һ����ת��w=1,x=0,y=d_y,z=0
float delta_z = gyr[2]*1.0 * halfT + z_ca * FACTOR;//��z ����ת�Ƕȵ�һ�룬��d_z ������z ���һ����ת��w=1,x=0,y=0,z=d_z
//������ת����Ϊһ����ת����������Ԫ�����
//��Ԫ���˷���ʽ��q3=q1*q2
//(w1*w2 - x1*x2 - y1*y2 - z1*z2) = w3
//(w1*x2 + x1*w2 + y1*z2 - z1*y2) = x3
//(w1*y2 - x1*z2 + y1*w2 + z1*x2) = y3
//(w1*z2 + x1*y2 - y1*x2 + z1*w2) = z3
//�ϳɵ�һ����ת��
// w=1 - d_x*d_y*d_z(���С�Ƕ���ˣ����ԣ���ͬ) =1
// x=d_x + d_y*d_z�����ԣ� =d_x
// y=d_y - d_x*d_z�����ԣ� =d_y
// z=d_z + d_x*d_y�����ԣ� =d_z
//
// �ںϣ���Ԫ���˷���//������ϳɵ���ת��Ԫ����֮ǰ����̬��Ԫ����ˣ��õ��µ���̬��Ԫ������һ��Ϊ��λ��Ԫ����
attitude[0] = w_q - x_q*delta_x - y_q*delta_y - z_q*delta_z;
attitude[1] = w_q*delta_x + x_q + y_q*delta_z - z_q*delta_y;
attitude[2] = w_q*delta_y - x_q*delta_z + y_q + z_q*delta_x;
attitude[3] = w_q*delta_z + x_q*delta_y - y_q*delta_x + z_q;
norm=sqrt(attitude[0]*attitude[0]+attitude[1]*attitude[1]+attitude[2]*attitude[2]+attitude[3]*attitude[3]);
attitude[0]=norm*attitude[0];
attitude[1]=norm*attitude[1];
attitude[2]=norm*attitude[2];
attitude[3]=norm*attitude[3];
		Pitch = asin(-2 * attitude[1] * attitude[3] + 2 * attitude[0]* attitude[2])* 57.3;	// pitch
		Roll  = atan2(2 * attitude[2] * attitude[3] + 2 * attitude[0] * attitude[1], -2 * attitude[1] * attitude[1] - 2 * attitude[2]* attitude[2] + 1)* 57.3;	// roll
		Yaw   = atan2(2*(attitude[1]*attitude[2] + attitude[0]*attitude[3]),attitude[0]*attitude[0]+attitude[1]*attitude[1]-attitude[2]*attitude[2]-attitude[3]*attitude[3]) * 57.3;	//yaw
//��Ԫ����һ��
}