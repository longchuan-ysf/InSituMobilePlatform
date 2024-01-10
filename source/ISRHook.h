/************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: ISRHook.h
* Project  : STM32F107VC/103VE/407VEģ��������
* Processor: STM32F107VC/103VE/407VE
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.00
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: ���ļ���������ϵͳ�жϴ�����ͷ�ļ�;
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
#include "const.h"
#include "config.h"
/************************************************************************************/
/************************************************************************************/
/************************************************************************************
// ������ȫ�ֱ�������
*************************************************************************************/

/************************************************************************************
//
//                 �жϵĹ��Ӻ���
//
*************************************************************************************/
/***********************************************************************************
* Function: Uart1_ISRHook,Uart2_ISRHook,Uart3_ISRHook,Uart4_ISRHook,Uart5_ISRHook,Uart6_ISRHook;
*
* Description: ���º�����Uart1,Uart2,Uart3,Uart4,Uart5�жϼ��������ݵĹ��Ӻ���;
*           
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   ������ֻ�ܸ��ݴ���״̬UartSR��д�������ݳ���, �����������ڲ��ж�ʵ��;
************************************************************************************/
extern void Uart1_ISRHook(INT16U UartSR, INT16U Data);
extern void Uart2_ISRHook(INT16U UartSR, INT16U Data);
extern void Uart3_ISRHook(INT16U UartSR, INT16U Data);
extern void Uart4_ISRHook(INT16U UartSR, INT16U Data);
extern void Uart5_ISRHook(INT16U UartSR, INT16U Data);
#if (MODULE_CLASS == STM32F407XX)
extern void Uart6_ISRHook(INT16U UartSR, INT16U Data);
#endif

