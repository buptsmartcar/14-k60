/*
************************************************************************
*                北京邮电大学 K60 学习例程                                        
* 文件名 :[steer.c] 
* 描  述 ：舵机驱动函数
*设计改进：snowwolf
*  Email ：snowwolf2012@qq.com
* 说  明 ：舵机驱动函数
***********************************************************************
*/

#include "steer.h"
#include "control.h"
#include "img_control.h"
#include  "mk60_uart.h"
#include "8700_2100.h"
/********************************************************************
** 函数名称 : void steer_init() 
** 功能描述 : 设置舵机转向
** 入口     ：
** 出口     ：
** 说明     :  初始化PWM波及占空比
*********************************************************************/
void steer_init()         
{
    //ASSERT_RST(STEER_INIT_VAL <= FTM_PRECISON,"舵机0最大值不能超过PWM精度值"); 
    if(STEER_INIT_VAL <= FTM_PRECISON){   
        ftm_pwm_init(STEER_FTMN,STEER_FTMCH,STEER_FREQ,STEER_MIDDLE); 
    }
    else{
        DEBUG_PRINTF("\n舵机0最大值不能超过PWM精度值");
    }
    
}

/********************************************************************
** 函数名称: void PWMSetSteer(int angle_pwm) 
** 功能描述: 设置舵机转向
** 入口：角度值
** 出口：
** 说明:  
*********************************************************************/
void PWMSetSteer(int angle_pwm)         
{
    //占空比不能超过上限（防止过压）
    //同时防止方向打死  
    //这个保护措施是必要的
    if(angle_pwm < STEER_RIGHT)
        angle_pwm = STEER_RIGHT;
    if(angle_pwm > STEER_LEFT)
        angle_pwm = STEER_LEFT;
    
    ftm_pwm_duty(STEER_FTMN,STEER_FTMCH,angle_pwm);
}



/**********************************************************************************
*  函数名称：void DirectionControl()
*  功能说明：位置式方向控制pd,计算cur_steer
*  参数说明：无
*  函数返回：无
*  修改时间：2018-1-12  Wei li
*  备    注：
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
