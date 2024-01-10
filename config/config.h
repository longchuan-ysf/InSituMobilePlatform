/************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: config.h
* Project  : STM32F1XX/4XXϵ��ģ�����
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: ���ļ�������������������ͷ�ļ�;�ͻ������޸Ĵ��ļ�, ��ɲ�Ʒ�ͺ�ѡ��
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
#ifndef __CONFIG_H 
#define __CONFIG_H 

#include "const.h" 

/************************************************************************************/
// UCOS-II ʹ�ܶ��� 
// ����UCOS-II��, �����ó�1; ����UCOS-II��, �����ó�0; 
/************************************************************************************/
#define UCOS_II_EN          1	    // 1:ʹ��UCOS-II; 0����ʹ��UCOS-II;

/************************************************************************************/
// ��Ʒ�ͺŶ���: ��2�ַ���
//1. ����Target options.../C C++/Preprocessor Symbols Define�ж���ѡ���Ʒ�ͺ�
//2. ��������ݹ���Ĳ�Ʒ�ͺ�ѡ��, ֻ��ѡ��һ��, ����ע���� 
/************************************************************************************/
#ifdef EMB8600I_TYPE
#define  PRODUCT_TYPE  EMB8600I	 // ��Ƕ����-���ذ��Ʒ
#endif
#ifdef EMB8612IA_TYPE
#define  PRODUCT_TYPE  EMB8612IA // ��Ƕ����-���ذ��Ʒ
#endif
#ifdef EMB8616I_TYPE
#define  PRODUCT_TYPE  EMB8616I	 // ��Ƕ����-���ذ��Ʒ
#endif
#ifdef EMB8618I_TYPE
#define  PRODUCT_TYPE  EMB8618I	 // ��Ƕ����-���ذ��Ʒ
#endif

#ifdef EMB8626I_TYPE
#define  PRODUCT_TYPE  EMB8626I	 // ��Ƕ����-���ذ��Ʒ
#endif

#ifdef EMB8628I_TYPE
#define  PRODUCT_TYPE  EMB8628I	 // ��Ƕ����-���ذ��Ʒ
#endif

#ifdef EMB8610IDK_TYPE
#define  PRODUCT_TYPE  EMB8610IDK	 // ��Ƕ����-���ذ��Ʒ
#endif

#ifdef STM32F107VC_TYPE
#define  PRODUCT_TYPE  STM32F107VC_DK	 // ��Ƕ����-��STM32F107VCΪ����ģ��Ŀ�����
#endif
#ifdef STM32F103VE_TYPE
#define  PRODUCT_TYPE  STM32F103VE_DK	 // ��Ƕ����-��STM32F107VEΪ����ģ��Ŀ�����
#endif
#ifdef STM32F103ZE_TYPE
#define  PRODUCT_TYPE  STM32F103ZE_DK	 // ��Ƕ����-��STM32F107ZEΪ����ģ��Ŀ�����
#endif

#ifdef STM32F407VE_TYPE
#define  PRODUCT_TYPE  STM32F407VE_DK	 // ��Ƕ����-��STM32F407VEΪ����ģ��Ŀ�����
#endif

#ifdef STM32F407ZE_TYPE
#define  PRODUCT_TYPE  STM32F407ZE_DK	 // ��Ƕ����-��STM32F407ZEΪ����ģ��Ŀ�����
#endif

#ifdef STM32F407ZG_TYPE
#define  PRODUCT_TYPE  STM32F407ZG_DK	 // ��Ƕ����-��STM32F407ZGΪ����ģ��Ŀ�����
#endif

// �ͻ������ͺ�
#ifdef EMB7XXXA_TYPE
#define  PRODUCT_TYPE  EMB7XXXA	// �ͻ����ƹ��ذ�
#endif

