/************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: net.h
* Project  : STM32F1XX/4XXϵ��ģ��������
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: ���ļ����������������ͷ�ļ�;
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
// �����ⲿͷ�ļ�
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

// NET_Ctrl()���ƺ��������
#define CMD_NET_SYNC       0   // ����ͬ������: ���������ߺ����ӣ�������Ӧ����, ��������״̬
#define CMD_NET_STATUS     1   // ��������״̬
#define CMD_NET_MACADDR    2   // ����MAC��ַ
#define CMD_NET_START      3   // �������繤��
#define CMD_NET_GETTXBUF   4   // �õ�����BUF��ַ

// ��������CMD_NET_SYNC��CMD_NET_STATUS, ��������״̬����
#define NET_PHY_LINK       0x0001   // ����Ӳ��(����)���ӱ�־
#define NET_PHY_10M        0x0002   // ����Ӳ��10M�������ӱ�־



//#define CMD_NET_INT        1   // �򿪺͹ر�DM9000A�ж�
//#define CMD_NET_HWRESET	   2   // ����оƬӲ����λ
//#define CMD_NET_HWINIT     4   // Ӳ����ʼ��

// LWIP����ģʽ
#define LWIP_SOCKET_CLIENT    0 // �ͻ���ģʽ
#define LWIP_SOCKET_SERVER    1 // ������ģʽ
#define LWIP_HTTP             2 // HTTP���ͷ�����

// ͨ������
#define LWIP_NETYPE_UDP       0 // UDPͨ��
#define LWIP_NETYPE_TCP       1 // TCPͨ��

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

// ������ƹܽŲ����ṹ 
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

// �����ʼ����������  
typedef struct
{	
	INT16U  Flag;               // ����������־
    NET_PIN Pin;                // ������ƹܽ�
   
    INT8U  RxBufNum;            // ���ջ�������
    INT16U MaxRxPacketSize;     // ���������ݰ���С
    ETH_DMADESCTypeDef *DMARxDscrTab; // ����������ָ��
    INT8U  *RxBuffer;                 // �������ݻ���ָ��
    
    INT8U  TxBufNum;            // ���ͻ�������
    INT16U MaxTxPacketSize;     // ��������ݰ���С
    ETH_DMADESCTypeDef *DMATxDscrTab; // ����������ָ��
    INT8U  *TxBuffer;                 // �������ݻ���ָ��
}NET_PARA;

/************************************************************************************
//
//                 �������������
//
*************************************************************************************/
/***********************************************************************************
* Function: NET_Init;
*
* Description: �����ʼ������;
*              
* Input:  *pPara, ��ʼ������;
*
* Output: none;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   none;
************************************************************************************/
INT32S NET_Init(NET_PARA *pPara);

/***********************************************************************************
* Function: NET_Write;
*
* Description: ������len�����ݷ��ͺ���;
*              
* Input:  len, �������ݳ���
*
* Output: none;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   none;
************************************************************************************/
INT32S NET_Write(INT32U len);

/***********************************************************************************
* Function: NET_Read;
*
* Description: �������ݺ���;
*              
* Input:  *p, ����������ʼ��ַ; len, �������ݳ���
*
* Output: none;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   none;
************************************************************************************/
INT32S NET_Read(INT32U *p, INT16U *len);

/***********************************************************************************
* Function: NET_Ctrl;
*
* Description: ������ƺ���;
*              
* Input:  Cmd, ��������: 
*              CMD_NET_SYNC�� ����ͬ������: ���������ߺ����ӣ�������Ӧ����, ��������״̬
*              CMD_NET_STATUS����������״̬
*              CMD_NET_SETMACADDR������MAC��ַ
*              CMD_NET_START���������繤��
*              CMD_NET_GETTXBUF���õ�����BUF��ַ
*         Para, �������, Ĭ��0 CMD_NET_GETTXBUF  
*
* Output: none;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   none;
************************************************************************************/
INT32S NET_Ctrl(INT8U Cmd, INT32U Para);
#endif


#if (MODULE_TYPE == STM32F103ZE)
// ������ļ�ʱ�뽫���涨��ر�
#ifdef EMB8612IA_TYPE
#include "pbuf.h"
#endif

// ������ļ�ʱ�뽫���涨���
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

// NET_Ctrl()���ƺ��������
#define CMD_NET_SYNC       0   // ����ͬ������: ���������ߺ����ӣ�������Ӧ����, ��������״̬
#define CMD_NET_STATUS     1   // ��������״̬
#define CMD_NET_MACADDR    2   // ����MAC��ַ
#define CMD_NET_START      3   // �������繤��
#define CMD_NET_GETTXBUF   4   // �õ�����BUF��ַ

#define CMD_NET_GETRXLEN   5   // �������ݳ���
#define CMD_NET_INT        6   // �򿪺͹ر�DM9000�ж�
//#define CMD_NET_RESET	   7   // ����оƬӲ����λ



// ��������CMD_NET_SYNC��CMD_NET_STATUS, ��������״̬����
#define NET_PHY_LINK       0x0001   // ����Ӳ��(����)���ӱ�־
#define NET_PHY_10M        0x0002   // ����Ӳ��10M�������ӱ�־


// LWIP����ģʽ
#define LWIP_SOCKET_CLIENT    0 // SOCKET���ͷ�����ģʽ
#define LWIP_SOCKET_SERVER    1 // SOCKET���ͷ�����ģʽ
#define LWIP_HTTP             2 // HTTP���ͷ�����

// ͨ������
#define LWIP_NETYPE_UDP       0 // UDPͨ��
#define LWIP_NETYPE_TCP       1 // TCPͨ��

// �������ش������
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
* LWIP�ӿں���
************************************************************************************/
extern INT32S NET_Init(void);
extern INT32S NET_Read(struct pbuf *p);
extern INT32S NET_Write(struct pbuf *p);

/***********************************************************************************
* Function: NET_Ctrl;
*
* Description: �������ƺ���;
*              
* Input:  Cmd, ��������: 
*              CMD_NET_ISLINK�� �ж�����Ӳ���Ƿ���������
*              CMD_NET_INT��    �򿪺͹ر�DM9000A�ж�
*              CMD_NET_HWRESET������оƬӲ����λ
*              CMD_NET_SETMACADDR������MAC��ַ
*              CMD_NET_HWINIT�� Ӳ����ʼ��
*         Para, �������, ���ж��趨�У�1:���ն�, 0�����ж�;
*
* Output: none;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   none;
************************************************************************************/
/***********************************************************************************
* Function: NET_Ctrl;
*
* Description: ������ƺ���;
*              
* Input:  Cmd, ��������: 
*              CMD_NET_SYNC�� ����ͬ������: ���������ߺ����ӣ�������Ӧ����, ��������״̬
*              CMD_NET_STATUS����������״̬
*              CMD_NET_SETMACADDR������MAC��ַ
*              CMD_NET_START���������繤��
*              CMD_NET_GETTXBUF���õ�����BUF��ַ
*         Para, �������, Ĭ��0 CMD_NET_GETTXBUF  
*
* Output: none;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   none;
************************************************************************************/

INT32U NET_Ctrl(INT8U Cmd, INT32U Para);


#endif





#endif

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
