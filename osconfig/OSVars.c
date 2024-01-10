/************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: OSVars.h
* Project  : STM32F1XX/4XXϵ��ģ�����
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.00
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: ���ļ��ǲ���ϵͳ����ȫ�ֱ�������, �ͻ����԰ѺͲ���ϵͳ��ص�ȫ�ֱ������õ�����;
*
* Others: none;
*
* Function List:
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/
/************************************************************************************/
// �����ⲿͷ�ļ�
/************************************************************************************/
#include "OSVars.h"

/************************************************************************************
// ������ȫ�ֱ�������
*************************************************************************************/
OS_FLAG_GRP *APIWaitOSFlag;       // ר��������APIʹ�õȴ��¼���־

OS_FLAG_GRP *OSFlagSys;

OS_EVENT *OSMboxADC;         // ADCת���������

OS_EVENT *OSMboxX;

OS_EVENT *OSMboxMalloc;       // malloc()��������
OS_EVENT *OSMboxFree;         // free()��������
OS_EVENT *OSMboxSPI;          // SPI����Ȩ�ޱ���
OS_EVENT *OSMboxNET;          // ������������Ȩ�ޱ���
OS_EVENT *OSMboxNETInt;       // �����ж�


//���˻��ź��������䡢��Ϣ���С��¼���־�鶨��
//���
OS_EVENT *OSMboxX_Motor;//˺Ĥ������䡪�������������ݵĲ����Ǻ���ָ��
OS_EVENT *OSMboxY_Motor;//���е������


OS_EVENT *OSQUniversalSynchFun;//ͨ��ͬ��������Ϣ����


void * OSQueue_UniverSyncFun[OS_QUEUE_SIZE];//������Ϣ����
//ģ�鹦��
/************************************************************************************
*   UCOS-ii �����ջ����
*************************************************************************************/
__align(8) OS_STK   App_TaskStartStk[APP_TASK_START_STK_SIZE];//
//��������


__align(8) OS_STK   App_HMIStk[APP_HMI_STK_SIZE];
__align(8) OS_STK   App_HMIRXStk[APP_HMI_RX_STK_SIZE];
//�������

__align(8) OS_STK  APP_MotorPanRFstk[APP_MOTOR_PanRF_STK_SIZE];
__align(8) OS_STK  APP_MotorPanRotatestk[APP_MOTOR_PanRotate_STK_SIZE];


//ģ������
__align(8) OS_STK  APP_UniversalSynchFunstk[APP_UNIVERSAL_SYNCH_FUN_STK_SIZE];
#if (TASK_ADCDAC_EN == 1)
__align(8) OS_STK   App_TaskADCDACStk[APP_TASK_ADCDAC_STK_SIZE];  
#endif

#if (TASK_IO_EN == 1)
__align(8) OS_STK   App_TaskIOStk[APP_TASK_IO_STK_SIZE];
#endif

#if (TASK_UARTCAN_EN == 1)
__align(8) OS_STK   App_TaskUartCanStk[APP_TASK_UARTCAN_STK_SIZE];	
#endif

#if (TASK_FILE_EN == 1)
__align(8) OS_STK   App_TaskFileStk[APP_TASK_FILE_STK_SIZE];
#endif

#if (TASK_PWMFCLK_EN == 1)
__align(8) OS_STK   App_TaskPWMFClkStk[APP_TASK_PWMFCLK_STK_SIZE];
#endif

#if (TASK_LWIP_EN == 1)
__align(8) OS_STK   App_TaskLWIPStk[APP_TASK_LWIP_STK_SIZE];
#endif

#if (TASK_MODBUS_EN == 1)
__align(8) OS_STK   APP_TaskModbusStk[APP_TASK_MODBUS_STK_SIZE];
#endif

#if (TASK_DTU_EN == 1)
__align(8) OS_STK   APP_TaskDTUStk[APP_TASK_DTU_STK_SIZE];
#endif


/***********************************************************************************/
// �ļ�����
/***********************************************************************************/



