#include "HBM32G003_flash.h"

/****************************************************************************************************************************************** 
* 函数名称: FLASH_Init()
* 功能说明:	FLASH初始化
* 输    入: uint8_t Read_Mode  读模式配置    0:单线读  1: 2线读  2: 4线读	   
*			uint8_t ClkDiv     时钟分频配置  0: 8分频  1: 4分频  2: 2分频   3:  1分频
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void FLASH_Init(uint8_t Read_Mode,uint8_t ClkDiv)
{
	uint32_t temp = 0;
	
	assert_param(IS_FLASH_READMODE(Read_Mode));               //检查输入的参数Read_Mode是否合法   
	assert_param(IS_FLASH_CLKDIV(ClkDiv));                    //检查输入的参数ClkDiv是否合法  
	
	temp = FLASH->CFG;
	
	temp &= ~(0x03 << FLASH_CFG_READMODE_POS);
	temp |=  (Read_Mode << FLASH_CFG_READMODE_POS);
	
	temp &= ~(0x03 << FLASH_CFG_CLKDIV_POS);
	temp |=  (ClkDiv << FLASH_CFG_CLKDIV_POS);
	
	FLASH->CFG = temp;
	
	FLASH_Quad_Enable();
}


/****************************************************************************************************************************************** 
* 函数名称: FLASH_Write_Command()
* 功能说明:	FLASH写命令码
* 输    入: uint8_t cmd	   
*			
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void FLASH_Write_Command(uint8_t cmd)
{
	uint32_t temp = 0;
	
	assert_param(IS_FLASH_COMMAND(cmd));               //检查输入的参数cmd是否合法   
	
	temp = FLASH->CFG;
	
	temp &= ~(0x0F << FLASH_CFG_CMD_POS);
	temp |=  (cmd  << FLASH_CFG_CMD_POS);
	
	FLASH->CFG = temp;
}


/****************************************************************************************************************************************** 
* 函数名称: FLASH_Check_Busy()
* 功能说明:	FLASH检查控制器忙标志
* 输    入: 无   
*			
* 输    出: 1 :  控制器正在进行当前命令操作过程中，处于忙状态   0: 控制器处于空闲状态
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t FLASH_Check_Busy(void)
{
	if(FLASH->STATE & FLASH_STATE_BUSY_MSK)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/****************************************************************************************************************************************** 
* 函数名称: FLASH_Check_ProgramDataValid()
* 功能说明:	FLASH编程命令操作时,数据寄存器有效标志查询
* 输    入: 无   
*			
* 输    出: 1 :  编程命令操作时,数据寄存器还有数据没有发送完成,不能写入新的数据    0: 编程命令操作时,数据寄存器没有有效数据,可以写入新的数据
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t FLASH_Check_ProgramDataValid(void)
{
	if(FLASH->STATE & FLASH_STATE_PROG_VALID_MSK)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/****************************************************************************************************************************************** 
* 函数名称: FLASH_Prog_Predata_End()
* 功能说明:	FLASH页编程操作预置数结束控制
* 输    入: 无   
*			
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void FLASH_Prog_Predata_End(void)
{
	FLASH->START |= 0x01 << FLASH_START_PROG_END_POS;
}

/****************************************************************************************************************************************** 
* 函数名称: FLASH_Command_Start()
* 功能说明:	FLASH命令启动控制
* 输    入: 无   
*			
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void FLASH_Command_Start(void)
{
	FLASH->START |= 0x01 << FLASH_START_EN_POS;     //启动命令
	
	while(FLASH_Check_Busy());                      //检查控制器忙标志
}

/****************************************************************************************************************************************** 
* 函数名称: FLASH_Write_Enable()
* 功能说明:	FLASH写使能命令
* 输    入: 无   
*			
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void FLASH_Write_Enable(void)
{
	while(FLASH_Check_Busy());                     //检查控制器忙标志
	
	FLASH_Write_Command(FLASH_WriteEnable);        //写使能命令

	FLASH_Command_Start();                         //FLASH命令启动控制
}

/****************************************************************************************************************************************** 
* 函数名称: FLASH_Set_DeepPowerDown()
* 功能说明:	FLASH进入低功耗命令
* 输    入: 无   
*			
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void FLASH_Set_DeepPowerDown(void)
{
	while(FLASH_Check_Busy());                     //检查控制器忙标志
	
	FLASH_Write_Command(FLASH_DeepPowerDown);      //进入低功耗命令

	FLASH_Command_Start();                         //FLASH命令启动控制
}

/****************************************************************************************************************************************** 
* 函数名称: FLASH_ReSet_DeepPowerDown()
* 功能说明:	FLASH退出低功耗命令
* 输    入: 无   
*			
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void FLASH_ReSet_DeepPowerDown(void)
{
	while(FLASH_Check_Busy());                     //检查控制器忙标志
	
	FLASH_Write_Command(FLASH_RelDeepPowerDown);   //退出低功耗命令

	FLASH_Command_Start();                         //FLASH命令启动控制
}

/****************************************************************************************************************************************** 
* 函数名称: FLASH_Wait_WIP()
* 功能说明:	FLASH等待操作完成
* 输    入: 无   
*			
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void FLASH_Wait_WIP(void)
{
	uint8_t Rec = 1;
	
	while(Rec)
	{
		while(FLASH_Check_Busy());                     //检查控制器忙标志
	
		FLASH_Write_Command(FLASH_ReadStatusRegL);     //读状态寄存器低八位

		FLASH_Command_Start();                         //FLASH命令启动控制 
		
		Rec = FLASH->RDATA & 0x01;                     //读取寄存器数据,当数据为0时,表示操作完成
	}
}


/****************************************************************************************************************************************** 
* 函数名称: FLASH_Erase_Command()
* 功能说明:	FLASH擦除命令
* 输    入: uint8_t erase   FLASH PAGE ERASE    FLASH_SectorErase       
*	        uint32_t addr   擦除的首地址		
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void FLASH_Erase_Command(uint8_t erase,uint32_t addr)
{
	assert_param(IS_FLASH_ERASE(erase));           //检查输入的参数erase是否合法   
	
	FLASH_Write_Enable();                          //FLASH写使能命令
	
	FLASH->ADDR = addr>>2;                         //地址转换为以字为单位
	
	FLASH_Write_Command(erase);                    //FLASH PAGE ERASE  SECTOR ERASE  
	
	FLASH_Command_Start();                         //FLASH命令启动控制 
	
	FLASH_Wait_WIP();                              //FLASH等待操作完成
}

/****************************************************************************************************************************************** 
* 函数名称: FLASH_Quad_Enable()
* 功能说明:	FLASH 四线模式使能
* 输    入: 无  
*			
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void FLASH_Quad_Enable(void)
{
	FLASH_Write_Enable();                          //FLASH写使能命令
	
	FLASH->WDATA = 0x0200;                         //Quad_Enable
	
	while(FLASH_Check_Busy());                     //检查控制器忙标志
	
	FLASH_Write_Command(FLASH_WriteStatusReg);     //写状态寄存器    

	FLASH_Command_Start();                         //FLASH命令启动控制 
	
	FLASH_Wait_WIP();                              //FLASH等待操作完成
}


/****************************************************************************************************************************************** 
* 函数名称: FLASH_Write_Word()
* 功能说明:	FLASH写单个字   
* 输    入: uint8_t cmd    单线  两线  四线方式
*			uint32_t addr  地址
*           uint32_t data  数据
* 输    出: 无
* 注意事项: 无
******************************************************************************************************************************************/
void FLASH_Write_Word(uint8_t cmd,uint32_t addr,uint32_t data)
{
	assert_param(IS_FLASH_WRITE(cmd));           //检查输入的参数cmd是否合法   
	
	FLASH_Write_Enable();                          //FLASH写使能命令
	
	FLASH->ADDR = addr>>2;                         //地址转换为以字为单位
	
	FLASH_Write_Command(cmd);                      //FLASH写命令   FLASH_SinglePageProgram    FLASH_DualPageProgram    FLASH_QuadPageProgram  

	FLASH->START |= 0x01 << FLASH_START_EN_POS;    //启动命令
	
	while(FLASH_Check_ProgramDataValid());         //FLASH编程命令操作时,数据寄存器有效标志查询
	
	FLASH->WDATA = data;                           //将数据放到写数据寄存器中
	
	while(FLASH_Check_ProgramDataValid());         //FLASH编程命令操作时,数据寄存器有效标志查询
	
	FLASH_Prog_Predata_End();                      //FLASH页编程操作预置数结束控制
	
	while(FLASH_Check_Busy());                     //检查控制器忙标志
	
	FLASH_Wait_WIP();                              //FLASH等待操作完成	
}

