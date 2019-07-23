/*
************************************************************************
*                �����ʵ��ѧ K60 ѧϰ����                                        
* �ļ��� :[steer.h] 
* ��  �� �������������
*��ƸĽ���snowwolf
*  Email ��snowwolf2012@qq.com
* ˵  �� �������������
***********************************************************************
*/
#ifndef __STEER_H__
#define __STEER_H__

#include "common.h"
#include "MK60_ftm.h"


//Ϊ˫���Ԥ��������ͷ��͵���������� 0
#define STEER_DOUBLE 0


#define STEER_MIDDLE    4850//1530    //����ڽ���ֵ  500~15��
#define STEER_LEFT      STEER_MIDDLE+700//2030-325   //zuoת  //����ڽ�����  �����ֵ�����ڲ��Եģ���Ҹ����Լ��Ķ������
#define STEER_RIGHT     STEER_MIDDLE-675//1030+325  //����ڽ��Ҽ��� 


#define  STEER_FTMN     FTM1
#define  STEER_FTMCH    FTM_CH1     //FTM1_CH1��ӦPTA13��
#define  STEER_FREQ     300    //���Ƶ��   ����һ��FTMģ��ֻ�����һ��Ƶ�ʣ�                               //�����������Ҳֻ����һ��Ƶ�� ����ͳһ100Hz
#define  STEER_INIT_VAL STEER_MIDDLE//1530   //�����ʼֵ������1/10000  ��1200/10000  = 12%//2100

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