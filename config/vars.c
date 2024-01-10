 /************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: vars.c
* Project  : STM32F1XX/4XXϵ��ģ�����
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.00
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: ���ļ��������������ܹ���ȫ�ֱ�������, �ͻ����ɸ���;
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
#include "config.h"
#include "net.h"
#include "modbus.h"
#include "vars.h"

/************************************************************************************/
//  ISRHook.c�ļ���ӡ�����Ϣ���涨��,�����޸�
/************************************************************************************/
#if (DEBUG_ISRHOOK_EN>0)
DEBUG_INFO  DebugInfo;
#endif  
/************************************************************************************/
//  ADC���ջ��涨��,�����޸�
/************************************************************************************/
#if (ADC_EN>0)
INT16S ADC_Buffer[ADC_AVGNUM][ADC_CHNUM];  // ADC��������FIFO(����)
INT8U  AITab[16];                  // AI����ɼ�˳���
#endif    

/************************************************************************************/
//  DAC1,DAC2���ͻ��涨��,�����޸�
/************************************************************************************/
#if ((DAC1_EN>0)&&(DAC1_MODE>0))
INT16U  DAC1_Buffer[DAC1_TXBUF_SIZE];       // DAC1�������ݻ���
#endif

#if ((DAC2_EN>0)&&(DAC2_MODE>0))
INT16U  DAC2_Buffer[DAC2_TXBUF_SIZE]; 	    // DAC2�������ݻ���
#endif

/************************************************************************************/
// UART1 ���ͽ��ջ��涨��,�����޸�
/************************************************************************************/
#if (UART1_EN > 0)
INT8U Uart1_RxBuffer[UART1_RXBUF_SIZE]; 	      // �������ݻ���
INT8U Uart1_TxBuffer[UART1_TXBUF_SIZE]; 	      // �������ݻ���
#endif
/************************************************************************************/
// UART2 ���ͽ��ջ��涨��,�����޸�
/************************************************************************************/
#if (UART2_EN > 0)
INT8U Uart2_RxBuffer[UART2_RXBUF_SIZE]; 	      // �������ݻ���
INT8U Uart2_TxBuffer[UART2_TXBUF_SIZE]; 		  // �������ݻ���
#endif

/************************************************************************************/
// UART3 ���ͽ��ջ��涨��,�����޸�
/************************************************************************************/
#if (UART3_EN > 0)
INT8U Uart3_RxBuffer[UART3_RXBUF_SIZE]; 	      // �������ݻ���
INT8U Uart3_TxBuffer[UART3_TXBUF_SIZE]; 		  // �������ݻ���
#endif

/************************************************************************************/
// UART4 ���ͽ��ջ��涨��,�����޸�
/************************************************************************************/
#if (UART4_EN > 0)
INT8U Uart4_RxBuffer[UART4_RXBUF_SIZE]; 	      // �������ݻ���
INT8U Uart4_TxBuffer[UART4_TXBUF_SIZE]; 		  // �������ݻ���
#endif

/************************************************************************************/
// UART5 ���ͽ��ջ��涨��,�����޸�
/************************************************************************************/
#if (UART5_EN > 0)
INT8U Uart5_RxBuffer[UART5_RXBUF_SIZE]; 	      // �������ݻ���
INT8U Uart5_TxBuffer[UART5_TXBUF_SIZE]; 		  // �������ݻ���
#endif
		
/************************************************************************************/
// UART6 ���ͽ��ջ��涨��,�����޸�
/************************************************************************************/
#if (MODULE_CLASS == STM32F407XX)
#if (UART6_EN > 0)
INT8U Uart6_RxBuffer[UART6_RXBUF_SIZE]; 	      // �������ݻ���
INT8U Uart6_TxBuffer[UART6_TXBUF_SIZE]; 		  // �������ݻ���
#endif
#endif
/************************************************************************************/
//  FCLK ������������, 
/************************************************************************************/
// FCLK1����
#if ((FCLK1_EN > 0)&&((FCLK1_MODE == 2)||(FCLK1_MODE == 3)))
#if ((MODULE_CLASS == STM32F407XX)&&((FCLK1_TIM == TIM2_ID)||(FCLK1_TIM == TIM5_ID))) // STM32F407XXϵ��TIM2��TIM5��������32λ, ���Ի����С����2
    #if (FCLK1CH1_EN > 0)
    #if (FCLK1_MODE == 3) // ����ռ�ձ�, CH1����ӱ�
    INT16U FClk1CH1Buf[FCLK1CH1_BUF_SIZE*4];
    #else
    INT16U FClk1CH1Buf[FCLK1CH1_BUF_SIZE*2];
    #endif
    #endif
    #if (FCLK1CH2_EN > 0)
    INT16U FClk1CH2Buf[FCLK1CH2_BUF_SIZE*2];
    #endif
    #if (FCLK1CH3_EN > 0)
    INT16U FClk1CH3Buf[FCLK1CH3_BUF_SIZE*2];
    #endif
    #if (FCLK1CH4_EN > 0)
    INT16U FClk1CH4Buf[FCLK1CH4_BUF_SIZE*2];
    #endif
