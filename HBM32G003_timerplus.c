#include "HBM32G003_timerplus.h"


/****************************************************************************************************************************************** 
* ��������:	TIMPLUS_Common_Init()
* ����˵��:	TIMPLUS����������ʼ��
* ��    ��: TIMPLUS_TypeDef * TIMPLUSx                              ָ��Ҫ�����õ�TIMPLUS����Чֵ����TIMPLUS0
*			TIMPLUS_CommonInitTypeDef * TIMPLUS_CommonInitStruct	����TIMPLUS����趨ֵ�Ľṹ��
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMPLUS_Common_Init(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type,TIMPLUS_CommonInitTypeDef * TIMPLUS_CommonInitStruct)
{
	uint32_t temp = 0;
	
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));                                //�������Ĳ���TIMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_TIMPLUS_TYPE(type));                                   //�������Ĳ���type�Ƿ�Ϸ�  
	
	assert_param(IS_TIMPLUS_CLKDIV(TIMPLUS_CommonInitStruct->ClkDiv));     //�������Ĳ���ClkDiv�Ƿ�Ϸ�   
	
	assert_param(IS_TIMPLUS_MODE(TIMPLUS_CommonInitStruct->Mode));         //�������Ĳ���Mode�Ƿ�Ϸ�  
	
	assert_param(IS_TIMPLUS_CLKSRC(TIMPLUS_CommonInitStruct->ClkSel));     //�������Ĳ���ClkSel�Ƿ�Ϸ�  
	
	assert_param(IS_TIMPLUS_EXTSEL(TIMPLUS_CommonInitStruct->ExtSel));     //�������Ĳ���ExtSel�Ƿ�Ϸ�  
	
	assert_param(IS_TIMPLUS_EXTLEVEL(TIMPLUS_CommonInitStruct->ExtLevel)); //�������Ĳ���ExtLevel�Ƿ�Ϸ�  
	
	assert_param(IS_TIMPLUS_PERIOD(TIMPLUS_CommonInitStruct->Period));     //�������Ĳ���Period�Ƿ�Ϸ�  
	
	assert_param(IS_TIMPLUS_OUTEN(TIMPLUS_CommonInitStruct->OutEn));       //�������Ĳ���OutEn�Ƿ�Ϸ�  
	
	assert_param(IS_TIMPLUS_OVF_IE(TIMPLUS_CommonInitStruct->Ovf_IE));     //�������Ĳ���Ovf_IE�Ƿ�Ϸ�  
	
	assert_param(IS_TIMPLUS_RISE_IE(TIMPLUS_CommonInitStruct->RIse_IE));   //�������Ĳ���RIse_IE�Ƿ�Ϸ�  
	
	assert_param(IS_TIMPLUS_FALL_IE(TIMPLUS_CommonInitStruct->Fall_IE));   //�������Ĳ���Fall_IE�Ƿ�Ϸ�  
	

	switch((uint32_t)TIMPLUSx)
	{
		case((uint32_t)TIMPLUS0):
		
			SYS->CLKEN |= 0x01 << SYS_CLKEN_TIMPLUS0_POS;           //����TIMPLUS0ʱ��
		
		break;
	}
	
	TIMPLUS_Stop(TIMPLUSx,type);                                    //�رն�ʱ�����
	
	TIMPLUSx->DIV = TIMPLUS_CommonInitStruct->ClkDiv;               //TIMPLUS��Ƶϵ��,ʵ�ʷ�ƵΪ����ֵ��1
	
	if((type & TIMPLUS_LOW) == TIMPLUS_LOW)
	{
		temp = TIMPLUSx->CTR;
		
		temp &= ~(0x03 << TIMPLUS_CTR_LOW_MODE_POS);       //����ģʽѡ��
		temp |=  (TIMPLUS_CommonInitStruct->Mode << TIMPLUS_CTR_LOW_MODE_POS);
		
		temp &= ~(0x03 << TIMPLUS_CTR_LOW_CLKSEL_POS);     //����ʱ��Դѡ��
		temp |=  (TIMPLUS_CommonInitStruct->ClkSel << TIMPLUS_CTR_LOW_CLKSEL_POS);
		
		temp &= ~(0x01 << TIMPLUS_CTR_LOW_EXTSEL_POS);     //����ģʽ�����벶��ģʽ�����ź�ѡ��
		temp |=  (TIMPLUS_CommonInitStruct->ExtSel << TIMPLUS_CTR_LOW_EXTSEL_POS);
		
		temp &= ~(0x03 << TIMPLUS_CTR_LOW_EXTLEVEL_POS);   //����ģʽ�����벶��ģʽ�����ź���Ч����ѡ��
		temp |=  (TIMPLUS_CommonInitStruct->ExtLevel << TIMPLUS_CTR_LOW_EXTLEVEL_POS);
		
		temp &= ~(0x01 << TIMPLUS_CTR_LOW_OUTEN_POS);      //��ʱģʽ�������������
		temp |=  (TIMPLUS_CommonInitStruct->OutEn << TIMPLUS_CTR_LOW_OUTEN_POS);
		
		TIMPLUSx->CTR = temp;
		
		TIMPLUSx->LOW_PERIOD = TIMPLUS_CommonInitStruct->Period;    //��ʱ����������ֵ
		
		temp = TIMPLUSx->IE;
		
		temp &= ~(0x01 << TIMPLUS_IE_LOW_OVF_POS);          //��ʱ������ж�ʹ��
		temp |= (TIMPLUS_CommonInitStruct->Ovf_IE << TIMPLUS_IE_LOW_OVF_POS);
		
		temp &= ~(0x01 << TIMPLUS_IE_LOW_RISE_POS);         //��ʱ�����������������ж�ʹ��
		temp |= (TIMPLUS_CommonInitStruct->RIse_IE << TIMPLUS_IE_LOW_RISE_POS);
		
		temp &= ~(0x01 << TIMPLUS_IE_LOW_FALL_POS);         //��ʱ�����������½����ж�ʹ��
		temp |= (TIMPLUS_CommonInitStruct->Fall_IE << TIMPLUS_IE_LOW_FALL_POS);
		
		TIMPLUSx->IE = temp;
	}
	
	if((type & TIMPLUS_HIGH) == TIMPLUS_HIGH)
	{
		if(TIMPLUS_CommonInitStruct->Mode >= HALL_MODE)
		{
			TIMPLUS_CommonInitStruct->Mode = TIMER_MODE;
		}
		
		temp = TIMPLUSx->CTR;
		
		temp &= ~(0x03 << TIMPLUS_CTR_HIGH_MODE_POS);       //����ģʽѡ��
		temp |=  (TIMPLUS_CommonInitStruct->Mode << TIMPLUS_CTR_HIGH_MODE_POS);
		
		temp &= ~(0x03 << TIMPLUS_CTR_HIGH_CLKSEL_POS);     //����ʱ��Դѡ��
		temp |=  (TIMPLUS_CommonInitStruct->ClkSel << TIMPLUS_CTR_HIGH_CLKSEL_POS);
		
		temp &= ~(0x01 << TIMPLUS_CTR_HIGH_EXTSEL_POS);     //����ģʽ�����벶��ģʽ�����ź�ѡ��
		temp |=  (TIMPLUS_CommonInitStruct->ExtSel << TIMPLUS_CTR_HIGH_EXTSEL_POS);
		
		temp &= ~(0x03 << TIMPLUS_CTR_HIGH_EXTLEVEL_POS);   //����ģʽ�����벶��ģʽ�����ź���Ч����ѡ��
		temp |=  (TIMPLUS_CommonInitStruct->ExtLevel << TIMPLUS_CTR_HIGH_EXTLEVEL_POS);
		
		temp &= ~(0x01 << TIMPLUS_CTR_HIGH_OUTEN_POS);      //��ʱģʽ�������������
		temp |=  (TIMPLUS_CommonInitStruct->OutEn << TIMPLUS_CTR_HIGH_OUTEN_POS);
		
		TIMPLUSx->CTR = temp;
		
		TIMPLUSx->HIGH_PERIOD = TIMPLUS_CommonInitStruct->Period;    //��ʱ����������ֵ
		
		temp = TIMPLUSx->IE;
		
		temp &= ~(0x01 << TIMPLUS_IE_HIGH_OVF_POS);          //��ʱ������ж�ʹ��
		temp |= (TIMPLUS_CommonInitStruct->Ovf_IE << TIMPLUS_IE_HIGH_OVF_POS);
		
		temp &= ~(0x01 << TIMPLUS_IE_HIGH_RISE_POS);         //��ʱ�����������������ж�ʹ��
		temp |= (TIMPLUS_CommonInitStruct->RIse_IE << TIMPLUS_IE_HIGH_RISE_POS);
		
		temp &= ~(0x01 << TIMPLUS_IE_HIGH_FALL_POS);         //��ʱ�����������½����ж�ʹ��
		temp |= (TIMPLUS_CommonInitStruct->Fall_IE << TIMPLUS_IE_HIGH_FALL_POS);
		
		TIMPLUSx->IE = temp;
	}
	
	if(TIMPLUSx->IE != 0)
	{
		NVIC_EnableIRQ(TIMPLUS0_IRQn);
	}
}

/****************************************************************************************************************************************** 
* ��������:	TIMPLUS_Hall_Init()
* ����˵��:	TIMPLUSͨ����ʼ��
* ��    ��: TIMPLUS_TypeDef * TIMPLUSx                  ָ��Ҫ�����õ�TIMPLUS����Чֵ����TIMPLUS0
*			TIMPLUS_HallInitTypeDef * TIMPLUS_HallInitStruct	����TIMPLUS HALL����趨ֵ�Ľṹ��
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMPLUS_Hall_Init(TIMPLUS_TypeDef * TIMPLUSx, TIMPLUS_HallInitTypeDef * TIMPLUS_HallInitStruct)
{
	uint32_t temp = 0;
	
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));                                          //�������Ĳ���TIMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_TIMPLUS_HALL0_RISE_IE(TIMPLUS_HallInitStruct->Hall0_Rise_IE));   //�������Ĳ���Hall0_Rise_IE�Ƿ�Ϸ�   
	
	assert_param(IS_TIMPLUS_HALL0_FALL_IE(TIMPLUS_HallInitStruct->Hall0_Fall_IE));   //�������Ĳ���Hall0_Fall_IE�Ƿ�Ϸ�   
	
	assert_param(IS_TIMPLUS_HALL1_RISE_IE(TIMPLUS_HallInitStruct->Hall1_Rise_IE));   //�������Ĳ���Hall1_Rise_IE�Ƿ�Ϸ�   
	
	assert_param(IS_TIMPLUS_HALL1_FALL_IE(TIMPLUS_HallInitStruct->Hall1_Fall_IE));   //�������Ĳ���Hall1_Fall_IE�Ƿ�Ϸ�   
	
	assert_param(IS_TIMPLUS_HALL2_RISE_IE(TIMPLUS_HallInitStruct->Hall2_Rise_IE));   //�������Ĳ���Hall2_Rise_IE�Ƿ�Ϸ�   
	
	assert_param(IS_TIMPLUS_HALL2_FALL_IE(TIMPLUS_HallInitStruct->Hall2_Fall_IE));   //�������Ĳ���Hall2_Fall_IE�Ƿ�Ϸ�   
	
	
	TIMPLUS_Stop(TIMPLUSx,TIMPLUS_LOW);                            //�رն�ʱ�����
	
	temp = 0;
	
	temp &= ~(0x01 << TIMPLUS_IE_HALL0_RISE_POS);          //HALL0�������ж�ʹ��
	temp |= (TIMPLUS_HallInitStruct->Hall0_Rise_IE << TIMPLUS_IE_HALL0_RISE_POS);
	
	temp &= ~(0x01 << TIMPLUS_IE_HALL0_FALL_POS);          //HALL0�½����ж�ʹ��
	temp |= (TIMPLUS_HallInitStruct->Hall0_Fall_IE << TIMPLUS_IE_HALL0_FALL_POS);
	
	temp &= ~(0x01 << TIMPLUS_IE_HALL1_RISE_POS);          //HALL1�������ж�ʹ��
	temp |= (TIMPLUS_HallInitStruct->Hall1_Rise_IE << TIMPLUS_IE_HALL1_RISE_POS);
	
	temp &= ~(0x01 << TIMPLUS_IE_HALL1_FALL_POS);          //HALL1�½����ж�ʹ��
	temp |= (TIMPLUS_HallInitStruct->Hall1_Fall_IE << TIMPLUS_IE_HALL1_FALL_POS);
	
	temp &= ~(0x01 << TIMPLUS_IE_HALL2_RISE_POS);          //HALL2�������ж�ʹ��
	temp |= (TIMPLUS_HallInitStruct->Hall2_Rise_IE << TIMPLUS_IE_HALL2_RISE_POS);
	
	temp &= ~(0x01 << TIMPLUS_IE_HALL2_FALL_POS);          //HALL2�½����ж�ʹ��
	temp |= (TIMPLUS_HallInitStruct->Hall2_Fall_IE << TIMPLUS_IE_HALL2_FALL_POS);
	
	TIMPLUSx->IE = temp;
	
	if(TIMPLUSx->IE != 0)
	{
		NVIC_EnableIRQ(TIMPLUS0_IRQn);
	}
}

/****************************************************************************************************************************************** 
* ��������:	TIMPLUS_Start()
* ����˵��:	������ʱ�����ӳ�ʼֵ��ʼ��ʱ/����
* ��    ��: TIMPLUS_TypeDef * TIMPLUSx       ��Чֵ��TIMPLUS0
*           TIMPLUS_TypeTypeDef type	     ��ʱ��ѡ��   1����16λ��ʱ��  2����16λ��ʱ�� 
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMPLUS_Start(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));                         //�������Ĳ���TIMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_TIMPLUS_TYPE(type));                            //�������Ĳ���type�Ƿ�Ϸ�  
	
	
	if((type & TIMPLUS_LOW) == TIMPLUS_LOW)
	{
		TIMPLUSx->EN |= (0x01 << TIMPLUS_EN_LOW_POS);
	}
	
	if((type & TIMPLUS_HIGH) == TIMPLUS_HIGH)
	{
		TIMPLUSx->EN |= (0x01 << TIMPLUS_EN_HIGH_POS);
	}
}


/****************************************************************************************************************************************** 
* ��������:	TIMPLUS_Stop()
* ����˵��:	ֹͣ��ʱ��
* ��    ��: TIMPLUS_TypeDef * TIMPLUSx       ��Чֵ��TIMPLUS0
*           TIMPLUS_TypeTypeDef type	     ��ʱ��ѡ��   1����16λ��ʱ��  2����16λ��ʱ�� 
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMPLUS_Stop(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));                         //�������Ĳ���TIMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_TIMPLUS_TYPE(type));                            //�������Ĳ���type�Ƿ�Ϸ�  
	
	
	if((type & TIMPLUS_LOW) == TIMPLUS_LOW)
	{
		TIMPLUSx->EN &= ~(0x01 << TIMPLUS_EN_LOW_POS);
	}
	
	if((type & TIMPLUS_HIGH) == TIMPLUS_HIGH)
	{
		TIMPLUSx->EN &= ~(0x01 << TIMPLUS_EN_HIGH_POS);
	}
}

/****************************************************************************************************************************************** 
* ��������:	TIMPLUS_SetClkDiv()
* ����˵��:	����Ԥ��Ƶϵ��   ʵ�ʷ�ƵΪ����ֵ��1
* ��    ��: TIMPLUS_TypeDef * TIMPLUSx       ��Чֵ��TIMPLUS0
            uint8_t Clk_Div   Ԥ��Ƶϵ��   
*			
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMPLUS_SetClkDiv(TIMPLUS_TypeDef * TIMPLUSx,uint8_t Clk_Div)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));       //�������Ĳ���TIMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_TIMPLUS_CLKDIV(Clk_Div));     //�������Ĳ���ClkDiv�Ƿ�Ϸ�  
	

	TIMPLUSx->DIV = Clk_Div;          //TIMPLUS��Ƶϵ��  ʵ�ʷ�ƵΪ����ֵ��1
}


/****************************************************************************************************************************************** 
* ��������:	TIMPLUS_SetMode()
* ����˵��:	���ù���ģʽ
* ��    ��: TIMPLUS_TypeDef * TIMPLUSx       ��Чֵ��TIMPLUS0
            TIMPLUS_TypeTypeDef type     ��ʱ��ѡ��   1����16λ��ʱ��  2����16λ��ʱ�� 
*	        TIMPLUS_ModeTypeDef Mode	 ����ģʽѡ��	
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMPLUS_SetMode(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type,TIMPLUS_ModeTypeDef Mode)
{
	uint32_t temp = 0;
	
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));       //�������Ĳ���TIMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_TIMPLUS_TYPE(type));          //�������Ĳ���type�Ƿ�Ϸ�  
	
	assert_param(IS_TIMPLUS_MODE(Mode));          //�������Ĳ���Mode�Ƿ�Ϸ�  
	
	
	if((type & TIMPLUS_LOW) == TIMPLUS_LOW)
	{
		temp = TIMPLUSx->CTR;
		
		temp &= ~(0x03 << TIMPLUS_CTR_LOW_MODE_POS);       //����ģʽѡ��
		temp |=  (Mode << TIMPLUS_CTR_LOW_MODE_POS);
		
		TIMPLUSx->CTR = temp;
	}
	
	if((type & TIMPLUS_HIGH) == TIMPLUS_HIGH)
	{
		temp = TIMPLUSx->CTR;
		
		temp &= ~(0x03 << TIMPLUS_CTR_HIGH_MODE_POS);      //����ģʽѡ��
		temp |=  (Mode << TIMPLUS_CTR_HIGH_MODE_POS);
		
		TIMPLUSx->CTR = temp;
	}
}


/****************************************************************************************************************************************** 
* ��������:	TIMPLUS_SetClkSel()
* ����˵��:	���ü���ʱ��Դ
* ��    ��: TIMPLUS_TypeDef * TIMPLUSx       ��Чֵ��TIMPLUS0
            TIMPLUS_TypeTypeDef type         ��ʱ��ѡ��   1����16λ��ʱ��  2����16λ��ʱ�� 
*	        TIMPLUS_ClkSelTypeDef ClkSel	 ����ʱ��Դѡ��
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMPLUS_SetClkSel(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type,TIMPLUS_ClkSelTypeDef ClkSel)
{
	uint32_t temp = 0;
	
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));       //�������Ĳ���TIMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_TIMPLUS_TYPE(type));          //�������Ĳ���type�Ƿ�Ϸ�  
	
	assert_param(IS_TIMPLUS_CLKSRC(ClkSel));      //�������Ĳ���ClkSel�Ƿ�Ϸ�  
	
	
	if((type & TIMPLUS_LOW) == TIMPLUS_LOW)
	{
		temp = TIMPLUSx->CTR;
		
		temp &= ~(0x03 << TIMPLUS_CTR_LOW_CLKSEL_POS);       //����ʱ��Դѡ��
		temp |=  (ClkSel << TIMPLUS_CTR_LOW_CLKSEL_POS);
		
		TIMPLUSx->CTR = temp;
	}
	
	if((type & TIMPLUS_HIGH) == TIMPLUS_HIGH)
	{
		temp = TIMPLUSx->CTR;
		
		temp &= ~(0x03 << TIMPLUS_CTR_HIGH_CLKSEL_POS);       //����ʱ��Դѡ��
		temp |=  (ClkSel << TIMPLUS_CTR_HIGH_CLKSEL_POS);
		
		TIMPLUSx->CTR = temp;
	}	
}


/****************************************************************************************************************************************** 
* ��������:	TIMPLUS_SetExtSel()
* ����˵��:	���ü���ģʽ�����벶��ģʽ�����ź�
* ��    ��: TIMPLUS_TypeDef * TIMPLUSx       ��Чֵ��TIMPLUS0
            TIMPLUS_TypeTypeDef type         ��ʱ��ѡ��   1����16λ��ʱ��  2����16λ��ʱ�� 
*	        TIMPLUS_ExtSelTypeDef ExtSel	 ����ģʽ�����벶��ģʽ�����ź�ѡ��
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMPLUS_SetExtSel(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type,TIMPLUS_ExtSelTypeDef ExtSel)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));       //�������Ĳ���TIMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_TIMPLUS_TYPE(type));          //�������Ĳ���type�Ƿ�Ϸ�  
	
	assert_param(IS_TIMPLUS_EXTSEL(ExtSel));      //�������Ĳ���ExtSel�Ƿ�Ϸ�  
	

	if((type & TIMPLUS_LOW) == TIMPLUS_LOW)
	{
		if(ExtSel == TIMPLUS_IN0)                 //����ģʽ�����벶��ģʽ�����ź�ѡ��
		{
			TIMPLUSx->CTR &= ~(0x01 << TIMPLUS_CTR_LOW_EXTSEL_POS); 
		}
		else
		{
			TIMPLUSx->CTR |=  (0x01 << TIMPLUS_CTR_LOW_EXTSEL_POS);
		}
	}
	
	if((type & TIMPLUS_HIGH) == TIMPLUS_HIGH)
	{
		if(ExtSel == TIMPLUS_IN0)                 //����ģʽ�����벶��ģʽ�����ź�ѡ��
		{
			TIMPLUSx->CTR &= ~(0x01 << TIMPLUS_CTR_HIGH_EXTSEL_POS); 
		}
		else
		{
			TIMPLUSx->CTR |=  (0x01 << TIMPLUS_CTR_HIGH_EXTSEL_POS);
		}
	}	
}


/****************************************************************************************************************************************** 
* ��������:	TIMPLUS_SetExtLevel()
* ����˵��:	���ü���ģʽ�����벶��ģʽ�����ź���Ч����
* ��    ��: TIMPLUS_TypeDef * TIMPLUSx       ��Чֵ��TIMPLUS0
            TIMPLUS_TypeTypeDef type             ��ʱ��ѡ��   1����16λ��ʱ��  2����16λ��ʱ�� 
*	        TIMPLUS_ExtLevelTypeDef ExtLevel	 ����ģʽ�����벶��ģʽ�����ź���Ч����ѡ��
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMPLUS_SetExtLevel(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type,TIMPLUS_ExtLevelTypeDef ExtLevel)
{
	uint32_t temp = 0;
	
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //�������Ĳ���TIMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_TIMPLUS_TYPE(type));              //�������Ĳ���type�Ƿ�Ϸ�  
	
	assert_param(IS_TIMPLUS_EXTLEVEL(ExtLevel));      //�������Ĳ���ExtLevel�Ƿ�Ϸ�  
	
	
	if((type & TIMPLUS_LOW) == TIMPLUS_LOW)
	{
		temp = TIMPLUSx->CTR;
		
		temp &= ~(0x03 << TIMPLUS_CTR_LOW_EXTLEVEL_POS);       //����ģʽ�����벶��ģʽ�����ź���Ч����ѡ��
		temp |=  (ExtLevel << TIMPLUS_CTR_LOW_EXTLEVEL_POS);
		
		TIMPLUSx->CTR = temp;
	}
	
	if((type & TIMPLUS_HIGH) == TIMPLUS_HIGH)
	{
		temp = TIMPLUSx->CTR;
		
		temp &= ~(0x03 << TIMPLUS_CTR_HIGH_EXTLEVEL_POS);       //����ģʽ�����벶��ģʽ�����ź���Ч����ѡ��
		temp |=  (ExtLevel << TIMPLUS_CTR_HIGH_EXTLEVEL_POS);
		
		TIMPLUSx->CTR = temp;
	}	
}

/****************************************************************************************************************************************** 
* ��������:	TIMPLUS_SetOutEn()
* ����˵��:	���ö�ʱģʽ�������������
* ��    ��: TIMPLUS_TypeDef * TIMPLUSx       ��Чֵ��TIMPLUS0
            TIMPLUS_TypeTypeDef type         ��ʱ��ѡ��   1����16λ��ʱ��  2����16λ��ʱ�� 
*	        TIMPLUS_OutEnTypeDef OutEn	     ��ʱģʽ�������������
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMPLUS_SetOutEn(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type,FunctionalState OutEn)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //�������Ĳ���TIMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_TIMPLUS_TYPE(type));              //�������Ĳ���type�Ƿ�Ϸ�  
	
	assert_param(IS_TIMPLUS_OUTEN(OutEn));            //�������Ĳ���OutEn�Ƿ�Ϸ�  
	
	
	if((type & TIMPLUS_LOW) == TIMPLUS_LOW)
	{
		if(OutEn == DISABLE)                          //��ʱģʽ�������������
		{
			TIMPLUSx->CTR &= ~(0x01 << TIMPLUS_CTR_LOW_OUTEN_POS);
		}
		else
		{
			TIMPLUSx->CTR |=  (0x01 << TIMPLUS_CTR_LOW_OUTEN_POS);
		}
	}
	
	if((type & TIMPLUS_HIGH) == TIMPLUS_HIGH)
	{
		if(OutEn == DISABLE)                          //��ʱģʽ�������������
		{
			TIMPLUSx->CTR &= ~(0x01 << TIMPLUS_CTR_HIGH_OUTEN_POS);
		}
		else
		{
			TIMPLUSx->CTR |=  (0x01 << TIMPLUS_CTR_HIGH_OUTEN_POS);
		}
	}	
}

/****************************************************************************************************************************************** 
* ��������:	TIMPLUS_SetPeriod()
* ����˵��:	���ö�ʱ����������ֵ
* ��    ��: TIMPLUS_TypeDef * TIMPLUSx       ��Чֵ��TIMPLUS0
            TIMPLUS_TypeTypeDef type         ��ʱ��ѡ��   1����16λ��ʱ��  2����16λ��ʱ�� 
*	        uint16_t Period          	     ��ʱ����������ֵ
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMPLUS_SetPeriod(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type,uint16_t Period)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //�������Ĳ���TIMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_TIMPLUS_TYPE(type));              //�������Ĳ���type�Ƿ�Ϸ�  
	
	assert_param(IS_TIMPLUS_PERIOD(Period));          //�������Ĳ���Period�Ƿ�Ϸ�  
	
	
	if((type & TIMPLUS_LOW) == TIMPLUS_LOW)
	{
		TIMPLUSx->LOW_PERIOD = Period;     //��ʱ����������ֵ   ʵ������ֵΪ����ֵ��1
	}
	
	if((type & TIMPLUS_HIGH) == TIMPLUS_HIGH)
	{
		TIMPLUSx->HIGH_PERIOD = Period;    //��ʱ����������ֵ   ʵ������ֵΪ����ֵ��1
	}	
}

/****************************************************************************************************************************************** 
* ��������:	TIMPLUS_SetPeriod()
* ����˵��:	��ȡ��ʱ����������ֵ
* ��    ��: TIMPLUS_TypeDef * TIMPLUSx       ��Чֵ��TIMPLUS0
            TIMPLUS_TypeTypeDef type         ��ʱ��ѡ��   1����16λ��ʱ��  2����16λ��ʱ��        	     
* ��    ��: ��ʱ����������ֵ
* ע������: ��
******************************************************************************************************************************************/
uint16_t TIMPLUS_GetPeriod(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //�������Ĳ���TIMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_TIMPLUS_TYPE(type));              //�������Ĳ���type�Ƿ�Ϸ�  
	
	
	if(type == TIMPLUS_LOW)
	{
		return TIMPLUSx->LOW_PERIOD;     //���ض�ʱ����������ֵ  
	}
	else if(type == TIMPLUS_HIGH)
	{
		return TIMPLUSx->HIGH_PERIOD;    //���ض�ʱ����������ֵ
	}

	return 0;
}


