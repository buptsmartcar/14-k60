/*
************************************************************************
*                北京邮电大学 K60 学习例程
* 文件名 :[motor.h]
* 描  述 ：电机机驱动函数
*设计改进：snowwolf
*  Email ：snowwolf2012@qq.com
* 说  明 ：电机机驱动函数
***********************************************************************
*/
#ifndef __MOTOR_H__
#define __MOTOR_H__

#define MOTOR_DOUBLE 0   //为光电组两路控制预留

#include "common.h"
#include "MK60_ftm.h"
#include "global.h"
#include "img_control.h"

// 我改动这里！！先让速度变小来测试,原为10000，现改动为2000，2014-2-27，肥叉烧.
 #define MOTOR_MAX     8000
 #define MOTOR_MIN    -8000



#define  MOTOR_FTMN       FTM0
#define  MOTOR_FTMCH0     FTM_CH0           //PTC1
#define  MOTOR_FTMCH1     FTM_CH1           //PTC2

//测试：：
  //  #define  MOTOR_FTMCH2     FTM_CH2           //PTC3
    //#define  MOTOR_FTMCH3     FTM_CH3           //PTC4



#define  MOTOR_FREQ 16000           //电机频率   16k
#define  MOTOR_INIT_VAL 800          //电机初始值，精度1/10000  即5000/10000 50%



void motor_init();

#if !MOTOR_DOUBLE
    void PWMSetMotor(s32 speed_pwm);
    void get_current_speed();
    void speedControl_PD();
    int convert_speed(int speed_in_cm);
#endif

#endif