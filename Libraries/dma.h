/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: dma.h
* Project  : STM32F107VC/103VE/407VE模块驱动库
* Processor: STM32F107VC/103VE/407VE
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.00
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: 本文件是DMA控制器硬件驱动程序头文件;
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
// 引用外部头文件
/************************************************************************************/
#include "const.h"
#include "config.h"

// DMA索引定义
#define DMA1_ID       0
#define DMA2_ID       1

// DMA:CH1-CH8索引
#define DMA_CH1       0
#define DMA_CH2       1
#define DMA_CH3       2
#define DMA_CH4       3
#define DMA_CH5       4
#define DMA_CH6       5
#define DMA_CH7       6
#define DMA_CH8       7

// DMA:CH1-CH8索引标志
#define DMACH1_FLAG       ((INT32U)0x00000001)
#define DMACH2_FLAG       ((INT32U)0x00000002)
#define DMACH3_FLAG       ((INT32U)0x00000004)
#define DMACH4_FLAG       ((INT32U)0x00000008)
#define DMACH5_FLAG       ((INT32U)0x00000010)
#define DMACH6_FLAG       ((INT32U)0x00000020)
#define DMACH7_FLAG       ((INT32U)0x00000040)
#define DMACH8_FLAG       ((INT32U)0x00000080)


// DMA1/2 各通道常量定义
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
    INT32U Flag;           // DMA工作标志  
    INT16U ChPara[8];      // 通道参数    
    void (* pISRHook) (INT8U ch, INT32U flag);    // DMA中断函数钩子函
}DMA_INIT;

