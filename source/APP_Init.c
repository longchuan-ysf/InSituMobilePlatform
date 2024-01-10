/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: APP_Init.c
* Project  : STM32F1XX/4XX系列模块软件
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.00
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: 本文件是应用程序及驱动库的初始化函数, 根据Conifg.h里的配置进行初始化
*
* Others: 参看API_Init()函数;
*
* Function List: void  API_Init(void);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/

/************************************************************************************/
// 引用外部头文件
/************************************************************************************/
#include "config.h"
#include "vars.h"
#include "UserVars.h"
#include "STM32Fxxx.h"

/************************************************************************************/
// 常量及全局变量定义
/************************************************************************************/
// 芯片产品唯一身份标识寄存器(96位)  
typedef struct
{
  INT8U ID1;
  INT8U ID2;
  INT8U ID3;
  INT8U ID4;
  INT8U ID5;
  INT8U ID6;

  INT8U ID7;
  INT8U ID8;
  INT8U ID9;
  INT8U ID10;
  INT8U ID11;
  INT8U ID12;
}MCU_ID_TypeDef;

void APP_ParaSave(USER_VARS *p)
{
	 p->Para.CRC16 = CRC16((INT8U *)&p->Para.Sync, CONFIG_PARA_LEN-2);  
	 EEPROM_Write(CONFIG_PARA_ADDR, (INT8U *)&p->Para.Sync, CONFIG_PARA_LEN);
} 

void APP_ParaInit(USER_VARS *p)
{
	INT8U i; 
    MCU_ID_TypeDef *pID;

    p->Para.Sync = SYNC_HEAD;
    
    p->Para.Flag = SPIFLASH_FORMAT_FLAG|NFLASH_FORMAT_FLAG|AT_DEBUG_FLAG;   	// 标志
	p->Para.ModbusID = 1; 	            	// Modbus ID
	
    #ifdef LWIP_EN
    p->Para.NetType = LWIP_NETYPE;
    p->Para.NetMode = LWIP_WKMODE;
    StrToIP(p->Para.LocalIP, (INT8U *)LOCAL_IP);
    StrToIP(p->Para.SubnetMask, (INT8U *)LOCAL_SUBNET_MASK);
    StrToIP(p->Para.Gataway, (INT8U *)LOCAL_GATEWAY);
    StrToIP(p->Para.DscIP, (INT8U *)DSC_IP);
    p->Para.LocalPort = LOCAL_PORT;      // 本机端口
    p->Para.DscPort = DSC_PORT;          // 服务器端口        
    #endif
    
    pID = (MCU_ID_TypeDef *)SysLib_Ctrl(CMD_SYSLIB_READ_MCUID, 0);
    
    p->Para.MACAddr[0] = 0;              //6 本机MAC地址
    p->Para.MACAddr[1] = 2;
    p->Para.MACAddr[2] = pID->ID3 + pID->ID9;
    p->Para.MACAddr[3] = pID->ID4 + pID->ID10;
    p->Para.MACAddr[4] = pID->ID5 + pID->ID11;
    p->Para.MACAddr[5] = pID->ID6 + pID->ID12;  
    
    
    p->Para.ATFlag = 0xffff;  // 使能所有调试信息输出
    
    p->Para.AI.Mode = 0;
    p->Para.AI.t1 = 100;
    p->Para.AI.t2 = 3000;

    p->Para.AO.Mode = 0;
    p->Para.AO.val = 1000;  // 默认每次增加1000mV(0-10量程)
    p->Para.AO.t = 3000;    // 默认输出间隔3秒

    p->Para.DI.Mode = 0;
    p->Para.DI.t1 = 100;
    p->Para.DI.t2 = 3000;

    p->Para.DO.Mode = 0;
    p->Para.DO.t1 = 100;
    p->Para.DO.t2 = 3000;
    
    #if (PWM1_EN > 0)
    p->Para.PWM[PWM1_ID].Mode = PWM1_MODE;
    p->Para.PWM[PWM1_ID].t1 = 100;
    p->Para.PWM[PWM1_ID].t2 = 3000;
    #endif
    #if (PWM2_EN > 0)
    p->Para.PWM[PWM2_ID].Mode = PWM2_MODE;
    p->Para.PWM[PWM2_ID].t1 = 100;
    p->Para.PWM[PWM2_ID].t2 = 3000;
    #endif
    #if (PWM3_EN > 0)
    p->Para.PWM[PWM3_ID].Mode = PWM3_MODE;
    p->Para.PWM[PWM3_ID].t1 = 100;
    p->Para.PWM[PWM3_ID].t2 = 3000;
    #endif
    #if (PWM4_EN > 0)
    p->Para.PWM[PWM4_ID].Mode = PWM4_MODE;
    p->Para.PWM[PWM4_ID].t1 = 100;
    p->Para.PWM[PWM4_ID].t2 = 3000;
    #endif
    #if (PWM5_EN > 0)
    p->Para.PWM[PWM5_ID].Mode = PWM5_MODE;
    p->Para.PWM[PWM5_ID].t1 = 100;
    p->Para.PWM[PWM5_ID].t2 = 3000;
    #endif
    #if (PWM6_EN > 0)
    p->Para.PWM[PWM6_ID].Mode = PWM6_MODE;
    p->Para.PWM[PWM6_ID].t1 = 100;
    p->Para.PWM[PWM6_ID].t2 = 3000;
    #endif
    #if (PWM7_EN > 0)
    p->Para.PWM[PWM7_ID].Mode = PWM7_MODE;
    p->Para.PWM[PWM7_ID].t1 = 100;
    p->Para.PWM[PWM7_ID].t2 = 3000;
    #endif


    #if (FCLK1_EN > 0)
    p->Para.FCLK[FCLK1_ID].Mode = FCLK1_MODE;
    p->Para.FCLK[FCLK1_ID].t1 = 100;
    p->Para.FCLK[FCLK1_ID].t2 = 3000;
    #endif

    #if (FCLK2_EN > 0)
    p->Para.FCLK[FCLK2_ID].Mode = FCLK2_MODE;
    p->Para.FCLK[FCLK2_ID].t1 = 100;
    p->Para.FCLK[FCLK2_ID].t2 = 3000;
    #endif

    #if (FCLK3_EN > 0)
    p->Para.FCLK[FCLK3_ID].Mode = FCLK3_MODE;
    p->Para.FCLK[FCLK3_ID].t1 = 100;
    p->Para.FCLK[FCLK3_ID].t2 = 3000;
    #endif

    #if (FCLK4_EN > 0)
    p->Para.FCLK[FCLK4_ID].Mode = FCLK4_MODE;
    p->Para.FCLK[FCLK4_ID].t1 = 100;
    p->Para.FCLK[FCLK4_ID].t2 = 3000;
    #endif
    
    #if (FCLK5_EN > 0)
    p->Para.FCLK[FCLK5_ID].Mode = FCLK5_MODE;
    p->Para.FCLK[FCLK5_ID].t1 = 100;
    p->Para.FCLK[FCLK5_ID].t2 = 3000;
    #endif

    #if (FCLK6_EN > 0)
    p->Para.FCLK[FCLK6_ID].Mode = FCLK6_MODE;
    p->Para.FCLK[FCLK6_ID].t1 = 100;
    p->Para.FCLK[FCLK6_ID].t2 = 3000;
    #endif

    #if (FCLK7_EN > 0)
    p->Para.FCLK[FCLK7_ID].Mode = FCLK7_MODE;
    p->Para.FCLK[FCLK7_ID].t1 = 100;
    p->Para.FCLK[FCLK7_ID].t2 = 3000;
    #endif
   
    APP_ParaSave(p);
}

INT32S APP_ParaRead(USER_VARS *Vars)
{
    INT16U crc;	   
	INT32S flag;
    
    flag = ERR_FALSE;
    
	EEPROM_Read(CONFIG_PARA_ADDR, (INT8U *)&Vars->Para.Sync, CONFIG_PARA_LEN);
    if (Vars->Para.Sync == SYNC_HEAD)
	{
		crc = CRC16((INT8U *)&Vars->Para.Sync, CONFIG_PARA_LEN-2);
		if (Vars->Para.CRC16 == crc)
		{	
			flag = ERR_TRUE;
    	}
	}
    if (flag != ERR_TRUE) 
    {
        APP_ParaInit(Vars);
        printf("AT+ERROR=APP_ParaRead, 读取配置参数失败,设置默认参数\r\n");
    }
    
    #if (LWIP_CONFIG_EN > 0)        // 按配置参数设置网络
    StrToIP(Vars->Para.LocalIP, (INT8U *)LOCAL_IP);
    StrToIP(Vars->Para.SubnetMask, (INT8U *)LOCAL_SUBNET_MASK);
    StrToIP(Vars->Para.Gataway, (INT8U *)LOCAL_GATEWAY);
    StrToIP(Vars->Para.DscIP, (INT8U *)DSC_IP);
    Vars->Para.LocalPort = LOCAL_PORT;      // 本机端口
    Vars->Para.DscPort = DSC_PORT;          // 服务器端口        
    #endif

    return flag;    
}

/***********************************************************************************
* Function: IO_APPInit;
*
* Description: 所有应用IO初始化函数;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   请根据板子型号初始化IO;
************************************************************************************/
void IO_APPInit(void)
{
    
// 按键K1-K8 IO初始化, 设置浮空输入(外部输入已经有上拉电阻)  
    #ifdef K1
    IO_Init(K1, IO_IN_FLOATING, IO_INPUT);  // 设置K1
    #endif
    #ifdef K2
    IO_Init(K2, IO_IN_FLOATING, IO_INPUT);  // 设置K2
	#endif
    #ifdef K3    
    IO_Init(K3, IO_IN_FLOATING, IO_INPUT);  // 设置K3
	#endif
    #ifdef K4
    IO_Init(K4, IO_IN_FLOATING, IO_INPUT);  // 设置K4
    #endif
    #ifdef K5
    IO_Init(K5, IO_IN_FLOATING, IO_INPUT);  // 设置K5
    #endif
    #ifdef K6
    IO_Init(K6, IO_IN_FLOATING, IO_INPUT);  // 设置K6
    #endif
    #ifdef K7
    IO_Init(K7, IO_IN_FLOATING, IO_INPUT);  // 设置K7
    #endif
    #ifdef K8
    IO_Init(K8, IO_IN_FLOATING, IO_INPUT);  // 设置K8
    #endif
    
// DI1-DI8初始化
    #ifdef DI1
    IO_Init(DI1, IO_IN_IPU, IO_INPUT);  // 输入DI1
	#endif
    #ifdef DI2
    IO_Init(DI2, IO_IN_IPU, IO_INPUT);  // 输入DI2
	#endif
    #ifdef DI3
    IO_Init(DI3, IO_IN_IPU, IO_INPUT);  // 输入DI3
	#endif
    #ifdef DI4
    IO_Init(DI4, IO_IN_IPU, IO_INPUT);  // 输入DI4
	#endif
    #ifdef DI5
    IO_Init(DI5, IO_IN_IPU, IO_INPUT);  // 输入DI5
    #endif
    #ifdef DI6
    IO_Init(DI6, IO_IN_IPU, IO_INPUT);  // 输入DI6
    #endif
    #ifdef DI7
    IO_Init(DI7, IO_IN_IPU, IO_INPUT);  // 输入DI6
    #endif
    #ifdef DI8
    IO_Init(DI8, IO_IN_IPU, IO_INPUT);  // 输入DI6
    #endif

// DI9-DI16初始化
    #ifdef DI9
    IO_Init(DI9, IO_IN_IPU, IO_INPUT);  // 输入DI9
	#endif
    #ifdef DI10
    IO_Init(DI10, IO_IN_IPU, IO_INPUT);  // 输入DI10
	#endif
    #ifdef DI11
    IO_Init(DI11, IO_IN_IPU, IO_INPUT);  // 输入DI11
	#endif
    #ifdef DI12
    IO_Init(DI12, IO_IN_IPU, IO_INPUT);  // 输入DI12
	#endif
    #ifdef DI13
    IO_Init(DI13, IO_IN_IPU, IO_INPUT);  // 输入DI13
    #endif
    #ifdef DI14
    IO_Init(DI14, IO_IN_IPU, IO_INPUT);  // 输入DI14
    #endif
    #ifdef DI15
    IO_Init(DI15, IO_IN_IPU, IO_INPUT);  // 输入DI15
    #endif
    #ifdef DI16
    IO_Init(DI16, IO_IN_IPU, IO_INPUT);  // 输入DI16
    #endif
    
// DO1-DO8初始化 
    #ifdef DO1
	#ifdef DO_OUT_PP
	IO_Init(DO1, IO_OUT_PP, IO_SPEED_2MHz);  // 输出DO1
	IO_Write(DO1, 0);
	#else
	IO_Init(DO1, IO_OUT_OD, IO_SPEED_2MHz);  // 输出DO1
	IO_Write(DO1, 1);
	#endif
	#endif
    
    #ifdef DO2
	#ifdef DO_OUT_PP
	IO_Init(DO2, IO_OUT_PP, IO_SPEED_2MHz);  // 输出DO2
	IO_Write(DO2, 0);
	#else
	IO_Init(DO2, IO_OUT_OD, IO_SPEED_2MHz);  // 输出DO2
	IO_Write(DO2, 1);
	#endif
	#endif
	
	#ifdef DO3
	#ifdef DO_OUT_PP
	IO_Init(DO3, IO_OUT_PP, IO_SPEED_2MHz);  // 输出DO3
	IO_Write(DO3, 0);
	#else
	IO_Init(DO3, IO_OUT_OD, IO_SPEED_2MHz);  // 输出DO3
	IO_Write(DO3, 1);
	#endif
	#endif
	
	#ifdef DO4
	#ifdef DO_OUT_PP
	IO_Init(DO4, IO_OUT_PP, IO_SPEED_2MHz);  // 输出DO4
	IO_Write(DO4, 0);
	#else
	IO_Init(DO4, IO_OUT_OD, IO_SPEED_2MHz);  // 输出DO4
	IO_Write(DO4, 1);
	#endif
	#endif
	
	#ifdef DO5
	#ifdef DO_OUT_PP
	IO_Init(DO5, IO_OUT_PP, IO_SPEED_2MHz);  // 输出DO5
	IO_Write(DO5, 0);
	#else
	IO_Init(DO5, IO_OUT_OD, IO_SPEED_2MHz);  // 输出DO5
	IO_Write(DO5, 1);
	#endif
	#endif
	
	#ifdef DO6
	#ifdef DO_OUT_PP
	IO_Init(DO6, IO_OUT_PP, IO_SPEED_2MHz);  // 输出DO6
	IO_Write(DO6, 0);
	#else
	IO_Init(DO6, IO_OUT_OD, IO_SPEED_2MHz);  // 输出DO6
	IO_Write(DO6, 1);
	#endif
	#endif
    
	#ifdef DO7
	#ifdef DO_OUT_PP
	IO_Init(DO7, IO_OUT_PP, IO_SPEED_2MHz);  // 输出DO7
	IO_Write(DO7, 0);
	#else
	IO_Init(DO7, IO_OUT_OD, IO_SPEED_2MHz);  // 输出DO7
	IO_Write(DO7, 1);
	#endif
	#endif
	
	#ifdef DO8
	#ifdef DO_OUT_PP
	IO_Init(DO8, IO_OUT_PP, IO_SPEED_2MHz);  // 输出DO8
	IO_Write(DO8, 0);
	#else
	IO_Init(DO8, IO_OUT_OD, IO_SPEED_2MHz);  // 输出DO8
	IO_Write(DO8, 1);
	#endif
	#endif
	
// DO9-DO16初始化 
  #ifdef DO9
	#ifdef DO_OUT_PP
	IO_Init(DO9, IO_OUT_PP, IO_SPEED_2MHz);  // 输出DO9
	IO_Write(DO9, 0);
	#else
	IO_Init(DO9, IO_OUT_OD, IO_SPEED_2MHz);  // 输出DO9
	IO_Write(DO9, 1);
	#endif
	#endif
    
    #ifdef DO10
	#ifdef DO_OUT_PP
	IO_Init(DO10, IO_OUT_PP, IO_SPEED_2MHz);  // 输出DO10
	IO_Write(DO10, 0);
	#else
	IO_Init(DO10, IO_OUT_OD, IO_SPEED_2MHz);  // 输出DO10
	IO_Write(DO10, 1);
	#endif
	#endif
	
	#ifdef DO11
	#ifdef DO_OUT_PP
	IO_Init(DO11, IO_OUT_PP, IO_SPEED_2MHz);  // 输出DO11
	IO_Write(DO11, 0);
	#else
	IO_Init(DO11, IO_OUT_OD, IO_SPEED_2MHz);  // 输出DO11
	IO_Write(DO11, 1);
	#endif
	#endif
	
	#ifdef DO12
	#ifdef DO_OUT_PP
	IO_Init(DO12, IO_OUT_PP, IO_SPEED_2MHz);  // 输出DO12
	IO_Write(DO12, 0);
	#else
	IO_Init(DO12, IO_OUT_OD, IO_SPEED_2MHz);  // 输出DO12
	IO_Write(DO12, 1);
	#endif
	#endif
	
	#ifdef DO13
	#ifdef DO_OUT_PP
	IO_Init(DO13, IO_OUT_PP, IO_SPEED_2MHz);  // 输出DO13
	IO_Write(DO13, 0);
	#else
	IO_Init(DO13, IO_OUT_OD, IO_SPEED_2MHz);  // 输出DO13
	IO_Write(DO13, 1);
	#endif
	#endif
	
	#ifdef DO14
	#ifdef DO_OUT_PP
	IO_Init(DO14, IO_OUT_PP, IO_SPEED_2MHz);  // 输出DO14
	IO_Write(DO14, 0);
	#else
	IO_Init(DO14, IO_OUT_OD, IO_SPEED_2MHz);  // 输出DO14
	IO_Write(DO14, 1);
	#endif
	#endif
    
	#ifdef DO15
	#ifdef DO_OUT_PP
	IO_Init(DO15, IO_OUT_PP, IO_SPEED_2MHz);  // 输出DO15
	IO_Write(DO15, 0);
	#else
	IO_Init(DO15, IO_OUT_OD, IO_SPEED_2MHz);  // 输出DO15
	IO_Write(DO15, 1);
	#endif
	#endif
	
	#ifdef DO16
	#ifdef DO_OUT_PP
	IO_Init(DO16, IO_OUT_PP, IO_SPEED_2MHz);  // 输出DO16
	IO_Write(DO16, 0);
	#else
	IO_Init(DO16, IO_OUT_OD, IO_SPEED_2MHz);  // 输出DO16
	IO_Write(DO16, 1);
	#endif
	#endif
    
	#ifdef DO17
	#ifdef DO_OUT_PP
	IO_Init(DO17, IO_OUT_PP, IO_SPEED_2MHz);  // 输出DO17
	IO_Write(DO17, 0);
	#else
	IO_Init(DO17, IO_OUT_OD, IO_SPEED_2MHz);  // 输出DO17
	IO_Write(DO17, 1);
	#endif
	#endif

	#ifdef DO18
	#ifdef DO_OUT_PP
	IO_Init(DO18, IO_OUT_PP, IO_SPEED_2MHz);  // 输出DO18
	IO_Write(DO18, 0);
	#else
	IO_Init(DO18, IO_OUT_OD, IO_SPEED_2MHz);  // 输出DO18
	IO_Write(DO18, 1);
	#endif
	#endif

	#ifdef DO19
	#ifdef DO_OUT_PP
	IO_Init(DO19, IO_OUT_PP, IO_SPEED_2MHz);  // 输出DO19
	IO_Write(DO19, 0);
	#else
	IO_Init(DO19, IO_OUT_OD, IO_SPEED_2MHz);  // 输出DO19
	IO_Write(DO19, 1);
	#endif
	#endif
    
	#ifdef DO20
	#ifdef DO_OUT_PP
	IO_Init(DO20, IO_OUT_PP, IO_SPEED_2MHz);  // 输出DO20
	IO_Write(DO20, 0);
	#else
	IO_Init(DO20, IO_OUT_OD, IO_SPEED_2MHz);  // 输出DO20
	IO_Write(DO20, 1);
	#endif
	#endif    
    
	#ifdef DO21
	#ifdef DO_OUT_PP
	IO_Init(DO21, IO_OUT_PP, IO_SPEED_2MHz);  // 输出DO21
	IO_Write(DO21, 0);
	#else
	IO_Init(DO21, IO_OUT_OD, IO_SPEED_2MHz);  // 输出DO21
	IO_Write(DO21, 1);
	#endif
	#endif       

 // 拨码开关SW1-SW8初始化
    #ifdef SW1
    IO_Init(SW1, IO_IN_IPU, IO_INPUT);  // 拨码开关SW1位
    #endif 
    #ifdef SW2
    IO_Init(SW2, IO_IN_IPU, IO_INPUT);  // 拨码开关SW2位
    #endif 
    #ifdef SW3
    IO_Init(SW3, IO_IN_IPU, IO_INPUT);  // 拨码开关SW3位
    #endif 
    #ifdef SW4
    IO_Init(SW4, IO_IN_IPU, IO_INPUT);  // 拨码开关SW4位
    #endif 
    #ifdef SW5
    IO_Init(SW5, IO_IN_IPU, IO_INPUT);  // 拨码开关SW5位
    #endif 
    #ifdef SW6
    IO_Init(SW6, IO_IN_IPU, IO_INPUT);  // 拨码开关SW6位
    #endif 
    #ifdef SW7
    IO_Init(SW7, IO_IN_IPU, IO_INPUT);  // 拨码开关SW7位
    #endif 
    #ifdef SW8
    IO_Init(SW8, IO_IN_IPU, IO_INPUT);  // 拨码开关SW8位
    #endif 
    
    // 蜂鸣器IO初始化
    #ifdef RUN_LED    
	IO_Init(ALARM, IO_OUT_PP, IO_SPEED_2MHz); // 通用推挽输出模式
	IO_Write(ALARM, 0);    
    #endif
    
    // 运行LED IO初始化  
    #ifdef RUN_LED
    IO_Init(RUN_LED, IO_OUT_PP, IO_SPEED_2MHz); // 通用推挽输出模式
	IO_Write(RUN_LED, 0);
    #endif
        
    // HC595_STB初始化
    #ifdef HC595_STB
    IO_Init(HC595_STB, IO_OUT_PP, IO_SPEED_2MHz);
    IO_Write(HC595_STB, 1);
    #endif
    
    // HC595_ENA初始化
    #ifdef HC595_ENA
    IO_Init(HC595_ENA, IO_OUT_OD, IO_SPEED_2MHz);    
    IO_Write(HC595_ENA, 1);                          // 输出使能禁止
    #endif
    
    // HC597_STB初始化
    #ifdef HC597_STB
    IO_Init(HC597_STB, IO_OUT_PP, IO_SPEED_2MHz); 
    IO_Write(HC597_STB, 1);
    #endif
    
    // HC597_LOAD初始化
    #ifdef HC597_LOAD
    IO_Init(HC597_LOAD, IO_OUT_PP, IO_SPEED_2MHz); 
    IO_Write(HC597_LOAD, 1);
    #endif
    
    // HC597_CS片选初始化
    #ifdef HC597_CS
    IO_Init(HC597_CS, IO_OUT_PP, IO_SPEED_2MHz); 
    IO_Write(HC597_CS, 0);
    #endif
    
	#ifdef PWM1_DIR
    IO_Init(PWM1_DIR, IO_OUT_PP, IO_SPEED_2MHz); 
    IO_Write(PWM1_DIR, 1);
    #endif
    #ifdef PWM1_ENA
    IO_Init(PWM1_ENA, IO_OUT_PP, IO_SPEED_2MHz); 
    IO_Write(PWM1_ENA, 1);
    #endif
    
	#ifdef PWM2_DIR
    IO_Init(PWM2_DIR, IO_OUT_PP, IO_SPEED_2MHz); 
    IO_Write(PWM2_DIR, 1);
    #endif
    #ifdef PWM2_ENA
    IO_Init(PWM2_ENA, IO_OUT_PP, IO_SPEED_2MHz); 
    IO_Write(PWM2_ENA, 1);
    #endif
	
    #ifdef PWM3_DIR
    IO_Init(PWM3_DIR, IO_OUT_PP, IO_SPEED_2MHz); 
    IO_Write(PWM3_DIR, 1);
    #endif
    #ifdef PWM3_ENA
    IO_Init(PWM3_ENA, IO_OUT_PP, IO_SPEED_2MHz); 
    IO_Write(PWM3_ENA, 1);
    #endif
	
    #ifdef PWM4_DIR
    IO_Init(PWM4_DIR, IO_OUT_PP, IO_SPEED_2MHz); 
    IO_Write(PWM4_DIR, 1);
    #endif
    #ifdef PWM4_ENA
    IO_Init(PWM4_ENA, IO_OUT_PP, IO_SPEED_2MHz); 
    IO_Write(PWM4_ENA, 1);
    #endif
    
	
	
    #if ((PRODUCT_TYPE == EMB8616I)||(PRODUCT_TYPE == EMB8626I)) // Modify 2019.5.22   
    #ifdef  JP18_P5
    IO_Init(JP18_P5, IO_OUT_PP, IO_SPEED_2MHz);    // JP18 5脚
    IO_Write(JP18_P5, 0);                          // 输出0 
    #endif
    
    #ifdef  JP18_P7
    IO_Init(JP18_P7, IO_OUT_PP, IO_SPEED_2MHz);    // JP18 7脚
    IO_Write(JP18_P7, 0);                          // 输出0 
    #endif
    
    #ifdef  JP18_P8
    IO_Init(JP18_P8, IO_OUT_PP, IO_SPEED_2MHz);    // JP18 8脚
    IO_Write(JP18_P8, 0);                          // 输出0 
    #endif    
    #endif
    
    #ifdef  JP9_P1
    IO_Init(JP9_P1, IO_OUT_PP, IO_SPEED_2MHz);    // JP9 1脚
    IO_Write(JP9_P1, 0);                          // 输出0 
    #endif
}
					 

