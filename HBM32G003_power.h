#ifndef __HBM32G003_POWER_H__
#define __HBM32G003_POWER_H__

#include "HBM32G003.h"

#define MODE_STANDBY         1
#define MODE_SLEEP           2
#define MODE_STOP            4

#define WAKEUP_IO            1


//���Ե͹���ģʽ
#define IS_LOWPOWER_MODE(LOWPOWER_MODE)    (((LOWPOWER_MODE) == MODE_STANDBY)   || ((LOWPOWER_MODE) == MODE_SLEEP) ||  \
                                            ((LOWPOWER_MODE) == MODE_STOP) )

//���Ի���ģʽ
#define IS_WAKEUP_MODE(WAKEUP_MODE)        ((WAKEUP_MODE) == WAKEUP_IO)
											


void Enter_LowPower_Mode(uint8_t Mode);              //���ý���͹���ģʽ     

void WakeUp_Style_Enable(uint8_t WakeUp_Style);      //����ģʽʹ�� 
void WakeUp_Style_Disable(uint8_t WakeUp_Style);     //����ģʽ���� 

uint8_t WakeUp_State_Check(uint8_t WakeUp_Style);    //����״̬��ѯ
void WakeUp_State_Clear(uint8_t WakeUp_Style);       //����״̬���
	

#endif //__HBM32G003_POWER_H__
