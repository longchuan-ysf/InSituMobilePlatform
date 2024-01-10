/************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: TastIO.c
* Project  : STM32F1XX/4XXϵ��ģ�����
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.00
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: ���ļ�����IO�������������;
*              1. DI������Գ���
*              2. DO���(�����̵���)���Գ���
*              3. ��ȡ�������Գ���
*              4. ��ȡ���뿪�ز��Գ���
*              5. RTCʵʱʱ�Ӳ��Գ���
*              6. EEPROM��д���Գ���
*              7. SPI�ӿ�FLASH��д���Գ���
*              8. ALARM��LED���Գ�
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
1. IO��˿ڲ��� 
   (1). ��IO�����ļ��ж���RUN_LED, ������, DI�˿�, DO�˿ں�K1-K8��IO����; 
   (2). ��������(1)����, ��APP_Init.c�е���IO_APPInit()������ʼ������IO; 
   �����̾���ʵ�ֹ�������:
   (3). RUN LED���1����˸;
   (4). ���������3����50ms;
   (5). DO���1�����1��0; ����DO_Write()����ʵ��;
   (6). ���DI�����Ƿ��б仯���б仯���ӡ���DI�����ֵ; ����DI_Read()����ʵ��;
   (7). ���K1-K8�����Ƿ��а���, �а�������һ������������ӡ�������������Ϣ; ����Key_Read()����ʵ��;

2. RTC��д����:
   (1). ���ܲ�������˵��: �������ļ�������������: 
        // STM32F107VC/103VE/103ZE ģ����������
        #define RTC_EN          1          // RTCʹ��, 1����ʹ�ܣ� 0���ر�
        #define RTC_SECIT_EN    0          // RTC���ж�ʹ��, 1����ʹ�ܣ� 0���ر�	
        #define RTC_ALRIT_EN    0          // RTC�����ж�ʹ��, 1����ʹ�ܣ� 0���ر�	
        
        // STM32F407VE ģ����������
        #define RTC_EN           1          // RTCʹ��, 1����ʹ�ܣ� 0���ر�

        #define RTC_WKUPIT_EN    0         // RTC�����ж�ʹ��, 1����ʹ�ܣ� 0���ر�	
        #define RTC_ALRAIT_EN    0         // RTC����A�ж�ʹ��, 1����ʹ�ܣ� 0���ر�	
        #define RTC_ALRBIT_EN    0         // RTC����B�ж�ʹ��, 1����ʹ�ܣ� 0���ر�	
        #define RTC_TSFIT_EN     0         // RTCʱ����ж�ʹ��, 1����ʹ�ܣ� 0���ر�
        #define RTC_TAMP1IT_EN   0         // RTC���ּ��1�ж�ʹ��, 1����ʹ�ܣ� 0���ر�
        #define RTC_TAMP2IT_EN   0         // RTC���ּ��1�ж�ʹ��, 1����ʹ�ܣ� 0���ر�
        
   (2). ��APP_Init.c�е���RTC_APPInit()������ʼ��; 
  
   (3). ������ʵ��: ����RTC�ϵ��־, �����³�ʼ��RTCʱ��; ÿ��3���ȡ1��RTCʱ�䣬��ӡ���;
   
   (4). �����������жϺ������жϽ�RTC_SECIT_EN��RTC_ALRIT_ENҲ����Ϊ1, ���Ӷ�ʱ5�������ж�

3. EEPROM��д���ԣ�
   (1). ��IO�����ļ��ж���I2C1_SDA,I2C1_SCL����
   (2). ���ܲ�������˵��: �������ļ�������������: 
        #define EEPROM_EN          1          // EEPROMʹ��, 1����ʹ�ܣ� 0���ر�
        #define EEPROM_DEVICE      AT24C64    // ���������ͺ�	
        #define EEPROM_FREQ        100000     // ��дʱ��Ƶ��
        ע��: ��������Ĭ�ϲ�Ҫ�޸�
   (3). ��������(1)(2)����, ��APP_Init.c�е���EEPROM_APPInit()������ʼ��; 
   (4). �����̵���EEPROM_Test()��0-255��ַ���ж�д����, ͨ�����Դ��ڴ�ӡ�����д���Խ��;
   ע��: EEPROM���512�ֽ�(��ַ��Χ:0x1E00~0x1FFF)����ϵͳIAP���¹̼�����, �벻Ҫ����������
   
   
4. SPI FLASH(W25QXX/AT45DB161)��д����: 
   (1). ��IO�����ļ��ж���SPI1_SCK/MISO/MOSI/NSS(W25QXX_CS)����
   (2). ���ܲ�������˵��: �������ļ�������������: 
        #define SPIFLASH_EN            1        // SPI FLASHʹ�ܣ�1, ʹ��;  0, �ر�;
        #define SPIFLASH_MODE          0        // SPI FLASH������ʽ��1, ����FATFS�ļ�ϵͳ���ж�д;  0, ��SPI FLASH��д�������в���;
                                                // ע��:2�ֲ�����ʽֻ��ѡ��һ��    
        #define SPIFLASH_TYPE          W25QXX   // SPI FLASH���Ͷ���: W25QXX��AT45DBXX
   (3). ��������(1)(2)����, ��APP_Init.c�е���SPIFlash_APPInit()������ʼ��; 
   (4). �����̵���W25QXX_Test()��AT45DBXX_Test()���ж�д����, ͨ�����Դ��ڴ�ӡ�����д���Խ��;

5. IO�жϲ���: 
   (1). ���ܲ�������˵��: �������ļ�������������, ��EXTI5�ο�: 
        // EXTI5�ж�����
        #define EXTI5_EN        1		 // �жϻ��¼�ʹ��: 0,�ر��жϺ��¼�; 1, ���ж�; 2, ���¼�����
        #define EXTI5_IO        PE5      // ��PA5, PB5, PC5, PD5, PE5, PF5, PG5, PH5, PI5 ��ѡ��һ��IO��Ϊ�ж������; 
        #define EXTI5_MODE      1		 // �����жϺ��¼�ģʽ: 0,�����ش����жϺ��¼�; 1,�½��ش����жϺ��¼�; 2,�������½��ض������жϺ��¼�;
   (2). ��������(1)����, ��APP_Init.c�е���EXTI_APPInit()������ʼ��;
   (3). PE5(���ԽӰ���)����ܽ�������źű仯, ������ж�, ͨ�����Դ��ڴ�ӡ����жϽ��;
   (4). �жϺ�����ISRHook.c�е�EXTI0_ISRHook()~EXTI15_ISRHook()
*/
/************************************************************************************/
// �����ⲿͷ�ļ�  
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
// ������ȫ�ֱ�������
/************************************************************************************/
// ���尴����ֵ
#define KNONE    0  // û�а�������
#define K1VAL    1  // K1����
#define K2VAL    2  // K2����
#define K3VAL    3  // K3����
#define K4VAL    4  // K4����
#define K5VAL    5  // K5����
#define K6VAL    6  // K6����
#define K7VAL    7  // K7����
#define K8VAL    8  // K8����

#define K9VAL    9   // K9����
#define K10VAL   10  // K10����
#define K11VAL   11  // K11����
#define K12VAL   12  // K12����
#define K13VAL   13  // K13����
#define K14VAL   14  // K14����
#define K15VAL   15  // K15����
#define K16VAL   16  // K16����

//�����־λ
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


// DI����ֵ��־λ
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

#define DI_NONE   0xFFFFFFFF // DI�����ޱ仯


// DO�����־λ
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

// EMB8616I��6���̵�������DO��־λ����
#define JDQ1FLAG    0x00000001 // ��DO1����
#define JDQ2FLAG    0x00000002 // ��DO2����
#define JDQ3FLAG    0x00000004 // ��DO3����
#define JDQ4FLAG    0x00000008 // ��DO4����
#define JDQ5FLAG    0x00000010 // ��DO5����
#define JDQ6FLAG    0x00000020 // ��DO6����

/***********************************************************************************
* EEPROM��д��������
************************************************************************************/
#define EEPROM_START_ADDR   1000           // EEPROM��д��ʼ��ַ
#define EEPROM_LEN          256            // EEPROM��д���ݳ���, �����û��泤��һ��

/***********************************************************************************
* AT45DBXX(SPI FLASH)��д��������
************************************************************************************/
#if (SPIFLASH_TYPE  == AT45DBXX)
// ��ҳ��д����
#define AT45DBXX_START_PAGE   2000          // SPI FLASH��д��ʼҳ
#define AT45DBXX_PAGE_NUM     2             // SPI FLASH��д����ҳ��

// ���ֽ������ַ��д����
#define AT45DBXX_START_ADDR   (AT45DBXX_START_PAGE*AT45DBXX_PAGE_SIZE+100)  // SPI FLASH��д��ʼ��ַ
#define AT45DBXX_LEN          AT45DBXX_PAGE_SIZE                            // SPI FLASH��д���ݳ���(512�ֽ�), �����û��泤��һ��

#endif
/***********************************************************************************
* W25QXX(SPI FLASH)��д��������
* ע��: ��д��ҳ(256�ֽ�), ������������(4096�ֽ�)����, ÿ����������16��ҳ
* ��д����ȫ��������W25QXX_ZDY_STARTSECTOR�����
************************************************************************************/
#if (SPIFLASH_TYPE  == W25QXX)
// ��ҳ��д����
#define W25QXX_START_PAGE   W25QXX_ZDY_STARTSECTOR*W25QXX_PAGE_PER_SECTOR   // W25QXX FLASH��д��ʼҳ
#define W25QXX_PAGE_NUM     16                        // W25QXX FLASH��д����ҳ��

// ���ֽ������ַ��д����
#define W25QXX_START_ADDR   (W25QXX_START_PAGE*W25QXX_PAGE_SIZE+100)  // W25QXX FLASH��д��ʼ��ַ
#define W25QXX_LEN          W25QXX_PAGE_SIZE                          // W25QXX FLASH��д���ݳ���(256�ֽ�), �����û��泤��һ��

#endif
/***********************************************************************************
* Function: EEPROM_Test;
*
* Description: EEPROM��д����  
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

    p = (INT8U *)OSMalloc(EEPROM_LEN); // �����ڴ�
    if (p == 0)
    {
        return ERR_FALSE;
    } 
    
    // ��ʼ����������: 0-255
    for(i=0;i<EEPROM_LEN;i++)		    
	{
        p[i] = i;			 	  
	}
	flag = EEPROM_Write(EEPROM_START_ADDR, p, EEPROM_LEN); // �ӵ�ַEEPROM_START_ADDRд��EEPROM_LEN�ֽ�����
	if (flag == ERR_TRUE) // �ж�д����ȷ
    {
        #if (DEBUG_APP_EN > 0)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            printf("AT+INFO=EEPROM�ӵ�ַ%dд��%d�ֽ�����\r\n", EEPROM_START_ADDR, EEPROM_LEN); 
        }
        #endif        
        flag = EEPROM_Read(EEPROM_START_ADDR, p, EEPROM_LEN); // �ӵ�ַEEPROM_START_ADDR��ȡEEPROM_LEN�ֽ�����
        if (flag == ERR_TRUE) // �ж���ȡ��ȷ
        {
            for(i=0;i<EEPROM_LEN;i++) // �Ա�����
            {
                 if (p[i]!=(i&0xff))	
                 {
                     #if (DEBUG_APP_EN == 1)
                     if (UserVars.Para.ATFlag&AT_INFO_FLAG)
                     {
                         printf("AT+ERROR=EEPROM��д���� ERROR, %d\r\n", i); 
                     }
                     #endif
                     OSFree(p);         // �ͷ��ڴ�
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
            printf("AT+INFO=EEPROM��д���� OK!\r\n\r\n");
        }
        else
        {
            printf("AT+ERROR=EEPROM��д���� ERROR!\r\n\r\n");
        }
    }
    #endif
    
    OSFree(p);         // �ͷ��ڴ�
    return flag;
}

/***********************************************************************************
* Function: AT45DBXX_Test;
*
* Description: AT45DBXX(SPI FLASH)��д����  
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
    
    if (SPI_RequestOSSem(2000) == ERR_TRUE)  // ��ȡSPI1��ʹ��Ȩ
    {
        p = (INT8U *)OSMalloc(AT45DBXX_PAGE_SIZE);   // �����ڴ�
        if (p == 0)
        {
            return ERR_FALSE;
        } 
                
        v.d = AT45DBXX_Ctrl(CMD_AT45DBXX_RDID, 0);
        #if (DEBUG_APP_EN == 1)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {    
            printf("AT+INFO=SPIFLASH��д����: ����,%02X; ����ID,%02X %02X %02X\r\n", v.chars.c3, v.chars.c2, v.chars.c1, v.chars.c0); 
        }
        #endif
        // printf("���ڲ���SPI Flash, ��ȴ�...%02X\r\n", SPIFlash.Status); 
    /***************************************************************************************************
    // ��һ��ҳ��дFlash����    
    ***************************************************************************************************/   
        for(i=0;i<AT45DBXX_PAGE_SIZE;i++)	// ��ʼ����������: 0-255
        {
            p[i] = i&0xff;			 	  
        }
        
        for (i=0; i<AT45DBXX_PAGE_NUM; i++)
        {
            flag = AT45DBXX_WritePage(p, i+AT45DBXX_START_PAGE, 1);  // ��SysPara.Databuf������д��SPI FLASHҳ��
            if (flag != ERR_TRUE)
            {
                #if (DEBUG_APP_EN == 1)
                if (UserVars.Para.ATFlag&AT_INFO_FLAG)
                {
                    printf("AT+ERROR=SPIFLASHд512�ֽڵ�%dҳ, ERROR!\r\n", i+AT45DBXX_START_PAGE); 
                }
                #endif
            }
        }
        
        for (i=0; i<AT45DBXX_PAGE_NUM; i++)
        {
            flag = AT45DBXX_ReadPage(p, i+AT45DBXX_START_PAGE, 1);  //��ȡ SPI FLASHҳ�����ݶ��뵽Databuf��
            if (flag != ERR_TRUE)
            {
                 #if (DEBUG_APP_EN == 1)
                 if (UserVars.Para.ATFlag&AT_INFO_FLAG)
                 {
                     printf("AT+ERROR=SPIFLASH��ȡ%dҳ, ERROR!\r\n", i+AT45DBXX_START_PAGE); 
                 }
                 #endif
                 SPI_ReleaseOSSem();       // �ͷ�SPI1ʹ��Ȩ
                 OSFree(p);         // �ͷ��ڴ�
                 return ERR_FALSE;
            }        
            for(j=0; j<AT45DBXX_PAGE_SIZE; j++)
            {
                if (p[j] != (j&0xff))	
                {
                    #if (DEBUG_APP_EN == 1)
                    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
                    {
                        printf("AT+ERROR=SPIFLASH���ݶԱ�, ERROR!, %d\r\n", j); 
                    }
                    #endif
                    SPI_ReleaseOSSem();       // �ͷ�SPI1ʹ��Ȩ
                    OSFree(p);         // �ͷ��ڴ�
                    return ERR_FALSE;
                }
            }
        }    
        #if (DEBUG_APP_EN == 1)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            printf("AT+INFO=SPIFLASH��ҳ��д���� OK!\r\n");
        }
        #endif
    /***************************************************************************************************
    // �����ַ��дFlash����    
    ***************************************************************************************************/   
        for(i=0;i<AT45DBXX_LEN;i++)	// ��ʼ����������: 0-255
        {
            p[i] = i&0xff;			 	  
        }
        
        flag = AT45DBXX_Write(p, AT45DBXX_START_ADDR, AT45DBXX_LEN);  // ��Databuf������д���ַSPIFLASH_START_ADDR��ʼ��FLASH��
        if (flag != ERR_TRUE)
        {
             #if (DEBUG_APP_EN == 1)
             if (UserVars.Para.ATFlag&AT_INFO_FLAG)
             {
                 printf("AT+ERROR=SPIFLASH�����ַд������, ERROR!\r\n");
             }
             #endif
             SPI_ReleaseOSSem();       // �ͷ�SPI1ʹ��Ȩ
             OSFree(p);         // �ͷ��ڴ�
             return ERR_FALSE;
        }
        Delay_ms(20);
        
        flag = AT45DBXX_Read(p, AT45DBXX_START_ADDR, AT45DBXX_LEN);  // ��ȡ���ݵ�Databuf��
        if (flag != ERR_TRUE)
        {         
             #if (DEBUG_APP_EN == 1)
             if (UserVars.Para.ATFlag&AT_INFO_FLAG)
             {
                 printf("AT+ERROR=SPIFLASH�����ַ��ȡ����, ERROR!\r\n");
             }
             #endif
             SPI_ReleaseOSSem();       // �ͷ�SPI1ʹ��Ȩ
             OSFree(p);         // �ͷ��ڴ�
             return ERR_FALSE;
        }
        
        for(i=0;i<AT45DBXX_LEN;i++)
        {
            if (p[i]!=(i&0xff))	
            {
                #if (DEBUG_APP_EN == 1)
                if (UserVars.Para.ATFlag&AT_INFO_FLAG)
                {
                    printf("AT+ERROR=SPIFLASH�Ա�����, ERROR, %d\r\n", i); 
                }
                #endif
                SPI_ReleaseOSSem();       // �ͷ�SPI1ʹ��Ȩ
                OSFree(p);         // �ͷ��ڴ�
                return ERR_FALSE;
            }
        }
        #if (DEBUG_APP_EN == 1)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            printf("AT+INFO=SPIFLASH�����ַ��д���� OK!\r\n");  
        }
        #endif
        SPI_ReleaseOSSem();       // �ͷ�SPI1ʹ��Ȩ
        OSFree(p);         // �ͷ��ڴ�
        return ERR_TRUE;
    }
    return ERR_FALSE;        
}
#endif

