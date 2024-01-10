/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: TastIO.c
* Project  : STM32F1XX/4XX系列模块软件
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.00
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: 本文件负责IO输入输出任务处理;
*              1. DI输入测试程序
*              2. DO输出(包括继电器)测试程序
*              3. 读取按键测试程序
*              4. 读取拨码开关测试程序
*              5. RTC实时时钟测试程序
*              6. EEPROM读写测试程序
*              7. SPI接口FLASH读写测试程序
*              8. ALARM和LED测试程
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
1. IO类端口测试 
   (1). 在IO配置文件中定义RUN_LED, 蜂鸣器, DI端口, DO端口和K1-K8的IO引脚; 
   (2). 根据以上(1)配置, 在APP_Init.c中调用IO_APPInit()函数初始化所有IO; 
   本例程具体实现功能如下:
   (3). RUN LED间隔1秒闪烁;
   (4). 蜂鸣器间隔3秒响50ms;
   (5). DO间隔1秒输出1或0; 调用DO_Write()函数实现;
   (6). 监测DI输入是否有变化，有变化会打印输出DI输入的值; 调用DI_Read()函数实现;
   (7). 监测K1-K8按键是否有按下, 有按下则响一声蜂鸣器并打印输出按键按下信息; 调用Key_Read()函数实现;

2. RTC读写测试:
   (1). 功能参数配置说明: 在配置文件中做如下配置: 
        // STM32F107VC/103VE/103ZE 模块配置如下
        #define RTC_EN          1          // RTC使能, 1：打开使能， 0：关闭
        #define RTC_SECIT_EN    0          // RTC秒中断使能, 1：打开使能， 0：关闭	
        #define RTC_ALRIT_EN    0          // RTC闹钟中断使能, 1：打开使能， 0：关闭	
        
        // STM32F407VE 模块配置如下
        #define RTC_EN           1          // RTC使能, 1：打开使能， 0：关闭

        #define RTC_WKUPIT_EN    0         // RTC唤醒中断使能, 1：打开使能， 0：关闭	
        #define RTC_ALRAIT_EN    0         // RTC闹钟A中断使能, 1：打开使能， 0：关闭	
        #define RTC_ALRBIT_EN    0         // RTC闹钟B中断使能, 1：打开使能， 0：关闭	
        #define RTC_TSFIT_EN     0         // RTC时间戳中断使能, 1：打开使能， 0：关闭
        #define RTC_TAMP1IT_EN   0         // RTC入侵检测1中断使能, 1：打开使能， 0：关闭
        #define RTC_TAMP2IT_EN   0         // RTC入侵检测1中断使能, 1：打开使能， 0：关闭
        
   (2). 在APP_Init.c中调用RTC_APPInit()函数初始化; 
  
   (3). 本例程实现: 根据RTC断电标志, 来重新初始化RTC时间; 每隔3秒读取1次RTC时间，打印输出;
   
   (4). 如果想测试秒中断和闹钟中断将RTC_SECIT_EN和RTC_ALRIT_EN也设置为1, 闹钟定时5秒会产生中断

3. EEPROM读写测试：
   (1). 在IO配置文件中定义I2C1_SDA,I2C1_SCL引脚
   (2). 功能参数配置说明: 在配置文件中做如下配置: 
        #define EEPROM_EN          1          // EEPROM使能, 1：打开使能， 0：关闭
        #define EEPROM_DEVICE      AT24C64    // 定义器件型号	
        #define EEPROM_FREQ        100000     // 读写时钟频率
        注意: 以上配置默认不要修改
   (3). 根据以上(1)(2)配置, 在APP_Init.c中调用EEPROM_APPInit()函数初始化; 
   (4). 本例程调用EEPROM_Test()对0-255地址进行读写测试, 通过调试串口打印输出读写测试结果;
   注意: EEPROM最后512字节(地址范围:0x1E00~0x1FFF)用作系统IAP更新固件参数, 请不要操作该区域
   
   
4. SPI FLASH(W25QXX/AT45DB161)读写测试: 
   (1). 在IO配置文件中定义SPI1_SCK/MISO/MOSI/NSS(W25QXX_CS)引脚
   (2). 功能参数配置说明: 在配置文件中做如下配置: 
        #define SPIFLASH_EN            1        // SPI FLASH使能：1, 使能;  0, 关闭;
        #define SPIFLASH_MODE          0        // SPI FLASH操作方式：1, 利用FATFS文件系统进行读写;  0, 用SPI FLASH读写函数进行操作;
                                                // 注意:2种操作方式只能选择一种    
        #define SPIFLASH_TYPE          W25QXX   // SPI FLASH类型定义: W25QXX或AT45DBXX
   (3). 根据以上(1)(2)配置, 在APP_Init.c中调用SPIFlash_APPInit()函数初始化; 
   (4). 本例程调用W25QXX_Test()或AT45DBXX_Test()进行读写测试, 通过调试串口打印输出读写测试结果;

5. IO中断测试: 
   (1). 功能参数配置说明: 在配置文件中做如下配置, 以EXTI5参考: 
        // EXTI5中断配置
        #define EXTI5_EN        1		 // 中断或事件使能: 0,关闭中断和事件; 1, 打开中断; 2, 打开事件请求
        #define EXTI5_IO        PE5      // 在PA5, PB5, PC5, PD5, PE5, PF5, PG5, PH5, PI5 中选择一个IO作为中断输入口; 
        #define EXTI5_MODE      1		 // 触发中断和事件模式: 0,上升沿触发中断和事件; 1,下降沿触发中断和事件; 2,上升沿下降沿都触发中断和事件;
   (2). 根据以上(1)配置, 在APP_Init.c中调用EXTI_APPInit()函数初始化;
   (3). PE5(可以接按键)输入管脚如果有信号变化, 会产生中断, 通过调试串口打印输出中断结果;
   (4). 中断函数在ISRHook.c中的EXTI0_ISRHook()~EXTI15_ISRHook()
*/
/************************************************************************************/
// 引用外部头文件  
#include "config.h"	 
#if (TASK_IO_EN == 1)
#include "Vars.h"
#include "OSVars.h"
#include "UserVars.h"
#include "STM32Fxxx.h"
//#if (PRODUCT_TYPE == EMB8628I)
#include "CH455.h"
#include "GPIO_manager.h"
//#endif
/************************************************************************************/

/************************************************************************************/
// 常量及全局变量定义
/************************************************************************************/
// 定义按键键值
#define KNONE    0  // 没有按键按下
#define K1VAL    1  // K1按下
#define K2VAL    2  // K2按下
#define K3VAL    3  // K3按下
#define K4VAL    4  // K4按下
#define K5VAL    5  // K5按下
#define K6VAL    6  // K6按下
#define K7VAL    7  // K7按下
#define K8VAL    8  // K8按下

#define K9VAL    9   // K9按下
#define K10VAL   10  // K10按下
#define K11VAL   11  // K11按下
#define K12VAL   12  // K12按下
#define K13VAL   13  // K13按下
#define K14VAL   14  // K14按下
#define K15VAL   15  // K15按下
#define K16VAL   16  // K16按下

//定义标志位
#define K1FLAG   0x0001
#define K2FLAG   0x0002
#define K3FLAG   0x0004
#define K4FLAG   0x0008
#define K5FLAG   0x0010
#define K6FLAG   0x0020
#define K7FLAG   0x0040
#define K8FLAG   0x0080

#define K9FLAG    0x0100
#define K10FLAG   0x0200
#define K11FLAG   0x0400
#define K12FLAG   0x0800
#define K13FLAG   0x1000
#define K14FLAG   0x2000
#define K15FLAG   0x4000
#define K16FLAG   0x8000


// DI输入值标志位
// DI1-DI8
#define DI1FLAG   0x00000001
#define DI2FLAG   0x00000002
#define DI3FLAG   0x00000004
#define DI4FLAG   0x00000008
#define DI5FLAG   0x00000010
#define DI6FLAG   0x00000020
#define DI7FLAG   0x00000040
#define DI8FLAG   0x00000080

// DI9-DI16
#define DI9FLAG   0x00000100
#define DI10FLAG  0x00000200
#define DI11FLAG  0x00000400
#define DI12FLAG  0x00000800
#define DI13FLAG  0x00001000
#define DI14FLAG  0x00002000
#define DI15FLAG  0x00004000
#define DI16FLAG  0x00008000

// DI17-DI24
#define DI17FLAG  0x00010000
#define DI18FLAG  0x00020000
#define DI19FLAG  0x00040000
#define DI20FLAG  0x00080000
#define DI21FLAG  0x00100000
#define DI22FLAG  0x00200000
#define DI23FLAG  0x00400000
#define DI24FLAG  0x00800000