/****************************************************************************************************************************************** 
* ��������:	TIMPLUS_GetCurrentCnt()
* ����˵��:	��ȡ��ʱ����ǰ����ֵ
* ��    ��: TIMPLUS_TypeDef * TIMPLUSx       ��Чֵ��TIMPLUS0
            TIMPLUS_TypeTypeDef type         ��ʱ��ѡ��   1����16λ��ʱ��  2����16λ��ʱ��        	     
* ��    ��: ��ʱ����ǰ����ֵ
* ע������: ��
******************************************************************************************************************************************/
uint16_t TIMPLUS_GetCurrentValue(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //�������Ĳ���TIMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_TIMPLUS_TYPE(type));              //�������Ĳ���type�Ƿ�Ϸ�  
	
	
	if(type == TIMPLUS_LOW)
	{
		return TIMPLUSx->LOW_CNT;     //���ض�ʱ����ǰ����ֵ
	}
	else if(type == TIMPLUS_HIGH)
	{
		return TIMPLUSx->HIGH_CNT;    //���ض�ʱ����ǰ����ֵ
	}
	
	return 0;
}


/****************************************************************************************************************************************** 
* ��������:	TIMPLUS_GetCaptureCnt()
* ����˵��:	��ȡ��ʱ������ֵ
* ��    ��: TIMPLUS_TypeDef * TIMPLUSx       ��Чֵ��TIMPLUS0
            TIMPLUS_TypeTypeDef type         ��ʱ��ѡ��   1����16λ��ʱ��  2����16λ��ʱ��        	     
* ��    ��: ��ʱ������ֵ
* ע������: ��
******************************************************************************************************************************************/
uint16_t TIMPLUS_GetCaptureValue(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //�������Ĳ���TIMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_TIMPLUS_TYPE(type));              //�������Ĳ���type�Ƿ�Ϸ�  
	
	
	if(type == TIMPLUS_LOW)
	{
		return TIMPLUSx->LOW_CVAL;     //���ض�ʱ������ֵ
	}
	else if(type == TIMPLUS_HIGH)
	{
		return TIMPLUSx->HIGH_CVAL;    //���ض�ʱ������ֵ
	}
	return 0;
}


