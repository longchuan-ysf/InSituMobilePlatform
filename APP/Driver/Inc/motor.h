/*************************************************************************************************** 
                                   xxxx公司
  
                  

文件:   motor.h
作者:   龙川
说明:   电机定时器设置
***************************************************************************************************/
#ifndef __MOTOR_H
#define __MOTOR_H
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "STM32Fxxx.h"

#define X_AxisMotor  PWM1_ID//X轴电机
#define Y_AxisMotor  PWM2_ID//Y轴电机


#define X_AxisMotorDir  PWM1_DIR//X轴电机方向
#define Y_AxisMotorDir  PWM2_DIR//Y轴电机方向

#define Dir_Foreward  0//电机方向
#define Dir_Backward  1//电机方向

//翻炒电机实际使用的普通的DO
typedef enum
{
	Enum_X_AxisMotor = 0,
	Enum_Y_AxisMotor,
	EnumMotorMax,
}MotorEnum;
extern void Motor_Enable(MotorEnum Motor,uint8_t Dir,uint32_t Fre,uint32_t PUL);
extern void Motor_Disable(MotorEnum Motor);
extern int32_t Motor_GetStatus(MotorEnum Motor);
extern int32_t Motor_SetFrequency(MotorEnum Motor,uint32_t Fre);
extern int32_t Motor_GetPulse(MotorEnum Motor);

extern uint8_t Motor_TimeEnableStatus(MotorEnum Motor);
#endif