// DI25-DI32
#define DI25FLAG  0x01000000
#define DI26FLAG  0x02000000
#define DI27FLAG  0x04000000
#define DI28FLAG  0x08000000
#define DI29FLAG  0x10000000
#define DI30FLAG  0x20000000
#define DI31FLAG  0x40000000
#define DI32FLAG  0x80000000

#define DI_NONE   0xFFFFFFFF // DI输入无变化


// DO输出标志位
// DO1-DO8
#define DO1FLAG  0x00000001
#define DO2FLAG  0x00000002
#define DO3FLAG  0x00000004
#define DO4FLAG  0x00000008
#define DO5FLAG  0x00000010
#define DO6FLAG  0x00000020
#define DO7FLAG  0x00000040
#define DO8FLAG  0x00000080

// DO9-DO16
#define DO9FLAG   0x00000100
#define DO10FLAG  0x00000200
#define DO11FLAG  0x00000400
#define DO12FLAG  0x00000800
#define DO13FLAG  0x00001000
#define DO14FLAG  0x00002000
#define DO15FLAG  0x00004000
#define DO16FLAG  0x00008000

// DO17-DO24
#define DO17FLAG  0x00010000
#define DO18FLAG  0x00020000
#define DO19FLAG  0x00040000
#define DO20FLAG  0x00080000
#define DO21FLAG  0x00100000
#define DO22FLAG  0x00200000
#define DO23FLAG  0x00400000
#define DO24FLAG  0x00800000

// DO25-DO32
#define DO25FLAG  0x01000000
#define DO26FLAG  0x02000000
#define DO27FLAG  0x04000000
#define DO28FLAG  0x08000000
#define DO29FLAG  0x10000000
#define DO30FLAG  0x20000000
#define DO31FLAG  0x40000000
#define DO32FLAG  0x80000000

// EMB8616I中6个继电器控制DO标志位定义
#define JDQ1FLAG    0x00000001 // 用DO1控制
#define JDQ2FLAG    0x00000002 // 用DO2控制
#define JDQ3FLAG    0x00000004 // 用DO3控制
#define JDQ4FLAG    0x00000008 // 用DO4控制
#define JDQ5FLAG    0x00000010 // 用DO5控制
#define JDQ6FLAG    0x00000020 // 用DO6控制

/***********************************************************************************
* EEPROM读写测试配置
************************************************************************************/
#define EEPROM_START_ADDR   1000           // EEPROM读写起始地址
#define EEPROM_LEN          256            // EEPROM读写数据长度, 与设置缓存长度一致

/***********************************************************************************
* AT45DBXX(SPI FLASH)读写测试配置
************************************************************************************/
#if (SPIFLASH_TYPE  == AT45DBXX)
// 按页读写配置
#define AT45DBXX_START_PAGE   2000          // SPI FLASH读写起始页
#define AT45DBXX_PAGE_NUM     2             // SPI FLASH读写数据页数

// 按字节随机地址读写配置
#define AT45DBXX_START_ADDR   (AT45DBXX_START_PAGE*AT45DBXX_PAGE_SIZE+100)  // SPI FLASH读写起始地址
#define AT45DBXX_LEN          AT45DBXX_PAGE_SIZE                            // SPI FLASH读写数据长度(512字节), 与设置缓存长度一致

#endif
/***********************************************************************************
* W25QXX(SPI FLASH)读写测试配置
* 注意: 读写按页(256字节), 但擦除按扇区(4096字节)擦除, 每个扇区包含16个页
* 读写测试全部在扇区W25QXX_ZDY_STARTSECTOR里进行
************************************************************************************/
#if (SPIFLASH_TYPE  == W25QXX)
// 按页读写配置
#define W25QXX_START_PAGE   W25QXX_ZDY_STARTSECTOR*W25QXX_PAGE_PER_SECTOR   // W25QXX FLASH读写起始页
#define W25QXX_PAGE_NUM     16                        // W25QXX FLASH读写数据页数

// 按字节随机地址读写配置
#define W25QXX_START_ADDR   (W25QXX_START_PAGE*W25QXX_PAGE_SIZE+100)  // W25QXX FLASH读写起始地址
#define W25QXX_LEN          W25QXX_PAGE_SIZE                          // W25QXX FLASH读写数据长度(256字节), 与设置缓存长度一致

#endif
/***********************************************************************************
* Function: EEPROM_Test;
*
* Description: EEPROM读写测试  
*
* Input:  none;
*
* Output: none;
*
* Return: none;
*
* Note:   none;
************************************************************************************/
INT32S EEPROM_Test(void)
{
    INT16U i, len;
    INT32S flag;
    INT8U *p;

    p = (INT8U *)OSMalloc(EEPROM_LEN); // 申请内存
    if (p == 0)
    {
        return ERR_FALSE;
    } 
    
    // 初始化缓存数据: 0-255
    for(i=0;i<EEPROM_LEN;i++)		    
	{
        p[i] = i;			 	  
	}
	flag = EEPROM_Write(EEPROM_START_ADDR, p, EEPROM_LEN); // 从地址EEPROM_START_ADDR写入EEPROM_LEN字节数据
	if (flag == ERR_TRUE) // 判断写入正确
    {
        #if (DEBUG_APP_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            printf("AT+INFO=EEPROM从地址%d写入%d字节数据\r\n", EEPROM_START_ADDR, EEPROM_LEN); 
        }
        #endif        
        flag = EEPROM_Read(EEPROM_START_ADDR, p, EEPROM_LEN); // 从地址EEPROM_START_ADDR读取EEPROM_LEN字节数据
        if (flag == ERR_TRUE) // 判读读取正确
        {
            for(i=0;i<EEPROM_LEN;i++) // 对比数据
            {
                 if (p[i]!=(i&0xff))	
                 {
                     #if (DEBUG_APP_EN == 1)
                     if (UserVars.Para.ATFlag&AT_INFO_FLAG)
                     {
                         printf("AT+ERROR=EEPROM读写测试 ERROR, %d\r\n", i); 
                     }
                     #endif
                     OSFree(p);         // 释放内存
                     return ERR_FALSE;
                 }
            }
        }
    }
    #if (DEBUG_APP_EN == 1)
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {
            printf("AT+INFO=EEPROM读写测试 OK!\r\n\r\n");
        }
        else
        {
            printf("AT+ERROR=EEPROM读写测试 ERROR!\r\n\r\n");
        }
    }
    #endif
    
    OSFree(p);         // 释放内存
    return flag;
}

