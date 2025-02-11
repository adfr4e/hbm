#ifndef __HBM32G003_SPI_H__
#define __HBM32G003_SPI_H__

#include "HBM32G003.h"


typedef enum
{ 
	SPI_SLAVE_MODE =    0x00,      //�ӻ�ģʽ
	SPI_MASTER_MODE =   0x01,      //����ģʽ
} Master_TypeDef;

typedef enum
{ 
	SPI_CLKDIV_4 =    0x00,        //ʱ�ӷ�Ƶϵ��Ϊ4
	SPI_CLKDIV_8 =    0x01, 
	SPI_CLKDIV_16 =   0x02,
	SPI_CLKDIV_32 =   0x03, 
	SPI_CLKDIV_64 =   0x04,
	SPI_CLKDIV_128 =  0x05, 
	SPI_CLKDIV_256 =  0x06,
	SPI_CLKDIV_512 =  0x07,
} ClkDiv_TypeDef;

typedef enum
{ 
	SPI_FIRST_EDGE  =   0x00,      //��һ��ʱ���ؿ�ʼ����
	SPI_SECOND_EDGE =   0x01,      //�ڶ���ʱ���ؿ�ʼ����
} SampleEdge_TypeDef;

typedef enum
{ 
	SPI_LOW_LEVEL  =   0x00,      //����ʱʱ���߱��ֵ͵�ƽ
	SPI_HIGH_LEVEL =   0x01,      //����ʱʱ���߱��ָߵ�ƽ
} IdleLevel_TypeDef;

typedef enum
{ 
	SPI_MSB_FISRT =    0x00,      //���ݴ���˳��  MSB
	SPI_LSB_FISRT =    0x01,      //���ݴ���˳��  LSB
} LsbFirst_TypeDef;

typedef struct {
	Master_TypeDef      Master;		    //1 ����ģʽ    0 �ӻ�ģʽ
	ClkDiv_TypeDef      ClkDiv;		    //SPI_CLK = SYS_CLK / clkDiv����Чֵ��SPI_CLKDIV_4��SPI_CLKDIV_8��... ... ��SPI_CLKDIV_512
	SampleEdge_TypeDef  SampleEdge;	    //��SPI֡��ʽ�£�ѡ�����ݲ������أ�SPI_FIRST_EDGE��SPI_SECOND_EDGE
	IdleLevel_TypeDef   IdleLevel;		//��SPI֡��ʽ�£�ѡ�����ʱ�������ݴ���ʱ��ʱ���ߵĵ�ƽ��SPI_LOW_LEVEL��SPI_HIGH_LEVEL
	LsbFirst_TypeDef    LsbFirst;		//���ݴ���˳��  0 MSB  1  LSB
} SPI_InitTypeDef;
            
//����SPI���ӻ�ģʽ
#define IS_SPI_MODE(MODE)                       (((MODE) == SPI_SLAVE_MODE) || ((MODE) == SPI_MASTER_MODE))

//����SPIʱ�ӷ�Ƶ
#define IS_SPI_CLKDIV(SPI_CLKDIV)               (((SPI_CLKDIV) == SPI_CLKDIV_4)   || ((SPI_CLKDIV) == SPI_CLKDIV_8)   ||   \
                                                 ((SPI_CLKDIV) == SPI_CLKDIV_16)  || ((SPI_CLKDIV) == SPI_CLKDIV_32)  ||   \
                                                 ((SPI_CLKDIV) == SPI_CLKDIV_64)  || ((SPI_CLKDIV) == SPI_CLKDIV_128) ||   \
                                                 ((SPI_CLKDIV) == SPI_CLKDIV_256) || ((SPI_CLKDIV) == SPI_CLKDIV_512) )

//����SPI����ʱ����
#define IS_SPI_SAMPLE_EDGE(SPI_SAMPLE_EDGE)     (((SPI_SAMPLE_EDGE) == SPI_FIRST_EDGE) || ((SPI_SAMPLE_EDGE) == SPI_SECOND_EDGE))


//����SPI����ʱ��
#define IS_SPI_IDLE_LEVEL(SPI_IDLE_LEVEL)       (((SPI_IDLE_LEVEL) == SPI_LOW_LEVEL) || ((SPI_IDLE_LEVEL) == SPI_HIGH_LEVEL))

//����SPI����˳��
#define IS_SPI_LSBFIRST(SPI_LSBFIRST)           (((SPI_LSBFIRST) == SPI_MSB_FISRT) || ((SPI_LSBFIRST) == SPI_LSB_FISRT))



void SPI_Init(SPI_TypeDef * SPIx,SPI_InitTypeDef * SPI_InitStruct);     //SPI��ʼ��
void SPI_Open(SPI_TypeDef * SPIx);                                      //SPI�򿪣������շ�
void SPI_Close(SPI_TypeDef * SPIx);                                     //SPI�رգ���ֹ�շ�

void SPI_Write(SPI_TypeDef * SPIx,uint8_t data);                        //SPI����һ������
void SPI_Write_Wait(SPI_TypeDef * SPIx,uint8_t data);                   //SPI����һ�����ݣ����ȴ����������
uint8_t SPI_ReadWrite(SPI_TypeDef * SPIx,uint8_t data);                 //����һ�����ݣ������ط��͹����н��յ���
void SPI_ReadBytes(SPI_TypeDef * SPIx,uint8_t* data,uint8_t num);       //SPI��������Ϊnum������

void SPI_Master_SSN_Out(SPI_TypeDef * SPIx,uint8_t out);                //��ģʽ�£�SSN����ߵ͵�ƽ���ƴӻ���Ƭѡ����


#endif //__HBM32G003_SPI_H__
