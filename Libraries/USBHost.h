/************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: USBHost.h
* Project  : STM32F1XX/4XXϵ��ģ��������
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: ���ļ���USB�����ӿ���������ͷ�ļ�(����FATFS�ļ�ϵͳU�̽ӿ�);
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
// �����ⲿͷ�ļ�
/************************************************************************************/

#include "const.h"

/************************************************************************************/
// ������ȫ�ֱ�������
/************************************************************************************/
#define USB_ID              0	    // USB����ID

#define USBHOST_MSC_MODE    0	    // USB����MSC(��U��)ģʽ
#define USBHOST_CDC_MODE    1	    // USB����CDCģʽ
#define USBHOST_HID_MODE    2	    // USB����HIDģʽ

// USB���ƹܽŲ����ṹ 
typedef struct
{
    INT8U  DM;    // USB DM�ܽŶ���
    INT8U  DP;    // USB DP�ܽŶ���
    INT8U  VBUS;  // VBUS���ܽŶ���
    INT8U  CPWR;  // ��Դ���ƹܽŶ���
}USBH_PIN;

// USB Host�жϱ�־����
#define USBH_CONNECT_IT       0x0001   // USB�����жϱ�־
#define USBH_DISCONNECT_IT    0x0002   // USB�Ͽ������жϱ�־
#define USBH_RESET_IT         0x0004   // USB��λ�жϱ�־
#define USBH_SETUP_IT         0x0008   // USB�豸�����жϱ�־
#define USBH_RESUME_IT        0x0010   // USB�ָ����¿�ʼ�жϱ�־
#define USBH_ISOIN_IT         0x0020   // USB ISOIN�жϱ�־
#define USBH_ISOOUT_IT        0x0040   // USB ISOOUT�жϱ�־
#define USBH_SUSPEND_IT       0x0080   // USB�����жϱ�־
#define USBH_SOF_IT           0x0100   // USB SOF�жϱ�־
#define USBH_DATAIN_IT        0x0200   // USB IN�˵��ж�
#define USBH_DATAOUT_IT       0x0400   // USB OUT�˵��ж�

// Flag����
//#define USB_DEBUG_SMP   0x0001   // �����ӡ���ʹ��
//#define USB_DEBUG_AMP   0x0002   // ��ϸ��ӡ���ʹ��

// USB��ʼ����������  
typedef struct
{	
	INT16U Flag;       // ������־
	INT8U  Mode;       // USB��������ģʽ
	USBH_PIN Pin;      // USB���ƹܽ�
}USBH_PARA;


// USBH_Ctrl()���ƺ��������
#define CMD_USBH_SYNC        	0 	 // USB����ͬ������
#define CMD_USBH_STATUS        	1 	 // ��ȡUSB����״̬
#define CMD_UDISK_STATUS      	2 	 // ��ȡU��״̬
#define CMD_UDISK_SECTOR_COUNT  3    // ��ȡU����������
#define CMD_UDISK_SECTOR_SIZE   4    // ��ȡU��������С

// ��������ΪCMD_USBH_SYNC��CMD_USBH_STATUSʱ����״̬����
#define USBH_WORK_OK                0x0001    // USBH��������
#define USBH_CONNECT                0x0002    // USBH�Ѿ����������ӳɹ�

//#define CMD_USB_START   	    0 	 // USB��������
//#define CMD_USB_STOP       	    1 	 // USBֹͣ����
/************************************************************************************
//
//                 USB�����ӿ�����������
//
*************************************************************************************/

/***********************************************************************************
* Function: USBH_Init;
*
* Description: USB������ʼ������;
*              
* Input:  id, USB����ֵ, Ĭ����0
*         USBH_PARA *pPara, USB��ʼ������
*
* Output: none;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   none;
************************************************************************************/
INT32S USBH_Init(INT8U id, USBH_PARA *pPara);

/***********************************************************************************
* Function: USBH_Ctrl;
*
* Description: USB�������ƺ���;
*              
* Input:  id, USB����ֵ, Ĭ����0
*         Cmd, ��������: 
*         CMD_USBH_SYNC:         USB����ͬ������
*         CMD_USBH_STATUS:       ��ȡUSB����״̬
*         CMD_UDISK_STATUS:      ��ȡU��״̬
*         CMD_UDISK_SECTOR_COUNT: ��ȡU����������
*         CMD_UDISK_SECTOR_SIZE:  ��ȡU��������С
*         Para, �������;   
*
* Output: none;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   none;
************************************************************************************/
INT32S USBH_Ctrl(INT8U id, INT8U Cmd, INT32U Para);

/***********************************************************************************
* Function: UDisk_Read;
*
* Description: FatFS�ӿڶ�ȡU���������ݺ���;
*              
* Input:  pdrv: �������������, Ĭ��0 
*         *p, ��ȡ���ݻ���ָ��;
*         sector, ��ȡ������ʼ���  
*         count, ��ȡ�������� (1..255)   
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
* Description: FatFS�ӿ�д��U���������ݺ���;
*              
* Input:  pdrv: �������������, Ĭ��0 
*         *p, д�����ݻ���ָ��;
*         sector, д��������ʼ���  
*         count, д���������� (1..255) 
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
