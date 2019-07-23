/*
************************************************************************
*                北京邮电大学 K60 学习例程
* 文件名 :[global.c]
* 描  述 ：全局变量
* 设计改进：Wei Li
* Email ：378987349@qq.com
* 说  明 ：定义所用的全局变量
***********************************************************************
*/

#ifndef __GLOBAL_H__
#define __GLOBAL_H__
#include "common.h"
#include "VCAN_OV7725_Eagle.h"

/*----------------------/
*-------速度部分-------/
*---------------------*/
extern int     speed_pwm;
extern s16     trueSpeedSigma; //编码器所读到的脉冲数
extern int     target_speed;
extern s16     sp_err;
extern s16     sp_err1;//上次
extern s16     sp_err2;//上上次
extern u16     P_motor;
extern u16     I_motor;
extern u16     D_motor;
/*----------------------/
*-------方向部分-------/
*---------------------*/
extern u16     P_steer;//舵机P
extern u16     D_steer;//舵机D
extern s16     st_ek,st_ek1;//当次、上次偏差
extern int     cur_steer;//舵机输出PWM值

/*----------------------/
*-------图像部分-------/
*---------------------*/

extern uint8 Picbuff[CAMERA_SIZE];//解压前缓冲区
extern uint8 img_origin[CAMERA_H][CAMERA_W];//解压后未进行矫正的
extern uint8 img[CAMERA_H][CAMERA_W];//梯形校正后用于处理的数组

#define ROW CAMERA_H
#define COLUMN CAMERA_W

#endif