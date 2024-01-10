/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2016        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/
#include "const.h"	
#include "config.h"	

#include "diskio.h"		/* FatFs lower layer API */

#include "sd.h"
#include "W25QXX.h"
#include "AT45DBXX.h"
#include "OSHook.h"
#include "USBHost.h"
#include "rtc.h"
#if ((MODULE_TYPE == STM32F103ZE)&&(NFLASH_EN > 0))
#include "nflash.h"
#endif

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat; 
	
    switch (pdrv) 
    {
        #if (SPIFLASH_EN > 0)
        case SPIFLASH_DISK:
            #if (SPIFLASH_TYPE == W25QXX)
            stat = W25QXX_Ctrl(CMD_W25QXX_STATUS, 0);  // 
            #endif
        
            #if (SPIFLASH_TYPE == AT45DBXX)
            stat = AT45DBXX_Ctrl(CMD_AT45DBXX_STATUS, 0);  // 
            #endif
            break;
        #endif
        #if (SDCARD_EN > 0)
        case SD_DISK :
            SPI_RequestOSSem(0);
            stat = SD_Ctrl(CMD_SD_STATUS,  0);
            SPI_ReleaseOSSem();
            break;
        #endif
        #if ((USB_HOST_EN > 0)&&(UDISK_EN > 0))
        case USB_DISK:
            stat = USBH_Ctrl(USB_ID, CMD_UDISK_STATUS, 0);            
            break;
        #endif
       
        #if ((MODULE_TYPE == STM32F103ZE)&&(NFLASH_EN > 0))
        case NFLASH_DISK:
            stat = NFlash_Ctrl(CMD_NFLASH_STATUS, 0);            
            break;
        #endif
        
        default:
            stat = RES_PARERR;
            break;
	}
	return stat;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
	INT32S result;

	switch (pdrv) 
    {
        #if (SPIFLASH_EN > 0)    
        case SPIFLASH_DISK:
            #if (SPIFLASH_TYPE == W25QXX)
            stat = W25QXX_Ctrl(CMD_W25QXX_INIT, 0);    // 初始化已经在APP_Init.c中的SPIFlash_APPInit()完成，这里只读取状态即可
            #endif
            
            #if (SPIFLASH_TYPE == AT45DBXX)
            stat = AT45DBXX_Ctrl(CMD_AT45DBXX_STATUS, 0);  // 初始化已经在APP_Init.c中的SPIFlash_APPInit()完成，这里只读取状态即可
            #endif
            // translate the reslut code here
            break;
        #endif
        #if (SDCARD_EN > 0)
        case SD_DISK:
            SPI_RequestOSSem(0);
            stat = SD_Ctrl(CMD_SD_STATUS,  0);
            SPI_ReleaseOSSem();            
            // translate the reslut code here
            break;
        #endif
        #if ((USB_HOST_EN > 0)&&(UDISK_EN > 0))
        case USB_DISK:
            stat = USBH_Ctrl(USB_ID, CMD_UDISK_STATUS, 0);//UDisk_Initialize(0);
            // translate the reslut code here
            break;
        #endif
        #if ((MODULE_TYPE == STM32F103ZE)&&(NFLASH_EN > 0))
        case NFLASH_DISK:
            stat = NFlash_Ctrl(CMD_NFLASH_STATUS, 0);  //stat = NFlash_Ctrl(CMD_NFLASH_INIT, 0);            
            break;
        #endif
        default:
            stat = RES_PARERR;
            break;
	}
	return stat;
}

