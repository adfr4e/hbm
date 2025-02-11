#include "HBM32G003_pwmplus.h"

/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_CommonInit()
* ����˵��:	PWMPLUS����������ʼ��
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx                  ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
*			PWMPLUS_InitTypeDef * PWMPLUS_ChannelInitStruct	����PWMPLUS����趨ֵ�Ľṹ��
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_CommonInit(PWMPLUS_TypeDef * PWMPLUSx, PWMPLUS_CommonInitTypeDef * PWMPLUS_CommonInitStruct)
{
	uint32_t temp = 0;
	
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                                            //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_PWMPLUS_CLKSRC(PWMPLUS_CommonInitStruct->Clk_Src));                 //�������Ĳ���ClkSrc�Ƿ�Ϸ�   
	
	assert_param(IS_PWMPLUS_CLKDIV(PWMPLUS_CommonInitStruct->ClkDiv));                 //�������Ĳ���ClkDiv�Ƿ�Ϸ�   
	
	assert_param(IS_PWMPLUS_MODE(PWMPLUS_CommonInitStruct->Mode));                     //�������Ĳ���Mode�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_DIR(PWMPLUS_CommonInitStruct->Dir));                       //�������Ĳ���Dir�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_RELOAD_CNT(PWMPLUS_CommonInitStruct->Reload_Cnt));         //�������Ĳ���Reload_Cnt�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_PERIOD(PWMPLUS_CommonInitStruct->Period));                 //�������Ĳ���Period�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_BRAKE_FILTER(PWMPLUS_CommonInitStruct->Brake_Filter));     //�������Ĳ���Brake_Filter�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_BRAKE_LEVEL(PWMPLUS_CommonInitStruct->Brake_InputLevel));  //�������Ĳ���Brake_InputLevel�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_TRIG_COMP(PWMPLUS_CommonInitStruct->Trig_Comp));           //�������Ĳ���Trig_Comp�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_TRIG_SEL(PWMPLUS_CommonInitStruct->Trig_Sel));             //�������Ĳ���Trig_Sel�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_RELOAD_IE(PWMPLUS_CommonInitStruct->Reload_IE));           //�������Ĳ���Reload_IE�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_BRAKE0_IE(PWMPLUS_CommonInitStruct->Brake0_IE));           //�������Ĳ���Brake0_IE�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_BRAKE1_IE(PWMPLUS_CommonInitStruct->Brake1_IE));           //�������Ĳ���Brake1_IE�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_UP_OVF_IE(PWMPLUS_CommonInitStruct->Up_OvfIE));            //�������Ĳ���Up_OvfIE�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_UP_TRIGCOMP_IE(PWMPLUS_CommonInitStruct->Up_TrigCompIE));            //�������Ĳ���Up_TrigCompIE�Ƿ�Ϸ� 
	
	assert_param(IS_PWMPLUS_DOWN_OVF_IE(PWMPLUS_CommonInitStruct->Down_OvfIE));                  //�������Ĳ���Down_OvfIE�Ƿ�Ϸ� 
	
	assert_param(IS_PWMPLUS_DOWN_TRIGCOMP_IE(PWMPLUS_CommonInitStruct->Down_TrigCompIE));        //�������Ĳ���Down_TrigCompIE�Ƿ�Ϸ� 
	

	switch((uint32_t)PWMPLUSx)
	{
		case((uint32_t)PWMPLUS0):
		
			SYS->CLKEN |= 0x01 << SYS_CLKEN_PWMPLUS0_POS;           //����PWMPLUS0ʱ��
		
		break;
	}

	PWMPLUS_Stop(PWMPLUSx);                                         //�ر�PWMBASE��ֹͣPWM���  
	
	temp = PWMPLUSx->CLK;
	
	temp &= ~(0x07 << PWMPLUS_CLK_SRC_POS);                //����ʱ��ѡ��
	temp |= ((PWMPLUS_CommonInitStruct->Clk_Src) << PWMPLUS_CLK_SRC_POS);
	
	temp &= ~((0xFFFF << PWMPLUS_CLK_PREDIV_POS));         //ʱ�ӷ�Ƶ   ʵ�ʷ�ƵΪ����ֵ��1
	temp |= ((PWMPLUS_CommonInitStruct->ClkDiv) << PWMPLUS_CLK_PREDIV_POS);
	
	PWMPLUSx->CLK = temp;
	
	temp = PWMPLUSx->CTR;
	
	temp &= ~(0x03 << PWMPLUS_CTR_OPM_POS);                //����ģʽ
	temp |= (PWMPLUS_CommonInitStruct->Mode << PWMPLUS_CTR_OPM_POS);	
	
	temp &= ~(0x01 << PWMPLUS_CTR_DIR_POS);                //��������
	temp |= (PWMPLUS_CommonInitStruct->Dir << PWMPLUS_CTR_DIR_POS);	
	
	temp &= ~(0xFF << PWMPLUS_CTR_RELOAD_POS);             //�Զ�װ�ش���   ʵ��װ�ش���Ϊ����ֵ��1
	temp |= (PWMPLUS_CommonInitStruct->Reload_Cnt << PWMPLUS_CTR_RELOAD_POS);
	
	PWMPLUSx->CTR = temp;
	
	if(PWMPLUS_CommonInitStruct->Period == 0)
	{
		PWMPLUS_CommonInitStruct->Period = 0xFFFF;
	}
	
	PWMPLUSx->PERIOD = PWMPLUS_CommonInitStruct->Period;           //PWMPLUS����   ʵ������Ϊ����ֵ��1
	
	temp = PWMPLUSx->BRK_CTR;
	
	temp &= ~(0x03 << PWMPLUS_BRK_CTR_FILTER_POS);    //ɲ���˲�
	temp |= (PWMPLUS_CommonInitStruct->Brake_Filter << PWMPLUS_BRK_CTR_FILTER_POS);
	
	temp &= ~(0x03 << PWMPLUS_BRK_CTR_INLEV_POS);     //ɲ��������Ч��ƽ����
	temp |= (PWMPLUS_CommonInitStruct->Brake_InputLevel << PWMPLUS_BRK_CTR_INLEV_POS);
	
	PWMPLUSx->BRK_CTR = temp;
	
	if(PWMPLUS_CommonInitStruct->Period < PWMPLUS_CommonInitStruct->Trig_Comp)
	{
		PWMPLUS_CommonInitStruct->Trig_Comp = 0;
	}
	
	PWMPLUSx->TRIG_COMP = PWMPLUS_CommonInitStruct->Trig_Comp;     //�����ڲ�������

	temp = PWMPLUSx->TRIG_SEL;
	
	temp &= ~(0x01 << PWMPLUS_TRIG_CTR_SEL0_POS);    //�����Trig0�źŹ���ѡ��
	temp |= (PWMPLUS_CommonInitStruct->Trig0_Sel << PWMPLUS_TRIG_CTR_SEL0_POS);
	
	temp &= ~(0x01 << PWMPLUS_TRIG_CTR_SEL1_POS);    //�����Trig1�źŹ���ѡ��
	temp |= (PWMPLUS_CommonInitStruct->Trig1_Sel << PWMPLUS_TRIG_CTR_SEL1_POS);
	
	temp &= ~(0x01 << PWMPLUS_TRIG_CTR_SEL2_POS);    //�����Trig2�źŹ���ѡ��
	temp |= (PWMPLUS_CommonInitStruct->Trig2_Sel << PWMPLUS_TRIG_CTR_SEL2_POS);
	
	temp &= ~(0x01 << PWMPLUS_TRIG_CTR_SEL3_POS);    //�����Trig3�źŹ���ѡ��
	temp |= (PWMPLUS_CommonInitStruct->Trig3_Sel << PWMPLUS_TRIG_CTR_SEL3_POS);
	
	PWMPLUSx->TRIG_SEL = temp;
	
	temp = PWMPLUSx->IE;
	
	temp &= ~(0x01 << PWMPLUS_IE_RELOAD_POS);              //�Զ�װ���ж�����
	temp |= (PWMPLUS_CommonInitStruct->Reload_IE << PWMPLUS_IE_RELOAD_POS);
	
	temp &= ~(0x01 << PWMPLUS_IE_BRK0_POS);                //BRAKE0�ж�����
	temp |= (PWMPLUS_CommonInitStruct->Brake0_IE << PWMPLUS_IE_BRK0_POS);
	
	temp &= ~(0x01 << PWMPLUS_IE_BRK1_POS);                //BRAKE1�ж�����
	temp |= (PWMPLUS_CommonInitStruct->Brake1_IE << PWMPLUS_IE_BRK1_POS);
	
	temp &= ~(0x01 << PWMPLUS_IE_UP_OVF_POS);              //���ϼ�����������ж�����
	temp |= (PWMPLUS_CommonInitStruct->Up_OvfIE << PWMPLUS_IE_UP_OVF_POS);
	
	temp &= ~(0x01 << PWMPLUS_IE_UP_TRIG_POS);             //���ϼ������ﴥ�����ж�����
	temp |= (PWMPLUS_CommonInitStruct->Up_TrigCompIE << PWMPLUS_IE_UP_TRIG_POS);
	
	temp &= ~(0x01 << PWMPLUS_IE_DOWN_OVF_POS);            //���¼�����������ж�����
	temp |= (PWMPLUS_CommonInitStruct->Down_OvfIE << PWMPLUS_IE_DOWN_OVF_POS);
	
	temp &= ~(0x01 << PWMPLUS_IE_DOWN_TRIG_POS);           //���¼������ﴥ�����ж�����
	temp |= (PWMPLUS_CommonInitStruct->Down_TrigCompIE << PWMPLUS_IE_DOWN_TRIG_POS);
	
	PWMPLUSx->IE = temp;
	
	
	switch((uint32_t)PWMPLUSx)
	{
		case((uint32_t)PWMPLUS0):
		
			if(PWMPLUSx->IE != 0)
			{
				NVIC_EnableIRQ(PWMPLUS0_IRQn);
			}
		
		break;
	}
	
	PWMPLUSx->IF = 0xFFFFF;
}

