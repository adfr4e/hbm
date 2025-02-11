#include "HBM32G003_pwmbase.h"

/****************************************************************************************************************************************** 
* ��������:	PWMBASE_Common_Init()
* ����˵��:	PWMBASE����������ʼ��
* ��    ��: PWMBASE_TypeDef * PWMBASEx                              ָ��Ҫ�����õ�PWMBASE����Чֵ����PWMBASE0
*			PWMBASE_CommonInitTypeDef * PWMBASE_CommonInitStruct	����PWMBASE����趨ֵ�Ľṹ��
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMBASE_Common_Init(PWMBASE_TypeDef * PWMBASEx, PWMBASE_CommonInitTypeDef * PWMBASE_CommonInitStruct)
{
	assert_param(IS_PWMBASE_ALL(PWMBASEx));                                //�������Ĳ���PWMBASEx�Ƿ�Ϸ�    
	
	assert_param(IS_PWMBASE_CLKDIV(PWMBASE_CommonInitStruct->ClkDiv));     //�������Ĳ���ClkDiv�Ƿ�Ϸ�     
	
	assert_param(IS_PWMBASE_PERIOD(PWMBASE_CommonInitStruct->Period));     //�������Ĳ���Period�Ƿ�Ϸ�     
	
	assert_param(IS_PWMBASE_IE_OVF(PWMBASE_CommonInitStruct->OvfIE));      //�������Ĳ���OvfIE�Ƿ�Ϸ�     
	
	switch((uint32_t)PWMBASEx)
	{
		case((uint32_t)PWMBASE0):
		
			SYS->CLKEN |= 0x01 << SYS_CLKEN_PWMBASE0_POS;           //����PWMBASE0ʱ��
		
		break;
	}
	
	PWMBASE_Stop(PWMBASEx);                                         //�ر�PWMBASE��ֹͣPWM���  

	PWMBASEx->DIV = PWMBASE_CommonInitStruct->ClkDiv;               //PWMBASE��Ƶϵ��   ʵ�ʷ�ƵΪ����ֵ��1
	
	if(PWMBASE_CommonInitStruct->Period == 0 || PWMBASE_CommonInitStruct->Period > 0xFFFF)
	{
		PWMBASE_CommonInitStruct->Period = 0xFFFF;
	}
	
	PWMBASEx->PERIOD = PWMBASE_CommonInitStruct->Period;                  //PWMBASE����   ʵ������������ֵ��1
	
	if(PWMBASE_CommonInitStruct->OvfIE == ENABLE)                         //PWMBASE��������ж�ʹ��
	{
		PWMBASEx->IE |= 0x01 << PWMBASE_IE_OVF_POS;
	}
	else
	{
		PWMBASEx->IE &= ~(0x01 << PWMBASE_IE_OVF_POS);
	}
	
	switch((uint32_t)PWMBASEx)
	{
		case((uint32_t)PWMBASE0):
		
			if(PWMBASE_CommonInitStruct->OvfIE)
			{
				NVIC_EnableIRQ(PWMBASE0_IRQn);
			}
		
		break;
	}
	
	PWMBASEx->IF = 0x0F;       //���жϱ�־
}

/****************************************************************************************************************************************** 
* ��������:	PWMBASE_Channel_Init()
* ����˵��:	PWMBASEͨ����ʼ��
* ��    ��: PWMBASE_TypeDef * PWMBASEx                  ָ��Ҫ�����õ�PWMBASE����Чֵ����PWMBASE0
*			PWMBASE_ChannelInitTypeDef * PWMBASE_ChannelInitStruct	����PWMBASE����趨ֵ�Ľṹ��
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMBASE_Channel_Init(PWMBASE_TypeDef * PWMBASEx, PWMBASE_ChannelInitTypeDef * PWMBASE_ChannelInitStruct)
{
	assert_param(IS_PWMBASE_ALL(PWMBASEx));                                  //�������Ĳ���PWMBASEx�Ƿ�Ϸ�    
	
	assert_param(IS_PWMBASE_COMP(PWMBASE_ChannelInitStruct->Comp));          //�������Ĳ���Comp�Ƿ�Ϸ�    
	
	assert_param(IS_PWMBASE_INV(PWMBASE_ChannelInitStruct->Inv));            //�������Ĳ���Inv�Ƿ�Ϸ�  
	
	assert_param(IS_PWMBASE_OUTEN(PWMBASE_ChannelInitStruct->OutEn));        //�������Ĳ���OutEn�Ƿ�Ϸ�  
	
	assert_param(IS_PWMBASE_IE_COMP(PWMBASE_ChannelInitStruct->CompIE));     //�������Ĳ���CompIE�Ƿ�Ϸ�  
	
	
	PWMBASE_Stop(PWMBASEx);                                                  //�ر�PWMBASE��ֹͣPWM���  

	if(PWMBASE_ChannelInitStruct->Comp > PWMBASE_GetPeriod(PWMBASEx))
	{
		PWMBASE_ChannelInitStruct->Comp = 0;
	}
	
	if((PWMBASE_ChannelInitStruct->Channel & PWMBASE_CH0) == PWMBASE_CH0)
	{
		PWMBASEx->CH0_COMP = PWMBASE_ChannelInitStruct->Comp;            //PWMBASE����ͨ��0��ת��
		
		if(PWMBASE_ChannelInitStruct->Inv == ENABLE)                     //PWMBASEͨ��0�ź������ת
		{
			PWMBASEx->OUTCTR |= 0x01 << PWMBASE_OUTCTR_CH0_INV_POS;
		}
		else
		{
			PWMBASEx->OUTCTR &= ~(0x01 << PWMBASE_OUTCTR_CH0_INV_POS);
		}

		if(PWMBASE_ChannelInitStruct->OutEn == ENABLE)                   //PWMBASEͨ��0�ź����ʹ��
		{
			PWMBASEx->OUTCTR |= 0x01 << PWMBASE_OUTCTR_CH0_EN_POS;
		}
		else
		{
			PWMBASEx->OUTCTR &= ~(0x01 << PWMBASE_OUTCTR_CH0_EN_POS);
		}
		
		if(PWMBASE_ChannelInitStruct->CompIE == ENABLE)                  //PWMBASEͨ��0���﷭ת���ж�ʹ��
		{
			PWMBASEx->IE |= 0x01 << PWMBASE_IE_CH0_COMP_POS;
		}
		else
		{
			PWMBASEx->IE &= ~(0x01 << PWMBASE_IE_CH0_COMP_POS);
		}
	}
	
	if((PWMBASE_ChannelInitStruct->Channel & PWMBASE_CH1) == PWMBASE_CH1)
	{
		PWMBASEx->CH1_COMP = PWMBASE_ChannelInitStruct->Comp;            //PWMBASE����ͨ��1��ת��
	
		if(PWMBASE_ChannelInitStruct->Inv == ENABLE)                     //PWMBASEͨ��1�ź������ת
		{
			PWMBASEx->OUTCTR |= 0x01 << PWMBASE_OUTCTR_CH1_INV_POS;
		}
		else
		{
			PWMBASEx->OUTCTR &= ~(0x01 << PWMBASE_OUTCTR_CH1_INV_POS);
		}
		
		if(PWMBASE_ChannelInitStruct->OutEn == ENABLE)                   //PWMBASEͨ��1�ź����ʹ��
		{
			PWMBASEx->OUTCTR |= 0x01 << PWMBASE_OUTCTR_CH1_EN_POS;
		}
		else
		{
			PWMBASEx->OUTCTR &= ~(0x01 << PWMBASE_OUTCTR_CH1_EN_POS);
		}
		
		PWMBASEx->CH1_COMP = PWMBASE_ChannelInitStruct->Comp;            //PWMBASE����ͨ��1��ת��
		
		if(PWMBASE_ChannelInitStruct->CompIE == ENABLE)                  //PWMBASEͨ��1���﷭ת���ж�ʹ��
		{
			PWMBASEx->IE |= 0x01 << PWMBASE_IE_CH1_COMP_POS;
		}
		else
		{
			PWMBASEx->IE &= ~(0x01 << PWMBASE_IE_CH1_COMP_POS);
		}	
	}
	
	if((PWMBASE_ChannelInitStruct->Channel & PWMBASE_CH2) == PWMBASE_CH2)
	{
		PWMBASEx->CH2_COMP = PWMBASE_ChannelInitStruct->Comp;            //PWMBASE����ͨ��2��ת��
	
		if(PWMBASE_ChannelInitStruct->Inv == ENABLE)                     //PWMBASEͨ��2�ź������ת
		{
			PWMBASEx->OUTCTR |= 0x01 << PWMBASE_OUTCTR_CH2_INV_POS;
		}
		else
		{
			PWMBASEx->OUTCTR &= ~(0x01 << PWMBASE_OUTCTR_CH2_INV_POS);
		}
		
		if(PWMBASE_ChannelInitStruct->OutEn == ENABLE)                   //PWMBASEͨ��2�ź����ʹ��
		{
			PWMBASEx->OUTCTR |= 0x01 << PWMBASE_OUTCTR_CH2_EN_POS;
		}
		else
		{
			PWMBASEx->OUTCTR &= ~(0x01 << PWMBASE_OUTCTR_CH2_EN_POS);
		}
		
		if(PWMBASE_ChannelInitStruct->CompIE == ENABLE)                  //PWMBASEͨ��2���﷭ת���ж�ʹ��
		{
			PWMBASEx->IE |= 0x01 << PWMBASE_IE_CH2_COMP_POS;
		}
		else
		{
			PWMBASEx->IE &= ~(0x01 << PWMBASE_IE_CH2_COMP_POS);
		}
	}
	
	switch((uint32_t)PWMBASEx)
	{
		case((uint32_t)PWMBASE0):
		
			if(PWMBASE_ChannelInitStruct->CompIE)
			{
				NVIC_EnableIRQ(PWMBASE0_IRQn);
			}
		
		break;
	}
	
	PWMBASEx->IF = 0x0F;       //���жϱ�־
}

/****************************************************************************************************************************************** 
* ��������:	PWMBASE_Start()
* ����˵��:	����PWMBASE����ʼPWM���
* ��    ��: PWMBASE_TypeDef * PWMBASEx			ָ��Ҫ�����õ�PWMBASE����Чֵ����PWMBASE0
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMBASE_Start(PWMBASE_TypeDef * PWMBASEx)
{
	assert_param(IS_PWMBASE_ALL(PWMBASEx));                                //�������Ĳ���PWMBASEx�Ƿ�Ϸ�    
	
	PWMBASEx->EN |= 0x01 << PWMBASE_EN_POS; 
}


/****************************************************************************************************************************************** 
* ��������:	PWMBASE_Stop()
* ����˵��:	�ر�PWMBASE��ֹͣPWM���
* ��    ��: PWMBASE_TypeDef * PWMBASEx			ָ��Ҫ�����õ�PWMBASE����Чֵ����PWMBASE0
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMBASE_Stop(PWMBASE_TypeDef * PWMBASEx)
{
	assert_param(IS_PWMBASE_ALL(PWMBASEx));                                //�������Ĳ���PWMBASEx�Ƿ�Ϸ�    
	
	PWMBASEx->EN &= ~(0x01 << PWMBASE_EN_POS);  
}


/****************************************************************************************************************************************** 
* ��������:	PWMBASE_SetClkDiv()
* ����˵��:	����Ԥ��Ƶϵ��   ʵ�ʷ�ƵΪ����ֵ��1
* ��    ��: uint8_t Clk_Div   
*			
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMBASE_SetClkDiv(PWMBASE_TypeDef * PWMBASEx,uint8_t Clk_Div)
{
	assert_param(IS_PWMBASE_ALL(PWMBASEx));       //�������Ĳ���PWMBASEx�Ƿ�Ϸ�    
	
	assert_param(IS_PWMBASE_CLKDIV(Clk_Div));     //�������Ĳ���ClkDiv�Ƿ�Ϸ�   
	
	PWMBASEx->DIV = Clk_Div;                      //PWMBASE��Ƶϵ��  ʵ�ʷ�ƵΪ����ֵ��1
}


/****************************************************************************************************************************************** 
* ��������:	PWMBASE_SetOutInv()
* ����˵��:	PWMBASE����źŷ�ת����
* ��    ��: PWMBASE_TypeDef * PWMBASEx     ָ��Ҫ�����õ�PWMBASE����Чֵ����PWMBASE0
*           uint8_t CHx                    ͨ��ѡ��  ���Զ�ͨ�����в��� ����  PWMBASE_CH0 | PWMBASE_CH1 | PWMBASE_CH2
*           FunctionalState  OutEn         ��Чֵ����ENABLE  DISABLE
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMBASE_SetOutInv(PWMBASE_TypeDef * PWMBASEx,uint8_t CHx,FunctionalState  OutInv)
{
	assert_param(IS_PWMBASE_ALL(PWMBASEx));       //�������Ĳ���PWMBASEx�Ƿ�Ϸ�    
	
	assert_param(IS_PWMBASE_CHANNEL(CHx));        //�������Ĳ���CHx�Ƿ�Ϸ�    
	
	assert_param(IS_PWMBASE_INV(OutInv));         //�������Ĳ���OutInv�Ƿ�Ϸ� 
	
	if((CHx & PWMBASE_CH0) == PWMBASE_CH0) 
	{
		if(OutInv == ENABLE)
		{
			PWMBASEx->OUTCTR |= 0x01 << PWMBASE_OUTCTR_CH0_INV_POS;
		}
		else
		{
			PWMBASEx->OUTCTR &= ~(0x01 << PWMBASE_OUTCTR_CH0_INV_POS);
		}	
	}
	
	if((CHx & PWMBASE_CH1) == PWMBASE_CH1) 
	{
		if(OutInv == ENABLE)
		{
			PWMBASEx->OUTCTR |= 0x01 << PWMBASE_OUTCTR_CH1_INV_POS;
		}
		else
		{
			PWMBASEx->OUTCTR &= ~(0x01 << PWMBASE_OUTCTR_CH1_INV_POS);
		}
	}
	
	if((CHx & PWMBASE_CH2) == PWMBASE_CH2) 
	{
		if(OutInv == ENABLE)
		{
			PWMBASEx->OUTCTR |= 0x01 << PWMBASE_OUTCTR_CH2_INV_POS;
		}
		else
		{
			PWMBASEx->OUTCTR &= ~(0x01 << PWMBASE_OUTCTR_CH2_INV_POS);
		}
	}
}


/****************************************************************************************************************************************** 
* ��������:	PWMBASE_SetOutEn()
* ����˵��:	PWMBASE���ʹ������
* ��    ��: PWMBASE_TypeDef * PWMBASEx     ָ��Ҫ�����õ�PWMBASE����Чֵ����PWMBASE0
*           uint8_t CHx                    ͨ��ѡ��  ���Զ�ͨ�����в��� ����  PWMBASE_CH0 | PWMBASE_CH1 | PWMBASE_CH2
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMBASE_SetOutEn(PWMBASE_TypeDef * PWMBASEx,uint8_t CHx,FunctionalState  OutEn)
{
	assert_param(IS_PWMBASE_ALL(PWMBASEx));       //�������Ĳ���PWMBASEx�Ƿ�Ϸ�    
	
	assert_param(IS_PWMBASE_CHANNEL(CHx));        //�������Ĳ���CHx�Ƿ�Ϸ�    
	
	assert_param(IS_PWMBASE_OUTEN(OutEn));        //�������Ĳ���OutEn�Ƿ�Ϸ� 
	
	
	if((CHx & PWMBASE_CH0) == PWMBASE_CH0) 
	{
		if(OutEn == ENABLE)
		{
			PWMBASEx->OUTCTR |= 0x01 << PWMBASE_OUTCTR_CH0_EN_POS;
		}
		else
		{
			PWMBASEx->OUTCTR &= ~(0x01 << PWMBASE_OUTCTR_CH0_EN_POS);
		}	
	}
	
	if((CHx & PWMBASE_CH1) == PWMBASE_CH1) 
	{
		if(OutEn == ENABLE)
		{
			PWMBASEx->OUTCTR |= 0x01 << PWMBASE_OUTCTR_CH1_EN_POS;
		}
		else
		{
			PWMBASEx->OUTCTR &= ~(0x01 << PWMBASE_OUTCTR_CH1_EN_POS);
		}
	}
	
	if((CHx & PWMBASE_CH2) == PWMBASE_CH2) 
	{
		if(OutEn == ENABLE)
		{
			PWMBASEx->OUTCTR |= 0x01 << PWMBASE_OUTCTR_CH2_EN_POS;
		}
		else
		{
			PWMBASEx->OUTCTR &= ~(0x01 << PWMBASE_OUTCTR_CH2_EN_POS);
		}
	}
}

/****************************************************************************************************************************************** 
* ��������:	PWMBASE_SetPeriod()
* ����˵��:	��������
* ��    ��: PWMBASE_TypeDef * PWMBASEx			ָ��Ҫ�����õ�PWMBASE����Чֵ����PWMBASE0
*			uint16_t Period			            Ҫ�趨������ֵ,16λ
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMBASE_SetPeriod(PWMBASE_TypeDef * PWMBASEx, uint16_t Period)
{
	assert_param(IS_PWMBASE_ALL(PWMBASEx));       //�������Ĳ���PWMBASEx�Ƿ�Ϸ�    
	
	assert_param(IS_PWMBASE_PERIOD(Period));      //�������Ĳ���Period�Ƿ�Ϸ�    
	
	if(Period == 0)
	{
		Period = 0xFFFF;
	}
	
	PWMBASEx->PERIOD = Period;                    //ʵ������������ֵ��1
}

/****************************************************************************************************************************************** 
* ��������:	PWMBASE_GetPeriod()
* ����˵��:	��ȡ����
* ��    ��: PWMBASE_TypeDef * PWMBASEx			ָ��Ҫ�����õ�PWMBASE����Чֵ����PWMBASE0
* ��    ��: ����ֵ
* ע������: ��
******************************************************************************************************************************************/
uint32_t PWMBASE_GetPeriod(PWMBASE_TypeDef * PWMBASEx)
{
	assert_param(IS_PWMBASE_ALL(PWMBASEx));       //�������Ĳ���PWMBASEx�Ƿ�Ϸ�    
	
	return PWMBASEx->PERIOD;
}

