/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: spi.h
* Project  : STM32F1XX/4XX系列模块驱动库
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2020.8.24			
* Email:   EmbedARM@126.com
* 
* Description: 本文件是SPI总线硬件驱动程序头文件;
*
* Others: none;
*
* Function List: 
*          1. INT32S SPI_Init(INT8U id, SPI_PARA *pPara);
*          2. INT32S SPI_Read(INT8U id, INT8U *p, INT32U len);
*          3. INT32S SPI_Write(INT8U id, INT8U *p, INT32U len);
*          4. INT8U  SPI_ReadWriteByte(INT8U id, INT8U val);
*          5. INT32S SPI_DMAWrite(INT8U id, INT8U *p, INT32U len, SPI_DMA_PARA *pPara);
*          6. INT32S SPI_DMARead(INT8U id, INT8U *p, INT32U len, SPI_DMA_PARA *pPara);
*          7. INT32S SPI_Ctrl(INT8U id, INT8U Cmd, INT32U Para);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 1.10
*	   Date:         2018.10.1
*      Modification: none
*
*************************************************************************************/
#ifndef __SPI_H 
#define __SPI_H 
/************************************************************************************/
// 引用外部头文件
/************************************************************************************/
#include "const.h"
/************************************************************************************/
// SPI初始化函数参数定义
/************************************************************************************/
// SPI索引定义
#define SPI1_ID		0 
#define SPI2_ID    	1 
#define SPI3_ID    	2 


//SPI主机和设备模式
#define SPI_Mode_Master                 ((INT16U)0x0104) // 主机模式
#define SPI_Mode_Slave                  ((INT16U)0x0000) // 设备模式

// SPI数据位数
#define SPI_DataSize_16b                ((INT16U)0x0800) // 16位数据位
#define SPI_DataSize_8b                 ((INT16U)0x0000) // 8位数据位

// SPI数据帧格式 
#define SPI_FirstBit_MSB                ((INT16U)0x0000) // 先发送MSB(高位)
#define SPI_FirstBit_LSB                ((INT16U)0x0080) // 先发送LSB(低位)

// SPI时钟极性
#define SPI_CPOL_Low                    ((INT16U)0x0000) // 时钟空闲低电平
#define SPI_CPOL_High                   ((INT16U)0x0002) // 时钟空闲高电平

// SPI时钟相位 
#define SPI_CPHA_1Edge                  ((INT16U)0x0000) // 数据采样从第一个时钟边沿开始(下降沿)
#define SPI_CPHA_2Edge                  ((INT16U)0x0001) // 数据采样从第二个时钟边沿开始(上升沿) 

// SPI_Slave_Select_management 
#define SPI_NSS_Soft                    ((INT16U)0x0200)
#define SPI_NSS_Hard                    ((INT16U)0x0000)

//SPI 全双工和只接收 
#define SPI_2Lines_FullDuplex           ((INT16U)0x0000) // 2线, 全双工
#define SPI_2Lines_RxOnly               ((INT16U)0x0400) // 2线，只接收

//#define SPI_Direction_1Line_Rx          ((INT16U)0x8000)
//#define SPI_Direction_1Line_Tx          ((INT16U)0xC000)
#define SPI_BaudRatePrescaler_2         ((INT16U)0x0000) // 2??
#define SPI_BaudRatePrescaler_4         ((INT16U)0x0008) // 4??
#define SPI_BaudRatePrescaler_8         ((INT16U)0x0010) // 8??
#define SPI_BaudRatePrescaler_16        ((INT16U)0x0018) // 16??
#define SPI_BaudRatePrescaler_32        ((INT16U)0x0020) // 32??
#define SPI_BaudRatePrescaler_64        ((INT16U)0x0028) // 64??
#define SPI_BaudRatePrescaler_128       ((INT16U)0x0030) // 128??
#define SPI_BaudRatePrescaler_256       ((INT16U)0x0038) // 256??



