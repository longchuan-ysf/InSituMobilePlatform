/************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: W25QXX.h
* Project  : STM32F1XX/4XXϵ��ģ��������
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: ���ļ�����W25QXXϵ��FLASH��д��������ͷ�ļ�;
*
* Others: none;
*
* Function List: 
*          1. INT32S W25QXX_Init(W25QXX_PARA *pPara);
*          2. INT32S W25QXX_Write(INT8U *p, INT32U addr, INT16U len);
*          3. INT32S W25QXX_WritePage(INT8U *p,  INT32U addr,  INT16U len);
*          4. INT32S W25QXX_WriteSector(INT8U *p, INT32U Sector, INT32U count);
*          5. INT32U W25QXX_Read(INT8U *p, INT32U addr, INT32U len);
*          6. INT32S W25QXX_ReadSector(INT8U *p, INT32U Sector, INT32U count);
*          7. INT32S W25QXX_Ctrl(INT8U Cmd, INT32U Para);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/
#ifndef __W25QXX_H
#define __W25QXX_H

/************************************************************************************/
// �����ⲿͷ�ļ�
/************************************************************************************/
#include "const.h"
/************************************************************************************/
// ��ʼ��������������
/************************************************************************************/
// SPI FLASH���Ͷ���
#define W25QXX     0
#define AT45DBXX   1

// оƬ�ͺŶ���, ���ɸ���
#define  W25Q80         0   // 1MB
#define  W25Q16         1   // 2MB
#define  W25Q32         2   // 4MB
#define  W25Q64         3   // 8MB, Ĭ��
#define  W25Q128        4   // 16MB

// ������ʶID 
#define  W25QXX_ID      0xEF
#define  GD25QXX_ID     0xC8

// Flag ��־
#define W25QXX_TYPE_FLAG     0x8000   // W25QXX���ͱ�־

//SPI Flash(W25QXX) ��ʼ����������  
typedef struct
{							 
	//INT8U  Type;           // оƬоƬ����, �̶�Ϊ0: W25QXX
    //INT8U  Model;          // оƬ�ͺ�
    INT16U Flag;           // ������־
    INT8U  SPI_ID;         // ѡ��SPI ID
	INT8U  CS_Pin;         // Ƭѡ�ܽ�
    INT16U SectorSize;	   // Flash������С(��λ���ֽ�) 
    INT32U SectorNum;	   // Flash�������� 
    INT32U FatFSSectorNum; // FatFS�ļ�ϵͳռ����������
    INT8U  *pBuf;          // FatFS�ӿں�������
}W25QXX_PARA;  

/************************************************************************************/
// ������ƺ�����������
/************************************************************************************/
// W25QXX_Ctrl() ���������
#define CMD_W25QXX_SYNC               0 	 // ͬ������(��д����), ֻ����FATFS��diskio.c�е���
#define CMD_W25QXX_INIT               1 	 // W25QXX��ʼ��, ֻ����FATFS��diskio.c�е���
#define CMD_W25QXX_STATUS             2 	 // ��ȡW25QXX״̬,ֻ����FATFS��diskio.c�е���

#define CMD_W25QXX_SECTOR_ERASE       3 	 // ��������
#define CMD_W25QXX_BLOCK32KB_ERASE    4 	 // ����32KB��
#define CMD_W25QXX_BLOCK64KB_ERASE    5 	 // ����64KB��
#define CMD_W25QXX_CHIP_ERASE         6 	 // ��������оƬ
#define CMD_W25QXX_RDID               7 	 // ��ȡ���̼�����ID
#define CMD_W25QXX_POWERDOWN          8 	 // �������ģʽ
#define CMD_W25QXX_WAKEUP             9 	 // ����

/************************************************************************************
//
//                 W25QXXϵ��FLASH��д�����⺯��
//
*************************************************************************************/

/***********************************************************************************
* Function: W25QXX_Init;
*
* Description: W25QXX��ʼ������;
*              
* Input:  *pPara, ��ʼ������ָ��;
*
* Output: none;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   ������ش�����������Լ���ѡ���SPI�����Ƿ��ʼ��;
************************************************************************************/
INT32S W25QXX_Init(W25QXX_PARA *pPara);