/****************************************************************************************************************************************** 
* ��������:	TIMPLUS_GetHallLevel()
* ����˵��:	��ȡHALL��ʼ��ƽ
* ��    ��: TIMPLUS_TypeDef * TIMPLUSx       ��Чֵ��TIMPLUS0
            TIMPLUS_HallTypeDef HallType    ����ѡ��  HALL0  HALL1  HALL2     	     
* ��    ��: HALL��ʼ��ƽ
* ע������: ��
******************************************************************************************************************************************/
uint8_t TIMPLUS_GetHallLevel(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_HallTypeDef HallType)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //�������Ĳ���TIMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_TIMPLUS_HALL_TYPE(HallType));    //�������Ĳ���HallType�Ƿ�Ϸ�  
	
	
	if(HallType == HALL_0)
	{
		return (TIMPLUSx->HALL_VAL & TIMPLUS_HALL_VAL_HALL0_MSK);
	}
	else if(HallType == HALL_1)
	{
		return (TIMPLUSx->HALL_VAL & TIMPLUS_HALL_VAL_HALL1_MSK);
	}
	else if(HallType == HALL_2)
	{
		return (TIMPLUSx->HALL_VAL & TIMPLUS_HALL_VAL_HALL2_MSK);
	}
	
	return 0;
}


