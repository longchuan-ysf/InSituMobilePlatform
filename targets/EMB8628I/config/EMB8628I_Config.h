/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: EMB8628I_Config.h
* Project  : STM32F1XX/4XX系列模块软件
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: 本文件是EMB8628I工控板配置软件, 客户可根据模块实际应用进行更改;
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
#ifndef __EMB8628I_CONFIG_H 
#define __EMB8628I_CONFIG_H 

/************************************************************************************/
// 引用外部头文件
/************************************************************************************/
#include "const.h" 
#include "STM32Fxxx.h" 

/************************************************************************************/
// AT指令支持定义  
/************************************************************************************/
#define AT_EN          1            // AT指令使能: 0, 关闭; 1, 使能;
#define AT_VERSION     100          // AT指令版本V1.00

/************************************************************************************/
// 板子常用信息定义, 用户可根据实际情况自行修改定义  
/************************************************************************************/
#define PRODUCT_MODEL  "EMB8628I"             // 产品型号, 用户可根据实际需要修改这这个型号
#define PRODUCT_NAME   "EMB8628I工业控制板"  // 产品名字, 用户可根据实际需要修改这这个产品名称

#define HW_VERSION     102          // 硬件版本V1.02

#define SW_VERSION     110          // 软件版本V1.10
#define SW_DATE        "2020.8.24"  // 软件版本生成日期

#define BIN_NAME       "EM88628I_APP_20200824.BIN"  // 生成固件名字, 用户根据软硬件版本及生产日期自行修改

/************************************************************************************/
// 系统任务运行选择 
// 用户可以在以下选项中设定1，使能该任务运行，或设定0，关闭该任务运行
/************************************************************************************/
#if (UCOS_II_EN > 0)
#define TASK_ADCDAC_EN      0     // ADC/DAC采集任务：   0, 关闭; 1, 使能运行;
#define TASK_FILE_EN      	0	  // FILE测试任务：  0, 关闭; 1, 使能运行;
#define TASK_LWIP_EN      	0	  // TCPIP测试任务： 0, 关闭; 1, 使能运行;
#define TASK_IO_EN      	0	  // IO测试任务：    0, 关闭; 1, 使能运行;
#define TASK_UARTCAN_EN     0	  // UART测试任务：  0, 关闭; 1, 使能运行;
#define TASK_PWMFCLK_EN     0	  // PWMCLK测试任务：0, 关闭; 1, 使能运行;
#define TASK_MODBUS_EN      0	  // MODBUS测试任务：0, 关闭; 1, 使能运行;
#define TASK_DTU_EN         0	  // DTU测试任务：0, 关闭; 1, 使能运行;
#endif

/************************************************************************************/
//  系统时钟定义、系统定时器定义  
//  注意: 如果使能CAN, 则请将SYSCLK设置为: SYSCLK_144MHZ/SYSCLK_72MHZ/SYSCLK_36MHZ/
/************************************************************************************/
#define SYSCLK_HSE    50000000           // 高速外部时钟源，可根据硬件配置在3~25MHZ
#define SYSCLK        SYSCLK_168MHZ      //SYSCLK_36MHZ //SYSCLK_72MHz       // SYSCLK_25MHz //       	   // 系统时钟

#define SYS_TICK_EN   1      // 系统定时器使能: 1：打开使能， 0：关闭
#define SYS_TICK_T    10     //单位ms, 当系统时钟是72MHZ时, 最大是230ms;
                             //注意:   系统定时器定时时间, 注意应用操作系统时,这个时间固定为10ms
/************************************************************************************/
// DEBUG输出及串口配置
// 用户可以在以下选项中设定1，使能该部分调试打印信息输出，或设定0，关闭调试信息输出
/************************************************************************************/
#define DEBUG_EN 	       1         // DEBUG输出使能, 1：打开使能， 0：关闭
#define DEBUG_UART	       UART1_ID  // 选择DEBUG串口输出

#define DEBUG_SD_EN	       1         // 驱动库SD卡调试输出使能, 1：打开使能， 0：关闭
#define DEBUG_USB_EN       1         // 驱动库USB调试输出使能, 1：打开使能， 0：关闭
#define DEBUG_LIB_EN       1         // 驱动库其它调试输出使能, 1：打开使能， 0：关闭
#define DEBUG_APP_EN       1	     // 应用程序调试信息输出使能, 1：打开使能， 0：关闭

#define DEBUG_ISRHOOK_EN   1         // ISRHook.c文件打印输出使能, 1：打开使能， 0：关闭
#define DEBUG_INFO_LEN     128       // ISRHook.c文件打印输出信息最大长度
/************************************************************************************/
// 编译生成可更新代码设置
/************************************************************************************/
#define  IAP_EN            0        // 0, 可生成用仿真器下载调试代码; 1, 用于生成IAP更新代码
#if (IAP_EN>0) 
#define  IAP_FLASH         1        // 更新固件存储器选择：0,2: 无效; 1(IAP_B_ID), B区FLASH;  3(IAP_C_ID), C区FLASH; 
                                    // 对于STM32F107VC(EMB8610I)：如果固件小于120KB,可以选择B区Flash, 如果固件大于120KB必须选择C区Falsh
                                    // 对于STM32F103VE/STM32F103ZE(EMB8612I)：如果固件小于248KB,可以选择B区Flash, 如果固件大于248KB必须选择C区Falsh
									// 对于STM32F407VE/STM32F407ZE：如果固件小于240KB,可以选择B区Flash, 如果固件大于240KB必须选择C区Falsh
#define  IAP_TFTP_EN       1        // 利用以太网TFTP协议更新固件使能： 1, 使能; 0, 关闭;
#define  IAP_UART_EN       0        // 利用串口自定义协议更新固件使能： 1, 使能; 0, 关闭;
#endif                                
                                       
/************************************************************************************/
// 内部独立看门狗参数配置 
/************************************************************************************/
#define IWDG_EN        0          // 内部看门狗使能, 1：打开使能， 0：关闭
#define IWDG_TIME      1000       // 看门狗时间设定, , 设置范围:200~26000ms(驱动库V1.04版本支持到最长26秒)

/************************************************************************************/
// EXTI0~EXTI19 输入中断配置
/************************************************************************************/
// EXTI0中断配置
#define EXTI0_EN        0		 // 中断或事件使能: 0,关闭中断和事件; 1, 打开中断; 2, 打开事件请求
#define EXTI0_IO        PF0      // 在PA0, PB0, PC0, PD0, PE0, PF0, PG0, PH0, PI0中选择一个IO作为中断输入口; 
#define EXTI0_MODE      0		 // 触发中断和事件模式: 0,上升沿触发中断和事件; 1,下降沿触发中断和事件; 2,上升沿下降沿都触发中断和事件;

// EXTI1中断配置
#define EXTI1_EN        0		 // 中断或事件使能: 0,关闭中断和事件; 1, 打开中断; 2, 打开事件请求
#define EXTI1_IO        PF1      // 在PA1, PB1, PC1, PD1, PE1, PF1, PG1, PH1, PI1中选择一个IO作为中断输入口; 
#define EXTI1_MODE      0		 // 触发中断和事件模式: 0,上升沿触发中断和事件; 1,下降沿触发中断和事件; 2,上升沿下降沿都触发中断和事件;

// EXTI2中断配置
#define EXTI2_EN        0		 // 中断或事件使能: 0,关闭中断和事件; 1, 打开中断; 2, 打开事件请求
#define EXTI2_IO        PF2      // 在PA2, PB2, PC2, PD2, PE2, PF2, PG2, PH2, PI2中选择一个IO作为中断输入口; 
#define EXTI2_MODE      0		 // 触发中断和事件模式: 0,上升沿触发中断和事件; 1,下降沿触发中断和事件; 2,上升沿下降沿都触发中断和事件;

// EXTI3中断配置(CH455中断配置)
#define EXTI3_EN        0		 // 中断或事件使能: 0,关闭中断和事件; 1, 打开中断; 2, 打开事件请求
#define EXTI3_IO        PF3      // 在PA3, PB3, PC3, PD3, PE3, PF3, PG3, PH3, PI3中选择一个IO作为中断输入口; 
#define EXTI3_MODE      0		 // 触发中断和事件模式: 0,上升沿触发中断和事件; 1,下降沿触发中断和事件; 2,上升沿下降沿都触发中断和事件;

// EXTI4中断配置
#define EXTI4_EN        0		 // 中断或事件使能: 0,关闭中断和事件; 1, 打开中断; 2, 打开事件请求
#define EXTI4_IO        PF4      // 在PA4, PB4, PC4, PD4, PE4, PF4, PG4, PH4, PI4 中选择一个IO作为中断输入口; 
#define EXTI4_MODE      0		 // 触发中断和事件模式: 0,上升沿触发中断和事件; 1,下降沿触发中断和事件; 2,上升沿下降沿都触发中断和事件;

// EXTI5中断配置
#define EXTI5_EN        0		 // 中断或事件使能: 0,关闭中断和事件; 1, 打开中断; 2, 打开事件请求
#define EXTI5_IO        PF5      // 在PA5, PB5, PC5, PD5, PE5, PF5, PG5, PH5, PI5 中选择一个IO作为中断输入口; 
#define EXTI5_MODE      0		 // 触发中断和事件模式: 0,上升沿触发中断和事件; 1,下降沿触发中断和事件; 2,上升沿下降沿都触发中断和事件;

// EXTI6中断配置
#define EXTI6_EN        0		 // 中断或事件使能: 0,关闭中断和事件; 1, 打开中断; 2, 打开事件请求
#define EXTI6_IO        PF6      // 在PA6, PB6, PC6, PD6, PE6, PF6, PG6, PH6, PI6 中选择一个IO作为中断输入口; 
#define EXTI6_MODE      0		 // 触发中断和事件模式: 0,上升沿触发中断和事件; 1,下降沿触发中断和事件; 2,上升沿下降沿都触发中断和事件;

// EXTI7中断配置
#define EXTI7_EN        0		 // 中断或事件使能: 0,关闭中断和事件; 1, 打开中断; 2, 打开事件请求
#define EXTI7_IO        PF7		 // 在PA7, PB7, PC7, PD7, PE7, PF7, PG7, PH7, PI7 中选择一个IO作为中断输入口; 
#define EXTI7_MODE      0		 // 触发中断和事件模式: 0,上升沿触发中断和事件; 1,下降沿触发中断和事件; 2,上升沿下降沿都触发中断和事件;

// EXTI8中断配置
#define EXTI8_EN        0		 // 中断或事件使能: 0,关闭中断和事件; 1, 打开中断; 2, 打开事件请求
#define EXTI8_IO        PF8	     // 在PA8, PB8, PC8, PD8, PE8, PF8, PG8, PH8, PI8 中选择一个IO作为中断输入口; 
#define EXTI8_MODE      0		 // 触发中断和事件模式: 0,上升沿触发中断和事件; 1,下降沿触发中断和事件; 2,上升沿下降沿都触发中断和事件;

// EXTI9中断配置
#define EXTI9_EN        0		 // 中断或事件使能: 0,关闭中断和事件; 1, 打开中断; 2, 打开事件请求
#define EXTI9_IO        PF9	     // 在PA9, PB9, PC9, PD9, PE9, PF9, PG9, PH9, PI9 中选择一个IO作为中断输入口; 
#define EXTI9_MODE      0		 // 触发中断和事件模式: 0,上升沿触发中断和事件; 1,下降沿触发中断和事件; 2,上升沿下降沿都触发中断和事件;

// EXTI10中断配置
#define EXTI10_EN       0		 // 中断或事件使能: 0,关闭中断和事件; 1, 打开中断; 2, 打开事件请求
#define EXTI10_IO       PF10     // 在PA10, PB10, PC10, PD10, PE10, PF10, PG10, PH10, PI10 中选择一个IO作为中断输入口; 
#define EXTI10_MODE     0		 // 触发中断和事件模式: 0,上升沿触发中断和事件; 1,下降沿触发中断和事件; 2,上升沿下降沿都触发中断和事件;

// EXTI11中断配置
#define EXTI11_EN       0		 // 中断或事件使能: 0,关闭中断和事件; 1, 打开中断; 2, 打开事件请求
#define EXTI11_IO       PF11     // 在PA11, PB11, PC11, PD11, PE11, PF11, PG11, PH11, PI11 中选择一个IO作为中断输入口; 
#define EXTI11_MODE     0		 // 触发中断和事件模式: 0,上升沿触发中断和事件; 1,下降沿触发中断和事件; 2,上升沿下降沿都触发中断和事件;

// EXTI12中断配置
#define EXTI12_EN       0		 // 中断或事件使能: 0,关闭中断和事件; 1, 打开中断; 2, 打开事件请求
#define EXTI12_IO       PF12     // 在PA12, PB12, PC12, PD12, PE12, PF12, PG12, PH12, PI12 中选择一个IO作为中断输入口; 
#define EXTI12_MODE     0		 // 触发中断和事件模式: 0,上升沿触发中断和事件; 1,下降沿触发中断和事件; 2,上升沿下降沿都触发中断和事件;

// EXTI13中断配置
#define EXTI13_EN       0		 // 中断或事件使能: 0,关闭中断和事件; 1, 打开中断; 2, 打开事件请求
#define EXTI13_IO       PF13     // 在PA13, PB13, PC13, PD13, PE13, PF13, PG13, PH13, PI13 中选择一个IO作为中断输入口; 
#define EXTI13_MODE     0		 // 触发中断和事件模式: 0,上升沿触发中断和事件; 1,下降沿触发中断和事件; 2,上升沿下降沿都触发中断和事件;

// EXTI14中断配置
#define EXTI14_EN       0		 // 中断或事件使能: 0,关闭中断和事件; 1, 打开中断; 2, 打开事件请求
#define EXTI14_IO       PF14     // 在PA14, PB14, PC14, PD14, PE14, PF14, PG14, PH14, PI14 中选择一个IO作为中断输入口;
#define EXTI14_MODE     0		 // 触发中断和事件模式: 0,上升沿触发中断和事件; 1,下降沿触发中断和事件; 2,上升沿下降沿都触发中断和事件;

// EXTI15中断配置
#define EXTI15_EN       0		 // 中断或事件使能: 0,关闭中断和事件; 1, 打开中断; 2, 打开事件请求
#define EXTI15_IO       PF15     // 在PA15, PB15, PC15, PD15, PE15, PF15, PG15, PH15, PI15 中选择一个IO作为中断输入口; 
#define EXTI15_MODE     0		 // 触发中断和事件模式: 0,上升沿触发中断和事件; 1,下降沿触发中断和事件; 2,上升沿下降沿都触发中断和事件;

// EXTI16_PVD中断配置(EXIT线16连接到PVD输出)
#define EXTI16_PVD_EN               0		 // 中断或事件使能: 0,关闭中断和事件; 1, 打开中断; 2, 打开事件请求
#define EXTI16_PVD_MODE             0		 // 触发中断和事件模式: 0,上升沿触发中断和事件; 1,下降沿触发中断和事件; 2,上升沿下降沿都触发中断和事件;

// EXTI17_RTCAlarm中断配置(EXIT线17连接到RTC闹钟事件)
#define EXTI17_RTCAlarm_EN          0		 // 中断或事件使能: 0,关闭中断和事件; 1, 打开中断; 2, 打开事件请求
#define EXTI17_RTCAlarm_MODE        0		 // 触发中断和事件模式: 0,上升沿触发中断和事件; 1,下降沿触发中断和事件; 2,上升沿下降沿都触发中断和事件;

// EXTI18_USBWakeUp中断配置(EXIT线18连接到USB唤醒事件)
#define EXTI18_USBWakeUp_EN         0		 // 中断或事件使能: 0,关闭中断和事件; 1, 打开中断; 2, 打开事件请求
#define EXTI18_USBWakeUp_MODE       0		 // 触发中断和事件模式: 0,上升沿触发中断和事件; 1,下降沿触发中断和事件; 2,上升沿下降沿都触发中断和事件;


// EXTI19_NETWakeUp中断配置(EXIT线18连接到以太网唤醒事件)
#define EXTI19_NETWakeUp_EN         0		 // 中断或事件使能: 0,关闭中断和事件; 1, 打开中断; 2, 打开事件请求
#define EXTI19_NETWakeUp_MODE       0		 // 触发中断和事件模式: 0,上升沿触发中断和事件; 1,下降沿触发中断和事件; 2,上升沿下降沿都触发中断和事件;