/***********************************************************************************
* Function: W25QXX_Write;
*
* Description: д��FLASHһ������;
*              
* Input:  *p, Ҫд�����ݵ�ָ��; addr, д��flash���ݵ���ʼ��ַ;  len,Ҫд�����ݵĳ���;
*         addr��ַ��Χ: W25Q80, 0x000000~0x000fffff; W25Q16, 0x000000~0x001fffff;
*                       W25Q32, 0x000000~0x003fffff; W25Q64, 0x000000~0x007fffff;
*                       W25Q128, 0x000000~0x00ffffff; 
*
* Output: none;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   ������������ַ��Χ��Χ���,���Բ�Ҫ������Χ;
************************************************************************************/
INT32S W25QXX_Write(INT8U *p, INT32U addr, INT16U len);

/***********************************************************************************
* Function: W25QXX_WritePage;
*
* Description: ��ҳд��FLASH����;
*              
* Input:  *p, Ҫд�����ݵ�ָ��; addr, ÿҳ����ʼ��ʼ��ַ;  len, Ҫд�����ݳ���;
*
* Output: none;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   addr������256��������, len��Χ������1-256;
************************************************************************************/
INT32S W25QXX_WritePage(INT8U *p,  INT32U addr,  INT16U len);

/***********************************************************************************
* Function: W25QXX_Read;
*
* Description: ��ȡFLASH������;
*              
* Input:  *p, Ҫ��ȡ���ݴ洢��ָ��; addr, �ڲ�FLASH��ʼ��ַ;  len,Ҫ��ȡ���ݵĳ���;
*         addr��ַ��Χ: W25Q80, 0x000000~0x000fffff; W25Q16, 0x000000~0x001fffff;
*                       W25Q32, 0x000000~0x003fffff; W25Q64, 0x000000~0x007fffff;
*                       W25Q128, 0x000000~0x00ffffff; 
*
* Output: *p, ���ݴ洢��ָ��;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   ������������ַ��Χ��Χ���,���Բ�Ҫ������Χ;
************************************************************************************/
INT32U W25QXX_Read(INT8U *p, INT32U addr, INT32U len);

/***********************************************************************************
* Function: W25QXX_WriteSector;
*
* Description: ������д��FLASH����;
*              
* Input:  *p, Ҫд�����ݵ�ָ��; sector,д��flash���ݵ���ʼ�������;  count, Ҫд����������;
*
* Output: none;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   ������СΪ512�ֽ�, ������ֻ��Ӧ����FATFS��diskio.c�е���;
************************************************************************************/
INT32S W25QXX_WriteSector(INT8U *p, INT32U sector, INT32U count);

/***********************************************************************************
* Function: W25QXX_ReadSector;
*
* Description: ��������ȡFLASH������;
*              
* Input:  *p, Ҫ��ȡ���ݴ洢��ָ��; sector,��ȡFlash���ݵ���ʼ����;  count, Ҫ��ȡ��������;
*
* Output: *p, ���ݴ洢��ָ��;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   ������СΪ512�ֽ�, ������ֻ��Ӧ����FATFS��diskio.c�е���;
************************************************************************************/
INT32S W25QXX_ReadSector(INT8U *p, INT32U sector, INT32U count);

/***********************************************************************************
* Function: W25QXX_Ctrl;
*
* Description: W25QXX�������;
* 
* Input:  Cmd,  W25QXX�������
*                CMD_W25QXX_SYNC:            ͬ������(��д����), ֻ����FATFS��diskio.c�е���
*                CMD_W25QXX_INIT: 	         W25QXX��ʼ��, ֻ����FATFS��diskio.c�е���
*                CMD_W25QXX_STATUS:          ��ȡW25QXX״̬,ֻ����FATFS��diskio.c�е���
*                CMD_W25QXX_SECTOR_ERASE:    ��������; Para, ������� 
*                CMD_W25QXX_BLOCK32KB_ERASE: ����32KB��; Para, 32KB����� 
*                CMD_W25QXX_BLOCK64KB_ERASE: ����64KB��; Para, 64KB�����
*                CMD_W25QXX_CHIP_ERASE:      ��������оƬ; Para, Ϊ0
*                CMD_W25QXX_RDID:            ��ȡ���̼�����ID; Para, Ϊ0
*                CMD_W25QXX_POWERDOWN:       �������ģʽ; Para, Ϊ0
*                CMD_W25QXX_WAKEUP:          ����; Para, Ϊ0	
*
*         Para��W25QXX������Ʋ���, �ο�����˵��
*
* Output: none;
*          		
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������; �з��ص��������Ӧ����;
*
* Note:   none;
************************************************************************************/
INT32S W25QXX_Ctrl(INT8U Cmd, INT32U Para);

#endif 

