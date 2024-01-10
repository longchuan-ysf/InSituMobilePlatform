/************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: TastFile.c
* Project  : STM32F1XX/4XXϵ��ģ�����
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.00
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: ���ļ������ļ�ϵͳ��д������;
*
* Others: none;
*
* Function List:
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/

/************************************************************************************/
// ����˵��
/************************************************************************************/
/*
1. SPI FLASH(W25Q64)�ļ���д����: 
   (1). SPI FALSH(W25Q64��AT45DB161)оƬ�ں���ģ����, ռ��SPI1����
   
   (2). ����˵��: �������ļ���SPIFLASH_EN����Ϊ1, SPIFLASH_MODE����Ϊ1, ����Ĭ�ϲ����޸�;
   
   (3). SPI FLASH(W25Q64)�ļ���д����: ��APP_Init.c�е���SPIFlash_APPInit()�����ȳ�ʼ��; 
   
   (4). �ȵ���disk_status(SPIFLASH_DISK)��ȡ״̬, �ٵ���SPIFLASH_FileTest()�����ļ���д����, ͨ�����ڵ������
        �۲���Խ��; ÿ���ϵ���߸�λֻ����һ��;
        
2. SD���ļ���д����: 
   (1). SD������SPI�������, ռ��SPI1����;
   
   (2). ����˵��: �������ļ���SDCARD_EN����Ϊ1;
   
   (3). ��APP_Init.c�е���SD_APPInit()��ʼ��;
   
   (4). �ȵ���SD_Ctrl(CMD_SD_STATUS,  0)��ȡ״̬, �ٵ���SD_Test()�����ļ���д����, ͨ�����ڵ������
        �۲���Խ��; ����ͨ�����SD������;
        
3. U���ļ���д����: 
   (1). ����˵��: �������ļ���USB_HOST_EN����Ϊ1, UDISK_EN����Ϊ1;
   
   (2). ��APP_Init.c�е���USBH_APPInit()�����ȳ�ʼ��;
   
   (3). �ȵ���USBH_Ctrl(CMD_USBH_SYNC, 0), ����U��״̬, �ٵ���UDISK_test()�����ļ���д����;
        
   (4). ��U�̲���USB�ӿ�, ͨ�����ڵ�������۲���Խ��; ÿ�β��һ��U�̶������һ�ζ�д�ļ�����
   
4. Nand Flash�ļ���д����: (ע: ֻ��STM32F103ZEģ��֧��) 
   (1). ����˵��: �������ļ���NFLASH_EN����Ϊ1, ����Ĭ������;
   
   (2). ��APP_Init.c�е���NFlash_APPInit()�����ȳ�ʼ��; ע��: �ڳ�ʼ�����֮ǰ�����ȵ���FSMC_APPInit(), FSMC���߳�ʼ��   
     
   (3). ����NFlash_Ctrl(CMD_NFLASH_STATUS, 0)��ȡNand Flash״̬, ����״̬, �ٵ���NFlash_test()�����ļ���д����;
        
   (4). ͨ�����ڵ�������۲���Խ��; ÿ���ϵ���߸�λֻ����һ��;
   
5. USB�豸ģʽ��, ��USB Mass StorageЭ�����SD����SPI FLASH�ļ�����:
   (1). ����˵��: �������ļ���USB_DEVICE_EN����Ϊ1, USB_MSC_EN����Ϊ1, USB_MSC_LUN������0����1��ѡ��洢����; ע��USB_VCP_ENҪ����Ϊ0;
   
   (2). ��APP_Init.c�е���USBD_APPInit()�����ȳ�ʼ��;
   
   (3). �ȵ���USBD_Ctrl(CMD_USBD_SYNC, 0), USBͬ������, ���USB�豸���벢����USB, ���USB�豸�γ����ر�USB�豸;
   
   (4). ����USB�ߣ����Ӽ���������ڼ�����Ϸ���U��(SPI FLASH��SD��), ���Խ��ж�д�ļ�����;
*/

