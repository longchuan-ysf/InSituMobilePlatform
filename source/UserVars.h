/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: UserVars.h
* Project  : STM32F1XX/4XX系列模块软件
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.00
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: 本文件负责用户应用程序公共全局变量引用头文件, 客户可以把应用的全局变量设置到这里;
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
#ifndef __USER_VARS_H 
#define __USER_VARS_H 

/************************************************************************************/
// 引用外部头文件
/************************************************************************************/
#include "const.h"	
#include "config.h"	
#include "timer.h"	
	
/************************************************************************************
*
*       系统状态标志定义
*
*************************************************************************************/
#define SYNC_HEAD         0x5AA5    // 配置参数同步头定义
#define CONFIG_PARA_ADDR  0         // 配置参数存储EEPROM地址

// 配置参数Flag定义
#define SPIFLASH_FORMAT_FLAG  0x0001 // SPI FLASH格式化标志
#define NFLASH_FORMAT_FLAG    0x0002 // NAND FLASH格式化标志

#define AT_DEBUG_FLAG         0x0004 // AT指令调试输出使能标志

#define AT_MODE_TIM           0      // 定时采集输出或输入模式
#define AT_MODE_START         10     // 立即采集输出或输入模式
typedef struct
{
    INT8U   Mode;     // 工作模式
    INT16U  t1;       // 定时扫描时间    
    INT16U  t2;       // 测试发送时间
}AT_PARA;

typedef struct
{
    INT8U   Mode;     // 工作模式
    INT16U  val;      // AO间隔输出增加值    
    INT16U  t;        // 测试发送时间
}AT_AO_PARA;

typedef struct
{
    INT32U  Baud;     // UART波特率
    INT8U   bits;     // 数据位数
    INT8U   PS;       // 校验位    
    INT8U   Stop;     // 停止位 
}AT_UART_PARA;

typedef struct
{
    INT32U  Baud;        // UART波特率
    INT8U   IDE;         // 帧类型: 0, 标准帧; 1, 扩展帧;
    INT16U  Filter[14];  // 滤波寄存器, 暂时设置16位    
}AT_CAN_PARA;


#define AT_DI_FLAG      0x0001   // DI AT输出标志
#define AT_DO_FLAG      0x0002   // DO AT输出标志
#define AT_AI_FLAG      0x0004   // AI AT输出标志
#define AT_AO_FLAG      0x0008   // AO AT输出标志
#define AT_PWM_FLAG     0x0010   // PWM AT输出标志
#define AT_FCLK_FLAG    0x0020   // FCLK AT输出标志

#define AT_UART_FLAG    0x0040   // UART AT输出标志
#define AT_CAN_FLAG     0x0080   // CAN AT输出标志
#define AT_RTC_FLAG     0x0100   // RTC AT输出标志
#define AT_NET_FLAG     0x0200   // NET AT输出标志
#define AT_TIM_FLAG     0x0400   // TIMER AT输出标志
#define AT_USB_FLAG     0x0800   // USB AT输出标志
#define AT_FILE_FLAG    0x1000   // FILE AT输出标志

#define AT_INFO_FLAG    0x8000   // 其它 AT输出标志

#define AT_ALL_FLAG     0x9FFF   // 所有AT输出标志


