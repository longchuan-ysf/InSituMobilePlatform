/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: TastFile.c
* Project  : STM32F1XX/4XX系列模块软件
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.00
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: 本文件负责文件系统读写任务处理;
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
// 测试说明
/************************************************************************************/
/*
1. SPI FLASH(W25Q64)文件读写测试: 
   (1). SPI FALSH(W25Q64或AT45DB161)芯片在核心模块上, 占用SPI1总线
   
   (2). 配置说明: 将配置文件中SPIFLASH_EN设置为1, SPIFLASH_MODE设置为1, 其它默认不用修改;
   
   (3). SPI FLASH(W25Q64)文件读写测试: 在APP_Init.c中调用SPIFlash_APPInit()函数先初始化; 
   
   (4). 先调用disk_status(SPIFLASH_DISK)读取状态, 再调用SPIFLASH_FileTest()进行文件读写测试, 通过串口调试输出
        观察测试结果; 每次上电或者复位只运行一次;
        
2. SD卡文件读写测试: 
   (1). SD卡采用SPI总线设计, 占用SPI1总线;
   
   (2). 配置说明: 将配置文件中SDCARD_EN配置为1;
   
   (3). 在APP_Init.c中调用SD_APPInit()初始化;
   
   (4). 先调用SD_Ctrl(CMD_SD_STATUS,  0)读取状态, 再调用SD_Test()进行文件读写测试, 通过串口调试输出
        观察测试结果; 可以通过插拔SD卡测试;
        
3. U盘文件读写测试: 
   (1). 配置说明: 将配置文件中USB_HOST_EN配置为1, UDISK_EN配置为1;
   
   (2). 在APP_Init.c中调用USBH_APPInit()函数先初始化;
   
   (3). 先调用USBH_Ctrl(CMD_USBH_SYNC, 0), 根据U盘状态, 再调用UDISK_test()进行文件读写测试;
        
   (4). 将U盘插入USB接口, 通过串口调试输出观察测试结果; 每次插拔一次U盘都会进行一次读写文件测试
   
4. Nand Flash文件读写测试: (注: 只有STM32F103ZE模块支持) 
   (1). 配置说明: 将配置文件中NFLASH_EN配置为1, 其它默认设置;
   
   (2). 在APP_Init.c中调用NFlash_APPInit()函数先初始化; 注意: 在初始化这个之前必须先调用FSMC_APPInit(), FSMC总线初始化   
     
   (3). 调用NFlash_Ctrl(CMD_NFLASH_STATUS, 0)读取Nand Flash状态, 根据状态, 再调用NFlash_test()进行文件读写测试;
        
   (4). 通过串口调试输出观察测试结果; 每次上电或者复位只运行一次;
   
5. USB设备模式下, 用USB Mass Storage协议操作SD卡或SPI FLASH文件测试:
   (1). 配置说明: 将配置文件中USB_DEVICE_EN配置为1, USB_MSC_EN配置为1, USB_MSC_LUN请设置0或者1来选择存储介质; 注意USB_VCP_EN要设置为0;
   
   (2). 在APP_Init.c中调用USBD_APPInit()函数先初始化;
   
   (3). 先调用USBD_Ctrl(CMD_USBD_SYNC, 0), USB同步处理, 检测USB设备插入并启动USB, 监测USB设备拔出并关闭USB设备;
   
   (4). 插上USB线，连接计算机可以在计算机上发线U盘(SPI FLASH或SD卡), 可以进行读写文件测试;
*/

/************************************************************************************/
// 引用外部头文件
#include "config.h"	 
#if (TASK_FILE_EN == 1)
#include "UserVars.h"
#include "STM32Fxxx.h"
#include "ff.h"
#include "diskio.h"

/************************************************************************************/

/************************************************************************************/
// 常量及全局变量定义
/************************************************************************************/
// 可以在下面更改测试读写数据包大小
#define FBUF_SIZE    700    // 测试数据包大小定义

// 可以在下面更改测试读写数据包数量
#define SD_PAGE_NUM          10  //360000  // 设置SD卡读写测试数据包数量 
#define UDISK_PAGE_NUM       10  // 设置U盘读写测试数据包数量 
#define SPIFLASH_PAGE_LEN    10  // 设置SPI FLASH读写测试数据包数量 
#define NANDFLASH_LEN        10  // 设置NAND FLASH读写测试数据包数量   


