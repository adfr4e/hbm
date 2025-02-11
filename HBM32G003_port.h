#ifndef __HBM32G003_PORT_H__
#define __HBM32G003_PORT_H__          

#include "HBM32G003.h"

typedef struct
{
	uint8_t Port;         //端口       
    uint8_t Pin;          //引脚号                              
    uint8_t Func;         //功能
	uint8_t Input_En;     //输入使能
} PORT_InitTypeDef;


typedef enum
{ 
	WAKEUP_EDGE_FALL =  0x00,    // 下降沿唤醒
	WAKEUP_EDGE_RISE =  0x01,    // 上升沿唤醒
} WakeUpEdge_TypeDef;

typedef enum
{ 
	PULLUP_RES_OPEN =  0x00,     // 开路
	PULLUP_RES_150K =  0x01,     // 上拉电阻150K
	PULLUP_RES_40K =   0x02,     // 上拉电阻40K
	PULLUP_RES_32K =   0x03,     // 上拉电阻32K	
} PullUpRes_TypeDef;

typedef enum
{ 
	OUT_CURRENT_5MA  =  0x00,    // 输出电流5MA
	OUT_CURRENT_14MA =  0x01,    // 输出电流14MA
	OUT_CURRENT_22MA =  0x02,    // 输出电流22MA
	OUT_CURRENT_30MA =  0x03,    // 输出电流30MA
} OutCurrent_TypeDef;

typedef enum
{ 
	INPUT_HYS_LOW =   0x00,      // 低输入迟滞  
	INPUT_HYS_HIGH =  0x01,      // 高输入迟滞  
} InputHys_TypeDef;


typedef struct
{
	WakeUpEdge_TypeDef   WakeUp_Edge;            //PORTA的唤醒沿
	PullUpRes_TypeDef    PullUp_Res;             //PORTA的上拉电阻
	OutCurrent_TypeDef   Out_Cur;                //PORTA的驱动能力
	InputHys_TypeDef     InputHys;               //PORTA的输入迟滞等级
} PORT_CFGTypeDef;

//断言  PORTA  
#define IS_PORT_ALL(PORT)           (((PORT) == PORTA))

//断言端口功能
#define IS_PORT_FUNC(PORT_FUNC)     ((PORT_FUNC) < 8)

//断言输入使能
#define IS_INPUT_EN(INPUT_EN)       (((INPUT_EN) == ENABLE) || ((INPUT_EN) == DISABLE))

//断言唤醒边沿
#define IS_WAKEUP_EDGE(WAKEUP_EDGE) (((WAKEUP_EDGE) == WAKEUP_EDGE_FALL) || ((WAKEUP_EDGE) == WAKEUP_EDGE_RISE))

//断言上拉电阻
#define IS_PULLUP_RES(PULLUP_RES)   (((PULLUP_RES) == PULLUP_RES_OPEN) || ((PULLUP_RES) == PULLUP_RES_150K) || \
                                     ((PULLUP_RES) == PULLUP_RES_40K ) || ((PULLUP_RES) == PULLUP_RES_32K ) )
//断言驱动能力
#define IS_OUT_CURRENT(OUT_CURRENT) (((OUT_CURRENT) == OUT_CURRENT_5MA ) || ((OUT_CURRENT) == OUT_CURRENT_14MA) || \
                                     ((OUT_CURRENT) == OUT_CURRENT_22MA) || ((OUT_CURRENT) == OUT_CURRENT_30MA) )

//断言输入迟滞等级
#define IS_INPUT_HYS(INPUT_HYS)     (((INPUT_HYS) == INPUT_HYS_LOW) || ((INPUT_HYS) == INPUT_HYS_HIGH))


#define PORTA	                   0             //端口A

#define PORTA_PIN0_GPIO		 	   0             //PORTA0配置为GPIOA0
#define PORTA_PIN0_SPI_CLK         1             //PORTA0配置为SPI的时钟
#define PORTA_PIN0_TMRP0_IN0       2             //PORTA0配置为TIMER_PLUS的输入0
#define PORTA_PIN0_TMRP0_OUT_L     3             //PORTA0配置为TIMER_PLUS低16位定时器的输出
#define PORTA_PIN0_PWMB0_CH0       4             //PORTA0配置为PWMBASE0的通道0
#define PORTA_PIN0_PWMP0_CH0N      5             //PORTA0配置为PWMPLUS0的通道0N


