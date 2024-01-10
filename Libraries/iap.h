/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: IAP.h
* Project  : STM32F1XX/4XX系列模块驱动库
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: 本文件负责IAP更新固件驱动程序头文件
*
* Others: none;
*
* Function List:
*          1. INT32S IAP_Init(IAP_PARA *pPara);
*          2. INT32S IAP_Write(INT8U id, INT8U *p, INT32U addr, INT32U len);
*          3. INT32S IAP_Ctrl(INT8U id, INT8U Cmd, INT32U Para);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/
/*************************************************************************************
关于IAP固件更新中FALSH区域划分: 

1. 芯片STM32F107VC(总页数128, 256KB) FLASH分区表:
-------------------------------------------------------------------------
|    分区     | 页大小 |  起始页 |  总页数   |        功能              |  
-------------------------------------------------------------------------
|    BOOT区   |  2048  |    0    | 8(16KB)   | 运行IAP启动程序          |
-------------------------------------------------------------------------
|    A区      |  2048  |    8    | 60(120KB) | 用于运行小于120KB应用程序|
-------------------------------------------------------------------------
|    B区      |  2048  |    68   | 60(120KB) | 用于存储小于120KB新固件  |
-------------------------------------------------------------------------
|    A+B区    |  2048  |    8    | 120(240KB)| 用于运行小于240KB应用程序|
-------------------------------------------------------------------------
| C区(W25QXX) |  4096  | 2048-60 | 60(240KB) | 用于存储小于240KB新固件  |
-------------------------------------------------------------------------
|C区(AT45DBXX)|  512   | 4096-480| 480(240KB)| 用于存储小于240KB新固件  |
-------------------------------------------------------------------------

2. 芯片STM32F103VE/STM32F103ZE(总页数256, 512KB) FLASH分区表:
--------------------------------------------------------------------------
|    分区     | 页大小 |  起始页  |  总页数   |        功能              |  
--------------------------------------------------------------------------
|    BOOT区   |  2048  |    0     | 8(16KB)   | 运行IAP启动程序          |
--------------------------------------------------------------------------
|    A区      |  2048  |    8     | 124(248KB)| 用于运行小于248KB应用程序|
--------------------------------------------------------------------------
|    B区      |  2048  |   132    | 124(248KB)| 用于存储小于248KB新固件  |
--------------------------------------------------------------------------
|    A+B区    |  2048  |    8     | 248(496KB)| 用于运行小于496KB应用程序|
--------------------------------------------------------------------------
| C区(W25QXX) |  4096  | 2048-124 | 124(496KB)| 用于存储小于496KB新固件  |
--------------------------------------------------------------------------
|C区(AT45DBXX)|  512   | 4096-992 | 992(496KB)| 用于存储小于496KB新固件  |
--------------------------------------------------------------------------

3. 芯片STM32F407VE/ZE, STM32F417VE/ZE(总扇区数8, 512KB) FLASH分区表:
---------------------------------------------------------------------------------------
|    分区     |  包含扇区(扇区大小)              | 总空间 |        功能               |  
---------------------------------------------------------------------------------------
|    BOOT区   |  0(16KB)                         |  16KB  | 运行IAP启动程序           |
---------------------------------------------------------------------------------------
|    A区      | 1/2/3(16KB), 4(64KB), 5(128KB)   | 240KB  | 用于运行小于240KB应用程序 |
---------------------------------------------------------------------------------------
|    B区      |  6/7(128KB)                      | 240KB  | 用于存储小于240KB新固件   |
---------------------------------------------------------------------------------------
|    A+B区    | 1/2/3(16KB),4(64KB),5/6/7(128KB) | 496KB  | 用于运行小于496KB应用程序 |
---------------------------------------------------------------------------------------
|    分区     |   页大小    |  起始页         |   总页数  |        功能               |  
---------------------------------------------------------------------------------------
| C区(W25QXX) |    4096     | 2048-124        | 124(496KB)| 用于存储小于496KB新固件   |
---------------------------------------------------------------------------------------

4. 芯片STM32F407VG/ZG, STM32F417VG/ZG(总扇区数12, 1024KB) FLASH分区表:
----------------------------------------------------------------------------------------
|    分区     |  包含扇区(扇区大小)               | 总空间 |        功能               |  
----------------------------------------------------------------------------------------
|    BOOT区   |  0(16KB)                          |  16KB  | 运行IAP启动程序           |
----------------------------------------------------------------------------------------
|    A区      | 1/2/3(16KB), 4(64KB), 5/6/7(128KB)|  496KB | 用于运行小于496KB应用程序 |
----------------------------------------------------------------------------------------
|    B区      |  8~11(128KB)                      |  496KB | 用于存储小于496KB新固件   |
----------------------------------------------------------------------------------------
|    A+B区    | 1/2/3(16KB),4(64KB),5~11(128KB)   | 1008KB | 用于运行小于1008KB应用程序|
----------------------------------------------------------------------------------------
|    分区     |   页大小    |  起始页         |   总页数  |        功能                |  
----------------------------------------------------------------------------------------
| C区(W25QXX) |    4096     | 2048-252        | 252(1008KB)| 用于存储小于1008KB新固件    |
----------------------------------------------------------------------------------------


5. 对于新固件小于B区容量时, 优先用B区存储新固件(当然也可以选择C区), 在配置文件中IAP_FLASH配置为1即可;

6. 对于新固件大于B区容量时, 必须用C区存储新固件, 在配置文件中IAP_FLASH配置为3即可;

7. 应用程序用串口或网口下载新固件并根据3、4项存储到B区或C区, 重新启动后, IAP启动程序会将B区固件读出并
   写入A区(或将C区固件读出并写入A+B区); 写入完成跳转到A区或A+B运行新固件;

*************************************************************************************/
#ifndef __IAP_H 
#define __IAP_H 

