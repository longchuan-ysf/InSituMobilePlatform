/********************************************************************************
								XXX公司
龙川
2020.09.30
实际每页每个控件的功能实现
*********************************************************************************/
#include "Delay.h"
#include "hmi_driver.h"
#include "hmi_user_uart.h"
#include "cmd_queue.h"
#include "cmd_process.h"
#include "hmi_app.h"
#include "hmi_functionHandle.h"
#include "hmi_WidgetHandle.h"
#include "STM32Fxxx.h"
#include "PlatformManage.h"
#include "fun.h"
#include "GPIO_manager.h"
#include "UserVars.h"	
#include "OSVars.h"
#include "motor.h"

void Screen1_Widget_Handle_para(uint8_t *para)
{
	PCTRL_MSG msg = (PCTRL_MSG)para;
	uint16 control_id = PTR2U16(&msg->control_id);	//控件ID
	uint8 * param = msg->param;
	uint8 button_state;
	switch(control_id)
	{
		case 3:
		{
			button_state=param[1];
			if(button_state)
			{
				ManageFlag.StartXFlag = 1;
				ManageFlag.StartXDir = Dir_Foreward;
			}

		}
		break;
		case 4:
		{
			button_state=param[1];
			if(button_state)
			{
				ManageFlag.StartXFlag = 2;
				ManageFlag.StartXDir = Dir_Backward;
			}

		}
		break;
		
		default:
			break;
	}

}
//每个控件具体执行函数数组
WidgetHandleStruct HMI_widget_handle_array[]=
{
	/*页面编号	控件编号		刷新函数			参数处理函数*/
	{1,			3,			NULL,			Screen1_Widget_Handle_para},
	{1,			4,			NULL,			Screen1_Widget_Handle_para},
	
};
/**
****************************************************************************************
@brief:   hmi_GetWidgetArraySize
@Input：  NULL
@Output： NULL
@Return   NULL.
@Warning: NULL
@note:  获取控件处理函数指针数
****************************************************************************************
 **/
uint16_t hmi_GetWidgetArraySize(void)
{
	//因为是 extern WidgetHandle HMI_widget_handle_array[]; 没有给定具体大小
	//所以文件外面使用这个语句会报错
	return sizeof(HMI_widget_handle_array)/sizeof(WidgetHandleStruct);
}

/**
****************************************************************************************
@brief:   HMI_Screen0_Initial
@Input：  NULL
@Output： NULL
@Return   NULL.
@Warning: NULL
@note:  页面0 初始化函数 也是页面0的刷新函数
****************************************************************************************
 **/
void HMI_Screen0_Initial(void)
{
	
	
	
}
/**
****************************************************************************************
@brief:   HMI_Screen1_Initial
@Input：  NULL
@Output： NULL
@Return   NULL.
@Warning: NULL
@note:  页面0 初始化函数
****************************************************************************************
 **/
void HMI_Screen1_Initial(void)
{

	
}

/**
****************************************************************************************
@brief:   HMI_Screen0_Initial
@Input：  NULL
@Output： NULL
@Return   NULL.
@Warning: NULL
@note:  页面0 初始化函数
****************************************************************************************
 **/
void HMI_Screen2_Initial(void)
{
	
}

/**
****************************************************************************************
@brief:   HMI_Screen0_Initial
@Input：  NULL
@Output： NULL
@Return   NULL.
@Warning: NULL
@note:  页面0 初始化函数
****************************************************************************************
 **/
PageInitStruct HMI_page_init_array[]=
{
	{0,HMI_Screen0_Initial},
	{1,HMI_Screen1_Initial},
	{2,HMI_Screen2_Initial},
};

/**
****************************************************************************************
@brief:   hmi_GetPageArraySize
@Input：  NULL
@Output： NULL
@Return   NULL.
@Warning: NULL
@note:  获取控件处理函数指针数
****************************************************************************************
 **/
uint16_t hmi_GetPageArraySize(void)
{
	return sizeof(HMI_page_init_array)/sizeof(PageInitStruct);
}