/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: i2c.h
* Project  : STM32F1XX/4XX系列模块驱动库
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: 本文件是I2C总线硬件驱动程序头文件;
*
* Others: none;
*
* Function List: 
*          1. INT32S I2C_Init(INT8U I2Cx, I2C_PARA *pPara);
*          2. INT32S I2C_Read(INT8U id, INT16U I2CAddr, INT16U addr, INT8U *p, INT16U len);
*          3. INT32S I2C_Write(INT8U id, INT16U I2CAddr, INT16U addr, INT8U *p, INT16U len);
*          4. INT32S I2C_Ctrl(INT8U id, INT8U Cmd, INT32U Para);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/
#ifndef __I2C_H 
#define __I2C_H 	 

/************************************************************************************/
// 引用外部头文件
/************************************************************************************/
#include "const.h" 

/************************************************************************************/
// 初始化函数参数定义
/************************************************************************************/
// I2C索引定义
#define I2C1_ID		0 
#define I2C2_ID    	1 
#define I2C3_ID    	2  // 只有STM32F407VE模块支持 

// I2C器件地址宽定义
#define I2C_8Bit		0x0000   // I2C器件地址宽度是8bit
#define I2C_16Bit    	0x8000   // I2C器件地址宽度是16bit

// I2C模式定义
#define I2C_Mode_I2C                    ((INT16U)0x0000)  // I2C模式
#define I2C_Mode_SMBusDevice            ((INT16U)0x0002)  // SMBus设备模式
#define I2C_Mode_SMBusHost              ((INT16U)0x000A)  // SMBus主机模式

// I2C_duty_cycle_in_fast_mode 
#define I2C_DutyCycle_16_9              ((INT16U)0x4000)  // I2C 快速模式下 Tlow/Thigh = 16/9 
#define I2C_DutyCycle_2                 ((INT16U)0xBFFF)  // I2C 快速模式下 Tlow/Thigh = 2 

// I2C_acknowledgement
#define I2C_Ack_Enable                  ((INT16U)0x0400)  // 应答确认使能：在接受到一个字节返回一个应答
#define I2C_Ack_Disable                 ((INT16U)0x0000)  // 应答确认关闭：无应答使能

// I2C_acknowledged_address 
#define I2C_AcknowledgedAddress_7bit    ((INT16U)0x4000)  // 7位地址模式
#define I2C_AcknowledgedAddress_10bit   ((INT16U)0xC000)  // 10位地址模式

// I2C(管脚)功能重映射定义
#define I2C_REMAP_0       0    // I2C没有重映射
#define I2C_REMAP_1       1    // I2C重映射
                              
/*
// I2C1(管脚)功能重映射定义
#define I2C1_REMAP_0       0   // I2C1没有重映射, 对应管脚定义：
                               // I2C1_SCL: PB6; I2C1_SDA: PB7;
                               
#define I2C1_REMAP_1       1   // I2C1重映射, 对应管脚定义：
                               // I2C1_SCL: PB8; I2C1_SDA: PB9;

// I2C2(管脚)没有功能重映射定义
#define I2C2_REMAP_0       0   // I2C2没有重映射, 对应管脚定义：
                               // I2C2_SCL: PB10; I2C2_SDA: PB11;
*/                              

/************************************************************************************************************************/
// 以下表是工控模块STM32F107VC,STM32F103VE,STM32F103ZE I2C1-2管脚映射表, 是利用重映射方式定义
/************************************************************************************************************************/
// I2C1-I2C2(管脚)功能重映射表
/*
|---------------------------------------|
| 项目  |  重映射  | SCL管脚 | SDA管脚  |
|---------------------------------------|
|       |   没有   |   PB6   |   PB7    |
| I2C1  |-------------------------------|
|       |  重映射1 |   PB8   |   PB9    |
|---------------------------------------|
| I2C2  |   没有   |   PB10  |   PB11   |
|---------------------------------------|
*/                               
                 