/***********************************************************************************
* Function: SPI1_ISRHook,SPI2_ISRHook,SPI2_ISRHook;
*
* Description: ���º�����SPI1,SPI2,SPI3���Ӻ���;
*           
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
extern void SPI1_ISRHook(INT32U flag);
extern void SPI2_ISRHook(INT32U flag);
extern void SPI3_ISRHook(INT32U flag);

/***********************************************************************************
* Function: RTC_ISRHook;
*
* Description: ���º�����RTC�жϵĹ��Ӻ���;
*           
* Input:  flag, �жϱ�־; cnt, RTC 32λ������ֵ
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
#if ((MODULE_CLASS == STM32F107XX)||(MODULE_CLASS == STM32F103XX))
extern void RTC_ISRHook(INT8U flag, INT32U cnt);
#endif

/***********************************************************************************
* Function: TIM1_BRK_ISRHook, TIM1_UP_ISRHook, TIM1_TRG_COM_ISRHook, TIM1_CC_ISRHook, 
*			TIM8_BRK_ISRHook, TIM8_UP_ISRHook, TIM8_TRG_COM_ISRHook, TIM8_CC_ISRHook
*
* Description: ��������TIM1��TIM8�жϹ��Ӻ���;
*           
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
extern void TIM1_BRK_ISRHook(INT32U flag);     // TIM1 Break  Interrupt
extern void TIM1_UP_ISRHook(INT32U flag);	  // TIM1 Update Interrupt
extern void TIM1_TRG_COM_ISRHook(INT32U flag); // TIM1 Trig & Commutation Interrupts
extern void TIM1_CC_ISRHook(INT32U flag);	  // TIM1 Capture Compare Interrupt

#if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F407XX))
extern void TIM8_BRK_ISRHook(INT32U flag);	  // TIM8 Break  Interrupt
extern void TIM8_UP_ISRHook(INT32U flag);	  // TIM8 Update Interrupt
extern void TIM8_TRG_COM_ISRHook(INT32U flag); // TIM8 Trig & Commutation Interrupts
extern void TIM8_CC_ISRHook(INT32U flag);	  // TIM8 Capture Compare Interrupt
#endif
/***********************************************************************************
* Function: TIM2_ISRHook, TIM3_ISRHook, TIM4_ISRHook, 
*			TIM5_ISRHook, TIM6_ISRHook, TIM7_ISRHook
*
* Description: ��������TIM2~TIM7�жϹ��Ӻ���;
*           
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
extern void TIM2_ISRHook(INT32U flag);		 // TIM2 Global Interrupt
extern void TIM3_ISRHook(INT32U flag);		 // TIM3 Global Interrupt
extern void TIM4_ISRHook(INT32U flag);		 // TIM4 Global Interrupt
extern void TIM5_ISRHook(INT32U flag);		 // TIM5 Global Interrupt
extern void TIM6_ISRHook(INT32U flag);		 // TIM6 Global Interrupt
extern void TIM7_ISRHook(INT32U flag);		 // TIM7 Global Interrupt

/***********************************************************************************
* Function: TIM9_ISRHook, TIM10_ISRHook, TIM11_ISRHook, 
*			TIM12_ISRHook, TIM13_ISRHook, TIM14_ISRHook
*
* Description: ��������TIM9~TIM14�жϹ��Ӻ���;
*           
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
#if (MODULE_CLASS == STM32F407XX)
extern void TIM9_ISRHook(INT32U flag);		 // TIM9 Global Interrupt
extern void TIM10_ISRHook(INT32U flag);		 // TIM10 Global Interrupt
extern void TIM11_ISRHook(INT32U flag);		 // TIM11 Global Interrupt
extern void TIM12_ISRHook(INT32U flag);		 // TIM12 Global Interrupt
extern void TIM13_ISRHook(INT32U flag);		 // TIM13 Global Interrupt
extern void TIM14_ISRHook(INT32U flag);		 // TIM14 Global Interrupt
#endif


/***********************************************************************************
* Function: EXTI16_PVD_ISRHook, EXTI17_RTCAlarm_ISRHook, EXTI8_USBWakeUp_ISRHook,
*           EXTI19_NETWakeUp_ISRHook;
*
* Description: ���º�����EXTI16~EXTI19�жϵĹ��Ӻ���;
*           
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
extern void EXTI16_PVD_ISRHook(INT32U Flag);
extern void EXTI17_RTCAlarm_ISRHook(INT32U Flag);
extern void EXTI18_USBWakeUp_ISRHook(INT32U Flag);
extern void EXTI19_NETWakeUp_ISRHook(INT32U Flag);
#if (MODULE_CLASS == STM32F407XX)
void  EXTI20_USBHSWakeUp_ISRHook(INT32U Flag);
void  EXTI21_RTCTSE_ISRHook(INT32U Flag);
void  EXTI22_RTCWakeUp_ISRHook(INT32U Flag);
#endif
/***********************************************************************************
* Function: EXTI0_ISRHook, EXTI1_ISRHook, EXTI2_ISRHook, EXTI3_ISRHook;
*           EXTI4_ISRHook, EXTI5_ISRHook, EXTI6_ISRHook, EXTI7_ISRHook,
*           EXTI8_ISRHook, EXTI9_ISRHook, EXTI10_ISRHook, EXTI11_ISRHook,
*           EXTI12_ISRHook, EXTI13_ISRHook, EXTI14_ISRHook, EXTI15_ISRHook,
*
* Description: ���º������ⲿIO 16���жϺ���;
*           
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
extern void EXTI0_ISRHook(void);
extern void EXTI1_ISRHook(void);
extern void EXTI2_ISRHook(void);
extern void EXTI3_ISRHook(void);
extern void EXTI4_ISRHook(void);
extern void EXTI5_ISRHook(void);
extern void EXTI6_ISRHook(void);
extern void EXTI7_ISRHook(void);
extern void EXTI8_ISRHook(void);
extern void EXTI9_ISRHook(void);
extern void EXTI10_ISRHook(void);
extern void EXTI11_ISRHook(void);
extern void EXTI12_ISRHook(void);
extern void EXTI13_ISRHook(void);
extern void EXTI14_ISRHook(void);
extern void EXTI15_ISRHook(void);

/***********************************************************************************
* Function: SysTickHandler_ISR,PendSVHandler_ISR,NMIHandler_ISR,FaultHandler_ISR;
*           MemFaultHandler_ISR,BusFaultHandler_ISR,UsageFaultHandler_ISR,SpuriousHandler_ISR
*
* Description: ϵͳ�쳣�жϴ�����;
*              
* Input:  none;
*
* Output: none;
*
* Return: none;
*
* Note:   none;
************************************************************************************/
extern void SysTickHandler_ISR(void);
extern void PendSVHandler_ISR(void);
extern void NMIHandler_ISR(void);
extern void FaultHandler_ISR(void);
extern void MemFaultHandler_ISR(void);
extern void BusFaultHandler_ISR(void);
extern void UsageFaultHandler_ISR(void);
extern void SpuriousHandler_ISR(void);   

