#ifndef __MENU_H__
#define __MENU_H__

#include "LQ12864.h"
#include "global.h"
#include "common.h"
#include "MK60_port.h"
#include "MK60_gpio.h"

#define ITEMNUM 7
#define PRESETNUM 5

typedef enum myorder {NONE,PREITEM,NEXTITEM,INC,DEC} ORDER;
typedef enum mymenuitem {STEER_D,STEER_P,TURNSPEED,SPEED,SHOWIMG,PRESET,EXIT} ITEM;


//≥ı º√¸¡Ó
extern ORDER order;
//≥ı º≤Àµ•
extern ITEM  item;


void menu();
void keyQuery();
void keyProcess();
void updateMenu();
void indexAnimation();
void preSet(const u8 pre);
#endif

