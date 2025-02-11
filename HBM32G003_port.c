#include "HBM32G003_port.h"


/****************************************************************************************************************************************** 
* ��������: PORT_Init()
* ����˵��:	�˿����Ź���ѡ��
* ��    ��: PORT_InitTypeDef* PORT_InitStruct
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PORT_Init(PORT_InitTypeDef* PORT_InitStruct)
{
	uint32_t temp = 0;
	
	assert_param(IS_PORT_ALL(PORT_InitStruct->Port));                             //�������Ĳ���Port�Ƿ�Ϸ�   
	
	assert_param(IS_INPUT_EN(PORT_InitStruct->Input_En));                         //�������Ĳ���Input_En�Ƿ�Ϸ�   
	
	assert_param(IS_PORT_FUNC(PORT_InitStruct->Func));                            //�������Ĳ���Func�Ƿ�Ϸ� 
	
	switch(PORT_InitStruct->Port)
	{
		case PORTA:
			
			assert_param(IS_GPIOA_PIN(PORT_InitStruct->Pin));                     //�������Ĳ���Pin�Ƿ�Ϸ�    
		
			if(PORT_InitStruct->Pin <= GPIO_PIN7)
			{
				temp = PORT->PORTA_SEL0;
				
				temp &= ~(0x0F << ((PORT_InitStruct->Pin)*4)); 
				temp |= ((PORT_InitStruct->Func) << ((PORT_InitStruct->Pin)*4));
				
				PORT->PORTA_SEL0 = temp;                                          //PORTA0-7 IO�˿ڹ�������
			}
			else if(PORT_InitStruct->Pin <= GPIO_PIN15)
			{
				temp = PORT->PORTA_SEL1;
				
				temp &= ~(0x0F << ((PORT_InitStruct->Pin - GPIO_PIN8)*4)); 
				temp |= ((PORT_InitStruct->Func) << ((PORT_InitStruct->Pin - GPIO_PIN8)*4));

				PORT->PORTA_SEL1 = temp;                                          //PORTA8-15 IO�˿ڹ�������
			}
			
			
			if(PORT_InitStruct->Input_En == ENABLE)                                 
			{
				PORT->PORTA_INEN |=  (0x01 << (PORT_InitStruct->Pin));            //����ʹ�ܴ�
			}
			else
			{
				PORT->PORTA_INEN &= ~(0x01 << (PORT_InitStruct->Pin));            //����ʹ�ܹر�
			}
			
		break;

		default:
			
		break;
	}
}

/****************************************************************************************************************************************** 
* ��������: PORT_CFG_Init()
* ����˵��:	�˿�����
* ��    ��: PORT_CFGTypeDef* PORT_CFGStruct
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void PORT_CFG_Init(PORT_CFGTypeDef* PORT_CFGStruct)
{
	uint32_t temp = 0;
	
	assert_param(IS_OUT_CURRENT(PORT_CFGStruct->Out_Cur));                       //�������Ĳ���Out_Cur�Ƿ�Ϸ�     
	
	assert_param(IS_PULLUP_RES(PORT_CFGStruct->PullUp_Res));                     //�������Ĳ���PullUp_Res�Ƿ�Ϸ�   
	
	assert_param(IS_INPUT_HYS(PORT_CFGStruct->InputHys));                        //�������Ĳ���InputHys�Ƿ�Ϸ�   
	
	assert_param(IS_WAKEUP_EDGE(PORT_CFGStruct->WakeUp_Edge));                   //�������Ĳ���WakeUp_Edge�Ƿ�Ϸ�   
	
	temp = PORT->PORT_CFG;
	
	temp &= ~(0x03 << PORT_CFG_DS_POS);
	temp |=  ((PORT_CFGStruct->Out_Cur) << PORT_CFG_DS_POS);                     //����PORTA����������
	
	temp &= ~(0x03 << PORT_CFG_PUR_POS);
	temp |=  ((PORT_CFGStruct->PullUp_Res) << PORT_CFG_PUR_POS);                 //���ö˿�PORTA����������
	
	temp &= ~(0x01 << PORT_CFG_HYS_POS);
	temp |=  ((PORT_CFGStruct->InputHys) << PORT_CFG_HYS_POS);                   //����PORTA��������͵ȼ�
	
	temp &= ~(0x01 << PORT_CFG_WKRF_POS);
	temp |=  ((PORT_CFGStruct->WakeUp_Edge) << PORT_CFG_WKRF_POS);	             //����PORTA�Ļ��ѹ�����
	
	PORT->PORT_CFG = temp;	
}



