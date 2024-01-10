/*************************************************************************************************** 
                                   xxxx公司
  
                  

文件:   GPIO_Manager.c 
作者:   龙川
说明:   输出控制与输入检测IO管理
***************************************************************************************************/
#include "GPIO_manager.h"
#include "EMB8628I_IOConfig.h"

IOMapping_TypeDef OutputIO[] = 
{
	{StirPUL,DO9}
};

IOMapping_TypeDef InputIO[] = 
{
	{Limiter,DI9},
	{Raster,DI10},
};

/******************************************************************************************************************
* Function: IOFunction_Read;
*
* Description: 读取DI的输入值;
* 
* Input:  IOx, 板子上DI映射的功能枚举
*
* Output: none;
*          		
* Return: IOx是单独IO端口：返回值是1,高电平, 是0,低电平; 
*
* Note:   如果返回值是0x80000000, 则表示出错
*******************************************************************************************************************/
uint32_t IOFunction_Read(cookerDI IOx)
{
	uint8_t i;
	for(i=0; i<CookerDIMax; i++)
	{
		if(IOx == InputIO[i].IOFunction)
		{
			return IO_Read(InputIO[i].IO);
		}
	}
}

/******************************************************************************************************************
* Function: IOFunction_Read;
*
* Description: 读取DO的输出值;
* 
* Input:  IOx, 板子上DO映射的功能枚举
*
* Output: none;
*          		
* Return: IOx是单独IO端口：返回值是1,高电平, 是0,低电平; 
*
* Note:   如果返回值是0x80000000, 则表示出错 实际我猜测应该都是读GPIOx_ODR寄存器
*******************************************************************************************************************/
uint32_t IOFunction_ReadDO(cookerDO IOx)
{
	uint8_t i;
	for(i=0; i<CookerDOMax; i++)
	{
		if(IOx == OutputIO[i].IOFunction)
		{
			return IO_Read(OutputIO[i].IO);
		}
	}
}

/******************************************************************************************************************
* Function: IO_Write;
*
* Description: 写入IO输出值;
* 
* Input:  IOx,板子上Do映射的功能枚举  Dval, 1输出高电平, 0,输出低电平; 
*         
* Output: none;
*          		
* Return: none;
*
* Note:   none;
*******************************************************************************************************************/
void IOFunction_Write(cookerDO IOx, uint16_t val)
{
	uint8_t i;
	for(i=0; i<CookerDOMax; i++)
	{
		if(IOx == OutputIO[i].IOFunction)
		{
			IO_Write(OutputIO[i].IO,val);
			return;
		}
	}
}
/******************************************************************************************************************
* Function: IO_Ctrl;
*
* Description: IO命令控制;
* 
* Input:  IOx, IOx,板子上Do映射的功能枚举
*		  Cmd, IO控制命令: 
*              CMD_IO_NEG,   IO取反; 参数Para为0
*              CMD_IO_ON_T,  IO置1后并延时一段时间再置0; 参数Para为延时时间,单位ms;
*              CMD_IO_OFF_T, IO置0后并延时一段时间再置1; 参数Para为延时时间,单位ms;
*              CMD_IO_RST,   复位IO寄存器为初始状态; 参数Para为0; 此时IOx应该PA/PB/PC/PD/PE/PF/PG/PH/PI
*              CMD_IO_CLOSE, 关闭IO时钟,也就是关闭DAC功能,可以省电; 参数Para为0; 此时IOx应该PA/PB/PC/PD/PE/PF/PG/PH/PI
*         Para, 命令参数;
*
* Output: none;
*          		
* Return: ERR_TRUE,操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
*******************************************************************************************************************/
int32_t IOFunction_Ctrl(cookerDO IOx, uint8_t Cmd, uint32_t Para)
{
	uint8_t i;
	for(i=0; i<CookerDOMax; i++)
	{
		if(IOx == OutputIO[i].IOFunction)
		{
			return IO_Ctrl(OutputIO[i].IO,Cmd,Para);

		}
	}
}