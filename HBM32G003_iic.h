#ifndef __HBM32G003_IIC_H__
#define __HBM32G003_IIC_H__

#include "HBM32G003.h"


//����IICʱ��
#define IS_IIC_CLK(IIC_CLK)   ((IIC_CLK) > 0)

//����IIC�ж�ʹ��
#define IS_IIC_INT(IIC_INT)   (((IIC_INT) == ENABLE) || ((IIC_INT) == DISABLE))


void IIC_Init(IIC_TypeDef *IICx,uint16_t clk,uint8_t IE_Enable);    //IIC��ʼ��

void IIC_Open(IIC_TypeDef *IICx);                              //��IIC
void IIC_Close(IIC_TypeDef *IICx);                             //�ر�IIC

uint8_t IIC_Start(IIC_TypeDef *IICx,uint8_t addr);             //IIC������ʼ�ź�   ��ѯģʽ
void IIC_Stop(IIC_TypeDef *IICx);                              //IIC����ֹͣ�ź�   ��ѯ���ж�ģʽ����
uint8_t IIC_Write(IIC_TypeDef *IICx,uint8_t data);             //IICд����         ��ѯģʽ
uint8_t IIC_Read(IIC_TypeDef *IICx,uint8_t ack);               //IIC������         ��ѯģʽ

void IIC_Start_NoWait(IIC_TypeDef *IICx,uint8_t addr);         //IIC������ʼ�ź�   �ж�ģʽ
void IIC_Write_NoWait(IIC_TypeDef *IICx,uint8_t data);         //IICд����         �ж�ģʽ
void IIC_Read_NoWait(IIC_TypeDef *IICx,uint8_t ack);           //IIC������         �ж�ģʽ
uint8_t IIC_Wait_ACK(IIC_TypeDef *IICx);                       //IIC�ȴ�Ӧ���ź�   �ж�ģʽ

void IIC_IntEn(IIC_TypeDef *IICx);                             //IIC�ж�ʹ��
void IIC_IntDis(IIC_TypeDef *IICx);                            //IIC�жϽ���
void IIC_IntClr(IIC_TypeDef *IICx);                            //IIC�ж����
uint8_t IIC_IntStat(IIC_TypeDef *IICx);                        //IIC�ж�״̬     



#endif //__HBM32G003_IIC_H__
