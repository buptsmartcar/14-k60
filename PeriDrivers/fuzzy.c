
/*
*       用于舵机模糊控制,这算法代码又丑又恶心不想再改第二遍
*       2018-5-8 09:51:02
*       lw
*       参考:https://wenku.baidu.com/view/983efff25022aaea998f0fb9.html
*           https://blog.csdn.net/weixin_36340979/article/details/79168052
*/
#include "include.h"
#include "global.h"
#include "fuzzy.h"
//--------------------------------------定义数据结构-------------------------------------------
//偏差，对于e:       0-5 0 5-10小 10-15中 15以上 大
//      对于de:      0-3   3-6    6-9     9以上
//输入量有两个，本次偏差e，以及偏差变化量de
//e属于-40,40.de一样
//对应每个输入量，从负到正，分为 
//e:  LL,LM,LS,CE,RS,RM,RL
//de: NL,NM,NS,ZO,PS,PM,PL
typedef enum fuzzy_input_e{LL=0,LM,LS,CE,RS,RM,RL,NONE} FuzzyInput_e;
typedef enum fuzzy_input_de{NL=0,NM,NS,ZO,PS,PM,PL,NONE} FuzzyInput_de;
typedef enum fuzzy_output {LL=0,LM,LS,CE,RS,RM,RL,NONE}FuzzyOutput_enum;
typedef union fuzzy_input_union{
  FuzzyInput_e e;
  FuzzyInput_de de;
} FuzzyInput_Union;
//每个输入项
typedef struct fuzzy_input
{
  int type;//0 for e,1 for de
  FuzzyInput_Union value;
  float membership;
} FuzzyInput ;
//每个输出项
typedef struct fuzzy_output
{
  FuzzyOutput_enum value;
  float membership;
}FuzzyOuput;

/*----------------------------------------定义常量表-------------------------------------------*/
//下面针对e和de的七个层次指定各自的隶属函数，每个隶属函数的参数由D和B再加中心点计算得出
//隶属函数采用三角形，左中右三个点分别为a,b,c

//中心点
s8 b_e[7]={-3*FUZZY_D_e,-2*FUZZY_D_e,-FUZZY_D_e,0,FUZZY_D_e,2*FUZZY_D_e,3*FUZZY_D_e};
//左
s8 a_e[7]={     -3*FUZZY_D_e-FUZZY_D_e*FUZZY_B_e,-2*FUZZY_D_e-FUZZY_D_e*FUZZY_B_e,-FUZZY_D_e-FUZZY_D_e*FUZZY_B_e,
                0-FUZZY_D_e*FUZZY_B_e,FUZZY_D_e-FUZZY_D_e*FUZZY_B_e,2*FUZZY_D_e-FUZZY_D_e*FUZZY_B_e,
                3*FUZZY_D_e-FUZZY_D_e*FUZZY_B_e
          };
//右
s8 c_e[7]={     -3*FUZZY_D_e+FUZZY_D_e*FUZZY_B_e,-2*FUZZY_D_e+FUZZY_D_e*FUZZY_B_e,-FUZZY_D_e+FUZZY_D_e*FUZZY_B_e,
                0+FUZZY_D_e*FUZZY_B_e,FUZZY_D_e+FUZZY_D_e*FUZZY_B_e,2*FUZZY_D_e+FUZZY_D_e*FUZZY_B_e,
                3*FUZZY_D_e+FUZZY_D_e*FUZZY_B_e
          };


s8 b_de[7]={-3*FUZZY_D_de,-2*FUZZY_D_de,-FUZZY_D_de,0,FUZZY_D_de,2*FUZZY_D_de,3*FUZZY_D_de};
//左
s8 a_de[7]={    -3*FUZZY_D_de-FUZZY_D_de*FUZZY_B_de,-2*FUZZY_D_de-FUZZY_D_de*FUZZY_B_de,-FUZZY_D_de-FUZZY_D_de*FUZZY_B_de,
                0-FUZZY_D_de*FUZZY_B_de,FUZZY_D_de-FUZZY_D_de*FUZZY_B_de,2*FUZZY_D_de-FUZZY_D_de*FUZZY_B_de,
                3*FUZZY_D_de-FUZZY_D_de*FUZZY_B_de
          };
