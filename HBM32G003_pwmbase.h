#ifndef __HBM32G003_PWMBASE_H__
#define __HBM32G003_PWMBASE_H__

#include "HBM32G003.h"


typedef enum
{ 
	PWMBASE_CH0 =  0x01,  
	PWMBASE_CH1 =  0x02, 
	PWMBASE_CH2 =  0x04, 
} PWMBASE_Channel_TypeDef;


typedef struct {
	uint8_t ClkDiv;		         //1---256��Ƶ
	uint32_t Period;		     //����,16λ
	FunctionalState  OvfIE;		 //��������ж�ʹ��	
} PWMBASE_CommonInitTypeDef;


typedef struct {
	PWMBASE_Channel_TypeDef Channel;
	uint32_t Comp;               //��ת��
	FunctionalState  CompIE;     //��ת���ж�ʹ��
	FunctionalState  Inv;        //����źŵ�ƽ��ת
	FunctionalState  OutEn;      //�������ʹ��
} PWMBASE_ChannelInitTypeDef;


//����  PWMBASE
#define IS_PWMBASE_ALL(PWMBASE)  ((PWMBASE) == PWMBASE0)

//����  PWMBASEͨ��
#define IS_PWMBASE_CHANNEL(PWMBASE_CHANNEL)  ((PWMBASE_CHANNEL) == PWMBASE_CH0 || (PWMBASE_CHANNEL) == PWMBASE_CH1 || (PWMBASE_CHANNEL) == PWMBASE_CH2)

//����  PWMBASEԤ��Ƶϵ��  
#define IS_PWMBASE_CLKDIV(PWMBASE_CLKDIV)    ((PWMBASE_CLKDIV) <= 255)

//����  PWMBASE����
#define IS_PWMBASE_PERIOD(PWMBASE_PERIOD)    (((PWMBASE_PERIOD) > 0) && ((PWMBASE_PERIOD) < 65536))

//����  PWMBASE��ת��
#define IS_PWMBASE_COMP(PWMBASE_COMP)        (((PWM_COMP) < 65536))

//����  PWMBASE����źŷ�ת
#define IS_PWMBASE_INV(PWMBASE_INV)          (((PWMBASE_INV) == ENABLE) || ((PWMBASE_INV) == DISABLE))

//����  PWMBASE����ź�ʹ��
#define IS_PWMBASE_OUTEN(PWMBASE_OUTEN)      (((PWMBASE_OUTEN) == ENABLE) || ((PWMBASE_OUTEN) == DISABLE))

//����  PWMBASE��������ж�
#define IS_PWMBASE_IE_OVF(PWMBASE_IE_OVF)    (((PWMBASE_IE_OVF) == ENABLE) || ((PWMBASE_IE_OVF) == DISABLE))

//����  PWMBASE��ת���ж�
#define IS_PWMBASE_IE_COMP(PWMBASE_IE_COMP)  (((PWMBASE_IE_COMP) == ENABLE) || ((PWMBASE_IE_COMP) == DISABLE))


void PWMBASE_Common_Init(PWMBASE_TypeDef * PWMBASEx, PWMBASE_CommonInitTypeDef * PWMBASE_CommonInitStruct);       //PWMBASE����������ʼ��

void PWMBASE_Channel_Init(PWMBASE_TypeDef * PWMBASEx, PWMBASE_ChannelInitTypeDef * PWMBASE_ChannelInitStruct);    //PWMBASEͨ����ʼ��

void PWMBASE_Start(PWMBASE_TypeDef * PWMBASEx);                                             //����PWMBASE����ʼPWM���

void PWMBASE_Stop(PWMBASE_TypeDef * PWMBASEx);                                              //�ر�PWMBASE��ֹͣPWM���

void PWMBASE_SetClkDiv(PWMBASE_TypeDef * PWMBASEx,uint8_t Clk_Div);                         //����Ԥ��Ƶϵ��   ʵ�ʷ�ƵΪ����ֵ��1

void PWMBASE_SetOutInv(PWMBASE_TypeDef * PWMBASEx,uint8_t CHx,FunctionalState  OutInv);     //PWMBASE����źŷ�ת����

void PWMBASE_SetOutEn(PWMBASE_TypeDef * PWMBASEx,uint8_t CHx,FunctionalState  OutEn);       //PWMBASE���ʹ������

void PWMBASE_SetPeriod(PWMBASE_TypeDef * PWMBASEx, uint16_t Period);                        //��������

uint32_t PWMBASE_GetPeriod(PWMBASE_TypeDef * PWMBASEx);                                     //��ȡ����

void PWMBASE_SetComp(PWMBASE_TypeDef * PWMBASEx, uint8_t CHx,uint32_t Comp);                //���÷�ת��

uint32_t PWMBASE_GetComp(PWMBASE_TypeDef * PWMBASEx, uint8_t CHx);                          //��ȡ���õķ�ת��

void PWMBASE_IntCompEn(PWMBASE_TypeDef * PWMBASEx, uint8_t CHx);                            //PWMBASE��ת���ж�ʹ��

void PWMBASE_IntCompDis(PWMBASE_TypeDef * PWMBASEx, uint8_t CHx);                           //PWMBASE��ת���жϽ���

void PWMBASE_IntCompClr(PWMBASE_TypeDef * PWMBASEx, uint8_t CHx);                           //PWMBASE��ת���жϱ�־���

uint8_t PWMBASE_IntCompState(PWMBASE_TypeDef * PWMBASEx, uint8_t CHx);                      //PWMBASE��ת���ж�״̬  

void PWMBASE_IntOvfEn(PWMBASE_TypeDef * PWMBASEx);                                          //PWMBASE��������ж�ʹ��

void PWMBASE_IntOvfDis(PWMBASE_TypeDef * PWMBASEx);                                         //PWMBASE��������жϽ���

void PWMBASE_IntOvfClr(PWMBASE_TypeDef * PWMBASEx);                                         //PWMBASE��������жϱ�־���

uint8_t PWMBASE_IntOvfState(PWMBASE_TypeDef * PWMBASEx);                                    //PWMBASE��������ж�״̬



#endif //__HBM32G003_PWMBASE_H__