/************************************************************************************/
// ����ģ���ͺ�ѡ��, ���ݹ���Ĳ�Ʒ�ͺ�ѡ��
/************************************************************************************/
#if (PRODUCT_TYPE == EMB8600I)      // ���ѡ���Ʒ�ͺ�: EMB8600I
#define  MODULE_CLASS STM32F107XX   // ���ò�ƷӦ�ú��Ĺ���ģ�����, ��Ӧ������STM32F107VC_xxxx_xxxxxxxx.lib
#define  MODULE_TYPE  STM32F107VC   // ���ò�ƷӦ�ú��Ĺ���ģ���ͺ�, ��Ӧ������STM32F107VC_xxxx_xxxxxxxx.lib
#include "EMB8600I_Config.h"        // ���ذ�EMB8600I���ܲ��������ļ�
#include "EMB8600I_IOConfig.h"      // ���ذ�EMB8600I IO�˿������ļ� 
#endif

#if (PRODUCT_TYPE == EMB8616I)      // ���ѡ���Ʒ�ͺ�: EMB8616I
#define  MODULE_CLASS STM32F107XX   // ���ò�ƷӦ�ú��Ĺ���ģ�����, ��Ӧ������STM32F107VC_xxxx_xxxxxxxx.lib
#define  MODULE_TYPE  STM32F107VC   // ���ò�ƷӦ�ú��Ĺ���ģ���ͺ�, ��Ӧ������STM32F107VC_xxxx_xxxxxxxx.lib
#include "EMB8616I_Config.h"        // ���ذ�EMB8616I���ܲ��������ļ�
#include "EMB8616I_IOConfig.h"      // ���ذ�EMB8616I IO�˿������ļ� 
#endif

#if (PRODUCT_TYPE == EMB8618I)      // ���ѡ���Ʒ�ͺ�: EMB8618I
#define  MODULE_CLASS STM32F107XX   // ���ò�ƷӦ�ú��Ĺ���ģ�����, ��Ӧ������STM32F107VC_xxxx_xxxxxxxx.lib
#define  MODULE_TYPE  STM32F107VC   // ���ò�ƷӦ�ú��Ĺ���ģ���ͺ�, ��Ӧ������STM32F107VC_xxxx_xxxxxxxx.lib
#include "EMB8618I_Config.h"        // ���ذ�EMB8618I���ܲ��������ļ�
#include "EMB8618I_IOConfig.h"      // ���ذ�EMB8618I IO�˿������ļ� 
#endif

#if (PRODUCT_TYPE == EMB8612IA)    	 // ���ѡ���Ʒ�ͺ�: EMB8612IA
#define  MODULE_CLASS STM32F103XX  	 // ���ò�ƷӦ�ú��Ĺ���ģ�����, ��Ӧ������STM32F103ZE_xxxx_xxxxxxxx.lib
#define  MODULE_TYPE  STM32F103ZE  	 // ���ò�ƷӦ�ú��Ĺ���ģ���ͺ�, ��Ӧ������STM32F103ZE_xxxx_xxxxxxxx.lib
#include "EMB8612IA_Config.h"      	 // ���ذ�EMB8612IA���ܲ��������ļ�
#include "EMB8612IA_IOConfig.h"    	 // ���ذ�EMB8612IA IO�˿������ļ� 
#endif

#if (PRODUCT_TYPE == EMB8626I)          // ���ѡ���Ʒ�ͺ�: EMB8626I
#define  MODULE_CLASS STM32F407XX       // ���ò�ƷӦ�ú��Ĺ���ģ�����, ��Ӧ������STM32F407XX_xxxx_xxxxxxxx.lib
#define  MODULE_TYPE  STM32F407VE       // ���ò�ƷӦ�ú��Ĺ���ģ���ͺ�, ��Ӧ������STM32F407XX_xxxx_xxxxxxxx.lib
#include "EMB8626I_Config.h"            // ���ذ�EMB8626I���ܲ��������ļ�
#include "EMB8626I_IOConfig.h"          // ���ذ�EMB8626I IO�˿������ļ� 
#endif

