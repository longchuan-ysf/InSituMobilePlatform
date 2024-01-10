/************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: USBDevice.h
* Project  : STM32F1XX/4XXϵ��ģ��������
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: ���ļ���USB�豸�ӿ���������ͷ�ļ�;
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
// �����ⲿͷ�ļ�
/************************************************************************************/
#include "const.h"

/************************************************************************************/
// ������ȫ�ֱ�������
/************************************************************************************/
#define USB_ID    0  // USB ID����, Ĭ����0           


#define USB_DEVICE_MSC_MODE    0	    // USB�豸MSCģʽ
#define USB_DEVICE_CDC_MODE    1	    // USB�豸CDCģʽ�����⴮��ģʽ
#define USB_DEVICE_HID_MODE    2	    // USB�豸HIDģʽ����ʱδʵ��
#define USB_DEVICE_DFU_MODE    3        // USB�豸DFUģʽ����ʱδʵ��

// USB���ƹܽŲ����ṹ 
typedef struct
{
    INT8U  DM;    // USB DM�ܽŶ���
    INT8U  DP;    // USB DP�ܽŶ���
    INT8U  VBUS;  // VBUS���ܽŶ���
}USBD_PIN;

// USB Device�ж϶���
#define USBD_CONNECT_IT       0x0001   // USB�����ж�
#define USBD_DISCONNECT_IT    0x0002   // USB�Ͽ������ж�
#define USBD_RESET_IT         0x0004   // USB��λ�ж�
#define USBD_SETUP_IT         0x0008   // USB�豸�����ж�
#define USBD_RESUME_IT        0x0010   // USB�ָ����¿�ʼ�ж�
#define USBD_ISOIN_IT         0x0020   // USB ISOIN�ж�
#define USBD_ISOOUT_IT        0x0040   // USB ISOOUT�ж�
#define USBD_SUSPEND_IT       0x0080   // USB�����ж�
#define USBD_SOF_IT           0x0100   // USB SOF�ж�
#define USBD_DATAIN_IT        0x0200   // USB IN�˵�
#define USBD_DATAOUT_IT       0x0400   // USB OUT�˵�

#define USBD_SPIFLASH_READY   0x0800   // ��USB Mass Storageģʽ��, ѯ��SPI Flash�Ƿ�ռ��
#define USBD_SD_READY         0x1000   // ��USB Mass Storageģʽ��, ѯ��SD�Ƿ�ռ��
#define USBD_NFLASH_READY     0x2000   // ��USB Mass Storageģʽ��, ѯ��Nand Flash�Ƿ�ռ��



#define  SD_USB_FLAG            0x04000000  // SD���������USB(USB Mass Storage)ռ�ñ�־
#define  SPIFLASH_USB_FLAG      0x08000000  // SPI Flash�������USB(USB Mass Storage)ռ�ñ�־
#define  NFLASH_USB_FLAG        0x10000000  // Nand Flash�������USB(USB Mass Storage)ռ�ñ�־
#define  SD_FATFS_FLAG          0x20000000  // SD����FatFSռ�ñ�־
#define  SPIFLASH_FATFS_FLAG    0x40000000  // SPI Flash��FatFSռ�ñ�־
#define  NFLASH_FATFS_FLAG      0x80000000  // Nand Flash��FatFSռ�ñ�־



// Flag����
//#define USB_DEBUG_SMP       0x0001   // �����ӡ���ʹ��
//#define USB_DEBUG_AMP       0x0002   // ��ϸ��ӡ���ʹ��
#define USB_VCPRX_FULL_FLAG 0x0004   // USB�豸���⴮�ڽ��ջ�������־

// USB��ʼ����������  
typedef struct
{	
	INT16U Flag;       // ������־
	INT8U  Mode;       // USB��������ģʽ
	USBD_PIN Pin;      // USB���ƹܽ�
    
    INT8U  lun;        // MSC�������̷�ѡ��: SPIFLASH_DISK,SD_DISK,USB_DISK,NAND_DISK    
    // ���⴮�ڽ��ջ��涨��, ע���������÷��ͻ���
    INT8U *pRxBuf;     // �������ݻ���ָ��
    INT16U RxBufLen;   // ���ջ��泤��
}USBD_PARA;

