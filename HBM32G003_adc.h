#ifndef __HBM32G003_ADC_H__
#define __HBM32G003_ADC_H__

#include "HBM32G003.h"



#define ADC_CH0		0x01
#define ADC_CH1		0x02
#define ADC_CH2		0x04
#define ADC_CH3		0x08
#define ADC_CH4		0x10
#define ADC_CH5		0x20
#define ADC_CH6		0x40
#define ADC_CH7		0x80
#define ADC_CH8		0x100


typedef enum
{ 
	CLK_DIV_1 =  0x00,       //ADCʱ����ϵͳʱ��1��Ƶ
	CLK_DIV_2 =  0x01,       //ADCʱ����ϵͳʱ��2��Ƶ
    CLK_DIV_4 =  0x02,       //ADCʱ����ϵͳʱ��4��Ƶ
	CLK_DIV_8 =  0x03        //ADCʱ����ϵͳʱ��8��Ƶ
} ADC_Clk_Div_TypeDef;

typedef enum
{ 
	SAMP_AVG_1 =  0x00,       //1�β���ȡƽ��
	SAMP_AVG_2 =  0x01,       //2�β���ȡƽ��
    SAMP_AVG_4 =  0x02,       //4�β���ȡƽ��
	SAMP_AVG_8 =  0x03        //8�β���ȡƽ��
} ADC_SampAvg_TypeDef;


typedef enum
{
	SAMP_MODE_SINGLE    =  0x00,   //ADC���β���
	SAMP_MODE_CONTINUE  =  0x01    //ADC��������
} ADC_Samp_Mode_TypeDef;


typedef enum
{ 
	MODE_FIFO =  0x00,       //ADC���ݴ洢ΪFIFOģʽ
	MODE_CHAN =  0x01        //ADC���ݴ洢Ϊͨ��ģʽ
} ADC_Mode_TypeDef;


typedef enum
{
	SAMP_CLK_EXT =  0x00,    //ADC�����ⲿ����ʱ�ӷ�ʽ
	SAMP_CLK_IN  =  0x01     //ADC�����ڲ�����ʱ�ӷ�ʽ
} ADC_Samp_Clk_TypeDef;


typedef enum
{
	EXTSAMP_CLKWIN_1   =  0x00,   //�ⲿ����ʱ�ӷ�ʽ��������1*CLK
	EXTSAMP_CLKWIN_2   =  0x01,   //�ⲿ����ʱ�ӷ�ʽ��������2*CLK
	EXTSAMP_CLKWIN_4   =  0x02,   //�ⲿ����ʱ�ӷ�ʽ��������4*CLK
	EXTSAMP_CLKWIN_8   =  0x03,   //�ⲿ����ʱ�ӷ�ʽ��������8*CLK
	EXTSAMP_CLKWIN_16  =  0x04,   //�ⲿ����ʱ�ӷ�ʽ��������16*CLK
	EXTSAMP_CLKWIN_32  =  0x05,   //�ⲿ����ʱ�ӷ�ʽ��������32*CLK
	EXTSAMP_CLKWIN_64  =  0x06,   //�ⲿ����ʱ�ӷ�ʽ��������64*CLK
	EXTSAMP_CLKWIN_128 =  0x07    //�ⲿ����ʱ�ӷ�ʽ��������128*CLK
} ExtSamp_ClkWin_TypeDef;

typedef enum
{
	INSAMP_CLKWIN_1  =  0x00,   //�ڲ�����ʱ�ӷ�ʽ��������1*CLK
	INSAMP_CLKWIN_3  =  0x01,   //�ڲ�����ʱ�ӷ�ʽ��������3*CLK
	INSAMP_CLKWIN_5  =  0x02,   //�ڲ�����ʱ�ӷ�ʽ��������5*CLK
	INSAMP_CLKWIN_7  =  0x03,   //�ڲ�����ʱ�ӷ�ʽ��������7*CLK
	INSAMP_CLKWIN_9  =  0x04,   //�ڲ�����ʱ�ӷ�ʽ��������9*CLK
	INSAMP_CLKWIN_11 =  0x05,   //�ڲ�����ʱ�ӷ�ʽ��������11*CLK
	INSAMP_CLKWIN_13 =  0x06,   //�ڲ�����ʱ�ӷ�ʽ��������13*CLK
	INSAMP_CLKWIN_15 =  0x07    //�ڲ�����ʱ�ӷ�ʽ��������15*CLK
} InSamp_ClkWin_TypeDef;


typedef enum
{
	VREF_EXT =  0x00,        //ADC�����ⲿ�ο�ʱ��
	VREF_IN  =  0x01         //ADC�����ڲ��ο�ʱ��
} ADC_Vref_TypeDef;


typedef enum
{
	TRIG_CPU  =  0x00,        //ADCѡ��CPU��������
	TRIG_EXT  =  0x01         //ADCѡ���ⲿ�źŴ�������
} ADC_Trig_TypeDef;


