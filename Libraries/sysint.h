/************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: sysint.h
* Project  : STM32F1XX/4XXϵ��ģ��������
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: ���ļ���ϵͳ���������ͷ�ļ�;
*
* Others: none;
*
* Function List: 
*          1. INT32S SysLib_Init(SYSLIB_PARA *pPara);
*          2. INT32S SysLib_Ctrl(INT8U Cmd, INT32U Para);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/
#ifndef  __SYSINT
#define  __SYSINT
/************************************************************************************/
// �����ⲿͷ�ļ�
/************************************************************************************/
#include    "const.h"
#include    "config.h"

/************************************************************************************/
// �ⲿ���ڲ�����Ƶ�� 
/************************************************************************************/
// STM32F10Xϵ���ڲ�����ʱ��Ƶ��
#define OSC_HSI_8MHZ      8000000

// STM32F40Xϵ���ڲ�����ʱ��Ƶ��
#define OSC_HSI_16MHZ     16000000

/************************************************************************************/
// STM32F1_M3 ϵͳʱ�Ӷ��� 
/************************************************************************************/
// ʱ�Ӷ���
#define SYSCLK_8MHZ     8000000
#define SYSCLK_11MHZ    11059200
#define SYSCLK_12MHZ    12000000
#define SYSCLK_24MHZ    24000000 
#define SYSCLK_25MHZ    25000000 
#define SYSCLK_36MHZ    36000000 
#define SYSCLK_48MHZ    48000000
#define SYSCLK_56MHZ    56000000
#define SYSCLK_60MHZ    60000000
#define SYSCLK_72MHZ    72000000

/************************************************************************************/
// STM32F4_M4ϵͳʱ�Ӷ���
/************************************************************************************/
#define SYSCLK_24MHZ    24000000
#define SYSCLK_30MHZ    30000000
#define SYSCLK_36MHZ    36000000
#define SYSCLK_42MHZ    42000000
#define SYSCLK_48MHZ    48000000
#define SYSCLK_60MHZ    60000000
#define SYSCLK_72MHZ    72000000
#define SYSCLK_84MHZ    84000000
#define SYSCLK_96MHZ    96000000
#define SYSCLK_120MHZ   120000000
#define SYSCLK_144MHZ   144000000
#define SYSCLK_168MHZ   168000000


#define SYSCLK_150MHZ   150000000
#define SYSCLK_100MHZ   100000000
#define SYSCLK_50MHZ    50000000


// IAP�ж��������ַ����
#define NVIC_VECTOR_TABLE_ADDR  0x4000     // �����޸�

// ��־λ����
#define SYS_OS_FLAG             0x00000001 // ����ϵͳʹ�ܱ�־
#define SYS_NVIC_VECTORTAB_FLAG 0x00000002 // �����µ��ж�������ʹ�ܱ�־ 
#define SYS_TICK_FLAG           0x00000004 // ����ϵͳ��ʱ��ʹ�ܱ�־ 
#define SYS_CLK_HSI_FLAG        0x00000008 // ѡ���ڲ�ʱ�Ӿ����־
#define SYS_CLK_HSE_FLAG        0x00000010 // ѡ���ⲿʱ�Ӿ����־

#define SYS_DEBUG_LIB_FLAG      0x01000000 // �������������������־ 
#define SYS_DEBUG_SD_FLAG       0x02000000 // ������SD�����������־ 
#define SYS_DEBUG_USB_FLAG      0x04000000 // ������USB���ֵ��������־ 
#define SYS_DEBUG_MODBUS_FLAG   0x08000000 // ������MODBUS���������־ 
#define SYS_DEBUG_NET_FLAG      0x10000000 // ������������������־ 
#define SYS_DEBUG_NFLASH_FLAG   0x20000000 // ������NAND FLASH���������־ 


// SYSLIB�����ṹ 
typedef struct
{
    INT32U Flag;            // ��־
    INT8U  ModuleType;      // ģ������
    INT8U  DebugUart;       // ѡ��printf�������Uart
    INT16U VectorTableAddr; // �ж��������ַ 
    INT32U OscClk;          // �ⲿ���ڲ�����Ƶ��
    INT32U SysClk;          // ϵͳʱ��Ƶ��
    INT16U Tick;            // ϵͳ��ʱ����ʱʱ��, ��λms
}SYSLIB_PARA;