/************************************************************************************/
// �����ⲿͷ�ļ�
#include "config.h"	 
#if (TASK_FILE_EN == 1)
#include "UserVars.h"
#include "STM32Fxxx.h"
#include "ff.h"
#include "diskio.h"

/************************************************************************************/

/************************************************************************************/
// ������ȫ�ֱ�������
/************************************************************************************/
// ������������Ĳ��Զ�д���ݰ���С
#define FBUF_SIZE    700    // �������ݰ���С����

// ������������Ĳ��Զ�д���ݰ�����
#define SD_PAGE_NUM          10  //360000  // ����SD����д�������ݰ����� 
#define UDISK_PAGE_NUM       10  // ����U�̶�д�������ݰ����� 
#define SPIFLASH_PAGE_LEN    10  // ����SPI FLASH��д�������ݰ����� 
#define NANDFLASH_LEN        10  // ����NAND FLASH��д�������ݰ�����   


INT8U f_buffer[FBUF_SIZE];  // �ļ����Զ�д���ݰ�����
FIL fsrc;                   // file objects
FATFS fs;                   // Work area (file system object) for logical drives

INT32S SD_test(void)
{

    INT32U i, k;
    FRESULT res;         // FatFs function common result code
    UINT bw;         // File R/W count

	printf("AT+FILE=SD��: ���Զ�д�ļ�\r\n");

    for (i=0;i<FBUF_SIZE;i++)
	{
        f_buffer[i] = i&0xff;
    }
    
	res = f_mount(&fs, SD_PATH, 0);
	if (res != FR_OK)
	{
		printf("AT+FILE=SD��: ע��һ��������ʧ��,�������->%d\r\n", res);
		return  ERR_FALSE;
	}

    res = f_open(&fsrc, "1:embedarm.dat",FA_CREATE_ALWAYS | FA_WRITE);	// ע��SD�����ļ��̷��̶�Ϊ��1��
	if (res != FR_OK)
	{
		printf("AT+FILE=SD��: ���ļ�ʧ��: �������->%d\r\n", res);
		return  ERR_FALSE;
	}

	
	for (i=0;i<SD_PAGE_NUM;i++)
	{
		if ((i%100)==0)
        {    
            printf("AT+FILE=SD��: д%dҳ\r\n", i+1);
		}
        
        res = f_write(&fsrc, f_buffer, FBUF_SIZE, &bw);
		if (res != FR_OK)
		{
			printf("AT+FILE=SD��: д�ļ�ʧ��,�������->%d\r\n", res);
			return  ERR_FALSE;
		}
	}
	res = f_close(&fsrc);
	if (res != FR_OK)
	{
		printf("AT+FILE=SD��: �ر��ļ�ʧ��, �������->%d\r\n", res);
		return  ERR_FALSE;
	}


	res = f_open(&fsrc, "1:embedarm.dat",FA_READ| FA_WRITE);
	if (res != FR_OK)
	{
		printf("AT+FILE=SD��: �ٴδ��ļ�ʧ��, �������->%d\r\n", res);
		return  ERR_FALSE;
	}
	
	for (i=0;i<SD_PAGE_NUM;i++)
	{
		if ((i%100)==0)
        {    
            printf("AT+FILE=SD��: ��%dҳ\r\n", i+1);
		}
        
        for (k=0;k<FBUF_SIZE;k++)
	    {
		    f_buffer[k] = 0;
		}
		res = f_read(&fsrc, f_buffer, FBUF_SIZE, &bw);
		if (res != FR_OK)
		{
			printf("AT+FILE=SD��: ���ļ�ʧ��, �������->%d\r\n", res);
			return  ERR_FALSE;
		}
		
		for (k=0;k<FBUF_SIZE;k++)
		{
		    if (f_buffer[k]!= (k&0xff))
			{
			     break;
			}
		}
		if (k==FBUF_SIZE)
		{
			printf("AT+FILE=SD��: ��%dҳ��ȷ\r\n", i+1);
		}
		else
		{
			printf("AT+FILE=SD��: ���ݶԱȴ���, ����λ��%d!\r\n", k);
			return  ERR_FALSE;
		}
        Delay_ms(20);
	}
	
	res = f_close(&fsrc);
    if (res != FR_OK)
	{
		printf("AT+FILE=SD��: �ر��ļ�ʧ��, �������->%d\r\n", res);
		return  ERR_FALSE;
	}
    f_unmount(SD_PATH);
    printf("\r\nAT+FILE=SD��: �ļ���д���Գɹ�!\r\n\r\n");
    return ERR_TRUE;
}