// EXTI20_USBHSWakeUp中断配置(EXIT线20连接到USB HOST唤醒事件)
#define EXTI20_USBHSWakeUp_EN         0		 // 中断或事件使能: 0,关闭中断和事件; 1, 打开中断; 2, 打开事件请求
#define EXTI20_USBHSWakeUp_MODE       0		 // 触发中断和事件模式: 0,上升沿触发中断和事件; 1,下降沿触发中断和事件; 2,上升沿下降沿都触发中断和事件;

// EXTI21_RTCTSE中断配置(EXIT线21连接到RTC唤醒中断)
#define EXTI21_RTCTSE_EN         0		 // 中断或事件使能: 0,关闭中断和事件; 1, 打开中断; 2, 打开事件请求
#define EXTI21_RTCTSE_MODE       0		 // 触发中断和事件模式: 0,上升沿触发中断和事件; 1,下降沿触发中断和事件; 2,上升沿下降沿都触发中断和事件;

// EXTI22_RTCWakeUp中断配置(EXIT线22连接到RTC入侵和时间戳中断)
#define EXTI22_RTCWakeUp_EN         0		 // 中断或事件使能: 0,关闭中断和事件; 1, 打开中断; 2, 打开事件请求
#define EXTI22_RTCWakeUp_MODE       0		 // 触发中断和事件模式: 0,上升沿触发中断和事件; 1,下降沿触发中断和事件; 2,上升沿下降沿都触发中断和事件;
/************************************************************************************/
// UART1 参数配置
// 注意：如果定义了奇偶检验位，请将字长设置成9bit，最后一个bit是奇偶检验位
/************************************************************************************/
#define UART1_EN          1       // UART1使能, 1：打开使能， 0：关闭

#define UART1_BAUD        115200  // 定义波特率，可以设置：1200，2400，4800，9600，19200，38400，57600，115200
#define UART1_WORD_LENGTH 0       // 定义数据字长,   0: 8bit;   1: 9bit;
#define UART1_STOP_BITS   0       // 定义停止位,     0: 1bit;   1: 2bit;    2: 0.5bit;  3: 1.5bit;
#define UART1_PARITY      0       // 定义奇偶检验位, 0: 无校验; 1: 偶校验;  2: 奇校验;

#if (UART1_EN > 0)
#define UART1TX_DMA_EN    0        // 定义发送DMA使能, 1：打开使能， 0：关闭; 占用DMA2_CH8(DMA2_Stream7)
#define UART1TX_DMA_CH    DMA2_CH8 // 选择通道: DMA2_CH8

#define UART1RX_DMA_EN    0        // 定义接收DMA使能, 1：打开使能， 0：关闭; 占用DMA2_CH3(DMA2_Stream2)或DMA2_CH6(DMA2_Stream7)
#define UART1RX_DMA_CH    DMA2_CH3 // 选择通道: DMA2_CH3或DMA2_CH6(备选, 暂时不支持)
#endif

#define UART1_RXBUF_SIZE  256     // 定义接收缓存长度, 范围大于0, 根据自己实际需要设置, 不可以太大; 
#define UART1_TXBUF_SIZE  1024     // 定义发送缓存长度, 范围大于0, 根据自己实际需要设置, 不可以太大; 

/************************************************************************************/
// UART2 参数配置 
/************************************************************************************/
#define UART2_EN          1       // UART2使能, 1：打开使能， 0：关闭

#define UART2_BAUD        9600  // 定义波特率，可以设置：1200，2400，4800，9600，19200，38400，57600，115200
#define UART2_WORD_LENGTH 0       // 定义数据字长,   0: 8bit;   1: 9bit;
#define UART2_STOP_BITS   0       // 定义停止位,     0: 1bit;   1: 2bit;    2: 0.5bit;  3: 1.5bit;
#define UART2_PARITY      0       // 定义奇偶检验位, 0: 无校验; 1: 偶校验;  2: 奇校验;

#if (UART2_EN > 0)
#define UART2TX_DMA_EN    0        // 定义发送DMA使能, 1：打开使能， 0：关闭; 占用DMA1_CH7(DMA1_Stream6)
#define UART2TX_DMA_CH    DMA1_CH7 // 选择通道: DMA1_CH7

#define UART2RX_DMA_EN    0        // 定义接收DMA使能, 1：打开使能， 0：关闭; 占用DMA1_CH6(DMA1_Stream5)
#define UART2RX_DMA_CH    DMA1_CH6 // 选择通道: DMA1_CH6
#endif

#define UART2_RXBUF_SIZE  256     // 定义接收缓存长度,范围大于0, 根据自己实际需要设置, 不可以太大; 
#define UART2_TXBUF_SIZE  256     // 定义发送缓存长度,范围大于0, 根据自己实际需要设置, 不可以太大; 

/************************************************************************************/
// UART3 参数配置 
// 注意：如果定义了奇偶检验位，请将字长设置成9bit，最后一个bit是奇偶检验位
/************************************************************************************/
#define UART3_EN          0       // UART3使能, 1：打开使能， 0：关闭

#define UART3_BAUD        115200  // 定义波特率，可以设置：1200，2400，4800，9600，19200，38400，57600，115200
#define UART3_WORD_LENGTH 0       // 定义数据字长,   0: 8bit;   1: 9bit;
#define UART3_STOP_BITS   0       // 定义停止位,     0: 1bit;   1: 2bit;    2: 0.5bit;  3: 1.5bit;
#define UART3_PARITY      0       // 定义奇偶检验位, 0: 无校验; 1: 偶校验;  2: 奇校验;

#if (UART3_EN > 0)
#define UART3TX_DMA_EN    0        // 定义发送DMA使能, 1：打开使能， 0：关闭; 占用DMA1_CH4(DMA1_Stream3)或DMA1_CH5(DMA1_Stream4)
#define UART3TX_DMA_CH    DMA1_CH4 // 选择通道: DMA1_CH4或DMA1_CH5(备选, 暂时不支持)

#define UART3RX_DMA_EN    0        // 定义接收DMA使能, 1：打开使能， 0：关闭; 占用DMA1_CH2(DMA1_Stream1)
#define UART3RX_DMA_CH    DMA1_CH2 // 选择通道: DMA1_CH2
#endif

#define UART3_RXBUF_SIZE  256     // 定义接收缓存长度, 范围大于0, 根据自己实际需要设置, 不可以太大; 
#define UART3_TXBUF_SIZE  256     // 定义发送缓存长度, 范围大于0, 根据自己实际需要设置, 不可以太大; 

/************************************************************************************/
// UART4 参数配置
// 注意：如果定义了奇偶检验位，请将字长设置成9bit，最后一个bit是奇偶检验位
/************************************************************************************/
#define UART4_EN          0       // UART4使能, 1：打开使能， 0：关闭

#define UART4_BAUD        115200  // 定义波特率，可以设置：1200，2400，4800，9600，19200，38400，57600，115200
#define UART4_WORD_LENGTH 0       // 定义数据字长,   0: 8bit;   1: 9bit;
#define UART4_STOP_BITS   0       // 定义停止位,     0: 1bit;   1: 2bit;    2: 0.5bit;  3: 1.5bit;
#define UART4_PARITY      0       // 定义奇偶检验位, 0: 无校验; 1: 偶校验;  2: 奇校验;

#if (UART4_EN > 0)
#define UART4TX_DMA_EN    0        // 定义发送DMA使能, 1：打开使能， 0：关闭; 占用DMA1_CH5(DMA1_Stream4)
#define UART4TX_DMA_CH    DMA1_CH5 // 选择通道: DMA1_CH5

#define UART4RX_DMA_EN    0        // 定义接收DMA使能, 1：打开使能， 0：关闭; 占用DMA1_CH3(DMA1_Stream2)
#define UART4RX_DMA_CH    DMA1_CH3 // 选择通道: DMA1_CH3
#endif

#define UART4_RXBUF_SIZE  256     // 定义接收缓存长度, 范围大于0, 根据自己实际需要设置, 不可以太大; 
#define UART4_TXBUF_SIZE  256     // 定义发送缓存长度, 范围大于0, 根据自己实际需要设置, 不可以太大;  

/************************************************************************************/
// UART5 参数配置 
// 注意：如果定义了奇偶检验位，请将字长设置成9bit，最后一个bit是奇偶检验位
/************************************************************************************/
#define UART5_EN          1      // UART5使能, 1：打开使能， 0：关闭

#define UART5_BAUD        115200  // 定义波特率，可以设置：1200，2400，4800，9600，19200，38400，57600，115200
#define UART5_WORD_LENGTH 0       // 定义数据字长,   0: 8bit;   1: 9bit;
#define UART5_STOP_BITS   0       // 定义停止位,     0: 1bit;   1: 2bit;    2: 0.5bit;  3: 1.5bit;
#define UART5_PARITY      0       // 定义奇偶检验位, 0: 无校验; 1: 偶校验;  2: 奇校验;

#if (UART5_EN > 0)
#define UART5TX_DMA_EN    0        // 定义发送DMA使能, 1：打开使能， 0：关闭; 占用DMA1_CH8(DMA1_Stream7)
#define UART5TX_DMA_CH    DMA1_CH8 // 选择通道: DMA1_CH8

#define UART5RX_DMA_EN    0        // 定义接收DMA使能, 1：打开使能， 0：关闭; 占用DMA1_CH1(DMA1_Stream0)
#define UART5RX_DMA_CH    DMA1_CH1 // 选择通道: DMA1_CH1
#endif

#define UART5_RXBUF_SIZE  256     // 定义接收缓存长度, 范围大于0, 根据自己实际需要设置, 不可以太大; 
#define UART5_TXBUF_SIZE  256     // 定义发送缓存长度, 范围大于0, 根据自己实际需要设置, 不可以太大; 

/************************************************************************************/
// UART6 参数配置 
// 注意：如果定义了奇偶检验位，请将字长设置成9bit，最后一个bit是奇偶检验位
/************************************************************************************/
/*
#define UART6_EN          0      // UART5使能, 1：打开使能， 0：关闭

#define UART6_BAUD        115200  // 定义波特率，可以设置：1200，2400，4800，9600，19200，38400，57600，115200
#define UART6_WORD_LENGTH 0       // 定义数据字长,   0: 8bit;   1: 9bit;
#define UART6_STOP_BITS   0       // 定义停止位,     0: 1bit;   1: 2bit;    2: 0.5bit;  3: 1.5bit;
#define UART6_PARITY      0       // 定义奇偶检验位, 0: 无校验; 1: 偶校验;  2: 奇校验;

#if (UART6_EN > 0)
#define UART6TX_DMA_EN    0        // 定义发送DMA使能, 1：打开使能， 0：关闭; 占用DMA2_CH7(DMA2_Stream6)或DMA2_CH8(DMA2_Stream7)
#define UART6TX_DMA_CH    DMA2_CH7 // 选择通道: DMA2_CH7或DMA2_CH8(备选, 暂时不支持)

#define UART6RX_DMA_EN    0        // 定义接收DMA使能, 1：打开使能， 0：关闭; 占用DMA2_CH2(DMA2_Stream1)或DMA2_CH3(DMA2_Stream2)
#define UART6RX_DMA_CH    DMA2_CH2 // 选择通道: DMA2_CH2或DMA2_CH3(备选, 暂时不支持)
#endif

#define UART6_RXBUF_SIZE  256     // 定义接收缓存长度, 范围大于0, 根据自己实际需要设置, 不可以太大; 
#define UART6_TXBUF_SIZE  256     // 定义发送缓存长度, 范围大于0, 根据自己实际需要设置, 不可以太大; 
*/
/************************************************************************************/
// EEPROM 参数配置(驱动库内部使用I2C1总线)
// 以下配置请不要更改
/************************************************************************************/
#define EEPROM_EN          1          // EEPROM使能, 1：打开使能， 0：关闭

#define EEPROM_DEVICE      AT24C64    // 定义器件型号	
#define EEPROM_FREQ        100000     // 读写时钟频率

/************************************************************************************/
// I2C1 参数配置(由模块内部EEPROM占用并是能初始化)
/************************************************************************************/
//#define I2C1_EN            0             // I2C1使能,      1：打开使能， 0：关闭

/************************************************************************************/
// I2C2 参数配置
/************************************************************************************/
#define I2C2_EN            1             // I2C2使能,      1：打开使能， 0：关闭

/************************************************************************************/
// I2C3 参数配置
/************************************************************************************/
#define I2C3_EN            1             // I2C3使能,      1：打开使能， 0：关闭

/************************************************************************************/
// CH455 参数配置(4*7按键驱动芯片)
/************************************************************************************/
#define CH455_EN           0            // CH455使能,      1：打开使能， 0：关闭
#define CH455_MODE         0             // CH455模式,      0(CH455_MODE_I2C): 用I2C总线控制; 1(CH455_MODE_IO)：用IO(模拟I2C总线)控制
#define CH455_I2C          I2C3_ID       // I2C选择: 0(I2C1_ID), 1(I2C2_ID), 2(I2C3_ID)

/************************************************************************************/
// SPI1参数配置
/************************************************************************************/
#define SPI1_EN         1                // SPI使能,      1：打开使能， 0：关闭
#define SPI1_CKMODE     SPI_CKMODE3      // 时钟相位模式, 参见spi.h中说明 
#define SPI1_DIVCLK     SPI_DIVCLK_8     // SPI时钟分频系数

//SPI DMA配置
#if (SPI1_EN > 0)
#define SPI1_DMA_ID      DMA2_ID  // 选择DMA: 固定DMA1_ID

#define SPI1TX_DMA_EN    0        // 定义发送DMA使能, 1：打开使能， 0：关闭; 占用DMA1_CH3
#define SPI1TX_DMA_CH    DMA2_CH4  // 选择通道: DMA2_CH4或DMA2_CH6

#define SPI1RX_DMA_EN    0        // 定义接收DMA使能, 1：打开使能， 0：关闭; 占用DMA1_CH2
#define SPI1RX_DMA_CH    DMA2_CH3  // 选择通道: DMA2_CH1或DMA2_CH3

#if (SPI1RX_DMA_EN > 0)           // 目前只支持全双工, 所以接收DMA使能则发送DMA必须使能 
#define SPI1TX_DMA_EN    1
#endif

//#define SPI1_ISRHOOK_EN   0       // 配置使能钩子函数: 1: 使能; 0: 关闭 
#endif

/************************************************************************************/
// SPI2参数配置
/************************************************************************************/
//#define SPI2_EN         0                // SPI使能: 1：打开使能， 0：关闭
//#define SPI2_CKMODE     SPI_CKMODE3      // 时钟相位模式, 参见spi.h中说明 
//#define SPI2_DIVCLK     SPI_DIVCLK_8     // SPI时钟分频系数

//SPI DMA配置
//#if (SPI2_EN > 0)
//#define SPI2_DMA_ID      DMA1_ID  // 选择DMA: 固定DMA1_ID

//#define SPI2TX_DMA_EN    0        // 定义发送DMA使能, 1：打开使能， 0：关闭; 占用DMA1_CH5
//#define SPI2TX_DMA_CH    DMA1_CH5 // 选择通道: DMA1_CH5

//#define SPI2RX_DMA_EN    0        // 定义接收DMA使能, 1：打开使能， 0：关闭; 占用DMA1_CH4
//#define SPI2RX_DMA_CH    DMA1_CH4  // 选择通道: DMA1_CH4

//#if (SPI2RX_DMA_EN > 0)           // 目前只支持全双工, 所以接收DMA使能则发送DMA必须使能 
//#define SPI2TX_DMA_EN    1
//#endif

//#define SPI2_ISRHOOK_EN   0        // 配置使能钩子函数: 1: 使能; 0: 关闭 
//#endif

/************************************************************************************/
// SPI3参数配置
/************************************************************************************/
#define SPI3_EN         0                // SPI使能: 1：打开使能， 0：关闭
#define SPI3_CKMODE     SPI_CKMODE3      // 时钟相位模式, 参见spi.h中说明 
#define SPI3_DIVCLK     SPI_DIVCLK_8     // SPI时钟分频系数

#if (SPI3_EN > 0)
#define SPI3_DMA_ID      DMA1_ID  // 选择DMA: 固定DMA2_ID

#define SPI3TX_DMA_EN    0        // 定义发送DMA使能, 1：打开使能， 0：关闭; 占用DMA1_CH2
#define SPI3TX_DMA_CH    DMA1_CH6 // 选择通道: DMA1_CH6或DMA1_CH8

