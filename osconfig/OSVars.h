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
#include <includes.h>
#include "const.h"
#include "config.h"
/************************************************************************************
// ������ȫ�ֱ�������
*************************************************************************************/
#define OSFLAG_FSMC_BANK1	0x00000001	 // BANK1�жϱ�־
#define OSFLAG_FSMC_BANK2	0x00000002	 // BANK2�жϱ�־
#define OSFLAG_FSMC_BANK3	0x00000004	 // BANK3�жϱ�־
#define OSFLAG_FSMC_BANK4	0x00000008	 // BANK4�жϱ�־
#define OSFLAG_NET_RXINT	0x00000010	 // DM9000�����жϱ�־

#define OS_QUEUE_SIZE 8//��Ϣ���д�С
/************************************************************************************
*
*       ϵͳ״̬��־����
*
*************************************************************************************/
extern OS_FLAG_GRP *APIWaitOSFlag;       // ר��������APIʹ�õȴ��¼���־

extern OS_FLAG_GRP *OSFlagSys;
//������������
extern OS_EVENT *OSMboxADC;          // ADCת���������
extern OS_EVENT *OSMboxMalloc;       // malloc()��������
extern OS_EVENT *OSMboxFree;         // free()��������
extern OS_EVENT *OSMboxSPI;          // SPI����Ȩ�ޱ���
extern OS_EVENT *OSMboxNET;          // ������������Ȩ�ޱ���
extern OS_EVENT *OSMboxNETInt;       // �����ж�

//�����������

extern OS_EVENT *OSMboxX_Motor;//�����������
extern OS_EVENT *OSMboxY_Motor;//ת���������


//ͨ��ͬ����Ϣ���� ϴ������ ����ģ���˺Ĥ �˺��ӻ�������ͬһ��ʱ������ֻ��һ������
extern OS_EVENT *OSQUniversalSynchFun;//ģ�鹦������
extern void * OSQueue_UniverSyncFun[OS_QUEUE_SIZE];
/************************************************************************************
*
*   ���������ڴ����뼰��Ϣ���ж��� 
*
*************************************************************************************/
// �����������
//#define OSQ_WRITE_CMD_SIZE  512
//extern  OS_EVENT *OSQWriteCmd;
//extern  void *OSQWriteCmdTbl[OSQ_WRITE_CMD_SIZE];
//
//
//#define OSQ_OUT_DATA_SIZE  32
//extern  OS_EVENT *OSQOutData;
//extern  void *OSQOutDataTbl[OSQ_OUT_DATA_SIZE];
/************************************************************************************
*   UCOS-ii �����ջ����
*************************************************************************************/
extern  OS_STK   App_TaskStartStk[];

extern OS_STK   App_HMIRXStk[APP_HMI_RX_STK_SIZE];
extern OS_STK   App_HMIStk[APP_HMI_STK_SIZE];

//�������

extern OS_STK  APP_MotorPanRFstk[APP_MOTOR_PanRF_STK_SIZE];
extern OS_STK  APP_MotorPanRotatestk[APP_MOTOR_PanRotate_STK_SIZE];

//ģ������
extern OS_STK  APP_UniversalSynchFunstk[APP_UNIVERSAL_SYNCH_FUN_STK_SIZE];

#if (TASK_ADCDAC_EN == 1)
extern  OS_STK   App_TaskADCDACStk[APP_TASK_ADCDAC_STK_SIZE];  
#endif

#if (TASK_IO_EN == 1)
extern  OS_STK   App_TaskIOStk[APP_TASK_IO_STK_SIZE];
#endif

#if (TASK_UARTCAN_EN == 1)
extern  OS_STK   App_TaskUartCanStk[APP_TASK_UARTCAN_STK_SIZE];	
#endif

#if (TASK_FILE_EN == 1)
extern  OS_STK   App_TaskFileStk[APP_TASK_FILE_STK_SIZE];
#endif

#if (TASK_PWMFCLK_EN == 1)
extern  OS_STK   App_TaskPWMFClkStk[APP_TASK_PWMFCLK_STK_SIZE];
#endif

#if (TASK_LWIP_EN == 1)
extern  OS_STK   App_TaskLWIPStk[APP_TASK_LWIP_STK_SIZE];
#endif

#if (TASK_MODBUS_EN == 1)
extern  OS_STK   APP_TaskModbusStk[APP_TASK_MODBUS_STK_SIZE];
#endif

#if (TASK_DTU_EN == 1)
extern  OS_STK   APP_TaskDTUStk[APP_TASK_DTU_STK_SIZE];
#endif

/************************************************************************************
*
*   ���������� 
*  OS_MAX_TASKS 30u��ඨ��30������
*************************************************************************************/
//����Ҫ������

extern  void  App_HMI           	(void *p_arg);
extern  void  App_HMI_RX           (void *p_arg);


//�������
extern void Motor_PanRiseFallTask	(void *p_arg);//�������
extern void Motor_PanRotateTask	    (void *p_arg);//ת�����

//����ģ��
extern void Func_UniversalSynchTask	(void *p_arg);//����ģ��

//�������

//��������

/***********************************************************************************/
// �ļ�����
/***********************************************************************************/
