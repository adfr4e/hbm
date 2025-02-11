#include "HBM32G003_gpio.h"

/****************************************************************************************************************************************** 
* ��������: GPIO_Init()
* ����˵��:	���ų�ʼ�����������ŷ�����������������©  ������� ���ѹ���
* ��    ��: GPIO_TypeDef * GPIOx	   
*			
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void GPIO_Init(GPIO_TypeDef * GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
	assert_param(IS_GPIO_ALL(GPIOx));                                             //�������Ĳ���GPIOx�Ƿ�Ϸ�                      
	
	assert_param(IS_GPIO_MODE(GPIO_InitStruct->Mode));                            //�������Ĳ���Mode�Ƿ�Ϸ�     
	
	assert_param(IS_GPIO_WAKEUP(GPIO_InitStruct->WakeUp_En));                     //�������Ĳ���WakeUp_En�Ƿ�Ϸ�               
	
	switch((uint32_t)GPIOx)
	{
		case ((uint32_t)GPIOA):
		    
			assert_param(IS_GPIOA_PIN(GPIO_InitStruct->Pin));                     //�������Ĳ���Pin�Ƿ�Ϸ�    
		
			SYS->CLKEN |= 0x01 << SYS_CLKEN_GPIOA_POS;                            //����GPIOA��ʱ��
		
			if(GPIO_InitStruct->Pin <= GPIO_PIN7)
			{
				PORT->PORTA_SEL0 &= ~(0x0F << ((GPIO_InitStruct->Pin)*4)); 
			}
			else if(GPIO_InitStruct->Pin <= GPIO_PIN15)
			{
				PORT->PORTA_SEL1 &= ~(0x0F << ((GPIO_InitStruct->Pin - GPIO_PIN8)*4)); 
			}
			
			if(GPIO_InitStruct->Mode == MODE_FLOATING_IN)                         //��������
			{
				PORT->PORTA_INEN |=  (0x01 << (GPIO_InitStruct->Pin));            //��������ʹ��
				
				PORT->PORTA_PU_IN  &= ~(0x01 << GPIO_InitStruct->Pin);
				PORT->PORTA_PD_IN  &= ~(0x01 << GPIO_InitStruct->Pin);
				PORT->PORTA_OD_OUT &= ~(0x01 << GPIO_InitStruct->Pin);
				
				GPIOA->DIR &= ~(1 << GPIO_InitStruct->Pin);                       //��������Ϊ����
			}				
			else if(GPIO_InitStruct->Mode == MODE_PU_IN)	                      //��������          
			{
				PORT->PORTA_INEN |=  (0x01 << (GPIO_InitStruct->Pin));            //��������ʹ��
				
				PORT->PORTA_PU_IN  |=  (0x01 << GPIO_InitStruct->Pin);
				PORT->PORTA_PD_IN  &= ~(0x01 << GPIO_InitStruct->Pin);
				PORT->PORTA_OD_OUT &= ~(0x01 << GPIO_InitStruct->Pin);
				
				GPIOA->DIR &= ~(1 << GPIO_InitStruct->Pin);                       //��������Ϊ����
			}
			else if(GPIO_InitStruct->Mode == MODE_PD_IN)	                      //��������   
			{
				PORT->PORTA_INEN |=  (0x01 << (GPIO_InitStruct->Pin));            //��������ʹ��
				
				PORT->PORTA_PU_IN  &= ~(0x01 << GPIO_InitStruct->Pin);
				PORT->PORTA_PD_IN  |=  (0x01 << GPIO_InitStruct->Pin);
				PORT->PORTA_OD_OUT &= ~(0x01 << GPIO_InitStruct->Pin);
				
				GPIOA->DIR &= ~(1 << GPIO_InitStruct->Pin);	                      //��������Ϊ����
			}
			else if(GPIO_InitStruct->Mode == MODE_PP_OUT)                         //�������
			{
				PORT->PORTA_INEN &= ~(0x01 << (GPIO_InitStruct->Pin));            //�ر�����ʹ��
				
				PORT->PORTA_PU_IN  &= ~(0x01 << GPIO_InitStruct->Pin);
				PORT->PORTA_PD_IN  &= ~(0x01 << GPIO_InitStruct->Pin);
				PORT->PORTA_OD_OUT &= ~(0x01 << GPIO_InitStruct->Pin);
				
				GPIOA->DIR |= (1 << GPIO_InitStruct->Pin);		                  //��������Ϊ���
			}	
			else if(GPIO_InitStruct->Mode == MODE_OD_OUT)                         //��©���       
			{
				PORT->PORTA_INEN &= ~(0x01 << (GPIO_InitStruct->Pin));            //�ر�����ʹ��
				
				PORT->PORTA_PU_IN  &= ~(0x01 << GPIO_InitStruct->Pin);
				PORT->PORTA_PD_IN  &= ~(0x01 << GPIO_InitStruct->Pin);
				PORT->PORTA_OD_OUT |=  (0x01 << GPIO_InitStruct->Pin);
				
				GPIOA->DIR |= (1 << GPIO_InitStruct->Pin);                        //��������Ϊ���
			}	 
			
			if(GPIO_InitStruct->WakeUp_En == WAKEUP_ENABLE)                       //���ѹ���ʹ��
			{
				PORT->PORTA_WAKEUP |=  (0x01 << GPIO_InitStruct->Pin);
			}
			else
			{
				PORT->PORTA_WAKEUP &= ~(0x01 << GPIO_InitStruct->Pin);
			}
	
		break;
		
		default:
			
		break;
	}		
}

/****************************************************************************************************************************************** 
* ��������: GPIO_Assert_Param()
* ����˵��:	�������Ĳ����Ƿ�Ϸ�    
* ��    ��: GPIO_TypeDef * GPIOx	    ָ��GPIO�˿ڣ���Чֵ����GPIOA
*			uint32_t GPIO_Pin		    ָ��GPIO���ţ���Чֵ����PIN0��PIN1��PIN2��... ... PIN14��PIN15
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void GPIO_Assert_Param(GPIO_TypeDef * GPIOx, uint32_t GPIO_Pin)
{
	assert_param(IS_GPIO_ALL(GPIOx));                                 //�������Ĳ���GPIOx�Ƿ�Ϸ�    
	
	if((uint32_t)GPIOx == (uint32_t)GPIOA)
	{
		assert_param(IS_GPIOA_PIN(GPIO_Pin));                         //�������Ĳ���Pin�Ƿ�Ϸ�    
	}
}

/****************************************************************************************************************************************** 
* ��������: GPIO_SetBit()
* ����˵��:	������ָ�������ŵ�ƽ�ø�
* ��    ��: GPIO_TypeDef * GPIOx	    ָ��GPIO�˿ڣ���Чֵ����GPIOA
*			uint32_t GPIO_Pin		    ָ��GPIO���ţ���Чֵ����PIN0��PIN1��PIN2��... ... PIN14��PIN15
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void GPIO_SetBit(GPIO_TypeDef * GPIOx, uint32_t GPIO_Pin)
{
	GPIO_Assert_Param(GPIOx,GPIO_Pin);     //�������Ĳ����Ƿ�Ϸ�   

	GPIOx->DATA |= (0x01 << GPIO_Pin);
}

/****************************************************************************************************************************************** 
* ��������:	GPIO_ClrBit()
* ����˵��:	������ָ�������ŵ�ƽ�õ�
* ��    ��: GPIO_TypeDef * GPIOx	    ָ��GPIO�˿ڣ���Чֵ����GPIOA
*			uint32_t GPIO_Pin		    ָ��GPIO���ţ���Чֵ����PIN0��PIN1��PIN2��... ... PIN14��PIN15
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void GPIO_ClrBit(GPIO_TypeDef * GPIOx, uint32_t GPIO_Pin)
{
	GPIO_Assert_Param(GPIOx,GPIO_Pin);     //�������Ĳ����Ƿ�Ϸ�   
	
	GPIOx->DATA &= ~(0x01 << GPIO_Pin);
}

/****************************************************************************************************************************************** 
* ��������: GPIO_InvBit()
* ����˵��:	������ָ�������ŵ�ƽ��ת
* ��    ��: GPIO_TypeDef * GPIOx	    ָ��GPIO�˿ڣ���Чֵ����GPIOA
*			uint32_t n		            ָ��GPIO���ţ���Чֵ����PIN0��PIN1��PIN2��... ... PIN14��PIN15
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void GPIO_InvBit(GPIO_TypeDef * GPIOx, uint32_t GPIO_Pin)
{
	GPIO_Assert_Param(GPIOx,GPIO_Pin);     //�������Ĳ����Ƿ�Ϸ�   
	
	GPIOx->DATA ^= (0x01 << GPIO_Pin);
}

/****************************************************************************************************************************************** 
* ��������:	GPIO_GetBit()
* ����˵��:	��ȡ����ָ�������ŵĵ�ƽ״̬
* ��    ��: GPIO_TypeDef * GPIOx	    ָ��GPIO�˿ڣ���Чֵ����GPIOA
*			uint32_t n		            ָ��GPIO���ţ���Чֵ����PIN0��PIN1��PIN2��... ... PIN14��PIN15
* ��    ��: ����ָ�������ŵĵ�ƽ״̬	0 �͵�ƽ	1 �ߵ�ƽ
* ע������: ��
******************************************************************************************************************************************/
uint32_t GPIO_GetBit(GPIO_TypeDef * GPIOx, uint32_t GPIO_Pin)
{	
	GPIO_Assert_Param(GPIOx,GPIO_Pin);     //�������Ĳ����Ƿ�Ϸ�   
	
	return ((GPIOx->DATA >> GPIO_Pin) & 0x01);
}



