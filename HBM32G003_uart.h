#ifndef __HBM32G003_UART_H__
#define __HBM32G003_UART_H__

#include "HBM32G003.h"


typedef enum
{ 
	UART_DATA_5BIT =  0x00,       //数据位5bit
	UART_DATA_6BIT =  0x01,       //数据位6bit
    UART_DATA_7BIT =  0x02,       //数据位7bit
	UART_DATA_8BIT =  0x03        //数据位8bit
} DataBits_TypeDef;

typedef enum
{ 
	UART_PARITY_NONE =  0x00,     //无校验
	UART_PARITY_ODD  =  0x01,     //奇校验
    UART_PARITY_EVEN =  0x03,     //偶校验
	UART_PARITY_ONE  =  0x05,     //常1
	UART_PARITY_ZERO =  0x07      //常0
} Parity_TypeDef;

typedef enum
{ 
	UART_STOP_1BIT =  0x00,       //1位停止位
	UART_STOP_2BIT =  0x01,       //2位停止位
} StopBits_TypeDef;


typedef struct {
	uint32_t          Baudrate;         //波特率
	
	DataBits_TypeDef  DataBits;			//数据位位数，可取值UART_DATA_5BIT、UART_DATA_6BIT  UART_DATA_7BIT、UART_DATA_8BIT
	
	Parity_TypeDef    Parity;			//奇偶校验位，可取值UART_PARITY_NONE、UART_PARITY_ODD、UART_PARITY_EVEN、UART_PARITY_ONE、UART_PARITY_ZERO
	
	StopBits_TypeDef  StopBits;			//停止位位数，可取值UART_STOP_1BIT、UART_STOP_2BIT
	
	uint8_t           RXIEn;	        //接收数据有效中断
} UART_InitTypeDef;


//断言  UART0 
#define IS_UART_ALL(UART) (((UART) == UART0))


//断言串口波特率 
#define IS_UART_BAUDRATE(UART_BAUDRATE)  (((UART_BAUDRATE) > 0) && ((UART_BAUDRATE) < SystemCoreClock/16))


//断言串口数据位位数
#define IS_UART_DATABITS(UART_DATABITS)  ( ((UART_DATABITS) == UART_DATA_5BIT) || ((UART_DATABITS) == UART_DATA_6BIT) ||   \
										   ((UART_DATABITS) == UART_DATA_7BIT) || ((UART_DATABITS) == UART_DATA_8BIT) )

//断言串口奇偶校验位
#define IS_UART_PARITY(UART_PARITY)      ( ((UART_PARITY) == UART_PARITY_NONE) || ((UART_PARITY) == UART_PARITY_ODD) ||  \
                                           ((UART_PARITY) == UART_PARITY_EVEN) || ((UART_PARITY) == UART_PARITY_ONE) ||  \
                                           ((UART_PARITY) == UART_PARITY_ZERO) )

//断言串口停止位
#define IS_UART_STOP(UART_STOP)          ( ((UART_STOP) == UART_STOP_1BIT) || ((UART_STOP) == UART_STOP_2BIT) )


//断言串口接收中断
#define IS_UART_RXIE(UART_RXIE)          ( ((UART_RXIE) == ENABLE) || ((UART_RXIE) == DISABLE))


#define UART_ERR_REC        1            //接收数据错误
#define UART_ERR_OVF        2            //溢出错误
#define UART_ERR_PARITY     3            //校验错误
#define UART_ERR_STOP       4            //停止位错误
#define UART_ERR_BREAK      5            //BREAK错误


void UART_Init(UART_TypeDef * UARTx, UART_InitTypeDef * initStruct);	//UART串口初始化
void UART_SendData(UART_TypeDef * UARTx, uint8_t data);                 //串口发送
uint8_t UART_ReceiveData(UART_TypeDef * UARTx, uint8_t *data);          //串口接收
uint8_t UART_IsTXEmpty(UART_TypeDef * UARTx);                           //串口发送空判断
uint8_t UART_IsRXValid(UART_TypeDef * UARTx);                           //串口接收数据有效判断


#endif //__HBM32G003_UART_H__