#pragma pack (1)
typedef struct
{
    INT16U	Sync;	        // 报文头：5AA5
	INT16U 	Flag;   	    // 标志
	INT8U 	ModbusID; 	    // Modbus ID
    INT8U   NetType;        // 网络类型
    INT8U   NetMode;        // 网络工作模式
    INT8U   LocalIP[4];     // 本机IP
    INT16U  LocalPort;      // 本机端口
    INT8U   SubnetMask[4];  // 本地子网掩码
    INT8U   Gataway[4];     // 本地网关
    INT8U   DscIP[4];       // 服务器IP
    INT16U  DscPort;        // 服务器端口         
    INT8U   MACAddr[6];	    // 本机MAC地址
    
    INT32U  ATFlag;       // AT指令输出使能标志
    AT_PARA DI;           // DI参数
    AT_PARA DO;           // DO参数
    AT_PARA AI;           // AI参数
    AT_AO_PARA AO;        // AO参数
    AT_PARA PWM[PWM_NUM];       // PWM参数
    AT_PARA FCLK[FCLK_NUM];     // FCLK参数
    AT_UART_PARA Uart[6]; // Uart参数
    AT_CAN_PARA  CAN[2];  // CAN参数
    INT16U	rev[4];         	//2  保留	
	INT16U	CRC16;         	//2  校验位			  
}CONFIG_PARA;
#pragma pack()

#define CONFIG_PARA_LEN	 sizeof(CONFIG_PARA)

#define TASK_ADCDAC_FLAG      0x00000004 
#define TASK_MODBUS_FLAG      0x00000008 	 
#define TASK_FILE_FLAG		  0x00000010
#define TASK_IO_FLAG		  0x00000040
#define TASK_UARTCAN_FLAG	  0x00000080
#define TASK_PWMFCLK_FLAG	  0x00000100
#define TASK_LWIP_FLAG		  0x00000200
#define TASK_DTU_FLAG		  0x00000400 

#define TASK_FLAG   (TASK_ADCDAC_FLAG*TASK_ADCDAC_EN + TASK_MODBUS_FLAG*TASK_MODBUS_EN + \
					TASK_FILE_FLAG*TASK_FILE_EN + \
					TASK_IO_FLAG*TASK_IO_EN + TASK_UARTCAN_FLAG*TASK_UARTCAN_EN + \
					TASK_PWMFCLK_FLAG*TASK_PWMFCLK_EN + TASK_LWIP_FLAG*TASK_LWIP_EN + \
					TASK_DTU_FLAG*TASK_DTU_EN)

// 和驱动库及系统相关全局变量定义, 用户不要修改这个
#define  USBD_CONNECT_FLAG      0x01000000  // USB设备连接状态标志
#define  USBH_CONNECT_FLAG      0x02000000  // USB主机连接状态标志
#define  SD_USB_FLAG            0x04000000  // SD卡被计算机USB(USB Mass Storage)占用标志
#define  SPIFLASH_USB_FLAG      0x08000000  // SPI Flash被计算机USB(USB Mass Storage)占用标志
#define  NFLASH_USB_FLAG        0x10000000  // Nand Flash被计算机USB(USB Mass Storage)占用标志
#define  SD_FATFS_FLAG          0x20000000  // SD卡被FatFS占用标志
#define  SPIFLASH_FATFS_FLAG    0x40000000  // SPI Flash被FatFS占用标志
#define  NFLASH_FATFS_FLAG      0x80000000  // Nand Flash被FatFS占用标志
typedef struct
{
    INT32U Flag;        // 标志
    INT32U APIWaitFlag; // 驱动库等待事件标志
}LIBSYS_VARS;

// ADC变量定义
#define ADC_READ_FLAG      0x0001 // ADC读取数据标志
#define ADC_MAX_BUF_SIZE   10     // ADC数据buf大小
typedef struct
{
    INT16U   Flag;      // ADC工作标志
	INT16U   len;       // ADC采样值数量
	INT16U   buf[ADC_MAX_BUF_SIZE];  // ADC采样值
}ADC_VARS;

typedef struct
{
    INT8U    Mode;      // FCLK工作模式
	INT16U   Rate;      // 占空比
	INT32U   Freq[4];   // 测量频率
	INT32S   cnt;       // FCLK计数值
    
    INT32S   QEICount;  // 
}FCLK_VARS;