/***********************************************************************************
* Function: NET_APPInit;
*
* Description: 网络应用初始化;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
#if ((LWIP_EN >0)&&(MODULE_CLASS != STM32F103XX))
void NET_APPInit(void)
{
    INT32S flag;

	NET_PARA Para;
	
    Para.Flag = 0;    
    Para.Pin.MCO = ETH_MCO;
    Para.Pin.MDC = ETH_MDC;
    Para.Pin.MDIO = ETH_MDIO;
    Para.Pin.REF = ETH_REF;
    Para.Pin.CRS_DV = ETH_CRS_DV;
    Para.Pin.RXD0 = ETH_RXD0;
    Para.Pin.RXD1 = ETH_RXD1;
    Para.Pin.TX_EN = ETH_TX_EN;
    Para.Pin.TXD0 = ETH_TXD0;
    Para.Pin.TXD1 = ETH_TXD1;
    Para.Pin.RESET = ETH_RESET;//IO_NONE;// 

    Para.DMARxDscrTab = DMARxDscrTab;
    Para.DMATxDscrTab = DMATxDscrTab;
    Para.RxBuffer = &ETH_RxBuffer[0][0];
    Para.TxBuffer = &ETH_TxBuffer[0][0];
    Para.RxBufNum = ETH_RXBUFNB;
    Para.TxBufNum = ETH_TXBUFNB;
    Para.MaxRxPacketSize = ETH_MAX_RX_PACKET_SIZE;
    Para.MaxTxPacketSize = ETH_MAX_TX_PACKET_SIZE;
    
    flag = NET_Init((NET_PARA *)&Para.Flag);
    if (flag == ERR_TRUE)
    {
        #if (DEBUG_APP_EN == 1)   
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            printf("AT+INFO=NET Init,OK\r\n");  
        }
        #endif 
    }
    else
    {
        #if (DEBUG_APP_EN == 1)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            printf("AT+ERROR=NET Init,ERROR,%d\r\n",flag);  
        }
        #endif
    }
}
#endif

/***********************************************************************************
* Function: EXTI_APPInit;
*
* Description: 外部中断和事件应用初始化函数;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   根据配置中EXTI1~EXTI19 输入中断配置初始化;
************************************************************************************/
void EXTI_APPInit(void)    
{
    EXTI_PARA Para;

    #if (EXTI0_EN > 0)
    Para.id   = EXTI0_ID;
    Para.Mode = EXTI0_MODE;
    Para.IOx  = EXTI0_IO;
    EXTI_Init((EXTI_PARA *)&Para);            // 初始化EXTI0
    //EXTI_Ctrl(EXTI0_ID, EXTI0_EN);            // 启动EXTI0中断或事件请求
    #endif
    
    #if (EXTI1_EN > 0)
    Para.id   = EXTI1_ID;
    Para.Mode = EXTI1_MODE;
    Para.IOx  = EXTI1_IO;
    EXTI_Init((EXTI_PARA *)&Para);            // 初始化EXTI1
    EXTI_Ctrl(EXTI1_ID, EXTI1_EN);            // 启动EXTI1中断或事件请求
    #endif
    
    #if (EXTI2_EN > 0)
    Para.id   = EXTI2_ID;
    Para.Mode = EXTI2_MODE;
    Para.IOx  = EXTI2_IO;
    EXTI_Init((EXTI_PARA *)&Para);            // 初始化EXTI2
    EXTI_Ctrl(EXTI2_ID, EXTI2_EN);            // 启动EXTI2中断或事件请求
    #endif
    
    #if (EXTI3_EN > 0)
    Para.id   = EXTI3_ID;
    Para.Mode = EXTI3_MODE;
    Para.IOx  = EXTI3_IO;
    EXTI_Init((EXTI_PARA *)&Para);            // 初始化EXTI3
    EXTI_Ctrl(EXTI3_ID, EXTI3_EN);            // 启动EXTI3中断或事件请求
    #endif
    
    #if (EXTI4_EN > 0)
    Para.id   = EXTI4_ID;
    Para.Mode = EXTI4_MODE;
    Para.IOx  = EXTI4_IO;
    EXTI_Init((EXTI_PARA *)&Para);            // 初始化EXTI4
    EXTI_Ctrl(EXTI4_ID, EXTI4_EN);            // 启动EXTI4中断或事件请求
    #endif
    
    #if (EXTI5_EN > 0)
    Para.id   = EXTI5_ID;
    Para.Mode = EXTI5_MODE;
    Para.IOx  = EXTI5_IO;
    EXTI_Init((EXTI_PARA *)&Para);            // 初始化EXTI5
    EXTI_Ctrl(EXTI5_ID, EXTI5_EN);            // 启动EXTI5中断或事件请求
    #endif
    
    #if (EXTI6_EN > 0)
    Para.id   = EXTI6_ID;
    Para.Mode = EXTI6_MODE;
    Para.IOx  = EXTI6_IO;
    EXTI_Init((EXTI_PARA *)&Para);            // 初始化EXTI6
    EXTI_Ctrl(EXTI6_ID, EXTI6_EN);            // 启动XTI6中断或事件请求
    #endif
    #if (EXTI7_EN > 0)
    Para.id   = EXTI7_ID;
    Para.Mode = EXTI7_MODE;
    Para.IOx  = EXTI7_IO;
    EXTI_Init((EXTI_PARA *)&Para);            // 初始化EXTI7
    EXTI_Ctrl(EXTI7_ID, EXTI7_EN);            // 启动EXTI7中断或事件请求
    #endif
    
    #if (EXTI8_EN > 0)
    Para.id   = EXTI8_ID;
    Para.Mode = EXTI8_MODE;
    Para.IOx  = EXTI8_IO;
    EXTI_Init((EXTI_PARA *)&Para);            // 初始化EXTI8
    EXTI_Ctrl(EXTI8_ID, EXTI8_EN);            // 启动EXTI8中断或事件请求
    #endif
    
    #if (EXTI9_EN > 0)
    Para.id   = EXTI9_ID;
    Para.Mode = EXTI9_MODE;
    Para.IOx  = EXTI9_IO;
    EXTI_Init((EXTI_PARA *)&Para);            // 初始化EXTI9
    EXTI_Ctrl(EXTI9_ID, EXTI9_EN);            // 启动EXTI9中断或事件请求
    #endif
    
    #if (EXTI10_EN > 0)
    Para.id   = EXTI10_ID;
    Para.Mode = EXTI10_MODE;
    Para.IOx  = EXTI10_IO;
    EXTI_Init((EXTI_PARA *)&Para);            // 初始化EXTI10
    EXTI_Ctrl(EXTI10_ID, EXTI10_EN);          // 启动EXTI10中断或事件请求
    #endif
    
    #if (EXTI11_EN > 0)
    Para.id   = EXTI11_ID;
    Para.Mode = EXTI11_MODE;
    Para.IOx  = EXTI11_IO;
    EXTI_Init((EXTI_PARA *)&Para);            // 初始化EXTI11
    EXTI_Ctrl(EXTI11_ID, EXTI11_EN);          // 启动EXTI11中断或事件请求
    #endif
    
    #if (EXTI12_EN > 0)
    Para.id   = EXTI12_ID;
    Para.Mode = EXTI12_MODE;
    Para.IOx  = EXTI12_IO;
    EXTI_Init((EXTI_PARA *)&Para);            // 初始化EXTI12
    EXTI_Ctrl(EXTI12_ID, EXTI12_EN);          // 启动EXTI12中断或事件请求
    #endif
    
    #if (EXTI13_EN > 0)
    Para.id   = EXTI13_ID;
    Para.Mode = EXTI13_MODE;
    Para.IOx  = EXTI13_IO;
    EXTI_Init((EXTI_PARA *)&Para);            // 初始化EXTI13
    EXTI_Ctrl(EXTI13_ID, EXTI13_EN);          // 启动EXTI13中断或事件请求
    #endif
    
    #if (EXTI14_EN > 0)
    Para.id   = EXTI14_ID;
    Para.Mode = EXTI14_MODE;
    Para.IOx  = EXTI14_IO;
    EXTI_Init((EXTI_PARA *)&Para);            // 初始化EXTI14
    EXTI_Ctrl(EXTI14_ID, EXTI14_EN);          // 启动EXTI14中断或事件请求
    #endif
    
    #if (EXTI15_EN > 0)
    Para.id   = EXTI15_ID;
    Para.Mode = EXTI15_MODE;
    Para.IOx  = EXTI15_IO;
    EXTI_Init((EXTI_PARA *)&Para);            // 初始化EXTI15
    EXTI_Ctrl(EXTI15_ID, EXTI15_EN);          // 启动EXTI15中断或事件请求
    #endif    

    #if (EXTI16_PVD_EN > 0)
    Para.id   = EXTI16_PVD_ID;
    Para.Mode = EXTI16_PVD_MODE;
    Para.IOx  = IO_NONE;
    EXTI_Init((EXTI_PARA *)&Para);            // 初始化EXTI16_PVD
    EXTI_Ctrl(EXTI16_PVD_ID, EXTI16_PVD_EN);  // 启动EXTI16_PVD中断或事件请求
    #endif    
    
    #if (EXTI17_RTCAlarm_EN > 0)
    Para.id   = EXTI17_RTCAlarm_ID;
    Para.Mode = EXTI17_RTCAlarm_MODE;
    Para.IOx  = IO_NONE;
    EXTI_Init((EXTI_PARA *)&Para);                      // 初始化EXTI17_RTCAlarm
    EXTI_Ctrl(EXTI17_RTCAlarm_ID, EXTI17_RTCAlarm_EN);  // 启动EXTI17_RTCAlarm中断或事件请求
    #endif    

    #if (EXTI18_USBWakeUp_EN > 0)
    Para.id   = EXTI18_USBWakeUp_ID;
    Para.Mode = EXTI18_USBWakeUp_MODE;
    Para.IOx  = IO_NONE;
    EXTI_Init((EXTI_PARA *)&Para);                        // 初始化EXTI18_USBWakeUp
    EXTI_Ctrl(EXTI18_USBWakeUp_ID, EXTI18_USBWakeUp_EN);  // 启动EXTI18_USBWakeUp中断或事件请求
    #endif  
    
    #if (EXTI19_NETWakeUp_EN > 0)
    Para.id   = EXTI19_NETWakeUp_ID;
    Para.Mode = EXTI19_NETWakeUp_MODE;
    Para.IOx  = IO_NONE;
    EXTI_Init((EXTI_PARA *)&Para);                        // 初始化EXTI19_NETWakeUp
    EXTI_Ctrl(EXTI19_NETWakeUp_ID, EXTI19_NETWakeUp_EN);  // 启动EXTI19_NETWakeUp中断或事件请求
    #endif      
    
    #if (MODULE_CLASS == STM32F407XX)    
    
    #if (EXTI20_USBHSWakeUp_EN > 0)
    Para.id   = EXTI20_USBHSWakeUp_ID;
    Para.Mode = EXTI20_USBHSWakeUp_MODE;
    Para.IOx  = IO_NONE;
    EXTI_Init((EXTI_PARA *)&Para);                            // 初始化EXTI20_USBHSWakeUp
    EXTI_Ctrl(EXTI20_USBHSWakeUp_ID, EXTI20_USBHSWakeUp_EN);  // 启动EXTI20_USBHSWakeUp中断或事件请求
    #endif      
    
    #if (EXTI21_RTCTSE_EN > 0)
    Para.id   = EXTI21_RTCTSE_ID;
    Para.Mode = EXTI21_RTCTSE_MODE;
    Para.IOx  = IO_NONE;
    EXTI_Init((EXTI_PARA *)&Para);                        // 初始化EXTI21_RTCTSE
    EXTI_Ctrl(EXTI21_RTCTSE_ID, EXTI21_RTCTSE_EN);        // 启动EXTI21_RTCTSE中断或事件请求
    #endif  

    #if (EXTI22_RTCWakeUp_EN > 0)
    Para.id   = EXTI22_RTCWakeUp_ID;
    Para.Mode = EXTI22_RTCWakeUp_MODE;
    Para.IOx  = IO_NONE;
    EXTI_Init((EXTI_PARA *)&Para);                        // 初始化EXTI22_RTCWakeUp
    EXTI_Ctrl(EXTI22_RTCWakeUp_ID, EXTI22_RTCWakeUp_EN);  // 启动EXTI22_RTCWakeUp中断或事件请求
    #endif 
    
    #endif
        
    #if (DEBUG_APP_EN == 1)   
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        printf("AT+INFO=EXTI Init,OK\r\n");  
    }
    #endif         
}

/***********************************************************************************
* Function: SPI_APPInit;
*
* Description: SPI1/SPI2/SPI3初始化函数;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
#if ((I2C2_EN > 0)||(I2C3_EN > 0)) // I2C2-I2C3配置使能
void I2C_APPInit(void)
{
    I2C_PARA  I2C_Para;
    INT32S flag;
    
    #if (I2C2_EN > 0)
    // I2C configuration 
    #if (MODULE_CLASS != STM32F407XX)
    I2C_Para.PinRemap = I2C_REMAP_1;
    #endif
    
    I2C_Para.SCLPin = I2C2_SCL;
    I2C_Para.SDAPin = I2C2_SDA;
    
    I2C_Para.Mode = I2C_Mode_I2C;
    I2C_Para.DutyCycle = I2C_DutyCycle_2;
    I2C_Para.OwnAddress1 = 0;//0xA0;
    I2C_Para.Ack = I2C_Ack_Enable;
    I2C_Para.AcknowledgedAddress = I2C_AcknowledgedAddress_10bit;
    I2C_Para.ClockSpeed = 100000;
    flag = I2C_Init(I2C2_ID, (I2C_PARA *)&I2C_Para);
    if (flag == ERR_TRUE)
    {   
        I2C_Ctrl(I2C2_ID, CMD_I2C, 1);      
        #if (DEBUG_APP_EN == 1)   
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            printf("AT+INFO=I2C2 Init, OK\r\n");  
        }
        #endif  
    }
    else
    {
        #if (DEBUG_APP_EN == 1)   
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            printf("AT+ERROR=I2C2 Init, ERROR\r\n");  
        }
        #endif  
    }        
    #endif

    #if (I2C3_EN > 0)
    // I2C configuration 
    #if (MODULE_CLASS != STM32F407XX)
    I2C_Para.PinRemap = I2C_REMAP_1;
    #endif    
    I2C_Para.SCLPin = I2C3_SCL;
    I2C_Para.SDAPin = I2C3_SDA;
    
    I2C_Para.Mode = I2C_Mode_I2C;
    I2C_Para.DutyCycle = I2C_DutyCycle_2;
    I2C_Para.OwnAddress1 = 0;//0xA0;
    I2C_Para.Ack = I2C_Ack_Enable;
    I2C_Para.AcknowledgedAddress = I2C_AcknowledgedAddress_10bit;
    I2C_Para.ClockSpeed = 100000;
    flag = I2C_Init(I2C3_ID, (I2C_PARA *)&I2C_Para);
    if (flag == ERR_TRUE)
    {   
        I2C_Ctrl(I2C3_ID, CMD_I2C, 1);
        #if (DEBUG_APP_EN == 1)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            printf("AT+INFO=I2C3 Init, OK\r\n");  
        }
        #endif  
    }
    else
    {
        #if (DEBUG_APP_EN == 1)   
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            printf("AT+ERROR=I2C3 Init, ERROR\r\n");  
        }
        #endif  
    }    
    #endif
}
#endif
/***********************************************************************************
* Function: SPI_APPInit;
*
* Description: SPI1/SPI2/SPI3初始化函数;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
#if ((SPI1_EN > 0)||(SPI2_EN > 0)||(SPI3_EN > 0))
void SPI_APPInit(void)
{
    SPI_PARA Para;
    INT32S flag;
    
    #if (SPI1_EN > 0)
    Para.Flag = 0;                       // 参数标志
    
    #if (SPI1TX_DMA_EN > 0)
    Para.Flag |= SPI_TXDMA_FLAG;  // 设置SPI1TX DMA使能标志
    Para.TXDmaCh = SPI1TX_DMA_CH;
    Para.DmaID = SPI1_DMA_ID;
    #endif
    #if (SPI1RX_DMA_EN > 0)
    Para.Flag |= SPI_RXDMA_FLAG;  // 设置SPI1RX DMA使能标志
    Para.RXDmaCh = SPI1RX_DMA_CH;
    Para.DmaID = SPI1_DMA_ID;
    #endif
    
    #if (SPI1_ISRHOOK_EN > 0)
    Para.Flag |= SPI1_ISRHOOK_FLAG;  // 设置SPI1 ISRHOOK使能标志
    Para.pISRHook = SPI1_ISRHook;
    #else
    Para.pISRHook = 0;
    #endif
    
    //设置SPI管脚
    #if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F107XX))
	Para.Pin.Remap = SPI1_REMAP;         // SPI引脚功能重映射
    #endif
    Para.Pin.NSS = SPI1_NSS;             // SPI1_NSS管脚
    Para.Pin.SCK = SPI1_SCK;             // SPI1_SCK管脚
    Para.Pin.MISO = SPI1_MISO;           // SPI1_MOSI管脚
    Para.Pin.MOSI = SPI1_MOSI;           // SPI1_MISO管脚

    // 参数配置
    // 以下按位设置
    /*
    Para.cfg.b.CPHA = 1;//SPI_CPHA_2Edge;   // 时钟相位:  SPI_CPHA_1Edge或SPI_CPHA_2Edge
    Para.cfg.b.CPOL = 1;//SPI_CPOL_High;    // 时钟极性:  SPI_CPOL_Low或SPI_CPOL_High
    Para.cfg.b.Mode = 1;//SPI_Mode_Master;  // 主机和设备模式选择: SPI_Mode_Master 或 SPI_Mode_Slave
    Para.cfg.b.BaudRatePrescaler = 6;//SPI_BaudRatePrescaler_8; // 分频系数: SPI_BaudRatePrescaler_2~SPI_BaudRatePrescaler_256
    Para.cfg.b.spe = 0;                 // SPI使能, 初始化默认为0, 关闭 
    Para.cfg.b.Direction = SPI_FirstBit_MSB; // 先发送高位和低位选择: SPI_FirstBit_MSB 或 SPI_FirstBit_LSB
    Para.cfg.b.SSI = 0;                 // 内部从设备选择, 默认为0;
    Para.cfg.b.SSM = 0;                 // 软件从设备选择, 默认为0;
    Para.cfg.b.RxOnly = SPI_2Lines_FullDuplex;  // 只接收设置, 默认为0(全双工)：SPI_2Lines_FullDuplex 或 SPI_2Lines_RxOnly
    Para.cfg.b.DataSize = SPI_DataSize_8b;      // 数据位数选择：SPI_DataSize_16b 或 SPI_DataSize_8b
    Para.cfg.b.CRCNext = 0;                     // 下一个发送CRC, 默认为0
    Para.cfg.b.CRCEN =0;                        // CRC校验使能, 默认为0
    Para.cfg.b.BIDIOE = 0;                      // 双向模式下输出使能, 默认为0: 0: 输出禁止(只收模式), 1:输出使能(只发模式)
    Para.cfg.b.BIDIMODE =0;                     // 双向数据模式使能, 默认0: 0: 选择双线模式, 1:选择单线模式
    */
    // 也可以这样设置
    Para.cfg.reg = SPI1_CKMODE|SPI_Mode_Master|SPI1_DIVCLK|SPI_FirstBit_MSB|SPI_DataSize_8b|SPI_NSS_Soft;
    
    Para.CRCPolynomial = 7;       // Specifies the polynomial used for the CRC calculation.
    flag = SPI_Init(SPI1_ID, (SPI_PARA *)&Para.Flag);     // SPI1初始化
    if (flag == ERR_TRUE)
    {
        #if (DEBUG_APP_EN == 1)   
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            printf("AT+INFO=SPI1 Init, OK\r\n");  
        }
        #endif 
    }
    else
    {
        #if (DEBUG_APP_EN == 1)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            printf("AT+ERROR=SPI1 Init, ERROR\r\n");  
        }
        #endif
    }  
    #endif
    
    
    #if (SPI2_EN > 0)
    Para.Flag = 0;                   // 参数标志
    
    #if (SPI2TX_DMA_EN > 0)
    Para.Flag |= SPI_TXDMA_FLAG;  // 设置SPI2TX DMA使能标志
    Para.TXDmaCh = SPI2TX_DMA_CH;
    Para.DmaID = SPI2_DMA_ID;    
    #endif
    #if (SPI2RX_DMA_EN > 0)
    Para.Flag |= SPI_RXDMA_FLAG;  // 设置SPI2RX DMA使能标志
    Para.RXDmaCh = SPI2RX_DMA_CH;
    Para.DmaID = SPI2_DMA_ID;
    #endif
    #if (SPI2_ISRHOOK_EN > 0)
    Para.Flag |= SPI_ISRHOOK_FLAG;  // 设置SPI2 ISRHOOK使能标志
    Para.pISRHook = SPI2_ISRHook;
    #else
    Para.pISRHook = 0;
    #endif
    
    //设置SPI管脚
    #if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F107XX))
	Para.Pin.Remap = SPI2_REMAP;     // SPI2引脚功能无重映射
    #endif
    Para.Pin.NSS = SPI2_NSS;         // SPI2_NSS管脚
    Para.Pin.SCK = SPI2_SCK;         // SPI2_SCK管脚
    Para.Pin.MISO = SPI2_MISO;       // SPI2_MOSI管脚
    Para.Pin.MOSI = SPI2_MOSI;       // SPI2_MISO管脚
    // 参数配置
    Para.cfg.reg =SPI2_CKMODE|SPI_Mode_Master|SPI2_DIVCLK|SPI_FirstBit_MSB|SPI_DataSize_8b;
    
    Para.CRCPolynomial = 7;       // Specifies the polynomial used for the CRC calculation.
    
    flag = SPI_Init(SPI2_ID, (SPI_PARA *)&Para.Flag);     // SPI2初始化
    
    if (flag == ERR_TRUE)
    {
        #if (DEBUG_APP_EN == 1)   
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            printf("AT+INFO=SPI2 Init, OK\r\n");   
        }
        #endif 
    }
    else
    {
        #if (DEBUG_APP_EN == 1)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            printf("AT+ERROR=SPI2 Init, ERROR\r\n"); 
        }
        #endif
    }  
    #endif
    
    #if (SPI3_EN > 0)
    Para.Flag = 0;                    // 参数标志

    #if (SPI3TX_DMA_EN > 0)
    Para.Flag |= SPI_TXDMA_FLAG;  // 设置SPI3TX DMA使能标志
    Para.TXDmaCh = SPI3TX_DMA_CH;
    Para.DmaID = SPI3_DMA_ID;
    #endif
    #if (SPI3RX_DMA_EN > 0)
    Para.Flag |= SPI_RXDMA_FLAG;  // 设置SPI3RX DMA使能标志
    Para.RXDmaCh = SPI3RX_DMA_CH;
    Para.DmaID = SPI3_DMA_ID;
    #endif
    #if (SPI3_ISRHOOK_EN > 0)
    Para.Flag |= SPI_ISRHOOK_FLAG;  // 设置SPI3 ISRHOOK使能标志
    Para.pISRHook = SPI3_ISRHook;
    #else
    Para.pISRHook = 0;
    #endif
    
    //设置SPI管脚
    #if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F107XX))
	Para.Pin.Remap = SPI3_REMAP;     // SPI3引脚功能重映射
    #endif
    Para.Pin.NSS = SPI3_NSS;         // SPI3_NSS管脚
    Para.Pin.SCK = SPI3_SCK;         // SPI3_SCK管脚
    Para.Pin.MISO = SPI3_MISO;       // SPI3_MOSI管脚
    Para.Pin.MOSI = SPI3_MOSI;       // SPI3_MISO管脚
    // 参数配置
    Para.cfg.reg = SPI3_CKMODE|SPI_Mode_Master|SPI3_DIVCLK|SPI_FirstBit_MSB|SPI_DataSize_8b;
    
    Para.CRCPolynomial = 7;       // Specifies the polynomial used for the CRC calculation.
    
    flag = SPI_Init(SPI3_ID, (SPI_PARA *)&Para.Flag);     // SPI2初始化
    
    if (flag == ERR_TRUE)
    {
        #if (DEBUG_APP_EN == 1)   
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            printf("AT+INFO=SPI3 Init, OK\r\n");   
        }
        #endif 
    }
    else
    {
        #if (DEBUG_APP_EN == 1)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            printf("AT+ERROR=SPI3 Init, ERROR\r\n"); 
        }
        #endif
    }  
    #endif
}
#endif

