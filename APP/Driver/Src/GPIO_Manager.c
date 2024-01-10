/*************************************************************************************************** 
                                   xxxx��˾
  
                  

�ļ�:   GPIO_Manager.c 
����:   ����
˵��:   ���������������IO����
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
* Description: ��ȡDI������ֵ;
* 
* Input:  IOx, ������DIӳ��Ĺ���ö��
*
* Output: none;
*          		
* Return: IOx�ǵ���IO�˿ڣ�����ֵ��1,�ߵ�ƽ, ��0,�͵�ƽ; 
*
* Note:   �������ֵ��0x80000000, ���ʾ����
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
* Description: ��ȡDO�����ֵ;
* 
* Input:  IOx, ������DOӳ��Ĺ���ö��
*
* Output: none;
*          		
* Return: IOx�ǵ���IO�˿ڣ�����ֵ��1,�ߵ�ƽ, ��0,�͵�ƽ; 
*
* Note:   �������ֵ��0x80000000, ���ʾ���� ʵ���Ҳ²�Ӧ�ö��Ƕ�GPIOx_ODR�Ĵ���
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
* Description: д��IO���ֵ;
* 
* Input:  IOx,������Doӳ��Ĺ���ö��  Dval, 1����ߵ�ƽ, 0,����͵�ƽ; 
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
* Description: IO�������;
* 
* Input:  IOx, IOx,������Doӳ��Ĺ���ö��
*		  Cmd, IO��������: 
*              CMD_IO_NEG,   IOȡ��; ����ParaΪ0
*              CMD_IO_ON_T,  IO��1����ʱһ��ʱ������0; ����ParaΪ��ʱʱ��,��λms;
*              CMD_IO_OFF_T, IO��0����ʱһ��ʱ������1; ����ParaΪ��ʱʱ��,��λms;
*              CMD_IO_RST,   ��λIO�Ĵ���Ϊ��ʼ״̬; ����ParaΪ0; ��ʱIOxӦ��PA/PB/PC/PD/PE/PF/PG/PH/PI
*              CMD_IO_CLOSE, �ر�IOʱ��,Ҳ���ǹر�DAC����,����ʡ��; ����ParaΪ0; ��ʱIOxӦ��PA/PB/PC/PD/PE/PF/PG/PH/PI
*         Para, �������;
*
* Output: none;
*          		
* Return: ERR_TRUE,�����ɹ�; ����ֵ, �μ�const.h�д������;
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