/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)   
{
	DRESULT res;
	INT32S result;
    INT16U m,n,i,j;
    

	switch (pdrv) 
    {
        #if (SPIFLASH_EN > 0)     
        case SPIFLASH_DISK:
            #if (SPIFLASH_TYPE == W25QXX)
            SPI_RequestOSSem(0);
            result = W25QXX_ReadSector(buff, sector, count);
            SPI_ReleaseOSSem();
            #endif
            
            #if (SPIFLASH_TYPE == AT45DBXX)
            SPI_RequestOSSem(0);
            result = AT45DBXX_ReadPage(buff, sector, count);  
            SPI_ReleaseOSSem();
            #endif
            if(result == ERR_TRUE)
            {
                res = RES_OK;
            }
            else
            {
                res = RES_ERROR;
            }
            break;
        #endif
            
        #if (SDCARD_EN > 0)
        case SD_DISK:
            // translate the arguments here
            SPI_RequestOSSem(0);
            res = SD_Read(buff, sector, count);
            SPI_ReleaseOSSem();
            break;
        #endif
        #if ((USB_HOST_EN > 0)&&(UDISK_EN > 0))
        case USB_DISK:
            res = UDisk_Read(0, buff, sector, count);
            break;
        #endif
        #if ((MODULE_TYPE == STM32F103ZE)&&(NFLASH_EN > 0))
        case NFLASH_DISK:
            res = NFlash_ReadSector(buff, sector, count); 
            break;
        #endif
        default:
            res = RES_PARERR;
            break;        
	}

	return res;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	DRESULT res;
	INT32S result;
    INT8U i;
    INT16U n, m, j;

	switch (pdrv) 
    {
        #if (SPIFLASH_EN > 0)    
        case SPIFLASH_DISK:
            // translate the arguments here
            #if (SPIFLASH_TYPE == W25QXX)
            SPI_RequestOSSem(0);
            result = W25QXX_WriteSector((INT8U *)buff, sector, count);
            SPI_ReleaseOSSem();
            #endif
            
            #if (SPIFLASH_TYPE == AT45DBXX)
            SPI_RequestOSSem(0);
            result = AT45DBXX_WritePage((INT8U *)buff, sector, count);  
            SPI_ReleaseOSSem();
            #endif
            
            if(result == ERR_TRUE)
            {
                res = RES_OK;
            }
            else
            {
                res = RES_ERROR;
            }
            // translate the reslut code here
            break;
        #endif
        #if (SDCARD_EN > 0)    
        case SD_DISK:
            // translate the arguments here
            SPI_RequestOSSem(0);
            res = SD_Write((INT8U *)buff, sector, count);
            SPI_ReleaseOSSem();
            break;
        #endif
        #if ((USB_HOST_EN > 0)&&(UDISK_EN > 0))
        case USB_DISK:
            // translate the arguments here
            res = UDisk_Write(0, (INT8U *)buff, sector, count);
            // translate the reslut code here
            break;
        #endif
        
        #if ((MODULE_TYPE == STM32F103ZE)&&(NFLASH_EN > 0))
        case NFLASH_DISK:               
             res = NFlash_WriteSector((INT8U *)buff, sector, count); 
            break;
        #endif
        default:
            res = RES_PARERR;
            break;
	}
	return res;
}