INT8U f_buffer[FBUF_SIZE];  // 文件测试读写数据包缓存
FIL fsrc;                   // file objects
FATFS fs;                   // Work area (file system object) for logical drives

INT32S SD_test(void)
{

    INT32U i, k;
    FRESULT res;         // FatFs function common result code
    UINT bw;         // File R/W count

	printf("AT+FILE=SD卡: 测试读写文件\r\n");

    for (i=0;i<FBUF_SIZE;i++)
	{
        f_buffer[i] = i&0xff;
    }
    
	res = f_mount(&fs, SD_PATH, 0);
	if (res != FR_OK)
	{
		printf("AT+FILE=SD卡: 注册一个工作区失败,出错代码->%d\r\n", res);
		return  ERR_FALSE;
	}

    res = f_open(&fsrc, "1:embedarm.dat",FA_CREATE_ALWAYS | FA_WRITE);	// 注意SD卡的文件盘符固定为‘1’
	if (res != FR_OK)
	{
		printf("AT+FILE=SD卡: 打开文件失败: 出错代码->%d\r\n", res);
		return  ERR_FALSE;
	}

	
	for (i=0;i<SD_PAGE_NUM;i++)
	{
		if ((i%100)==0)
        {    
            printf("AT+FILE=SD卡: 写%d页\r\n", i+1);
		}
        
        res = f_write(&fsrc, f_buffer, FBUF_SIZE, &bw);
		if (res != FR_OK)
		{
			printf("AT+FILE=SD卡: 写文件失败,出错代码->%d\r\n", res);
			return  ERR_FALSE;
		}
	}
	res = f_close(&fsrc);
	if (res != FR_OK)
	{
		printf("AT+FILE=SD卡: 关闭文件失败, 出错代码->%d\r\n", res);
		return  ERR_FALSE;
	}


	res = f_open(&fsrc, "1:embedarm.dat",FA_READ| FA_WRITE);
	if (res != FR_OK)
	{
		printf("AT+FILE=SD卡: 再次打开文件失败, 出错代码->%d\r\n", res);
		return  ERR_FALSE;
	}
	
	for (i=0;i<SD_PAGE_NUM;i++)
	{
		if ((i%100)==0)
        {    
            printf("AT+FILE=SD卡: 读%d页\r\n", i+1);
		}
        
        for (k=0;k<FBUF_SIZE;k++)
	    {
		    f_buffer[k] = 0;
		}
		res = f_read(&fsrc, f_buffer, FBUF_SIZE, &bw);
		if (res != FR_OK)
		{
			printf("AT+FILE=SD卡: 读文件失败, 出错代码->%d\r\n", res);
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
			printf("AT+FILE=SD卡: 读%d页正确\r\n", i+1);
		}
		else
		{
			printf("AT+FILE=SD卡: 数据对比错误, 出错位置%d!\r\n", k);
			return  ERR_FALSE;
		}
        Delay_ms(20);
	}
	
	res = f_close(&fsrc);
    if (res != FR_OK)
	{
		printf("AT+FILE=SD卡: 关闭文件失败, 出错代码->%d\r\n", res);
		return  ERR_FALSE;
	}
    f_unmount(SD_PATH);
    printf("\r\nAT+FILE=SD卡: 文件读写测试成功!\r\n\r\n");
    return ERR_TRUE;
}


