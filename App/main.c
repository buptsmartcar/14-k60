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
 *  @brief      main����forӥ������ͷ�ɼ�
���main����ֻ����ʾ��һ����ôʹ��ӥ������ͷ�ɼ�����Ҫʹ�����main����(Ĭ�Ͼ��ǲ�ʹ�ã�ͨ��Ԥ����ָ��#if 0�ر���)
 */
//u8 showPhotoFlag=0;
//int main(void)
//{
//    init();        
//    while(1)
//    {      
//        camera_get_img_halffps();//halffps��ָֻ��ӥ�۵�74֡ģʽ����Ҫʵ��148֡������ʵ��˫��������    
//        img_extract(img_origin,Picbuff,CAMERA_SIZE); //��Picbuff��ѹ����ά����img,ӥ��Ĭ�����ݸ�ʽ��ѹ���˵ģ������ѹ�ɻҶ�ͼ��      
//        /*----------ͼ����----------*/
//        image_process();
//        /*----------���Ʋ�������------*/
//        calc_and_ctrl();        
//        /*---------����ͼ����λ�� ---------*/
//        if(showPhotoFlag){
//            vcan_sendimg(img, sizeof(img));
//        }            
//    }
//}


#elif 1
/*
 *  @brief      ����main����,��ʹ�����main����,�Լ���д����
 */
int main(void){
  init();
  while(1){
    //TODO
  }
}
#endif




