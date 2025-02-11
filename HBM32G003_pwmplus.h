#ifndef __HBM32G003_PWMPLUS_H__
#define __HBM32G003_PWMPLUS_H__

#include "HBM32G003.h"


typedef enum
{ 
	CLKSRC_DIV    =  0x00,              // �ڲ�Ԥ��Ƶʱ����Ϊ����ʱ��
	CLKSRC_LOW16  =  0x03,              // ��16λ��ʱ����Ϊ����ʱ��
	CLKSRC_HIGH16 =  0x04,              // ��16λ��ʱ����Ϊ����ʱ��
} PWMPLUS_Clk_Src_TypeDef;


typedef enum
{ 
	SINGLE_EDGE_ALIGN   =  0x00,       // ���α��ض������
	CYCLE_EDGE_ALIGN    =  0x01,       // ѭ�����ض������
	SINGLE_CENTER_ALIGN =  0x02,       // �������Ķ������ 
	CYCLE_CENTER_ALIGN  =  0x03,       // ѭ�����Ķ������ 
} PWMPLUS_Mode_TypeDef;

typedef enum
{ 
	DIR_UP   =  0x00,                  // ���ϼ���
	DIR_DOWN =  0x01,                  // ���¼���
} PWMPLUS_Dir_TypeDef;

typedef enum
{ 
	PWMPLUS_CH0   =  0x01,             //ͨ��CH0     
	PWMPLUS_CH1   =  0x02,             //ͨ��CH1   
	PWMPLUS_CH2   =  0x04,             //ͨ��CH2   
	PWMPLUS_CH0N  =  0x08,             //ͨ��CH0N   
	PWMPLUS_CH1N  =  0x10,             //ͨ��CH1N   
	PWMPLUS_CH2N  =  0x20,             //ͨ��CH2N   
} PWMPLUS_Channel_TypeDef;

typedef enum
{ 
	LEVEL_LOW   =  0x00,               //�͵�ƽ
	LEVEL_HIGH  =  0x01,               //�ߵ�ƽ
} PWMPLUS_Level_TypeDef;

typedef enum
{ 
	BRAKE_FILTER_1   =  0x00,          //ɲ���˲�1��ʱ������                
	BRAKE_FILTER_2   =  0x01,          //ɲ���˲�2��ʱ������ 
	BRAKE_FILTER_4   =  0x02,          //ɲ���˲�4��ʱ������ 
	BRAKE_FILTER_8   =  0x03,          //ɲ���˲�8��ʱ������ 
} PWMPLUS_BrakeFilter_TypeDef;

typedef enum
{ 
	BRAKE0_LOW_BRAKE1_LOW    = 0x00,   //ɲ��0�͵�ƽɲ��1�͵�ƽ
	BRAKE0_HIGH_BRAKE1_LOW   = 0x01,   //ɲ��0�ߵ�ƽɲ��1�͵�ƽ
	BRAKE0_LOW_BRAKE1_HIGH   = 0x02,   //ɲ��0�͵�ƽɲ��1�ߵ�ƽ
	BRAKE0_HIGH_BRAKE1_HIGH  = 0x03,   //ɲ��0�ߵ�ƽɲ��1�ߵ�ƽ
} PWMPLUS_BrakeLevel_TypeDef;

typedef enum
{ 
	BRAKE0_DIS_BRAKE1_DIS    =  0x00,  //ɲ��0����ɲ��1����
	BRAKE0_EN_BRAKE1_DIS     =  0x01,  //ɲ��0ʹ��ɲ��1����
	BRAKE0_DIS_BRAKE1_EN     =  0x02,  //ɲ��0����ɲ��1ʹ��
	BRAKE0_EN_BRAKE1_EN      =  0x03,  //ɲ��0ʹ��ɲ��1ʹ��
} PWMPLUS_BrakeEnable_TypeDef;