INT32S UDISK_test(void)
{
    INT32U i, k;
    FRESULT res;         // FatFs function common result code
    UINT  bw;         // File R/W count

	printf("AT+FILE=U盘: 测试读写文件\r\n");

    for (i=0;i<FBUF_SIZE;i++)
	{
	   f_buffer[i] = i&0xff;
	}

	//res = f_mount(USB_DISK, &fs);
	res = f_mount(&fs, UDISK_PATH, 0);
    //res = f_mount(&fs, "", 0);
    if (res != FR_OK)
	{
		printf("AT+FILE=U盘: 注册一个工作区失败, 出错代码->%d\r\n", res);
		return  ERR_FALSE;
	}

    res = f_open(&fsrc, "2:embedarm.dat",FA_CREATE_ALWAYS | FA_WRITE);	// 注意SD卡的文件盘符固定为‘1’
	if (res != FR_OK)
	{
		f_unmount(UDISK_PATH);
        printf("AT+FILE=U盘: 打开文件失败, 出错代码->%d\r\n", res);
		return  ERR_FALSE;
	}

    for (i=0; i<UDISK_PAGE_NUM; i++)
	{
		printf("AT+FILE=U盘: 写%d页\r\n", i+1);
	
        res = f_write(&fsrc, f_buffer, FBUF_SIZE, &bw);
		if (res != FR_OK)
		{
			f_unmount(UDISK_PATH);
            printf("AT+FILE=U盘: 写文件失败, 出错代码->%d\r\n", res);
			return  ERR_FALSE;
		}
	}
    
	res = f_close(&fsrc);
	if (res != FR_OK)
	{
		f_unmount(UDISK_PATH);
        printf("AT+FILE=U盘: 关闭文件失败, 出错代码->%d\r\n", res);
		return  ERR_FALSE;
	}
    
	res = f_open(&fsrc, "2:embedarm.dat",FA_READ| FA_WRITE);
	if (res != FR_OK)
	{
		f_unmount(UDISK_PATH);
        printf("AT+FILE=U盘: 再次打开文件失败, 出错代码->%d\r\n", res);
		return  ERR_FALSE;
	}

	for (i=0; i<UDISK_PAGE_NUM; i++)
	{
	    printf("AT+FILE=U盘: 读%d页\r\n", i+1);

		for (k=0;k<FBUF_SIZE;k++)
	    {
		    f_buffer[k] = 0;
		}
		res = f_read(&fsrc, f_buffer, FBUF_SIZE, &bw);
		if (res != FR_OK)
		{
			f_unmount(UDISK_PATH);
            printf("AT+FILE=U盘: 读文件失败, 出错代码->%d\r\n", res);
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
			printf("AT+FILE=U盘: 读%d页正确\r\n",1+1);
		}
		else
		{
			f_unmount(UDISK_PATH);
            printf("AT+FILE=U盘: 数据对比错误：出错位置%d\r\n", k);
			return  ERR_FALSE;
		}
        Delay_ms(20);
	}
	res = f_close(&fsrc);
    if (res != FR_OK)
	{
		f_unmount(UDISK_PATH);
        printf("AT+FILE=U盘: 关闭文件失败, 出错代码->%d\r\n", res);
		return  ERR_FALSE;
	}
    f_unmount(UDISK_PATH);
     printf("\r\nAT+FILE=U盘: 文件读写测试成功!\r\n\r\n");
    return ERR_TRUE;
}

void format_disk(void)
{
	INT8U res;

	res = f_mount(&fs, SPIFLASH_PATH, 0);
    if (res != FR_OK)
	{
		printf("AT+FILE=SPIFlash: 挂载文件系统失败,错误代码: %u\r\n",res);
		return;
	}	
	printf("AT+FILE=SPIFlash:正在格式化磁盘,请稍候...\r\n");

	res = f_mkfs(SPIFLASH_PATH, FM_FAT, 0, fsrc.buf, FF_MAX_SS);  // 为节约内存，先利用文件结构中缓存buf
    if (res == FR_OK)
	{
        UserVars.Para.Flag &= ~SPIFLASH_FORMAT_FLAG;    // 清除格式化标志
        APP_ParaSave((USER_VARS *)&UserVars.Flag);      // 存储更新的参数
		printf("AT+FILE=SPIFlash: 格式化成功...\r\n");
	}
	else
	{
		printf("AT+FILE=SPIFlash: 格式化失败, 错误代码: %u\r\n",res);
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
		printf("AT+FILE=SPIFlash:挂载文件系统失败,错误代码: %u\r\n",res);
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
		printf("AT+FILE=SPIFlash: 获得磁盘信息失败, 错误代码: %u\r\n", res);
	}
	f_unmount(SPIFLASH_PATH);
}


