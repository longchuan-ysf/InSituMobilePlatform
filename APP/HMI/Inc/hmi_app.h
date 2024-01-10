#ifndef _HMI_APP_
#define _HMI_APP_
#include <stdint.h>
#include "mylist.h"
#include "hmi_functionHandle.h"
#include "hmi_WidgetHandle.h"

typedef struct 
{
    uint16_t curPageNum;//��ǰ��ҳ���
    uint16_t setPageNum;//���õ�ҳ���
    uint32_t curPageResidenceTime;//��ǰҳͣ��ʱ�� 1ms��λ
    uint16_t newPageFlag;//
    uint16_t backReturnPageNum;//����Ա�����˳����ؽ���
    uint8_t enterAdministratorState;//�������Ա����״̬
    uint32_t autoDecVal;//ÿ100ms �Լ�1�����������ʱ��δ������Ļ�����ص�������
    uint8_t (*get_cur_pagenum)(uint16_t *page);//��ȡ��ǰ�����
    void (*set_cur_pagenum)(uint16_t page);//�����µĽ����
	void (*rxtask_handle)(void);//���ݽ��մ���
	void (*refresh)(void);//��Ļˢ�º���
    WidgetHandleStruct *WidgetHandle;//�ؼ�����ṹ������ָ��
    uint16_t WidgetHandleArraySize;//�ؼ�����ṹ�������С
	PageInitStruct *PageInitial;//ҳ���ʼ���ṹ������ָ��
    uint16_t PageInitArraySize;//ҳ���ʼ���ṹ�������С
    
}HMIDeviceManager;

extern HMIDeviceManager HMI_Manager;//HMI����ṹ��
extern volatile  uint32_t hmi_timer_tick_count;	//��ʾ�����ļ���

extern void hmi_application_init(void);
extern void hmi_application_handle(void);

//extern void hmi_RecieveTimerCreate(void);
#endif
