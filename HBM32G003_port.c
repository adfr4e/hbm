#include "HBM32G003_port.h"


/****************************************************************************************************************************************** 
* 函数名称: PORT_Init()
* 功能说明:	端口引脚功能选择
* 输    入: PORT_InitTypeDef* PORT_InitStruct
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PORT_Init(PORT_InitTypeDef* PORT_InitStruct)
{
	uint32_t temp = 0;
	
	assert_param(IS_PORT_ALL(PORT_InitStruct->Port));                             //检查输入的参数Port是否合法   
	
	assert_param(IS_INPUT_EN(PORT_InitStruct->Input_En));                         //检查输入的参数Input_En是否合法   
	
	assert_param(IS_PORT_FUNC(PORT_InitStruct->Func));                            //检查输入的参数Func是否合法 
	
	switch(PORT_InitStruct->Port)
	{
		case PORTA:
			
			assert_param(IS_GPIOA_PIN(PORT_InitStruct->Pin));                     //检查输入的参数Pin是否合法    
		
			if(PORT_InitStruct->Pin <= GPIO_PIN7)
			{
				temp = PORT->PORTA_SEL0;
				
				temp &= ~(0x0F << ((PORT_InitStruct->Pin)*4)); 
				temp |= ((PORT_InitStruct->Func) << ((PORT_InitStruct->Pin)*4));
				
				PORT->PORTA_SEL0 = temp;                                          //PORTA0-7 IO端口功能配置
			}
			else if(PORT_InitStruct->Pin <= GPIO_PIN15)
			{
				temp = PORT->PORTA_SEL1;
				
				temp &= ~(0x0F << ((PORT_InitStruct->Pin - GPIO_PIN8)*4)); 
				temp |= ((PORT_InitStruct->Func) << ((PORT_InitStruct->Pin - GPIO_PIN8)*4));

				PORT->PORTA_SEL1 = temp;                                          //PORTA8-15 IO端口功能配置
			}
			
			
			if(PORT_InitStruct->Input_En == ENABLE)                                 
			{
				PORT->PORTA_INEN |=  (0x01 << (PORT_InitStruct->Pin));            //输入使能打开
			}
			else
			{
				PORT->PORTA_INEN &= ~(0x01 << (PORT_InitStruct->Pin));            //输入使能关闭
			}
			
		break;

		default:
			
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称: PORT_CFG_Init()
* 功能说明:	端口配置
* 输    入: PORT_CFGTypeDef* PORT_CFGStruct
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void PORT_CFG_Init(PORT_CFGTypeDef* PORT_CFGStruct)
{
	uint32_t temp = 0;
	
	assert_param(IS_OUT_CURRENT(PORT_CFGStruct->Out_Cur));                       //检查输入的参数Out_Cur是否合法     
	
	assert_param(IS_PULLUP_RES(PORT_CFGStruct->PullUp_Res));                     //检查输入的参数PullUp_Res是否合法   
	
	assert_param(IS_INPUT_HYS(PORT_CFGStruct->InputHys));                        //检查输入的参数InputHys是否合法   
	
	assert_param(IS_WAKEUP_EDGE(PORT_CFGStruct->WakeUp_Edge));                   //检查输入的参数WakeUp_Edge是否合法   
	
	temp = PORT->PORT_CFG;
	
	temp &= ~(0x03 << PORT_CFG_DS_POS);
	temp |=  ((PORT_CFGStruct->Out_Cur) << PORT_CFG_DS_POS);                     //配置PORTA的驱动能力
	
	temp &= ~(0x03 << PORT_CFG_PUR_POS);
	temp |=  ((PORT_CFGStruct->PullUp_Res) << PORT_CFG_PUR_POS);                 //配置端口PORTA的上拉电阻
	
	temp &= ~(0x01 << PORT_CFG_HYS_POS);
	temp |=  ((PORT_CFGStruct->InputHys) << PORT_CFG_HYS_POS);                   //配置PORTA的输入迟滞等级
	
	temp &= ~(0x01 << PORT_CFG_WKRF_POS);
	temp |=  ((PORT_CFGStruct->WakeUp_Edge) << PORT_CFG_WKRF_POS);	             //配置PORTA的唤醒功能沿
	
	PORT->PORT_CFG = temp;	
}