/************************************************************************************/
// STM32F4_M4 常量定义
/************************************************************************************/
#if (MODULE_CLASS == STM32F407XX)
// DMA1目前支持应用对照表  
/*
|------------------------------------------------------------------------------------------------------|
| 通道  |  应用     | 外设请求 | 功能说明       |   在EMBXXX_Config.h中配置项   |备注                  |
|------------------------------------------------------------------------------------------------------|
|       | UART5     | UART5_RX | UART5接收数据  | #define UART5RX_DMA_EN     1  |                      |
|  CH1  |----------------------------------------------------------------------------------------------|
|       | PWMx(TIM5)| TIM5_UP  | PWMx脉冲输出   | #define PWMx_MODE PWM_DMA     |                      |
|       |           |          |                | #define PWMx_TIM TIM5_ID      |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH1  | TIM4_CH1 | 测频或占空比   | #define FCLKx_TIM     TIM4_ID |                      |
|       |           |          |                | #define FCLKxCH1_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH3  | TIM5_CH3 | 测频           | #define FCLKx_TIM     TIM5_ID |                      |
|       |           |          |                | #define FCLKxCH3_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | SPI3      | SPI3_RX  | SPI3接收数据   | #define SPI3RX_DMA_EN      1  | 暂时未实现           |
|------------------------------------------------------------------------------------------------------|
|       | UART3     | UART3_RX | UART3接收数据  | #define UART3RX_DMA_EN     1  |                      |
|  CH2  |----------------------------------------------------------------------------------------------|
|       | PWMx(TIM2)| TIM2_UP  | PWMx脉冲输出   | #define PWMx_MODE PWM_DMA     |                      |
|       |           |          |                | #define PWMx_TIM TIM2_ID      |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH3  | TIM2_CH3 | 测频           | #define FCLKx_TIM     TIM2_ID |                      |
|       |           |          |                | #define FCLKxCH3_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH4  | TIM5_CH4 | 测频           | #define FCLKx_TIM     TIM5_ID |                      |
|       |           |          |                | #define FCLKxCH4_DMA_EN    1  |                      |
|------------------------------------------------------------------------------------------------------|
|       | UART4     | UART4_RX | UART4接收数据  | #define UART4RX_DMA_EN    1   |                      |
|  CH3  |----------------------------------------------------------------------------------------------|
|       | PWMx(TIM3)| TIM3_UP  | PWMx脉冲输出   | #define PWMx_MODE PWM_DMA     |                      |
|       |           |          |                | #define PWMx_TIM TIM3_ID      |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH1  | TIM5_CH1 | 测频或占空比   | #define FCLKx_TIM     TIM5_ID |                      |
|       |           |          |                | #define FCLKxCH1_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH4  | TIM3_CH4 | 测频           | #define FCLKx_TIM     TIM3_ID |                      |
|       |           |          |                | #define FCLKxCH4_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | SPI3      | SPI3_RX  | SPI3接收数据   | #define SPI3RX_DMA_EN      1  | 暂时未实现           |
|------------------------------------------------------------------------------------------------------|
|       | UART3     | UART3_TX | UART3发送数据  | #define UART3TX_DMA_EN    1   |                      |
|  CH4  |----------------------------------------------------------------------------------------------|
|       | FCLKxCH2  | TIM4_CH2 | 测频           | #define FCLKx_TIM     TIM4_ID |                      |
|       |           |          |                | #define FCLKxCH2_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH4  | TIM5_CH4 | 测频           | #define FCLKx_TIM     TIM5_ID |                      |
|       |           |          |                | #define FCLKxCH4_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | SPI2      | SPI2_RX  | SPI2接收数据   | #define SPI2RX_DMA_EN      1  | 暂时未实现           |
|------------------------------------------------------------------------------------------------------|
|       | UART4     | UART4_TX | UART4发送数据  | #define UART4TX_DMA_EN    1   |                      |
|  CH5  |----------------------------------------------------------------------------------------------|
|       | FCLKxCH1  | TIM3_CH1 | 测频或占空比   | #define FCLKx_TIM     TIM3_ID |                      |
|       |           |          |                | #define FCLKxCH1_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH2  | TIM5_CH2 | 测频           | #define FCLKx_TIM     TIM5_ID |                      |
|       |           |          |                | #define FCLKxCH2_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | SPI2      | SPI2_TX  | SPI2发送数据   | #define SPI2TX_DMA_EN      1  | 暂时未实现           |
|       |----------------------------------------------------------------------------------------------|
|       | UART3     | UART3_TX | UART3发送数据  | #define UART3TX_DMA_EN    1   |  备用, 默认使用CH4                     |
|------------------------------------------------------------------------------------------------------|
|       | UART2     | UART2_RX | UART2接收数据  | #define UART2RX_DMA_EN    1   |                      |
|  CH6  |----------------------------------------------------------------------------------------------|
|       | DAC1      | DAC1     | DAC1输出信号   | #define DAC1_MODE 1(or 2)     | 工作模式为1或者2     |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH1  | TIM2_CH1 | 测频或占空比   | #define FCLKx_TIM     TIM2_ID |                      |
|       |           |          |                | #define FCLKxCH1_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH2  | TIM3_CH2 | 测频           | #define FCLKx_TIM     TIM3_ID |                      |
|       |           |          |                | #define FCLKxCH2_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | SPI3      | SPI3_TX  | SPI3发送数据   | #define SPI3TX_DMA_EN      1  | 暂时未实现           |
|------------------------------------------------------------------------------------------------------|
|       | UART2     | UART2_TX | UART2发送数据  | #define UART2TX_DMA_EN    1   |                      |
|  CH7  |----------------------------------------------------------------------------------------------|
|       | DAC2      | DAC2     | DAC2输出信号   | #define DAC2_MODE 1(or 2)     | 工作模式为1或者2     |
|       |----------------------------------------------------------------------------------------------|
|       | PWMx(TIM4)| TIM4_UP  | PWMx脉冲输出   | #define PWMx_MODE PWM_DMA     |                      |
|       |           |          |                | #define PWMx_TIM TIM4_ID      |                      |
|       |----------------------------------------------------------------------------------------------|
|       | PWMx(TIM5)| TIM5_UP  | PWMx脉冲输出   | #define PWMx_MODE PWM_DMA     |  备用, 默认使用CH1   |
|       |           |          |                | #define PWMx_TIM TIM5_ID      |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH2  | TIM2_CH2 | 测频           | #define FCLKx_TIM     TIM2_ID |                      |
|       |           |          |                | #define FCLKxCH2_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH4  | TIM2_CH4 | 测频           | #define FCLKx_TIM     TIM2_ID |                      |
|       |           |          |                | #define FCLKxCH4_DMA_EN    1  |                      |
|------------------------------------------------------------------------------------------------------|
|       | UART5     | UART5_TX | UART5发送数据  | #define UART5TX_DMA_EN    1   |                      |
|  CH8  |----------------------------------------------------------------------------------------------|
|       | PWMx(TIM2)| TIM2_UP  | PWMx脉冲输出   | #define PWMx_MODE PWM_DMA     | 备用, 默认使用CH2    |
|       |           |          |                | #define PWMx_TIM TIM2_ID      |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH4  | TIM2_CH4 | 测频           | #define FCLKx_TIM     TIM2_ID |                      |
|       |           |          |                | #define FCLKxCH4_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH3  | TIM3_CH3 | 测频           | #define FCLKx_TIM     TIM3_ID |                      |
|       |           |          |                | #define FCLKxCH3_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH3  | TIM4_CH3 | 测频           | #define FCLKx_TIM     TIM4_ID |                      |
|       |           |          |                | #define FCLKxCH3_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | SPI3      | SPI3_TX  | SPI3发送数据   | #define SPI3TX_DMA_EN      1  | 暂时未实现           |
|------------------------------------------------------------------------------------------------------|
*/
// DMA2目前支持应用对照表  
/*
|------------------------------------------------------------------------------------------------------|
| 通道  |  应用     | 外设请求 | 功能说明       |  在EMBXXX_Config.h中配置项    |备注                  |
|------------------------------------------------------------------------------------------------------|
|       | ADC1      | ADC1     | ADC1模拟量转换 | #define ADC_EN             1  |                      |
|       |           |          |                | #define ADC_DMA_EN         1  |                      |
|  CH1  |----------------------------------------------------------------------------------------------|
|       | SPI1      | SPI1_RX  | SPI1接收数据   | #define SPI1RX_DMA_EN      1  | 暂时未实现           |
|------------------------------------------------------------------------------------------------------|
|       | UART6     | UART6_RX | UART6接收数据  | #define UART6RX_DMA_EN     1  |                      |
|  CH2  |----------------------------------------------------------------------------------------------|
|       | PWMx(TIM8)| TIM8_UP  | PWMx脉冲输出   | #define PWMx_MODE PWM_DMA     |                      |
|       |           |          |                | #define PWMx_TIM TIM8_ID      |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH1  | TIM1_CH1 | 测频或占空比   | #define FCLKx_TIM     TIM1_ID |                      |
|       |           |          |                | #define FCLKxCH1_DMA_EN    1  |                      |
|------------------------------------------------------------------------------------------------------|
|       | UART1     | UART1_RX | UART1接收数据  | #define UART1RX_DMA_EN    1   |                      |
|  CH3  |----------------------------------------------------------------------------------------------|
|       | FCLKxCH1  | TIM8_CH1 | 测频或占空比   | #define FCLKx_TIM     TIM8_ID |                      |
|       |           |          |                | #define FCLKxCH1_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH2  | TIM8_CH2 | 测频           | #define FCLKx_TIM     TIM8_ID |                      |
|       |           |          |                | #define FCLKxCH2_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH3  | TIM8_CH3 | 测频           | #define FCLKx_TIM     TIM8_ID |                      |
|       |           |          |                | #define FCLKxCH3_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH2  | TIM1_CH2 | 测频           | #define FCLKx_TIM     TIM1_ID |                      |
|       |           |          |                | #define FCLKxCH2_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | SPI1      | SPI1_RX  | SPI1接收数据   | #define SPI1RX_DMA_EN      1  | 暂时未实现           |
|------------------------------------------------------------------------------------------------------|
|       | SDIO      | SDIO     | SDIO通信       | #define SDIO_DMA_EN    1      | 暂时未实现           |
|  CH4  |----------------------------------------------------------------------------------------------|
|       | FCLKxCH1  | TIM1_CH1 | 测频或占空比   | #define FCLKx_TIM     TIM1_ID |                      |
|       |           |          |                | #define FCLKxCH1_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH2  | TIM8_CH2 | 测频           | #define FCLKx_TIM     TIM8_ID |                      |
|       |           |          |                | #define FCLKxCH2_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | SPI1      | SPI1_TX  | SPI1发送数据   | #define SPI1TX_DMA_EN      1  | 暂时未实现           |
|------------------------------------------------------------------------------------------------------|
|       |  ADC1      | ADC1    | ADC1模拟量转换 | #define ADC_EN             1  | 备用, 默认使用CH1 ???                     |
|       |           |          |                | #define ADC_DMA_EN         1  |                      |
|  CH5  |----------------------------------------------------------------------------------------------|     
|       | FCLKxCH4  | TIM1_CH4 | 测频           | #define FCLKx_TIM     TIM1_ID |                      |
|       |           |          |                | #define FCLKxCH4_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH5  | TIM8_CH3 | 测频           | #define FCLKx_TIM     TIM8_ID |                      |
|       |           |          |                | #define FCLKxCH3_DMA_EN    1  |                      |
|------------------------------------------------------------------------------------------------------|
|       | UART1     | UART1_RX | UART1接收数据  | #define UART1RX_DMA_EN     1  | 备用, 默认使用CH3    |
|  CH6  |----------------------------------------------------------------------------------------------|
|       | PWMx(TIM1)| TIM1_UP  | PWMx脉冲输出   | #define PWMx_MODE PWM_DMA     |                      |
|       |           |          |                | #define PWMx_TIM TIM1_ID      |                      |
|       |----------------------------------------------------------------------------------------------|     
|       | SPI1      | SPI1_TX  | SPI1发送数据   | #define SPI1TX_DMA_EN      1  | 暂时未实现           |
|------------------------------------------------------------------------------------------------------|
|       | UART6     | UART6_TX | UART6发送数据  | #define UART6TX_DMA_EN    1   |                      |
|  CH7  |----------------------------------------------------------------------------------------------|
|       | FCLKxCH1  | TIM1_CH1 | 测频或占空比   | #define FCLKx_TIM     TIM1_ID |                      |
|       |           |          |                | #define FCLKxCH1_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH2  | TIM1_CH2 | 测频           | #define FCLKx_TIM     TIM1_ID |                      |
|       |           |          |                | #define FCLKxCH2_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH3  | TIM1_CH3 | 测频           | #define FCLKx_TIM     TIM1_ID |                      |
|       |           |          |                | #define FCLKxCH3_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|       
|       | SDIO      | SDIO     | SDIO通信       | #define SDIO_DMA_EN    1      | 暂时未实现           |
|------------------------------------------------------------------------------------------------------|
|       | UART1     | UART1_TX | UART1发送数据  | #define UART1TX_DMA_EN    1   |                      |
|  CH8  |----------------------------------------------------------------------------------------------|
|       | UART6     | UART6_TX | UART6发送数据  | #define UART6TX_DMA_EN    1   |  备用, 默认由CH7实现 |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH4  | TIM8_CH4 | 测频           | #define FCLKx_TIM     TIM8_ID |                      |
|       |           |          |                | #define FCLKxCH4_DMA_EN    1  |                      |
|------------------------------------------------------------------------------------------------------|
*/
// DMA状态标志
#define DMA_BUSY_FLAG       ((INT32U)0x80000000)   // DMA忙标志
#define DMA_INIT_FLAG       ((INT32U)0x40000000)   // 初始化完成标志