#define PORTA_PIN1_GPIO			   0             //PORTA1配置为GPIOA1
#define PORTA_PIN1_SPI_MOSI	       1             //PORTA1配置为SPI的主出从入
#define PORTA_PIN1_UART0_TX        2             //PORTA1配置为串口0的发送
#define PORTA_PIN1_HALL_IN0        3             //PORTA1配置为HALL的通道0
#define PORTA_PIN1_PWMP0_CH1N      4             //PORTA1配置为PWMPLUS0的通道1N
#define PORTA_PIN1_ADC_CH1	       7             //PORTA1配置为ADC的通道1


#define PORTA_PIN2_GPIO			   0             //PORTA2配置为GPIOA2
#define PORTA_PIN2_SPI_MISO	       1             //PORTA2配置为SPI的主入从出
#define PORTA_PIN2_UART0_RX        2             //PORTA2配置为串口0的接收
#define PORTA_PIN2_HALL_IN1        3             //PORTA2配置为HALL的通道1
#define PORTA_PIN2_PWMP0_CH2N      4             //PORTA2配置为PWMPLUS0的通道2N
#define PORTA_PIN2_ADC_CH0	       7             //PORTA2配置为ADC的通道0


#define PORTA_PIN3_GPIO			   0             //PORTA3配置为GPIOA3
#define PORTA_PIN3_IIC_SDA	       1             //PORTA3配置为IIC的数据
#define PORTA_PIN3_PWMP0_CH0       2             //PORTA3配置为PWMPLUS0的通道0
#define PORTA_PIN3_XTAH_IN         7             //PORTA3配置为XTAH_IN


#define PORTA_PIN4_GPIO			   0             //PORTA4配置为GPIOA4
#define PORTA_PIN4_IIC_SCL	       1             //PORTA4配置为IIC的时钟
#define PORTA_PIN4_PWMP0_CH1       2             //PORTA4配置为PWMPLUS0的通道1
#define PORTA_PIN4_XTAH_OUT        7             //PORTA4配置为XTAH_OUT


#define PORTA_PIN5_GPIO			   0             //PORTA5配置为GPIOA5
#define PORTA_PIN5_SPI_SSN	       1             //PORTA5配置为SPI的片选
#define PORTA_PIN5_TMRP0_IN1       2             //PORTA5配置为TIMER_PLUS的输入1
#define PORTA_PIN5_TMRP0_OUT_H     3             //PORTA5配置为TIMER_PLUS高16位定时器的输出
#define PORTA_PIN5_PWMB0_CH1       4             //PORTA5配置为PWMBASE0的通道1
#define PORTA_PIN5_PWMP0_CH2       5             //PORTA5配置为PWMPLUS0的通道2
#define PORTA_PIN5_ADC_CH7	       7             //PORTA5配置为ADC的通道7


#define PORTA_PIN6_GPIO			   0             //PORTA6配置为GPIOA6
#define PORTA_PIN6_IIC_SDA	       1             //PORTA6配置为IIC的数据
#define PORTA_PIN6_HALL_IN2        2             //PORTA6配置为HALL的通道2
#define PORTA_PIN6_BREAK_IN0       3             //PORTA6配置为BREAK_IN0
#define PORTA_PIN6_ADC_CH6	       7             //PORTA6配置为ADC的通道6


#define PORTA_PIN7_GPIO			   0             //PORTA7配置为GPIOA7
#define PORTA_PIN7_IIC_SCL	       1             //PORTA7配置为IIC的时钟
#define PORTA_PIN7_BREAK_IN1       2             //PORTA7配置为BREAK_IN1
#define PORTA_PIN7_ADC_CH5	       7             //PORTA7配置为ADC的通道5


#define PORTA_PIN8_GPIO		 	   0             //PORTA8配置为GPIOA8
#define PORTA_PIN8_UART0_TX        1             //PORTA8配置为串口0的发送
#define PORTA_PIN8_TMRP0_IN0       2             //PORTA8配置为TIMER_PLUS的输入0
#define PORTA_PIN8_TMRP0_OUT_L     3             //PORTA8配置为TIMER_PLUS低16位定时器的输出
#define PORTA_PIN8_PWMP0_CH2       4             //PORTA8配置为PWMPLUS0的通道2
#define PORTA_PIN8_PWMP0_CH0N      5             //PORTA8配置为PWMPLUS0的通道0N 
 
 
#define PORTA_PIN9_GPIO			   0             //PORTA9配置为GPIOA9
#define PORTA_PIN9_UART0_RX        1             //PORTA9配置为串口0的接收
#define PORTA_PIN9_TMRP0_IN1       2             //PORTA9配置为TIMER_PLUS的输入1
#define PORTA_PIN9_TMRP0_OUT_H     3             //PORTA9配置为TIMER_PLUS高16位定时器的输出
#define PORTA_PIN9_PWMB0_CH2       4             //PORTA9配置为PWMBASE0的通道2
#define PORTA_PIN9_PWMP0_CH1N      5             //PORTA9配置为PWMPLUS0的通道1N
#define PORTA_PIN9_ADC_CH4	       7             //PORTA9配置为ADC的通道4


