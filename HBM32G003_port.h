#ifndef __HBM32G003_PORT_H__
#define __HBM32G003_PORT_H__          

#include "HBM32G003.h"

typedef struct
{
	uint8_t Port;         //�˿�       
    uint8_t Pin;          //���ź�                              
    uint8_t Func;         //����
	uint8_t Input_En;     //����ʹ��
} PORT_InitTypeDef;


typedef enum
{ 
	WAKEUP_EDGE_FALL =  0x00,    // �½��ػ���
	WAKEUP_EDGE_RISE =  0x01,    // �����ػ���
} WakeUpEdge_TypeDef;

typedef enum
{ 
	PULLUP_RES_OPEN =  0x00,     // ��·
	PULLUP_RES_150K =  0x01,     // ��������150K
	PULLUP_RES_40K =   0x02,     // ��������40K
	PULLUP_RES_32K =   0x03,     // ��������32K	
} PullUpRes_TypeDef;

typedef enum
{ 
	OUT_CURRENT_5MA  =  0x00,    // �������5MA
	OUT_CURRENT_14MA =  0x01,    // �������14MA
	OUT_CURRENT_22MA =  0x02,    // �������22MA
	OUT_CURRENT_30MA =  0x03,    // �������30MA
} OutCurrent_TypeDef;

typedef enum
{ 
	INPUT_HYS_LOW =   0x00,      // ���������  
	INPUT_HYS_HIGH =  0x01,      // ���������  
} InputHys_TypeDef;


typedef struct
{
	WakeUpEdge_TypeDef   WakeUp_Edge;            //PORTA�Ļ�����
	PullUpRes_TypeDef    PullUp_Res;             //PORTA����������
	OutCurrent_TypeDef   Out_Cur;                //PORTA����������
	InputHys_TypeDef     InputHys;               //PORTA��������͵ȼ�
} PORT_CFGTypeDef;

//����  PORTA  
#define IS_PORT_ALL(PORT)           (((PORT) == PORTA))

//���Զ˿ڹ���
#define IS_PORT_FUNC(PORT_FUNC)     ((PORT_FUNC) < 8)

//��������ʹ��
#define IS_INPUT_EN(INPUT_EN)       (((INPUT_EN) == ENABLE) || ((INPUT_EN) == DISABLE))

//���Ի��ѱ���
#define IS_WAKEUP_EDGE(WAKEUP_EDGE) (((WAKEUP_EDGE) == WAKEUP_EDGE_FALL) || ((WAKEUP_EDGE) == WAKEUP_EDGE_RISE))

//������������
#define IS_PULLUP_RES(PULLUP_RES)   (((PULLUP_RES) == PULLUP_RES_OPEN) || ((PULLUP_RES) == PULLUP_RES_150K) || \
                                     ((PULLUP_RES) == PULLUP_RES_40K ) || ((PULLUP_RES) == PULLUP_RES_32K ) )
//������������
#define IS_OUT_CURRENT(OUT_CURRENT) (((OUT_CURRENT) == OUT_CURRENT_5MA ) || ((OUT_CURRENT) == OUT_CURRENT_14MA) || \
                                     ((OUT_CURRENT) == OUT_CURRENT_22MA) || ((OUT_CURRENT) == OUT_CURRENT_30MA) )

//����������͵ȼ�
#define IS_INPUT_HYS(INPUT_HYS)     (((INPUT_HYS) == INPUT_HYS_LOW) || ((INPUT_HYS) == INPUT_HYS_HIGH))


#define PORTA	                   0             //�˿�A

#define PORTA_PIN0_GPIO		 	   0             //PORTA0����ΪGPIOA0
#define PORTA_PIN0_SPI_CLK         1             //PORTA0����ΪSPI��ʱ��
#define PORTA_PIN0_TMRP0_IN0       2             //PORTA0����ΪTIMER_PLUS������0
#define PORTA_PIN0_TMRP0_OUT_L     3             //PORTA0����ΪTIMER_PLUS��16λ��ʱ�������
#define PORTA_PIN0_PWMB0_CH0       4             //PORTA0����ΪPWMBASE0��ͨ��0
#define PORTA_PIN0_PWMP0_CH0N      5             //PORTA0����ΪPWMPLUS0��ͨ��0N