/****************************************************************************************************************************************** 
* ��������:	PWMBASE_SetComp()
* ����˵��:	���÷�ת��
* ��    ��: PWMBASE_TypeDef * PWMBASEx			ָ��Ҫ�����õ�PWMBASE����Чֵ����PWMBASE0
*           uint8_t CHx                         PWMBASE_CH0    PWMBASE_CH1   PWMBASE_CH2
*			uint32_t Comp			            Ҫ�趨�ķ�ת��,16λ
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMBASE_SetComp(PWMBASE_TypeDef * PWMBASEx, uint8_t CHx,uint32_t Comp)
{
	assert_param(IS_PWMBASE_ALL(PWMBASEx));       //�������Ĳ���PWMBASEx�Ƿ�Ϸ�  
	
	assert_param(IS_PWMBASE_CHANNEL(CHx));        //�������Ĳ���CHx�Ƿ�Ϸ�    
	
	assert_param(IS_PWMBASE_COMP(Comp));          //�������Ĳ���Comp�Ƿ�Ϸ�    
	
	
	if(Comp > PWMBASE_GetPeriod(PWMBASEx))
	{
		Comp = 0;
	}
	
	if((CHx & PWMBASE_CH0) == PWMBASE_CH0) 
	{
		PWMBASEx->CH0_COMP  = Comp;
	}
	
	if((CHx & PWMBASE_CH1) == PWMBASE_CH1) 
	{
		PWMBASEx->CH1_COMP  = Comp;
	}
	
	if((CHx & PWMBASE_CH2) == PWMBASE_CH2) 
	{
		PWMBASEx->CH2_COMP  = Comp;
	}
}

/****************************************************************************************************************************************** 
* ��������:	PWMBASE_GetComp()
* ����˵��:	��ȡ���õķ�ת��
* ��    ��: PWMBASE_TypeDef * PWMBASEx			ָ��Ҫ�����õ�PWMBASE����Чֵ����PWMBASE0
*           uint8_t CHx                         PWMBASE_CH0    PWMBASE_CH1   PWMBASE_CH2
* ��    ��: �������õķ�ת��
* ע������: ��
******************************************************************************************************************************************/
uint32_t PWMBASE_GetComp(PWMBASE_TypeDef * PWMBASEx, uint8_t CHx)
{
	assert_param(IS_PWMBASE_ALL(PWMBASEx));       //�������Ĳ���PWMBASEx�Ƿ�Ϸ�  
	
	assert_param(IS_PWMBASE_CHANNEL(CHx));        //�������Ĳ���CHx�Ƿ�Ϸ�    
	
	
	if(CHx == PWMBASE_CH0) 
	{
		return PWMBASEx->CH0_COMP;
	}
	else if(CHx == PWMBASE_CH1) 
	{
		return PWMBASEx->CH1_COMP;
	}
	else if(CHx == PWMBASE_CH2) 
	{
		return PWMBASEx->CH2_COMP;
	}
	
	return 0;
}

