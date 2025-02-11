#include "HBM32G003_uart.h"

/****************************************************************************************************************************************** 
* 函数名称: UART_Init()
* 功能说明:	串口初始化，包含串口号  波特率  数据长度   校验位   停止位   中断使能
* 输    入: UART_TypeDef * UARTx     UART0  
*			UART_InitTypeDef * UART_InitStruct
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void UART_Init(UART_TypeDef * UARTx, UART_InitTypeDef * UART_InitStruct)	
{
	uint32_t temp = 0,Baudrate_Set = 0;
	
	assert_param(IS_UART_ALL(UARTx));                                 //检查输入的参数UARTx是否合法      
	
	assert_param(IS_UART_BAUDRATE(UART_InitStruct->Baudrate));        //检查输入的参数Baudrate是否合法  
	
	assert_param(IS_UART_DATABITS(UART_InitStruct->DataBits));        //检查输入的参数DataBits是否合法    
	
	assert_param(IS_UART_PARITY(UART_InitStruct->Parity));            //检查输入的参数Parity是否合法  
	
	assert_param(IS_UART_STOP(UART_InitStruct->StopBits));            //检查输入的参数StopBits是否合法  
	
	assert_param(IS_UART_RXIE(UART_InitStruct->RXIEn));               //检查输入的参数RXIEn是否合法  
	
	
	switch((uint32_t)UARTx)
	{
		case ((uint32_t)UART0):
			
			SYS->CLKEN |= 0x01 << SYS_CLKEN_UART0_POS;        //打开串口0的时钟
		
		break;
	}
	
	UARTx->CTRL |= (0x01 << UART_CTRL_BAUDEN_POS);            //开启波特率设置位              
	
	if(((SystemCoreClock/16)%UART_InitStruct->Baudrate)*1.0/UART_InitStruct->Baudrate > 0.5)
	{
		Baudrate_Set = (SystemCoreClock/16/UART_InitStruct->Baudrate) + 1;
	}
	else
	{
		Baudrate_Set = (SystemCoreClock/16/UART_InitStruct->Baudrate);
	}
	
	UARTx->DHL = Baudrate_Set>>8;                             //配置波特率
	UARTx->DLL = Baudrate_Set&0xFF;
	
	UARTx->CTRL &= ~(0x01 << UART_CTRL_BAUDEN_POS);           //关闭波特率设置位
	
	temp = UARTx->CTRL;
	
	temp &= ~(UART_CTRL_DATALEN_MSK | UART_CTRL_STOP2BIT_MSK | UART_CTRL_PARITY_MSK);
	
	temp |= (UART_InitStruct->DataBits << UART_CTRL_DATALEN_POS) |            //配置数据长度
				   (UART_InitStruct->StopBits << UART_CTRL_STOP2BIT_POS)|     //配置停止位
				   (UART_InitStruct->Parity   << UART_CTRL_PARITY_POS);       //配置校验位
	
	UARTx->CTRL = temp;
	
	if(UART_InitStruct->RXIEn == ENABLE)
	{
		UARTx->IE |= 0x01 << UART_IE_RXIEN_POS;                 //配置接收数据有效中断
	}
	else
	{
		UARTx->IE &= ~(0x01 << UART_IE_RXIEN_POS);
	}
	
	switch((uint32_t)UARTx)         
	{
		case ((uint32_t)UART0):		
			
			if(UART_InitStruct->RXIEn)
			{
				NVIC_EnableIRQ(UART0_IRQn);         //使能串口0中断   
			}
			else
			{
				NVIC_DisableIRQ(UART0_IRQn);        //禁能串口0中断  
			}
			
		break;
	}
}

/****************************************************************************************************************************************** 
* 函数名称: UART_SendData()
* 功能说明:	串口发送函数   
* 输    入: UART_TypeDef * UARTx     UART0    
*			uint8_t data    待发送的数据
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void UART_SendData(UART_TypeDef * UARTx, uint8_t data)
{
	assert_param(IS_UART_ALL(UARTx));               //检查输入的参数UARTx是否合法      
	
	UARTx->SDR = data;                              //发送数据
	while((UARTx->LSR & UART_LSR_THRE_MSK) == 0);   //等待发送完成
}

/****************************************************************************************************************************************** 
* 函数名称: UART_ReceiveData()
* 功能说明:	串口接收函数  
* 输    入: UART_TypeDef * UARTx     UART0 	   
*			uint8_t *data    接收到的数据
* 输    出: 错误状态   无错误返回0 
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t UART_ReceiveData(UART_TypeDef * UARTx, uint8_t *data)
{
	uint8_t temp;
	
	assert_param(IS_UART_ALL(UARTx));                               //检查输入的参数UARTx是否合法     
	
	temp = UARTx->LSR;
	
	if((temp & UART_LSR_REC_MSK) == 0)  return UART_ERR_REC;        //没有接收到数据
	if(temp & UART_LSR_OVF_MSK)         return UART_ERR_OVF;        //溢出错误
	if(temp & UART_LSR_PARITY_MSK)      return UART_ERR_PARITY;     //校验错误
	if(temp & UART_LSR_STOP_MSK)        return UART_ERR_STOP;       //停止位错误
	if(temp & UART_LSR_BREAK_MSK)       return UART_ERR_BREAK;      //BREAK错误
	
	*data = UARTx->RDR;               //无错误，取出接收的数据
	
	return 0;	                      //无错误返回0
}

/****************************************************************************************************************************************** 
* 函数名称: UART_IsTXEmpty()
* 功能说明:	串口发送寄存器是否为空
* 输    入: UART_TypeDef * UARTx     UART0  
*			
* 输    出: 1 发送寄存器为空，可以继续发送数据   0  发送寄存器不为空 表示正在发送数据还没有发送完成
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t UART_IsTXEmpty(UART_TypeDef * UARTx)
{
	assert_param(IS_UART_ALL(UARTx));               //检查输入的参数UARTx是否合法     
	
	if(UARTx->LSR & UART_LSR_THRE_MSK) 
	{
		return 1;
	}
	else
	{
	    return 0;
	}
}

/****************************************************************************************************************************************** 
* 函数名称: UART_IsRXValid()
* 功能说明:	串口接收寄存器是否有数据
* 输    入: UART_TypeDef * UARTx     UART0    
*			
* 输    出: 1 接收寄存器有数据可以读取   0  接收寄存器为空
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t UART_IsRXValid(UART_TypeDef * UARTx)
{
	assert_param(IS_UART_ALL(UARTx));               //检查输入的参数UARTx是否合法     
	
	if(UARTx->LSR & UART_LSR_REC_MSK) 
	{
		return 1;
	}
	else
	{
	    return 0;
	}
}


/****************************************************************************************************************************************** 
* 函数名称: UART_TX_INTEn()
* 功能说明:	串口发送中断使能 
* 输    入: UART_TypeDef * UARTx     UART0    
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void UART_TX_INTEn(UART_TypeDef * UARTx)
{
	assert_param(IS_UART_ALL(UARTx));               //检查输入的参数UARTx是否合法     
	
	switch((uint32_t)UARTx)         
	{
		case ((uint32_t)UART0):
		
			UART0->IE |= 0x01 << UART_IE_TXE_POS;
		
			NVIC_EnableIRQ(UART0_IRQn);
		
		break;
	}	
}

/****************************************************************************************************************************************** 
* 函数名称: UART_TX_INTDis()
* 功能说明:	串口发送中断禁能
* 输    入: UART_TypeDef * UARTx     UART0	   
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void UART_TX_INTDis(UART_TypeDef * UARTx)
{
	assert_param(IS_UART_ALL(UARTx));               //检查输入的参数UARTx是否合法     
	
	switch((uint32_t)UARTx)         
	{
		case ((uint32_t)UART0):
		
			UART0->IE &= ~(0x01 << UART_IE_TXE_POS);
			
		break;
	}	
}


/****************************************************************************************************************************************** 
* 函数名称: UART_RX_INTEn()
* 功能说明:	串口接收中断使能 
* 输    入: UART_TypeDef * UARTx     UART0  
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void UART_RX_INTEn(UART_TypeDef * UARTx)
{
	assert_param(IS_UART_ALL(UARTx));               //检查输入的参数UARTx是否合法     
	
	switch((uint32_t)UARTx)         
	{
		case ((uint32_t)UART0):
		
			UART0->IE |= 0x01 << UART_IE_RXIEN_POS;
			
			NVIC_EnableIRQ(UART0_IRQn);
		
		break;
	}	
}

/****************************************************************************************************************************************** 
* 函数名称: UART_RX_INTDis()
* 功能说明:	串口接收中断禁能
* 输    入: UART_TypeDef * UARTx     UART0    
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void UART_RX_INTDis(UART_TypeDef * UARTx)
{
	assert_param(IS_UART_ALL(UARTx));               //检查输入的参数UARTx是否合法     
	
	switch((uint32_t)UARTx)         
	{
		case ((uint32_t)UART0):
		
			UART0->IE &= ~(0x01 << UART_IE_RXIEN_POS);
			
		break;
	}	
}


