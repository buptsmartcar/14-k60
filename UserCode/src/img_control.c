#include "include.h"
#include "img_control.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "timer.h"
#include "beep.h"

/**********************************************************************************
*  �������ƣ�void show_photo() 
*  ����˵�����������ͼ��
*  ����˵����f==1 ����ӥ������ͷ�Ķ�ֵ����ʽ�����f==0�Ҷ�ģʽ���
*  �������أ���
*  �޸�ʱ�䣺2014-6-17  wuwenqi
*  ��    ע��
**********************************************************************************/

void show_photo(int f)
{
  uart_putchar(UART0,0x01);  //ͼ��ͷ
  uart_putchar(UART0,0xFE);  //ͼ��ͷ
  int i,j;
  if(f==1){//��ֵ��ģʽ
    for(i=0;i<ROW*COLUMN/8;i++){
      uart_putchar(UART0,Picbuff[i]);
    }
  }
  else{//�Ҷ�ģʽ
    for(i=0;i<ROW;i++){
      for(j=0;j<COLUMN;j++){
        uart_putchar(UART0,img[i][j]);
      }
    }
  }
  uart_putchar(UART0,0xFE);  //ͼ��ͷ
  uart_putchar(UART0,0x01);  //ͼ��ͷ
}

/**********************************************************************************
*  �������ƣ�void image_process() 
*  ����˵����ͼ����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2014-6-17  wuwenqi
*  ��    ע��
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
  //��buffer(img_origin)�е�ͼ��copy��img��������������Ҫ��
  copyImgBuffer();
  
  //TODO 
  //����д���Լ��Ĵ����㷨,Ŀ���ǻ��st_ek�������Ҳ���Ƕ��ƫ�ι������
}