typedef struct
{
    INT8U    ArgcNum;     // 0函数不带参 1带一个参数 2 代两个参数 3 带三个参数 4带四个参数
	//函数参数默认INT32U类型，如果是其他类型可以强制类型转换
	INT32U   FuncArgc1;   // 函数参数1
	INT32U   FuncArgc2;   // 函数参数2
	INT32U   FuncArgc3;   // 函数参数3
	INT32U   FuncArgc4;   // 函数参数4
	//这里的函数默认返回INT32U类型，如果是其他类型可以强制类型转换
	INT32U (*FuncZeroArgc)(void);
	INT32U (*FuncOneArgc)(INT32U);
	INT32U (*FuncTwoArgc)(INT32U,INT32U);
	INT32U (*FuncThreeArgc)(INT32U,INT32U,INT32U);
	INT32U (*FuncFourArgc)(INT32U,INT32U,INT32U,INT32U);
}APP_FuncMboxMsgStruct;


// Flag各种标志位定义
#define  RTC_SECIT_FLAG         0x00000001  // RTC秒中断标志
#define  RTC_ALRIT_FLAG         0x00000002  // RTC闹钟中断标志
#define  SPIFLASH_WK_FLAG       0x00000004  // SPI FLASH正在工作中标志, 用这个标志
#define  SD_WK_FLAG             0x00000008  // SD卡正在工作中标志
#define  NET_PHY_LINK_FLAG      0x00000010  // 网络硬件设备连接状态标志
#define  OS_START_FLAG          0x00000020  // 操作系统启动运行标志

// OKFlag 板子各功能测试成功标志
#define  SPIFLASH_OK_FLAG       0x00000001  // SPI FLASH测试成功标志
#define  NFLASH_OK_FLAG         0x00000002  // NAND FLASH测试成功标志
#define  EEPROM_OK_FLAG         0x00000004  // EEPROM测试成功标志
#define  SRAM_OK_FLAG           0x00000008  // 扩展SRAM测试成功标志
#define  SD_OK_FLAG             0x00000010  // SD卡测试成功标志
#define  UDISK_OK_FLAG          0x00000020  // UDISK测试成功标志
#define  USB_OK_FLAG            0x00000040  // USB设备测试成功标志
#define  NET_LINK_OK_FLAG       0x00000080  // 网络连接服务器或客户端成功标志
#define  NET_HWLINK_OK_FLAG     0x00000100  // 网络硬件(网线)连接成功标志



#define  DATABUF_SIZE   512

// EXTIFlag EXTI中断标志
#define  EXTI0_ISR_FLAG         0x00000001  // EXTI0中断标志
#define  EXTI1_ISR_FLAG         0x00000002  // EXTI1中断标志
#define  EXTI2_ISR_FLAG         0x00000004  // EXTI2中断标志
#define  EXTI3_ISR_FLAG         0x00000008  // EXTI3中断标志
#define  EXTI4_ISR_FLAG         0x00000010  // EXTI4中断标志
#define  EXTI5_ISR_FLAG         0x00000020  // EXTI5中断标志
#define  EXTI6_ISR_FLAG         0x00000040  // EXTI6中断标志
#define  EXTI7_ISR_FLAG         0x00000080  // EXTI7中断标志
#define  EXTI8_ISR_FLAG         0x00000100  // EXTI8中断标志
#define  EXTI9_ISR_FLAG         0x00000200  // EXTI9中断标志
#define  EXTI10_ISR_FLAG        0x00000400  // EXTI10中断标志
#define  EXTI11_ISR_FLAG        0x00000800  // EXTI11中断标志
#define  EXTI12_ISR_FLAG        0x00001000  // EXTI12中断标志
#define  EXTI13_ISR_FLAG        0x00002000  // EXTI13中断标志
#define  EXTI14_ISR_FLAG        0x00004000  // EXTI14中断标志
#define  EXTI15_ISR_FLAG        0x00008000  // EXTI15中断标志