#define PORTA_PIN1_GPIO			   0             //PORTA1����ΪGPIOA1
#define PORTA_PIN1_SPI_MOSI	       1             //PORTA1����ΪSPI����������
#define PORTA_PIN1_UART0_TX        2             //PORTA1����Ϊ����0�ķ���
#define PORTA_PIN1_HALL_IN0        3             //PORTA1����ΪHALL��ͨ��0
#define PORTA_PIN1_PWMP0_CH1N      4             //PORTA1����ΪPWMPLUS0��ͨ��1N
#define PORTA_PIN1_ADC_CH1	       7             //PORTA1����ΪADC��ͨ��1


#define PORTA_PIN2_GPIO			   0             //PORTA2����ΪGPIOA2
#define PORTA_PIN2_SPI_MISO	       1             //PORTA2����ΪSPI������ӳ�
#define PORTA_PIN2_UART0_RX        2             //PORTA2����Ϊ����0�Ľ���
#define PORTA_PIN2_HALL_IN1        3             //PORTA2����ΪHALL��ͨ��1
#define PORTA_PIN2_PWMP0_CH2N      4             //PORTA2����ΪPWMPLUS0��ͨ��2N
#define PORTA_PIN2_ADC_CH0	       7             //PORTA2����ΪADC��ͨ��0


#define PORTA_PIN3_GPIO			   0             //PORTA3����ΪGPIOA3
#define PORTA_PIN3_IIC_SDA	       1             //PORTA3����ΪIIC������
#define PORTA_PIN3_PWMP0_CH0       2             //PORTA3����ΪPWMPLUS0��ͨ��0
#define PORTA_PIN3_XTAH_IN         7             //PORTA3����ΪXTAH_IN


#define PORTA_PIN4_GPIO			   0             //PORTA4����ΪGPIOA4
#define PORTA_PIN4_IIC_SCL	       1             //PORTA4����ΪIIC��ʱ��
#define PORTA_PIN4_PWMP0_CH1       2             //PORTA4����ΪPWMPLUS0��ͨ��1
#define PORTA_PIN4_XTAH_OUT        7             //PORTA4����ΪXTAH_OUT


#define PORTA_PIN5_GPIO			   0             //PORTA5����ΪGPIOA5
#define PORTA_PIN5_SPI_SSN	       1             //PORTA5����ΪSPI��Ƭѡ
#define PORTA_PIN5_TMRP0_IN1       2             //PORTA5����ΪTIMER_PLUS������1
#define PORTA_PIN5_TMRP0_OUT_H     3             //PORTA5����ΪTIMER_PLUS��16λ��ʱ�������
#define PORTA_PIN5_PWMB0_CH1       4             //PORTA5����ΪPWMBASE0��ͨ��1
#define PORTA_PIN5_PWMP0_CH2       5             //PORTA5����ΪPWMPLUS0��ͨ��2
#define PORTA_PIN5_ADC_CH7	       7             //PORTA5����ΪADC��ͨ��7


#define PORTA_PIN6_GPIO			   0             //PORTA6����ΪGPIOA6
#define PORTA_PIN6_IIC_SDA	       1             //PORTA6����ΪIIC������
#define PORTA_PIN6_HALL_IN2        2             //PORTA6����ΪHALL��ͨ��2
#define PORTA_PIN6_BREAK_IN0       3             //PORTA6����ΪBREAK_IN0
#define PORTA_PIN6_ADC_CH6	       7             //PORTA6����ΪADC��ͨ��6


#define PORTA_PIN7_GPIO			   0             //PORTA7����ΪGPIOA7
#define PORTA_PIN7_IIC_SCL	       1             //PORTA7����ΪIIC��ʱ��
#define PORTA_PIN7_BREAK_IN1       2             //PORTA7����ΪBREAK_IN1
#define PORTA_PIN7_ADC_CH5	       7             //PORTA7����ΪADC��ͨ��5


#define PORTA_PIN8_GPIO		 	   0             //PORTA8����ΪGPIOA8
#define PORTA_PIN8_UART0_TX        1             //PORTA8����Ϊ����0�ķ���
#define PORTA_PIN8_TMRP0_IN0       2             //PORTA8����ΪTIMER_PLUS������0
#define PORTA_PIN8_TMRP0_OUT_L     3             //PORTA8����ΪTIMER_PLUS��16λ��ʱ�������
#define PORTA_PIN8_PWMP0_CH2       4             //PORTA8����ΪPWMPLUS0��ͨ��2
#define PORTA_PIN8_PWMP0_CH0N      5             //PORTA8����ΪPWMPLUS0��ͨ��0N 
 
 
#define PORTA_PIN9_GPIO			   0             //PORTA9����ΪGPIOA9
#define PORTA_PIN9_UART0_RX        1             //PORTA9����Ϊ����0�Ľ���
#define PORTA_PIN9_TMRP0_IN1       2             //PORTA9����ΪTIMER_PLUS������1
#define PORTA_PIN9_TMRP0_OUT_H     3             //PORTA9����ΪTIMER_PLUS��16λ��ʱ�������
#define PORTA_PIN9_PWMB0_CH2       4             //PORTA9����ΪPWMBASE0��ͨ��2
#define PORTA_PIN9_PWMP0_CH1N      5             //PORTA9����ΪPWMPLUS0��ͨ��1N
#define PORTA_PIN9_ADC_CH4	       7             //PORTA9����ΪADC��ͨ��4