/***********************************************************************************
* Function: AT45DBXX_Test;
*
* Description: AT45DBXX(SPI FLASH)读写测试  
*
* Input:  none;
*
* Output: none;
*
* Return: none;
*
* Note:   none;
************************************************************************************/
#if (SPIFLASH_TYPE  == AT45DBXX)
INT32S AT45DBXX_Test(void)
{
    INT16U i, j;
    INT32S flag;
    INT32_TypeDef v;
    INT8U *p;
    
    if (SPI_RequestOSSem(2000) == ERR_TRUE)  // 获取SPI1的使用权
    {
        p = (INT8U *)OSMalloc(AT45DBXX_PAGE_SIZE);   // 申请内存
        if (p == 0)
        {
            return ERR_FALSE;
        } 
                
        v.d = AT45DBXX_Ctrl(CMD_AT45DBXX_RDID, 0);
        #if (DEBUG_APP_EN == 1)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {    
            printf("AT+INFO=SPIFLASH读写测试: 厂家,%02X; 器件ID,%02X %02X %02X\r\n", v.chars.c3, v.chars.c2, v.chars.c1, v.chars.c0); 
        }
        #endif
        // printf("正在测试SPI Flash, 请等待...%02X\r\n", SPIFlash.Status); 
    /***************************************************************************************************
    // 按一整页读写Flash测试    
    ***************************************************************************************************/   
        for(i=0;i<AT45DBXX_PAGE_SIZE;i++)	// 初始化缓存数据: 0-255
        {
            p[i] = i&0xff;			 	  
        }
        
        for (i=0; i<AT45DBXX_PAGE_NUM; i++)
        {
            flag = AT45DBXX_WritePage(p, i+AT45DBXX_START_PAGE, 1);  // 将SysPara.Databuf内数据写入SPI FLASH页里
            if (flag != ERR_TRUE)
            {
                #if (DEBUG_APP_EN == 1)
                if (UserVars.Para.ATFlag&AT_INFO_FLAG)
                {
                    printf("AT+ERROR=SPIFLASH写512字节到%d页, ERROR!\r\n", i+AT45DBXX_START_PAGE); 
                }
                #endif
            }
        }
        
        for (i=0; i<AT45DBXX_PAGE_NUM; i++)
        {
            flag = AT45DBXX_ReadPage(p, i+AT45DBXX_START_PAGE, 1);  //读取 SPI FLASH页里数据读入到Databuf中
            if (flag != ERR_TRUE)
            {
                 #if (DEBUG_APP_EN == 1)
                 if (UserVars.Para.ATFlag&AT_INFO_FLAG)
                 {
                     printf("AT+ERROR=SPIFLASH读取%d页, ERROR!\r\n", i+AT45DBXX_START_PAGE); 
                 }
                 #endif
                 SPI_ReleaseOSSem();       // 释放SPI1使用权
                 OSFree(p);         // 释放内存
                 return ERR_FALSE;
            }        
            for(j=0; j<AT45DBXX_PAGE_SIZE; j++)
            {
                if (p[j] != (j&0xff))	
                {
                    #if (DEBUG_APP_EN == 1)
                    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
                    {
                        printf("AT+ERROR=SPIFLASH数据对比, ERROR!, %d\r\n", j); 
                    }
                    #endif
                    SPI_ReleaseOSSem();       // 释放SPI1使用权
                    OSFree(p);         // 释放内存
                    return ERR_FALSE;
                }
            }
        }    
        #if (DEBUG_APP_EN == 1)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            printf("AT+INFO=SPIFLASH按页读写测试 OK!\r\n");
        }
        #endif
    /***************************************************************************************************
    // 随机地址读写Flash测试    
    ***************************************************************************************************/   
        for(i=0;i<AT45DBXX_LEN;i++)	// 初始化缓存数据: 0-255
        {
            p[i] = i&0xff;			 	  
        }
        
        flag = AT45DBXX_Write(p, AT45DBXX_START_ADDR, AT45DBXX_LEN);  // 将Databuf内数据写入地址SPIFLASH_START_ADDR开始的FLASH里
        if (flag != ERR_TRUE)
        {
             #if (DEBUG_APP_EN == 1)
             if (UserVars.Para.ATFlag&AT_INFO_FLAG)
             {
                 printf("AT+ERROR=SPIFLASH随机地址写入数据, ERROR!\r\n");
             }
             #endif
             SPI_ReleaseOSSem();       // 释放SPI1使用权
             OSFree(p);         // 释放内存
             return ERR_FALSE;
        }
        Delay_ms(20);
        
        flag = AT45DBXX_Read(p, AT45DBXX_START_ADDR, AT45DBXX_LEN);  // 读取数据到Databuf里
        if (flag != ERR_TRUE)
        {         
             #if (DEBUG_APP_EN == 1)
             if (UserVars.Para.ATFlag&AT_INFO_FLAG)
             {
                 printf("AT+ERROR=SPIFLASH随机地址读取数据, ERROR!\r\n");
             }
             #endif
             SPI_ReleaseOSSem();       // 释放SPI1使用权
             OSFree(p);         // 释放内存
             return ERR_FALSE;
        }
        
        for(i=0;i<AT45DBXX_LEN;i++)
        {
            if (p[i]!=(i&0xff))	
            {
                #if (DEBUG_APP_EN == 1)
                if (UserVars.Para.ATFlag&AT_INFO_FLAG)
                {
                    printf("AT+ERROR=SPIFLASH对比数据, ERROR, %d\r\n", i); 
                }
                #endif
                SPI_ReleaseOSSem();       // 释放SPI1使用权
                OSFree(p);         // 释放内存
                return ERR_FALSE;
            }
        }
        #if (DEBUG_APP_EN == 1)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            printf("AT+INFO=SPIFLASH随机地址读写测试 OK!\r\n");  
        }
        #endif
        SPI_ReleaseOSSem();       // 释放SPI1使用权
        OSFree(p);         // 释放内存
        return ERR_TRUE;
    }
    return ERR_FALSE;        
}
#endif

/***********************************************************************************
* Function: W25QXX_Test;
*
* Description: W25QXX(SPI FLASH)读写测试  
*
* Input:  none;
*
* Output: none;
*
* Return: none;
*
* Note:   none;
************************************************************************************/
#if (SPIFLASH_TYPE  == W25QXX)
INT32S W25QXX_Test(void)
{
    INT32U i, j;
    INT32S flag;
    INT32_TypeDef v;
    INT8U *p;
    
    if (SPI_RequestOSSem(2000) == ERR_TRUE)  // 获取SPI1的使用权
    {     
        p = (INT8U *)OSMalloc(W25QXX_PAGE_SIZE);   // 申请内存
        if (p == 0)
        {
            return ERR_FALSE;
        } 
        
        v.d = W25QXX_Ctrl(CMD_AT45DBXX_RDID, 0);
        #if (DEBUG_APP_EN == 1)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            printf("AT+INFO=SPIFLASH厂家代号:%02X; 器件ID:%02X %02X\r\n", v.chars.c2, v.chars.c1, v.chars.c0); 
        }
        #endif
    /***************************************************************************************************
    // 按一整页读写Flash测试    
    ***************************************************************************************************/   
        for(i=0;i<W25QXX_PAGE_SIZE;i++)	// 初始化缓存数据: 0-255
        {
            p[i] = i&0xff;			 	  
        }
        W25QXX_Ctrl(CMD_W25QXX_SECTOR_ERASE, W25QXX_ZDY_STARTSECTOR);               // 擦除W25QXX_ZDY_STARTSECTOR扇区
        for (i=0; i<W25QXX_PAGE_NUM; i++)
        {
            flag = W25QXX_WritePage(p, (i+W25QXX_START_PAGE)*256, W25QXX_PAGE_SIZE);  // 将SysPara.Databuf内数据写入SPI FLASH页里
            if (flag != ERR_TRUE)
            {
                #if (DEBUG_APP_EN == 1)
                if (UserVars.Para.ATFlag&AT_INFO_FLAG)
                {
                    printf("AT+ERROR=SPIFLASH写%d字节到%d页 ERROR!\r\n", W25QXX_PAGE_SIZE, i+W25QXX_START_PAGE); 
                }
                #endif
            }
        }
        for (i=0; i<W25QXX_PAGE_NUM; i++)
        {
            flag = W25QXX_Read(p, (i+W25QXX_START_PAGE)*256, W25QXX_PAGE_SIZE);  //读取 SPI FLASH页里数据读入到Databuf中
            if (flag != ERR_TRUE)
            {
                 #if (DEBUG_APP_EN == 1)
                 if (UserVars.Para.ATFlag&AT_INFO_FLAG)
                 {
                     printf("AT+ERROR=SPIFLASH读取%d页 ERROR!\r\n", i+W25QXX_START_PAGE); 
                 }
                 #endif
                 SPI_ReleaseOSSem();       // 释放SPI1使用权
                 OSFree(p);         // 释放内存
                 return ERR_FALSE;
            }        
            for(j=0; j<W25QXX_PAGE_SIZE; j++)
            {
                if (p[j] != (j&0xff))	
                {
                    #if (DEBUG_APP_EN == 1)
                    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
                    {
                        printf("AT+ERROR=SPIFLASH数据对比 ERROR!, %d\r\n", j); 
                    }
                    #endif
                    SPI_ReleaseOSSem();       // 释放SPI1使用权
                    OSFree(p);         // 释放内存
                    return ERR_FALSE;
                }
            }
        }    
        #if (DEBUG_APP_EN == 1)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            printf("AT+INFO=SPIFLASH按页读写测试 OK!\r\n");
        }
        #endif
    /***************************************************************************************************
    // 随机地址读写Flash测试    
    ***************************************************************************************************/   
        for(i=0;i<W25QXX_LEN;i++)	// 初始化缓存数据: 0-255
        {
            p[i] = i&0xff;			 	  
        }        
        W25QXX_Ctrl(CMD_W25QXX_SECTOR_ERASE, W25QXX_ZDY_STARTSECTOR);               // 擦除W25QXX_ZDY_STARTSECTOR扇区
        flag = W25QXX_Write(p, W25QXX_START_ADDR, W25QXX_LEN);  // 将Databuf内数据写入地址SPIFLASH_START_ADDR开始的FLASH里
        if (flag != ERR_TRUE)
        {
             #if (DEBUG_APP_EN == 1)
             if (UserVars.Para.ATFlag&AT_INFO_FLAG)
             {
                 printf("AT+ERROR=SPIFLASH随机地址写入数据, ERROR!\r\n");
             }
             #endif
             SPI_ReleaseOSSem();       // 释放SPI1使用权
             OSFree(p);         // 释放内存
             return ERR_FALSE;
        }    
        flag = W25QXX_Read(p, W25QXX_START_ADDR, W25QXX_LEN);  // 读取数据到Databuf里
        if (flag != ERR_TRUE)
        {         
             #if (DEBUG_APP_EN == 1)
             if (UserVars.Para.ATFlag&AT_INFO_FLAG)
             {
                 printf("AT+ERROR=SPIFLASH随机地址读取数据 ERROR!\r\n");
             }
             #endif
             SPI_ReleaseOSSem();       // 释放SPI1使用权
             OSFree(p);         // 释放内存
             return ERR_FALSE;
        }
        
        for(i=0;i<W25QXX_LEN;i++)
        {
            if (p[i]!=(i&0xff))	
            {
                #if (DEBUG_APP_EN == 1)
                if (UserVars.Para.ATFlag&AT_INFO_FLAG)
                {
                    printf("AT+ERROR=SPIFLASH随机读写对比数据 ERROR, %d\r\n", i); 
                }        
                #endif    
                SPI_ReleaseOSSem();       // 释放SPI1使用权
                OSFree(p);         // 释放内存
                return ERR_FALSE;
            }
        }    
        #if (DEBUG_APP_EN == 1)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            printf("AT+INFO=SPIFLASH随机地址读写测试 OK!\r\n\r\n");  
        }
        #endif
        SPI_ReleaseOSSem();       // 释放SPI1使用权
        OSFree(p);         // 释放内存
        return ERR_TRUE;
    }
    return ERR_FALSE;
}
#endif

