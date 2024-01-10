/************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: app_cfg.h
* Project  : STM32F1XX/4XXϵ��ģ�����
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.00
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: ���ļ��������ϵͳ�����������ȼ��Ͷ�ջ����;
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
#ifndef  __APP_CFG_H__
#define  __APP_CFG_H__

/*
*********************************************************************************************************
*                                       MODULE ENABLE / DISABLE
*********************************************************************************************************
*/

#define APP_TEST 0//��������
/**********************************************************************************************************
*                         ����ϵͳ�������ȼ�����
**********************************************************************************************************/	

#define  APP_TASK_START_PRIO                               2
#define  APP_MutexLMIP_PRIO						           3
#if APP_TEST
#define  APP_TASK_IO_PRIO                                  4
#define  APP_TASK_PWMFCLK_PRIO                             5
#define  APP_TASK_ADCDAC_PRIO						       6

#define  APP_TASK_DTU_PRIO                                 7
#define  APP_TASK_UARTCAN_PRIO                             8
#define  APP_TASK_MODBUS_PRIO						       9
#define  APP_TASK_FILE_PRIO                                10

#define  APP_TASK_LWIP_PRIO                                20
#else
//10��������Ҫ����





#define APP_HMI_PRIO 						           7//������������񣬱��� ��Ļ�� ʵʱ�Բ��ߵ�����
#define APP_HMI_RX_PRIO 						       8//��������������
//10���ϵ������

#define APP_MOTOR_PanRF_PRIO   					       12//�������
#define APP_MOTOR_PanRot_PRIO   					   13//ת�����

//20~30 lwip tasks is from 20-24

//30����ͨ��ͬ������
#define APP_UNIVERSAL_SYNCH_FUN_PRIO   				   30//ͨ��ͬ������ģ����Ƕ�������ɵĹ���ģ�飩
#define OS_TASK_TMR_PRIO							   35//�����ʱ���������ȼ�
#endif
#define  LWIP_TASK_START_PRIO                              21   // so priority of lwip tasks is from 20-24
#define  LWIP_TASK_MAX                                     3
#define  APP_TASK_ETHERNETIF_INPUT_PRIO 				   (LWIP_TASK_START_PRIO+LWIP_TASK_MAX)

/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*                             Size of the task stacks (# of OS_STK entries)
*********************************************************************************************************
*/

#define  APP_TASK_START_STK_SIZE                     256
#if APP_TEST
#define  APP_TASK_ADCDAC_STK_SIZE				     160
#define  APP_TASK_MODBUS_STK_SIZE					 160
#define  APP_TASK_FILE_STK_SIZE					     256
#define  APP_TASK_LWIP_STK_SIZE					     256
#define  APP_TASK_IO_STK_SIZE				    	 160
#define  APP_TASK_UARTCAN_STK_SIZE  		    	 160
#define  APP_TASK_PWMFCLK_STK_SIZE				     160
#define  APP_TASK_DTU_STK_SIZE				    	 160
#else


#define APP_HMI_STK_SIZE						     256
#define APP_HMI_RX_STK_SIZE						     256


#define APP_MOTOR_PanRF_STK_SIZE   				     128
#define APP_MOTOR_PanRotate_STK_SIZE   			     128


#define APP_UNIVERSAL_SYNCH_FUN_STK_SIZE 			 256
#endif
#define  LWIP_STK_SIZE                               256
#define  LWIP_TASK_ETHERNETIF_INPUT_STK_SIZE		 256

/*
*********************************************************************************************************
*                                                  LIB
*********************************************************************************************************
*/
#define  uC_CFG_OPTIMIZE_ASM_EN                 DEF_ENABLED
#define  LIB_STR_CFG_FP_EN                      DEF_DISABLED

#endif