#define SPI3RX_DMA_EN    0        // 定义接收DMA使能, 1：打开使能， 0：关闭; 占用DMA1_CH1
#define SPI3RX_DMA_CH    DMA1_CH1  // 选择通道: DMA1_CH1或DMA_CH3

#if (SPI3RX_DMA_EN > 0)           // 目前只支持全双工, 所以接收DMA使能则发送DMA必须使能 
#define SPI3TX_DMA_EN    1
#endif

//#define SPI3_ISRHOOK_EN   0        // 配置使能钩子函数: 1: 使能; 0: 关闭 
#endif
     
/************************************************************************************/
// RTC 参数配置 
/************************************************************************************/
#define RTC_EN           0          // RTC使能, 1：打开使能， 0：关闭

#define RTC_WKUPIT_EN    0         // RTC唤醒中断使能, 1：打开使能， 0：关闭	
#define RTC_ALRAIT_EN    0         // RTC闹钟A中断使能, 1：打开使能， 0：关闭	
#define RTC_ALRBIT_EN    0         // RTC闹钟B中断使能, 1：打开使能， 0：关闭	
#define RTC_TSFIT_EN     0         // RTC时间戳中断使能, 1：打开使能， 0：关闭
#define RTC_TAMP1IT_EN   0         // RTC入侵检测1中断使能, 1：打开使能， 0：关闭
#define RTC_TAMP2IT_EN   0         // RTC入侵检测1中断使能, 1：打开使能， 0：关闭
/************************************************************************************/
// BKP 参数配置 
/************************************************************************************/
#define BKP_EN          0          // BKP使能, 1：打开使能， 0：关闭

/***********************************************************************************
// ADC参数配置
// 注意: ADC1(AI1-AI6)占用DMA2_CH1(DMA2_Stream0)
*********************************************************************************/
#define ADC_EN         0      // ADC使能, 1：打开使能， 0：关闭

// 设置AD转换输出值方式
#define ADC_OUT_TYPE   ADC_ISROUT // 可以选择: 0：ADC_ISROUT,选择中断输出AD采样值;
                                  //           1：ADC_READOUT, 选择ADC_Read()函数读取采样值
// 模块模拟量输入使能定义
#define AI1_EN        1      // AI1使能, 1：打开使能， 0：关闭
#define AI2_EN        1      // AI2使能, 1：打开使能， 0：关闭
#define AI3_EN        1      // AI3使能, 1：打开使能， 0：关闭
#define AI4_EN        1      // AI4使能, 1：打开使能， 0：关闭
#define AI5_EN        1      // AI5使能, 1：打开使能， 0：关闭
#define AI6_EN        1      // AI6使能, 1：打开使能， 0：关闭
#define AI7_EN        0      // AI7使能, 1：打开使能， 0：关闭
#define AI8_EN        0      // AI8使能, 1：打开使能， 0：关闭
#define AI9_EN        0      // AI9使能, 1：打开使能， 0：关闭 
#define AI10_EN       0      // AI10使能, 1：打开使能， 0：关闭

#if (ADC_EN == 1)
#define ADC_CHNUM      (AI1_EN+AI2_EN+AI3_EN+AI4_EN+AI5_EN+AI6_EN+AI7_EN+AI8_EN+AI9_EN+AI10_EN)	  // 采样通道数
#define ADC_AVGNUM     4           // 定义采样次数来计算平均值, 范围 1~256, 注意：此值太大会占用很大内存空间
#endif

#define ADC_FREQ       100                // AD采样频率, 每秒钟采样次数
#define ADC_SAMPLE_TIME  ADC_SAMP7T0US   // 采样间隔
#define ADC_TIM14        ADC_TIM14MAIN_FLAG  // 选择AD采样定时器, 可在ADC_TIM14CH1_FLAG/ADC_TIM14MAIN_FLAG中选择
                                             // 默认ADC_TIM14MAIN_FLAG就可以了, 不用修改  

// 板子端口输入量程
#define AI1_RANGE     0      // AI1采样量程: 0, 原始采样值(0~4095); 1, 0~+10V; 2, -10V~+10V; 3, 0~5V; 4, -5V~+5V; 5, 0~+20mA; 6, -20mA~+20mA; 
#define AI2_RANGE     1      // AI2采样量程: 0, 原始采样值(0~4095); 1, 0~+10V; 2, -10V~+10V; 3, 0~5V; 4, -5V~+5V; 5, 0~+20mA; 6, -20mA~+20mA; 
#define AI3_RANGE     1      // AI3采样量程: 0, 原始采样值(0~4095); 1, 0~+10V; 2, -10V~+10V; 3, 0~5V; 4, -5V~+5V; 5, 0~+20mA; 6, -20mA~+20mA; 
#define AI4_RANGE     1      // AI4采样量程: 0, 原始采样值(0~4095); 1, 0~+10V; 2, -10V~+10V; 3, 0~5V; 4, -5V~+5V; 5, 0~+20mA; 6, -20mA~+20mA; 
#define AI5_RANGE     1      // AI5采样量程: 0, 原始采样值(0~4095); 1, 0~+10V; 2, -10V~+10V; 3, 0~5V; 4, -5V~+5V; 5, 0~+20mA; 6, -20mA~+20mA; 
#define AI6_RANGE     1      // AI6采样量程: 0, 原始采样值(0~4095); 1, 0~+10V; 2, -10V~+10V; 3, 0~5V; 4, -5V~+5V; 5, 0~+20mA; 6, -20mA~+20mA; 
#define AI7_RANGE     0      // AI7采样量程: 0, 原始采样值(0~4095); 1, 0~+10V; 2, -10V~+10V; 3, 0~5V; 4, -5V~+5V; 5, 0~+20mA; 6, -20mA~+20mA;
#define AI8_RANGE     0      // AI8采样量程: 0, 原始采样值(0~4095); 1, 0~+10V; 2, -10V~+10V; 3, 0~5V; 4, -5V~+5V; 5, 0~+20mA; 6, -20mA~+20mA; 
#define AI9_RANGE     0      // AI9采样量程: 0, 原始采样值(0~4095); 1, 0~+10V; 2, -10V~+10V; 3, 0~5V; 4, -5V~+5V; 5, 0~+20mA; 6, -20mA~+20mA; 
#define AI10_RANGE    0      // AI10采样量程: 0, 原始采样值(0~4095); 1, 0~+10V; 2, -10V~+10V; 3, 0~5V; 4, -5V~+5V; 5, 0~+20mA; 6, -20mA~+20mA; 

// 目前ADC采样固定用DMA方式存储数据
#if (ADC_EN > 0)
#define ADC_DMA_EN    1        // ADC DMA使能, 1：打开使能， 0：关闭; 占用DMA2_CH1(DMA2_Stream0)或DMA2_CH5(DMA2_Stream6)
#define ADC_DMA_CH    DMA2_CH1 // 选择通道: DMA2_CH1或DMA2_CH5(备选, 暂时不支持)
#endif
/************************************************************************************/
//  DAC1,DAC2配置
// 注意: 在模式是1或者2时, DAC1(AO1)占用DMA1_CH6(DMA1_Stream5), DAC2(AO2)占用DMA1_CH7(DMA1_Stream6)
/************************************************************************************/
// DAC1
#define DAC1_EN            0		// DAC1使能, 1：打开使能， 0：关闭
#define DAC1_MODE		   0		// DAC1模式：0(DAC_MODE_MTOUT), 手动输出; 
                                    //           1(DAC_MODE_ATOUT_N), 连续输出1~N个缓存中的数据后停止; 
                                    //           2(DAC_MODE_ATOUT), 持续输出缓存中的数据, 不停止;
#define DAC1_FREQ		   1000   	// DAC1自动输出频率
#if ((DAC1_EN>0)&&(DAC1_MODE>0))
#define DAC1_TXBUF_SIZE    256 	    // DAC1发送数据缓存长度

#define DAC1_DMA_EN        1        // DAC1 DMA使能, 1：打开使能， 0：关闭; 占用DMA1_CH6(DMA1_Stream5)
#define DAC1_DMA_CH        DMA1_CH6 // 选择通道: DMA1_CH6
#endif

// DAC2
#define DAC2_EN            0		// DAC2使能, 1：打开使能， 0：关闭
#define DAC2_MODE		   0		// DAC2模式：0(DAC_MODE_MTOUT), 手动输出; 
                                    //           1(DAC_MODE_ATOUT_N), 连续输出1~N个缓存中的数据后停止; 
                                    //           2(DAC_MODE_ATOUT), 持续输出缓存中的数据, 不停止;             
#define DAC2_FREQ		   1000   	// DAC2自动输出频率
#if ((DAC2_EN>0)&&(DAC2_MODE>0))
#define DAC2_TXBUF_SIZE    256 	    // DAC2发送数据缓存长度

#define DAC2_DMA_EN        1        // DAC2 DMA使能, 1：打开使能， 0：关闭; 占用DMA1_CH7(DMA1_Stream6)
#define DAC2_DMA_CH        DMA1_CH7 // 选择通道: DMA1_CH7
#endif

/************************************************************************************/
// PWM1 输出配置(占用定时器2)
// JP12: PWM1(PWM1_PUL),DIR1(PWM1_DIR)和ENA1(PWM1_ENA)
// 注意: 在PWM_DMA输出模式, 占用DMA1_CH2(DMA1_Stream1) 
/************************************************************************************/
#define PWM1_EN             1		   // PWM1使能, 1：打开使能， 0：关闭

// 定义PWM输出模式设置
#define PWM1_MODE           PWM_FREQ_N   // 可以选择: 0(PWM_FREQ):   连续脉冲频率输出, 持续输出
                                       //           1(PWM_FREQ_N): 多个脉冲频率输出, 输出完设定的脉冲数后停止
                                       //           2(PWM_RATE):   固定频率占空比可调连续脉冲输出: 输出PWM, 频率固定,占空比0%-100%可调, 持续输出
                                       //           3(PWM_DMA):    新增控制模式, 利用PWM_Write()函数实现DMA输出控制模式, 具体控制方式由函数参数决定 
                                       
#define PWM1_FREQ		    1000  	   // 初始频率
#define PWM1_TIM            TIM2_ID    // 选择定时器, 这个设置不可更改

// 通道使能
#define PWM1CH1_EN		    1		   // PWM1CH1：1, 使能; 0, 关闭
#define PWM1CH2_EN		    0		   // PWM1CH2：1, 使能; 0, 关闭
#define PWM1CH3_EN		    0		   // PWM1CH3：1, 使能; 0, 关闭
#define PWM1CH4_EN		    0		   // PWM1CH4：1, 使能; 0, 关闭

// PWM所有通道使能 
#define PWM1CH_EN		   (PWM1CH1_EN|(PWM1CH2_EN<<1)|(PWM1CH3_EN<<2)|(PWM1CH4_EN<<3))  // PWM1所有通道使能：BIT0:CH1;BIT1:CH2;BIT2:CH3;BIT3:CH4;

#define PWM1CH1_RATE		500        // PWM1CH1初始占空比50%(0(0.0%)~1000(100.0%))
#define PWM1CH2_RATE		500        // PWM1CH2初始占空比50%(0(0.0%)~1000(100.0%))
#define PWM1CH3_RATE		500        // PWM1CH3初始占空比50%(0(0.0%)~1000(100.0%))
#define PWM1CH4_RATE		500        // PWM1CH4初始占空比50%(0(0.0%)~1000(100.0%))

#define PWM1CH1_PIN		    0          // PWM1CH1停止模式输出管脚电平: 0, 低电平; 1, 高电平
#define PWM1CH2_PIN		    0          // PWM1CH2停止模式输出管脚电平: 0, 低电平; 1, 高电平
#define PWM1CH3_PIN		    0          // PWM1CH3停止模式输出管脚电平: 0, 低电平; 1, 高电平
#define PWM1CH4_PIN		    0          // PWM1CH4停止模式输出管脚电平: 0, 低电平; 1, 高电平

#if ((PWM1_EN > 0)&&(PWM1_MODE == PWM_DMA))
#define PWM1_DMA_EN         1          // PWM1 DMA使能, 1：打开使能， 0：关闭; 占用DMA1_CH2(DMA1_Stream1)
#define PWM1_DMA_CH         DMA1_CH2   // 选择通道: DMA1_CH2
#endif
/************************************************************************************/
// PWM2输出配置(占用定时器3)
// JP12: PWM2(PWM2_PUL),DIR2(PWM2_DIR)和ENA2(PWM2_ENA)
// 注意: 在PWM_DMA输出模式, 占用DMA1_CH3(DMA1_Stream2)
/************************************************************************************/
// PWM2 配置
#define PWM2_EN           	1		   // PWM2使能, 1：打开使能， 0：关闭

// 定义PWM输出模式设置
#define PWM2_MODE           PWM_FREQ   // 可以选择: 0(PWM_FREQ):   连续脉冲频率输出, 持续输出
                                       //           1(PWM_FREQ_N): 多个脉冲频率输出, 输出完设定的脉冲数后停止
                                       //           2(PWM_RATE):   固定频率占空比可调连续脉冲输出: 输出PWM, 频率固定,占空比0%-100%可调, 持续输出
                                       //           3(PWM_DMA):    新增控制模式, 利用PWM_Write()函数实现DMA输出控制模式, 具体控制方式由函数参数决定 
                                       
#define PWM2_FREQ		    1000	   // 初始频率
#define PWM2_TIM        	TIM3_ID    // 选择定时器, 这个设置不可更改

#define PWM2CH1_EN		    1		   // PWM1CH1：1, 使能; 0, 关闭
#define PWM2CH2_EN		    0		   // PWM1CH2：1, 使能; 0, 关闭
#define PWM2CH3_EN		    0		   // PWM1CH3：1, 使能; 0, 关闭
#define PWM2CH4_EN		    0		   // PWM1CH4：1, 使能; 0, 关闭
// PWM所有通道使能 
#define PWM2CH_EN		   (PWM2CH1_EN|(PWM2CH2_EN<<1)|(PWM2CH3_EN<<2)|(PWM2CH4_EN<<3))  // PWM2所有通道使能：BIT0:CH1;BIT1:CH2;BIT2:CH3;BIT3:CH4;

#define PWM2CH1_RATE		500        // PWM1CH1初始占空比50%(0(0.0%)~1000(100.0%))
#define PWM2CH2_RATE		500        // PWM1CH2初始占空比50%(0(0.0%)~1000(100.0%))
#define PWM2CH3_RATE		500        // PWM1CH3初始占空比50%(0(0.0%)~1000(100.0%))
#define PWM2CH4_RATE		500        // PWM1CH4初始占空比50%(0(0.0%)~1000(100.0%))

#define PWM2CH1_PIN		    0          // PWM1CH1停止模式输出管脚电平: 0, 低电平; 1, 高电平
#define PWM2CH2_PIN		    0          // PWM1CH2停止模式输出管脚电平: 0, 低电平; 1, 高电平
#define PWM2CH3_PIN		    0          // PWM1CH3停止模式输出管脚电平: 0, 低电平; 1, 高电平
#define PWM2CH4_PIN		    0          // PWM1CH4停止模式输出管脚电平: 0, 低电平; 1, 高电平

#if ((PWM2_EN > 0)&&(PWM2_MODE == PWM_DMA))
#define PWM2_DMA_EN         1          // PWM2 DMA使能, 1：打开使能， 0：关闭; 占用DMA1_CH3(DMA1_Stream2)
#define PWM2_DMA_CH         DMA1_CH3   // 选择通道: DMA1_CH3
#endif
/************************************************************************************/
// PWM3输出配置(占用定时器5)    
// JP13: PWM3(PWM3_PUL),DIR3(PWM3_DIR)和ENA3(PWM3_ENA)
// 注意: 在PWM_DMA输出模式, 占用DMA1_CH1(DMA1_Stream0)
/************************************************************************************/
// PWM3 配置
#define PWM3_EN           	1		   // PWM3使能, 1：打开使能， 0：关闭

// 定义PWM输出模式设置
#define PWM3_MODE           PWM_FREQ   // 可以选择: 0(PWM_FREQ):   连续脉冲频率输出, 持续输出
                                       //           1(PWM_FREQ_N): 多个脉冲频率输出, 输出完设定的脉冲数后停止
                                       //           2(PWM_RATE):   固定频率占空比可调连续脉冲输出: 输出PWM, 频率固定,占空比0%-100%可调, 持续输出
                                       //           3(PWM_DMA):    新增控制模式, 利用PWM_Write()函数实现DMA输出控制模式, 具体控制方式由函数参数决定 
                                       
