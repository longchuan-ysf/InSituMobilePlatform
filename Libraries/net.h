/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: net.h
* Project  : STM32F1XX/4XX系列模块驱动库
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: 本文件是网络驱动库程序头文件;
*
* Others: none;
*
* Function List: 
*          1. INT32S NET_Init(NET_PARA *pPara);
*          2. INT32S NET_Write(INT32U len);
*          3. INT32S NET_Read(INT32U *p, INT16U *len);
*          4. INT32S NET_Ctrl(INT8U Cmd, INT32U Para);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/
#ifndef __NET_H
#define __NET_H

#include "const.h"
#include "config.h"

#if ((MODULE_CLASS == STM32F107XX)||(MODULE_CLASS == STM32F407XX))
/************************************************************************************/
// 引用外部头文件
/************************************************************************************/
typedef struct  
{
  INT32U   Status;                /*!< Status */
  INT32U   ControlBufferSize;     /*!< Control and Buffer1, Buffer2 lengths */
  INT32U   Buffer1Addr;           /*!< Buffer1 address pointer */
  INT32U   Buffer2NextDescAddr;   /*!< Buffer2 or next descriptor address pointer */

  INT32U   Rev[4];   /*!< Buffer2 or next descriptor address pointer */
}ETH_DMADESCTypeDef;
//#endif


//typedef struct  
//{
//  __IO uint32_t   Status;           /*!< Status */
//  
//  uint32_t   ControlBufferSize;     /*!< Control and Buffer1, Buffer2 lengths */
//  
//  uint32_t   Buffer1Addr;           /*!< Buffer1 address pointer */
//  
//  uint32_t   Buffer2NextDescAddr;   /*!< Buffer2 or next descriptor address pointer */
//  
//  /*!< Enhanced ETHERNET DMA PTP Descriptors */
//  uint32_t   ExtendedStatus;        /*!< Extended status for PTP receive descriptor */
//  
//  uint32_t   Reserved1;             /*!< Reserved */
//  
//  uint32_t   TimeStampLow;          /*!< Time Stamp Low value for transmit and receive */
//  
//  uint32_t   TimeStampHigh;         /*!< Time Stamp High value for transmit and receive */

//} ETH_DMADescTypeDef;

// NET_Ctrl()控制函数命令定义
#define CMD_NET_SYNC       0   // 网络同步操作: 检测网络断线和连接，并做相应处理, 返回网络状态
#define CMD_NET_STATUS     1   // 返回网络状态
#define CMD_NET_MACADDR    2   // 设置MAC地址
#define CMD_NET_START      3   // 启动网络工作
#define CMD_NET_GETTXBUF   4   // 得到发送BUF地址

// 当命令是CMD_NET_SYNC或CMD_NET_STATUS, 返回网络状态定义
#define NET_PHY_LINK       0x0001   // 网络硬件(网线)连接标志
#define NET_PHY_10M        0x0002   // 网络硬件10M网速连接标志



//#define CMD_NET_INT        1   // 打开和关闭DM9000A中断
//#define CMD_NET_HWRESET	   2   // 网络芯片硬件复位
//#define CMD_NET_HWINIT     4   // 硬件初始化

// LWIP工作模式
#define LWIP_SOCKET_CLIENT    0 // 客户端模式
#define LWIP_SOCKET_SERVER    1 // 服务器模式
#define LWIP_HTTP             2 // HTTP类型服务器

// 通信类型
#define LWIP_NETYPE_UDP       0 // UDP通信
#define LWIP_NETYPE_TCP       1 // TCP通信

