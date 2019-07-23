/*===========================================
* @Brief:       BUPT smartcar code template for MK60
* @Author:      Wei Lee
* @Date:        2019-07-23
=============================================*/

#include "common.h"
#include "include.h"
#include "VCAN_OV7725_Eagle.h"


#if 0
/*
 *  @brief      main函数for鹰眼摄像头采集
这个main函数只是演示了一下怎么使用鹰眼摄像头采集，不要使用这个main函数(默认就是不使用，通过预编译指令#if 0关闭了)
 */
//u8 showPhotoFlag=0;
//int main(void)
//{
//    init();        
//    while(1)
//    {      
//        camera_get_img_halffps();//halffps是指只用鹰眼的74帧模式，若要实现148帧请自行实现双缓冲区法    
//        img_extract(img_origin,Picbuff,CAMERA_SIZE); //将Picbuff解压到二维数组img,鹰眼默认数据格式是压缩了的，这里解压成灰度图像      
//        /*----------图像处理----------*/
//        image_process();
//        /*----------控制参数计算------*/
//        calc_and_ctrl();        
//        /*---------发送图像到上位机 ---------*/
//        if(showPhotoFlag){
//            vcan_sendimg(img, sizeof(img));
//        }            
//    }
//}


#elif 1
/*
 *  @brief      纯净main函数,请使用这个main函数,自己编写代码
 */
int main(void){
  init();
  while(1){
    //TODO
  }
}
#endif




