#ifndef __HBM32G003_FLASH_H__
#define __HBM32G003_FLASH_H__

#include "HBM32G003.h"

#define FLASH_WriteEnable         0x00          //写使能
#define FLASH_WriteDisable        0x01          //写禁止
#define FLASH_DeepPowerDown       0x02          //进入低功耗模式
#define FLASH_RelDeepPowerDown    0x03          //退出低功耗模式
#define FLASH_ReadManDeviceID     0x04          //读取FLASH厂家ID号
#define FLASH_ReadDeviceID        0x05          //读取FLASH设备ID号
#define FLASH_WriteStatusReg	  0x06          //写状态寄存器
#define FLASH_ReadStatusRegL	  0x07          //读状态寄存器低八位
#define FLASH_ReadStatusRegH	  0x08          //读状态寄存器高八位
#define FLASH_PageErase	          0x09          //页擦除
#define FLASH_SectorErase	      0x0A          //扇区擦除
#define FLASH_SinglePageProgram	  0x0B          //单线编程
#define FLASH_DualPageProgram	  0x0C          //双线编程
#define FLASH_QuadPageProgram	  0x0D          //四线编程
#define FLASH_ReadData            0x0E          //读操作   单线读  双线读  四线读  取决于RD_MD寄存器配置


#define FLASH_SingleReadData      0x00          //单线读
#define FLASH_DualReadData        0x01          //双线读
#define FLASH_QuadReadData        0x02          //四线读


#define FLASH_CLKDIV_8            0x00          //时钟8分频
#define FLASH_CLKDIV_4            0x01          //时钟4分频
#define FLASH_CLKDIV_2            0x02          //时钟2分频
#define FLASH_CLKDIV_1            0x03          //时钟1分频

#define FLASH_DATA_ADDR     0x41000000          //FLASH基址


//断言  FLASH读模式 
#define IS_FLASH_READMODE(READMODE) (((READMODE) == FLASH_SingleReadData) || ((READMODE) == FLASH_DualReadData) || ((READMODE) == FLASH_QuadReadData))

//断言  FLASH时钟分频
#define IS_FLASH_CLKDIV(CLKDIV)     (((CLKDIV) == FLASH_CLKDIV_8) || ((CLKDIV) == FLASH_CLKDIV_4) ||   \
									 ((CLKDIV) == FLASH_CLKDIV_2) || ((CLKDIV) == FLASH_CLKDIV_1) )
//断言   FLASH命令码
#define IS_FLASH_COMMAND(COMMAND)   ((COMMAND >= FLASH_WriteEnable) && (COMMAND <= FLASH_ReadData))

//断言  FLASH擦除命令
#define IS_FLASH_ERASE(ERASE)       ((ERASE == FLASH_PageErase) || (ERASE == FLASH_SectorErase))

//断言  FLASH写命令
#define IS_FLASH_WRITE(WRITE)       ((WRITE == FLASH_SinglePageProgram) || (WRITE == FLASH_DualPageProgram)|| (WRITE == FLASH_QuadPageProgram))




void FLASH_Init(uint8_t Read_Mode,uint8_t ClkDiv);      //FLASH初始化
void FLASH_Write_Command(uint8_t cmd);                  //FLASH写命令
uint8_t FLASH_Check_Busy(void);                         //FLASH检查控制器忙标志
void FLASH_Prog_Predata_End(void);                      //FLASH编程命令操作时,数据寄存器有效标志查询
void FLASH_Prog_Predata_End(void);                      //FLASH页编程操作预置数结束控制
void FLASH_Command_Start(void);                         //FLASH命令启动控制
void FLASH_Write_Enable(void);                          //FLASH写使能命令

void FLASH_Set_DeepPowerDown(void);                     //FLASH进入低功耗命令
void FLASH_ReSet_DeepPowerDown(void);                   //FLASH退出低功耗命令

void FLASH_Wait_WIP(void);                              //FLASH等待操作完成
void FLASH_Erase_Command(uint8_t erase,uint32_t addr);  //FLASH擦除命令
void FLASH_Quad_Enable(void);                           //FLASH 四线模式使能
void FLASH_Write_Word(uint8_t cmd,uint32_t addr,uint32_t data);    //FLASH写单个字   
uint8_t FLASH_Write_Words(uint8_t cmd,uint32_t addr,uint32_t data[],uint32_t num);   //FLASH写多个字   
uint32_t FLASH_Read_Word_1(uint8_t cmd,uint32_t addr);  //FLASH读单个字  
uint32_t FLASH_Read_Word_2(uint32_t addr);              //FLASH读单个字  

#endif //__HBM32G003_FLASH_H__