#define PWM3_FREQ		    1000	   // 初始频率
#define PWM3_TIM        	TIM5_ID    // 选择定时器, 这个设置不可更改

#define PWM3CH1_EN		    1		   // PWM1CH1：1, 使能; 0, 关闭
#define PWM3CH2_EN		    0		   // PWM1CH2：1, 使能; 0, 关闭
#define PWM3CH3_EN		    0		   // PWM1CH3：1, 使能; 0, 关闭
#define PWM3CH4_EN		    0		   // PWM1CH4：1, 使能; 0, 关闭
// PWM所有通道使能 
#define PWM3CH_EN		   (PWM3CH1_EN|(PWM3CH2_EN<<1)|(PWM3CH3_EN<<2)|(PWM3CH4_EN<<3))  // PWM3所有通道使能：BIT0:CH1;BIT1:CH2;BIT2:CH3;BIT3:CH4;


#define PWM3CH1_RATE		500        // PWM1CH1初始占空比50%(0(0.0%)~1000(100.0%))
#define PWM3CH2_RATE		500        // PWM1CH2初始占空比50%(0(0.0%)~1000(100.0%))
#define PWM3CH3_RATE		500        // PWM1CH3初始占空比50%(0(0.0%)~1000(100.0%))
#define PWM3CH4_RATE		500        // PWM1CH4初始占空比50%(0(0.0%)~1000(100.0%))

#define PWM3CH1_PIN		    0          // PWM1CH1停止模式输出管脚电平: 0, 低电平; 1, 高电平
#define PWM3CH2_PIN		    0          // PWM1CH2停止模式输出管脚电平: 0, 低电平; 1, 高电平
#define PWM3CH3_PIN		    0          // PWM1CH3停止模式输出管脚电平: 0, 低电平; 1, 高电平
#define PWM3CH4_PIN		    0          // PWM1CH4停止模式输出管脚电平: 0, 低电平; 1, 高电平

#if ((PWM3_EN > 0)&&(PWM3_MODE == PWM_DMA))
#define PWM3_DMA_EN         1          // PWM3 DMA使能, 1：打开使能， 0：关闭; 占用DMA1_CH1(DMA1_Stream0)
#define PWM3_DMA_CH         DMA1_CH1   // 选择通道: DMA1_CH1
#endif
/************************************************************************************/
// PWM4输出配置(占用定时器4) 
// JP13: PWM4(PWM4_PUL),DIR4(PWM4_DIR)和ENA4(PWM4_ENA)
// 注意不能与FCLK3同时使能, 而且当PWM4使能时板子上: RK10断开, RK11短接
// 注意: 在PWM_DMA输出模式, 占用DMA1_CH7(DMA1_Stream6)
/************************************************************************************/
// PWM4 配置
#define PWM4_EN           	1		   // PWM4使能, 1：打开使能， 0：关闭

// 定义PWM输出模式设置
#define PWM4_MODE           PWM_FREQ   // 可以选择: 0(PWM_FREQ):   连续脉冲频率输出, 持续输出
                                       //           1(PWM_FREQ_N): 多个脉冲频率输出, 输出完设定的脉冲数后停止
                                       //           2(PWM_RATE):   固定频率占空比可调连续脉冲输出: 输出PWM, 频率固定,占空比0%-100%可调, 持续输出
                                       //           3(PWM_DMA):    新增控制模式, 利用PWM_Write()函数实现DMA输出控制模式, 具体控制方式由函数参数决定 
                                       
#define PWM4_FREQ		    1000	   // 初始频率
#define PWM4_TIM        	TIM4_ID    // 选择定时器, 这个设置不可更改

#define PWM4CH1_EN		    1		   // CH1：1, 使能; 0, 关闭
#define PWM4CH2_EN		    0		   // CH2：1, 使能; 0, 关闭
#define PWM4CH3_EN		    0		   // CH3：1, 使能; 0, 关闭
#define PWM4CH4_EN		    0		   // CH4：1, 使能; 0, 关闭
// PWM所有通道使能 
#define PWM4CH_EN		   (PWM4CH1_EN|(PWM4CH2_EN<<1)|(PWM4CH3_EN<<2)|(PWM4CH4_EN<<3))  // PWM4所有通道使能：BIT0:CH1;BIT1:CH2;BIT2:CH3;BIT3:CH4;


#define PWM4CH1_RATE		500        // CH1初始占空比50%(0(0.0%)~1000(100.0%))
#define PWM4CH2_RATE		500        // CH2初始占空比50%(0(0.0%)~1000(100.0%))
#define PWM4CH3_RATE		500        // CH3初始占空比50%(0(0.0%)~1000(100.0%))
#define PWM4CH4_RATE		500        // CH4初始占空比50%(0(0.0%)~1000(100.0%))

#define PWM4CH1_PIN		    0          // CH1停止模式输出管脚电平: 0, 低电平; 1, 高电平
#define PWM4CH2_PIN		    0          // CH2停止模式输出管脚电平: 0, 低电平; 1, 高电平
#define PWM4CH3_PIN		    0          // CH3停止模式输出管脚电平: 0, 低电平; 1, 高电平
#define PWM4CH4_PIN		    0          // CH4停止模式输出管脚电平: 0, 低电平; 1, 高电平

#if ((PWM4_EN > 0)&&(PWM4_MODE == PWM_DMA))
#define PWM4_DMA_EN         1          // PWM4 DMA使能, 1：打开使能， 0：关闭; 占用DMA1_CH7(DMA1_Stream6)
#define PWM4_DMA_CH         DMA1_CH7   // 选择通道: DMA1_CH7
#endif
/************************************************************************************/
// FCLK 脉冲输入配置(占用定时器1)
// JP17: 1脚, +VT; 2,3脚(A+,A-: FCLK1_CH1),PE9; 4,5脚(B+,B-: FCLK1_CH2), PE11; 6,7脚(Z+,Z-: FCLK1_CH3), PE13; 8脚, GND;
/************************************************************************************/
#define FCLK1_EN           0	       // FCLK1使能, 1：打开使能， 0：关闭
#define FCLK1_MODE	       2		   // 模式选择: 0(FCLK_MODE_COUNT), 计数模式(1路, CH1输入有效); 
                                       //           1(FCLK_MODE_DECODE), 正交编码器计数(CH1接A，CH2接B);
                                       //           2(FCLK_MODE_FREQ), 测频模式(4路, CH1, CH2, CH3, CH4输入都有效); 
                                       //           3(FCLK_MODE_PWMRATE), 测PWM占空比模式(1路, CH1输入有效); 
#define FCLK1_TIM          TIM1_ID     // 选择定时器, 这个设置不可更改

#define FCLK1CH1_EN		   1	       // FCLK1：1, 使能; 0, 关闭
#define FCLK1CH2_EN		   1		   // FCLK2：1, 使能; 0, 关闭
#define FCLK1CH3_EN		   1	       // FCLK3：1, 使能; 0, 关闭
#define FCLK1CH4_EN		   0		   // FCLK4：1, 使能; 0, 关闭
// FCLK1所有通道使能 
#define FCLK1CH_EN		   (FCLK1CH1_EN|(FCLK1CH2_EN<<1)|(FCLK1CH3_EN<<2)|(FCLK1CH4_EN<<3))  // FCLK1所有通道使能：BIT0:CH1;BIT1:CH2;BIT2:CH3;BIT3:CH4;

#define FCLK1_MINFREQ	   100     	   // 模式2，3中，测量最小频率设定, 单位hz
 
#define FCLK1CH1_PIN	   0           // FCLK1管脚输入信号触发边沿： 0, 上升沿; 1, 下降沿
#define FCLK1CH2_PIN	   0           // FCLK2管脚输入信号触发边沿： 0, 上升沿; 1, 下降沿
#define FCLK1CH3_PIN	   0           // FCLK3管脚输入信号触发边沿： 0, 上升沿; 1, 下降沿
#define FCLK1CH4_PIN	   0           // FCLK4管脚输入信号触发边沿： 0, 上升沿; 1, 下降沿

#define FCLK1CH1_PCS	   0           // CH1管脚输入信号预分频系数： 0, 不分频; 1, 2分频; 2, 4分频; 3, 8分频;
#define FCLK1CH2_PCS	   0           // CH2管脚输入信号预分频系数： 0, 不分频; 1, 2分频; 2, 4分频; 3, 8分频;
#define FCLK1CH3_PCS	   0           // CH3管脚输入信号预分频系数： 0, 不分频; 1, 2分频; 2, 4分频; 3, 8分频;
#define FCLK1CH4_PCS	   0           // CH4管脚输入信号预分频系数： 0, 不分频; 1, 2分频; 2, 4分频; 3, 8分频;


#if ((FCLK1_EN > 0)&&((FCLK1_MODE == 2)||(FCLK1_MODE == 3)))
#if (FCLK1CH1_EN > 0)
#define FCLK1CH1_BUF_SIZE  16         // FCLK1CH1缓存长度,范围 1~64
#endif
#if (FCLK1CH2_EN > 0)
#define FCLK1CH2_BUF_SIZE  16         // FCLK1CH2缓存长度,范围 1~64
#endif
#if (FCLK1CH3_EN > 0)
#define FCLK1CH3_BUF_SIZE  16         // FCLK1CH3缓存长度,范围 1~64
#endif
#if (FCLK1CH4_EN > 0)
#define FCLK1CH4_BUF_SIZE  16         // FCLK1CH4缓存长度,范围 1~64
#endif
#endif

// FCLK1各个通道DMA使能, 只有测频模式和测PWM占空比模式才支持DMA功能
// 注意以下FCLK各通道同时只允许一个通道DMA使能, 使用TIM1定时器
#if ((FCLK1_EN > 0)&&(FCLK1_MODE > 1)) 
#define FCLK1CH1_DMA_EN		0	         // CH1 DMA：1, 使能; 0, 关闭,  占用DMA2_CH2(DMA2_Stream1)或DMA2_CH4(DMA2_Stream3)或DMA2_CH7(DMA2_Stream6)
#define FCLK1CH1_DMA_CH     DMA2_CH2     // 选择通道: DMA2_CH2或DMA2_CH4(备选, 暂时不支持)或DMA2_CH7(备选, 暂时不支持)

#define FCLK1CH2_DMA_EN		0	         // CH2 DMA：1, 使能; 0, 关闭,  占用DMA2_CH3(DMA2_Stream2)或DMA2_CH7(DMA2_Stream6) 
#define FCLK1CH2_DMA_CH     DMA2_CH3     // 选择通道: DMA2_CH3或DMA2_CH7(备选, 暂时不支持)

#define FCLK1CH3_DMA_EN	    0	         // CH3 DMA：1, 使能; 0, 关闭,  占用DMA2_CH7(DMA2_Stream6)
#define FCLK1CH3_DMA_CH     DMA2_CH7     // 选择通道: DMA2_CH7

// 注意:  FCLK1CH4不支持DMA功能
#endif
/************************************************************************************/
// FCLK2 脉冲输入配置(占用定时器8)
// JP15: 1脚, +VT; 2,3脚(A+,A-: FCLK2_CH1),PC6; 4,5脚(B+,B-: FCLK2_CH2), PC7; 6,7脚(Z+,Z-: FCLK2_CH3), PC8; 8脚, GND;
/************************************************************************************/
#define FCLK2_EN          	0	      	 // FCLK1使能, 1：打开使能， 0：关闭
#define FCLK2_MODE	        2		     // 模式选择: 0(FCLK_MODE_COUNT), 计数模式(1路, CH1输入有效); 
                                         //           1(FCLK_MODE_DECODE), 正交编码器计数(CH1接A，CH2接B);
                                         //           2(FCLK_MODE_FREQ), 测频模式(4路, CH1, CH2, CH3, CH4输入都有效); 
                                         //           3(FCLK_MODE_PWMRATE), 测PWM占空比模式(1路, CH1输入有效);  
#define FCLK2_TIM        	TIM8_ID      // 选择定时器, 这个设置不可更改

#define FCLK2CH1_EN		    1	         // CH1：1, 使能; 0, 关闭
#define FCLK2CH2_EN		    1		     // CH2：1, 使能; 0, 关闭
#define FCLK2CH3_EN		    1	         // CH3：1, 使能; 0, 关闭
#define FCLK2CH4_EN		    0		     // CH4：1, 使能; 0, 关闭
// FCLK2所有通道使能 
#define FCLK2CH_EN		   (FCLK2CH1_EN|(FCLK2CH2_EN<<1)|(FCLK2CH3_EN<<2)|(FCLK2CH4_EN<<3))  // FCLK2所有通道使能：BIT0:CH1;BIT1:CH2;BIT2:CH3;BIT3:CH4;

#define FCLK2_MINFREQ	    100     	 // 模式2，3中，测量最小频率设定, 单位hz
 
#define FCLK2CH1_PIN	    0            // CH1管脚输入信号触发边沿： 0, 上升沿; 1, 下降沿
#define FCLK2CH2_PIN	    0            // CH2管脚输入信号触发边沿： 0, 上升沿; 1, 下降沿
#define FCLK2CH3_PIN	    0            // CH3管脚输入信号触发边沿： 0, 上升沿; 1, 下降沿
#define FCLK2CH4_PIN	    0            // CH4管脚输入信号触发边沿： 0, 上升沿; 1, 下降沿

#define FCLK2CH1_PCS	    0            // CH1管脚输入信号预分频系数： 0, 不分频; 1, 2分频; 2, 4分频; 3, 8分频;
#define FCLK2CH2_PCS	    0            // CH2管脚输入信号预分频系数： 0, 不分频; 1, 2分频; 2, 4分频; 3, 8分频;
#define FCLK2CH3_PCS	    0            // CH3管脚输入信号预分频系数： 0, 不分频; 1, 2分频; 2, 4分频; 3, 8分频;
#define FCLK2CH4_PCS	    0            // CH4管脚输入信号预分频系数： 0, 不分频; 1, 2分频; 2, 4分频; 3, 8分频;

#if ((FCLK2_EN > 0)&&((FCLK2_MODE == 2)||(FCLK2_MODE == 3)))
#if (FCLK2CH1_EN > 0)
#define FCLK2CH1_BUF_SIZE  16         // FCLK2CH1缓存长度,范围 1~64
#endif
#if (FCLK2CH2_EN > 0)
#define FCLK2CH2_BUF_SIZE  16         // FCLK2CH2缓存长度,范围 1~64
#endif
#if (FCLK2CH3_EN > 0)
#define FCLK2CH3_BUF_SIZE  16         // FCLK2CH3缓存长度,范围 1~64
#endif
#if (FCLK2CH4_EN > 0)
#define FCLK2CH4_BUF_SIZE  16         // FCLK2CH4缓存长度,范围 1~64
#endif
#endif

// FCLK2各个通道DMA使能, 只有测频模式和测PWM占空比模式才支持DMA功能
// 注意以下FCLK各通道同时只允许一个通道DMA使能, 使用TIM8定时器
#if ((FCLK2_EN > 0)&&(FCLK2_MODE > 1)) 
#define FCLK2CH1_DMA_EN		0	         // CH1 DMA：1, 使能; 0, 关闭,  占用DMA2_CH3(DMA2_Stream2)
#define FCLK2CH1_DMA_CH     DMA2_CH3     // 选择通道: DMA2_CH3

#define FCLK2CH2_DMA_EN		0	         // CH2 DMA：1, 使能; 0, 关闭,  占用DMA2_CH4(DMA2_Stream3)或DMA2_CH3(DMA2_Stream2) 
#define FCLK2CH2_DMA_CH     DMA2_CH4     // 选择通道: DMA2_CH4或DMA2_CH3(备选, 暂时不支持)

#define FCLK2CH3_DMA_EN	    0	         // CH3 DMA：1, 使能; 0, 关闭,  占用DMA2_CH5(DMA2_Stream4)或DMA2_CH3(DMA2_Stream2) 
#define FCLK2CH3_DMA_CH     DMA2_CH5     // 选择通道: DMA2_CH5或DMA2_CH3(备选, 暂时不支持)