/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_ChannelInit()
* ����˵��:	PWMPLUSͨ����ʼ��
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx                  ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
*			PWMPLUS_InitTypeDef * PWMPLUS_ChannelInitStruct	����PWMPLUS����趨ֵ�Ľṹ��
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_ChannelInit(PWMPLUS_TypeDef * PWMPLUSx, PWMPLUS_ChannelInitTypeDef * PWMPLUS_ChannelInitStruct)
{
	uint32_t temp = 0;
	
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                                       //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_PWMPLUS_CHANNEL_HALF(PWMPLUS_ChannelInitStruct->Channel));    //�������Ĳ���Channel�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_COMP(PWMPLUS_ChannelInitStruct->Comp));               //�������Ĳ���Comp�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_DEADZONE(PWMPLUS_ChannelInitStruct->DeadZone));       //�������Ĳ���DeadZone�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_OUTEN(PWMPLUS_ChannelInitStruct->CHxOutEn));          //�������Ĳ���CHxOutEn�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_OUTEN(PWMPLUS_ChannelInitStruct->CHxNOutEn));         //�������Ĳ���CHxNOutEn�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_OUTINV(PWMPLUS_ChannelInitStruct->CHxInv));           //�������Ĳ���CHxInv�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_OUTINV(PWMPLUS_ChannelInitStruct->CHxNInv));          //�������Ĳ���CHxNInv�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_START_LEVEL(PWMPLUS_ChannelInitStruct->StartLevel));  //�������Ĳ���StartLevel�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_IDLE_LEVEL(PWMPLUS_ChannelInitStruct->CHxIdleLevel));       //�������Ĳ���CHxIdleLevel�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_IDLE_LEVEL(PWMPLUS_ChannelInitStruct->CHxNIdleLevel));      //�������Ĳ���CHxNIdleLevel�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_BRAKEEN(PWMPLUS_ChannelInitStruct->Brake_Enable));          //�������Ĳ���Brake_Enable�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_BRAKE_OUTLEVEL(PWMPLUS_ChannelInitStruct->Brake_CHxOutLevel));         //�������Ĳ���Brake_CHxOutLevel�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_BRAKE_OUTLEVEL(PWMPLUS_ChannelInitStruct->Brake_CHxNOutLevel));        //�������Ĳ���Brake_CHxNOutLevel�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_MASK_EN(PWMPLUS_ChannelInitStruct->Mask_CHx_Enable));                  //�������Ĳ���Mask_CHx_Enable�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_MASK_EN(PWMPLUS_ChannelInitStruct->Mask_CHxN_Enable));                 //�������Ĳ���Mask_CHxN_Enable�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_MASK_LEVEL(PWMPLUS_ChannelInitStruct->Mask_CHx_Level));                //�������Ĳ���Mask_CHx_Level�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_MASK_LEVEL(PWMPLUS_ChannelInitStruct->Mask_CHxN_Level));               //�������Ĳ���Mask_CHxN_Level�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_UP_COMP_IE(PWMPLUS_ChannelInitStruct->Up_CompIE));                     //�������Ĳ���Up_CompIE�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_DOWN_COMP_IE(PWMPLUS_ChannelInitStruct->Down_CompIE));                 //�������Ĳ���Down_CompIE�Ƿ�Ϸ�  
	
	
	PWMPLUS_Stop(PWMPLUSx);                                                                        //�ر�PWMBASE��ֹͣPWM���  
	
	if(PWMPLUS_ChannelInitStruct->Comp > PWMPLUS_GetPeriod(PWMPLUSx))
	{
		PWMPLUS_ChannelInitStruct->Comp = 0;
	}

	if(PWMPLUS_ChannelInitStruct->DeadZone > PWMPLUS_ChannelInitStruct->Comp)
	{
		PWMPLUS_ChannelInitStruct->DeadZone = PWMPLUS_ChannelInitStruct->Comp;
		
		if(PWMPLUS_ChannelInitStruct->DeadZone > 1023)
		{
			PWMPLUS_ChannelInitStruct->DeadZone = 1023;
		}
	}
	
	
	if((PWMPLUS_ChannelInitStruct->Channel & PWMPLUS_CH0) == PWMPLUS_CH0)
	{
		if(PWMPLUS_ChannelInitStruct->CHxOutEn == ENABLE)    
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH0_OUTEN_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH0_OUTEN_POS);
		}
		
		if(PWMPLUS_ChannelInitStruct->CHxNOutEn == ENABLE)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH0N_OUTEN_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH0N_OUTEN_POS);
		}
		
		if(PWMPLUS_ChannelInitStruct->CHxInv == ENABLE)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH0_INV_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH0_INV_POS);
		}
		
		if(PWMPLUS_ChannelInitStruct->CHxNInv == ENABLE)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH0N_INV_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH0N_INV_POS);
		}
		
		if(PWMPLUS_ChannelInitStruct->StartLevel == LEVEL_HIGH)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH0_START_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH0_START_POS);
		}
		
		if(PWMPLUS_ChannelInitStruct->CHxIdleLevel == LEVEL_HIGH)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH0_IDLE_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH0_IDLE_POS);
		}
		
		if(PWMPLUS_ChannelInitStruct->CHxNIdleLevel == LEVEL_HIGH)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH0N_IDLE_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH0N_IDLE_POS);
		}
		
		temp = PWMPLUSx->BRK_CTR;
		
		temp &= ~(0x03 << PWMPLUS_BRK_CTR_CH0EN_POS);        //ɲ��ʹ��
		temp |= (PWMPLUS_ChannelInitStruct->Brake_Enable << PWMPLUS_BRK_CTR_CH0EN_POS);
		
		temp &= ~(0x01 << PWMPLUS_BRK_CTR_CH0_POL_POS);      //ɲ�������ƽ
		temp |= (PWMPLUS_ChannelInitStruct->Brake_CHxOutLevel << PWMPLUS_BRK_CTR_CH0_POL_POS);
		
		temp &= ~(0x01 << PWMPLUS_BRK_CTR_CH0N_POL_POS);     //ɲ�������ƽ
		temp |= (PWMPLUS_ChannelInitStruct->Brake_CHxNOutLevel << PWMPLUS_BRK_CTR_CH0N_POL_POS);
		
		PWMPLUSx->BRK_CTR = temp;
		
		
		temp = PWMPLUSx->MSK_EN;
		
		temp &= ~(0x01 << PWMPLUS_MSK_EN_CH0_POS);      //ͨ��x�����Ƿ�ʹ��
		temp |= (PWMPLUS_ChannelInitStruct->Mask_CHx_Enable << PWMPLUS_MSK_EN_CH0_POS);
		
		temp &= ~(0x01 << PWMPLUS_MSK_EN_CH0N_POS);     //ͨ��xN�����Ƿ�ʹ��
		temp |= (PWMPLUS_ChannelInitStruct->Mask_CHxN_Enable << PWMPLUS_MSK_EN_CH0N_POS);
		
		PWMPLUSx->MSK_EN = temp;
		
		temp = PWMPLUSx->MSK_LEVEL;
		
		temp &= ~(0x01 << PWMPLUS_MSK_LEVEL_CH0_POS);      //ͨ��x���������ƽѡ��
		temp |= (PWMPLUS_ChannelInitStruct->Mask_CHx_Level << PWMPLUS_MSK_LEVEL_CH0_POS);
		
		temp &= ~(0x01 << PWMPLUS_MSK_LEVEL_CH0N_POS);     //ͨ��xN���������ƽѡ��
		temp |= (PWMPLUS_ChannelInitStruct->Mask_CHxN_Level << PWMPLUS_MSK_LEVEL_CH0N_POS);
		
		PWMPLUSx->MSK_LEVEL = temp;
		
		
		PWMPLUSx->CH0_COMP = PWMPLUS_ChannelInitStruct->Comp;                  //���÷�ת��
		
		PWMPLUSx->CH0_DEADZONE = PWMPLUS_ChannelInitStruct->DeadZone;          //��������ʱ��
		
		temp = PWMPLUSx->IE;
		
		temp &= ~(0x01 << PWMPLUS_IE_CH0_UP_COMP_POS);            //���ϼ������﷭ת���ж�����
		temp |= (PWMPLUS_ChannelInitStruct->Up_CompIE << PWMPLUS_IE_CH0_UP_COMP_POS);
		
		temp &= ~(0x01 << PWMPLUS_IE_CH0_DOWN_COMP_POS);          //���¼������﷭ת���ж�����
		temp |= (PWMPLUS_ChannelInitStruct->Down_CompIE << PWMPLUS_IE_CH0_DOWN_COMP_POS);
		
		PWMPLUSx->IE = temp;
	}
	
	if((PWMPLUS_ChannelInitStruct->Channel & PWMPLUS_CH1) == PWMPLUS_CH1)
	{
		if(PWMPLUS_ChannelInitStruct->CHxOutEn == ENABLE)    
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH1_OUTEN_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH1_OUTEN_POS);
		}
		
		if(PWMPLUS_ChannelInitStruct->CHxNOutEn == ENABLE)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH1N_OUTEN_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH1N_OUTEN_POS);
		}
		
		if(PWMPLUS_ChannelInitStruct->CHxInv == ENABLE)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH1_INV_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH1_INV_POS);
		}
		
		if(PWMPLUS_ChannelInitStruct->CHxNInv == ENABLE)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH1N_INV_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH1N_INV_POS);
		}
		
		if(PWMPLUS_ChannelInitStruct->StartLevel == LEVEL_HIGH)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH1_START_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH1_START_POS);
		}
		
		if(PWMPLUS_ChannelInitStruct->CHxIdleLevel == LEVEL_HIGH)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH1_IDLE_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH1_IDLE_POS);
		}
		
		if(PWMPLUS_ChannelInitStruct->CHxNIdleLevel == LEVEL_HIGH)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH1N_IDLE_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH1N_IDLE_POS);
		}
		
		temp = PWMPLUSx->BRK_CTR;
		
		temp &= ~(0x07 << PWMPLUS_BRK_CTR_CH1EN_POS);     //ɲ��ʹ��
		temp |= (PWMPLUS_ChannelInitStruct->Brake_Enable << PWMPLUS_BRK_CTR_CH1EN_POS);
		
		temp &= ~(0x01 << PWMPLUS_BRK_CTR_CH1_POL_POS);     //ɲ�������ƽ
		temp |= (PWMPLUS_ChannelInitStruct->Brake_CHxOutLevel << PWMPLUS_BRK_CTR_CH1_POL_POS);
		
		temp &= ~(0x01 << PWMPLUS_BRK_CTR_CH1N_POL_POS);     //ɲ�������ƽ
		temp |= (PWMPLUS_ChannelInitStruct->Brake_CHxNOutLevel << PWMPLUS_BRK_CTR_CH1N_POL_POS);
		
		PWMPLUSx->BRK_CTR = temp;
		
		temp = PWMPLUSx->MSK_EN;
		
		temp &= ~(0x01 << PWMPLUS_MSK_EN_CH1_POS);            //ͨ��x�����Ƿ�ʹ��
		temp |= (PWMPLUS_ChannelInitStruct->Mask_CHx_Enable << PWMPLUS_MSK_EN_CH1_POS);
		
		temp &= ~(0x01 << PWMPLUS_MSK_EN_CH1N_POS);           //ͨ��xN�����Ƿ�ʹ��
		temp |= (PWMPLUS_ChannelInitStruct->Mask_CHxN_Enable << PWMPLUS_MSK_EN_CH1N_POS);
		
		PWMPLUSx->MSK_EN = temp;
		
		temp = PWMPLUSx->MSK_LEVEL;
		
		temp &= ~(0x01 << PWMPLUS_MSK_LEVEL_CH1_POS);      //ͨ��x���������ƽѡ��
		temp |= (PWMPLUS_ChannelInitStruct->Mask_CHx_Level << PWMPLUS_MSK_LEVEL_CH1_POS);
		
		temp &= ~(0x01 << PWMPLUS_MSK_LEVEL_CH1N_POS);     //ͨ��xN���������ƽѡ��
		temp |= (PWMPLUS_ChannelInitStruct->Mask_CHxN_Level << PWMPLUS_MSK_LEVEL_CH1N_POS);
		
		PWMPLUSx->MSK_LEVEL = temp;
		
		PWMPLUSx->CH1_COMP = PWMPLUS_ChannelInitStruct->Comp;              //���÷�ת��
		
		PWMPLUSx->CH1_DEADZONE = PWMPLUS_ChannelInitStruct->DeadZone;      //��������ʱ��
		
		temp = PWMPLUSx->IE;
		
		temp &= ~(0x01 << PWMPLUS_IE_CH1_UP_COMP_POS);            //���ϼ������﷭ת���ж�����
		temp |= (PWMPLUS_ChannelInitStruct->Up_CompIE << PWMPLUS_IE_CH1_UP_COMP_POS);
		
		temp &= ~(0x01 << PWMPLUS_IE_CH1_DOWN_COMP_POS);          //���¼������﷭ת���ж�����
		temp |= (PWMPLUS_ChannelInitStruct->Down_CompIE << PWMPLUS_IE_CH1_DOWN_COMP_POS);
		
		PWMPLUSx->IE = temp;
	}
	
	if((PWMPLUS_ChannelInitStruct->Channel & PWMPLUS_CH2) == PWMPLUS_CH2)
	{
		if(PWMPLUS_ChannelInitStruct->CHxOutEn == ENABLE)    
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH2_OUTEN_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH2_OUTEN_POS);
		}
		
		if(PWMPLUS_ChannelInitStruct->CHxNOutEn == ENABLE)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH2N_OUTEN_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH2N_OUTEN_POS);
		}
		
		if(PWMPLUS_ChannelInitStruct->CHxInv == ENABLE)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH2_INV_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH2_INV_POS);
		}
		
		if(PWMPLUS_ChannelInitStruct->CHxNInv == ENABLE)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH2N_INV_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH2N_INV_POS);
		}
		
		if(PWMPLUS_ChannelInitStruct->StartLevel == LEVEL_HIGH)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH2_START_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH2_START_POS);
		}
		
		if(PWMPLUS_ChannelInitStruct->CHxIdleLevel == LEVEL_HIGH)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH2_IDLE_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH2_IDLE_POS);
		}
		
		if(PWMPLUS_ChannelInitStruct->CHxNIdleLevel == LEVEL_HIGH)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH2N_IDLE_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH2N_IDLE_POS);
		}
		
		temp = PWMPLUSx->BRK_CTR;
		
		temp &= ~(0x07 << PWMPLUS_BRK_CTR_CH2EN_POS);     //ɲ��ʹ��
		temp |= (PWMPLUS_ChannelInitStruct->Brake_Enable << PWMPLUS_BRK_CTR_CH2EN_POS);
		
		temp &= ~(0x01 << PWMPLUS_BRK_CTR_CH2_POL_POS);     //ɲ�������ƽ
		temp |= (PWMPLUS_ChannelInitStruct->Brake_CHxOutLevel << PWMPLUS_BRK_CTR_CH2_POL_POS);
		
		temp &= ~(0x01 << PWMPLUS_BRK_CTR_CH2N_POL_POS);    //ɲ�������ƽ
		temp |= (PWMPLUS_ChannelInitStruct->Brake_CHxNOutLevel << PWMPLUS_BRK_CTR_CH2N_POL_POS);
		
		PWMPLUSx->BRK_CTR = temp;
		
		temp = PWMPLUSx->MSK_EN;
		
		temp &= ~(0x01 << PWMPLUS_MSK_EN_CH2_POS);      //ͨ��x�����Ƿ�ʹ��
		temp |= (PWMPLUS_ChannelInitStruct->Mask_CHx_Enable << PWMPLUS_MSK_EN_CH2_POS);
		
		temp &= ~(0x01 << PWMPLUS_MSK_EN_CH2N_POS);     //ͨ��xN�����Ƿ�ʹ��
		temp |= (PWMPLUS_ChannelInitStruct->Mask_CHxN_Enable << PWMPLUS_MSK_EN_CH2N_POS);
		
		PWMPLUSx->MSK_EN = temp;
		
		temp = PWMPLUSx->MSK_LEVEL;
		
		temp &= ~(0x01 << PWMPLUS_MSK_LEVEL_CH2_POS);      //ͨ��x���������ƽѡ��
		temp |= (PWMPLUS_ChannelInitStruct->Mask_CHx_Level << PWMPLUS_MSK_LEVEL_CH2_POS);
		
		temp &= ~(0x01 << PWMPLUS_MSK_LEVEL_CH2N_POS);     //ͨ��xN���������ƽѡ��
		temp |= (PWMPLUS_ChannelInitStruct->Mask_CHxN_Level << PWMPLUS_MSK_LEVEL_CH2N_POS);
		
		PWMPLUSx->MSK_LEVEL = temp;
		
		PWMPLUSx->CH2_COMP = PWMPLUS_ChannelInitStruct->Comp;                  //���÷�ת��
		
		PWMPLUSx->CH2_DEADZONE = PWMPLUS_ChannelInitStruct->DeadZone;          //��������ʱ��
		
		temp = PWMPLUSx->IE;
		
		temp &= ~(0x01 << PWMPLUS_IE_CH2_UP_COMP_POS);            //���ϼ������﷭ת���ж�����
		temp |= (PWMPLUS_ChannelInitStruct->Up_CompIE << PWMPLUS_IE_CH2_UP_COMP_POS);
		
		temp &= ~(0x01 << PWMPLUS_IE_CH2_DOWN_COMP_POS);          //���¼������﷭ת���ж�����
		temp |= (PWMPLUS_ChannelInitStruct->Down_CompIE << PWMPLUS_IE_CH2_DOWN_COMP_POS);
		
		PWMPLUSx->IE = temp;
	}
	
	switch((uint32_t)PWMPLUSx)
	{
		case((uint32_t)PWMPLUS0):
		
			if(PWMPLUSx->IE != 0)
			{
				NVIC_EnableIRQ(PWMPLUS0_IRQn);
			}
		
		break;
	}
	
	PWMPLUSx->IF = 0xFFFFF;
}


