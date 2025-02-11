#ifndef __HBM32G003_IIC_H__
#define __HBM32G003_IIC_H__

#include "HBM32G003.h"


//断言IIC时钟
#define IS_IIC_CLK(IIC_CLK)   ((IIC_CLK) > 0)

//断言IIC中断使能
#define IS_IIC_INT(IIC_INT)   (((IIC_INT) == ENABLE) || ((IIC_INT) == DISABLE))


void IIC_Init(IIC_TypeDef *IICx,uint16_t clk,uint8_t IE_Enable);    //IIC初始化

void IIC_Open(IIC_TypeDef *IICx);                              //打开IIC
void IIC_Close(IIC_TypeDef *IICx);                             //关闭IIC

uint8_t IIC_Start(IIC_TypeDef *IICx,uint8_t addr);             //IIC发送起始信号   查询模式
void IIC_Stop(IIC_TypeDef *IICx);                              //IIC发送停止信号   查询、中断模式共用
uint8_t IIC_Write(IIC_TypeDef *IICx,uint8_t data);             //IIC写数据         查询模式
uint8_t IIC_Read(IIC_TypeDef *IICx,uint8_t ack);               //IIC读数据         查询模式

void IIC_Start_NoWait(IIC_TypeDef *IICx,uint8_t addr);         //IIC发送起始信号   中断模式
void IIC_Write_NoWait(IIC_TypeDef *IICx,uint8_t data);         //IIC写数据         中断模式
void IIC_Read_NoWait(IIC_TypeDef *IICx,uint8_t ack);           //IIC读数据         中断模式
uint8_t IIC_Wait_ACK(IIC_TypeDef *IICx);                       //IIC等待应答信号   中断模式

void IIC_IntEn(IIC_TypeDef *IICx);                             //IIC中断使能
void IIC_IntDis(IIC_TypeDef *IICx);                            //IIC中断禁能
void IIC_IntClr(IIC_TypeDef *IICx);                            //IIC中断清除
uint8_t IIC_IntStat(IIC_TypeDef *IICx);                        //IIC中断状态     



#endif //__HBM32G003_IIC_H__
