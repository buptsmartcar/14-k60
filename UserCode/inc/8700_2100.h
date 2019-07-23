#ifndef __8700_2100_H__
#define __8700_2100_H__ 

#define	SlaveAddress2100	      0x20	//IIC写入时的地址字节数据，+1为读取   现在是8451的程序
#define CTRL_REG1_2100                0x13

#define	SlaveAddress8700	      0x1e	//IIC写入时的地址字节数据，+1为读取   现在是8451的程序
#define CTRL_REG1_8700                0x2a


#define OUT_X_MSB_REG         0x01
#define OUT_X_LSB_REG         0x02
#define OUT_Y_MSB_REG         0x03
#define OUT_Y_LSB_REG         0x04
#define OUT_Z_MSB_REG         0x05
#define OUT_Z_LSB_REG         0x06


void Init2100();
void Init8700();
void nine_Read(unsigned char slave,unsigned char * p,short * q);
void nine_Test();
float nine_Use();
float angle_Correct();
void Gyro_Offset_Calculate();
extern s16 gyro_x,gyro_y,gyro_z;
extern s16 accle_x,accle_y,accle_z;
extern u8 ramp_Flag,jolt_Flag;
extern u32 rampPoint;

extern u8 hasUp;


#endif