/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_Start()
* ����˵��:	����PWMPLUS����ʼPWM���
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_Start(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                                      //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�   
	
	PWMPLUSx->CTR |= 0x01 << PWMPLUS_CTR_EN_POS; 
}


/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_Stop()
* ����˵��:	�ر�PWMPLUS��ֹͣPWM���
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_Stop(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                                      //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�   
	
	PWMPLUSx->CTR &= ~(0x01 << PWMPLUS_CTR_EN_POS);  
}

/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_SetClk_Src()
* ����˵��:	PWMPLUSʱ��ѡ��   
* ��    ��: PWMPLUS_Clk_Src_TypeDef Clk_Src  
*			
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_SetClk_Src(PWMPLUS_TypeDef * PWMPLUSx,PWMPLUS_Clk_Src_TypeDef Clk_Src)
{
	uint32_t temp = 0;
	
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                      //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_PWMPLUS_CLKSRC(Clk_Src));                    //�������Ĳ���Clk_Src�Ƿ�Ϸ�   
	
	temp = PWMPLUSx->CLK;
	
	PWMPLUSx->CLK &= ~(0x07 << PWMPLUS_CLK_SRC_POS);             //PWMPLUSʱ��ѡ��   
	PWMPLUSx->CLK |= ((Clk_Src) << PWMPLUS_CLK_SRC_POS);
	
	PWMPLUSx->CLK = temp;
}

/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_SetClkDiv()
* ����˵��:	����Ԥ��Ƶϵ��   ʵ�ʷ�ƵΪ����ֵ��1
* ��    ��: uint8_t Clk_Div   
*			
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_SetClkDiv(PWMPLUS_TypeDef * PWMPLUSx,uint8_t ClkDiv)
{
	uint32_t temp = 0;
	
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                         //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_PWMPLUS_CLKDIV(ClkDiv));                        //�������Ĳ���ClkDiv�Ƿ�Ϸ�   
	
	temp = PWMPLUSx->CLK;
	
	temp &= ~((0xFFFF << PWMPLUS_CLK_PREDIV_POS));             
	temp |= ((ClkDiv) << PWMPLUS_CLK_PREDIV_POS);            //ʱ�ӷ�Ƶ   ʵ�ʷ�ƵΪ����ֵ��1
	
	PWMPLUSx->CLK = temp;
}

/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_SetMode()
* ����˵��:	���ù���ģʽ
* ��    ��: PWMPLUS_Mode_TypeDef Mode 
*			
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_SetMode(PWMPLUS_TypeDef * PWMPLUSx,PWMPLUS_Mode_TypeDef Mode)
{
	uint32_t temp = 0;
	
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_PWMPLUS_MODE(Mode));                 //�������Ĳ���Mode�Ƿ�Ϸ�  
	
	temp = PWMPLUSx->CTR;
	
	temp &= ~(0x03 << PWMPLUS_CTR_OPM_POS);
	temp |= (Mode << PWMPLUS_CTR_OPM_POS);	
	
	PWMPLUSx->CTR = temp;
}

/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_SetDir()
* ����˵��:	���ü�������
* ��    ��: PWMPLUS_Dir_TypeDef Dir
*			
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_SetDir(PWMPLUS_TypeDef * PWMPLUSx,PWMPLUS_Dir_TypeDef Dir)
{
	uint32_t temp = 0;
	
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_PWMPLUS_DIR(Dir));                   //�������Ĳ���Dir�Ƿ�Ϸ�  
	
	temp = PWMPLUSx->CTR;
	
	temp &= ~(0x01 << PWMPLUS_CTR_DIR_POS);
	temp |= (Dir << PWMPLUS_CTR_DIR_POS);	
	
	PWMPLUSx->CTR = temp;
}

/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_SetReload_Cnt()
* ����˵��:	�����Զ�װ�ش���   ʵ��װ�ش���Ϊ����ֵ��1
* ��    ��: uint8_t Reload_Cnt
*			
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_SetReload_Cnt(PWMPLUS_TypeDef * PWMPLUSx,uint8_t Reload_Cnt)
{
	uint32_t temp = 0;
	
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                         //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_PWMPLUS_RELOAD_CNT(Reload_Cnt));                //�������Ĳ���Reload_Cnt�Ƿ�Ϸ�  
	
	temp = PWMPLUSx->CTR;
	
	temp &= ~(0xFF << PWMPLUS_CTR_RELOAD_POS);
	temp |= (Reload_Cnt << PWMPLUS_CTR_RELOAD_POS);	                //�Զ�װ�ش���   ʵ��װ�ش���Ϊ����ֵ��1
	
	PWMPLUSx->CTR = temp;
}