INT32S UDISK_test(void)
{
    INT32U i, k;
    FRESULT res;         // FatFs function common result code
    UINT  bw;         // File R/W count

	printf("AT+FILE=U��: ���Զ�д�ļ�\r\n");

    for (i=0;i<FBUF_SIZE;i++)
	{
	   f_buffer[i] = i&0xff;
	}

	//res = f_mount(USB_DISK, &fs);
	res = f_mount(&fs, UDISK_PATH, 0);
    //res = f_mount(&fs, "", 0);
    if (res != FR_OK)
	{
		printf("AT+FILE=U��: ע��һ��������ʧ��, �������->%d\r\n", res);
		return  ERR_FALSE;
	}

    res = f_open(&fsrc, "2:embedarm.dat",FA_CREATE_ALWAYS | FA_WRITE);	// ע��SD�����ļ��̷��̶�Ϊ��1��
	if (res != FR_OK)
	{
		f_unmount(UDISK_PATH);
        printf("AT+FILE=U��: ���ļ�ʧ��, �������->%d\r\n", res);
		return  ERR_FALSE;
	}

    for (i=0; i<UDISK_PAGE_NUM; i++)
	{
		printf("AT+FILE=U��: д%dҳ\r\n", i+1);
	
        res = f_write(&fsrc, f_buffer, FBUF_SIZE, &bw);
		if (res != FR_OK)
		{
			f_unmount(UDISK_PATH);
            printf("AT+FILE=U��: д�ļ�ʧ��, �������->%d\r\n", res);
			return  ERR_FALSE;
		}
	}
    
	res = f_close(&fsrc);
	if (res != FR_OK)
	{
		f_unmount(UDISK_PATH);
        printf("AT+FILE=U��: �ر��ļ�ʧ��, �������->%d\r\n", res);
		return  ERR_FALSE;
	}
    
	res = f_open(&fsrc, "2:embedarm.dat",FA_READ| FA_WRITE);
	if (res != FR_OK)
	{
		f_unmount(UDISK_PATH);
        printf("AT+FILE=U��: �ٴδ��ļ�ʧ��, �������->%d\r\n", res);
		return  ERR_FALSE;
	}

	for (i=0; i<UDISK_PAGE_NUM; i++)
	{
	    printf("AT+FILE=U��: ��%dҳ\r\n", i+1);

		for (k=0;k<FBUF_SIZE;k++)
	    {
		    f_buffer[k] = 0;
		}
		res = f_read(&fsrc, f_buffer, FBUF_SIZE, &bw);
		if (res != FR_OK)
		{
			f_unmount(UDISK_PATH);
            printf("AT+FILE=U��: ���ļ�ʧ��, �������->%d\r\n", res);
			return  ERR_FALSE;
		}
		
		for (k=0;k<FBUF_SIZE;k++)
		{
		    if (f_buffer[k]!= (k&0xff))
			{
			     break;
			}
		}
		if (k==FBUF_SIZE)
		{
			printf("AT+FILE=U��: ��%dҳ��ȷ\r\n",1+1);
		}
		else
		{
			f_unmount(UDISK_PATH);
            printf("AT+FILE=U��: ���ݶԱȴ��󣺳���λ��%d\r\n", k);
			return  ERR_FALSE;
		}
        Delay_ms(20);
	}
	res = f_close(&fsrc);
    if (res != FR_OK)
	{
		f_unmount(UDISK_PATH);
        printf("AT+FILE=U��: �ر��ļ�ʧ��, �������->%d\r\n", res);
		return  ERR_FALSE;
	}
    f_unmount(UDISK_PATH);
     printf("\r\nAT+FILE=U��: �ļ���д���Գɹ�!\r\n\r\n");
    return ERR_TRUE;
}