/****************************************************************************************************************************************** 
* ��������:	TIMPLUS_IntOvfEn()
* ����˵��:	���ö�ʱ������ж�ʹ��
* ��    ��: TIMPLUS_TypeDef * TIMPLUSx       ��Чֵ��TIMPLUS0
            TIMPLUS_TypeTypeDef type         ��ʱ��ѡ��   1����16λ��ʱ��  2����16λ��ʱ��        	     
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMPLUS_IntOvfEn(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //�������Ĳ���TIMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_TIMPLUS_TYPE(type));              //�������Ĳ���type�Ƿ�Ϸ�  
	
	
	if((type & TIMPLUS_LOW) == TIMPLUS_LOW)
	{
		TIMPLUSx->IE |= (0x01 << TIMPLUS_IE_LOW_OVF_POS);         //��ʱ������ж�ʹ��
	}
	
	if((type & TIMPLUS_HIGH) == TIMPLUS_HIGH)
	{
		TIMPLUSx->IE |= (0x01 << TIMPLUS_IE_HIGH_OVF_POS);        //��ʱ������ж�ʹ��
	}
}

/****************************************************************************************************************************************** 
* ��������:	TIMPLUS_IntOvfDis()
* ����˵��:	���ö�ʱ������жϽ���
* ��    ��: TIMPLUS_TypeDef * TIMPLUSx       ��Чֵ��TIMPLUS0
            TIMPLUS_TypeTypeDef type         ��ʱ��ѡ��   1����16λ��ʱ��  2����16λ��ʱ��        	     
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMPLUS_IntOvfDis(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //�������Ĳ���TIMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_TIMPLUS_TYPE(type));              //�������Ĳ���type�Ƿ�Ϸ�  
	
	
	if((type & TIMPLUS_LOW) == TIMPLUS_LOW)
	{
		TIMPLUSx->IE &= ~(0x01 << TIMPLUS_IE_LOW_OVF_POS);         //��ʱ������жϽ���
	}
	
	if((type & TIMPLUS_HIGH) == TIMPLUS_HIGH)
	{
		TIMPLUSx->IE &= ~(0x01 << TIMPLUS_IE_HIGH_OVF_POS);        //��ʱ������жϽ���
	}
}

/****************************************************************************************************************************************** 
* ��������:	TIMPLUS_IntOvfClr()
* ����˵��:	�����ʱ������ж�״̬
* ��    ��: TIMPLUS_TypeDef * TIMPLUSx       ��Чֵ��TIMPLUS0
            TIMPLUS_TypeTypeDef type         ��ʱ��ѡ��   1����16λ��ʱ��  2����16λ��ʱ��        	     
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMPLUS_IntOvfClr(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //�������Ĳ���TIMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_TIMPLUS_TYPE(type));              //�������Ĳ���type�Ƿ�Ϸ�  
	
	
	if((type & TIMPLUS_LOW) == TIMPLUS_LOW)
	{
		TIMPLUSx->IF = (0x01 << TIMPLUS_IF_LOW_OVF_POS);         //�����ʱ������ж�״̬
	}
	
	if((type & TIMPLUS_HIGH) == TIMPLUS_HIGH)
	{
		TIMPLUSx->IF = (0x01 << TIMPLUS_IF_HIGH_OVF_POS);        //�����ʱ������ж�״̬
	}
}

/****************************************************************************************************************************************** 
* ��������:	TIMPLUS_IntOvfState()
* ����˵��:	��ȡ��ʱ������ж�״̬
* ��    ��: TIMPLUS_TypeDef * TIMPLUSx       ��Чֵ��TIMPLUS0
            TIMPLUS_TypeTypeDef type         ��ʱ��ѡ��   1����16λ��ʱ��  2����16λ��ʱ��        	     
* ��    ��: 1 ����ж��Ѿ�����    0  ����ж�δ����
* ע������: ��
******************************************************************************************************************************************/
uint8_t TIMPLUS_IntOvfState(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //�������Ĳ���TIMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_TIMPLUS_TYPE(type));              //�������Ĳ���type�Ƿ�Ϸ�  
	
	
	if(type == TIMPLUS_LOW)
	{
		if(TIMPLUSx->IF & TIMPLUS_IF_LOW_OVF_MSK)
		{
			return 1;
		}
	}
	else if(type == TIMPLUS_HIGH)
	{
		if(TIMPLUSx->IF & TIMPLUS_IF_HIGH_OVF_MSK)
		{
			return 1;
		}
	}
	
	return 0;
}


