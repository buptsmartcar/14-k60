#include "beep.h"
#include "MK60_gpio.h"
u8 beep_count=0;
u8 beep_flag=0;
u8 beep_time=0;
//time最小单位为1/4秒
void beep(const u8 time){
    if(beep_flag==0){
        beep_flag=1;
        beep_count=0;
        beep_time=time;
        gpio_set(PTC4,1);
        
    }
}
