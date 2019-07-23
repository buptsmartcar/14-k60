#include "include.h"


double fGyroscopeAngleIntegral=0;
double g_fCarAngle ;
double g_fGyroscopeAngleSpeed ;
double g_fGravityAngle ;
#define GRAVITY_OFFSET   150
#define GYROSCOPE_OFFSET 0
#define GYROSCOPE_ANGLE_SIGMA_FREQUENCY	 100//200//15//8
#define GRAVITY_ADJUST_TIME_CONSTANT	 2//1.2//0.05
#define GYROSCOPE_ANGLE_RATIO		1.75//0.95
#define GRAVITY_ANGLE_RATIO            1//0.89//0.089



extern short gyro_z;
void AngleCalculate(void)
{

 double   fDeltaValue=0;

	g_fGravityAngle = (Angle - GRAVITY_OFFSET) * GRAVITY_ANGLE_RATIO;  //加速度
	g_fGyroscopeAngleSpeed = (gyro_z - GYROSCOPE_OFFSET ) * GYROSCOPE_ANGLE_RATIO;   //gyro

	g_fCarAngle = fGyroscopeAngleIntegral;
	fDeltaValue =(g_fGravityAngle - g_fCarAngle) / GRAVITY_ADJUST_TIME_CONSTANT;      //补偿量


	fGyroscopeAngleIntegral +=(g_fGyroscopeAngleSpeed + fDeltaValue) / GYROSCOPE_ANGLE_SIGMA_FREQUENCY;

}

float g_fAngleControlOut;
float AngleControl(void) {

        double fValue=0;
        float   ANGLE_CONTROL_P ;
        float   ANGLE_CONTROL_D ;



            ANGLE_CONTROL_P = -0.65;//2.2/-2.7
            ANGLE_CONTROL_D =-0.0155;//0.5


            fValue = (0 - g_fCarAngle) * ANGLE_CONTROL_P +                     //角速度控制系数
	      (0 - g_fGyroscopeAngleSpeed) * ANGLE_CONTROL_D;//角度控制系数


	if(fValue > 4800)      fValue = 4800;
	else if(fValue < -4800) fValue =- 4800;
	g_fAngleControlOut = fValue;



return g_fAngleControlOut ;

}



float SpeedPID(int  collect_speed,int AmSpeed)
 {

   float  SpeedPWMK=0;
   float  SpeedPWMKP ,SpeedPWMKI ;
   float  SpeedDifference=0;
   float  new_speed;




     float  SpeedKP = 200;//1.5//0.4;//0.2;//0.05;//0.1;//0.005;
     float  SpeedKI =0.1;//0.004// 0.5;//0.1;//0.0001





     SpeedDifference = AmSpeed - collect_speed  ;


     /////////////////-----P------/////////////////////

          SpeedPWMKP = SpeedKP*SpeedDifference;

     //////////////////------I------////////////////////////



          SpeedPWMKI = SpeedKI* SpeedDifference;

          SpeedPWMK += SpeedPWMKI ;
          if(SpeedPWMK>1500)
            SpeedPWMK=1500;
          if(SpeedPWMK<-1500)
            SpeedPWMK=-1500;


   ///////////////////////////////////////////////////

          new_speed=SpeedPWMKP+SpeedPWMK;

         /////////////////////////////////////
          if(new_speed>2500)
            new_speed=2500;
         if(new_speed<-2500)
            new_speed=-2500;


          return new_speed;

}


int Speed_L=0;
int Speed_R=0;

int MotorSpeedOut(float anglePWM ,float speedPWM,float dirPWM )
 {
   // int L_last,R_last;

  Speed_L = (int)(-anglePWM + speedPWM - dirPWM) ;
  Speed_R = (int)(-anglePWM + speedPWM + dirPWM) ;
  int limit=4800;

 if(Speed_L > limit) Speed_L = limit;
 if(Speed_L < -limit) Speed_L = -limit;
 if(Speed_R > limit) Speed_R = limit;
 if(Speed_R < -limit) Speed_R = -limit;


   if(Speed_R > 0)
    {
       ftm_pwm_duty(FTM0, FTM_CH0, Speed_R);
       ftm_pwm_duty(FTM0, FTM_CH1, 0);
    }
     else
    {
       ftm_pwm_duty(FTM0, FTM_CH0,0 );
       ftm_pwm_duty(FTM0, FTM_CH1, -Speed_R);
    }



     if(Speed_L > 0)
     {
       ftm_pwm_duty(FTM0, FTM_CH2,0);
       ftm_pwm_duty(FTM0, FTM_CH3, Speed_L);
     }
     else
     {
       ftm_pwm_duty(FTM0, FTM_CH2,-Speed_L);
       ftm_pwm_duty(FTM0, FTM_CH3, 0);
     }

    return ((Speed_L +Speed_R)/2);
 }

/***********************************************************
函数名称：SpeedPWMOut

***********************************************************/
#define SPEEDPERIODFAV  (100)
s16 SpeedPWMOut(s16 NewspeedPWM ,s16 LastspeedPWM,uint8_t PeriodCount)
{
    int16_t  speedPWMfav ;
    int16_t  SpeedOUT ;
    speedPWMfav = NewspeedPWM - LastspeedPWM ;
    SpeedOUT = speedPWMfav *(PeriodCount)/SPEEDPERIODFAV + LastspeedPWM ;

    return SpeedOUT ;

}

/***********************************************************
函数名称：AAangPWMOut

***********************************************************/
#define AANGPERIODFAV  (5)
s16 AAangPWMOut(s16 NewAangPWM ,s16 LastAangPWM,uint8_t PeriodCount)
{
    int16_t  AangPWMfav ;
    int16_t  AangOUT ;
    AangPWMfav = NewAangPWM - LastAangPWM ;
    AangOUT = AangPWMfav *(PeriodCount)/AANGPERIODFAV + LastAangPWM ;

    return AangOUT ;

}