#define ADC_EXTTRIG_NOSIGNAL       0x00
#define ADC_EXTTRIG_PWMPLUS_TRIG0  0x01
#define ADC_EXTTRIG_PWMPLUS_TRIG1  0x02
#define ADC_EXTTRIG_PWMPLUS_TRIG2  0x04
#define ADC_EXTTRIG_PWMPLUS_TRIG3  0x08
#define ADC_EXTTRIG_TIMPLUS_LOW    0x10
#define ADC_EXTTRIG_TIMPLUS_HIGH   0x20


//����ADCʱ�ӷ�Ƶϵ��
#define IS_ADC_CLKDIV(ADC_CLKDIV)  (((ADC_CLKDIV) >= CLK_DIV_1) && ((ADC_CLKDIV) <= CLK_DIV_8))

//����ADCͨ��
#define IS_ADC_CH(ADC_CH)  (((ADC_CH) == ADC_CH0) || ((ADC_CH) == ADC_CH1) ||  \
                            ((ADC_CH) == ADC_CH2) || ((ADC_CH) == ADC_CH3) ||  \
							((ADC_CH) == ADC_CH4) || ((ADC_CH) == ADC_CH5) ||  \
							((ADC_CH) == ADC_CH6) || ((ADC_CH) == ADC_CH7) ||  \
                             (ADC_CH) == ADC_CH8) )

//����ADC����ȡƽ��
#define IS_ADC_SAMP_AVG(ADC_SAMP_AVG)  (((ADC_SAMP_AVG) >= SAMP_AVG_1) && ((ADC_SAMP_AVG) <= SAMP_AVG_8))

//����ADC����ģʽ
#define IS_ADC_SAMP_MODE(ADC_SAMP_MODE)  (((ADC_SAMP_MODE) == SAMP_MODE_SINGLE) || ((ADC_SAMP_MODE) == SAMP_MODE_CONTINUE))

//����ADCģʽ
#define IS_ADC_MODE(ADC_MODE)  (((ADC_MODE) == MODE_FIFO) || ((ADC_MODE) == MODE_CHAN))

//����ADC����ʱ��
#define IS_ADC_SAMP_CLOCK(ADC_SAMP_CLOCK)   (ADC_SAMP_CLOCK == SAMP_CLK_EXT || ADC_SAMP_CLOCK == SAMP_CLK_IN)

//����ADC�ⲿ����ʱ�Ӵ���
#define IS_ADC_EXTSAMP_CLKWIN(ADC_EXTSAMP_CLKWIN)  (ADC_EXTSAMP_CLKWIN >= EXTSAMP_CLKWIN_1 || ADC_EXTSAMP_CLKWIN <= EXTSAMP_CLKWIN_128)

//����ADC�ڲ�����ʱ�Ӵ���
#define IS_ADC_INSAMP_CLKWIN(ADC_INSAMP_CLKWIN)  (ADC_INSAMP_CLKWIN >= INSAMP_CLKWIN_1 || ADC_INSAMP_CLKWIN <= INSAMP_CLKWIN_15)

//����ADC�ο�Դѡ��
#define IS_ADC_VREF(ADC_VREF)  (ADC_VREF == VREF_EXT || ADC_VREF == VREF_IN)

//����ADCVDD���ʹ�ܳ���
#define IS_ADC_VDDOPEN(ADC_VDDOPEN)     (((ADC_VDDOPEN) == ENABLE) || ((ADC_VDDOPEN) == DISABLE))

//����ADC��offset����ʹ��
#define IS_ADC_OFFSET_EN(ADC_OFFSET_EN) (((ADC_OFFSET_EN) == ENABLE) || ((ADC_OFFSET_EN) == DISABLE))

//����ADC��kd����ʹ��
#define IS_ADC_KD_EN(ADC_KD_EN) (((ADC_KD_EN) == ENABLE) || ((ADC_KD_EN) == DISABLE))

//����ADC��ת������ж�ʹ��
#define IS_ADC_EOC_IEN(ADC_EOC_IEN) (((ADC_EOC_IEN) == ENABLE) || ((ADC_EOC_IEN) == DISABLE))

//����ADC��FIFO����ж�ʹ��
#define IS_ADC_FIFO_OVF_IEN(ADC_FIFO_OVF_IEN) (((ADC_FIFO_OVF_IEN) == ENABLE) || ((ADC_FIFO_OVF_IEN) == DISABLE))

//����ADC��FIFO�����ж�ʹ��
#define IS_ADC_FIFO_HALFFULL_IEN(ADC_FIFO_HALFFULL_IEN) (((ADC_FIFO_HALFFULL_IEN) == ENABLE) || ((ADC_FIFO_HALFFULL_IEN) == DISABLE))

//����ADC��FIFO���ж�ʹ��
#define IS_ADC_FIFO_FULL_IEN(ADC_FIFO_FULL_IEN) (((ADC_FIFO_FULL_IEN) == ENABLE) || ((ADC_FIFO_FULL_IEN) == DISABLE))