/***********************************************************************************
* Function: SW_Read;
*
* Description: 拨码开关读取函数;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   对于拨码开关读到0,表示ON; 读到1代表OFF;
************************************************************************************/
INT16U SW_Read(void)
{
    INT8U val;
    INT16U sw;

    sw = 0;
// 读取拨码开关S1
#ifdef SW1 
	val = IO_Read(SW1);
	if (val)
	{
	    sw |= 0x01;
    }
#endif	

// 读取拨码开关S2
#ifdef SW2 
	val = IO_Read(SW2);
	if (val)
	{
	    sw |= 0x02;
    }
#endif	

    // 读取拨码开关S3
#ifdef SW3 
	val = IO_Read(SW3);
	if (val)
	{
	    sw |= 0x04;
    }
#endif	

    // 读取拨码开关S4
#ifdef SW4 
	val = IO_Read(SW4);
	if (val)
	{
	    sw |= 0x08;
    }
#endif	

    // 读取拨码开关S5
#ifdef SW5 
	val = IO_Read(SW5);
	if (val)
	{
	    sw |= 0x10;
    }
#endif	

    // 读取拨码开关S6
#ifdef SW6 
	val = IO_Read(SW6);
	if (val)
	{
	    sw |= 0x20;
    }
#endif	

    // 读取拨码开关S7
#ifdef SW7 
	val = IO_Read(SW7);
	if (val)
	{
	    sw |= 0x40;
    }
#endif	

    // 读取拨码开关S8
#ifdef SW8 
	val = IO_Read(SW8);
	if (val)
	{
	    sw |= 0x80;
    }
#endif	
	return sw;
}

/***********************************************************************************
* Function: DI_SPIRead;
*
* Description: SPI总线读取DI输入函数;
* 
* Input:  p, 输入数据指针; len, 数据长度
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
#if ((DI1_8SPI_EN > 0)||(DI9_16SPI_EN > 0)||(DI17_24SPI_EN > 0)||(DI25_32SPI_EN > 0))   
void DI_SPIRead(INT8U *p, INT8U len)
{
	INT8U i;
    
    // 移位锁定输入IO
    IO_Write(HC597_STB, 0);
    Delay_us(1);
    IO_Write(HC597_STB, 1);  	
    Delay_us(1);
    IO_Write(HC597_LOAD, 0);
    Delay_us(1);
    IO_Write(HC597_LOAD, 1);
    
    if (SPI_RequestOSSem(1000) == ERR_TRUE)  // 获取SPI1的使用权
    {         
        // SPI读取数值
        #ifdef HC597_CS
        IO_Write(HC597_CS, 1);
        #endif
        for(i=0; i<len; i++)
        {
            *p++ = SPI_ReadWriteByte(SPI1_ID, 0);		//读取输入
        }
        #ifdef HC597_CS
        IO_Write(HC597_CS, 0);
        #endif
        SPI_ReleaseOSSem();
    }	
}
#endif
/***********************************************************************************
* Function: DO_SPIWrite;
*
* Description: 控制SPI总线转并口DO输出函数;
* 
* Input:  p, 输出数据指针; len, 数据长度
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
#if ((DO1_8SPI_EN > 0)||(DO9_16SPI_EN > 0)||(DO17_24SPI_EN > 0)||(DO25_32SPI_EN > 0))  
void DO_SPIWrite(INT8U *p, INT8U len)
{
	INT8U i;
    
    if (SPI_RequestOSSem(1000) == ERR_TRUE)
    {  
        #ifdef HC595_ENA
        IO_Write(HC595_ENA, 0);                          // 输出使能
        #endif
        
        // SPI写入数值
        for (i=0; i<len; i++)
        {
            #if ((PRODUCT_TYPE == EMB8616I)||(PRODUCT_TYPE == EMB8626I))  // Modify 2019.5.22
            SPI_ReadWriteByte(SPI1_ID, p[len-i-1]);
            #else
            SPI_ReadWriteByte(SPI1_ID, *p++);
            #endif        
        }
        
        // 移位锁定输出IO
        IO_Write(HC595_STB, 0);
        Delay_us(1);
        IO_Write(HC595_STB, 1);
        
        SPI_ReleaseOSSem();
    }
    
}
#endif

/***********************************************************************************
* Function: DO_Write;
*
* Description: 控制DO输出;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   本函数支持16个DO1-DO16输出, 用户可以参照这个增加更多DO输出;
*         本函数同时支持32个SPI总线转并口DO1-DO32输出
************************************************************************************/
void DO_Write(INT32U DOVal)
{
    INT8U DOBuf[4];
    INT8U Num;
    
// DO1输出
#ifdef DO1    
    if (DOVal&DO1FLAG)
    {
        IO_Write(DO1, 1);  
    }
    else
    {
        IO_Write(DO1, 0);
    }
#endif
    
// DO2输出
#ifdef DO2     
    if (DOVal&DO2FLAG)
    {
        IO_Write(DO2, 1);  
    }
    else
    {
        IO_Write(DO2, 0);
    }
#endif
    
// DO3输出
#ifdef DO3 
    if (DOVal&DO3FLAG)
    {
        IO_Write(DO3, 1);  
    }
    else
    {
        IO_Write(DO3, 0);
    }
    #endif
    
// DO4输出
#ifdef DO4 
    if (DOVal&DO4FLAG)
    {
        IO_Write(DO4, 1);  
    }
    else
    {
        IO_Write(DO4, 0);
    }
#endif

// DO5输出
#ifdef DO5 
    if (DOVal&DO5FLAG)
    {
        IO_Write(DO5, 1);  
    }
    else
    {
        IO_Write(DO5, 0);
    }
#endif

// DO6输出
#ifdef DO6 
    if (DOVal&DO6FLAG)
    {
        IO_Write(DO6, 1);  
    }
    else
    {
        IO_Write(DO6, 0);
    }
#endif

// DO7输出
#ifdef DO7 
    if (DOVal&DO7FLAG)
    {
        IO_Write(DO7, 1);  
    }
    else
    {
        IO_Write(DO7, 0);
    }
#endif

// DO8输出
#ifdef DO8 
    if (DOVal&DO8FLAG)
    {
        IO_Write(DO8, 1);  
    }
    else
    {
        IO_Write(DO8, 0);
    }
#endif
	
// DO9输出
#ifdef DO9 
    if (DOVal&DO9FLAG)
    {
        IO_Write(DO9, 1);  
    }
    else
    {
        IO_Write(DO9, 0);
    }
#endif	
	
// DO10输出
#ifdef DO10 
    if (DOVal&DO10FLAG)
    {
        IO_Write(DO10, 1);  
    }
    else
    {
        IO_Write(DO10, 0);
    }
#endif	
	
// DO11输出
#ifdef DO11 
    if (DOVal&DO11FLAG)
    {
        IO_Write(DO11, 1);  
    }
    else
    {
        IO_Write(DO11, 0);
    }
#endif

// DO12输出
#ifdef DO12 
    if (DOVal&DO12FLAG)
    {
        IO_Write(DO12, 1);  
    }
    else
    {
        IO_Write(DO12, 0);
    }
#endif

// DO13输出
#ifdef DO13 
    if (DOVal&DO13FLAG)
    {
        IO_Write(DO13, 1);  
    }
    else
    {
        IO_Write(DO13, 0);
    }
#endif

// DO14输出
#ifdef DO14 
    if (DOVal&DO14FLAG)
    {
        IO_Write(DO14, 1);  
    }
    else
    {
        IO_Write(DO14, 0);
    }
#endif
// DO15输出
#ifdef DO15 
    if (DOVal&DO15FLAG)
    {
        IO_Write(DO15, 1);  
    }
    else
    {
        IO_Write(DO15, 0);
    }
#endif

// DO16输出
#ifdef DO16 
    if (DOVal&DO16FLAG)
    {
        IO_Write(DO16, 1);  
    }
    else
    {
        IO_Write(DO16, 0);
    }
#endif	
    
// DO17输出
#ifdef DO17 
    if (DOVal&DO17FLAG)
    {
        IO_Write(DO17, 1);  
    }
    else
    {
        IO_Write(DO17, 0);
    }
#endif	    
    
// DO18输出
#ifdef DO18 
    if (DOVal&DO18FLAG)
    {
        IO_Write(DO18, 1);  
    }
    else
    {
        IO_Write(DO18, 0);
    }
#endif	    

// DO19输出
#ifdef DO19 
    if (DOVal&DO19FLAG)
    {
        IO_Write(DO19, 1);  
    }
    else
    {
        IO_Write(DO19, 0);
    }
#endif	    

// DO20输出
#ifdef DO20 
    if (DOVal&DO20FLAG)
    {
        IO_Write(DO20, 1);  
    }
    else
    {
        IO_Write(DO20, 0);
    }
#endif	    
    
 // DO21输出
#ifdef DO21 
    if (DOVal&DO21FLAG)
    {
        IO_Write(DO21, 1);  
    }
    else
    {
        IO_Write(DO21, 0);
    }
#endif	   
    
// 以下是SPI总线转并口DO输出
    Num = 0;
#if (DO1_8SPI_EN > 0)       // SPI总线转并口DO1-8使能
    DOBuf[Num++] = DOVal&0xff;
#endif
    
#if (DO9_16SPI_EN > 0)      // SPI总线转并口DO9-16使能
    DOBuf[Num++] = (DOVal>>8)&0xff;
#endif
    
#if (DO17_24SPI_EN > 0)     // SPI总线转并口DO17-24使能
    DOBuf[Num++] = (DOVal>>16)&0xff;
#endif

#if (DO25_32SPI_EN > 0)     // SPI总线转并口DO25-32使能  
    DOBuf[Num++] = (DOVal>>24)&0xff;
#endif

#if ((DO9_16SPI_EN > 0)||(DO1_8SPI_EN > 0)||(DO17_24SPI_EN > 0)||(DO25_32SPI_EN > 0))   
    if (Num > 0)
    {
        DO_SPIWrite(DOBuf, Num);  
    }
#endif    
}

