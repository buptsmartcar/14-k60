#include "menu.h"
#include "VCAN_SCCB.h"
#include "img_control.h"

#include "VCAN_camera.h"
//��ʼ����
ORDER order=NONE;
//��ʼ�˵�
ITEM  item= SHOWIMG;

uint8 startFlag=0;
s8 preset=2;

void menu(){
    startFlag=0;
    preSet(preset);
    //����
#if MENU_ANIMATION
    indexAnimation();
#endif
    //LCD_DLY_ms(1000);
    while(!startFlag){
        keyQuery();
        keyProcess();
        updateMenu();
        LCD_DLY_ms(200);
    }
    LCD_CLS();
}

void keyQuery(){
    uint8 num=0;
    //���β�ѯE1~E4������״̬
    uint8 temp=2;
    temp=gpio_get(PTE0);
    if(temp==0) {
        
        num=4;
    }
    temp=gpio_get(PTE1);
    if(temp==0) {
        
        num=3;
    }
    temp=gpio_get(PTE2);
    if(temp==0) {
        
        num=1;
    }
    temp=gpio_get(PTE3);
    if(temp==0) {
        
        num=2;
    }
    //���ݰ���ѡ������
    
    switch(num){
    case 4:
        order=PREITEM;
        break;
    case 3:
        order=NEXTITEM;
        break;
    case 2:
        order=INC;
        break;
    case 1:
        order=DEC;
        break;
    default:
        order=NONE;
        break;
    }
}

void preSet(const u8 pre){
    switch(pre){
    case 0:
      normal_speed=260;
      normal_turn_speed=260;
    break;
    case 1:
      normal_speed=300;
      normal_turn_speed=260;
    break;
    case 2:
      normal_speed=350;
      normal_turn_speed=280;
        break;
    case 3:
      normal_speed=400;
      normal_turn_speed=300;
        break;
    case 4:
      normal_speed=450;
      normal_turn_speed=300;
        break;
    }
}
//���������л��˵���
void keyProcess(){
    u8 temp;
    switch (order) {
    case NONE:
        break;
    case PREITEM:
        if ((int)item == 0) item =(ITEM)(ITEMNUM-1);
        else item--;
        break;
    case NEXTITEM:
        item++;
        item = (ITEM)(item % ITEMNUM);
        break;
    case INC:
        switch(item){
        case TURNSPEED:      normal_turn_speed+=10;break;
        case SPEED:       normal_speed+=10;break;
        case EXIT:startFlag=1; stop_flag=0;break;
        case SHOWIMG:
            SCCB_ReadByte( &temp, 1, OV7725_CNST);
            temp++;
            SCCB_WriteByte(OV7725_CNST,temp);
            break;
        case STEER_P:anglp1++;break;
        case STEER_D:angld++;break;
        case PRESET:++preset;preset=preset%PRESETNUM;preSet(preset);break;
        default:break;
        }
        break;
    case DEC:
        switch(item){
        case TURNSPEED:   normal_turn_speed-=10;break;
        
        case SPEED:       normal_speed-=10;break;
        case EXIT:startFlag=1;    stop_flag=0;break;
        case SHOWIMG:
            SCCB_ReadByte( &temp, 1, OV7725_CNST);
            temp--;
            SCCB_WriteByte(OV7725_CNST,temp);
            break;
        case STEER_P:anglp1--;break;
        case STEER_D:angld--;break;
        case PRESET:if(--preset<0){preset=PRESETNUM-1;}preSet(preset);break;
        default:break;
        }
        break;
    default:
        break;
    }
}