/************************************************************************************************************************/
// 以下表是工控模块STM32F407VE I2C1-3管脚映射表, 是利用管脚复用寄存器定义
/************************************************************************************************************************/
// I2C1-I2C2(管脚)功能映射表
/*
|---------------------------------------|
| 项目  | 复用选择 | SCL管脚 | SDA管脚  |
|---------------------------------------|
|       |          |   PB6   |   PB7    |
| I2C1  |   AF4    |--------------------|
|       |          |   PB8   |   PB9    |
|---------------------------------------|
|       |          |   PB10  |   PB11   |
| I2C2  |   AF4    |--------------------|
|       |          |   PF0   |   PF1    |
|---------------------------------------|
|       |          |   PA8   |   PC9    |
| I2C3  |   AF4    |--------------------|
|       |          |   PH7   |   PH8    |
|---------------------------------------|
*/                               
       
                               
// I2C参数结构
typedef struct
{
    INT16U Flag;                // 参数标志
    INT8U  PinRemap;            // I2C引脚功能重映射
    INT8U  SDAPin;              // SDA引脚
    INT8U  SCLPin;              // SCL引脚
    
    INT16U Mode;                // I2C工作模式:
                                // This parameter can be a value of I2C_mode 
    INT16U DutyCycle;           // Specifies the I2C fast mode duty cycle.
                                // This parameter can be a value of I2C_duty_cycle_in_fast_mode 
    INT16U OwnAddress1;         // Specifies the first device own address.
                                // This parameter can be a 7-bit or 10-bit address. 
    INT16U Ack;                 // Enables or disables the acknowledgement.
                                // This parameter can be a value of I2C_acknowledgement 
    INT16U AcknowledgedAddress; // Specifies if 7-bit or 10-bit address is acknowledged.
                                // This parameter can be a value of @ref I2C_acknowledged_address
    INT32U ClockSpeed;          // I2C时钟频率, 设置值必须小于400KHz.
}I2C_PARA;

/************************************************************************************/
// 命令控制函数参数定义
/************************************************************************************/
// I2C命令定义
#define CMD_I2C                  0  // 启用I2C外设或禁用I2C外设，参数是ENABLE或DISABLE	
#define CMD_I2C_RST              4  // 复位I2C寄存器为初始状态
#define CMD_I2C_CLOSE            5  // 关闭I2C时钟,也就是关闭I2C功能,可以省电 

/************************************************************************************
//
//                 I2C总线硬件驱动程序
//
*************************************************************************************/

/***********************************************************************************
* Function: I2C_Init;
*
* Description: I2C初始化函数;
*              
* Input:  id, I2C索引标识：I2C1_ID、I2C2_ID、I2C3_ID;
*		  *pPara, I2C参数表指针 
*
* Output: none;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   初始化完成，I2C已经使能开始工作，无需调用I2C_Ctrl再次使能;
************************************************************************************/
INT32S I2C_Init(INT8U I2Cx, I2C_PARA *pPara);

/***********************************************************************************
* Function: I2C_Read;
*
* Description: I2C总线读数据函数;
*              
* Input:  id, I2C索引标识：I2C1_ID、I2C2_ID、I2C3_ID;
*         I2CAddr, I2C器件识别地址;  
*         addr,读数据的起始地址; 
*         *p, 读出数据存储的地址指针;
*         len,要读出数据长度;
*
* Output: none;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   如果I2C挂载器件是EEPROM则：
*         I2CAddr的bit15=0,支持24C01/02/04/08/16或地址是8位的器件; 
*         I2CAddr的bit15=1,支持24C32/64/128/256或地址是16位的器件;
************************************************************************************/
INT32S I2C_Read(INT8U id, INT16U I2CAddr, INT16U addr, INT8U *p, INT16U len);

/***********************************************************************************
* Function: I2C_Write;
*
* Description: I2C总线写数据函数;
*              
* Input:  id, I2C索引标识：I2C1_ID、I2C2_ID、I2C3_ID;
*         I2CAddr, I2C器件识别地址;
*         addr, 写数据的起始地址; 
*         *p, 写入数据存储的地址指针;
*         len,要写入数据长度;
*
* Output: none;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   如果I2C挂载器件是EEPROM则：
*         I2CAddr的bit15=0,支持24C01/02/04/08/16或地址是8位的器件; 
*         I2CAddr的bit15=1,支持24C32/64/128/256或地址是16位的器件;
************************************************************************************/
INT32S I2C_Write(INT8U id, INT16U I2CAddr, INT16U addr, INT8U *p, INT16U len);

/***********************************************************************************
* Function: I2C_Ctrl;
*
* Description: I2C命令控制;
* 
* Input:  id, I2C索引标识：I2C1_ID、I2C2_ID、I2C3_ID;
*         Cmd,  I2C控制命令, 如下定义：
*         CMD_I2C:       启用I2C外设或禁用I2C外设, Para是ENABLE或DISABLE	
*         CMD_I2C_RST:   复位I2C寄存器为初始状态, Para为0
*         CMD_I2C_CLOSE: 关闭I2C时钟,也就是关闭I2C功能,可以省电, Para为0
*
*         Para，I2C命令控制参数;
*
* Output: none;
*          		
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32S  I2C_Ctrl(INT8U id, INT8U Cmd, INT32U Para);

#endif
