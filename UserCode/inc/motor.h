/*
************************************************************************
*                �����ʵ��ѧ K60 ѧϰ����
* �ļ��� :[motor.h]
* ��  �� ���������������
*��ƸĽ���snowwolf
*  Email ��snowwolf2012@qq.com
* ˵  �� ���������������
***********************************************************************
*/
#ifndef __MOTOR_H__
#define __MOTOR_H__

#define MOTOR_DOUBLE 0   //Ϊ�������·����Ԥ��

#include "common.h"
#include "MK60_ftm.h"
#include "global.h"
#include "img_control.h"

// �ҸĶ�����������ٶȱ�С������,ԭΪ10000���ָĶ�Ϊ2000��2014-2-27���ʲ���.
 #define MOTOR_MAX     8000
 #define MOTOR_MIN    -8000



#define  MOTOR_FTMN       FTM0
#define  MOTOR_FTMCH0     FTM_CH0           //PTC1
#define  MOTOR_FTMCH1     FTM_CH1           //PTC2

//���ԣ���
  //  #define  MOTOR_FTMCH2     FTM_CH2           //PTC3
    //#define  MOTOR_FTMCH3     FTM_CH3           //PTC4



#define  MOTOR_FREQ 16000           //���Ƶ��   16k
#define  MOTOR_INIT_VAL 800          //�����ʼֵ������1/10000  ��5000/10000 50%



void motor_init();

#if !MOTOR_DOUBLE
    void PWMSetMotor(s32 speed_pwm);
    void get_current_speed();
    void speedControl_PD();
    int convert_speed(int speed_in_cm);
#endif

#endif