/****************************************************************************************************************************************** 
* ��������:	TIMPLUS_IntRiseEn()
* ����˵��:	���ö�ʱ�����������������ж�ʹ��
* ��    ��: TIMPLUS_TypeDef * TIMPLUSx       ��Чֵ��TIMPLUS0
            TIMPLUS_TypeTypeDef type         ��ʱ��ѡ��   1����16λ��ʱ��  2����16λ��ʱ��        	     
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMPLUS_IntRiseEn(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //�������Ĳ���TIMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_TIMPLUS_TYPE(type));              //�������Ĳ���type�Ƿ�Ϸ�  
	
	
	if((type & TIMPLUS_LOW) == TIMPLUS_LOW)
	{
		TIMPLUSx->IE |= (0x01 << TIMPLUS_IE_LOW_RISE_POS);         //��ʱ�����������������ж�ʹ��
	}
	
	if((type & TIMPLUS_HIGH) == TIMPLUS_HIGH)
	{
		TIMPLUSx->IE |= (0x01 << TIMPLUS_IE_HIGH_RISE_POS);        //��ʱ�����������������ж�ʹ��
	}
}

/****************************************************************************************************************************************** 
* ��������:	TIMPLUS_IntRiseDis()
* ����˵��:	���ö�ʱ�����������������жϽ���
* ��    ��: TIMPLUS_TypeDef * TIMPLUSx       ��Чֵ��TIMPLUS0
            TIMPLUS_TypeTypeDef type         ��ʱ��ѡ��   1����16λ��ʱ��  2����16λ��ʱ��        	     
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMPLUS_IntRiseDis(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //�������Ĳ���TIMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_TIMPLUS_TYPE(type));              //�������Ĳ���type�Ƿ�Ϸ�  
	
	
	if((type & TIMPLUS_LOW) == TIMPLUS_LOW)
	{
		TIMPLUSx->IE &= ~(0x01 << TIMPLUS_IE_LOW_RISE_POS);         //��ʱ�����������������жϽ���
	}
	
	if((type & TIMPLUS_HIGH) == TIMPLUS_HIGH)
	{
		TIMPLUSx->IE &= ~(0x01 << TIMPLUS_IE_HIGH_RISE_POS);        //��ʱ�����������������жϽ���
	}
}

/****************************************************************************************************************************************** 
* ��������:	TIMPLUS_IntRiseClr()
* ����˵��:	�����ʱ�����������������ж�״̬
* ��    ��: TIMPLUS_TypeDef * TIMPLUSx       ��Чֵ��TIMPLUS0
            TIMPLUS_TypeTypeDef type         ��ʱ��ѡ��   1����16λ��ʱ��  2����16λ��ʱ��        	     
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMPLUS_IntRiseClr(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //�������Ĳ���TIMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_TIMPLUS_TYPE(type));              //�������Ĳ���type�Ƿ�Ϸ�  
	
	
	if((type & TIMPLUS_LOW) == TIMPLUS_LOW)
	{
		TIMPLUSx->IF = (0x01 << TIMPLUS_IF_LOW_RISE_POS);         //�����ʱ�����������������ж�״̬
	}
	
	if((type & TIMPLUS_HIGH) == TIMPLUS_HIGH)
	{
		TIMPLUSx->IF = (0x01 << TIMPLUS_IF_HIGH_RISE_POS);        //�����ʱ�����������������ж�״̬
	}
}


/****************************************************************************************************************************************** 
* ��������:	TIMPLUS_IntRiseState()
* ����˵��:	��ȡ��ʱ�����������������ж�״̬
* ��    ��: TIMPLUS_TypeDef * TIMPLUSx       ��Чֵ��TIMPLUS0
            TIMPLUS_TypeTypeDef type         ��ʱ��ѡ��   1����16λ��ʱ��  2����16λ��ʱ��        	     
* ��    ��: 1 �������ж��Ѿ�����    0 �������ж�δ����
* ע������: ��
******************************************************************************************************************************************/
uint8_t TIMPLUS_IntRiseState(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //�������Ĳ���TIMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_TIMPLUS_TYPE(type));              //�������Ĳ���type�Ƿ�Ϸ�  
	
	
	if(type == TIMPLUS_LOW)
	{
		if(TIMPLUSx->IF & TIMPLUS_IF_LOW_RISE_MSK)
		{
			return 1;
		}
	}
	else if(type == TIMPLUS_HIGH)
	{
		if(TIMPLUSx->IF & TIMPLUS_IF_HIGH_RISE_MSK)
		{
			return 1;
		}
	}
	
	return 0;
}


