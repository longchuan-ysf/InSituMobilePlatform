/************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: dma.h
* Project  : STM32F107VC/103VE/407VEģ��������
* Processor: STM32F107VC/103VE/407VE
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.00
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: ���ļ���DMA������Ӳ����������ͷ�ļ�;
*
* Others: none;
*
* Function List: 
*          1. INT32S DMA_Init(INT8U id, INT8U ch, DMA_PARA *pPara);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/
#ifndef __DMA_H 
#define __DMA_H 

/************************************************************************************/
// �����ⲿͷ�ļ�
/************************************************************************************/
#include "const.h"
#include "config.h"

// DMA��������
#define DMA1_ID       0
#define DMA2_ID       1

// DMA:CH1-CH8����
#define DMA_CH1       0
#define DMA_CH2       1
#define DMA_CH3       2
#define DMA_CH4       3
#define DMA_CH5       4
#define DMA_CH6       5
#define DMA_CH7       6
#define DMA_CH8       7

// DMA:CH1-CH8������־
#define DMACH1_FLAG       ((INT32U)0x00000001)
#define DMACH2_FLAG       ((INT32U)0x00000002)
#define DMACH3_FLAG       ((INT32U)0x00000004)
#define DMACH4_FLAG       ((INT32U)0x00000008)
#define DMACH5_FLAG       ((INT32U)0x00000010)
#define DMACH6_FLAG       ((INT32U)0x00000020)
#define DMACH7_FLAG       ((INT32U)0x00000040)
#define DMACH8_FLAG       ((INT32U)0x00000080)


// DMA1/2 ��ͨ����������
#define DMA1_CH1       0x00
#define DMA1_CH2       0x01
#define DMA1_CH3       0x02
#define DMA1_CH4       0x03
#define DMA1_CH5       0x04
#define DMA1_CH6       0x05
#define DMA1_CH7       0x06
#define DMA1_CH8       0x07

#define DMA2_CH1       0x10
#define DMA2_CH2       0x11
#define DMA2_CH3       0x12
#define DMA2_CH4       0x13
#define DMA2_CH5       0x14
#define DMA2_CH6       0x15
#define DMA2_CH7       0x16
#define DMA2_CH8       0x17

typedef struct
{   
    INT32U Flag;           // DMA������־  
    INT16U ChPara[8];      // ͨ������    
    void (* pISRHook) (INT8U ch, INT32U flag);    // DMA�жϺ������Ӻ�
}DMA_INIT;