/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;
	int result;

	switch (pdrv) 
    {
        #if (SPIFLASH_EN > 0)    
        case SPIFLASH_DISK:
            // Process of the command for the SPI FLASH drive
            switch(cmd)
            {
                case CTRL_SYNC:
                    #if (SPIFLASH_TYPE == W25QXX)                    
                    SPI_RequestOSSem(0);
                    W25QXX_Ctrl(CMD_W25QXX_SYNC, 0);
                    SPI_ReleaseOSSem();
                    #endif
                    res = RES_OK;
                    break;
                case GET_SECTOR_COUNT:
                    #if (SPIFLASH_TYPE == W25QXX)
                    *(INT32U *)buff = (INT32U)W25QXX_FATFS_SECTORNUM*8;
                    #endif
                
                    #if (SPIFLASH_TYPE == AT45DBXX)
                    *(INT32U *)buff = AT45DBXX_FATFS_PAGENUM;
                    #endif
                    res = RES_OK;
                    break;
                case GET_BLOCK_SIZE:                    
                    *(INT32U *)buff = 1;                    
                    res = RES_OK;
                    break;
                case GET_SECTOR_SIZE:
                    *(INT32U *)buff = 512;                  
                    res = RES_OK;
                    break;				
                case MMC_GET_TYPE:
                case MMC_GET_CSD:
                case MMC_GET_CID:
                case MMC_GET_OCR:
                case MMC_GET_SDSTAT:
                    res = RES_OK;
                    break;
                default:
                    res = RES_PARERR;
                    break;
            }		
            break;
        #endif
        #if (SDCARD_EN > 0)    
        case SD_DISK:
           // Process of the command for the MMC/SD card
           switch(cmd)
           {    
                case GET_SECTOR_COUNT:
                    *(INT32U *)buff = SD_Ctrl(CMD_SD_SECTOR_COUNT, 0);
                    res = RES_OK;
                    break;
                case GET_BLOCK_SIZE:
                    *(INT32U *)buff = 1;                    
                    res = RES_OK;
                case GET_SECTOR_SIZE:
                    *(INT32U *)buff = SD_Ctrl(CMD_SD_SECTOR_SIZE, 0);
                    res = RES_OK;
                    break;
                case MMC_GET_TYPE:
                    *(INT32U *)buff = SD_Ctrl(CMD_SD_TYPE, 0);
                    res = RES_OK;
                    break;
                case CTRL_SYNC:
                case MMC_GET_CSD:
                case MMC_GET_CID:
                case MMC_GET_OCR:
                case MMC_GET_SDSTAT:
                    res = RES_OK;
                    break;
                default:
                    res = RES_PARERR;
                    break;
            }
            break;
        #endif
        #if ((USB_HOST_EN > 0)&&(UDISK_EN > 0))
        case USB_DISK:
           switch(cmd)
           {    
                case GET_SECTOR_COUNT:
                    *(INT32U *)buff = USBH_Ctrl(USB_ID, CMD_UDISK_SECTOR_COUNT, 0);
                    res = RES_OK;
                    break;
                case GET_BLOCK_SIZE:
                    *(INT32U *)buff = 1;                    
                    res = RES_OK;
                case GET_SECTOR_SIZE:
                    *(INT32U *)buff = USBH_Ctrl(USB_ID, CMD_UDISK_SECTOR_SIZE, 0);
                    res = RES_OK;
                    break;
                case MMC_GET_TYPE:
                case CTRL_SYNC:
                case MMC_GET_CSD:
                case MMC_GET_CID:
                case MMC_GET_OCR:
                case MMC_GET_SDSTAT:
                    res = RES_OK;
                    break;
                default:
                    res = RES_PARERR;
                    break;
            }
            break;
        #endif
        #if ((MODULE_TYPE == STM32F103ZE)&&(NFLASH_EN > 0))
        case NFLASH_DISK:
           switch(cmd)
           {    
                case CTRL_SYNC:
                    NFlash_Ctrl(CMD_NFLASH_SYNC, 0);
                    //printf("SYNC\r\n"); 
                    res = RES_OK;
                    break;
                case GET_SECTOR_COUNT:
                    *(INT32U *)buff = NFlash_Ctrl(CMD_NFLASH_SECTOR_COUNT, 0);
                    res = RES_OK;
                    break;
                case GET_BLOCK_SIZE:
                    *(INT32U *)buff = NFlash_Ctrl(CMD_NFLASH_BLOCK_SIZE, 0);
                    res = RES_OK;
                    break;
                case GET_SECTOR_SIZE:
                    *(INT32U *)buff = NFlash_Ctrl(CMD_NFLASH_SECTOR_SIZE, 0);
                    res = RES_OK;
                    break;
                case MMC_GET_TYPE:
                case MMC_GET_CSD:
                case MMC_GET_CID:
                case MMC_GET_OCR:
                case MMC_GET_SDSTAT:
                    res = RES_OK;
                    break;
                default:
                    res = RES_PARERR;
                    break;
            }
            break;
        #endif    
        default:
            res = RES_PARERR;
            break;
	}

	return res;
}

INT32U get_fattime(void)
{
	RTC_TIME rtc; 
	INT32U tmx = 0, flag;

	flag = RTC_Read(&rtc);
    if (flag == ERR_TRUE)
    {
        tmx = ((INT32U)rtc.year+20) << 25;		//from 1980 
        tmx |= (INT32U)rtc.month << 24;
        tmx |= (INT32U)rtc.day << 16;
        tmx |= (INT32U)rtc.hour << 11;
        tmx |= (INT32U)rtc.minute << 5;
        tmx |= (INT32U)rtc.second>>1;			//0~29 second/2
    }
    return(tmx);
}