// SysLib_Ctrl()���Ʋ���
#define CMD_SYSLIB_RESET           0  // ϵͳ��λ(�൱�ڰ��Ӽӵ�����������)
#define CMD_SYSLIB_READ_VERSION    1  // ��ȡ������汾
#define CMD_SYSLIB_READ_DATE       2  // ��ȡ�����������������
#define CMD_MCO1                   3  // MCO1�������
#if (MODULE_CLASS == STM32F407XX)
#define CMD_MCO2                   4  // MCO2�������
#endif
#define CMD_SYSLIB_READ_MCUID      5  // ��ȡMCUΨһ��IDֵ: 96λ��12�ֽ�


// MCO1/2 ����Para����
#define MCO_OUT_ENA               0x8000  // MCO1/2 ���ʹ��, bit15=1;
#define MCO_OUT_DIS               0x0000  // MCO1/2 ����ر�, bit15=0;

#if (MODULE_CLASS == STM32F407XX) //STM32F40XоƬ�����²��� 
// MCO1/2�����������
#define MCO_DIV1                  0x0010  // MCO1/2 �޷�Ƶ, bit[6,5,4]= 1;
#define MCO_DIV2                  0x0020  // MCO1/2 2��Ƶ,  bit[6,5,4]= 2;
#define MCO_DIV3                  0x0030  // MCO1/2 3��Ƶ,  bit[6,5,4]= 3;
#define MCO_DIV4                  0x0040  // MCO1/2 4��Ƶ,  bit[6,5,4]= 4;
#define MCO_DIV5                  0x0050  // MCO1/2 5��Ƶ,  bit[6,5,4]= 5;

// MCO1����ź�ѡ��(�ܽ�PA8���)
#define MCO1_HSI                  0x0000  // MCO1���HSI, bit[1,0] = 0;
#define MCO1_LSE                  0x0001  // MCO1���LSE, bit[1,0] = 1;
#define MCO1_HSE                  0x0002  // MCO1���HSE, bit[1,0] = 2;
#define MCO1_PLL                  0x0003  // MCO1���PLL, bit[1,0] = 3;

// MCO2����ź�ѡ��(�ܽ�PC9���)
#define MCO2_SYSCLK               0x0000  // MCO2���ϵͳʱ��, bit[1,0] = 0;
#define MCO2_PLLI2S               0x0001  // MCO2���PLLI2S,   bit[1,0] = 1;
#define MCO2_HSE                  0x0002  // MCO2���HSE,      bit[1,0] = 2;
#define MCO2_PLL                  0x0003  // MCO2���PLL,      bit[1,0] = 3;

#else  //STM32F10XоƬ�����²��� 
#define MCO1_SYSCLK               0x0001  // MCO1���ϵͳʱ��,  bit[1,0] = 0;
#define MCO1_HSI                  0x0001  // MCO1���PLLI2S,   bit[1,0] = 1;
#define MCO1_HSE                  0x0002  // MCO1���HSE,      bit[1,0] = 2;
#define MCO1_PLL_DIV2             0x0003  // MCO1���PLL,      bit[1,0] = 3;
#endif

/************************************************************************************
//
//                 ϵͳ���������
//
*************************************************************************************/

/***********************************************************************************
* Function: SysLib_Init;
*
* Description: ϵͳ�������ʼ������;
* 
* Input: *pPara, ��ʼ������ָ��;
*
* Output: none;
*          		
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   none;
************************************************************************************/
INT32S SysLib_Init(SYSLIB_PARA *pPara);

/***********************************************************************************
* Function: SysLib_Ctrl;
*
* Description: ϵͳ���ƺ���;
* 
* Input:  Cmd: �������CMD_SYSLIB_RESET, ϵͳ��λ, ParaĬ��0;
*                        CMD_SYSLIB_READ_VERSION,  ��ȡ������汾, ParaĬ��0;
*                        CMD_SYSLIB_READ_DATE, ��ȡ�����������������, ParaĬ��0;
*                        CMD_MCO1,CMD_MCO2: MCO1/2�������, Para�ο�: MCO1/2����Para����
*                        CMD_SYSLIB_READ_MCUID: ��ȡMCUΨһ��IDֵ: 96λ��12�ֽ�, ParaĬ��0;
*         Para: ���Ʋ��� 
*
* Output: none;
*          		
* Return: ���CMD_SYSLIB_RESET/CMD_MCO1/CMD_MCO2: ���أ�ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*               CMD_SYSLIB_READ_DATE/CMD_SYSLIB_READ_MCUID: �����ַ���ָ��/12�ֽ�ָ��
*               CMD_SYSLIB_READ_VERSION�����ذ汾��ֵ
*
* Note:   none;
************************************************************************************/
INT32S SysLib_Ctrl(INT8U Cmd, INT32U Para);

#endif                                                          
