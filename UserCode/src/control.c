#include "include.h"
#include "control.h"
#include "isr.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "steer.h"
/**********************************************************************************
*  函数名称：void init()
*  功能说明：初始化各个模块
*  参数说明：无
*  函数返回：无
*  修改时间：2014-6-16  wuwenqi
*  备    注：
**********************************************************************************/	
void init()
{
  DisableInterrupts;
//下面是示例代码，旨在让你知道init里该做什么。具体引脚和模块请自行进函数改写
//  //配置中断服务函数
//  set_vector_handler(PORTB_VECTORn , PORTB_IRQHandler);
//  set_vector_handler(DMA0_VECTORn , DMA0_IRQHandler);
//  set_vector_handler(PIT0_VECTORn , PIT0_IRQHandler);
//  set_vector_handler(UART0_RX_TX_VECTORn , UART0_IRQHandler);
//  //set_vector_handler(LPTMR_VECTORn , LPT_Handler);
//  
//  //打开串口中断
//  uart_init(UART0,115200);
//  uart_rx_irq_en(UART0); 
//  
//  //初始化并开启PIT中断
//  pit_init_ms(PIT0,20); //pit定时,20ms一次
//  enable_irq(PIT0_IRQn);
//
//  //电机初始化，PTC1,PTC2频率：16kHz，50%占空比
//  motor_init();
//  
//  //舵机初始化
//  steer_init();
//  
//  //编码器初始化
//  //lptmr_pulse_init(LPT0_ALT2,LIN_COUT,LPT_Rising);
//  ftm_quad_init(FTM2);
//  //调整中断优先级
//  set_irq_priority(PORTB_IRQn,0); //exti_PTB最高优先级0，用于控制DMA采集图像；
//  set_irq_priority(PIT0_IRQn ,1); // PIT0第二优先级1，用于速度和方向控制；
//  set_irq_priority(DMA0_IRQn,2); // UART0第三优先级，没你的事儿。
//  set_irq_priority(UART0_RX_TX_IRQn,3); // UART0第三优先级，没你的事儿。
//  //按键初始化
//  gpio_init (PTE0, GPI,0);
//  gpio_init (PTE1, GPI,0);
//  gpio_init (PTE2, GPI,0);
//  gpio_init (PTE3, GPI,0);
//
//  //摄像头初始化
//  camera_init(Picbuff);
//  //显示屏
//  //LCD_Init();

  EnableInterrupts;
}
