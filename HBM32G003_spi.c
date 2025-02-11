#include "HBM32G003_spi.h"

/****************************************************************************************************************************************** 
* 函数名称:	SPI_Init()
* 功能说明:	SPI初始化
* 输    入: SPI_TypeDef * SPIx    SPI0   
			SPI_InitTypeDef * SPI_InitStruct    
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void SPI_Init(SPI_TypeDef * SPIx,SPI_InitTypeDef * SPI_InitStruct)
{
	uint32_t temp = 0;
	
	assert_param(IS_SPI_MODE(SPI_InitStruct->Master));               //检查输入的参数Master是否合法     
	
	assert_param(IS_SPI_CLKDIV(SPI_InitStruct->ClkDiv));             //检查输入的参数ClkDiv是否合法 
	
	assert_param(IS_SPI_SAMPLE_EDGE(SPI_InitStruct->SampleEdge));    //检查输入的参数SampleEdge是否合法 
	
	assert_param(IS_SPI_IDLE_LEVEL(SPI_InitStruct->IdleLevel));      //检查输入的参数IdleLevel是否合法 
	
	assert_param(IS_SPI_LSBFIRST(SPI_InitStruct->LsbFirst));         //检查输入的参数LsbFirst是否合法 
	
	switch((uint32_t)SPIx)
	{
		case ((uint32_t)SPI0):
			
			SYS->CLKEN |= 0x01 << SYS_CLKEN_SPI0_POS;    //打开SPI0时钟
		
			break;
	}
	
	SPI_Close(SPIx);     //SPI关闭时设置寄存器
	
	temp = SPIx->CTRL;
	
	temp &= ~(SPI_CTRL_CLKDIV_MSK | SPI_CTRL_CPHA_MSK | SPI_CTRL_CPOL_MSK | SPI_CTRL_MSTR_MSK | SPI_CTRL_LSBF_MSK);
	
	temp |= (SPI_InitStruct->ClkDiv     << SPI_CTRL_CLKDIV_POS) |
	        (SPI_InitStruct->SampleEdge << SPI_CTRL_CPHA_POS)   |
	        (SPI_InitStruct->IdleLevel  << SPI_CTRL_CPOL_POS)   |
	        (SPI_InitStruct->Master     << SPI_CTRL_MSTR_POS)   |
	        (SPI_InitStruct->LsbFirst   << SPI_CTRL_LSBF_POS);
	
	SPIx->CTRL = temp;
}

/****************************************************************************************************************************************** 
* 函数名称:	SPI_Open()
* 功能说明:	SPI打开，允许收发
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void SPI_Open(SPI_TypeDef * SPIx)
{
	SPIx->CTRL |= (0x01 << SPI_CTRL_EN_POS);
}

/****************************************************************************************************************************************** 
* 函数名称:	SPI_Close()
* 功能说明:	SPI关闭，禁止收发
* 输    入: 无
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void SPI_Close(SPI_TypeDef * SPIx)
{
	SPIx->CTRL &= ~(0x01 << SPI_CTRL_EN_POS);
}


/****************************************************************************************************************************************** 
* 函数名称: SPI_Write()
* 功能说明: 发送一个数据
* 输    入: uint8_t data 			要发送的数据		
* 输    出: 无
* 注意事项: 
******************************************************************************************************************************************/
void SPI_Write(SPI_TypeDef * SPIx,uint8_t data)
{
	SPIx->WDATA = data;	
}

/****************************************************************************************************************************************** 
* 函数名称: SPI_Write_Wait()
* 功能说明: 发送一个数据，并等待它发送完成
* 输    入: uint8_t data 			要发送的数据		
* 输    出: 无
* 注意事项: 
******************************************************************************************************************************************/
void SPI_Write_Wait(SPI_TypeDef * SPIx,uint8_t data)
{
	SPIx->WDATA = data;
	while(!(SPIx->IF & SPI_SPIF_IF_MSK));
	SPIx->IF = 0x01 << SPI_SPIF_IF_POS;
}


/****************************************************************************************************************************************** 
* 函数名称: SPI_ReadWrite()
* 功能说明: 发送一个数据，并返回发送过程中接收到的
* 输    入: uint8_t data 			要发送的数据		
* 输    出: uint8_t				    接收到的数据
* 注意事项: 
******************************************************************************************************************************************/
uint8_t SPI_ReadWrite(SPI_TypeDef * SPIx,uint8_t data)
{
	uint8_t temp;
	
	SPIx->WDATA = data;
	while(!(SPIx->IF & SPI_SPIF_IF_MSK));
	
	temp = SPIx->RDATA;
	SPIx->IF = 0x01 << SPI_SPIF_IF_POS;
	
	return temp;
}

/****************************************************************************************************************************************** 
* 函数名称: SPI_ReadBytes()
* 功能说明: 接收数量为num的数据
* 输    入: uint8_t num 			要读取的数据个数	
* 输    出: uint8_t	*data			接收到的数据
* 注意事项: 
******************************************************************************************************************************************/
void SPI_ReadBytes(SPI_TypeDef * SPIx,uint8_t* data,uint8_t num)
{
	uint8_t i;
	
	SPI_Write_Wait(SPIx,0xFF);
	
	for(i = 0; i < num; i++)
	{
		SPIx->WDATA = 0xFF;
		while(!(SPIx->IF & SPI_SPIF_IF_MSK));
		data[i] = SPIx->RDATA;
		SPIx->IF = 0x01 << SPI_SPIF_IF_POS;
	}
}

/****************************************************************************************************************************************** 
* 函数名称: SPI_Master_SSN_Out()
* 功能说明: 主模式下，SSN输出高低电平控制从机的片选引脚
* 输    入: uint8_t out 			SSN要输出的电平    0 低电平   1 高电平		
* 输    出: 无
* 注意事项: 
******************************************************************************************************************************************/
void SPI_Master_SSN_Out(SPI_TypeDef * SPIx,uint8_t out)
{
	if(out == 0)
	{
		SPIx->CTRL &= ~(0x01 << SPI_CTRL_MST_SSN_POS);
	}
	else
	{
		SPIx->CTRL |= (0x01 << SPI_CTRL_MST_SSN_POS);
	}	
}



