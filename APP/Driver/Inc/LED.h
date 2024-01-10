/*************************************************************************************************** 
                                   xxxx公司
  
                  

文件:   LED.h 
作者:   龙川
说明:   LED灯控制
***************************************************************************************************/

#ifndef __LED_H
#define __LED_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "main.h"

#define Slow_On_Time  1000//慢闪2s一个周期
#define Fast_On_Time  200//快闪400ms一个周期

#define Red_LED    1
#define Green_LED  2

//#define AllColor_LED 0xff//不允许所有灯都亮——对灯不好，会烧坏

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
	GPIO_TypeDef  *GPIOx;//使用的哪个GPIO

	uint32_t Pin;//使用的IO引脚       

	GPIO_PinState InitLevel; //初始化电平——对于输出就是输出电压对于输入就是检测电压按下检测为低则初始化设置为高
	
	GPIO_PinState OutPutOnstate;//输出使得LED亮的电平
	
	uint32_t Pull;//作为输入时上拉下拉的选择

} LEDInit_TypeDef;
extern void LED_Init(void);
extern void LED_StateControl(void);
extern uint32_t TimeSubtract(uint32_t subtrahend,uint32_t minuend);
extern uint16_t LED_StateSet(uint16_t LED_Index,LEDState State);
extern void ColorLED_StateSet(uint16_t Color_Index,LEDState State);
#endif

