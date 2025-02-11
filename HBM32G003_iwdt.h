#ifndef __HBM32G003_IWDT_H__
#define __HBM32G003_IWDT_H__

#include "HBM32G003.h"


typedef enum
{ 
	RstEn_DISABLE =  0x00,    // 禁止复位
	RstEn_ENABLE =   0x01     // 使能复位
} RstEn_TypeDef;


typedef struct
{                                               
	RstEn_TypeDef     RstEn;       //使能复位
	uint32_t          Load;        //装载值
} IWDT_InitTypeDef;


//断言IWDT复位选择
#define IS_IWDT_RST(IWDT_RST)        (((IWDT_RST) == RstEn_DISABLE) || ((IWDT_RST) == RstEn_ENABLE))

//断言IWDT装载值
#define IS_IWDT_LOAD(IWDT_LOAD)      ((IWDT_LOAD) != 0)


void IWDT_Init(IWDT_InitTypeDef * IWDT_InitStruct);  //IWDT初始化
void IWDT_Start(void);                               //启动IWDT
void IWDT_Stop(void);                                //停止IWDT
void IWDT_FEED(void);                                //IWDT喂狗
uint8_t IWDT_INTStat(void);                          //查询IWDT中断状态
void IWDT_INTClr(void);                              //清除IWDT中断状态


#endif //__HBM32G003_IWDT_H__
