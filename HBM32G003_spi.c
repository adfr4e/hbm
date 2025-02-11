#include "HBM32G003_spi.h"

/****************************************************************************************************************************************** 
* ��������:	SPI_Init()
* ����˵��:	SPI��ʼ��
* ��    ��: SPI_TypeDef * SPIx    SPI0   
			SPI_InitTypeDef * SPI_InitStruct    
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void SPI_Init(SPI_TypeDef * SPIx,SPI_InitTypeDef * SPI_InitStruct)
{
	uint32_t temp = 0;
	
	assert_param(IS_SPI_MODE(SPI_InitStruct->Master));               //�������Ĳ���Master�Ƿ�Ϸ�     
	
	assert_param(IS_SPI_CLKDIV(SPI_InitStruct->ClkDiv));             //�������Ĳ���ClkDiv�Ƿ�Ϸ� 
	
	assert_param(IS_SPI_SAMPLE_EDGE(SPI_InitStruct->SampleEdge));    //�������Ĳ���SampleEdge�Ƿ�Ϸ� 
	
	assert_param(IS_SPI_IDLE_LEVEL(SPI_InitStruct->IdleLevel));      //�������Ĳ���IdleLevel�Ƿ�Ϸ� 
	
	assert_param(IS_SPI_LSBFIRST(SPI_InitStruct->LsbFirst));         //�������Ĳ���LsbFirst�Ƿ�Ϸ� 
	
	switch((uint32_t)SPIx)
	{
		case ((uint32_t)SPI0):
			
			SYS->CLKEN |= 0x01 << SYS_CLKEN_SPI0_POS;    //��SPI0ʱ��
		
			break;
	}
	
	SPI_Close(SPIx);     //SPI�ر�ʱ���üĴ���
	
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
* ��������:	SPI_Open()
* ����˵��:	SPI�򿪣������շ�
* ��    ��: ��
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void SPI_Open(SPI_TypeDef * SPIx)
{
	SPIx->CTRL |= (0x01 << SPI_CTRL_EN_POS);
}

/****************************************************************************************************************************************** 
* ��������:	SPI_Close()
* ����˵��:	SPI�رգ���ֹ�շ�
* ��    ��: ��
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void SPI_Close(SPI_TypeDef * SPIx)
{
	SPIx->CTRL &= ~(0x01 << SPI_CTRL_EN_POS);
}


/****************************************************************************************************************************************** 
* ��������: SPI_Write()
* ����˵��: ����һ������
* ��    ��: uint8_t data 			Ҫ���͵�����		
* ��    ��: ��
* ע������: 
******************************************************************************************************************************************/
void SPI_Write(SPI_TypeDef * SPIx,uint8_t data)
{
	SPIx->WDATA = data;	
}

/****************************************************************************************************************************************** 
* ��������: SPI_Write_Wait()
* ����˵��: ����һ�����ݣ����ȴ����������
* ��    ��: uint8_t data 			Ҫ���͵�����		
* ��    ��: ��
* ע������: 
******************************************************************************************************************************************/
void SPI_Write_Wait(SPI_TypeDef * SPIx,uint8_t data)
{
	SPIx->WDATA = data;
	while(!(SPIx->IF & SPI_SPIF_IF_MSK));
	SPIx->IF = 0x01 << SPI_SPIF_IF_POS;
}


/****************************************************************************************************************************************** 
* ��������: SPI_ReadWrite()
* ����˵��: ����һ�����ݣ������ط��͹����н��յ���
* ��    ��: uint8_t data 			Ҫ���͵�����		
* ��    ��: uint8_t				    ���յ�������
* ע������: 
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
* ��������: SPI_ReadBytes()
* ����˵��: ��������Ϊnum������
* ��    ��: uint8_t num 			Ҫ��ȡ�����ݸ���	
* ��    ��: uint8_t	*data			���յ�������
* ע������: 
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
* ��������: SPI_Master_SSN_Out()
* ����˵��: ��ģʽ�£�SSN����ߵ͵�ƽ���ƴӻ���Ƭѡ����
* ��    ��: uint8_t out 			SSNҪ����ĵ�ƽ    0 �͵�ƽ   1 �ߵ�ƽ		
* ��    ��: ��
* ע������: 
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