#define  EXTI16_PVD_FLAG            0x00010000  // EXTI16中断标志
#define  EXTI17_RTCAlarm_FLAG       0x00020000  // EXTI17中断标志
#define  EXTI18_USBWakeUp_FLAG      0x00040000  // EXTI18中断标志
#define  EXTI19_NETWakeUp_FLAG      0x00080000  // EXTI19中断标志
#define  EXTI20_USBHSWakeUp_FLAG    0x00100000  // EXTI20中断标志
#define  EXTI21_RTCTSE_FLAG         0x00200000  // EXTI21中断标志
#define  EXTI22_RTCWakeUp_FLAG      0x00400000  // EXTI22中断标志

#define ALL_FF_8 0xff
#define ALL_FF_16 0xffff
#define ALL_FF_32 0xffffffff
//#pragma pack (1)
typedef struct
{ 
    INT32U   Flag;          // 各种标志位
    INT32U   TaskRunStatus; // 操作系统任务运行状态 
    INT32U   EXTIFlag;      // EXTI中断标志
    INT32U   OKFlag;        // 板子各功能测试成功标志
    INT32U   DI;	        // DI输入值: DI1=bit0, DI2=bit1; 以此类推DI32=bit31; 此值为从MCU端口读取的实际值
    INT32U   DI_P;	        // 控制板端口输入值: DI1_P=bit0, DI2_P=bit1; 以此类推DI32_P=bit31; 此值为工控板端口输入的实际值, 
                            // 一般板子内部有光耦隔离或者NPN三极管反向等电路, 则DI_P = ~PI
    INT32U   DO;	        // DO输出值: DO1=bit0, DO2=bit1; 以此类推DO32=bit31; 
    INT16U   SW;            // 拨码开关值: S1=bit0, S2=bit1; 以此类推S16=bit15; 
    INT8U    Key;           // 按键值
    INT32U   KeyVal;        // 按键标识变量
    INT16U   AO[2];         // AO输出变量标志
    ADC_VARS ADC;
    INT32U   PWM_ITFlag[PWM_NUM];   // PWM中断标志
    PWM_CTRL  PWMPara[PWM_NUM];	
    FCLK_VARS FCLK[FCLK_NUM];
	
	INT32U Tim6Pul;
	INT8U Tim6Dir;
    #if (MODULE_CLASS == STM32F107XX)
    INT16U   TIMx_ITFlag[7];   // TIM1-7中断标志
    #endif
    #if (MODULE_CLASS == STM32F103XX)
    INT16U   TIMx_ITFlag[7];   // TIM1-8中断标志
    #endif
    #if (MODULE_CLASS == STM32F407XX)
    INT16U   TIMx_ITFlag[14];  // TIM1-8中断标志
    #endif
    #if (MODULE_TYPE == STM32F103ZE)
    INT16U   FSMC_ITFlag;
    #endif
    
    #if ((PWM1_EN > 0)&&(PWM1_MODE==PWM_DMA))
    PWM_WRITE PWM1WritePara;
    #endif
    #if ((PWM2_EN > 0)&&(PWM2_MODE==PWM_DMA))
    PWM_WRITE PWM2WritePara;
    #endif
    #if ((PWM3_EN > 0)&&(PWM3_MODE==PWM_DMA))
    PWM_WRITE PWM3WritePara;
    #endif
    #if ((PWM4_EN > 0)&&(PWM4_MODE==PWM_DMA))
    PWM_WRITE PWM4WritePara;
    #endif
	
	INT32U   TimerCount;
    INT8U    buf[DATABUF_SIZE+1];  // 屏幕串口数据接受buff
    INT16U   UartData;      // Uart接收数据
    
    LIBSYS_VARS  LibSys;    // 
    CONFIG_PARA  Para;      //配置参数
}USER_VARS;	 
//#pragma pack() 
extern USER_VARS UserVars;	     // 用户变量

#endif
/***********************************************************************************/
// 文件结束
/***********************************************************************************/
