/*
************************************************************************
*                �����ʵ��ѧ K60 ѧϰ����
* �ļ��� :[motor.c]
* ��  �� �������������
*��ƸĽ���snowwolf
*  Email ��snowwolf2012@qq.com
* ˵  �� �������������
***********************************************************************
*/

#include "motor.h"      
#include "steer.h"
#include "MK60_uart.h"

/********************************************************************
** ��������: motor_init()
** ��������: �����ʼ��
** ��ڣ��Ƕ�ֵ
** ���ڣ�
** ˵��:
*********************************************************************/
void motor_init()
{

    if(abs(MOTOR_MAX) <= FTM_PRECISON){
        if(abs(MOTOR_MIN) <= FTM_PRECISON){
            //��ʼ��FTM0_CH0 CH1 CH2 CH3���Ƶ��Ϊ 16kHZ,ռ�ձ�Ϊ 50% ��PWM;
            ftm_pwm_init(MOTOR_FTMN,MOTOR_FTMCH0,MOTOR_FREQ,0);
            ftm_pwm_init(MOTOR_FTMN,MOTOR_FTMCH1,MOTOR_FREQ,0);
        }
        else{
            
            DEBUG_PRINTF("\n��Сֵ���ܳ���PWM����ֵ");
        }
    }
    else{
        DEBUG_PRINTF("\n���ֵ���ܳ���PWM����ֵ");
    }
    
}

/********************************************************************
** ��������: PWMSetMotor
** ��������: �����ٶ�
** ��ڣ��ٶ�
** ���ڣ�
** ˵��:
*********************************************************************/
void PWMSetMotor(s32 speed_pwm)
{
    if(speed_pwm < MOTOR_MIN)
    {
        speed_pwm = MOTOR_MIN;
    }
    if(speed_pwm > MOTOR_MAX)
    {
        speed_pwm = MOTOR_MAX;
    }
    if(speed_pwm > 0)
    {
        ftm_pwm_duty(MOTOR_FTMN,MOTOR_FTMCH1,0);
        ftm_pwm_duty(MOTOR_FTMN,MOTOR_FTMCH0,speed_pwm);
    }
    else
    {
        speed_pwm = -speed_pwm;
        ftm_pwm_duty(MOTOR_FTMN,MOTOR_FTMCH0,0);
        ftm_pwm_duty(MOTOR_FTMN,MOTOR_FTMCH1,speed_pwm);
    }
    
}

/***********************************************
*  �������ƣ�get_current_speed(void)
*  ����˵������ȡ������
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2014-6-17
*  ��    ע��
***********************************************/
void get_current_speed()
{      
    trueSpeedSigma= ftm_quad_get(FTM2);
    ftm_quad_clean(FTM2);
}


/**********************************************************************************
*  �������ƣ�void SpeedControl_PD()
*  ����˵����λ��ʽ�ٶȿ���PD,posΪ����PWM��ֵ;
*  �������أ���
*  �޸�ʱ�䣺2018-3-25 15:06:09 ������
*  ��    ע��
**********************************************************************************/

void speedControl_PD()
{
    get_current_speed();
    
    sp_err = target_speed - trueSpeedSigma;
    
    //PD equation
    int pos= P_motor*(sp_err) + D_motor*(sp_err-sp_err1);
    
    speed_pwm =  pos;
      
    if(speed_pwm > MOTOR_MAX)
    {
        speed_pwm = MOTOR_MAX;
    } 
    if(speed_pwm < MOTOR_MIN)
    {
        speed_pwm = MOTOR_MIN;
    }

    sp_err2 = sp_err1;//���ϴε����ϴ�
    sp_err1 = sp_err; //�ϴε������
    //send pwm to motor
    PWMSetMotor(speed_pwm);  
    
}
/**********************************************************************************
*  �������ƣ�int speed_convert
*  ����˵����cmΪ��λ���ٶ�ת��Ϊ������������Ϊ��λ���ٶȣ�������ָһ��PIT�����ڵ�������
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2018-1-28 Wei li
*  ��    ע�������Ǹ��ݳ��ֵ�ҧ�Ϲ�ϵ���־��Լ�����һȦ����������ת����,Ŀ���ǵ��Ե�ʱ��ֱ�Ӹ���������Ϊ��λ���ٶȣ������Ǳ���������Ϊ��λ���������˵�ϰ��
**********************************************************************************/

int convert_speed(int speed_in_cm){
    return ((((float)speed_in_cm/60)/5.5*4)*10/(18*3.14))*512;
}


