/*************************************************************************************************** 
                                   xxxx公司
  
                  

文件:   CookManage.c 
作者:   龙川
说明: 炒菜机设备管理的实现
***************************************************************************************************/
#include "PlatformDrive.h"
#include "PlatformManage.h"
#include "GPIO_Manager.h"
#include "STM32Fxxx.h"
#include "UserVars.h"
#include "APP_Init.h"
#include "OSVars.h"
#include "Delay.h"

uint32_t AlarmBitInfo[8];
AlarmStruct AlarmArr[]=
{
	{0,A_Scram,Scram_Alarm_Offset},


};

FlagStruct ManageFlag;
SysManageStruct SysManage;


  

 /**
****************************************************************************************
@brief:    AlarmSet 设置告警
@Input：   AlarmOffset 偏移
@Output：  NULL
@Return    NULL
@Warning:  NULL  
@note:     龙川2019-4-30
****************************************************************************************
 **/
void  AlarmSet(uint32_t AlarmOffset)
{
	uint8_t index,bit;
	if(AlarmOffset > sizeof(AlarmBitInfo)*4-1)//最大偏移0~sizeof(AlarmBitInfo)*4-1
	{
		return;
	}
	index = AlarmOffset>>5;//左移5位就是除以32
	bit = AlarmOffset%32;
	AlarmBitInfo[index] |= (0x01<<bit);
}
 /**
****************************************************************************************
@brief:    AlarmGet 获取告警
@Input：   AlarmOffset 偏移
@Output：  NULL
@Return    NULL
@Warning:  NULL  
@note:     龙川2019-4-30
****************************************************************************************
 **/
uint8_t  AlarmGet(uint32_t AlarmOffset)
{
	uint8_t index,bit;
	if(AlarmOffset > sizeof(AlarmBitInfo)*4-1)//最大偏移0~sizeof(AlarmBitInfo)*4-1
	{
		return 0xff;
	}
	index = AlarmOffset>>5;//左移5位就是除以32
	bit = AlarmOffset%32;
	return (AlarmBitInfo[index]>>bit) & 0x01;
}
/**
****************************************************************************************
@brief:    AlarmGet 设置告警
@Input：   AlarmOffset 偏移
@Output：  NULL
@Return    NULL
@Warning:  NULL  
@note:     龙川2019-4-30
****************************************************************************************
 **/
void  AlarmClear(uint32_t AlarmOffset)
{
	uint8_t index,bit;
	if(AlarmOffset > sizeof(AlarmBitInfo)*4-1)//最大偏移0~sizeof(AlarmBitInfo)*4-1
	{
		return;
	}
	index = AlarmOffset>>5;//左移5位就是除以32
	bit = AlarmOffset%32;
	AlarmBitInfo[index] &= ~(0x01<<bit);
}
 /**
****************************************************************************************
@brief:    AlarmHandle 告警处理——获取最高优先级告警
@Input：   NULL
@Output：  NULL
@Return    NULL
@Warning:  NULL  
@note:     龙川2019-4-30
****************************************************************************************
 **/
void AlarmHandle()
{
	uint32_t i;
	uint16_t AlarmPriority = 0xff,Alarm;
	for(i=0;i<sizeof(AlarmArr)/sizeof(AlarmStruct);i++)
	{
		if(AlarmGet(AlarmArr[i].AlarmBit))//如果想用的位置1表示产生告警
		{
			if(AlarmPriority > AlarmArr[i].Priority)//如果当前告警优先级比之前记录的低，记录最新最高优先级告警
			{
				AlarmPriority = AlarmArr[i].Priority;
				Alarm = AlarmArr[i].AlarmCode;
			}
		}
	}
	if(AlarmPriority != 0xff)
	{
		SysManage.Alarm = Alarm;
	}
}
 

/**
****************************************************************************************
@brief:    Motor_TaskCreate创建电机任务
@Input：   NULL
@Output：  NULL
@Return    NULL
@Warning:  NULL  
@note:     龙川2019-4-29
****************************************************************************************
 **/
void Motor_TaskCreate()
{
	CPU_INT08U  os_err;

	//升降电机任务创建
   	os_err = OSTaskCreate((void (*)(void *)) Motor_PanRiseFallTask,
                          (void          * ) 0,
                          (OS_STK        * )&APP_MotorPanRFstk[APP_MOTOR_PanRF_STK_SIZE - 1],
                          (INT8U           ) APP_MOTOR_PanRF_PRIO
                          );
						  
	//转锅电机任务创建
   	os_err = OSTaskCreate((void (*)(void *)) Motor_PanRotateTask,
                          (void          * ) 0,
                          (OS_STK        * )&APP_MotorPanRotatestk[APP_MOTOR_PanRotate_STK_SIZE-1],
                          (INT8U           ) APP_MOTOR_PanRot_PRIO
                          );

}
/**
****************************************************************************************
@brief:    Func_TaskCreate 功能模块任务
@Input：   NULL
@Output：  NULL
@Return    NULL
@Warning:  NULL  
@note:     龙川2019-4-29
****************************************************************************************
 **/
void Func_TaskCreate()
{
	CPU_INT08U  os_err;

   	os_err = OSTaskCreate((void (*)(void *)) Func_UniversalSynchTask,
                          (void          * ) 0,
                          (OS_STK        * )&APP_UniversalSynchFunstk[APP_UNIVERSAL_SYNCH_FUN_STK_SIZE-1],
                          (INT8U           ) APP_UNIVERSAL_SYNCH_FUN_PRIO
                          );
}

