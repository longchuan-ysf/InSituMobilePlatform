#ifndef _HMI_WIDGETHANDLE_H
#define _HMI_WIDGETHANDLE_H

#include "stdint.h"
#include "stdio.h"

typedef struct
{
	uint8_t year;//��
	uint8_t mon;//��
	uint8_t week;//����
	uint8_t day;//��
	uint8_t hour;//ʱ
	uint8_t min;//��
	uint8_t sec;//��
	
}RTCStruct;


typedef struct 
{
    uint16_t page_num;//ҳ���
	uint16_t widget_num;//�ؼ���	
	void (*HMI_Widget_Handle)(void);//ˢ�µ���
	void (*HMI_Widget_Handle_para)(uint8_t *para);//���ݴ������
}WidgetHandleStruct;

typedef struct 
{
    uint16_t page_num;//ҳ���	
	void (*HMI_Screen_Initial)(void);//ҳ���ʼ����
}PageInitStruct;




extern WidgetHandleStruct HMI_widget_handle_array[];
extern PageInitStruct HMI_page_init_array[];

extern uint16_t hmi_GetWidgetArraySize(void);
extern uint16_t hmi_GetPageArraySize(void);
#endif

