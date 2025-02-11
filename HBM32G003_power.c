#include "HBM32G003_power.h"


/****************************************************************************************************************************************** 
* ��������: Enter_LowPower_Mode()
* ����˵��:	���ý���͹���ģʽ     
* ��    ��: uint8_t Mode	1 STANDBY   2 SLEEP   4 STOP  	
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void Enter_LowPower_Mode(uint8_t Mode)
{
	assert_param(IS_LOWPOWER_MODE(Mode));                              //�������Ĳ���Mode�Ƿ�Ϸ� 
	
	switch(Mode)
	{
		case MODE_STANDBY:
			
			PMU->LPOW_MD = 0x01 << PMU_LPOW_MD_STANDBY_POS;            //����ϵͳ����STANDBYģʽ
		
		break;
		
		case MODE_SLEEP:
			
			FLASH_Set_DeepPowerDown();
			PMU->LPOW_MD = 0x01 << PMU_LPOW_MD_SLEEP_POS;              //����ϵͳ����SLEEPģʽ
			FLASH_ReSet_DeepPowerDown();
		
		break;
		
		case MODE_STOP:
			
			FLASH_Set_DeepPowerDown();
			PMU->LPOW_MD = 0x01 << PMU_LPOW_MD_STOP_POS;               //����ϵͳ����STOPģʽ 
			FLASH_ReSet_DeepPowerDown();
		
		break;
		
	
		default:
			
		break;
	}
}

/****************************************************************************************************************************************** 
* ��������: WakeUp_Style_Enable()
* ����˵��:	����ģʽʹ��  
* ��    ��: uint8_t WakeUp_Style   1 WAKEUP_IO  		
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void WakeUp_Style_Enable(uint8_t WakeUp_Style)
{
	assert_param(IS_WAKEUP_MODE(WakeUp_Style));                         //�������Ĳ���WakeUp_Style�Ƿ�Ϸ� 
	
	switch(WakeUp_Style)
	{
		case WAKEUP_IO:
			
			PMU->LPMD_WKEN |= 0x01 << PMU_LPMD_WKEN_IO_POS;             //����IO����ʹ��
		
		break;
		
		default:
			
		break;
	}
}

/****************************************************************************************************************************************** 
* ��������: WakeUp_Style_Disable()
* ����˵��:	����ģʽ���� 
* ��    ��: uint8_t WakeUp_Style	 1 WAKEUP_IO  		
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void WakeUp_Style_Disable(uint8_t WakeUp_Style)
{
	assert_param(IS_WAKEUP_MODE(WakeUp_Style));                            //�������Ĳ���WakeUp_Style�Ƿ�Ϸ� 
	
	switch(WakeUp_Style)
	{
		case WAKEUP_IO:
			
			PMU->LPMD_WKEN &= ~(0x01 << PMU_LPMD_WKEN_IO_POS);             //����IO���ѽ���
		
		break;
		
		default:
			
		break;
	}
}

/****************************************************************************************************************************************** 
* ��������: WakeUp_State_Check()
* ����˵��:	����״̬��ѯ
* ��    ��: uint8_t WakeUp_Style	   1 WAKEUP_IO  		
* ��    ��: 1  ���������ѱ�־   0δ�������ѱ�־
* ע������: ��
******************************************************************************************************************************************/
uint8_t WakeUp_State_Check(uint8_t WakeUp_Style)
{
	uint8_t state = 0;
	
	assert_param(IS_WAKEUP_MODE(WakeUp_Style));                            //�������Ĳ���WakeUp_Style�Ƿ�Ϸ� 
	
	switch(WakeUp_Style)
	{
		case WAKEUP_IO:
			
			if(PMU->LPMD_WKST & PMU_LPMD_WKST_IO_MSK)                      //�ж��Ƿ����IO���ѱ�־
			{
				state = 1;
			}
		
		break;
		
		default:
			
			state = 0;
		
		break;
	}

	return state;
}

/****************************************************************************************************************************************** 
* ��������: WakeUp_State_Clear()
* ����˵��:	����״̬���
* ��    ��: uint8_t WakeUp_Style	1 WAKEUP_IO  		
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void WakeUp_State_Clear(uint8_t WakeUp_Style)
{
	assert_param(IS_WAKEUP_MODE(WakeUp_Style));                                //�������Ĳ���WakeUp_Style�Ƿ�Ϸ� 
	
	switch(WakeUp_Style)
	{
		case WAKEUP_IO:
			
			PMU->LPMD_WKST = 0x01 << PMU_LPMD_WKST_IO_POS;                     //���IO���ѱ�־
		
		break;
		
		default:	
		
		break;
	}
}