/***********************************************************************************
* Function: EEPROM_APPInit;
*
* Description: EEPROM应用初始化函数;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
void  EEPROM_APPInit(void)  // EEPROM应用初始化函数;
{    
	EEPROM_PARA EEPromPara;
    INT32S flag;
    
    EEPromPara.SDAPin = I2C1_SDA;            // I2C SDA管脚 
    EEPromPara.SCLPin = I2C1_SCL;            // I2C SCL管脚 
    
    EEPromPara.I2C_ID = I2C1_ID;              // 选择I2C接口索引: I2C1_ID 或者I2C2_ID 
    EEPromPara.I2CAddr = IIC_EEPROM_ADDR;     // 器件地址标识
    EEPromPara.Freq = EEPROM_FREQ;            // 设置EEPROM读写频率(即I2C读写频率)
    EEPromPara.Model = EEPROM_DEVICE;         // 设置器件型号
    
	flag = EEPROM_Init((EEPROM_PARA *)&EEPromPara.Flag); // 初始化EEPROM, 里面包含初始化I2C1
//    if (flag == ERR_TRUE)
//    {
//        #if (DEBUG_APP_EN == 1)   
//        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
//        {
//            printf("AT+INFO=EEPROM Init, OK\r\n");  
//        }
//        #endif 
//    }
//    else
//    {
//        #if (DEBUG_APP_EN == 1)
//        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
//        {
//            printf("AT+ERROR=EEPROM Init, ERROR\r\n");  
//        }
//        #endif
//    } 
}

/***********************************************************************************
* Function: RTC_APPInit;
*
* Description: RTC应用初始化函数;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
#if (RTC_EN > 0)

#define  ENABLE  1
#define  DISABLE 0
#define RTC_PWROFF_FLAG  0x5AA5   // RTC断电标志
#define RTC_BKP_ID       42       // RTC断电标志存储在BKP的位置, 范围：1-42
void RTC_APPInit(void)
{
    INT16U RTCFlag;
    RTC_TIME rtc;
    INT32S flag;
    RTC_PARA Para;
    
    Para.Flag = 0;
    
    Para.Flag |= RTC_CLK_LSE_FLAG; 	          // 设置外部低速时钟晶振
    //Para.Flag |= RTC_CLK_LSI_FLAG;          // 设置内部低速时钟晶振
    //Para.Flag |= RTC_CLK_HSEDIV_FLAG;
    //Para.Flag |= RTC_CLK_LSEBYP_FLAG;       // RTC时钟选择LSE有源时钟标志,最高1MHZ, 内部必须旁路LSE振荡器
    
//    #if (MODULE_CLASS == STM32F407XX)
//        //Para.Flag |= RTC_CR_COE_EN|RTC_CR_COSEL_1HZ;     // 设置PC13输出秒脉冲, 但只有LSE是32768HZ才有效
//        #if (RTC_ALR_EN > 0)            // RTC唤醒使能
//        Para.Flag |= RTC_CR_WUTE_EN;    // 使能唤醒定时器 
//        Para.Flag |= RTC_CR_WUTIE_EN;   // 使能中断  
//        #endif
//        
//        #if ( RTC_ALRA_EN > 0)          // RTC闹钟A使能
//        Para.Flag |= RTC_CR_ALRAE_EN;   // 使能闹钟A 
//        Para.Flag |= RTC_CR_OSEL_A;     // 输出使能选择：闹钟A 
//        Para.Flag |= RTC_CR_ALRAIE_EN;  // 使能中断 
//        #endif
//        
//        #if ( RTC_ALRB_EN > 0)          // RTC闹钟B使能
//        Para.Flag |= RTC_CR_ALRBE_EN;   // 使能闹钟B
//        Para.Flag |= RTC_CR_OSEL_B;     // 输出使能选择：闹钟B 
//        Para.Flag |= RTC_CR_ALRBIE_EN;  // 使能中断 
//        #endif
//        
//        #if (RTC_TSF_EN  > 0)           // RTC时间戳使能        
//        Para.Flag |= RTC_CR_TSE_EN;     // 使能时间戳  
//        Para.Flag |= RTC_CR_TSIE_EN;    // 使能中断 
//        #endif
//        
//    #endif
    
    if (Para.Flag&RTC_CLK_LSEBYP_FLAG)
    {
        #if (MODULE_CLASS == STM32F407XX)
        Para.LSEVal = 1024000;
        #endif
        #if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F107XX))
        Para.LSEVal = 32768;
        #endif
    }
    
    flag = RTC_Init((RTC_PARA *)&Para.Flag);     // RTC初始化
    if (flag == ERR_TRUE)
    {
        #if (DEBUG_APP_EN == 1)   
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            printf("AT+INFO=RTC Init, OK\r\n");  
        }
        #endif 
    }
    else
    {
        #if (DEBUG_APP_EN == 1)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            printf("AT+ERROR=RTC Init, ERROR\r\n");  
        }
        #endif
    } 


    // 初始化时间
    rtc.year = 17;
    rtc.month = 12;
    rtc.day  = 31;
    rtc.hour = 23;
    rtc.minute = 59;
    rtc.second = 30;
    rtc.ss = 0;
//    flag = RTC_Write(&rtc);
//    if (flag!=ERR_TRUE)
//    {
//       printf("RTC Write Error!\r\n");  
//    }        
    #if (BKP_EN > 0)    
    BKP_Read(RTC_BKP_ID, &RTCFlag, 1);        // 读取RTC时钟标志
	if (RTCFlag != RTC_PWROFF_FLAG)           // 判断是否断电，如果断电重新初始化时间
	{
        RTC_Write(&rtc);  // 设置新的时间
        RTCFlag = RTC_PWROFF_FLAG;            // 设置时钟已经校时标志
		BKP_Write(RTC_BKP_ID, &RTCFlag, 1);   // 设置初始化时间标志
	}
    #else
    RTC_Write(&rtc);  // 设置新的时间
    #endif
    
#if (MODULE_CLASS == STM32F407XX)  
        #if (RTC_ALRA_EN > 0) // RTC闹钟A使能, 间隔1秒
        //rtc.year = 17;
        //rtc.month = 12;
        //rtc.day  = 31;
        //rtc.hour = 23;
        //rtc.minute = 59;
        rtc.second = 0;    
        //flag = RTC_ALARM_IT_FLAG|RTC_ALARM_SS_FLAG|RTC_ALARM_MINUTE_FLAG|RTC_ALARM_HOUR_FLAG|RTC_ALARM_DAY_FLAG;
        flag = RTC_ALARM_IT_FLAG|RTC_ALARM_SECOND_FLAG|RTC_ALARM_MINUTE_FLAG|RTC_ALARM_HOUR_FLAG|RTC_ALARM_DAY_FLAG|RTC_ALARM_OTYPE_FLAG;
        rtc.ss = 100;
    
        RTC_Ctrl(CMD_RTC_SET_ALRMA_RTC, flag, &rtc);
        #endif
#endif    

#if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F107XX))
    #if (RTC_SECIT_EN > 0)  // RTC秒中断
    RTC_Ctrl(CMD_RTC_SECOND_INT, ENABLE, 0);
    #endif
    #if (RTC_ALRIT_EN > 0)  // RTC闹钟中断
    RTC_Ctrl(CMD_RTC_ALARM_INT, ENABLE, 0);
    RTC_Ctrl(CMD_RTC_SET_ALMTIM_XS, 5, 0);   // 设置闹钟时间, 5秒后产生闹钟中断
    #if (DEBUG_APP_EN == 1)
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        printf("AT+INFO=RTC设置闹钟时间, 5秒后产生闹钟中断\r\n");
    }
    #endif
    #endif    
#endif    
    
    
}
#endif
/***********************************************************************************
* Function: Uart_APPInit;
*
* Description: UART1-UART5应用初始化函数;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
void Uart_APPInit(void)
{
    UART_PARA  UartPara;
    INT32S flag;
    
//---UART1初始化-------------------------------------------------------
#if (UART1_EN > 0)   
    UartPara.Flag = 0;                      // 设置为0
    #if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F107XX))
        #if (UART1_REMAP == UART_REMAP_1)       // 设置管脚重映射
        UartPara.Flag |= UART_REMAP1_FLAG;
        #endif
    #endif
    UartPara.TXPin = UART1_TX;              // 设置TX管脚
    UartPara.RXPin = UART1_RX;              // 设置RX管脚
    UartPara.RS485DirPin = UART1_DIR;       // 设置RS485方向控制IO
    #if (UART1_DIR != IO_NONE)              // 没有转RS485接口
    UartPara.Flag |= UART_RS485EN_FLAG;   // 设置RS485接口标志
    #if (UART1_DIR_HL == 1)                 // 为1设置高电平接收, 默认低电平接收
    UartPara.Flag |= UART_RS485DIR_FLAG;  // DIR高电平接收
    #endif
    #endif    
    
    #if (UART1_WORD_LENGTH == UART_WORD_LENGTH_9B) // 设置数据位数  
    UartPara.Flag |= UART_WORD_LENGTH_9BIT_FLAG;
    #endif
    #if (UART1_PARITY == UART_PARITY_EVEN)      // 设置偶检验
    UartPara.Flag |= UART_PARITY_EVEN_FLAG;
    #elif (UART1_PARITY == UART_PARITY_ODD)     // 设置奇检验
    UartPara.Flag |= UART_PARITY_ODD_FLAG;
    #endif    
    #if (UART1_STOP_BITS == UART_STOP_BITS_2)   // 设置2位停止位
    UartPara.Flag |= UART_STOP_BITS2_FLAG;
    #elif (UART1_PARITY == UART_STOP_BITS_0_5)  // 设置0.5位停止位
    UartPara.Flag |= UART_STOP_BITS0_5_FLAG;
    #elif (UART1_PARITY == UART_STOP_BITS_2)    // 设置1.5位停止位
    UartPara.Flag |= UART_STOP_BITS1_5_FLAG;
    #endif
    
    // 在设置了奇偶检验位并且数据位设置8bit, 实际有效数据位是7bit请初始化时设置该标志
    #if ((UART1_PARITY > 0)&&(UART1_WORD_LENGTH == UART_WORD_LENGTH_8B))  
    UartPara.Flag |= UART_DATA_7BIT_FLAG;
    #endif   
    
    // 发送和接收DMA设置
    #if (UART1TX_DMA_EN > 0)
    UartPara.Flag |= UART_DMAREQ_TX_FLAG;   // 设置发送DMA
    #endif
    #if (UART1RX_DMAEN > 0)
    UartPara.Flag |= UART_DMAREQ_RX_FLAG;   // 设置接收DMA
    #endif
    
    //UartPara.Flag |= UART_HWFC_RTS_FLAG|UART_HWFC_CTS_FLAG; // 流控及DMA设置
    //UartPara.Flag |= UART_ISRHOOK_FLAG;   // 设置调用串口接收钩子函数, 串口接收数据由用户在Uart1_ISRHook()函数中自己编程实现    
    
    UartPara.Mode = UART_AsynFD;             // 设置模式: 全双工的，异步通信
    UartPara.BaudRate = UART1_BAUD;          // 设置波特率
    
    UartPara.TxBufLen = UART1_TXBUF_SIZE;   // 设置发送缓存长度
    UartPara.RxBufLen = UART1_RXBUF_SIZE;   // 设置接收缓存长度
    UartPara.pTxBuf = Uart1_TxBuffer;       // 设置发送缓存指针
    UartPara.pRxBuf = Uart1_RxBuffer;       // 设置接收缓存指针    
    
    flag = Uart_Init(UART1_ID, (UART_PARA *)&UartPara.Flag); // 初始化UART1
    #if (DEBUG_APP_EN == 1)
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {
            printf("AT+INFO=UART1 Init, OK\r\n");  
        }
        else
        {
            printf("AT+ERROR=UART1 Init,ERROR,%d\r\n", flag);  
        }
    }
    #endif
#endif

//---UART2初始化-------------------------------------------------------
#if (UART2_EN > 0) 
    UartPara.Flag = 0;                    // 设置为0
    #if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F107XX))
		#if (UART2_REMAP == UART_REMAP_1)     // 设置管脚重映射
        UartPara.Flag |= UART_REMAP1_FLAG;
        #endif
    #endif
    UartPara.TXPin = UART2_TX;              // 设置TX管脚
    UartPara.RXPin = UART2_RX;              // 设置RX管脚
    UartPara.RS485DirPin = UART2_DIR;       // 设置RS485方向控制IO
    #if (UART2_DIR != IO_NONE)              // 没有转RS485接口
    UartPara.Flag |= UART_RS485EN_FLAG;   // 设置RS485接口标志
    #if (UART2_DIR_HL == 1)                 // 为1设置高电平接收, 默认低电平接收
    UartPara.Flag |= UART_RS485DIR_FLAG;  // DIR高电平接收
    #endif
    #endif
    #if (UART2_WORD_LENGTH == UART_WORD_LENGTH_9B) // 设置数据位数  
    UartPara.Flag |= UART_WORD_LENGTH_9BIT_FLAG;
    #endif
    #if (UART2_PARITY == UART_PARITY_EVEN)      // 设置偶检验
    UartPara.Flag |= UART_PARITY_EVEN_FLAG;
    #elif (UART2_PARITY == UART_PARITY_ODD)     // 设置奇检验
    UartPara.Flag |= UART_PARITY_ODD_FLAG;
    #endif    
    #if (UART2_STOP_BITS == UART_STOP_BITS_2)   // 设置2位停止位
    UartPara.Flag |= UART_STOP_BITS2_FLAG;
    #elif (UART2_PARITY == UART_STOP_BITS_0_5)  // 设置0.5位停止位
    UartPara.Flag |= UART_STOP_BITS0_5_FLAG;
    #elif (UART2_PARITY == UART_STOP_BITS_2)    // 设置1.5位停止位
    UartPara.Flag |= UART_STOP_BITS1_5_FLAG;
    #endif    
    
    // 在设置了奇偶检验位并且数据位设置8bit, 实际有效数据位是7bit请初始化时设置该标志
    #if ((UART2_PARITY > 0)&&(UART2_WORD_LENGTH == UART_WORD_LENGTH_8B))  
    UartPara.Flag |= UART_DATA_7BIT_FLAG;
    #endif
    
    // 发送和接收DMA设置
    #if (UART2TX_DMA_EN > 0)
    UartPara.Flag |= UART_DMAREQ_TX_FLAG;   // 设置发送DMA
    #endif
    #if (UART2RX_DMA_EN > 0)
    UartPara.Flag |= UART_DMAREQ_RX_FLAG;   // 设置接收DMA
    #endif
    
    //UartPara.Flag |= UART_HWFC_RTS_FLAG|UART_HWFC_CTS_FLAG; // 流控及DMA设置
    //UartPara.Flag |= UART_ISRHOOK_FLAG;    // 设置调用串口接收钩子函数, 串口接收数据由用户在Uart2_ISRHook()函数中自己编程实现    
    
    UartPara.Mode = UART_AsynFD;             // 设置模式: 全双工的，异步通信
    UartPara.BaudRate = UART2_BAUD;          // 设置波特率

    UartPara.TxBufLen = UART2_TXBUF_SIZE;   // 设置发送缓存长度
    UartPara.RxBufLen = UART2_RXBUF_SIZE;   // 设置接收缓存长度
    UartPara.pTxBuf = Uart2_TxBuffer;       // 设置发送缓存指针
    UartPara.pRxBuf = Uart2_RxBuffer;       // 设置接收缓存指针    
   
    flag = Uart_Init(UART2_ID, (UART_PARA *)&UartPara.Flag); // 初始化UART2
    #if (DEBUG_APP_EN == 1)
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {
            printf("AT+INFO=UART2 Init, OK\r\n");  
        }
        else
        {
            printf("AT+ERROR=UART2 Init,ERROR,%d\r\n", flag);  
        } 
    }
    #endif    
#endif
    
//---UART3初始化-------------------------------------------------------
#if (UART3_EN > 0) 
    UartPara.Flag = 0;                    // 设置为0
    #if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F107XX))
		#if (UART3_REMAP == UART_REMAP_1)     // 设置管脚重映射
        UartPara.Flag |= UART_REMAP1_FLAG;
        #elif (UART3_REMAP == UART_REMAP_2)   // 设置管脚重映射
        UartPara.Flag |= UART_REMAP2_FLAG;
        #endif 
    #endif
    
    UartPara.TXPin = UART3_TX;              // 设置TX管脚
    UartPara.RXPin = UART3_RX;              // 设置RX管脚
    UartPara.RS485DirPin = UART3_DIR;       // 设置RS485方向控制IO
    #if (UART3_DIR != IO_NONE)              // 没有转RS485接口
    UartPara.Flag |= UART_RS485EN_FLAG;   // 设置RS485接口标志
    #if (UART3_DIR_HL == 1)                 // 为1设置高电平接收, 默认低电平接收
    UartPara.Flag |= UART_RS485DIR_FLAG;  // DIR高电平接收
    #endif
    #endif
    #if (UART3_WORD_LENGTH == UART_WORD_LENGTH_9B) // 设置数据位数  
    UartPara.Flag |= UART_WORD_LENGTH_9BIT_FLAG;
    #endif
    #if (UART3_PARITY == UART_PARITY_EVEN)      // 设置偶检验
    UartPara.Flag |= UART_PARITY_EVEN_FLAG;
    #elif (UART3_PARITY == UART_PARITY_ODD)     // 设置奇检验
    UartPara.Flag |= UART_PARITY_ODD_FLAG;
    #endif    
    #if (UART3_STOP_BITS == UART_STOP_BITS_2)   // 设置2位停止位
    UartPara.Flag |= UART_STOP_BITS2_FLAG;
    #elif (UART3_PARITY == UART_STOP_BITS_0_5)  // 设置0.5位停止位
    UartPara.Flag |= UART_STOP_BITS0_5_FLAG;
    #elif (UART3_PARITY == UART_STOP_BITS_2)    // 设置1.5位停止位
    UartPara.Flag |= UART_STOP_BITS1_5_FLAG;
    #endif    
    
    // 在设置了奇偶检验位并且数据位设置8bit, 实际有效数据位是7bit请初始化时设置该标志
    #if ((UART3_PARITY > 0)&&(UART3_WORD_LENGTH == UART_WORD_LENGTH_8B))  
    UartPara.Flag |= UART_DATA_7BIT_FLAG;
    #endif    
    
    // 发送和接收DMA设置
    #if (UART3TX_DMA_EN > 0)
    UartPara.Flag |= UART_DMAREQ_TX_FLAG;   // 设置发送DMA
    #endif
    #if (UART3RX_DMA_EN > 0)
    UartPara.Flag |= UART_DMAREQ_RX_FLAG;   // 设置接收DMA
    #endif
    
    //UartPara.Flag |= UART_HWFC_RTS_FLAG|UART_HWFC_CTS_FLAG; // 流控及DMA设置
    //UartPara.Flag |= UART_ISRHOOK_FLAG;   // 设置调用串口接收钩子函数, 串口接收数据由用户在Uart3_ISRHook()函数中自己编程实现    
    
    UartPara.Mode = UART_AsynFD;             // 设置模式: 全双工的，异步通信
    UartPara.BaudRate = UART3_BAUD;          // 设置波特率
    
    UartPara.TxBufLen = UART3_TXBUF_SIZE;   // 设置发送缓存长度
    UartPara.RxBufLen = UART3_RXBUF_SIZE;   // 设置接收缓存长度
    UartPara.pTxBuf = Uart3_TxBuffer;       // 设置发送缓存指针
    UartPara.pRxBuf = Uart3_RxBuffer;       // 设置接收缓存指针    
  
    flag = Uart_Init(UART3_ID, (UART_PARA *)&UartPara.Flag); // 初始化UART3
    #if (DEBUG_APP_EN == 1)
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {
            printf("AT+INFO=UART3 Init, OK\r\n");  
        }
        else
        {
            printf("AT+ERROR=UART3 Init, ERROR, %d\r\n", flag);  
        } 
    }
    #endif    
#endif

//---UART4初始化-------------------------------------------------------
#if (UART4_EN > 0)     
    UartPara.Flag = 0;                    // 设置为0
    UartPara.TXPin = UART4_TX;              // 设置TX管脚
    UartPara.RXPin = UART4_RX;              // 设置RX管脚
    UartPara.RS485DirPin = UART4_DIR;       // 设置RS485方向控制IO
    #if (UART4_DIR != IO_NONE)              // 没有转RS485接口
    UartPara.Flag |= UART_RS485EN_FLAG;   // 设置RS485接口标志
    #if (UART4_DIR_HL == 1)                 // 为1设置高电平接收, 默认低电平接收
    UartPara.Flag |= UART_RS485DIR_FLAG;  // DIR高电平接收
    #endif
    #endif
    #if (UART4_WORD_LENGTH == UART_WORD_LENGTH_9B) // 设置数据位数  
    UartPara.Flag |= UART_WORD_LENGTH_9BIT_FLAG;
    #endif
    #if (UART4_PARITY == UART_PARITY_EVEN)      // 设置偶检验
    UartPara.Flag |= UART_PARITY_EVEN_FLAG;
    #elif (UART4_PARITY == UART_PARITY_ODD)     // 设置奇检验
    UartPara.Flag |= UART_PARITY_ODD_FLAG;
    #endif    
    #if (UART4_STOP_BITS == UART_STOP_BITS_2)   // 设置2位停止位
    UartPara.Flag |= UART_STOP_BITS2_FLAG;
    #elif (UART4_PARITY == UART_STOP_BITS_0_5)  // 设置0.5位停止位
    UartPara.Flag |= UART_STOP_BITS0_5_FLAG;
    #elif (UART4_PARITY == UART_STOP_BITS_2)    // 设置1.5位停止位
    UartPara.Flag |= UART_STOP_BITS1_5_FLAG;
    #endif
    // 在设置了奇偶检验位并且数据位设置8bit, 实际有效数据位是7bit请初始化时设置该标志
    #if ((UART4_PARITY > 0)&&(UART4_WORD_LENGTH == UART_WORD_LENGTH_8B))  
    UartPara.Flag |= UART_DATA_7BIT_FLAG;
    #endif    
        
    // 发送和接收DMA设置
    #if (UART4TX_DMA_EN > 0)
    UartPara.Flag |= UART_DMAREQ_TX_FLAG;   // 设置发送DMA
    #endif
    #if (UART4RX_DMA_EN > 0)
    UartPara.Flag |= UART_DMAREQ_RX_FLAG;   // 设置接收DMA
    #endif
    
    //UartPara.Flag |= UART_ISRHOOK_FLAG;   // 设置调用串口接收钩子函数, 串口接收数据由用户在Uart4_ISRHook()函数中自己编程实现    
    
    UartPara.Mode = UART_AsynFD;             // 设置模式: 全双工的，异步通信
    UartPara.BaudRate = UART4_BAUD;          // 设置波特率
   
    UartPara.TxBufLen = UART4_TXBUF_SIZE;   // 设置发送缓存长度
    UartPara.RxBufLen = UART4_RXBUF_SIZE;   // 设置接收缓存长度
    UartPara.pTxBuf = Uart4_TxBuffer;       // 设置发送缓存指针
    UartPara.pRxBuf = Uart4_RxBuffer;       // 设置接收缓存指针    
  
    flag = Uart_Init(UART4_ID, (UART_PARA *)&UartPara.Flag); // 初始化UART4
    #if (DEBUG_APP_EN == 1)
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {
            printf("AT+INFO=UART4 Init, OK\r\n");  
        }
        else
        {
            printf("AT+ERROR=UART4 Init, ERROR,%d\r\n", flag);  
        } 
    }
    #endif    
#endif

//---UART5初始化-------------------------------------------------------
#if (UART5_EN > 0) 
    UartPara.Flag = 0;                    // 设置为0
    UartPara.TXPin = UART5_TX;              // 设置TX管脚
    UartPara.RXPin = UART5_RX;              // 设置RX管脚
    UartPara.RS485DirPin = UART5_DIR;       // 设置RS485方向控制IO
    #if (UART5_DIR != IO_NONE)              // 没有转RS485接口
    UartPara.Flag |= UART_RS485EN_FLAG;   // 设置RS485接口标志
    #if (UART5_DIR_HL == 1)                 // 为1设置高电平接收, 默认低电平接收
    UartPara.Flag |= UART_RS485DIR_FLAG;  // DIR高电平接收
    #endif
    #endif
    #if (UART5_WORD_LENGTH == UART_WORD_LENGTH_9B) // 设置数据位数  
    UartPara.Flag |= UART_WORD_LENGTH_9BIT_FLAG;
    #endif
    #if (UART5_PARITY == UART_PARITY_EVEN)      // 设置偶检验
    UartPara.Flag |= UART_PARITY_EVEN_FLAG;
    #elif (UART5_PARITY == UART_PARITY_ODD)     // 设置奇检验
    UartPara.Flag |= UART_PARITY_ODD_FLAG;
    #endif    
    #if (UART5_STOP_BITS == UART_STOP_BITS_2)   // 设置2位停止位
    UartPara.Flag |= UART_STOP_BITS2_FLAG;
    #elif (UART5_PARITY == UART_STOP_BITS_0_5)  // 设置0.5位停止位
    UartPara.Flag |= UART_STOP_BITS0_5_FLAG;
    #elif (UART5_PARITY == UART_STOP_BITS_2)    // 设置1.5位停止位
    UartPara.Flag |= UART_STOP_BITS1_5_FLAG;
    #endif
    
    // 在设置了奇偶检验位并且数据位设置8bit, 实际有效数据位是7bit请初始化时设置该标志
    #if ((UART5_PARITY > 0)&&(UART5_WORD_LENGTH == UART_WORD_LENGTH_8B))  
    UartPara.Flag |= UART_DATA_7BIT_FLAG;
    #endif   
    
    // 发送和接收DMA设置
    #if (UART5TX_DMA_EN > 0)
    UartPara.Flag |= UART_DMAREQ_TX_FLAG;   // 设置发送DMA
    #endif
    #if (UART5RX_DMA_EN > 0)
    UartPara.Flag |= UART_DMAREQ_RX_FLAG;   // 设置接收DMA
    #endif
            
    //UartPara.Flag |= UART_ISRHOOK_FLAG;   // 设置调用串口接收钩子函数, 串口接收数据由用户在Uart5_ISRHook()函数中自己编程实现    


    UartPara.Mode = UART_AsynFD;             // 设置模式: 全双工的，异步通信
    UartPara.BaudRate = UART5_BAUD;          // 设置波特率
    
    UartPara.TxBufLen = UART5_TXBUF_SIZE;   // 设置发送缓存长度
    UartPara.RxBufLen = UART5_RXBUF_SIZE;   // 设置接收缓存长度
    UartPara.pTxBuf = Uart5_TxBuffer;       // 设置发送缓存指针
    UartPara.pRxBuf = Uart5_RxBuffer;       // 设置接收缓存指针    

    flag = Uart_Init(UART5_ID, (UART_PARA *)&UartPara.Flag); // 初始化UART5
    #if (DEBUG_APP_EN == 1)
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {
            printf("AT+INFO=UART5 Init, OK\r\n");  
        }
        else
        {
            printf("AT+ERROR=UART5 Init, ERROR, %d\r\n", flag);  
        } 
    }
    #endif    
#endif

//---UART6初始化-------------------------------------------------------
#if (UART6_EN > 0) 
    UartPara.Flag = 0;                    // 设置为0
    UartPara.TXPin = UART6_TX;              // 设置TX管脚
    UartPara.RXPin = UART6_RX;              // 设置RX管脚
    UartPara.RS485DirPin = UART6_DIR;       // 设置RS485方向控制IO
    #if (UART6_DIR != IO_NONE)              // 没有转RS485接口
    UartPara.Flag |= UART_RS485EN_FLAG;   // 设置RS485接口标志
    #if (UART5_DIR_HL == 1)                 // 为1设置高电平接收, 默认低电平接收
    UartPara.Flag |= UART_RS485DIR_FLAG;  // DIR高电平接收
    #endif
    #endif
    #if (UART6_WORD_LENGTH == UART_WORD_LENGTH_9B) // 设置数据位数  
    UartPara.Flag |= UART_WORD_LENGTH_9BIT_FLAG;
    #endif
    #if (UART6_PARITY == UART_PARITY_EVEN)      // 设置偶检验
    UartPara.Flag |= UART_PARITY_EVEN_FLAG;
    #elif (UART6_PARITY == UART_PARITY_ODD)     // 设置奇检验
    UartPara.Flag |= UART_PARITY_ODD_FLAG;
    #endif    
    #if (UART6_STOP_BITS == UART_STOP_BITS_2)   // 设置2位停止位
    UartPara.Flag |= UART_STOP_BITS2_FLAG;
    #elif (UART6_PARITY == UART_STOP_BITS_0_5)  // 设置0.5位停止位
    UartPara.Flag |= UART_STOP_BITS0_5_FLAG;
    #elif (UART6_PARITY == UART_STOP_BITS_2)    // 设置1.5位停止位
    UartPara.Flag |= UART_STOP_BITS1_5_FLAG;
    #endif
    
    // 在设置了奇偶检验位并且数据位设置8bit, 实际有效数据位是7bit请初始化时设置该标志
    #if ((UART6_PARITY > 0)&&(UART6_WORD_LENGTH == UART_WORD_LENGTH_8B))  
    UartPara.Flag |= UART_DATA_7BIT_FLAG;
    #endif   
    
    // 发送和接收DMA设置
    #if (UART6TX_DMA_EN > 0)
    UartPara.Flag |= UART_DMAREQ_TX_FLAG;   // 设置发送DMA
    #endif
    #if (UART6RX_DMA_EN > 0)
    UartPara.Flag |= UART_DMAREQ_RX_FLAG;   // 设置接收DMA
    #endif
    
    //UartPara.Flag |= UART_HWFC_RTS_FLAG|UART_HWFC_CTS_FLAG; // 流控及DMA设置    
    //UartPara.Flag |= UART_ISRHOOK_FLAG;   // 设置调用串口接收钩子函数, 串口接收数据由用户在Uart6_ISRHook()函数中自己编程实现    


    UartPara.Mode = UART_AsynFD;             // 设置模式: 全双工的，异步通信
    UartPara.BaudRate = UART6_BAUD;          // 设置波特率
    
    UartPara.TxBufLen = UART6_TXBUF_SIZE;   // 设置发送缓存长度
    UartPara.RxBufLen = UART6_RXBUF_SIZE;   // 设置接收缓存长度
    UartPara.pTxBuf = Uart6_TxBuffer;       // 设置发送缓存指针
    UartPara.pRxBuf = Uart6_RxBuffer;       // 设置接收缓存指针    

    flag = Uart_Init(UART6_ID, (UART_PARA *)&UartPara.Flag); // 初始化UART5
    #if (DEBUG_APP_EN == 1)
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {
            printf("AT+INFO=UART6 Init, OK\r\n");  
        }
        else
        {
            printf("AT+ERROR=UART6 Init, ERROR, %d\r\n", flag);  
        } 
    }
    #endif    
#endif
}


/***********************************************************************************
* Function: CAN_APPInit;
*
* Description: CAN1-CAN2应用初始化函数;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
#if ((CAN1_EN>0)||(CAN2_EN>0)) // CAN1-2应用初始化
void CAN_APPInit(void)
{
    CAN_PARA  CANPara;
    CAN_FILTER_PARA Filter;
    INT32U i;
    INT32S flag;
    
    // 滤波器初始化参数
    Filter.CAN2StartBank = CAN2_START_BANK; // CAN2开始组, 它们定义了CAN2(从)接口的开始组，范围是1~27    
    Filter.FIFO = CAN_FILTER_FIFO;          // CAN 过滤器FIFO关联配置:Bit27~Bit0有效, bit0是第0组，bit27是第27组 报文在通过了某过滤器的过滤后，
                                            // 将被存放到其关联的FIFO中, 0：过滤器被关联到FIFO0；1：过滤器被关联到FIFO1。
    Filter.Scale = CAN_FILTER_SCALE;        // CAN 过滤器位宽寄存器：Bit27~Bit0有效, bit0是第0组，bit27是第27组，
                                            // 0：过滤器位宽为2个16位; 1：过滤器位宽为单个32位。
    Filter.Mode = CAN_FILTER_MODE;          // CAN过滤器模式 (Filter mode)：Bit27~Bit0有效, bit0是第0组，	bit27是第27组，
                                            // 0: 过滤器组x的2个32位寄存器工作在标识符屏蔽位模式；1: 过滤器组x的2个32位寄存器工作在标识符列表模式。
    Filter.Active = CAN_FILTER_ACTIVE;      // 过滤器激活 (Filter active): 	 Bit27~Bit0有效, bit0是第0组，	bit27是第27组
                                            // 0：过滤器被禁用；1：过滤器被激活。
    Filter.pBuf = CAN_FilterBuf;            // 设置的过滤器寄存器数据指针
    Filter.MaxLen = CAN_FILTER_MAXNUM*2;      // 滤波器总长度
    
    #if (CAN1_EN>0)
    Filter.len = CAN2_START_BANK*2;       // 设置的过滤器寄存器数据长度
    for(i=0; i<(CAN2_START_BANK*2); i++) // 初始化滤波器ID为1-28
    {
    	CAN_FilterBuf[i] = ((i+1)<<SHIFT_BIT)|(CAN1_IDE<<2)|(CAN1_RTR<<1);
	}
    #endif
    
    #if (CAN2_EN>0)
    Filter.len += CAN2_START_BANK*2;                        // 设置的过滤器寄存器数据长度
    for(i=CAN2_START_BANK*2; i<CAN_FILTER_MAXNUM*2; i++)    // 初始化滤波器ID为1-28
    {
    	CAN_FilterBuf[i] = ((i-CAN2_START_BANK*2+1)<<SHIFT_BIT)|(CAN2_IDE<<2)|(CAN2_RTR<<1);
	}
    #endif
    
    #if (CAN1_EN>0)
    // CAN1初始化参数
    CANPara.Flag = 0;
    CANPara.Mode = CAN1_MODE;       // 0,正常模式; 1, 环回模式(用于调试); 2, 静默模式(用于调试); 3, 环回/静默模式(用于调试);
	CANPara.IDE = CAN1_IDE;         // 帧类型: 标准帧:CAN_STD_ID, 扩展帧:CAN_EXT_ID; 默认由配置文件设置
    CANPara.RTR = CAN1_RTR;         // 远程发送请求: 数据帧, CAN_RTR_DATA; 远程帧, CAN_RTR_REMOTE; 默认由配置文件设置
    #if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F107XX))
	CANPara.PinRemap = CAN1_REMAP;  // CAN引脚功能重映射
    #endif
    CANPara.TXPin = CAN1_TX;        // CAN发送引脚定义
    CANPara.RXPin = CAN1_RX;        // CAN接收引脚定义   
    
    CANPara.Baud = CAN1_BAUD;              // CAN波特率
    CANPara.RxMsgNum = CAN1_RXBUF_SIZE;    // CAN接收缓存可接收消息个数,范围 1~256, 数量不要太大,会占用大量RAM
    CANPara.TxMsgNum = CAN1_TXBUF_SIZE;    // CAN发送缓存可发送消息个数,范围 1~256, 数量不要太大,会占用大量RAM
    CANPara.pRxMsgBuf =  CAN1_RxBuffer;     // CAN接收缓存指针
    CANPara.pTxMsgBuf = CAN1_TxBuffer;     // CAN发送缓存指针
    
    flag = CAN_Init(CAN1_ID, (CAN_PARA *)&CANPara.Flag, (CAN_FILTER_PARA *)&Filter.CAN2StartBank); // 初始化CAN1
    #if (DEBUG_APP_EN == 1)
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {           
            printf("AT+INFO=CAN1 Init, OK\r\n");  
        }
        else
        {        
            printf("AT+ERROR=CAN1 Init, ERROR\r\n");         
        }
    }    
    #endif
    #endif
    
     #if (CAN2_EN>0)
    // CAN2初始化参数
    CANPara.Flag = 0;
    CANPara.Mode = CAN2_MODE;       // 0,正常模式; 1, 环回模式(用于调试); 2, 静默模式(用于调试); 3, 环回/静默模式(用于调试);
	CANPara.IDE = CAN2_IDE;         // 帧类型: 标准帧:CAN_STD_ID, 扩展帧:CAN_EXT_ID; 默认由配置文件设置
    CANPara.RTR = CAN2_RTR;         // 远程发送请求: 数据帧, CAN_RTR_DATA; 远程帧, CAN_RTR_REMOTE; 默认由配置文件设置
    #if (MODULE_CLASS == STM32F107XX)
	CANPara.PinRemap = CAN2_REMAP;  // CAN引脚功能重映射
    #endif
    CANPara.TXPin = CAN2_TX;        // CAN发送引脚定义
    CANPara.RXPin = CAN2_RX;        // CAN接收引脚定义   
    
    CANPara.Baud = CAN2_BAUD;              // CAN波特率
    CANPara.RxMsgNum = CAN2_RXBUF_SIZE;    // CAN接收缓存可接收消息个数,范围 1~256, 数量不要太大,会占用大量RAM
    CANPara.TxMsgNum = CAN2_TXBUF_SIZE;    // CAN发送缓存可发送消息个数,范围 1~256, 数量不要太大,会占用大量RAM
    CANPara.pRxMsgBuf =  CAN2_RxBuffer;     // CAN接收缓存指针
    CANPara.pTxMsgBuf = CAN2_TxBuffer;     // CAN发送缓存指针
    
    flag = CAN_Init(CAN2_ID, (CAN_PARA *)&CANPara.Flag, 0); // 初始化CAN2
    #if (DEBUG_APP_EN == 1)
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {           
            printf("AT+INFO=CAN2 Init, OK\r\n");  
        }
        else
        {        
            printf("AT+ERROR=CAN2 Init, ERROR\r\n");         
        }
    }    
    #endif
    #endif
}
#endif
/***********************************************************************************
* Function: TIMER_APPInit;
*
* Description: TIM1-TIM5应用初始化;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
#if ((TIM1_EN > 0)||(TIM2_EN > 0)||(TIM3_EN > 0)||(TIM4_EN > 0)||(TIM5_EN > 0)||(TIM6_EN > 0)||(TIM7_EN > 0)||(TIM8_EN > 0)  \
    ||(TIM9_EN > 0)||(TIM10_EN > 0)||(TIM11_EN > 0)||(TIM12_EN > 0)||(TIM13_EN > 0)||(TIM14_EN > 0)) //TIM1-TIM14应用初始化
void TIM_APPInit(void)
{
    TIM_PARA TIMPara;
    INT32S flag;

/***********************************************************************/
// TIM1初始化
/***********************************************************************/
#if (TIM1_EN>0)
    TIMPara.Flag = 0;              // 初始化0
    TIMPara.Flag |= TIM1CH_EN;     // 初始化TIM使能标志
    TIMPara.Mode = TIM1_MODE;        // 设置工作模式
    #if (TIM1_MODE == TIM_WKMODE_COUNT) // 计数模式需要设置分频系数
    TIMPara.Prescaler = TIM1_PSC;    // 设置时钟分频   
    #endif

    flag = Timer_Init(TIM1_ID, (TIM_PARA *)&TIMPara.Flag); // 初始化定时器
    #if (DEBUG_APP_EN == 1)           
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {
            printf("AT+INFO=TIM1 Init, OK\r\n");  
            
        }
        else
        {
            printf("AT+ERROR=TIM1 Init, ERROR\r\n");  
        }
    }
    #endif