void format_disk(void)
{
	INT8U res;

	res = f_mount(&fs, SPIFLASH_PATH, 0);
    if (res != FR_OK)
	{
		printf("AT+FILE=SPIFlash: �����ļ�ϵͳʧ��,�������: %u\r\n",res);
		return;
	}	
	printf("AT+FILE=SPIFlash:���ڸ�ʽ������,���Ժ�...\r\n");

	res = f_mkfs(SPIFLASH_PATH, FM_FAT, 0, fsrc.buf, FF_MAX_SS);  // Ϊ��Լ�ڴ棬�������ļ��ṹ�л���buf
    if (res == FR_OK)
	{
        UserVars.Para.Flag &= ~SPIFLASH_FORMAT_FLAG;    // �����ʽ����־
        APP_ParaSave((USER_VARS *)&UserVars.Flag);      // �洢���µĲ���
		printf("AT+FILE=SPIFlash: ��ʽ���ɹ�...\r\n");
	}
	else
	{
		printf("AT+FILE=SPIFlash: ��ʽ��ʧ��, �������: %u\r\n",res);
	}
    f_unmount(SPIFLASH_PATH);
}

void get_disk_info(void)
{
	FATFS *fls = &fs;
	FRESULT res;
	DWORD clust,fre_sect;	
	
	res = f_mount(&fs, SPIFLASH_PATH, 0);
	if (res != FR_OK)
	{
		printf("AT+FILE=SPIFlash:�����ļ�ϵͳʧ��,�������: %u\r\n",res);
		return;
	}	

	res = f_getfree("/",&clust,&fls);
	if (res == FR_OK) 
	{
		fre_sect = clust*fls->csize;
		printf("AT+FILE=SPIFlash: %dKB free total drive space\r\n",
			fre_sect/2);
	}
	else
	{
		printf("AT+FILE=SPIFlash: ��ô�����Ϣʧ��, �������: %u\r\n", res);
	}
	f_unmount(SPIFLASH_PATH);
}