// 引用外部头文件
#include "const.h"  

/************************************************************************************/
// 常量及全局变量定义
/************************************************************************************/
// 定义FLASH划分区域标识
#define IAP_A_ID           0  // A区, STM32Fxxx芯片上FLASH  
#define IAP_B_ID           1  // B区, STM32Fxxx芯片上FLASH  
#define IAP_AB_ID          2  // A+B区, STM32Fxxx芯片上FLASH  
#define IAP_C_ID           3  // C区, SPI FLASH

// FLASH总页数
#define STM32F107XC_PAGENUM   128 // STM32F107VC芯片总页数, 共256KB
#define STM32F103XE_PAGENUM   256 // STM32F103VE/ZE芯片总页数, 共512KB
#define STM32F407XE_PAGENUM   248 // STM32F407VE/ZE芯片总页数, 共496KB
#define STM32F417XE_PAGENUM   248 // STM32F417VE/ZE芯片总页数, 共496KB
#define STM32F407XG_PAGENUM   504 // STM32F407VG/ZG芯片总页数, 共1008KB
#define STM32F417XG_PAGENUM   504 // STM32F417VG/ZG芯片总页数, 共1008KB

#define IAP_AB_PAGESIZE       2048    // A,B,AB区(STM32F107VC/103VE/ZE芯片)FLASH页大小 
#define IAP_APP_STARTPAGE     8       // APP程序起始页 

// AT45DB161
#define AT45DBXX_PAGENUM      4096   // AT45DBXX总页数, 每页512字节 
#define AT45DBXX_PAGESIZE     512    // AT45DBXX页大小 

// W25Q64
#define W25QXX_PAGENUM        2048   // W25QXX总页数, 每页512字节 
#define W25QXX_PAGESIZE       4096   // W25QXX页大小 

#if (MODULE_TYPE == STM32F107VC)
    #define IAP_APP_PAGENUM    (STM32F107XC_PAGENUM - IAP_APP_STARTPAGE)
#elif ((MODULE_TYPE == STM32F103VE)||(MODULE_TYPE == STM32F103ZE))
    #define IAP_APP_PAGENUM    (STM32F103XE_PAGENUM - IAP_APP_STARTPAGE) 
#elif ((MODULE_TYPE == STM32F407VE)||(MODULE_TYPE == STM32F407ZE))
    #define IAP_APP_PAGENUM    (STM32F407XE_PAGENUM - IAP_APP_STARTPAGE)     
#elif ((MODULE_TYPE == STM32F417VE)||(MODULE_TYPE == STM32F417ZE))
    #define IAP_APP_PAGENUM    (STM32F417XE_PAGENUM - IAP_APP_STARTPAGE)     
#elif ((MODULE_TYPE == STM32F407VG)||(MODULE_TYPE == STM32F407ZG))
    #define IAP_APP_PAGENUM    (STM32F407XG_PAGENUM - IAP_APP_STARTPAGE)  
#elif ((MODULE_TYPE == STM32F417VG)||(MODULE_TYPE == STM32F417ZG))
    #define IAP_APP_PAGENUM    (STM32F417XG_PAGENUM - IAP_APP_STARTPAGE)  
#endif

// A区定义
#define IAP_A_STARTPAGE  IAP_APP_STARTPAGE      // A区APP程序起始页  
#define IAP_A_PAGENUM    (IAP_APP_PAGENUM/2)    // A区APP程序总页数  

// B区定义
#define IAP_B_STARTPAGE  (IAP_A_STARTPAGE+IAP_A_PAGENUM)    // B区更新固件起始页  
#define IAP_B_PAGENUM    (IAP_APP_PAGENUM/2)                // B区更新固件总页数 

//  A+B区定义
#define IAP_AB_STARTPAGE IAP_APP_STARTPAGE      // AB区APP程序起始页  
#define IAP_AB_PAGENUM   IAP_APP_PAGENUM        // AB区APP程序总页数 

// C区(AT45DBXX)定义
#define IAP_C_AT45DBXX_PAGENUM    (IAP_APP_PAGENUM*4)                       // C区更新固件总页数, 每页512字节 
#define IAP_C_AT45DBXX_STARTPAGE  (AT45DBXX_PAGENUM-IAP_C_AT45DBXX_PAGENUM) // C区更新固件起始页  
#define IAP_C_AT45DBXX_PAGESIZE   AT45DBXX_PAGESIZE                         // C区更新固件页大小 

