#include "include.h"
#include "img_control.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "timer.h"
#include "beep.h"

/**********************************************************************************
*  函数名称：void show_photo() 
*  功能说明：连续输出图像
*  参数说明：f==1 按照鹰眼摄像头的二值化格式输出，f==0灰度模式输出
*  函数返回：无
*  修改时间：2014-6-17  wuwenqi
*  备    注：
**********************************************************************************/

void show_photo(int f)
{
  uart_putchar(UART0,0x01);  //图像头
  uart_putchar(UART0,0xFE);  //图像头
  int i,j;
  if(f==1){//二值化模式
    for(i=0;i<ROW*COLUMN/8;i++){
      uart_putchar(UART0,Picbuff[i]);
    }
  }
  else{//灰度模式
    for(i=0;i<ROW;i++){
      for(j=0;j<COLUMN;j++){
        uart_putchar(UART0,img[i][j]);
      }
    }
  }
  uart_putchar(UART0,0xFE);  //图像头
  uart_putchar(UART0,0x01);  //图像头
}

/**********************************************************************************
*  函数名称：void image_process() 
*  功能说明：图像处理
*  参数说明：无
*  函数返回：无
*  修改时间：2014-6-17  wuwenqi
*  备    注：
**********************************************************************************/	

void copyImgBuffer(){
  u8 i,j;
  for(i=0;i<ROW;i++){
      for(j=0;j<COLUMN;j++){
        img[i][j]=img_origin[i][j];
      }
  }  
};


void image_process()
{       
  //将buffer(img_origin)中的图像copy到img数组里，这个函数不要关
  copyImgBuffer();
  
  //TODO 
  //这里写你自己的处理算法,目的是获得st_ek这个量，也就是舵机偏差，喂给方向环
}

