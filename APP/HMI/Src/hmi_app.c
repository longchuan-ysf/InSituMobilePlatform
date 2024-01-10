
/********************************************************************************
				xxxx公司
  
文件:   hmi_app.c 
作者:   龙川
说明：提供应用层调用的接口
主要两个函数根据实际情况修改函数
hmi_application_init初始化函数
hmi_application_handle屏幕处理函数
*********************************************************************************/


#include "hmi_app.h"
#include "hmi_user_uart.h"
#include "cmd_queue.h"
#include "Delay.h"
#include "string.h"
#include "ucos_ii.h"
HMIDeviceManager HMI_Manager;
volatile uint32_t  hmi_timer_tick_count = 0;          //单位1ms 
/**
****************************************************************************************
@brief:   hmi_application_init
@Input：  NULL
@Output： NULL
@Return   NULL.
@Warning: NULL
@note:   触摸屏显示初始化 
****************************************************************************************
 **/
void hmi_application_init(void)
{
//	uint16 screen;
	//串口初始化                                              
    HMI_UartInit(115200);                                                               

    //清空串口接收缓冲区                                                          
    queue_reset();  
	
	memset(&HMI_Manager,0,sizeof(HMI_Manager));
	
	//几个重要指针初始化，包括函数指针和数组指针
	HMI_Manager.get_cur_pagenum = hmi_GetCurPagenum;
	HMI_Manager.set_cur_pagenum = SetScreen;
	HMI_Manager.rxtask_handle=hmi_rxtask_handle;
	HMI_Manager.WidgetHandle=HMI_widget_handle_array;
	HMI_Manager.WidgetHandleArraySize = hmi_GetWidgetArraySize();
	HMI_Manager.PageInitial= HMI_page_init_array;
	HMI_Manager.PageInitArraySize = hmi_GetPageArraySize();
	HMI_Manager.refresh = hmi_refresh;
	
	HMI_Manager.curPageNum = 0;
	HMI_Manager.setPageNum = 0;
	HMI_Manager.newPageFlag = 1;

	//创建串口读数据定时器
	printf("%s\r\n",__func__);

    //延时等待串口屏初始化完毕,必须等待300ms                                      
    Delay_ms(300); //——————重点强调如果发送的数据量比较大一定要间隔发送，否则屏幕会混乱
	//重启后会将页面设置到第0页
	HMI_Manager.set_cur_pagenum(0);
}
/**
****************************************************************************************
@brief:   hmi_application_handle
@Input：  NULL
@Output： NULL
@Return   NULL.
@Warning: NULL
@note:   触摸屏处理函数，外部调用该函数即可实现触摸屏处理 这个函数的调用周期是10ms
****************************************************************************************
 **/
void hmi_application_handle(void)
{     
   //页面跳转
   hmi_timer_tick_count+=10;//10ms的调用周期
   HMI_Manager.rxtask_handle();//数据接收处理
   //每500ms刷一次屏幕
   if (hmi_timer_tick_count%500 == 0)
   {
       HMI_Manager.refresh();//刷新屏幕
   }
}





