/************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: const.h
* Project  : STM32F1XX/4XXϵ��ģ�����
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2020.1.1			
* Email:   EmbedARM@126.com
* 
* Description: ���ļ������������ȫ�ֳ�������, �û����ɸ���;
*
* Others: ���ļ��ĵ��κζ��嶼�����޸�,�������!
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
#ifndef __CONST_H 
#define __CONST_H 

/*************************************************************************************/
//  ����ģ�������, ���¶�����Բ����޸�
/*************************************************************************************/
#define  STM32F107XX    0   // STM32F107XXϵ�к���ģ��
#define  STM32F103XX    1   // STM32F103XXϵ�к���ģ��
#define  STM32F407XX    2   // STM32F407XXϵ�к���ģ��
#define  STM32F417XX    3   // STM32F417XXϵ�к���ģ��

/*************************************************************************************/
//  ����ģ���ͺŶ���, ���¶�����Բ����޸�
/*************************************************************************************/
#define  STM32F107VC  	0   // ԭ�е�EMB8610Iģ�����ڹ�Ϊ���ģ���ͺ� 
#define  STM32F103VE 	1
#define  STM32F103ZE  	2   // ����EMB8612I �����ϰ汾V1.02���°汾V1.10 
#define  STM32F407VE  	3
#define  STM32F407ZE  	4
#define  STM32F407VG  	5
#define  STM32F407ZG  	6

/*************************************************************************************/
//  ��Ʒ���ͺŶ���, �����Ѿ�������Բ����޸ģ�����������
/*************************************************************************************/
#define  EMB8600I    	1   // ��Ƕ����-���ذ��Ʒ
#define  EMB8610IDK    	2   // ��Ƕ����-�������Ʒ
#define  EMB8612IA    	3	// ��Ƕ����-���ذ��Ʒ
#define  EMB8616I    	4	// ��Ƕ����-���ذ��Ʒ
#define  EMB8618I    	5	// ��Ƕ����-���ذ��Ʒ
#define  EMB8626I    	6	// ��Ƕ����-���ذ��Ʒ
#define  EMB8628I    	7	// ��Ƕ����-���ذ��Ʒ

#define  STM32F107VC_DK 101	// ��Ƕ����-��STM32F107VCΪ����ģ��Ŀ�����
#define  STM32F103VE_DK 102	// ��Ƕ����-��STM32F103VEΪ����ģ��Ŀ�����
#define  STM32F103ZE_DK 103	// ��Ƕ����-��STM32F103ZEΪ����ģ��Ŀ�����
#define  STM32F407VE_DK 104	// ��Ƕ����-��STM32F407VEΪ����ģ��Ŀ�����
#define  STM32F407ZE_DK 105	// ��Ƕ����-��STM32F407ZEΪ����ģ��Ŀ�����
#define  STM32F407ZG_DK 106	// ��Ƕ����-��STM32F407ZGΪ����ģ��Ŀ�����


#define  EMB7XXXA       150	// ��Ƕ����-���ͻ����Ʋ�Ʒ

/*************************************************************************************/
//  �����������Ͷ���, ���¶�����Բ����޸�
/*************************************************************************************/
#define  null    0
#define  NULL    0
#define  false   0
#define  true    1
#define  OFF     0
#define  ON      1
#define  CLOSE   0
#define  OPEN    1
#define  RSP_OK	 0xff

/*************************************************************************************/
//  �������Ͷ���, ���¶�����Բ����޸�
/*************************************************************************************/
typedef unsigned char  INT8U;      // 8λ�޷�����                          
typedef signed   char  INT8S;      // 8λ�з�����                         
typedef unsigned short INT16U;     // 16λ�޷�����                            
typedef signed   short INT16S;     // 16λ�з�����                          
typedef unsigned int   INT32U;     // 32λ�޷�����                            
typedef signed   int   INT32S;     // 32λ�з����� 
typedef unsigned long long INT64U; // 64λ�޷�����                            
typedef long long      INT64S;     // 64λ�з�����                        
typedef float          FP32;       // �����ȸ�����                    
typedef double         FP64;       // ˫���ȸ����� 

typedef  void  (*FUNCTION_VOID)(void);  

// 32λ����Ͻṹ
typedef union 
{
    struct 
    {
        unsigned char c0;   // LSB
        unsigned char c1;   
        unsigned char c2;   
        unsigned char c3;   // MSB
    }chars;

    struct
    {
        unsigned short w0;  // LSW 
        unsigned short w1;  // MSW
    }ints;

    unsigned int d;         // �޷���32λ
	int          s;         // �з���32λ
}INT32_TypeDef;

// 16λ����Ͻṹ
typedef union  
{
    struct 
    {
        unsigned char c0;   // LSB
		unsigned char c1;   // MSB 
    } chars;   
    unsigned short d;       // �޷���16λ
    short          s;       // �з���16λ
}INT16_TypeDef;

#define EXRAM __attribute__ ((section ("RW_RAM1")))	   //��EXRAM���������嵽�ⲿRAM��, ֻ���ں���ģ��STM32F103ZE��ʹ��, ����: INT32U tmpreg  EXRAM;
#define CCRAM __attribute__ ((section ("CCM_IRAM")))   //��CCRAM���������嵽����RAM��, ֻ���ں���ģ��STM32F407XX��ʹ��, ����: INT32U tmpreg  CCRAM; 

/*************************************************************************************/
//  ������붨��, ���¶�����Բ����޸�
/*************************************************************************************/
#define  ERR_OK   	 0	  // ��ȷ
#define  ERR_TRUE    0	  // �ɹ�
#define  ERR_FALSE   1	  // ʧ��
#define  ERR_TIMEOUT 2	  // ��ʱ����
#define  ERR_PARA	 3	  // ������������
#define  ERR_CRC     4	  // CRCУ�����
#define  ERR_HWID    5    // Ӳ��ʶ�����
#define  ERR_NOINIT  6    // ���Ӳ��δ��ʼ��
#define  ERR_NOFIND  7    // û�з���
#define  ERR_BUFFULL 8    // �����Ѿ���
#define  ERR_BUSY    9    // æ
#define  ERR_DMABUSY 10   // DMAæ�������豸ռ��

/************************************************************************************/
//  ���ش洢�������̷����� 
/************************************************************************************/
#define SPIFLASH_DISK    0    // SPI FLASH����Ϊ�߼�������0
#define SD_DISK          1    // SD������Ϊ�߼�������1;	
#define USB_DISK         2    // U������Ϊ�߼�������2;
#define NFLASH_DISK      3    // NAND FLASH����Ϊ�߼�������3;

/************************************************************************************/
//  ������ȴ���־���� 
/************************************************************************************/
#define SPI1_WAIT_FLAG    0x00000001
#define SPI2_WAIT_FLAG    0x00000002
#define SPI3_WAIT_FLAG    0x00000004


#endif

/***********************************************************************************/
// �ļ�����
/***********************************************************************************/
