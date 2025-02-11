#ifndef __HBM32G003_TIMERPLUS_H__
#define __HBM32G003_TIMERPLUS_H__

#include "HBM32G003.h"

typedef enum
{
	HALL_0  = 0x01,
	HALL_1  = 0x02,
	HALL_2  = 0x04,
} TIMPLUS_HallTypeDef;

typedef enum
{
	TIMPLUS_LOW  = 0x01,
	TIMPLUS_HIGH = 0x02,
} TIMPLUS_TypeTypeDef;

typedef enum
{
	TIMER_MODE = 0x00,
	COUNT_MODE = 0x01,
	INCAP_MODE = 0x02,
	HALL_MODE  = 0x03,
} TIMPLUS_ModeTypeDef;

typedef enum
{
	SYSCLK_DIV = 0x00,
	CNTSRC0    = 0x01,
	CNTSRC1    = 0x02,
} TIMPLUS_ClkSelTypeDef;


typedef enum
{
	TIMPLUS_IN0 = 0x00,
	TIMPLUS_IN1 = 0x01,
} TIMPLUS_ExtSelTypeDef;

typedef enum
{
	EXTLEVEL_RISE = 0x00,
	EXTLEVEL_FALL = 0x01,
	EXTLEVEL_BOTH = 0x02,
} TIMPLUS_ExtLevelTypeDef;


typedef struct
{
	uint8_t                 ClkDiv;       //ʱ�ӷ�Ƶ
	
	TIMPLUS_ModeTypeDef     Mode;         //����ģʽ
	
	TIMPLUS_ClkSelTypeDef   ClkSel;       //����ʱ��Դѡ��  
	
	TIMPLUS_ExtSelTypeDef   ExtSel;       //����ģʽ�����벶��ģʽ�����ź�ѡ��
	
	TIMPLUS_ExtLevelTypeDef ExtLevel;     //����ģʽ�����벶��ģʽ�����ź���Ч����ѡ��
	
	FunctionalState         OutEn;        //�����������ʹ�� 
	
	uint16_t                Period;       //��������ֵ	
	
	FunctionalState         Ovf_IE;       //����ж�ʹ��
	
	FunctionalState         RIse_IE;      //�������ж�ʹ��
	
	FunctionalState         Fall_IE;      //�½����ж�ʹ��
	
} TIMPLUS_CommonInitTypeDef;


typedef struct
{
	FunctionalState         Hall0_Rise_IE;     //HALL0�������ж�ʹ��
	
	FunctionalState         Hall0_Fall_IE;     //HALL0�½����ж�ʹ��
	
	FunctionalState         Hall1_Rise_IE;     //HALL1�������ж�ʹ��
	
	FunctionalState         Hall1_Fall_IE;     //HALL1�½����ж�ʹ��
	
	FunctionalState         Hall2_Rise_IE;     //HALL2�������ж�ʹ��
	
	FunctionalState         Hall2_Fall_IE;     //HALL2�½����ж�ʹ��	
} TIMPLUS_HallInitTypeDef;



//����  TIMPLUS
#define IS_TIMPLUS_ALL(TIMPLUS)      ((TIMPLUS) == TIMPLUS0)

//����  TIMPLUS ģʽ
#define IS_TIMPLUS_TYPE(TYPE)        ((TYPE) == TIMPLUS_LOW || (TYPE) == TIMPLUS_HIGH)

//����  TIMPLUSԤ��Ƶϵ��  
#define IS_TIMPLUS_CLKDIV(CLKDIV)    ((CLKDIV) <= 255)

//����  TIMPLUS����ģʽ
#define IS_TIMPLUS_MODE(MODE)        ((MODE) == TIMER_MODE || (MODE) == COUNT_MODE || (MODE) == INCAP_MODE || (MODE) == HALL_MODE) 

//����  TIMPLUS����ʱ��ѡ��
#define IS_TIMPLUS_CLKSRC(CLKSRC)    ((CLKSRC) == SYSCLK_DIV || (CLKSRC) == CNTSRC0 || (CLKSRC) == CNTSRC1)                

