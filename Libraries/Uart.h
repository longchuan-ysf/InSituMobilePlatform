/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: uart.h
* Project  : STM32F1XX/4XX系列模块驱动库
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2020.4.1	
* Modify:  增加DMA发送和接收
* Email:   EmbedARM@126.com
* 
* Description: 本文件是UART串口硬件驱动程序头文件;
*
* Others: none;
*
* Function List: 
*          1. INT32S Uart_Init(INT8U id, UART_PARA *pPara);
*          2. INT32S Uart_Read(INT8U id, INT8U *p, INT16U len);
*          3. INT32S Uart_Write(INT8U id, INT8U *p, INT16U len);
*          4. INT32S Uart_RecvChar(INT8U id, INT8U *val);
*          5. INT32S Uart_SendChar(INT8U id, INT8U val);
*          6. INT32S Uart_Ctrl(INT8U id, INT8U Cmd, INT32U Para);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 1.10
*	   Date:         2018.10.1
*      Modification: none
*
*************************************************************************************/
#ifndef __UART_H 
#define __UART_H 
/************************************************************************************/
// 引用外部头文件
/************************************************************************************/
#include "const.h" 
/************************************************************************************/
// 初始化函数参数定义
/************************************************************************************/
// UART索引定义
#define UART1_ID	0 
#define UART2_ID	1 
#define UART3_ID	2 
#define UART4_ID	3 
#define UART5_ID	4 

#define UART6_ID	5  // 只有STM32F407VE模块支持

// 工作模式定义  
#define UART_AsynFD 	0    // 全双工的，异步通信
#define UART_SyncFD	    1	 // 全双工的，同步通信, 暂不支持
#define UART_LIN 		2	 // LIN通信, 暂不支持
#define UART_IrDA		3	 // IrDA通信, 暂不支持
#define UART_ISO7816	4	 // 智能卡通信, 暂不支持
#define UART_SWHALF		5    // 单线半双工通信, 暂不支持

// 波特率定义
#define BaudRate_1200	    1200 
#define BaudRate_2400	    2400
#define BaudRate_4800	    4800
#define BaudRate_9600	    9600
#define BaudRate_19200	    19200
#define BaudRate_38400	    38400
#define BaudRate_57600	    57600
#define BaudRate_115200	    115200
#define BaudRate_230400	    230400
#define BaudRate_460800	    460800
#define BaudRate_921600	    921600 

// 数据字长定义：0: 8bit;   1: 9bit;
#define UART_WORD_LENGTH_8B      0   // 定义数据字长8bit
#define UART_WORD_LENGTH_9B      1   // 定义数据字长9bit

// 停止位定义: 0: 1bit;   1: 2bit;    2: 0.5bit;  3: 1.5bit;
#define UART_STOP_BITS_1         0   // 定义停止位1bit
#define UART_STOP_BITS_2         1   // 定义停止位2bit
#define UART_STOP_BITS_0_5       2   // 定义停止位0.5bit
#define UART_STOP_BITS_1_5       3   // 定义停止位1.5bit

// 奇偶检验位位定义: 0: 无校验; 1: 偶校验;  2: 奇校验;  
#define UART_PARITY_NO           0   // 定义奇偶检验位: 无校验
#define UART_PARITY_EVEN         1   // 定义奇偶检验位: 偶校验
#define UART_PARITY_ODD          2   // 定义奇偶检验位: 奇校验

// 硬件流控定义: 0: 无流控; 1: RTS流控;  2: CTS流控; 3: RTS和CTS流控;
#define UART_HWFLOW_CTRL_NO        0 // 无流控
#define UART_HWFLOW_CTRL_RTS       1 // RTS流控, 暂时不支持
#define UART_HWFLOW_CTRL_CTS       2 // CTS流控, 暂时不支持
#define UART_HWFLOW_CTRL_RTS_CTS   3 // RTS和CTS流控, 暂时不支持

// DMA使能定义: 0: 关闭DMA; 1:TX使能DMA; 2: RX使能DMA;
#define UART_DMAREQ_NO             0 // 关闭DMA
#define UART_DMAREQ_TX             1 // TX使能DMA
#define UART_DMAREQ_RX             2 // RX使能DMA

// UART(管脚)功能重映射定义
#define UART_REMAP_0       0    // UART没有重映射
#define UART_REMAP_1       1    // UART重映射1
#define UART_REMAP_2       2    // UART重映射2
/************************************************************************************************************************/
// 以下表是工控模块STM32F107VC,STM32F103VE,STM32F103ZE UART1-5管脚映射表, 是利用重映射方式定义
/************************************************************************************************************************/
// UART1-UART5(管脚)功能重映射表
/*
|---------------------------------------|
| 项目  |  重映射  |  TX管脚  |  RX管脚 |
|---------------------------------------|
|       |   没有   |   PA9    |   PA10  |
| UART1 |-------------------------------|
|       |  重映射1 |   PB6    |   PB7   |
|---------------------------------------|
|       |   没有   |   PA2    |   PA3   |
| UART2 |-------------------------------|
|       |  重映射1 |   PD5    |   PD6   |
|---------------------------------------|
|       |   没有   |   PB10   |   PB11  |
|       |-------------------------------|
| UART3 |  重映射1 |   PC10   |   PC11  |
|       |-------------------------------|
|       |  重映射2 |   PD8    |   PD9   |
|---------------------------------------|
| UART4 |   没有   |   PC10   |   PC11  |
|---------------------------------------|
| UART5 |   没有   |   PC12   |   PD2   |
|---------------------------------------|
*/