/************************************************************************************/
// STM32F4_M4 ��������
/************************************************************************************/
#if (MODULE_CLASS == STM32F407XX)
// DMA1Ŀǰ֧��Ӧ�ö��ձ�  
/*
|------------------------------------------------------------------------------------------------------|
| ͨ��  |  Ӧ��     | �������� | ����˵��       |   ��EMBXXX_Config.h��������   |��ע                  |
|------------------------------------------------------------------------------------------------------|
|       | UART5     | UART5_RX | UART5��������  | #define UART5RX_DMA_EN     1  |                      |
|  CH1  |----------------------------------------------------------------------------------------------|
|       | PWMx(TIM5)| TIM5_UP  | PWMx�������   | #define PWMx_MODE PWM_DMA     |                      |
|       |           |          |                | #define PWMx_TIM TIM5_ID      |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH1  | TIM4_CH1 | ��Ƶ��ռ�ձ�   | #define FCLKx_TIM     TIM4_ID |                      |
|       |           |          |                | #define FCLKxCH1_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH3  | TIM5_CH3 | ��Ƶ           | #define FCLKx_TIM     TIM5_ID |                      |
|       |           |          |                | #define FCLKxCH3_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | SPI3      | SPI3_RX  | SPI3��������   | #define SPI3RX_DMA_EN      1  | ��ʱδʵ��           |
|------------------------------------------------------------------------------------------------------|
|       | UART3     | UART3_RX | UART3��������  | #define UART3RX_DMA_EN     1  |                      |
|  CH2  |----------------------------------------------------------------------------------------------|
|       | PWMx(TIM2)| TIM2_UP  | PWMx�������   | #define PWMx_MODE PWM_DMA     |                      |
|       |           |          |                | #define PWMx_TIM TIM2_ID      |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH3  | TIM2_CH3 | ��Ƶ           | #define FCLKx_TIM     TIM2_ID |                      |
|       |           |          |                | #define FCLKxCH3_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH4  | TIM5_CH4 | ��Ƶ           | #define FCLKx_TIM     TIM5_ID |                      |
|       |           |          |                | #define FCLKxCH4_DMA_EN    1  |                      |
|------------------------------------------------------------------------------------------------------|
|       | UART4     | UART4_RX | UART4��������  | #define UART4RX_DMA_EN    1   |                      |
|  CH3  |----------------------------------------------------------------------------------------------|
|       | PWMx(TIM3)| TIM3_UP  | PWMx�������   | #define PWMx_MODE PWM_DMA     |                      |
|       |           |          |                | #define PWMx_TIM TIM3_ID      |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH1  | TIM5_CH1 | ��Ƶ��ռ�ձ�   | #define FCLKx_TIM     TIM5_ID |                      |
|       |           |          |                | #define FCLKxCH1_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH4  | TIM3_CH4 | ��Ƶ           | #define FCLKx_TIM     TIM3_ID |                      |
|       |           |          |                | #define FCLKxCH4_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | SPI3      | SPI3_RX  | SPI3��������   | #define SPI3RX_DMA_EN      1  | ��ʱδʵ��           |
|------------------------------------------------------------------------------------------------------|
|       | UART3     | UART3_TX | UART3��������  | #define UART3TX_DMA_EN    1   |                      |
|  CH4  |----------------------------------------------------------------------------------------------|
|       | FCLKxCH2  | TIM4_CH2 | ��Ƶ           | #define FCLKx_TIM     TIM4_ID |                      |
|       |           |          |                | #define FCLKxCH2_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH4  | TIM5_CH4 | ��Ƶ           | #define FCLKx_TIM     TIM5_ID |                      |
|       |           |          |                | #define FCLKxCH4_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | SPI2      | SPI2_RX  | SPI2��������   | #define SPI2RX_DMA_EN      1  | ��ʱδʵ��           |
|------------------------------------------------------------------------------------------------------|
|       | UART4     | UART4_TX | UART4��������  | #define UART4TX_DMA_EN    1   |                      |
|  CH5  |----------------------------------------------------------------------------------------------|
|       | FCLKxCH1  | TIM3_CH1 | ��Ƶ��ռ�ձ�   | #define FCLKx_TIM     TIM3_ID |                      |
|       |           |          |                | #define FCLKxCH1_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH2  | TIM5_CH2 | ��Ƶ           | #define FCLKx_TIM     TIM5_ID |                      |
|       |           |          |                | #define FCLKxCH2_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | SPI2      | SPI2_TX  | SPI2��������   | #define SPI2TX_DMA_EN      1  | ��ʱδʵ��           |
|       |----------------------------------------------------------------------------------------------|
|       | UART3     | UART3_TX | UART3��������  | #define UART3TX_DMA_EN    1   |  ����, Ĭ��ʹ��CH4                     |
|------------------------------------------------------------------------------------------------------|
|       | UART2     | UART2_RX | UART2��������  | #define UART2RX_DMA_EN    1   |                      |
|  CH6  |----------------------------------------------------------------------------------------------|
|       | DAC1      | DAC1     | DAC1����ź�   | #define DAC1_MODE 1(or 2)     | ����ģʽΪ1����2     |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH1  | TIM2_CH1 | ��Ƶ��ռ�ձ�   | #define FCLKx_TIM     TIM2_ID |                      |
|       |           |          |                | #define FCLKxCH1_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH2  | TIM3_CH2 | ��Ƶ           | #define FCLKx_TIM     TIM3_ID |                      |
|       |           |          |                | #define FCLKxCH2_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | SPI3      | SPI3_TX  | SPI3��������   | #define SPI3TX_DMA_EN      1  | ��ʱδʵ��           |
|------------------------------------------------------------------------------------------------------|
|       | UART2     | UART2_TX | UART2��������  | #define UART2TX_DMA_EN    1   |                      |
|  CH7  |----------------------------------------------------------------------------------------------|
|       | DAC2      | DAC2     | DAC2����ź�   | #define DAC2_MODE 1(or 2)     | ����ģʽΪ1����2     |
|       |----------------------------------------------------------------------------------------------|
|       | PWMx(TIM4)| TIM4_UP  | PWMx�������   | #define PWMx_MODE PWM_DMA     |                      |
|       |           |          |                | #define PWMx_TIM TIM4_ID      |                      |
|       |----------------------------------------------------------------------------------------------|
|       | PWMx(TIM5)| TIM5_UP  | PWMx�������   | #define PWMx_MODE PWM_DMA     |  ����, Ĭ��ʹ��CH1   |
|       |           |          |                | #define PWMx_TIM TIM5_ID      |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH2  | TIM2_CH2 | ��Ƶ           | #define FCLKx_TIM     TIM2_ID |                      |
|       |           |          |                | #define FCLKxCH2_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH4  | TIM2_CH4 | ��Ƶ           | #define FCLKx_TIM     TIM2_ID |                      |
|       |           |          |                | #define FCLKxCH4_DMA_EN    1  |                      |
|------------------------------------------------------------------------------------------------------|
|       | UART5     | UART5_TX | UART5��������  | #define UART5TX_DMA_EN    1   |                      |
|  CH8  |----------------------------------------------------------------------------------------------|
|       | PWMx(TIM2)| TIM2_UP  | PWMx�������   | #define PWMx_MODE PWM_DMA     | ����, Ĭ��ʹ��CH2    |
|       |           |          |                | #define PWMx_TIM TIM2_ID      |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH4  | TIM2_CH4 | ��Ƶ           | #define FCLKx_TIM     TIM2_ID |                      |
|       |           |          |                | #define FCLKxCH4_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH3  | TIM3_CH3 | ��Ƶ           | #define FCLKx_TIM     TIM3_ID |                      |
|       |           |          |                | #define FCLKxCH3_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH3  | TIM4_CH3 | ��Ƶ           | #define FCLKx_TIM     TIM4_ID |                      |
|       |           |          |                | #define FCLKxCH3_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | SPI3      | SPI3_TX  | SPI3��������   | #define SPI3TX_DMA_EN      1  | ��ʱδʵ��           |
|------------------------------------------------------------------------------------------------------|
*/
// DMA2Ŀǰ֧��Ӧ�ö��ձ�  
/*
|------------------------------------------------------------------------------------------------------|
| ͨ��  |  Ӧ��     | �������� | ����˵��       |  ��EMBXXX_Config.h��������    |��ע                  |
|------------------------------------------------------------------------------------------------------|
|       | ADC1      | ADC1     | ADC1ģ����ת�� | #define ADC_EN             1  |                      |
|       |           |          |                | #define ADC_DMA_EN         1  |                      |
|  CH1  |----------------------------------------------------------------------------------------------|
|       | SPI1      | SPI1_RX  | SPI1��������   | #define SPI1RX_DMA_EN      1  | ��ʱδʵ��           |
|------------------------------------------------------------------------------------------------------|
|       | UART6     | UART6_RX | UART6��������  | #define UART6RX_DMA_EN     1  |                      |
|  CH2  |----------------------------------------------------------------------------------------------|
|       | PWMx(TIM8)| TIM8_UP  | PWMx�������   | #define PWMx_MODE PWM_DMA     |                      |
|       |           |          |                | #define PWMx_TIM TIM8_ID      |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH1  | TIM1_CH1 | ��Ƶ��ռ�ձ�   | #define FCLKx_TIM     TIM1_ID |                      |
|       |           |          |                | #define FCLKxCH1_DMA_EN    1  |                      |
|------------------------------------------------------------------------------------------------------|
|       | UART1     | UART1_RX | UART1��������  | #define UART1RX_DMA_EN    1   |                      |
|  CH3  |----------------------------------------------------------------------------------------------|
|       | FCLKxCH1  | TIM8_CH1 | ��Ƶ��ռ�ձ�   | #define FCLKx_TIM     TIM8_ID |                      |
|       |           |          |                | #define FCLKxCH1_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH2  | TIM8_CH2 | ��Ƶ           | #define FCLKx_TIM     TIM8_ID |                      |
|       |           |          |                | #define FCLKxCH2_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH3  | TIM8_CH3 | ��Ƶ           | #define FCLKx_TIM     TIM8_ID |                      |
|       |           |          |                | #define FCLKxCH3_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH2  | TIM1_CH2 | ��Ƶ           | #define FCLKx_TIM     TIM1_ID |                      |
|       |           |          |                | #define FCLKxCH2_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | SPI1      | SPI1_RX  | SPI1��������   | #define SPI1RX_DMA_EN      1  | ��ʱδʵ��           |
|------------------------------------------------------------------------------------------------------|
|       | SDIO      | SDIO     | SDIOͨ��       | #define SDIO_DMA_EN    1      | ��ʱδʵ��           |
|  CH4  |----------------------------------------------------------------------------------------------|
|       | FCLKxCH1  | TIM1_CH1 | ��Ƶ��ռ�ձ�   | #define FCLKx_TIM     TIM1_ID |                      |
|       |           |          |                | #define FCLKxCH1_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH2  | TIM8_CH2 | ��Ƶ           | #define FCLKx_TIM     TIM8_ID |                      |
|       |           |          |                | #define FCLKxCH2_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | SPI1      | SPI1_TX  | SPI1��������   | #define SPI1TX_DMA_EN      1  | ��ʱδʵ��           |
|------------------------------------------------------------------------------------------------------|
|       |  ADC1      | ADC1    | ADC1ģ����ת�� | #define ADC_EN             1  | ����, Ĭ��ʹ��CH1 ???                     |
|       |           |          |                | #define ADC_DMA_EN         1  |                      |
|  CH5  |----------------------------------------------------------------------------------------------|     
|       | FCLKxCH4  | TIM1_CH4 | ��Ƶ           | #define FCLKx_TIM     TIM1_ID |                      |
|       |           |          |                | #define FCLKxCH4_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH5  | TIM8_CH3 | ��Ƶ           | #define FCLKx_TIM     TIM8_ID |                      |
|       |           |          |                | #define FCLKxCH3_DMA_EN    1  |                      |
|------------------------------------------------------------------------------------------------------|
|       | UART1     | UART1_RX | UART1��������  | #define UART1RX_DMA_EN     1  | ����, Ĭ��ʹ��CH3    |
|  CH6  |----------------------------------------------------------------------------------------------|
|       | PWMx(TIM1)| TIM1_UP  | PWMx�������   | #define PWMx_MODE PWM_DMA     |                      |
|       |           |          |                | #define PWMx_TIM TIM1_ID      |                      |
|       |----------------------------------------------------------------------------------------------|     
|       | SPI1      | SPI1_TX  | SPI1��������   | #define SPI1TX_DMA_EN      1  | ��ʱδʵ��           |
|------------------------------------------------------------------------------------------------------|
|       | UART6     | UART6_TX | UART6��������  | #define UART6TX_DMA_EN    1   |                      |
|  CH7  |----------------------------------------------------------------------------------------------|
|       | FCLKxCH1  | TIM1_CH1 | ��Ƶ��ռ�ձ�   | #define FCLKx_TIM     TIM1_ID |                      |
|       |           |          |                | #define FCLKxCH1_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH2  | TIM1_CH2 | ��Ƶ           | #define FCLKx_TIM     TIM1_ID |                      |
|       |           |          |                | #define FCLKxCH2_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH3  | TIM1_CH3 | ��Ƶ           | #define FCLKx_TIM     TIM1_ID |                      |
|       |           |          |                | #define FCLKxCH3_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|       
|       | SDIO      | SDIO     | SDIOͨ��       | #define SDIO_DMA_EN    1      | ��ʱδʵ��           |
|------------------------------------------------------------------------------------------------------|
|       | UART1     | UART1_TX | UART1��������  | #define UART1TX_DMA_EN    1   |                      |
|  CH8  |----------------------------------------------------------------------------------------------|
|       | UART6     | UART6_TX | UART6��������  | #define UART6TX_DMA_EN    1   |  ����, Ĭ����CH7ʵ�� |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH4  | TIM8_CH4 | ��Ƶ           | #define FCLKx_TIM     TIM8_ID |                      |
|       |           |          |                | #define FCLKxCH4_DMA_EN    1  |                      |
|------------------------------------------------------------------------------------------------------|
*/
// DMA״̬��־
#define DMA_BUSY_FLAG       ((INT32U)0x80000000)   // DMAæ��־
#define DMA_INIT_FLAG       ((INT32U)0x40000000)   // ��ʼ����ɱ�־