// SPI(管脚)功能重映射定义
#define SPI_REMAP_0       0    // SPI没有重映射
#define SPI_REMAP_1       1    // SPI重映射
/*
// SPI1(管脚)功能重映射定义
#define SPI1_REMAP_0      0   // SPI1没有重映射, 对应管脚定义：
                              // SPI1_NSS: PA4; SPI1_SCK: PA5; SPI1_MISO: PA6; SPI1_MOSI: PA7;
                               
#define SPI1_REMAP_1      1   // SPI1重映射, 对应管脚定义：
                              // SPI1_NSS: PA15; SPI1_SCK: PB3; SPI1_MISO: PB4; SPI1_MOSI: PB5;

// SPI2(管脚)没有功能重映射定义
#define SPI2_REMAP_0      0   // SPI2没有重映射, 对应管脚定义：
                              // SPI2_NSS: PB12; SPI2_SCK: PB13; SPI2_MISO: PB14; SPI2_MOSI: PB15;
                               
// SPI3(管脚)功能重映射定义
#define SPI3_REMAP_0      0   // SPI3没有重映射, 对应管脚定义：
                              // SPI3_NSS: PA15; SPI3_SCK: PB3; SPI3_MISO: PB4; SPI3_MOSI: PB5;
                               
#define SPI3_REMAP_1      1   // SPI3重映射, 对应管脚定义：
                              // SPI3_NSS: PA4; SPI3_SCK: PC10; SPI3_MISO: PC11; SPI3_MOSI: PC12;
*/
/************************************************************************************************************************/
// 以下表是工控模块STM32F107VC,STM32F103VE,STM32F103ZE SPI1-3管脚映射表, 是利用重映射方式定义
/************************************************************************************************************************/
// SPI1-SPI3(管脚)功能重映射表
/*
|-------------------------------------------------------------|
| 项目  |  重映射  | NSS管脚 | SCK管脚  | MISO管脚 | MOSI管脚 |
|-------------------------------------------------------------|
|       |   没有   |   PA4   |   PA5    |    PA6   |   PA7    |
| SPI1  |-----------------------------------------------------|
|       |  重映射1 |   PA15  |   PB3    |    PB4   |   PB5    |
|-------------------------------------------------------------|
| SPI2  |   没有   |   PB12  |   PB13   |    PB14  |   PB15   |
|-------------------------------------------------------------|
|       |   没有   |   PA15  |   PB3    |    PB4   |   PB5    |
| SPI3  |-----------------------------------------------------|
|       |  重映射1 |   PA4   |   PC10   |    PC11  |   PC12   |
|-------------------------------------------------------------|
*/

/************************************************************************************************************************/
// 以下表是工控模块STM32F407VE SPI1-3管脚映射表, 是利用管脚复用寄存器定义
/************************************************************************************************************************/
// SPI1-SPI3(管脚)功能映射表
/*
|-------------------------------------------------------------|
| 项目  | 复用选择 | NSS管脚 | SCK管脚  | MISO管脚 | MOSI管脚 |
|-------------------------------------------------------------|
|       |          |   PA4   |   PA5    |    PA6   |   PA7    |
| SPI1  |   AF5    |------------------------------------------|
|       |          |   PA15  |   PB3    |    PB4   |   PB5    |
|-------------------------------------------------------------|
|       |          |   PB12  |   PB13   |    PB14  |   PB15   |
| SPI2  |   AF5    |------------------------------------------|
|       |          |   PB9   |   PB10   |    PC2   |   PC3    |
|-------------------------------------------------------------|
|       |          |   PA15  |   PB3    |    PB4   |   PB5    |
| SPI3  |   AF6    |------------------------------------------|
|       |          |   PA4   |   PC10   |    PC11  |   PC12   |
|-------------------------------------------------------------|
*/

// SPI管脚参数结构 
typedef struct
{
    INT8U  Remap;       // SPI引脚功能重映射
    INT8U  SCK;         // SPI_SCK管脚
    INT8U  MISO;        // SPI_MOSI管脚
    INT8U  MOSI;        // SPI_MISO管脚
    INT8U  NSS;         // SPI_NSS管脚
}SPI_PIN;

// 配置寄存器参数, 可以有2种配置方式: 直接给reg赋值或者给各个b.x位赋值
typedef union 
{
    INT16U   reg;
    struct
    {
        INT16U CPHA:                1; // 时钟相位: 0,数据采样从第一个时钟边沿开始(下降沿); 1, 数据采样从第二个时钟边沿开始(上升沿) 
        INT16U CPOL:                1; // 时钟极性: 0,时钟空闲低电平; 1,时钟空闲高电平;
        INT16U Mode:                1; // 主设备和从设备模式选择: 0, 配置为从设备; 1,配置为主设备
        INT16U BaudRatePrescaler:   3; // 分频系数设置: 0,2分频; 1,4分频; 2,8分频; 3,16分频; 4,32分频; 5,64分频; 6,128分频; 7,256分频;
        INT16U SPE:                 1; // SPI使能: 0,关闭SPI; 1, 使能SPI 
        INT16U Direction:           1; // 先发送高位和低位选择: 0,先发送MSB(高位); 1,先发送LSB(低位)
        INT16U SSI:                 1; // 内部从设备选择, 默认为0;
        INT16U SSM:                 1; // 软件从设备选择, 默认为0;
        INT16U RxOnly:              1; // 只接收设置, 默认为0(全双工)：SPI_2Lines_FullDuplex 或 SPI_2Lines_RxOnly
        INT16U DataSize:            1; // 数据位数选择：SPI_DataSize_16b 或 SPI_DataSize_8b
        INT16U CRCNext:             1; // 下一个发送CRC, 默认为0
        INT16U CRCEN:               1; // CRC校验使能, 默认为0
        INT16U BIDIOE:              1; // 双向模式下输出使能, 默认为0: 0: 输出禁止(只收模式), 1:输出使能(只发模式)
        INT16U BIDIMODE:            1; // 双向数据模式使能, 默认0: 0: 选择双线模式, 1:选择单线模式
    }b;
} SPI_CR1_TypeDef;