#define FCLK2CH4_DMA_EN	    0	         // CH3 DMA：1, 使能; 0, 关闭,  占用DMA2_CH8(DMA2_Stream7) 
#define FCLK2CH4_DMA_CH     DMA2_CH8     // 选择通道: DMA2_CH8
#endif
/************************************************************************************/
// FCLK3 脉冲输入配置(占用定时器4)
// JP16: 1脚, +VT; 2,3脚(A+,A-: FCLK3_CH1),PD12; 4,5脚(B+,B-: FCLK3_CH2), PD13; 6,7脚(Z+,Z-: FCLK3_CH3), PD14; 8脚, GND;
// 注意不能与PWM4同时使能, 而且当FCLK3使能时板子上: RK10短接, RK11断开
/************************************************************************************/
#define FCLK3_EN          	0	      	  // FCLK1使能, 1：打开使能， 0：关闭
#define FCLK3_MODE	        2		      // 模式选择: 0(FCLK_MODE_COUNT), 计数模式(1路, CH1输入有效); 
                                          //           1(FCLK_MODE_DECODE), 正交编码器计数(CH1接A，CH2接B);
                                          //           2(FCLK_MODE_FREQ), 测频模式(4路, CH1, CH2, CH3, CH4输入都有效); 
                                          //           3(FCLK_MODE_PWMRATE), 测PWM占空比模式(1路, CH1输入有效); 
#define FCLK3_TIM       	TIM4_ID       // 选择定时器, 这个设置不可更改

#define FCLK3CH1_EN		    1	          // CH1：1, 使能; 0, 关闭
#define FCLK3CH2_EN		    1		      // CH2：1, 使能; 0, 关闭
#define FCLK3CH3_EN		    1	          // CH3：1, 使能; 0, 关闭
#define FCLK3CH4_EN		    0		      // CH4：1, 使能; 0, 关闭
// FCLK3所有通道使能 
#define FCLK3CH_EN		   (FCLK3CH1_EN|(FCLK3CH2_EN<<1)|(FCLK3CH3_EN<<2)|(FCLK3CH4_EN<<3))  // FCLK3所有通道使能：BIT0:CH1;BIT1:CH2;BIT2:CH3;BIT3:CH4;

#define FCLK3_MINFREQ	    100     	  // 模式2，3中，测量最小频率设定, 单位hz
 
#define FCLK3CH1_PIN	    0             // CH1管脚输入信号触发边沿： 0, 上升沿; 1, 下降沿
#define FCLK3CH2_PIN	    0             // CH2管脚输入信号触发边沿： 0, 上升沿; 1, 下降沿
#define FCLK3CH3_PIN	    0             // CH3管脚输入信号触发边沿： 0, 上升沿; 1, 下降沿
#define FCLK3CH4_PIN	    0             // CH4管脚输入信号触发边沿： 0, 上升沿; 1, 下降沿

#define FCLK3CH1_PCS	    0             // CH1管脚输入信号预分频系数： 0, 不分频; 1, 2分频; 2, 4分频; 3, 8分频;
#define FCLK3CH2_PCS	    0             // CH2管脚输入信号预分频系数： 0, 不分频; 1, 2分频; 2, 4分频; 3, 8分频;
#define FCLK3CH3_PCS	    0             // CH3管脚输入信号预分频系数： 0, 不分频; 1, 2分频; 2, 4分频; 3, 8分频;
#define FCLK3CH4_PCS	    0             // CH4管脚输入信号预分频系数： 0, 不分频; 1, 2分频; 2, 4分频; 3, 8分频;

#if ((FCLK3_EN > 0)&&((FCLK3_MODE == 2)||(FCLK3_MODE == 3)))
#if (FCLK3CH1_EN > 0)
#define FCLK3CH1_BUF_SIZE  16         // FCLK3CH1缓存长度,范围 1~64
#endif
#if (FCLK3CH2_EN > 0)
#define FCLK3CH2_BUF_SIZE  16         // FCLK3CH2缓存长度,范围 1~64
#endif
#if (FCLK3CH3_EN > 0)
#define FCLK3CH3_BUF_SIZE  16         // FCLK3CH3缓存长度,范围 1~64
#endif
#if (FCLK3CH4_EN > 0)
#define FCLK3CH4_BUF_SIZE  16         // FCLK3CH4缓存长度,范围 1~64
#endif
#endif

// FCLK3各个通道DMA使能, 只有测频模式和测PWM占空比模式才支持DMA功能
// 注意以下FCLK各通道同时只允许一个通道DMA使能, 使用TIM4定时器
#if ((FCLK3_EN > 0)&&(FCLK3_MODE > 1)) 
#define FCLK3CH1_DMA_EN		0	         // CH1 DMA：1, 使能; 0, 关闭,  占用DMA1CH1(DMA1_Stream0)
#define FCLK3CH1_DMA_CH     DMA_CH1      // 选择通道: DMA_CH1

#define FCLK3CH2_DMA_EN		0	         // CH2 DMA：1, 使能; 0, 关闭,  占用DMA1CH4(DMA1_Stream3) 
#define FCLK3CH2_DMA_CH     DMA_CH4      // 选择通道: DMA_CH4

#define FCLK3CH3_DMA_EN	    0	         // CH3 DMA：1, 使能; 0, 关闭,  占用DMA1CH8(DMA1_Stream7) 
#define FCLK3CH3_DMA_CH     DMA_CH8      // 选择通道: DMA_CH8

// 注意:  FCLK3CH4不支持DMA功能
#endif
/************************************************************************************/
// FCLK4 脉冲输入配置(占用定时器9)
// JP18: 1脚, +VT; 2,3脚(A+,B-: FCLK4_CH1), PE5;  4脚, GND;
// 注意: 只有CH1,CH2通道可以使能, 只支持0,2,3模式
/************************************************************************************/
#define FCLK4_EN           0	      	  // FCLK使能, 1：打开使能， 0：关闭
#define FCLK4_MODE	       2		      // 模式选择: 0(FCLK_MODE_COUNT), 计数模式(1路, CH1输入有效); 
                                          //           2(FCLK_MODE_FREQ), 测频模式(2路, CH1, CH2输入都有效); 
                                          //           3(FCLK_MODE_PWMRATE), 测PWM占空比模式(1路, CH1输入有效); 
#define FCLK4_TIM       	TIM9_ID       // 选择定时器, 这个设置不可更改

#define FCLK4CH1_EN		    1	          // CH1：1, 使能; 0, 关闭
#define FCLK4CH2_EN		    0		      // CH2：1, 使能; 0, 关闭
// FCLK4所有通道使能 
#define FCLK4CH_EN		   (FCLK4CH1_EN|(FCLK4CH2_EN<<1))  // FCLK所有通道使能：BIT0:CH1;BIT1:CH2;

#define FCLK4_MINFREQ	    100     	  // 模式2，3中，测量最小频率设定, 单位hz
 
#define FCLK4CH1_PIN	    0             // CH1管脚输入信号触发边沿： 0, 上升沿; 1, 下降沿
#define FCLK4CH2_PIN	    0             // CH2管脚输入信号触发边沿： 0, 上升沿; 1, 下降沿

#define FCLK4CH1_PCS	    0             // CH1管脚输入信号预分频系数： 0, 不分频; 1, 2分频; 2, 4分频; 3, 8分频;
#define FCLK4CH2_PCS	    0             // CH2管脚输入信号预分频系数： 0, 不分频; 1, 2分频; 2, 4分频; 3, 8分频;

#if ((FCLK4_EN > 0)&&((FCLK4_MODE == 2)||(FCLK4_MODE == 3)))
#if (FCLK4CH1_EN > 0)
#define FCLK4CH1_BUF_SIZE  16         // FCLK4CH1缓存长度,范围 1~64
#endif
#if (FCLK4CH2_EN > 0)
#define FCLK4CH2_BUF_SIZE  16         // FCLK4CH2缓存长度,范围 1~64
#endif
#endif

/************************************************************************************/
//  定时器1配置 
/************************************************************************************/
#define TIM1_EN       0		  // TIM1使能, 1：打开使能， 0：关闭

#define TIM1_MODE     0		  // TIM1工作模式: 0, TIM_WKMODE_INT, 定时器工作在定时中断模式, 定时时间由参数TIM1_T,TIM1_T1-TIM1_T4设置; 
                              //               1, TIM_WKMODE_COUNT, 定时器工作在定时计数模式, 外部通过调用Timer_Ctrl函数参数CMD_TIM_ENA/CMD_TIM_DIS启动/停止定时器,
                              // 再通过参数CMD_TIM_READ读取计数值

#define TIM1CH1_EN    0		  // TIM1子定时器1使能, 1：打开使能， 0：关闭
#define TIM1CH2_EN    0		  // TIM1子定时器2使能, 1：打开使能， 0：关闭
#define TIM1CH3_EN    0		  // TIM1子定时器3使能, 1：打开使能， 0：关闭
#define TIM1CH4_EN    0		  // TIM1子定时器4使能, 1：打开使能， 0：关闭

// TIM1所有定时器(包含子定时器)使能 
#define TIM1CH_EN	   (TIM1_EN|(TIM1CH1_EN<<1)|(TIM1CH2_EN<<2)|(TIM1CH3_EN<<3)|(TIM1CH4_EN<<4))  // TIM1所有定时器(包含子定时器)：BIT0:TIM1(主定时器);BIT1:CH1;BIT2:CH2;BIT3:CH3;BIT4:CH4;

// 初始定时时间设定 (注意: 子定时器1、2、3、4定时时间必须小于主定时器定时时间)
#define TIM1_T        1000000	  // TIM1主定时器定时时间, 单位us
					  
#define TIM1_T1       1000000     // TIM1子定时器1定时时间, 单位us
#define TIM1_T2       1000000	  // TIM1子定时器2定时时间, 单位us
#define TIM1_T3       1000000	  // TIM1子定时器3定时时间, 单位us
#define TIM1_T4       500000	  // TIM1子定时器4定时时间, 单位us

#define TIM1_PSC      (SYSCLK/1000000)  // 分频系数, 当工作模式设置为TIM_WKMODE_COUNT, 请设置这个;
                                        // 默认计数单位是1us
/************************************************************************************/
//  定时器2配置 
/************************************************************************************/
#define TIM2_EN       0		  // TIM2使能, 1：打开使能， 0：关闭

#define TIM2_MODE     0		  // TIM2工作模式: 0, TIM_WKMODE_INT, 定时器工作在定时中断模式, 定时时间由参数TIM2_T,TIM2_T1-TIM2_T4设置; 
                              //               1, TIM_WKMODE_COUNT, 定时器工作在定时计数模式, 外部通过调用Timer_Ctrl函数参数CMD_TIM_ENA/CMD_TIM_DIS启动/停止定时器,
                              // 再通过参数CMD_TIM_READ读取计数值
                                  
#define TIM2CH1_EN    0		  // TIM2子定时器1使能, 1：打开使能， 0：关闭
#define TIM2CH2_EN    0		  // TIM2子定时器2使能, 1：打开使能， 0：关闭
#define TIM2CH3_EN    0		  // TIM2子定时器3使能, 1：打开使能， 0：关闭
#define TIM2CH4_EN    0		  // TIM2子定时器4使能, 1：打开使能， 0：关闭
// TIM2所有定时器(包含子定时器)使能 
#define TIM2CH_EN	   (TIM2_EN|(TIM2CH1_EN<<1)|(TIM2CH2_EN<<2)|(TIM2CH3_EN<<3)|(TIM2CH4_EN<<4))  // TIM2所有定时器(包含子定时器)：BIT0:TIM2(主定时器);BIT1:CH1;BIT2:CH2;BIT3:CH3;BIT4:CH4;

// 初始定时时间设定 (注意: 子定时器1、2、3、4定时时间必须小于主定时器定时时间)
#define TIM2_T        1000000	  // TIM2主定时器定时时间, 单位us
					  
#define TIM2_T1       1000000     // TIM2子定时器1定时时间, 单位us
#define TIM2_T2       1000000	  // TIM2子定时器2定时时间, 单位us
#define TIM2_T3       1000000	  // TIM2子定时器3定时时间, 单位us
#define TIM2_T4       500000	  // TIM2子定时器4定时时间, 单位us

#define TIM2_PSC      (SYSCLK/1000000)  // 分频系数, 当工作模式设置为TIM_WKMODE_COUNT, 请设置这个;
                                        // 默认计数单位是1us
/************************************************************************************/
//  定时器3配置 
/************************************************************************************/
#define TIM3_EN       0		  // TIM3使能, 1：打开使能， 0：关闭

#define TIM3_MODE     0		  // TIM3工作模式: 0, TIM_WKMODE_INT, 定时器工作在定时中断模式, 定时时间由参数TIM3_T,TIM3_T1-TIM3_T4设置; 
                              //               1, TIM_WKMODE_COUNT, 定时器工作在定时计数模式, 外部通过调用Timer_Ctrl函数参数CMD_TIM_ENA/CMD_TIM_DIS启动/停止定时器,
                              // 再通过参数CMD_TIM_READ读取计数值

#define TIM3CH1_EN    0		  // TIM3子定时器1使能, 1：打开使能， 0：关闭
#define TIM3CH2_EN    0		  // TIM3子定时器2使能, 1：打开使能， 0：关闭
#define TIM3CH3_EN    0		  // TIM3子定时器3使能, 1：打开使能， 0：关闭
#define TIM3CH4_EN    0		  // TIM3子定时器4使能, 1：打开使能， 0：关闭
// TIM3所有定时器(包含子定时器)使能 
#define TIM3CH_EN	  (TIM3_EN|(TIM3CH1_EN<<1)|(TIM3CH2_EN<<2)|(TIM3CH3_EN<<3)|(TIM3CH4_EN<<4))  // TIM3所有定时器(包含子定时器)：BIT0:(TIM3主定时器);BIT1:CH1;BIT2:CH2;BIT3:CH3;BIT4:CH4;


// 初始定时时间设定 (注意: 子定时器1、2、3、4定时时间必须小于主定时器定时时间)
#define TIM3_T        1000000	  // TIM3主定时器定时时间, 单位us
					  
#define TIM3_T1       1000000     // TIM3子定时器1定时时间, 单位us
#define TIM3_T2       1000000	  // TIM3子定时器2定时时间, 单位us
#define TIM3_T3       1000000	  // TIM3子定时器3定时时间, 单位us
#define TIM3_T4       500000	  // TIM3子定时器4定时时间, 单位us

#define TIM3_PSC      (SYSCLK/1000000)  // 分频系数, 当工作模式设置为TIM_WKMODE_COUNT, 请设置这个;
                                        // 默认计数单位是1us
/************************************************************************************/
//  定时器3配置 
/************************************************************************************/
#define TIM4_EN       0		  // TIM4使能, 1：打开使能， 0：关闭

#define TIM4_MODE     0		  // TIM4工作模式: 0, TIM_WKMODE_INT, 定时器工作在定时中断模式, 定时时间由参数TIM4_T,TIM4_T1-TIM4_T4设置; 
                              //               1, TIM_WKMODE_COUNT, 定时器工作在定时计数模式, 外部通过调用Timer_Ctrl函数参数CMD_TIM_ENA/CMD_TIM_DIS启动/停止定时器,
                              // 再通过参数CMD_TIM_READ读取计数值

#define TIM4CH1_EN    0		  // TIM4子定时器1使能, 1：打开使能， 0：关闭
#define TIM4CH2_EN    0		  // TIM4子定时器2使能, 1：打开使能， 0：关闭
#define TIM4CH3_EN    0		  // TIM4子定时器3使能, 1：打开使能， 0：关闭
#define TIM4CH4_EN    0		  // TIM4子定时器4使能, 1：打开使能， 0：关闭
// TIM4所有定时器(包含子定时器)使能 
#define TIM4CH_EN	  (TIM4_EN|(TIM4CH1_EN<<1)|(TIM4CH2_EN<<2)|(TIM4CH3_EN<<3)|(TIM4CH4_EN<<4))  // TIM4所有定时器(包含子定时器)：BIT0:TIM4(主定时器);BIT1:CH1;BIT2:CH2;BIT3:CH3;BIT4:CH4;

// 初始定时时间设定 (注意: 子定时器1、2、3、4定时时间必须小于主定时器定时时间)
#define TIM4_T        1000000	  // TIM4主定时器定时时间, 单位us
					  
#define TIM4_T1       1000000     // TIM4子定时器1定时时间, 单位us
#define TIM4_T2       1000000	  // TIM4子定时器2定时时间, 单位us
#define TIM4_T3       1000000	  // TIM4子定时器3定时时间, 单位us
#define TIM4_T4       500000	  // TIM4子定时器4定时时间, 单位us