/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_SetBrake_Filter()
* ����˵��:	����ɲ���˲�
* ��    ��: PWMPLUS_BrakeFilter_TypeDef Brake_Filter
*			
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_SetBrake_Filter(PWMPLUS_TypeDef * PWMPLUSx,PWMPLUS_BrakeFilter_TypeDef Brake_Filter)
{
	uint32_t temp = 0;
	
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_PWMPLUS_BRAKE_FILTER(Brake_Filter));                 //�������Ĳ���Brake_Filter�Ƿ�Ϸ�  
	
	temp = PWMPLUSx->BRK_CTR;
	
	temp &= ~(0x03 << PWMPLUS_BRK_CTR_FILTER_POS);                       //ɲ���˲�
	temp |= (Brake_Filter << PWMPLUS_BRK_CTR_FILTER_POS);
	
	PWMPLUSx->BRK_CTR = temp;
}

/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_SetBrake_InputLevel()
* ����˵��:	����ɲ��������Ч��ƽѡ�� 
* ��    ��: PWMPLUS_BrakeLevel_TypeDef Brake_InputLevel
*			
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_SetBrake_InputLevel(PWMPLUS_TypeDef * PWMPLUSx,PWMPLUS_BrakeLevel_TypeDef Brake_InputLevel)
{
	uint32_t temp = 0;
	
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_PWMPLUS_BRAKE_LEVEL(Brake_InputLevel));              //�������Ĳ���Brake_InputLevel�Ƿ�Ϸ�  
	
	temp = PWMPLUSx->BRK_CTR;
	
	temp &= ~(0x03 << PWMPLUS_BRK_CTR_INLEV_POS);           //ɲ��������Ч��ƽѡ�� 
	temp |= (Brake_InputLevel << PWMPLUS_BRK_CTR_INLEV_POS);
	
	PWMPLUSx->BRK_CTR = temp;
}

/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_SetBrake_Enable()
* ����˵��:	����ɲ��ʹ��
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx          ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
*           uint8_t CHx                         ͨ��ѡ��  ���Զ�ͨ�����в��� ����  PWMPLUS_CH0 | PWMPLUS_CH1
*		    PWMPLUS_BrakeLevel_TypeDef Brake_InputLevel		    
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_SetBrake_Enable(PWMPLUS_TypeDef * PWMPLUSx,uint8_t CHx,PWMPLUS_BrakeEnable_TypeDef Brake_Enable)
{
	uint32_t temp = 0;
	
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_PWMPLUS_CHANNEL_HALF(CHx));                          //�������Ĳ���CHx�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_BRAKE_ENABLE(Brake_Enable));                 //�������Ĳ���Brake_Enable�Ƿ�Ϸ�  
	
	if((CHx & PWMPLUS_CH0) == PWMPLUS_CH0) 
	{
		temp = PWMPLUSx->BRK_CTR;
		
		temp &= ~(0x03 << PWMPLUS_BRK_CTR_CH0EN_POS);          
		temp |= (Brake_Enable << PWMPLUS_BRK_CTR_CH0EN_POS);
		
		PWMPLUSx->BRK_CTR = temp;
	}
	
	if((CHx & PWMPLUS_CH1) == PWMPLUS_CH1) 
	{
		temp = PWMPLUSx->BRK_CTR;
		
		temp &= ~(0x03 << PWMPLUS_BRK_CTR_CH1EN_POS);          
		temp |= (Brake_Enable << PWMPLUS_BRK_CTR_CH1EN_POS);
		
		PWMPLUSx->BRK_CTR = temp;
	}
	
	if((CHx & PWMPLUS_CH2) == PWMPLUS_CH2) 
	{
		temp = PWMPLUSx->BRK_CTR;
		
		temp &= ~(0x03 << PWMPLUS_BRK_CTR_CH2EN_POS);          
		temp |= (Brake_Enable << PWMPLUS_BRK_CTR_CH2EN_POS);
		
		PWMPLUSx->BRK_CTR = temp;
	}	
}

/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_SetBrake_OutLevel()
* ����˵��:	����ɲ��ʱͨ�������ƽ
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx          ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
*           uint8_t CHx                         ͨ��ѡ��  ���Զ�ͨ�����в��� ����  PWMPLUS_CH0 | PWMPLUS_CH1
*		    PWMPLUS_Level_TypeDef Brake_OutLevel		    
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_SetBrake_OutLevel(PWMPLUS_TypeDef * PWMPLUSx,uint8_t CHx,PWMPLUS_Level_TypeDef Brake_OutLevel)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_PWMPLUS_CHANNEL_ALL(CHx));                           //�������Ĳ���CHx�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_BRAKE_OUTLEVEL(Brake_OutLevel));             //�������Ĳ���Brake_OutLevel�Ƿ�Ϸ�  
	
	if((CHx & PWMPLUS_CH0) == PWMPLUS_CH0) 
	{
		if(Brake_OutLevel == LEVEL_LOW)
		{
			PWMPLUSx->BRK_CTR &= ~(0x01 << PWMPLUS_BRK_CTR_CH0_POL_POS); 
		}
		else if(Brake_OutLevel == LEVEL_HIGH)
		{
			PWMPLUSx->BRK_CTR |= (0x01 << PWMPLUS_BRK_CTR_CH0_POL_POS);
		}        
	}
	
	if((CHx & PWMPLUS_CH1) == PWMPLUS_CH1) 
	{
		if(Brake_OutLevel == LEVEL_LOW)
		{
			PWMPLUSx->BRK_CTR &= ~(0x01 << PWMPLUS_BRK_CTR_CH1_POL_POS); 
		}
		else if(Brake_OutLevel == LEVEL_HIGH)
		{
			PWMPLUSx->BRK_CTR |= (0x01 << PWMPLUS_BRK_CTR_CH1_POL_POS);
		}   
	}
	
	if((CHx & PWMPLUS_CH2) == PWMPLUS_CH2) 
	{
		if(Brake_OutLevel == LEVEL_LOW)
		{
			PWMPLUSx->BRK_CTR &= ~(0x01 << PWMPLUS_BRK_CTR_CH2_POL_POS); 
		}
		else if(Brake_OutLevel == LEVEL_HIGH)
		{
			PWMPLUSx->BRK_CTR |= (0x01 << PWMPLUS_BRK_CTR_CH2_POL_POS);
		}   
	}	
	
	if((CHx & PWMPLUS_CH0N) == PWMPLUS_CH0N) 
	{
		if(Brake_OutLevel == LEVEL_LOW)
		{
			PWMPLUSx->BRK_CTR &= ~(0x01 << PWMPLUS_BRK_CTR_CH0N_POL_POS); 
		}
		else if(Brake_OutLevel == LEVEL_HIGH)
		{
			PWMPLUSx->BRK_CTR |= (0x01 << PWMPLUS_BRK_CTR_CH0N_POL_POS);
		}   
	}
	
	if((CHx & PWMPLUS_CH1N) == PWMPLUS_CH1N) 
	{
		if(Brake_OutLevel == LEVEL_LOW)
		{
			PWMPLUSx->BRK_CTR &= ~(0x01 << PWMPLUS_BRK_CTR_CH1N_POL_POS); 
		}
		else if(Brake_OutLevel == LEVEL_HIGH)
		{
			PWMPLUSx->BRK_CTR |= (0x01 << PWMPLUS_BRK_CTR_CH1N_POL_POS);
		}   
	}
	
	if((CHx & PWMPLUS_CH2N) == PWMPLUS_CH2N) 
	{
		if(Brake_OutLevel == LEVEL_LOW)
		{
			PWMPLUSx->BRK_CTR &= ~(0x01 << PWMPLUS_BRK_CTR_CH2N_POL_POS); 
		}
		else if(Brake_OutLevel == LEVEL_HIGH)
		{
			PWMPLUSx->BRK_CTR |= (0x01 << PWMPLUS_BRK_CTR_CH2N_POL_POS);
		}   
	}	
}


/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_SetMask_Enable()
* ����˵��:	�������ι����Ƿ�ʹ��
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx          ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
*           uint8_t CHx                         ͨ��ѡ��  ���Զ�ͨ�����в��� ����  PWMPLUS_CH0 | PWMPLUS_CH1
*		    FunctionalState Mask_Enable		    
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_SetMask_Enable(PWMPLUS_TypeDef * PWMPLUSx,uint8_t CHx,FunctionalState Mask_Enable)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_PWMPLUS_CHANNEL_ALL(CHx));                           //�������Ĳ���CHx�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_MASK_EN(Mask_Enable));                       //�������Ĳ���Mask_Enable�Ƿ�Ϸ�  
	
	if((CHx & PWMPLUS_CH0) == PWMPLUS_CH0) 
	{
		if(Mask_Enable == DISABLE)
		{
			PWMPLUSx->MSK_EN &= ~(0x01 << PWMPLUS_MSK_EN_CH0_POS);    
		}
		else if(Mask_Enable == ENABLE)
		{
			PWMPLUSx->MSK_EN |= (0x01 << PWMPLUS_MSK_EN_CH0_POS);
		} 
	}
	
	if((CHx & PWMPLUS_CH1) == PWMPLUS_CH1) 
	{
		if(Mask_Enable == DISABLE)
		{
			PWMPLUSx->MSK_EN &= ~(0x01 << PWMPLUS_MSK_EN_CH1_POS);    
		}
		else if(Mask_Enable == ENABLE)
		{
			PWMPLUSx->MSK_EN |= (0x01 << PWMPLUS_MSK_EN_CH1_POS);
		} 
	}
	
	if((CHx & PWMPLUS_CH2) == PWMPLUS_CH2) 
	{
		if(Mask_Enable == DISABLE)
		{
			PWMPLUSx->MSK_EN &= ~(0x01 << PWMPLUS_MSK_EN_CH2_POS);    
		}
		else if(Mask_Enable == ENABLE)
		{
			PWMPLUSx->MSK_EN |= (0x01 << PWMPLUS_MSK_EN_CH2_POS);
		} 
	}
	
	if((CHx & PWMPLUS_CH0N) == PWMPLUS_CH0N) 
	{
		if(Mask_Enable == DISABLE)
		{
			PWMPLUSx->MSK_EN &= ~(0x01 << PWMPLUS_MSK_EN_CH0N_POS);    
		}
		else if(Mask_Enable == ENABLE)
		{
			PWMPLUSx->MSK_EN |= (0x01 << PWMPLUS_MSK_EN_CH0N_POS);
		} 
	}
	
	if((CHx & PWMPLUS_CH1N) == PWMPLUS_CH1N) 
	{
		if(Mask_Enable == DISABLE)
		{
			PWMPLUSx->MSK_EN &= ~(0x01 << PWMPLUS_MSK_EN_CH1N_POS);    
		}
		else if(Mask_Enable == ENABLE)
		{
			PWMPLUSx->MSK_EN |= (0x01 << PWMPLUS_MSK_EN_CH1N_POS);
		} 
	}
	
	if((CHx & PWMPLUS_CH2N) == PWMPLUS_CH2N) 
	{
		if(Mask_Enable == DISABLE)
		{
			PWMPLUSx->MSK_EN &= ~(0x01 << PWMPLUS_MSK_EN_CH2N_POS);    
		}
		else if(Mask_Enable == ENABLE)
		{
			PWMPLUSx->MSK_EN |= (0x01 << PWMPLUS_MSK_EN_CH2N_POS);
		} 
	}
}

