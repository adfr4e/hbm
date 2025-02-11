#ifndef __HBM32G003_UART_H__
#define __HBM32G003_UART_H__

#include "HBM32G003.h"


typedef enum
{ 
	UART_DATA_5BIT =  0x00,       //����λ5bit
	UART_DATA_6BIT =  0x01,       //����λ6bit
    UART_DATA_7BIT =  0x02,       //����λ7bit
	UART_DATA_8BIT =  0x03        //����λ8bit
} DataBits_TypeDef;

typedef enum
{ 
	UART_PARITY_NONE =  0x00,     //��У��
	UART_PARITY_ODD  =  0x01,     //��У��
    UART_PARITY_EVEN =  0x03,     //żУ��
	UART_PARITY_ONE  =  0x05,     //��1
	UART_PARITY_ZERO =  0x07      //��0
} Parity_TypeDef;

typedef enum
{ 
	UART_STOP_1BIT =  0x00,       //1λֹͣλ
	UART_STOP_2BIT =  0x01,       //2λֹͣλ
} StopBits_TypeDef;


typedef struct {
	uint32_t          Baudrate;         //������
	
	DataBits_TypeDef  DataBits;			//����λλ������ȡֵUART_DATA_5BIT��UART_DATA_6BIT  UART_DATA_7BIT��UART_DATA_8BIT
	
	Parity_TypeDef    Parity;			//��żУ��λ����ȡֵUART_PARITY_NONE��UART_PARITY_ODD��UART_PARITY_EVEN��UART_PARITY_ONE��UART_PARITY_ZERO
	
	StopBits_TypeDef  StopBits;			//ֹͣλλ������ȡֵUART_STOP_1BIT��UART_STOP_2BIT
	
	uint8_t           RXIEn;	        //����������Ч�ж�
} UART_InitTypeDef;


//����  UART0 
#define IS_UART_ALL(UART) (((UART) == UART0))


//���Դ��ڲ����� 
#define IS_UART_BAUDRATE(UART_BAUDRATE)  (((UART_BAUDRATE) > 0) && ((UART_BAUDRATE) < SystemCoreClock/16))


//���Դ�������λλ��
#define IS_UART_DATABITS(UART_DATABITS)  ( ((UART_DATABITS) == UART_DATA_5BIT) || ((UART_DATABITS) == UART_DATA_6BIT) ||   \
										   ((UART_DATABITS) == UART_DATA_7BIT) || ((UART_DATABITS) == UART_DATA_8BIT) )

//���Դ�����żУ��λ
#define IS_UART_PARITY(UART_PARITY)      ( ((UART_PARITY) == UART_PARITY_NONE) || ((UART_PARITY) == UART_PARITY_ODD) ||  \
                                           ((UART_PARITY) == UART_PARITY_EVEN) || ((UART_PARITY) == UART_PARITY_ONE) ||  \
                                           ((UART_PARITY) == UART_PARITY_ZERO) )

//���Դ���ֹͣλ
#define IS_UART_STOP(UART_STOP)          ( ((UART_STOP) == UART_STOP_1BIT) || ((UART_STOP) == UART_STOP_2BIT) )


//���Դ��ڽ����ж�
#define IS_UART_RXIE(UART_RXIE)          ( ((UART_RXIE) == ENABLE) || ((UART_RXIE) == DISABLE))


#define UART_ERR_REC        1            //�������ݴ���
#define UART_ERR_OVF        2            //�������
#define UART_ERR_PARITY     3            //У�����
#define UART_ERR_STOP       4            //ֹͣλ����
#define UART_ERR_BREAK      5            //BREAK����


void UART_Init(UART_TypeDef * UARTx, UART_InitTypeDef * initStruct);	//UART���ڳ�ʼ��
void UART_SendData(UART_TypeDef * UARTx, uint8_t data);                 //���ڷ���
uint8_t UART_ReceiveData(UART_TypeDef * UARTx, uint8_t *data);          //���ڽ���
uint8_t UART_IsTXEmpty(UART_TypeDef * UARTx);                           //���ڷ��Ϳ��ж�
uint8_t UART_IsRXValid(UART_TypeDef * UARTx);                           //���ڽ���������Ч�ж�


#endif //__HBM32G003_UART_H__
