#include "HBM32G003_uart.h"

/****************************************************************************************************************************************** 
* ��������: UART_Init()
* ����˵��:	���ڳ�ʼ�����������ں�  ������  ���ݳ���   У��λ   ֹͣλ   �ж�ʹ��
* ��    ��: UART_TypeDef * UARTx     UART0  
*			UART_InitTypeDef * UART_InitStruct
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void UART_Init(UART_TypeDef * UARTx, UART_InitTypeDef * UART_InitStruct)	
{
	uint32_t temp = 0,Baudrate_Set = 0;
	
	assert_param(IS_UART_ALL(UARTx));                                 //�������Ĳ���UARTx�Ƿ�Ϸ�      
	
	assert_param(IS_UART_BAUDRATE(UART_InitStruct->Baudrate));        //�������Ĳ���Baudrate�Ƿ�Ϸ�  
	
	assert_param(IS_UART_DATABITS(UART_InitStruct->DataBits));        //�������Ĳ���DataBits�Ƿ�Ϸ�    
	
	assert_param(IS_UART_PARITY(UART_InitStruct->Parity));            //�������Ĳ���Parity�Ƿ�Ϸ�  
	
	assert_param(IS_UART_STOP(UART_InitStruct->StopBits));            //�������Ĳ���StopBits�Ƿ�Ϸ�  
	
	assert_param(IS_UART_RXIE(UART_InitStruct->RXIEn));               //�������Ĳ���RXIEn�Ƿ�Ϸ�  
	
	
	switch((uint32_t)UARTx)
	{
		case ((uint32_t)UART0):
			
			SYS->CLKEN |= 0x01 << SYS_CLKEN_UART0_POS;        //�򿪴���0��ʱ��
		
		break;
	}
	
	UARTx->CTRL |= (0x01 << UART_CTRL_BAUDEN_POS);            //��������������λ              
	
	if(((SystemCoreClock/16)%UART_InitStruct->Baudrate)*1.0/UART_InitStruct->Baudrate > 0.5)
	{
		Baudrate_Set = (SystemCoreClock/16/UART_InitStruct->Baudrate) + 1;
	}
	else
	{
		Baudrate_Set = (SystemCoreClock/16/UART_InitStruct->Baudrate);
	}
	
	UARTx->DHL = Baudrate_Set>>8;                             //���ò�����
	UARTx->DLL = Baudrate_Set&0xFF;
	
	UARTx->CTRL &= ~(0x01 << UART_CTRL_BAUDEN_POS);           //�رղ���������λ
	
	temp = UARTx->CTRL;
	
	temp &= ~(UART_CTRL_DATALEN_MSK | UART_CTRL_STOP2BIT_MSK | UART_CTRL_PARITY_MSK);
	
	temp |= (UART_InitStruct->DataBits << UART_CTRL_DATALEN_POS) |            //�������ݳ���
				   (UART_InitStruct->StopBits << UART_CTRL_STOP2BIT_POS)|     //����ֹͣλ
				   (UART_InitStruct->Parity   << UART_CTRL_PARITY_POS);       //����У��λ
	
	UARTx->CTRL = temp;
	
	if(UART_InitStruct->RXIEn == ENABLE)
	{
		UARTx->IE |= 0x01 << UART_IE_RXIEN_POS;                 //���ý���������Ч�ж�
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
				NVIC_EnableIRQ(UART0_IRQn);         //ʹ�ܴ���0�ж�   
			}
			else
			{
				NVIC_DisableIRQ(UART0_IRQn);        //���ܴ���0�ж�  
			}
			
		break;
	}
}

/****************************************************************************************************************************************** 
* ��������: UART_SendData()
* ����˵��:	���ڷ��ͺ���   
* ��    ��: UART_TypeDef * UARTx     UART0    
*			uint8_t data    �����͵�����
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void UART_SendData(UART_TypeDef * UARTx, uint8_t data)
{
	assert_param(IS_UART_ALL(UARTx));               //�������Ĳ���UARTx�Ƿ�Ϸ�      
	
	UARTx->SDR = data;                              //��������
	while((UARTx->LSR & UART_LSR_THRE_MSK) == 0);   //�ȴ��������
}

/****************************************************************************************************************************************** 
* ��������: UART_ReceiveData()
* ����˵��:	���ڽ��պ���  
* ��    ��: UART_TypeDef * UARTx     UART0 	   
*			uint8_t *data    ���յ�������
* ��    ��: ����״̬   �޴��󷵻�0 
* ע������: ��
******************************************************************************************************************************************/
uint8_t UART_ReceiveData(UART_TypeDef * UARTx, uint8_t *data)
{
	uint8_t temp;
	
	assert_param(IS_UART_ALL(UARTx));                               //�������Ĳ���UARTx�Ƿ�Ϸ�     
	
	temp = UARTx->LSR;
	
	if((temp & UART_LSR_REC_MSK) == 0)  return UART_ERR_REC;        //û�н��յ�����
	if(temp & UART_LSR_OVF_MSK)         return UART_ERR_OVF;        //�������
	if(temp & UART_LSR_PARITY_MSK)      return UART_ERR_PARITY;     //У�����
	if(temp & UART_LSR_STOP_MSK)        return UART_ERR_STOP;       //ֹͣλ����
	if(temp & UART_LSR_BREAK_MSK)       return UART_ERR_BREAK;      //BREAK����
	
	*data = UARTx->RDR;               //�޴���ȡ�����յ�����
	
	return 0;	                      //�޴��󷵻�0
}