/****************************************************************************************************************************************** 
* 函数名称: FLASH_Write_Words()
* 功能说明:	FLASH写多个字  
* 输    入: uint8_t cmd      单线  两线  四线方式
*			uint32_t addr    地址
*           uint32_t data[]  数据
*           uint32_t num     编程数量  以字为单位  不能超过64   也就是256字节
* 输    出: 0  编程成功   1  编程失败
* 注意事项: 无
******************************************************************************************************************************************/
uint8_t FLASH_Write_Words(uint8_t cmd,uint32_t addr,uint32_t data[],uint32_t num)
{
	uint32_t i = 0;
	
	assert_param(IS_FLASH_WRITE(cmd));           //检查输入的参数cmd是否合法   
	
	if(num > 64 || ((((addr%256) >>2)+ num) > 64))
	{
		return 1;
	}
	
	FLASH_Write_Enable();                          //FLASH写使能命令
	
	FLASH->ADDR = addr>>2;                         //地址转换为以字为单位
	
	FLASH_Write_Command(cmd);                      //FLASH写命令   FLASH_SinglePageProgram    FLASH_DualPageProgram    FLASH_QuadPageProgram  

	FLASH->START |= 0x01 << FLASH_START_EN_POS;    //启动命令
	
	for(i = 0;i < num;i++)
	{
		while(FLASH_Check_ProgramDataValid());     //FLASH编程命令操作时,数据寄存器有效标志查询
	
		FLASH->WDATA = data[i];                    //将数据放到写数据寄存器中
	}
	
	while(FLASH_Check_ProgramDataValid());         //FLASH编程命令操作时,数据寄存器有效标志查询
	
	FLASH_Prog_Predata_End();                      //FLASH页编程操作预置数结束控制
	
	while(FLASH_Check_Busy());                     //检查控制器忙标志
	
	FLASH_Wait_WIP();                              //FLASH等待操作完成	
	
	return 0;
}