/***********************************************************************************
* Function: W25QXX_Test;
*
* Description: W25QXX(SPI FLASH)��д����  
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
    
    if (SPI_RequestOSSem(2000) == ERR_TRUE)  // ��ȡSPI1��ʹ��Ȩ
    {     
        p = (INT8U *)OSMalloc(W25QXX_PAGE_SIZE);   // �����ڴ�
        if (p == 0)
        {
            return ERR_FALSE;
        } 
        
        v.d = W25QXX_Ctrl(CMD_AT45DBXX_RDID, 0);
        #if (DEBUG_APP_EN == 1)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            printf("AT+INFO=SPIFLASH���Ҵ���:%02X; ����ID:%02X %02X\r\n", v.chars.c2, v.chars.c1, v.chars.c0); 
        }
        #endif
    /***************************************************************************************************
    // ��һ��ҳ��дFlash����    
    ***************************************************************************************************/   
        for(i=0;i<W25QXX_PAGE_SIZE;i++)	// ��ʼ����������: 0-255
        {
            p[i] = i&0xff;			 	  
        }
        W25QXX_Ctrl(CMD_W25QXX_SECTOR_ERASE, W25QXX_ZDY_STARTSECTOR);               // ����W25QXX_ZDY_STARTSECTOR����
        for (i=0; i<W25QXX_PAGE_NUM; i++)
        {
            flag = W25QXX_WritePage(p, (i+W25QXX_START_PAGE)*256, W25QXX_PAGE_SIZE);  // ��SysPara.Databuf������д��SPI FLASHҳ��
            if (flag != ERR_TRUE)
            {
                #if (DEBUG_APP_EN == 1)
                if (UserVars.Para.ATFlag&AT_INFO_FLAG)
                {
                    printf("AT+ERROR=SPIFLASHд%d�ֽڵ�%dҳ ERROR!\r\n", W25QXX_PAGE_SIZE, i+W25QXX_START_PAGE); 
                }
                #endif
            }
        }
        for (i=0; i<W25QXX_PAGE_NUM; i++)
        {
            flag = W25QXX_Read(p, (i+W25QXX_START_PAGE)*256, W25QXX_PAGE_SIZE);  //��ȡ SPI FLASHҳ�����ݶ��뵽Databuf��
            if (flag != ERR_TRUE)
            {
                 #if (DEBUG_APP_EN == 1)
                 if (UserVars.Para.ATFlag&AT_INFO_FLAG)
                 {
                     printf("AT+ERROR=SPIFLASH��ȡ%dҳ ERROR!\r\n", i+W25QXX_START_PAGE); 
                 }
                 #endif
                 SPI_ReleaseOSSem();       // �ͷ�SPI1ʹ��Ȩ
                 OSFree(p);         // �ͷ��ڴ�
                 return ERR_FALSE;
            }        
            for(j=0; j<W25QXX_PAGE_SIZE; j++)
            {
                if (p[j] != (j&0xff))	
                {
                    #if (DEBUG_APP_EN == 1)
                    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
                    {
                        printf("AT+ERROR=SPIFLASH���ݶԱ� ERROR!, %d\r\n", j); 
                    }
                    #endif
                    SPI_ReleaseOSSem();       // �ͷ�SPI1ʹ��Ȩ
                    OSFree(p);         // �ͷ��ڴ�
                    return ERR_FALSE;
                }
            }
        }    
        #if (DEBUG_APP_EN == 1)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            printf("AT+INFO=SPIFLASH��ҳ��д���� OK!\r\n");
        }
        #endif
    /***************************************************************************************************
    // �����ַ��дFlash����    
    ***************************************************************************************************/   
        for(i=0;i<W25QXX_LEN;i++)	// ��ʼ����������: 0-255
        {
            p[i] = i&0xff;			 	  
        }        
        W25QXX_Ctrl(CMD_W25QXX_SECTOR_ERASE, W25QXX_ZDY_STARTSECTOR);               // ����W25QXX_ZDY_STARTSECTOR����
        flag = W25QXX_Write(p, W25QXX_START_ADDR, W25QXX_LEN);  // ��Databuf������д���ַSPIFLASH_START_ADDR��ʼ��FLASH��
        if (flag != ERR_TRUE)
        {
             #if (DEBUG_APP_EN == 1)
             if (UserVars.Para.ATFlag&AT_INFO_FLAG)
             {
                 printf("AT+ERROR=SPIFLASH�����ַд������, ERROR!\r\n");
             }
             #endif
             SPI_ReleaseOSSem();       // �ͷ�SPI1ʹ��Ȩ
             OSFree(p);         // �ͷ��ڴ�
             return ERR_FALSE;
        }    
        flag = W25QXX_Read(p, W25QXX_START_ADDR, W25QXX_LEN);  // ��ȡ���ݵ�Databuf��
        if (flag != ERR_TRUE)
        {         
             #if (DEBUG_APP_EN == 1)
             if (UserVars.Para.ATFlag&AT_INFO_FLAG)
             {
                 printf("AT+ERROR=SPIFLASH�����ַ��ȡ���� ERROR!\r\n");
             }
             #endif
             SPI_ReleaseOSSem();       // �ͷ�SPI1ʹ��Ȩ
             OSFree(p);         // �ͷ��ڴ�
             return ERR_FALSE;
        }
        
        for(i=0;i<W25QXX_LEN;i++)
        {
            if (p[i]!=(i&0xff))	
            {
                #if (DEBUG_APP_EN == 1)
                if (UserVars.Para.ATFlag&AT_INFO_FLAG)
                {
                    printf("AT+ERROR=SPIFLASH�����д�Ա����� ERROR, %d\r\n", i); 
                }        
                #endif    
                SPI_ReleaseOSSem();       // �ͷ�SPI1ʹ��Ȩ
                OSFree(p);         // �ͷ��ڴ�
                return ERR_FALSE;
            }
        }    
        #if (DEBUG_APP_EN == 1)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            printf("AT+INFO=SPIFLASH�����ַ��д���� OK!\r\n\r\n");  
        }
        #endif
        SPI_ReleaseOSSem();       // �ͷ�SPI1ʹ��Ȩ
        OSFree(p);         // �ͷ��ڴ�
        return ERR_TRUE;
    }
    return ERR_FALSE;
}
#endif