// C区(W25QXX)定义
#define IAP_C_W25QXX_PAGENUM    (IAP_APP_PAGENUM/2)                     // C区更新固件总页数, 每页4096字节
#define IAP_C_W25QXX_STARTPAGE  (W25QXX_PAGENUM-IAP_C_W25QXX_PAGENUM)   // C区更新固件起始页  
#define IAP_C_W25QXX_PAGESIZE   W25QXX_PAGESIZE                         // C区更新固件页大小 

typedef struct
{
    INT16U  StartPage;  // 起始页
    INT16U  PageNum;    // 总页数
}AREA_DEF;

// Flag标志定义
#define IAP_YMODEM_FLAG      0x0001     // 启动时支持超级终端Ymodem协议 
#define IAP_BA_UPDATE_FLAG   0x0002     // 启动更新固件标志: 将B区固件拷贝到A区 
#define IAP_CAB_UPDATE_FLAG  0x0004     // 启动更新固件标志: 将C区固件拷贝到AB区
#define IAP_SPIFLASH_UPDATE_FLAG 0x0008 // 启动更新固件标志: 将SPI FLASH文件固件拷贝到AB区
#define IAP_SD_UPDATE_FLAG   0x0010     // 启动更新固件标志: 将SD卡文件固件拷贝到AB区(IAP启动检测SD卡文件, 更新固件, 暂时未实现 )
#define IAP_ZDY_FLAG         0x0020     // 启动时支持自定义协议更新固件(暂时未实现)
#define IAP_BOOTPIN_FLAG     0x0040     // IAP启动检测IO管脚标志, IO管脚低电平应用IAP下载固件
#define IAP_UART_REMAP1_FLAG 0x0080     // IAP串口管脚REMAP1标志 
#define IAP_UART_REMAP2_FLAG 0x0100     // IAP串口管脚REMAP2标志 
#define IAP_HSE_FLAG         0x0200     // 使用外部高速晶振作为BOOT程序时钟标志
#define IAP_DEBUG_FLAG       0x0400     // BOOT程序调试输出标志


#define IAP_INIT_FLAG        0x8000  // 初始化完成标志

typedef struct
{
      INT16U  Flag;       // 标志位
      INT32U  HSEClk;     // 外部时钟晶振频率
      INT16U  Moduel;     // 模块类型
	  INT16U  UartID;     // 串口ID, Debug信息输出串口选择   
      INT32U  Baud;       // 串口波特率	
      INT16U  ABPageSize; // A/B/AB区页大小
      INT16U  CPageSize;  // C区页大小  
      AREA_DEF  Area[4];  // 区参数
      INT16U  BootPin;    // 启动检测管脚
      INT8U   FileName[12]; // 启动文件名称, 采用8.3文件定义  
}IAP_PARA;

// IAP_Ctrl()函数指令定义
#define CMD_IAP_UNLOCK         0   // FLASH解锁
#define CMD_IAP_LOCK           1   // FLASH加锁
#define CMD_IAP_ERASE          2   // FLASH擦除
#define CMD_IAP_UPDATE         3   // 更新启动参数(id为IAP_B_ID: B区拷贝到A区并启动; id为IAP_C_ID: C区拷贝到A+B区并启动;)

/************************************************************************************
//
//                 常用函数子程序
//
*************************************************************************************/
/***********************************************************************************
* Function: IAP_Init;
*
* Description: IAP初始化函数
* 
* Input:  *pPara, 初始化参数指针;
*
* Output: none;
*          		
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32S IAP_Init(IAP_PARA *pPara);

/***********************************************************************************
* Function: IAP_Write;
*
* Description: IAP固件数据写入函数;
* 
* Input:  id, 操作FLASH区域标志: 只能是IAP_B_ID(B区)或IAP_C_ID(C区), 其它无效
*         *p, 要写入固件数据的指针; addr, 写入固件数据的起始地址;  len,要写入固件数据的长度;
*           
* Output: none;
*          		
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32S IAP_Write(INT8U id, INT8U *p, INT32U addr, INT32U len);
    
/***********************************************************************************
* Function: IAP_Ctrl;
*
* Description: IAP控制函数;
* 
* Input:  id, 操作FLASH区域标志: 只能是IAP_B_ID(B区)或IAP_C_ID(C区), 其它无效
*         Cmd: 控制命令: CMD_IAP_UNLOCK, FLASH解锁
*                        CMD_IAP_LOCK, FLASH加锁
*                        CMD_IAP_ERASE, FLASH擦除
*                        CMD_IAP_UPDATE, 更新启动参数(id为IAP_B_ID: B区拷贝到A区并启动; id为IAP_C_ID: C区拷贝到A+B区并启动)
*         Para: 控制参数, 当Cmd是CMD_IAP_UPDATE, 该参数为更新固件大小; Cmd是其它值设置为0;
*           
* Output: none;
*          		
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32S IAP_Ctrl(INT8U id, INT8U Cmd, INT32U Para);

#endif
/***********************************************************************************/
// 文件结束
/***********************************************************************************/