// DMA�жϴ����־ 
#define DMA_IT_FIFOERR      ((INT16U)0x0001) // ������FIFO�����־ 
#define DMA_IT_TC           ((INT16U)0x0002) // ��������жϱ�־
#define DMA_IT_HT           ((INT16U)0x0004) // �봫������жϱ�־
#define DMA_IT_TERR         ((INT16U)0x0008) // ��������жϱ�־
#define DMA_IT_DERR         ((INT16U)0x0010) // ������ֱ�Ӵ����־

// DMA1,DMA2����ʹ�ñ�־����
#define DMAxCHx_MASK_FLAG          ((INT16U)0xFF80) // ���α�־

// DMA1CH1
#define DMA1CH1_UART5RX_FLAG       ((INT16U)0x0100)
#define DMA1CH1_TIM5UP_FLAG        ((INT16U)0x0200)
#define DMA1CH1_TIM4CH1_FLAG       ((INT16U)0x0400) 
#define DMA1CH1_TIM5CH3_FLAG       ((INT16U)0x0800) 
#define DMA1CH1_SPI3RX_FLAG        ((INT16U)0x1000) 
#define DMA1CH1_UART8TX_FLAG       ((INT16U)0x2000) 
#define DMA1CH1_I2S3EXTRX_FLAG     ((INT16U)0x4000) 
#define DMA1CH1_I2C1RX_FLAG        ((INT16U)0x8000)