/****************************************************************************************************************************************** 
* ��������: UART_IsTXEmpty()
* ����˵��:	���ڷ��ͼĴ����Ƿ�Ϊ��
* ��    ��: UART_TypeDef * UARTx     UART0  
*			
* ��    ��: 1 ���ͼĴ���Ϊ�գ����Լ�����������   0  ���ͼĴ�����Ϊ�� ��ʾ���ڷ������ݻ�û�з������
* ע������: ��
******************************************************************************************************************************************/
uint8_t UART_IsTXEmpty(UART_TypeDef * UARTx)
{
	assert_param(IS_UART_ALL(UARTx));               //�������Ĳ���UARTx�Ƿ�Ϸ�     
	
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
* ��������: UART_IsRXValid()
* ����˵��:	���ڽ��ռĴ����Ƿ�������
* ��    ��: UART_TypeDef * UARTx     UART0    
*			
* ��    ��: 1 ���ռĴ��������ݿ��Զ�ȡ   0  ���ռĴ���Ϊ��
* ע������: ��
******************************************************************************************************************************************/
uint8_t UART_IsRXValid(UART_TypeDef * UARTx)
{
	assert_param(IS_UART_ALL(UARTx));               //�������Ĳ���UARTx�Ƿ�Ϸ�     
	
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
* ��������: UART_TX_INTEn()
* ����˵��:	���ڷ����ж�ʹ�� 
* ��    ��: UART_TypeDef * UARTx     UART0    
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void UART_TX_INTEn(UART_TypeDef * UARTx)
{
	assert_param(IS_UART_ALL(UARTx));               //�������Ĳ���UARTx�Ƿ�Ϸ�     
	
	switch((uint32_t)UARTx)         
	{
		case ((uint32_t)UART0):
		
			UART0->IE |= 0x01 << UART_IE_TXE_POS;
		
			NVIC_EnableIRQ(UART0_IRQn);
		
		break;
	}	
}

/****************************************************************************************************************************************** 
* ��������: UART_TX_INTDis()
* ����˵��:	���ڷ����жϽ���
* ��    ��: UART_TypeDef * UARTx     UART0	   
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void UART_TX_INTDis(UART_TypeDef * UARTx)
{
	assert_param(IS_UART_ALL(UARTx));               //�������Ĳ���UARTx�Ƿ�Ϸ�     
	
	switch((uint32_t)UARTx)         
	{
		case ((uint32_t)UART0):
		
			UART0->IE &= ~(0x01 << UART_IE_TXE_POS);
			
		break;
	}	
}


/****************************************************************************************************************************************** 
* ��������: UART_RX_INTEn()
* ����˵��:	���ڽ����ж�ʹ�� 
* ��    ��: UART_TypeDef * UARTx     UART0  
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void UART_RX_INTEn(UART_TypeDef * UARTx)
{
	assert_param(IS_UART_ALL(UARTx));               //�������Ĳ���UARTx�Ƿ�Ϸ�     
	
	switch((uint32_t)UARTx)         
	{
		case ((uint32_t)UART0):
		
			UART0->IE |= 0x01 << UART_IE_RXIEN_POS;
			
			NVIC_EnableIRQ(UART0_IRQn);
		
		break;
	}	
}

/****************************************************************************************************************************************** 
* ��������: UART_RX_INTDis()
* ����˵��:	���ڽ����жϽ���
* ��    ��: UART_TypeDef * UARTx     UART0    
* ��    ��: ��
* ע������: ��
******************************************************************************************************************************************/
void UART_RX_INTDis(UART_TypeDef * UARTx)
{
	assert_param(IS_UART_ALL(UARTx));               //�������Ĳ���UARTx�Ƿ�Ϸ�     
	
	switch((uint32_t)UARTx)         
	{
		case ((uint32_t)UART0):
		
			UART0->IE &= ~(0x01 << UART_IE_RXIEN_POS);
			
		break;
	}	
}