// DMA中断错误标志 
#define DMA_IT_FIFOERR      ((INT16U)0x0001) // 数据流FIFO错误标志 
#define DMA_IT_TC           ((INT16U)0x0002) // 传输完成中断标志
#define DMA_IT_HT           ((INT16U)0x0004) // 半传输完成中断标志
#define DMA_IT_TERR         ((INT16U)0x0008) // 传输出错中断标志
#define DMA_IT_DERR         ((INT16U)0x0010) // 数据流直接错误标志

// DMA1,DMA2器件使用标志定义
#define DMAxCHx_MASK_FLAG          ((INT16U)0xFF80) // 屏蔽标志

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
// STM32F1_M3 常量定义
/************************************************************************************/
#if ((MODULE_CLASS == STM32F107XX)||(MODULE_CLASS == STM32F103XX))
// DMA1目前支持应用对照表  
/*
|------------------------------------------------------------------------------------------------------|
| 通道  |  应用     | 外设请求 | 功能说明       |   在EMBXXX_Config.h中配置项   |备注                  |
|------------------------------------------------------------------------------------------------------|
|       | ADC1      | ADC1     | ADC1模拟量转换 | #define ADC_EN         1      |                      |
|  CH1  |----------------------------------------------------------------------------------------------|
|       | FCLKxCH1  | TIM4_CH1 | 测频或占空比   | #define FCLKx_TIM     TIM4_ID |                      |
|       |           |          |                | #define FCLKxCH1_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH3  | TIM2_CH3 | 测频           | #define FCLKx_TIM     TIM2_ID |                      |
|       |           |          |                | #define FCLKxCH3_DMA_EN    1  |                      |
|------------------------------------------------------------------------------------------------------|
|       | UART3     | UART3_TX | UART3发送数据  | #define UART3TX_DMA_EN    1   |                      |
|  CH2  |----------------------------------------------------------------------------------------------|
|       | PWMx(TIM2)| TIM2_UP  | PWMx脉冲输出   | #define PWMx_MODE PWM_DMA     |                      |
|       |           |          |                | #define PWMx_TIM TIM2_ID      |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH1  | TIM1_CH1 | 测频或占空比   | #define FCLKx_TIM     TIM1_ID |                      |
|       |           |          |                | #define FCLKxCH1_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH3  | TIM3_CH3 | 测频           | #define FCLKx_TIM     TIM3_ID |                      |
|       |           |          |                | #define FCLKxCH3_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | SPI1      | SPI1_RX  | SPI1接收数据   | #define SPI1RX_DMA_EN      1  | 暂时未实现           |
|------------------------------------------------------------------------------------------------------|
|       | UART3     | UART3_RX | UART3接收数据  | #define UART3RX_DMA_EN    1   |                      |
|  CH3  |----------------------------------------------------------------------------------------------|
|       | PWMx(TIM3)| TIM3_UP  | PWMx脉冲输出   | #define PWMx_MODE PWM_DMA     |                      |
|       |           |          |                | #define PWMx_TIM TIM3_ID      |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH2  | TIM1_CH2 | 测频           | #define FCLKx_TIM     TIM1_ID |                      |
|       |           |          |                | #define FCLKxCH2_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH4  | TIM3_CH4 | 测频           | #define FCLKx_TIM     TIM3_ID |                      |
|       |           |          |                | #define FCLKxCH4_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | SPI1      | SPI1_TX  | SPI1发送数据   | #define SPI1TX_DMA_EN      1  | 暂时未实现           |
|------------------------------------------------------------------------------------------------------|
|       | UART1     | UART1_TX | UART1发送数据  | #define UART1TX_DMA_EN    1   |                      |
|  CH4  |----------------------------------------------------------------------------------------------|
|       | FCLKxCH2  | TIM4_CH2 | 测频           | #define FCLKx_TIM     TIM4_ID |                      |
|       |           |          |                | #define FCLKxCH2_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH4  | TIM1_CH4 | 测频           | #define FCLKx_TIM     TIM1_ID |                      |
|       |           |          |                | #define FCLKxCH4_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | SPI2      | SPI2_RX  | SPI2接收数据   | #define SPI2RX_DMA_EN      1  | 暂时未实现           |
|------------------------------------------------------------------------------------------------------|
|       | UART1     | UART1_RX | UART1接收数据  | #define UART1RX_DMA_EN    1   |                      |
|  CH5  |----------------------------------------------------------------------------------------------|
|       | PWMx(TIM1)| TIM1_UP  | PWMx脉冲输出   | #define PWMx_MODE PWM_DMA     |                      |
|       |           |          |                | #define PWMx_TIM TIM1_ID      |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH1  | TIM2_CH1 | 测频或占空比   | #define FCLKx_TIM     TIM2_ID |                      |
|       |           |          |                | #define FCLKxCH1_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH3  | TIM4_CH3 | 测频           | #define FCLKx_TIM     TIM4_ID |                      |
|       |           |          |                | #define FCLKxCH3_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | SPI2      | SPI2_TX  | SPI2发送数据   | #define SPI2TX_DMA_EN      1  | 暂时未实现           |
|------------------------------------------------------------------------------------------------------|
|       | UART2     | UART2_RX | UART2接收数据  | #define UART2RX_DMA_EN    1   |                      |
|  CH6  |----------------------------------------------------------------------------------------------|
|       | FCLKxCH1  | TIM3_CH1 | 测频或占空比   | #define FCLKx_TIM     TIM3_ID |                      |
|       |           |          |                | #define FCLKxCH1_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH3  | TIM1_CH3 | 测频           | #define FCLKx_TIM     TIM1_ID |                      |
|       |           |          |                | #define FCLKxCH3_DMA_EN    1  |                      |
|------------------------------------------------------------------------------------------------------|
|       | UART2     | UART2_TX | UART2发送数据  | #define UART2TX_DMA_EN    1   |                      |
|  CH7  |----------------------------------------------------------------------------------------------|
|       | DAC2      | DAC2     | DAC2输出信号   | #define DAC2_MODE 1(or 2)     | 工作模式为1或者2     |
|       |----------------------------------------------------------------------------------------------|
|       | PWMx(TIM4)| TIM4_UP  | PWMx脉冲输出   | #define PWMx_MODE PWM_DMA     |                      |
|       |           |          |                | #define PWMx_TIM TIM4_ID      |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH2  | TIM2_CH2 | 测频           | #define FCLKx_TIM     TIM2_ID |                      |
|       |           |          |                | #define FCLKxCH2_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH4  | TIM2_CH4 | 测频           | #define FCLKx_TIM     TIM2_ID |                      |
|       |           |          |                | #define FCLKxCH4_DMA_EN    1  |                      |
|------------------------------------------------------------------------------------------------------|
*/
// DMA2目前支持应用对照表  
/*
|------------------------------------------------------------------------------------------------------|
| 通道  |  应用     | 外设请求 | 功能说明       |   在EMBXXX_Config.h中配置项   |备注                  |
|------------------------------------------------------------------------------------------------------|
|       | ADC1      | ADC1     | ADC1模拟量转换 | #define ADC_EN         1      |                      |
|  CH1  |----------------------------------------------------------------------------------------------|
|       | PWMx(TIM8)|TIM8_UP   | PWMx脉冲输出   | #define PWMx_MODE PWM_DMA     |                      |
|       |           |          |                | #define PWMx_TIM TIM8_ID      |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH4  | TIM5_CH4 | 测频           | #define FCLKx_TIM     TIM5_ID |                      |
|       |           |          |                | #define FCLKxCH4_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH3  | TIM8_CH3 | 测频           | #define FCLKx_TIM     TIM8_ID |                      |
|       |           |          |                | #define FCLKxCH3_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | SPI3      | SPI3_RX  | SPI3接收数据   | #define SPI3RX_DMA_EN      1  | 暂时未实现           |
|------------------------------------------------------------------------------------------------------|
|       | UART6     | UART6_RX | UART6接收数据  | #define UART6RX_DMA_EN     1  |                      |
|  CH2  |----------------------------------------------------------------------------------------------|
|       | PWMx(TIM5)| TIM5_UP  | PWMx脉冲输出   | #define PWMx_MODE PWM_DMA     |                      |
|       |           |          |                | #define PWMx_TIM TIM5_ID      |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH3  | TIM5_CH3 | 测频           | #define FCLKx_TIM     TIM5_ID |                      |
|       |           |          |                | #define FCLKxCH3_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH4  | TIM8_CH4 | 测频           | #define FCLKx_TIM     TIM8_ID |                      |
|       |           |          |                | #define FCLKxCH4_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | SPI3      | SPI3_TX  | SPI3发送数据   | #define SPI3TX_DMA_EN      1  | 暂时未实现           |
|------------------------------------------------------------------------------------------------------|
|       | UART4     | UART4_RX | UART1接收数据  | #define UART4RX_DMA_EN    1   |                      |
|  CH3  |----------------------------------------------------------------------------------------------|
|       | PWMx(TIM83)|TIM8_UP  | PWMx脉冲输出   | #define PWMx_MODE PWM_DMA     |                      |
|       |           |          |                | #define PWMx_TIM TIM8_ID      |                      |
|       |----------------------------------------------------------------------------------------------|
|       | DAC1      | DAC1     | DAC1输出信号   | #define DAC1_MODE 1(or 2)     | 工作模式为1或者2     |
|------------------------------------------------------------------------------------------------------|
|       | SDIO      | SDIO     | SDIO通信       | #define SDIO_DMA_EN    1      | 暂时未实现           |
|  CH4  |----------------------------------------------------------------------------------------------|
|       | FCLKxCH2  | TIM5_CH2 | 测频           | #define FCLKx_TIM     TIM5_ID |                      |
|       |           |          |                | #define FCLKxCH2_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | DAC2      | DAC2     | DAC1输出信号   | #define DAC2_MODE 1(or 2)     | 工作模式为1或者2     |
|------------------------------------------------------------------------------------------------------|
|       | UART4     | UART4_TX | UART4发送数据  | #define UART4TX_DMA_EN    1   |                      |
|  CH5  |----------------------------------------------------------------------------------------------|      
|       | FCLKxCH1  | TIM5_CH1 | 测频或占空比   | #define FCLKx_TIM     TIM5_ID |                      |
|       |           |          |                | #define FCLKxCH1_DMA_EN    1  |                      |
|       |----------------------------------------------------------------------------------------------|
|       | FCLKxCH2  | TIM8_CH2 | 测频           | #define FCLKx_TIM     TIM8_ID |                      |
|       |           |          |                | #define FCLKxCH2_DMA_EN    1  |                      |
|------------------------------------------------------------------------------------------------------|

*/
// DMA状态标志
#define DMA_BUSY_FLAG       ((INT32U)0x80000000)   // DMA忙标志
#define DMA_INIT_FLAG       ((INT32U)0x40000000)   // 初始化完成标志

// DMA中断错误标志 
#define DMA_IT_TC           ((INT16U)0x0002) // 传输完成中断标志
#define DMA_IT_HT           ((INT16U)0x0004) // 半传输完成中断标志
#define DMA_IT_TERR         ((INT16U)0x0008) // 传输出错中断标志

// DMA1,DMA2器件使用标志定义
#define DMAxCHx_MASK_FLAG       ((INT16U)0xFF80) // 屏蔽标志

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
// 					 DMA控制器硬件驱动函数定义
//
/*************************************************************************************/

/***********************************************************************************
* Function: DMA_Init;
*
* Description: DMA初始化;
* 
* Input:  id, DMA识别号: DMA1_ID或DMA2_ID
*         pPara, DMA初始化参数;
*
* Output: none;
*          		
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32S DMA_Init(INT8U id, DMA_INIT *pPara);

#endif
/***********************************************************************************/
// 文件结束
/***********************************************************************************/