typedef enum
{ 
	NOSIGNAL_TRIG         =  0x00,     //�޴����ź�
	UP_OVF_TRIG           =  0x01,     //���ϼ����������
	DOWN_OVF_TRIG         =  0x02,     //���¼����������
	UPDOWN_OVF_TRIG       =  0x03,     //�������¼����������
	CH0_UP_COMP_TRIG      =  0x04,     //ͨ��0���Ϸ�ת�㴥��
	CH0_DOWN_COMP_TRIG    =  0x05,     //ͨ��0���·�ת�㴥��
	CH0_UPDOWN_COMP_TRIG  =  0x06,     //ͨ��0�������·�ת�㴥��
	CH1_UP_COMP_TRIG      =  0x07,     //ͨ��1���Ϸ�ת�㴥�� 
	CH1_DOWN_COMP_TRIG    =  0x08,     //ͨ��1���·�ת�㴥��
	CH1_UPDOWN_COMP_TRIG  =  0x09,     //ͨ��1�������·�ת�㴥��
	CH2_UP_COMP_TRIG      =  0x0A,     //ͨ��2���Ϸ�ת�㴥�� 
	CH2_DOWN_COMP_TRIG    =  0x0B,     //ͨ��2���·�ת�㴥��
	CH2_UPDOWN_COMP_TRIG  =  0x0C,     //ͨ��2�������·�ת�㴥��
	UP_INCOMP_TRIG        =  0x0D,     //���ϼ����ڲ������㴥��
	DOWN_INCOMP_TRIG      =  0x0E,     //���¼����ڲ������㴥��   
	UPDOWN_INCOMP_TRIG    =  0x0F,     //�������¼����ڲ������㴥��
} PWMPLUS_TrigSel_TypeDef;



typedef struct {
	
	PWMPLUS_Clk_Src_TypeDef Clk_Src;          //����ʱ��ѡ��     
	
	uint8_t ClkDiv;		                      //1---256��Ƶ
	
	PWMPLUS_Mode_TypeDef Mode;                //ģʽ   
	
	PWMPLUS_Dir_TypeDef Dir;                  //����   0 ���ϼ���  1 ���¼���
	
	uint8_t Reload_Cnt;                       //�Զ�װ�ش���
	
	uint16_t Period;		                  //����,16λ
	
	PWMPLUS_BrakeFilter_TypeDef Brake_Filter;      //ɲ���ź������˲�  00 ���˲�   01  2��ʱ���˲�  10 4��ʱ���˲�  11  8��ʱ���˲�
	
	PWMPLUS_BrakeLevel_TypeDef Brake_InputLevel;   //ɲ��������Ч��ƽѡ��   0  �͵�ƽ��Ч  1  �ߵ�ƽ��Ч
	
	uint32_t Trig_Comp;                       //�ڲ�������
	
	PWMPLUS_TrigSel_TypeDef Trig0_Sel;        //�����trig0�źŹ���ѡ��
	
	PWMPLUS_TrigSel_TypeDef Trig1_Sel;        //�����trig1�źŹ���ѡ��
	
	PWMPLUS_TrigSel_TypeDef Trig2_Sel;        //�����trig2�źŹ���ѡ��
	
	PWMPLUS_TrigSel_TypeDef Trig3_Sel;        //�����trig3�źŹ���ѡ��
	
	FunctionalState Reload_IE;                //�Զ�װ���ж�ʹ��
	
	FunctionalState Brake0_IE;                //ɲ��0�ж�ʹ��
	
	FunctionalState Brake1_IE;                //ɲ��1�ж�ʹ��
	
	FunctionalState Up_OvfIE;		          //���ϼ�����������ж�ʹ��
	
	FunctionalState Up_TrigCompIE;		      //���ϼ����ڲ��������ж�ʹ��
	
	FunctionalState Down_OvfIE;		          //���¼�����������ж�ʹ��
	
	FunctionalState Down_TrigCompIE;          //���¼����ڲ��������ж�ʹ��
} PWMPLUS_CommonInitTypeDef;