void updateMenu(){
    LCD_CLS();
    //�����ȴ�������
    u8 tmp[10]={0};
    switch(item){
    case SPEED:
        LCD_Print(0,0," Normal Speed");
        LCD_Print(0,2,"----------------");
        sprintf((char*)tmp,"%d",normal_speed);
        LCD_Print(80,4,tmp);
        break;
    case TURNSPEED:
        LCD_Print(0,0," Turn Speed");
        LCD_Print(0,2,"----------------");
        sprintf((char*)tmp,"%d",normal_turn_speed);
        LCD_Print(0,4,"turnspeed: ");
        LCD_Print(80,4,tmp);
        break;
    case EXIT:
        LCD_Print(0,0,"   Exit  Menu");
        LCD_Print(0,2,"----------------");
        
        break;
    case SHOWIMG:
#if OV7725_FULLFPS
        camera_get_img_fullfps();  //ѡ�񻺳���
        
        if(skipFlag){break;}
        PORTB_ISFR = ~0;                        //д1���жϱ�־λ(����ģ���Ȼ�ص���һ���жϾ����ϴ����ж�)
        enable_irq(PORTB_IRQn);                         //����PTA���ж�,��ʼ�ɼ�,���жϵ���ʱ�ر�  
        //LCD_CLS();
        Draw_BMP_fullfps();
        if(!imgGetIndex){
            curImg=1;          
        }
        else{
            curImg=0;     
        }
        //������ϣ�����Ӧ������flag��0
        if(curImg){
            buffer1_flag=0;
        }
        else{
            buffer_flag=0;
        }
#else
        camera_get_img_halffps();
        Draw_BMP_halffps();
#endif
        break;
    case STEER_P:
     LCD_Print(0,0," STEER_P");
        LCD_Print(0,2,"----------------");
        sprintf((char*)tmp,"%d",anglp1);
        LCD_Print(0,4,"steer_p1: ");
        LCD_Print(80,4,tmp);
        break;
    case STEER_D:
        LCD_Print(0,0," STEER_D");
        LCD_Print(0,2,"----------------");
        sprintf((char*)tmp,"%d",angld);
        LCD_Print(0,4,"steer_d: ");
        LCD_Print(80,4,tmp);
        break;
    case PRESET:
        LCD_Print(0,0,"Preset:");
        sprintf((char*)tmp,"%d",preset);
        LCD_Print(56,0,tmp);
        LCD_Print(0,2,"================");
        //��ӡ�ٶ�
        sprintf((char*)tmp,"%d",normal_speed);
        LCD_Print(8,4,tmp);
        sprintf((char*)tmp,"%d",normal_turn_speed);
        LCD_Print(72,4,tmp);
        break;
    default:break;
    }
}
#if MENU_ANIMATION
void indexAnimation(){
    LCD_P16x16Str(0,4,"��");
    LCD_DLY_ms(100);
    LCD_P16x16Str(0,4,"����");
    LCD_DLY_ms(100);
    LCD_P16x16Str(0,4,"�ܳ���");
    LCD_DLY_ms(100);
    LCD_P16x16Str(0,4,"���ܳ���");
    LCD_DLY_ms(100);
    LCD_P16x16Str(0,4,"�����ܳ���");
    LCD_DLY_ms(100);
    LCD_P16x16Str(0,4,"�տ����ܳ���");
    LCD_DLY_ms(100);
    LCD_P16x16Str(0,4,"�տտ����ܳ���");
    LCD_DLY_ms(100);
    LCD_P16x16Str(0,4,"�տտտ����ܳ���");
    LCD_DLY_ms(100);
    Draw_Logo();
    LCD_P16x16Str(0,0,"��");
    LCD_DLY_ms(100);
    LCD_P16x16Str(0,0,"����");
    LCD_DLY_ms(100);
    LCD_P16x16Str(0,2,"��");
    LCD_DLY_ms(100);
    LCD_P16x16Str(0,2,"����");
    LCD_DLY_ms(100);
    LCD_P16x16Str(0,2,"ʮ����");
    LCD_DLY_ms(100);
    LCD_P16x16Str(0,2,"��ʮ����");
    LCD_DLY_ms(100);
    LCD_P16x16Str(0,2,"�յ�ʮ����");
    LCD_DLY_ms(100);
    LCD_Print(64,6,"  v0.1");
}
#endif