#if (PRODUCT_TYPE == EMB8628I)          // ���ѡ���Ʒ�ͺ�: EMB8628I
#define  MODULE_CLASS STM32F407XX       // ���ò�ƷӦ�ú��Ĺ���ģ�����, ��Ӧ������STM32F407XX_xxxx_xxxxxxxx.lib
#define  MODULE_TYPE  STM32F407ZE       // ���ò�ƷӦ�ú��Ĺ���ģ���ͺ�, ��Ӧ������STM32F407XX_xxxx_xxxxxxxx.lib
#include "EMB8628I_Config.h"            // ���ذ�EMB8628I���ܲ��������ļ�
#include "EMB8628I_IOConfig.h"          // ���ذ�EMB8628I IO�˿������ļ� 
#endif

#if (PRODUCT_TYPE == EMB8610IDK)      // ���ѡ���Ʒ�ͺ�: EMB8610IDK
#define  MODULE_CLASS STM32F107XX     // ���ò�ƷӦ�ú��Ĺ���ģ�����, ��Ӧ������STM32F107VC_xxxx_xxxxxxxx.lib
#define  MODULE_TYPE  STM32F107VC     // ���ò�ƷӦ�ú��Ĺ���ģ���ͺ�, ��Ӧ������STM32F107VC_xxxx_xxxxxxxx.lib
#include "EMB8610I_Config.h"          // ���ذ�EMB8610IDK���ܲ��������ļ�
#include "EMB8610I_IOConfig.h"        // ���ذ�EMB8610IDK IO�˿������ļ� 
#endif

#if (PRODUCT_TYPE == STM32F107VC_DK)   // ���ѡ���Ʒ�ͺ�: STM32F107VC-DK
#define  MODULE_CLASS STM32F107XX      // ���ò�ƷӦ�ú��Ĺ���ģ�����, ��Ӧ������STM32F107VC_xxxx_xxxxxxxx.lib
#define  MODULE_TYPE  STM32F107VC      // ���ò�ƷӦ�ú��Ĺ���ģ���ͺ�, ��Ӧ������STM32F107VC_xxxx_xxxxxxxx.lib
#include "STM32F107VC_Config.h"        // ����ģ��STM32F107VC���ܲ��������ļ�
#include "STM32F107VC_IOConfig.h"      // ����ģ��STM32F107VC IO�˿������ļ� 
#endif



#if (PRODUCT_TYPE == STM32F103VE_DK)    // ���ѡ���Ʒ�ͺ�: STM32F103VE-DK
#define  MODULE_CLASS STM32F103XX       // ���ò�ƷӦ�ú��Ĺ���ģ�����, ��Ӧ������STM32F103VE_xxxx_xxxxxxxx.lib
#define  MODULE_TYPE  STM32F103VE       // ���ò�ƷӦ�ú��Ĺ���ģ���ͺ�, ��Ӧ������STM32F103VE_xxxx_xxxxxxxx.lib
#include "STM32F103VE_Config.h"         // ����ģ��STM32F103VE���ܲ��������ļ�
#include "STM32F103VE_IOConfig.h"       // ����ģ��STM32F103VE IO�˿������ļ� 
#endif

#if (PRODUCT_TYPE == STM32F103ZE_DK)    // ���ѡ���Ʒ�ͺ�: STM32F103ZE-DK
#define  MODULE_CLASS STM32F103XX  	 	// ���ò�ƷӦ�ú��Ĺ���ģ�����, ��Ӧ������STM32F103ZE_xxxx_xxxxxxxx.lib
#define  MODULE_TYPE  STM32F103ZE       // ���ò�ƷӦ�ú��Ĺ���ģ���ͺ�, ��Ӧ������STM32F103ZE_xxxx_xxxxxxxx.lib
#include "STM32F103ZE_Config.h"         // ����ģ��STM32F103ZE���ܲ��������ļ�
#include "STM32F103ZE_IOConfig.h"       // ����ģ��STM32F103ZE IO�˿������ļ� 
#endif

