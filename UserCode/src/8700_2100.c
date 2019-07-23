#include "include.h"
#include "beep.h"
s16 gyro_x,gyro_y,gyro_z;
s16 accle_x,accle_y,accle_z;
#define USE_CORRECT 0
#define USE_CORRECT_C 1

#if USE_CORRECT_C
float h_fGyroscopeAngleIntegral = 0;//������
float fDeltaValue = 0;  //����ƫ����
float h_fGravityAngle = 0;                                              //���ٶȼ�ת�����ĽǶ�
float h_fGyroscopeAngleSpeed  = 0;                                      //������ת�����Ľ��ٶ�
float h_fCarAngle = 0;                                                  //����Ƕ�
float h_fCarAngleP = 0;
float VOLTAGE_GYRO = 0;                                                 //���������ǣ�ѡX,Y,Z��
float VOLTAGE_GRAVITY = 0;                                              //������ٶȼƣ�ѡX,Y,Z��

float GRAVITY_OFFSET = 27;                                               //���ٶȼ���ƫ
float GRAVITY_ANGLE_RATIO = (90 /(1050.0 - 27)) ;                       //���ٶȼƹ�һ������

float GYROSCOPE_OFFSET = 0;//21;//0  ;                                            //��������ƫ��
float GYROSCOPE_ANGLE_RATIO = 1.780;                                       //��һ������

float GRAVITY_ADJUST_TIME_CONSTANT = 2;                                  //�����Ǽ��ٶȼƼӺ͵ı�������
float GYROSCOPE_ANGLE_SIGMA_FREQUENCY = 50;                             //���ֵ�Ƶ��

float Clocks_Gyro = 0;                                                   //����2s�ڽ������������ȶ�
#endif

void Init2100()
{
    i2c_write_reg(I2C1,SlaveAddress2100,0x0d,0x02);
    
    Pause();
    
    i2c_write_reg(I2C1,SlaveAddress2100,CTRL_REG1_2100,0x02);
    
    Pause();
}

void Init8700()
{
    
    //  i2c_write_reg(I2C1,SlaveAddress8700,0x0f,0x33);
    
    //   Pause();
    
    i2c_write_reg(I2C1,SlaveAddress8700,CTRL_REG1_8700,0x05);
    
    Pause();
}