typedef struct {
	PWMPLUS_Channel_TypeDef Channel;          //ͨ��ѡ��
	
	uint16_t Comp;                            //��ת��
	
	uint16_t DeadZone;                        //��������
	
	PWMPLUS_Level_TypeDef StartLevel;         //������ʼ�����ƽ
	
	PWMPLUS_Level_TypeDef CHxIdleLevel;       //ͨ��x���������ƽ
	
	PWMPLUS_Level_TypeDef CHxNIdleLevel;      //ͨ��xN���������ƽ
	
	FunctionalState  CHxInv;                  //ͨ��x����źŵ�ƽ��ת
	
	FunctionalState  CHxNInv;                 //ͨ��xN����źŵ�ƽ��ת
	
	FunctionalState  CHxOutEn;                //ͨ��x�������ʹ��
	
	FunctionalState  CHxNOutEn;               //ͨ��xN�������ʹ��
	
	PWMPLUS_BrakeEnable_TypeDef Brake_Enable; //ɲ��ʹ��
	
	PWMPLUS_Level_TypeDef Brake_CHxOutLevel;  //ɲ��ͨ��CHx�����ƽ
	
	PWMPLUS_Level_TypeDef Brake_CHxNOutLevel; //ɲ��ͨ��CHxN�����ƽ
	
	FunctionalState Mask_CHx_Enable;          //ͨ��CHx����ʹ��
	
	FunctionalState Mask_CHxN_Enable;         //ͨ��CHxN����ʹ��
	
	PWMPLUS_Level_TypeDef Mask_CHx_Level;     //ͨ��CHx���������ƽ
	
	PWMPLUS_Level_TypeDef Mask_CHxN_Level;    //ͨ��CHxN���������ƽ
	
	FunctionalState Up_CompIE;		          //���ϼ�����ת���ж�ʹ��
	
	FunctionalState Down_CompIE;		      //���¼�����ת���ж�ʹ��	
} PWMPLUS_ChannelInitTypeDef;


//����  PWMPLUS
#define IS_PWMPLUS_ALL(PWMPLUS)  ((PWMPLUS) == PWMPLUS0)

//����  PWMPLUS����ʱ��ѡ��
#define IS_PWMPLUS_CLKSRC(PWMPLUS_CLKSRC)    ((PWMPLUS_CLKSRC) == CLKSRC_DIV || (PWMPLUS_CLKSRC) == CLKSRC_LOW16 || (PWMPLUS_CLKSRC) == CLKSRC_HIGH16)                

//����  PWMPLUSԤ��Ƶϵ��  
#define IS_PWMPLUS_CLKDIV(PWMPLUS_CLKDIV)    ((PWMPLUS_CLKDIV) <= 255)

//����  PWMPLUS����ģʽ
#define IS_PWMPLUS_MODE(PWMPLUS_MODE)  ((PWMPLUS_MODE == SINGLE_EDGE_ALIGN)   || (PWMPLUS_MODE == CYCLE_EDGE_ALIGN) || \
                                        (PWMPLUS_MODE == SINGLE_CENTER_ALIGN) || (PWMPLUS_MODE == CYCLE_CENTER_ALIGN) )
//����  PWMPLUS��������
#define IS_PWMPLUS_DIR(PWMPLUS_DIR)    ((PWMPLUS_DIR == DIR_UP) || (PWMPLUS_DIR == DIR_DOWN))
                                        
//����  PWMPLUS����ͨ��
#define IS_PWMPLUS_CHANNEL_ALL(PWMPLUS_CHANNEL_ALL)  ((PWMPLUS_CHANNEL_ALL == PWMPLUS_CH0) || (PWMPLUS_CHANNEL_ALL == PWMPLUS_CH0N) || \
                                                      (PWMPLUS_CHANNEL_ALL == PWMPLUS_CH1) || (PWMPLUS_CHANNEL_ALL == PWMPLUS_CH1N) || \
                                                      (PWMPLUS_CHANNEL_ALL == PWMPLUS_CH2) || (PWMPLUS_CHANNEL_ALL == PWMPLUS_CH2N))

//����  PWMPLUS����ͨ��
#define IS_PWMPLUS_CHANNEL_HALF(PWMPLUS_CHANNEL_HALF)  ((PWMPLUS_CHANNEL_HALF == PWMPLUS_CH0) || (PWMPLUS_CHANNEL_HALF == PWMPLUS_CH1) || \
                                                        (PWMPLUS_CHANNEL_HALF == PWMPLUS_CH2) ) 
                                                      
//����  PWMPLUS�Զ�װ�ش���
#define IS_PWMPLUS_RELOAD_CNT(PWMPLUS_RELOAD_CNT)    ((PWMPLUS_RELOAD_CNT) <= 255)