// ETH DMA Interrupts 
#define ETH_DMA_IT_TST       0x20000000U  // Time-stamp trigger interrupt (on DMA) 
#define ETH_DMA_IT_PMT       0x10000000U  // PMT interrupt (on DMA) 
#define ETH_DMA_IT_MMC       0x08000000U  // MMC interrupt (on DMA) 
#define ETH_DMA_IT_NIS       0x00010000U  // Normal interrupt summary 
#define ETH_DMA_IT_AIS       0x00008000U  // Abnormal interrupt summary 
#define ETH_DMA_IT_ER        0x00004000U  // Early receive interrupt 
#define ETH_DMA_IT_FBE       0x00002000U  // Fatal bus error interrupt 
#define ETH_DMA_IT_ET        0x00000400U  // Early transmit interrupt 
#define ETH_DMA_IT_RWT       0x00000200U  // Receive watchdog timeout interrupt 
#define ETH_DMA_IT_RPS       0x00000100U  // Receive process stopped interrupt 
#define ETH_DMA_IT_RBU       0x00000080U  // Receive buffer unavailable interrupt 
#define ETH_DMA_IT_R         0x00000040U  // Receive interrupt 
#define ETH_DMA_IT_TU        0x00000020U  // Underflow interrupt 
#define ETH_DMA_IT_RO        0x00000010U  // Overflow interrupt 
#define ETH_DMA_IT_TJT       0x00000008U  // Transmit jabber timeout interrupt 
#define ETH_DMA_IT_TBU       0x00000004U  // Transmit buffer unavailable interrupt 
#define ETH_DMA_IT_TPS       0x00000002U  // Transmit process stopped interrupt 
#define ETH_DMA_IT_T         0x00000001U  // Transmit interrupt 

// 网络控制管脚参数结构 
typedef struct
{
    INT8U  MCO;
    INT8U  MDC;    
    INT8U  MDIO;     
    INT8U  REF;    
    INT8U  CRS_DV;  
    INT8U  RXD0;
    INT8U  RXD1;
    INT8U  TX_EN;
    INT8U  TXD0;
    INT8U  TXD1;
    INT8U  RESET;
}NET_PIN;

// 网络初始化参数定义  
typedef struct
{	
	INT16U  Flag;               // 工作参数标志
    NET_PIN Pin;                // 网络控制管脚
   
    INT8U  RxBufNum;            // 接收缓存数量
    INT16U MaxRxPacketSize;     // 最大接收数据包大小
    ETH_DMADESCTypeDef *DMARxDscrTab; // 接收描述符指针
    INT8U  *RxBuffer;                 // 接收数据缓存指针
    
    INT8U  TxBufNum;            // 发送缓存数量
    INT16U MaxTxPacketSize;     // 最大发送数据包大小
    ETH_DMADESCTypeDef *DMATxDscrTab; // 发送描述符指针
    INT8U  *TxBuffer;                 // 发送数据缓存指针
}NET_PARA;

