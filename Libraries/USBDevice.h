/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: USBDevice.h
* Project  : STM32F1XX/4XX系列模块驱动库
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: 本文件是USB设备接口驱动程序头文件;
*
* Others: none;
*
* Function List: 
*          1. INT32S USBD_Init(INT8U id, USBD_PARA *pPara);
*          2. INT32S USBD_Read(INT8U id, INT8U *p, INT16U len);
*          3. INT32S USBD_Write(INT8U id, INT8U *p, INT16U len);
*          4. INT32S USBD_Ctrl(INT8U id, INT8U Cmd, INT32U Para);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/
#ifndef  __USBDEVICE_H
#define  __USBDEVICE_H

/************************************************************************************/
// 引用外部头文件
/************************************************************************************/
#include "const.h"

/************************************************************************************/
// 常量及全局变量定义
/************************************************************************************/
#define USB_ID    0  // USB ID定义, 默认是0           


#define USB_DEVICE_MSC_MODE    0	    // USB设备MSC模式
#define USB_DEVICE_CDC_MODE    1	    // USB设备CDC模式，虚拟串口模式
#define USB_DEVICE_HID_MODE    2	    // USB设备HID模式，暂时未实现
#define USB_DEVICE_DFU_MODE    3        // USB设备DFU模式，暂时未实现

// USB控制管脚参数结构 
typedef struct
{
    INT8U  DM;    // USB DM管脚定义
    INT8U  DP;    // USB DP管脚定义
    INT8U  VBUS;  // VBUS监测管脚定义
}USBD_PIN;

// USB Device中断定义
#define USBD_CONNECT_IT       0x0001   // USB连接中断
#define USBD_DISCONNECT_IT    0x0002   // USB断开连接中断
#define USBD_RESET_IT         0x0004   // USB复位中断
#define USBD_SETUP_IT         0x0008   // USB设备设置中断
#define USBD_RESUME_IT        0x0010   // USB恢复重新开始中断
#define USBD_ISOIN_IT         0x0020   // USB ISOIN中断
#define USBD_ISOOUT_IT        0x0040   // USB ISOOUT中断
#define USBD_SUSPEND_IT       0x0080   // USB挂起中断
#define USBD_SOF_IT           0x0100   // USB SOF中断
#define USBD_DATAIN_IT        0x0200   // USB IN端点
#define USBD_DATAOUT_IT       0x0400   // USB OUT端点

#define USBD_SPIFLASH_READY   0x0800   // 在USB Mass Storage模式下, 询问SPI Flash是否被占用
#define USBD_SD_READY         0x1000   // 在USB Mass Storage模式下, 询问SD是否被占用
#define USBD_NFLASH_READY     0x2000   // 在USB Mass Storage模式下, 询问Nand Flash是否被占用



#define  SD_USB_FLAG            0x04000000  // SD卡被计算机USB(USB Mass Storage)占用标志
#define  SPIFLASH_USB_FLAG      0x08000000  // SPI Flash被计算机USB(USB Mass Storage)占用标志
#define  NFLASH_USB_FLAG        0x10000000  // Nand Flash被计算机USB(USB Mass Storage)占用标志
#define  SD_FATFS_FLAG          0x20000000  // SD卡被FatFS占用标志
#define  SPIFLASH_FATFS_FLAG    0x40000000  // SPI Flash被FatFS占用标志
#define  NFLASH_FATFS_FLAG      0x80000000  // Nand Flash被FatFS占用标志



// Flag定义
//#define USB_DEBUG_SMP       0x0001   // 精简打印输出使能
//#define USB_DEBUG_AMP       0x0002   // 详细打印输出使能
#define USB_VCPRX_FULL_FLAG 0x0004   // USB设备虚拟串口接收缓存满标志