// SPI数据帧格式 
#define SPI_FirstBit_MSB                ((INT16U)0x0000) // 先发送MSB(高位)
#define SPI_FirstBit_LSB                ((INT16U)0x0080) // 先发送LSB(低位)

// SPI时钟极性
#define SPI_CPOL_Low                    ((INT16U)0x0000) // 时钟空闲低电平
#define SPI_CPOL_High                   ((INT16U)0x0002) // 时钟空闲高电平

// SPI时钟相位 
#define SPI_CPHA_1Edge                  ((INT16U)0x0000) // 数据采样从第一个时钟边沿开始(下降沿)
#define SPI_CPHA_2Edge                  ((INT16U)0x0001) // 数据采样从第二个时钟边沿开始(上升沿) 

// 参数标志Flag定义
#define SPI_ISRHOOK_FLAG  0x0001  // 配置使能钩子函数标志
#define SPI_RXDMA_FLAG    0x0002  // RX接收DMA使能标志
#define SPI_TXDMA_FLAG    0x0004  // TX发送DMA使能标志;

// void (* pISRHook) (INT32U flag) 中flag标志


// SPI参数结构
typedef struct
{
    INT16U Flag;                // 参数标志
    SPI_PIN Pin;                // SPI管脚 
    SPI_CR1_TypeDef cfg;        // SPI配置参数
    INT8U   CRCPolynomial;      // CRC多项式
    INT8U   DmaID;              // DMA ID
    INT8U   TXDmaCh;            // TX DMA 通道
    INT8U   RXDmaCh;            // RX DMA 通道
    void (* pISRHook) (INT32U flag); // SPI中断钩子函数, 在DMA方式读写时是非阻塞模式，则可以通过这个函数判定是否写入完成；
                                     // 在阻塞模式可以不用, 设置为0
}SPI_PARA;


typedef struct
{
    INT16U Flag;                // 参数标志, 暂无定义，默认0
    INT16U TimeOut;             // 函数最大延时, 单位ms
}SPI_DMA_PARA;
 
/************************************************************************************/
// 命令控制函数参数定义
/************************************************************************************/
// SPI时钟分频系数
#define SPI_DIVCLK_2         ((INT16U)0x0000)   // 2分频
#define SPI_DIVCLK_4         ((INT16U)0x0008)	// 4分频
#define SPI_DIVCLK_8         ((INT16U)0x0010)	// 8分频
#define SPI_DIVCLK_16        ((INT16U)0x0018)	// 16分频
#define SPI_DIVCLK_32        ((INT16U)0x0020)	// 32分频
#define SPI_DIVCLK_64        ((INT16U)0x0028)	// 64分频
#define SPI_DIVCLK_128       ((INT16U)0x0030)	// 128分频
#define SPI_DIVCLK_256       ((INT16U)0x0038)	// 256分频

// 时钟相位模式
#define SPI_CKMODE0  0	// CPOL = 0, CPHA = 0: 时钟空闲低电平, 数据采样从第一个时钟边沿开始(上升沿)  
#define SPI_CKMODE1  1	// CPOL = 0, CPHA = 1：时钟空闲低电平, 数据采样从第二个时钟边沿开始(下降沿)  
#define SPI_CKMODE2  2	// CPOL = 1, CPHA = 0：时钟空闲高电平, 数据采样从第一个时钟边沿开始(下降沿)  
#define SPI_CKMODE3  3	// CPOL = 1, CPHA = 1：时钟空闲高电平, 数据采样从第二个时钟边沿开始(上升沿)   