//����  TIMPLUS����ģʽ�����벶��ģʽ�����ź�ѡ��
#define IS_TIMPLUS_EXTSEL(EXTSEL)    ((EXTSEL) == TIMPLUS_IN0 || (EXTSEL) == TIMPLUS_IN1)

//����  TIMPLUS����ģʽ�����벶��ģʽ�����ź���Ч����ѡ��
#define IS_TIMPLUS_EXTLEVEL(EXTLEVEL)    ((EXTLEVEL) == EXTLEVEL_RISE || (EXTLEVEL) == EXTLEVEL_FALL || (EXTLEVEL) == EXTLEVEL_BOTH)

//����  TIMPLUS����
#define IS_TIMPLUS_PERIOD(PERIOD)    (((PERIOD) > 0) && ((PERIOD) < 65536))

//����  TIMPLUS�����������ʹ�� 
#define IS_TIMPLUS_OUTEN(OUTEN)        (((OUTEN) == ENABLE) || ((OUTEN) == DISABLE))

//����  TIMPLUS����ж�ʹ��
#define IS_TIMPLUS_OVF_IE(OVF_IE)      (((OVF_IE) == ENABLE) || ((OVF_IE) == DISABLE))

//����  TIMPLUS�������ж�ʹ��
#define IS_TIMPLUS_RISE_IE(RISE_IE)    (((RISE_IE) == ENABLE) || ((RISE_IE) == DISABLE))

//����  TIMPLUS�½����ж�ʹ��
#define IS_TIMPLUS_FALL_IE(FALL_IE)    (((FALL_IE) == ENABLE) || ((FALL_IE) == DISABLE))

//����  TIMPLUS HALL0�������ж�ʹ��
#define IS_TIMPLUS_HALL0_RISE_IE(HALL0_RISE_IE)    (((HALL0_RISE_IE) == ENABLE) || ((HALL0_RISE_IE) == DISABLE))

//����  TIMPLUS HALL0�½����ж�ʹ��
#define IS_TIMPLUS_HALL0_FALL_IE(HALL0_FALL_IE)    (((HALL0_FALL_IE) == ENABLE) || ((HALL0_FALL_IE) == DISABLE))

//����  TIMPLUS HALL1�������ж�ʹ��
#define IS_TIMPLUS_HALL1_RISE_IE(HALL1_RISE_IE)    (((HALL1_RISE_IE) == ENABLE) || ((HALL1_RISE_IE) == DISABLE))

//����  TIMPLUS HALL1�½����ж�ʹ��
#define IS_TIMPLUS_HALL1_FALL_IE(HALL1_FALL_IE)    (((HALL1_FALL_IE) == ENABLE) || ((HALL1_FALL_IE) == DISABLE))

//����  TIMPLUS HALL0�������ж�ʹ��
#define IS_TIMPLUS_HALL2_RISE_IE(HALL2_RISE_IE)    (((HALL2_RISE_IE) == ENABLE) || ((HALL2_RISE_IE) == DISABLE))

//����  TIMPLUS HALL0�½����ж�ʹ��
#define IS_TIMPLUS_HALL2_FALL_IE(HALL2_FALL_IE)    (((HALL2_FALL_IE) == ENABLE) || ((HALL2_FALL_IE) == DISABLE))

//����  TIMPLUS HALLͨ��
#define IS_TIMPLUS_HALL_TYPE(HALL_TYPE)            ((HALL_TYPE) >= HALL_0 && (HALL_TYPE) <= (HALL_0 + HALL_1 + HALL_2))



void TIMPLUS_Common_Init(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type,TIMPLUS_CommonInitTypeDef * TIMPLUS_CommonInitStruct);      //TIMPLUS����������ʼ��

void TIMPLUS_Hall_Init(TIMPLUS_TypeDef * TIMPLUSx, TIMPLUS_HallInitTypeDef * TIMPLUS_HallInitStruct);                                    //TIMPLUSͨ����ʼ��

void TIMPLUS_Start(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type);                                                 //������ʱ�����ӳ�ʼֵ��ʼ��ʱ/����

void TIMPLUS_Stop(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type);                                                  //ֹͣ��ʱ��

void TIMPLUS_SetClkDiv(TIMPLUS_TypeDef * TIMPLUSx,uint8_t Clk_Div);                                                      //����Ԥ��Ƶϵ��   ʵ�ʷ�ƵΪ����ֵ��1

void TIMPLUS_SetMode(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type,TIMPLUS_ModeTypeDef Mode);                      //���ù���ģʽ

void TIMPLUS_SetClkSel(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type,TIMPLUS_ClkSelTypeDef ClkSel);                //���ü���ʱ��Դ

void TIMPLUS_SetExtSel(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type,TIMPLUS_ExtSelTypeDef ExtSel);                //���ü���ģʽ�����벶��ģʽ�����ź�

void TIMPLUS_SetExtLevel(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type,TIMPLUS_ExtLevelTypeDef ExtLevel);          //���ü���ģʽ�����벶��ģʽ�����ź���Ч����

void TIMPLUS_SetOutEn(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type,FunctionalState OutEn);                        //���ö�ʱģʽ�������������

void TIMPLUS_SetPeriod(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type,uint16_t Period);                             //���ö�ʱ����������ֵ

uint16_t TIMPLUS_GetPeriod(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type);                                         //��ȡ��ʱ����������ֵ

uint16_t TIMPLUS_GetCurrentValue(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type);                                   //��ȡ��ʱ����ǰ����ֵ

uint16_t TIMPLUS_GetCaptureValue(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type);                                   //��ȡ��ʱ������ֵ

uint8_t TIMPLUS_GetHallLevel(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_HallTypeDef HallLevel);                                  //��ȡHALL��ʼ��ƽ

void TIMPLUS_IntOvfEn(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type);                                              //���ö�ʱ������ж�ʹ��

void TIMPLUS_IntOvfDis(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type);                                             //���ö�ʱ������жϽ���

void TIMPLUS_IntOvfClr(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type);                                             //�����ʱ������ж�״̬  

uint8_t TIMPLUS_IntOvfState(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type);                                        //��ȡ��ʱ������ж�״̬                                                                     
                                                           
void TIMPLUS_IntRiseEn(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type);                                             //���ö�ʱ�����������������ж�ʹ��

void TIMPLUS_IntRiseDis(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type);                                            //���ö�ʱ�����������������жϽ���

void TIMPLUS_IntRiseClr(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type);                                            //�����ʱ�����������������ж�״̬

uint8_t TIMPLUS_IntRiseState(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type);                                       //��ȡ��ʱ�����������������ж�״̬   

void TIMPLUS_IntFallEn(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type);                                             //���ö�ʱ�����������½����ж�ʹ��

void TIMPLUS_IntFallDis(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type);                                            //���ö�ʱ�����������½����жϽ���

void TIMPLUS_IntFallClr(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type);                                            //�����ʱ�����������½����ж�״̬

uint8_t TIMPLUS_IntFallState(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type);                                       //��ȡ��ʱ�����������½����ж�״̬

void TIMPLUS_IntHallRiseEn(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_HallTypeDef HallType);                                     //���ö�ʱ��HALL�������ж�ʹ��

void TIMPLUS_IntHallRiseDis(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_HallTypeDef HallType);                                    //���ö�ʱ��HALL�������жϽ���

void TIMPLUS_IntHallRiseClr(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_HallTypeDef HallType);                                    //�����ʱ��HALL�������ж�״̬

uint8_t TIMPLUS_IntHallRiseState(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_HallTypeDef HallType);                               //��ȡ��ʱ��HALL�������ж�״̬                                    

void TIMPLUS_IntHallFallEn(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_HallTypeDef HallType);                                     //���ö�ʱ��HALL�½����ж�ʹ��

void TIMPLUS_IntHallFallDis(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_HallTypeDef HallType);                                    //���ö�ʱ��HALL�½����жϽ���

void TIMPLUS_IntHallFallClr(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_HallTypeDef HallType);                                    //�����ʱ��HALL�½����ж�״̬

uint8_t TIMPLUS_IntHallFallState(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_HallTypeDef HallType);                               //��ȡ��ʱ��HALL�½����ж�״̬

                   
#endif //__HBM32G003_TIMERPLUS_H__
