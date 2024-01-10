/************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: main.c
* Project  : STM32F1XX/4XXϵ��ģ�����
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.00
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: ���ļ�����ϵͳ��ʼ����ucos���������񴴽������Ź�����;
*
* Others: none;
*
* Function List:
*		
*
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*����
*************************************************************************************/

/************************************************************************************/
// �����ⲿͷ�ļ�
#include "config.h"
#include <includes.h>
#include "STM32Fxxx.h"
#include "UserVars.h"
#include "APP_Init.h"
#include "OSVars.h"
#include "Delay.h"
#include "Motor.h"
#include "PlatformManage.h"
#include "PlatformDrive.h"
#include "hmi_app.h"
#include "fun.h"
#include "hmi_user_uart.h"
#include "GPIO_manager.h"
/************************************************************************************/

/************************************************************************************/
// ������ȫ�ֱ�������
/************************************************************************************/
static  void  App_TaskCreate       (void);
static  void  App_TaskStart        (void *p_arg);
 /**
****************************************************************************************
@brief:     OS_SemFlagCreat
@Input��    NULL
@Output��   NULL
@Return     NULL
@Warning:   NULL  
@note:      �ź��������һЩ����ͨѶ�����Ĵ���
****************************************************************************************
 **/
static void OS_SemFlagCreate(void)
{
	CPU_INT08U  os_err;
	
	OSMboxADC = OSMboxCreate((void*)0);          // ����ADC���ݴ�������
	OSMboxMalloc = OSMboxCreate((void*)1);      //  ����malloc()������������
	OSMboxFree   = OSMboxCreate((void*)1);      //  ����free()������������
	OSMboxSPI   = OSMboxCreate((void*)1);       //  ����SPI����Ȩ�ޱ�������
	OSMboxX_Motor   = OSMboxCreate((void*)1);
	OSMboxY_Motor   = OSMboxCreate((void*)1);
	OSFlagSys = OSFlagCreate (0, (INT8U *)&os_err); // ������־����

    APIWaitOSFlag = OSFlagCreate (0, (INT8U *)&os_err); // ������־����  

	
	OSQUniversalSynchFun = OSQCreate(OSQueue_UniverSyncFun,OS_QUEUE_SIZE);//ģ�鹦��

}
/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Argument(s) : none.
*
* Return(s)   : none.
*********************************************************************************************************
*/
int  main (void)
 {
    CPU_INT08U  os_err;
	
    API_Init();             // Ӧ�ù��ܳ�ʼ��
     
	CPU_IntDis();	        // ��������ж�
	OSInit();               // Initialize "uC/OS-II, The Real-Time Kernel".         

    // ����App_TaskStart����
	os_err = OSTaskCreate((void (*)(void *)) App_TaskStart,     // Create the start task.
                          (void          * ) 0,
                          (OS_STK        * )&App_TaskStartStk[APP_TASK_START_STK_SIZE - 1],
                          (INT8U           ) APP_TASK_START_PRIO
                         );                  
    OS_SemFlagCreate();               
	OSTimeSet(0);  // ��ʼ��ϵͳʱ��
                          
    #if (IWDG_EN > 0)         // ���Ź�ʹ��             
	IWDG_Ctrl(CMD_IWDG_CLEAR);   // ������Ź�
    #endif
    OSStart();                    // ��������ϵͳ����, �ò���ϵͳ�ӹ�������� 
                                  // Start multitasking (i.e. give control to uC/OS-II). 

    return (0);                   // ��Զ�������е�����
}

/*
*********************************************************************************************************
*                                          App_TaskStart()
*
* Description : The startup task.  The uC/OS-II ticker should only be initialize once multitasking starts.
*
* Argument(s) : p_arg       Argument passed to 'App_TaskStart()' by 'OSTaskCreate()'.
*
* Return(s)   : none.
*
* Caller(s)   : This is a task.
*
* Note(s)     : none.��������Ȼ����һЩ�����ȼ��Ĵ���������λ�������������������������
*********************************************************************************************************/

static  void  App_TaskStart (void *p_arg)
{
	INT8U err;
	static uint8_t DIreadTemp=0xff;
	uint8_t DIread;
	ADC_VAR *pADC;
	(void)p_arg; 
	
	#if (IWDG_EN > 0) 
	IWDG_Ctrl(CMD_IWDG_CLEAR);
    #endif	

    UserVars.Flag |= OS_START_FLAG;      // ���ò���ϵͳ������־
#if (OS_TASK_STAT_EN > 0)
    OSStatInit();                        // Determine CPU capacity.                              
#endif
 	App_TaskCreate();
	UserVars.TaskRunStatus = 0; 
	UserVars.TimerCount = 0;
  while (1) 
	{                                                           // Task body, always written as an infinite loop.       
		Delay_ms(10);
        #if (IWDG_EN > 0) 
        IWDG_Ctrl(CMD_IWDG_CLEAR);                               // Ӳ��ι��  
		#endif
		UserVars.TimerCount+=10;
		if ((UserVars.TimerCount%1000)==0)
		{
			IO_Ctrl(RUN_LED, CMD_IO_ON_T, 300); //RUN LED���1����˸ 	
		}
		MotorFlagHandle();
		if (UserVars.TimerCount==3000)
		{
			X_AxisPositionFoundStart();;
			printf("%d\r\n",IOFunction_Read(Limiter));
		}
		
		//Limit();//�����λ����	
	}
}
 /**
****************************************************************************************
@brief:     App_HMI 
@Input��    p_arg ��������ʱ���ݸ�����Ĳ���
@Output��   NULL
@Return     NULL
@Warning:   NULL  
@note:      HMI����������
****************************************************************************************
 **/
void  App_HMI (void *p_arg)
{
	INT32U General_TimeCnt; 
	uint32_t len,rUart1Len,i;
	General_TimeCnt	= 0;
	hmi_application_init();
	while(1)
	{
		Delay_ms(10);	                 // ��ʱ10ms
        General_TimeCnt +=10 ;           // ����ʱ�������
		hmi_application_handle();		 //��Ļ����
	}
	
} /**
****************************************************************************************
@brief:     App_HMI_RX 
@Input��    p_arg ��������ʱ���ݸ�����Ĳ���
@Output��   NULL
@Return     NULL
@Warning:   NULL  
@note:      ���������ݽ��մ���
****************************************************************************************
 **/
static  void  App_HMI_RX (void *p_arg)
{
	
	while(1)
	{
		Delay_ms(20);	                 // ��ʱ10ms
		HMI_UartRecieve();

	}
	
}
/*
*********************************************************************************************************
*                                            App_TaskCreate()
*
* Description : Create the application tasks.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : App_TaskStart().
*
* Note(s)     : none.
*********************************************************************************************************
*/ 
static  void  App_TaskCreate (void)
{
    CPU_INT08U  os_err;
	
	//�˻����洦�����񣬱��紮��ͨ�ŵ�
   	os_err = OSTaskCreate((void (*)(void *)) App_HMI,
                          (void          * ) 0,
                          (OS_STK        * )&App_HMIStk[APP_HMI_STK_SIZE - 1],
                          (INT8U           ) APP_HMI_PRIO
                          );
	os_err = OSTaskCreate((void (*)(void *)) App_HMI_RX,
                          (void          * ) 0,
                          (OS_STK        * )&App_HMIRXStk[APP_HMI_RX_STK_SIZE - 1],
                          (INT8U           ) APP_HMI_RX_PRIO
                          );
 	//����������񴴽�
	Motor_TaskCreate();
	Func_TaskCreate();
	//					  
}

/***********************************************************************************/
// �ļ�����
/***********************************************************************************/