#define TIM4_PSC      (SYSCLK/1000000)  // 分频系数, 当工作模式设置为TIM_WKMODE_COUNT, 请设置这个;
                                        // 默认计数单位是1us
/************************************************************************************/
//  定时器5配置 
/************************************************************************************/
#define TIM5_EN       0		  // TIM5使能, 1：打开使能， 0：关闭

#define TIM5_MODE     0		  // TIM5工作模式: 0, TIM_WKMODE_INT, 定时器工作在定时中断模式, 定时时间由参数TIM5_T,TIM5_T1-TIM5_T4设置; 
                              //               1, TIM_WKMODE_COUNT, 定时器工作在定时计数模式, 外部通过调用Timer_Ctrl函数参数CMD_TIM_ENA/CMD_TIM_DIS启动/停止定时器,
                              // 再通过参数CMD_TIM_READ读取计数值

#define TIM5CH1_EN    0		  // TIM5子定时器1使能, 1：打开使能， 0：关闭
#define TIM5CH2_EN    0		  // TIM5子定时器2使能, 1：打开使能， 0：关闭
#define TIM5CH3_EN    0		  // TIM5子定时器3使能, 1：打开使能， 0：关闭
#define TIM5CH4_EN    0		  // TIM5子定时器4使能, 1：打开使能， 0：关闭
// TIM5所有定时器(包含子定时器)使能 
#define TIM5CH_EN	  (TIM5_EN|(TIM5CH1_EN<<1)|(TIM5CH2_EN<<2)|(TIM5CH3_EN<<3)|(TIM5CH4_EN<<4))  // TIM5所有定时器(包含子定时器)：BIT0:TIM5(主定时器);BIT1:CH1;BIT2:CH2;BIT3:CH3;BIT4:CH4;


// 初始定时时间设定 (注意: 子定时器1、2、3、4定时时间必须小于主定时器定时时间)
#define TIM5_T        1000000	  // TIM5主定时器定时时间, 单位us
					  
#define TIM5_T1       1000000     // TIM5子定时器1定时时间, 单位us
#define TIM5_T2       1000000     // TIM5子定时器2定时时间, 单位us
#define TIM5_T3       1000000	  // TIM5子定时器3定时时间, 单位us
#define TIM5_T4       500000	  // TIM5子定时器4定时时间, 单位us

#define TIM5_PSC      (SYSCLK/1000000)  // 分频系数, 当工作模式设置为TIM_WKMODE_COUNT, 请设置这个;
                                        // 默认计数单位是1us
                           
/************************************************************************************/
//  定时器6配置 
/************************************************************************************/
#define TIM6_EN       0		  // TIM6使能, 1：打开使能， 0：关闭

#define TIM6_MODE     0		  // TIM6工作模式: 0, TIM_WKMODE_INT, 定时器工作在定时中断模式, 定时时间由参数TIM6_T设置; 
                              //               1, TIM_WKMODE_COUNT, 定时器工作在定时计数模式, 外部通过调用Timer_Ctrl函数参数CMD_TIM_ENA/CMD_TIM_DIS启动/停止定时器,
                              // 再通过参数CMD_TIM_READ读取计数值
// 初始定时时间设定 
#define TIM6_T        100000	  // TIM6主定时器定时时间, 单位us---定时100ms

#define TIM6_PSC      (SYSCLK/1000000)  // 分频系数, 当工作模式设置为TIM_WKMODE_COUNT, 请设置这个;
                                        // 默认计数单位是1us

/************************************************************************************/
//  定时器7配置 
/************************************************************************************/
#define TIM7_EN       0		  // TIM7使能, 1：打开使能， 0：关闭

#define TIM7_MODE     0		  // TIM7工作模式: 0, TIM_WKMODE_INT, 定时器工作在定时中断模式, 定时时间由参数TIM7_T设置; 
                              //               1, TIM_WKMODE_COUNT, 定时器工作在定时计数模式, 外部通过调用Timer_Ctrl函数参数CMD_TIM_ENA/CMD_TIM_DIS启动/停止定时器,
                              // 再通过参数CMD_TIM_READ读取计数值
// 初始定时时间设定 
#define TIM7_T        1000000	  // TIM7主定时器定时时间, 单位us

#define TIM7_PSC      (SYSCLK/1000000)  // 分频系数, 当工作模式设置为TIM_WKMODE_COUNT, 请设置这个;
                                        // 默认计数单位是1us
                              
/************************************************************************************/
//  定时器8配置 
/************************************************************************************/
#define TIM8_EN       0		  // TIM8使能, 1：打开使能， 0：关闭

#define TIM8_MODE     0		  // TIM8工作模式: 0, TIM_WKMODE_INT, 定时器工作在定时中断模式, 定时时间由参数TIM8_T,TIM8_T1~TIM8_T4设置; 
                              //               1, TIM_WKMODE_COUNT, 定时器工作在定时计数模式, 外部通过调用Timer_Ctrl函数参数CMD_TIM_ENA/CMD_TIM_DIS启动/停止定时器,
                              // 再通过参数CMD_TIM_READ读取计数值

#define TIM8CH1_EN    1		  // TIM8子定时器1使能, 1：打开使能， 0：关闭
#define TIM8CH2_EN    1		  // TIM8子定时器2使能, 1：打开使能， 0：关闭
#define TIM8CH3_EN    1		  // TIM8子定时器3使能, 1：打开使能， 0：关闭
#define TIM8CH4_EN    1		  // TIM8子定时器4使能, 1：打开使能， 0：关闭

// TIM8所有定时器(包含子定时器)使能 
#define TIM8CH_EN	   (TIM8_EN|(TIM8CH1_EN<<1)|(TIM8CH2_EN<<2)|(TIM8CH3_EN<<3)|(TIM8CH4_EN<<4))  // TIM8所有定时器(包含子定时器)：BIT0:TIM8(主定时器);BIT1:CH1;BIT2:CH2;BIT3:CH3;BIT4:CH4;

// 初始定时时间设定 (注意: 子定时器1、2、3、4定时时间必须小于主定时器定时时间)
#define TIM8_T        1000000	  // TIM8主定时器定时时间, 单位us
					  
#define TIM8_T1       1000000     // TIM8子定时器1定时时间, 单位us
#define TIM8_T2       1000000	  // TIM8子定时器2定时时间, 单位us
#define TIM8_T3       1000000	  // TIM8子定时器3定时时间, 单位us
#define TIM8_T4       1000000	  // TIM8子定时器4定时时间, 单位us

#define TIM8_PSC      (SYSCLK/1000000)  // 分频系数, 当工作模式设置为TIM_WKMODE_COUNT, 请设置这个;
                                        // 默认计数单位是1us
/************************************************************************************/
//  定时器9配置 
/************************************************************************************/
#define TIM9_EN       0		  // TIM9使能, 1：打开使能， 0：关闭

#define TIM9_MODE     0		  // TIM9工作模式: 0, TIM_WKMODE_INT, 定时器工作在定时中断模式, 定时时间由参数TIM9_T,TIM9_T1-TIM9_T2设置; 
                              //               1, TIM_WKMODE_COUNT, 定时器工作在定时计数模式, 外部通过调用Timer_Ctrl函数参数CMD_TIM_ENA/CMD_TIM_DIS启动/停止定时器,
                              // 再通过参数CMD_TIM_READ读取计数值

#define TIM9CH1_EN    1		  // TIM9子定时器1使能, 1：打开使能， 0：关闭
#define TIM9CH2_EN    0		  // TIM9子定时器2使能, 1：打开使能， 0：关闭
// TIM9所有定时器(包含子定时器)使能 
#define TIM9CH_EN	  (TIM9_EN|(TIM9CH1_EN<<1)|(TIM9CH2_EN<<2))  // TIM9所有定时器(包含子定时器)：BIT0:TIM9(主定时器);BIT1:CH1;BIT2:CH2;


// 初始定时时间设定 (注意: 子定时器1、2定时时间必须小于主定时器定时时间)
#define TIM9_T        1000000	  // TIM9主定时器定时时间, 单位us
					  
#define TIM9_T1       1000000     // TIM9子定时器1定时时间, 单位us
#define TIM9_T2       1000000     // TIM9子定时器2定时时间, 单位us

#define TIM9_PSC      (SYSCLK/1000000)  // 分频系数, 当工作模式设置为TIM_WKMODE_COUNT, 请设置这个;
                                        // 默认计数单位是1us

/************************************************************************************/
//  定时器10配置 
/************************************************************************************/
#define TIM10_EN       0		  // TIM10使能, 1：打开使能， 0：关闭

#define TIM10_MODE     0		  // TIM10工作模式: 0, TIM_WKMODE_INT, 定时器工作在定时中断模式, 定时时间由参数TIM10_T,TIM10_T1设置; 
                                  //                1, TIM_WKMODE_COUNT, 定时器工作在定时计数模式, 外部通过调用Timer_Ctrl函数参数CMD_TIM_ENA/CMD_TIM_DIS启动/停止定时器,
                                  // 再通过参数CMD_TIM_READ读取计数值

#define TIM10CH1_EN    1		  // TIM10子定时器1使能, 1：打开使能， 0：关闭
// TIM10所有定时器(包含子定时器)使能 
#define TIM10CH_EN	  (TIM10_EN|(TIM10CH1_EN<<1))  // TIM10所有定时器(包含子定时器)：BIT0:TIM10(主定时器);BIT1:CH1;


// 初始定时时间设定 (注意: 子定时器1定时时间必须小于主定时器定时时间)
#define TIM10_T        1000000	  // TIM10主定时器定时时间, 单位us
					  
#define TIM10_T1       1000000    // TIM10子定时器1定时时间, 单位us

#define TIM10_PSC      (SYSCLK/1000000)  // 分频系数, 当工作模式设置为TIM_WKMODE_COUNT, 请设置这个;
                                         // 默认计数单位是1us

/************************************************************************************/
//  定时器11配置 
/************************************************************************************/
#define TIM11_EN       0		  // TIM11使能, 1：打开使能， 0：关闭

#define TIM11_MODE     0		  // TIM11工作模式: 0, TIM_WKMODE_INT, 定时器工作在定时中断模式, 定时时间由参数TIM11_T,TIM11_T1设置; 
                                  //               1, TIM_WKMODE_COUNT, 定时器工作在定时计数模式, 外部通过调用Timer_Ctrl函数参数CMD_TIM_ENA/CMD_TIM_DIS启动/停止定时器,
                                  // 再通过参数CMD_TIM_READ读取计数值

#define TIM11CH1_EN    1		  // TIM11子定时器1使能, 1：打开使能， 0：关闭
// TIM11所有定时器(包含子定时器)使能 
#define TIM11CH_EN	  (TIM11_EN|(TIM11CH1_EN<<1))  // TIM11所有定时器(包含子定时器)：BIT0:TIM11(主定时器);BIT1:CH1;


// 初始定时时间设定 (注意: 子定时器1定时时间必须小于主定时器定时时间)
#define TIM11_T        1000000	  // TIM11主定时器定时时间, 单位us
					  
#define TIM11_T1       1000000    // TIM11子定时器1定时时间, 单位us

#define TIM11_PSC      (SYSCLK/1000000)  // 分频系数, 当工作模式设置为TIM_WKMODE_COUNT, 请设置这个;
                                         // 默认计数单位是1us

/************************************************************************************/
//  定时器12配置 
/************************************************************************************/
#define TIM12_EN       0		  // TIM12使能, 1：打开使能， 0：关闭

#define TIM12_MODE     0		  // TIM9工作模式: 0, TIM_WKMODE_INT, 定时器工作在定时中断模式, 定时时间由参数TIM12_T,TIM12_T1-TIM12_T2设置; 
                                  //               1, TIM_WKMODE_COUNT, 定时器工作在定时计数模式, 外部通过调用Timer_Ctrl函数参数CMD_TIM_ENA/CMD_TIM_DIS启动/停止定时器,
                                  // 再通过参数CMD_TIM_READ读取计数值

#define TIM12CH1_EN    0		  // TIM12子定时器1使能, 1：打开使能， 0：关闭
#define TIM12CH2_EN    0		  // TIM12子定时器2使能, 1：打开使能， 0：关闭
// TIM12所有定时器(包含子定时器)使能 
#define TIM12CH_EN	  (TIM12_EN|(TIM12CH1_EN<<1)|(TIM12CH2_EN<<2))  // TIM12所有定时器(包含子定时器)：BIT0:TIM12(主定时器);BIT1:CH1;BIT2:CH2;


// 初始定时时间设定 (注意: 子定时器1、2定时时间必须小于主定时器定时时间)
#define TIM12_T        1000000	  // TIM9主定时器定时时间, 单位us
					  
#define TIM12_T1       1000000     // TIM9子定时器1定时时间, 单位us
#define TIM12_T2       1000000     // TIM9子定时器2定时时间, 单位us

#define TIM12_PSC      (SYSCLK/1000000)  // 分频系数, 当工作模式设置为TIM_WKMODE_COUNT, 请设置这个;
                                        // 默认计数单位是1us

/************************************************************************************/
//  定时器13配置 
/************************************************************************************/
#define TIM13_EN       0		  // TIM13使能, 1：打开使能， 0：关闭

#define TIM13_MODE     0		  // TIM13工作模式: 0, TIM_WKMODE_INT, 定时器工作在定时中断模式, 定时时间由参数TIM13_T,TIM13_T1设置; 
                                  //                1, TIM_WKMODE_COUNT, 定时器工作在定时计数模式, 外部通过调用Timer_Ctrl函数参数CMD_TIM_ENA/CMD_TIM_DIS启动/停止定时器,
                                  // 再通过参数CMD_TIM_READ读取计数值

#define TIM13CH1_EN    0		  // TIM13子定时器1使能, 1：打开使能， 0：关闭
// TIM13所有定时器(包含子定时器)使能 
#define TIM13CH_EN	  (TIM13_EN|(TIM13CH1_EN<<1))  // TIM13所有定时器(包含子定时器)：BIT0:TIM13(主定时器);BIT1:CH1;


// 初始定时时间设定 (注意: 子定时器1定时时间必须小于主定时器定时时间)
#define TIM13_T        1000000	  // TIM13主定时器定时时间, 单位us
					  
#define TIM13_T1       1000000    // TIM13子定时器1定时时间, 单位us

#define TIM13_PSC      (SYSCLK/1000000)  // 分频系数, 当工作模式设置为TIM_WKMODE_COUNT, 请设置这个;
                                         // 默认计数单位是1us
                                         

/************************************************************************************/
//  定时器14配置 
/************************************************************************************/
#define TIM14_EN       1		  // TIM14使能, 1：打开使能， 0：关闭

#define TIM14_MODE     0		  // TIM14工作模式: 0, TIM_WKMODE_INT, 定时器工作在定时中断模式, 定时时间由参数TIM14_T,TIM14_T1设置; 
                                  //                1, TIM_WKMODE_COUNT, 定时器工作在定时计数模式, 外部通过调用Timer_Ctrl函数参数CMD_TIM_ENA/CMD_TIM_DIS启动/停止定时器,
                                  // 再通过参数CMD_TIM_READ读取计数值

#define TIM14CH1_EN    0		  // TIM14子定时器1使能, 1：打开使能， 0：关闭
// TIM14所有定时器(包含子定时器)使能 
#define TIM14CH_EN	  (TIM14_EN|(TIM14CH1_EN<<1))  // TIM14所有定时器(包含子定时器)：BIT0:TIM14(主定时器);BIT1:CH1;


// 初始定时时间设定 (注意: 子定时器1定时时间必须小于主定时器定时时间)
#define TIM14_T        (1000000/ADC_FREQ)	  // TIM14主定时器定时时间, 单位us
					  
#define TIM14_T1       1000000    // TIM14子定时器1定时时间, 单位us

#define TIM14_PSC      (SYSCLK/1000000)  // 分频系数, 当工作模式设置为TIM_WKMODE_COUNT, 请设置这个;
                                         // 默认计数单位是1us
                                         
/************************************************************************************/
//  CAN1, CAN2 通信配置
//  目前只支持CAN1
/************************************************************************************/
// CAN1配置
#define CAN1_EN          0		       // CAN1使能, 1：打开使能， 0：关闭

