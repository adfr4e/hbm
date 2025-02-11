#ifndef __HBM32G003_GPIO_H__
#define	__HBM32G003_GPIO_H__

#include "HBM32G003.h"

//����  GPIOA  
#define IS_GPIO_ALL(GPIO) (((GPIO) == GPIOA))
    
#define GPIO_PIN0                  0             //����0
#define GPIO_PIN1                  1             //����1
#define GPIO_PIN2                  2             //����2
#define GPIO_PIN3                  3             //����3
#define GPIO_PIN4                  4             //����4
#define GPIO_PIN5                  5             //����5
#define GPIO_PIN6                  6             //����6
#define GPIO_PIN7                  7             //����7
#define GPIO_PIN8                  8             //����8
#define GPIO_PIN9                  9             //����9
#define GPIO_PIN10                 10            //����10
#define GPIO_PIN11                 11            //����11
#define GPIO_PIN12                 12            //����12
#define GPIO_PIN13                 13            //����13
#define GPIO_PIN14                 14            //����14
#define GPIO_PIN15                 15            //����15

#define IS_GPIOA_PIN(PIN)   (((PIN) == GPIO_PIN0)  || ((PIN) == GPIO_PIN1)  ||  \
                             ((PIN) == GPIO_PIN2)  || ((PIN) == GPIO_PIN3)  ||  \
							 ((PIN) == GPIO_PIN4)  || ((PIN) == GPIO_PIN5)  ||  \
							 ((PIN) == GPIO_PIN6)  || ((PIN) == GPIO_PIN7)  ||  \
							 ((PIN) == GPIO_PIN8)  || ((PIN) == GPIO_PIN9)  ||  \
							 ((PIN) == GPIO_PIN10) || ((PIN) == GPIO_PIN11) ||  \
							 ((PIN) == GPIO_PIN12) || ((PIN) == GPIO_PIN13) ||  \
							 ((PIN) == GPIO_PIN14) || ((PIN) == GPIO_PIN15) )

typedef enum
{ 
	MODE_FLOATING_IN = 0x00,    // ��������
	MODE_PU_IN =       0x01,    // ��������
	MODE_PD_IN =       0x02,    // ��������
	MODE_PP_OUT =      0x03,    // �������
	MODE_OD_OUT =      0x04,    // ��©���
} Mode_TypeDef;

//����  GPIOģʽ
#define IS_GPIO_MODE(MODE) (((MODE) == MODE_FLOATING_IN) || ((MODE) == MODE_PU_IN)  || \
                            ((MODE) == MODE_PD_IN)       || ((MODE) == MODE_PP_OUT) || \
                            ((MODE) == MODE_OD_OUT) )

typedef enum
{ 
	WAKEUP_DISABLE =  0x00,    // ��ֹ����
	WAKEUP_ENABLE =   0x01,    // ʹ�ܻ���
} WakeUpEn_TypeDef;

//����  GPIO����ʹ��
#define IS_GPIO_WAKEUP(WAKEUP) (((WAKEUP) == WAKEUP_DISABLE) || ((WAKEUP) == WAKEUP_ENABLE))


typedef struct
{            
    uint8_t              Pin;               //���ź�                      
    Mode_TypeDef         Mode;              //ģʽ
	WakeUpEn_TypeDef     WakeUp_En;         //����ʹ��
} GPIO_InitTypeDef;

void GPIO_Init(GPIO_TypeDef * GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);        //GPIO��ʼ��

void GPIO_SetBit(GPIO_TypeDef * GPIOx, uint32_t GPIO_Pin);						//������ָ�������ŵ�ƽ�ø�
void GPIO_ClrBit(GPIO_TypeDef * GPIOx, uint32_t GPIO_Pin);						//������ָ�������ŵ�ƽ�õ�
void GPIO_InvBit(GPIO_TypeDef * GPIOx, uint32_t GPIO_Pin);						//������ָ�������ŵ�ƽ��ת
uint32_t GPIO_GetBit(GPIO_TypeDef * GPIOx, uint32_t GPIO_Pin);					//��ȡ����ָ�������ŵĵ�ƽ״̬

#endif //__HBM32G003_GPIO_H__