/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_SetMask_Level()
* ����˵��:	�������������ƽ
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx          ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
*           uint8_t CHx                         ͨ��ѡ��  ���Զ�ͨ�����в��� ����  PWMPLUS_CH0 | PWMPLUS_CH1
*		    PWMPLUS_Level_TypeDef Mask_Level		    
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_SetMask_Level(PWMPLUS_TypeDef * PWMPLUSx,uint8_t CHx,PWMPLUS_Level_TypeDef Mask_Level)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_PWMPLUS_CHANNEL_ALL(CHx));                           //�������Ĳ���CHx�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_MASK_LEVEL(Mask_Level));                     //�������Ĳ���Mask_Level�Ƿ�Ϸ�  
	
	if((CHx & PWMPLUS_CH0) == PWMPLUS_CH0) 
	{
		if(Mask_Level == LEVEL_LOW)
		{
			PWMPLUSx->MSK_LEVEL &= ~(0x01 << PWMPLUS_MSK_LEVEL_CH0_POS); 
		}
		else if(Mask_Level == LEVEL_HIGH)
		{
			PWMPLUSx->MSK_LEVEL |= (0x01 << PWMPLUS_MSK_LEVEL_CH0_POS);
		}   
	}
	
	if((CHx & PWMPLUS_CH1) == PWMPLUS_CH1) 
	{
		if(Mask_Level == LEVEL_LOW)
		{
			PWMPLUSx->MSK_LEVEL &= ~(0x01 << PWMPLUS_MSK_LEVEL_CH1_POS); 
		}
		else if(Mask_Level == LEVEL_HIGH)
		{
			PWMPLUSx->MSK_LEVEL |= (0x01 << PWMPLUS_MSK_LEVEL_CH1_POS);
		}   
	}
	
	if((CHx & PWMPLUS_CH2) == PWMPLUS_CH2) 
	{
		if(Mask_Level == LEVEL_LOW)
		{
			PWMPLUSx->MSK_LEVEL &= ~(0x01 << PWMPLUS_MSK_LEVEL_CH2_POS); 
		}
		else if(Mask_Level == LEVEL_HIGH)
		{
			PWMPLUSx->MSK_LEVEL |= (0x01 << PWMPLUS_MSK_LEVEL_CH2_POS);
		}   
	}
	
	if((CHx & PWMPLUS_CH0N) == PWMPLUS_CH0N) 
	{
		if(Mask_Level == LEVEL_LOW)
		{
			PWMPLUSx->MSK_LEVEL &= ~(0x01 << PWMPLUS_MSK_LEVEL_CH0N_POS); 
		}
		else if(Mask_Level == LEVEL_HIGH)
		{
			PWMPLUSx->MSK_LEVEL |= (0x01 << PWMPLUS_MSK_LEVEL_CH0N_POS);
		}   
	}
	
	if((CHx & PWMPLUS_CH1N) == PWMPLUS_CH1N) 
	{
		if(Mask_Level == LEVEL_LOW)
		{
			PWMPLUSx->MSK_LEVEL &= ~(0x01 << PWMPLUS_MSK_LEVEL_CH1N_POS); 
		}
		else if(Mask_Level == LEVEL_HIGH)
		{
			PWMPLUSx->MSK_LEVEL |= (0x01 << PWMPLUS_MSK_LEVEL_CH1N_POS);
		}   
	}
	
	if((CHx & PWMPLUS_CH2N) == PWMPLUS_CH2N) 
	{
		if(Mask_Level == LEVEL_LOW)
		{
			PWMPLUSx->MSK_LEVEL &= ~(0x01 << PWMPLUS_MSK_LEVEL_CH2N_POS); 
		}
		else if(Mask_Level == LEVEL_HIGH)
		{
			PWMPLUSx->MSK_LEVEL |= (0x01 << PWMPLUS_MSK_LEVEL_CH2N_POS);
		}   
	}
}

/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_SetStartLevel()
* ����˵��:	PWMPLUS������ʼ�����ƽ
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx          ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
*           uint8_t CHx                         ͨ��ѡ��  ���Զ�ͨ�����в��� ����  PWMPLUS_CH0 | PWMPLUS_CH1
*           PWMPLUS_Level_TypeDef StartLevel    ������ʼ�����ƽ
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_SetStartLevel(PWMPLUS_TypeDef * PWMPLUSx,uint8_t CHx,PWMPLUS_Level_TypeDef StartLevel)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_PWMPLUS_CHANNEL_HALF(CHx));                          //�������Ĳ���CHx�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_START_LEVEL(StartLevel));                    //�������Ĳ���StartLevel�Ƿ�Ϸ�  
	
	if((CHx & PWMPLUS_CH0) == PWMPLUS_CH0) 
	{
		if(StartLevel == LEVEL_HIGH)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH0_START_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH0_START_POS);
		}
	}
	
	if((CHx & PWMPLUS_CH1) == PWMPLUS_CH1) 
	{
		if(StartLevel == LEVEL_HIGH)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH1_START_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH1_START_POS);
		}
	}
	
	if((CHx & PWMPLUS_CH2) == PWMPLUS_CH2) 
	{
		if(StartLevel == LEVEL_HIGH)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH2_START_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH2_START_POS);
		}
	}
}

/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_SetIdleLevel()
* ����˵��:	PWMPLUS���������ƽ����
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx         ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
*           uint8_t CHx                        ͨ��ѡ��  ���Զ�ͨ�����в��� ����  PWMPLUS_CH0 | PWMPLUS_CH0N | PWMPLUS_CH1
*           PWMPLUS_Level_TypeDef  IdleLevel   ��Чֵ����LEVEL_LOW  LEVEL_HIGH
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_SetIdleLevel(PWMPLUS_TypeDef * PWMPLUSx,uint8_t CHx,PWMPLUS_Level_TypeDef  IdleLevel)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_PWMPLUS_CHANNEL_ALL(CHx));                           //�������Ĳ���CHx�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_IDLE_LEVEL(IdleLevel));                      //�������Ĳ���IdleLevel�Ƿ�Ϸ�  
	
	if((CHx & PWMPLUS_CH0) == PWMPLUS_CH0) 
	{
		if(IdleLevel == LEVEL_HIGH)
		{
			PWMPLUSx->OUTCTR |= 0x01 << PWMPLUS_OUTCTR_CH0_IDLE_POS;
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH0_IDLE_POS);
		}
	}
	
	if((CHx & PWMPLUS_CH1) == PWMPLUS_CH1) 
	{
		if(IdleLevel == LEVEL_HIGH)
		{
			PWMPLUSx->OUTCTR |= 0x01 << PWMPLUS_OUTCTR_CH1_IDLE_POS;
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH1_IDLE_POS);
		}
	}
	
	if((CHx & PWMPLUS_CH2) == PWMPLUS_CH2) 
	{
		if(IdleLevel == LEVEL_HIGH)
		{
			PWMPLUSx->OUTCTR |= 0x01 << PWMPLUS_OUTCTR_CH2_IDLE_POS;
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH2_IDLE_POS);
		}
	}
	
	if((CHx & PWMPLUS_CH0N) == PWMPLUS_CH0N) 
	{
		if(IdleLevel == LEVEL_HIGH)
		{
			PWMPLUSx->OUTCTR |= 0x01 << PWMPLUS_OUTCTR_CH0N_IDLE_POS;
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH0N_IDLE_POS);
		}
	}
	
	if((CHx & PWMPLUS_CH1N) == PWMPLUS_CH1N) 
	{
		if(IdleLevel == LEVEL_HIGH)
		{
			PWMPLUSx->OUTCTR |= 0x01 << PWMPLUS_OUTCTR_CH1N_IDLE_POS;
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH1N_IDLE_POS);
		}
	}
	
	if((CHx & PWMPLUS_CH2N) == PWMPLUS_CH2N) 
	{
		if(IdleLevel == LEVEL_HIGH)
		{
			PWMPLUSx->OUTCTR |= 0x01 << PWMPLUS_OUTCTR_CH2N_IDLE_POS;
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH2N_IDLE_POS);
		}
	}
}

/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_SetOutEn()
* ����˵��:	PWMPLUS���ʹ��
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx     ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
*           uint8_t CHx                    ͨ��ѡ��  ���Զ�ͨ�����в��� ����  PWMPLUS_CH0 | PWMPLUS_CH0N | PWMPLUS_CH1
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_SetOutEn(PWMPLUS_TypeDef * PWMPLUSx,uint8_t CHx,FunctionalState  OutEn)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_PWMPLUS_CHANNEL_ALL(CHx));                           //�������Ĳ���CHx�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_OUTEN(OutEn));                               //�������Ĳ���OutEn�Ƿ�Ϸ�  
	
	if((CHx & PWMPLUS_CH0) == PWMPLUS_CH0) 
	{
		if(OutEn == ENABLE)
		{
			PWMPLUSx->OUTCTR |= 0x01 << PWMPLUS_OUTCTR_CH0_OUTEN_POS;
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH0_OUTEN_POS);
		}
	}
	
	if((CHx & PWMPLUS_CH1) == PWMPLUS_CH1) 
	{
		if(OutEn == ENABLE)
		{
			PWMPLUSx->OUTCTR |= 0x01 << PWMPLUS_OUTCTR_CH1_OUTEN_POS;
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH1_OUTEN_POS);
		}
	}
	
	if((CHx & PWMPLUS_CH2) == PWMPLUS_CH2) 
	{
		if(OutEn == ENABLE)
		{
			PWMPLUSx->OUTCTR |= 0x01 << PWMPLUS_OUTCTR_CH2_OUTEN_POS;
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH2_OUTEN_POS);
		}
	}
	
	if((CHx & PWMPLUS_CH0N) == PWMPLUS_CH0N) 
	{
		if(OutEn == ENABLE)
		{
			PWMPLUSx->OUTCTR |= 0x01 << PWMPLUS_OUTCTR_CH0N_OUTEN_POS;
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH0N_OUTEN_POS);
		}
	}
	
	if((CHx & PWMPLUS_CH1N) == PWMPLUS_CH1N) 
	{
		if(OutEn == ENABLE)
		{
			PWMPLUSx->OUTCTR |= 0x01 << PWMPLUS_OUTCTR_CH1N_OUTEN_POS;
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH1N_OUTEN_POS);
		}
	}
	
	if((CHx & PWMPLUS_CH2N) == PWMPLUS_CH2N) 
	{
		if(OutEn == ENABLE)
		{
			PWMPLUSx->OUTCTR |= 0x01 << PWMPLUS_OUTCTR_CH2N_OUTEN_POS;
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH2N_OUTEN_POS);
		}
	}
}

