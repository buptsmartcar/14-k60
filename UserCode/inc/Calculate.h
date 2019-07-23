#ifndef __Calculate_H__
#define __Calculate_H__ 

extern double g_fGravityAngle ;

float SpeedPID(int  collect_speed,int AmSpeed);
void AngleCalculate(void);
int MotorSpeedOut(float anglePWM ,float speedPWM,float dirPWM );
float AngleControl(void);
s16 SpeedPWMOut(int16_t NewspeedPWM ,int16_t LastspeedPWM,uint8_t PeriodCount);
s16 AAangPWMOut(int16_t NewAangPWM ,int16_t LastAangPWM,uint8_t PeriodCount);




#endif