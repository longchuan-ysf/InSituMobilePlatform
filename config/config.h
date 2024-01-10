/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: config.h
* Project  : STM32F1XX/4XX系列模块软件
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: 本文件是针对整个软件的配置头文件;客户可以修改此文件, 完成产品型号选择
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
// UCOS-II 使能定义 
// 在有UCOS-II下, 请设置成1; 在无UCOS-II下, 请设置成0; 
/************************************************************************************/
#define UCOS_II_EN          1	    // 1:使能UCOS-II; 0：不使用UCOS-II;

/************************************************************************************/
// 产品型号定义: 有2种方法
//1. 根据Target options.../C C++/Preprocessor Symbols Define中定义选择产品型号
//2. 或者请根据购买的产品型号选择, 只能选择一个, 其它注销掉 
/************************************************************************************/
#ifdef EMB8600I_TYPE
#define  PRODUCT_TYPE  EMB8600I	 // 中嵌凌云-工控板产品
#endif
#ifdef EMB8612IA_TYPE
#define  PRODUCT_TYPE  EMB8612IA // 中嵌凌云-工控板产品
#endif
#ifdef EMB8616I_TYPE
#define  PRODUCT_TYPE  EMB8616I	 // 中嵌凌云-工控板产品
#endif
#ifdef EMB8618I_TYPE
#define  PRODUCT_TYPE  EMB8618I	 // 中嵌凌云-工控板产品
#endif

#ifdef EMB8626I_TYPE
#define  PRODUCT_TYPE  EMB8626I	 // 中嵌凌云-工控板产品
#endif

#ifdef EMB8628I_TYPE
#define  PRODUCT_TYPE  EMB8628I	 // 中嵌凌云-工控板产品
#endif

#ifdef EMB8610IDK_TYPE
#define  PRODUCT_TYPE  EMB8610IDK	 // 中嵌凌云-工控板产品
#endif

#ifdef STM32F107VC_TYPE
#define  PRODUCT_TYPE  STM32F107VC_DK	 // 中嵌凌云-以STM32F107VC为核心模块的开发板
#endif
#ifdef STM32F103VE_TYPE
#define  PRODUCT_TYPE  STM32F103VE_DK	 // 中嵌凌云-以STM32F107VE为核心模块的开发板
#endif
#ifdef STM32F103ZE_TYPE
#define  PRODUCT_TYPE  STM32F103ZE_DK	 // 中嵌凌云-以STM32F107ZE为核心模块的开发板
#endif

#ifdef STM32F407VE_TYPE
#define  PRODUCT_TYPE  STM32F407VE_DK	 // 中嵌凌云-以STM32F407VE为核心模块的开发板
#endif

#ifdef STM32F407ZE_TYPE
#define  PRODUCT_TYPE  STM32F407ZE_DK	 // 中嵌凌云-以STM32F407ZE为核心模块的开发板
#endif

#ifdef STM32F407ZG_TYPE
#define  PRODUCT_TYPE  STM32F407ZG_DK	 // 中嵌凌云-以STM32F407ZG为核心模块的开发板
#endif

// 客户定制型号
#ifdef EMB7XXXA_TYPE
#define  PRODUCT_TYPE  EMB7XXXA	// 客户定制工控板
#endif

/************************************************************************************/
// 核心模块型号选择, 根据购买的产品型号选择
/************************************************************************************/
#if (PRODUCT_TYPE == EMB8600I)      // 如果选择产品型号: EMB8600I
#define  MODULE_CLASS STM32F107XX   // 设置产品应用核心工控模块类别, 对应驱动库STM32F107VC_xxxx_xxxxxxxx.lib
#define  MODULE_TYPE  STM32F107VC   // 设置产品应用核心工控模块型号, 对应驱动库STM32F107VC_xxxx_xxxxxxxx.lib
#include "EMB8600I_Config.h"        // 工控板EMB8600I功能参数配置文件
#include "EMB8600I_IOConfig.h"      // 工控板EMB8600I IO端口配置文件 
#endif

#if (PRODUCT_TYPE == EMB8616I)      // 如果选择产品型号: EMB8616I
#define  MODULE_CLASS STM32F107XX   // 设置产品应用核心工控模块类别, 对应驱动库STM32F107VC_xxxx_xxxxxxxx.lib
#define  MODULE_TYPE  STM32F107VC   // 设置产品应用核心工控模块型号, 对应驱动库STM32F107VC_xxxx_xxxxxxxx.lib
#include "EMB8616I_Config.h"        // 工控板EMB8616I功能参数配置文件
#include "EMB8616I_IOConfig.h"      // 工控板EMB8616I IO端口配置文件 
#endif