#else
    #if (FCLK1CH1_EN > 0)
    #if (FCLK1_MODE == 3) // ����ռ�ձ�, CH1����ӱ�
    INT16U FClk1CH1Buf[FCLK1CH1_BUF_SIZE*2];
    #else
    INT16U FClk1CH1Buf[FCLK1CH1_BUF_SIZE];
    #endif
    #endif
    #if (FCLK1CH2_EN > 0)
    INT16U FClk1CH2Buf[FCLK1CH2_BUF_SIZE];
    #endif
    #if (FCLK1CH3_EN > 0)
    INT16U FClk1CH3Buf[FCLK1CH3_BUF_SIZE];
    #endif
    #if (FCLK1CH4_EN > 0)
    INT16U FClk1CH4Buf[FCLK1CH4_BUF_SIZE];
    #endif
#endif
    
#endif
								 
// FCLK2����
#if ((FCLK2_EN > 0)&&((FCLK2_MODE == 2)||(FCLK2_MODE == 3)))
#if ((MODULE_CLASS == STM32F407XX)&&((FCLK2_TIM == TIM2_ID)||(FCLK2_TIM == TIM5_ID))) // STM32F407XXϵ��TIM2��TIM5��������32λ, ���Ի����С����2
    #if (FCLK2CH1_EN > 0)
    #if (FCLK1_MODE == 3) // ����ռ�ձ�, CH1����ӱ�
    INT16U FClk2CH1Buf[FCLK2CH1_BUF_SIZE*4];
    #else
    INT16U FClk2CH1Buf[FCLK2CH1_BUF_SIZE*2];
    #endif
    #endif
    #if (FCLK2CH2_EN > 0)
    INT16U FClk2CH2Buf[FCLK2CH2_BUF_SIZE*2];
    #endif
    #if (FCLK2CH3_EN > 0)
    INT16U FClk2CH3Buf[FCLK2CH3_BUF_SIZE*2];
    #endif
    #if (FCLK2CH4_EN > 0)
    INT16U FClk2CH4Buf[FCLK2CH4_BUF_SIZE*2];
    #endif
#else
    #if (FCLK2CH1_EN > 0)
    #if (FCLK1_MODE == 3) // ����ռ�ձ�, CH1����ӱ�
    INT16U FClk2CH1Buf[FCLK2CH1_BUF_SIZE*2];
    #else
    INT16U FClk2CH1Buf[FCLK2CH1_BUF_SIZE];
    #endif
    #endif
    #if (FCLK2CH2_EN > 0)
    INT16U FClk2CH2Buf[FCLK2CH2_BUF_SIZE];
    #endif
    #if (FCLK2CH3_EN > 0)
    INT16U FClk2CH3Buf[FCLK2CH3_BUF_SIZE];
    #endif
    #if (FCLK2CH4_EN > 0)
    INT16U FClk2CH4Buf[FCLK2CH4_BUF_SIZE];
    #endif
#endif
#endif

// FCLK3����
#if ((FCLK3_EN > 0)&&((FCLK3_MODE == 2)||(FCLK3_MODE == 3)))
#if ((MODULE_CLASS == STM32F407XX)&&((FCLK3_TIM == TIM2_ID)||(FCLK3_TIM == TIM5_ID))) // STM32F407XXϵ��TIM2��TIM5��������32λ, ���Ի����С����2
    #if (FCLK3CH1_EN > 0)
    #if (FCLK1_MODE == 3) // ����ռ�ձ�, CH1����ӱ�
    INT16U FClk3CH1Buf[FCLK3CH1_BUF_SIZE*4];
    #else
    INT16U FClk3CH1Buf[FCLK3CH1_BUF_SIZE*2];
    #endif
    #endif
    #if (FCLK3CH2_EN > 0)
    INT16U FClk3CH2Buf[FCLK3CH2_BUF_SIZE*2];
    #endif
    #if (FCLK3CH3_EN > 0)
    INT16U FClk3CH3Buf[FCLK3CH3_BUF_SIZE*2];
    #endif
    #if (FCLK3CH4_EN > 0)
    INT16U FClk3CH4Buf[FCLK3CH4_BUF_SIZE*2];
    #endif
