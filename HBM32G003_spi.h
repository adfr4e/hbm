#ifndef __HBM32G003_SPI_H__
#define __HBM32G003_SPI_H__

#include "HBM32G003.h"


typedef enum
{ 
	SPI_SLAVE_MODE =    0x00,      //从机模式
	SPI_MASTER_MODE =   0x01,      //主机模式
} Master_TypeDef;

typedef enum
{ 
	SPI_CLKDIV_4 =    0x00,        //时钟分频系数为4
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
	SPI_FIRST_EDGE  =   0x00,      //第一个时钟沿开始采样
	SPI_SECOND_EDGE =   0x01,      //第二个时钟沿开始采样
} SampleEdge_TypeDef;

typedef enum
{ 
	SPI_LOW_LEVEL  =   0x00,      //空闲时时钟线保持低电平
	SPI_HIGH_LEVEL =   0x01,      //空闲时时钟线保持高电平
} IdleLevel_TypeDef;

typedef enum
{ 
	SPI_MSB_FISRT =    0x00,      //数据传输顺序  MSB
	SPI_LSB_FISRT =    0x01,      //数据传输顺序  LSB
} LsbFirst_TypeDef;

typedef struct {
	Master_TypeDef      Master;		    //1 主机模式    0 从机模式
	ClkDiv_TypeDef      ClkDiv;		    //SPI_CLK = SYS_CLK / clkDiv，有效值：SPI_CLKDIV_4、SPI_CLKDIV_8、... ... 、SPI_CLKDIV_512
	SampleEdge_TypeDef  SampleEdge;	    //在SPI帧格式下，选择数据采样边沿：SPI_FIRST_EDGE、SPI_SECOND_EDGE
	IdleLevel_TypeDef   IdleLevel;		//在SPI帧格式下，选择空闲时（无数据传输时）时钟线的电平：SPI_LOW_LEVEL、SPI_HIGH_LEVEL
	LsbFirst_TypeDef    LsbFirst;		//数据传输顺序  0 MSB  1  LSB
} SPI_InitTypeDef;
            
//断言SPI主从机模式
#define IS_SPI_MODE(MODE)                       (((MODE) == SPI_SLAVE_MODE) || ((MODE) == SPI_MASTER_MODE))

//断言SPI时钟分频
#define IS_SPI_CLKDIV(SPI_CLKDIV)               (((SPI_CLKDIV) == SPI_CLKDIV_4)   || ((SPI_CLKDIV) == SPI_CLKDIV_8)   ||   \
                                                 ((SPI_CLKDIV) == SPI_CLKDIV_16)  || ((SPI_CLKDIV) == SPI_CLKDIV_32)  ||   \
                                                 ((SPI_CLKDIV) == SPI_CLKDIV_64)  || ((SPI_CLKDIV) == SPI_CLKDIV_128) ||   \
                                                 ((SPI_CLKDIV) == SPI_CLKDIV_256) || ((SPI_CLKDIV) == SPI_CLKDIV_512) )

//断言SPI采样时钟沿
#define IS_SPI_SAMPLE_EDGE(SPI_SAMPLE_EDGE)     (((SPI_SAMPLE_EDGE) == SPI_FIRST_EDGE) || ((SPI_SAMPLE_EDGE) == SPI_SECOND_EDGE))


//断言SPI空闲时钟
#define IS_SPI_IDLE_LEVEL(SPI_IDLE_LEVEL)       (((SPI_IDLE_LEVEL) == SPI_LOW_LEVEL) || ((SPI_IDLE_LEVEL) == SPI_HIGH_LEVEL))

//断言SPI传输顺序
#define IS_SPI_LSBFIRST(SPI_LSBFIRST)           (((SPI_LSBFIRST) == SPI_MSB_FISRT) || ((SPI_LSBFIRST) == SPI_LSB_FISRT))



void SPI_Init(SPI_TypeDef * SPIx,SPI_InitTypeDef * SPI_InitStruct);     //SPI初始化
void SPI_Open(SPI_TypeDef * SPIx);                                      //SPI打开，允许收发
void SPI_Close(SPI_TypeDef * SPIx);                                     //SPI关闭，禁止收发

void SPI_Write(SPI_TypeDef * SPIx,uint8_t data);                        //SPI发送一个数据
void SPI_Write_Wait(SPI_TypeDef * SPIx,uint8_t data);                   //SPI发送一个数据，并等待它发送完成
uint8_t SPI_ReadWrite(SPI_TypeDef * SPIx,uint8_t data);                 //发送一个数据，并返回发送过程中接收到的
void SPI_ReadBytes(SPI_TypeDef * SPIx,uint8_t* data,uint8_t num);       //SPI接收数量为num的数据

void SPI_Master_SSN_Out(SPI_TypeDef * SPIx,uint8_t out);                //主模式下，SSN输出高低电平控制从机的片选引脚


#endif //__HBM32G003_SPI_H__