// DMA1CH2
#define DMA1CH2_UART3RX_FLAG       ((INT16U)0x0100)
#define DMA1CH2_TIM2UP_FLAG        ((INT16U)0x0200)
#define DMA1CH2_TIM2CH3_FLAG       ((INT16U)0x0400) 
#define DMA1CH2_TIM5CH4_FLAG       ((INT16U)0x0800)
#define DMA1CH2_UART7TX_FLAG       ((INT16U)0x1000) 
#define DMA1CH2_TIM5TRIG_FLAG      ((INT16U)0x2000) 
#define DMA1CH2_TIM6UP_FLAG        ((INT16U)0x4000) 

// DMA1CH3
#define DMA1CH3_UART4RX_FLAG       ((INT16U)0x0100)
#define DMA1CH3_TIM3UP_FLAG        ((INT16U)0x0200)
#define DMA1CH3_TIM5CH1_FLAG       ((INT16U)0x0400) 
#define DMA1CH3_SPI3RX_FLAG        ((INT16U)0x0800) 
#define DMA1CH3_TIM3CH4_FLAG       ((INT16U)0x1000) 
#define DMA1CH3_I2C3RX_FLAG        ((INT16U)0x2000) 
#define DMA1CH3_TIM7UP_FLAG        ((INT16U)0x4000) 
#define DMA1CH3_I2S3EXTRX_FLAG     ((INT16U)0x8000)
#define DMA1CH3_I2C2RX_FLAG        ((INT16U)0x0080)

// DMA1CH4
#define DMA1CH4_UART3TX_FLAG       ((INT16U)0x0100)
#define DMA1CH4_TIM4CH2_FLAG       ((INT16U)0x0200)
#define DMA1CH4_TIM5CH4_FLAG       ((INT16U)0x0400) 
#define DMA1CH4_SPI2RX_FLAG        ((INT16U)0x0800)
#define DMA1CH4_UART7RX_FLAG       ((INT16U)0x1000) 
#define DMA1CH4_I2S3EXTRX_FLAG     ((INT16U)0x2000) 
#define DMA1CH4_TIM5TRIG_FLAG      ((INT16U)0x4000)
#define DMA1CH4_I2C2RX_FLAG        ((INT16U)0x8000)

// DMA1CH5
#define DMA1CH5_UART4TX_FLAG       ((INT16U)0x0100)
#define DMA1CH5_UART3TX_FLAG       ((INT16U)0x0200)
#define DMA1CH5_TIM3CH1_FLAG       ((INT16U)0x0400)
#define DMA1CH5_TIM5CH2_FLAG       ((INT16U)0x0800)
#define DMA1CH5_SPI2TX_FLAG        ((INT16U)0x1000)
#define DMA1CH5_TIM7UP_FLAG        ((INT16U)0x2000)  
#define DMA1CH5_TIM3TRIG_FLAG      ((INT16U)0x4000)
#define DMA1CH5_I2C3TX_FLAG        ((INT16U)0x8000)
#define DMA1CH5_I2S2EXTTX_FLAG     ((INT16U)0x0080)

// DMA1CH6
#define DMA1CH6_UART2RX_FLAG       ((INT16U)0x0100)
#define DMA1CH6_DAC1_FLAG          ((INT16U)0x0200)
#define DMA1CH6_TIM2CH1_FLAG       ((INT16U)0x0400)
#define DMA1CH6_TIM3CH2_FLAG       ((INT16U)0x0800)
#define DMA1CH6_SPI3TX_FLAG        ((INT16U)0x1000)
#define DMA1CH6_I2S3EXTTX_FLAG     ((INT16U)0x2000)
#define DMA1CH6_I2C1RX_FLAG        ((INT16U)0x4000)

// DMA1CH7
#define DMA1CH7_UART2TX_FLAG       ((INT16U)0x0100)
#define DMA1CH7_DAC2_FLAG          ((INT16U)0x0200)
#define DMA1CH7_TIM4UP_FLAG        ((INT16U)0x0400)
#define DMA1CH7_TIM5UP_FLAG        ((INT16U)0x0800)
#define DMA1CH7_TIM2CH2_FLAG       ((INT16U)0x1000)
#define DMA1CH7_TIM2CH4_FLAG       ((INT16U)0x2000)
#define DMA1CH7_UART8RX_FLAG       ((INT16U)0x4000)
#define DMA1CH7_I2C1TX_FLAG        ((INT16U)0x8000)