INT32S SPIFLASH_FileTest(void)
{
	INT32U i, k;
    FRESULT res;         // FatFs function common result code
    UINT  bw;         // File R/W count

	
	printf("AT+FILE=SPIFlash: 测试读写文件\r\n");
    //UserVars.Para.Flag |= SPIFLASH_FORMAT_FLAG;
    if ((UserVars.Para.Flag&SPIFLASH_FORMAT_FLAG)>0) // 判断是否格式化
	{
        format_disk();              // 格式化SPI FLASH
    }
    
    get_disk_info();            // 获得磁盘信息
    for (i=0;i<FBUF_SIZE;i++)   // 初始化f_buffer
	{
	   f_buffer[i] = i&0xff;
	}

	res = f_mount(&fs, SPIFLASH_PATH, 0);   // 注册工作区
	if (res != FR_OK)
	{
		printf("AT+FILE=SPIFlash: 注册一个工作区失败: 出错代码->%d\r\n", res);
		return  ERR_FALSE;
	}

    res = f_open(&fsrc, "0:m.dat",FA_CREATE_ALWAYS|FA_WRITE);	// 以写入创建方式打开文件m.dat
	if (res != FR_OK)
	{
		printf("AT+FILE=SPIFlash: 打开文件失败: 出错代码->%d\r\n", res);
		return  ERR_FALSE;
	}

    for (i=0;i<SPIFLASH_PAGE_LEN;i++)  // 写入SPIFLASH_LEN页数据
	{
		printf("AT+FILE=SPIFlash: 写%d页\r\n", i+1);
		res = f_write(&fsrc, f_buffer, FBUF_SIZE, &bw);          // 将缓存数据写入文件
		if (res != FR_OK)
		{
			printf("AT+FILE=SPIFlash: 写文件失败,出错代码->%d\r\n", res);
			return  ERR_FALSE;
		}
	}
	res = f_close(&fsrc);           // 关闭文件
	if (res != FR_OK)
	{
		printf("AT+FILE=SPIFlash: 关闭文件失败,出错代码->%d\r\n", res);
		return  ERR_FALSE;
	}


	res = f_open(&fsrc, "0:m.dat",FA_READ| FA_WRITE);       // 以读写方式打开文件
	if (res != FR_OK)
	{
		printf("AT+FILE=SPIFlash: 再次打开文件失败, 出错代码->%d\r\n", res);
		return  ERR_FALSE;
	}
	

	for (i=0;i<SPIFLASH_PAGE_LEN;i++)
	{
		//printf("AT+FILE=SPIFlash: 读%d页\r\n", i+1);
	    for (k=0;k<FBUF_SIZE;k++)  // 清除缓存
		{
	   		f_buffer[k] = 0;
		}
        
		res = f_read(&fsrc, f_buffer, FBUF_SIZE, &bw); // 读取文件数据到缓存
		if (res != FR_OK)
		{
			printf("AT+FILE=SPIFlash: 读文件失败,出错代码->%d\r\n", res);
			return  ERR_FALSE;
		}
		
		for (k=0;k<FBUF_SIZE;k++)   // 对比数据
		{
		    if (f_buffer[k]!= (k&0xff))
			{
			     break;
			}
		}

		if (k==FBUF_SIZE)
		{
			printf("AT+FILE=SPIFlash: 读%d页正确\r\n", i+1);
		}
		else
		{
			printf("AT+FILE=SPIFlash: 数据对比错误,出错页%d, 出错位置%d\r\n", i, k);
			return  ERR_FALSE;
		}
        Delay_ms(20);
	}

	res = f_close(&fsrc);
    if (res != FR_OK)
	{
		printf("AT+FILE=SPIFlash: 关闭文件失败: 出错代码->%d\r\n", res);
		
		return  ERR_FALSE;
	}
	f_unmount(SPIFLASH_PATH);
    
    printf("\r\nAT+FILE=SPIFlash: 文件读写测试成功\r\n\r\n");
    return ERR_TRUE;
}