/****************************************************************************************************************************************** 
* ��������:	PWMBASE_IntCompEn()
* ����˵��:	PWMBASE��ת���ж�ʹ��
* ��    ��: PWMBASE_TypeDef * PWMBASEx     ָ��Ҫ�����õ�PWMBASE����Чֵ����PWMBASE0
*           uint8_t CHx                    ͨ��ѡ��  ���Զ�ͨ�����в��� ����  PWMBASE_CH0 | PWMBASE_CH1 | PWMBASE_CH2
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMBASE_IntCompEn(PWMBASE_TypeDef * PWMBASEx, uint8_t CHx)
{
	assert_param(IS_PWMBASE_ALL(PWMBASEx));       //�������Ĳ���PWMBASEx�Ƿ�Ϸ�  
	
	assert_param(IS_PWMBASE_CHANNEL(CHx));        //�������Ĳ���CHx�Ƿ�Ϸ�    
	
	
	if((CHx & PWMBASE_CH0) == PWMBASE_CH0) 
	{
		PWMBASEx->IE |= (0x01 << PWMBASE_IE_CH0_COMP_POS);
	}
	
	if((CHx & PWMBASE_CH1) == PWMBASE_CH1) 
	{
		PWMBASEx->IE |= (0x01 << PWMBASE_IE_CH1_COMP_POS);
	}
	
	if((CHx & PWMBASE_CH2) == PWMBASE_CH2) 
	{
		PWMBASEx->IE |= (0x01 << PWMBASE_IE_CH2_COMP_POS);
	}
}


/****************************************************************************************************************************************** 
* ��������:	PWMBASE_IntCompDis()
* ����˵��:	PWMBASE��ת���жϽ���
* ��    ��: PWMBASE_TypeDef * PWMBASEx     ָ��Ҫ�����õ�PWMBASE����Чֵ����PWMBASE0
*           uint8_t CHx                    ͨ��ѡ��  ���Զ�ͨ�����в��� ����  PWMBASE_CH0 | PWMBASE_CH1 | PWMBASE_CH2
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMBASE_IntCompDis(PWMBASE_TypeDef * PWMBASEx, uint8_t CHx)
{
	assert_param(IS_PWMBASE_ALL(PWMBASEx));       //�������Ĳ���PWMBASEx�Ƿ�Ϸ�  
	
	assert_param(IS_PWMBASE_CHANNEL(CHx));        //�������Ĳ���CHx�Ƿ�Ϸ�    
	
	if((CHx & PWMBASE_CH0) == PWMBASE_CH0) 
	{
		PWMBASEx->IE &= ~(0x01 << PWMBASE_IE_CH0_COMP_POS);
	}
	
	if((CHx & PWMBASE_CH1) == PWMBASE_CH1) 
	{
		PWMBASEx->IE &= ~(0x01 << PWMBASE_IE_CH1_COMP_POS);
	}
	
	if((CHx & PWMBASE_CH2) == PWMBASE_CH2) 
	{
		PWMBASEx->IE &= ~(0x01 << PWMBASE_IE_CH2_COMP_POS);
	}
}


/****************************************************************************************************************************************** 
* ��������:	PWMBASE_IntCompClr()
* ����˵��:	PWMBASE��ת���жϱ�־���
* ��    ��: PWMBASE_TypeDef * PWMBASEx     ָ��Ҫ�����õ�PWMBASE����Чֵ����PWMBASE0
*           uint8_t CHx                    ͨ��ѡ��  ���Զ�ͨ�����в��� ����  PWMBASE_CH0 | PWMBASE_CH1 | PWMBASE_CH2
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMBASE_IntCompClr(PWMBASE_TypeDef * PWMBASEx, uint8_t CHx)
{
	assert_param(IS_PWMBASE_ALL(PWMBASEx));       //�������Ĳ���PWMBASEx�Ƿ�Ϸ�  
	
	assert_param(IS_PWMBASE_CHANNEL(CHx));        //�������Ĳ���CHx�Ƿ�Ϸ�    
	
	if((CHx & PWMBASE_CH0) == PWMBASE_CH0) 
	{
		PWMBASEx->IF = (0x01 << PWMBASE_IF_CH0_COMP_POS);
	}
	
	if((CHx & PWMBASE_CH1) == PWMBASE_CH1) 
	{
		PWMBASEx->IF = (0x01 << PWMBASE_IF_CH1_COMP_POS);
	}
	
	if((CHx & PWMBASE_CH2) == PWMBASE_CH2) 
	{
		PWMBASEx->IF = (0x01 << PWMBASE_IF_CH2_COMP_POS);
	}
}

/****************************************************************************************************************************************** 
* ��������:	PWMBASE_IntCompState()
* ����˵��:	PWMBASE��ת���ж�״̬
* ��    ��: PWMBASE_TypeDef * PWMBASEx     ָ��Ҫ�����õ�PWMBASE����Чֵ����PWMBASE0
*           uint8_t CHx                    ͨ��ѡ�� ֻ��ѡ��һ��ͨ��  PWMBASE_CH0   PWMBASE_CH1   PWMBASE_CH2
* ��    ��: 1 ��ת���ж��Ѿ�����    0  ��ת���ж�δ����
* ע������: ��
******************************************************************************************************************************************/
uint8_t PWMBASE_IntCompState(PWMBASE_TypeDef * PWMBASEx, uint8_t CHx)
{
	uint8_t State = 0;
	
	assert_param(IS_PWMBASE_ALL(PWMBASEx));       //�������Ĳ���PWMBASEx�Ƿ�Ϸ�  
	
	assert_param(IS_PWMBASE_CHANNEL(CHx));        //�������Ĳ���CHx�Ƿ�Ϸ�    
	
	
	if(CHx  == PWMBASE_CH0) 
	{
		if(PWMBASEx->IF & PWMBASE_IF_CH0_COMP_MSK)
		{
			State = 1;
		}
	}
	else if(CHx == PWMBASE_CH1) 
	{
		if(PWMBASEx->IF & PWMBASE_IF_CH1_COMP_MSK)
		{
			State = 1;
		}
	}
	else if(CHx == PWMBASE_CH2) 
	{
		if(PWMBASEx->IF & PWMBASE_IF_CH2_COMP_MSK)
		{
			State = 1;
		}
	}

	return State;
}