/****************************************************************************************************************************************** 
* ��������:	TIMPLUS_IntFallEn()
* ����˵��:	���ö�ʱ�����������½����ж�ʹ��
* ��    ��: TIMPLUS_TypeDef * TIMPLUSx       ��Чֵ��TIMPLUS0
            TIMPLUS_TypeTypeDef type         ��ʱ��ѡ��   1����16λ��ʱ��  2����16λ��ʱ��        	     
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMPLUS_IntFallEn(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //�������Ĳ���TIMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_TIMPLUS_TYPE(type));              //�������Ĳ���type�Ƿ�Ϸ�  
	
	
	if((type & TIMPLUS_LOW) == TIMPLUS_LOW)
	{
		TIMPLUSx->IE |= (0x01 << TIMPLUS_IE_LOW_FALL_POS);         //��ʱ�����������½����ж�ʹ��
	}
	
	if((type & TIMPLUS_HIGH) == TIMPLUS_HIGH)
	{
		TIMPLUSx->IE |= (0x01 << TIMPLUS_IE_HIGH_FALL_POS);        //��ʱ�����������½����ж�ʹ��
	}
}

/****************************************************************************************************************************************** 
* ��������:	TIMPLUS_IntFallDis()
* ����˵��:	���ö�ʱ�����������½����жϽ���
* ��    ��: TIMPLUS_TypeDef * TIMPLUSx       ��Чֵ��TIMPLUS0
            TIMPLUS_TypeTypeDef type         ��ʱ��ѡ��   1����16λ��ʱ��  2����16λ��ʱ��        	     
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMPLUS_IntFallDis(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //�������Ĳ���TIMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_TIMPLUS_TYPE(type));              //�������Ĳ���type�Ƿ�Ϸ�  
	
	
	if((type & TIMPLUS_LOW) == TIMPLUS_LOW)
	{
		TIMPLUSx->IE &= ~(0x01 << TIMPLUS_IE_LOW_FALL_POS);         //��ʱ�����������½����жϽ���
	}
	
	if((type & TIMPLUS_HIGH) == TIMPLUS_HIGH)
	{
		TIMPLUSx->IE &= ~(0x01 << TIMPLUS_IE_HIGH_FALL_POS);        //��ʱ�����������½����жϽ���
	}
}

/****************************************************************************************************************************************** 
* ��������:	TIMPLUS_IntFallClr()
* ����˵��:	�����ʱ�����������½����ж�״̬
* ��    ��: TIMPLUS_TypeDef * TIMPLUSx       ��Чֵ��TIMPLUS0
            TIMPLUS_TypeTypeDef type         ��ʱ��ѡ��   1����16λ��ʱ��  2����16λ��ʱ��        	     
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMPLUS_IntFallClr(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //�������Ĳ���TIMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_TIMPLUS_TYPE(type));              //�������Ĳ���type�Ƿ�Ϸ�  
	
	
	if((type & TIMPLUS_LOW) == TIMPLUS_LOW)
	{
		TIMPLUSx->IF = (0x01 << TIMPLUS_IF_LOW_FALL_POS);         //�����ʱ�����������½����ж�״̬
	}
	
	if((type & TIMPLUS_HIGH) == TIMPLUS_HIGH)
	{
		TIMPLUSx->IF = (0x01 << TIMPLUS_IF_HIGH_FALL_POS);        //�����ʱ�����������½����ж�״̬
	}
}


/****************************************************************************************************************************************** 
* ��������:	TIMPLUS_IntFallState()
* ����˵��:	��ȡ��ʱ�����������½����ж�״̬
* ��    ��: TIMPLUS_TypeDef * TIMPLUSx       ��Чֵ��TIMPLUS0
            TIMPLUS_TypeTypeDef type         ��ʱ��ѡ��   1����16λ��ʱ��  2����16λ��ʱ��        	     
* ��    ��: 1 �½����ж��Ѿ�����    0 �½����ж�δ����
* ע������: ��
******************************************************************************************************************************************/
uint8_t TIMPLUS_IntFallState(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_TypeTypeDef type)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //�������Ĳ���TIMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_TIMPLUS_TYPE(type));              //�������Ĳ���type�Ƿ�Ϸ�  
	
	
	if(type == TIMPLUS_LOW)
	{
		if(TIMPLUSx->IF & TIMPLUS_IF_LOW_FALL_MSK)
		{
			return 1;
		}
	}
	else if(type == TIMPLUS_HIGH)
	{
		if(TIMPLUSx->IF & TIMPLUS_IF_HIGH_FALL_MSK)
		{
			return 1;
		}
	}
	
	return 0;
}