/************************************************************************************
//
//                 网络驱动库程序
//
*************************************************************************************/
/***********************************************************************************
* Function: NET_Init;
*
* Description: 网络初始化函数;
*              
* Input:  *pPara, 初始化参数;
*
* Output: none;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32S NET_Init(NET_PARA *pPara);

/***********************************************************************************
* Function: NET_Write;
*
* Description: 将长度len的数据发送函数;
*              
* Input:  len, 发送数据长度
*
* Output: none;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32S NET_Write(INT32U len);

/***********************************************************************************
* Function: NET_Read;
*
* Description: 接收数据函数;
*              
* Input:  *p, 接收数据起始地址; len, 接收数据长度
*
* Output: none;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32S NET_Read(INT32U *p, INT16U *len);

/***********************************************************************************
* Function: NET_Ctrl;
*
* Description: 网络控制函数;
*              
* Input:  Cmd, 控制命令: 
*              CMD_NET_SYNC： 网络同步操作: 检测网络断线和连接，并做相应处理, 返回网络状态
*              CMD_NET_STATUS：返回网络状态
*              CMD_NET_SETMACADDR：设置MAC地址
*              CMD_NET_START：启动网络工作
*              CMD_NET_GETTXBUF：得到发送BUF地址
*         Para, 命令参数, 默认0 CMD_NET_GETTXBUF  
*
* Output: none;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32S NET_Ctrl(INT8U Cmd, INT32U Para);
#endif


#if (MODULE_TYPE == STM32F103ZE)
// 编译库文件时请将下面定义关闭
#ifdef EMB8612IA_TYPE
#include "pbuf.h"
#endif

// 编译库文件时请将下面定义打开
#ifdef STM32F103ZE_TYPE
struct pbuf 
{
  struct pbuf *next;
  void *payload;
  INT16U tot_len;
  INT16U len;
  INT8U type;
  INT8U flags;
  INT16U ref;
};
#endif

// NET_Ctrl()控制函数命令定义
#define CMD_NET_SYNC       0   // 网络同步操作: 检测网络断线和连接，并做相应处理, 返回网络状态
#define CMD_NET_STATUS     1   // 返回网络状态
#define CMD_NET_MACADDR    2   // 设置MAC地址
#define CMD_NET_START      3   // 启动网络工作
#define CMD_NET_GETTXBUF   4   // 得到发送BUF地址

#define CMD_NET_GETRXLEN   5   // 接收数据长度
#define CMD_NET_INT        6   // 打开和关闭DM9000中断
//#define CMD_NET_RESET	   7   // 网络芯片硬件复位



// 当命令是CMD_NET_SYNC或CMD_NET_STATUS, 返回网络状态定义
#define NET_PHY_LINK       0x0001   // 网络硬件(网线)连接标志
#define NET_PHY_10M        0x0002   // 网络硬件10M网速连接标志


// LWIP工作模式
#define LWIP_SOCKET_CLIENT    0 // SOCKET类型服务器模式
#define LWIP_SOCKET_SERVER    1 // SOCKET类型服务器模式
#define LWIP_HTTP             2 // HTTP类型服务器

// 通信类型
#define LWIP_NETYPE_UDP       0 // UDP通信
#define LWIP_NETYPE_TCP       1 // TCP通信

// 函数返回错误代码
#define ERR_OK          0    /* No error, everything OK. */
//#define ERR_MEM        -1    /* Out of memory error.     */
//#define ERR_BUF        -2    /* Buffer error.            */
#define ERR_TIMEOUT    -3    /* Timeout.                 */
//#define ERR_RTE        -4    /* Routing problem.         */
#define ERR_INPROGRESS -5    /* Operation in progress    */
//#define ERR_VAL        -6    /* Illegal value.           */
//#define ERR_WOULDBLOCK -7    /* Operation would block.   */
//#define ERR_USE        -8    /* Address in use.          */
//#define ERR_ISCONN     -9    /* Already connected.       */

#define ERR_IS_FATAL(e) ((e) < ERR_ISCONN)

#define ERR_ABRT       -10   /* Connection aborted.      */
#define ERR_RST        -11   /* Connection reset.        */
#define ERR_CLSD       -12   /* Connection closed.       */
#define ERR_CONN       -13   /* Not connected.           */

#define ERR_ARG        -14   /* Illegal argument.        */

#define ERR_IF         -15   /* Low-level netif error    */

/***********************************************************************************
* LWIP接口函数
************************************************************************************/
extern INT32S NET_Init(void);
extern INT32S NET_Read(struct pbuf *p);
extern INT32S NET_Write(struct pbuf *p);

/***********************************************************************************
* Function: NET_Ctrl;
*
* Description: 网卡控制函数;
*              
* Input:  Cmd, 控制命令: 
*              CMD_NET_ISLINK： 判断网洛硬件是否连接正常
*              CMD_NET_INT：    打开和关闭DM9000A中断
*              CMD_NET_HWRESET：网络芯片硬件复位
*              CMD_NET_SETMACADDR：设置MAC地址
*              CMD_NET_HWINIT： 硬件初始化
*         Para, 命令参数, 在中断设定中，1:开终端, 0：关中断;
*
* Output: none;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
/***********************************************************************************
* Function: NET_Ctrl;
*
* Description: 网络控制函数;
*              
* Input:  Cmd, 控制命令: 
*              CMD_NET_SYNC： 网络同步操作: 检测网络断线和连接，并做相应处理, 返回网络状态
*              CMD_NET_STATUS：返回网络状态
*              CMD_NET_SETMACADDR：设置MAC地址
*              CMD_NET_START：启动网络工作
*              CMD_NET_GETTXBUF：得到发送BUF地址
*         Para, 命令参数, 默认0 CMD_NET_GETTXBUF  
*
* Output: none;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/

INT32U NET_Ctrl(INT8U Cmd, INT32U Para);


#endif





#endif

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
