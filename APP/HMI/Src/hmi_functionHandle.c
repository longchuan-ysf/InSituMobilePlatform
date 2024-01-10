/********************************************************************************
								XXX公司
龙川
2020.09.30
屏幕处理实际使用的一些中间函数处理
*********************************************************************************/

#include "hmi_WidgetHandle.h"
#include "hmi_functionHandle.h"
#include "Delay.h"
#include "hmi_driver.h"
#include "hmi_user_uart.h"
#include "cmd_queue.h"
#include "cmd_process.h"
#include "hmi_app.h"
#include "string.h"
#include "fun.h"
/**
****************************************************************************************
@brief:   hmi_widget_handle
@Input：  pageID    页面ID
		  widgetID  控件ID
		  widgetHandle 实际处理的函数指针数组的指针
		  size 这个数组的大小
		  para 是否带参数 ==NULL不带参数的显示函数 !=NULL使用带参数的显示函数
@Output： NULL
@Return   NULL.
@Warning: NULL
@note:  屏幕控件处理函数
****************************************************************************************
 **/
void hmi_widget_handle(uint16_t pageID, uint16_t widgetID, WidgetHandleStruct *widgetHandle, uint32_t size, uint8_t *para)
{
	uint16_t page, widget;
	uint16_t i = 0;

	void (*fun)(void) = 0;
	void (*fun_para)(uint8_t *) = 0;
	printf("%s,pageID=%d,widgetID=%d\r\n", __func__, pageID, widgetID);
	for (i = 0; i < size; i++)
	{
		if ((widgetHandle[i].page_num == pageID) && (widgetHandle[i].widget_num == widgetID))
		{
			printf("page_num=%d,widget_num=%d\r\n", widgetHandle[i].page_num, widgetHandle[i].widget_num);
			if (!para)
			{
				fun = widgetHandle[i].HMI_Widget_Handle;
				if (fun)
				{
					fun();
				}
			}
			else
			{
				fun_para = widgetHandle[i].HMI_Widget_Handle_para;
				if (fun_para)
				{
					fun_para(para);
				}
			}
			return;
		}
	}
}
/**
****************************************************************************************
@brief:   hmi_NotifyScreen
@Input：  pageID    页面ID
@Output： NULL
@Return   NULL.
@Warning: NULL
@note:  屏幕控件处理函数
****************************************************************************************
 **/
void hmi_NotifyScreen(uint16 screen_id)
{
	uint16_t i;
	HMI_Manager.curPageNum = screen_id;
	printf("%s,HMI_Manager.curPageNum = %d\r\n", __func__, HMI_Manager.curPageNum);

	// 调用初始化函数初始化界面
	for (i = 0; i < HMI_Manager.PageInitArraySize; i++)
	{
		if (HMI_Manager.PageInitial[i].page_num == screen_id)
		{
			if (HMI_Manager.PageInitial[i].HMI_Screen_Initial)
				HMI_Manager.PageInitial[i].HMI_Screen_Initial();
		}
	}
}
/**
****************************************************************************************
@brief:   hmi_GetCurPagenum
@Input：  NULL
@Output： page接收获取到的页面ID
@Return   0表示成功
		  其他非零也是出错.
@Warning: NULL
@note:   触摸屏数据接收解析及处理
****************************************************************************************
 **/
uint8_t hmi_GetCurPagenum(uint16_t *page) // 设置新的界面号
{

	GetScreen(0);
	return 0;
}
/**
****************************************************************************************
@brief:   hmi_rxtask_handle
@Input：  NULL
@Output： NULL
@Return   NULL.
@Warning: NULL
@note:   触摸屏数据接收解析及处理
****************************************************************************************
 **/
static uint8 cmd_buffer[CMD_MAX_SIZE];
void hmi_rxtask_handle(void)
{
	uint8_t i;
	qsize size = 0;
	PCTRL_MSG msg;
	uint8 cmd_type;	   // 指令类型
	uint8 ctrl_msg;	   // 消息的类型
	uint16 screen_id;  // 画面ID
	uint16 control_id; // 控件ID
	memset(cmd_buffer, 0, CMD_MAX_SIZE);
	size = queue_find_cmd(cmd_buffer, CMD_MAX_SIZE); // 从缓冲区中获取一条指令
	// 数据没有接收到
	if (!size)
		return;
	msg = (PCTRL_MSG)cmd_buffer;
	cmd_type = msg->cmd_type;
	ctrl_msg = msg->ctrl_msg;				// 消息的类型
	control_id = PTR2U16(&msg->control_id); // 控件ID
	screen_id = PTR2U16(&msg->screen_id);

	printf("rx hmi data len=%d,data=:\r\n", size);
	printf_Hexbuffer((uint8_t *)msg, size);

	switch (cmd_type)
	{
	case NOTIFY_TOUCH_PRESS:   // 触摸屏按下
	case NOTIFY_TOUCH_RELEASE: // 触摸屏松开
		break;
	case NOTIFY_WRITE_FLASH_OK: // 写FLASH成功
		// NotifyWriteFlash(1);
		break;
	case NOTIFY_WRITE_FLASH_FAILD: // 写FLASH失败
		// NotifyWriteFlash(0);
		break;
	case NOTIFY_READ_FLASH_OK: // 读取FLASH成功
		break;
	case NOTIFY_READ_FLASH_FAILD: // 读取FLASH失败
		break;
	case NOTIFY_READ_RTC: // 读取RTC时间
						  //  NotifyReadRTC(cmd_buffer[2],cmd_buffer[3],cmd_buffer[4],cmd_buffer[5],cmd_buffer[6],cmd_buffer[7],cmd_buffer[8]);
		break;
	case NOTIFY_CONTROL: // 控件信息通知，包括页面更替通知和控件内容变更通知
	{
		if (ctrl_msg == MSG_GET_CURRENT_SCREEN) // 画面ID变化通知
		{
			hmi_NotifyScreen(screen_id); // 画面切换调动的函数
		}
		else
		{
			hmi_widget_handle(screen_id, control_id, HMI_Manager.WidgetHandle, HMI_Manager.WidgetHandleArraySize, (uint8_t *)msg);
		}
	}
	break;
	case NOTIFY_HandShake: // 握手通知
		// NOTIFYHandShake();
		break;
	default:
		break;
	}
}
/**
****************************************************************************************
@brief:   hmi_all_widget_handle
@Input：  NULL
@Output： NULL
@Return   NULL.
@Warning: NULL
@note:   触摸屏刷新函数
****************************************************************************************
 **/
void hmi_refresh(void)
{
	uint16_t i;

	for (i = 0; i < HMI_Manager.WidgetHandleArraySize; i++)
	{
		// 只需要页面和当前页面一样就行 不关心控件 因为所有需要刷新的控件都要刷新
		if (HMI_Manager.WidgetHandle[i].page_num == HMI_Manager.curPageNum)
		{
			if (HMI_Manager.WidgetHandle[i].HMI_Widget_Handle)
			{
				HMI_Manager.WidgetHandle[i].HMI_Widget_Handle();
			}
		}
	}
}
