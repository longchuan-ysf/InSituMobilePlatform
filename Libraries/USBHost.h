/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: USBHost.h
* Project  : STM32F1XX/4XX系列模块驱动库
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: 本文件是USB主机接口驱动程序头文件(包括FATFS文件系统U盘接口);
*
* Others: none;
*
* Function List: 
*          1. INT32S USBH_Init(INT8U id, USBH_PARA *pPara);
*          2. INT32S USBH_Ctrl(INT8U id, INT8U Cmd, INT32U Para);
*          3. INT8U UDisk_Read(INT8U pdrv, INT8U *p, INT32U sector, INT8U count);
*          4. INT8U UDisk_Write(INT8U pdrv, INT8U *p, INT32U sector, INT8U count);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/
#ifndef  __USBHOST_H
#define  __USBHOST_H

/************************************************************************************/
// 引用外部头文件
/************************************************************************************/

#include "const.h"

/************************************************************************************/
// 常量及全局变量定义
/************************************************************************************/
#define USB_ID              0	    // USB主机ID

#define USBHOST_MSC_MODE    0	    // USB主机MSC(接U盘)模式
#define USBHOST_CDC_MODE    1	    // USB主机CDC模式
#define USBHOST_HID_MODE    2	    // USB主机HID模式

// USB控制管脚参数结构 
typedef struct
{
    INT8U  DM;    // USB DM管脚定义
    INT8U  DP;    // USB DP管脚定义
    INT8U  VBUS;  // VBUS监测管脚定义
    INT8U  CPWR;  // 电源控制管脚定义
}USBH_PIN;

// USB Host中断标志定义
#define USBH_CONNECT_IT       0x0001   // USB连接中断标志
#define USBH_DISCONNECT_IT    0x0002   // USB断开连接中断标志
#define USBH_RESET_IT         0x0004   // USB复位中断标志
#define USBH_SETUP_IT         0x0008   // USB设备设置中断标志
#define USBH_RESUME_IT        0x0010   // USB恢复重新开始中断标志
#define USBH_ISOIN_IT         0x0020   // USB ISOIN中断标志
#define USBH_ISOOUT_IT        0x0040   // USB ISOOUT中断标志
#define USBH_SUSPEND_IT       0x0080   // USB挂起中断标志
#define USBH_SOF_IT           0x0100   // USB SOF中断标志
#define USBH_DATAIN_IT        0x0200   // USB IN端点中断
#define USBH_DATAOUT_IT       0x0400   // USB OUT端点中断

// Flag定义
//#define USB_DEBUG_SMP   0x0001   // 精简打印输出使能
//#define USB_DEBUG_AMP   0x0002   // 详细打印输出使能

// USB初始化参数定义  
typedef struct
{	
	INT16U Flag;       // 操作标志
	INT8U  Mode;       // USB主机操作模式
	USBH_PIN Pin;      // USB控制管脚
}USBH_PARA;


// USBH_Ctrl()控制函数命令定义
#define CMD_USBH_SYNC        	0 	 // USB主机同步处理
#define CMD_USBH_STATUS        	1 	 // 读取USB主机状态
#define CMD_UDISK_STATUS      	2 	 // 读取U盘状态
#define CMD_UDISK_SECTOR_COUNT  3    // 读取U盘扇区数量
#define CMD_UDISK_SECTOR_SIZE   4    // 读取U盘扇区大小

// 控制命令为CMD_USBH_SYNC和CMD_USBH_STATUS时返回状态定义
#define USBH_WORK_OK                0x0001    // USBH正常工作
#define USBH_CONNECT                0x0002    // USBH已经启动并连接成功

//#define CMD_USB_START   	    0 	 // USB启动运行
//#define CMD_USB_STOP       	    1 	 // USB停止运行
/************************************************************************************
//
//                 USB主机接口驱动程序函数
//
*************************************************************************************/

/***********************************************************************************
* Function: USBH_Init;
*
* Description: USB主机初始化函数;
*              
* Input:  id, USB索引值, 默认是0
*         USBH_PARA *pPara, USB初始化参数
*
* Output: none;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32S USBH_Init(INT8U id, USBH_PARA *pPara);

/***********************************************************************************
* Function: USBH_Ctrl;
*
* Description: USB主机控制函数;
*              
* Input:  id, USB索引值, 默认是0
*         Cmd, 控制命令: 
*         CMD_USBH_SYNC:         USB主机同步处理
*         CMD_USBH_STATUS:       读取USB主机状态
*         CMD_UDISK_STATUS:      读取U盘状态
*         CMD_UDISK_SECTOR_COUNT: 读取U盘扇区数量
*         CMD_UDISK_SECTOR_SIZE:  读取U盘扇区大小
*         Para, 命令参数;   
*
* Output: none;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32S USBH_Ctrl(INT8U id, INT8U Cmd, INT32U Para);

/***********************************************************************************
* Function: UDisk_Read;
*
* Description: FatFS接口读取U盘扇区数据函数;
*              
* Input:  pdrv: 物理驱动器序号, 默认0 
*         *p, 读取数据缓存指针;
*         sector, 读取扇区起始序号  
*         count, 读取扇区数量 (1..255)   
*
* Output: none;
*
* Return: RES_OK,     Successful 
*   	  RES_ERROR,  R/W Error 
*	      RES_WRPRT,  Write Protected 
*	      RES_NOTRDY, Not Ready 
*	      RES_PARERR, Invalid Parameter
*
* Note:   none;
************************************************************************************/
INT8U UDisk_Read(INT8U pdrv, INT8U *p, INT32U sector, INT8U count);

/***********************************************************************************
* Function: UDisk_Write;
*
* Description: FatFS接口写入U盘扇区数据函数;
*              
* Input:  pdrv: 物理驱动器序号, 默认0 
*         *p, 写入数据缓存指针;
*         sector, 写入扇区起始序号  
*         count, 写入扇区数量 (1..255) 
*
* Output: none;
*
* Return: RES_OK,     Successful 
*   	  RES_ERROR,  R/W Error 
*	      RES_WRPRT,  Write Protected 
*	      RES_NOTRDY, Not Ready 
*	      RES_PARERR, Invalid Parameter
*
* Note:   none;
************************************************************************************/
INT8U UDisk_Write(INT8U pdrv, INT8U *p, INT32U sector, INT8U count);

#endif