#else
    #if (FCLK3CH1_EN > 0)
    #if (FCLK1_MODE == 3) // ����ռ�ձ�, CH1����ӱ�
    INT16U FClk3CH1Buf[FCLK3CH1_BUF_SIZE*2];
    #else
    INT16U FClk3CH1Buf[FCLK3CH1_BUF_SIZE];
    #endif
    #endif
    #if (FCLK3CH2_EN > 0)
    INT16U FClk3CH2Buf[FCLK3CH2_BUF_SIZE];
    #endif
    #if (FCLK3CH3_EN > 0)
    INT16U FClk3CH3Buf[FCLK3CH3_BUF_SIZE];
    #endif
    #if (FCLK3CH4_EN > 0)
    INT16U FClk3CH4Buf[FCLK3CH4_BUF_SIZE];
    #endif
#endif
#endif
																		
// FCLK4����
#if ((FCLK4_EN > 0)&&((FCLK4_MODE == 2)||(FCLK4_MODE == 3)))
#if ((MODULE_CLASS == STM32F407XX)&&((FCLK4_TIM == TIM2_ID)||(FCLK4_TIM == TIM5_ID))) // STM32F407XXϵ��TIM2��TIM5��������32λ, ���Ի����С����2
    #if (FCLK4CH1_EN > 0)
    #if (FCLK1_MODE == 3) // ����ռ�ձ�, CH1����ӱ�
    INT16U FClk4CH1Buf[FCLK4CH1_BUF_SIZE*4];
    #else
    INT16U FClk4CH1Buf[FCLK4CH1_BUF_SIZE*2];
    #endif
    #endif    
    #if (FCLK4CH2_EN > 0)
    INT16U FClk4CH2Buf[FCLK4CH2_BUF_SIZE*2];
    #endif
    #if (FCLK4CH3_EN > 0)
    INT16U FClk4CH3Buf[FCLK4CH3_BUF_SIZE*2];
    #endif
    #if (FCLK4CH4_EN > 0)
    INT16U FClk4CH4Buf[FCLK4CH4_BUF_SIZE*2];
    #endif
#else
    #if (FCLK4CH1_EN > 0)
    #if (FCLK1_MODE == 3) // ����ռ�ձ�, CH1����ӱ�
    INT16U FClk4CH1Buf[FCLK4CH1_BUF_SIZE*2];
    #else
    INT16U FClk4CH1Buf[FCLK4CH1_BUF_SIZE];
    #endif
    #endif    
    #if (FCLK4CH2_EN > 0)
    INT16U FClk4CH2Buf[FCLK4CH2_BUF_SIZE];
    #endif
    #if (FCLK4CH3_EN > 0)
    INT16U FClk4CH3Buf[FCLK4CH3_BUF_SIZE];
    #endif
    #if (FCLK4CH4_EN > 0)
    INT16U FClk4CH4Buf[FCLK4CH4_BUF_SIZE];
    #endif
#endif
#endif

#if (MODULE_CLASS == STM32F407XX)
// FCLK5����
#if ((FCLK5_EN > 0)&&((FCLK5_MODE == 2)||(FCLK5_MODE == 3)))
    #if (FCLK5CH1_EN > 0)
    #if (FCLK1_MODE == 3) // ����ռ�ձ�, CH1����ӱ�
    INT16U FClk5CH1Buf[FCLK5CH1_BUF_SIZE*2];
    #else
    INT16U FClk5CH1Buf[FCLK5CH1_BUF_SIZE];
    #endif
    #endif    
    #if (FCLK5CH2_EN > 0)
    INT16U FClk5CH2Buf[FCLK5CH2_BUF_SIZE];
    #endif
#endif

// FCLK6����
#if ((FCLK6_EN > 0)&&((FCLK6_MODE == 2)||(FCLK6_MODE == 3)))
    #if (FCLK6CH1_EN > 0)
    #if (FCLK1_MODE == 3) // ����ռ�ձ�, CH1����ӱ�
    INT16U FClk6CH1Buf[FCLK6CH1_BUF_SIZE*2];
    #else
    INT16U FClk6CH1Buf[FCLK6CH1_BUF_SIZE];
    #endif
    #endif    
    #if (FCLK6CH2_EN > 0)
    INT16U FClk6CH2Buf[FCLK6CH2_BUF_SIZE];
    #endif
