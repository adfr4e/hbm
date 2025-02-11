#ifndef __HBM32G003_FLASH_H__
#define __HBM32G003_FLASH_H__

#include "HBM32G003.h"

#define FLASH_WriteEnable         0x00          //дʹ��
#define FLASH_WriteDisable        0x01          //д��ֹ
#define FLASH_DeepPowerDown       0x02          //����͹���ģʽ
#define FLASH_RelDeepPowerDown    0x03          //�˳��͹���ģʽ
#define FLASH_ReadManDeviceID     0x04          //��ȡFLASH����ID��
#define FLASH_ReadDeviceID        0x05          //��ȡFLASH�豸ID��
#define FLASH_WriteStatusReg	  0x06          //д״̬�Ĵ���
#define FLASH_ReadStatusRegL	  0x07          //��״̬�Ĵ����Ͱ�λ
#define FLASH_ReadStatusRegH	  0x08          //��״̬�Ĵ����߰�λ
#define FLASH_PageErase	          0x09          //ҳ����
#define FLASH_SectorErase	      0x0A          //��������
#define FLASH_SinglePageProgram	  0x0B          //���߱��
#define FLASH_DualPageProgram	  0x0C          //˫�߱��
#define FLASH_QuadPageProgram	  0x0D          //���߱��
#define FLASH_ReadData            0x0E          //������   ���߶�  ˫�߶�  ���߶�  ȡ����RD_MD�Ĵ�������


#define FLASH_SingleReadData      0x00          //���߶�
#define FLASH_DualReadData        0x01          //˫�߶�
#define FLASH_QuadReadData        0x02          //���߶�


#define FLASH_CLKDIV_8            0x00          //ʱ��8��Ƶ
#define FLASH_CLKDIV_4            0x01          //ʱ��4��Ƶ
#define FLASH_CLKDIV_2            0x02          //ʱ��2��Ƶ
#define FLASH_CLKDIV_1            0x03          //ʱ��1��Ƶ

#define FLASH_DATA_ADDR     0x41000000          //FLASH��ַ


//����  FLASH��ģʽ 
#define IS_FLASH_READMODE(READMODE) (((READMODE) == FLASH_SingleReadData) || ((READMODE) == FLASH_DualReadData) || ((READMODE) == FLASH_QuadReadData))

//����  FLASHʱ�ӷ�Ƶ
#define IS_FLASH_CLKDIV(CLKDIV)     (((CLKDIV) == FLASH_CLKDIV_8) || ((CLKDIV) == FLASH_CLKDIV_4) ||   \
									 ((CLKDIV) == FLASH_CLKDIV_2) || ((CLKDIV) == FLASH_CLKDIV_1) )
//����   FLASH������
#define IS_FLASH_COMMAND(COMMAND)   ((COMMAND >= FLASH_WriteEnable) && (COMMAND <= FLASH_ReadData))

//����  FLASH��������
#define IS_FLASH_ERASE(ERASE)       ((ERASE == FLASH_PageErase) || (ERASE == FLASH_SectorErase))

//����  FLASHд����
#define IS_FLASH_WRITE(WRITE)       ((WRITE == FLASH_SinglePageProgram) || (WRITE == FLASH_DualPageProgram)|| (WRITE == FLASH_QuadPageProgram))




void FLASH_Init(uint8_t Read_Mode,uint8_t ClkDiv);      //FLASH��ʼ��
void FLASH_Write_Command(uint8_t cmd);                  //FLASHд����
uint8_t FLASH_Check_Busy(void);                         //FLASH��������æ��־
void FLASH_Prog_Predata_End(void);                      //FLASH����������ʱ,���ݼĴ�����Ч��־��ѯ
void FLASH_Prog_Predata_End(void);                      //FLASHҳ��̲���Ԥ������������
void FLASH_Command_Start(void);                         //FLASH������������
void FLASH_Write_Enable(void);                          //FLASHдʹ������

void FLASH_Set_DeepPowerDown(void);                     //FLASH����͹�������
void FLASH_ReSet_DeepPowerDown(void);                   //FLASH�˳��͹�������

void FLASH_Wait_WIP(void);                              //FLASH�ȴ��������
void FLASH_Erase_Command(uint8_t erase,uint32_t addr);  //FLASH��������
void FLASH_Quad_Enable(void);                           //FLASH ����ģʽʹ��
void FLASH_Write_Word(uint8_t cmd,uint32_t addr,uint32_t data);    //FLASHд������   
uint8_t FLASH_Write_Words(uint8_t cmd,uint32_t addr,uint32_t data[],uint32_t num);   //FLASHд�����   
uint32_t FLASH_Read_Word_1(uint8_t cmd,uint32_t addr);  //FLASH��������  
uint32_t FLASH_Read_Word_2(uint32_t addr);              //FLASH��������  

#endif //__HBM32G003_FLASH_H__