/****************************************************************************************************************************************** 
* ��������:	TIMPLUS_IntHallRiseEn()
* ����˵��:	���ö�ʱ��HALL�������ж�ʹ��
* ��    ��: TIMPLUS_TypeDef * TIMPLUSx       ��Чֵ��TIMPLUS0
            TIMPLUS_HallTypeDef HallType    ����ѡ��  HALL0  HALL1  HALL2        	     
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMPLUS_IntHallRiseEn(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_HallTypeDef HallType)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //�������Ĳ���TIMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_TIMPLUS_HALL_TYPE(HallType));     //�������Ĳ���HallType�Ƿ�Ϸ�  
	
	
	if((HallType & HALL_0) == HALL_0)
	{
		TIMPLUSx->IE |= (0x01 << TIMPLUS_IE_HALL0_RISE_POS);      //��ʱ��HALL0�������ж�ʹ��
	}
	
	if((HallType & HALL_1) == HALL_1)
	{
		TIMPLUSx->IE |= (0x01 << TIMPLUS_IE_HALL1_RISE_POS);     //��ʱ��HALL1�������ж�ʹ��
	}
	
	if((HallType & HALL_2) == HALL_2)
	{
		TIMPLUSx->IE |= (0x01 << TIMPLUS_IE_HALL2_RISE_POS);     //��ʱ��HALL2�������ж�ʹ��
	}
}

/****************************************************************************************************************************************** 
* ��������:	TIMPLUS_IntHallRiseDis()
* ����˵��:	���ö�ʱ��HALL�������жϽ���
* ��    ��: TIMPLUS_TypeDef * TIMPLUSx       ��Чֵ��TIMPLUS0
            TIMPLUS_HallTypeDef HallType    ����ѡ��  HALL0  HALL1  HALL2     	     
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMPLUS_IntHallRiseDis(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_HallTypeDef HallType)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //�������Ĳ���TIMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_TIMPLUS_HALL_TYPE(HallType));     //�������Ĳ���HallType�Ƿ�Ϸ�  
	
	
	if((HallType & HALL_0) == HALL_0)
	{
		TIMPLUSx->IE &= ~(0x01 << TIMPLUS_IE_HALL0_RISE_POS);    //��ʱ��HALL0�������жϽ���
	}
	
	if((HallType & HALL_1) == HALL_1)
	{
		TIMPLUSx->IE &= ~(0x01 << TIMPLUS_IE_HALL1_RISE_POS);    //��ʱ��HALL1�������жϽ���
	}
	
	if((HallType & HALL_2) == HALL_2)
	{
		TIMPLUSx->IE &= ~(0x01 << TIMPLUS_IE_HALL2_RISE_POS);    //��ʱ��HALL2�������жϽ���
	}
}

/****************************************************************************************************************************************** 
* ��������:	TIMPLUS_IntHallRiseClr()
* ����˵��:	�����ʱ��HALL�������ж�״̬
* ��    ��: TIMPLUS_TypeDef * TIMPLUSx       ��Чֵ��TIMPLUS0
            TIMPLUS_HallTypeDef HallType    ����ѡ��  HALL0  HALL1  HALL2        	     
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMPLUS_IntHallRiseClr(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_HallTypeDef HallType)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //�������Ĳ���TIMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_TIMPLUS_HALL_TYPE(HallType));     //�������Ĳ���HallType�Ƿ�Ϸ�  
	
	
	if((HallType & HALL_0) == HALL_0)
	{
		TIMPLUSx->IF = (0x01 << TIMPLUS_IF_HALL0_RISE_POS);    //�����ʱ��HALL0�������ж�״̬
	}
	
	if((HallType & HALL_1) == HALL_1)
	{
		TIMPLUSx->IF = (0x01 << TIMPLUS_IF_HALL1_RISE_POS);    //�����ʱ��HALL1�������ж�״̬
	}
	
	if((HallType & HALL_2) == HALL_2)
	{
		TIMPLUSx->IF = (0x01 << TIMPLUS_IF_HALL2_RISE_POS);    //�����ʱ��HALL2�������ж�״̬
	}
}


/****************************************************************************************************************************************** 
* ��������:	TIMPLUS_IntHallRiseState()
* ����˵��:	��ȡ��ʱ��HALL�������ж�״̬
* ��    ��: TIMPLUS_TypeDef * TIMPLUSx       ��Чֵ��TIMPLUS0  	     
* ��    ��: 1 �������ж��Ѿ�����    0 �������ж�δ����
* ע������: ��
******************************************************************************************************************************************/
uint8_t TIMPLUS_IntHallRiseState(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_HallTypeDef HallType)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //�������Ĳ���TIMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_TIMPLUS_HALL_TYPE(HallType));     //�������Ĳ���HallType�Ƿ�Ϸ�  
	
	
	if(HallType == HALL_0)
	{
		if(TIMPLUSx->IF & TIMPLUS_IF_HALL0_RISE_MSK)
		{
			return 1;
		}
	}
	else if(HallType == HALL_1)
	{
		if(TIMPLUSx->IF & TIMPLUS_IF_HALL1_RISE_MSK)
		{
			return 1;
		}
	}
	else if(HallType == HALL_2)
	{
		if(TIMPLUSx->IF & TIMPLUS_IF_HALL2_RISE_MSK)
		{
			return 1;
		}
	}
	
	return 0;
}


