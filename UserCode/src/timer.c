#include "timer.h"
#include "global.h"

u32 startTime,endTime;

u32 getTime(){
  return halfsecond;
}

void startTimer(){
  startTime=getTime();
}

void stopTimer(){
  endTime=getTime();
}

u8 timerLessThan(u32 time){
    stopTimer();
    return (endTime-startTime)<time?1:0;
}