#define PORTA_PIN10_GPIO		   0             //PORTA10配置为GPIOA10
#define PORTA_PIN10_SPI_CLK	       1             //PORTA10配置为SPI的时钟
#define PORTA_PIN10_TMRP0_IN0      2             //PORTA10配置为TIMER_PLUS的输入0
#define PORTA_PIN10_TMRP0_OUT_L    3             //PORTA10配置为TIMER_PLUS低16位定时器的输出
#define PORTA_PIN10_PWMB0_CH0      4             //PORTA10配置为PWMBASE0的通道0
#define PORTA_PIN10_PWMP0_CH2N     5             //PORTA10配置为PWMPLUS0的通道2N


#define PORTA_PIN11_GPIO		   0             //PORTA11配置为GPIOA11
#define PORTA_PIN11_SPI_MOSI	   1             //PORTA11配置为SPI的主出从入
#define PORTA_PIN11_TMRP0_IN1      2             //PORTA11配置为TIMER_PLUS的输入1
#define PORTA_PIN11_TMRP0_OUT_H    3             //PORTA11配置为TIMER_PLUS高16位定时器的输出
#define PORTA_PIN11_PWMP0_CH0      4             //PORTA11配置为PWMPLUS0的通道0


#define PORTA_PIN12_GPIO		   0             //PORTA12配置为GPIOA12
#define PORTA_PIN12_SPI_MISO	   1             //PORTA12配置为SPI的主入从出
#define PORTA_PIN12_TMRP0_IN0      2             //PORTA12配置为TIMER_PLUS的输入0
#define PORTA_PIN12_TMRP0_OUT_L    3             //PORTA12配置为TIMER_PLUS低16位定时器的输出
#define PORTA_PIN12_PWMP0_CH1      4             //PORTA12配置为PWMPLUS0的通道1


#define PORTA_PIN13_GPIO		   0             //PORTA13配置为GPIOA13
#define PORTA_PIN13_SWCLK		   1             //PORTA13配置为SW下载的时钟
#define PORTA_PIN13_PWMP0_CH2      2             //PORTA13配置为PWMPLUS0的通道2


#define PORTA_PIN14_GPIO		   0             //PORTA14配置为GPIOA14
#define PORTA_PIN14_SWDIO		   1             //PORTA14配置为SW下载的数据
#define PORTA_PIN14_TMRP0_IN1      2             //PORTA14配置为TIMER_PLUS的输入1
#define PORTA_PIN14_TMRP0_OUT_H    3             //PORTA14配置为TIMER_PLUS高16位定时器的输出
#define PORTA_PIN14_PWMB0_CH1      4             //PORTA14配置为PWMBASE0的通道1
#define PORTA_PIN14_ADC_CH3	       7             //PORTA14配置为ADC的通道3


#define PORTA_PIN15_GPIO		   0             //PORTA15配置为GPIOA15
#define PORTA_PIN15_SPI_SSN	       1             //PORTA15配置为SPI的片选
#define PORTA_PIN15_TMRP0_IN0      2             //PORTA15配置为TIMER_PLUS的输入0
#define PORTA_PIN15_TMRP0_OUT_L    3             //PORTA15配置为TIMER_PLUS低16位定时器的输出
#define PORTA_PIN15_PWMB0_CH2      4             //PORTA15配置为PWMBASE0的通道2
#define PORTA_PIN15_ADC_CH2	       7             //PORTA15配置为ADC的通道2


void PORT_Init(PORT_InitTypeDef* PORT_InitStruct);               //PORT初始化函数
void PORT_CFG_Init(PORT_CFGTypeDef* PORT_CFGStruct);             //PORT配置寄存器函数

#endif //__HBM32G003_PORT_H__