/************************************************************************************/
// USBD_Ctrl()���ƺ��������
/************************************************************************************/
// USB�����
#define CMD_USBD_SYNC   	        0 	 // USBͬ������, ���USB�豸����, ������USB; ���USB�豸�γ����ر�USB�豸
#define CMD_USBD_STATUS             1 	 // ��ȡUSB�豸״̬(�Ƿ���USB�豸����): ����ERE_TRUE, USB�豸�Ѿ�����; ����ERR_FALSE, ��USB�豸����; 
#define CMD_USBD_GetCharsRxBuf	    2 	 // ��ȡ�������ݻ��������ݳ���
#define CMD_USBD_ClearRxBuffer      3    // ������ջ���
#define CMD_USBD_START   	        4 	 // USB����
#define CMD_USBD_STOP   	        5 	 // USBֹͣ


// ��������ΪCMD_USBD_SYNC��CMD_USBD_STATUSʱ����״̬����
#define USBD_WORK_OK                0x0001    // USBD��������
#define USBD_CONNECT                0x0002    // USBD�Ѿ����������ӳɹ�
#define USBD_VBUS_CONNECT           0x0004    // USBD�豸Ӳ�����ӳɹ�

/************************************************************************************
//
//                 USB�豸�ӿ�����������
//
*************************************************************************************/

/***********************************************************************************
* Function: USBD_Init;
*
* Description: USB�豸ģʽ��ʼ������;
*              
* Input:  id, USB����ֵ, Ĭ����0
*         USBD_PARA *pPara, USB��ʼ������
*
* Output: none;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   none;
************************************************************************************/
INT32S USBD_Init(INT8U id, USBD_PARA *pPara);

/***********************************************************************************
* Function: USBD_Read;
*																	 
* Description: ��ȡUSB���⴮�ڽ��յ�������;,
*           
* Input:  id, USB����ֵ, Ĭ����0
*         *p,  �������ݿ�ָ��; 
*         len, �������ݿ鳤��;
*      		  
* Output: *p, �������ݿ�ָ��; 
*          		
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*			   
* Note:   ������ݻ���������С�ڶ�ȡ����len, ��ú��������ȴ�, ֱ�ӷ���ERR_FALSE;
*         ��ȡ�ɹ���, ���ݻ������
************************************************************************************/
INT32S USBD_Read(INT8U id, INT8U *p, INT16U len);

/***********************************************************************************
* Function: USBD_Write;
*
* Description: USB���⴮�ڷ�������;
*           
* Input:  id, USB����ֵ, Ĭ����0
*         *p,   �������ݿ�ָ��; 
*         len,  �������ݿ鳤��;
*      		
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   �ú���������ɺ󷵻�, �����ʱ1�뻹û�����귵��ERR_FALSE;
************************************************************************************/
INT32S USBD_Write(INT8U id, INT8U *p, INT16U len);

/***********************************************************************************
* Function: USBD_Ctrl;
*
* Description: USB�豸���ƺ���;
*              
* Input:  id, USB����ֵ, Ĭ����0
*         Cmd,    USB��������:
*                 CMD_USBD_START:         USB��������
*                 CMD_USBD_STOP:          USBֹͣ����
*                 CMD_USBD_VBUS_CONNECT:  ��ȡUSBӲ������״̬(�Ƿ���USB�豸����): ����ERE_TRUE, USB�豸�Ѿ�����; ����ERR_FALSE, ��USB�豸����; 
*                 CMD_USBD_GetCharsRxBuf: ��ȡ�������ݻ��������ݳ���
*                 CMD_USBD_ClearRxBuffer: ������ջ���  
*         Para��  ������Ʋ���, Ĭ��0   
*
* Output: none;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   none;
************************************************************************************/
INT32S USBD_Ctrl(INT8U id, INT8U Cmd, INT32U Para);

#endif