/***********************************************************************************
* Function: SW_Read;
*
* Description: ���뿪�ض�ȡ����;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   ���ڲ��뿪�ض���0,��ʾON; ����1����OFF;
************************************************************************************/
INT16U SW_Read(void)
{
    INT8U val;
    INT16U sw;

    sw = 0;
// ��ȡ���뿪��S1
#ifdef SW1 
	val = IO_Read(SW1);
	if (val)
	{
	    sw |= 0x01;
    }
#endif	

// ��ȡ���뿪��S2
#ifdef SW2 
	val = IO_Read(SW2);
	if (val)
	{
	    sw |= 0x02;
    }
#endif	

    // ��ȡ���뿪��S3
#ifdef SW3 
	val = IO_Read(SW3);
	if (val)
	{
	    sw |= 0x04;
    }
#endif	

    // ��ȡ���뿪��S4
#ifdef SW4 
	val = IO_Read(SW4);
	if (val)
	{
	    sw |= 0x08;
    }
#endif	

    // ��ȡ���뿪��S5
#ifdef SW5 
	val = IO_Read(SW5);
	if (val)
	{
	    sw |= 0x10;
    }
#endif	

    // ��ȡ���뿪��S6
#ifdef SW6 
	val = IO_Read(SW6);
	if (val)
	{
	    sw |= 0x20;
    }
#endif	

    // ��ȡ���뿪��S7
#ifdef SW7 
	val = IO_Read(SW7);
	if (val)
	{
	    sw |= 0x40;
    }
#endif	

    // ��ȡ���뿪��S8
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
* Description: SPI���߶�ȡDI���뺯��;
* 
* Input:  p, ��������ָ��; len, ���ݳ���
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
    
    // ��λ��������IO
    IO_Write(HC597_STB, 0);
    Delay_us(1);
    IO_Write(HC597_STB, 1);  	
    Delay_us(1);
    IO_Write(HC597_LOAD, 0);
    Delay_us(1);
    IO_Write(HC597_LOAD, 1);
    
    if (SPI_RequestOSSem(1000) == ERR_TRUE)  // ��ȡSPI1��ʹ��Ȩ
    {         
        // SPI��ȡ��ֵ
        #ifdef HC597_CS
        IO_Write(HC597_CS, 1);
        #endif
        for(i=0; i<len; i++)
        {
            *p++ = SPI_ReadWriteByte(SPI1_ID, 0);		//��ȡ����
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
* Description: ����SPI����ת����DO�������;
* 
* Input:  p, �������ָ��; len, ���ݳ���
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
        IO_Write(HC595_ENA, 0);                          // ���ʹ��
        #endif
        
        // SPIд����ֵ
        for (i=0; i<len; i++)
        {
            #if ((PRODUCT_TYPE == EMB8616I)||(PRODUCT_TYPE == EMB8626I))  // Modify 2019.5.22
            SPI_ReadWriteByte(SPI1_ID, p[len-i-1]);
            #else
            SPI_ReadWriteByte(SPI1_ID, *p++);
            #endif        
        }
        
        // ��λ�������IO
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
* Description: ����DO���;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   ������֧��16��DO1-DO16���, �û����Բ���������Ӹ���DO���;
*         ������ͬʱ֧��32��SPI����ת����DO1-DO32���
************************************************************************************/
void DO_Write(INT32U DOVal)
{
    INT8U DOBuf[4];
    INT8U Num;
    
// DO1���
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
    
// DO2���
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
    
// DO3���
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
    
// DO4���
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

// DO5���
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

// DO6���
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

// DO7���
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

// DO8���
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
	
// DO9���
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
	
// DO10���
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
	
// DO11���
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

// DO12���
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

// DO13���
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

// DO14���
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
// DO15���
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

// DO16���
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
    
// DO17���
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
    
// DO18���
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

// DO19���
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

// DO20���
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
    
 // DO21���
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
    
// ������SPI����ת����DO���
    Num = 0;
#if (DO1_8SPI_EN > 0)       // SPI����ת����DO1-8ʹ��
    DOBuf[Num++] = DOVal&0xff;
#endif
    
#if (DO9_16SPI_EN > 0)      // SPI����ת����DO9-16ʹ��
    DOBuf[Num++] = (DOVal>>8)&0xff;
#endif
    
#if (DO17_24SPI_EN > 0)     // SPI����ת����DO17-24ʹ��
    DOBuf[Num++] = (DOVal>>16)&0xff;
#endif

#if (DO25_32SPI_EN > 0)     // SPI����ת����DO25-32ʹ��  
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
* Description: ��ȡDI����ֵ;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: ����ERR_TRUE, DI�б仯; ����ERR_FALSE, DI���б仯; UserVars.DI��ʵ��DIֵ;
*
* Note:   �Ѿ�����20ms��������; ������֧��16��DI1-DI16��ȡ, �û����Բ���������Ӹ���DI��ȡ;
*         ������ͬʱ֧��32��SPI���߶�ȡDI1-DI32����(�޷�������)
************************************************************************************/
INT32S DI_Read(void)
{
	INT32U val, DIVal, DI;
  INT8U Num, DIBuf[4], i;
    
    
	DI = 0;
// ��ȡDI1����ֵ    
#ifdef DI1
    if (IO_Read(DI1)>0)
    {
        DI |= DI1FLAG;
	}		 
#endif
// ��ȡDI2����ֵ    
#ifdef DI2
    if (IO_Read(DI2)>0)
	{
		DI |= DI2FLAG;
	}		 
#endif
// ��ȡDI3����ֵ    
#ifdef DI3
    if (IO_Read(DI3)>0)
	{
		DI |= DI3FLAG;
	}		 
#endif
// ��ȡDI4����ֵ    
#ifdef DI4
    if (IO_Read(DI4)>0)
    {
		DI |= DI4FLAG;
    }		 
#endif 
// ��ȡDI5����ֵ    
#ifdef DI5
    if (IO_Read(DI5)>0)
	{
		DI |= DI5FLAG;
	}		 
#endif
// ��ȡDI6����ֵ    
#ifdef DI6
    if (IO_Read(DI6)>0)
	{
		DI |= DI6FLAG;
	}		 
#endif
// ��ȡDI7����ֵ    
#ifdef DI7
    if (IO_Read(DI7)>0)
	{
		DI |= DI7FLAG;
	}		 
#endif
// ��ȡDI8����ֵ    
#ifdef DI8
    if (IO_Read(DI8)>0)
	{
		DI |= DI8FLAG;
	}		 
#endif
// ��ȡDI9����ֵ    
#ifdef DI9
    if (IO_Read(DI9)>0)
	{
		DI |= DI9FLAG;
	}		 
#endif
// ��ȡDI10����ֵ    
#ifdef DI10
    if (IO_Read(DI10)>0)
	{
		DI |= DI10FLAG;
	}		 
#endif
// ��ȡDI11����ֵ    
#ifdef DI11
    if (IO_Read(DI11)>0)
	{
		DI |= DI11FLAG;
	}		 
#endif
// ��ȡDI12����ֵ    
#ifdef DI12
    if (IO_Read(DI12)>0)
	{
		DI |= DI12FLAG;
	}		 
#endif
// ��ȡDI13����ֵ    
#ifdef DI13
    if (IO_Read(DI13)>0)
	{
		DI |= DI13FLAG;
	}		 
#endif
// ��ȡDI14����ֵ    
#ifdef DI14
    if (IO_Read(DI14)>0)
	{
		DI |= DI14FLAG;
	}		 
#endif
// ��ȡDI15����ֵ    
#ifdef DI15
    if (IO_Read(DI15)>0)
	{
		DI |= DI15FLAG;
	}		 
#endif
// ��ȡDI6����ֵ    
#ifdef DI16
    if (IO_Read(DI16)>0)
	{
		DI |= DI16FLAG;
	}		 
#endif
    DIVal = UserVars.DI; // ��ȡ�ϴδ洢��DIֵ 
	if (DI != (UserVars.DI&0xff)) // DI�����б仯
	{
        Delay_ms(20);      // ��ʱ20ms����	
        // �ٴζ�ȡDI1����ֵ    
		#ifdef DI1
        if ((DI&DI1FLAG) != (UserVars.DI&DI1FLAG)) // �ж�DI1�б仯
        {
              val = IO_Read(DI1);  // �ٴζ�ȡDI1 
              if (DI&DI1FLAG)      // DI1=1
              {
                    if (val == 1)	   // �ٴζ�DI1����Ϊ1
                        {
                            UserVars.DI |= DI1FLAG;  // �ж�DI1=1,����¼
                        }								
                }
                else								 // DI1=0
                {
                        if (val == 0)    // �ٴζ�DI1����Ϊ0
                        {
                            UserVars.DI &= ~DI1FLAG;  // �ж�DI1=0,����¼
                        }
                }			
        }		 
		#endif

        // �ٴζ�ȡDI2����ֵ    
		#ifdef DI2
        if ((DI&DI2FLAG) != (UserVars.DI&DI2FLAG)) // �ж�DI2�б仯
        {
            val = IO_Read(DI2);  // �ٴζ�ȡDI2 
            if (DI&DI2FLAG)      // DI2=1
            {
                if (val == 1)	   // �ٴζ�DI2����Ϊ1
                {
                    UserVars.DI |= DI2FLAG;  // �ж�DI2=1,����¼
                }								
            }
            else								 // DI2=0
            {
                if (val == 0)    // �ٴζ�DI2����Ϊ0
                {
                    UserVars.DI &= ~DI2FLAG;  // �ж�DI2=0,����¼
                }
            }			
        }		 
		#endif

      // �ٴζ�ȡDI3����ֵ    
        #ifdef DI3
        if ((DI&DI3FLAG) != (UserVars.DI&DI3FLAG)) // �ж�DI3�б仯
        {
            val = IO_Read(DI3);  // �ٴζ�ȡDI3 
            if (DI&DI3FLAG)      // DI3=1
            {
                if (val == 1)	   // �ٴζ�DI3����Ϊ1
                {
                    UserVars.DI |= DI3FLAG;  // �ж�DI3=1,����¼
                }								
            }
            else								 // DI3=0
            {
                if (val == 0)    // �ٴζ�DI3����Ϊ0
                {
                    UserVars.DI &= ~DI3FLAG;  // �ж�DI3=0,����¼
                }
            }			
        }		 
        #endif	
	
      // �ٴζ�ȡDI4����ֵ    
		#ifdef DI4
        if ((DI&DI4FLAG) != (UserVars.DI&DI4FLAG)) // �ж�DI4�б仯
        {
            val = IO_Read(DI4);  // �ٴζ�ȡDI4 
            if (DI&DI4FLAG)      // DI4=1
            {
                if (val == 1)	   // �ٴζ�DI4����Ϊ1
                {
                    UserVars.DI |= DI4FLAG;  // �ж�DI4=1,����¼
                }								
            }
            else								 // DI4=0
            {
                if (val == 0)    // �ٴζ�DI4����Ϊ0
                {
                    UserVars.DI &= ~DI4FLAG;  // �ж�DI4=0,����¼
                }
            }			
        }		 
		#endif	

      // �ٴζ�ȡDI5����ֵ    
		#ifdef DI5
        if ((DI&DI5FLAG) != (UserVars.DI&DI5FLAG)) // �ж�DI5�б仯
        {
            val = IO_Read(DI5);  // �ٴζ�ȡDI5 
            if (DI&DI5FLAG)      // DI5=1
            {
                if (val == 1)	   // �ٴζ�DI5����Ϊ1
                {
                    UserVars.DI |= DI5FLAG;  // �ж�DI5=1,����¼
                }								
            }
            else								 // DI5=0
            {
                if (val == 0)    // �ٴζ�DI5����Ϊ0
                {
                    UserVars.DI &= ~DI5FLAG;  // �ж�DI5=0,����¼
                }
            }			
        }		 
		#endif	
			
      // �ٴζ�ȡDI6����ֵ    
		#ifdef DI6
        if ((DI&DI6FLAG) != (UserVars.DI&DI6FLAG)) // �ж�DI6�б仯
        {
            val = IO_Read(DI6);  // �ٴζ�ȡDI6 
            if (DI&DI6FLAG)      // DI6=1
            {
                if (val == 1)	   // �ٴζ�DI6����Ϊ1
                {
                    UserVars.DI |= DI6FLAG;  // �ж�DI6=1,����¼
                }								
            }
            else								 // DI6=0
            {
                if (val == 0)    // �ٴζ�DI6����Ϊ0
                {
                    UserVars.DI &= ~DI6FLAG;  // �ж�DI6=0,����¼
                }
            }			
        }		 
		#endif			
			
      // �ٴζ�ȡDI7����ֵ    
        #ifdef DI7
        if ((DI&DI7FLAG) != (UserVars.DI&DI7FLAG)) // �ж�DI7�б仯
        {
            val = IO_Read(DI7);  // �ٴζ�ȡDI7 
            if (DI&DI7FLAG)      // DI7=1
            {
                if (val == 1)	   // �ٴζ�DI7����Ϊ1
                {
                    UserVars.DI |= DI7FLAG;  // �ж�DI7=1,����¼
                }								
            }
            else								 // DI7=0
            {
                if (val == 0)    // �ٴζ�DI7����Ϊ0
                {
                    UserVars.DI &= ~DI7FLAG;  // �ж�DI7=0,����¼
                }
            }			
        }		 
        #endif			
	
      // �ٴζ�ȡDI8����ֵ    
        #ifdef DI8
        if ((DI&DI8FLAG) != (UserVars.DI&DI8FLAG)) // �ж�DI8�б仯
        {
            val = IO_Read(DI8);  // �ٴζ�ȡDI8 
            if (DI&DI8FLAG)      // DI8=1
            {
                if (val == 1)	   // �ٴζ�DI8����Ϊ1
                {
                    UserVars.DI |= DI8FLAG;  // �ж�DI8=1,����¼
                }								
            }
            else								 // DI8=0
            {
                if (val == 0)    // �ٴζ�DI8����Ϊ0
                {
                    UserVars.DI &= ~DI8FLAG;  // �ж�DI8=0,����¼
                }
            }			
        }		 
        #endif	
			
      // �ٴζ�ȡDI9����ֵ    
		#ifdef DI9
        if ((DI&DI9FLAG) != (UserVars.DI&DI9FLAG)) // �ж�DI9�б仯
        {
            val = IO_Read(DI9);  // �ٴζ�ȡDI9 
            if (DI&DI9FLAG)      // DI9=1
            {
                if (val == 1)	   // �ٴζ�DI9����Ϊ1
                {
                    UserVars.DI |= DI9FLAG;  // �ж�DI9=1,����¼
                }								
            }
            else								 // DI9=0
            {
                if (val == 0)    // �ٴζ�DI9����Ϊ0
                {
                    UserVars.DI &= ~DI9FLAG;  // �ж�DI9=0,����¼
                }
            }			
        }		 
		#endif			

      // �ٴζ�ȡDI10����ֵ    
		#ifdef DI10
        if ((DI&DI10FLAG) != (UserVars.DI&DI10FLAG)) // �ж�DI10�б仯
        {
            val = IO_Read(DI10);  // �ٴζ�ȡDI10 
            if (DI&DI10FLAG)      // DI10=1
            {
                if (val == 1)	   // �ٴζ�DI10����Ϊ1
                {
                    UserVars.DI |= DI10FLAG;  // �ж�DI10=1,����¼
                }								
            }
            else								 // DI10=0
            {
                if (val == 0)    // �ٴζ�DI10����Ϊ0
                {
                    UserVars.DI &= ~DI10FLAG;  // �ж�DI10=0,����¼
                }
            }			
        }		 
		#endif
			
      // �ٴζ�ȡDI11����ֵ    
		#ifdef DI11
        if ((DI&DI11FLAG) != (UserVars.DI&DI11FLAG)) // �ж�DI11�б仯
        {
            val = IO_Read(DI11);  // �ٴζ�ȡDI11 
            if (DI&DI11FLAG)      // DI11=1
            {
                if (val == 1)	   // �ٴζ�DI11����Ϊ1
                {
                    UserVars.DI |= DI11FLAG;  // �ж�DI11=1,����¼
                }								
            }
            else								 // DI11=0
            {
                if (val == 0)    // �ٴζ�DI11����Ϊ0
                {
                    UserVars.DI &= ~DI11FLAG;  // �ж�DI11=0,����¼
                }
            }			
        }		 
		#endif
			
      // �ٴζ�ȡDI12����ֵ    
		  #ifdef DI12
        if ((DI&DI12FLAG) != (UserVars.DI&DI12FLAG)) // �ж�DI12�б仯
        {
            val = IO_Read(DI12);  // �ٴζ�ȡDI12 
            if (DI&DI12FLAG)      // DI12=1
            {
                if (val == 1)	   // �ٴζ�DI12����Ϊ1
                {
                    UserVars.DI |= DI12FLAG;  // �ж�DI12=1,����¼
                }								
            }
            else								 // DI12=0
            {
                if (val == 0)    // �ٴζ�DI12����Ϊ0
                {
                    UserVars.DI &= ~DI12FLAG;  // �ж�DI12=0,����¼
                }
            }			
        }		 
		  #endif

      // �ٴζ�ȡDI13����ֵ    
		#ifdef DI13
        if ((DI&DI13FLAG) != (UserVars.DI&DI13FLAG)) // �ж�DI13�б仯
        {
            val = IO_Read(DI13);  // �ٴζ�ȡDI13 
            if (DI&DI13FLAG)      // DI13=1
            {
                if (val == 1)	   // �ٴζ�DI13����Ϊ1
                {
                    UserVars.DI |= DI13FLAG;  // �ж�DI13=1,����¼
                }								
            }
            else								 // DI13=0
            {
                if (val == 0)    // �ٴζ�DI13����Ϊ0
                {
                    UserVars.DI &= ~DI13FLAG;  // �ж�DI13=0,����¼
                }
            }			
        }		 
		#endif			

      // �ٴζ�ȡDI14����ֵ    
		#ifdef DI14
        if ((DI&DI14FLAG) != (UserVars.DI&DI14FLAG)) // �ж�DI14�б仯
        {
            val = IO_Read(DI14);  // �ٴζ�ȡDI14 
            if (DI&DI14FLAG)      // DI14=1
            {
                if (val == 1)	   // �ٴζ�DI14����Ϊ1
                {
                    UserVars.DI |= DI14FLAG;  // �ж�DI14=1,����¼
                }								
            }
            else								 // DI14=0
            {
                if (val == 0)    // �ٴζ�DI14����Ϊ0
                {
                    UserVars.DI &= ~DI14FLAG;  // �ж�DI14=0,����¼
                }
            }			
        }		 
		#endif	

		// �ٴζ�ȡDI15����ֵ    
		#ifdef DI15
        if ((DI&DI15FLAG) != (UserVars.DI&DI15FLAG)) // �ж�DI15�б仯
        {
            val = IO_Read(DI15);  // �ٴζ�ȡDI15
            if (DI&DI15FLAG)      // DI15=1
            {
                if (val == 1)	   // �ٴζ�DI15����Ϊ1
                {
                    UserVars.DI |= DI15FLAG;  // �ж�DI15=1,����¼
                }								
            }
            else								 // DI15=0
            {
                if (val == 0)    // �ٴζ�DI15����Ϊ0
                {
                    UserVars.DI &= ~DI15FLAG;  // �ж�DI15=0,����¼
                }
            }			
        }		 
		#endif

			// �ٴζ�ȡDI16����ֵ    
		#ifdef DI16
        if ((DI&DI16FLAG) != (UserVars.DI&DI16FLAG)) // �ж�DI16�б仯
        {
            val = IO_Read(DI16);  // �ٴζ�ȡDI16
            if (DI&DI16FLAG)      // DI16=1
            {
                if (val == 1)	   // �ٴζ�DI16����Ϊ1
                {
                    UserVars.DI |= DI16FLAG;  // �ж�DI16=1,����¼
                }								
            }
            else								 // DI16=0
            {
                if (val == 0)    // �ٴζ�DI16����Ϊ0
                {
                    UserVars.DI &= ~DI16FLAG;  // �ж�DI16=0,����¼
                }
            }			
        }		 
		#endif			
	}
	      
    
// ������SPI���߶�ȡDI����
    Num = 0;
#if (DI1_8SPI_EN > 0)       // SPI���߶�ȡDI1-8ʹ��
    Num++;
#endif
#if (DI9_16SPI_EN > 0)      // SPI���߶�ȡDI9-16ʹ��
    Num++;
#endif
#if (DI17_24SPI_EN > 0)     // SPI���߶�ȡDI17-24ʹ��
    Num++;
#endif
#if (DI25_32SPI_EN > 0)     // SPI���߶�ȡDI25-32ʹ��
    Num++;
#endif
    
#if ((DI1_8SPI_EN > 0)||(DI9_16SPI_EN > 0)||(DI17_24SPI_EN > 0)||(DI25_32SPI_EN > 0))   
    if (Num > 0)
    {
        DI_SPIRead(DIBuf, Num);  // SPI���߶�ȡDI����
        
        // EMB88616I �ȶ���DI17~DI24�ŵ�DIBuf[0];�����DI9~DI16�ŵ�DIBuf[1];
        // ����2�����ݻ���λ��
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
    
    if (DIVal != UserVars.DI) // DI�����б仯
    {
        return ERR_TRUE;    // ������ȷ, DI�б仯ֵ  
    }
    else                   
    {
        return ERR_FALSE;   // ���ش���, DI�ޱ仯ֵ
    }
}

/***********************************************************************************
* Function: Key_Read;
*
* Description: ��ȡ����K1-K8��ֵ;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: ���ؼ�ֵ��KNONE��K1VAL-K8VAL;
*
* Note:   �Ѿ�����20ms��������; ������֧��1-8��������ȡ, , �û����Բ���������Ӹ��ఴ����ȡ;
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
#define  ALARM_COUNT   5  // 5��
void RTC_Test(void)
{
    INT32S flag;
    RTC_TIME rtc;

    
    // ��ʼ��ʱ��
    rtc.year = 17;
    rtc.month = 12;
    rtc.day  = 31;
    rtc.hour = 23;
    rtc.minute = 59;
    rtc.second = 30;
    rtc.ss = 0;
    
    flag = RTC_Read(&rtc); // ÿ��3��RTC��ʱ�����  
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
    
    #if (RTC_ALRIT_EN > 0)                   // �����ж�ʹ��   
    if (UserVars.Flag&RTC_ALRIT_FLAG)        // �Ѿ����������ж�
    {
        UserVars.Flag &= ~RTC_ALRIT_FLAG;    // ��������жϱ�־
        RTC_Ctrl(CMD_RTC_SET_ALMTIM_XS, ALARM_COUNT, 0);   // ��������ʱ��, (ALARM_COUNT)�����������ж�
        #if (DEBUG_APP_EN == 1)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        { 
            printf("AT+INFO=RTC����%d���������ӱ���\r\n", ALARM_COUNT);
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
        printf("AT+DO=%d,", DO_NUM);   // ��ӡDOֵ
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
        printf("AT+DI=%d,", DI_NUM);   // ��ӡDIֵ
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
//   EEPROM��д���� 
/****************************************************************/ 
    flag = EEPROM_Test();  // EEPROM��д����    
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
//   SPI FLASH��д���� 
/****************************************************************/     
    #if ((SPIFLASH_EN > 0)&&(SPIFLASH_MODE == 0)) // SPI FLASHʹ�ܲ��Ҷ�д��ʽΪ������д
        #if (SPIFLASH_TYPE  == W25QXX)
        flag = W25QXX_Test();    // W25QXX FLASH��д����
        #endif
        #if (SPIFLASH_TYPE  == AT45DBXX)
        flag = AT45DBXX_Test();  // AT45DBXX FLASH��д����
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

	UserVars.DO = 0x55555555;  // ��ʼ��DOֵ
    t = 0;	         
    while(1)
    {		
		UserVars.TaskRunStatus |= TASK_IO_FLAG; // ���ñ���������״̬��־
		Delay_ms(20);	                        // ��ʱ20ms
        t +=20 ;                                // ����ʱ�������

/*************************************************************************************************************/        
//      ��ȡ���뿪�ز���
/*************************************************************************************************************/        
        // ��ȡ���뿪��
        #ifdef SW_NUM                                    
        sw = SW_Read();
        if (sw != UserVars.SW) // ���뿪���б仯
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
//      ��ȡ��������, �а�������һ������������ӡ�������������Ϣ
/*************************************************************************************************************/ 
//        #if (PRODUCT_TYPE == EMB8628I)&&(CH455_EN)
//        Key = CH455_Read();                    // ��ȡ��ֵ
//        #else 
//        Key = Key_Read();			           // ��ȡ������ֵ
//		#endif
//        if (Key != KNONE)                      // �жϰ����Ƿ���Ч
//        {
//            UserVars.Key = Key;                // ��ֵ����ֵ
//            #if (DEBUG_APP_EN == 1)
//            if (UserVars.Para.ATFlag&AT_INFO_FLAG)
//            { 
//                printf("AT+KEY=%d\r\n", Key);   
//            }
//            #endif            
//            IO_Ctrl(ALARM, CMD_IO_ON_T, 50);   // ���Ʒ�������50ms
//        }
/*************************************************************************************************************/        
//      DI�������
/*************************************************************************************************************/ 
        //if (((t%UserVars.Para.DI.t1)==0)||(UserVars.Para.DI.Mode == AT_MODE_START)) // ���UserVars.Para.DI.t1ʱ���ȡDIֵ ������������ȡģʽ
        flag = DI_Read();           // ��ȡDIֵ
        if (flag == ERR_TRUE)       // DI�б仯
        {
            UserVars.DI_P = ~UserVars.DI;  // ���DI�����źű������ܷ�����߹������, Ҫ��������ȡ������
            
            #if (MODBUS_SLAVE_EN > 0)  // Modbus�豸ģʽʹ��
            ModbusDisInput[0] = UserVars.DI_P&0xff;       // ��DI1-DI8����ֵ������ɢ����Ĵ���
            ModbusDisInput[1] = (UserVars.DI_P>>8)&0xff;  // ��DI9-DI16����ֵ������ɢ����Ĵ���
            ModbusDisInput[2] = (UserVars.DI_P>>16)&0xff; // ��DI17-D24����ֵ������ɢ����Ĵ���
            ModbusDisInput[3] = (UserVars.DI_P>>24)&0xff; // ��DI25-DI32����ֵ������ɢ����Ĵ���
            #endif
            
            #if (DEBUG_APP_EN == 1)
            DI_Printf();
            #endif
        } 
        else
        {                
            
            #if (DEBUG_APP_EN == 1)
            if ((t%3000)==0)    // ÿ��3����ʾһ��
            {
                DI_Printf();
            } 
            
            #endif
        }
      
/**************************************************************************************************/        
//      DO���(�����̵���)���Գ���
/**************************************************************************************************/  
        if ((t%1000)==0)    // ���3��������DO
        { 
			//DOFunction_Test();
            #if (MODBUS_SLAVE_EN > 0)        // Modbus�豸ģʽʹ��
            UserVars.DO = ModbusCoils[0] + ((INT32U)ModbusCoils[1]<<8)+((INT32U)ModbusCoils[2]<<16)+((INT32U)ModbusCoils[3]<<24);
            #else
            // DO������0��1
//            if (UserVars.DO == 0x55555555)
//            {
//                UserVars.DO = 0xAAAAAAAA;     // �����µ�DO���ֵ
//            }
//            else
//            {
//                UserVars.DO = 0x55555555;     // �����µ�DO���ֵ
//            }
            #endif            
//            DO_Write(UserVars.DO);            // ���DO
//            
//            #if (DEBUG_APP_EN == 1)
//            DO_Printf();
//            #endif
        }
/**************************************************************************************************/        
// ALARM��LED����, RTCʵʱʱ�Ӳ���
/**************************************************************************************************/         
		if ((t%1000)==0)	  // 1��ִ��1��
		{

            IO_Ctrl(RUN_LED, CMD_IO_NEG, 0); //RUN LED���1����˸  
            #ifdef  JP9_P1
            IO_Ctrl(JP9_P1, CMD_IO_NEG, 0);  // ���1�����1��0
            // ������IO_Write(JP9_P1,1)���1, IO_Write(JP9_P1,0)���0 
            #endif
        }        
//        if ((t%3000)==0)      // 3��ִ��1�� 
//        {
//            #if (RTC_EN > 0)
//            RTC_Test();       //  RTC��д����
//            #endif

//            // ����������
//			IO_Ctrl(ALARM, CMD_IO_ON_T, 50);  // ���������5����50ms;
//		}
	} // while(1)����
}
#endif
/***********************************************************************************/
// �ļ�����
/***********************************************************************************/