/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_SetOutInv()
* ����˵��:	PWMPLUS����źŷ�ת
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx     ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
*           uint8_t CHx                    ͨ��ѡ��  ���Զ�ͨ�����в��� ����  PWMPLUS_CH0 | PWMPLUS_CH0N | PWMPLUS_CH1
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_SetOutInv(PWMPLUS_TypeDef * PWMPLUSx,uint8_t CHx,FunctionalState  OutInv)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_PWMPLUS_CHANNEL_ALL(CHx));                           //�������Ĳ���CHx�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_OUTINV(OutInv));                             //�������Ĳ���OutInv�Ƿ�Ϸ�  

	if((CHx & PWMPLUS_CH0) == PWMPLUS_CH0) 
	{
		if(OutInv == ENABLE)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH0_INV_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH0_INV_POS);
		}	
	}
	
	if((CHx & PWMPLUS_CH1) == PWMPLUS_CH1) 
	{
		if(OutInv == ENABLE)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH1_INV_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH1_INV_POS);
		}	
	}
	
	if((CHx & PWMPLUS_CH2) == PWMPLUS_CH2) 
	{
		if(OutInv == ENABLE)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH2_INV_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH2_INV_POS);
		}	
	}
	
	if((CHx & PWMPLUS_CH0N) == PWMPLUS_CH0N) 
	{
		if(OutInv == ENABLE)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH0N_INV_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH0N_INV_POS);
		}	
	}
	
	if((CHx & PWMPLUS_CH1N) == PWMPLUS_CH1N) 
	{
		if(OutInv == ENABLE)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH1N_INV_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH1N_INV_POS);
		}	
	}
	
	if((CHx & PWMPLUS_CH2N) == PWMPLUS_CH2N) 
	{
		if(OutInv == ENABLE)
		{
			PWMPLUSx->OUTCTR |= (0x01 << PWMPLUS_OUTCTR_CH2N_INV_POS);
		}
		else
		{
			PWMPLUSx->OUTCTR &= ~(0x01 << PWMPLUS_OUTCTR_CH2N_INV_POS);
		}	
	}
}



/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_SetPeriod()
* ����˵��:	��������
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
*			uint16_t Period			            Ҫ�趨������ֵ,16λ
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_SetPeriod(PWMPLUS_TypeDef * PWMPLUSx, uint16_t Period)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                            //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_PWMPLUS_PERIOD(Period));                           //�������Ĳ���CHx�Ƿ�Ϸ�  
	
	if(Period == 0)
	{
		Period = 0xFFFF;
	}
	
	PWMPLUSx->PERIOD = Period;      //ʵ������Ϊ����ֵ��1
}


/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_GetPeriod()
* ����˵��:	��ȡ����
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
* ��    ��: ����ֵ
* ע������: ��
******************************************************************************************************************************************/
uint32_t PWMPLUS_GetPeriod(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                            //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�   
	
	return PWMPLUSx->PERIOD;
}

/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_SetComp()
* ����˵��:	���÷�ת��
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
*           uint8_t CHx                         PWMPLUS_CH0    PWMPLUS_CH1   PWMPLUS_CH2
*			uint16_t Comp			            Ҫ�趨�ķ�ת��,16λ
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_SetComp(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx,uint16_t Comp)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_PWMPLUS_CHANNEL_HALF(CHx));                          //�������Ĳ���CHx�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_COMP(Comp));                                 //�������Ĳ���Comp�Ƿ�Ϸ�  

	if(Comp > PWMPLUS_GetPeriod(PWMPLUSx))
	{
		Comp = 0;
	}
	
	if((CHx & PWMPLUS_CH0) == PWMPLUS_CH0) 
	{
		PWMPLUSx->CH0_COMP  = Comp;
	}
	
	if((CHx & PWMPLUS_CH1) == PWMPLUS_CH1) 
	{
		PWMPLUSx->CH1_COMP  = Comp;
	}
	
	if((CHx & PWMPLUS_CH2) == PWMPLUS_CH2) 
	{
		PWMPLUSx->CH2_COMP  = Comp;
	}
}


/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_GetComp()
* ����˵��:	��ȡ���õķ�ת��
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
*           uint8_t CHx                         PWMPLUS_CH0    PWMPLUS_CH1   PWMPLUS_CH2
* ��    ��: �������õķ�ת��
* ע������: ��
******************************************************************************************************************************************/
uint32_t PWMPLUS_GetComp(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_PWMPLUS_CHANNEL_HALF(CHx));                          //�������Ĳ���CHx�Ƿ�Ϸ�  
	
	if(CHx == PWMPLUS_CH0) 
	{
		return PWMPLUSx->CH0_COMP;
	}
	else if(CHx == PWMPLUS_CH1) 
	{
		return PWMPLUSx->CH1_COMP;
	}
	else if(CHx == PWMPLUS_CH2) 
	{
		return PWMPLUSx->CH2_COMP;
	}
	
	return 0;
}


/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_SetDeadZone()
* ����˵��:	����ͨ����������
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
*           uint8_t CHx                         PWMPLUS_CH0    PWMPLUS_CH1   PWMPLUS_CH2
*			uint16_t DeadZone			        Ҫ�趨����������,10λ
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_SetDeadZone(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx,uint16_t DeadZone)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_PWMPLUS_CHANNEL_HALF(CHx));                          //�������Ĳ���CHx�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_DEADZONE(DeadZone));                         //�������Ĳ���DeadZone�Ƿ�Ϸ�  

	if(DeadZone > PWMPLUS_GetComp(PWMPLUSx,CHx))
	{
		DeadZone = PWMPLUS_GetComp(PWMPLUSx,CHx);
		
		if(DeadZone > 1023)
		{
			DeadZone = 1023;
		}
	}
	
	if((CHx & PWMPLUS_CH0) == PWMPLUS_CH0) 
	{
		PWMPLUSx->CH0_DEADZONE  = DeadZone;
	}
	
	if((CHx & PWMPLUS_CH1) == PWMPLUS_CH1) 
	{
		PWMPLUSx->CH1_DEADZONE  = DeadZone;
	}
	
	if((CHx & PWMPLUS_CH2) == PWMPLUS_CH2) 
	{
		PWMPLUSx->CH2_DEADZONE  = DeadZone;
	}
}


/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_GetDeadZone()
* ����˵��:	��ȡͨ����������
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
*           uint8_t CHx                         PWMPLUS_CH0    PWMPLUS_CH1   PWMPLUS_CH2
* ��    ��: �������õ�ͨ����������
* ע������: ��
******************************************************************************************************************************************/
uint16_t PWMPLUS_GetDeadZone(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_PWMPLUS_CHANNEL_HALF(CHx));                          //�������Ĳ���CHx�Ƿ�Ϸ�  
	
	if(CHx == PWMPLUS_CH0) 
	{
		return PWMPLUSx->CH0_DEADZONE;
	}
	else if(CHx == PWMPLUS_CH1) 
	{
		return PWMPLUSx->CH1_DEADZONE;
	}
	else if(CHx == PWMPLUS_CH2) 
	{
		return PWMPLUSx->CH2_DEADZONE;
	}
	
	return 0;
}


/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_SetTrig_Comp()
* ����˵��:	�����ڲ�������
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
*			uint32_t Trig_Comp			        Ҫ���õ��ڲ�������,16λ  ����С������ֵ
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_SetTrig_Comp(PWMPLUS_TypeDef * PWMPLUSx, uint16_t Trig_Comp)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_TRIG_COMP(Trig_Comp));                       //�������Ĳ���Trig_Comp�Ƿ�Ϸ�  
	
	if(Trig_Comp > PWMPLUS_GetPeriod(PWMPLUSx))
	{
		Trig_Comp = 0;
	}
	
	PWMPLUSx->TRIG_COMP = Trig_Comp;            //�����ڲ�������
}


/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_GetTrig_Comp()
* ����˵��:	��ȡ�ڲ�������
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
* ��    ��: �ڲ�������
* ע������: ��
******************************************************************************************************************************************/
uint32_t PWMPLUS_GetTrig_Comp(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	return PWMPLUSx->TRIG_COMP;
}

/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_SetTrig_Sel0()
* ����˵��:	���ô����ź�0����ѡ��
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
*			PWMPLUS_TrigSel_TypeDef Trig_Sel    Ҫ���õĴ����źŹ���ѡ��
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_SetTrig_Sel0(PWMPLUS_TypeDef * PWMPLUSx, PWMPLUS_TrigSel_TypeDef Trig_Sel)
{
	uint32_t temp = 0;
	
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_TRIG_SEL(Trig_Sel));                         //�������Ĳ���Trig_Sel�Ƿ�Ϸ�  
	
	temp = PWMPLUSx->TRIG_SEL;
	
	temp &= ~(0x0F << PWMPLUS_TRIG_CTR_SEL0_POS);
	temp |= (Trig_Sel << PWMPLUS_TRIG_CTR_SEL0_POS);                     //���ô����źŹ���ѡ��
	
	PWMPLUSx->TRIG_SEL = temp;
}

/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_SetTrig_Sel1()
* ����˵��:	���ô����ź�1����ѡ��
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
*			PWMPLUS_TrigSel_TypeDef Trig_Sel    Ҫ���õĴ����źŹ���ѡ��
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_SetTrig_Sel1(PWMPLUS_TypeDef * PWMPLUSx, PWMPLUS_TrigSel_TypeDef Trig_Sel)
{
	uint32_t temp = 0;
	
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_TRIG_SEL(Trig_Sel));                         //�������Ĳ���Trig_Sel�Ƿ�Ϸ�  
	
	temp = PWMPLUSx->TRIG_SEL;
	
	temp &= ~(0x0F << PWMPLUS_TRIG_CTR_SEL1_POS);
	temp |= (Trig_Sel << PWMPLUS_TRIG_CTR_SEL1_POS);                     //���ô����źŹ���ѡ��
	
	PWMPLUSx->TRIG_SEL = temp;
}