//����  PWMPLUS����
#define IS_PWMPLUS_PERIOD(PWMPLUS_PERIOD)    (((PWMPLUS_PERIOD) > 0) && ((PWMPLUS_PERIOD) < 65536))

//����  PWMPLUS��ת��
#define IS_PWMPLUS_COMP(PWMPLUS_COMP)    (((PWMPLUS_COMP) >= 0) && ((PWMPLUS_COMP) < 65536))

//����  PWMPLUS��������
#define IS_PWMPLUS_DEADZONE(PWMPLUS_DEADZONE)    (((PWMPLUS_DEADZONE) >= 0) && ((PWMPLUS_DEADZONE) < 1024))

//����  PWMPLUSɲ���ź������˲�
#define IS_PWMPLUS_BRAKE_FILTER(PWMPLUS_BRAKE_FILTER)    ((PWMPLUS_BRAKE_FILTER == BRAKE_FILTER_1) || (PWMPLUS_BRAKE_FILTER == BRAKE_FILTER_2) || \
                                                          (PWMPLUS_BRAKE_FILTER == BRAKE_FILTER_4) || (PWMPLUS_BRAKE_FILTER == BRAKE_FILTER_8) )
//����  PWMPLUSɲ���ź���Ч��ƽ
#define IS_PWMPLUS_BRAKE_LEVEL(PWMPLUS_BRAKE_LEVEL)    ((PWMPLUS_BRAKE_LEVEL == BRAKE0_LOW_BRAKE1_LOW)  || (PWMPLUS_BRAKE_LEVEL == BRAKE0_HIGH_BRAKE1_LOW) || \
                                                        (PWMPLUS_BRAKE_LEVEL == BRAKE0_LOW_BRAKE1_HIGH) || (PWMPLUS_BRAKE_LEVEL == BRAKE0_HIGH_BRAKE1_HIGH) )
//����  PWMPLUSɲ���ź�ʹ��
#define IS_PWMPLUS_BRAKE_ENABLE(PWMPLUS_BRAKE_ENABLE)    ((PWMPLUS_BRAKE_ENABLE == BRAKE0_DIS_BRAKE1_DIS)  || (PWMPLUS_BRAKE_ENABLE == BRAKE0_EN_BRAKE1_DIS) || \
                                                          (PWMPLUS_BRAKE_ENABLE == BRAKE0_DIS_BRAKE1_EN)   || (PWMPLUS_BRAKE_ENABLE == BRAKE0_EN_BRAKE1_EN) )
//����  PWMPLUS�����trig�źŹ���ѡ��
#define IS_PWMPLUS_TRIG_SEL(PWMPLUS_TRIG_SEL)    (((PWMPLUS_TRIG_SEL) >= NOSIGNAL_TRIG) && ((PWMPLUS_TRIG_SEL) <= UPDOWN_INCOMP_TRIG))

//����  PWMPLUS�ڲ�������
#define IS_PWMPLUS_TRIG_COMP(PWMPLUS_TRIG_COMP)    (((PWMPLUS_TRIG_COMP) > 0) && ((PWMPLUS_TRIG_COMP) < 65536))

//����  PWMPLUS������ʼ�����ƽ
#define IS_PWMPLUS_START_LEVEL(PWMPLUS_START_LEVEL)    (((PWMPLUS_START_LEVEL) == LEVEL_LOW) || ((PWMPLUS_START_LEVEL) == LEVEL_HIGH))

//����  PWMPLUSͨ�����������ƽ
#define IS_PWMPLUS_IDLE_LEVEL(PWMPLUS_IDLE_LEVEL)    (((PWMPLUS_IDLE_LEVEL) == LEVEL_LOW) || ((PWMPLUS_IDLE_LEVEL) == LEVEL_HIGH))

//����  PWMPLUSͨ������źŵ�ƽ��ת
#define IS_PWMPLUS_OUTINV(PWMPLUS_OUTINV)            (((PWMPLUS_OUTINV) == ENABLE) || ((PWMPLUS_OUTINV) == DISABLE))

//����  PWMPLUSͨ���������ʹ��
#define IS_PWMPLUS_OUTEN(PWMPLUS_OUTEN)        (((PWMPLUS_OUTEN) == ENABLE) || ((PWMPLUS_OUTEN) == DISABLE))