#endif

// FCLK7����
#if ((FCLK7_EN > 0)&&((FCLK7_MODE == 2)||(FCLK7_MODE == 3)))
    #if (FCLK7CH1_EN > 0)
    #if (FCLK1_MODE == 3) // ����ռ�ձ�, CH1����ӱ�
    INT16U FClk7CH1Buf[FCLK7CH1_BUF_SIZE*2];
    #else
    INT16U FClk7CH1Buf[FCLK7CH1_BUF_SIZE];
    #endif
    #endif    
    #if (FCLK7CH2_EN > 0)
    INT16U FClk7CH2Buf[FCLK7CH2_BUF_SIZE];
    #endif
#endif

#endif
																		 
/************************************************************************************/
//  CAN1, CAN2ͨ������,�����޸�
/************************************************************************************/
// CAN1, CAN2�˲������涨��
#if ((CAN1_EN > 0)||(CAN2_EN > 0)) 
INT32U CAN_FilterBuf[CAN_FILTER_MAXNUM*2]; // �˲�������
#endif

// CAN1���涨��
#if (CAN1_EN > 0)
CAN_BUF_MSG CAN1_RxBuffer[CAN1_RXBUF_SIZE];     // CAN1���ջ���
CAN_BUF_MSG CAN1_TxBuffer[CAN1_TXBUF_SIZE];     // CAN1���ͻ���	 
#endif
									
// CAN2���涨��
#if (CAN2_EN > 0)
CAN_BUF_MSG CAN2_RxBuffer[CAN2_RXBUF_SIZE];    // CAN2���ջ���
CAN_BUF_MSG CAN2_TxBuffer[CAN2_TXBUF_SIZE];    // CAN2���ͻ���
#endif

/************************************************************************************/
// MODBUS �ӻ�ͨ������
/************************************************************************************/
#if (MODBUS_SLAVE_EN > 0)
MODBUS_DATA ModbusData;                               // ��������  
INT8U  ModbusCoils[(MODBUS_MAX_COILS-1)/8 + 1];       // �����Ȧ����
INT8U  ModbusDisInput[(MODBUS_MAX_DISINPUT-1)/8 + 1]; // ������ɢ����������
INT16U ModbusHoldReg[MODBUS_MAX_HOLDREG];             // ���ּĴ���
INT16U ModbusInputReg[MODBUS_MAX_INPUTREG];           // ����Ĵ���
MODBUS_PARA ModbusPara;                               // ��������  
#endif

/************************************************************************************/
// TCPIP(LWIP)Э��ջ����
/************************************************************************************/
#if ((MODULE_CLASS == STM32F107XX)||(MODULE_CLASS == STM32F407XX))
#if (LWIP_EN > 0)
ETH_DMADESCTypeDef  DMARxDscrTab[ETH_RXBUFNB];
ETH_DMADESCTypeDef  DMATxDscrTab[ETH_TXBUFNB];
INT8U ETH_RxBuffer[ETH_RXBUFNB][ETH_MAX_RX_PACKET_SIZE];
INT8U ETH_TxBuffer[ETH_TXBUFNB][ETH_MAX_TX_PACKET_SIZE];
#endif
#endif
/************************************************************************************/
// USB�豸 ���⴮�ڷ��ͽ��ջ��涨��,�����޸�
/************************************************************************************/
#if (USB_VCP_EN > 0)
INT8U USB_RxBuffer[USB_RXBUF_SIZE]; 	      // �������ݻ���
#endif

/************************************************************************************/
//  SPI FLASH(W25QXX)���涨��,�����޸�
/************************************************************************************/
#if ((SPIFLASH_EN > 0)&&(SPIFLASH_TYPE == W25QXX)&&(SPIFLASH_MODE==1))
INT8U  W25QBuf[4096];   // ����
#endif

/************************************************************************************/
// NAND FLASH��������
/************************************************************************************/
#if (NFLASH_EN > 0)
INT8U  NFlashBadBlkFlag[(NFLASH_BLOCK_NUM+7)/8];                  // NAND������
INT16U NFlashBadTab[NFLASH_MAX_BAD_BLOCK];	                      // NAND�����滻��
INT8U  NFlashBlkBuffer[NFLASH_BLOCK_SIZE][NFLASH_PAGE_SIZE] EXRAM;	 // NAND�黺��
INT8U  NFlashBlkSpareBuffer[NFLASH_BLOCK_SIZE][64] EXRAM;	       // NAND�黺��, ��������
#endif
/***********************************************************************************/
// �ļ�����
/***********************************************************************************/