#define PORTA_PIN10_GPIO		   0             //PORTA10����ΪGPIOA10
#define PORTA_PIN10_SPI_CLK	       1             //PORTA10����ΪSPI��ʱ��
#define PORTA_PIN10_TMRP0_IN0      2             //PORTA10����ΪTIMER_PLUS������0
#define PORTA_PIN10_TMRP0_OUT_L    3             //PORTA10����ΪTIMER_PLUS��16λ��ʱ�������
#define PORTA_PIN10_PWMB0_CH0      4             //PORTA10����ΪPWMBASE0��ͨ��0
#define PORTA_PIN10_PWMP0_CH2N     5             //PORTA10����ΪPWMPLUS0��ͨ��2N


#define PORTA_PIN11_GPIO		   0             //PORTA11����ΪGPIOA11
#define PORTA_PIN11_SPI_MOSI	   1             //PORTA11����ΪSPI����������
#define PORTA_PIN11_TMRP0_IN1      2             //PORTA11����ΪTIMER_PLUS������1
#define PORTA_PIN11_TMRP0_OUT_H    3             //PORTA11����ΪTIMER_PLUS��16λ��ʱ�������
#define PORTA_PIN11_PWMP0_CH0      4             //PORTA11����ΪPWMPLUS0��ͨ��0


#define PORTA_PIN12_GPIO		   0             //PORTA12����ΪGPIOA12
#define PORTA_PIN12_SPI_MISO	   1             //PORTA12����ΪSPI������ӳ�
#define PORTA_PIN12_TMRP0_IN0      2             //PORTA12����ΪTIMER_PLUS������0
#define PORTA_PIN12_TMRP0_OUT_L    3             //PORTA12����ΪTIMER_PLUS��16λ��ʱ�������
#define PORTA_PIN12_PWMP0_CH1      4             //PORTA12����ΪPWMPLUS0��ͨ��1


#define PORTA_PIN13_GPIO		   0             //PORTA13����ΪGPIOA13
#define PORTA_PIN13_SWCLK		   1             //PORTA13����ΪSW���ص�ʱ��
#define PORTA_PIN13_PWMP0_CH2      2             //PORTA13����ΪPWMPLUS0��ͨ��2


#define PORTA_PIN14_GPIO		   0             //PORTA14����ΪGPIOA14
#define PORTA_PIN14_SWDIO		   1             //PORTA14����ΪSW���ص�����
#define PORTA_PIN14_TMRP0_IN1      2             //PORTA14����ΪTIMER_PLUS������1
#define PORTA_PIN14_TMRP0_OUT_H    3             //PORTA14����ΪTIMER_PLUS��16λ��ʱ�������
#define PORTA_PIN14_PWMB0_CH1      4             //PORTA14����ΪPWMBASE0��ͨ��1
#define PORTA_PIN14_ADC_CH3	       7             //PORTA14����ΪADC��ͨ��3


#define PORTA_PIN15_GPIO		   0             //PORTA15����ΪGPIOA15
#define PORTA_PIN15_SPI_SSN	       1             //PORTA15����ΪSPI��Ƭѡ
#define PORTA_PIN15_TMRP0_IN0      2             //PORTA15����ΪTIMER_PLUS������0
#define PORTA_PIN15_TMRP0_OUT_L    3             //PORTA15����ΪTIMER_PLUS��16λ��ʱ�������
#define PORTA_PIN15_PWMB0_CH2      4             //PORTA15����ΪPWMBASE0��ͨ��2
#define PORTA_PIN15_ADC_CH2	       7             //PORTA15����ΪADC��ͨ��2


void PORT_Init(PORT_InitTypeDef* PORT_InitStruct);               //PORT��ʼ������
void PORT_CFG_Init(PORT_CFGTypeDef* PORT_CFGStruct);             //PORT���üĴ�������

#endif //__HBM32G003_PORT_H__