#if (PRODUCT_TYPE == EMB8618I)      // 如果选择产品型号: EMB8618I
#define  MODULE_CLASS STM32F107XX   // 设置产品应用核心工控模块类别, 对应驱动库STM32F107VC_xxxx_xxxxxxxx.lib
#define  MODULE_TYPE  STM32F107VC   // 设置产品应用核心工控模块型号, 对应驱动库STM32F107VC_xxxx_xxxxxxxx.lib
#include "EMB8618I_Config.h"        // 工控板EMB8618I功能参数配置文件
#include "EMB8618I_IOConfig.h"      // 工控板EMB8618I IO端口配置文件 
#endif

#if (PRODUCT_TYPE == EMB8612IA)    	 // 如果选择产品型号: EMB8612IA
#define  MODULE_CLASS STM32F103XX  	 // 设置产品应用核心工控模块类别, 对应驱动库STM32F103ZE_xxxx_xxxxxxxx.lib
#define  MODULE_TYPE  STM32F103ZE  	 // 设置产品应用核心工控模块型号, 对应驱动库STM32F103ZE_xxxx_xxxxxxxx.lib
#include "EMB8612IA_Config.h"      	 // 工控板EMB8612IA功能参数配置文件
#include "EMB8612IA_IOConfig.h"    	 // 工控板EMB8612IA IO端口配置文件 
#endif

#if (PRODUCT_TYPE == EMB8626I)          // 如果选择产品型号: EMB8626I
#define  MODULE_CLASS STM32F407XX       // 设置产品应用核心工控模块类别, 对应驱动库STM32F407XX_xxxx_xxxxxxxx.lib
#define  MODULE_TYPE  STM32F407VE       // 设置产品应用核心工控模块型号, 对应驱动库STM32F407XX_xxxx_xxxxxxxx.lib
#include "EMB8626I_Config.h"            // 工控板EMB8626I功能参数配置文件
#include "EMB8626I_IOConfig.h"          // 工控板EMB8626I IO端口配置文件 
#endif

#if (PRODUCT_TYPE == EMB8628I)          // 如果选择产品型号: EMB8628I
#define  MODULE_CLASS STM32F407XX       // 设置产品应用核心工控模块类别, 对应驱动库STM32F407XX_xxxx_xxxxxxxx.lib
#define  MODULE_TYPE  STM32F407ZE       // 设置产品应用核心工控模块型号, 对应驱动库STM32F407XX_xxxx_xxxxxxxx.lib
#include "EMB8628I_Config.h"            // 工控板EMB8628I功能参数配置文件
#include "EMB8628I_IOConfig.h"          // 工控板EMB8628I IO端口配置文件 
#endif

#if (PRODUCT_TYPE == EMB8610IDK)      // 如果选择产品型号: EMB8610IDK
#define  MODULE_CLASS STM32F107XX     // 设置产品应用核心工控模块类别, 对应驱动库STM32F107VC_xxxx_xxxxxxxx.lib
#define  MODULE_TYPE  STM32F107VC     // 设置产品应用核心工控模块型号, 对应驱动库STM32F107VC_xxxx_xxxxxxxx.lib
#include "EMB8610I_Config.h"          // 工控板EMB8610IDK功能参数配置文件
#include "EMB8610I_IOConfig.h"        // 工控板EMB8610IDK IO端口配置文件 
#endif

#if (PRODUCT_TYPE == STM32F107VC_DK)   // 如果选择产品型号: STM32F107VC-DK
#define  MODULE_CLASS STM32F107XX      // 设置产品应用核心工控模块类别, 对应驱动库STM32F107VC_xxxx_xxxxxxxx.lib
#define  MODULE_TYPE  STM32F107VC      // 设置产品应用核心工控模块型号, 对应驱动库STM32F107VC_xxxx_xxxxxxxx.lib
#include "STM32F107VC_Config.h"        // 工控模块STM32F107VC功能参数配置文件
#include "STM32F107VC_IOConfig.h"      // 工控模块STM32F107VC IO端口配置文件 
#endif



