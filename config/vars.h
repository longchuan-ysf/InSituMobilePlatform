/************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: vars.h
* Project  : STM32F1XX/4XXϵ��ģ�����
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.00
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: ���ļ��������������ܹ���ȫ�ֱ�������ͷ�ļ�, �ͻ����ɸ���;
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
#ifndef __VARS_H 
#define __VARS_H 
/************************************************************************************/
// �����ⲿͷ�ļ�
/************************************************************************************/
#include "config.h"	  
#include "modbus.h"
#include "net.h"

/************************************************************************************/
//  ISRHook.c�ļ���ӡ�����Ϣ���涨��,�����޸�
/************************************************************************************/
#if (DEBUG_ISRHOOK_EN>0)
typedef struct
{
    INT8U  len;                // ��ӡ��Ϣ����
    INT8U  buf[DEBUG_INFO_LEN];  // ��ӡ�����Ϣ����
}DEBUG_INFO;

extern DEBUG_INFO  DebugInfo;
#endif
/************************************************************************************/
//  ADC���ջ���,�����޸�
/************************************************************************************/
#if (ADC_EN>0)
extern INT16S ADC_Buffer[ADC_AVGNUM][ADC_CHNUM];  // ADC1��������FIFO(����)
extern INT8U  AITab[];                            // AI����ɼ�˳���
#endif

/************************************************************************************/
//  DAC1,DAC2���ͻ��涨��,�����޸�
/************************************************************************************/
#if ((DAC1_EN>0)&&(DAC1_MODE>0))
extern INT16U  DAC1_Buffer[DAC1_TXBUF_SIZE];  // DAC1�������ݻ���
#endif
#if ((DAC2_EN>0)&&(DAC2_MODE>0))
extern INT16U  DAC2_Buffer[DAC2_TXBUF_SIZE];  // DAC2�������ݻ���
#endif

/************************************************************************************/
// UART1 ���ͽ��ջ��涨��,�����޸�
/************************************************************************************/
#if (UART1_EN > 0)
extern INT8U Uart1_RxBuffer[]; 	    // �������ݻ���
extern INT8U  Uart1_TxBuffer[]; 	// �������ݻ���
#endif

/************************************************************************************/
// UART2 ���ͽ��ջ��涨��,�����޸�
/************************************************************************************/
#if (UART2_EN > 0)
extern INT8U Uart2_RxBuffer[]; 	    // �������ݻ���
extern INT8U Uart2_TxBuffer[]; 		// �������ݻ���
#endif

/************************************************************************************/
// UART3 ���ͽ��ջ��涨��,�����޸�
/************************************************************************************/
#if (UART3_EN > 0)
extern INT8U Uart3_RxBuffer[]; 	    // �������ݻ���
extern INT8U Uart3_TxBuffer[]; 		// �������ݻ���
#endif

/************************************************************************************/
// UART4 ���ͽ��ջ��涨��,�����޸�
/************************************************************************************/
#if (UART4_EN > 0)
extern INT8U Uart4_RxBuffer[]; 	    // �������ݻ���
extern INT8U Uart4_TxBuffer[]; 		// �������ݻ���
#endif

/************************************************************************************/
// UART5 ���ͽ��ջ��涨��,�����޸�
/************************************************************************************/
#if (UART5_EN > 0)
extern INT8U Uart5_RxBuffer[]; 	    // �������ݻ���
extern INT8U Uart5_TxBuffer[]; 		// �������ݻ���
#endif

/************************************************************************************/
// UART6 ���ͽ��ջ��涨��,�����޸�
/************************************************************************************/
#if (MODULE_CLASS == STM32F407XX)
#if (UART6_EN > 0)
extern INT8U Uart6_RxBuffer[]; 	    // �������ݻ���
extern INT8U Uart6_TxBuffer[]; 		// �������ݻ���
#endif
#endif
/************************************************************************************/
//  FCLK ������������
/************************************************************************************/
// FCLK1����
#if ((FCLK1_EN > 0)&&((FCLK1_MODE == 2)||(FCLK1_MODE == 3)))
    #if (FCLK1CH1_EN > 0)
    extern INT16U FClk1CH1Buf[];
    #endif
    #if (FCLK1CH2_EN > 0)
    extern INT16U FClk1CH2Buf[];
    #endif
    #if (FCLK1CH3_EN > 0)
    extern INT16U FClk1CH3Buf[];
    #endif
    #if (FCLK1CH4_EN > 0)
    extern INT16U FClk1CH4Buf[];
    #endif
#endif
								 
// FCLK2����
#if ((FCLK2_EN > 0)&&((FCLK2_MODE == 2)||(FCLK2_MODE == 3)))
    #if (FCLK2CH1_EN > 0)
    extern INT16U FClk2CH1Buf[];
    #endif
    #if (FCLK2CH2_EN > 0)
    extern INT16U FClk2CH2Buf[];
    #endif
    #if (FCLK2CH3_EN > 0)
    extern INT16U FClk2CH3Buf[];
    #endif
    #if (FCLK2CH4_EN > 0)
    extern INT16U FClk2CH4Buf[];
    #endif
#endif

// FCLK3����
#if ((FCLK3_EN > 0)&&((FCLK3_MODE == 2)||(FCLK3_MODE == 3)))
    #if (FCLK3CH1_EN > 0)
    extern INT16U FClk3CH1Buf[];
    #endif
    #if (FCLK3CH2_EN > 0)
    extern INT16U FClk3CH2Buf[];
    #endif
    #if (FCLK3CH3_EN > 0)
    extern INT16U FClk3CH3Buf[];
    #endif
    #if (FCLK3CH4_EN > 0)
    extern INT16U FClk3CH4Buf[];
    #endif