#endif
    
/***********************************************************************/
// TIM2初始化
/***********************************************************************/
#if (TIM2_EN>0)
    TIMPara.Flag = 0;              // 初始化0
    TIMPara.Flag |= TIM2CH_EN;     // 初始化TIM使能标志
    TIMPara.Mode = TIM2_MODE;        // 设置工作模式
    #if (TIM2_MODE == TIM_WKMODE_COUNT) // 计数模式需要设置分频系数
    TIMPara.Prescaler = TIM2_PSC;    // 设置时钟分频   
    #endif
    
    
    flag = Timer_Init(TIM2_ID, (TIM_PARA *)&TIMPara.Flag); // 初始化定时器
    #if (DEBUG_APP_EN == 1)           
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {
            printf("AT+INFO=TIM2 Init, OK\r\n");  
            
        }
        else
        {
            printf("AT+ERROR=TIM2 Init, ERROR\r\n");  
        }
    }
    #endif
#endif   

/***********************************************************************/
// TIM3初始化
/***********************************************************************/
#if (TIM3_EN>0)
    TIMPara.Flag = 0;              // 初始化0
    TIMPara.Flag |= TIM2CH_EN;     // 初始化TIM使能标志
    TIMPara.Mode = TIM3_MODE;        // 设置工作模式
    #if (TIM3_MODE == TIM_WKMODE_COUNT) // 计数模式需要设置分频系数
    TIMPara.Prescaler = TIM3_PSC;    // 设置时钟分频   
    #endif  
    
    flag = Timer_Init(TIM3_ID, (TIM_PARA *)&TIMPara.Flag); // 初始化定时器
    #if (DEBUG_APP_EN == 1)           
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {
            printf("AT+INFO=TIM3 Init, OK\r\n");  
            
        }
        else
        {
            printf("AT+ERROR=TIM3 Init, ERROR\r\n");  
        }
    }
    #endif
#endif 

/***********************************************************************/
// TIM4初始化
/***********************************************************************/
#if (TIM4_EN>0)
    TIMPara.Flag = 0;              // 初始化0
    TIMPara.Flag |= TIM4CH_EN;     // 初始化TIM使能标志
    TIMPara.Mode = TIM4_MODE;        // 设置工作模式
    #if (TIM4_MODE == TIM_WKMODE_COUNT) // 计数模式需要设置分频系数
    TIMPara.Prescaler = TIM4_PSC;    // 设置时钟分频   
    #endif
    
    flag = Timer_Init(TIM4_ID, (TIM_PARA *)&TIMPara.Flag); // 初始化定时器
    #if (DEBUG_APP_EN == 1)           
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {
            printf("AT+INFO=TIM4 Init, OK\r\n");  
            
        }
        else
        {
            printf("AT+ERROR=TIM4 Init, ERROR\r\n");  
        }
    }
    #endif
#endif   

/***********************************************************************/
// TIM5初始化
/***********************************************************************/
#if (TIM5_EN>0)
    TIMPara.Flag = 0;              // 初始化0
    TIMPara.Flag |= TIM5CH_EN;     // 初始化TIM使能标志
    TIMPara.Mode = TIM5_MODE;        // 设置工作模式
    #if (TIM5_MODE == TIM_WKMODE_COUNT) // 计数模式需要设置分频系数
    TIMPara.Prescaler = TIM5_PSC;    // 设置时钟分频   
    #endif

    
    flag = Timer_Init(TIM5_ID, (TIM_PARA *)&TIMPara.Flag); // 初始化定时器
    #if (DEBUG_APP_EN == 1)           
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {
            printf("AT+INFO=TIM5 Init, OK\r\n");  
            
        }
        else
        {
            printf("AT+ERROR=TIM5 Init, ERROR\r\n");  
        }
    }
    #endif
#endif 
    
/***********************************************************************/
// TIM6初始化
/***********************************************************************/
#if (TIM6_EN>0)
    TIMPara.Flag = 0;              // 初始化0
    TIMPara.Flag |= TIM6_EN;       // 初始化TIM使能标志
    TIMPara.Mode = TIM6_MODE;        // 设置工作模式
    #if (TIM6_MODE == TIM_WKMODE_COUNT) // 计数模式需要设置分频系数
    TIMPara.Prescaler = TIM6_PSC;    // 设置时钟分频   
    #endif
    
    flag = Timer_Init(TIM6_ID, (TIM_PARA *)&TIMPara.Flag); // 初始化定时器
    #if (DEBUG_APP_EN == 1)           
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {
            printf("AT+INFO=TIM6 Init, OK\r\n");  
            
        }
        else
        {
            printf("AT+ERROR=TIM6 Init, ERROR\r\n");  
        }
    }
    #endif
#endif

/***********************************************************************/
// TIM7初始化
/***********************************************************************/
#if (TIM7_EN>0)
    TIMPara.Flag = 0;              // 初始化0
    TIMPara.Flag |= TIM7_EN;     // 初始化TIM使能标志
    TIMPara.Mode = TIM7_MODE;        // 设置工作模式
    #if (TIM7_MODE == TIM_WKMODE_COUNT) // 计数模式需要设置分频系数
    TIMPara.Prescaler = TIM7_PSC;    // 设置时钟分频   
    #endif
    
    flag = Timer_Init(TIM7_ID, (TIM_PARA *)&TIMPara.Flag); // 初始化定时器
    #if (DEBUG_APP_EN == 1)           
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {
            printf("AT+INFO=TIM7 Init, OK\r\n");  
            
        }
        else
        {
            printf("AT+ERROR=TIM7 Init, ERROR\r\n");  
        }
    }
    #endif
#endif     

/***********************************************************************/
// TIM8初始化
/***********************************************************************/  
#if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F407XX))
#if (TIM8_EN>0)
    TIMPara.Flag = 0;              // 初始化0
    TIMPara.Flag |= TIM8CH_EN;     // 初始化TIM使能标志
    TIMPara.Mode = TIM8_MODE;        // 设置工作模式
    #if (TIM8_MODE == TIM_WKMODE_COUNT) // 计数模式需要设置分频系数
    TIMPara.Prescaler = TIM8_PSC;    // 设置时钟分频   
    #endif

    flag = Timer_Init(TIM8_ID, (TIM_PARA *)&TIMPara.Flag); // 初始化定时器
    #if (DEBUG_APP_EN == 1)           
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {
            printf("AT+INFO=TIM8 Init, OK\r\n");  
            
        }
        else
        {
            printf("AT+ERROR=TIM8 Init, ERROR\r\n");  
        }
    }
    #endif
#endif   
#endif

/***********************************************************************/
// STM32F407XX模块新增定时器初始化
/***********************************************************************/
#if (MODULE_CLASS == STM32F407XX)
/***********************************************************************/
// TIM9初始化
/***********************************************************************/
#if (TIM9_EN>0)
    TIMPara.Flag = 0;              // 初始化0
    TIMPara.Flag |= TIM9CH_EN;     // 初始化TIM使能标志
    TIMPara.Mode = TIM9_MODE;        // 设置工作模式
    #if (TIM9_MODE == TIM_WKMODE_COUNT) // 计数模式需要设置分频系数
    TIMPara.Prescaler = TIM9_PSC;    // 设置时钟分频   
    #endif

    flag = Timer_Init(TIM9_ID, (TIM_PARA *)&TIMPara.Flag); // 初始化定时器
    #if (DEBUG_APP_EN == 1)           
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {
            printf("AT+INFO=TIM9 Init, OK\r\n");  
            
        }
        else
        {
            printf("AT+ERROR=TIM9 Init, ERROR\r\n");  
        }
    }
    #endif
#endif  
/***********************************************************************/
// TIM10初始化
/***********************************************************************/
#if (TIM10_EN>0)
    TIMPara.Flag = 0;              // 初始化0
    TIMPara.Flag |= TIM10CH_EN;     // 初始化TIM使能标志
    TIMPara.Mode = TIM10_MODE;        // 设置工作模式
    #if (TIM10_MODE == TIM_WKMODE_COUNT) // 计数模式需要设置分频系数
    TIMPara.Prescaler = TIM10_PSC;    // 设置时钟分频   
    #endif

    flag = Timer_Init(TIM10_ID, (TIM_PARA *)&TIMPara.Flag); // 初始化定时器
    #if (DEBUG_APP_EN == 1)           
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {
            printf("AT+INFO=TIM10 Init, OK\r\n");  
            
        }
        else
        {
            printf("AT+ERROR=TIM10 Init, ERROR\r\n");  
        }
    }
    #endif
#endif   
/***********************************************************************/
// TIM11初始化
/***********************************************************************/
#if (TIM11_EN>0)
    TIMPara.Flag = 0;              // 初始化0
    TIMPara.Flag |= TIM11CH_EN;     // 初始化TIM使能标志
    TIMPara.Mode = TIM11_MODE;        // 设置工作模式
    #if (TIM11_MODE == TIM_WKMODE_COUNT) // 计数模式需要设置分频系数
    TIMPara.Prescaler = TIM11_PSC;    // 设置时钟分频   
    #endif

    flag = Timer_Init(TIM11_ID, (TIM_PARA *)&TIMPara.Flag); // 初始化定时器
    #if (DEBUG_APP_EN == 1)           
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {
            printf("AT+INFO=TIM11 Init, OK\r\n");  
            
        }
        else
        {
            printf("AT+ERROR=TIM11 Init, ERROR\r\n");  
        }
    }
    #endif
#endif  
/***********************************************************************/
// TIM12初始化
/***********************************************************************/
#if (TIM12_EN>0)
    TIMPara.Flag = 0;              // 初始化0
    TIMPara.Flag |= TIM12CH_EN;     // 初始化TIM使能标志
    TIMPara.Mode = TIM12_MODE;        // 设置工作模式
    #if (TIM12_MODE == TIM_WKMODE_COUNT) // 计数模式需要设置分频系数
    TIMPara.Prescaler = TIM12_PSC;    // 设置时钟分频   
    #endif

    flag = Timer_Init(TIM12_ID, (TIM_PARA *)&TIMPara.Flag); // 初始化定时器
    #if (DEBUG_APP_EN == 1)           
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {
            printf("AT+INFO=TIM12 Init, OK\r\n");  
            
        }
        else
        {
            printf("AT+ERROR=TIM12 Init, ERROR\r\n");  
        }
    }
    #endif
#endif  
/***********************************************************************/
// TIM13初始化
/***********************************************************************/
#if (TIM13_EN>0)
    TIMPara.Flag = 0;              // 初始化0
    TIMPara.Flag |= TIM13CH_EN;     // 初始化TIM使能标志
    TIMPara.Mode = TIM13_MODE;        // 设置工作模式
    #if (TIM13_MODE == TIM_WKMODE_COUNT) // 计数模式需要设置分频系数
    TIMPara.Prescaler = TIM13_PSC;    // 设置时钟分频   
    #endif

    flag = Timer_Init(TIM13_ID, (TIM_PARA *)&TIMPara.Flag); // 初始化定时器
    #if (DEBUG_APP_EN == 1)           
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {
            printf("AT+INFO=TIM13 Init, OK\r\n");  
            
        }
        else
        {
            printf("AT+ERROR=TIM13 Init, ERROR\r\n");  
        }
    }
    #endif
#endif 
/***********************************************************************/
// TIM14初始化
/***********************************************************************/
#if (TIM14_EN>0)
    TIMPara.Flag = 0;              // 初始化0
    TIMPara.Flag |= TIM14CH_EN;     // 初始化TIM使能标志
    TIMPara.Mode = TIM14_MODE;        // 设置工作模式
    #if (TIM14_MODE == TIM_WKMODE_COUNT) // 计数模式需要设置分频系数
    TIMPara.Prescaler = TIM14_PSC;    // 设置时钟分频   
    #endif

    flag = Timer_Init(TIM14_ID, (TIM_PARA *)&TIMPara.Flag); // 初始化定时器
    #if (DEBUG_APP_EN == 1)           
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {
            printf("AT+INFO=TIM14 Init, OK\r\n");  
            
        }
        else
        {
            printf("AT+ERROR=TIM14 Init, ERROR\r\n");  
        }
    }
    #endif
#endif 
    