// DMA1CH8
#define DMA1CH8_UART5TX_FLAG       ((INT16U)0x0100)
#define DMA1CH8_TIM2UP_FLAG        ((INT16U)0x0200)
#define DMA1CH8_TIM3CH3_FLAG       ((INT16U)0x0400)
#define DMA1CH8_TIM4CH3_FLAG       ((INT16U)0x0800)
#define DMA1CH8_TIM2CH4_FLAG       ((INT16U)0x1000)
#define DMA1CH8_SPI3TX_FLAG        ((INT16U)0x2000)
#define DMA1CH8_I2C1TX_FLAG        ((INT16U)0x4000)
#define DMA1CH8_I2C2TX_FLAG        ((INT16U)0x8000)

// DMA2CH1
#define DMA2CH1_ADC1_FLAG        ((INT16U)0x0100)
#define DMA2CH1_ADC3_FLAG        ((INT16U)0x0200)
#define DMA2CH1_SPI1RX_FLAG      ((INT16U)0x0400)
#define DMA2CH1_SPI4RX_FLAG      ((INT16U)0x0800)
#define DMA2CH1_TIM1TRIG_FLAG    ((INT16U)0x1000)

// DMA2CH2
#define DMA2CH2_UART6RX_FLAG     ((INT16U)0x0100)
#define DMA2CH2_TIM8UP_FLAG      ((INT16U)0x0200)
#define DMA2CH2_TIM1CH1_FLAG     ((INT16U)0x0400)
#define DMA2CH2_DCMI_FLAG        ((INT16U)0x0800)
#define DMA2CH2_SPI4TX_FLAG      ((INT16U)0x1000)
#define DMA2CH2_ADC3_FLAG        ((INT16U)0x2000)

// DMA2CH3
#define DMA2CH3_UART1RX_FLAG     ((INT16U)0x0100)
#define DMA2CH3_UART6RX_FLAG     ((INT16U)0x0200)
#define DMA2CH3_TIM8CH1_FLAG     ((INT16U)0x0400)
#define DMA2CH3_TIM1CH2_FLAG     ((INT16U)0x0800)
#define DMA2CH3_SPI1RX_FLAG      ((INT16U)0x1000)
#define DMA2CH3_TIM8CH3_FLAG     ((INT16U)0x2000)
#define DMA2CH3_TIM8CH2_FLAG     ((INT16U)0x4000)
#define DMA2CH3_ADC2_FLAG        ((INT16U)0x8000)

// DMA2CH4
#define DMA2CH4_SDIO_FLAG       ((INT16U)0x0100)
#define DMA2CH4_TIM1CH1_FLAG    ((INT16U)0x0200)
#define DMA2CH4_SPI1TX_FLAG     ((INT16U)0x0400)
#define DMA2CH4_ADC2_FLAG       ((INT16U)0x0800) 
#define DMA2CH4_SPI4RX_FLAG     ((INT16U)0x1000)
#define DMA2CH4_SPI5RX_FLAG     ((INT16U)0x2000)
#define DMA2CH4_TIM8CH2_FLAG    ((INT16U)0x4000)

// DMA2CH5
#define DMA2CH5_ADC1_FLAG       ((INT16U)0x0100)
#define DMA2CH5_SPI5TX_FLAG     ((INT16U)0x0200)
#define DMA2CH5_SPI4TX_FLAG     ((INT16U)0x0400)
#define DMA2CH5_TIM1CH4_FLAG    ((INT16U)0x0800) 
#define DMA2CH5_TIM1TRIG_FLAG   ((INT16U)0x1000)
#define DMA2CH5_TIM1COM_FLAG    ((INT16U)0x2000)
#define DMA2CH5_TIM8CH3_FLAG    ((INT16U)0x4000)

// DMA2CH6
#define DMA2CH6_UART1RX_FLAG    ((INT16U)0x0100)
#define DMA2CH6_TIM1UP_FLAG     ((INT16U)0x0200)
#define DMA2CH6_SPI1TX_FLAG     ((INT16U)0x0400)
#define DMA2CH6_SPI6TX_FLAG     ((INT16U)0x0800) 
#define DMA2CH6_CRYPOUT_FLAG    ((INT16U)0x1000)
#define DMA2CH6_SPI5RX_FLAG     ((INT16U)0x2000)

// DMA2CH7
#define DMA2CH7_UART6TX_FLAG   ((INT16U)0x0100)
#define DMA2CH7_SDIO_FLAG      ((INT16U)0x0200)
#define DMA2CH7_TIM1CH1_FLAG   ((INT16U)0x0400)
#define DMA2CH7_TIM1CH2_FLAG   ((INT16U)0x0800) 
#define DMA2CH7_TIM1CH3_FLAG   ((INT16U)0x1000)
#define DMA2CH7_SPI6RX_FLAG    ((INT16U)0x2000) 
#define DMA2CH7_CRYPIN_FLAG    ((INT16U)0x4000)
#define DMA2CH7_SPI5TX_FLAG    ((INT16U)0x8000)

// DMA2CH8
#define DMA2CH8_DCMI_FLAG      ((INT16U)0x0100)
#define DMA2CH8_HASHIN_FLAG    ((INT16U)0x0200)
#define DMA2CH8_UART1TX_FLAG   ((INT16U)0x0400) 
#define DMA2CH8_UART6TX_FLAG   ((INT16U)0x0800)
#define DMA2CH8_TIM8CH4_FLAG   ((INT16U)0x1000)
#define DMA2CH8_TIM8TRIG_FLAG  ((INT16U)0x2000)
#define DMA2CH8_TIM8COM_FLAG   ((INT16U)0x4000)

#endif

