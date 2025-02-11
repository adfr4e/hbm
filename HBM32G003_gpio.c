#include "HBM32G003_gpio.h"

/****************************************************************************************************************************************** 
* 函数名称: GPIO_Init()
* 功能说明:	引脚初始化，包含引脚方向、上拉、下拉、开漏  推挽输出 唤醒功能
* 输    入: GPIO_TypeDef * GPIOx	   
*			
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void GPIO_Init(GPIO_TypeDef * GPIOx, GPIO_InitTypeDef* GPIO_InitStruct)
{
	assert_param(IS_GPIO_ALL(GPIOx));                                             //检查输入的参数GPIOx是否合法                      
	
	assert_param(IS_GPIO_MODE(GPIO_InitStruct->Mode));                            //检查输入的参数Mode是否合法     
	
	assert_param(IS_GPIO_WAKEUP(GPIO_InitStruct->WakeUp_En));                     //检查输入的参数WakeUp_En是否合法               
	
	switch((uint32_t)GPIOx)
	{
		case ((uint32_t)GPIOA):
		    
			assert_param(IS_GPIOA_PIN(GPIO_InitStruct->Pin));                     //检查输入的参数Pin是否合法    
		
			SYS->CLKEN |= 0x01 << SYS_CLKEN_GPIOA_POS;                            //开启GPIOA的时钟
		
			if(GPIO_InitStruct->Pin <= GPIO_PIN7)
			{
				PORT->PORTA_SEL0 &= ~(0x0F << ((GPIO_InitStruct->Pin)*4)); 
			}
			else if(GPIO_InitStruct->Pin <= GPIO_PIN15)
			{
				PORT->PORTA_SEL1 &= ~(0x0F << ((GPIO_InitStruct->Pin - GPIO_PIN8)*4)); 
			}
			
			if(GPIO_InitStruct->Mode == MODE_FLOATING_IN)                         //浮空输入
			{
				PORT->PORTA_INEN |=  (0x01 << (GPIO_InitStruct->Pin));            //开启输入使能
				
				PORT->PORTA_PU_IN  &= ~(0x01 << GPIO_InitStruct->Pin);
				PORT->PORTA_PD_IN  &= ~(0x01 << GPIO_InitStruct->Pin);
				PORT->PORTA_OD_OUT &= ~(0x01 << GPIO_InitStruct->Pin);
				
				GPIOA->DIR &= ~(1 << GPIO_InitStruct->Pin);                       //方向设置为输入
			}				
			else if(GPIO_InitStruct->Mode == MODE_PU_IN)	                      //上拉输入          
			{
				PORT->PORTA_INEN |=  (0x01 << (GPIO_InitStruct->Pin));            //开启输入使能
				
				PORT->PORTA_PU_IN  |=  (0x01 << GPIO_InitStruct->Pin);
				PORT->PORTA_PD_IN  &= ~(0x01 << GPIO_InitStruct->Pin);
				PORT->PORTA_OD_OUT &= ~(0x01 << GPIO_InitStruct->Pin);
				
				GPIOA->DIR &= ~(1 << GPIO_InitStruct->Pin);                       //方向设置为输入
			}
			else if(GPIO_InitStruct->Mode == MODE_PD_IN)	                      //下拉输入   
			{
				PORT->PORTA_INEN |=  (0x01 << (GPIO_InitStruct->Pin));            //开启输入使能
				
				PORT->PORTA_PU_IN  &= ~(0x01 << GPIO_InitStruct->Pin);
				PORT->PORTA_PD_IN  |=  (0x01 << GPIO_InitStruct->Pin);
				PORT->PORTA_OD_OUT &= ~(0x01 << GPIO_InitStruct->Pin);
				
				GPIOA->DIR &= ~(1 << GPIO_InitStruct->Pin);	                      //方向设置为输入
			}
			else if(GPIO_InitStruct->Mode == MODE_PP_OUT)                         //推挽输出
			{
				PORT->PORTA_INEN &= ~(0x01 << (GPIO_InitStruct->Pin));            //关闭输入使能
				
				PORT->PORTA_PU_IN  &= ~(0x01 << GPIO_InitStruct->Pin);
				PORT->PORTA_PD_IN  &= ~(0x01 << GPIO_InitStruct->Pin);
				PORT->PORTA_OD_OUT &= ~(0x01 << GPIO_InitStruct->Pin);
				
				GPIOA->DIR |= (1 << GPIO_InitStruct->Pin);		                  //方向设置为输出
			}	
			else if(GPIO_InitStruct->Mode == MODE_OD_OUT)                         //开漏输出       
			{
				PORT->PORTA_INEN &= ~(0x01 << (GPIO_InitStruct->Pin));            //关闭输入使能
				
				PORT->PORTA_PU_IN  &= ~(0x01 << GPIO_InitStruct->Pin);
				PORT->PORTA_PD_IN  &= ~(0x01 << GPIO_InitStruct->Pin);
				PORT->PORTA_OD_OUT |=  (0x01 << GPIO_InitStruct->Pin);
				
				GPIOA->DIR |= (1 << GPIO_InitStruct->Pin);                        //方向设置为输出
			}	 
			
			if(GPIO_InitStruct->WakeUp_En == WAKEUP_ENABLE)                       //唤醒功能使能
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
* 函数名称: GPIO_Assert_Param()
* 功能说明:	检查输入的参数是否合法    
* 输    入: GPIO_TypeDef * GPIOx	    指定GPIO端口，有效值包括GPIOA
*			uint32_t GPIO_Pin		    指定GPIO引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN14、PIN15
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void GPIO_Assert_Param(GPIO_TypeDef * GPIOx, uint32_t GPIO_Pin)
{
	assert_param(IS_GPIO_ALL(GPIOx));                                 //检查输入的参数GPIOx是否合法    
	
	if((uint32_t)GPIOx == (uint32_t)GPIOA)
	{
		assert_param(IS_GPIOA_PIN(GPIO_Pin));                         //检查输入的参数Pin是否合法    
	}
}

/****************************************************************************************************************************************** 
* 函数名称: GPIO_SetBit()
* 功能说明:	将参数指定的引脚电平置高
* 输    入: GPIO_TypeDef * GPIOx	    指定GPIO端口，有效值包括GPIOA
*			uint32_t GPIO_Pin		    指定GPIO引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN14、PIN15
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void GPIO_SetBit(GPIO_TypeDef * GPIOx, uint32_t GPIO_Pin)
{
	GPIO_Assert_Param(GPIOx,GPIO_Pin);     //检查输入的参数是否合法   

	GPIOx->DATA |= (0x01 << GPIO_Pin);
}

/****************************************************************************************************************************************** 
* 函数名称:	GPIO_ClrBit()
* 功能说明:	将参数指定的引脚电平置低
* 输    入: GPIO_TypeDef * GPIOx	    指定GPIO端口，有效值包括GPIOA
*			uint32_t GPIO_Pin		    指定GPIO引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN14、PIN15
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void GPIO_ClrBit(GPIO_TypeDef * GPIOx, uint32_t GPIO_Pin)
{
	GPIO_Assert_Param(GPIOx,GPIO_Pin);     //检查输入的参数是否合法   
	
	GPIOx->DATA &= ~(0x01 << GPIO_Pin);
}

/****************************************************************************************************************************************** 
* 函数名称: GPIO_InvBit()
* 功能说明:	将参数指定的引脚电平反转
* 输    入: GPIO_TypeDef * GPIOx	    指定GPIO端口，有效值包括GPIOA
*			uint32_t n		            指定GPIO引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN14、PIN15
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void GPIO_InvBit(GPIO_TypeDef * GPIOx, uint32_t GPIO_Pin)
{
	GPIO_Assert_Param(GPIOx,GPIO_Pin);     //检查输入的参数是否合法   
	
	GPIOx->DATA ^= (0x01 << GPIO_Pin);
}

/****************************************************************************************************************************************** 
* 函数名称:	GPIO_GetBit()
* 功能说明:	读取参数指定的引脚的电平状态
* 输    入: GPIO_TypeDef * GPIOx	    指定GPIO端口，有效值包括GPIOA
*			uint32_t n		            指定GPIO引脚，有效值包括PIN0、PIN1、PIN2、... ... PIN14、PIN15
* 输    出: 参数指定的引脚的电平状态	0 低电平	1 高电平
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t GPIO_GetBit(GPIO_TypeDef * GPIOx, uint32_t GPIO_Pin)
{	
	GPIO_Assert_Param(GPIOx,GPIO_Pin);     //检查输入的参数是否合法   
	
	return ((GPIOx->DATA >> GPIO_Pin) & 0x01);
}