#define CAN1_MODE		 0		       // 0,正常模式; 1, 环回模式(用于调试); 2, 静默模式(用于调试); 3, 环回/静默模式(用于调试);
#define CAN1_IDE         CAN_EXT_ID    // 帧类型: 标准帧:CAN_STD_ID, 扩展帧:CAN_EXT_ID
#define CAN1_RTR         CAN_RTR_DATA  // 选择数据帧:CAN_RTR_DATA 或远程帧:CAN_RTR_REMOTE
#define CAN1_BAUD	     50000         // CAN1波特率; 

#define CAN1_RXBUF_SIZE   16            // CAN接收缓存可接收消息个数,范围 1~256
#define CAN1_TXBUF_SIZE   16            // CAN发送缓存可发送消息个数,范围 1~256

// CAN2配置
#define CAN2_EN          0		       // CAN2使能, 1：打开使能， 0：关闭

#define CAN2_MODE		 0		       // 0,正常模式; 1, 环回模式(用于调试); 2, 静默模式(用于调试); 3, 环回/静默模式(用于调试);
#define CAN2_IDE         CAN_EXT_ID    // 帧类型: 标准帧:CAN_STD_ID, 扩展帧:CAN_EXT_ID
#define CAN2_RTR         CAN_RTR_DATA  // // 选择数据帧:CAN_RTR_DATA 或远程帧:CAN_RTR_REMOTE
#define CAN2_BAUD	     50000         // CAN2波特率; 

#define CAN2_RXBUF_SIZE   16            // CAN接收缓存可接收消息个数,范围 1~256
#define CAN2_TXBUF_SIZE   16            // CAN发送缓存可发送消息个数,范围 1~256


// CAN过滤器组配置
#define CAN2_START_BANK    14            // CAN2开始组, 它们定义了CAN2(从)接口的开始组，范围是1~27
#define CAN_FILTER_FIFO    0x0FE03F80    // CAN 过滤器FIFO关联配置, 报文在通过了某过滤器的过滤后，将被存放到其关联的FIFO中。
 										 // 0：过滤器被关联到FIFO0；1：过滤器被关联到FIFO1。
#define CAN_FILTER_SCALE   0x0FFFFFFF    // CAN 过滤器位宽寄存器：Bit27~Bit0有效, bit0是第0组，bit27是第27组，
                                         // 0：过滤器位宽为2个16位; 1：过滤器位宽为单个32位。
#define CAN_FILTER_ACTIVE  0x0FFFFFFF    // 过滤器激活 (Filter active): 	 Bit27~Bit0有效, bit0是第0组，	bit27是第27组
                                         // 0：过滤器被禁用；1：过滤器被激活。
#define CAN_FILTER_MODE    0x0FFFFFFF    // CAN过滤器模式 (Filter mode)：Bit27~Bit0有效, bit0是第0组，	bit27是第27组，
                                         // 0: 过滤器组x的2个32位寄存器工作在标识符屏蔽位模式；1: 过滤器组x的2个32位寄存器工作在标识符列表模式。
// 滤波器最大数目数 
#define CAN_FILTER_MAXNUM  28            // 最大数目

// CAN1 FIFO0滤波器组默认设置
#if (CAN1_IDE == CAN_EXT_ID)
#define SHIFT_BIT   3                // 左移位数
#define CAN_STDEXT_ID    CAN_EXT_ID  // 使用扩展标识符
#else
#define SHIFT_BIT   21               // 左移位数
#define CAN_STDEXT_ID    CAN_STD_ID  // 使用标准标识符 
#endif

/************************************************************************************/
// MODBUS 主机通信配置
// 注意：ASCII模式暂时不支持
/************************************************************************************/
#define MODBUS_EN         0           // MODBUS通信使能：1, 使能;  0, 关闭;

#define MODBUS_MODE       0           // MODBUS通信模式：0, RTU;  1, ASCII码; 
#define MODBUS_CH         UART3_ID    // MODBUS通信通道：0: UART1_ID, 1: UART2_ID, 2: UART3_ID, 3: UART4_ID, 4: UART5_ID; 
#define MODBUS_ID         1           // MODBUS操作设备的通信地址ID, 默认1 

#define MODBUS_TIMEOUT    1000        // MODBUS通信超时时间, 单位ms;

/************************************************************************************/
// MODBUS 从机通信配置
// 注意：ASCII模式暂时不支持
/************************************************************************************/
#define MODBUS_SLAVE_EN        0           // MODBUS从机通信使能：1, 使能;  0, 关闭;

#define MODBUS_SLAVE_MODE      0           // MODBUS从机通信模式：0, RTU;  1, ASCII码; 
#define MODBUS_SLAVE_CH        UART4_ID    // MODBUS从机通信通道：0: UART1_ID, 1: UART2_ID, 2: UART3_ID, 3: UART4_ID, 4: UART5_ID; 
#define MODBUS_SLAVE_ID        1           // MODBUS从机通信地址码, 范围：1~255;

#define MODBUS_COILS_BASEADDR 	  10000        // 线圈寄存器基地址;
#define MODBUS_DISINPUT_BASEADDR  10000        // 离散输入量寄存器基地址;
#define MODBUS_HOLDREG_BASEADDR   10000        // 保持寄存器基地址;
#define MODBUS_INPUTREG_BASEADDR  10000        // 输入寄存器基地址;

#define MODBUS_MAX_COILS       32          // MODBUS从机最大线圈数量(读写,可用功能码:1,5,15);
#define MODBUS_MAX_DISINPUT    32          // MODBUS从机最大离散输入量(只读,可用功能码:2);
#define MODBUS_MAX_HOLDREG     16          // MODBUS从机最大保持寄存器(读写,可用功能码:3,6,16,23)数量;	 
#define MODBUS_MAX_INPUTREG    16          // MODBUS从机最大输入寄存器(只读,可用功能码:4)数量;

/************************************************************************************/
// SD卡配置
/************************************************************************************/
#define SDCARD_EN              0          // SD卡使能：1, 使能;  0, 关闭;

/************************************************************************************/
// SPI FLASH(W25QXX系列)配置
/************************************************************************************/
#define SPIFLASH_EN            1        // SPI FLASH使能：1, 使能;  0, 关闭;

#define SPIFLASH_MODE          0        // SPI FLASH操作方式：1, 利用FATFS文件系统进行读写;  0, 用SPI FLASH读写函数进行操作;
                                        // 注意:2种操作方式只能选择一种    

#define SPIFLASH_TYPE          W25QXX   // SPI FLASH类型定义: 必须是W25QXX


#if (SPIFLASH_TYPE == W25QXX)
// 注意: 因为W25QXX是按扇区擦除, 所以建立文件系统就按扇区计算
#define W25QXX_MODEL           W25Q64   // SPI FLASH型号：W25Q80~W25Q128

#define W25QXX_SECTOR_SIZE	   4096      // W25QXX扇区大小 	

#define W25QXX_SECTOR_NUM	   2048      // SPI FLASH总扇区数
#define W25QXX_FATFS_SECTORNUM (2048-60) // 用于建立文件系统的扇区数(范围：0~W25QXX_SECTOR_NUM-1) 	

#define W25QXX_ZDY_STARTSECTOR W25QXX_FATFS_SECTORNUM                        // 用于自定义扇区起始扇区 
#define W25QXX_ZDY_SECTORNUM   (W25QXX_SECTOR_NUM - W25QXX_FATFS_SECTORNUM)	 // 用于自定义扇区数(范围：W25QXX_ZDY_STARTSECTOR ~ W25QXX_SECTOR_NUM-1) 	

#define W25QXX_PAGE_SIZE	   256      // W25QXX读写页大小 	
#define W25QXX_PAGE_PER_SECTOR (W25QXX_SECTOR_SIZE/W25QXX_PAGE_SIZE)//每个扇区多少页--16页
#endif

/************************************************************************************/
// FatFS文件系统配置
/************************************************************************************/
#define FATFS_EN               (SDCARD_EN|(SPIFLASH_EN&SPIFLASH_MODE)|UDISK_EN) // 文件系统使能：1, 使能;  0, 关闭;

/************************************************************************************/
// TCPIP(LWIP)协议栈配置
/************************************************************************************/
#define LWIP_EN               TASK_LWIP_EN        // TCPIP(LWIP)协议栈使能：1, 使能;  0, 关闭;

#define LWIP_WKMODE			  LWIP_SOCKET_CLIENT  //LWIP_HTTP// 工作模式, 选择LWIP_SOCKET_CLIENT、LWIP_SOCKET_SERVER、LWIP_HTTP 
#define LWIP_NETYPE			  LWIP_NETYPE_TCP     // 通信类型, 选择LWIP_NETYPE_UDP、LWIP_NETYPE_TCP 

#define MODBUS_TCP_EN         0                   // Modbus TCP使能: 1, 执行Modbus TCP测试使能; 0, 执行服务器模式网络测试
                                                  // 注意使能MODBUS_TCP_EN, 请使能MODBUS_SLAVE_EN并且将LWIP_WKMODE模式设置为LWIP_SOCKET_SERVER;
                                                  
#define LWIP_CONFIG_EN        1                   // 配置选择: 1, 按配置设置网络; 0, 按EEPROM存储信息配置网络
#define LOCAL_IP              "192.168.2.135"	      // 本地IP
#define LOCAL_PORT      	  5000		   	      // 本地端口号
#define LOCAL_SUBNET_MASK     "255.255.255.0"     // 本地子网掩码
#define LOCAL_GATEWAY         "192.168.2.1"       // 本地网关

#define DSC_IP                "192.168.2.91"	      // 远端服务器IP
#define DSC_PORT              8899			      // 远端服务器端口号

#define ETH_RXBUFNB           3
#define ETH_TXBUFNB           3
#define ETH_MAX_RX_PACKET_SIZE	  1520
#define ETH_MAX_TX_PACKET_SIZE	  1520


/************************************************************************************/
// DMA1/DMA2系统配置
/************************************************************************************/
// DMA1_CH1
#if ((UART5RX_DMA_EN > 0)||(PWM3_DMA_EN > 0)||(FCLK3CH1_DMA_EN > 0)||((SPI3RX_DMA_EN > 0)&&(SPI3RX_DMA_CH == DMA1_CH1)))
#define DMA1CH1_EN         1        // DMA1CH1使能：1, 使能;  0, 关闭;
#if (UART5RX_DMA_EN > 0)
#define DMA1CH1_PARA       DMA1CH1_UART5RX_FLAG // DMA1CH1参数
#endif
#if (PWM3_DMA_EN > 0)
#define DMA1CH1_PARA       DMA1CH1_TIM5UP_FLAG  // DMA1CH1参数
#endif
#if (FCLK3CH1_DMA_EN > 0)
#define DMA1CH1_PARA       DMA1CH1_TIM4CH1_FLAG // DMA1CH1参数
#endif
#if ((SPI3RX_DMA_EN > 0)&&(SPI3RX_DMA_CH == DMA1_CH1))
#define DMA1CH1_PARA       DMA1CH1_SPI3RX_FLAG  // DMA1CH1参数
#endif
#endif

// DMA1_CH2
#if ((UART3RX_DMA_EN > 0)||(PWM1_DMA_EN > 0))
#define DMA1CH2_EN         1        // DMA1CH2使能：1, 使能;  0, 关闭;
#if (UART3RX_DMA_EN > 0)
#define DMA1CH2_PARA       DMA1CH2_UART3RX_FLAG // DMA1CH2参数
#endif
#if (PWM1_DMA_EN > 0)
#define DMA1CH2_PARA       DMA1CH2_TIM2UP_FLAG  // DMA1CH2参数
#endif
#endif

// DMA1_CH3
#if ((UART4RX_DMA_EN > 0)||(PWM2_DMA_EN > 0)||((SPI3RX_DMA_EN > 0)&&(SPI3RX_DMA_CH == DMA1_CH3)))
#define DMA1CH3_EN         1        // DMA1CH3使能：1, 使能;  0, 关闭;
#if (UART4RX_DMA_EN > 0)
#define DMA1CH3_PARA       DMA1CH3_UART4RX_FLAG // DMA1CH3参数
#endif
#if (PWM2_DMA_EN > 0)
#define DMA1CH3_PARA       DMA1CH3_TIM3UP_FLAG  // DMA1CH3参数
#endif
#if ((SPI3RX_DMA_EN > 0)&&(SPI3RX_DMA_CH == DMA1_CH3))
#define DMA1CH3_PARA       DMA1CH3_SPI3RX_FLAG  // DMA1CH3参数
#endif
#endif

// DMA1_CH4
#if (((UART3TX_DMA_EN > 0)&&(UART3TX_DMA_CH == DMA1_CH4))||(FCLK3CH2_DMA_EN > 0))
#define DMA1CH4_EN         1        // DMA1CH4使能：1, 使能;  0, 关闭;
#if ((UART3TX_DMA_EN > 0)&&(UART3TX_DMA_CH == DMA1_CH4))
#define DMA1CH4_PARA       DMA1CH4_UART3TX_FLAG     // DMA1CH4参数
#endif
#if (FCLK3CH2_DMA_EN > 0)
#define DMA1CH4_PARA       DMA1CH4_TIM4CH2_FLAG     // DMA1CH4参数
#endif
#endif

// DMA1_CH5
#if (UART4TX_DMA_EN > 0)
#define DMA1CH5_EN         1        // DMA1CH5使能：1, 使能;  0, 关闭;
#if (UART4TX_DMA_EN > 0)
#define DMA1CH5_PARA       DMA1CH5_UART4TX_FLAG // DMA1CH5参数
#endif
#endif

// DMA1_CH6
#if ((UART2RX_DMA_EN > 0)||(DAC1_DMA_EN > 0))
#define DMA1CH6_EN         1        // DMA1CH6使能：1, 使能;  0, 关闭;
#if (UART2RX_DMA_EN > 0)
#define DMA1CH6_PARA       DMA1CH6_UART2RX_FLAG // DMA1CH6参数
#endif
#if (DAC1_DMA_EN > 0)
#define DMA1CH6_PARA       DMA1CH6_DAC1_FLAG    // DMA1CH6参数
#endif
#endif

// DMA1_CH7
#if ((UART2TX_DMA_EN > 0)||(DAC2_DMA_EN > 0)||(PWM4_DMA_EN > 0))
#define DMA1CH7_EN         1        // DMA1CH7使能：1, 使能;  0, 关闭;
#if (UART2TX_DMA_EN > 0)
#define DMA1CH7_PARA       DMA1CH7_UART2TX_FLAG // DMA1CH7参数
#endif
#if (DAC2_DMA_EN > 0)
#define DMA1CH7_PARA       DMA1CH7_DAC2_FLAG    // DMA1CH7参数
#endif
#if (PWM4_DMA_EN > 0)
#define DMA1CH7_PARA       DMA1CH7_TIM4UP_FLAG  // DMA1CH7参数
#endif
#endif

// DMA1_CH8
#if ((UART5TX_DMA_EN > 0)||(FCLK3CH3_DMA_EN > 0))
#define DMA1CH8_EN         1        // DMA1CH7使能：1, 使能;  0, 关闭;
#if (UART5TX_DMA_EN > 0)
#define DMA1CH8_PARA       DMA1CH8_UART5TX_FLAG // DMA1CH8参数
#endif
#if (FCLK3CH3_DMA_EN > 0)
#define DMA1CH8_PARA       DMA1CH8_TIM4CH3_FLAG // DMA1CH8参数
#endif
#endif


// DMA2_CH1
#if (((ADC_DMA_EN > 0)&&(ADC_DMA_CH == DMA2_CH1))||((SPI1RX_DMA_EN > 0)&&(SPI1RX_DMA_CH == DMA2_CH1)))
#define DMA2CH1_EN         1        // DMA2CH1使能：1, 使能;  0, 关闭;
#if ((ADC_DMA_EN > 0)&&(ADC_DMA_CH == DMA2_CH1))
#define DMA2CH1_PARA       DMA2CH1_ADC1_FLAG   // DMA2CH1参数
#endif
#if ((SPI1RX_DMA_EN > 0)&&(SPI1RX_DMA_CH == DMA2_CH1))
#define DMA2CH1_PARA       DMA2CH1_SPI1RX_FLAG // DMA2CH1参数
#endif
#endif