INT32S SPIFLASH_FileTest(void)
{
	INT32U i, k;
    FRESULT res;         // FatFs function common result code
    UINT  bw;         // File R/W count

	
	printf("AT+FILE=SPIFlash: ���Զ�д�ļ�\r\n");
    //UserVars.Para.Flag |= SPIFLASH_FORMAT_FLAG;
    if ((UserVars.Para.Flag&SPIFLASH_FORMAT_FLAG)>0) // �ж��Ƿ��ʽ��
	{
        format_disk();              // ��ʽ��SPI FLASH
    }
    
    get_disk_info();            // ��ô�����Ϣ
    for (i=0;i<FBUF_SIZE;i++)   // ��ʼ��f_buffer
	{
	   f_buffer[i] = i&0xff;
	}

	res = f_mount(&fs, SPIFLASH_PATH, 0);   // ע�Ṥ����
	if (res != FR_OK)
	{
		printf("AT+FILE=SPIFlash: ע��һ��������ʧ��: �������->%d\r\n", res);
		return  ERR_FALSE;
	}

    res = f_open(&fsrc, "0:m.dat",FA_CREATE_ALWAYS|FA_WRITE);	// ��д�봴����ʽ���ļ�m.dat
	if (res != FR_OK)
	{
		printf("AT+FILE=SPIFlash: ���ļ�ʧ��: �������->%d\r\n", res);
		return  ERR_FALSE;
	}

    for (i=0;i<SPIFLASH_PAGE_LEN;i++)  // д��SPIFLASH_LENҳ����
	{
		printf("AT+FILE=SPIFlash: д%dҳ\r\n", i+1);
		res = f_write(&fsrc, f_buffer, FBUF_SIZE, &bw);          // ����������д���ļ�
		if (res != FR_OK)
		{
			printf("AT+FILE=SPIFlash: д�ļ�ʧ��,�������->%d\r\n", res);
			return  ERR_FALSE;
		}
	}
	res = f_close(&fsrc);           // �ر��ļ�
	if (res != FR_OK)
	{
		printf("AT+FILE=SPIFlash: �ر��ļ�ʧ��,�������->%d\r\n", res);
		return  ERR_FALSE;
	}


	res = f_open(&fsrc, "0:m.dat",FA_READ| FA_WRITE);       // �Զ�д��ʽ���ļ�
	if (res != FR_OK)
	{
		printf("AT+FILE=SPIFlash: �ٴδ��ļ�ʧ��, �������->%d\r\n", res);
		return  ERR_FALSE;
	}
	

	for (i=0;i<SPIFLASH_PAGE_LEN;i++)
	{
		//printf("AT+FILE=SPIFlash: ��%dҳ\r\n", i+1);
	    for (k=0;k<FBUF_SIZE;k++)  // �������
		{
	   		f_buffer[k] = 0;
		}
        
		res = f_read(&fsrc, f_buffer, FBUF_SIZE, &bw); // ��ȡ�ļ����ݵ�����
		if (res != FR_OK)
		{
			printf("AT+FILE=SPIFlash: ���ļ�ʧ��,�������->%d\r\n", res);
			return  ERR_FALSE;
		}
		
		for (k=0;k<FBUF_SIZE;k++)   // �Ա�����
		{
		    if (f_buffer[k]!= (k&0xff))
			{
			     break;
			}
		}

		if (k==FBUF_SIZE)
		{
			printf("AT+FILE=SPIFlash: ��%dҳ��ȷ\r\n", i+1);
		}
		else
		{
			printf("AT+FILE=SPIFlash: ���ݶԱȴ���,����ҳ%d, ����λ��%d\r\n", i, k);
			return  ERR_FALSE;
		}
        Delay_ms(20);
	}

	res = f_close(&fsrc);
    if (res != FR_OK)
	{
		printf("AT+FILE=SPIFlash: �ر��ļ�ʧ��: �������->%d\r\n", res);
		
		return  ERR_FALSE;
	}
	f_unmount(SPIFLASH_PATH);
    
    printf("\r\nAT+FILE=SPIFlash: �ļ���д���Գɹ�\r\n\r\n");
    return ERR_TRUE;
}



void NFlash_Format(void)
{
	INT8U res;
	
	res = f_mount(&fs, NFLASH_PATH, 0);
	if (res != FR_OK)
	{
		printf("\r\nAT+FILE=NFlash: �����ļ�ϵͳʧ��,�������: %u",res);
		return;
	}	
	printf("\r\nAT+FILE=NFlash: ���ڸ�ʽ������,���Ժ�...");
    res = f_mkfs(NFLASH_PATH, FM_FAT, 0, f_buffer, FF_MAX_SS);  // Ϊ��Լ�ڴ棬�������ļ��ṹ�л���buf
    
	if (res == FR_OK)
	{
        UserVars.Para.Flag &= ~NFLASH_FORMAT_FLAG;    // �����ʽ����־
        APP_ParaSave((USER_VARS *)&UserVars.Flag);      // �洢���µĲ���
		printf("\r\nAT+FILE=NFlash: ��ʽ���ɹ�...");
	}
	else
	{
		printf("\r\nAT+FILE=NFlash: ��ʽ��ʧ��...");
		printf("\r\nAT+FILE=NFlash: �������: %u",res);
	}
	f_unmount(NFLASH_PATH);
}

void NFlash_Info(void)
{
	FATFS *fls = &fs;
	FRESULT res;
	DWORD clust, fre_sect;	
	
	res = f_mount(&fs, NFLASH_PATH, 0);
	if (res != FR_OK)
	{
		printf("\r\nAT+FILE=NFlash: �����ļ�ϵͳʧ��,�������: %u",res);
		return;
	}	
    res = f_getfree(NFLASH_PATH,&clust,&fls);
	if (res == FR_OK) 
	{
		fre_sect = clust * fls->csize;
		printf("AT+FILE=NFlash: %dKB free total drive space\r\n", fre_sect/2);
	}
	else
	{
		printf("AT+FILE=NFlash: ��ô�����Ϣʧ��, �������: %u\r\n", res);
	}
	f_unmount(NFLASH_PATH);

}

