#ifndef __TIMER_H__
#define __TIMER_H__
#include "global.h"
extern u32 getTime();
extern u8 timerLessThan(u32 time);
extern void startTimer();
extern void stopTimer();
#endif