/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_SetTrig_Sel2()
* ����˵��:	���ô����ź�2����ѡ��
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
*			PWMPLUS_TrigSel_TypeDef Trig_Sel    Ҫ���õĴ����źŹ���ѡ��
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_SetTrig_Sel2(PWMPLUS_TypeDef * PWMPLUSx, PWMPLUS_TrigSel_TypeDef Trig_Sel)
{
	uint32_t temp = 0;
	
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_TRIG_SEL(Trig_Sel));                         //�������Ĳ���Trig_Sel�Ƿ�Ϸ�  
	
	temp = PWMPLUSx->TRIG_SEL;
	
	temp &= ~(0x0F << PWMPLUS_TRIG_CTR_SEL2_POS);
	temp |= (Trig_Sel << PWMPLUS_TRIG_CTR_SEL2_POS);                     //���ô����źŹ���ѡ��
	
	PWMPLUSx->TRIG_SEL = temp;
}

/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_SetTrig_Sel3()
* ����˵��:	���ô����ź�3����ѡ��
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
*			PWMPLUS_TrigSel_TypeDef Trig_Sel    Ҫ���õĴ����źŹ���ѡ��
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_SetTrig_Sel3(PWMPLUS_TypeDef * PWMPLUSx, PWMPLUS_TrigSel_TypeDef Trig_Sel)
{
	uint32_t temp = 0;
	
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_TRIG_SEL(Trig_Sel));                         //�������Ĳ���Trig_Sel�Ƿ�Ϸ�  
	
	temp = PWMPLUSx->TRIG_SEL;
	
	temp &= ~(0x0F << PWMPLUS_TRIG_CTR_SEL3_POS);
	temp |= (Trig_Sel << PWMPLUS_TRIG_CTR_SEL3_POS);                     //���ô����źŹ���ѡ��
	
	PWMPLUSx->TRIG_SEL = temp;
}

/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_IntReloadEn()
* ����˵��:	�����Զ�װ���ж�ʹ��
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_IntReloadEn(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	PWMPLUSx->IE |= (0x01 << PWMPLUS_IE_RELOAD_POS);                     //�Զ�װ���ж�ʹ��
}


/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_IntReloadDis()
* ����˵��:	�����Զ�װ���жϽ���
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_IntReloadDis(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	PWMPLUSx->IE &= ~(0x01 << PWMPLUS_IE_RELOAD_POS);                    //�Զ�װ���жϽ���
}

