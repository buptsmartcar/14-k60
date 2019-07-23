/*
************************************************************************
*                北京邮电大学 K60 学习例程                                        
* 文件名 :[drivers_cfg.h] 
* 描  述 ：K60复用管脚配置
* 原创   ：野火嵌入式开发工作室
*设计改进：snowwolf
*  Email ：snowwolf2012@qq.com
* 说  明 ：这里定义的是针对100脚芯片，144脚会有不同
***********************************************************************
*/

#ifndef __DRIVERS_CFG_H_
#define __DRIVERS_CFG_H_

#include "gpio_cfg.h"
    //建议  PTA0~3   不要用 与Jtag冲突）
    //      PTA18~19 不要用 外部时钟   
    /**********************************  UART   ***************************************/   
    //      模块通道    端口          可选范围                          建议
    #define UART0_RX    PTB16       //PTA15、PTB16、PTD6        PTA1、  PTA1不要用（与Jtag冲突）
    #define UART0_TX    PTB17       //PTA14、PTB17、PTD7        PTA2、  PTA2不要用（与Jtag冲突）
    
    #define UART1_RX    PTC3        //PTC3、PTE1
    #define UART1_TX    PTC4        //PTC4、PTE0
    
    #define UART2_RX    PTD2        //PTD2
    #define UART2_TX    PTD3        //PTD3
    
    #define UART3_RX    PTC16       //PTB10、PTC16、PTE5
    #define UART3_TX    PTC17       //PTB11、PTC17、PTE4
    
    #define UART4_RX    PTE25       //PTC14、PTE25
    #define UART4_TX    PTE24       //PTC15、PTE24
     
    /**********************************  FTM    ***************************************/
    
    //      模块通道    端口          可选范围              建议
    #define FTM0_CH0    PTC1        //PTC1、          PTA3  PTA3不要用（与Jtag、SWD冲突）
    #define FTM0_CH1    PTC2        //PTC2、PTA4
    #define FTM0_CH2    PTC3        //PTC3、PTA5
    #define FTM0_CH3    PTC4        //PTC4、
    #define FTM0_CH4    PTD4        //PTD4、
    #define FTM0_CH5    PTD5        //PTD5、          PTA0  PTA0不要用（与Jtag、SWD冲突）
    #define FTM0_CH6    PTD6        //PTD6、          PTA1  PTA1不要用（与Jtag冲突）
    #define FTM0_CH7    PTD7        //PTD7、          PTA2  PTA2不要用（与Jtag冲突）
    
    
    //      模块通道    端口          可选范围              建议
    #define FTM1_CH0    PTA12       //PTA12、PTB0
    #define FTM1_CH1    PTA13       //PTA13、PTB1
    /*
    #define FTM1_CH2                //空
    #define FTM1_CH3                //空
    #define FTM1_CH4                //空
    #define FTM1_CH5                //空
    #define FTM1_CH6                //空
    #define FTM1_CH7                //空
    */
              
    //      模块通道    端口          可选范围              建议
    #define FTM2_CH0    PTB18       //PTB18
    #define FTM2_CH1    PTB19       //PTB19
    /*
    #define FTM2_CH2                //空
    #define FTM2_CH3                //空
    #define FTM2_CH4                //空
    #define FTM2_CH5                //空
    #define FTM2_CH6                //空
    #define FTM2_CH7                //空
    */
    
    
    
    /**********************************  I2C   ***************************************/
    
    //      模块通道    端口          可选范围              建议
    #define I2C0_SCL    PTB0        // PTB0、PTB2
    #define I2C0_SDA    PTB1        // PTB1、PTB3
    
    #define I2C1_SCL    PTC10       // PTE1、PTC10
    #define I2C1_SDA    PTC11       // PTE0、PTC11


     /*
    
    typedef enum ADC_Ch
      {
                  //SC1n[DIFF]= 0
                  //  ------ADC0------------------                       -------------ADC1------------
        DAD0=0,   //	    ADC0_DP0				                ADC1_DP0
        DAD1=1,   //	    ADC0_DP1				                ADC1_DP1
        DAD2=2,   //	    PGA0_DP					        PGA1_DP
        DAD3=3,   //	    ADC0_DP3				                ADC1_DP3
      
        //ADCx_CFG2[MUXSEL] 位决定 ADCx_SEn 通道为 a 或 b.
        AD4a=4,   //	    保留					        ADC1_SE4a   -- PTE0
        AD5a=5,   //	    保留					        ADC1_SE5a   -- PTE1
        AD6a=6,   //	    保留					        ADC1_SE6a   -- PTE2
        AD7a=7,   //	    保留					        ADC1_SE7a   -- PTE3
      
        //也是 4、5、6、7     b是硬件触发，我们一般不用
        AD4b=AD4a, //	    ADC0_SE4b	-- PTC2			                ADC1_SE4b   -- PTC8
        AD5b=AD5a, //	    ADC0_SE5b	-- PTD1			                ADC1_SE5b   -- PTC9
        AD6b=AD6a, //	    ADC0_SE6b	-- PTD5			                ADC1_SE6b   -- PTC10
        AD7b=AD7a, //	    ADC0_SE7b	-- PTD6			                ADC1_SE7b   -- PTC11
      
        AD8=8,    //	    ADC0_SE8  	-- PTB0			                ADC1_SE8    -- PTB0
        AD9=9,    //	    ADC0_SE9  	-- PTB1			                ADC1_SE9    -- PTB1
        AD10=10,  //	    ADC0_SE10 	--  无    		                ADC1_SE10   -- 无
        AD11=11,  //	    ADC0_SE11 	--  无			                ADC1_SE11   -- 无
        AD12=12,  //	    ADC0_SE12 	-- PTB2			                ADC1_SE12   -- 无
        AD13=13,  //	    ADC0_SE13 	-- PTB3			                ADC1_SE13   -- 无
        AD14=14,  //	    ADC0_SE14 	-- PTC0			                ADC1_SE14   -- PTB10
        AD15=15,  //	    ADC0_SE15 	-- PTC1			                ADC1_SE15   -- PTB11
        AD16=16,  //	    ADC0_SE16	    无  			        ADC1_SE16   无
        AD17=17,  //	    ADC0_SE17 	-- PTE24		                ADC1_SE17   -- PTA17
        AD18=18,  //	    ADC0_SE18 	-- PTE25		                VREF Output
        AD19=19,  //	    ADC0_DM0				                    ADC1_DM0
        AD20=20,  //	    ADC0_DM1				                    ADC1_DM1
        AD21=21,  //				        	                        保留
        AD22=22,  //				
        AD23=23,  //	    DAC0_OUT(12-bit) -- DAC0_OUT		        DAC1_OUT(12-bit)
        AD24=24,  //	    保留					        保留
        AD25=25,  //	    保留					        保留
        AD26=26,  //	    Temperature Sensor (S.E)		                Temperature Sensor (S.E)
        AD27=27,  //	    Bandgap (S.E)				        Bandgap (S.E)
        AD28=28,  //	    保留					        保留
        AD29=29,  //	    VREFH (S.E)				                VREFH (S.E)
        AD30=30,  //	    VREFL					        VREFL
        AD31=31   //	    禁用ADC0				                禁用ADC1
      }ADC_Ch;

    */



#endif  //_FIRE_DRIVERS_CFG_H_