// DMA2_CH2
#if (((UART6RX_DMA_EN > 0)&&(UART6RX_DMA_CH == DMA2_CH2))||((FCLK1CH1_DMA_EN > 0)&&(FCLK1CH1_DMA_CH == DMA2_CH2)))
#define DMA2CH2_EN         1        // DMA2CH2使能：1, 使能;  0, 关闭;
#if ((UART6RX_DMA_EN > 0)&&(UART6RX_DMA_CH == DMA2_CH2))
#define DMA2CH2_PARA       DMA2CH2_UART6RX_FLAG      // DMA2CH2参数
#endif
#if ((FCLK1CH1_DMA_EN > 0)&&(FCLK1CH1_DMA_CH == DMA2_CH2))
#define DMA2CH2_PARA       DMA2CH2_TIM1CH1_FLAG     // DMA2CH2参数
#endif
#endif

// DMA2_CH3
#if (((UART1RX_DMA_EN > 0)&&(UART1RX_DMA_CH == DMA2_CH3))||((UART6RX_DMA_EN > 0)&&(UART6RX_DMA_CH == DMA2_CH3))       \
    ||((FCLK1CH2_DMA_EN > 0)&&(FCLK1CH2_DMA_CH == DMA2_CH3))||((FCLK2CH1_DMA_EN > 0)&&(FCLK2CH1_DMA_CH == DMA2_CH3))  \
    ||((SPI1RX_DMA_EN > 0)&&(SPI1RX_DMA_CH == DMA2_CH3)))
#define DMA2CH3_EN         1        // DMA2CH3使能：1, 使能;  0, 关闭;
#if ((UART1RX_DMA_EN > 0)&&(UART1RX_DMA_CH == DMA2_CH3))
#define DMA2CH3_PARA       DMA2CH3_UART1RX_FLAG // DMA2CH3参数
#endif
#if ((UART6RX_DMA_EN > 0)&&(UART6RX_DMA_CH == DMA2_CH3))
#define DMA2CH3_PARA       DMA2CH3_UART1RX_FLAG // DMA2CH3参数
#endif
#if ((FCLK1CH2_DMA_EN > 0)&&(FCLK1CH2_DMA_CH == DMA2_CH3))
#define DMA2CH3_PARA       DMA2CH3_TIM1CH2_FLAG // DMA2CH3参数
#endif
#if ((FCLK2CH1_DMA_EN > 0)&&(FCLK2CH1_DMA_CH == DMA2_CH3))
#define DMA2CH3_PARA       DMA2CH3_TIM8CH3_FLAG // DMA2CH3参数
#endif
#if ((SPI1RX_DMA_EN > 0)&&(SPI1RX_DMA_CH == DMA2_CH3))
#define DMA2CH3_PARA       DMA2CH3_SPI1RX_FLAG // DMA2CH3参数
#endif
#endif

// DMA2_CH4
#if (((FCLK2CH2_DMA_EN > 0)&&(FCLK2CH2_DMA_CH == DMA2_CH4))||((SPI1TX_DMA_EN > 0)&&(SPI1TX_DMA_CH == DMA2_CH4)))
#define DMA2CH4_EN         1        // DMA2CH4使能：1, 使能;  0, 关闭;
#if ((FCLK2CH2_DMA_EN > 0)&&(FCLK2CH2_DMA_CH == DMA2_CH4))
#define DMA2CH4_PARA       DMA2CH4_TIM8CH2_FLAG // DMA2CH4参数
#endif
#if ((SPI1TX_DMA_EN > 0)&&(SPI1TX_DMA_CH == DMA2_CH4))
#define DMA2CH4_PARA       DMA2CH4_SPI1TX_FLAG // DMA2CH4参数
#endif
#endif

// DMA2_CH5
#if ((FCLK2CH3_DMA_EN > 0)&&(FCLK2CH2_DMA_CH == DMA2_CH4))
#define DMA2CH5_EN         1        // DMA2CH5使能：1, 使能;  0, 关闭;
#if ((FCLK2CH3_DMA_EN > 0)&&(FCLK2CH2_DMA_CH == DMA2_CH4))
#define DMA2CH5_PARA       DMA2CH5_TIM8CH3_FLAG  // DMA2CH5参数
#endif
#endif

// DMA2_CH6
#if (((UART1RX_DMA_EN > 0)&&(UART1RX_DMA_CH == DMA2_CH6))||((SPI1TX_DMA_EN > 0)&&(SPI1TX_DMA_CH == DMA2_CH6)))
#define DMA2CH6_EN         1        // DMA2CH6使能：1, 使能;  0, 关闭;
#if ((UART1RX_DMA_EN > 0)&&(UART1RX_DMA_CH == DMA2_CH6))
#define DMA2CH6_PARA       DMA2CH6_UART1RX_FLAG  // DMA2CH6参数
#endif
#if ((SPI1TX_DMA_EN > 0)&&(SPI1TX_DMA_CH == DMA2_CH6))
#define DMA2CH6_PARA       DMA2CH6_SPI1TX_FLAG // DMA2CH6参数
#endif
#endif

// DMA2_CH7
#if (((UART6TX_DMA_EN > 0)&&(UART6TX_DMA_CH == DMA2_CH7))||((FCLK1CH3_DMA_EN > 0)&&(FCLK1CH3_DMA_CH == DMA2_CH7)))
#define DMA2CH7_EN         1        // DMA2CH7使能：1, 使能;  0, 关闭;
#if ((UART6TX_DMA_EN > 0)&&(UART6TX_DMA_CH == DMA2_CH7))
#define DMA2CH7_PARA       DMA2CH7_UART6TX_FLAG      // DMA2CH7参数
#endif
#if ((FCLK1CH3_DMA_EN > 0)&&(FCLK1CH3_DMA_CH == DMA2_CH7))
#define DMA2CH7_PARA       DMA2CH7_TIM1CH3_FLAG      // DMA2CH7参数
#endif
#endif

// DMA2_CH8
#if ((UART1TX_DMA_EN > 0)||(FCLK2CH4_DMA_EN > 0)||((UART6TX_DMA_EN > 0)&&(UART6TX_DMA_CH == DMA2_CH8)))
#define DMA2CH8_EN         1        // DMA2CH7使能：1, 使能;  0, 关闭;
#if (UART1TX_DMA_EN > 0)
#define DMA2CH8_PARA       DMA2CH8_UART1TX_FLAG      // DMA2CH8参数
#endif
#if (FCLK2CH4_DMA_EN > 0)
#define DMA2CH8_PARA       DMA2CH8_TIM8CH4_FLAG      // DMA2CH8参数
#endif
#if ((UART6TX_DMA_EN > 0)&&(UART6TX_DMA_CH == DMA2_CH8))
#define DMA2CH8_PARA       MA2CH8_UART6TX_FLAG       // DMA2CH8参数
#endif
#endif

#define DMA1_EN            (DMA1CH1_EN|DMA1CH2_EN|DMA1CH3_EN|DMA1CH4_EN|DMA1CH5_EN|DMA1CH6_EN|DMA1CH7_EN|DMA1CH8_EN)   // DMA1使能：1, 使能;  0, 关闭;
#define DMA2_EN            (DMA2CH1_EN|DMA2CH2_EN|DMA2CH3_EN|DMA2CH4_EN|DMA2CH5_EN|DMA2CH6_EN|DMA2CH7_EN|DMA2CH8_EN)   // DMA2使能：1, 使能;  0, 关闭;
/************************************************************************************/
// 配置出错定义
/************************************************************************************/
#if (EEPROM_EN == 0)
  #error "ERROR: EEPROM_EN必需使能"
#endif

#if ((DAC1_EN>0)&&(DAC1_MODE>0)&&(TIM6_EN>0))
  #error "ERROR: DAC1(非手动输出模式)和TIM6不能同时使能"
#endif
#if ((DAC2_EN>0)&&(DAC2_MODE>0)&&(TIM7_EN>0))
  #error "ERROR: DAC2(非手动输出模式)和TIM7不能同时使能"
#endif

#if ((PWM1_EN + TIM2_EN)>1)
	#error "ERROR: PWM1_EN和TIM2_EN任何两个不能同时使能"
#endif

#if ((PWM2_EN + TIM3_EN)>1)
	#error "ERROR: PWM2_EN和TIM3_EN任何两个不能同时使能"
#endif

#if ((PWM3_EN + TIM5_EN)>1)
	#error "ERROR: PWM3_EN和TIM5_EN任何两个不能同时使能"
#endif

#if ((FCLK1_EN + TIM1_EN)>1)
	#error "ERROR: FCLK1_EN和TIM1_EN任何两个不能同时使能"
#endif

#if ((FCLK2_EN + TIM8_EN)>1)
	#error "ERROR: FCLK2_EN和TIM8_EN任何两个不能同时使能"
#endif

#if ((FCLK3_EN + PWM4_EN + TIM4_EN)>1)
	#error "ERROR: FCLK3_EN、PWM4_EN和TIM4_EN任何两个不能同时使能"
#endif

#if ((FCLK4_EN + TIM9_EN)>1)
	#error "ERROR: FCLK4_EN和TIM9_EN任何两个不能同时使能"
#endif


#if (((FCLK1_EN>0)&&(FCLK1CH1_EN == 0))&&((FCLK1_MODE == 0)||(FCLK1_MODE == 3)))
  #error "ERROR: 在计数模式和测PWM占空比模式下FCLK1CH1_EN必须使能"
#endif

#if ((FCLK1_EN>0)&&((FCLK1CH1_EN == 0)||(FCLK1CH2_EN == 0))&&(FCLK1_MODE == 1))
  #error "ERROR: 在正交编码器计数模式下FCLK1CH1_EN, FCLK1CH2_EN必须使能"
#endif


#if (((FCLK2_EN>0)&&(FCLK2CH1_EN == 0))&&((FCLK2_MODE == 0)||(FCLK2_MODE == 3)))
  #error "ERROR: 在计数模式和测PWM占空比模式下FCLK2CH1_EN必须使能"
#endif

#if ((FCLK2_EN>0)&&((FCLK2CH1_EN == 0)||(FCLK2CH2_EN == 0))&&(FCLK2_MODE == 1))
  #error "ERROR: 正交编码器计数模式下FCLK2CH1_EN, FCLK2CH2_EN必须使能"
#endif

#if (((FCLK3_EN>0)&&(FCLK3CH1_EN == 0))&&((FCLK3_MODE == 0)||(FCLK3_MODE == 3)))
  #error "ERROR: 在计数模式和测PWM占空比模式下FCLK3CH1_EN必须使能"
#endif

#if ((FCLK3_EN>0)&&((FCLK3CH1_EN == 0)||(FCLK3CH2_EN == 0))&&(FCLK3_MODE == 1))
  #error "ERROR: 正交编码器计数模式下FCLK3CH1_EN, FCLK3CH2_EN必须使能"
#endif

#if (((FCLK4_EN>0)&&(FCLK4CH1_EN == 0))&&((FCLK4_MODE == 0)||(FCLK4_MODE == 3)))
	#error "ERROR: 在计数模式和测PWM占空比模式下FCLK4CH1_EN必须使能"
#endif

#if (CAN2_EN>0)
  #error "ERROR: 不支持CAN2, CAN2_EN不能使能"
#endif

#if ((MODBUS_EN>0)&&(MODBUS_MODE!=0))
  #error "ERROR: MODBUS主机通信模式暂不支持ASCII码"
#endif

#if ((MODBUS_SLAVE_EN>0)&&(MODBUS_SLAVE_MODE==1))
  #error "ERROR: MODBUS从机通信模式暂不支持ASCII码"
#endif


// DMA占用冲突
#if ((UART5RX_DMA_EN + PWM3_DMA_EN + FCLK3CH1_DMA_EN + SPI3RX_DMA_EN*(SPI3RX_DMA_CH == DMA1_CH1)) > 1)
  #error "ERROR: UART5RX,PWM3,SPI3RX和FCLK3CH1占用同一个DMA1CH1"
#endif

#if ((UART3RX_DMA_EN + PWM1_DMA_EN) > 1)
  #error "ERROR: UART3RX和PWM1占用同一个DMA1CH2"
#endif

#if ((UART4RX_DMA_EN + PWM2_DMA_EN + SPI3RX_DMA_EN*(SPI3RX_DMA_CH == DMA1_CH3)) > 1)
	#error "ERROR: UART4RX和PWM2占用同一个DMA1CH3"
#endif
 
#if ((UART3TX_DMA_EN*(UART3TX_DMA_CH == DMA1_CH4) + FCLK3CH2_DMA_EN) > 1)
	#error "ERROR: UART3TX和FCLK3CH2占用同一个DMA1CH4"
#endif

#if ((UART2RX_DMA_EN + DAC1_DMA_EN) > 1)
	#error "ERROR: UART2RX和DAC1占用同一个DMA1CH6"
#endif

#if ((UART2TX_DMA_EN + DAC2_DMA_EN + PWM4_DMA_EN) > 1)
	#error "ERROR: UART2TX,DAC2和PWM4占用同一个DMA1CH7"
#endif
 
#if ((UART5TX_DMA_EN + FCLK3CH3_DMA_EN) > 1)
	#error "ERROR: UART5TX和FCLK3CH3占用同一个DMA1CH8"
#endif

#if ((ADC_DMA_EN*(ADC_DMA_CH == DMA2_CH1) + SPI1RX_DMA_EN*(SPI1RX_DMA_CH == DMA2_CH1)) > 1)
	#error "ERROR: ADC和SPI1RX占用同一个DMA2CH1"
#endif

#if ((UART6RX_DMA_EN*(UART6RX_DMA_CH == DMA2_CH2) + FCLK1CH1_DMA_EN*(FCLK1CH1_DMA_CH == DMA2_CH2)) > 1)
	#error "ERROR: UART6RX和FCLK1CH1占用同一个DMA2CH2"
#endif

#if ((UART1RX_DMA_EN*(UART1RX_DMA_CH == DMA2_CH3) + UART6RX_DMA_EN*(UART6RX_DMA_CH == DMA2_CH3) + FCLK1CH2_DMA_EN*      \
    (FCLK1CH2_DMA_CH == DMA2_CH3) + FCLK2CH1_DMA_EN*(FCLK2CH1_DMA_CH == DMA2_CH3) + SPI1RX_DMA_EN*(SPI1RX_DMA_CH == DMA2_CH3)) > 1)
	#error "ERROR: UART1RX,UART6RX,SPI1RX,FCLK1CH2和FCLK2CH1占用同一个DMA2CH3"
#endif

#if ((FCLK2CH2_DMA_EN*(FCLK2CH2_DMA_CH == DMA2_CH4) + SPI1TX_DMA_EN*(SPI1TX_DMA_CH == DMA2_CH4)) > 1)
	#error "ERROR: FCLK2CH2和SPI1TX_占用同一个DMA2CH4"
#endif

#if ((UART1RX_DMA_EN*(UART1RX_DMA_CH == DMA2_CH6) + SPI1TX_DMA_EN*(SPI1TX_DMA_CH == DMA2_CH6)) > 1)
	#error "ERROR: UART1RX和SPI1TX_占用同一个DMA2CH6"
#endif

#if ((UART6TX_DMA_EN*(UART6TX_DMA_CH == DMA2_CH7) + FCLK1CH3_DMA_EN*(FCLK1CH3_DMA_CH == DMA2_CH7)) > 1)
	#error "ERROR: UART6TX和FCLK1CH3占用同一个DMA2CH7"
#endif

#if ((UART1TX_DMA_EN + FCLK2CH4_DMA_EN + UART6TX_DMA_EN*(UART6TX_DMA_CH == DMA2_CH8)) > 1)
   #error "ERROR: UART1TX,UART6TX和FCLK2CH4占用同一个DMA2CH8"
#endif


#if ((FCLK1CH1_DMA_EN + FCLK1CH2_DMA_EN + FCLK1CH3_DMA_EN + FCLK1CH4_DMA_EN) > 1)
	#error "ERROR: FCLK1各通道同时只允许一个通道DMA使能"
#endif

#if ((FCLK2CH1_DMA_EN + FCLK2CH2_DMA_EN + FCLK2CH3_DMA_EN + FCLK2CH4_DMA_EN) > 1)
	#error "ERROR: FCLK2各通道同时只允许一个通道DMA使能"
#endif

#if ((FCLK3CH1_DMA_EN + FCLK3CH2_DMA_EN + FCLK3CH3_DMA_EN + FCLK3CH4_DMA_EN) > 1)
	#error "ERROR: FCLK3各通道同时只允许一个通道DMA使能"
#endif

#endif
/***********************************************************************************/
// 文件结束
/***********************************************************************************/
