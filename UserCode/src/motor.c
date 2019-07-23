/*
************************************************************************
*                北京邮电大学 K60 学习例程
* 文件名 :[motor.c]
* 描  述 ：电机驱动函数
*设计改进：snowwolf
*  Email ：snowwolf2012@qq.com
* 说  明 ：电机驱动函数
***********************************************************************
*/

#include "motor.h"      
#include "steer.h"
#include "MK60_uart.h"

/********************************************************************
** 函数名称: motor_init()
** 功能描述: 电机初始化
** 入口：角度值
** 出口：
** 说明:
*********************************************************************/
void motor_init()
{

    if(abs(MOTOR_MAX) <= FTM_PRECISON){
        if(abs(MOTOR_MIN) <= FTM_PRECISON){
            //初始化FTM0_CH0 CH1 CH2 CH3输出频率为 16kHZ,占空比为 50% 的PWM;
            ftm_pwm_init(MOTOR_FTMN,MOTOR_FTMCH0,MOTOR_FREQ,0);
            ftm_pwm_init(MOTOR_FTMN,MOTOR_FTMCH1,MOTOR_FREQ,0);
        }
        else{
            
            DEBUG_PRINTF("\n最小值不能超过PWM精度值");
        }
    }
    else{
        DEBUG_PRINTF("\n最大值不能超过PWM精度值");
    }
    
}

/********************************************************************
** 函数名称: PWMSetMotor
** 功能描述: 设置速度
** 入口：速度
** 出口：
** 说明:
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
*  函数名称：get_current_speed(void)
*  功能说明：获取脉冲数
*  参数说明：
*  函数返回：无
*  修改时间：2014-6-17
*  备    注：
***********************************************/
void get_current_speed()
{      
    trueSpeedSigma= ftm_quad_get(FTM2);
    ftm_quad_clean(FTM2);
}


/**********************************************************************************
*  函数名称：void SpeedControl_PD()
*  功能说明：位置式速度控制PD,pos为所求PWM波值;
*  函数返回：无
*  修改时间：2018-3-25 15:06:09 李先生
*  备    注：
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

    sp_err2 = sp_err1;//上上次等于上次
    sp_err1 = sp_err; //上次等于这次
    //send pwm to motor
    PWMSetMotor(speed_pwm);  
    
}
/**********************************************************************************
*  函数名称：int speed_convert
*  功能说明：cm为单位的速度转换为编码器脉冲数为单位的速度，这里是指一个PIT周期内的脉冲数
*  参数说明：无
*  函数返回：无
*  修改时间：2018-1-28 Wei li
*  备    注：这里是根据齿轮的咬合关系和轮距以及编码一圈的脉冲数来转换的,目的是调试的时候直接给出以厘米为单位的速度，而不是编码其脉冲为单位，更符合人的习惯
**********************************************************************************/

int convert_speed(int speed_in_cm){
    return ((((float)speed_in_cm/60)/5.5*4)*10/(18*3.14))*512;
}


