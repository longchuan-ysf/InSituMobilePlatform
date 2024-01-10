/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: ISRHook.h
* Project  : STM32F107VC/103VE/407VE模块驱动库
* Processor: STM32F107VC/103VE/407VE
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.00
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: 本文件负责整个系统中断处理函数头文件;
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
// 引用外部头文件
#include "const.h"
#include "config.h"
/************************************************************************************/
/************************************************************************************/
/************************************************************************************
// 常量及全局变量定义
*************************************************************************************/

/************************************************************************************
//
//                 中断的钩子函数
//
*************************************************************************************/
/***********************************************************************************
* Function: Uart1_ISRHook,Uart2_ISRHook,Uart3_ISRHook,Uart4_ISRHook,Uart5_ISRHook,Uart6_ISRHook;
*
* Description: 以下函数是Uart1,Uart2,Uart3,Uart4,Uart5中断及接收数据的钩子函数;
*           
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   本函数只能根据串口状态UartSR编写接收数据程序, 发送数据由内部中断实现;
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
* Description: 以下函数是SPI1,SPI2,SPI3钩子函数;
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
* Description: 以下函数是RTC中断的钩子函数;
*           
* Input:  flag, 中断标志; cnt, RTC 32位计数器值
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
* Description: 本函数是TIM1、TIM8中断钩子函数;
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
* Description: 本函数是TIM2~TIM7中断钩子函数;
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
* Description: 本函数是TIM9~TIM14中断钩子函数;
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
* Description: 以下函数是EXTI16~EXTI19中断的钩子函数;
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
* Description: 以下函数是外部IO 16个中断函数;
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
* Description: 系统异常中断处理函数;
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
* Description: ADC中断处理完成回调函数;
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
* Description: 本函数是CAN1发送邮箱中断钩子函数;
*           
* Input:  val, 发送缓存中还有多少条数据未发送;
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
* Description: 本函数是CAN1 RX0接收中断钩子函数;
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
* Description: 本函数是CAN1 RX1接收中断钩子函数;
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
* Description: 本函数是CAN1错误和状态变化中断钩子函数;
*           
* Input:  val, 出错代码;
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
* Description: 本函数是CAN2发送邮箱中断钩子函数;
*           
* Input:  val, 发送缓存中还有多少条数据未发送;
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
* Description: 本函数是CAN2 RX0接收中断钩子函数;
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
* Description: 本函数是CAN2 RX1接收中断钩子函数;
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
* Description: 本函数是CAN2错误和状态变化中断钩子函数;
*           
* Input:  val, 出错代码;
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
* Description: USB Device中断钩子函数;
*              
* Input:  flag, 中断标志;
*
* Output: none;
*
* Return: ERR_TRUE,成功; ERR_FALSE,失败;
*
* Note:   none;
************************************************************************************/
INT32S USBD_ISRHook(INT32U flag);		 // USB Device中断钩子函数

/***********************************************************************************
* Function: USBH_ISRHook;
*
* Description: USB Host中断钩子函数;
*              
* Input:  flag, 中断标志;
*
* Output: none;
*
* Return: none;
*
* Note:   none;
************************************************************************************/
extern void USBH_ISRHook(INT32U flag);		 // USB Host中断钩子函数

/***********************************************************************************
* Function: OSIntEnterHook;
*
* Description: 供库函数调用的进入操作系统关中断函数;
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
* Description: 供库函数调用的退出操作系统关中断函数;
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
* Description: 延时程序, 延时时间范围: 0~65535ms;
*              
* Input:  val, 延时时间变量, 单位：ms;
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
* Description: 向操作系统申请SPI访问权限;
*              
* Input:  timeout, 超时时间返回;
*
* Output: none;
*
* Return: ERR_TRUE, 申请成功; TIMEOUT, 超时退出,申请失败;	ERR_FALSE, 申请失败;
*
* Note:   none;
************************************************************************************/
extern INT32S SPI_RequestOSSem(INT16U timeout);

/***********************************************************************************
* Function: SPI_ReleaseOSSem;
*
* Description: 向操作系释放SPI访问权限;
*              
* Input:  none;
*
* Output: none;
*
* Return: ERR_TRUE, 申请成功; ERR_FALSE, 释放失败;
*
* Note:   none;
************************************************************************************/
extern INT32S SPI_ReleaseOSSem(void);

#if (MODULE_TYPE == STM32F103ZE)

/***********************************************************************************
* Function: FSMC_ISRHook;
*
* Description: 本函数FSMC中断处理函数;
*           
* Input:  inr：中断来源, 2：BANK2中断; 3：BANK3中断; 4：BANK4中断;;
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
* Description: 读取FSMC的Bank2, Bank3, Bank4状态输入引脚;
*              
* Input:  none;
*
* Output: none;
*
* Return: ERR_TRUE: 成功;  ERR_FALSE: 失败;
*
* Note:   none;
************************************************************************************/
extern INT32S FSMC_ISRRead(INT16U flag);

/***********************************************************************************
* Function: NET_CreateOSSem;
*
* Description: 向操作系统申请NET访问权限;
*              
* Input:  timeout, 超时时间返回;
*
* Output: none;
*
* Return: ERR_TRUE, 申请成功; TIMEOUT, 超时退出,申请失败;	ERR_FALSE, 申请失败;
*
* Note:   none;
************************************************************************************/
extern void NET_CreateOSSem(void);

/***********************************************************************************
* Function: NET_RequestOSSem;
*
* Description: 向操作系统申请NET访问权限;
*              
* Input:  timeout, 超时时间返回;
*
* Output: none;
*
* Return: ERR_TRUE, 申请成功; TIMEOUT, 超时退出,申请失败;	ERR_FALSE, 申请失败;
*
* Note:   none;
************************************************************************************/
INT32S NET_RequestOSSem(INT16U timeout);