/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_IntReloadState()
* ����˵��:	��ȡ�Զ�װ���ж�״̬
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
* ��    ��: 1 �Զ�װ���ж��Ѿ�����    0  �Զ�װ���ж�δ����
* ע������: ��
******************************************************************************************************************************************/
uint8_t PWMPLUS_IntReloadState(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	if(PWMPLUSx->IF & PWMPLUS_IF_RELOAD_MSK)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_IntReloadClr()
* ����˵��:	����Զ�װ���ж�״̬
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_IntReloadClr(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	PWMPLUSx->IF = (0x01 << PWMPLUS_IF_RELOAD_POS);	
}


/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_IntBrake0En()
* ����˵��:	����ɲ��0�ж�ʹ��
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_IntBrake0En(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	PWMPLUSx->IE |= (0x01 << PWMPLUS_IE_BRK0_POS);                       //ɲ��0�ж�ʹ��
}


/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_IntBrake0Dis()
* ����˵��:	����ɲ��0�жϽ���
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_IntBrake0Dis(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	PWMPLUSx->IE &= ~(0x01 << PWMPLUS_IE_BRK0_POS);                      //�Զ�װ���жϽ���
}

/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_IntBrake0State()
* ����˵��:	��ȡɲ��0�ж�״̬
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
* ��    ��: 1 ɲ��0�ж��Ѿ�����    0  ɲ��0�ж�δ����
* ע������: ��
******************************************************************************************************************************************/
uint8_t PWMPLUS_IntBrake0State(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	if(PWMPLUSx->IF & PWMPLUS_IF_BRK0_MSK)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_IntBrake0Clr()
* ����˵��:	���ɲ��0�ж�״̬
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_IntBrake0Clr(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	PWMPLUSx->IF = (0x01 << PWMPLUS_IF_BRK0_POS);	
}


/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_IntBrake1En()
* ����˵��:	����ɲ��1�ж�ʹ��
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_IntBrake1En(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	PWMPLUSx->IE |= (0x01 << PWMPLUS_IE_BRK1_POS);                       //ɲ��0�ж�ʹ��
}


/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_IntBrake1Dis()
* ����˵��:	����ɲ��1�жϽ���
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_IntBrake1Dis(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	PWMPLUSx->IE &= ~(0x01 << PWMPLUS_IE_BRK1_POS);                      //ɲ��0�жϽ���
}

/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_IntBrake1State()
* ����˵��:	��ȡɲ��1�ж�״̬
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
* ��    ��: 1 ɲ��1�ж��Ѿ�����    0  ɲ��1�ж�δ����
* ע������: ��
******************************************************************************************************************************************/
uint8_t PWMPLUS_IntBrake1State(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  

	if(PWMPLUSx->IF & PWMPLUS_IF_BRK1_MSK)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_IntBrake1Clr()
* ����˵��:	���ɲ��1�ж�״̬
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_IntBrake1Clr(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	PWMPLUSx->IF = (0x01 << PWMPLUS_IF_BRK1_POS);	
}


/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_IntUp_OvfEn()
* ����˵��:	�������ϼ�����������ж�ʹ��
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_IntUp_OvfEn(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	PWMPLUSx->IE |= (0x01 << PWMPLUS_IE_UP_OVF_POS);                     //���ϼ�����������ж�ʹ��
}

/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_IntUp_OvfDis()
* ����˵��:	�������ϼ�����������жϽ���
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_IntUp_OvfDis(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	PWMPLUSx->IE &= ~(0x01 << PWMPLUS_IE_UP_OVF_POS);                    //���ϼ�����������жϽ���
}


/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_IntUp_OvfState()
* ����˵��:	��ȡ���ϼ�����������ж�״̬
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
* ��    ��: 1 ���ϼ�����������ж��Ѿ�����    0  ���ϼ�����������ж�δ����
* ע������: ��
******************************************************************************************************************************************/
uint8_t PWMPLUS_IntUp_OvfState(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	if(PWMPLUSx->IF & PWMPLUS_IF_UP_OVF_MSK)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_IntUp_OvfClr()
* ����˵��:	������ϼ�����������ж�״̬
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_IntUp_OvfClr(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	PWMPLUSx->IF = (0x01 << PWMPLUS_IF_UP_OVF_POS);	
}


/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_IntUp_TrigCompEn()
* ����˵��:	�������ϼ������ﴥ�����ж�ʹ��
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_IntUp_TrigCompEn(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	PWMPLUSx->IE |= (0x01 << PWMPLUS_IE_UP_TRIG_POS);                    //���ϼ������ﴥ�����ж�ʹ��
}

/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_IntUp_TrigCompDis()
* ����˵��:	�������ϼ������ﴥ�����жϽ���
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_IntUp_TrigCompDis(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	PWMPLUSx->IE &= ~(0x01 << PWMPLUS_IE_UP_TRIG_POS);                   //���ϼ������ﴥ�����жϽ���
}


/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_IntUp_TrigCompState()
* ����˵��:	��ȡ���ϼ������ﴥ�����ж�״̬
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
* ��    ��: 1 ���ϼ������ﴥ�����ж��Ѿ�����    0  ���ϼ������ﴥ�����ж�δ����
* ע������: ��
******************************************************************************************************************************************/
uint8_t PWMPLUS_IntUp_TrigCompState(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	if(PWMPLUSx->IF & PWMPLUS_IF_UP_TRIG_MSK)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_IntUp_TrigCompClr()
* ����˵��:	������ϼ������ﴥ�����ж�״̬
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_IntUp_TrigCompClr(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	PWMPLUSx->IF = (0x01 << PWMPLUS_IF_UP_TRIG_POS);	
}


/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_IntDown_OvfEn()
* ����˵��:	�������¼�����������ж�ʹ��
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_IntDown_OvfEn(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	PWMPLUSx->IE |= (0x01 << PWMPLUS_IE_DOWN_OVF_POS);                   //���¼�����������ж�ʹ��
}

/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_IntDown_OvfDis()
* ����˵��:	�������¼�����������жϽ���
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_IntDown_OvfDis(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	PWMPLUSx->IE &= ~(0x01 << PWMPLUS_IE_DOWN_OVF_POS);                  //���¼�����������жϽ���
}


/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_IntDown_OvfState()
* ����˵��:	��ȡ���¼�����������ж�״̬
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
* ��    ��: 1 ���¼�����������ж��Ѿ�����    0  ���¼�����������ж�δ����
* ע������: ��
******************************************************************************************************************************************/
uint8_t PWMPLUS_IntDown_OvfState(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	if(PWMPLUSx->IF & PWMPLUS_IF_DOWN_OVF_MSK)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_IntDown_OvfClr()
* ����˵��:	������¼�����������ж�״̬
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_IntDown_OvfClr(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	PWMPLUSx->IF = (0x01 << PWMPLUS_IF_DOWN_OVF_POS);	
}


/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_IntDown_TrigCompEn()
* ����˵��:	�������¼������ﴥ�����ж�ʹ��
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_IntDown_TrigCompEn(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	PWMPLUSx->IE |= (0x01 << PWMPLUS_IE_DOWN_TRIG_POS);                  //���¼������ﴥ�����ж�ʹ��
}

/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_IntDown_TrigCompDis()
* ����˵��:	�������¼������ﴥ�����жϽ���
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_IntDown_TrigCompDis(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	PWMPLUSx->IE &= ~(0x01 << PWMPLUS_IE_DOWN_TRIG_POS);                 //���¼������ﴥ�����жϽ���
}


/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_IntDown_TrigCompState()
* ����˵��:	��ȡ���¼������ﴥ�����ж�״̬
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
* ��    ��: 1 ���¼������ﴥ�����ж��Ѿ�����    0  ���¼������ﴥ�����ж�δ����
* ע������: ��
******************************************************************************************************************************************/
uint8_t PWMPLUS_IntDown_TrigCompState(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	if(PWMPLUSx->IF & PWMPLUS_IF_DOWN_TRIG_MSK)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_IntDown_TrigCompClr()
* ����˵��:	������¼������ﴥ�����ж�״̬
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_IntDown_TrigCompClr(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	PWMPLUSx->IF = (0x01 << PWMPLUS_IF_DOWN_TRIG_POS);	
}


/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_IntUp_CompEn()
* ����˵��:	�������ϼ������﷭ת���ж�ʹ��
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
*           uint8_t CHx                         PWMPLUS_CH0    PWMPLUS_CH1   PWMPLUS_CH2
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_IntUp_CompEn(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_CHANNEL_HALF(CHx));                          //�������Ĳ���CHx�Ƿ�Ϸ�  
	
	if((CHx & PWMPLUS_CH0) == PWMPLUS_CH0) 
	{
		PWMPLUSx->IE |= (0x01 << PWMPLUS_IE_CH0_UP_COMP_POS);
	}
	
	if((CHx & PWMPLUS_CH1) == PWMPLUS_CH1) 
	{
		PWMPLUSx->IE |= (0x01 << PWMPLUS_IE_CH1_UP_COMP_POS);
	}
	
	if((CHx & PWMPLUS_CH2) == PWMPLUS_CH2) 
	{
		PWMPLUSx->IE |= (0x01 << PWMPLUS_IE_CH2_UP_COMP_POS);
	}
}


/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_IntUp_CompDis()
* ����˵��:	�������ϼ������﷭ת���жϽ���
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
*           uint8_t CHx                         PWMPLUS_CH0    PWMPLUS_CH1   PWMPLUS_CH2
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_IntUp_CompDis(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_CHANNEL_HALF(CHx));                          //�������Ĳ���CHx�Ƿ�Ϸ�  
	
	if((CHx & PWMPLUS_CH0) == PWMPLUS_CH0) 
	{
		PWMPLUSx->IE &= ~(0x01 << PWMPLUS_IE_CH0_UP_COMP_POS);
	}
	
	if((CHx & PWMPLUS_CH1) == PWMPLUS_CH1) 
	{
		PWMPLUSx->IE &= ~(0x01 << PWMPLUS_IE_CH1_UP_COMP_POS);
	}
	
	if((CHx & PWMPLUS_CH2) == PWMPLUS_CH2) 
	{
		PWMPLUSx->IE &= ~(0x01 << PWMPLUS_IE_CH2_UP_COMP_POS);
	}
}


/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_IntUp_CompState()
* ����˵��:	��ȡ���ϼ������﷭ת���ж�״̬
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
*           uint8_t CHx                         PWMPLUS_CH0    PWMPLUS_CH1   PWMPLUS_CH2
* ��    ��: 1 ���ϼ������﷭ת���ж��Ѿ�����    0  ���ϼ������﷭ת���ж�δ����
* ע������: ��
******************************************************************************************************************************************/
uint8_t PWMPLUS_IntUp_CompState(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_CHANNEL_HALF(CHx));                          //�������Ĳ���CHx�Ƿ�Ϸ�  
	
	if(CHx == PWMPLUS_CH0) 
	{
		if(PWMPLUSx->IF & PWMPLUS_IF_CH0_UP_COMP_MSK)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	
	else if(CHx == PWMPLUS_CH1) 
	{
		if(PWMPLUSx->IF & PWMPLUS_IF_CH1_UP_COMP_MSK)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	
	else if(CHx == PWMPLUS_CH2) 
	{
		if(PWMPLUSx->IF & PWMPLUS_IF_CH2_UP_COMP_MSK)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	
	return 0;
}


/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_IntUp_CompClr()
* ����˵��:	������ϼ������﷭ת���ж�״̬
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
*           uint8_t CHx                         PWMPLUS_CH0    PWMPLUS_CH1   PWMPLUS_CH2
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_IntUp_CompClr(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_CHANNEL_HALF(CHx));                          //�������Ĳ���CHx�Ƿ�Ϸ�  
	
	if((CHx & PWMPLUS_CH0) == PWMPLUS_CH0) 
	{
		PWMPLUSx->IF = (0x01 << PWMPLUS_IF_CH0_UP_COMP_POS);
	}
	
	if((CHx & PWMPLUS_CH1) == PWMPLUS_CH1) 
	{
		PWMPLUSx->IF = (0x01 << PWMPLUS_IF_CH1_UP_COMP_POS);
	}
	
	if((CHx & PWMPLUS_CH2) == PWMPLUS_CH2) 
	{
		PWMPLUSx->IF = (0x01 << PWMPLUS_IF_CH2_UP_COMP_POS);
	}
}



/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_IntDown_CompEn()
* ����˵��:	�������¼������﷭ת���ж�ʹ��
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
*           uint8_t CHx                         PWMPLUS_CH0    PWMPLUS_CH1   PWMPLUS_CH2
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_IntDown_CompEn(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_CHANNEL_HALF(CHx));                          //�������Ĳ���CHx�Ƿ�Ϸ�  
	
	if((CHx & PWMPLUS_CH0) == PWMPLUS_CH0) 
	{
		PWMPLUSx->IE |= (0x01 << PWMPLUS_IE_CH0_DOWN_COMP_POS);
	}
	
	if((CHx & PWMPLUS_CH1) == PWMPLUS_CH1) 
	{
		PWMPLUSx->IE |= (0x01 << PWMPLUS_IE_CH1_DOWN_COMP_POS);
	}
	
	if((CHx & PWMPLUS_CH2) == PWMPLUS_CH2) 
	{
		PWMPLUSx->IE |= (0x01 << PWMPLUS_IE_CH2_DOWN_COMP_POS);
	}
}


/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_IntDown_CompDis()
* ����˵��:	�������¼������﷭ת���жϽ���
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
*           uint8_t CHx                         PWMPLUS_CH0    PWMPLUS_CH1   PWMPLUS_CH2
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_IntDown_CompDis(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_CHANNEL_HALF(CHx));                          //�������Ĳ���CHx�Ƿ�Ϸ�  
	
	if((CHx & PWMPLUS_CH0) == PWMPLUS_CH0) 
	{
		PWMPLUSx->IE &= ~(0x01 << PWMPLUS_IE_CH0_DOWN_COMP_POS);
	}
	
	if((CHx & PWMPLUS_CH1) == PWMPLUS_CH1) 
	{
		PWMPLUSx->IE &= ~(0x01 << PWMPLUS_IE_CH1_DOWN_COMP_POS);
	}
	
	if((CHx & PWMPLUS_CH2) == PWMPLUS_CH2) 
	{
		PWMPLUSx->IE &= ~(0x01 << PWMPLUS_IE_CH2_DOWN_COMP_POS);
	}
}


/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_IntDown_CompState()
* ����˵��:	��ȡ���¼������﷭ת���ж�״̬
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
*           uint8_t CHx                         PWMPLUS_CH0    PWMPLUS_CH1   PWMPLUS_CH2
* ��    ��: 1 ���¼������﷭ת���ж��Ѿ�����    0  ���¼������﷭ת���ж�δ����
* ע������: ��
******************************************************************************************************************************************/
uint8_t PWMPLUS_IntDown_CompState(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_CHANNEL_HALF(CHx));                          //�������Ĳ���CHx�Ƿ�Ϸ�  
	
	if(CHx == PWMPLUS_CH0) 
	{
		if(PWMPLUSx->IF & PWMPLUS_IF_CH0_DOWN_COMP_MSK)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if(CHx == PWMPLUS_CH1) 
	{
		if(PWMPLUSx->IF & PWMPLUS_IF_CH1_DOWN_COMP_MSK)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else if(CHx == PWMPLUS_CH2) 
	{
		if(PWMPLUSx->IF & PWMPLUS_IF_CH2_DOWN_COMP_MSK)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	
	return 0;
}


/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_IntDown_CompClr()
* ����˵��:	������¼������﷭ת���ж�״̬
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
*           uint8_t CHx                         PWMPLUS_CH0    PWMPLUS_CH1   PWMPLUS_CH2
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_IntDown_CompClr(PWMPLUS_TypeDef * PWMPLUSx, uint8_t CHx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	assert_param(IS_PWMPLUS_CHANNEL_HALF(CHx));                          //�������Ĳ���CHx�Ƿ�Ϸ�  
	
	if((CHx & PWMPLUS_CH0) == PWMPLUS_CH0) 
	{
		PWMPLUSx->IF = (0x01 << PWMPLUS_IF_CH0_DOWN_COMP_POS);
	}
	
	if((CHx & PWMPLUS_CH1) == PWMPLUS_CH1) 
	{
		PWMPLUSx->IF = (0x01 << PWMPLUS_IF_CH1_DOWN_COMP_POS);
	}
	
	if((CHx & PWMPLUS_CH2) == PWMPLUS_CH2) 
	{
		PWMPLUSx->IF = (0x01 << PWMPLUS_IF_CH2_DOWN_COMP_POS);
	}
}

/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_SoftLoad()
* ����˵��:	PWMPLUS���LOAD
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
*           
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMPLUS_SoftLoad(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	PWMPLUSx->SWLOAD = (0x01 << PWMPLUS_SWLOAD_POS);
}

/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_GetCntState()
* ����˵��:	��ȡPWMPLUS����������״̬
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
*           
* ��    ��: 1 ���������ڼ���   0 ������δ����
* ע������: ��
******************************************************************************************************************************************/
uint8_t PWMPLUS_GetCntState(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	if(PWMPLUSx->CNT_STATE & PWMPLUS_CNT_STATE_STATE_MSK)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_GetCntDir()
* ����˵��:	��ȡPWMPLUS��������ǰ��������
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
*           
* ��    ��: 1 ��������ǰ���¼���   0 ��������ǰ���ϼ���
* ע������: ��
******************************************************************************************************************************************/
uint8_t PWMPLUS_GetCntDir(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	if(PWMPLUSx->CNT_STATE & PWMPLUS_CNT_STATE_DIR_MSK)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_GetCurrentCnt()
* ����˵��:	��ȡPWMPLUS��������ǰ����ֵ
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
*           
* ��    ��: ��������ǰ����ֵ
* ע������: ��
******************************************************************************************************************************************/
uint16_t PWMPLUS_GetCurrentCnt(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	return (PWMPLUSx->CNT_STATE & 0xFFFF);
}


/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_GetBrake0State()
* ����˵��:	��ȡPWMPLUSɲ��0�ĵ�ǰ״̬
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
*           
* ��    ��: ɲ��0�ĵ�ǰ״̬
* ע������: ��
******************************************************************************************************************************************/
uint8_t PWMPLUS_GetBrake0State(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	if(PWMPLUSx->BRK_STATE & PWMPLUS_BRK0_STATE_MSK)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


/****************************************************************************************************************************************** 
* ��������:	PWMPLUS_GetBrake1State()
* ����˵��:	��ȡPWMPLUSɲ��1�ĵ�ǰ״̬
* ��    ��: PWMPLUS_TypeDef * PWMPLUSx			ָ��Ҫ�����õ�PWMPLUS����Чֵ����PWMPLUS0
*           
* ��    ��: ɲ��1�ĵ�ǰ״̬
* ע������: ��
******************************************************************************************************************************************/
uint8_t PWMPLUS_GetBrake1State(PWMPLUS_TypeDef * PWMPLUSx)
{
	assert_param(IS_PWMPLUS_ALL(PWMPLUSx));                              //�������Ĳ���PWMPLUSx�Ƿ�Ϸ�  
	
	if(PWMPLUSx->BRK_STATE & PWMPLUS_BRK1_STATE_MSK)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}



