#include "include.h"
#include "control.h"
#include "isr.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "steer.h"
/**********************************************************************************
*  �������ƣ�void init()
*  ����˵������ʼ������ģ��
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2014-6-16  wuwenqi
*  ��    ע��
**********************************************************************************/	
void init()
{
  DisableInterrupts;
//������ʾ�����룬ּ������֪��init�����ʲô���������ź�ģ�������н�������д
//  //�����жϷ�����
//  set_vector_handler(PORTB_VECTORn , PORTB_IRQHandler);
//  set_vector_handler(DMA0_VECTORn , DMA0_IRQHandler);
//  set_vector_handler(PIT0_VECTORn , PIT0_IRQHandler);
//  set_vector_handler(UART0_RX_TX_VECTORn , UART0_IRQHandler);
//  //set_vector_handler(LPTMR_VECTORn , LPT_Handler);
//  
//  //�򿪴����ж�
//  uart_init(UART0,115200);
//  uart_rx_irq_en(UART0); 
//  
//  //��ʼ��������PIT�ж�
//  pit_init_ms(PIT0,20); //pit��ʱ,20msһ��
//  enable_irq(PIT0_IRQn);
//
//  //�����ʼ����PTC1,PTC2Ƶ�ʣ�16kHz��50%ռ�ձ�
//  motor_init();
//  
//  //�����ʼ��
//  steer_init();
//  
//  //��������ʼ��
//  //lptmr_pulse_init(LPT0_ALT2,LIN_COUT,LPT_Rising);
//  ftm_quad_init(FTM2);
//  //�����ж����ȼ�
//  set_irq_priority(PORTB_IRQn,0); //exti_PTB������ȼ�0�����ڿ���DMA�ɼ�ͼ��
//  set_irq_priority(PIT0_IRQn ,1); // PIT0�ڶ����ȼ�1�������ٶȺͷ�����ƣ�
//  set_irq_priority(DMA0_IRQn,2); // UART0�������ȼ���û����¶���
//  set_irq_priority(UART0_RX_TX_IRQn,3); // UART0�������ȼ���û����¶���
//  //������ʼ��
//  gpio_init (PTE0, GPI,0);
//  gpio_init (PTE1, GPI,0);
//  gpio_init (PTE2, GPI,0);
//  gpio_init (PTE3, GPI,0);
//
//  //����ͷ��ʼ��
//  camera_init(Picbuff);
//  //��ʾ��
//  //LCD_Init();

  EnableInterrupts;
}
