/*
************************************************************************
*                �����ʵ��ѧ K60 ѧϰ����                                        
* �ļ��� :[drivers_cfg.h] 
* ��  �� ��K60���ùܽ�����
* ԭ��   ��Ұ��Ƕ��ʽ����������
*��ƸĽ���snowwolf
*  Email ��snowwolf2012@qq.com
* ˵  �� �����ﶨ��������100��оƬ��144�Ż��в�ͬ
***********************************************************************
*/

#ifndef __DRIVERS_CFG_H_
#define __DRIVERS_CFG_H_

#include "gpio_cfg.h"
    //����  PTA0~3   ��Ҫ�� ��Jtag��ͻ��
    //      PTA18~19 ��Ҫ�� �ⲿʱ��   
    /**********************************  UART   ***************************************/   
    //      ģ��ͨ��    �˿�          ��ѡ��Χ                          ����
    #define UART0_RX    PTB16       //PTA15��PTB16��PTD6        PTA1��  PTA1��Ҫ�ã���Jtag��ͻ��
    #define UART0_TX    PTB17       //PTA14��PTB17��PTD7        PTA2��  PTA2��Ҫ�ã���Jtag��ͻ��
    
    #define UART1_RX    PTC3        //PTC3��PTE1
    #define UART1_TX    PTC4        //PTC4��PTE0
    
    #define UART2_RX    PTD2        //PTD2
    #define UART2_TX    PTD3        //PTD3
    
    #define UART3_RX    PTC16       //PTB10��PTC16��PTE5
    #define UART3_TX    PTC17       //PTB11��PTC17��PTE4
    
    #define UART4_RX    PTE25       //PTC14��PTE25
    #define UART4_TX    PTE24       //PTC15��PTE24
     
    /**********************************  FTM    ***************************************/
    
    //      ģ��ͨ��    �˿�          ��ѡ��Χ              ����
    #define FTM0_CH0    PTC1        //PTC1��          PTA3  PTA3��Ҫ�ã���Jtag��SWD��ͻ��
    #define FTM0_CH1    PTC2        //PTC2��PTA4
    #define FTM0_CH2    PTC3        //PTC3��PTA5
    #define FTM0_CH3    PTC4        //PTC4��
    #define FTM0_CH4    PTD4        //PTD4��
    #define FTM0_CH5    PTD5        //PTD5��          PTA0  PTA0��Ҫ�ã���Jtag��SWD��ͻ��
    #define FTM0_CH6    PTD6        //PTD6��          PTA1  PTA1��Ҫ�ã���Jtag��ͻ��
    #define FTM0_CH7    PTD7        //PTD7��          PTA2  PTA2��Ҫ�ã���Jtag��ͻ��
    
    
    //      ģ��ͨ��    �˿�          ��ѡ��Χ              ����
    #define FTM1_CH0    PTA12       //PTA12��PTB0
    #define FTM1_CH1    PTA13       //PTA13��PTB1
    /*
    #define FTM1_CH2                //��
    #define FTM1_CH3                //��
    #define FTM1_CH4                //��
    #define FTM1_CH5                //��
    #define FTM1_CH6                //��
    #define FTM1_CH7                //��
    */
              
    //      ģ��ͨ��    �˿�          ��ѡ��Χ              ����
    #define FTM2_CH0    PTB18       //PTB18
    #define FTM2_CH1    PTB19       //PTB19
    /*
    #define FTM2_CH2                //��
    #define FTM2_CH3                //��
    #define FTM2_CH4                //��
    #define FTM2_CH5                //��
    #define FTM2_CH6                //��
    #define FTM2_CH7                //��
    */
    
    
    
    /**********************************  I2C   ***************************************/
    
    //      ģ��ͨ��    �˿�          ��ѡ��Χ              ����
    #define I2C0_SCL    PTB0        // PTB0��PTB2
    #define I2C0_SDA    PTB1        // PTB1��PTB3
    
    #define I2C1_SCL    PTC10       // PTE1��PTC10
    #define I2C1_SDA    PTC11       // PTE0��PTC11


     /*
    
    typedef enum ADC_Ch
      {
                  //SC1n[DIFF]= 0
                  //  ------ADC0------------------                       -------------ADC1------------
        DAD0=0,   //	    ADC0_DP0				                ADC1_DP0
        DAD1=1,   //	    ADC0_DP1				                ADC1_DP1
        DAD2=2,   //	    PGA0_DP					        PGA1_DP
        DAD3=3,   //	    ADC0_DP3				                ADC1_DP3
      
        //ADCx_CFG2[MUXSEL] λ���� ADCx_SEn ͨ��Ϊ a �� b.
        AD4a=4,   //	    ����					        ADC1_SE4a   -- PTE0
        AD5a=5,   //	    ����					        ADC1_SE5a   -- PTE1
        AD6a=6,   //	    ����					        ADC1_SE6a   -- PTE2
        AD7a=7,   //	    ����					        ADC1_SE7a   -- PTE3
      
        //Ҳ�� 4��5��6��7     b��Ӳ������������һ�㲻��
        AD4b=AD4a, //	    ADC0_SE4b	-- PTC2			                ADC1_SE4b   -- PTC8
        AD5b=AD5a, //	    ADC0_SE5b	-- PTD1			                ADC1_SE5b   -- PTC9
        AD6b=AD6a, //	    ADC0_SE6b	-- PTD5			                ADC1_SE6b   -- PTC10
        AD7b=AD7a, //	    ADC0_SE7b	-- PTD6			                ADC1_SE7b   -- PTC11
      
        AD8=8,    //	    ADC0_SE8  	-- PTB0			                ADC1_SE8    -- PTB0
        AD9=9,    //	    ADC0_SE9  	-- PTB1			                ADC1_SE9    -- PTB1
        AD10=10,  //	    ADC0_SE10 	--  ��    		                ADC1_SE10   -- ��
        AD11=11,  //	    ADC0_SE11 	--  ��			                ADC1_SE11   -- ��
        AD12=12,  //	    ADC0_SE12 	-- PTB2			                ADC1_SE12   -- ��
        AD13=13,  //	    ADC0_SE13 	-- PTB3			                ADC1_SE13   -- ��
        AD14=14,  //	    ADC0_SE14 	-- PTC0			                ADC1_SE14   -- PTB10
        AD15=15,  //	    ADC0_SE15 	-- PTC1			                ADC1_SE15   -- PTB11
        AD16=16,  //	    ADC0_SE16	    ��  			        ADC1_SE16   ��
        AD17=17,  //	    ADC0_SE17 	-- PTE24		                ADC1_SE17   -- PTA17
        AD18=18,  //	    ADC0_SE18 	-- PTE25		                VREF Output
        AD19=19,  //	    ADC0_DM0				                    ADC1_DM0
        AD20=20,  //	    ADC0_DM1				                    ADC1_DM1
        AD21=21,  //				        	                        ����
        AD22=22,  //				
        AD23=23,  //	    DAC0_OUT(12-bit) -- DAC0_OUT		        DAC1_OUT(12-bit)
        AD24=24,  //	    ����					        ����
        AD25=25,  //	    ����					        ����
        AD26=26,  //	    Temperature Sensor (S.E)		                Temperature Sensor (S.E)
        AD27=27,  //	    Bandgap (S.E)				        Bandgap (S.E)
        AD28=28,  //	    ����					        ����
        AD29=29,  //	    VREFH (S.E)				                VREFH (S.E)
        AD30=30,  //	    VREFL					        VREFL
        AD31=31   //	    ����ADC0				                ����ADC1
      }ADC_Ch;

    */



#endif  //_FIRE_DRIVERS_CFG_H_