//右
s8 c_de[7]={    -3*FUZZY_D_de+FUZZY_D_de*FUZZY_B_de,-2*FUZZY_D_de+FUZZY_D_de*FUZZY_B_de,-FUZZY_D_de+FUZZY_D_de*FUZZY_B_de,
                0+FUZZY_D_de*FUZZY_B_de,FUZZY_D_de+FUZZY_D_de*FUZZY_B_de,2*FUZZY_D_de+FUZZY_D_de*FUZZY_B_de,
                3*FUZZY_D_de+FUZZY_D_de*FUZZY_B_de
          };
//推理规则表
FuzzyOuput FuzzyTable[][7]={
  {RL,RL,RM,RM,RS,CE,CE},
  {RL,RL,RM,RM,RS,CE,CE},
  {RL,RL,RM,RS,CE,LM,LM},
  {RL,RL,RS,CE,LS,LL,LL},
  {RM,RM,CE,LS,LM,LL,LL},
  {CE,CE,LS,LM,LM,LL,LL},
  {CE,CE,LS,LM,LM,LL,LL}
};
//output所对应的pwm
u16 output_pwm[]={(STEER_LEFT-STEER_MIDDLE),(STEER_LEFT-STEER_MIDDLE)/2,(STEER_LEFT-STEER_MIDDLE)/3,
                  0,
                  (STEER_MIDDLE-STEER_RIGHT)/3,(STEER_MIDDLE-STEER_RIGHT)/2,(STEER_MIDDLE-STEER_RIGHT)};