/***********************************************************************************
* Function: ADC_ISRHook;
*
* Description: ADC�жϴ�����ɻص�����;
*              
* Input:  none;
*
* Output: none;
*
* Return: none;
*
* Note:   none;
************************************************************************************/
extern void  ADC_ISRHook(ADC_VAR *pData);

/***********************************************************************************
* Function: CAN1TX_ISRHook;
*
* Description: ��������CAN1���������жϹ��Ӻ���;
*           
* Input:  val, ���ͻ����л��ж���������δ����;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
extern void CAN1TX_ISRHook(INT32U val);

/***********************************************************************************
* Function: CAN1RX0_ISRHook;
*
* Description: ��������CAN1 RX0�����жϹ��Ӻ���;
*           
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
extern void CAN1RX0_ISRHook(INT32U val);

/***********************************************************************************
* Function: CAN1RX1_ISRHook;
*
* Description: ��������CAN1 RX1�����жϹ��Ӻ���;
*           
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
extern void CAN1RX1_ISRHook(INT32U val);

/***********************************************************************************
* Function: CAN1SCE_ISRHook;
*
* Description: ��������CAN1�����״̬�仯�жϹ��Ӻ���;
*           
* Input:  val, �������;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
extern void CAN1SCE_ISRHook(INT32U val);

/***********************************************************************************
* Function: CAN2TX_ISRHook;
*
* Description: ��������CAN2���������жϹ��Ӻ���;
*           
* Input:  val, ���ͻ����л��ж���������δ����;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
extern void CAN2TX_ISRHook(INT32U val);

/***********************************************************************************
* Function: CAN2RX0_ISRHook;
*
* Description: ��������CAN2 RX0�����жϹ��Ӻ���;
*           
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
extern void CAN2RX0_ISRHook(INT32U val);

/***********************************************************************************
* Function: CAN2RX1_ISRHook;
*
* Description: ��������CAN2 RX1�����жϹ��Ӻ���;
*           
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
extern void CAN2RX1_ISRHook(INT32U val);

/***********************************************************************************
* Function: CAN2SCE_ISRHook;
*
* Description: ��������CAN2�����״̬�仯�жϹ��Ӻ���;
*           
* Input:  val, �������;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
extern void CAN2SCE_ISRHook(INT32U val);

/***********************************************************************************
* Function: USBD_ISRHook;
*
* Description: USB Device�жϹ��Ӻ���;
*              
* Input:  flag, �жϱ�־;
*
* Output: none;
*
* Return: ERR_TRUE,�ɹ�; ERR_FALSE,ʧ��;
*
* Note:   none;
************************************************************************************/
INT32S USBD_ISRHook(INT32U flag);		 // USB Device�жϹ��Ӻ���

/***********************************************************************************
* Function: USBH_ISRHook;
*
* Description: USB Host�жϹ��Ӻ���;
*              
* Input:  flag, �жϱ�־;
*
* Output: none;
*
* Return: none;
*
* Note:   none;
************************************************************************************/
extern void USBH_ISRHook(INT32U flag);		 // USB Host�жϹ��Ӻ���

/***********************************************************************************
* Function: OSIntEnterHook;
*
* Description: ���⺯�����õĽ������ϵͳ���жϺ���;
*              
* Input:  none;
*
* Output: none;
*
* Return: none;
*
* Note:   none;
************************************************************************************/
extern void OSIntEnterHook(void);

/***********************************************************************************
* Function: OSIntExitHook;
*
* Description: ���⺯�����õ��˳�����ϵͳ���жϺ���;
*              
* Input:  none;
*
* Output: none;
*
* Return: none;
*
* Note:   none;
************************************************************************************/
extern void OSIntExitHook(void);

/***********************************************************************************
* Function: OSDelay_ms;
*
* Description: ��ʱ����, ��ʱʱ�䷶Χ: 0~65535ms;
*              
* Input:  val, ��ʱʱ�����, ��λ��ms;
*
* Output: none;
*
* Return: none;
*
* Note:   none;
************************************************************************************/
extern void OSDelay_ms(INT16U val);

/***********************************************************************************
* Function: SPI_RequestOSSem;
*
* Description: �����ϵͳ����SPI����Ȩ��;
*              
* Input:  timeout, ��ʱʱ�䷵��;
*
* Output: none;
*
* Return: ERR_TRUE, ����ɹ�; TIMEOUT, ��ʱ�˳�,����ʧ��;	ERR_FALSE, ����ʧ��;
*
* Note:   none;
************************************************************************************/
extern INT32S SPI_RequestOSSem(INT16U timeout);