#if (PRODUCT_TYPE == STM32F103VE_DK)    // 如果选择产品型号: STM32F103VE-DK
#define  MODULE_CLASS STM32F103XX       // 设置产品应用核心工控模块类别, 对应驱动库STM32F103VE_xxxx_xxxxxxxx.lib
#define  MODULE_TYPE  STM32F103VE       // 设置产品应用核心工控模块型号, 对应驱动库STM32F103VE_xxxx_xxxxxxxx.lib
#include "STM32F103VE_Config.h"         // 工控模块STM32F103VE功能参数配置文件
#include "STM32F103VE_IOConfig.h"       // 工控模块STM32F103VE IO端口配置文件 
#endif

#if (PRODUCT_TYPE == STM32F103ZE_DK)    // 如果选择产品型号: STM32F103ZE-DK
#define  MODULE_CLASS STM32F103XX  	 	// 设置产品应用核心工控模块类别, 对应驱动库STM32F103ZE_xxxx_xxxxxxxx.lib
#define  MODULE_TYPE  STM32F103ZE       // 设置产品应用核心工控模块型号, 对应驱动库STM32F103ZE_xxxx_xxxxxxxx.lib
#include "STM32F103ZE_Config.h"         // 工控模块STM32F103ZE功能参数配置文件
#include "STM32F103ZE_IOConfig.h"       // 工控模块STM32F103ZE IO端口配置文件 
#endif

#if (PRODUCT_TYPE == STM32F407VE_DK)    // 如果选择产品型号: STM32F407VE-DK
#define  MODULE_CLASS STM32F407XX       // 设置产品应用核心工控模块类别, 对应驱动库STM32F407XX_xxxx_xxxxxxxx.lib
#define  MODULE_TYPE  STM32F407VE       // 设置产品应用核心工控模块型号, 对应驱动库STM32F407XX_xxxx_xxxxxxxx.lib
#include "STM32F407VX_Config.h"         // 工控模块STM32F407VE功能参数配置文件
#include "STM32F407VX_IOConfig.h"       // 工控模块STM32F407VE IO端口配置文件 
#endif

#if (PRODUCT_TYPE == STM32F407ZE_DK)    // 如果选择产品型号: STM32F407ZE-DK
#define  MODULE_CLASS STM32F407XX       // 设置产品应用核心工控模块类别, 对应驱动库STM32F407XX_xxxx_xxxxxxxx.lib
#define  MODULE_TYPE  STM32F407ZE       // 设置产品应用核心工控模块型号, 对应驱动库STM32F407XX_xxxx_xxxxxxxx.lib
#include "STM32F407ZX_Config.h"         // 工控模块STM32F407ZE功能参数配置文件
#include "STM32F407ZX_IOConfig.h"       // 工控模块STM32F407ZE IO端口配置文件 
#endif

#if (PRODUCT_TYPE == STM32F407ZG_DK)    // 如果选择产品型号: STM32F407ZG-DK
#define  MODULE_CLASS STM32F407XX       // 设置产品应用核心工控模块类别, 对应驱动库STM32F407XX_xxxx_xxxxxxxx.lib
#define  MODULE_TYPE  STM32F407ZG       // 设置产品应用核心工控模块型号, 对应驱动库STM32F407XX_xxxx_xxxxxxxx.lib
//#include "STM32F407ZX_Config.h"         // 工控模块STM32F407ZG功能参数配置文件
//#include "STM32F407ZX_IOConfig.h"       // 工控模块STM32F407ZG IO端口配置文件 
#include "EMB8628I_Config.h"            // 工控板EMB8628I功能参数配置文件
#include "EMB8628I_IOConfig.h"          // 工控板EMB8628I IO端口配置文件 
#endif


// 给客户定制工控板产品, 请在这里修改, 选择相应模块
#if (PRODUCT_TYPE == EMB7XXXA)          // 如果选择产品型号: EMB7XXXA
#define  MODULE_CLASS STM32F407XX       // 根据硬件设计, 设置产品应用核心工控模块类别
#define  MODULE_TYPE  STM32F407ZE       // 根据硬件设计, 设置产品应用核心工控模块型号
#include "EMB7XXXA_Config.h"            // 工控板EMB7XXXA功能参数配置文件: 可根据产品应用核心模块型号, 将"核心工控模块_Config.h"赋值一份
                                        // 并修改文件名为"EMB7XXXA_Config.h", 在这个文件里根据硬件设计修改配置
#include "EMB7XXXA_IOConfig.h"          // 工控板EMB7XXXA IO端口配置文件: 可根据产品应用核心模块型号, 将"核心工控模块_IOConfig.h"赋值一份
                                        // 并修改文件名为"EMB7XXXA_IOConfig.h", 在这个文件里根据硬件设计修改配置
#endif


#endif
/************************************************************************************/
// 文件结束
/************************************************************************************/