/*-------------下面是计算隶属度函数，即三角形函数-----------------------
*函数形式为(x-a)/(b-a),a<=x<=b
*          (x-c)/(b-c),b<x<=c
*          0          ,else    
*-------------------------------------------------------------------*/
void calcMembership(FuzzyInput *input,s8 x){
  //判断是哪个自变量在哪一点处的隶属函数
  if(!input->type){//e的函数
    if(input->value.e==NONE){return;}
    //判断是否是最边缘两个，如果是单独处理
    if(input->value.e==LL){
      //右侧三角，左侧平
      if(x>b_e[input->value.e]&&x<=c_e[input->value.e]){
        input->membership=(float)(x-c_e[input->value.e])/(b_e[input->value.e]-c_e[input->value.e]);
      }
      else if(x<=b_e[input->value.e]){input->membership=1;}
      else {input->membership=0;}
    }
    else if(input->value.e==RL){
       //左侧三角，右侧平
      if(x>=a_e[input->value.e]&&x<b_e[input->value.e]){
        input->membership=(float)(x-a_e[input->value.e])/(b_e[input->value.e]-a_e[input->value.e]);
      }
      else if(x>=b_e[input->value.e]){input->membership=1;}
      else {input->membership=0;}
    }
    else{
      if(x>=a_e[input->value.e]&&x<=b_e[input->value.e]){
        input->membership=(float)(x-a_e[input->value.e])/(b_e[input->value.e]-a_e[input->value.e]);
      }
      else if(x>b_e[input->value.e]&&x<=c_e[input->value.e]){
        input->membership=(float)(x-c_e[input->value.e])/(b_e[input->value.e]-c_e[input->value.e]);
      }
      else{
        input->membership=0;
      }
    }
  }
  else{//de的 函数
    if(input->value.de==NONE){return;}
    //判断是否是最边缘两个，如果是单独处理
    if(input->value.de==NL){
      //右侧三角，左侧平
      if(x>b_de[input->value.de]&&x<=c_de[input->value.de]){
        input->membership=(float)(x-c_de[input->value.de])/(b_de[input->value.de]-c_de[input->value.de]);
      }
      else if(x<=b_de[input->value.de]){input->membership=1;}
      else {input->membership=0;}
    }
    else if(input->value.de==PL){
      //左侧三角，右侧平
      if(x>=a_de[input->value.de]&&x<b_de[input->value.de]){
        input->membership=(float)(x-a_de[input->value.de])/(b_de[input->value.de]-a_de[input->value.de]);
      }
      else if(x>=b_de[input->value.de]){input->membership=1;}
      else {input->membership=0;}
    }
    else{
      if(x>=a_de[input->value.de]&&x<=b_de[input->value.de]){
        input->membership=(float)(x-a_de[input->value.de])/(b_de[input->value.de]-a_de[input->value.de]);
      }
      else if(x>b_de[input->value.de]&&x<=c_de[input->value.de]){
        input->membership=(float)(x-c_de[input->value.de])/(b_de[input->value.de]-c_de[input->value.de]);
      }
      else{
        input->membership=0;
      }
    }
  }
}
/*---------------------------------------------------------------------------------------
**  @func_name     :  void getFuzzyInput(s16 e,s16 de,FuzzyInput *result_e,FuzzyInput *result_de)  
**  @last_edit     :  2018-5-12 15:28:01
**  @by            :  lw
**  @function:
**          对于任意一个偏差e，在某一点处可能有一个或者有两个隶属度函数重合
            根据隶属度个数于模糊表中找出输出模糊量，可能对应一个、两个、或者四个输出模糊量
            对输出模糊量采用求重心法求出重心，即把隶属度作为权值加权平均，其中所有隶属度∑必为1
            再由所求出的重心求出精确的控制量


            该函数用于根据输入e和de计算出二者所述的摄入量模糊子集以及相关隶属度


**  @params:
**          输入 e-偏差 de偏差的变化
            输出 *result_e保存e所对应的模糊量及其隶属度 *result_de de所对应模糊量及其隶属度
**--------------------------------------------------------------------------------------*/
void getFuzzyInput(s16 e,s16 de,FuzzyInput *result_e,FuzzyInput *result_de){
  //处理e
  FuzzyInput *ptre=result_e,*ptrde=result_de;
  //1.根据e找到可能存在的区间
  s16 i,j;
  for(i=0;i<7;i++){
    if(e<b_e[i]){break;}
  }
  //2.根据所在区间选择两个对应的模糊输入量存入对应的result数组中,准备计算隶属度
  (ptre++)->value.type=0;
  ptre->value.type=0;
  ptre=result_e;
  if(i==0){
    (ptre++)->value.e=LL;
    ptre->value.e=NONE;
  }
  else if(i==7){
    (ptre++)->value.e=RL;
    ptre->value.e=NONE;
  }
  else{
    (ptre++)->value.e=(FuzzyInput_e)(LL+i-1);
    ptre->value.e=(FuzzyInput_e)(LL+i);
  }
  //3.计算隶属度,存入对应的m数组中
  ptre=result_e;
  for(i=0;i<2;i++){
    calcMembership(ptr+i,e);
  }
  
   //处理de
  //1.根据de找到可能存在的区间
  //s16 i,j;
  for(i=0;i<7;i++){
    if(de<b_de[i]){break;}
  }
  //2.根据所在区间选择两个对应的模糊输入量存入对应的result数组中,准备计算隶属度
  (ptrde++)->value.type=1;
  ptrde->value.type=1;
  ptrde=result_de;
  if(i==0){
    (ptrde++)->value.de=NL;
    ptrde->value.de=NONE;
  }
  else if(i==7){
    (ptrde++)->value.de=PL;
    ptrde->value.de=NONE;
  }
  else{
    (ptrde++)->value.de=(FuzzyInput_de)(NL+i-1);
    ptrde->value.de=(FuzzyInput_de)(NL+i);
  }
  //3.计算隶属度,存入对应的m数组中
  ptrde=result_de;
  for(i=0;i<2;i++){
    calcMembership(ptrde+i,de);
  }
}

/*---------------------------------------------------------------------------------------
**  @func_name      :  getFuzzyOutputPwm
**  @last_edit      :  2018-5-12 14:25:43   
**  @by             :  lw
**  @function:
**    查表解模糊并用重心法求出相应的PWM脉宽
**    obtain the fuzzy output result by looking up the fuzzy table
**  @params:
**  
**--------------------------------------------------------------------------------------*/

float getFuzzyOutputPwm(FuzzyInput *result_e,FuzzyInput *result_de,FuzzyOutput *output){
  int ptr_output=0;
  float result;
  //每次拿出一个结果，乘以其隶属度加到结果上去
  int i,j;
  for(i=0;i<2;i++){
    if(*(result_e+i).value.e==NONE){continue;}
    for(j=0;j<2;j++){
      if(*(result_de+i).value.de==NONE){continue;}
        //找出对应于该组e和de的output
        FuzzyOutput_enum temp=FuzzyTable[de][e];
        result+=output_pwm[temp]*(*(result_e+i).membership)*(*(result_de+j).membership);
    }
  }

}