void nine_Read(unsigned char slave,unsigned char * p, short * q)
{
    int MUP_Zero=0x0000;
    
    p[0]  =    i2c_read_reg(I2C1,slave,OUT_X_MSB_REG);
    Pause();
    p[1]  =    i2c_read_reg(I2C1,slave,OUT_X_LSB_REG);
    Pause();
    p[2]  =    i2c_read_reg(I2C1,slave,OUT_Y_MSB_REG);
    Pause();
    p[3]  =    i2c_read_reg(I2C1,slave,OUT_Y_LSB_REG);
    Pause();
    p[4]  =    i2c_read_reg(I2C1,slave,OUT_Z_MSB_REG);
    Pause();
    p[5]  =    i2c_read_reg(I2C1,slave,OUT_Z_LSB_REG);
    Pause();
    
    
    q[0] = (((MUP_Zero | p[0])<<8)|p[1]);
    q[1] = (((MUP_Zero | p[2])<<8)|p[3]);
    q[2] = (((MUP_Zero | p[4])<<8)|p[5]);
    
}
void nine_Test(void){
    u8 bit8_data[6];
    s16 bit16_data16[3];
    unsigned short send_data[8];
    
    nine_Read(SlaveAddress8700,bit8_data,bit16_data16);
    accle_x=bit16_data16[0];
    accle_y=bit16_data16[1];
    accle_z=bit16_data16[2];
    
    nine_Read(SlaveAddress2100,bit8_data,bit16_data16);
    gyro_x=bit16_data16[0];
    gyro_y=bit16_data16[1];
    gyro_z=bit16_data16[2];
    
    send_data[0]=accle_x;
    send_data[1]=accle_y;
    send_data[2]=accle_z;
    send_data[3]=gyro_x;
    send_data[4]=gyro_y;
    send_data[5]=gyro_z;
    //uart_putchar(UART0,0x03);
    //uart_putchar(UART0,0xFC);
    Data_Send(UART0,send_data);
    // uart_putchar(UART0,0xFC);
    // uart_putchar(UART0,0x03);
}
//============================================================================
//�������ƣ�void nine_U(void) 
//�������أ���
//����˵������
//���ܸ�Ҫ������Ƕȼ��㡣
//============================================================================
float nine_Use(void){
    //u8 bit8_data[6];
    //s16 bit16_data16[3];
    //��ȡ������
    //nine_Read(SlaveAddress2100,bit8_data,bit16_data16);
    //gyro_y=bit16_data16[1];
    //if(gyro_y > 2000 ||gyro_y<-2000 ){// �ж�y���Ƿ���Ч
    return angle_Correct();
    //}
}
//============================================================================
//�������ƣ�void Angle_C(void) 
//�������أ���
//����˵������
//���ܸ�Ҫ������Ƕȼ��㡣
//============================================================================
int count = 0;
float arg = 0;
int i=1;
int g;
u32 rampPoint;
u8 hasUp=0;
float angle_Correct(void) 
{
    u8 bit8_data[6];
    s16 bit16_data16[3];
    
    
    //��ȡ������
    nine_Read(SlaveAddress2100,bit8_data,bit16_data16);
    //gyro_x=bit16_data16[0];
    gyro_y=bit16_data16[1];
    // gyro_z=bit16_data16[2];
    
    
    
#if USE_CORRECT
    s16 VOLTAGE_GYRO,VOLTAGE_GRAVITY;
    //ȡ�����ǵ�Y������
    VOLTAGE_GYRO = gyro_y;
    
    //ȡ���ٶȶ��Ƶ�X������
    VOLTAGE_GRAVITY = accle_z;
    
    //��������ƫ����
    //Gyro_Offset_Calculate();
    
    
    if(VOLTAGE_GRAVITY > 1050)                              //���Ƽ��ٶȼƶ���-1050 ~1050
    {
        VOLTAGE_GRAVITY = 1050;
    }
    
    if(VOLTAGE_GRAVITY <=  -1050)
    {
        VOLTAGE_GRAVITY = - 1050;
    }
    
    // h_fCarAngle += 
    //���ٶȼƶ�ȡ��Y����ֵת��Ϊ�Ƕ�
    h_fGravityAngle = (VOLTAGE_GRAVITY - GRAVITY_OFFSET) * GRAVITY_ANGLE_RATIO;
    
    //��������ȡ���ٶ�
    h_fGyroscopeAngleSpeed = (VOLTAGE_GYRO - GYROSCOPE_OFFSET) * GYROSCOPE_ANGLE_RATIO;
    
    //����Ƕȼ���
    //  h_fCarAngle = h_fGyroscopeAngleIntegral; 
    fDeltaValue = (h_fGravityAngle - h_fCarAngle) / GRAVITY_ADJUST_TIME_CONSTANT;
    h_fGyroscopeAngleIntegral += (h_fGyroscopeAngleSpeed + fDeltaValue) / GYROSCOPE_ANGLE_SIGMA_FREQUENCY;
    // arg += gyro_y;
    //count++;
    h_fCarAngle += (gyro_y+GYROSCOPE_OFFSET)/GYROSCOPE_ANGLE_SIGMA_FREQUENCY;
    
    if(i){
        g= accle_z;
        g++;
        i=0;
    }
    
    float angle = (float)acos((float)accle_z/g)*180/3.14;
    return acos((float)accle_z/g);//angle;// h_fCarAngle;//arg/count;//h_fCarAngle;
    
#else
    
    h_fCarAngleP = h_fCarAngle;
    h_fCarAngle = gyro_y;
    
    if(waytype ==0){
        // if(gyro_y <1200&&gyro_y>-1200){
        //   gyro_y =0;
        //}
        if(h_fCarAngle > 7000){
            count ++;
        }
        
        else if(h_fCarAngle <-5000){
            count--;
        }
        
        else{
            count = 0;
        }
        
        
        if(count > 3){
            
            if(ramp_Flag==0){
                rampPoint=getTime();
                ramp_Flag =1;
                
#if BEEP_DEBUG
                beep(2);
#endif
            }
            
        }
        
        else if(count < -3){
            if(ramp_Flag==1){
                ramp_Flag =2;
                
#if BEEP_DEBUG
                beep(2);
#endif
            }
            
        }
        
    }
    else{
        
        count = 0;
        
    } 
    u32 ct=getTime();
    if((u32)ct-rampPoint>0){
        ramp_Flag=0;
    }
    // char t[4]={0};
    //sprintf(t,"a:%d\n",(int)(h_fCarAngle));
    //uart_putstr(UART0,t);
    return h_fCarAngle;//ramp_Flag;
#endif
}
//============================================================================
//�������ƣ�void Gyro_Offset_Calculate()
//�������أ���
//����˵������
//���ܸ�Ҫ��//�������������������  Cut_Gyro_XΪ����������ֵ�� Gyro_XΪʵ�ʵĶ�ֵ��Gyro_X_Offset Ϊ���
//============================================================================
void Gyro_Offset_Calculate()      
{
    float Cut_Gyro_X;
    
    
    //��ȥƫ��ֵ�õ���ʵʱֵ
    Cut_Gyro_X = gyro_y - GYROSCOPE_OFFSET;
    
    //����ʵʱֵ���޸���ƫ��
    if(Cut_Gyro_X>=2) 
    {
        GYROSCOPE_OFFSET += 0.001;
    } 
    else if(Cut_Gyro_X<=-2) 
    {
        GYROSCOPE_OFFSET -= 0.001;
    } 
    else 
    {
        GYROSCOPE_OFFSET = GYROSCOPE_OFFSET * 0.99 + 0.01 * gyro_y;
    }
    
    //����2����и���  
    //if (Clocks_Gyro <= 400)
    // GYROSCOPE_OFFSET = GYROSCOPE_OFFSET * 0.5 + 0.5 * gyro_y;
    
}
/*
void Angle_collect()
{

}
*/