//����  PWMPLUSɲ��ʹ��
#define IS_PWMPLUS_BRAKEEN(PWMPLUS_BRAKEEN)    (((PWMPLUS_BRAKEEN) == ENABLE) || ((PWMPLUS_BRAKEEN) == DISABLE))

//����  PWMPLUSɲ��ͨ�������ƽ
#define IS_PWMPLUS_BRAKE_OUTLEVEL(PWMPLUS_BRAKE_OUTLEVEL)    (((PWMPLUS_BRAKE_OUTLEVEL) == LEVEL_LOW) || ((PWMPLUS_BRAKE_OUTLEVEL) == LEVEL_HIGH))

//����  PWMPLUSͨ������ʹ��
#define IS_PWMPLUS_MASK_EN(PWMPLUS_MASK_EN)    (((PWMPLUS_MASK_EN) == ENABLE) || ((PWMPLUS_MASK_EN) == DISABLE))

//����  PWMPLUSͨ�����������ƽ
#define IS_PWMPLUS_MASK_LEVEL(PWMPLUS_MASK_LEVEL)    (((PWMPLUS_MASK_LEVEL) == LEVEL_LOW) || ((PWMPLUS_MASK_LEVEL) == LEVEL_HIGH))

//����  PWMPLUS�Զ�װ���ж�ʹ��
#define IS_PWMPLUS_RELOAD_IE(PWMPLUS_RELOAD_IE)    (((PWMPLUS_RELOAD_IE) == ENABLE) || ((PWMPLUS_RELOAD_IE) == DISABLE))

//����  PWMPLUSɲ��0�ж�ʹ��
#define IS_PWMPLUS_BRAKE0_IE(PWMPLUS_BRAKE0_IE)    (((PWMPLUS_BRAKE0_IE) == ENABLE) || ((PWMPLUS_BRAKE0_IE) == DISABLE))

//����  PWMPLUSɲ��1�ж�ʹ��
#define IS_PWMPLUS_BRAKE1_IE(PWMPLUS_BRAKE1_IE)    (((PWMPLUS_BRAKE1_IE) == ENABLE) || ((PWMPLUS_BRAKE1_IE) == DISABLE))

//����  PWMPLUS���ϼ�����������ж�ʹ��
#define IS_PWMPLUS_UP_OVF_IE(PWMPLUS_UP_OVF_IE)    (((PWMPLUS_UP_OVF_IE) == ENABLE) || ((PWMPLUS_UP_OVF_IE) == DISABLE))

//����  PWMPLUS���¼�����������ж�ʹ��
#define IS_PWMPLUS_DOWN_OVF_IE(PWMPLUS_DOWN_OVF_IE)    (((PWMPLUS_DOWN_OVF_IE) == ENABLE) || ((PWMPLUS_DOWN_OVF_IE) == DISABLE))

//����  PWMPLUS���ϼ����ڲ��������ж�ʹ��
#define IS_PWMPLUS_UP_TRIGCOMP_IE(PWMPLUS_UP_TRIGCOMP_IE)    (((PWMPLUS_UP_TRIGCOMP_IE) == ENABLE) || ((PWMPLUS_UP_TRIGCOMP_IE) == DISABLE))

//����  PWMPLUS���¼����ڲ��������ж�ʹ��
#define IS_PWMPLUS_DOWN_TRIGCOMP_IE(PWMPLUS_DOWN_TRIGCOMP_IE)    (((PWMPLUS_DOWN_TRIGCOMP_IE) == ENABLE) || ((PWMPLUS_DOWN_TRIGCOMP_IE) == DISABLE))

//����  PWMPLUS���ϼ�����ת���ж�ʹ��
#define IS_PWMPLUS_UP_COMP_IE(PWMPLUS_UP_COMP_IE)    (((PWMPLUS_UP_COMP_IE) == ENABLE) || ((PWMPLUS_UP_COMP_IE) == DISABLE))

//����  PWMPLUS���¼�����ת���ж�ʹ��
#define IS_PWMPLUS_DOWN_COMP_IE(PWMPLUS_DOWN_COMP_IE)    (((PWMPLUS_DOWN_COMP_IE) == ENABLE) || ((PWMPLUS_DOWN_COMP_IE) == DISABLE))