/***********************************************************************************
* Function: DI_Read;
*
* Description: 读取DI输入值;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: 返回ERR_TRUE, DI有变化; 返回ERR_FALSE, DI无有变化; UserVars.DI：实际DI值;
*
* Note:   已经加了20ms防抖处理; 本函数支持16个DI1-DI16读取, 用户可以参照这个增加更多DI读取;
*         本函数同时支持32个SPI总线读取DI1-DI32输入(无防抖处理)
************************************************************************************/
INT32S DI_Read(void)
{
	INT32U val, DIVal, DI;
  INT8U Num, DIBuf[4], i;
    
    
	DI = 0;
// 读取DI1输入值    
#ifdef DI1
    if (IO_Read(DI1)>0)
    {
        DI |= DI1FLAG;
	}		 
#endif
// 读取DI2输入值    
#ifdef DI2
    if (IO_Read(DI2)>0)
	{
		DI |= DI2FLAG;
	}		 
#endif
// 读取DI3输入值    
#ifdef DI3
    if (IO_Read(DI3)>0)
	{
		DI |= DI3FLAG;
	}		 
#endif
// 读取DI4输入值    
#ifdef DI4
    if (IO_Read(DI4)>0)
    {
		DI |= DI4FLAG;
    }		 
#endif 
// 读取DI5输入值    
#ifdef DI5
    if (IO_Read(DI5)>0)
	{
		DI |= DI5FLAG;
	}		 
#endif
// 读取DI6输入值    
#ifdef DI6
    if (IO_Read(DI6)>0)
	{
		DI |= DI6FLAG;
	}		 
#endif
// 读取DI7输入值    
#ifdef DI7
    if (IO_Read(DI7)>0)
	{
		DI |= DI7FLAG;
	}		 
#endif
// 读取DI8输入值    
#ifdef DI8
    if (IO_Read(DI8)>0)
	{
		DI |= DI8FLAG;
	}		 
#endif
// 读取DI9输入值    
#ifdef DI9
    if (IO_Read(DI9)>0)
	{
		DI |= DI9FLAG;
	}		 
#endif
// 读取DI10输入值    
#ifdef DI10
    if (IO_Read(DI10)>0)
	{
		DI |= DI10FLAG;
	}		 
#endif
// 读取DI11输入值    
#ifdef DI11
    if (IO_Read(DI11)>0)
	{
		DI |= DI11FLAG;
	}		 
#endif
// 读取DI12输入值    
#ifdef DI12
    if (IO_Read(DI12)>0)
	{
		DI |= DI12FLAG;
	}		 
#endif
// 读取DI13输入值    
#ifdef DI13
    if (IO_Read(DI13)>0)
	{
		DI |= DI13FLAG;
	}		 
#endif
// 读取DI14输入值    
#ifdef DI14
    if (IO_Read(DI14)>0)
	{
		DI |= DI14FLAG;
	}		 
#endif
// 读取DI15输入值    
#ifdef DI15
    if (IO_Read(DI15)>0)
	{
		DI |= DI15FLAG;
	}		 
#endif
// 读取DI6输入值    
#ifdef DI16
    if (IO_Read(DI16)>0)
	{
		DI |= DI16FLAG;
	}		 
#endif
    DIVal = UserVars.DI; // 读取上次存储的DI值 
	if (DI != (UserVars.DI&0xff)) // DI输入有变化
	{
        Delay_ms(20);      // 延时20ms防抖	
        // 再次读取DI1输入值    
		#ifdef DI1
        if ((DI&DI1FLAG) != (UserVars.DI&DI1FLAG)) // 判断DI1有变化
        {
              val = IO_Read(DI1);  // 再次读取DI1 
              if (DI&DI1FLAG)      // DI1=1
              {
                    if (val == 1)	   // 再次读DI1还是为1
                        {
                            UserVars.DI |= DI1FLAG;  // 判定DI1=1,并记录
                        }								
                }
                else								 // DI1=0
                {
                        if (val == 0)    // 再次读DI1还是为0
                        {
                            UserVars.DI &= ~DI1FLAG;  // 判定DI1=0,并记录
                        }
                }			
        }		 
		#endif

        // 再次读取DI2输入值    
		#ifdef DI2
        if ((DI&DI2FLAG) != (UserVars.DI&DI2FLAG)) // 判断DI2有变化
        {
            val = IO_Read(DI2);  // 再次读取DI2 
            if (DI&DI2FLAG)      // DI2=1
            {
                if (val == 1)	   // 再次读DI2还是为1
                {
                    UserVars.DI |= DI2FLAG;  // 判定DI2=1,并记录
                }								
            }
            else								 // DI2=0
            {
                if (val == 0)    // 再次读DI2还是为0
                {
                    UserVars.DI &= ~DI2FLAG;  // 判定DI2=0,并记录
                }
            }			
        }		 
		#endif

      // 再次读取DI3输入值    
        #ifdef DI3
        if ((DI&DI3FLAG) != (UserVars.DI&DI3FLAG)) // 判断DI3有变化
        {
            val = IO_Read(DI3);  // 再次读取DI3 
            if (DI&DI3FLAG)      // DI3=1
            {
                if (val == 1)	   // 再次读DI3还是为1
                {
                    UserVars.DI |= DI3FLAG;  // 判定DI3=1,并记录
                }								
            }
            else								 // DI3=0
            {
                if (val == 0)    // 再次读DI3还是为0
                {
                    UserVars.DI &= ~DI3FLAG;  // 判定DI3=0,并记录
                }
            }			
        }		 
        #endif	
	
      // 再次读取DI4输入值    
		#ifdef DI4
        if ((DI&DI4FLAG) != (UserVars.DI&DI4FLAG)) // 判断DI4有变化
        {
            val = IO_Read(DI4);  // 再次读取DI4 
            if (DI&DI4FLAG)      // DI4=1
            {
                if (val == 1)	   // 再次读DI4还是为1
                {
                    UserVars.DI |= DI4FLAG;  // 判定DI4=1,并记录
                }								
            }
            else								 // DI4=0
            {
                if (val == 0)    // 再次读DI4还是为0
                {
                    UserVars.DI &= ~DI4FLAG;  // 判定DI4=0,并记录
                }
            }			
        }		 
		#endif	

      // 再次读取DI5输入值    
		#ifdef DI5
        if ((DI&DI5FLAG) != (UserVars.DI&DI5FLAG)) // 判断DI5有变化
        {
            val = IO_Read(DI5);  // 再次读取DI5 
            if (DI&DI5FLAG)      // DI5=1
            {
                if (val == 1)	   // 再次读DI5还是为1
                {
                    UserVars.DI |= DI5FLAG;  // 判定DI5=1,并记录
                }								
            }
            else								 // DI5=0
            {
                if (val == 0)    // 再次读DI5还是为0
                {
                    UserVars.DI &= ~DI5FLAG;  // 判定DI5=0,并记录
                }
            }			
        }		 
		#endif	
			
      // 再次读取DI6输入值    
		#ifdef DI6
        if ((DI&DI6FLAG) != (UserVars.DI&DI6FLAG)) // 判断DI6有变化
        {
            val = IO_Read(DI6);  // 再次读取DI6 
            if (DI&DI6FLAG)      // DI6=1
            {
                if (val == 1)	   // 再次读DI6还是为1
                {
                    UserVars.DI |= DI6FLAG;  // 判定DI6=1,并记录
                }								
            }
            else								 // DI6=0
            {
                if (val == 0)    // 再次读DI6还是为0
                {
                    UserVars.DI &= ~DI6FLAG;  // 判定DI6=0,并记录
                }
            }			
        }		 
		#endif			
			
      // 再次读取DI7输入值    
        #ifdef DI7
        if ((DI&DI7FLAG) != (UserVars.DI&DI7FLAG)) // 判断DI7有变化
        {
            val = IO_Read(DI7);  // 再次读取DI7 
            if (DI&DI7FLAG)      // DI7=1
            {
                if (val == 1)	   // 再次读DI7还是为1
                {
                    UserVars.DI |= DI7FLAG;  // 判定DI7=1,并记录
                }								
            }
            else								 // DI7=0
            {
                if (val == 0)    // 再次读DI7还是为0
                {
                    UserVars.DI &= ~DI7FLAG;  // 判定DI7=0,并记录
                }
            }			
        }		 
        #endif			
	
      // 再次读取DI8输入值    
        #ifdef DI8
        if ((DI&DI8FLAG) != (UserVars.DI&DI8FLAG)) // 判断DI8有变化
        {
            val = IO_Read(DI8);  // 再次读取DI8 
            if (DI&DI8FLAG)      // DI8=1
            {
                if (val == 1)	   // 再次读DI8还是为1
                {
                    UserVars.DI |= DI8FLAG;  // 判定DI8=1,并记录
                }								
            }
            else								 // DI8=0
            {
                if (val == 0)    // 再次读DI8还是为0
                {
                    UserVars.DI &= ~DI8FLAG;  // 判定DI8=0,并记录
                }
            }			
        }		 
        #endif	
			
      // 再次读取DI9输入值    
		#ifdef DI9
        if ((DI&DI9FLAG) != (UserVars.DI&DI9FLAG)) // 判断DI9有变化
        {
            val = IO_Read(DI9);  // 再次读取DI9 
            if (DI&DI9FLAG)      // DI9=1
            {
                if (val == 1)	   // 再次读DI9还是为1
                {
                    UserVars.DI |= DI9FLAG;  // 判定DI9=1,并记录
                }								
            }
            else								 // DI9=0
            {
                if (val == 0)    // 再次读DI9还是为0
                {
                    UserVars.DI &= ~DI9FLAG;  // 判定DI9=0,并记录
                }
            }			
        }		 
		#endif			

      // 再次读取DI10输入值    
		#ifdef DI10
        if ((DI&DI10FLAG) != (UserVars.DI&DI10FLAG)) // 判断DI10有变化
        {
            val = IO_Read(DI10);  // 再次读取DI10 
            if (DI&DI10FLAG)      // DI10=1
            {
                if (val == 1)	   // 再次读DI10还是为1
                {
                    UserVars.DI |= DI10FLAG;  // 判定DI10=1,并记录
                }								
            }
            else								 // DI10=0
            {
                if (val == 0)    // 再次读DI10还是为0
                {
                    UserVars.DI &= ~DI10FLAG;  // 判定DI10=0,并记录
                }
            }			
        }		 
		#endif
			
      // 再次读取DI11输入值    
		#ifdef DI11
        if ((DI&DI11FLAG) != (UserVars.DI&DI11FLAG)) // 判断DI11有变化
        {
            val = IO_Read(DI11);  // 再次读取DI11 
            if (DI&DI11FLAG)      // DI11=1
            {
                if (val == 1)	   // 再次读DI11还是为1
                {
                    UserVars.DI |= DI11FLAG;  // 判定DI11=1,并记录
                }								
            }
            else								 // DI11=0
            {
                if (val == 0)    // 再次读DI11还是为0
                {
                    UserVars.DI &= ~DI11FLAG;  // 判定DI11=0,并记录
                }
            }			
        }		 
		#endif
			
      // 再次读取DI12输入值    
		  #ifdef DI12
        if ((DI&DI12FLAG) != (UserVars.DI&DI12FLAG)) // 判断DI12有变化
        {
            val = IO_Read(DI12);  // 再次读取DI12 
            if (DI&DI12FLAG)      // DI12=1
            {
                if (val == 1)	   // 再次读DI12还是为1
                {
                    UserVars.DI |= DI12FLAG;  // 判定DI12=1,并记录
                }								
            }
            else								 // DI12=0
            {
                if (val == 0)    // 再次读DI12还是为0
                {
                    UserVars.DI &= ~DI12FLAG;  // 判定DI12=0,并记录
                }
            }			
        }		 
		  #endif

      // 再次读取DI13输入值    
		#ifdef DI13
        if ((DI&DI13FLAG) != (UserVars.DI&DI13FLAG)) // 判断DI13有变化
        {
            val = IO_Read(DI13);  // 再次读取DI13 
            if (DI&DI13FLAG)      // DI13=1
            {
                if (val == 1)	   // 再次读DI13还是为1
                {
                    UserVars.DI |= DI13FLAG;  // 判定DI13=1,并记录
                }								
            }
            else								 // DI13=0
            {
                if (val == 0)    // 再次读DI13还是为0
                {
                    UserVars.DI &= ~DI13FLAG;  // 判定DI13=0,并记录
                }
            }			
        }		 
		#endif			

      // 再次读取DI14输入值    
		#ifdef DI14
        if ((DI&DI14FLAG) != (UserVars.DI&DI14FLAG)) // 判断DI14有变化
        {
            val = IO_Read(DI14);  // 再次读取DI14 
            if (DI&DI14FLAG)      // DI14=1
            {
                if (val == 1)	   // 再次读DI14还是为1
                {
                    UserVars.DI |= DI14FLAG;  // 判定DI14=1,并记录
                }								
            }
            else								 // DI14=0
            {
                if (val == 0)    // 再次读DI14还是为0
                {
                    UserVars.DI &= ~DI14FLAG;  // 判定DI14=0,并记录
                }
            }			
        }		 
		#endif	

		// 再次读取DI15输入值    
		#ifdef DI15
        if ((DI&DI15FLAG) != (UserVars.DI&DI15FLAG)) // 判断DI15有变化
        {
            val = IO_Read(DI15);  // 再次读取DI15
            if (DI&DI15FLAG)      // DI15=1
            {
                if (val == 1)	   // 再次读DI15还是为1
                {
                    UserVars.DI |= DI15FLAG;  // 判定DI15=1,并记录
                }								
            }
            else								 // DI15=0
            {
                if (val == 0)    // 再次读DI15还是为0
                {
                    UserVars.DI &= ~DI15FLAG;  // 判定DI15=0,并记录
                }
            }			
        }		 
		#endif

			// 再次读取DI16输入值    
		#ifdef DI16
        if ((DI&DI16FLAG) != (UserVars.DI&DI16FLAG)) // 判断DI16有变化
        {
            val = IO_Read(DI16);  // 再次读取DI16
            if (DI&DI16FLAG)      // DI16=1
            {
                if (val == 1)	   // 再次读DI16还是为1
                {
                    UserVars.DI |= DI16FLAG;  // 判定DI16=1,并记录
                }								
            }
            else								 // DI16=0
            {
                if (val == 0)    // 再次读DI16还是为0
                {
                    UserVars.DI &= ~DI16FLAG;  // 判定DI16=0,并记录
                }
            }			
        }		 
		#endif			
	}
	      
    
// 以下是SPI总线读取DI输入
    Num = 0;
#if (DI1_8SPI_EN > 0)       // SPI总线读取DI1-8使能
    Num++;
#endif
#if (DI9_16SPI_EN > 0)      // SPI总线读取DI9-16使能
    Num++;
#endif
#if (DI17_24SPI_EN > 0)     // SPI总线读取DI17-24使能
    Num++;
#endif
#if (DI25_32SPI_EN > 0)     // SPI总线读取DI25-32使能
    Num++;
#endif
    
#if ((DI1_8SPI_EN > 0)||(DI9_16SPI_EN > 0)||(DI17_24SPI_EN > 0)||(DI25_32SPI_EN > 0))   
    if (Num > 0)
    {
        DI_SPIRead(DIBuf, Num);  // SPI总线读取DI输入
        
        // EMB88616I 先读的DI17~DI24放到DIBuf[0];后读的DI9~DI16放到DIBuf[1];
        // 将这2个数据换个位置
        #if ((PRODUCT_TYPE == EMB8616I)||(PRODUCT_TYPE == EMB8626I)) // Modify 2019.5.22
        val = DIBuf[0];
        DIBuf[0] = DIBuf[1];
        DIBuf[1] = val;
        #endif
        
        Num = 0;
        #if (DI1_8SPI_EN > 0)       
        UserVars.DI &= ~0x000000FF;
        UserVars.DI |= (INT32U)DIBuf[Num]; 
        Num++;
        #endif

        #if (DI9_16SPI_EN > 0)       
        UserVars.DI &= ~(0x000000FF<<8);
        UserVars.DI |= (INT32U)DIBuf[Num]<<8; 
        Num++;
        #endif

        #if (DI17_24SPI_EN > 0)       
        UserVars.DI &= ~(0x000000FF<<16);
        UserVars.DI |= (INT32U)DIBuf[Num]<<16; 
        Num++;
        #endif

        #if (DI25_32SPI_EN > 0)       
        UserVars.DI &= ~(0x000000FF<<24);
        UserVars.DI |= (INT32U)DIBuf[Num]<<24; 
        #endif
    }
#endif 
    
    if (DIVal != UserVars.DI) // DI输入有变化
    {
        return ERR_TRUE;    // 返回正确, DI有变化值  
    }
    else                   
    {
        return ERR_FALSE;   // 返回错误, DI无变化值
    }
}

