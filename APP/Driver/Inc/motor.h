/*************************************************************************************************** 
                                   xxxx��˾
  
                  

�ļ�:   motor.h
����:   ����
˵��:   �����ʱ������
***************************************************************************************************/
#ifndef __MOTOR_H
#define __MOTOR_H
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "STM32Fxxx.h"

#define X_AxisMotor  PWM1_ID//X����
#define Y_AxisMotor  PWM2_ID//Y����


#define X_AxisMotorDir  PWM1_DIR//X��������
#define Y_AxisMotorDir  PWM2_DIR//Y��������

#define Dir_Foreward  0//�������
#define Dir_Backward  1//�������

//�������ʵ��ʹ�õ���ͨ��DO
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

