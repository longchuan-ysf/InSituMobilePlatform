/*************************************************************************************************** 
                                   xxxx��˾
  
                  

�ļ�:   GPIO_Manager.h
����:   ����
˵��:   ��ͨ��������ڵ�IO����
***************************************************************************************************/
#ifndef __GPIO_MANAGER_H
#define __GPIO_MANAGER_H
#include <stdint.h>
#include <stdio.h>
#include <string.h>
//�������IO�������궨�塪��һ��Ҫ�������λ��һһ��Ӧ
typedef enum
{
	StirPUL = 0,//��������-----

	
	//�������ö��	
	CookerDOMax,
}cookerDO;
//�������IO��������
typedef enum
{
	Limiter=0,//��λ��
	Raster,
	CookerDIMax,
}cookerDI;

typedef enum
{
  GPIO_PIN_RESET = 0U,
  GPIO_PIN_SET
} GPIO_PinState;

#define CHECK_STATE GPIO_PIN_SET
#define CHECK_STATE_N GPIO_PIN_RESET

#define NOT_CHECK_STATE  GPIO_PIN_RESET 
#define NOT_CHECK_STATE_N GPIO_PIN_SET

#define FORWARD_STATE  GPIO_PIN_SET//��ת
#define BACKWARD_STATE  GPIO_PIN_RESET//��ת


#define UP_STATE  GPIO_PIN_SET//����
#define DOWN_STATE  GPIO_PIN_RESET//�½�

#define OUTDISH_STATE  GPIO_PIN_RESET //����
#define WASH_STATE   GPIO_PIN_SET//��ϴ��ˮ

#define OPEN_STATE  GPIO_PIN_SET  //
#define CLOSE_STATE   GPIO_PIN_RESET//

#define ROLL_STATE  GPIO_PIN_SET  //��Ĥ
#define RELEASE_STATE   GPIO_PIN_RESET//�ͷ�Ĥ

#define ENABLE_STATE  GPIO_PIN_SET
#define DISABLE_STATE  GPIO_PIN_RESET

#define ENABLE_STATE_N  GPIO_PIN_RESET
#define DISABLE_STATE_N  GPIO_PIN_SET
extern uint32_t IOFunction_Read(cookerDI IOx);

extern void IOFunction_Write(cookerDO IOx, uint16_t val);

extern int32_t IOFunction_Ctrl(cookerDO IOx, uint8_t Cmd, uint32_t Para);



typedef struct  
{
	uint16_t IOFunction;//IO�Ĺ���cookerDO ���� cookerDI�е�һ��
	uint16_t IO;//�ײ����ı��
} IOMapping_TypeDef;



extern uint32_t IOFunction_Read(cookerDI IOx);
extern uint32_t IOFunction_ReadDO(cookerDO IOx);

extern void IOFunction_Write(cookerDO IOx, uint16_t val);

extern int32_t IOFunction_Ctrl(cookerDO IOx, uint8_t Cmd, uint32_t Para);


#endif