typedef struct {
	ADC_Clk_Div_TypeDef Clk_Div;		   //ADCת��ʱ�ӷ�Ƶ��ȡֵ1 2 4 8
	
	uint16_t Channels;		               //ADCת��ͨ��ѡ�У�ADC_CH0��ADC_CH1��... ... ��ADC_CH8������ϣ�������λ�����㣩
	
	ADC_SampAvg_TypeDef    SampAvg;	       //����ȡƽ������������ADCת����ADC��һ��ͨ��������������ת����Σ��������ǵ�ƽ��ֵ��Ϊ��ͨ��ת�����
	
	ADC_Samp_Mode_TypeDef  Samp_Mode;	   //���������ģʽ�£�1 ����ת��ģʽ��������һֱ������ת����ֱ��������STARTλ
							               //                  0 ����ת��ģʽ��ת����ɺ�STARTλ�Զ����ֹͣת��

	ADC_Mode_TypeDef Mode;                 //���ݴ洢ΪFIFOģʽ����ͨ��ģʽ   0: FIFO  1:ͨ��
	
	ADC_Samp_Clk_TypeDef   SampClk;        //ADC����ʱ��ѡ��  1:�ڲ�����ʱ��   0:�ⲿ����ʱ��
	
	ExtSamp_ClkWin_TypeDef ExtSamp_ClkWin; //�ⲿ������������
	
	InSamp_ClkWin_TypeDef  InSamp_ClkWin;  //�ڲ�������������
	
	FunctionalState Adcvdd_Open;           //ADC VDD���ʹ�ܳ���   0:ֻ��ͨ��8��Чʱ,ADC VDD���ʹ�ܲŴ�  1:ADC VDD���ʹ�ܳ���
	
	ADC_Vref_TypeDef Vref;                 //ADC�ο�Դѡ��  0:�ⲿ�ο�  1:�ڲ��ο�
	
	ADC_Trig_TypeDef Trig;                 //ADC����Դѡ��  0  CPU   1  �ⲿ�ź�
	
	uint8_t  ExtTrig_Sel;                  //�ⲿ�źŴ���Դѡ��
	
	FunctionalState Offset_En;             //offset����ʹ��   0:��ʹ��  1:ʹ��
	
	FunctionalState Kd_En;                 //kd����ʹ��       0:��ʹ��  1:ʹ��
	
	uint8_t Eoc_IEn;		               //EOC�ж�ʹ�ܣ������ÿ��ͨ�����ã�����ЧֵΪADC_CH0��ADC_CH1��... ... ��ADC_CH8������ϣ�������λ�����㣩
	
	FunctionalState Ovf_IEn;		       //FIFO ����ж�ʹ��
	
	FunctionalState HalfFull_IEn;	       //FIFO�����ж�ʹ��
	
	FunctionalState Full_IEn;		       //FIFO  ���ж�ʹ��
} ADC_InitStructure;



void ADC_Init(ADC_InitStructure * ADC_initStruct);  //ADCģ��ת������ʼ��
void ADC_Open(void);                                //ADC����
void ADC_Close(void);                               //ADC�ر�
void ADC_Start(void);                               //ADC����ת��
void ADC_Stop(void);                                //ADCֹͣת��
void ADC_SoftReset(void);                           //ADC��λ
uint16_t ADC_Read(uint32_t chn);                    //��ָ��ͨ����ȡת�����
void ADC_Read_FIFO(uint16_t * buffer,uint8_t num);  //��FIFO�Ĵ����ж�ȡת�����
uint8_t ADC_IsEOC(uint32_t chn);                    //ָ��ͨ���Ƿ�ת�����
void ADC_IntEOCEn(uint32_t chn);                    //ת������ж�ʹ��
void ADC_IntEOCDis(uint32_t chn);                   //ת������жϽ�ֹ
uint8_t ADC_IntEOCStat(uint32_t chn);               //ת������ж�״̬
void ADC_IntEOCClr(uint32_t chn);                   //ת������жϱ�־���
uint8_t ADC_FIFO_Level(void);                       //��ȡFIFOˮλ
uint8_t ADC_FULLStat(void);                         //FIFO��״̬
uint8_t ADC_HALFFULLStat(void);                     //FIFO����״̬
uint8_t ADC_EMPTYStat(void);                        //FIFO��״̬
uint8_t ADC_OVFStat(void);                          //FIFO���״̬
void ADC_IntFULLEn(void);                           //FIFO���ж�ʹ��
void ADC_IntFULLDis(void);                          //FIFO���жϽ�ֹ
uint8_t ADC_IntFULLStat(void);                      //FIFO���ж�״̬
void ADC_IntFULLClr(void);                          //FIFO���ж�״̬���
void ADC_IntHALFFULLEn(void);                       //FIFO�����ж�ʹ��
void ADC_IntHALFFULLDis(void);                      //FIFO�����жϽ�ֹ
uint8_t ADC_IntHALFFULLStat(void);                  //FIFO�����ж�״̬
void ADC_IntHALFFULLClr(void);                      //FIFO�����ж�״̬���
void ADC_IntOVFEn(void);                            //FIFO����ж�ʹ��
void ADC_IntOVFDis(void);                           //FIFO����жϽ�ֹ
uint8_t ADC_IntOVFStat(void);                       //FIFO����ж�״̬
void ADC_IntOVFClr(void);                           //FIFO����ж�״̬���


#endif //__HBM32G003_ADC_H__