/************************************************************************************/
// STM32F1_M3 ��������
/************************************************************************************/
#if ((MODULE_CLASS == STM32F107XX)||(MODULE_CLASS == STM32F103XX))
// DMA1Ŀǰ֧��Ӧ�ö��ձ�  
/*
|------------------------------------------------------------------------------------------------------|
| ͨ��  |  Ӧ��     | �������� | ����˵��       |   ��EMBXXX_Config.h��������   |��ע                  |
|------------------------------------------------------------------------------------------------------|
|       | ADC1      | ADC1     | ADC1ģ����ת�� | #define ADC_EN         1      |                      |
|  CH1  |----------------------------------------------------------------------------------------------|
|       | FCLKxCH1  | TIM4_CH1 | ��Ƶ��ռ�ձ�   | #define FCLKx_TIM     TIM4_ID |                      |
|       |           |          |                | #define FCLKxCH1_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH3  | TIM2_CH3 | ��Ƶ           | #define FCLKx_TIM     TIM2_ID |                      |
|       |           |          |                | #define FCLKxCH3_DMA_EN    1  |                      |
|------------------------------------------------------------------------------------------------------|
|       | UART3     | UART3_TX | UART3��������  | #define UART3TX_DMA_EN    1   |                      |
|  CH2  |----------------------------------------------------------------------------------------------|
|       | PWMx(TIM2)| TIM2_UP  | PWMx�������   | #define PWMx_MODE PWM_DMA     |                      |
|       |           |          |                | #define PWMx_TIM TIM2_ID      |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH1  | TIM1_CH1 | ��Ƶ��ռ�ձ�   | #define FCLKx_TIM     TIM1_ID |                      |
|       |           |          |                | #define FCLKxCH1_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH3  | TIM3_CH3 | ��Ƶ           | #define FCLKx_TIM     TIM3_ID |                      |
|       |           |          |                | #define FCLKxCH3_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | SPI1      | SPI1_RX  | SPI1��������   | #define SPI1RX_DMA_EN      1  | ��ʱδʵ��           |
|------------------------------------------------------------------------------------------------------|
|       | UART3     | UART3_RX | UART3��������  | #define UART3RX_DMA_EN    1   |                      |
|  CH3  |----------------------------------------------------------------------------------------------|
|       | PWMx(TIM3)| TIM3_UP  | PWMx�������   | #define PWMx_MODE PWM_DMA     |                      |
|       |           |          |                | #define PWMx_TIM TIM3_ID      |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH2  | TIM1_CH2 | ��Ƶ           | #define FCLKx_TIM     TIM1_ID |                      |
|       |           |          |                | #define FCLKxCH2_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH4  | TIM3_CH4 | ��Ƶ           | #define FCLKx_TIM     TIM3_ID |                      |
|       |           |          |                | #define FCLKxCH4_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | SPI1      | SPI1_TX  | SPI1��������   | #define SPI1TX_DMA_EN      1  | ��ʱδʵ��           |
|------------------------------------------------------------------------------------------------------|
|       | UART1     | UART1_TX | UART1��������  | #define UART1TX_DMA_EN    1   |                      |
|  CH4  |----------------------------------------------------------------------------------------------|
|       | FCLKxCH2  | TIM4_CH2 | ��Ƶ           | #define FCLKx_TIM     TIM4_ID |                      |
|       |           |          |                | #define FCLKxCH2_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH4  | TIM1_CH4 | ��Ƶ           | #define FCLKx_TIM     TIM1_ID |                      |
|       |           |          |                | #define FCLKxCH4_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | SPI2      | SPI2_RX  | SPI2��������   | #define SPI2RX_DMA_EN      1  | ��ʱδʵ��           |
|------------------------------------------------------------------------------------------------------|
|       | UART1     | UART1_RX | UART1��������  | #define UART1RX_DMA_EN    1   |                      |
|  CH5  |----------------------------------------------------------------------------------------------|
|       | PWMx(TIM1)| TIM1_UP  | PWMx�������   | #define PWMx_MODE PWM_DMA     |                      |
|       |           |          |                | #define PWMx_TIM TIM1_ID      |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH1  | TIM2_CH1 | ��Ƶ��ռ�ձ�   | #define FCLKx_TIM     TIM2_ID |                      |
|       |           |          |                | #define FCLKxCH1_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH3  | TIM4_CH3 | ��Ƶ           | #define FCLKx_TIM     TIM4_ID |                      |
|       |           |          |                | #define FCLKxCH3_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | SPI2      | SPI2_TX  | SPI2��������   | #define SPI2TX_DMA_EN      1  | ��ʱδʵ��           |
|------------------------------------------------------------------------------------------------------|
|       | UART2     | UART2_RX | UART2��������  | #define UART2RX_DMA_EN    1   |                      |
|  CH6  |----------------------------------------------------------------------------------------------|
|       | FCLKxCH1  | TIM3_CH1 | ��Ƶ��ռ�ձ�   | #define FCLKx_TIM     TIM3_ID |                      |
|       |           |          |                | #define FCLKxCH1_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH3  | TIM1_CH3 | ��Ƶ           | #define FCLKx_TIM     TIM1_ID |                      |
|       |           |          |                | #define FCLKxCH3_DMA_EN    1  |                      |
|------------------------------------------------------------------------------------------------------|
|       | UART2     | UART2_TX | UART2��������  | #define UART2TX_DMA_EN    1   |                      |
|  CH7  |----------------------------------------------------------------------------------------------|
|       | DAC2      | DAC2     | DAC2����ź�   | #define DAC2_MODE 1(or 2)     | ����ģʽΪ1����2     |
|       |----------------------------------------------------------------------------------------------|
|       | PWMx(TIM4)| TIM4_UP  | PWMx�������   | #define PWMx_MODE PWM_DMA     |                      |
|       |           |          |                | #define PWMx_TIM TIM4_ID      |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH2  | TIM2_CH2 | ��Ƶ           | #define FCLKx_TIM     TIM2_ID |                      |
|       |           |          |                | #define FCLKxCH2_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH4  | TIM2_CH4 | ��Ƶ           | #define FCLKx_TIM     TIM2_ID |                      |
|       |           |          |                | #define FCLKxCH4_DMA_EN    1  |                      |
|------------------------------------------------------------------------------------------------------|
*/
// DMA2Ŀǰ֧��Ӧ�ö��ձ�  
/*
|------------------------------------------------------------------------------------------------------|
| ͨ��  |  Ӧ��     | �������� | ����˵��       |   ��EMBXXX_Config.h��������   |��ע                  |
|------------------------------------------------------------------------------------------------------|
|       | ADC1      | ADC1     | ADC1ģ����ת�� | #define ADC_EN         1      |                      |
|  CH1  |----------------------------------------------------------------------------------------------|
|       | PWMx(TIM8)|TIM8_UP   | PWMx�������   | #define PWMx_MODE PWM_DMA     |                      |
|       |           |          |                | #define PWMx_TIM TIM8_ID      |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH4  | TIM5_CH4 | ��Ƶ           | #define FCLKx_TIM     TIM5_ID |                      |
|       |           |          |                | #define FCLKxCH4_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH3  | TIM8_CH3 | ��Ƶ           | #define FCLKx_TIM     TIM8_ID |                      |
|       |           |          |                | #define FCLKxCH3_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | SPI3      | SPI3_RX  | SPI3��������   | #define SPI3RX_DMA_EN      1  | ��ʱδʵ��           |
|------------------------------------------------------------------------------------------------------|
|       | UART6     | UART6_RX | UART6��������  | #define UART6RX_DMA_EN     1  |                      |
|  CH2  |----------------------------------------------------------------------------------------------|
|       | PWMx(TIM5)| TIM5_UP  | PWMx�������   | #define PWMx_MODE PWM_DMA     |                      |
|       |           |          |                | #define PWMx_TIM TIM5_ID      |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH3  | TIM5_CH3 | ��Ƶ           | #define FCLKx_TIM     TIM5_ID |                      |
|       |           |          |                | #define FCLKxCH3_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH4  | TIM8_CH4 | ��Ƶ           | #define FCLKx_TIM     TIM8_ID |                      |
|       |           |          |                | #define FCLKxCH4_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | SPI3      | SPI3_TX  | SPI3��������   | #define SPI3TX_DMA_EN      1  | ��ʱδʵ��           |
|------------------------------------------------------------------------------------------------------|
|       | UART4     | UART4_RX | UART1��������  | #define UART4RX_DMA_EN    1   |                      |
|  CH3  |----------------------------------------------------------------------------------------------|
|       | PWMx(TIM83)|TIM8_UP  | PWMx�������   | #define PWMx_MODE PWM_DMA     |                      |
|       |           |          |                | #define PWMx_TIM TIM8_ID      |                      |
|       |----------------------------------------------------------------------------------------------|
|       | DAC1      | DAC1     | DAC1����ź�   | #define DAC1_MODE 1(or 2)     | ����ģʽΪ1����2     |
|------------------------------------------------------------------------------------------------------|
|       | SDIO      | SDIO     | SDIOͨ��       | #define SDIO_DMA_EN    1      | ��ʱδʵ��           |
|  CH4  |----------------------------------------------------------------------------------------------|
|       | FCLKxCH2  | TIM5_CH2 | ��Ƶ           | #define FCLKx_TIM     TIM5_ID |                      |
|       |           |          |                | #define FCLKxCH2_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | DAC2      | DAC2     | DAC1����ź�   | #define DAC2_MODE 1(or 2)     | ����ģʽΪ1����2     |
|------------------------------------------------------------------------------------------------------|
|       | UART4     | UART4_TX | UART4��������  | #define UART4TX_DMA_EN    1   |                      |
|  CH5  |----------------------------------------------------------------------------------------------|      
|       | FCLKxCH1  | TIM5_CH1 | ��Ƶ��ռ�ձ�   | #define FCLKx_TIM     TIM5_ID |                      |
|       |           |          |                | #define FCLKxCH1_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH2  | TIM8_CH2 | ��Ƶ           | #define FCLKx_TIM     TIM8_ID |                      |
|       |           |          |                | #define FCLKxCH2_DMA_EN    1  |                      |
|------------------------------------------------------------------------------------------------------|

*/
// DMA״̬��־
#define DMA_BUSY_FLAG       ((INT32U)0x80000000)   // DMAæ��־
#define DMA_INIT_FLAG       ((INT32U)0x40000000)   // ��ʼ����ɱ�־

