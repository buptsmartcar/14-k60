#ifndef __CONTROL_H__
#define __CONTROL_H__
#include "global.h"
#include "common.h"

extern char g_ucFuzzyDirectionKp[7][7], g_ucFuzyDirectionKd[7][7];
extern float g_fDirectionKp, g_fDirectionKd, g_fMotorK;
#define       NB        -3//建立模糊表
#define       NM        -2
#define       NS        -1
#define       ZO        0
#define       PS        -1
#define       PM        -2
#define       PB        -3
#define       TABLE        3
#define       MIDLINE_ERR_MAX        30
#define       MIDLINE_ERR_ERR_MAX        9
#define       KP_MAX        0.0018
#define       KD_MAX        -0.00012


void init();
void FuzzyControl(void);
void calc_and_ctrl();




#endif