void NFlash_Format(void)
{
	INT8U res;
	
	res = f_mount(&fs, NFLASH_PATH, 0);
	if (res != FR_OK)
	{
		printf("\r\nAT+FILE=NFlash: 挂载文件系统失败,错误代码: %u",res);
		return;
	}	
	printf("\r\nAT+FILE=NFlash: 正在格式化磁盘,请稍候...");
    res = f_mkfs(NFLASH_PATH, FM_FAT, 0, f_buffer, FF_MAX_SS);  // 为节约内存，先利用文件结构中缓存buf
    
	if (res == FR_OK)
	{
        UserVars.Para.Flag &= ~NFLASH_FORMAT_FLAG;    // 清除格式化标志
        APP_ParaSave((USER_VARS *)&UserVars.Flag);      // 存储更新的参数
		printf("\r\nAT+FILE=NFlash: 格式化成功...");
	}
	else
	{
		printf("\r\nAT+FILE=NFlash: 格式化失败...");
		printf("\r\nAT+FILE=NFlash: 错误代码: %u",res);
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
		printf("\r\nAT+FILE=NFlash: 挂载文件系统失败,错误代码: %u",res);
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
		printf("AT+FILE=NFlash: 获得磁盘信息失败, 错误代码: %u\r\n", res);
	}
	f_unmount(NFLASH_PATH);

}

INT32S NFlash_test(void)
{
	INT32U i, k;
    FRESULT res;         // FatFs function common result code
    UINT br, bw;         // File R/W count

	printf("AT+FILE=NFlash: 准备就绪, 测试读写文件\r\n");
    //UserVars.Para.Flag |= NFLASH_FORMAT_FLAG;
    if ((UserVars.Para.Flag&NFLASH_FORMAT_FLAG)>0) // 判断是否格式化
	{
        NFlash_Format();                                // 格式化NAND FLASH
    }
    NFlash_Info();
    
	for (i=0;i<FBUF_SIZE;i++)
	{
	   f_buffer[i] = i&0xff;
	}

	res = f_mount(&fs, NFLASH_PATH, 0);
	if (res != FR_OK)
	{
		printf("AT+FILE=NFlash: 注册一个工作区失败: 出错代码->%d\r\n", res);
		return  ERR_FALSE;
	}

    res = f_open(&fsrc, "3:k.dat", FA_CREATE_ALWAYS | FA_WRITE);	// 注意SD卡的文件盘符固定为‘1’
	if (res)
	{

	}
	
	
	if (res != FR_OK)
	{
		printf("AT+FILE=NFlash: 打开文件失败: 出错代码->%d\r\n", res);
		return  ERR_FALSE;
	}
	
	for (i=0;i<NANDFLASH_LEN;i++)
	{
		printf("AT+FILE=NFlash: 写%d页!\r\n", i+1);
		res = f_write(&fsrc, f_buffer, FBUF_SIZE, &bw);
		if (res != FR_OK)
		{
			printf("AT+FILE=NFlash: 写文件失败: 出错代码->%d\r\n", res);
			return  ERR_FALSE;
		}
	}

	res = f_close(&fsrc);
	if (res != FR_OK)
	{
		printf("AT+FILE=NFlash: 关闭文件失败: 出错代码->%d\r\n", res);
		return  ERR_FALSE;
	}

	res = f_open(&fsrc, "3:k.dat",FA_READ| FA_WRITE);
	if (res != FR_OK)
	{
		printf("AT+FILE=NFlash: 再次打开文件失败: 出错代码->%d\r\n", res);
		return  ERR_FALSE;
	}
	
	for (i=0;i<NANDFLASH_LEN;i++)
	{
		res = f_read(&fsrc, f_buffer, FBUF_SIZE, &bw);
		if (res != FR_OK)
		{
			printf("AT+FILE=NFlash: 读文件失败: 出错代码->%d\r\n", res);
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
			printf("AT+FILE=NFlash: 读%d页正确\r\n", i+1);
		}
		else
		{
			printf("AT+FILE=NFlash: 数据对比错误：出错页%d, 出错位置%d!\r\n", i, k);
			return  ERR_FALSE;
		}
        Delay_ms(20);
	}
	res = f_close(&fsrc);
    if (res != FR_OK)
	{
		printf("AT+FILE=NFlash: 关闭文件失败: 出错代码->%d\r\n", res);
		
		return  ERR_FALSE;
	}
	f_unmount(NFLASH_PATH);
    printf("\r\nAT+FILE=NFlash: 文件读写测试成功!\r\n\r\n");
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
	    UserVars.TaskRunStatus |= TASK_FILE_FLAG;     // 设置本任务运行状态标志
		Delay_ms(20);	                              // 延时20ms

/****************************************************************/
// 测试SPI FLash读写
/****************************************************************/
        #if ((SPIFLASH_EN>0)&&(SPIFLASH_MODE == 1)) // SPI FLASH使能并且利用FATFS文件系统进行读写
        if ((UserVars.LibSys.Flag&SPIFLASH_USB_FLAG)==0)  // 判断SPI FLASH没有被USB设置占用
        {
            UserVars.LibSys.Flag |= SPIFLASH_FATFS_FLAG;  // 设置SPI Flash被FatFS占用标志
            flag = disk_status(SPIFLASH_DISK);            // 读取SPI FLASH状态
            if ((SPIFlashFlag == 0)&&((flag&0x03)==0))    // 检测到SPI FLASH
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
            UserVars.LibSys.Flag &= ~SPIFLASH_FATFS_FLAG; // 清除SPI Flash被FatFS占用标志
        }
        #endif        

/****************************************************************/
// 测试SD卡读写
/****************************************************************/
        #if (SDCARD_EN > 0)               // SD卡配置使能
        if ((UserVars.LibSys.Flag&SD_USB_FLAG)==0)  // 判断SD卡没有被USB设置占用
        {            
            UserVars.LibSys.Flag |= SD_FATFS_FLAG;   // 设置SD卡被FatFS占用标志
            SPI_RequestOSSem(0);
            flag = SD_Ctrl(CMD_SD_STATUS,  0);       // 读取SD卡状态
            SPI_ReleaseOSSem();
            
            if ((flag&(SD_NODISK|SD_NOINIT)) == 0)	 // 检测到SD卡
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
                    //printf("AT+FILE=SD卡: 被拔掉\r\n");
                    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
                    {
                        printf("AT+SD=ERROR\r\n");  
                    }
                    #endif
                }
            }
            UserVars.LibSys.Flag &= ~SD_FATFS_FLAG;  // 清除SD卡被FatFS占用标志
        }
        #endif