// DMA�жϴ����־ 
#define DMA_IT_TC           ((INT16U)0x0002) // ��������жϱ�־
#define DMA_IT_HT           ((INT16U)0x0004) // �봫������жϱ�־
#define DMA_IT_TERR         ((INT16U)0x0008) // ��������жϱ�־

// DMA1,DMA2����ʹ�ñ�־����
#define DMAxCHx_MASK_FLAG       ((INT16U)0xFF80) // ���α�־

// DMA1CH1
#define DMA1CH1_ADC1_FLAG       ((INT16U)0x0100)
#define DMA1CH1_TIM2CH3_FLAG    ((INT16U)0x0200)
#define DMA1CH1_TIM4CH1_FLAG    ((INT16U)0x0400)

// DMA1CH2
#define DMA1CH2_SPI1RX_FLAG     ((INT16U)0x0100)
#define DMA1CH2_UART3TX_FLAG    ((INT16U)0x0200)
#define DMA1CH2_TIM1CH1_FLAG    ((INT16U)0x0400)
#define DMA1CH2_TIM2UP_FLAG     ((INT16U)0x0800) 
#define DMA1CH2_TIM3CH3_FLAG    ((INT16U)0x1000) 

// DMA1CH3
#define DMA1CH3_SPI1TX_FLAG     ((INT16U)0x0100)
#define DMA1CH3_UART3RX_FLAG    ((INT16U)0x0200)
#define DMA1CH3_TIM1CH2_FLAG    ((INT16U)0x0400)
#define DMA1CH3_TIM3UP_FLAG     ((INT16U)0x0800) 
#define DMA1CH3_TIM3CH4_FLAG    ((INT16U)0x1000) 

