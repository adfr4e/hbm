#ifndef __HBM32G003_POWER_H__
#define __HBM32G003_POWER_H__

#include "HBM32G003.h"

#define MODE_STANDBY         1
#define MODE_SLEEP           2
#define MODE_STOP            4

#define WAKEUP_IO            1


//断言低功耗模式
#define IS_LOWPOWER_MODE(LOWPOWER_MODE)    (((LOWPOWER_MODE) == MODE_STANDBY)   || ((LOWPOWER_MODE) == MODE_SLEEP) ||  \
                                            ((LOWPOWER_MODE) == MODE_STOP) )

//断言唤醒模式
#define IS_WAKEUP_MODE(WAKEUP_MODE)        ((WAKEUP_MODE) == WAKEUP_IO)
											


void Enter_LowPower_Mode(uint8_t Mode);              //配置进入低功耗模式     

void WakeUp_Style_Enable(uint8_t WakeUp_Style);      //唤醒模式使能 
void WakeUp_Style_Disable(uint8_t WakeUp_Style);     //唤醒模式禁能 

uint8_t WakeUp_State_Check(uint8_t WakeUp_Style);    //唤醒状态查询
void WakeUp_State_Clear(uint8_t WakeUp_Style);       //唤醒状态清除
	

#endif //__HBM32G003_POWER_H__
