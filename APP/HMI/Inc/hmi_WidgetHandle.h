#ifndef _HMI_WIDGETHANDLE_H
#define _HMI_WIDGETHANDLE_H

#include "stdint.h"
#include "stdio.h"

typedef struct
{
	uint8_t year;//年
	uint8_t mon;//月
	uint8_t week;//星期
	uint8_t day;//日
	uint8_t hour;//时
	uint8_t min;//分
	uint8_t sec;//秒
	
}RTCStruct;


typedef struct 
{
    uint16_t page_num;//页面号
	uint16_t widget_num;//控件号	
	void (*HMI_Widget_Handle)(void);//刷新调用
	void (*HMI_Widget_Handle_para)(uint8_t *para);//数据处理调用
}WidgetHandleStruct;

typedef struct 
{
    uint16_t page_num;//页面号	
	void (*HMI_Screen_Initial)(void);//页面初始函数
}PageInitStruct;




extern WidgetHandleStruct HMI_widget_handle_array[];
extern PageInitStruct HMI_page_init_array[];

extern uint16_t hmi_GetWidgetArraySize(void);
extern uint16_t hmi_GetPageArraySize(void);
#endif

