#ifndef __BEEP_H__
#define __BEEP_H__
#include "global.h"

extern u8 beep_count;
extern u8 beep_flag;
extern u8 beep_time;
void beep(const u8 time);
#endif