#endif
    
}
#endif
/***********************************************************************************
* Function: PWM_APPInit;
*
* Description: PWM输出应用初始化函数;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
#if ((PWM1_EN>0)||(PWM2_EN>0)||(PWM3_EN>0)||(PWM4_EN>0)||(PWM5_EN>0)||(PWM6_EN>0)||(PWM7_EN>0)||(PWM8_EN>0)) //PWM1-PWM8应用初始化
void PWM_APPInit(void)
{
    PWM_PARA PWMPara;
    INT32S flag;
    
#if (PWM1_EN>0)                                // 通道1使能
    PWMPara.Flag = 0;                          // 初始化0
    PWMPara.Mode = 0;                          // 初始化工作模式,默认是0
    PWMPara.Freq = PWM1_FREQ;                  // 初始化PWM1频率
    PWMPara.TimerID = PWM1_TIM;              // 设置PWM使用的定时器
    #if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F107XX))
	PWMPara.TimPin.Remap = PWM1_REMAP;         // 设置PWM1管脚重映射    
    #endif
    
    #if (PWM1_ISRHOOK_EN > 0)
    PWMPara.Flag |= PWM_ISRHOOK_EN_FLAG;      // 使能PWM_ISRHOOK函数调用: 当PWM发送脉冲完成或者出错调用该钩子函数
    #endif
    PWMPara.pISRHook = PWM_ISRHook;
    
    #if (PWM1_MODE == PWM_DMA)
    PWMPara.Flag |= PWM_WRITE_EN_FLAG;         // 使能PWM脉冲输出由PWM_Write()函数控制
    #endif
    
    #if (PWM1CH1_EN == 1)
        PWMPara.Flag |= PWMCH1_EN_FLAG;        // 初始化PWM CH1使能标志
        #if (PWM1CH1_PIN == 1)
        PWMPara.Flag |= PWMCH1_PIN_FLAG;       // 初始化PWM CH1停止模式管脚输出电平标志
        #endif
        PWMPara.Rate[PWM_CH1] = PWM1CH1_RATE;  // 初始化通道1占空比
        PWMPara.TimPin.CH1 = PWM1_CH1;         // 设置CH1管脚         
    #endif
    
    #if (PWM1CH2_EN == 1)                      // 通道2使能
        PWMPara.Flag |= PWMCH2_EN_FLAG;        // 初始化PWM CH2使能标志
        #if (PWM1CH2_PIN == 1)
        PWMPara.Flag |= PWMCH2_PIN_FLAG;       // 初始化PWM CH2停止模式管脚输出电平标志
        #endif
        PWMPara.Rate[PWM_CH2] = PWM1CH2_RATE;  // 初始化通道2占空比
        PWMPara.TimPin.CH2 = PWM1_CH2;         // 设置CH2管脚 
    #endif
    
    #if (PWM1CH3_EN == 1)                      // 通道3使能
        PWMPara.Flag |= PWMCH3_EN_FLAG;        // 初始化PWM CH3使能标志
        #if (PWM1CH3_PIN == 1)
        PWMPara.Flag |= PWMCH3_PIN_FLAG;       // 初始化PWM CH3停止模式管脚输出电平标志
        #endif
        PWMPara.Rate[PWM_CH3] = PWM1CH3_RATE;  // 初始化通道3占空比
        PWMPara.TimPin.CH3 = PWM1_CH3;         // 设置CH3管脚 
    #endif
    
    #if (PWM1CH4_EN == 1)                      // 通道4使能
        PWMPara.Flag |= PWMCH4_EN_FLAG;        // 初始化PWM CH4使能标志
        #if (PWM1CH4_PIN == 1)
        PWMPara.Flag |= PWMCH4_PIN_FLAG;       // 初始化PWM CH4停止模式管脚输出电平标志
        #endif
        PWMPara.Rate[PWM_CH4] = PWM1CH4_RATE;  // 初始化通道4占空比
        PWMPara.TimPin.CH4 = PWM1_CH4;         // 设置CH4管脚 
    #endif
    #ifdef PWM1_ETR
    PWMPara.TimPin.ETR = PWM1_ETR;             // 设置ETR管脚
    #else
    PWMPara.TimPin.ETR = IO_NONE;              // 设置ETR管脚
    #endif
    
    flag = PWM_Init(PWM1_ID, (PWM_PARA *)&PWMPara.Flag);  // PWM1初始化
    #if (DEBUG_APP_EN == 1)           
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {
            printf("AT+INFO=PWM1 Init, OK\r\n");  
            
        }
        else
        {
            printf("AT+ERROR=PWM1 Init, ERROR\r\n");  
        }
    }
    #endif
#endif
    
#if (PWM2_EN>0)   
    PWMPara.Flag = 0;                         // 初始化0
    PWMPara.Mode = 0;                         // 初始化工作模式,默认是0
    PWMPara.Freq = PWM2_FREQ;                 // 初始化PWM2频率
    PWMPara.TimerID = PWM2_TIM;               // 设置PWM使用的定时器
    #if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F107XX))
	PWMPara.TimPin.Remap = PWM2_REMAP;         // 设置PWM2管脚重映射    
    #endif

    #if (PWM2_ISRHOOK_EN > 0)
    PWMPara.Flag |= PWM_ISRHOOK_EN_FLAG;      // 使能PWM_ISRHOOK函数调用: 当PWM发送脉冲完成或者出错调用该钩子函数
    #endif
    PWMPara.pISRHook = PWM_ISRHook;
    
    #if (PWM2_MODE == PWM_DMA)
    PWMPara.Flag |= PWM_WRITE_EN_FLAG;         // 使能PWM脉冲输出由PWM_Write()函数控制
    #endif
    
    #if (PWM2CH1_EN == 1)                     // 通道1使能
        PWMPara.Flag |= PWMCH1_EN_FLAG;       // 初始化PWM CH1使能标志
        #if (PWM2CH1_PIN == 1)
        PWMPara.Flag |= PWMCH1_PIN_FLAG;      // 初始化PWM CH1停止模式管脚输出电平标志
        #endif
        PWMPara.Rate[PWM_CH1] = PWM2CH1_RATE; // 初始化通道1占空比
        PWMPara.TimPin.CH1 = PWM2_CH1;        // 设置CH1管脚         
    #endif
    
    #if (PWM2CH2_EN == 1)                     // 通道2使能
        PWMPara.Flag |= PWMCH2_EN_FLAG;       // 初始化PWM CH2使能标志
        #if (PWM2CH2_PIN == 1)
        PWMPara.Flag |= PWMCH2_PIN_FLAG;      // 初始化PWM CH2停止模式管脚输出电平标志
        #endif
        PWMPara.Rate[PWM_CH2] = PWM2CH2_RATE; // 初始化通道2占空比
        PWMPara.TimPin.CH2 = PWM2_CH2;        // 设置CH2管脚 
    #endif
    
    #if (PWM2CH3_EN == 1)                     // 通道3使能
        PWMPara.Flag |= PWMCH3_EN_FLAG;       // 初始化PWM CH3使能标志
        #if (PWM2CH3_PIN == 1)
        PWMPara.Flag |= PWMCH3_PIN_FLAG;      // 初始化PWM CH3停止模式管脚输出电平标志
        #endif
        PWMPara.Rate[PWM_CH3] = PWM2CH3_RATE; // 初始化通道3占空比
        PWMPara.TimPin.CH3 = PWM2_CH3;        // 设置CH3管脚 
    #endif
    
    #if (PWM2CH4_EN == 1)                     // 通道4使能
        PWMPara.Flag |= PWMCH4_EN_FLAG;       // 初始化PWM CH4使能标志
        #if (PWM2CH4_PIN == 1)
        PWMPara.Flag |= PWMCH4_PIN_FLAG;      // 初始化PWM CH4停止模式管脚输出电平标志
        #endif
        PWMPara.Rate[PWM_CH4] = PWM2CH4_RATE; // 初始化通道4占空比
        PWMPara.TimPin.CH4 = PWM2_CH4;        // 设置CH4管脚 
    #endif
    #ifdef PWM2_ETR
    PWMPara.TimPin.ETR = PWM2_ETR;             // 设置ETR管脚
    #else
    PWMPara.TimPin.ETR = IO_NONE;              // 设置ETR管脚
    #endif

    
    flag = PWM_Init(PWM2_ID, (PWM_PARA *)&PWMPara.Flag);  // PWM2初始化
    #if (DEBUG_APP_EN == 1)           
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {
            printf("AT+INFO=PWM2 Init, OK\r\n");  
            
        }
        else
        {
            printf("AT+ERROR=PWM2 Init, ERROR\r\n");  
        }
    }
    #endif
#endif    
    
#if (PWM3_EN>0)   
    PWMPara.Flag = 0;                         // 初始化0
    PWMPara.Mode = 0;                         // 初始化工作模式,默认是0
    PWMPara.Freq = PWM3_FREQ;                 // 初始化PWM3频率
    PWMPara.TimerID = PWM3_TIM;               // 设置PWM使用的定时器
    #if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F107XX))
	PWMPara.TimPin.Remap = PWM3_REMAP;         // 设置PWM3管脚重映射    
    #endif    

    #if (PWM3_ISRHOOK_EN > 0)
    PWMPara.Flag |= PWM_ISRHOOK_EN_FLAG;      // 使能PWM_ISRHOOK函数调用: 当PWM发送脉冲完成或者出错调用该钩子函数
    #endif
    PWMPara.pISRHook = PWM_ISRHook;

    #if (PWM3_MODE == PWM_DMA)
    PWMPara.Flag |= PWM_WRITE_EN_FLAG;         // 使能PWM脉冲输出由PWM_Write()函数控制
    #endif
    
    #if (PWM3CH1_EN == 1)                     // 通道1使能
        PWMPara.Flag |= PWMCH1_EN_FLAG;       // 初始化PWM CH1使能标志
        #if (PWM3CH1_PIN == 1)
        PWMPara.Flag |= PWMCH1_PIN_FLAG;      // 初始化PWM CH1停止模式管脚输出电平标志
        #endif
        PWMPara.Rate[PWM_CH1] = PWM3CH1_RATE; // 初始化通道1占空比
        PWMPara.TimPin.CH1 = PWM3_CH1;        // 设置CH1管脚         
    #endif
    
    #if (PWM3CH2_EN == 1)                     // 通道2使能
        PWMPara.Flag |= PWMCH2_EN_FLAG;       // 初始化PWM CH2使能标志
        #if (PWM3CH2_PIN == 1)
        PWMPara.Flag |= PWMCH2_PIN_FLAG;      // 初始化PWM CH2停止模式管脚输出电平标志
        #endif
        PWMPara.Rate[PWM_CH2] = PWM3CH2_RATE; // 初始化通道2占空比
        PWMPara.TimPin.CH2 = PWM3_CH2;        // 设置CH2管脚 
    #endif
    
    #if (PWM3CH3_EN == 1)                     // 通道3使能
        PWMPara.Flag |= PWMCH3_EN_FLAG;       // 初始化PWM CH3使能标志
        #if (PWM3CH3_PIN == 1)
        PWMPara.Flag |= PWMCH3_PIN_FLAG;      // 初始化PWM CH3停止模式管脚输出电平标志
        #endif
        PWMPara.Rate[PWM_CH3] = PWM3CH3_RATE; // 初始化通道3占空比
        PWMPara.TimPin.CH3 = PWM3_CH3;        // 设置CH3管脚 
    #endif
    
    #if (PWM3CH4_EN == 1)                     // 通道4使能
        PWMPara.Flag |= PWMCH4_EN_FLAG;       // 初始化PWM CH4使能标志
        #if (PWM3CH4_PIN == 1)
        PWMPara.Flag |= PWMCH4_PIN_FLAG;      // 初始化PWM CH4停止模式管脚输出电平标志
        #endif
        PWMPara.Rate[PWM_CH4] = PWM3CH4_RATE; // 初始化通道4占空比
        PWMPara.TimPin.CH4 = PWM3_CH4;        // 设置CH4管脚 
    #endif
    #ifdef PWM3_ETR
    PWMPara.TimPin.ETR = PWM3_ETR;             // 设置ETR管脚
    #else
    PWMPara.TimPin.ETR = IO_NONE;              // 设置ETR管脚
    #endif
    
    flag = PWM_Init(PWM3_ID, (PWM_PARA *)&PWMPara.Flag);  // PWM3初始化
    #if (DEBUG_APP_EN == 1)           
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {
            printf("AT+INFO=PWM3 Init, OK\r\n");  
            
        }
        else
        {
            printf("AT+ERROR=PWM3 Init, ERROR\r\n");  
        }
    }
    #endif
#endif       
    
#if (PWM4_EN>0)   
    PWMPara.Flag = 0;                         // 初始化0
    PWMPara.Mode = 0;                         // 初始化工作模式,默认是0
    PWMPara.Freq = PWM4_FREQ;                 // 初始化PWM4频率
    PWMPara.TimerID = PWM4_TIM;               // 设置PWM使用的定时器
    #if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F107XX))
	PWMPara.TimPin.Remap = PWM4_REMAP;         // 设置PWM4管脚重映射    
    #endif 

    #if (PWM4_ISRHOOK_EN > 0)
    PWMPara.Flag |= PWM_ISRHOOK_EN_FLAG;      // 使能PWM_ISRHOOK函数调用: 当PWM发送脉冲完成或者出错调用该钩子函数
    #endif
    PWMPara.pISRHook = PWM_ISRHook;

    #if (PWM4_MODE == PWM_DMA)
    PWMPara.Flag |= PWM_WRITE_EN_FLAG;         // 使能PWM脉冲输出由PWM_Write()函数控制
    #endif
    
    #if (PWM4CH1_EN == 1)                     // 通道1使能
        PWMPara.Flag |= PWMCH1_EN_FLAG;       // 初始化PWM CH1使能标志
        #if (PWM4CH1_PIN == 1)
        PWMPara.Flag |= PWMCH1_PIN_FLAG;      // 初始化PWM CH1停止模式管脚输出电平标志
        #endif
        PWMPara.Rate[PWM_CH1] = PWM4CH1_RATE; // 初始化通道1占空比
        PWMPara.TimPin.CH1 = PWM4_CH1;        // 设置CH1管脚         
    #endif
    
    #if (PWM4CH2_EN == 1)                     // 通道2使能
        PWMPara.Flag |= PWMCH2_EN_FLAG;       // 初始化PWM CH2使能标志
        #if (PWM4CH2_PIN == 1)
        PWMPara.Flag |= PWMCH2_PIN_FLAG;      // 初始化PWM CH2停止模式管脚输出电平标志
        #endif
        PWMPara.Rate[PWM_CH2] = PWM4CH2_RATE; // 初始化通道2占空比
        PWMPara.TimPin.CH2 = PWM4_CH2;        // 设置CH2管脚 
    #endif
    
    #if (PWM4CH3_EN == 1)                     // 通道3使能
        PWMPara.Flag |= PWMCH3_EN_FLAG;       // 初始化PWM CH3使能标志
        #if (PWM4CH3_PIN == 1)
        PWMPara.Flag |= PWMCH3_PIN_FLAG;      // 初始化PWM CH3停止模式管脚输出电平标志
        #endif
        PWMPara.Rate[PWM_CH3] = PWM4CH3_RATE; // 初始化通道3占空比
        PWMPara.TimPin.CH3 = PWM4_CH3;        // 设置CH3管脚 
    #endif
    
    #if (PWM4CH4_EN == 1)                     // 通道4使能
        PWMPara.Flag |= PWMCH4_EN_FLAG;       // 初始化PWM CH4使能标志
        #if (PWM4CH4_PIN == 1)
        PWMPara.Flag |= PWMCH4_PIN_FLAG;      // 初始化PWM CH4停止模式管脚输出电平标志
        #endif
        PWMPara.Rate[PWM_CH4] = PWM4CH4_RATE; // 初始化通道4占空比
        PWMPara.TimPin.CH4 = PWM4_CH4;        // 设置CH4管脚 
    #endif
    #ifdef PWM4_ETR
    PWMPara.TimPin.ETR = PWM4_ETR;             // 设置ETR管脚
    #else
    PWMPara.TimPin.ETR = IO_NONE;              // 设置ETR管脚
    #endif
    
    flag = PWM_Init(PWM4_ID, (PWM_PARA *)&PWMPara.Flag);  // PWM4初始化
    #if (DEBUG_APP_EN == 1)           
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {
            printf("AT+INFO=PWM4 Init, OK\r\n");  
            
        }
        else
        {
            printf("AT+ERROR=PWM4 Init, ERROR\r\n");  
        }
    }
    #endif
#endif       
    
#if (MODULE_CLASS == STM32F407XX) 
    
#if (PWM5_EN>0)   
    PWMPara.Flag = 0;                         // 初始化0
    PWMPara.Mode = 0;                         // 初始化工作模式,默认是0
    PWMPara.Freq = PWM5_FREQ;                 // 初始化PWM5频率
    PWMPara.TimerID = PWM5_TIM;               // 设置PWM使用的定时器

    #if (PWM5_ISRHOOK_EN > 0)
    PWMPara.Flag |= PWM_ISRHOOK_EN_FLAG;      // 使能PWM_ISRHOOK函数调用: 当PWM发送脉冲完成或者出错调用该钩子函数
    #endif
    PWMPara.pISRHook = PWM_ISRHook;

    #if (PWM5_MODE == PWM_DMA)
    PWMPara.Flag |= PWM_WRITE_EN_FLAG;         // 使能PWM脉冲输出由PWM_Write()函数控制
    #endif
    
    #if (PWM5CH1_EN == 1)                     // 通道1使能
        PWMPara.Flag |= PWMCH1_EN_FLAG;       // 初始化PWM CH1使能标志
        #if (PWM5CH1_PIN == 1)
        PWMPara.Flag |= PWMCH1_PIN_FLAG;      // 初始化PWM CH1停止模式管脚输出电平标志
        #endif
        PWMPara.Rate[PWM_CH1] = PWM5CH1_RATE; // 初始化通道1占空比
        PWMPara.TimPin.CH1 = PWM5_CH1;        // 设置CH1管脚         
    #endif
    
    #if (PWM5CH2_EN == 1)                     // 通道2使能
        PWMPara.Flag |= PWMCH2_EN_FLAG;       // 初始化PWM CH2使能标志
        #if (PWM5CH2_PIN == 1)
        PWMPara.Flag |= PWMCH2_PIN_FLAG;      // 初始化PWM CH2停止模式管脚输出电平标志
        #endif
        PWMPara.Rate[PWM_CH2] = PWM5CH2_RATE; // 初始化通道2占空比
        PWMPara.TimPin.CH2 = PWM5_CH2;        // 设置CH2管脚 
    #endif
    #ifdef PWM5_ETR
    PWMPara.TimPin.ETR = PWM5_ETR;             // 设置ETR管脚
    #else
    PWMPara.TimPin.ETR = IO_NONE;              // 设置ETR管脚
    #endif
        
    flag = PWM_Init(PWM5_ID, (PWM_PARA *)&PWMPara.Flag);  // PWM5初始化
    #if (DEBUG_APP_EN == 1)           
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {
            printf("AT+INFO=PWM5 Init, OK\r\n");  
            
        }
        else
        {
            printf("AT+ERROR=PWM5 Init, ERROR\r\n");  
        }
    }
    #endif
#endif   
    
#if (PWM6_EN>0)   
    PWMPara.Flag = 0;                         // 初始化0
    PWMPara.Mode = 0;                         // 初始化工作模式,默认是0
    PWMPara.Freq = PWM6_FREQ;                 // 初始化PWM6频率
    PWMPara.TimerID = PWM6_TIM;               // 设置PWM使用的定时器

    #if (PWM6_ISRHOOK_EN > 0)
    PWMPara.Flag |= PWM_ISRHOOK_EN_FLAG;      // 使能PWM_ISRHOOK函数调用: 当PWM发送脉冲完成或者出错调用该钩子函数
    #endif
    PWMPara.pISRHook = PWM_ISRHook;

    #if (PWM6_MODE == PWM_DMA)
    PWMPara.Flag |= PWM_WRITE_EN_FLAG;         // 使能PWM脉冲输出由PWM_Write()函数控制
    #endif
    
    #if (PWM6CH1_EN == 1)                     // 通道1使能
        PWMPara.Flag |= PWMCH1_EN_FLAG;       // 初始化PWM CH1使能标志
        #if (PWM6CH1_PIN == 1)
        PWMPara.Flag |= PWMCH1_PIN_FLAG;      // 初始化PWM CH1停止模式管脚输出电平标志
        #endif
        PWMPara.Rate[PWM_CH1] = PWM6CH1_RATE; // 初始化通道1占空比
        PWMPara.TimPin.CH1 = PWM6_CH1;        // 设置CH1管脚         
    #endif
    
    #if (PWM6CH2_EN == 1)                     // 通道2使能
        PWMPara.Flag |= PWMCH2_EN_FLAG;       // 初始化PWM CH2使能标志
        #if (PWM6CH2_PIN == 1)
        PWMPara.Flag |= PWMCH2_PIN_FLAG;      // 初始化PWM CH2停止模式管脚输出电平标志
        #endif
        PWMPara.Rate[PWM_CH2] = PWM6CH2_RATE; // 初始化通道2占空比
        PWMPara.TimPin.CH2 = PWM6_CH2;        // 设置CH2管脚 
    #endif
    #ifdef PWM6_ETR
    PWMPara.TimPin.ETR = PWM6_ETR;             // 设置ETR管脚
    #else
    PWMPara.TimPin.ETR = IO_NONE;              // 设置ETR管脚
    #endif
        
    flag = PWM_Init(PWM6_ID, (PWM_PARA *)&PWMPara.Flag);  // PWM6初始化
    #if (DEBUG_APP_EN == 1)           
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {
            printf("AT+INFO=PWM6 Init, OK\r\n");  
            
        }
        else
        {
            printf("AT+ERROR=PWM6 Init, ERROR\r\n");  
        }
    }
    #endif
#endif 
    
#if (PWM7_EN>0)   
    PWMPara.Flag = 0;                         // 初始化0
    PWMPara.Mode = 0;                         // 初始化工作模式,默认是0
    PWMPara.Freq = PWM7_FREQ;                 // 初始化PWM7频率
    PWMPara.TimerID = PWM7_TIM;               // 设置PWM使用的定时器

    #if (PWM7_ISRHOOK_EN > 0)
    PWMPara.Flag |= PWM_ISRHOOK_EN_FLAG;      // 使能PWM_ISRHOOK函数调用: 当PWM发送脉冲完成或者出错调用该钩子函数
    #endif
    PWMPara.pISRHook = PWM_ISRHook;
    
    #if (PWM7_MODE == PWM_DMA)
    PWMPara.Flag |= PWM_WRITE_EN_FLAG;         // 使能PWM脉冲输出由PWM_Write()函数控制
    #endif    
    
    #if (PWM7CH1_EN == 1)                     // 通道1使能
        PWMPara.Flag |= PWMCH1_EN_FLAG;       // 初始化PWM CH1使能标志
        #if (PWM7CH1_PIN == 1)
        PWMPara.Flag |= PWMCH1_PIN_FLAG;      // 初始化PWM CH1停止模式管脚输出电平标志
        #endif
        PWMPara.Rate[PWM_CH1] = PWM7CH1_RATE; // 初始化通道1占空比
        PWMPara.TimPin.CH1 = PWM7_CH1;        // 设置CH1管脚         
    #endif
    #ifdef PWM7_ETR
    PWMPara.TimPin.ETR = PWM7_ETR;             // 设置ETR管脚
    #else
    PWMPara.TimPin.ETR = IO_NONE;              // 设置ETR管脚
    #endif
            
    flag = PWM_Init(PWM7_ID, (PWM_PARA *)&PWMPara.Flag);  // PWM7初始化
    #if (DEBUG_APP_EN == 1)           
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {
            printf("AT+INFO=PWM7 Init, OK\r\n");  
            
        }
        else
        {
            printf("AT+ERROR=PWM7 Init, ERROR\r\n");  
        }
    }
    #endif
#endif    

#endif
}
#endif
/***********************************************************************************
* Function: FCLK_APPInit;
*
* Description: FCLK输入应用初始化函数;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
#if ((FCLK1_EN>0)||(FCLK2_EN>0)||(FCLK3_EN>0)||(FCLK4_EN>0)||(FCLK5_EN>0)||(FCLK6_EN>0)||(FCLK7_EN>0)||(FCLK8_EN>0)) //FCLK1-FCLK8应用初始化
void FCLK_APPInit(void)
{
    FCLK_PARA FCLKPara;
    INT32S flag;
    
#if (FCLK1_EN>0)    
    FCLKPara.Flag = 0;                            // 初始化0    
    FCLKPara.Mode = FCLK1_MODE;                   // 初始化工作模式
    FCLKPara.TimerID = FCLK1_TIM;                 // 设置FCLK使用的定时器
    #if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F107XX))
	FCLKPara.TimPin.Remap = FCLK1_REMAP;          // 设置FCLK1管脚重映射 
    #endif
    FCLKPara.MinFreq = FCLK1_MINFREQ; 	          // 模式2，3中，测量最小频率设定, 单位hz
    #ifdef FCLK1_ETR
    FCLKPara.TimPin.ETR = FCLK1_ETR;              // 设置ETR管脚
    #else
    FCLKPara.TimPin.ETR = IO_NONE;
    #endif
    #if (FCLK1CH1_EN == 1)                        // 通道1使能
        FCLKPara.Flag |= FCLKCH1_EN_FLAG;         // 初始化FCLK CH1使能标志
        #if (FCLK1CH1_PIN == 1)
        FCLKPara.Flag |= FCLKCH1_PIN_FLAG;        // 初始化FCLK CH1管脚输入信号触发边沿： 0, 上升沿; 1, 下降沿
        #endif
        #if (FCLK1CH1_PCS > 0)
        FCLKPara.Flag &= ~FCLKCH1_PCS_FLAG;       // 清除标志
        FCLKPara.Flag |= (INT32U)FCLK1CH1_PCS<<8; // FCLK CH1管脚输入信号预分频系数： 0, 不分频; 1, 2分频; 2, 4分频; 3, 8分频;
        #endif
        FCLKPara.TimPin.CH1 = FCLK1_CH1;          // 设置CH1管脚 
        #if ((FCLK1_MODE == 2)||(FCLK1_MODE == 3))
        FCLKPara.BufLen[0] = FCLK1CH1_BUF_SIZE;   // 设置接收缓存长度  
        FCLKPara.pBuf[0] = FClk1CH1Buf;           // 设置接收数据缓存指针
        #if (FCLK1CH1_DMA_EN > 0)
        FCLKPara.Flag |= FCLKCH1_DMA_FLAG;
        #endif
        #endif
    #endif
    
    #if (FCLK1CH2_EN == 1)                        // 通道2使能
        FCLKPara.Flag |= FCLKCH2_EN_FLAG;         // 初始化FCLK CH2使能标志
        #if (FCLK1CH2_PIN == 1)
        FCLKPara.Flag |= FCLKCH2_PIN_FLAG;        // 初始化FCLK CH2管脚输入信号触发边沿： 0, 上升沿; 1, 下降沿
        #endif
        #if (FCLK1CH2_PCS > 0)
        FCLKPara.Flag &= ~FCLKCH2_PCS_FLAG;       // 清除标志
        FCLKPara.Flag |= (INT32U)FCLK1CH2_PCS<<10;// FCLK CH2管脚输入信号预分频系数： 0, 不分频; 1, 2分频; 2, 4分频; 3, 8分频;
        #endif    
        FCLKPara.TimPin.CH2 = FCLK1_CH2;          // 设置CH2管脚 
        #if ((FCLK1_MODE == 2)||(FCLK1_MODE == 3))
        FCLKPara.BufLen[1] = FCLK1CH2_BUF_SIZE;   // 设置接收缓存长度  
        FCLKPara.pBuf[1] = FClk1CH2Buf;           // 设置接收数据缓存指针
        #if (FCLK1CH2_DMA_EN > 0)
        FCLKPara.Flag |= FCLKCH2_DMA_FLAG;
        #endif
        #endif
    #endif
    
    #if (FCLK1CH3_EN == 1)                        // 通道3使能
        FCLKPara.Flag |= FCLKCH3_EN_FLAG;         // 初始化FCLK CH3使能标志
        #if (FCLK1CH3_PIN == 1)
        FCLKPara.Flag |= FCLKCH3_PIN_FLAG;        // 初始化FCLK CH3管脚输入信号触发边沿： 0, 上升沿; 1, 下降沿
        #endif 
        #if (FCLK1CH3_PCS > 0)
        FCLKPara.Flag &= ~FCLKCH3_PCS_FLAG;       // 清除标志
        FCLKPara.Flag |= (INT32U)FCLK1CH3_PCS<<12;// FCLK CH3管脚输入信号预分频系数： 0, 不分频; 1, 2分频; 2, 4分频; 3, 8分频;
        #endif       
        FCLKPara.TimPin.CH3 = FCLK1_CH3;          // 设置CH3管脚 
        #if ((FCLK1_MODE == 2)||(FCLK1_MODE == 3))
        FCLKPara.BufLen[2] = FCLK1CH3_BUF_SIZE;   // 设置接收缓存长度  
        FCLKPara.pBuf[2] = FClk1CH3Buf;           // 设置接收数据缓存指针
        #if (FCLK1CH3_DMA_EN > 0)
        FCLKPara.Flag |= FCLKCH3_DMA_FLAG;
        #endif        
        #endif
    #endif
    
    #if (FCLK1CH4_EN == 1)                        // 通道4使能
        FCLKPara.Flag |= FCLKCH4_EN_FLAG;         // 初始化FCLK CH4使能标志
        #if (FCLK1CH4_PIN == 1)
        FCLKPara.Flag |= FCLKCH4_PIN_FLAG;        // 初始化FCLK CH4管脚输入信号触发边沿： 0, 上升沿; 1, 下降沿
        #endif   
        #if (FCLK1CH4_PCS > 0)
        FCLKPara.Flag &= ~FCLKCH4_PCS_FLAG;       // 清除标志
        FCLKPara.Flag |= (INT32U)FCLK1CH4_PCS<<14;// FCLK CH4管脚输入信号预分频系数： 0, 不分频; 1, 2分频; 2, 4分频; 3, 8分频;
        #endif   
        FCLKPara.TimPin.CH4 = FCLK1_CH4;          // 设置CH4管脚     
        #if ((FCLK1_MODE == 2)||(FCLK1_MODE == 3))
        FCLKPara.BufLen[3] = FCLK1CH4_BUF_SIZE;   // 设置接收缓存长度  
        FCLKPara.pBuf[3] = FClk1CH4Buf;           // 设置接收数据缓存指针
        #if (FCLK1CH4_DMA_EN > 0)
        FCLKPara.Flag |= FCLKCH4_DMA_FLAG;
        #endif
        #endif
    #endif    
    
    flag = FCLK_Init(FCLK1_ID, (FCLK_PARA *)&FCLKPara.Flag); // FCLK1初始化
    #if (DEBUG_APP_EN == 1)           
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {
            printf("AT+INFO=FCLK1 Init, OK\r\n");  
            
        }
        else
        {
            printf("AT+ERROR=FCLK1 Init, ERROR\r\n");  
        }
    }
    #endif   
#endif
    
#if (FCLK2_EN>0)    
    FCLKPara.Flag = 0;                            // 初始化0    
    FCLKPara.Mode = FCLK2_MODE;                   // 初始化工作模式
    FCLKPara.TimerID = FCLK2_TIM;                 // 设置FCLK使用的定时器
    #if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F107XX))
	FCLKPara.TimPin.Remap = FCLK2_REMAP;          // 设置FCLK2管脚重映射 
    #endif
    FCLKPara.MinFreq = FCLK2_MINFREQ; 	          // 模式2，3中，测量最小频率设定, 单位hz
    #ifdef FCLK2_ETR
    FCLKPara.TimPin.ETR = FCLK2_ETR;              // 设置ETR管脚
    #else
    FCLKPara.TimPin.ETR = IO_NONE;
    #endif
    
    #if (FCLK2CH1_EN == 1)                        // 通道1使能
        FCLKPara.Flag |= FCLKCH1_EN_FLAG;         // 初始化FCLK CH1使能标志
        #if (FCLK2CH1_PIN == 1)
        FCLKPara.Flag |= FCLKCH1_PIN_FLAG;        // 初始化FCLK CH1管脚输入信号触发边沿： 0, 上升沿; 1, 下降沿
        #endif
        #if (FCLK2CH1_PCS > 0)
        FCLKPara.Flag &= ~FCLKCH1_PCS_FLAG;       // 清除标志
        FCLKPara.Flag |= (INT32U)FCLK1CH1_PCS<<8; // FCLK CH1管脚输入信号预分频系数： 0, 不分频; 1, 2分频; 2, 4分频; 3, 8分频;
        #endif
        FCLKPara.TimPin.CH1 = FCLK2_CH1;          // 设置CH1管脚 
        #if ((FCLK2_MODE == 2)||(FCLK2_MODE == 3))
        FCLKPara.BufLen[0] = FCLK2CH1_BUF_SIZE;   // 设置接收缓存长度  
        FCLKPara.pBuf[0] = FClk2CH1Buf;           // 设置接收数据缓存指针
        #if (FCLK2CH1_DMA_EN > 0)
        FCLKPara.Flag |= FCLKCH1_DMA_FLAG;
        #endif
        #endif
    #endif
    
    #if (FCLK2CH2_EN == 1)                        // 通道2使能
        FCLKPara.Flag |= FCLKCH2_EN_FLAG;         // 初始化FCLK CH2使能标志
        #if (FCLK2CH2_PIN == 1)
        FCLKPara.Flag |= FCLKCH2_PIN_FLAG;        // 初始化FCLK CH2管脚输入信号触发边沿： 0, 上升沿; 1, 下降沿
        #endif
        #if (FCLK2CH2_PCS > 0)
        FCLKPara.Flag &= ~FCLKCH2_PCS_FLAG;       // 清除标志
        FCLKPara.Flag |= (INT32U)FCLK2CH2_PCS<<10;// FCLK CH2管脚输入信号预分频系数： 0, 不分频; 1, 2分频; 2, 4分频; 3, 8分频;
        #endif
        FCLKPara.TimPin.CH2 = FCLK2_CH2;            // 设置CH2管脚 
        #if ((FCLK2_MODE == 2)||(FCLK2_MODE == 3))
        FCLKPara.BufLen[1] = FCLK2CH2_BUF_SIZE;     // 设置接收缓存长度  
        FCLKPara.pBuf[1] = FClk2CH2Buf;             // 设置接收数据缓存指针
        #if (FCLK2CH2_DMA_EN > 0)
        FCLKPara.Flag |= FCLKCH2_DMA_FLAG;
        #endif        
        #endif    
    #endif
    
    #if (FCLK2CH3_EN == 1)                          // 通道3使能
        FCLKPara.Flag |= FCLKCH3_EN_FLAG;           // 初始化FCLK CH3使能标志
        #if (FCLK2CH3_PIN == 1)
        FCLKPara.Flag |= FCLKCH3_PIN_FLAG;          // 初始化FCLK CH3管脚输入信号触发边沿： 0, 上升沿; 1, 下降沿
        #endif 
        #if (FCLK2CH3_PCS > 0)
        FCLKPara.Flag &= ~FCLKCH3_PCS_FLAG;         // 清除标志
        FCLKPara.Flag |= (INT32U)FCLK2CH3_PCS<<12;  // FCLK CH3管脚输入信号预分频系数： 0, 不分频; 1, 2分频; 2, 4分频; 3, 8分频;
        #endif       
        FCLKPara.TimPin.CH3 = FCLK2_CH3;            // 设置CH3管脚 
        #if ((FCLK2_MODE == 2)||(FCLK2_MODE == 3))
        FCLKPara.BufLen[2] = FCLK2CH3_BUF_SIZE;     // 设置接收缓存长度  
        FCLKPara.pBuf[2] = FClk2CH3Buf;             // 设置接收数据缓存指针
        #if (FCLK2CH3_DMA_EN > 0)
        FCLKPara.Flag |= FCLKCH3_DMA_FLAG;
        #endif
        #endif
    #endif
    
    #if (FCLK2CH4_EN == 1)                          // 通道4使能
        FCLKPara.Flag |= FCLKCH4_EN_FLAG;           // 初始化FCLK CH4使能标志
        #if (FCLK2CH4_PIN == 1)
        FCLKPara.Flag |= FCLKCH4_PIN_FLAG;          // 初始化FCLK CH4管脚输入信号触发边沿： 0, 上升沿; 1, 下降沿
        #endif   
        #if (FCLK2CH4_PCS > 0)
        FCLKPara.Flag &= ~FCLKCH4_PCS_FLAG;         // 清除标志
        FCLKPara.Flag |= (INT32U)FCLK2CH4_PCS<<14;  // FCLK CH4管脚输入信号预分频系数： 0, 不分频; 1, 2分频; 2, 4分频; 3, 8分频;
        #endif   
        FCLKPara.TimPin.CH4 = FCLK2_CH4;            // 设置CH4管脚    
        #if ((FCLK2_MODE == 2)||(FCLK2_MODE == 3))        
        FCLKPara.BufLen[3] = FCLK2CH4_BUF_SIZE;     // 设置接收缓存长度  
        FCLKPara.pBuf[3] = FClk2CH4Buf;             // 设置接收数据缓存指针
        #if (FCLK2CH4_DMA_EN > 0)
        FCLKPara.Flag |= FCLKCH4_DMA_FLAG;
        #endif
        #endif
    #endif    
    
    flag = FCLK_Init(FCLK2_ID, (FCLK_PARA *)&FCLKPara.Flag); // FCLK2初始化
    #if (DEBUG_APP_EN == 1)           
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {
            printf("AT+INFO=FCLK2 Init, OK\r\n");  
            
        }
        else
        {
            printf("AT+ERROR=FCLK2 Init, ERROR\r\n");  
        }
    }
    #endif    
#endif    
    
#if (FCLK3_EN>0)    
    FCLKPara.Flag = 0;                              // 初始化0    
    FCLKPara.Mode = FCLK3_MODE;                     // 初始化工作模式
    FCLKPara.TimerID = FCLK3_TIM;                   // 设置FCLK使用的定时器
    #if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F107XX))
	FCLKPara.TimPin.Remap = FCLK3_REMAP;            // 设置FCLK3管脚重映射 
    #endif
    FCLKPara.MinFreq = FCLK3_MINFREQ; 	            // 模式2，3中，测量最小频率设定, 单位hz
    #ifdef FCLK3_ETR
    FCLKPara.TimPin.ETR = FCLK3_ETR;              // 设置ETR管脚
    #else
    FCLKPara.TimPin.ETR = IO_NONE;
    #endif
    
    #if (FCLK3CH1_EN == 1)                          // 通道1使能
        FCLKPara.Flag |= FCLKCH1_EN_FLAG;           // 初始化FCLK CH1使能标志
        #if (FCLK3CH1_PIN == 1)
        FCLKPara.Flag |= FCLKCH1_PIN_FLAG;          // 初始化FCLK CH1管脚输入信号触发边沿： 0, 上升沿; 1, 下降沿
        #endif
        #if (FCLK3CH1_PCS > 0)
        FCLKPara.Flag &= ~FCLKCH1_PCS_FLAG;         // 清除标志
        FCLKPara.Flag |= (INT32U)FCLK3CH1_PCS<<8;   // FCLK CH1管脚输入信号预分频系数： 0, 不分频; 1, 2分频; 2, 4分频; 3, 8分频;
        #endif
        FCLKPara.TimPin.CH1 = FCLK3_CH1;            // 设置CH1管脚 
        #if ((FCLK3_MODE == 2)||(FCLK3_MODE == 3))
        FCLKPara.BufLen[0] = FCLK3CH1_BUF_SIZE;     // 设置接收缓存长度  
        FCLKPara.pBuf[0] = FClk3CH1Buf;             // 设置接收数据缓存指针
        #if (FCLK3CH1_DMA_EN > 0)
        FCLKPara.Flag |= FCLKCH1_DMA_FLAG;
        #endif
        #endif
    #endif
    
    #if (FCLK3CH2_EN == 1)                          // 通道2使能
        FCLKPara.Flag |= FCLKCH2_EN_FLAG;           // 初始化FCLK CH2使能标志
        #if (FCLK3CH2_PIN == 1)
        FCLKPara.Flag |= FCLKCH2_PIN_FLAG;          // 初始化FCLK CH2管脚输入信号触发边沿： 0, 上升沿; 1, 下降沿
        #endif
        #if (FCLK3CH2_PCS > 0)
        FCLKPara.Flag &= ~FCLKCH2_PCS_FLAG;         // 清除标志
        FCLKPara.Flag |= (INT32U)FCLK3CH2_PCS<<10;  // FCLK CH2管脚输入信号预分频系数： 0, 不分频; 1, 2分频; 2, 4分频; 3, 8分频;
        #endif
        FCLKPara.TimPin.CH2 = FCLK3_CH2;            // 设置CH2管脚 
        #if ((FCLK3_MODE == 2)||(FCLK3_MODE == 3))
        FCLKPara.BufLen[1] = FCLK3CH2_BUF_SIZE;     // 设置接收缓存长度  
        FCLKPara.pBuf[1] = FClk3CH2Buf;             // 设置接收数据缓存指针
        #if (FCLK3CH2_DMA_EN > 0)
        FCLKPara.Flag |= FCLKCH2_DMA_FLAG;
        #endif
        #endif    
    #endif
    
    #if (FCLK3CH3_EN == 1)                          // 通道3使能
        FCLKPara.Flag |= FCLKCH3_EN_FLAG;           // 初始化FCLK CH3使能标志
        #if (FCLK3CH3_PIN == 1)
        FCLKPara.Flag |= FCLKCH3_PIN_FLAG;          // 初始化FCLK CH3管脚输入信号触发边沿： 0, 上升沿; 1, 下降沿
        #endif 
        #if (FCLK3CH3_PCS > 0)
        FCLKPara.Flag &= ~FCLKCH3_PCS_FLAG;         // 清除标志
        FCLKPara.Flag |= (INT32U)FCLK3CH3_PCS<<12;  // FCLK CH3管脚输入信号预分频系数： 0, 不分频; 1, 2分频; 2, 4分频; 3, 8分频;
        #endif       
        FCLKPara.TimPin.CH3 = FCLK3_CH3;            // 设置CH3管脚 
        #if ((FCLK3_MODE == 2)||(FCLK3_MODE == 3))
        FCLKPara.BufLen[2] = FCLK3CH3_BUF_SIZE;     // 设置接收缓存长度  
        FCLKPara.pBuf[2] = FClk3CH3Buf;             // 设置接收数据缓存指针
        #if (FCLK3CH3_DMA_EN > 0)
        FCLKPara.Flag |= FCLKCH3_DMA_FLAG;
        #endif
        #endif
    #endif
    
    #if (FCLK3CH4_EN == 1)                          // 通道4使能
        FCLKPara.Flag |= FCLKCH4_EN_FLAG;           // 初始化FCLK CH4使能标志
        #if (FCLK3CH4_PIN == 1)
        FCLKPara.Flag |= FCLKCH4_PIN_FLAG;          // 初始化FCLK CH4管脚输入信号触发边沿： 0, 上升沿; 1, 下降沿
        #endif   
        #if (FCLK3CH4_PCS > 0)
        FCLKPara.Flag &= ~FCLKCH4_PCS_FLAG;         // 清除标志
        FCLKPara.Flag |= (INT32U)FCLK3CH4_PCS<<14;  // FCLK CH4管脚输入信号预分频系数： 0, 不分频; 1, 2分频; 2, 4分频; 3, 8分频;
        #endif   
        FCLKPara.TimPin.CH4 = FCLK3_CH4;            // 设置CH4管脚     
        #if ((FCLK3_MODE == 2)||(FCLK3_MODE == 3))
        FCLKPara.BufLen[3] = FCLK3CH4_BUF_SIZE;     // 设置接收缓存长度  
        FCLKPara.pBuf[3] = FClk3CH4Buf;             // 设置接收数据缓存指针
        #if (FCLK3CH4_DMA_EN > 0)
        FCLKPara.Flag |= FCLKCH4_DMA_FLAG;
        #endif
        #endif
    #endif    
    
    flag = FCLK_Init(FCLK3_ID, (FCLK_PARA *)&FCLKPara.Flag); // FCLK3初始化
    #if (DEBUG_APP_EN == 1)           
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {
            printf("AT+INFO=FCLK3 Init, OK\r\n");  
            
        }
        else
        {
            printf("AT+ERROR=FCLK3 Init, ERROR\r\n");  
        }
    }
    #endif    
#endif 

#if (FCLK4_EN>0)    
    FCLKPara.Flag = 0;                              // 初始化0    
    FCLKPara.Mode = FCLK4_MODE;                     // 初始化工作模式
    FCLKPara.TimerID = FCLK4_TIM;                   // 设置FCLK使用的定时器
    #if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F107XX))
	FCLKPara.TimPin.Remap = FCLK4_REMAP;            // 设置FCLK4管脚重映射 
    #endif
    FCLKPara.MinFreq = FCLK4_MINFREQ; 	            // 模式2，3中，测量最小频率设定, 单位hz
    #ifdef FCLK4_ETR
    FCLKPara.TimPin.ETR = FCLK4_ETR;              // 设置ETR管脚
    #else
    FCLKPara.TimPin.ETR = IO_NONE;
    #endif
    
    #if (FCLK4CH1_EN == 1)                          // 通道1使能
        FCLKPara.Flag |= FCLKCH1_EN_FLAG;           // 初始化FCLK CH1使能标志
        #if (FCLK4CH1_PIN == 1)
        FCLKPara.Flag |= FCLKCH1_PIN_FLAG;          // 初始化FCLK CH1管脚输入信号触发边沿： 0, 上升沿; 1, 下降沿
        #endif
        #if (FCLK4CH1_PCS > 0)
        FCLKPara.Flag &= ~FCLKCH1_PCS_FLAG;         // 清除标志
        FCLKPara.Flag |= (INT32U)FCLK4CH1_PCS<<8;   // FCLK CH1管脚输入信号预分频系数： 0, 不分频; 1, 2分频; 2, 4分频; 3, 8分频;
        #endif
        FCLKPara.TimPin.CH1 = FCLK4_CH1;            // 设置CH1管脚 
        #if ((FCLK4_MODE == 2)||(FCLK4_MODE == 3))
        FCLKPara.BufLen[0] = FCLK4CH1_BUF_SIZE;     // 设置接收缓存长度  
        FCLKPara.pBuf[0] = FClk4CH1Buf;             // 设置接收数据缓存指针
        #if (FCLK4CH1_DMA_EN > 0)
        FCLKPara.Flag |= FCLKCH1_DMA_FLAG;
        #endif
        #endif
    #endif
    
    #if (FCLK4CH2_EN == 1)                          // 通道2使能
        FCLKPara.Flag |= FCLKCH2_EN_FLAG;           // 初始化FCLK CH2使能标志
        #if (FCLK4CH2_PIN == 1)
        FCLKPara.Flag |= FCLKCH2_PIN_FLAG;          // 初始化FCLK CH2管脚输入信号触发边沿： 0, 上升沿; 1, 下降沿
        #endif
        #if (FCLK4CH2_PCS > 0)
        FCLKPara.Flag &= ~FCLKCH2_PCS_FLAG;         // 清除标志
        FCLKPara.Flag |= (INT32U)FCLK4CH2_PCS<<10;  // FCLK CH2管脚输入信号预分频系数： 0, 不分频; 1, 2分频; 2, 4分频; 3, 8分频;
        #endif
        FCLKPara.TimPin.CH2 = FCLK4_CH2;            // 设置CH2管脚 
        #if ((FCLK4_MODE == 2)||(FCLK4_MODE == 3))
        FCLKPara.BufLen[1] = FCLK4CH2_BUF_SIZE;     // 设置接收缓存长度  
        FCLKPara.pBuf[1] = FClk4CH2Buf;             // 设置接收数据缓存指针
        #if (FCLK4CH2_DMA_EN > 0)
        FCLKPara.Flag |= FCLKCH2_DMA_FLAG;
        #endif
        #endif    
    #endif
    
    #if (FCLK4CH3_EN == 1)                          // 通道3使能
        FCLKPara.Flag |= FCLKCH3_EN_FLAG;           // 初始化FCLK CH3使能标志
        #if (FCLK4CH3_PIN == 1)
        FCLKPara.Flag |= FCLKCH3_PIN_FLAG;          // 初始化FCLK CH3管脚输入信号触发边沿： 0, 上升沿; 1, 下降沿
        #endif 
        #if (FCLK4CH3_PCS > 0)
        FCLKPara.Flag &= ~FCLKCH3_PCS_FLAG;         // 清除标志
        FCLKPara.Flag |= (INT32U)FCLK4CH3_PCS<<12;  // FCLK CH3管脚输入信号预分频系数： 0, 不分频; 1, 2分频; 2, 4分频; 3, 8分频;
        #endif       
        FCLKPara.TimPin.CH3 = FCLK4_CH3;            // 设置CH3管脚 
        #if ((FCLK4_MODE == 2)||(FCLK4_MODE == 3))
        FCLKPara.BufLen[2] = FCLK4CH3_BUF_SIZE;     // 设置接收缓存长度  
        FCLKPara.pBuf[2] = FClk4CH3Buf;             // 设置接收数据缓存指针
        #if (FCLK4CH3_DMA_EN > 0)
        FCLKPara.Flag |= FCLKCH3_DMA_FLAG;
        #endif
        #endif
    #endif
    
    #if (FCLK4CH4_EN == 1)                          // 通道4使能
        FCLKPara.Flag |= FCLKCH4_EN_FLAG;           // 初始化FCLK CH4使能标志
        #if (FCLK4CH4_PIN == 1)
        FCLKPara.Flag |= FCLKCH4_PIN_FLAG;          // 初始化FCLK CH4管脚输入信号触发边沿： 0, 上升沿; 1, 下降沿
        #endif   
        #if (FCLK4CH4_PCS > 0)
        FCLKPara.Flag &= ~FCLKCH4_PCS_FLAG;         // 清除标志
        FCLKPara.Flag |= (INT32U)FCLK4CH4_PCS<<14;  // FCLK CH4管脚输入信号预分频系数： 0, 不分频; 1, 2分频; 2, 4分频; 3, 8分频;
        #endif   
        FCLKPara.TimPin.CH4 = FCLK4_CH4;            // 设置CH4管脚     
        #if ((FCLK4_MODE == 2)||(FCLK4_MODE == 3))
        FCLKPara.BufLen[3] = FCLK4CH4_BUF_SIZE;     // 设置接收缓存长度  
        FCLKPara.pBuf[3] = FClk4CH4Buf;             // 设置接收数据缓存指针
        #if (FCLK4CH4_DMA_EN > 0)
        FCLKPara.Flag |= FCLKCH4_DMA_FLAG;
        #endif
        #endif
    #endif    
    
    flag = FCLK_Init(FCLK4_ID, (FCLK_PARA *)&FCLKPara.Flag); // FCLK4初始化
    #if (DEBUG_APP_EN == 1)           
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {
            printf("AT+INFO=FCLK4 Init, OK\r\n");  
            
        }
        else
        {
            printf("AT+ERROR=FCLK4 Init, ERROR\r\n");  
        }
    }
    #endif   
#endif     

#if (MODULE_CLASS == STM32F407XX)
    
#if (FCLK5_EN>0)    
    FCLKPara.Flag = 0;                              // 初始化0    
    FCLKPara.Mode = FCLK5_MODE;                     // 初始化工作模式
    FCLKPara.TimerID = FCLK5_TIM;                   // 设置FCLK使用的定时器
    FCLKPara.MinFreq = FCLK5_MINFREQ; 	            // 模式2，3中，测量最小频率设定, 单位hz
    #ifdef FCLK5_ETR
    FCLKPara.TimPin.ETR = FCLK5_ETR;              // 设置ETR管脚
    #else
    FCLKPara.TimPin.ETR = IO_NONE;
    #endif
    
    #if (FCLK5CH1_EN == 1)                          // 通道1使能
        FCLKPara.Flag |= FCLKCH1_EN_FLAG;           // 初始化FCLK CH1使能标志
        #if (FCLK5CH1_PIN == 1)
        FCLKPara.Flag |= FCLKCH1_PIN_FLAG;          // 初始化FCLK CH1管脚输入信号触发边沿： 0, 上升沿; 1, 下降沿
        #endif
        #if (FCLK5CH1_PCS > 0)
        FCLKPara.Flag &= ~FCLKCH1_PCS_FLAG;         // 清除标志
        FCLKPara.Flag |= (INT32U)FCLK5CH1_PCS<<8;   // FCLK CH1管脚输入信号预分频系数： 0, 不分频; 1, 2分频; 2, 4分频; 3, 8分频;
        #endif
        FCLKPara.TimPin.CH1 = FCLK5_CH1;            // 设置CH1管脚 
        #if ((FCLK5_MODE == 2)||(FCLK5_MODE == 3))
        FCLKPara.BufLen[0] = FCLK5CH1_BUF_SIZE;     // 设置接收缓存长度  
        FCLKPara.pBuf[0] = FClk5CH1Buf;             // 设置接收数据缓存指针
        #if (FCLK5CH1_DMA_EN > 0)
        FCLKPara.Flag |= FCLKCH1_DMA_FLAG;
        #endif
        #endif
    #endif
    
    #if (FCLK5CH2_EN == 1)                          // 通道2使能
        FCLKPara.Flag |= FCLKCH2_EN_FLAG;           // 初始化FCLK CH2使能标志
        #if (FCLK5CH2_PIN == 1)
        FCLKPara.Flag |= FCLKCH2_PIN_FLAG;          // 初始化FCLK CH2管脚输入信号触发边沿： 0, 上升沿; 1, 下降沿
        #endif
        #if (FCLK5CH2_PCS > 0)
        FCLKPara.Flag &= ~FCLKCH2_PCS_FLAG;         // 清除标志
        FCLKPara.Flag |= (INT32U)FCLK5CH2_PCS<<10;  // FCLK CH2管脚输入信号预分频系数： 0, 不分频; 1, 2分频; 2, 4分频; 3, 8分频;
        #endif
        FCLKPara.TimPin.CH2 = FCLK5_CH2;            // 设置CH2管脚 
        #if ((FCLK5_MODE == 2)||(FCLK5_MODE == 3))
        FCLKPara.BufLen[1] = FCLK5CH2_BUF_SIZE;     // 设置接收缓存长度  
        FCLKPara.pBuf[1] = FClk5CH2Buf;             // 设置接收数据缓存指针
        #if (FCLK5CH2_DMA_EN > 0)
        FCLKPara.Flag |= FCLKCH2_DMA_FLAG;
        #endif
        #endif    
    #endif    
       
    flag = FCLK_Init(FCLK5_ID, (FCLK_PARA *)&FCLKPara.Flag); // FCLK5初始化
    #if (DEBUG_APP_EN == 1)           
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {
            printf("AT+INFO=FCLK5 Init, OK\r\n");  
            
        }
        else
        {
            printf("AT+ERROR=FCLK5 Init, ERROR\r\n");  
        }
    }
    #endif   
#endif   
    
#if (FCLK6_EN>0)    
    FCLKPara.Flag = 0;                              // 初始化0    
    FCLKPara.Mode = FCLK6_MODE;                     // 初始化工作模式
    FCLKPara.TimerID = FCLK6_TIM;                   // 设置FCLK使用的定时器
    FCLKPara.MinFreq = FCLK6_MINFREQ; 	            // 模式2，3中，测量最小频率设定, 单位hz
    #ifdef FCLK6_ETR
    FCLKPara.TimPin.ETR = FCLK6_ETR;              // 设置ETR管脚
    #else
    FCLKPara.TimPin.ETR = IO_NONE;
    #endif
    
    #if (FCLK6CH1_EN == 1)                          // 通道1使能
        FCLKPara.Flag |= FCLKCH1_EN_FLAG;           // 初始化FCLK CH1使能标志
        #if (FCLK6CH1_PIN == 1)
        FCLKPara.Flag |= FCLKCH1_PIN_FLAG;          // 初始化FCLK CH1管脚输入信号触发边沿： 0, 上升沿; 1, 下降沿
        #endif
        #if (FCLK6CH1_PCS > 0)
        FCLKPara.Flag &= ~FCLKCH1_PCS_FLAG;         // 清除标志
        FCLKPara.Flag |= (INT32U)FCLK6CH1_PCS<<8;   // FCLK CH1管脚输入信号预分频系数： 0, 不分频; 1, 2分频; 2, 4分频; 3, 8分频;
        #endif
        FCLKPara.TimPin.CH1 = FCLK6_CH1;            // 设置CH1管脚 
        #if ((FCLK6_MODE == 2)||(FCLK6_MODE == 3))
        FCLKPara.BufLen[0] = FCLK6CH1_BUF_SIZE;     // 设置接收缓存长度  
        FCLKPara.pBuf[0] = FClk6CH1Buf;             // 设置接收数据缓存指针
        #if (FCLK6CH1_DMA_EN > 0)
        FCLKPara.Flag |= FCLKCH1_DMA_FLAG;
        #endif
        #endif
    #endif
    
    #if (FCLK6CH2_EN == 1)                          // 通道2使能
        FCLKPara.Flag |= FCLKCH2_EN_FLAG;           // 初始化FCLK CH2使能标志
        #if (FCLK6CH2_PIN == 1)
        FCLKPara.Flag |= FCLKCH2_PIN_FLAG;          // 初始化FCLK CH2管脚输入信号触发边沿： 0, 上升沿; 1, 下降沿
        #endif
        #if (FCLK6CH2_PCS > 0)
        FCLKPara.Flag &= ~FCLKCH2_PCS_FLAG;         // 清除标志
        FCLKPara.Flag |= (INT32U)FCLK6CH2_PCS<<10;  // FCLK CH2管脚输入信号预分频系数： 0, 不分频; 1, 2分频; 2, 4分频; 3, 8分频;
        #endif
        FCLKPara.TimPin.CH2 = FCLK6_CH2;            // 设置CH2管脚 
        #if ((FCLK6_MODE == 2)||(FCLK6_MODE == 3))
        FCLKPara.BufLen[1] = FCLK6CH2_BUF_SIZE;     // 设置接收缓存长度  
        FCLKPara.pBuf[1] = FClk6CH2Buf;             // 设置接收数据缓存指针
        #if (FCLK6CH2_DMA_EN > 0)
        FCLKPara.Flag |= FCLKCH2_DMA_FLAG;
        #endif
        #endif    
    #endif    
       
    flag = FCLK_Init(FCLK6_ID, (FCLK_PARA *)&FCLKPara.Flag); // FCLK6初始化
    #if (DEBUG_APP_EN == 1)           
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {
            printf("AT+INFO=FCLK6 Init, OK\r\n");  
            
        }
        else
        {
            printf("AT+ERROR=FCLK6 Init, ERROR\r\n");  
        }
    }
    #endif     
#endif    
    
#if (FCLK7_EN>0)    
    FCLKPara.Flag = 0;                              // 初始化0    
    FCLKPara.Mode = FCLK7_MODE;                     // 初始化工作模式
    FCLKPara.TimerID = FCLK7_TIM;                   // 设置FCLK使用的定时器
    FCLKPara.MinFreq = FCLK7_MINFREQ; 	            // 模式2，3中，测量最小频率设定, 单位hz
    #ifdef FCLK7_ETR
    FCLKPara.TimPin.ETR = FCLK7_ETR;                // 设置ETR管脚
    #else
    FCLKPara.TimPin.ETR = IO_NONE;
    #endif
    
    #if (FCLK7CH1_EN == 1)                          // 通道1使能
        FCLKPara.Flag |= FCLKCH1_EN_FLAG;           // 初始化FCLK CH1使能标志
        #if (FCLK7CH1_PIN == 1)
        FCLKPara.Flag |= FCLKCH1_PIN_FLAG;          // 初始化FCLK CH1管脚输入信号触发边沿： 0, 上升沿; 1, 下降沿
        #endif
        #if (FCLK7CH1_PCS > 0)
        FCLKPara.Flag &= ~FCLKCH1_PCS_FLAG;         // 清除标志
        FCLKPara.Flag |= (INT32U)FCLK7CH1_PCS<<8;   // FCLK CH1管脚输入信号预分频系数： 0, 不分频; 1, 2分频; 2, 4分频; 3, 8分频;
        #endif
        FCLKPara.TimPin.CH1 = FCLK7_CH1;            // 设置CH1管脚 
        #if ((FCLK7_MODE == 2)||(FCLK7_MODE == 3))
        FCLKPara.BufLen[0] = FCLK7CH1_BUF_SIZE;     // 设置接收缓存长度  
        FCLKPara.pBuf[0] = FClk7CH1Buf;             // 设置接收数据缓存指针
        #if (FCLK7CH1_DMA_EN > 0)
        FCLKPara.Flag |= FCLKCH1_DMA_FLAG;
        #endif
        #endif
    #endif
  
    flag = FCLK_Init(FCLK7_ID, (FCLK_PARA *)&FCLKPara.Flag); // FCLK7初始化
    #if (DEBUG_APP_EN == 1)           
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {
            printf("AT+INFO=FCLK7 Init, OK\r\n");  
            
        }
        else
        {
            printf("AT+ERROR=FCLK7 Init, ERROR\r\n");  
        }
    }
    #endif    
#endif        
    
#endif
    
}
#endif

/***********************************************************************************
* Function: SPIFlash_APPInit;
*
* Description: SPI FLASH(W25QXX或AT45DBXX)应用初始化函数;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
#if (SPIFLASH_EN > 0)
void SPIFlash_APPInit(void)
{
    INT32S flag;
    
    #if (SPIFLASH_TYPE == W25QXX)
    W25QXX_PARA Para;
    #endif
    #if (SPIFLASH_TYPE == AT45DBXX)
    AT45DBXX_PARA Para;
    #endif
    Para.Flag = 0;              // 工作标志
    Para.SPI_ID = SPI1_ID;
    #if (SPIFLASH_TYPE == W25QXX)
    Para.CS_Pin = W25QXX_CS;
    Para.Flag |= W25QXX_TYPE_FLAG;
    Para.SectorSize = W25QXX_SECTOR_SIZE;	       // Flash扇区大小(单位：字节) 
    Para.SectorNum = W25QXX_SECTOR_NUM;	           // Flash扇区数量 
    Para.FatFSSectorNum = W25QXX_FATFS_SECTORNUM;  // FatFS文件系统占用扇区数量
    #if (SPIFLASH_MODE==1) // 利用FATFS文件系统进行读写
    Para.pBuf = W25QBuf;
    #else
    Para.pBuf = 0;
    #endif
    flag = W25QXX_Init(&Para);
    #if (DEBUG_APP_EN == 1)   
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {
            printf("AT+INFO=W25QXX Init, OK\r\n");
        }
        else
        {           
            printf("AT+ERROR=W25QXX Init, ERROR\r\n");  
        } 
    }
    #endif 
    #endif   

    #if (SPIFLASH_TYPE == AT45DBXX)
    Para.CS_Pin = AT45DBXX_CS;
    //Para.Type = AT45DBXX;
    //Para.Model = AT45DBXX;
    Para.Flag |= AT45DBXX_TYPE_FLAG;
    Para.SectorSize = AT45DBXX_PAGE_SIZE;	       // Flash扇区大小(单位：字节) 
    Para.SectorNum = AT45DBXX_PAGE_NUM;	           // Flash扇区数量 
    Para.FatFSSectorNum = AT45DBXX_FATFS_PAGENUM;
    flag = AT45DBXX_Init(&Para);
    #if (DEBUG_APP_EN == 1)   
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {
            printf("AT+INFO=AT45DBXX Init, OK\r\n");
        }
        else
        {           
            printf("AT+ERROR=AT45DBXX Init, ERROR\r\n");  
        } 
    }
    #endif     
    #endif 
}
#endif
/***********************************************************************************
* Function: SD_APPInit;
*
* Description: SD卡应用初始化;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
#if (SDCARD_EN > 0) // SD卡使能
void SD_APPInit(void)
{
    SD_PARA Para;
    INT32S flag;
    
    Para.Flag = 0;
    Para.Mode = SD_SPI_MODE;  // SPI读写模式
    Para.SPIx_ID = SPI1_ID;   // 选择SPI1
    
    Para.Pin.CPWR = SD_PWR;
    Para.Pin.INR = SD_INR;
    Para.Pin.CS = SD_CS;
    Para.Pin.WP = SD_WP;
    flag = SD_Init((SD_PARA *)&Para.Flag);    
    #if (DEBUG_APP_EN == 1)   
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {
            printf("AT+INFO=SD Init, OK\r\n");
        }
        else
        {           
            printf("AT+ERROR=SD Init, ERROR\r\n");  
        } 
    }
    #endif  
}
#endif


/***********************************************************************************
* Function: DAC_APPInit;
*
* Description: DAC应用初始化函数;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
#if ((DAC1_EN|DAC2_EN)>0)
void  DAC_APPInit(void)  // DAC应用初始化函数;
{    
    DAC_PARA DACPara;
    INT32S flag;
    
    #if (DAC1_EN==1)
        DACPara.Flag = 0;
        DACPara.pin = DAC1_PIN;
        DACPara.Mode = DAC1_MODE;    
        #if (DAC1_MODE > 0) 
        DACPara.Freq = DAC1_FREQ;
        DACPara.pbuf = DAC1_Buffer;
        DACPara.len = DAC1_TXBUF_SIZE;
        #endif
        flag = DAC_Init(DAC1_ID, (DAC_PARA *)&DACPara.Flag);   
        #if (DEBUG_APP_EN == 1)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            if (flag == ERR_TRUE)
            {
                printf("AT+INFO=DAC1 Init, OK\r\n");  
            }
            else
            {
                printf("AT+ERROR=DAC1 Init, ERROR, %d\r\n", flag);  
            } 
        }
        #endif
	#endif
    

    #if (DAC2_EN==1)
        DACPara.Flag = 0;
        DACPara.pin = DAC2_PIN;
        DACPara.Mode = DAC2_MODE; 
        #if (DAC2_MODE > 0) 
        DACPara.Freq = DAC2_FREQ;
        DACPara.pbuf = DAC2_Buffer;
        DACPara.len = DAC2_TXBUF_SIZE;
        #endif 
        flag = DAC_Init(DAC2_ID, (DAC_PARA *)&DACPara.Flag);
        #if (DEBUG_APP_EN == 1)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            if (flag == ERR_TRUE)
            {
                printf("AT+INFO=DAC2 Init, OK\r\n");  
            }
            else
            {
                printf("AT+ERROR=DAC2 Init, ERROR, %d\r\n", flag);  
            } 
        }
        #endif      
	#endif					
}
#endif

/***********************************************************************************
* Function: ADC_APPInit;
*
* Description: ADC应用初始化函数;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
#if (ADC_EN>0)
void  ADC_APPInit(void)  // ADC应用初始化函数;
{    
    ADC_PARA ADCPara;
    INT8U n;
    INT32S flag;
    
    ADCPara.Mode = 0;                        // 无定义, 默认0
    ADCPara.Flag = 0; 
    // 选择AD输出方式
    #if (ADC_OUT_TYPE == ADC_ISROUT)  // 判断是中断输出AD采样值
    ADCPara.Flag |= ADC_ISROUT_FLAG;  
    #else
    ADCPara.Flag &= ~ADC_ISROUT_FLAG; // 选择ADC_Read()函数读取采样值
    #endif
    #if ((MODULE_CLASS == STM32F107XX)||(MODULE_CLASS == STM32F103XX))
    ADCPara.Flag |= ADC_TIM5;         // 必须设置TIM5作为AD采样定时器 
    #endif
    #if (MODULE_CLASS == STM32F407XX)
    ADCPara.Flag |= ADC_TIM14;        // 必须设置TIM14作为AD采样定时器 
    #endif
    
    ADCPara.AINum = ADC_CHNUM;
    ADCPara.AvgNum = ADC_AVGNUM;
    ADCPara.Freq = ADC_FREQ;                 // AD采样频率, 每秒钟采样次数
    ADCPara.SampleTime = ADC_SAMPLE_TIME;    // ADC采样转换时间
    ADCPara.pBuf = (INT16S *)&ADC_Buffer[0][0];
    //ADCPara.isr = ADC_ISRHook;     
    ADCPara.pAITab = AITab;
    
    // 以下设置AI1-AI10采集顺序, 初始化采集顺序表
    for (n=0; n<16; n++) // 默认必须初始化成0xFF;
    {
        AITab[n] = AI_ID_NONE; // AI_ID_NONE就是0xFF 
    }
    
    #if (AI1_EN == 1)   // 判断AI1使能
    AITab[AI1_ID] = AI1; // 设置采集AI1顺序
    #endif
    #if (AI2_EN == 1)   // 判断AI2使能
    AITab[AI2_ID] = AI2;     // 设置采集AI2顺序
    #endif
    #if (AI3_EN == 1)   // 判断AI3使能
    AITab[AI3_ID] = AI3;     // 设置采集AI3顺序
    #endif
    #if (AI4_EN == 1)   // 判断AI4使能
    AITab[AI4_ID] = AI4;     // 设置采集AI4顺序
    #endif
    #if (AI5_EN == 1)   // 判断AI5使能
    AITab[AI5_ID] = AI5;     // 设置采集AI5顺序
    #endif
    #if (AI6_EN == 1)   // 判断AI6使能
    AITab[AI6_ID] = AI6;     // 设置采集AI6顺序
    #endif
    #if (AI7_EN == 1)   // 判断AI7使能
    AITab[AI7_ID] = AI7;     // 设置采集AI7顺序
    #endif
    #if (AI8_EN == 1)   // 判断AI8使能
    AITab[AI8_ID] = AI8;     // 设置采集AI8顺序
    #endif
    #if (AI9_EN == 1)   // 判断AI9使能
    AITab[AI9_ID] = AI9;     // 设置采集AI9顺序
    #endif
    #if (AI10_EN == 1)  // 判断AI10使能
    AITab[AI10_ID] = AI10;    // 设置采集AI10顺序
    #endif
    
    flag = ADC_Init(ADC1_ID, (ADC_PARA *)&ADCPara.Flag);
    #if (DEBUG_APP_EN == 1)
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {
            printf("AT+INFO=ADC1 Init,OK\r\n");   
        }
        else
        {
            printf("AT+ERROR=ADC1 Init, ERROR, %d\r\n", flag);  
        } 
    }
    #endif    
}
#endif

/***********************************************************************************
* Function: USBH_APPInit;
*
* Description: USB主机模式应用初始化函数;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
#if ((USB_HOST_EN > 0)&&(MODULE_CLASS != STM32F103XX))
void USBH_APPInit(void)
{
    USBH_PARA Para;
    INT32S flag;
	    
    Para.Flag = 0;
    #if (UDISK_EN > 0)
    Para.Mode = USBHOST_MSC_MODE;   // 配置U盘操作模式
    #endif
    Para.Pin.CPWR = USB_PWR;
    Para.Pin.DM = USB_DM;
    Para.Pin.DP = USB_DP;
    Para.Pin.VBUS = USB_VBUS; 
    
    flag = USBH_Init(USB_ID, (USBH_PARA *)&Para.Flag);
    #if (DEBUG_APP_EN == 1)
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {               
            printf("AT+INFO=USBH Init, OK\r\n");              
        }
        else
        {
            printf("AT+ERROR=USBH Init, ERROR\r\n"); 
        } 
    }
    #endif 
}
#endif

/***********************************************************************************
* Function: USBD_APPInit;
*
* Description: USB设备模式应用初始化函数;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
#if (USB_DEVICE_EN > 0)
void USBD_APPInit(void)
{
    USBD_PARA Para;
    INT32S flag;
	    
    Para.Flag = 0;
    #if (USB_MSC_EN > 0)
    Para.Mode = USB_DEVICE_MSC_MODE;  // USB Mass Storage模式
    Para.lun = USB_MSC_LUN;
    #endif
    
    #if (USB_VCP_EN > 0)
    Para.Mode = USB_DEVICE_CDC_MODE;  // 虚拟串口模式
    Para.pRxBuf = USB_RxBuffer;       // 接收数据缓存指针
    Para.RxBufLen = USB_RXBUF_SIZE;   // 接收缓存长度
    #endif
    
    Para.Pin.DM = USB_DM;
    Para.Pin.DP = USB_DP;
    Para.Pin.VBUS = USB_VBUS; 
    
    #ifdef USB_CTRL
    IO_Init(USB_CTRL, IO_OUT_PP, IO_SPEED_2MHz); // 通用推挽输出模式
	IO_Write(USB_CTRL, 1);
    #endif
    
    flag = USBD_Init(USB_ID, (USBD_PARA *)&Para.Flag);
    #if (DEBUG_APP_EN == 1)
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {               
            printf("AT+INFO=USBD Init, OK\r\n");              
        }
        else
        {
            printf("AT+ERROR=USBD Init, ERROR\r\n"); 
        } 
    }
    #endif     
}
#endif


/***********************************************************************************
* Function: SysLib_APPInit;
*
* Description: 系统驱动库应用初始化函数;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
void SysLib_APPInit(void)
{
    SYSLIB_PARA SysLibPara;
    
    SysLibPara.Flag = 0;
    
    SysLibPara.Flag |= SYS_CLK_HSE_FLAG; // 使用外部晶振
    
    #if (UCOS_II_EN > 0)         //UCOS_II使能 
    SysLibPara.Flag |= SYS_OS_FLAG;
    #endif    
    
    #if (IAP_EN > 0)             // IAP功能使能
	SysLibPara.Flag |= SYS_NVIC_VECTORTAB_FLAG;
    SysLibPara.VectorTableAddr = NVIC_VECTOR_TABLE_ADDR;
    #else
    SysLibPara.VectorTableAddr = 0;
    #endif
        
    #if (SYS_TICK_EN > 0)        // 系统定时器使能
	SysLibPara.Flag |= SYS_TICK_FLAG;
    #endif
    
    #if (DEBUG_SD_EN > 0)        // 驱动库SD卡调试输出使能
    SysLibPara.Flag |= SYS_DEBUG_SD_FLAG;
    #endif        
    
    #if (DEBUG_USB_EN > 0)       // 驱动库USB调试输出使能
    SysLibPara.Flag |= SYS_DEBUG_USB_FLAG;
    #endif          
    
    #if (DEBUG_NFLASH_EN > 0)       // 驱动库NFlash调试输出使能
    SysLibPara.Flag |= SYS_DEBUG_NFLASH_FLAG;
    #endif          
    
    #if (DEBUG_LIB_EN > 0)       // 驱动库其它调试输出使能
    SysLibPara.Flag |= SYS_DEBUG_LIB_FLAG;
    #endif          
    
    SysLibPara.Flag |=  SYS_DEBUG_MODBUS_FLAG; // 驱动库MODBUS调试输出标志 
    //SysLibPara.Flag |= SYS_DEBUG_NET_FLAG;  // 驱动库网络调试输出标志 
    
    SysLibPara.ModuleType = MODULE_TYPE;    // 设置模块类型
    SysLibPara.OscClk = SYSCLK_HSE;         // 设置外部时钟晶振频率
    SysLibPara.SysClk = SYSCLK;             // 设置系统时钟频率
    SysLibPara.Tick   = SYS_TICK_T;         // 设置系统定时器定时时间
    SysLibPara.DebugUart = DEBUG_UART;      // 设置选择printf函数输出Uart
    
    SysLib_Init((SYSLIB_PARA *)&SysLibPara.Flag);   

    #if (DEBUG_APP_EN == 1)
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
         printf("AT+INFO=SysLib Init, OK\r\n");               
    }
    #endif 
    
    //SysLib_Ctrl(CMD_MCO1, MCO_OUT_ENA|MCO1_HSE|MCO_DIV5);
}

/***********************************************************************************
* Function: ModbusSlave_APPInit;
*
* Description: Modbus从机(设备)模式应用初始化函数;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
#if (MODBUS_SLAVE_EN > 0) // Modbus设备模式使能
void ModbusSlave_APPInit(void)
{
    INT16U i;
    
    #if (MODBUS_SLAVE_MODE == 0)           // MODBUS从机通信模式：0, RTU;  1, ASCII码; 
    ModbusPara.Flag = MODBUS_RTU_FLAG;     // RTU通信模式
    #else
    ModbusPara.Flag = MODBUS_ASCII_FLAG    // ASCII通信模式
    #endif

    ModbusPara.CoilsBaseAddr = MODBUS_COILS_BASEADDR;           // 线圈寄存器基地址;
    ModbusPara.DisInputBaseAddr = MODBUS_DISINPUT_BASEADDR;     // 离散输入量寄存器基地址;
    ModbusPara.HoldRegBaseAddr = MODBUS_HOLDREG_BASEADDR;       // 保持寄存器基地址;
    ModbusPara.InputRegBaseAddr = MODBUS_INPUTREG_BASEADDR;     // 输入寄存器基地址;    
    ModbusPara.MaxCoils = MODBUS_MAX_COILS;                     // MODBUS从机最大线圈数量(读写,可用功能码:1,5,15);
    ModbusPara.MaxDisInput = MODBUS_MAX_DISINPUT;               // MODBUS从机最大离散输入量(只读,可用功能码:2);
    ModbusPara.MaxHoldReg = MODBUS_MAX_HOLDREG;                 // MODBUS从机最大保持寄存器(读写,可用功能码:3,6,16,23)数量;	 
    ModbusPara.MaxInputReg = MODBUS_MAX_INPUTREG;               // MODBUS从机最大输入寄存器(只读,可用功能码:4)数量;
    
    ModbusPara.pCoils = ModbusCoils;           // 输出线圈寄存器指针
    ModbusPara.pDisInput = ModbusDisInput;     // 输入离散输入量寄存器指针
    ModbusPara.pHoldReg = ModbusHoldReg;       // 保持寄存器指针
    ModbusPara.pInputReg = ModbusInputReg;     // 输入寄存器指针
    
    ModbusPara.pData = (MODBUS_DATA *)&ModbusData.Flag;       // 操作缓存指针     
    
    // 初始化输出线圈数组
    for (i=0; i<((MODBUS_MAX_COILS-1)/8 + 1); i++)  
    {
        ModbusPara.pCoils[i] = 0;
    }
    
    // 初始化输入离散输入量数组
    for (i=0; i<((MODBUS_MAX_DISINPUT-1)/8 + 1); i++)
    {
        ModbusPara.pDisInput[i] = 0;
    }
    
    // 初始化保持寄存器
    for (i=0; i<MODBUS_MAX_HOLDREG; i++)
    {
        ModbusPara.pHoldReg[i] = 0;
    }
    
    // 初始化输入寄存器
    for (i=0; i<MODBUS_MAX_INPUTREG; i++)
    {
        ModbusPara.pInputReg[i] = 0;
    }    
    #if (DEBUG_APP_EN == 1)
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
         printf("AT+INFO=MODBUS Init, OK\r\n");               
    }
    #endif
}
#endif

/***********************************************************************************
* Function: IAP_APPInit;
*
* Description: IAP模式应用初始化函数;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
#if (IAP_EN > 0) // IAP模式使能
void IAP_APPInit(void)
{
    INT32S flag, i;
    IAP_PARA Para;
    
	Para.Flag = 0;
    Para.Flag |= IAP_YMODEM_FLAG|IAP_DEBUG_FLAG; // 启动时支持超级终端Ymodem协议及BOOT程序调试输出;
    
	#if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F107XX))
		#if ((DEBUG_UART == UART1_ID)&&(UART1_REMAP == UART_REMAP_1))
		Para.Flag |= IAP_UART_REMAP1_FLAG; // IAP串口管脚REMAP1标志
		#endif
	
		#if ((DEBUG_UART == UART2_ID)&&(UART2_REMAP == UART_REMAP_1))
		Para.Flag |= IAP_UART_REMAP1_FLAG; // IAP串口管脚REMAP1标志 
		#endif
	
		#if (DEBUG_UART == UART3_ID)
			#if (UART3_REMAP == UART_REMAP_1)
			Para.Flag |= IAP_UART_REMAP1_FLAG; // IAP串口管脚REMAP1标志 
			#endif
			#if (UART3_REMAP == UART_REMAP_2)
			Para.Flag |= IAP_UART_REMAP2_FLAG; // IAP串口管脚REMAP2标志 
			#endif
		#endif
    #endif
	
	#if (DEBUG_UART == UART1_ID)
	Para.Baud = UART1_BAUD;
	#endif
	#if (DEBUG_UART == UART2_ID)
	Para.Baud = UART2_BAUD;
	#endif
	#if (DEBUG_UART == UART3_ID)
	Para.Baud = UART3_BAUD;
	#endif
	#if (DEBUG_UART == UART4_ID)
	Para.Baud = UART4_BAUD;		
	#endif	
	#if (DEBUG_UART == UART5_ID)
	Para.Baud = UART5_BAUD;		
	#endif	
	#if (DEBUG_UART == UART6_ID)
	Para.Baud = UART6_BAUD;		
	#endif		
	
    Para.Moduel = MODULE_TYPE;              // 设置模块类型
    Para.HSEClk = SYSCLK_HSE; 
    Para.UartID = DEBUG_UART;    // 串口ID, Debug信息输出串口选择    
    Para.ABPageSize = IAP_AB_PAGESIZE; // 设置A/B/AB区页大小    
    Para.BootPin = IO_NONE;
    for (i=0; i<12; i++)
    {    
        Para.FileName[i] = 0;
    }
    
    // A区初始化
	Para.Area[IAP_A_ID].StartPage = IAP_A_STARTPAGE;
    Para.Area[IAP_A_ID].PageNum   = IAP_A_PAGENUM;

    // B区初始化
	Para.Area[IAP_B_ID].StartPage = IAP_B_STARTPAGE;
    Para.Area[IAP_B_ID].PageNum   = IAP_B_PAGENUM;

    // AB区初始化
	Para.Area[IAP_AB_ID].StartPage = IAP_AB_STARTPAGE;
    Para.Area[IAP_AB_ID].PageNum   = IAP_AB_PAGENUM;

    // C区初始化
    #if (SPIFLASH_TYPE == W25QXX)
	Para.CPageSize = IAP_C_W25QXX_PAGESIZE;                  // 设置C区页大小
    Para.Area[IAP_C_ID].StartPage = IAP_C_W25QXX_STARTPAGE;
    Para.Area[IAP_C_ID].PageNum   = IAP_C_W25QXX_PAGENUM;
    #endif
    #if (SPIFLASH_TYPE == AT45DBXX)
    Para.CPageSize = IAP_C_AT45DBXX_PAGESIZE;                  // 设置C区页大小
	Para.Area[IAP_C_ID].StartPage = IAP_C_AT45DBXX_STARTPAGE;
    Para.Area[IAP_C_ID].PageNum   = IAP_C_AT45DBXX_PAGENUM;
    #endif
    
    flag = IAP_Init((IAP_PARA *)&Para.Flag);
    #if (DEBUG_APP_EN == 1)
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {           
            printf("AT+INFO=IAP Init, OK\r\n");  
        }
        else
        {
            printf("AT+ERROR=IAP Init, ERROR\r\n");  
        }
    }
    #endif 
}
#endif

/***********************************************************************************
* Function: FSMC_APPInit;
*
* Description: FSMC总线初始化函数;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
#if (FSMC_EN > 0)       // FSMC总线使能
void FSMC_APPInit(void) // FSMC总线初始化
{
    FSMC_PARA Para;
    INT32S flag;
    
    Para.Flag = 0;
    #if (SRAM_EN >0 )
    Para.Flag |= FSMC_SRAM_EN; // 总线扩展RAM使能标志
    #endif
    
    #if (EXBUS_EN >0 )
    Para.Flag |= FSMC_EXBUS_EN;// 总线扩展引出使能标志
    #endif
    
    #if (NFLASH_EN >0 )
        Para.Flag |= FSMC_NFLASH_EN; // 总线扩展NAND使能标志
        #if (NFLASH_ECCEN >0 )
        Para.Flag |= FSMC_NFLASH_ECCEN; // Nand flash ECC使能标志
        #endif
        #if (NFLASH_RBIT_EN >0 )         // RB信号中断使能
        Para.Flag |= FSMC_NFLASH_ITFLAG; // Nand flash 中断产生标志
        #endif
    #endif
    
    #if (LWIP_EN >0 )
    Para.Flag |= FSMC_NET_EN;  // 总线扩展NET使能标志
    #endif
    
    Para.ECCSize = NFLASH_ECC_SIZE;    // Nand Flash ECC页面大小
    Para.SRAMSize = SRAM_SIZE;         // 扩展SRAM容量;
    Para.EXBusAddrSet = EXBUS_ADDSET;  // 外部总线地址建立时间(范围：0~15)：实际建立时间(EXBUS_ADDSET+1)个HCLK;
    Para.EXBusDataSet = EXBUS_DATAST;  // 外部总线数据保持时间(范围：1~255)：实际保持时间：读(EXBUS_DATAST+3)个HCLK, 写(DATAST+1)个HCLK;
    Para.EXBusTurn = EXBUS_TURN;       // 外部总线恢复时间(范围：0~15)：实际恢复时间(EXBUS_TURN+1)个HCLK
      
    flag = FSMC_Init((FSMC_PARA *)&Para.Flag);
    #if (DEBUG_APP_EN == 1)
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {           
            printf("AT+INFO=FSMC Init, OK\r\n");  
        }
        else
        {
            printf("AT+ERROR=FSMC Init, ERROR\r\n");  
        }
    }
    #endif 
    
    flag = FSMC_Ctrl(CMD_FSMC_SRAM_TEST, 0);
    if (flag == ERR_TRUE)
    {           
        UserVars.OKFlag |= SRAM_OK_FLAG;
        #if (DEBUG_APP_EN == 1)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            printf("AT+INFO=SRAM Test, OK\r\n");  
        }
        #endif
    }    
    else
    {
        UserVars.OKFlag &= ~SRAM_OK_FLAG;
        #if (DEBUG_APP_EN == 1)
        if (UserVars.Para.ATFlag&AT_INFO_FLAG)
        {
            printf("AT+ERROR=SRAM Test, ERROR\r\n");  
        }
        #endif
    } 
}
#endif

/***********************************************************************************
* Function: NFlash_APPInit;
*
* Description: NAND FLASH应用初始化函数;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
#if (NFLASH_EN > 0)       // NAND FLASH使能
void NFlash_APPInit(void) // NAND FLASH应用初始化
{
    NFLASH_PARA Para;
    INT32S flag;
    INT8U *p;
    
    Para.Flag = 0;    
    //#if (NFLASH_ECCEN > 0) // ECC使能
    //Para.Flag |= NFLASH_ECCEN_FLAG; // 设置ECC使能标志
    //#endif
    //Para.ECCSize = NFLASH_ECC_SIZE;
    
    Para.BlkNum = NFLASH_BLOCK_NUM;       // NAND 总块数
    Para.PagePerBlk = NFLASH_BLOCK_SIZE;  // NAND 每个块包含页数 
    Para.PageSize = NFLASH_PAGE_SIZE;     // 页大小 
    Para.PageNum = NFLASH_BLOCK_NUM*NFLASH_BLOCK_SIZE;  // 总页数
    Para.BadBlkNum = NFLASH_MAX_BAD_BLOCK;              // 坏块总数
    Para.pBadBlkFlag = (INT8U *)&NFlashBadBlkFlag[0];   // 坏块标记指针
    Para.pBadTab = (INT16U *)&NFlashBadTab[0];	        // 坏块替换表指针
    Para.pBlkBuf = (INT8U *)&NFlashBlkBuffer[0][0];     // 块缓存指针
    
    //#if (NFLASH_ECCEN > 0) // ECC使能
    Para.pBlkSpareBuf = (INT8U *)&NFlashBlkSpareBuffer[0][0]; // 块空闲区域缓存指针
    //#else
    //Para.pBlkSpareBuf = 0;
    //#endif
    
    flag = NFlash_Init((NFLASH_PARA *)&Para.Flag);
    #if (DEBUG_APP_EN == 1)
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        if (flag == ERR_TRUE)
        {           
            printf("AT+INFO=NFLASH Init, OK\r\n");  
        }
        else
        {
            printf("AT+ERROR=NFLASH Init, ERROR\r\n");  
        }
    }
    #endif 
    
    p = (INT8U *)NFlash_Ctrl(CMD_NFLASH_RDID, 0);           // 读取Nand Flash ID
    #if (DEBUG_APP_EN > 0)
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        printf("AT+INFO=NFLASH ID,%02X %02X %02X %02X %02X\r\n", p[0],p[1],p[2],p[3],p[4]);
    }
    #endif
    
//    flag = NFlash_Ctrl(CMD_NFLASH_BADBLK, 0);  // 初始化Nand Flash坏块表
//    if (flag == ERR_FALSE)
//    {
//        #if (DEBUG_APP_EN > 0)
//        printf("NFlash: 坏块处理失败\r\n");
//        #endif
//    }
    //#endif
    
}
#endif

/***********************************************************************************
* Function: CH455_APPInit;
*
* Description: CH455应用初始化函数;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
#if (CH455_EN > 0)       // CH455使能
#include "CH455.h"
void CH455_APPInit(void) // CH455应用初始化
{
    INT32S flag;
    CH455_PARA CH455Para;
    
    CH455Para.Mode = CH455_MODE;    // 选择I2C模式
    CH455Para.INTPin = CH455_INT;
    CH455Para.SCLPin = CH455_SCL;
    CH455Para.SDAPin = CH455_SDA;
    CH455Para.I2C    = CH455_I2C;    
    
    CH455_Init(&CH455Para);  // 按键驱动芯片初始化
}
#endif

void Logo_Out(void)
{
	INT32S  ver;
	INT8U *p;
    
	#if (DEBUG_APP_EN == 1)
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        printf("\r\n\r\n******************************************************\r\n");
        printf("* Copyright (c), 2004-2020, 北京中嵌凌云电子有限公司\r\n");
        printf("*            All rights reserved.\r\n");
        printf("*\r\n");
        printf("* 设计人员: EmbedARM\r\n"); 
        printf("* 产品名称: %s\r\n", PRODUCT_NAME);        
        printf("* 产品型号: %s\r\n", PRODUCT_MODEL);
        printf("* 硬件版本: %d.%d%d\r\n", HW_VERSION/100, (HW_VERSION%100)/10, HW_VERSION%10);
        printf("* 软件版本: %d.%d%d\r\n", SW_VERSION/100, (SW_VERSION%100)/10, SW_VERSION%10);
        printf("* 固件名字: %s\r\n", BIN_NAME);
        printf("* 发布日期: %s\r\n", SW_DATE);

        ver = SysLib_Ctrl(CMD_SYSLIB_READ_VERSION, 0);      // 读取驱动库版本
        printf("*\r\n* 驱动库版本: %d.%d%d\r\n", ver/100, (ver%100)/10, ver%10);			
        p = (INT8U *)SysLib_Ctrl(CMD_SYSLIB_READ_DATE, 0);  // 读取驱动库生成日期
        printf("* 驱动库日期: %s\r\n", p);
        
        #if (UCOS_II_EN > 0)
        printf("*\r\n* 操作系统: UCOS-II V2.86\r\n");
        #else
        printf("*\r\n* 操作系统: 无\r\n");
        #endif
        printf("*\r\n* 本地IP和端口号: %d.%d.%d.%d, %d\r\n", UserVars.Para.LocalIP[0], UserVars.Para.LocalIP[1], UserVars.Para.LocalIP[2], UserVars.Para.LocalIP[3], UserVars.Para.LocalPort);
        printf("* 服务器IP和端口号: %d.%d.%d.%d, %d\r\n", UserVars.Para.DscIP[0], UserVars.Para.DscIP[1], UserVars.Para.DscIP[2], UserVars.Para.DscIP[3], UserVars.Para.DscPort);
        printf("* 网关IP: %d.%d.%d.%d\r\n", UserVars.Para.Gataway[0], UserVars.Para.Gataway[1], UserVars.Para.Gataway[2], UserVars.Para.Gataway[3]);
        printf("* MAC地址: %02X %02X %02X %02X %02X %02X\r\n", UserVars.Para.MACAddr[0], UserVars.Para.MACAddr[1], UserVars.Para.MACAddr[2], UserVars.Para.MACAddr[3], UserVars.Para.MACAddr[4], UserVars.Para.MACAddr[5]);
        
        printf("*\r\n* 公司邮箱: embedarm@126.com\r\n");
        printf("* 公司网址: www.embedarm.com\r\n");
        printf("*****************************************************\r\n");
    }
	#endif    
}

/***********************************************************************************
* Function: UserVars_Init;
*
* Description: 用户全局变量初始化函数;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
void UserVars_Init(void)
{
    INT16U i, n;
    
    UserVars.Flag = 0;          // 各种标志位
    UserVars.KeyVal = 0;        // 按键标识变量
    UserVars.Key = 0;           // 按键值
    //UserVars.DIVal = 0;         // DI输入标识变量
    UserVars.DI = 0;	        // DIN输入
    
    // TIM初始化
    #if (MODULE_CLASS == STM32F107XX)
    n = 7;  
    #endif
    #if (MODULE_CLASS == STM32F103XX)
    n = 8;
    #endif
    #if (MODULE_CLASS == STM32F407XX)
    n = 14;
    #endif
    for(i=0; i<n; i++)
    {
        UserVars.TIMx_ITFlag[i] = 0;   // TIMx中断标志
    }
    
    UserVars.DO = 0;	        // DOUT输出
	//UserVars.Status = 0;   	    // 系统状态
	UserVars.TaskRunStatus = 0; // 操作系统任务运行状态 
    UserVars.TimerCount = 0;
    
    //UserVars.Para.ATFlag = 0xffff;  // 使能所有调试信息输出
}

/***********************************************************************************
* Function: DMA_APPInit;
*
* Description: DMA_APPInit应用初始化函数;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
#if ((DMA1_EN > 0)||(DMA2_EN > 0)) // DMA1-DMA2配置使能
void DMA_APPInit(void)             // DMA1-DMA2应用初始化函数;	
{
    DMA_INIT DMAInit;
    INT16U i;
    
    DMAInit.Flag = 0;
    
#if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F107XX))
    
    // DMA1CH1
    #if (DMA1CH1_EN > 0)
    DMAInit.Flag |= DMACH1_FLAG;
    DMAInit.ChPara[DMA_CH1] = DMA1CH1_PARA|DMA_IT_TERR;// |DMA_IT_HT;
    #endif
    
    // DMA1CH2
    #if (DMA1CH2_EN > 0)
    DMAInit.Flag |= DMACH2_FLAG;
    DMAInit.ChPara[DMA_CH2] = DMA1CH2_PARA|DMA_IT_TERR;// |DMA_IT_HT;
    #endif

    // DMA1CH3
    #if (DMA1CH3_EN > 0)
    DMAInit.Flag |= DMACH3_FLAG;
    DMAInit.ChPara[DMA_CH3] = DMA1CH3_PARA|DMA_IT_TERR;// |DMA_IT_HT;
    #endif

    // DMA1CH4
    #if (DMA1CH4_EN > 0)
    DMAInit.Flag |= DMACH4_FLAG;
    DMAInit.ChPara[DMA_CH4] = DMA1CH4_PARA|DMA_IT_TERR;// |DMA_IT_HT;
    #endif

    // DMA1CH5
    #if (DMA1CH5_EN > 0)
    DMAInit.Flag |= DMACH5_FLAG;
    DMAInit.ChPara[DMA_CH5] = DMA1CH5_PARA|DMA_IT_TERR;// |DMA_IT_HT;
    #endif

    // DMA1CH6
    #if (DMA1CH6_EN > 0)
    DMAInit.Flag |= DMACH6_FLAG;
    DMAInit.ChPara[DMA_CH6] = DMA1CH6_PARA|DMA_IT_TERR;// |DMA_IT_HT;
    #endif

    // DMA1CH7
    #if (DMA1CH7_EN > 0)
    DMAInit.Flag |= DMACH7_FLAG;
    DMAInit.ChPara[DMA_CH7] = DMA1CH7_PARA|DMA_IT_TERR;// |DMA_IT_HT;
    #endif
    DMAInit.pISRHook = DMA1_ISRHook;
    DMA_Init(DMA1_ID, &DMAInit);
    
    // DMA2CH1
    #if (DMA2CH1_EN > 0)
    DMAInit.Flag |= DMACH1_FLAG;
    DMAInit.ChPara[DMA_CH1] = DMA2CH1_PARA|DMA_IT_TERR;// |DMA_IT_HT;
    #endif
    
    // DMA2CH2
    #if (DMA2CH2_EN > 0)
    DMAInit.Flag |= DMACH2_FLAG;
    DMAInit.ChPara[DMA_CH2] = DMA2CH2_PARA|DMA_IT_TERR;// |DMA_IT_HT;
    #endif

    // DMA2CH3
    #if (DMA2CH3_EN > 0)
    DMAInit.Flag |= DMACH3_FLAG;
    DMAInit.ChPara[DMA_CH3] = DMA2CH3_PARA|DMA_IT_TERR;// |DMA_IT_HT;
    #endif

    // DMA2CH4
    #if (DMA2CH4_EN > 0)
    DMAInit.Flag |= DMACH4_FLAG;
    DMAInit.ChPara[DMA_CH4] = DMA2CH4_PARA|DMA_IT_TERR;// |DMA_IT_HT;
    #endif

    // DMA2CH5
    #if (DMA2CH5_EN > 0)
    DMAInit.Flag |= DMACH5_FLAG;
    DMAInit.ChPara[DMA_CH5] = DMA2CH5_PARA|DMA_IT_TERR;// |DMA_IT_HT;
    #endif

    DMAInit.pISRHook = DMA2_ISRHook;
    DMA_Init(DMA2_ID, &DMAInit);    
#endif

#if (MODULE_CLASS == STM32F407XX)
    // DMA1CH1
    #if (DMA1CH1_EN > 0)
    DMAInit.Flag |= DMACH1_FLAG;
    DMAInit.ChPara[DMA_CH1] = DMA1CH1_PARA|DMA_IT_TERR|DMA_IT_FIFOERR|DMA_IT_DERR;// |DMA_IT_HT;
    #endif
    
    // DMA1CH2
    #if (DMA1CH2_EN > 0)
    DMAInit.Flag |= DMACH2_FLAG;
    DMAInit.ChPara[DMA_CH2] = DMA1CH2_PARA|DMA_IT_TERR|DMA_IT_FIFOERR|DMA_IT_DERR;// |DMA_IT_HT;
    #endif

    // DMA1CH3
    #if (DMA1CH3_EN > 0)
    DMAInit.Flag |= DMACH3_FLAG;
    DMAInit.ChPara[DMA_CH3] = DMA1CH3_PARA|DMA_IT_TERR|DMA_IT_FIFOERR|DMA_IT_DERR;// |DMA_IT_HT;
    #endif

    // DMA1CH4
    #if (DMA1CH4_EN > 0)
    DMAInit.Flag |= DMACH4_FLAG;
    DMAInit.ChPara[DMA_CH4] = DMA1CH4_PARA|DMA_IT_TERR|DMA_IT_FIFOERR|DMA_IT_DERR;// |DMA_IT_HT;
    #endif

    // DMA1CH5
    #if (DMA1CH5_EN > 0)
    DMAInit.Flag |= DMACH5_FLAG;
    DMAInit.ChPara[DMA_CH5] = DMA1CH5_PARA|DMA_IT_TERR|DMA_IT_FIFOERR|DMA_IT_DERR;// |DMA_IT_HT;
    #endif

    // DMA1CH6
    #if (DMA1CH6_EN > 0)
    DMAInit.Flag |= DMACH6_FLAG;
    DMAInit.ChPara[DMA_CH6] = DMA1CH6_PARA|DMA_IT_TERR|DMA_IT_FIFOERR|DMA_IT_DERR;// |DMA_IT_HT;
    #endif

    // DMA1CH7
    #if (DMA1CH7_EN > 0)
    DMAInit.Flag |= DMACH7_FLAG;
    DMAInit.ChPara[DMA_CH7] = DMA1CH7_PARA|DMA_IT_TERR|DMA_IT_FIFOERR|DMA_IT_DERR;// |DMA_IT_HT;
    #endif

    // DMA1CH8
    #if (DMA1CH8_EN > 0)
    DMAInit.Flag |= DMACH8_FLAG;
    DMAInit.ChPara[DMA_CH8] = DMA1CH8_PARA|DMA_IT_TERR|DMA_IT_FIFOERR|DMA_IT_DERR;// |DMA_IT_HT;
    #endif
    
    DMAInit.pISRHook = DMA1_ISRHook;
    DMA_Init(DMA1_ID, &DMAInit);
    
    // DMA2CH1
    #if (DMA2CH1_EN > 0)
    DMAInit.Flag |= DMACH1_FLAG;
    DMAInit.ChPara[DMA_CH1] = DMA2CH1_PARA|DMA_IT_TERR|DMA_IT_FIFOERR|DMA_IT_DERR;// |DMA_IT_HT;
    #endif
    
    // DMA2CH2
    #if (DMA2CH2_EN > 0)
    DMAInit.Flag |= DMACH2_FLAG;
    DMAInit.ChPara[DMA_CH2] = DMA2CH2_PARA|DMA_IT_TERR|DMA_IT_FIFOERR|DMA_IT_DERR;// |DMA_IT_HT;
    #endif

    // DMA2CH3
    #if (DMA2CH3_EN > 0)
    DMAInit.Flag |= DMACH3_FLAG;
    DMAInit.ChPara[DMA_CH3] = DMA2CH3_PARA|DMA_IT_TERR|DMA_IT_FIFOERR|DMA_IT_DERR;// |DMA_IT_HT;
    #endif

    // DMA2CH4
    #if (DMA2CH4_EN > 0)
    DMAInit.Flag |= DMACH4_FLAG;
    DMAInit.ChPara[DMA_CH4] = DMA2CH4_PARA|DMA_IT_TERR|DMA_IT_FIFOERR|DMA_IT_DERR;// |DMA_IT_HT;
    #endif

    // DMA2CH5
    #if (DMA2CH5_EN > 0)
    DMAInit.Flag |= DMACH5_FLAG;
    DMAInit.ChPara[DMA_CH5] = DMA2CH5_PARA|DMA_IT_TERR|DMA_IT_FIFOERR|DMA_IT_DERR;// |DMA_IT_HT;
    #endif

    // DMA2CH6
    #if (DMA2CH6_EN > 0)
    DMAInit.Flag |= DMACH6_FLAG;
    DMAInit.ChPara[DMA_CH6] = DMA2CH6_PARA|DMA_IT_TERR|DMA_IT_FIFOERR|DMA_IT_DERR;// |DMA_IT_HT;
    #endif
 
    // DMA2CH7
    #if (DMA2CH7_EN > 0)
    DMAInit.Flag |= DMACH7_FLAG;
    DMAInit.ChPara[DMA_CH7] = DMA2CH7_PARA|DMA_IT_TERR|DMA_IT_FIFOERR|DMA_IT_DERR;// |DMA_IT_HT;
    #endif

    // DMA2CH8
    #if (DMA2CH8_EN > 0)
    DMAInit.Flag |= DMACH8_FLAG;
    DMAInit.ChPara[DMA_CH8] = DMA2CH8_PARA|DMA_IT_TERR|DMA_IT_FIFOERR|DMA_IT_DERR;// |DMA_IT_HT;
    #endif
    
    DMAInit.pISRHook = DMA2_ISRHook;
    DMA_Init(DMA2_ID, &DMAInit);    
#endif
}
#endif

/***********************************************************************************
* Function: API_Init;
*
* Description: 驱动库初始化函数;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
void  API_Init (void)
{   
    SysLib_APPInit();    // 系统驱动库应用初始化函数;
    
    #if (IWDG_EN > 0)           // IWDG配置使能
    IWDG_Init(IWDG_TIME);       // 初始化看门狗时间
	IWDG_Ctrl(CMD_IWDG_ENA);    // 使能看门狗
   	IWDG_Ctrl(CMD_IWDG_CLEAR);  // 喂狗
    #endif
    
    #if ((DMA1_EN > 0)||(DMA2_EN > 0)) // DMA1-DMA2配置使能
    DMA_APPInit();      // DMA1-DMA2应用初始化函数;	
    #endif
        
    UserVars_Init();     // 用户全局变量初始化
    EEPROM_APPInit();    // EEPROM应用初始化函数;   
    APP_ParaRead((USER_VARS *)&UserVars.Flag); // 读取用户参数
    
    #if ((UART1_EN > 0)||(UART2_EN > 0)||(UART3_EN > 0)||(UART4_EN > 0)||(UART5_EN > 0)||(UART6_EN > 0)) // UART1-UART6配置使能
    Uart_APPInit();      // UART1-UART6应用初始化函数;	
    #endif    
    
    Logo_Out();          // 软件logo打印输出
        
    #if ((I2C2_EN > 0)||(I2C3_EN > 0)) // I2C2-I2C3配置使能
    I2C_APPInit();      // I2C2-I2C3应用初始化函数;	
    #endif    

    #if (IAP_EN > 0)    // IAP配置使能
    IAP_APPInit();      // IAP应用初始化
    #endif

    #if (IWDG_EN > 0)           // IWDG配置使能
   	IWDG_Ctrl(CMD_IWDG_CLEAR);  // 喂狗
    #endif

    IO_APPInit();      // 所有IO初始化
	EXTI_APPInit();    // 外部中断和事件应用初始化   
    
    #if (BKP_EN > 0)   // BKP配置使能
    BKP_Init();        // BKP应用初始化
    #endif

    #if (MODBUS_SLAVE_EN > 0)   // Modbus设备模式配置使能
    ModbusSlave_APPInit();      //Modbus从机(设备)模式应用初始化函数;
    #endif

    #if (IWDG_EN > 0)           // IWDG配置使能
   	IWDG_Ctrl(CMD_IWDG_CLEAR);  // 喂狗
    #endif

    #if (RTC_EN > 0)            // RTC配置使能
    RTC_APPInit();              // RTC应用初始化函数;
    #endif

    #if ((SPI1_EN > 0)||(SPI2_EN > 0)||(SPI3_EN > 0)) // SPI1~SPI3配置使能
    SPI_APPInit();	            // SPI总线应用初始化
    #endif
     
    #if (ADC_EN>0)              // ADC配置使能
    ADC_APPInit();              // ADC应用初始化函数;
    #endif 
    
    #if ((DAC1_EN>0)||(DAC2_EN>0)) // DAC1-2配置使能
    DAC_APPInit();                 // DAC应用初始化
    #endif
    
    #if ((TIM1_EN > 0)||(TIM2_EN > 0)||(TIM3_EN > 0)||(TIM4_EN > 0)||(TIM5_EN > 0)||(TIM6_EN > 0)||(TIM7_EN > 0)||(TIM8_EN > 0)  \
    ||(TIM9_EN > 0)||(TIM10_EN > 0)||(TIM11_EN > 0)||(TIM12_EN > 0)||(TIM13_EN > 0)||(TIM14_EN > 0)) //TIM1-TIM14配置使能
    TIM_APPInit();     // 定时器应用初始化
    #endif
    
    #if ((FCLK1_EN>0)||(FCLK2_EN>0)||(FCLK3_EN>0)||(FCLK4_EN>0)||(FCLK5_EN>0)||(FCLK6_EN>0)||(FCLK7_EN>0)||(FCLK8_EN>0)) //FCLK1-FCLK8配置使能
    FCLK_APPInit();    // FCLK输入应用初始化
    #endif
    
    #if ((PWM1_EN>0)||(PWM2_EN>0)||(PWM3_EN>0)||(PWM4_EN>0)||(PWM5_EN>0)||(PWM6_EN>0)||(PWM7_EN>0)||(PWM8_EN>0)) //PWM1-PWM8配置使能
    PWM_APPInit();     // PWM输出应用初始化
    #endif
    
    #if ((CAN1_EN>0)||(CAN2_EN>0)) // CAN1-2配置使能
    CAN_APPInit();                 // CAN1-2应用初始化
	#endif
    
    #if (SPIFLASH_EN > 0)   // SPI FLASH配置使能
    SPIFlash_APPInit();     // SPI Flash(W25QXX或AT45DBXX)应用初始化
    #endif
   
    
    #if (SDCARD_EN > 0)     // SD卡配置使能
    SD_APPInit();           // SD卡应用初始化
    #endif
    
    #if (IWDG_EN > 0)           // IWDG配置使能
   	IWDG_Ctrl(CMD_IWDG_CLEAR);  // 喂狗
    #endif

    #if ((USB_HOST_EN > 0)&&(MODULE_CLASS != STM32F103XX)) // USB主机模式配置使能
    USBH_APPInit();         // USB主机模式应用初始化
    #endif
    
    #if (USB_DEVICE_EN > 0) // USB设备模式配置使能
    USBD_APPInit();         // USB设备模式应用初始化
    #endif
    
    #if (FSMC_EN > 0)       // FSMC总线配置使能
    FSMC_APPInit();         // FSMC总线初始化
    #endif
            
    #if (NFLASH_EN > 0)     // NAND FLASH配置使能
    NFlash_APPInit();       // NAND FLASH应用初始化
    #endif
                        
	#if ((LWIP_EN >0)&&((MODULE_CLASS == STM32F107XX)||(MODULE_CLASS == STM32F407XX))) // 网络配置使能
	NET_APPInit();	        // 网络配置使能
    #endif
    
    #if (CH455_EN > 0)      // CH455配置使能
    CH455_APPInit();       // CH455应用初始化
    #endif
}


/***********************************************************************************/
// 文件结束
/***********************************************************************************/
