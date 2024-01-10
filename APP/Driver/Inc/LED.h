/*************************************************************************************************** 
                                   xxxx��˾
  
                  

�ļ�:   LED.h 
����:   ����
˵��:   LED�ƿ���
***************************************************************************************************/

#ifndef __LED_H
#define __LED_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "main.h"

#define Slow_On_Time  1000//����2sһ������
#define Fast_On_Time  200//����400msһ������

#define Red_LED    1
#define Green_LED  2

//#define AllColor_LED 0xff//���������еƶ��������ԵƲ��ã����ջ�

typedef enum
{
	LED_ON = 0U,
	LED_OFF,
	LED_Flash_Slow ,
	LED_Flash_Fast,
	LEDStateMax,
} LEDState;

typedef struct  
{
	GPIO_TypeDef  *GPIOx;//ʹ�õ��ĸ�GPIO

	uint32_t Pin;//ʹ�õ�IO����       

	GPIO_PinState InitLevel; //��ʼ����ƽ��������������������ѹ����������Ǽ���ѹ���¼��Ϊ�����ʼ������Ϊ��
	
	GPIO_PinState OutPutOnstate;//���ʹ��LED���ĵ�ƽ
	
	uint32_t Pull;//��Ϊ����ʱ����������ѡ��

} LEDInit_TypeDef;
extern void LED_Init(void);
extern void LED_StateControl(void);
extern uint32_t TimeSubtract(uint32_t subtrahend,uint32_t minuend);
extern uint16_t LED_StateSet(uint16_t LED_Index,LEDState State);
extern void ColorLED_StateSet(uint16_t Color_Index,LEDState State);
#endif