// SPI 控制命令定义
#define CMD_SPI_ENA                    0  // 使能SPI外设
#define CMD_SPI_DIS                    1  // 禁用SPI外设
#define CMD_SPI_DIVCLK	               2  // 设置时钟分频系数
#define CMD_SPI_CKMODE	               3  // 时钟相位模式，Para：可以为0,1,2,3
#define CMD_SPI_RST                    4  // 复位SPI寄存器为初始状态
#define CMD_SPI_CLOSE                  5  // 关闭SPI时钟,也就是关闭SPI功能,可以省电 

/*************************************************************************************/
//
// 				    SPI控制器硬件驱动函数定义
//
/*************************************************************************************/

/***********************************************************************************
* Function: SPI_Init;
*
* Description: SPI初始化函数;
* 
* Input:  id, SPI识别号(SPI1_ID,SPI2_ID,SPI3_ID);
*         *pPara, SPI初始化参数指针;
*
* Output: none;
*          		
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   初始化完成，SPI已经使能开始工作，无需调用SPI_Ctrl再次使能;
*         这里这个函数初始化了SCK/MOSI/MISO, 对于SPI片选信号GPIO用户自行初始化
************************************************************************************/
INT32S SPI_Init(INT8U id, SPI_PARA *pPara);

/***********************************************************************************
* Function: SPI_Read;
*
* Description: SPI总线读数据函数;
*              
* Input:  id,SPI识别号(SPI1_ID,SPI2_ID,SPI3_ID);
*         *p, 读出数据存储的地址指针; 
*         len,要读出数据长度;
*
* Output: none;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32S SPI_Read(INT8U id, INT8U *p, INT32U len);

/***********************************************************************************
* Function: SPI_DMARead;
*
* Description: SPI总线利用DMA读数据函数;
*              
* Input:  id, SPI识别号(SPI1_ID,SPI2_ID,SPI3_ID);
*         *p, 读出数据存储的地址指针; 
*         len,要读出数据长度;
*         pPara, 读函数参数  
*
* Output: none;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32S SPI_DMARead(INT8U id, INT8U *p, INT32U len, SPI_DMA_PARA *pPara);

/***********************************************************************************
* Function: _SPI_Write;
*
* Description: SPI总线写数据函数;
*              
* Input:  id,SPI识别号(SPI1_ID,SPI2_ID,SPI3_ID);
*         *p, 写入数据的存储的地址指针; 
*         len,要写入数据长度;
*
* Output: none;
*
* Return: 只能返回ERR_TRUE;
*
* Note:   none;
************************************************************************************/
INT32S SPI_Write(INT8U id, INT8U *p, INT32U len);

/***********************************************************************************
* Function: SPI_DMAWrite;
*
* Description: SPI总线利用DMA写数据函数;
*              
* Input:  id, SPI识别号(SPI1_ID,SPI2_ID,SPI3_ID);
*         *p, 写入数据的存储的地址指针; 
*         len,要写入数据长度;
*         pPara, 写函数参数  
*
* Output: none;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32S SPI_DMAWrite(INT8U id, INT8U *p, INT32U len, SPI_DMA_PARA *pPara);

/***********************************************************************************
* Function: SPI_ReadWriteByte;
*
* Description: SPI总线读写一个字节数据函数;
*              
* Input:  id,SPI识别号(SPI1_ID,SPI2_ID,SPI3_ID);
*         val, 写入的数据; 
*
* Output: none;
*
* Return: 返回读出的数据;
*
* Note:   none;
************************************************************************************/
INT8U SPI_ReadWriteByte(INT8U id, INT8U val);

/***********************************************************************************
* Function: SPI_Ctrl;
*
* Description: SPI命令控制;
* 
* Input:  id, SPI识别号(SPI1_ID,SPI2_ID,SPI3_ID);
*         Cmd,  SPI控制命令：
*               CMD_SPI_ENA：   使能SPI外设, Para为0
*　　　　　　　 CMD_SPI_DIS：   使能SPI外设, Para为0　　　　　　　　　　
*               CMD_SPI_DIVCLK：设置时钟分频系数, Para为SPI_DIVCLK_2~SPI_DIVCLK_256
*               CMD_SPI_CKMODE：时钟相位模式，Para为：SPI_CKMODE0~SPI_CKMODE3
*               CMD_SPI_RST：   复位SPI寄存器为初始状态, Para为0
*               CMD_SPI_CLOSE： 关闭SPI时钟,也就是关闭SPI功能,可以省电, Para为0 
*         Para, SPI命令控制参数;
*
* Output: none;
*          		
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32S SPI_Ctrl(INT8U id, INT8U Cmd, INT32U Para);
  
#endif
/***********************************************************************************/
// 文件结束
/***********************************************************************************/