void PWMPLUS_CommonInit(PWMPLUS_TypeDef * PWMPLUSx, PWMPLUS_CommonInitTypeDef * PWMPLUS_CommonInitStruct);        //PWMPLUS����������ʼ��

void PWMPLUS_ChannelInit(PWMPLUS_TypeDef * PWMPLUSx, PWMPLUS_ChannelInitTypeDef * PWMPLUS_ChannelInitStruct);     //PWMPLUSͨ����ʼ��

void PWMPLUS_Start(PWMPLUS_TypeDef * PWMPLUSx);                                                                   //����PWMPLUS����ʼPWM���

void PWMPLUS_Stop(PWMPLUS_TypeDef * PWMPLUSx);                                                                    //�ر�PWMPLUS��ֹͣPWM���

void PWMPLUS_SetClk_Src(PWMPLUS_TypeDef * PWMPLUSx,PWMPLUS_Clk_Src_TypeDef Clk_Src);                              //PWMPLUSʱ��ѡ��

void PWMPLUS_SetClkDiv(PWMPLUS_TypeDef * PWMPLUSx,uint8_t ClkDiv);                                                //����Ԥ��Ƶϵ��   ʵ�ʷ�ƵΪ����ֵ��1

void PWMPLUS_SetMode(PWMPLUS_TypeDef * PWMPLUSx,PWMPLUS_Mode_TypeDef Mode);                                       //���ù���ģʽ

void PWMPLUS_SetDir(PWMPLUS_TypeDef * PWMPLUSx,PWMPLUS_Dir_TypeDef Dir);                                          //���ü�������

void PWMPLUS_SetReload_Cnt(PWMPLUS_TypeDef * PWMPLUSx,uint8_t Reload_Cnt);                                        //�����Զ�װ�ش���   ʵ��װ�ش���Ϊ����ֵ��1

void PWMPLUS_SetBrake_Filter(PWMPLUS_TypeDef * PWMPLUSx,PWMPLUS_BrakeFilter_TypeDef Brake_Filter);                //����ɲ���˲�

void PWMPLUS_SetBrake_InputLevel(PWMPLUS_TypeDef * PWMPLUSx,PWMPLUS_BrakeLevel_TypeDef Brake_InputLevel);         //����ɲ��������Ч��ƽѡ�� 

void PWMPLUS_SetBrake_Enable(PWMPLUS_TypeDef * PWMPLUSx,uint8_t CHx,PWMPLUS_BrakeEnable_TypeDef Brake_Enable);    //����ɲ��ʹ��

void PWMPLUS_SetBrake_OutLevel(PWMPLUS_TypeDef * PWMPLUSx,uint8_t CHx,PWMPLUS_Level_TypeDef Brake_OutLevel);      //����ɲ��ʱͨ�������ƽ

void PWMPLUS_SetMask_Enable(PWMPLUS_TypeDef * PWMPLUSx,uint8_t CHx,FunctionalState Mask_Enable);                  //�������ι����Ƿ�ʹ��

void PWMPLUS_SetMask_Level(PWMPLUS_TypeDef * PWMPLUSx,uint8_t CHx,PWMPLUS_Level_TypeDef Mask_Level);              //�������������ƽ

void PWMPLUS_SetStartLevel(PWMPLUS_TypeDef * PWMPLUSx,uint8_t CHx,PWMPLUS_Level_TypeDef StartLevel);              //PWMPLUS������ʼ�����ƽ

void PWMPLUS_SetIdleLevel(PWMPLUS_TypeDef * PWMPLUSx,uint8_t CHx,PWMPLUS_Level_TypeDef  IdleLevel);               //PWMPLUS���������ƽ����

void PWMPLUS_SetOutEn(PWMPLUS_TypeDef * PWMPLUSx,uint8_t CHx,FunctionalState  OutEn);                             //PWMPLUS���ʹ��

void PWMPLUS_SetOutInv(PWMPLUS_TypeDef * PWMPLUSx,uint8_t CHx,FunctionalState  OutInv);                           //PWMPLUS����źŷ�ת

void PWMPLUS_SetPeriod(PWMPLUS_TypeDef * PWMPLUSx, uint16_t Period);                                              //��������

uint32_t PWMPLUS_GetPeriod(PWMPLUS_TypeDef * PWMPLUSx);                                                           //��ȡ����

void PWMPLUS_SetComp(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx,uint16_t Comp);                                      //���÷�ת��

uint32_t PWMPLUS_GetComp(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx);                                                //��ȡ���õķ�ת��

void PWMPLUS_SetDeadZone(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx,uint16_t DeadZone);                              //����ͨ����������

uint16_t PWMPLUS_GetDeadZone(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx);                                            //��ȡͨ����������

void PWMPLUS_SetTrig_Comp(PWMPLUS_TypeDef * PWMPLUSx, uint16_t Trig_Comp);                                        //�����ڲ�������

uint32_t PWMPLUS_GetTrig_Comp(PWMPLUS_TypeDef * PWMPLUSx);                                                        //��ȡ�ڲ�������

void PWMPLUS_SetTrig_Sel0(PWMPLUS_TypeDef * PWMPLUSx, PWMPLUS_TrigSel_TypeDef Trig_Sel);                          //���ô����ź�0����ѡ��

void PWMPLUS_SetTrig_Sel1(PWMPLUS_TypeDef * PWMPLUSx, PWMPLUS_TrigSel_TypeDef Trig_Sel);                          //���ô����ź�1����ѡ��

void PWMPLUS_SetTrig_Sel2(PWMPLUS_TypeDef * PWMPLUSx, PWMPLUS_TrigSel_TypeDef Trig_Sel);                          //���ô����ź�2����ѡ��

void PWMPLUS_SetTrig_Sel3(PWMPLUS_TypeDef * PWMPLUSx, PWMPLUS_TrigSel_TypeDef Trig_Sel);                          //���ô����ź�3����ѡ��

void PWMPLUS_IntReloadEn(PWMPLUS_TypeDef * PWMPLUSx);                                                             //�����Զ�װ���ж�ʹ��

void PWMPLUS_IntReloadDis(PWMPLUS_TypeDef * PWMPLUSx);                                                            //�����Զ�װ���жϽ���

uint8_t PWMPLUS_IntReloadState(PWMPLUS_TypeDef * PWMPLUSx);                                                       //��ȡ�Զ�װ���ж�״̬

void PWMPLUS_IntReloadClr(PWMPLUS_TypeDef * PWMPLUSx);                                                            //����Զ�װ���ж�״̬

void PWMPLUS_IntBrake0En(PWMPLUS_TypeDef * PWMPLUSx);                                                             //����ɲ��0�ж�ʹ��
 
void PWMPLUS_IntBrake0Dis(PWMPLUS_TypeDef * PWMPLUSx);                                                            //����ɲ��0�жϽ���

uint8_t PWMPLUS_IntBrake0State(PWMPLUS_TypeDef * PWMPLUSx);                                                       //��ȡɲ��0�ж�״̬

void PWMPLUS_IntBrake0Clr(PWMPLUS_TypeDef * PWMPLUSx);                                                            //���ɲ��0�ж�״̬

void PWMPLUS_IntBrake1En(PWMPLUS_TypeDef * PWMPLUSx);                                                             //����ɲ��1�ж�ʹ��

void PWMPLUS_IntBrake1Dis(PWMPLUS_TypeDef * PWMPLUSx);                                                            //����ɲ��1�жϽ���

uint8_t PWMPLUS_IntBrake1State(PWMPLUS_TypeDef * PWMPLUSx);                                                       //��ȡɲ��1�ж�״̬

void PWMPLUS_IntBrake1Clr(PWMPLUS_TypeDef * PWMPLUSx);                                                            //���ɲ��1�ж�״̬

void PWMPLUS_IntUp_OvfEn(PWMPLUS_TypeDef * PWMPLUSx);                                                             //�������ϼ�����������ж�ʹ��

void PWMPLUS_IntUp_OvfDis(PWMPLUS_TypeDef * PWMPLUSx);                                                            //�������ϼ�����������жϽ���

uint8_t PWMPLUS_IntUp_OvfState(PWMPLUS_TypeDef * PWMPLUSx);                                                       //��ȡ���ϼ�����������ж�״̬

void PWMPLUS_IntUp_OvfClr(PWMPLUS_TypeDef * PWMPLUSx);                                                            //������ϼ�����������ж�״̬