/****************************************************************/
// 测试U盘读写
/****************************************************************/
        #if (USB_HOST_EN > 0)   // USB主机模式使能
        flag = USBH_Ctrl(USB_ID, CMD_USBH_SYNC, 0);
        if (flag&USBH_WORK_OK)	  // 检测到U盘
        {
             if(UDISKFlag == 0)           
             {
                 flag = UDISK_test(); 			  // 测试U盘读写
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
                 //printf("AT+FILE=U盘: 被拔掉\r\n");
                 if (UserVars.Para.ATFlag&AT_INFO_FLAG)
                 {
                    printf("AT+UDISK=ERROR\r\n");  
                 }
                 #endif
             }
        }
        #endif  
        
/****************************************************************/
// 测试Nand Flash读写
/****************************************************************/        
        #if ((MODULE_TYPE == STM32F103ZE)&&(NFLASH_EN > 0))
        if ((UserVars.LibSys.Flag&NFLASH_USB_FLAG)==0)  // 判断Nand Flash没有被USB设置占用
        { 
            UserVars.LibSys.Flag |= NFLASH_FATFS_FLAG;  // 设置Nand Flash被FatFS占用标志
            if (NFlashFlag==0)
            {
                 flag = NFlash_Ctrl(CMD_NFLASH_STATUS, 0);  // 读取Nand Flash状态
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
            UserVars.LibSys.Flag |= NFLASH_FATFS_FLAG;  // 清除Nand Flash被FatFS占用标志
        }
        #endif        
        
/****************************************************************/
// 测试USB设置模式下,用USB Mass Storage协议操作SD卡或SPI FLASH文件
/****************************************************************/       
        #if ((USB_DEVICE_EN > 0)&&(USB_MSC_EN > 0)) // USB设备模式使能及USB Mass Storage使能   
        USBD_Ctrl(USB_ID, CMD_USBD_SYNC, 0);	  // USB同步处理, 检测USB设备插入并启动USB, 监测USB设备拔出并关闭USB设备;
        #endif 
    }   
}

#endif
/***********************************************************************************/
// 文件结束
/***********************************************************************************/


	 