/****************************************************************************************************************************************** 
* 函数名称: FLASH_Read_Word_1()
* 功能说明:	FLASH读单个字  
* 输    入: uint8_t cmd    单线  两线  四线方式
*			uint32_t addr  地址
* 输    出: 读到的数据
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t FLASH_Read_Word_1(uint8_t cmd,uint32_t addr)
{
	uint32_t temp = 0;
	
	assert_param(IS_FLASH_READMODE(cmd));              //检查输入的参数cmd是否合法   
	
	FLASH->ADDR = addr>>2;                             //地址转换为以字为单位
	
	temp = FLASH->CFG;
	
	temp &= ~(0x03 << FLASH_CFG_READMODE_POS);
	temp |=  (cmd << FLASH_CFG_READMODE_POS);          //单线读  双线读  四线读 
	
	FLASH->CFG = temp;
	
	FLASH_Write_Command(FLASH_ReadData);               //读操作   单线读  双线读  四线读  取决于RD_MD寄存器配置
	
	FLASH_Command_Start();                             //FLASH命令启动控制 
	
	return FLASH->RDATA;                               //返回读到的数据
}


/****************************************************************************************************************************************** 
* 函数名称: FLASH_Read_Word_2()
* 功能说明:	FLASH读单个字  
* 输    入: uint32_t addr  地址
* 输    出: 读到的数据
* 注意事项: 无
******************************************************************************************************************************************/
uint32_t FLASH_Read_Word_2(uint32_t addr)
{
	addr = (addr>>2)<<2;               //地址字对齐
	
	return *((volatile unsigned int *)(FLASH_DATA_ADDR + addr));    //读取该地址的数据
}