/***********************************************************************************
* Function: Key_Read;
*
* Description: 读取按键K1-K8键值;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: 返回键值：KNONE，K1VAL-K8VAL;
*
* Note:   已经加了20ms防抖处理; 本函数支持1-8个按键读取, , 用户可以参照这个增加更多按键读取;
************************************************************************************/
INT8U Key_Read(void)
{    
	INT8U val;

#ifdef K1    
	val = IO_Read(K1);
	if (val==0)
	{
		if ((UserVars.KeyVal&K1FLAG)==0)
		{
		    Delay_ms(20);
		    val = IO_Read(K1);
		    if (val==0)
		    { 
			    UserVars.KeyVal |= K1FLAG;
                return K1VAL;
		    }
		}
	}
	else
	{
		if (UserVars.KeyVal&K1FLAG)
		{
		    Delay_ms(20);
		    val = IO_Read(K1);
		    if (val)
		    { 
			    UserVars.KeyVal &= ~K1FLAG;
		    }
		}
	}
#endif
    
#ifdef K2 	
	val = IO_Read(K2);
	if (val==0)
	{
		if ((UserVars.KeyVal&K2FLAG)==0)
		{
		    Delay_ms(20);
		    val = IO_Read(K2);
		    if (val==0)
		    { 
			    UserVars.KeyVal |= K2FLAG;
                return K2VAL;
		    }
		}
	}
	else
	{
		if (UserVars.KeyVal&K2FLAG)
		{
		    Delay_ms(20);
		    val = IO_Read(K2);
		    if (val)
		    { 
			    UserVars.KeyVal &= ~K2FLAG;
		    }
		}
	}
#endif
#ifdef K3     
	val = IO_Read(K3);
	if (val==0)
	{
		if ((UserVars.KeyVal&K3FLAG)==0)
		{
		    Delay_ms(20);
		    val = IO_Read(K3);
		    if (val==0)
		    { 
			    UserVars.KeyVal |= K3FLAG;
			    return K3VAL;
		    }
		}
	}
	else
	{
		if (UserVars.KeyVal&K3FLAG)
		{
		    Delay_ms(20);
		    val = IO_Read(K3);
		    if (val)
		    { 
			    UserVars.KeyVal &= ~K3FLAG;
		    }
		}
	}
#endif
#ifdef K4     
	val = IO_Read(K4);
	if (val==0)
	{
		if ((UserVars.KeyVal&K4FLAG)==0)
		{
		    Delay_ms(20);
		    val = IO_Read(K4);
		    if (val==0)
		    { 
			    UserVars.KeyVal |= K4FLAG;
			    return K4VAL;
		    }
		}
	}
	else
	{
		if (UserVars.KeyVal&K4FLAG)
		{
		    Delay_ms(20);
		    val = IO_Read(K4);
		    if (val)
		    { 
			    UserVars.KeyVal &= ~K4FLAG;
		    }
		}
	}
#endif  
#ifdef K5     
	val = IO_Read(K5);
	if (val==0)
	{
		if ((UserVars.KeyVal&K5FLAG)==0)
		{
		    Delay_ms(20);
		    val = IO_Read(K5);
		    if (val==0)
		    { 
			    UserVars.KeyVal |= K5FLAG;
			    return K5VAL;
		    }
		}
	}
	else
	{
		if (UserVars.KeyVal&K5FLAG)
		{
		    Delay_ms(20);
		    val = IO_Read(K5);
		    if (val)
		    { 
			    UserVars.KeyVal &= ~K5FLAG;
		    }
		}
	}
#endif    
#ifdef K6     
	val = IO_Read(K6);
	if (val==0)
	{
		if ((UserVars.KeyVal&K6FLAG)==0)
		{
		    Delay_ms(20);
		    val = IO_Read(K6);
		    if (val==0)
		    { 
			    UserVars.KeyVal |= K6FLAG;
			    return K6VAL;
		    }
		}
	}
	else
	{
		if (UserVars.KeyVal&K6FLAG)
		{
		    Delay_ms(20);
		    val = IO_Read(K6);
		    if (val)
		    { 
			    UserVars.KeyVal &= ~K6FLAG;
		    }
		}
	}
#endif  
#ifdef K7    
	val = IO_Read(K7);
	if (val==0)
	{
		if ((UserVars.KeyVal&K7FLAG)==0)
		{
		    Delay_ms(20);
		    val = IO_Read(K7);
		    if (val==0)
		    { 
			    UserVars.KeyVal |= K7FLAG;
			    return K7VAL;
		    }
		}
	}
	else
	{
		if (UserVars.KeyVal&K7FLAG)
		{
		    Delay_ms(20);
		    val = IO_Read(K7);
		    if (val)
		    { 
			    UserVars.KeyVal &= ~K7FLAG;
		    }
		}
	}
#endif    
#ifdef K8    
	val = IO_Read(K8);
	if (val==0)
	{
		if ((UserVars.KeyVal&K8FLAG)==0)
		{
		    Delay_ms(20);
		    val = IO_Read(K8);
		    if (val==0)
		    { 
			    UserVars.KeyVal |= K8FLAG;
			    return K8VAL;
		    }
		}
	}
	else
	{
		if (UserVars.KeyVal&K8FLAG)
		{
		    Delay_ms(20);
		    val = IO_Read(K8);
		    if (val)
		    { 
			    UserVars.KeyVal &= ~K8FLAG;
		    }
		}
	}
#endif      
    
    return KNONE;
}