/***********************************************************************************
* Function: SPI_ReleaseOSSem;
*
* Description: �����ϵ�ͷ�SPI����Ȩ��;
*              
* Input:  none;
*
* Output: none;
*
* Return: ERR_TRUE, ����ɹ�; ERR_FALSE, �ͷ�ʧ��;
*
* Note:   none;
************************************************************************************/
extern INT32S SPI_ReleaseOSSem(void);

#if (MODULE_TYPE == STM32F103ZE)

/***********************************************************************************
* Function: FSMC_ISRHook;
*
* Description: ������FSMC�жϴ�����;
*           
* Input:  inr���ж���Դ, 2��BANK2�ж�; 3��BANK3�ж�; 4��BANK4�ж�;;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
extern void FSMC_ISRHook(INT16U flag);

/***********************************************************************************
* Function: FSMC_ISRRead;
*
* Description: ��ȡFSMC��Bank2, Bank3, Bank4״̬��������;
*              
* Input:  none;
*
* Output: none;
*
* Return: ERR_TRUE: �ɹ�;  ERR_FALSE: ʧ��;
*
* Note:   none;
************************************************************************************/
extern INT32S FSMC_ISRRead(INT16U flag);

/***********************************************************************************
* Function: NET_CreateOSSem;
*
* Description: �����ϵͳ����NET����Ȩ��;
*              
* Input:  timeout, ��ʱʱ�䷵��;
*
* Output: none;
*
* Return: ERR_TRUE, ����ɹ�; TIMEOUT, ��ʱ�˳�,����ʧ��;	ERR_FALSE, ����ʧ��;
*
* Note:   none;
************************************************************************************/
extern void NET_CreateOSSem(void);

/***********************************************************************************
* Function: NET_RequestOSSem;
*
* Description: �����ϵͳ����NET����Ȩ��;
*              
* Input:  timeout, ��ʱʱ�䷵��;
*
* Output: none;
*
* Return: ERR_TRUE, ����ɹ�; TIMEOUT, ��ʱ�˳�,����ʧ��;	ERR_FALSE, ����ʧ��;
*
* Note:   none;
************************************************************************************/
INT32S NET_RequestOSSem(INT16U timeout);

/***********************************************************************************
* Function: NET_ReleaseOSSem;
*
* Description: �����ϵ�ͷ�NET����Ȩ��;
*              
* Input:  none;
*
* Output: none;
*
* Return: ERR_TRUE, ����ɹ�; ERR_FALSE, �ͷ�ʧ��;
*
* Note:   none;
************************************************************************************/
INT32S NET_ReleaseOSSem(void);

/***********************************************************************************
* Function: NET_PendRXIntOSFlag;
*
* Description: �����ϵͳ������������жϱ�־;
*              
* Input:  timeout, ��ʱʱ�䷵��;
*
* Output: none;
*
* Return: ERR_TRUE, ����ɹ�; TIMEOUT, ��ʱ�˳�,����ʧ��;	ERR_FALSE, ����ʧ��;
*
* Note:   none;
************************************************************************************/
INT32S NET_PendRXIntOSFlag(INT16U timeout);

/***********************************************************************************
* Function: INT32S NET_PostRXIntOSFlag;
*
* Description: �����ϵͳ������������жϱ�־;;
*              
* Input:  none;
*
* Output: none;
*
* Return: ERR_TRUE, ����ɹ�; ERR_FALSE, �ͷ�ʧ��;
*
* Note:   none;
************************************************************************************/
INT32S NET_PostRXIntOSFlag(void);

#endif
/***********************************************************************************
* Function: OSMalloc;
*
* Description: ��̬�ڴ����뺯��;
*              
* Input:  len, �����ڴ泤��, ��λ: �ֽ�;
*
* Output: none;
*
* Return: �ڴ���ʼ��ַָ��;
*
* Note:   �˺�������Ҫ����OSMboxMalloc����, ����ʼ��Ϊ1; ��������ڴ��ַΪ0, ������ʧ��;
************************************************************************************/
extern void *OSMalloc(INT16U len);