// USB初始化参数定义  
typedef struct
{	
	INT16U Flag;       // 操作标志
	INT8U  Mode;       // USB主机操作模式
	USBD_PIN Pin;      // USB控制管脚
    
    INT8U  lun;        // MSC驱动器盘符选择: SPIFLASH_DISK,SD_DISK,USB_DISK,NAND_DISK    
    // 虚拟串口接收缓存定义, 注：不需设置发送缓存
    INT8U *pRxBuf;     // 接收数据缓存指针
    INT16U RxBufLen;   // 接收缓存长度
}USBD_PARA;

/************************************************************************************/
// USBD_Ctrl()控制函数命令定义
/************************************************************************************/
// USB命令定义
#define CMD_USBD_SYNC   	        0 	 // USB同步处理, 检测USB设备插入, 并启动USB; 监测USB设备拔出并关闭USB设备
#define CMD_USBD_STATUS             1 	 // 读取USB设备状态(是否有USB设备插入): 返回ERE_TRUE, USB设备已经连接; 返回ERR_FALSE, 无USB设备连接; 
#define CMD_USBD_GetCharsRxBuf	    2 	 // 读取接收数据缓存中数据长度
#define CMD_USBD_ClearRxBuffer      3    // 清除接收缓存
#define CMD_USBD_START   	        4 	 // USB启动
#define CMD_USBD_STOP   	        5 	 // USB停止


// 控制命令为CMD_USBD_SYNC和CMD_USBD_STATUS时返回状态定义
#define USBD_WORK_OK                0x0001    // USBD正常工作
#define USBD_CONNECT                0x0002    // USBD已经启动并连接成功
#define USBD_VBUS_CONNECT           0x0004    // USBD设备硬件连接成功

/************************************************************************************
//
//                 USB设备接口驱动程序函数
//
*************************************************************************************/

/***********************************************************************************
* Function: USBD_Init;
*
* Description: USB设备模式初始化函数;
*              
* Input:  id, USB索引值, 默认是0
*         USBD_PARA *pPara, USB初始化参数
*
* Output: none;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32S USBD_Init(INT8U id, USBD_PARA *pPara);

/***********************************************************************************
* Function: USBD_Read;
*																	 
* Description: 读取USB虚拟串口接收到的数据;,
*           
* Input:  id, USB索引值, 默认是0
*         *p,  接收数据块指针; 
*         len, 接收数据块长度;
*      		  
* Output: *p, 接收数据块指针; 
*          		
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*			   
* Note:   如果数据缓存中数据小于读取长度len, 则该函数并不等待, 直接返回ERR_FALSE;
*         读取成功后, 数据缓存清空
************************************************************************************/
INT32S USBD_Read(INT8U id, INT8U *p, INT16U len);

/***********************************************************************************
* Function: USBD_Write;
*
* Description: USB虚拟串口发送数据;
*           
* Input:  id, USB索引值, 默认是0
*         *p,   发送数据块指针; 
*         len,  发送数据块长度;
*      		
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   该函数发送完成后返回, 如果超时1秒还没发送完返回ERR_FALSE;
************************************************************************************/
INT32S USBD_Write(INT8U id, INT8U *p, INT16U len);

/***********************************************************************************
* Function: USBD_Ctrl;
*
* Description: USB设备控制函数;
*              
* Input:  id, USB索引值, 默认是0
*         Cmd,    USB控制命令:
*                 CMD_USBD_START:         USB启动运行
*                 CMD_USBD_STOP:          USB停止运行
*                 CMD_USBD_VBUS_CONNECT:  读取USB硬件连接状态(是否有USB设备插入): 返回ERE_TRUE, USB设备已经连接; 返回ERR_FALSE, 无USB设备连接; 
*                 CMD_USBD_GetCharsRxBuf: 读取接收数据缓存中数据长度
*                 CMD_USBD_ClearRxBuffer: 清除接收缓存  
*         Para，  命令控制参数, 默认0   
*
* Output: none;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32S USBD_Ctrl(INT8U id, INT8U Cmd, INT32U Para);

#endif
