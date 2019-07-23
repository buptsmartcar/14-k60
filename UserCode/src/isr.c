#include "common.h"
#include "include.h"
#include "isr.h"
#include "control.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
/**********************************************************************************
*  函数名称：UART0_IRQHandler()
*  功能说明：串口中断处理函数
*  参数说明：无
*  函数返回：无
*  修改时间：2014-6-16  wuwenqi
*  备    注：
**********************************************************************************/	
void UART0_IRQHandler(void)
{
    char ch;
    //接收一个字节数据
    uart_getchar(UART0,&ch);
    switch(ch){
    case '0':
        //TODO     
        break;
    case 'a':
        //TODO   
        break;
    default:
        //TODO   
        break;
    }
}

/*************************************************************************
*  函数名称：PIT0_IRQHandler
*  功能说明：PIT0 定时中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2014-6-17 wuwenqi
*  备    注：
*************************************************************************/
void PIT0_IRQHandler(void)
{
    
    PIT_Flag_Clear(PIT0);//清中断标志位,清除了才能进下次中断
    //TODO 
    /*注意，PIT中断里尽量避免耗时过大的操作，如部分复杂计算等*/
    /*通常来讲，图像处理等复杂耗时操作应该放在主线程，也就是main函数中while部分*/
    /*而PIT中断内放的是电机和舵机控制等简单的控制操作*/
    //speedControl_PD();

}

/************************************************************************* 
*  函数名称：PORTB_IRQHandler
*  功能说明：PORTB的EXTI中断服务
*  参数说明：无   
*  函数返回：无
*  修改时间：2014-6-17 wuwenqi
*  备    注：
*************************************************************************/
void PORTB_IRQHandler()
{
    uint8  n;    //引脚号
    uint32 flag;
    
    while(!PORTB_ISFR);
    flag = PORTB_ISFR;
    PORTB_ISFR  = ~0;                                   //清中断标志位
    
    n = 2;                                             //场中断
    if(flag & (1 << n))                                 //PTA29触发中断
    {
        camera_vsync();
    }
#if ( CAMERA_USE_HREF == 1 )                            //使用行中断
    n = 3;
    if(flag & (1 << n))                                 //PTA28触发中断
    {
        camera_href();
    }
#endif
}

/*************************************************************************
*
*  函数名称：DMA_CH0_Handler
*  功能说明：DMA0中断服务函数
*  参数说明：无
*  函数返回：无
*
*************************************************************************/
void DMA0_IRQHandler()
{
    camera_dma();
}

