/*
************************************************************************
*                �����ʵ��ѧ K60 ѧϰ����
* �ļ��� :[global.c]
* ��  �� ��ȫ�ֱ���
* ��ƸĽ���Wei Li
* Email ��378987349@qq.com
* ˵  �� ���������õ�ȫ�ֱ���
***********************************************************************
*/

#ifndef __GLOBAL_H__
#define __GLOBAL_H__
#include "common.h"
#include "VCAN_OV7725_Eagle.h"

/*----------------------/
*-------�ٶȲ���-------/
*---------------------*/
extern int     speed_pwm;
extern s16     trueSpeedSigma; //��������������������
extern int     target_speed;
extern s16     sp_err;
extern s16     sp_err1;//�ϴ�
extern s16     sp_err2;//���ϴ�
extern u16     P_motor;
extern u16     I_motor;
extern u16     D_motor;
/*----------------------/
*-------���򲿷�-------/
*---------------------*/
extern u16     P_steer;//���P
extern u16     D_steer;//���D
extern s16     st_ek,st_ek1;//���Ρ��ϴ�ƫ��
extern int     cur_steer;//������PWMֵ

/*----------------------/
*-------ͼ�񲿷�-------/
*---------------------*/

extern uint8 Picbuff[CAMERA_SIZE];//��ѹǰ������
extern uint8 img_origin[CAMERA_H][CAMERA_W];//��ѹ��δ���н�����
extern uint8 img[CAMERA_H][CAMERA_W];//����У�������ڴ��������

#define ROW CAMERA_H
#define COLUMN CAMERA_W

#endif