/************************************************************************************************************************/
// 以下表是工控模块STM32F407VE UART1-6管脚映射表, 是利用管脚复用寄存器定义
/************************************************************************************************************************/
// UART1-UART6(管脚)功能映射表
/*
|---------------------------------------|
| 项目  | 复用选择 |  TX管脚  |  RX管脚 |
|---------------------------------------|
|       |          |   PA9    |   PA10  |
| UART1 |   AF7    |--------------------|
|       |          |   PB6    |   PB7   |
|---------------------------------------|
|       |          |   PA2    |   PA3   |
| UART2 |   AF7    |--------------------|
|       |          |   PD5    |   PD6   |
|---------------------------------------|
|       |          |   PB10   |   PB11  |
|       |          |--------------------|
| UART3 |   AF7    |   PC10   |   PC11  |
|       |          |--------------------|
|       |          |   PD8    |   PD9   |
|---------------------------------------|
|       |          |   PA0    |   PA1   |
| UART4 |   AF8    |--------------------|
|       |          |   PC10   |   PC11  |
|---------------------------------------|
| UART5 |   AF8    |   PC12   |   PD2   |
|---------------------------------------|
|       |          |   PC6    |   PC7   |
| UART6 |   AF8    |--------------------|
|       |          |   PG14   |   PG9   |
|---------------------------------------|
*/

// 参数标志Flag定义
#define UART_REMAP1_FLAG       0x00000001  // WKFlag的bit0=1, REMAP1有效
#define UART_REMAP2_FLAG       0x00000002  // WKFlag的bit1=1, REMAP2有效
#define UART_DATA_7BIT_FLAG    0x00000008  // WKFlag的bit3=1, 实际有效7位数据位;在设置了奇偶检验位并且数据位设置8bit, 实际有效数据位是7bit
                                           // 请初始化时设置该标志
#define UART_WORD_LENGTH_9BIT_FLAG  0x00000010  // WKFlag的bit4=1, 数据位9bit标志;
#define UART_PARITY_EVEN_FLAG  0x00000020  // WKFlag的bit5=1, 偶校验
#define UART_PARITY_ODD_FLAG   0x00000040  // WKFlag的bit6=1, 奇校验
#define UART_STOP_BITS2_FLAG   0x00000080  // WKFlag的bit7=1,  停止位2位;
#define UART_STOP_BITS0_5_FLAG 0x00000100  // WKFlag的bit8=1,  停止位0.5位;
#define UART_STOP_BITS1_5_FLAG 0x00000200  // WKFlag的bit9=1,  停止位1.5位;
#define UART_DMAREQ_RX_FLAG    0x00000400  // WKFlag的bit10=1, RX接收DMA使能;
#define UART_DMAREQ_TX_FLAG    0x00000800  // WKFlag的bit11=1, TX发送DMA使能;
#define UART_HWFC_CTS_FLAG     0x00001000  // WKFlag的bit12=1, CTS流控使能;
#define UART_HWFC_RTS_FLAG     0x00002000  // WKFlag的bit13=1, RTS流控使能;
#define UART_RS485DIR_FLAG     0x00004000  // UART转RS485接口时, WKFlag的bit14=1, 方向IO DIR高电平接收; bit14=0, 方向IO DIR低电平电平接收;
#define UART_RS485EN_FLAG      0x00008000  // WKFlag的bit15=1, UART转RS485接口, 需要DIR方向信号; bit15=0, UART转RS232或者TTL接口，不需要DIR方向;
#define UART_ISRHOOK_FLAG      0x00010000  // WKFlag的bit16=1, 中断调用Uart1(2/3/4/5/6)_ISRHook()接收数据;


#define UART_TXBUSY_FLAG        0x80000000  // WKFlag的bit31=1, 数据发送正在进行标志;

// UART参数结构 
typedef struct
{
    INT32U Flag;                 // 工作参数标志
    INT32U BaudRate;             // 波特率：参见波特率定义
    INT8U  Mode;                 // 工作模式：参考工作模式定义
   
    INT8U  TXPin;                // 发送数据IO管脚定义     
    INT8U  RXPin;                // 接收数据IO管脚定义     
    INT8U  RS485DirPin;          // RS485方向控制IO管脚定义 
   
    INT8U *pTxBuf;               // 发送数据缓存指针
    INT16U TxBufLen;             // 发送缓存长度
  
    INT8U *pRxBuf;               // 接收数据缓存指针
    INT16U RxBufLen;             // 接收缓存长度
}UART_PARA;

