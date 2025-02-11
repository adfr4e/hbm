#ifndef __HBM32G003_IWDT_H__
#define __HBM32G003_IWDT_H__

#include "HBM32G003.h"


typedef enum
{ 
	RstEn_DISABLE =  0x00,    // ��ֹ��λ
	RstEn_ENABLE =   0x01     // ʹ�ܸ�λ
} RstEn_TypeDef;


typedef struct
{                                               
	RstEn_TypeDef     RstEn;       //ʹ�ܸ�λ
	uint32_t          Load;        //װ��ֵ
} IWDT_InitTypeDef;


//����IWDT��λѡ��
#define IS_IWDT_RST(IWDT_RST)        (((IWDT_RST) == RstEn_DISABLE) || ((IWDT_RST) == RstEn_ENABLE))

//����IWDTװ��ֵ
#define IS_IWDT_LOAD(IWDT_LOAD)      ((IWDT_LOAD) != 0)


void IWDT_Init(IWDT_InitTypeDef * IWDT_InitStruct);  //IWDT��ʼ��
void IWDT_Start(void);                               //����IWDT
void IWDT_Stop(void);                                //ֹͣIWDT
void IWDT_FEED(void);                                //IWDTι��
uint8_t IWDT_INTStat(void);                          //��ѯIWDT�ж�״̬
void IWDT_INTClr(void);                              //���IWDT�ж�״̬


#endif //__HBM32G003_IWDT_H__