// DMA1CH4
#define DMA1CH4_SPI2RX_FLAG     ((INT16U)0x0100)
#define DMA1CH4_UART1TX_FLAG    ((INT16U)0x0200)
#define DMA1CH4_I2C2TX_FLAG     ((INT16U)0x0400)
#define DMA1CH4_TIM1CH4_FLAG    ((INT16U)0x0800) 
#define DMA1CH4_TIM1TRIG_FLAG   ((INT16U)0x1000)
#define DMA1CH4_TIM1COM_FLAG    ((INT16U)0x2000)
#define DMA1CH4_TIM4CH2_FLAG    ((INT16U)0x4000)
#define DMA1CH4_I2S2RX_FLAG     ((INT16U)0x8000)

// DMA1CH5
#define DMA1CH5_SPI2TX_FLAG     ((INT16U)0x0100)
#define DMA1CH5_UART1RX_FLAG    ((INT16U)0x0200)
#define DMA1CH5_I2C2RX_FLAG     ((INT16U)0x0400)
#define DMA1CH5_TIM1UP_FLAG     ((INT16U)0x0800)
#define DMA1CH5_TIM2CH1_FLAG    ((INT16U)0x1000)
#define DMA1CH5_TIM4CH3_FLAG    ((INT16U)0x2000)
#define DMA1CH5_I2S2TX_FLAG     ((INT16U)0x4000)


// DMA1CH6
#define DMA1CH6_UART2RX_FLAG    ((INT16U)0x0100)
#define DMA1CH6_I2C1TX_FLAG     ((INT16U)0x0200)
#define DMA1CH6_TIM1CH3_FLAG    ((INT16U)0x0400)
#define DMA1CH6_TIM3CH1_FLAG    ((INT16U)0x0800)
#define DMA1CH6_TIM3TRIG_FLAG   ((INT16U)0x1000)

// DMA1CH7
#define DMA1CH7_UART2TX_FLAG    ((INT16U)0x0100)
#define DMA1CH7_I2C1RX_FLAG     ((INT16U)0x0200)
#define DMA1CH7_TIM2CH2_FLAG    ((INT16U)0x0400)
#define DMA1CH7_TIM2CH4_FLAG    ((INT16U)0x0800)
#define DMA1CH7_TIM4UP_FLAG     ((INT16U)0x1000)


// DMA2CH1
#define DMA2CH1_SPI3RX_FLAG     ((INT16U)0x0100)
#define DMA2CH1_TIM5CH4_FLAG    ((INT16U)0x0200)
#define DMA2CH1_TIM5TRIG_FLAG   ((INT16U)0x0400)
#define DMA2CH1_TIM8CH3_FLAG    ((INT16U)0x0800)
#define DMA2CH1_TIM8UP_FLAG     ((INT16U)0x1000)
#define DMA2CH1_I2S3RX_FLAG     ((INT16U)0x2000)

// DMA2CH2
#define DMA2CH2_SPI3TX_FLAG     ((INT16U)0x0100)
#define DMA2CH2_TIM5CH3_FLAG    ((INT16U)0x0200)
#define DMA2CH2_TIM5UP_FLAG     ((INT16U)0x0400)
#define DMA2CH2_TIM8CH4_FLAG    ((INT16U)0x0800)
#define DMA2CH2_TIM8TRIG_FLAG   ((INT16U)0x1000)
#define DMA2CH2_TIM8COM_FLAG    ((INT16U)0x2000)
#define DMA2CH2_I2S3TX_FLAG     ((INT16U)0x4000)

// DMA2CH3
#define DMA2CH3_UART4RX_FLAG    ((INT16U)0x0100)
#define DMA2CH3_TIM6UP_FLAG     ((INT16U)0x0200)
#define DMA2CH3_DAC1_FLAG       ((INT16U)0x0400)
#define DMA2CH3_TIM8CH1_FLAG    ((INT16U)0x0800)

// DMA2CH4
#define DMA2CH4_SDIO_FLAG       ((INT16U)0x0100)
#define DMA2CH4_TIM5CH2_FLAG    ((INT16U)0x0200)
#define DMA2CH4_TIM7UP_FLAG     ((INT16U)0x0400)
#define DMA2CH4_DAC2_FLAG       ((INT16U)0x0800)

// DMA2CH5
#define DMA2CH5_ADC3_FLAG       ((INT16U)0x0100)
#define DMA2CH5_UART4TX_FLAG    ((INT16U)0x0200)
#define DMA2CH5_TIM5CH1_FLAG    ((INT16U)0x0400)
#define DMA2CH5_TIM8CH2_FLAG    ((INT16U)0x0800)

#endif
/*************************************************************************************/
//
// 					 DMA������Ӳ��������������
//
/*************************************************************************************/

/***********************************************************************************
* Function: DMA_Init;
*
* Description: DMA��ʼ��;
* 
* Input:  id, DMAʶ���: DMA1_ID��DMA2_ID
*         pPara, DMA��ʼ������;
*
* Output: none;
*          		
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   none;
************************************************************************************/
INT32S DMA_Init(INT8U id, DMA_INIT *pPara);

#endif
/***********************************************************************************/
// �ļ�����
/***********************************************************************************/