/************************************************************************************/
// 命令控制函数参数定义
/************************************************************************************/
// UART命令定义
#define CMD_UART_GetCharsRxBuf	0 	 // 读取接收数据缓存中数据长度
#define CMD_UART_GetCharsTxBuf	1 	 // 读取发送数据缓存中空闲空间长度
#define CMD_UART_ChangeBaud  	2 	 // 改变波特率
#define CMD_UART_ClearRxBuffer  3    // 清除接收缓存中数据.
#define CMD_UART_ClearTxBuffer  4    // 清除发送缓存中数据.	
#define CMD_UART_ChangeUtcf		5	 // 改变串口数据格式
#define CMD_UART_RXCtrl      	6	 // 串口接收使能控制
#define CMD_UART_RST            7    // 复位UART寄存器为初始状态
#define CMD_UART_CLOSE          8    // 关闭UART时钟,也就是关闭UART功能,可以省电 

/*************************************************************************************/
//
// 						UART硬件驱动程序函数定义
//
/*************************************************************************************/
/***********************************************************************************
* Function: Uart_Init;
*
* Description: Uart初始化函数;
*              
* Input:  id, UART索引标识(UART1_ID~UART6_ID);
*         *pPara, UART初始化参数指针;
*
* Output: none;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   初始化完成，UART已经使能开始工作，无需调用Uart_Ctrl再次使能;
*         这里这个函数初始化了TXD/RXD, 和RS485方向DIR信号;
************************************************************************************/
INT32S Uart_Init(INT8U id, UART_PARA *pPara);

/***********************************************************************************
* Function: Uart_Read;
*
* Description: 读取接收的数据; 如果有数据被接收,该函数会返回接收一定长度的数据块,
*              否则将返回错误代码,
*           
* Input:  id,  UART索引标识(UART1_ID~UART6_ID);
*         *p,  接收数据块指针; 
*         len, 接收数据块长度;
*      		  
* Output: *p,  接收数据块指针; 
*          		
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   该函数并不等待接收数据就返回;
************************************************************************************/
INT32S Uart_Read(INT8U id, INT8U *p, INT16U len);

/***********************************************************************************
* Function: Uart_Write;
*
* Description: 发送一个数据块到发送缓存中;
*           
* Input:  id,  UART索引标识(UART1_ID~UART6_ID);
*         *p,  发送数据块指针; 
*         len, 发送数据块长度;
*      		
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   该函数只是将数据发送缓存中,UART会立即启动发送数据，但函数返回时并不意味着
*         数据已经发送完成；
************************************************************************************/
INT32S Uart_Write(INT8U id, INT8U *p, INT16U len);

/***********************************************************************************
* Function: Uart_RecvChar;
*
* Description: 接收一个字节数据，如果有数据被接收,该函数会返回一个接收数据,否则将返回错误代码;
*               
* Input:  id,  UART索引标识(UART1_ID~UART6_ID);
*         *val,接收数据的指针;
*
* Output: none;
*          		
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   该函数并不等待接收数据就返回;
************************************************************************************/
INT32S Uart_RecvChar(INT8U id, INT8U *val);

/***********************************************************************************
* Function: Uart_SendChar;
*
* Description: 发送一个字节数据到发送缓存中;
* 
* Input:  iid,  UART索引标识(UART1_ID~UART6_ID);
*         val,  发送的数据;
*
* Output: none;
*          		
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   1. 该函数只是存储数据到发送缓存中,UART会立即启动发送数据，但函数返回时并不意味着
*            数据已经发送完成;
*         2. 该函数不支持DMA数据发送, 在设置为DMA发送模式, 返回ERR_FALSE;
************************************************************************************/
INT32S Uart_SendChar(INT8U id, INT8U val);

/***********************************************************************************
* Function: Uart_Ctrl;
*
* Description: UART命令控制;
* 
* Input:  id,   UART索引标识(UART1_ID~UART6_ID);
*         Cmd,  UART控制命令: 
*               CMD_UART_GetCharsRxBuf: 读取接收数据缓存中数据长度
*               CMD_UART_GetCharsTxBuf: 读取发送数据缓存中空闲空间长度
*               CMD_UART_ChangeBaud:    改变波特率
*               CMD_UART_ClearRxBuffer: 清除接收缓存中数据.
*               CMD_UART_ClearTxBuffer: 清除发送缓存中数据.
*               CMD_UART_ChangeUtcf:    改变串口数据格式
*               CMD_UART_RXCtrl:	    串口接收使能控制
*               CMD_UART_RST:           复位UART寄存器为初始状态
*               CMD_UART_CLOSE:         关闭UART时钟,也就是关闭UART功能,可以省电 
*         Para，CMD命令控制参数;
*
* Output: none;
*          		
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码; 有返回数据的返回相应数据；
*
* Note:   none;
************************************************************************************/
INT32S Uart_Ctrl(INT8U id, INT8U Cmd, INT32U Para);

#endif
/***********************************************************************************/
// 文件结束
/***********************************************************************************/