/***********************************************************************************
* Function: NET_ReleaseOSSem;
*
* Description: 向操作系释放NET访问权限;
*              
* Input:  none;
*
* Output: none;
*
* Return: ERR_TRUE, 申请成功; ERR_FALSE, 释放失败;
*
* Note:   none;
************************************************************************************/
INT32S NET_ReleaseOSSem(void);

/***********************************************************************************
* Function: NET_PendRXIntOSFlag;
*
* Description: 向操作系统接收网络接收中断标志;
*              
* Input:  timeout, 超时时间返回;
*
* Output: none;
*
* Return: ERR_TRUE, 申请成功; TIMEOUT, 超时退出,申请失败;	ERR_FALSE, 申请失败;
*
* Note:   none;
************************************************************************************/
INT32S NET_PendRXIntOSFlag(INT16U timeout);

/***********************************************************************************
* Function: INT32S NET_PostRXIntOSFlag;
*
* Description: 向操作系统发送网络接收中断标志;;
*              
* Input:  none;
*
* Output: none;
*
* Return: ERR_TRUE, 申请成功; ERR_FALSE, 释放失败;
*
* Note:   none;
************************************************************************************/
INT32S NET_PostRXIntOSFlag(void);

#endif
/***********************************************************************************
* Function: OSMalloc;
*
* Description: 动态内存申请函数;
*              
* Input:  len, 申请内存长度, 单位: 字节;
*
* Output: none;
*
* Return: 内存起始地址指针;
*
* Note:   此函数必须要定义OSMboxMalloc邮箱, 并初始化为1; 如果返回内存地址为0, 则申请失败;
************************************************************************************/
extern void *OSMalloc(INT16U len);

/***********************************************************************************
* Function: OSFree;
*
* Description: 动态内存释放函数;
*              
* Input:  *p, 释放内存起始地址指针
*
* Output: none;
*
* Return: ERR_TRUE:释放成功;  ERR_FALSE:释放失败;
*
* Note:   此函数必须要定义OSMboxFree邮箱, 并初始化为1;
************************************************************************************/
extern INT32S OSFree(void *p);
/***********************************************************************************
* Function: PWM_ISRHook;
*
* Description: PWM输出完成或出错中断的钩子函数;
*           
* Input:  id: PWM索引ID, PWM1_ID~PWM8_ID 
*         flag: 中断标志
*         PWMCH1_OK_FLAG: PWM CH1发送脉冲完成标志;
*         PWMCH2_OK_FLAG: PWM CH2发送脉冲完成标志;
*         PWMCH3_OK_FLAG: PWM CH3发送脉冲完成标志;
*         PWMCH4_OK_FLAG: PWM CH4发送脉冲完成标志;
*         PWMCH1_ERR_FLAG: PWM CH1发送脉冲失败标志;
*         PWMCH2_ERR_FLAG: PWM CH2发送脉冲失败标志;
*         PWMCH3_ERR_FLAG: PWM CH3发送脉冲失败标志;
*         PWMCH4_ERR_FLAG: PWM CH4发送脉冲失败标志;
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
* Description: 以下函数是DMA1,DMA2中断的钩子函数;
*           
* Input:  ch: 通道0(DMA_CH1)~8(DMA_CH8)
*         flag: 中断类别: DMA_IT_TC, 传输完成中断标志
*                         DMA_IT_HT, 半传输完成中断标志
*                         DMA_IT_TERR, 传输出错中断标志
*                         DMA_IT_FIFOERR, 数据流FIFO错误标志   
*                         DMA_IT_DERR, 数据流直接错误标志
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
* Description: 驱动库设置等待标志函数;
*              
* Input:  flag: 等待标志, 在const.h中定义
*
* Output: none;
*
* Return: none;
*
* Note:   这个函数只提供给驱动库中断调用, 请用户不要修改该函数;
************************************************************************************/
extern void API_OSFlagPostHook(INT32U flag);

/***********************************************************************************
* Function: API_OSFlagPendHook;
*
* Description: 驱动库读取等待标志函数;
*              
* Input:  flag: 等待标志, 在const.h中定义
*         TimeOut: 超时时间, 单位ms, 如果为0则设置为0xFFFFFFFF, 就是无线等待
*
* Output: none;
*
* Return: ERR_TRUE: 成功;  ERR_FALSE: 失败; ERR_TIMEOUT: 超时失败;
*
* Note:   这个函数只提供给驱动库调用, 请用户不要修改该函数;
************************************************************************************/
extern API_OSFlagPendHook(INT32U flag, INT32U TimeOut);

/***********************************************************************************/
// 文件结束
/***********************************************************************************/

/***********************************************************************************
* Function: I2C1_ISRHook,I2C1_ER_ISRHook,I2C2_ISRHook,I2C2_ER_ISRHook,;
*
* Description: 以下函数是I2C1,I2C2中断的钩子函数;
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
* Description: 以下函数是SPI1,SPI2,SPI3中断的钩子函数;
*           
* Input:  none;
*
* Output: none;
*          		
* Return: ERR_TRUE, 执行驱动库中的中断处理;	ERR_FALSE, 不执行驱动库中的中断处理;
*
* Note:   如客户不想自己处理该中断，请选择ERR_TRUE返回;
************************************************************************************/
//extern INT32S SPI1_ISRHook(void);
//extern INT32S SPI2_ISRHook(void);
//extern INT32S SPI3_ISRHook(void);