#if (RTC_EN > 0)
#define  ALARM_COUNT   5  // 5秒
void RTC_Test(void)
{
    INT32S flag;
    RTC_TIME rtc;

    
    // 初始化时间
    rtc.year = 17;
    rtc.month = 12;
    rtc.day  = 31;
    rtc.hour = 23;
    rtc.minute = 59;
    rtc.second = 30;
    rtc.ss = 0;
    
    flag = RTC_Read(&rtc); // 每隔3秒RTC读时间测试  
    #if (DEBUG_APP_EN == 1)
    if (flag == ERR_TRUE)
    {
        if (UserVars.Para.ATFlag&AT_RTC_FLAG)
        {    
            printf("AT+RTC=%d.%d.%d,%d:%d:%d,%d\r\n", rtc.year+2000,rtc.month,rtc.day,rtc.hour,rtc.minute,rtc.second, rtc.ss);	
        }
    }
    else
    {
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        { 
            printf("AT+ERROR=RTC Read, ERROR\r\n");
        }
    } 
    #endif    
    
    #if (RTC_ALRIT_EN > 0)                   // 闹钟中断使能   
    if (UserVars.Flag&RTC_ALRIT_FLAG)        // 已经产生闹钟中断
    {
        UserVars.Flag &= ~RTC_ALRIT_FLAG;    // 清除闹钟中断标志
        RTC_Ctrl(CMD_RTC_SET_ALMTIM_XS, ALARM_COUNT, 0);   // 设置闹钟时间, (ALARM_COUNT)秒后产生闹钟中断
        #if (DEBUG_APP_EN == 1)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        { 
            printf("AT+INFO=RTC设置%d秒后产生闹钟报警\r\n", ALARM_COUNT);
        }
        #endif
    }
    #endif
}
#endif