/***********************************************************************************
* Function: OSFree;
*
* Description: ��̬�ڴ��ͷź���;
*              
* Input:  *p, �ͷ��ڴ���ʼ��ַָ��
*
* Output: none;
*
* Return: ERR_TRUE:�ͷųɹ�;  ERR_FALSE:�ͷ�ʧ��;
*
* Note:   �˺�������Ҫ����OSMboxFree����, ����ʼ��Ϊ1;
************************************************************************************/
extern INT32S OSFree(void *p);
/***********************************************************************************
* Function: PWM_ISRHook;
*
* Description: PWM�����ɻ�����жϵĹ��Ӻ���;
*           
* Input:  id: PWM����ID, PWM1_ID~PWM8_ID 
*         flag: �жϱ�־
*         PWMCH1_OK_FLAG: PWM CH1����������ɱ�־;
*         PWMCH2_OK_FLAG: PWM CH2����������ɱ�־;
*         PWMCH3_OK_FLAG: PWM CH3����������ɱ�־;
*         PWMCH4_OK_FLAG: PWM CH4����������ɱ�־;
*         PWMCH1_ERR_FLAG: PWM CH1��������ʧ�ܱ�־;
*         PWMCH2_ERR_FLAG: PWM CH2��������ʧ�ܱ�־;
*         PWMCH3_ERR_FLAG: PWM CH3��������ʧ�ܱ�־;
*         PWMCH4_ERR_FLAG: PWM CH4��������ʧ�ܱ�־;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
extern void PWM_ISRHook(INT8U id, INT32U flag);
/***********************************************************************************
* Function: DMA1_ISRHook, DMA2_ISRHook;
*
* Description: ���º�����DMA1,DMA2�жϵĹ��Ӻ���;
*           
* Input:  ch: ͨ��0(DMA_CH1)~8(DMA_CH8)
*         flag: �ж����: DMA_IT_TC, ��������жϱ�־
*                         DMA_IT_HT, �봫������жϱ�־
*                         DMA_IT_TERR, ��������жϱ�־
*                         DMA_IT_FIFOERR, ������FIFO�����־   
*                         DMA_IT_DERR, ������ֱ�Ӵ����־
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
extern void DMA1_ISRHook(INT8U ch, INT32U flag);
extern void DMA2_ISRHook(INT8U ch, INT32U flag);

/***********************************************************************************
* Function: API_OSFlagPostHook;
*
* Description: ���������õȴ���־����;
*              
* Input:  flag: �ȴ���־, ��const.h�ж���
*
* Output: none;
*
* Return: none;
*
* Note:   �������ֻ�ṩ���������жϵ���, ���û���Ҫ�޸ĸú���;
************************************************************************************/
extern void API_OSFlagPostHook(INT32U flag);

/***********************************************************************************
* Function: API_OSFlagPendHook;
*
* Description: �������ȡ�ȴ���־����;
*              
* Input:  flag: �ȴ���־, ��const.h�ж���
*         TimeOut: ��ʱʱ��, ��λms, ���Ϊ0������Ϊ0xFFFFFFFF, �������ߵȴ�
*
* Output: none;
*
* Return: ERR_TRUE: �ɹ�;  ERR_FALSE: ʧ��; ERR_TIMEOUT: ��ʱʧ��;
*
* Note:   �������ֻ�ṩ�����������, ���û���Ҫ�޸ĸú���;
************************************************************************************/
extern API_OSFlagPendHook(INT32U flag, INT32U TimeOut);

/***********************************************************************************/
// �ļ�����
/***********************************************************************************/

/***********************************************************************************
* Function: I2C1_ISRHook,I2C1_ER_ISRHook,I2C2_ISRHook,I2C2_ER_ISRHook,;
*
* Description: ���º�����I2C1,I2C2�жϵĹ��Ӻ���;
*           
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
//extern void I2C1_ISRHook(void);
//extern void I2C1_ER_ISRHook(void);
//extern void I2C2_ISRHook(void);
//extern void I2C2_ER_ISRHook(void);

/***********************************************************************************
* Function: SPI1_ISRHook,SPI2_ISRHook,SPI2_ISRHook;
*
* Description: ���º�����SPI1,SPI2,SPI3�жϵĹ��Ӻ���;
*           
* Input:  none;
*
* Output: none;
*          		
* Return: ERR_TRUE, ִ���������е��жϴ���;	ERR_FALSE, ��ִ���������е��жϴ���;
*
* Note:   ��ͻ������Լ�������жϣ���ѡ��ERR_TRUE����;
************************************************************************************/
//extern INT32S SPI1_ISRHook(void);
//extern INT32S SPI2_ISRHook(void);
//extern INT32S SPI3_ISRHook(void);