#if (PRODUCT_TYPE == STM32F407VE_DK)    // ���ѡ���Ʒ�ͺ�: STM32F407VE-DK
#define  MODULE_CLASS STM32F407XX       // ���ò�ƷӦ�ú��Ĺ���ģ�����, ��Ӧ������STM32F407XX_xxxx_xxxxxxxx.lib
#define  MODULE_TYPE  STM32F407VE       // ���ò�ƷӦ�ú��Ĺ���ģ���ͺ�, ��Ӧ������STM32F407XX_xxxx_xxxxxxxx.lib
#include "STM32F407VX_Config.h"         // ����ģ��STM32F407VE���ܲ��������ļ�
#include "STM32F407VX_IOConfig.h"       // ����ģ��STM32F407VE IO�˿������ļ� 
#endif

#if (PRODUCT_TYPE == STM32F407ZE_DK)    // ���ѡ���Ʒ�ͺ�: STM32F407ZE-DK
#define  MODULE_CLASS STM32F407XX       // ���ò�ƷӦ�ú��Ĺ���ģ�����, ��Ӧ������STM32F407XX_xxxx_xxxxxxxx.lib
#define  MODULE_TYPE  STM32F407ZE       // ���ò�ƷӦ�ú��Ĺ���ģ���ͺ�, ��Ӧ������STM32F407XX_xxxx_xxxxxxxx.lib
#include "STM32F407ZX_Config.h"         // ����ģ��STM32F407ZE���ܲ��������ļ�
#include "STM32F407ZX_IOConfig.h"       // ����ģ��STM32F407ZE IO�˿������ļ� 
#endif

#if (PRODUCT_TYPE == STM32F407ZG_DK)    // ���ѡ���Ʒ�ͺ�: STM32F407ZG-DK
#define  MODULE_CLASS STM32F407XX       // ���ò�ƷӦ�ú��Ĺ���ģ�����, ��Ӧ������STM32F407XX_xxxx_xxxxxxxx.lib
#define  MODULE_TYPE  STM32F407ZG       // ���ò�ƷӦ�ú��Ĺ���ģ���ͺ�, ��Ӧ������STM32F407XX_xxxx_xxxxxxxx.lib
//#include "STM32F407ZX_Config.h"         // ����ģ��STM32F407ZG���ܲ��������ļ�
//#include "STM32F407ZX_IOConfig.h"       // ����ģ��STM32F407ZG IO�˿������ļ� 
#include "EMB8628I_Config.h"            // ���ذ�EMB8628I���ܲ��������ļ�
#include "EMB8628I_IOConfig.h"          // ���ذ�EMB8628I IO�˿������ļ� 
#endif


// ���ͻ����ƹ��ذ��Ʒ, ���������޸�, ѡ����Ӧģ��
#if (PRODUCT_TYPE == EMB7XXXA)          // ���ѡ���Ʒ�ͺ�: EMB7XXXA
#define  MODULE_CLASS STM32F407XX       // ����Ӳ�����, ���ò�ƷӦ�ú��Ĺ���ģ�����
#define  MODULE_TYPE  STM32F407ZE       // ����Ӳ�����, ���ò�ƷӦ�ú��Ĺ���ģ���ͺ�
#include "EMB7XXXA_Config.h"            // ���ذ�EMB7XXXA���ܲ��������ļ�: �ɸ��ݲ�ƷӦ�ú���ģ���ͺ�, ��"���Ĺ���ģ��_Config.h"��ֵһ��
                                        // ���޸��ļ���Ϊ"EMB7XXXA_Config.h", ������ļ������Ӳ������޸�����
#include "EMB7XXXA_IOConfig.h"          // ���ذ�EMB7XXXA IO�˿������ļ�: �ɸ��ݲ�ƷӦ�ú���ģ���ͺ�, ��"���Ĺ���ģ��_IOConfig.h"��ֵһ��
                                        // ���޸��ļ���Ϊ"EMB7XXXA_IOConfig.h", ������ļ������Ӳ������޸�����
#endif


#endif
/************************************************************************************/
// �ļ�����
/************************************************************************************/

