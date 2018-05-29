#include "filter.h"


/*       
        Q:����������Q���󣬶�̬��Ӧ��죬�����ȶ��Ա仵
        R:����������R���󣬶�̬��Ӧ�����������ȶ��Ա��       
*/



/* ??????? */



float KalmanFilter(const float ResrcData,Kalman_Date *K)
{
    K->x_mid = K->x_last1;                       //x_last=x(k-1|k-1),x_mid=x(k|k-1)
    K->p_mid = K->p_last1 + K->ProcessNoise_Q;                     //p_mid=p(k|k-1),p_last=p(k-1|k-1),Q=??
    K->kg = K->p_mid / (K->p_mid + K->MeasureNoise_R);                 //kg?kalman filter,R ???
    K->x_now = K->x_mid + K->kg * (ResrcData - K->x_mid);   //???????
    K->p_now = (1 - K->kg) * K->p_mid;                 //??????covariance
    K->p_last1 = K->p_now;                     //??covariance ?
    K->x_last1 = K->x_now;                     //???????

    return K->x_now;
}





float filter_1st(const float ResrcData, Filter_1st_Str *Fil)
{
   Fil->ResrcData_mem[1] = Fil->ResrcData_mem[0];
   Fil->ResrcData_mem[0] = ResrcData;	 
   Fil->output_mem[1] = Fil->output_mem[0];	
   Fil->output_mem[0] = Fil->m_filter*Fil->ResrcData_mem[0]+(1-Fil->m_filter)*Fil->output_mem[1];	
  return Fil->output_mem[0];
}
double filter_1st1(const double ResrcData,float m_filter)
{
  static double ResrcData_mem1[2];
  static double output_mem1[2];

   ResrcData_mem1[1]=ResrcData_mem1[0];
   ResrcData_mem1[0]=ResrcData;	 
   output_mem1[1]=output_mem1[0];	
   output_mem1[0]=m_filter*ResrcData_mem1[0]+(1-m_filter)*output_mem1[1];	
  return output_mem1[0];
}


double filter_1st2(const double ResrcData,float m_filter)
{
	static double ResrcData_mem2[2];
	static double output_mem2[2];
	
	 ResrcData_mem2[1]=ResrcData_mem2[0];
	 ResrcData_mem2[0]=ResrcData;	 
	 output_mem2[1]=output_mem2[0];	
	 output_mem2[0]=m_filter*ResrcData_mem2[0]+(1-m_filter)*output_mem2[1];	
  return output_mem2[0];
}



double filter_1st3(const double ResrcData,float m_filter)
{
	static double ResrcData_mem3[2];
	static double output_mem3[2];
	
	 ResrcData_mem3[1]=ResrcData_mem3[0];
	 ResrcData_mem3[0]=ResrcData;	 
	 output_mem3[1]=output_mem3[0];	
	 output_mem3[0]=m_filter*ResrcData_mem3[0]+(1-m_filter)*output_mem3[1];	
  return output_mem3[0];
}



double filter_1st4(const double ResrcData,float m_filter)
{
	static double ResrcData_mem4[2];
	static double output_mem4[2];
	
	 ResrcData_mem4[1]=ResrcData_mem4[0];
	 ResrcData_mem4[0]=ResrcData;	 
	 output_mem4[1]=output_mem4[0];	
	 output_mem4[0]=m_filter*ResrcData_mem4[0]+(1-m_filter)*output_mem4[1];	
  return output_mem4[0];
}






double filter_ave1(const double ResrcData_ave)
{
  #define AVENUM 20
	u16 count_ave;
	static double ave_ResrcData_mem1[AVENUM];
	static double sum_ave1;
	
	for(count_ave=AVENUM-1;count_ave>0;count_ave--)
	ave_ResrcData_mem1[count_ave]=ave_ResrcData_mem1[count_ave-1];
	
	
	ave_ResrcData_mem1[0]=ResrcData_ave;
	
  sum_ave1=0;
	for(count_ave=0;count_ave<AVENUM;count_ave++)
	sum_ave1=sum_ave1+ave_ResrcData_mem1[count_ave];

	return (sum_ave1/AVENUM);
	





}