/****************************************************************************************************************************************** 
* ��������:	TIMPLUS_IntHallFallEn()
* ����˵��:	���ö�ʱ��HALL�½����ж�ʹ��
* ��    ��: TIMPLUS_TypeDef * TIMPLUSx       ��Чֵ��TIMPLUS0
            TIMPLUS_HallTypeDef HallType    ����ѡ��  HALL0  HALL1  HALL2         	     
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMPLUS_IntHallFallEn(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_HallTypeDef HallType)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //�������Ĳ���TIMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_TIMPLUS_HALL_TYPE(HallType));     //�������Ĳ���HallType�Ƿ�Ϸ�  
	
	
	if((HallType & HALL_0) == HALL_0)
	{
		TIMPLUSx->IE |= (0x01 << TIMPLUS_IE_HALL0_FALL_POS);      //��ʱ��HALL0�½����ж�ʹ��
	}
	
	if((HallType & HALL_1) == HALL_1)
	{
		TIMPLUSx->IE |= (0x01 << TIMPLUS_IE_HALL1_FALL_POS);     //��ʱ��HALL1�½����ж�ʹ��
	}
	
	if((HallType & HALL_2) == HALL_2)
	{
		TIMPLUSx->IE |= (0x01 << TIMPLUS_IE_HALL2_FALL_POS);     //��ʱ��HALL2�½����ж�ʹ��
	}
}

/****************************************************************************************************************************************** 
* ��������:	TIMPLUS_IntHallFallDis()
* ����˵��:	���ö�ʱ��HALL�½����жϽ���
* ��    ��: TIMPLUS_TypeDef * TIMPLUSx       ��Чֵ��TIMPLUS0
            TIMPLUS_HallTypeDef HallType    ����ѡ��  HALL0  HALL1  HALL2       	     
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMPLUS_IntHallFallDis(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_HallTypeDef HallType)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //�������Ĳ���TIMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_TIMPLUS_HALL_TYPE(HallType));     //�������Ĳ���HallType�Ƿ�Ϸ�  
	
	
	if((HallType & HALL_0) == HALL_0)
	{
		TIMPLUSx->IE &= ~(0x01 << TIMPLUS_IE_HALL0_FALL_POS);    //��ʱ��HALL0�½����жϽ���
	}
	
	if((HallType & HALL_1) == HALL_1)
	{
		TIMPLUSx->IE &= ~(0x01 << TIMPLUS_IE_HALL1_FALL_POS);    //��ʱ��HALL1�½����жϽ���
	}
	
	if((HallType & HALL_2) == HALL_2)
	{
		TIMPLUSx->IE &= ~(0x01 << TIMPLUS_IE_HALL2_FALL_POS);    //��ʱ��HALL2�½����жϽ���
	}
}

/****************************************************************************************************************************************** 
* ��������:	TIMPLUS_IntHallFallClr()
* ����˵��:	�����ʱ��HALL�½����ж�״̬
* ��    ��: TIMPLUS_TypeDef * TIMPLUSx       ��Чֵ��TIMPLUS0
            TIMPLUS_HallTypeDef HallType    ����ѡ��  HALL0  HALL1  HALL2         	     
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void TIMPLUS_IntHallFallClr(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_HallTypeDef HallType)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //�������Ĳ���TIMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_TIMPLUS_HALL_TYPE(HallType));     //�������Ĳ���HallType�Ƿ�Ϸ�  
	
	
	if((HallType & HALL_0) == HALL_0)
	{
		TIMPLUSx->IF = (0x01 << TIMPLUS_IF_HALL0_FALL_POS);    //�����ʱ��HALL0�½����ж�״̬
	}
	
	if((HallType & HALL_1) == HALL_1)
	{
		TIMPLUSx->IF = (0x01 << TIMPLUS_IF_HALL1_FALL_POS);    //�����ʱ��HALL1�½����ж�״̬
	}
	
	if((HallType & HALL_2) == HALL_2)
	{
		TIMPLUSx->IF = (0x01 << TIMPLUS_IF_HALL2_FALL_POS);    //�����ʱ��HALL2�½����ж�״̬
	}
}


/****************************************************************************************************************************************** 
* ��������:	TIMPLUS_IntHallFallState()
* ����˵��:	��ȡ��ʱ��HALL�½����ж�״̬
* ��    ��: TIMPLUS_TypeDef * TIMPLUSx       ��Чֵ��TIMPLUS0     	     
* ��    ��: 1 �½����ж��Ѿ�����    0 �½����ж�δ����
* ע������: ��
******************************************************************************************************************************************/
uint8_t TIMPLUS_IntHallFallState(TIMPLUS_TypeDef * TIMPLUSx,TIMPLUS_HallTypeDef HallType)
{
	assert_param(IS_TIMPLUS_ALL(TIMPLUSx));           //�������Ĳ���TIMPLUSx�Ƿ�Ϸ�   
	
	assert_param(IS_TIMPLUS_HALL_TYPE(HallType));     //�������Ĳ���HallType�Ƿ�Ϸ�  
	
	
	if(HallType == HALL_0)
	{
		if(TIMPLUSx->IF & TIMPLUS_IF_HALL0_FALL_MSK)
		{
			return 1;
		}
	}
	else if(HallType == HALL_1)
	{
		if(TIMPLUSx->IF & TIMPLUS_IF_HALL1_FALL_MSK)
		{
			return 1;
		}
	}
	else if(HallType == HALL_2)
	{
		if(TIMPLUSx->IF & TIMPLUS_IF_HALL2_FALL_MSK)
		{
			return 1;
		}
	}
	
	return 0;
}



