/*
************************************************************************
*                �����ʵ��ѧ K60 ѧϰ����                                        
* �ļ��� :[steer.c] 
* ��  �� �������������
*��ƸĽ���snowwolf
*  Email ��snowwolf2012@qq.com
* ˵  �� �������������
***********************************************************************
*/

#include "steer.h"
#include "control.h"
#include "img_control.h"
#include  "mk60_uart.h"
#include "8700_2100.h"
/********************************************************************
** �������� : void steer_init() 
** �������� : ���ö��ת��
** ���     ��
** ����     ��
** ˵��     :  ��ʼ��PWM����ռ�ձ�
*********************************************************************/
void steer_init()         
{
    //ASSERT_RST(STEER_INIT_VAL <= FTM_PRECISON,"���0���ֵ���ܳ���PWM����ֵ"); 
    if(STEER_INIT_VAL <= FTM_PRECISON){   
        ftm_pwm_init(STEER_FTMN,STEER_FTMCH,STEER_FREQ,STEER_MIDDLE); 
    }
    else{
        DEBUG_PRINTF("\n���0���ֵ���ܳ���PWM����ֵ");
    }
    
}

/********************************************************************
** ��������: void PWMSetSteer(int angle_pwm) 
** ��������: ���ö��ת��
** ��ڣ��Ƕ�ֵ
** ���ڣ�
** ˵��:  
*********************************************************************/
void PWMSetSteer(int angle_pwm)         
{
    //ռ�ձȲ��ܳ������ޣ���ֹ��ѹ��
    //ͬʱ��ֹ�������  
    //���������ʩ�Ǳ�Ҫ��
    if(angle_pwm < STEER_RIGHT)
        angle_pwm = STEER_RIGHT;
    if(angle_pwm > STEER_LEFT)
        angle_pwm = STEER_LEFT;
    
    ftm_pwm_duty(STEER_FTMN,STEER_FTMCH,angle_pwm);
}



/**********************************************************************************
*  �������ƣ�void DirectionControl()
*  ����˵����λ��ʽ�������pd,����cur_steer
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2018-1-12  Wei li
*  ��    ע��
**********************************************************************************/
void directionControl_PD()

{
     
    float adjust = P_steer * st_ek + D_steer*(st_ek - st_ek1);
  
    st_ek1=st_ek;      
    
    cur_steer = STEER_MIDDLE +(int)adjust; 

    if(cur_steer < STEER_RIGHT)
    {
        cur_steer = STEER_RIGHT;
    }
    else if(cur_steer > STEER_LEFT)
    {
        cur_steer = STEER_LEFT;
    } 
    PWMSetSteer(cur_steer);
}