void PWMPLUS_IntUp_TrigCompEn(PWMPLUS_TypeDef * PWMPLUSx);                                                        //�������ϼ������ﴥ�����ж�ʹ��

void PWMPLUS_IntUp_TrigCompDis(PWMPLUS_TypeDef * PWMPLUSx);                                                       //�������ϼ������ﴥ�����жϽ���

uint8_t PWMPLUS_IntUp_TrigCompState(PWMPLUS_TypeDef * PWMPLUSx);                                                  //��ȡ���ϼ������ﴥ�����ж�״̬

void PWMPLUS_IntUp_TrigCompClr(PWMPLUS_TypeDef * PWMPLUSx);                                                       //������ϼ������ﴥ�����ж�״̬

void PWMPLUS_IntDown_OvfEn(PWMPLUS_TypeDef * PWMPLUSx);                                                           //�������¼�����������ж�ʹ��

void PWMPLUS_IntDown_OvfDis(PWMPLUS_TypeDef * PWMPLUSx);                                                          //�������¼�����������жϽ���

uint8_t PWMPLUS_IntDown_OvfState(PWMPLUS_TypeDef * PWMPLUSx);                                                     //��ȡ���¼�����������ж�״̬

void PWMPLUS_IntDown_OvfClr(PWMPLUS_TypeDef * PWMPLUSx);                                                          //������¼�����������ж�״̬

void PWMPLUS_IntDown_TrigCompEn(PWMPLUS_TypeDef * PWMPLUSx);                                                      //�������¼������ﴥ�����ж�ʹ��

void PWMPLUS_IntDown_TrigCompDis(PWMPLUS_TypeDef * PWMPLUSx);                                                     //�������¼������ﴥ�����жϽ���

uint8_t PWMPLUS_IntDown_TrigCompState(PWMPLUS_TypeDef * PWMPLUSx);                                                //��ȡ���¼������ﴥ�����ж�״̬

void PWMPLUS_IntDown_TrigCompClr(PWMPLUS_TypeDef * PWMPLUSx);                                                     //������¼������ﴥ�����ж�״̬

void PWMPLUS_IntUp_CompEn(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx);                                               //�������ϼ������﷭ת���ж�ʹ��

void PWMPLUS_IntUp_CompDis(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx);                                              //�������ϼ������﷭ת���жϽ���

uint8_t PWMPLUS_IntUp_CompState(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx);                                         //��ȡ���ϼ������﷭ת���ж�״̬

void PWMPLUS_IntUp_CompClr(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx);                                              //������ϼ������﷭ת���ж�״̬

void PWMPLUS_IntDown_CompEn(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx);                                             //�������¼������﷭ת���ж�ʹ��

void PWMPLUS_IntDown_CompDis(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx);                                            //�������¼������﷭ת���жϽ���

uint8_t PWMPLUS_IntDown_CompState(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx);                                       //��ȡ���¼������﷭ת���ж�״̬

void PWMPLUS_IntDown_CompClr(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx);                                            //������¼������﷭ת���ж�״̬

void PWMPLUS_SoftLoad(PWMPLUS_TypeDef * PWMPLUSx);                                                                //PWMPLUS���LOAD

uint8_t PWMPLUS_GetCntState(PWMPLUS_TypeDef * PWMPLUSx);                                                          //��ȡPWMPLUS����������״̬

uint8_t PWMPLUS_GetCntDir(PWMPLUS_TypeDef * PWMPLUSx);                                                            //��ȡPWMPLUS��������ǰ��������

uint16_t PWMPLUS_GetCurrentCnt(PWMPLUS_TypeDef * PWMPLUSx);                                                       //��ȡPWMPLUS��������ǰ����ֵ

uint8_t PWMPLUS_GetBrake0State(PWMPLUS_TypeDef * PWMPLUSx);                                                       //��ȡPWMPLUSɲ��0�ĵ�ǰ״̬

uint8_t PWMPLUS_GetBrake1State(PWMPLUS_TypeDef * PWMPLUSx);                                                       //��ȡPWMPLUSɲ��1�ĵ�ǰ״̬
	

#endif //__HBM32G003_PWMPLUS_H__
