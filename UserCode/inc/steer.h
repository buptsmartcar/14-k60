/*
************************************************************************
*                北京邮电大学 K60 学习例程                                        
* 文件名 :[steer.h] 
* 描  述 ：舵机驱动函数
*设计改进：snowwolf
*  Email ：snowwolf2012@qq.com
* 说  明 ：舵机驱动函数
***********************************************************************
*/
#ifndef __STEER_H__
#define __STEER_H__

#include "common.h"
#include "MK60_ftm.h"


//为双舵机预留，摄像头组和单舵机可以置 0
#define STEER_DOUBLE 0


#define STEER_MIDDLE    4850//1530    //舵机摆角中值  500~15度
#define STEER_LEFT      STEER_MIDDLE+700//2030-325   //zuo转  //舵机摆角左极限  这里的值是用于测试的，大家根据自己的舵机更改
#define STEER_RIGHT     STEER_MIDDLE-675//1030+325  //舵机摆角右极限 


#define  STEER_FTMN     FTM1
#define  STEER_FTMCH    FTM_CH1     //FTM1_CH1对应PTA13口
#define  STEER_FREQ     300    //舵机频率   由于一个FTM模块只能输出一个频率，                               //所以两个舵机也只能用一个频率 这里统一100Hz
#define  STEER_INIT_VAL STEER_MIDDLE//1530   //舵机初始值，精度1/10000  即1200/10000  = 12%//2100

extern s16 st_err;
extern s16 st_err1;
extern s16 st_ek_foresee;
extern s16 st_ek_foresee1;
extern u8 circleSmallError;
extern float paramA;
void steer_init();
void PWMSetSteer(int angle_pwm);

void calcDirection();
void calcDirection_k();
void directionControl();
void directionControl_PD();
void directionControl_PD_SQR();
void set_steer(void);
float getErrorK();
void calc_steer();
void steerCtrl();
float getErrorCurvature();
void calcDirection_curvature();
#endif