INT32S NFlash_test(void)
{
	INT32U i, k;
    FRESULT res;         // FatFs function common result code
    UINT br, bw;         // File R/W count

	printf("AT+FILE=NFlash: ׼������, ���Զ�д�ļ�\r\n");
    //UserVars.Para.Flag |= NFLASH_FORMAT_FLAG;
    if ((UserVars.Para.Flag&NFLASH_FORMAT_FLAG)>0) // �ж��Ƿ��ʽ��
	{
        NFlash_Format();                                // ��ʽ��NAND FLASH
    }
    NFlash_Info();
    
	for (i=0;i<FBUF_SIZE;i++)
	{
	   f_buffer[i] = i&0xff;
	}

	res = f_mount(&fs, NFLASH_PATH, 0);
	if (res != FR_OK)
	{
		printf("AT+FILE=NFlash: ע��һ��������ʧ��: �������->%d\r\n", res);
		return  ERR_FALSE;
	}

    res = f_open(&fsrc, "3:k.dat", FA_CREATE_ALWAYS | FA_WRITE);	// ע��SD�����ļ��̷��̶�Ϊ��1��
	if (res)
	{

	}
	
	
	if (res != FR_OK)
	{
		printf("AT+FILE=NFlash: ���ļ�ʧ��: �������->%d\r\n", res);
		return  ERR_FALSE;
	}
	
	for (i=0;i<NANDFLASH_LEN;i++)
	{
		printf("AT+FILE=NFlash: д%dҳ!\r\n", i+1);
		res = f_write(&fsrc, f_buffer, FBUF_SIZE, &bw);
		if (res != FR_OK)
		{
			printf("AT+FILE=NFlash: д�ļ�ʧ��: �������->%d\r\n", res);
			return  ERR_FALSE;
		}
	}

	res = f_close(&fsrc);
	if (res != FR_OK)
	{
		printf("AT+FILE=NFlash: �ر��ļ�ʧ��: �������->%d\r\n", res);
		return  ERR_FALSE;
	}

	res = f_open(&fsrc, "3:k.dat",FA_READ| FA_WRITE);
	if (res != FR_OK)
	{
		printf("AT+FILE=NFlash: �ٴδ��ļ�ʧ��: �������->%d\r\n", res);
		return  ERR_FALSE;
	}
	
	for (i=0;i<NANDFLASH_LEN;i++)
	{
		res = f_read(&fsrc, f_buffer, FBUF_SIZE, &bw);
		if (res != FR_OK)
		{
			printf("AT+FILE=NFlash: ���ļ�ʧ��: �������->%d\r\n", res);
			return  ERR_FALSE;
		}
		
		for (k=0;k<FBUF_SIZE;k++)
		{
		    if (f_buffer[k]!= (k&0xff))
			{
			     break;
			}
		}

		if (k==FBUF_SIZE)
		{
			printf("AT+FILE=NFlash: ��%dҳ��ȷ\r\n", i+1);
		}
		else
		{
			printf("AT+FILE=NFlash: ���ݶԱȴ��󣺳���ҳ%d, ����λ��%d!\r\n", i, k);
			return  ERR_FALSE;
		}
        Delay_ms(20);
	}
	res = f_close(&fsrc);
    if (res != FR_OK)
	{
		printf("AT+FILE=NFlash: �ر��ļ�ʧ��: �������->%d\r\n", res);
		
		return  ERR_FALSE;
	}
	f_unmount(NFLASH_PATH);
    printf("\r\nAT+FILE=NFlash: �ļ���д���Գɹ�!\r\n\r\n");
    return ERR_TRUE;
}