/****************************************************************************************************************************************** 
* ��������:	PWMBASE_IntOvfEn()
* ����˵��:	PWMBASE��������ж�ʹ��
* ��    ��: PWMBASE_TypeDef * PWMBASEx     ָ��Ҫ�����õ�PWMBASE����Чֵ����PWMBASE0
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMBASE_IntOvfEn(PWMBASE_TypeDef * PWMBASEx)
{
	assert_param(IS_PWMBASE_ALL(PWMBASEx));       //�������Ĳ���PWMBASEx�Ƿ�Ϸ�  
	
	PWMBASEx->IE |= (0x01 << PWMBASE_IE_OVF_POS);
}


/****************************************************************************************************************************************** 
* ��������:	PWMBASE_IntOvfDis()
* ����˵��:	PWMBASE��������жϽ���
* ��    ��: PWMBASE_TypeDef * PWMBASEx     ָ��Ҫ�����õ�PWMBASE����Чֵ����PWMBASE0
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMBASE_IntOvfDis(PWMBASE_TypeDef * PWMBASEx)
{
	assert_param(IS_PWMBASE_ALL(PWMBASEx));       //�������Ĳ���PWMBASEx�Ƿ�Ϸ�  
	
	PWMBASEx->IE &= ~(0x01 << PWMBASE_IE_OVF_POS);
}


/****************************************************************************************************************************************** 
* ��������:	PWMBASE_IntOvfClr()
* ����˵��:	PWMBASE��������жϱ�־���
* ��    ��: PWMBASE_TypeDef * PWMBASEx     ָ��Ҫ�����õ�PWMBASE����Чֵ����PWMBASE0
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PWMBASE_IntOvfClr(PWMBASE_TypeDef * PWMBASEx)
{
	assert_param(IS_PWMBASE_ALL(PWMBASEx));       //�������Ĳ���PWMBASEx�Ƿ�Ϸ�  
	
	PWMBASEx->IF = (0x01 << PWMBASE_IF_OVF_POS);
}


/****************************************************************************************************************************************** 
* ��������:	PWMBASE_IntOvfState()
* ����˵��:	PWMBASE��������ж�״̬
* ��    ��: PWMBASE_TypeDef * PWMBASEx     ָ��Ҫ�����õ�PWMBASE����Чֵ����PWMBASE0
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
uint8_t PWMBASE_IntOvfState(PWMBASE_TypeDef * PWMBASEx)
{
	uint8_t State = 0;
	
	assert_param(IS_PWMBASE_ALL(PWMBASEx));       //�������Ĳ���PWMBASEx�Ƿ�Ϸ�  
	
	if(PWMBASEx->IF & PWMBASE_IF_OVF_MSK)
	{
		State = 1;
	}
	
	return State;
}










