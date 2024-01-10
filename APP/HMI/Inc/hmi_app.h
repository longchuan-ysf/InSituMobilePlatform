#ifndef _HMI_APP_
#define _HMI_APP_
#include <stdint.h>
#include "mylist.h"
#include "hmi_functionHandle.h"
#include "hmi_WidgetHandle.h"

typedef struct 
{
    uint16_t curPageNum;//当前的页码号
    uint16_t setPageNum;//设置的页码号
    uint32_t curPageResidenceTime;//当前页停留时间 1ms单位
    uint16_t newPageFlag;//
    uint16_t backReturnPageNum;//管理员界面退出返回界面
    uint8_t enterAdministratorState;//进入管理员界面状态
    uint32_t autoDecVal;//每100ms 自减1，设计用来长时间未操作屏幕主动回到主界面
    uint8_t (*get_cur_pagenum)(uint16_t *page);//获取当前界面号
    void (*set_cur_pagenum)(uint16_t page);//设置新的界面号
	void (*rxtask_handle)(void);//数据接收处理
	void (*refresh)(void);//屏幕刷新函数
    WidgetHandleStruct *WidgetHandle;//控件处理结构体数组指针
    uint16_t WidgetHandleArraySize;//控件处理结构体数组大小
	PageInitStruct *PageInitial;//页面初始化结构体数组指针
    uint16_t PageInitArraySize;//页面初始化结构体数组大小
    
}HMIDeviceManager;

extern HMIDeviceManager HMI_Manager;//HMI管理结构体
extern volatile  uint32_t hmi_timer_tick_count;	//显示屏节拍计数

extern void hmi_application_init(void);
extern void hmi_application_handle(void);

//extern void hmi_RecieveTimerCreate(void);
#endif