void  App_TaskFile (void *p_arg)
{
	INT32U flag;
    INT8U  SDFlag, UDISKFlag, SPIFlashFlag, NFlashFlag;
		
    (void)p_arg;

    SDFlag = 0;
	UDISKFlag = 0;
	SPIFlashFlag = 0;
    NFlashFlag = 0;    
   
    while (1) 
	{
	    UserVars.TaskRunStatus |= TASK_FILE_FLAG;     // ���ñ���������״̬��־
		Delay_ms(20);	                              // ��ʱ20ms

/****************************************************************/
// ����SPI FLash��д
/****************************************************************/
        #if ((SPIFLASH_EN>0)&&(SPIFLASH_MODE == 1)) // SPI FLASHʹ�ܲ�������FATFS�ļ�ϵͳ���ж�д
        if ((UserVars.LibSys.Flag&SPIFLASH_USB_FLAG)==0)  // �ж�SPI FLASHû�б�USB����ռ��
        {
            UserVars.LibSys.Flag |= SPIFLASH_FATFS_FLAG;  // ����SPI Flash��FatFSռ�ñ�־
            flag = disk_status(SPIFLASH_DISK);            // ��ȡSPI FLASH״̬
            if ((SPIFlashFlag == 0)&&((flag&0x03)==0))    // ��⵽SPI FLASH
            {
                 flag = SPIFLASH_FileTest(); 
                 if (flag == ERR_TRUE)
                 {
                     UserVars.OKFlag |= SPIFLASH_OK_FLAG;
                     #if (DEBUG_APP_EN == 1)
                     if (UserVars.Para.ATFlag&AT_INFO_FLAG)
                     {
                        printf("AT+SPIFLASH=OK\r\n");  
                     }
                     #endif
                 }
                 else
                 {
                     UserVars.OKFlag &= ~SPIFLASH_OK_FLAG;
                     #if (DEBUG_APP_EN == 1)
                     if (UserVars.Para.ATFlag&AT_INFO_FLAG)
                     {
                         printf("AT+SPIFLASH=ERROR\r\n");  
                     }
                     #endif
                 } 
                SPIFlashFlag = 1;
            }
            UserVars.LibSys.Flag &= ~SPIFLASH_FATFS_FLAG; // ���SPI Flash��FatFSռ�ñ�־
        }
        #endif        

/****************************************************************/
// ����SD����д
/****************************************************************/
        #if (SDCARD_EN > 0)               // SD������ʹ��
        if ((UserVars.LibSys.Flag&SD_USB_FLAG)==0)  // �ж�SD��û�б�USB����ռ��
        {            
            UserVars.LibSys.Flag |= SD_FATFS_FLAG;   // ����SD����FatFSռ�ñ�־
            SPI_RequestOSSem(0);
            flag = SD_Ctrl(CMD_SD_STATUS,  0);       // ��ȡSD��״̬
            SPI_ReleaseOSSem();
            
            if ((flag&(SD_NODISK|SD_NOINIT)) == 0)	 // ��⵽SD��
            {
                if(SDFlag == 0)           
                {
                     flag = SD_test(); 
                     if (flag == ERR_TRUE)
                     {
                         UserVars.OKFlag |= SD_OK_FLAG;
                         #if (DEBUG_APP_EN == 1)
                         if (UserVars.Para.ATFlag&AT_INFO_FLAG)
                         {
                            printf("AT+SD=OK\r\n");  
                         }
                         #endif
                     }
                     else
                     {
                         UserVars.OKFlag &= ~SD_OK_FLAG;
                         #if (DEBUG_APP_EN == 1)
                         if (UserVars.Para.ATFlag&AT_INFO_FLAG)
                         {
                             printf("AT+SD=ERROR\r\n");  
                         }
                         #endif
                     } 
                    SDFlag = 1;
                }
            }
            else
            {
                if (SDFlag == 1)
                {
                    SDFlag = 0;
                    UserVars.OKFlag &= ~SD_OK_FLAG;
                    #if (DEBUG_APP_EN > 0)
                    //printf("AT+FILE=SD��: ���ε�\r\n");
                    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
                    {
                        printf("AT+SD=ERROR\r\n");  
                    }
                    #endif
                }
            }
            UserVars.LibSys.Flag &= ~SD_FATFS_FLAG;  // ���SD����FatFSռ�ñ�־
        }
        #endif
/****************************************************************/
// ����U�̶�д
/****************************************************************/
        #if (USB_HOST_EN > 0)   // USB����ģʽʹ��
        flag = USBH_Ctrl(USB_ID, CMD_USBH_SYNC, 0);
        if (flag&USBH_WORK_OK)	  // ��⵽U��
        {
             if(UDISKFlag == 0)           
             {
                 flag = UDISK_test(); 			  // ����U�̶�д
                 if (flag == ERR_TRUE)
                 {
                     UserVars.OKFlag |= UDISK_OK_FLAG;
                     #if (DEBUG_APP_EN == 1)
                     if (UserVars.Para.ATFlag&AT_INFO_FLAG)
                     {
                        printf("AT+UDISK=OK\r\n");  
                     }
                     #endif
                 }
                 else
                 {
                     UserVars.OKFlag &= ~UDISK_OK_FLAG;
                     #if (DEBUG_APP_EN == 1)
                     if (UserVars.Para.ATFlag&AT_INFO_FLAG)
                     {
                         printf("AT+UDISK=ERROR\r\n");  
                     }
                     #endif
                 } 
                 UDISKFlag= 1;
             }
        }
        else
        {
             if (UDISKFlag == 1)
             {
                 UDISKFlag = 0;
                 UserVars.OKFlag &= ~UDISK_OK_FLAG;
                 #if (DEBUG_APP_EN > 0)
                 //printf("AT+FILE=U��: ���ε�\r\n");
                 if (UserVars.Para.ATFlag&AT_INFO_FLAG)
                 {
                    printf("AT+UDISK=ERROR\r\n");  
                 }
                 #endif
             }
        }
        #endif  
        
/****************************************************************/
// ����Nand Flash��д
/****************************************************************/        
        #if ((MODULE_TYPE == STM32F103ZE)&&(NFLASH_EN > 0))
        if ((UserVars.LibSys.Flag&NFLASH_USB_FLAG)==0)  // �ж�Nand Flashû�б�USB����ռ��
        { 
            UserVars.LibSys.Flag |= NFLASH_FATFS_FLAG;  // ����Nand Flash��FatFSռ�ñ�־
            if (NFlashFlag==0)
            {
                 flag = NFlash_Ctrl(CMD_NFLASH_STATUS, 0);  // ��ȡNand Flash״̬
                 if (flag == 0) 
                 {
                     flag = NFlash_test(); 
                     if (flag == ERR_TRUE)
                     {
                         UserVars.OKFlag |= NFLASH_OK_FLAG;
                         #if (DEBUG_APP_EN == 1)
                         if (UserVars.Para.ATFlag&AT_INFO_FLAG)
                         {
                            printf("AT+NFLASH=OK\r\n");  
                         }
                         #endif
                     }
                     else
                     {
                         UserVars.OKFlag &= ~NFLASH_OK_FLAG;
                         #if (DEBUG_APP_EN == 1)
                         if (UserVars.Para.ATFlag&AT_INFO_FLAG)
                         {
                             printf("AT+NFLASH=ERROR\r\n");  
                         }
                         #endif
                     }                         
                     NFlashFlag = 1;
                 }
            }
            UserVars.LibSys.Flag |= NFLASH_FATFS_FLAG;  // ���Nand Flash��FatFSռ�ñ�־
        }
        #endif        
        
/****************************************************************/
// ����USB����ģʽ��,��USB Mass StorageЭ�����SD����SPI FLASH�ļ�
/****************************************************************/       
        #if ((USB_DEVICE_EN > 0)&&(USB_MSC_EN > 0)) // USB�豸ģʽʹ�ܼ�USB Mass Storageʹ��   
        USBD_Ctrl(USB_ID, CMD_USBD_SYNC, 0);	  // USBͬ������, ���USB�豸���벢����USB, ���USB�豸�γ����ر�USB�豸;
        #endif 
    }   
}

#endif
/***********************************************************************************/
// �ļ�����
/***********************************************************************************/


	 