void DO_Printf(void)
{
    INT8U i;
    
    if (UserVars.Para.ATFlag&AT_DO_FLAG)
    { 
        printf("AT+DO=%d,", DO_NUM);   // 打印DO值
        for(i=0; i<DO_NUM; i++)
        {
            if (UserVars.DO&(0x00000001<<i))
            {    
                printf("1"); 
            }
            else
            {
                printf("0"); 
            }
        }
        printf("\r\n");
    }
}
    
void DI_Printf(void)
{
    INT8U i;
    
    if (UserVars.Para.ATFlag&AT_DI_FLAG)
    {
        printf("AT+DI=%d,", DI_NUM);   // 打印DI值
        for(i=0; i<DI_NUM; i++)
        {
            if (UserVars.DI_P&(0x00000001<<i))
            {    
                printf("1"); 
            }
            else
            {
                printf("0"); 
            }
        }
        printf("\r\n");
    }
}
void DOFunction_Test()
{
	static INT8U DOFunction=0;
	printf("IO_Ctrl %d\r\n",DOFunction);
	IOFunction_Ctrl(DOFunction,CMD_IO_ON_T,300);
	if(DOFunction<CookerDOMax)
	{
		DOFunction++;
	}
	else
	{
		DOFunction=0;
	}
}
void App_TaskIO(void *p_arg)
{	 
    INT16U sw, i; 
    INT8U Key;
    INT32U t;    
    INT32S flag;    
    
	(void)p_arg;
/****************************************************************/        
//   EEPROM读写测试 
/****************************************************************/ 
    flag = EEPROM_Test();  // EEPROM读写测试    
    if (flag == ERR_TRUE)
    {
        UserVars.OKFlag |= EEPROM_OK_FLAG;
        #if (DEBUG_APP_EN == 1)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        { 
            printf("AT+EEPROM=OK\r\n");
        }
        #endif
    }
    else
    {
        UserVars.OKFlag &= ~EEPROM_OK_FLAG;
        #if (DEBUG_APP_EN == 1)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        { 
            printf("AT+EEPROM=ERROR\r\n");
        }
        #endif
    }    
/****************************************************************/        
//   SPI FLASH读写测试 
/****************************************************************/     
    #if ((SPIFLASH_EN > 0)&&(SPIFLASH_MODE == 0)) // SPI FLASH使能并且读写方式为函数读写
        #if (SPIFLASH_TYPE  == W25QXX)
        flag = W25QXX_Test();    // W25QXX FLASH读写测试
        #endif
        #if (SPIFLASH_TYPE  == AT45DBXX)
        flag = AT45DBXX_Test();  // AT45DBXX FLASH读写测试
        #endif
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
    #endif    

	UserVars.DO = 0x55555555;  // 初始化DO值
    t = 0;	         
    while(1)
    {		
		UserVars.TaskRunStatus |= TASK_IO_FLAG; // 设置本任务运行状态标志
		Delay_ms(20);	                        // 延时20ms
        t +=20 ;                                // 更新时间计数器

/*************************************************************************************************************/        
//      读取拨码开关测试
/*************************************************************************************************************/        
        // 读取拨码开关
        #ifdef SW_NUM                                    
        sw = SW_Read();
        if (sw != UserVars.SW) // 拨码开关有变化
        {
            UserVars.SW = sw;
            #if (DEBUG_APP_EN == 1)
            if (UserVars.Para.ATFlag&AT_INFO_FLAG)
            {    
                printf("AT+SW=");
                for(i=0; i<SW_NUM; i++)
                {
                    if (UserVars.SW&(0x0001<<i))
                    {    
                        printf("1"); 
                    }
                    else
                    {
                        printf("0"); 
                    }
                }
                printf("\r\n");   
            }        
            #endif
        }
        #endif
/*************************************************************************************************************/        
//      读取按键测试, 有按下则响一声蜂鸣器并打印输出按键按下信息
/*************************************************************************************************************/ 
//        #if (PRODUCT_TYPE == EMB8628I)&&(CH455_EN)
//        Key = CH455_Read();                    // 读取键值
//        #else 
//        Key = Key_Read();			           // 读取按键键值
//		#endif
//        if (Key != KNONE)                      // 判断按键是否有效
//        {
//            UserVars.Key = Key;                // 赋值按键值
//            #if (DEBUG_APP_EN == 1)
//            if (UserVars.Para.ATFlag&AT_INFO_FLAG)
//            { 
//                printf("AT+KEY=%d\r\n", Key);   
//            }
//            #endif            
//            IO_Ctrl(ALARM, CMD_IO_ON_T, 50);   // 控制蜂鸣器响50ms
//        }
/*************************************************************************************************************/        
//      DI输入测试
/*************************************************************************************************************/ 
        //if (((t%UserVars.Para.DI.t1)==0)||(UserVars.Para.DI.Mode == AT_MODE_START)) // 间隔UserVars.Para.DI.t1时间读取DI值 或立即启动读取模式
        flag = DI_Read();           // 读取DI值
        if (flag == ERR_TRUE)       // DI有变化
        {
            UserVars.DI_P = ~UserVars.DI;  // 如果DI输入信号被三极管反向或者光耦隔离, 要在这里做取反处理
            
            #if (MODBUS_SLAVE_EN > 0)  // Modbus设备模式使能
            ModbusDisInput[0] = UserVars.DI_P&0xff;       // 将DI1-DI8输入值赋给离散输入寄存器
            ModbusDisInput[1] = (UserVars.DI_P>>8)&0xff;  // 将DI9-DI16输入值赋给离散输入寄存器
            ModbusDisInput[2] = (UserVars.DI_P>>16)&0xff; // 将DI17-D24输入值赋给离散输入寄存器
            ModbusDisInput[3] = (UserVars.DI_P>>24)&0xff; // 将DI25-DI32输入值赋给离散输入寄存器
            #endif
            
            #if (DEBUG_APP_EN == 1)
            DI_Printf();
            #endif
        } 
        else
        {                
            
            #if (DEBUG_APP_EN == 1)
            if ((t%3000)==0)    // 每隔3秒显示一次
            {
                DI_Printf();
            } 
            
            #endif
        }
      
/**************************************************************************************************/        
//      DO输出(包括继电器)测试程序
/**************************************************************************************************/  
        if ((t%1000)==0)    // 间隔3秒更新输出DO
        { 
			//DOFunction_Test();
            #if (MODBUS_SLAVE_EN > 0)        // Modbus设备模式使能
            UserVars.DO = ModbusCoils[0] + ((INT32U)ModbusCoils[1]<<8)+((INT32U)ModbusCoils[2]<<16)+((INT32U)ModbusCoils[3]<<24);
            #else
            // DO间隔输出0或1
//            if (UserVars.DO == 0x55555555)
//            {
//                UserVars.DO = 0xAAAAAAAA;     // 设置新的DO输出值
//            }
//            else
//            {
//                UserVars.DO = 0x55555555;     // 设置新的DO输出值
//            }
            #endif            
//            DO_Write(UserVars.DO);            // 输出DO
//            
//            #if (DEBUG_APP_EN == 1)
//            DO_Printf();
//            #endif
        }
/**************************************************************************************************/        
// ALARM和LED测试, RTC实时时钟测试
/**************************************************************************************************/         
		if ((t%1000)==0)	  // 1秒执行1次
		{

            IO_Ctrl(RUN_LED, CMD_IO_NEG, 0); //RUN LED间隔1秒闪烁  
            #ifdef  JP9_P1
            IO_Ctrl(JP9_P1, CMD_IO_NEG, 0);  // 间隔1秒输出1或0
            // 或者用IO_Write(JP9_P1,1)输出1, IO_Write(JP9_P1,0)输出0 
            #endif
        }        
//        if ((t%3000)==0)      // 3秒执行1次 
//        {
//            #if (RTC_EN > 0)
//            RTC_Test();       //  RTC读写测试
//            #endif

//            // 蜂鸣器测试
//			IO_Ctrl(ALARM, CMD_IO_ON_T, 50);  // 蜂鸣器间隔5秒响50ms;
//		}
	} // while(1)结束
}
#endif
/***********************************************************************************/
// 文件结束
/***********************************************************************************/