#endif
																		
// FCLK4����
#if ((FCLK4_EN > 0)&&((FCLK4_MODE == 2)||(FCLK4_MODE == 3)))
    #if (FCLK4CH1_EN > 0)
    extern INT16U FClk4CH1Buf[];
    #endif    
    #if (FCLK4CH2_EN > 0)
    extern INT16U FClk4CH2Buf[];
    #endif
    #if (FCLK4CH3_EN > 0)
    extern INT16U FClk4CH3Buf[];
    #endif
    #if (FCLK4CH4_EN > 0)
    extern INT16U FClk4CH4Buf[];
    #endif
#endif

#if (MODULE_CLASS == STM32F407XX)
// FCLK5����
#if ((FCLK5_EN > 0)&&((FCLK5_MODE == 2)||(FCLK5_MODE == 3)))
    #if (FCLK5CH1_EN > 0)
    extern INT16U FClk5CH1Buf[];
    #endif    
    #if (FCLK5CH2_EN > 0)
    extern INT16U FClk5CH2Buf[];
    #endif
#endif

// FCLK6����
#if ((FCLK6_EN > 0)&&((FCLK6_MODE == 2)||(FCLK6_MODE == 3)))
    #if (FCLK6CH1_EN > 0)
    extern INT16U FClk6CH1Buf[];
    #endif    
    #if (FCLK6CH2_EN > 0)
    extern INT16U FClk6CH2Buf[];
    #endif
#endif

// FCLK7����
#if ((FCLK7_EN > 0)&&((FCLK7_MODE == 2)||(FCLK7_MODE == 3)))
    #if (FCLK7CH1_EN > 0)
    extern INT16U FClk7CH1Buf[];
    #endif    
    #if (FCLK7CH2_EN > 0)
    extern INT16U FClk7CH2Buf[];
    #endif
#endif

#endif

/************************************************************************************/
//  CAN1, CAN2 ͨ������,�����޸�
/************************************************************************************/
// CAN1, CAN2�˲������涨��
#if ((CAN1_EN > 0)||(CAN2_EN > 0)) 
extern INT32U CAN_FilterBuf[]; // �˲�������
#endif		

// CAN1���涨��
#if (CAN1_EN > 0)
extern CAN_BUF_MSG CAN1_RxBuffer[];     // CAN1���ջ���
extern CAN_BUF_MSG CAN1_TxBuffer[];     // CAN1���ͻ���	 
#endif		

// CAN2���涨��
#if (CAN2_EN > 0)
extern CAN_BUF_MSG CAN2_RxBuffer[];    // CAN2���ջ���
extern CAN_BUF_MSG CAN2_TxBuffer[];    // CAN2���ͻ���
#endif 

/************************************************************************************/
// MODBUS �ӻ�ͨ������
/************************************************************************************/
#if (MODBUS_SLAVE_EN > 0)		
extern MODBUS_DATA ModbusData;                               // �������� 
extern INT8U ModbusCoils[(MODBUS_MAX_COILS-1)/8 + 1];        // �����Ȧ����
extern INT8U ModbusDisInput[(MODBUS_MAX_DISINPUT-1)/8 + 1];  // ������ɢ����������
extern INT16U ModbusHoldReg[MODBUS_MAX_HOLDREG];             // ���ּĴ���
extern INT16U ModbusInputReg[MODBUS_MAX_INPUTREG];           // ����Ĵ���
extern MODBUS_PARA ModbusPara;                               // ��������  
#endif
/************************************************************************************/
// TCPIP(LWIP)Э��ջ����
/************************************************************************************/
#if ((MODULE_CLASS == STM32F107XX)||(MODULE_CLASS == STM32F407XX))
#if (LWIP_EN > 0)
extern ETH_DMADESCTypeDef  DMARxDscrTab[];
extern ETH_DMADESCTypeDef  DMATxDscrTab[];
extern INT8U ETH_RxBuffer[ETH_RXBUFNB][ETH_MAX_RX_PACKET_SIZE];
extern INT8U ETH_TxBuffer[ETH_TXBUFNB][ETH_MAX_TX_PACKET_SIZE];
#endif
#endif


/************************************************************************************/
// USB�豸 ���⴮�ڷ��ͽ��ջ��涨��,�����޸�
/************************************************************************************/
#if (USB_VCP_EN > 0)
extern INT8U USB_RxBuffer[]; 	  // �������ݻ���
#endif

/************************************************************************************/
//  SPI FLASH(W25QXX)���涨��,�����޸�
/************************************************************************************/
#if ((SPIFLASH_EN > 0)&&(SPIFLASH_TYPE == W25QXX)&&(SPIFLASH_MODE==1))
extern INT8U  W25QBuf[];   // ����
#endif

/************************************************************************************/
// NAND FLASH��������
/************************************************************************************/
#if (NFLASH_EN > 0)
extern INT8U  NFlashBadBlkFlag[];                // NAND������
extern INT16U NFlashBadTab[];	                  // NAND�����滻��
extern INT8U  NFlashBlkBuffer[NFLASH_BLOCK_SIZE][NFLASH_PAGE_SIZE] EXRAM;	 // NAND�黺��
extern INT8U  NFlashBlkSpareBuffer[NFLASH_BLOCK_SIZE][64] EXRAM;	       // NAND�黺��, ��������
#endif

#endif
/***********************************************************************************/
// �ļ�����
/***********************************************************************************/
