/************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: APP_Init.c
* Project  : STM32F1XX/4XXϵ��ģ�����
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.00
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: ���ļ���Ӧ�ó���������ĳ�ʼ������, ����Conifg.h������ý��г�ʼ��
*
* Others: �ο�API_Init()����;
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
// �����ⲿͷ�ļ�
/************************************************************************************/
#include "config.h"
#include "vars.h"
#include "UserVars.h"
#include "STM32Fxxx.h"

/************************************************************************************/
// ������ȫ�ֱ�������
/************************************************************************************/
// оƬ��ƷΨһ��ݱ�ʶ�Ĵ���(96λ)  
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
    
    p->Para.Flag = SPIFLASH_FORMAT_FLAG|NFLASH_FORMAT_FLAG|AT_DEBUG_FLAG;   	// ��־
	p->Para.ModbusID = 1; 	            	// Modbus ID
	
    #ifdef LWIP_EN
    p->Para.NetType = LWIP_NETYPE;
    p->Para.NetMode = LWIP_WKMODE;
    StrToIP(p->Para.LocalIP, (INT8U *)LOCAL_IP);
    StrToIP(p->Para.SubnetMask, (INT8U *)LOCAL_SUBNET_MASK);
    StrToIP(p->Para.Gataway, (INT8U *)LOCAL_GATEWAY);
    StrToIP(p->Para.DscIP, (INT8U *)DSC_IP);
    p->Para.LocalPort = LOCAL_PORT;      // �����˿�
    p->Para.DscPort = DSC_PORT;          // �������˿�        
    #endif
    
    pID = (MCU_ID_TypeDef *)SysLib_Ctrl(CMD_SYSLIB_READ_MCUID, 0);
    
    p->Para.MACAddr[0] = 0;              //6 ����MAC��ַ
    p->Para.MACAddr[1] = 2;
    p->Para.MACAddr[2] = pID->ID3 + pID->ID9;
    p->Para.MACAddr[3] = pID->ID4 + pID->ID10;
    p->Para.MACAddr[4] = pID->ID5 + pID->ID11;
    p->Para.MACAddr[5] = pID->ID6 + pID->ID12;  
    
    
    p->Para.ATFlag = 0xffff;  // ʹ�����е�����Ϣ���
    
    p->Para.AI.Mode = 0;
    p->Para.AI.t1 = 100;
    p->Para.AI.t2 = 3000;

    p->Para.AO.Mode = 0;
    p->Para.AO.val = 1000;  // Ĭ��ÿ������1000mV(0-10����)
    p->Para.AO.t = 3000;    // Ĭ��������3��

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
        printf("AT+ERROR=APP_ParaRead, ��ȡ���ò���ʧ��,����Ĭ�ϲ���\r\n");
    }
    
    #if (LWIP_CONFIG_EN > 0)        // �����ò�����������
    StrToIP(Vars->Para.LocalIP, (INT8U *)LOCAL_IP);
    StrToIP(Vars->Para.SubnetMask, (INT8U *)LOCAL_SUBNET_MASK);
    StrToIP(Vars->Para.Gataway, (INT8U *)LOCAL_GATEWAY);
    StrToIP(Vars->Para.DscIP, (INT8U *)DSC_IP);
    Vars->Para.LocalPort = LOCAL_PORT;      // �����˿�
    Vars->Para.DscPort = DSC_PORT;          // �������˿�        
    #endif

    return flag;    
}

/***********************************************************************************
* Function: IO_APPInit;
*
* Description: ����Ӧ��IO��ʼ������;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   ����ݰ����ͺų�ʼ��IO;
************************************************************************************/
void IO_APPInit(void)
{
    
// ����K1-K8 IO��ʼ��, ���ø�������(�ⲿ�����Ѿ�����������)  
    #ifdef K1
    IO_Init(K1, IO_IN_FLOATING, IO_INPUT);  // ����K1
    #endif
    #ifdef K2
    IO_Init(K2, IO_IN_FLOATING, IO_INPUT);  // ����K2
	#endif
    #ifdef K3    
    IO_Init(K3, IO_IN_FLOATING, IO_INPUT);  // ����K3
	#endif
    #ifdef K4
    IO_Init(K4, IO_IN_FLOATING, IO_INPUT);  // ����K4
    #endif
    #ifdef K5
    IO_Init(K5, IO_IN_FLOATING, IO_INPUT);  // ����K5
    #endif
    #ifdef K6
    IO_Init(K6, IO_IN_FLOATING, IO_INPUT);  // ����K6
    #endif
    #ifdef K7
    IO_Init(K7, IO_IN_FLOATING, IO_INPUT);  // ����K7
    #endif
    #ifdef K8
    IO_Init(K8, IO_IN_FLOATING, IO_INPUT);  // ����K8
    #endif
    
// DI1-DI8��ʼ��
    #ifdef DI1
    IO_Init(DI1, IO_IN_IPU, IO_INPUT);  // ����DI1
	#endif
    #ifdef DI2
    IO_Init(DI2, IO_IN_IPU, IO_INPUT);  // ����DI2
	#endif
    #ifdef DI3
    IO_Init(DI3, IO_IN_IPU, IO_INPUT);  // ����DI3
	#endif
    #ifdef DI4
    IO_Init(DI4, IO_IN_IPU, IO_INPUT);  // ����DI4
	#endif
    #ifdef DI5
    IO_Init(DI5, IO_IN_IPU, IO_INPUT);  // ����DI5
    #endif
    #ifdef DI6
    IO_Init(DI6, IO_IN_IPU, IO_INPUT);  // ����DI6
    #endif
    #ifdef DI7
    IO_Init(DI7, IO_IN_IPU, IO_INPUT);  // ����DI6
    #endif
    #ifdef DI8
    IO_Init(DI8, IO_IN_IPU, IO_INPUT);  // ����DI6
    #endif

// DI9-DI16��ʼ��
    #ifdef DI9
    IO_Init(DI9, IO_IN_IPU, IO_INPUT);  // ����DI9
	#endif
    #ifdef DI10
    IO_Init(DI10, IO_IN_IPU, IO_INPUT);  // ����DI10
	#endif
    #ifdef DI11
    IO_Init(DI11, IO_IN_IPU, IO_INPUT);  // ����DI11
	#endif
    #ifdef DI12
    IO_Init(DI12, IO_IN_IPU, IO_INPUT);  // ����DI12
	#endif
    #ifdef DI13
    IO_Init(DI13, IO_IN_IPU, IO_INPUT);  // ����DI13
    #endif
    #ifdef DI14
    IO_Init(DI14, IO_IN_IPU, IO_INPUT);  // ����DI14
    #endif
    #ifdef DI15
    IO_Init(DI15, IO_IN_IPU, IO_INPUT);  // ����DI15
    #endif
    #ifdef DI16
    IO_Init(DI16, IO_IN_IPU, IO_INPUT);  // ����DI16
    #endif
    
// DO1-DO8��ʼ�� 
    #ifdef DO1
	#ifdef DO_OUT_PP
	IO_Init(DO1, IO_OUT_PP, IO_SPEED_2MHz);  // ���DO1
	IO_Write(DO1, 0);
	#else
	IO_Init(DO1, IO_OUT_OD, IO_SPEED_2MHz);  // ���DO1
	IO_Write(DO1, 1);
	#endif
	#endif
    
    #ifdef DO2
	#ifdef DO_OUT_PP
	IO_Init(DO2, IO_OUT_PP, IO_SPEED_2MHz);  // ���DO2
	IO_Write(DO2, 0);
	#else
	IO_Init(DO2, IO_OUT_OD, IO_SPEED_2MHz);  // ���DO2
	IO_Write(DO2, 1);
	#endif
	#endif
	
	#ifdef DO3
	#ifdef DO_OUT_PP
	IO_Init(DO3, IO_OUT_PP, IO_SPEED_2MHz);  // ���DO3
	IO_Write(DO3, 0);
	#else
	IO_Init(DO3, IO_OUT_OD, IO_SPEED_2MHz);  // ���DO3
	IO_Write(DO3, 1);
	#endif
	#endif
	
	#ifdef DO4
	#ifdef DO_OUT_PP
	IO_Init(DO4, IO_OUT_PP, IO_SPEED_2MHz);  // ���DO4
	IO_Write(DO4, 0);
	#else
	IO_Init(DO4, IO_OUT_OD, IO_SPEED_2MHz);  // ���DO4
	IO_Write(DO4, 1);
	#endif
	#endif
	
	#ifdef DO5
	#ifdef DO_OUT_PP
	IO_Init(DO5, IO_OUT_PP, IO_SPEED_2MHz);  // ���DO5
	IO_Write(DO5, 0);
	#else
	IO_Init(DO5, IO_OUT_OD, IO_SPEED_2MHz);  // ���DO5
	IO_Write(DO5, 1);
	#endif
	#endif
	
	#ifdef DO6
	#ifdef DO_OUT_PP
	IO_Init(DO6, IO_OUT_PP, IO_SPEED_2MHz);  // ���DO6
	IO_Write(DO6, 0);
	#else
	IO_Init(DO6, IO_OUT_OD, IO_SPEED_2MHz);  // ���DO6
	IO_Write(DO6, 1);
	#endif
	#endif
    
	#ifdef DO7
	#ifdef DO_OUT_PP
	IO_Init(DO7, IO_OUT_PP, IO_SPEED_2MHz);  // ���DO7
	IO_Write(DO7, 0);
	#else
	IO_Init(DO7, IO_OUT_OD, IO_SPEED_2MHz);  // ���DO7
	IO_Write(DO7, 1);
	#endif
	#endif
	
	#ifdef DO8
	#ifdef DO_OUT_PP
	IO_Init(DO8, IO_OUT_PP, IO_SPEED_2MHz);  // ���DO8
	IO_Write(DO8, 0);
	#else
	IO_Init(DO8, IO_OUT_OD, IO_SPEED_2MHz);  // ���DO8
	IO_Write(DO8, 1);
	#endif
	#endif
	
// DO9-DO16��ʼ�� 
  #ifdef DO9
	#ifdef DO_OUT_PP
	IO_Init(DO9, IO_OUT_PP, IO_SPEED_2MHz);  // ���DO9
	IO_Write(DO9, 0);
	#else
	IO_Init(DO9, IO_OUT_OD, IO_SPEED_2MHz);  // ���DO9
	IO_Write(DO9, 1);
	#endif
	#endif
    
    #ifdef DO10
	#ifdef DO_OUT_PP
	IO_Init(DO10, IO_OUT_PP, IO_SPEED_2MHz);  // ���DO10
	IO_Write(DO10, 0);
	#else
	IO_Init(DO10, IO_OUT_OD, IO_SPEED_2MHz);  // ���DO10
	IO_Write(DO10, 1);
	#endif
	#endif
	
	#ifdef DO11
	#ifdef DO_OUT_PP
	IO_Init(DO11, IO_OUT_PP, IO_SPEED_2MHz);  // ���DO11
	IO_Write(DO11, 0);
	#else
	IO_Init(DO11, IO_OUT_OD, IO_SPEED_2MHz);  // ���DO11
	IO_Write(DO11, 1);
	#endif
	#endif
	
	#ifdef DO12
	#ifdef DO_OUT_PP
	IO_Init(DO12, IO_OUT_PP, IO_SPEED_2MHz);  // ���DO12
	IO_Write(DO12, 0);
	#else
	IO_Init(DO12, IO_OUT_OD, IO_SPEED_2MHz);  // ���DO12
	IO_Write(DO12, 1);
	#endif
	#endif
	
	#ifdef DO13
	#ifdef DO_OUT_PP
	IO_Init(DO13, IO_OUT_PP, IO_SPEED_2MHz);  // ���DO13
	IO_Write(DO13, 0);
	#else
	IO_Init(DO13, IO_OUT_OD, IO_SPEED_2MHz);  // ���DO13
	IO_Write(DO13, 1);
	#endif
	#endif
	
	#ifdef DO14
	#ifdef DO_OUT_PP
	IO_Init(DO14, IO_OUT_PP, IO_SPEED_2MHz);  // ���DO14
	IO_Write(DO14, 0);
	#else
	IO_Init(DO14, IO_OUT_OD, IO_SPEED_2MHz);  // ���DO14
	IO_Write(DO14, 1);
	#endif
	#endif
    
	#ifdef DO15
	#ifdef DO_OUT_PP
	IO_Init(DO15, IO_OUT_PP, IO_SPEED_2MHz);  // ���DO15
	IO_Write(DO15, 0);
	#else
	IO_Init(DO15, IO_OUT_OD, IO_SPEED_2MHz);  // ���DO15
	IO_Write(DO15, 1);
	#endif
	#endif
	
	#ifdef DO16
	#ifdef DO_OUT_PP
	IO_Init(DO16, IO_OUT_PP, IO_SPEED_2MHz);  // ���DO16
	IO_Write(DO16, 0);
	#else
	IO_Init(DO16, IO_OUT_OD, IO_SPEED_2MHz);  // ���DO16
	IO_Write(DO16, 1);
	#endif
	#endif
    
	#ifdef DO17
	#ifdef DO_OUT_PP
	IO_Init(DO17, IO_OUT_PP, IO_SPEED_2MHz);  // ���DO17
	IO_Write(DO17, 0);
	#else
	IO_Init(DO17, IO_OUT_OD, IO_SPEED_2MHz);  // ���DO17
	IO_Write(DO17, 1);
	#endif
	#endif

	#ifdef DO18
	#ifdef DO_OUT_PP
	IO_Init(DO18, IO_OUT_PP, IO_SPEED_2MHz);  // ���DO18
	IO_Write(DO18, 0);
	#else
	IO_Init(DO18, IO_OUT_OD, IO_SPEED_2MHz);  // ���DO18
	IO_Write(DO18, 1);
	#endif
	#endif

	#ifdef DO19
	#ifdef DO_OUT_PP
	IO_Init(DO19, IO_OUT_PP, IO_SPEED_2MHz);  // ���DO19
	IO_Write(DO19, 0);
	#else
	IO_Init(DO19, IO_OUT_OD, IO_SPEED_2MHz);  // ���DO19
	IO_Write(DO19, 1);
	#endif
	#endif
    
	#ifdef DO20
	#ifdef DO_OUT_PP
	IO_Init(DO20, IO_OUT_PP, IO_SPEED_2MHz);  // ���DO20
	IO_Write(DO20, 0);
	#else
	IO_Init(DO20, IO_OUT_OD, IO_SPEED_2MHz);  // ���DO20
	IO_Write(DO20, 1);
	#endif
	#endif    
    
	#ifdef DO21
	#ifdef DO_OUT_PP
	IO_Init(DO21, IO_OUT_PP, IO_SPEED_2MHz);  // ���DO21
	IO_Write(DO21, 0);
	#else
	IO_Init(DO21, IO_OUT_OD, IO_SPEED_2MHz);  // ���DO21
	IO_Write(DO21, 1);
	#endif
	#endif       

 // ���뿪��SW1-SW8��ʼ��
    #ifdef SW1
    IO_Init(SW1, IO_IN_IPU, IO_INPUT);  // ���뿪��SW1λ
    #endif 
    #ifdef SW2
    IO_Init(SW2, IO_IN_IPU, IO_INPUT);  // ���뿪��SW2λ
    #endif 
    #ifdef SW3
    IO_Init(SW3, IO_IN_IPU, IO_INPUT);  // ���뿪��SW3λ
    #endif 
    #ifdef SW4
    IO_Init(SW4, IO_IN_IPU, IO_INPUT);  // ���뿪��SW4λ
    #endif 
    #ifdef SW5
    IO_Init(SW5, IO_IN_IPU, IO_INPUT);  // ���뿪��SW5λ
    #endif 
    #ifdef SW6
    IO_Init(SW6, IO_IN_IPU, IO_INPUT);  // ���뿪��SW6λ
    #endif 
    #ifdef SW7
    IO_Init(SW7, IO_IN_IPU, IO_INPUT);  // ���뿪��SW7λ
    #endif 
    #ifdef SW8
    IO_Init(SW8, IO_IN_IPU, IO_INPUT);  // ���뿪��SW8λ
    #endif 
    
    // ������IO��ʼ��
    #ifdef RUN_LED    
	IO_Init(ALARM, IO_OUT_PP, IO_SPEED_2MHz); // ͨ���������ģʽ
	IO_Write(ALARM, 0);    
    #endif
    
    // ����LED IO��ʼ��  
    #ifdef RUN_LED
    IO_Init(RUN_LED, IO_OUT_PP, IO_SPEED_2MHz); // ͨ���������ģʽ
	IO_Write(RUN_LED, 0);
    #endif
        
    // HC595_STB��ʼ��
    #ifdef HC595_STB
    IO_Init(HC595_STB, IO_OUT_PP, IO_SPEED_2MHz);
    IO_Write(HC595_STB, 1);
    #endif
    
    // HC595_ENA��ʼ��
    #ifdef HC595_ENA
    IO_Init(HC595_ENA, IO_OUT_OD, IO_SPEED_2MHz);    
    IO_Write(HC595_ENA, 1);                          // ���ʹ�ܽ�ֹ
    #endif
    
    // HC597_STB��ʼ��
    #ifdef HC597_STB
    IO_Init(HC597_STB, IO_OUT_PP, IO_SPEED_2MHz); 
    IO_Write(HC597_STB, 1);
    #endif
    
    // HC597_LOAD��ʼ��
    #ifdef HC597_LOAD
    IO_Init(HC597_LOAD, IO_OUT_PP, IO_SPEED_2MHz); 
    IO_Write(HC597_LOAD, 1);
    #endif
    
    // HC597_CSƬѡ��ʼ��
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
    IO_Init(JP18_P5, IO_OUT_PP, IO_SPEED_2MHz);    // JP18 5��
    IO_Write(JP18_P5, 0);                          // ���0 
    #endif
    
    #ifdef  JP18_P7
    IO_Init(JP18_P7, IO_OUT_PP, IO_SPEED_2MHz);    // JP18 7��
    IO_Write(JP18_P7, 0);                          // ���0 
    #endif
    
    #ifdef  JP18_P8
    IO_Init(JP18_P8, IO_OUT_PP, IO_SPEED_2MHz);    // JP18 8��
    IO_Write(JP18_P8, 0);                          // ���0 
    #endif    
    #endif
    
    #ifdef  JP9_P1
    IO_Init(JP9_P1, IO_OUT_PP, IO_SPEED_2MHz);    // JP9 1��
    IO_Write(JP9_P1, 0);                          // ���0 
    #endif
}
					 

/***********************************************************************************
* Function: NET_APPInit;
*
* Description: ����Ӧ�ó�ʼ��;
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
* Description: �ⲿ�жϺ��¼�Ӧ�ó�ʼ������;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   ����������EXTI1~EXTI19 �����ж����ó�ʼ��;
************************************************************************************/
void EXTI_APPInit(void)    
{
    EXTI_PARA Para;

    #if (EXTI0_EN > 0)
    Para.id   = EXTI0_ID;
    Para.Mode = EXTI0_MODE;
    Para.IOx  = EXTI0_IO;
    EXTI_Init((EXTI_PARA *)&Para);            // ��ʼ��EXTI0
    //EXTI_Ctrl(EXTI0_ID, EXTI0_EN);            // ����EXTI0�жϻ��¼�����
    #endif
    
    #if (EXTI1_EN > 0)
    Para.id   = EXTI1_ID;
    Para.Mode = EXTI1_MODE;
    Para.IOx  = EXTI1_IO;
    EXTI_Init((EXTI_PARA *)&Para);            // ��ʼ��EXTI1
    EXTI_Ctrl(EXTI1_ID, EXTI1_EN);            // ����EXTI1�жϻ��¼�����
    #endif
    
    #if (EXTI2_EN > 0)
    Para.id   = EXTI2_ID;
    Para.Mode = EXTI2_MODE;
    Para.IOx  = EXTI2_IO;
    EXTI_Init((EXTI_PARA *)&Para);            // ��ʼ��EXTI2
    EXTI_Ctrl(EXTI2_ID, EXTI2_EN);            // ����EXTI2�жϻ��¼�����
    #endif
    
    #if (EXTI3_EN > 0)
    Para.id   = EXTI3_ID;
    Para.Mode = EXTI3_MODE;
    Para.IOx  = EXTI3_IO;
    EXTI_Init((EXTI_PARA *)&Para);            // ��ʼ��EXTI3
    EXTI_Ctrl(EXTI3_ID, EXTI3_EN);            // ����EXTI3�жϻ��¼�����
    #endif
    
    #if (EXTI4_EN > 0)
    Para.id   = EXTI4_ID;
    Para.Mode = EXTI4_MODE;
    Para.IOx  = EXTI4_IO;
    EXTI_Init((EXTI_PARA *)&Para);            // ��ʼ��EXTI4
    EXTI_Ctrl(EXTI4_ID, EXTI4_EN);            // ����EXTI4�жϻ��¼�����
    #endif
    
    #if (EXTI5_EN > 0)
    Para.id   = EXTI5_ID;
    Para.Mode = EXTI5_MODE;
    Para.IOx  = EXTI5_IO;
    EXTI_Init((EXTI_PARA *)&Para);            // ��ʼ��EXTI5
    EXTI_Ctrl(EXTI5_ID, EXTI5_EN);            // ����EXTI5�жϻ��¼�����
    #endif
    
    #if (EXTI6_EN > 0)
    Para.id   = EXTI6_ID;
    Para.Mode = EXTI6_MODE;
    Para.IOx  = EXTI6_IO;
    EXTI_Init((EXTI_PARA *)&Para);            // ��ʼ��EXTI6
    EXTI_Ctrl(EXTI6_ID, EXTI6_EN);            // ����XTI6�жϻ��¼�����
    #endif
    #if (EXTI7_EN > 0)
    Para.id   = EXTI7_ID;
    Para.Mode = EXTI7_MODE;
    Para.IOx  = EXTI7_IO;
    EXTI_Init((EXTI_PARA *)&Para);            // ��ʼ��EXTI7
    EXTI_Ctrl(EXTI7_ID, EXTI7_EN);            // ����EXTI7�жϻ��¼�����
    #endif
    
    #if (EXTI8_EN > 0)
    Para.id   = EXTI8_ID;
    Para.Mode = EXTI8_MODE;
    Para.IOx  = EXTI8_IO;
    EXTI_Init((EXTI_PARA *)&Para);            // ��ʼ��EXTI8
    EXTI_Ctrl(EXTI8_ID, EXTI8_EN);            // ����EXTI8�жϻ��¼�����
    #endif
    
    #if (EXTI9_EN > 0)
    Para.id   = EXTI9_ID;
    Para.Mode = EXTI9_MODE;
    Para.IOx  = EXTI9_IO;
    EXTI_Init((EXTI_PARA *)&Para);            // ��ʼ��EXTI9
    EXTI_Ctrl(EXTI9_ID, EXTI9_EN);            // ����EXTI9�жϻ��¼�����
    #endif
    
    #if (EXTI10_EN > 0)
    Para.id   = EXTI10_ID;
    Para.Mode = EXTI10_MODE;
    Para.IOx  = EXTI10_IO;
    EXTI_Init((EXTI_PARA *)&Para);            // ��ʼ��EXTI10
    EXTI_Ctrl(EXTI10_ID, EXTI10_EN);          // ����EXTI10�жϻ��¼�����
    #endif
    
    #if (EXTI11_EN > 0)
    Para.id   = EXTI11_ID;
    Para.Mode = EXTI11_MODE;
    Para.IOx  = EXTI11_IO;
    EXTI_Init((EXTI_PARA *)&Para);            // ��ʼ��EXTI11
    EXTI_Ctrl(EXTI11_ID, EXTI11_EN);          // ����EXTI11�жϻ��¼�����
    #endif
    
    #if (EXTI12_EN > 0)
    Para.id   = EXTI12_ID;
    Para.Mode = EXTI12_MODE;
    Para.IOx  = EXTI12_IO;
    EXTI_Init((EXTI_PARA *)&Para);            // ��ʼ��EXTI12
    EXTI_Ctrl(EXTI12_ID, EXTI12_EN);          // ����EXTI12�жϻ��¼�����
    #endif
    
    #if (EXTI13_EN > 0)
    Para.id   = EXTI13_ID;
    Para.Mode = EXTI13_MODE;
    Para.IOx  = EXTI13_IO;
    EXTI_Init((EXTI_PARA *)&Para);            // ��ʼ��EXTI13
    EXTI_Ctrl(EXTI13_ID, EXTI13_EN);          // ����EXTI13�жϻ��¼�����
    #endif
    
    #if (EXTI14_EN > 0)
    Para.id   = EXTI14_ID;
    Para.Mode = EXTI14_MODE;
    Para.IOx  = EXTI14_IO;
    EXTI_Init((EXTI_PARA *)&Para);            // ��ʼ��EXTI14
    EXTI_Ctrl(EXTI14_ID, EXTI14_EN);          // ����EXTI14�жϻ��¼�����
    #endif
    
    #if (EXTI15_EN > 0)
    Para.id   = EXTI15_ID;
    Para.Mode = EXTI15_MODE;
    Para.IOx  = EXTI15_IO;
    EXTI_Init((EXTI_PARA *)&Para);            // ��ʼ��EXTI15
    EXTI_Ctrl(EXTI15_ID, EXTI15_EN);          // ����EXTI15�жϻ��¼�����
    #endif    

    #if (EXTI16_PVD_EN > 0)
    Para.id   = EXTI16_PVD_ID;
    Para.Mode = EXTI16_PVD_MODE;
    Para.IOx  = IO_NONE;
    EXTI_Init((EXTI_PARA *)&Para);            // ��ʼ��EXTI16_PVD
    EXTI_Ctrl(EXTI16_PVD_ID, EXTI16_PVD_EN);  // ����EXTI16_PVD�жϻ��¼�����
    #endif    
    
    #if (EXTI17_RTCAlarm_EN > 0)
    Para.id   = EXTI17_RTCAlarm_ID;
    Para.Mode = EXTI17_RTCAlarm_MODE;
    Para.IOx  = IO_NONE;
    EXTI_Init((EXTI_PARA *)&Para);                      // ��ʼ��EXTI17_RTCAlarm
    EXTI_Ctrl(EXTI17_RTCAlarm_ID, EXTI17_RTCAlarm_EN);  // ����EXTI17_RTCAlarm�жϻ��¼�����
    #endif    

    #if (EXTI18_USBWakeUp_EN > 0)
    Para.id   = EXTI18_USBWakeUp_ID;
    Para.Mode = EXTI18_USBWakeUp_MODE;
    Para.IOx  = IO_NONE;
    EXTI_Init((EXTI_PARA *)&Para);                        // ��ʼ��EXTI18_USBWakeUp
    EXTI_Ctrl(EXTI18_USBWakeUp_ID, EXTI18_USBWakeUp_EN);  // ����EXTI18_USBWakeUp�жϻ��¼�����
    #endif  
    
    #if (EXTI19_NETWakeUp_EN > 0)
    Para.id   = EXTI19_NETWakeUp_ID;
    Para.Mode = EXTI19_NETWakeUp_MODE;
    Para.IOx  = IO_NONE;
    EXTI_Init((EXTI_PARA *)&Para);                        // ��ʼ��EXTI19_NETWakeUp
    EXTI_Ctrl(EXTI19_NETWakeUp_ID, EXTI19_NETWakeUp_EN);  // ����EXTI19_NETWakeUp�жϻ��¼�����
    #endif      
    
    #if (MODULE_CLASS == STM32F407XX)    
    
    #if (EXTI20_USBHSWakeUp_EN > 0)
    Para.id   = EXTI20_USBHSWakeUp_ID;
    Para.Mode = EXTI20_USBHSWakeUp_MODE;
    Para.IOx  = IO_NONE;
    EXTI_Init((EXTI_PARA *)&Para);                            // ��ʼ��EXTI20_USBHSWakeUp
    EXTI_Ctrl(EXTI20_USBHSWakeUp_ID, EXTI20_USBHSWakeUp_EN);  // ����EXTI20_USBHSWakeUp�жϻ��¼�����
    #endif      
    
    #if (EXTI21_RTCTSE_EN > 0)
    Para.id   = EXTI21_RTCTSE_ID;
    Para.Mode = EXTI21_RTCTSE_MODE;
    Para.IOx  = IO_NONE;
    EXTI_Init((EXTI_PARA *)&Para);                        // ��ʼ��EXTI21_RTCTSE
    EXTI_Ctrl(EXTI21_RTCTSE_ID, EXTI21_RTCTSE_EN);        // ����EXTI21_RTCTSE�жϻ��¼�����
    #endif  

    #if (EXTI22_RTCWakeUp_EN > 0)
    Para.id   = EXTI22_RTCWakeUp_ID;
    Para.Mode = EXTI22_RTCWakeUp_MODE;
    Para.IOx  = IO_NONE;
    EXTI_Init((EXTI_PARA *)&Para);                        // ��ʼ��EXTI22_RTCWakeUp
    EXTI_Ctrl(EXTI22_RTCWakeUp_ID, EXTI22_RTCWakeUp_EN);  // ����EXTI22_RTCWakeUp�жϻ��¼�����
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
* Description: SPI1/SPI2/SPI3��ʼ������;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
#if ((I2C2_EN > 0)||(I2C3_EN > 0)) // I2C2-I2C3����ʹ��
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
* Description: SPI1/SPI2/SPI3��ʼ������;
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
    Para.Flag = 0;                       // ������־
    
    #if (SPI1TX_DMA_EN > 0)
    Para.Flag |= SPI_TXDMA_FLAG;  // ����SPI1TX DMAʹ�ܱ�־
    Para.TXDmaCh = SPI1TX_DMA_CH;
    Para.DmaID = SPI1_DMA_ID;
    #endif
    #if (SPI1RX_DMA_EN > 0)
    Para.Flag |= SPI_RXDMA_FLAG;  // ����SPI1RX DMAʹ�ܱ�־
    Para.RXDmaCh = SPI1RX_DMA_CH;
    Para.DmaID = SPI1_DMA_ID;
    #endif
    
    #if (SPI1_ISRHOOK_EN > 0)
    Para.Flag |= SPI1_ISRHOOK_FLAG;  // ����SPI1 ISRHOOKʹ�ܱ�־
    Para.pISRHook = SPI1_ISRHook;
    #else
    Para.pISRHook = 0;
    #endif
    
    //����SPI�ܽ�
    #if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F107XX))
	Para.Pin.Remap = SPI1_REMAP;         // SPI���Ź�����ӳ��
    #endif
    Para.Pin.NSS = SPI1_NSS;             // SPI1_NSS�ܽ�
    Para.Pin.SCK = SPI1_SCK;             // SPI1_SCK�ܽ�
    Para.Pin.MISO = SPI1_MISO;           // SPI1_MOSI�ܽ�
    Para.Pin.MOSI = SPI1_MOSI;           // SPI1_MISO�ܽ�

    // ��������
    // ���°�λ����
    /*
    Para.cfg.b.CPHA = 1;//SPI_CPHA_2Edge;   // ʱ����λ:  SPI_CPHA_1Edge��SPI_CPHA_2Edge
    Para.cfg.b.CPOL = 1;//SPI_CPOL_High;    // ʱ�Ӽ���:  SPI_CPOL_Low��SPI_CPOL_High
    Para.cfg.b.Mode = 1;//SPI_Mode_Master;  // �������豸ģʽѡ��: SPI_Mode_Master �� SPI_Mode_Slave
    Para.cfg.b.BaudRatePrescaler = 6;//SPI_BaudRatePrescaler_8; // ��Ƶϵ��: SPI_BaudRatePrescaler_2~SPI_BaudRatePrescaler_256
    Para.cfg.b.spe = 0;                 // SPIʹ��, ��ʼ��Ĭ��Ϊ0, �ر� 
    Para.cfg.b.Direction = SPI_FirstBit_MSB; // �ȷ��͸�λ�͵�λѡ��: SPI_FirstBit_MSB �� SPI_FirstBit_LSB
    Para.cfg.b.SSI = 0;                 // �ڲ����豸ѡ��, Ĭ��Ϊ0;
    Para.cfg.b.SSM = 0;                 // ������豸ѡ��, Ĭ��Ϊ0;
    Para.cfg.b.RxOnly = SPI_2Lines_FullDuplex;  // ֻ��������, Ĭ��Ϊ0(ȫ˫��)��SPI_2Lines_FullDuplex �� SPI_2Lines_RxOnly
    Para.cfg.b.DataSize = SPI_DataSize_8b;      // ����λ��ѡ��SPI_DataSize_16b �� SPI_DataSize_8b
    Para.cfg.b.CRCNext = 0;                     // ��һ������CRC, Ĭ��Ϊ0
    Para.cfg.b.CRCEN =0;                        // CRCУ��ʹ��, Ĭ��Ϊ0
    Para.cfg.b.BIDIOE = 0;                      // ˫��ģʽ�����ʹ��, Ĭ��Ϊ0: 0: �����ֹ(ֻ��ģʽ), 1:���ʹ��(ֻ��ģʽ)
    Para.cfg.b.BIDIMODE =0;                     // ˫������ģʽʹ��, Ĭ��0: 0: ѡ��˫��ģʽ, 1:ѡ����ģʽ
    */
    // Ҳ������������
    Para.cfg.reg = SPI1_CKMODE|SPI_Mode_Master|SPI1_DIVCLK|SPI_FirstBit_MSB|SPI_DataSize_8b|SPI_NSS_Soft;
    
    Para.CRCPolynomial = 7;       // Specifies the polynomial used for the CRC calculation.
    flag = SPI_Init(SPI1_ID, (SPI_PARA *)&Para.Flag);     // SPI1��ʼ��
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
    Para.Flag = 0;                   // ������־
    
    #if (SPI2TX_DMA_EN > 0)
    Para.Flag |= SPI_TXDMA_FLAG;  // ����SPI2TX DMAʹ�ܱ�־
    Para.TXDmaCh = SPI2TX_DMA_CH;
    Para.DmaID = SPI2_DMA_ID;    
    #endif
    #if (SPI2RX_DMA_EN > 0)
    Para.Flag |= SPI_RXDMA_FLAG;  // ����SPI2RX DMAʹ�ܱ�־
    Para.RXDmaCh = SPI2RX_DMA_CH;
    Para.DmaID = SPI2_DMA_ID;
    #endif
    #if (SPI2_ISRHOOK_EN > 0)
    Para.Flag |= SPI_ISRHOOK_FLAG;  // ����SPI2 ISRHOOKʹ�ܱ�־
    Para.pISRHook = SPI2_ISRHook;
    #else
    Para.pISRHook = 0;
    #endif
    
    //����SPI�ܽ�
    #if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F107XX))
	Para.Pin.Remap = SPI2_REMAP;     // SPI2���Ź�������ӳ��
    #endif
    Para.Pin.NSS = SPI2_NSS;         // SPI2_NSS�ܽ�
    Para.Pin.SCK = SPI2_SCK;         // SPI2_SCK�ܽ�
    Para.Pin.MISO = SPI2_MISO;       // SPI2_MOSI�ܽ�
    Para.Pin.MOSI = SPI2_MOSI;       // SPI2_MISO�ܽ�
    // ��������
    Para.cfg.reg =SPI2_CKMODE|SPI_Mode_Master|SPI2_DIVCLK|SPI_FirstBit_MSB|SPI_DataSize_8b;
    
    Para.CRCPolynomial = 7;       // Specifies the polynomial used for the CRC calculation.
    
    flag = SPI_Init(SPI2_ID, (SPI_PARA *)&Para.Flag);     // SPI2��ʼ��
    
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
    Para.Flag = 0;                    // ������־

    #if (SPI3TX_DMA_EN > 0)
    Para.Flag |= SPI_TXDMA_FLAG;  // ����SPI3TX DMAʹ�ܱ�־
    Para.TXDmaCh = SPI3TX_DMA_CH;
    Para.DmaID = SPI3_DMA_ID;
    #endif
    #if (SPI3RX_DMA_EN > 0)
    Para.Flag |= SPI_RXDMA_FLAG;  // ����SPI3RX DMAʹ�ܱ�־
    Para.RXDmaCh = SPI3RX_DMA_CH;
    Para.DmaID = SPI3_DMA_ID;
    #endif
    #if (SPI3_ISRHOOK_EN > 0)
    Para.Flag |= SPI_ISRHOOK_FLAG;  // ����SPI3 ISRHOOKʹ�ܱ�־
    Para.pISRHook = SPI3_ISRHook;
    #else
    Para.pISRHook = 0;
    #endif
    
    //����SPI�ܽ�
    #if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F107XX))
	Para.Pin.Remap = SPI3_REMAP;     // SPI3���Ź�����ӳ��
    #endif
    Para.Pin.NSS = SPI3_NSS;         // SPI3_NSS�ܽ�
    Para.Pin.SCK = SPI3_SCK;         // SPI3_SCK�ܽ�
    Para.Pin.MISO = SPI3_MISO;       // SPI3_MOSI�ܽ�
    Para.Pin.MOSI = SPI3_MOSI;       // SPI3_MISO�ܽ�
    // ��������
    Para.cfg.reg = SPI3_CKMODE|SPI_Mode_Master|SPI3_DIVCLK|SPI_FirstBit_MSB|SPI_DataSize_8b;
    
    Para.CRCPolynomial = 7;       // Specifies the polynomial used for the CRC calculation.
    
    flag = SPI_Init(SPI3_ID, (SPI_PARA *)&Para.Flag);     // SPI2��ʼ��
    
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
* Description: EEPROMӦ�ó�ʼ������;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
void  EEPROM_APPInit(void)  // EEPROMӦ�ó�ʼ������;
{    
	EEPROM_PARA EEPromPara;
    INT32S flag;
    
    EEPromPara.SDAPin = I2C1_SDA;            // I2C SDA�ܽ� 
    EEPromPara.SCLPin = I2C1_SCL;            // I2C SCL�ܽ� 
    
    EEPromPara.I2C_ID = I2C1_ID;              // ѡ��I2C�ӿ�����: I2C1_ID ����I2C2_ID 
    EEPromPara.I2CAddr = IIC_EEPROM_ADDR;     // ������ַ��ʶ
    EEPromPara.Freq = EEPROM_FREQ;            // ����EEPROM��дƵ��(��I2C��дƵ��)
    EEPromPara.Model = EEPROM_DEVICE;         // ���������ͺ�
    
	flag = EEPROM_Init((EEPROM_PARA *)&EEPromPara.Flag); // ��ʼ��EEPROM, ���������ʼ��I2C1
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
* Description: RTCӦ�ó�ʼ������;
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
#define RTC_PWROFF_FLAG  0x5AA5   // RTC�ϵ��־
#define RTC_BKP_ID       42       // RTC�ϵ��־�洢��BKP��λ��, ��Χ��1-42
void RTC_APPInit(void)
{
    INT16U RTCFlag;
    RTC_TIME rtc;
    INT32S flag;
    RTC_PARA Para;
    
    Para.Flag = 0;
    
    Para.Flag |= RTC_CLK_LSE_FLAG; 	          // �����ⲿ����ʱ�Ӿ���
    //Para.Flag |= RTC_CLK_LSI_FLAG;          // �����ڲ�����ʱ�Ӿ���
    //Para.Flag |= RTC_CLK_HSEDIV_FLAG;
    //Para.Flag |= RTC_CLK_LSEBYP_FLAG;       // RTCʱ��ѡ��LSE��Դʱ�ӱ�־,���1MHZ, �ڲ�������·LSE����
    
//    #if (MODULE_CLASS == STM32F407XX)
//        //Para.Flag |= RTC_CR_COE_EN|RTC_CR_COSEL_1HZ;     // ����PC13���������, ��ֻ��LSE��32768HZ����Ч
//        #if (RTC_ALR_EN > 0)            // RTC����ʹ��
//        Para.Flag |= RTC_CR_WUTE_EN;    // ʹ�ܻ��Ѷ�ʱ�� 
//        Para.Flag |= RTC_CR_WUTIE_EN;   // ʹ���ж�  
//        #endif
//        
//        #if ( RTC_ALRA_EN > 0)          // RTC����Aʹ��
//        Para.Flag |= RTC_CR_ALRAE_EN;   // ʹ������A 
//        Para.Flag |= RTC_CR_OSEL_A;     // ���ʹ��ѡ������A 
//        Para.Flag |= RTC_CR_ALRAIE_EN;  // ʹ���ж� 
//        #endif
//        
//        #if ( RTC_ALRB_EN > 0)          // RTC����Bʹ��
//        Para.Flag |= RTC_CR_ALRBE_EN;   // ʹ������B
//        Para.Flag |= RTC_CR_OSEL_B;     // ���ʹ��ѡ������B 
//        Para.Flag |= RTC_CR_ALRBIE_EN;  // ʹ���ж� 
//        #endif
//        
//        #if (RTC_TSF_EN  > 0)           // RTCʱ���ʹ��        
//        Para.Flag |= RTC_CR_TSE_EN;     // ʹ��ʱ���  
//        Para.Flag |= RTC_CR_TSIE_EN;    // ʹ���ж� 
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
    
    flag = RTC_Init((RTC_PARA *)&Para.Flag);     // RTC��ʼ��
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


    // ��ʼ��ʱ��
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
    BKP_Read(RTC_BKP_ID, &RTCFlag, 1);        // ��ȡRTCʱ�ӱ�־
	if (RTCFlag != RTC_PWROFF_FLAG)           // �ж��Ƿ�ϵ磬����ϵ����³�ʼ��ʱ��
	{
        RTC_Write(&rtc);  // �����µ�ʱ��
        RTCFlag = RTC_PWROFF_FLAG;            // ����ʱ���Ѿ�Уʱ��־
		BKP_Write(RTC_BKP_ID, &RTCFlag, 1);   // ���ó�ʼ��ʱ���־
	}
    #else
    RTC_Write(&rtc);  // �����µ�ʱ��
    #endif
    
#if (MODULE_CLASS == STM32F407XX)  
        #if (RTC_ALRA_EN > 0) // RTC����Aʹ��, ���1��
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
    #if (RTC_SECIT_EN > 0)  // RTC���ж�
    RTC_Ctrl(CMD_RTC_SECOND_INT, ENABLE, 0);
    #endif
    #if (RTC_ALRIT_EN > 0)  // RTC�����ж�
    RTC_Ctrl(CMD_RTC_ALARM_INT, ENABLE, 0);
    RTC_Ctrl(CMD_RTC_SET_ALMTIM_XS, 5, 0);   // ��������ʱ��, 5�����������ж�
    #if (DEBUG_APP_EN == 1)
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        printf("AT+INFO=RTC��������ʱ��, 5�����������ж�\r\n");
    }
    #endif
    #endif    
#endif    
    
    
}
#endif
/***********************************************************************************
* Function: Uart_APPInit;
*
* Description: UART1-UART5Ӧ�ó�ʼ������;
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
    
//---UART1��ʼ��-------------------------------------------------------
#if (UART1_EN > 0)   
    UartPara.Flag = 0;                      // ����Ϊ0
    #if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F107XX))
        #if (UART1_REMAP == UART_REMAP_1)       // ���ùܽ���ӳ��
        UartPara.Flag |= UART_REMAP1_FLAG;
        #endif
    #endif
    UartPara.TXPin = UART1_TX;              // ����TX�ܽ�
    UartPara.RXPin = UART1_RX;              // ����RX�ܽ�
    UartPara.RS485DirPin = UART1_DIR;       // ����RS485�������IO
    #if (UART1_DIR != IO_NONE)              // û��תRS485�ӿ�
    UartPara.Flag |= UART_RS485EN_FLAG;   // ����RS485�ӿڱ�־
    #if (UART1_DIR_HL == 1)                 // Ϊ1���øߵ�ƽ����, Ĭ�ϵ͵�ƽ����
    UartPara.Flag |= UART_RS485DIR_FLAG;  // DIR�ߵ�ƽ����
    #endif
    #endif    
    
    #if (UART1_WORD_LENGTH == UART_WORD_LENGTH_9B) // ��������λ��  
    UartPara.Flag |= UART_WORD_LENGTH_9BIT_FLAG;
    #endif
    #if (UART1_PARITY == UART_PARITY_EVEN)      // ����ż����
    UartPara.Flag |= UART_PARITY_EVEN_FLAG;
    #elif (UART1_PARITY == UART_PARITY_ODD)     // ���������
    UartPara.Flag |= UART_PARITY_ODD_FLAG;
    #endif    
    #if (UART1_STOP_BITS == UART_STOP_BITS_2)   // ����2λֹͣλ
    UartPara.Flag |= UART_STOP_BITS2_FLAG;
    #elif (UART1_PARITY == UART_STOP_BITS_0_5)  // ����0.5λֹͣλ
    UartPara.Flag |= UART_STOP_BITS0_5_FLAG;
    #elif (UART1_PARITY == UART_STOP_BITS_2)    // ����1.5λֹͣλ
    UartPara.Flag |= UART_STOP_BITS1_5_FLAG;
    #endif
    
    // ����������ż����λ��������λ����8bit, ʵ����Ч����λ��7bit���ʼ��ʱ���øñ�־
    #if ((UART1_PARITY > 0)&&(UART1_WORD_LENGTH == UART_WORD_LENGTH_8B))  
    UartPara.Flag |= UART_DATA_7BIT_FLAG;
    #endif   
    
    // ���ͺͽ���DMA����
    #if (UART1TX_DMA_EN > 0)
    UartPara.Flag |= UART_DMAREQ_TX_FLAG;   // ���÷���DMA
    #endif
    #if (UART1RX_DMAEN > 0)
    UartPara.Flag |= UART_DMAREQ_RX_FLAG;   // ���ý���DMA
    #endif
    
    //UartPara.Flag |= UART_HWFC_RTS_FLAG|UART_HWFC_CTS_FLAG; // ���ؼ�DMA����
    //UartPara.Flag |= UART_ISRHOOK_FLAG;   // ���õ��ô��ڽ��չ��Ӻ���, ���ڽ����������û���Uart1_ISRHook()�������Լ����ʵ��    
    
    UartPara.Mode = UART_AsynFD;             // ����ģʽ: ȫ˫���ģ��첽ͨ��
    UartPara.BaudRate = UART1_BAUD;          // ���ò�����
    
    UartPara.TxBufLen = UART1_TXBUF_SIZE;   // ���÷��ͻ��泤��
    UartPara.RxBufLen = UART1_RXBUF_SIZE;   // ���ý��ջ��泤��
    UartPara.pTxBuf = Uart1_TxBuffer;       // ���÷��ͻ���ָ��
    UartPara.pRxBuf = Uart1_RxBuffer;       // ���ý��ջ���ָ��    
    
    flag = Uart_Init(UART1_ID, (UART_PARA *)&UartPara.Flag); // ��ʼ��UART1
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

//---UART2��ʼ��-------------------------------------------------------
#if (UART2_EN > 0) 
    UartPara.Flag = 0;                    // ����Ϊ0
    #if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F107XX))
		#if (UART2_REMAP == UART_REMAP_1)     // ���ùܽ���ӳ��
        UartPara.Flag |= UART_REMAP1_FLAG;
        #endif
    #endif
    UartPara.TXPin = UART2_TX;              // ����TX�ܽ�
    UartPara.RXPin = UART2_RX;              // ����RX�ܽ�
    UartPara.RS485DirPin = UART2_DIR;       // ����RS485�������IO
    #if (UART2_DIR != IO_NONE)              // û��תRS485�ӿ�
    UartPara.Flag |= UART_RS485EN_FLAG;   // ����RS485�ӿڱ�־
    #if (UART2_DIR_HL == 1)                 // Ϊ1���øߵ�ƽ����, Ĭ�ϵ͵�ƽ����
    UartPara.Flag |= UART_RS485DIR_FLAG;  // DIR�ߵ�ƽ����
    #endif
    #endif
    #if (UART2_WORD_LENGTH == UART_WORD_LENGTH_9B) // ��������λ��  
    UartPara.Flag |= UART_WORD_LENGTH_9BIT_FLAG;
    #endif
    #if (UART2_PARITY == UART_PARITY_EVEN)      // ����ż����
    UartPara.Flag |= UART_PARITY_EVEN_FLAG;
    #elif (UART2_PARITY == UART_PARITY_ODD)     // ���������
    UartPara.Flag |= UART_PARITY_ODD_FLAG;
    #endif    
    #if (UART2_STOP_BITS == UART_STOP_BITS_2)   // ����2λֹͣλ
    UartPara.Flag |= UART_STOP_BITS2_FLAG;
    #elif (UART2_PARITY == UART_STOP_BITS_0_5)  // ����0.5λֹͣλ
    UartPara.Flag |= UART_STOP_BITS0_5_FLAG;
    #elif (UART2_PARITY == UART_STOP_BITS_2)    // ����1.5λֹͣλ
    UartPara.Flag |= UART_STOP_BITS1_5_FLAG;
    #endif    
    
    // ����������ż����λ��������λ����8bit, ʵ����Ч����λ��7bit���ʼ��ʱ���øñ�־
    #if ((UART2_PARITY > 0)&&(UART2_WORD_LENGTH == UART_WORD_LENGTH_8B))  
    UartPara.Flag |= UART_DATA_7BIT_FLAG;
    #endif
    
    // ���ͺͽ���DMA����
    #if (UART2TX_DMA_EN > 0)
    UartPara.Flag |= UART_DMAREQ_TX_FLAG;   // ���÷���DMA
    #endif
    #if (UART2RX_DMA_EN > 0)
    UartPara.Flag |= UART_DMAREQ_RX_FLAG;   // ���ý���DMA
    #endif
    
    //UartPara.Flag |= UART_HWFC_RTS_FLAG|UART_HWFC_CTS_FLAG; // ���ؼ�DMA����
    //UartPara.Flag |= UART_ISRHOOK_FLAG;    // ���õ��ô��ڽ��չ��Ӻ���, ���ڽ����������û���Uart2_ISRHook()�������Լ����ʵ��    
    
    UartPara.Mode = UART_AsynFD;             // ����ģʽ: ȫ˫���ģ��첽ͨ��
    UartPara.BaudRate = UART2_BAUD;          // ���ò�����

    UartPara.TxBufLen = UART2_TXBUF_SIZE;   // ���÷��ͻ��泤��
    UartPara.RxBufLen = UART2_RXBUF_SIZE;   // ���ý��ջ��泤��
    UartPara.pTxBuf = Uart2_TxBuffer;       // ���÷��ͻ���ָ��
    UartPara.pRxBuf = Uart2_RxBuffer;       // ���ý��ջ���ָ��    
   
    flag = Uart_Init(UART2_ID, (UART_PARA *)&UartPara.Flag); // ��ʼ��UART2
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
    
//---UART3��ʼ��-------------------------------------------------------
#if (UART3_EN > 0) 
    UartPara.Flag = 0;                    // ����Ϊ0
    #if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F107XX))
		#if (UART3_REMAP == UART_REMAP_1)     // ���ùܽ���ӳ��
        UartPara.Flag |= UART_REMAP1_FLAG;
        #elif (UART3_REMAP == UART_REMAP_2)   // ���ùܽ���ӳ��
        UartPara.Flag |= UART_REMAP2_FLAG;
        #endif 
    #endif
    
    UartPara.TXPin = UART3_TX;              // ����TX�ܽ�
    UartPara.RXPin = UART3_RX;              // ����RX�ܽ�
    UartPara.RS485DirPin = UART3_DIR;       // ����RS485�������IO
    #if (UART3_DIR != IO_NONE)              // û��תRS485�ӿ�
    UartPara.Flag |= UART_RS485EN_FLAG;   // ����RS485�ӿڱ�־
    #if (UART3_DIR_HL == 1)                 // Ϊ1���øߵ�ƽ����, Ĭ�ϵ͵�ƽ����
    UartPara.Flag |= UART_RS485DIR_FLAG;  // DIR�ߵ�ƽ����
    #endif
    #endif
    #if (UART3_WORD_LENGTH == UART_WORD_LENGTH_9B) // ��������λ��  
    UartPara.Flag |= UART_WORD_LENGTH_9BIT_FLAG;
    #endif
    #if (UART3_PARITY == UART_PARITY_EVEN)      // ����ż����
    UartPara.Flag |= UART_PARITY_EVEN_FLAG;
    #elif (UART3_PARITY == UART_PARITY_ODD)     // ���������
    UartPara.Flag |= UART_PARITY_ODD_FLAG;
    #endif    
    #if (UART3_STOP_BITS == UART_STOP_BITS_2)   // ����2λֹͣλ
    UartPara.Flag |= UART_STOP_BITS2_FLAG;
    #elif (UART3_PARITY == UART_STOP_BITS_0_5)  // ����0.5λֹͣλ
    UartPara.Flag |= UART_STOP_BITS0_5_FLAG;
    #elif (UART3_PARITY == UART_STOP_BITS_2)    // ����1.5λֹͣλ
    UartPara.Flag |= UART_STOP_BITS1_5_FLAG;
    #endif    
    
    // ����������ż����λ��������λ����8bit, ʵ����Ч����λ��7bit���ʼ��ʱ���øñ�־
    #if ((UART3_PARITY > 0)&&(UART3_WORD_LENGTH == UART_WORD_LENGTH_8B))  
    UartPara.Flag |= UART_DATA_7BIT_FLAG;
    #endif    
    
    // ���ͺͽ���DMA����
    #if (UART3TX_DMA_EN > 0)
    UartPara.Flag |= UART_DMAREQ_TX_FLAG;   // ���÷���DMA
    #endif
    #if (UART3RX_DMA_EN > 0)
    UartPara.Flag |= UART_DMAREQ_RX_FLAG;   // ���ý���DMA
    #endif
    
    //UartPara.Flag |= UART_HWFC_RTS_FLAG|UART_HWFC_CTS_FLAG; // ���ؼ�DMA����
    //UartPara.Flag |= UART_ISRHOOK_FLAG;   // ���õ��ô��ڽ��չ��Ӻ���, ���ڽ����������û���Uart3_ISRHook()�������Լ����ʵ��    
    
    UartPara.Mode = UART_AsynFD;             // ����ģʽ: ȫ˫���ģ��첽ͨ��
    UartPara.BaudRate = UART3_BAUD;          // ���ò�����
    
    UartPara.TxBufLen = UART3_TXBUF_SIZE;   // ���÷��ͻ��泤��
    UartPara.RxBufLen = UART3_RXBUF_SIZE;   // ���ý��ջ��泤��
    UartPara.pTxBuf = Uart3_TxBuffer;       // ���÷��ͻ���ָ��
    UartPara.pRxBuf = Uart3_RxBuffer;       // ���ý��ջ���ָ��    
  
    flag = Uart_Init(UART3_ID, (UART_PARA *)&UartPara.Flag); // ��ʼ��UART3
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

//---UART4��ʼ��-------------------------------------------------------
#if (UART4_EN > 0)     
    UartPara.Flag = 0;                    // ����Ϊ0
    UartPara.TXPin = UART4_TX;              // ����TX�ܽ�
    UartPara.RXPin = UART4_RX;              // ����RX�ܽ�
    UartPara.RS485DirPin = UART4_DIR;       // ����RS485�������IO
    #if (UART4_DIR != IO_NONE)              // û��תRS485�ӿ�
    UartPara.Flag |= UART_RS485EN_FLAG;   // ����RS485�ӿڱ�־
    #if (UART4_DIR_HL == 1)                 // Ϊ1���øߵ�ƽ����, Ĭ�ϵ͵�ƽ����
    UartPara.Flag |= UART_RS485DIR_FLAG;  // DIR�ߵ�ƽ����
    #endif
    #endif
    #if (UART4_WORD_LENGTH == UART_WORD_LENGTH_9B) // ��������λ��  
    UartPara.Flag |= UART_WORD_LENGTH_9BIT_FLAG;
    #endif
    #if (UART4_PARITY == UART_PARITY_EVEN)      // ����ż����
    UartPara.Flag |= UART_PARITY_EVEN_FLAG;
    #elif (UART4_PARITY == UART_PARITY_ODD)     // ���������
    UartPara.Flag |= UART_PARITY_ODD_FLAG;
    #endif    
    #if (UART4_STOP_BITS == UART_STOP_BITS_2)   // ����2λֹͣλ
    UartPara.Flag |= UART_STOP_BITS2_FLAG;
    #elif (UART4_PARITY == UART_STOP_BITS_0_5)  // ����0.5λֹͣλ
    UartPara.Flag |= UART_STOP_BITS0_5_FLAG;
    #elif (UART4_PARITY == UART_STOP_BITS_2)    // ����1.5λֹͣλ
    UartPara.Flag |= UART_STOP_BITS1_5_FLAG;
    #endif
    // ����������ż����λ��������λ����8bit, ʵ����Ч����λ��7bit���ʼ��ʱ���øñ�־
    #if ((UART4_PARITY > 0)&&(UART4_WORD_LENGTH == UART_WORD_LENGTH_8B))  
    UartPara.Flag |= UART_DATA_7BIT_FLAG;
    #endif    
        
    // ���ͺͽ���DMA����
    #if (UART4TX_DMA_EN > 0)
    UartPara.Flag |= UART_DMAREQ_TX_FLAG;   // ���÷���DMA
    #endif
    #if (UART4RX_DMA_EN > 0)
    UartPara.Flag |= UART_DMAREQ_RX_FLAG;   // ���ý���DMA
    #endif
    
    //UartPara.Flag |= UART_ISRHOOK_FLAG;   // ���õ��ô��ڽ��չ��Ӻ���, ���ڽ����������û���Uart4_ISRHook()�������Լ����ʵ��    
    
    UartPara.Mode = UART_AsynFD;             // ����ģʽ: ȫ˫���ģ��첽ͨ��
    UartPara.BaudRate = UART4_BAUD;          // ���ò�����
   
    UartPara.TxBufLen = UART4_TXBUF_SIZE;   // ���÷��ͻ��泤��
    UartPara.RxBufLen = UART4_RXBUF_SIZE;   // ���ý��ջ��泤��
    UartPara.pTxBuf = Uart4_TxBuffer;       // ���÷��ͻ���ָ��
    UartPara.pRxBuf = Uart4_RxBuffer;       // ���ý��ջ���ָ��    
  
    flag = Uart_Init(UART4_ID, (UART_PARA *)&UartPara.Flag); // ��ʼ��UART4
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

//---UART5��ʼ��-------------------------------------------------------
#if (UART5_EN > 0) 
    UartPara.Flag = 0;                    // ����Ϊ0
    UartPara.TXPin = UART5_TX;              // ����TX�ܽ�
    UartPara.RXPin = UART5_RX;              // ����RX�ܽ�
    UartPara.RS485DirPin = UART5_DIR;       // ����RS485�������IO
    #if (UART5_DIR != IO_NONE)              // û��תRS485�ӿ�
    UartPara.Flag |= UART_RS485EN_FLAG;   // ����RS485�ӿڱ�־
    #if (UART5_DIR_HL == 1)                 // Ϊ1���øߵ�ƽ����, Ĭ�ϵ͵�ƽ����
    UartPara.Flag |= UART_RS485DIR_FLAG;  // DIR�ߵ�ƽ����
    #endif
    #endif
    #if (UART5_WORD_LENGTH == UART_WORD_LENGTH_9B) // ��������λ��  
    UartPara.Flag |= UART_WORD_LENGTH_9BIT_FLAG;
    #endif
    #if (UART5_PARITY == UART_PARITY_EVEN)      // ����ż����
    UartPara.Flag |= UART_PARITY_EVEN_FLAG;
    #elif (UART5_PARITY == UART_PARITY_ODD)     // ���������
    UartPara.Flag |= UART_PARITY_ODD_FLAG;
    #endif    
    #if (UART5_STOP_BITS == UART_STOP_BITS_2)   // ����2λֹͣλ
    UartPara.Flag |= UART_STOP_BITS2_FLAG;
    #elif (UART5_PARITY == UART_STOP_BITS_0_5)  // ����0.5λֹͣλ
    UartPara.Flag |= UART_STOP_BITS0_5_FLAG;
    #elif (UART5_PARITY == UART_STOP_BITS_2)    // ����1.5λֹͣλ
    UartPara.Flag |= UART_STOP_BITS1_5_FLAG;
    #endif
    
    // ����������ż����λ��������λ����8bit, ʵ����Ч����λ��7bit���ʼ��ʱ���øñ�־
    #if ((UART5_PARITY > 0)&&(UART5_WORD_LENGTH == UART_WORD_LENGTH_8B))  
    UartPara.Flag |= UART_DATA_7BIT_FLAG;
    #endif   
    
    // ���ͺͽ���DMA����
    #if (UART5TX_DMA_EN > 0)
    UartPara.Flag |= UART_DMAREQ_TX_FLAG;   // ���÷���DMA
    #endif
    #if (UART5RX_DMA_EN > 0)
    UartPara.Flag |= UART_DMAREQ_RX_FLAG;   // ���ý���DMA
    #endif
            
    //UartPara.Flag |= UART_ISRHOOK_FLAG;   // ���õ��ô��ڽ��չ��Ӻ���, ���ڽ����������û���Uart5_ISRHook()�������Լ����ʵ��    


    UartPara.Mode = UART_AsynFD;             // ����ģʽ: ȫ˫���ģ��첽ͨ��
    UartPara.BaudRate = UART5_BAUD;          // ���ò�����
    
    UartPara.TxBufLen = UART5_TXBUF_SIZE;   // ���÷��ͻ��泤��
    UartPara.RxBufLen = UART5_RXBUF_SIZE;   // ���ý��ջ��泤��
    UartPara.pTxBuf = Uart5_TxBuffer;       // ���÷��ͻ���ָ��
    UartPara.pRxBuf = Uart5_RxBuffer;       // ���ý��ջ���ָ��    

    flag = Uart_Init(UART5_ID, (UART_PARA *)&UartPara.Flag); // ��ʼ��UART5
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

//---UART6��ʼ��-------------------------------------------------------
#if (UART6_EN > 0) 
    UartPara.Flag = 0;                    // ����Ϊ0
    UartPara.TXPin = UART6_TX;              // ����TX�ܽ�
    UartPara.RXPin = UART6_RX;              // ����RX�ܽ�
    UartPara.RS485DirPin = UART6_DIR;       // ����RS485�������IO
    #if (UART6_DIR != IO_NONE)              // û��תRS485�ӿ�
    UartPara.Flag |= UART_RS485EN_FLAG;   // ����RS485�ӿڱ�־
    #if (UART5_DIR_HL == 1)                 // Ϊ1���øߵ�ƽ����, Ĭ�ϵ͵�ƽ����
    UartPara.Flag |= UART_RS485DIR_FLAG;  // DIR�ߵ�ƽ����
    #endif
    #endif
    #if (UART6_WORD_LENGTH == UART_WORD_LENGTH_9B) // ��������λ��  
    UartPara.Flag |= UART_WORD_LENGTH_9BIT_FLAG;
    #endif
    #if (UART6_PARITY == UART_PARITY_EVEN)      // ����ż����
    UartPara.Flag |= UART_PARITY_EVEN_FLAG;
    #elif (UART6_PARITY == UART_PARITY_ODD)     // ���������
    UartPara.Flag |= UART_PARITY_ODD_FLAG;
    #endif    
    #if (UART6_STOP_BITS == UART_STOP_BITS_2)   // ����2λֹͣλ
    UartPara.Flag |= UART_STOP_BITS2_FLAG;
    #elif (UART6_PARITY == UART_STOP_BITS_0_5)  // ����0.5λֹͣλ
    UartPara.Flag |= UART_STOP_BITS0_5_FLAG;
    #elif (UART6_PARITY == UART_STOP_BITS_2)    // ����1.5λֹͣλ
    UartPara.Flag |= UART_STOP_BITS1_5_FLAG;
    #endif
    
    // ����������ż����λ��������λ����8bit, ʵ����Ч����λ��7bit���ʼ��ʱ���øñ�־
    #if ((UART6_PARITY > 0)&&(UART6_WORD_LENGTH == UART_WORD_LENGTH_8B))  
    UartPara.Flag |= UART_DATA_7BIT_FLAG;
    #endif   
    
    // ���ͺͽ���DMA����
    #if (UART6TX_DMA_EN > 0)
    UartPara.Flag |= UART_DMAREQ_TX_FLAG;   // ���÷���DMA
    #endif
    #if (UART6RX_DMA_EN > 0)
    UartPara.Flag |= UART_DMAREQ_RX_FLAG;   // ���ý���DMA
    #endif
    
    //UartPara.Flag |= UART_HWFC_RTS_FLAG|UART_HWFC_CTS_FLAG; // ���ؼ�DMA����    
    //UartPara.Flag |= UART_ISRHOOK_FLAG;   // ���õ��ô��ڽ��չ��Ӻ���, ���ڽ����������û���Uart6_ISRHook()�������Լ����ʵ��    


    UartPara.Mode = UART_AsynFD;             // ����ģʽ: ȫ˫���ģ��첽ͨ��
    UartPara.BaudRate = UART6_BAUD;          // ���ò�����
    
    UartPara.TxBufLen = UART6_TXBUF_SIZE;   // ���÷��ͻ��泤��
    UartPara.RxBufLen = UART6_RXBUF_SIZE;   // ���ý��ջ��泤��
    UartPara.pTxBuf = Uart6_TxBuffer;       // ���÷��ͻ���ָ��
    UartPara.pRxBuf = Uart6_RxBuffer;       // ���ý��ջ���ָ��    

    flag = Uart_Init(UART6_ID, (UART_PARA *)&UartPara.Flag); // ��ʼ��UART5
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
* Description: CAN1-CAN2Ӧ�ó�ʼ������;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
#if ((CAN1_EN>0)||(CAN2_EN>0)) // CAN1-2Ӧ�ó�ʼ��
void CAN_APPInit(void)
{
    CAN_PARA  CANPara;
    CAN_FILTER_PARA Filter;
    INT32U i;
    INT32S flag;
    
    // �˲�����ʼ������
    Filter.CAN2StartBank = CAN2_START_BANK; // CAN2��ʼ��, ���Ƕ�����CAN2(��)�ӿڵĿ�ʼ�飬��Χ��1~27    
    Filter.FIFO = CAN_FILTER_FIFO;          // CAN ������FIFO��������:Bit27~Bit0��Ч, bit0�ǵ�0�飬bit27�ǵ�27�� ������ͨ����ĳ�������Ĺ��˺�
                                            // ������ŵ��������FIFO��, 0����������������FIFO0��1����������������FIFO1��
    Filter.Scale = CAN_FILTER_SCALE;        // CAN ������λ��Ĵ�����Bit27~Bit0��Ч, bit0�ǵ�0�飬bit27�ǵ�27�飬
                                            // 0��������λ��Ϊ2��16λ; 1��������λ��Ϊ����32λ��
    Filter.Mode = CAN_FILTER_MODE;          // CAN������ģʽ (Filter mode)��Bit27~Bit0��Ч, bit0�ǵ�0�飬	bit27�ǵ�27�飬
                                            // 0: ��������x��2��32λ�Ĵ��������ڱ�ʶ������λģʽ��1: ��������x��2��32λ�Ĵ��������ڱ�ʶ���б�ģʽ��
    Filter.Active = CAN_FILTER_ACTIVE;      // ���������� (Filter active): 	 Bit27~Bit0��Ч, bit0�ǵ�0�飬	bit27�ǵ�27��
                                            // 0�������������ã�1�������������
    Filter.pBuf = CAN_FilterBuf;            // ���õĹ������Ĵ�������ָ��
    Filter.MaxLen = CAN_FILTER_MAXNUM*2;      // �˲����ܳ���
    
    #if (CAN1_EN>0)
    Filter.len = CAN2_START_BANK*2;       // ���õĹ������Ĵ������ݳ���
    for(i=0; i<(CAN2_START_BANK*2); i++) // ��ʼ���˲���IDΪ1-28
    {
    	CAN_FilterBuf[i] = ((i+1)<<SHIFT_BIT)|(CAN1_IDE<<2)|(CAN1_RTR<<1);
	}
    #endif
    
    #if (CAN2_EN>0)
    Filter.len += CAN2_START_BANK*2;                        // ���õĹ������Ĵ������ݳ���
    for(i=CAN2_START_BANK*2; i<CAN_FILTER_MAXNUM*2; i++)    // ��ʼ���˲���IDΪ1-28
    {
    	CAN_FilterBuf[i] = ((i-CAN2_START_BANK*2+1)<<SHIFT_BIT)|(CAN2_IDE<<2)|(CAN2_RTR<<1);
	}
    #endif
    
    #if (CAN1_EN>0)
    // CAN1��ʼ������
    CANPara.Flag = 0;
    CANPara.Mode = CAN1_MODE;       // 0,����ģʽ; 1, ����ģʽ(���ڵ���); 2, ��Ĭģʽ(���ڵ���); 3, ����/��Ĭģʽ(���ڵ���);
	CANPara.IDE = CAN1_IDE;         // ֡����: ��׼֡:CAN_STD_ID, ��չ֡:CAN_EXT_ID; Ĭ���������ļ�����
    CANPara.RTR = CAN1_RTR;         // Զ�̷�������: ����֡, CAN_RTR_DATA; Զ��֡, CAN_RTR_REMOTE; Ĭ���������ļ�����
    #if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F107XX))
	CANPara.PinRemap = CAN1_REMAP;  // CAN���Ź�����ӳ��
    #endif
    CANPara.TXPin = CAN1_TX;        // CAN�������Ŷ���
    CANPara.RXPin = CAN1_RX;        // CAN�������Ŷ���   
    
    CANPara.Baud = CAN1_BAUD;              // CAN������
    CANPara.RxMsgNum = CAN1_RXBUF_SIZE;    // CAN���ջ���ɽ�����Ϣ����,��Χ 1~256, ������Ҫ̫��,��ռ�ô���RAM
    CANPara.TxMsgNum = CAN1_TXBUF_SIZE;    // CAN���ͻ���ɷ�����Ϣ����,��Χ 1~256, ������Ҫ̫��,��ռ�ô���RAM
    CANPara.pRxMsgBuf =  CAN1_RxBuffer;     // CAN���ջ���ָ��
    CANPara.pTxMsgBuf = CAN1_TxBuffer;     // CAN���ͻ���ָ��
    
    flag = CAN_Init(CAN1_ID, (CAN_PARA *)&CANPara.Flag, (CAN_FILTER_PARA *)&Filter.CAN2StartBank); // ��ʼ��CAN1
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
    // CAN2��ʼ������
    CANPara.Flag = 0;
    CANPara.Mode = CAN2_MODE;       // 0,����ģʽ; 1, ����ģʽ(���ڵ���); 2, ��Ĭģʽ(���ڵ���); 3, ����/��Ĭģʽ(���ڵ���);
	CANPara.IDE = CAN2_IDE;         // ֡����: ��׼֡:CAN_STD_ID, ��չ֡:CAN_EXT_ID; Ĭ���������ļ�����
    CANPara.RTR = CAN2_RTR;         // Զ�̷�������: ����֡, CAN_RTR_DATA; Զ��֡, CAN_RTR_REMOTE; Ĭ���������ļ�����
    #if (MODULE_CLASS == STM32F107XX)
	CANPara.PinRemap = CAN2_REMAP;  // CAN���Ź�����ӳ��
    #endif
    CANPara.TXPin = CAN2_TX;        // CAN�������Ŷ���
    CANPara.RXPin = CAN2_RX;        // CAN�������Ŷ���   
    
    CANPara.Baud = CAN2_BAUD;              // CAN������
    CANPara.RxMsgNum = CAN2_RXBUF_SIZE;    // CAN���ջ���ɽ�����Ϣ����,��Χ 1~256, ������Ҫ̫��,��ռ�ô���RAM
    CANPara.TxMsgNum = CAN2_TXBUF_SIZE;    // CAN���ͻ���ɷ�����Ϣ����,��Χ 1~256, ������Ҫ̫��,��ռ�ô���RAM
    CANPara.pRxMsgBuf =  CAN2_RxBuffer;     // CAN���ջ���ָ��
    CANPara.pTxMsgBuf = CAN2_TxBuffer;     // CAN���ͻ���ָ��
    
    flag = CAN_Init(CAN2_ID, (CAN_PARA *)&CANPara.Flag, 0); // ��ʼ��CAN2
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
* Description: TIM1-TIM5Ӧ�ó�ʼ��;
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
    ||(TIM9_EN > 0)||(TIM10_EN > 0)||(TIM11_EN > 0)||(TIM12_EN > 0)||(TIM13_EN > 0)||(TIM14_EN > 0)) //TIM1-TIM14Ӧ�ó�ʼ��
void TIM_APPInit(void)
{
    TIM_PARA TIMPara;
    INT32S flag;

/***********************************************************************/
// TIM1��ʼ��
/***********************************************************************/
#if (TIM1_EN>0)
    TIMPara.Flag = 0;              // ��ʼ��0
    TIMPara.Flag |= TIM1CH_EN;     // ��ʼ��TIMʹ�ܱ�־
    TIMPara.Mode = TIM1_MODE;        // ���ù���ģʽ
    #if (TIM1_MODE == TIM_WKMODE_COUNT) // ����ģʽ��Ҫ���÷�Ƶϵ��
    TIMPara.Prescaler = TIM1_PSC;    // ����ʱ�ӷ�Ƶ   
    #endif

    flag = Timer_Init(TIM1_ID, (TIM_PARA *)&TIMPara.Flag); // ��ʼ����ʱ��
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
// TIM2��ʼ��
/***********************************************************************/
#if (TIM2_EN>0)
    TIMPara.Flag = 0;              // ��ʼ��0
    TIMPara.Flag |= TIM2CH_EN;     // ��ʼ��TIMʹ�ܱ�־
    TIMPara.Mode = TIM2_MODE;        // ���ù���ģʽ
    #if (TIM2_MODE == TIM_WKMODE_COUNT) // ����ģʽ��Ҫ���÷�Ƶϵ��
    TIMPara.Prescaler = TIM2_PSC;    // ����ʱ�ӷ�Ƶ   
    #endif
    
    
    flag = Timer_Init(TIM2_ID, (TIM_PARA *)&TIMPara.Flag); // ��ʼ����ʱ��
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
// TIM3��ʼ��
/***********************************************************************/
#if (TIM3_EN>0)
    TIMPara.Flag = 0;              // ��ʼ��0
    TIMPara.Flag |= TIM2CH_EN;     // ��ʼ��TIMʹ�ܱ�־
    TIMPara.Mode = TIM3_MODE;        // ���ù���ģʽ
    #if (TIM3_MODE == TIM_WKMODE_COUNT) // ����ģʽ��Ҫ���÷�Ƶϵ��
    TIMPara.Prescaler = TIM3_PSC;    // ����ʱ�ӷ�Ƶ   
    #endif  
    
    flag = Timer_Init(TIM3_ID, (TIM_PARA *)&TIMPara.Flag); // ��ʼ����ʱ��
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
// TIM4��ʼ��
/***********************************************************************/
#if (TIM4_EN>0)
    TIMPara.Flag = 0;              // ��ʼ��0
    TIMPara.Flag |= TIM4CH_EN;     // ��ʼ��TIMʹ�ܱ�־
    TIMPara.Mode = TIM4_MODE;        // ���ù���ģʽ
    #if (TIM4_MODE == TIM_WKMODE_COUNT) // ����ģʽ��Ҫ���÷�Ƶϵ��
    TIMPara.Prescaler = TIM4_PSC;    // ����ʱ�ӷ�Ƶ   
    #endif
    
    flag = Timer_Init(TIM4_ID, (TIM_PARA *)&TIMPara.Flag); // ��ʼ����ʱ��
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
// TIM5��ʼ��
/***********************************************************************/
#if (TIM5_EN>0)
    TIMPara.Flag = 0;              // ��ʼ��0
    TIMPara.Flag |= TIM5CH_EN;     // ��ʼ��TIMʹ�ܱ�־
    TIMPara.Mode = TIM5_MODE;        // ���ù���ģʽ
    #if (TIM5_MODE == TIM_WKMODE_COUNT) // ����ģʽ��Ҫ���÷�Ƶϵ��
    TIMPara.Prescaler = TIM5_PSC;    // ����ʱ�ӷ�Ƶ   
    #endif

    
    flag = Timer_Init(TIM5_ID, (TIM_PARA *)&TIMPara.Flag); // ��ʼ����ʱ��
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
// TIM6��ʼ��
/***********************************************************************/
#if (TIM6_EN>0)
    TIMPara.Flag = 0;              // ��ʼ��0
    TIMPara.Flag |= TIM6_EN;       // ��ʼ��TIMʹ�ܱ�־
    TIMPara.Mode = TIM6_MODE;        // ���ù���ģʽ
    #if (TIM6_MODE == TIM_WKMODE_COUNT) // ����ģʽ��Ҫ���÷�Ƶϵ��
    TIMPara.Prescaler = TIM6_PSC;    // ����ʱ�ӷ�Ƶ   
    #endif
    
    flag = Timer_Init(TIM6_ID, (TIM_PARA *)&TIMPara.Flag); // ��ʼ����ʱ��
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
// TIM7��ʼ��
/***********************************************************************/
#if (TIM7_EN>0)
    TIMPara.Flag = 0;              // ��ʼ��0
    TIMPara.Flag |= TIM7_EN;     // ��ʼ��TIMʹ�ܱ�־
    TIMPara.Mode = TIM7_MODE;        // ���ù���ģʽ
    #if (TIM7_MODE == TIM_WKMODE_COUNT) // ����ģʽ��Ҫ���÷�Ƶϵ��
    TIMPara.Prescaler = TIM7_PSC;    // ����ʱ�ӷ�Ƶ   
    #endif
    
    flag = Timer_Init(TIM7_ID, (TIM_PARA *)&TIMPara.Flag); // ��ʼ����ʱ��
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
// TIM8��ʼ��
/***********************************************************************/  
#if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F407XX))
#if (TIM8_EN>0)
    TIMPara.Flag = 0;              // ��ʼ��0
    TIMPara.Flag |= TIM8CH_EN;     // ��ʼ��TIMʹ�ܱ�־
    TIMPara.Mode = TIM8_MODE;        // ���ù���ģʽ
    #if (TIM8_MODE == TIM_WKMODE_COUNT) // ����ģʽ��Ҫ���÷�Ƶϵ��
    TIMPara.Prescaler = TIM8_PSC;    // ����ʱ�ӷ�Ƶ   
    #endif

    flag = Timer_Init(TIM8_ID, (TIM_PARA *)&TIMPara.Flag); // ��ʼ����ʱ��
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
// STM32F407XXģ��������ʱ����ʼ��
/***********************************************************************/
#if (MODULE_CLASS == STM32F407XX)
/***********************************************************************/
// TIM9��ʼ��
/***********************************************************************/
#if (TIM9_EN>0)
    TIMPara.Flag = 0;              // ��ʼ��0
    TIMPara.Flag |= TIM9CH_EN;     // ��ʼ��TIMʹ�ܱ�־
    TIMPara.Mode = TIM9_MODE;        // ���ù���ģʽ
    #if (TIM9_MODE == TIM_WKMODE_COUNT) // ����ģʽ��Ҫ���÷�Ƶϵ��
    TIMPara.Prescaler = TIM9_PSC;    // ����ʱ�ӷ�Ƶ   
    #endif

    flag = Timer_Init(TIM9_ID, (TIM_PARA *)&TIMPara.Flag); // ��ʼ����ʱ��
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
// TIM10��ʼ��
/***********************************************************************/
#if (TIM10_EN>0)
    TIMPara.Flag = 0;              // ��ʼ��0
    TIMPara.Flag |= TIM10CH_EN;     // ��ʼ��TIMʹ�ܱ�־
    TIMPara.Mode = TIM10_MODE;        // ���ù���ģʽ
    #if (TIM10_MODE == TIM_WKMODE_COUNT) // ����ģʽ��Ҫ���÷�Ƶϵ��
    TIMPara.Prescaler = TIM10_PSC;    // ����ʱ�ӷ�Ƶ   
    #endif

    flag = Timer_Init(TIM10_ID, (TIM_PARA *)&TIMPara.Flag); // ��ʼ����ʱ��
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
// TIM11��ʼ��
/***********************************************************************/
#if (TIM11_EN>0)
    TIMPara.Flag = 0;              // ��ʼ��0
    TIMPara.Flag |= TIM11CH_EN;     // ��ʼ��TIMʹ�ܱ�־
    TIMPara.Mode = TIM11_MODE;        // ���ù���ģʽ
    #if (TIM11_MODE == TIM_WKMODE_COUNT) // ����ģʽ��Ҫ���÷�Ƶϵ��
    TIMPara.Prescaler = TIM11_PSC;    // ����ʱ�ӷ�Ƶ   
    #endif

    flag = Timer_Init(TIM11_ID, (TIM_PARA *)&TIMPara.Flag); // ��ʼ����ʱ��
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
// TIM12��ʼ��
/***********************************************************************/
#if (TIM12_EN>0)
    TIMPara.Flag = 0;              // ��ʼ��0
    TIMPara.Flag |= TIM12CH_EN;     // ��ʼ��TIMʹ�ܱ�־
    TIMPara.Mode = TIM12_MODE;        // ���ù���ģʽ
    #if (TIM12_MODE == TIM_WKMODE_COUNT) // ����ģʽ��Ҫ���÷�Ƶϵ��
    TIMPara.Prescaler = TIM12_PSC;    // ����ʱ�ӷ�Ƶ   
    #endif

    flag = Timer_Init(TIM12_ID, (TIM_PARA *)&TIMPara.Flag); // ��ʼ����ʱ��
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
// TIM13��ʼ��
/***********************************************************************/
#if (TIM13_EN>0)
    TIMPara.Flag = 0;              // ��ʼ��0
    TIMPara.Flag |= TIM13CH_EN;     // ��ʼ��TIMʹ�ܱ�־
    TIMPara.Mode = TIM13_MODE;        // ���ù���ģʽ
    #if (TIM13_MODE == TIM_WKMODE_COUNT) // ����ģʽ��Ҫ���÷�Ƶϵ��
    TIMPara.Prescaler = TIM13_PSC;    // ����ʱ�ӷ�Ƶ   
    #endif

    flag = Timer_Init(TIM13_ID, (TIM_PARA *)&TIMPara.Flag); // ��ʼ����ʱ��
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
// TIM14��ʼ��
/***********************************************************************/
#if (TIM14_EN>0)
    TIMPara.Flag = 0;              // ��ʼ��0
    TIMPara.Flag |= TIM14CH_EN;     // ��ʼ��TIMʹ�ܱ�־
    TIMPara.Mode = TIM14_MODE;        // ���ù���ģʽ
    #if (TIM14_MODE == TIM_WKMODE_COUNT) // ����ģʽ��Ҫ���÷�Ƶϵ��
    TIMPara.Prescaler = TIM14_PSC;    // ����ʱ�ӷ�Ƶ   
    #endif

    flag = Timer_Init(TIM14_ID, (TIM_PARA *)&TIMPara.Flag); // ��ʼ����ʱ��
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
* Description: PWM���Ӧ�ó�ʼ������;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
#if ((PWM1_EN>0)||(PWM2_EN>0)||(PWM3_EN>0)||(PWM4_EN>0)||(PWM5_EN>0)||(PWM6_EN>0)||(PWM7_EN>0)||(PWM8_EN>0)) //PWM1-PWM8Ӧ�ó�ʼ��
void PWM_APPInit(void)
{
    PWM_PARA PWMPara;
    INT32S flag;
    
#if (PWM1_EN>0)                                // ͨ��1ʹ��
    PWMPara.Flag = 0;                          // ��ʼ��0
    PWMPara.Mode = 0;                          // ��ʼ������ģʽ,Ĭ����0
    PWMPara.Freq = PWM1_FREQ;                  // ��ʼ��PWM1Ƶ��
    PWMPara.TimerID = PWM1_TIM;              // ����PWMʹ�õĶ�ʱ��
    #if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F107XX))
	PWMPara.TimPin.Remap = PWM1_REMAP;         // ����PWM1�ܽ���ӳ��    
    #endif
    
    #if (PWM1_ISRHOOK_EN > 0)
    PWMPara.Flag |= PWM_ISRHOOK_EN_FLAG;      // ʹ��PWM_ISRHOOK��������: ��PWM����������ɻ��߳�����øù��Ӻ���
    #endif
    PWMPara.pISRHook = PWM_ISRHook;
    
    #if (PWM1_MODE == PWM_DMA)
    PWMPara.Flag |= PWM_WRITE_EN_FLAG;         // ʹ��PWM���������PWM_Write()��������
    #endif
    
    #if (PWM1CH1_EN == 1)
        PWMPara.Flag |= PWMCH1_EN_FLAG;        // ��ʼ��PWM CH1ʹ�ܱ�־
        #if (PWM1CH1_PIN == 1)
        PWMPara.Flag |= PWMCH1_PIN_FLAG;       // ��ʼ��PWM CH1ֹͣģʽ�ܽ������ƽ��־
        #endif
        PWMPara.Rate[PWM_CH1] = PWM1CH1_RATE;  // ��ʼ��ͨ��1ռ�ձ�
        PWMPara.TimPin.CH1 = PWM1_CH1;         // ����CH1�ܽ�         
    #endif
    
    #if (PWM1CH2_EN == 1)                      // ͨ��2ʹ��
        PWMPara.Flag |= PWMCH2_EN_FLAG;        // ��ʼ��PWM CH2ʹ�ܱ�־
        #if (PWM1CH2_PIN == 1)
        PWMPara.Flag |= PWMCH2_PIN_FLAG;       // ��ʼ��PWM CH2ֹͣģʽ�ܽ������ƽ��־
        #endif
        PWMPara.Rate[PWM_CH2] = PWM1CH2_RATE;  // ��ʼ��ͨ��2ռ�ձ�
        PWMPara.TimPin.CH2 = PWM1_CH2;         // ����CH2�ܽ� 
    #endif
    
    #if (PWM1CH3_EN == 1)                      // ͨ��3ʹ��
        PWMPara.Flag |= PWMCH3_EN_FLAG;        // ��ʼ��PWM CH3ʹ�ܱ�־
        #if (PWM1CH3_PIN == 1)
        PWMPara.Flag |= PWMCH3_PIN_FLAG;       // ��ʼ��PWM CH3ֹͣģʽ�ܽ������ƽ��־
        #endif
        PWMPara.Rate[PWM_CH3] = PWM1CH3_RATE;  // ��ʼ��ͨ��3ռ�ձ�
        PWMPara.TimPin.CH3 = PWM1_CH3;         // ����CH3�ܽ� 
    #endif
    
    #if (PWM1CH4_EN == 1)                      // ͨ��4ʹ��
        PWMPara.Flag |= PWMCH4_EN_FLAG;        // ��ʼ��PWM CH4ʹ�ܱ�־
        #if (PWM1CH4_PIN == 1)
        PWMPara.Flag |= PWMCH4_PIN_FLAG;       // ��ʼ��PWM CH4ֹͣģʽ�ܽ������ƽ��־
        #endif
        PWMPara.Rate[PWM_CH4] = PWM1CH4_RATE;  // ��ʼ��ͨ��4ռ�ձ�
        PWMPara.TimPin.CH4 = PWM1_CH4;         // ����CH4�ܽ� 
    #endif
    #ifdef PWM1_ETR
    PWMPara.TimPin.ETR = PWM1_ETR;             // ����ETR�ܽ�
    #else
    PWMPara.TimPin.ETR = IO_NONE;              // ����ETR�ܽ�
    #endif
    
    flag = PWM_Init(PWM1_ID, (PWM_PARA *)&PWMPara.Flag);  // PWM1��ʼ��
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
    PWMPara.Flag = 0;                         // ��ʼ��0
    PWMPara.Mode = 0;                         // ��ʼ������ģʽ,Ĭ����0
    PWMPara.Freq = PWM2_FREQ;                 // ��ʼ��PWM2Ƶ��
    PWMPara.TimerID = PWM2_TIM;               // ����PWMʹ�õĶ�ʱ��
    #if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F107XX))
	PWMPara.TimPin.Remap = PWM2_REMAP;         // ����PWM2�ܽ���ӳ��    
    #endif

    #if (PWM2_ISRHOOK_EN > 0)
    PWMPara.Flag |= PWM_ISRHOOK_EN_FLAG;      // ʹ��PWM_ISRHOOK��������: ��PWM����������ɻ��߳�����øù��Ӻ���
    #endif
    PWMPara.pISRHook = PWM_ISRHook;
    
    #if (PWM2_MODE == PWM_DMA)
    PWMPara.Flag |= PWM_WRITE_EN_FLAG;         // ʹ��PWM���������PWM_Write()��������
    #endif
    
    #if (PWM2CH1_EN == 1)                     // ͨ��1ʹ��
        PWMPara.Flag |= PWMCH1_EN_FLAG;       // ��ʼ��PWM CH1ʹ�ܱ�־
        #if (PWM2CH1_PIN == 1)
        PWMPara.Flag |= PWMCH1_PIN_FLAG;      // ��ʼ��PWM CH1ֹͣģʽ�ܽ������ƽ��־
        #endif
        PWMPara.Rate[PWM_CH1] = PWM2CH1_RATE; // ��ʼ��ͨ��1ռ�ձ�
        PWMPara.TimPin.CH1 = PWM2_CH1;        // ����CH1�ܽ�         
    #endif
    
    #if (PWM2CH2_EN == 1)                     // ͨ��2ʹ��
        PWMPara.Flag |= PWMCH2_EN_FLAG;       // ��ʼ��PWM CH2ʹ�ܱ�־
        #if (PWM2CH2_PIN == 1)
        PWMPara.Flag |= PWMCH2_PIN_FLAG;      // ��ʼ��PWM CH2ֹͣģʽ�ܽ������ƽ��־
        #endif
        PWMPara.Rate[PWM_CH2] = PWM2CH2_RATE; // ��ʼ��ͨ��2ռ�ձ�
        PWMPara.TimPin.CH2 = PWM2_CH2;        // ����CH2�ܽ� 
    #endif
    
    #if (PWM2CH3_EN == 1)                     // ͨ��3ʹ��
        PWMPara.Flag |= PWMCH3_EN_FLAG;       // ��ʼ��PWM CH3ʹ�ܱ�־
        #if (PWM2CH3_PIN == 1)
        PWMPara.Flag |= PWMCH3_PIN_FLAG;      // ��ʼ��PWM CH3ֹͣģʽ�ܽ������ƽ��־
        #endif
        PWMPara.Rate[PWM_CH3] = PWM2CH3_RATE; // ��ʼ��ͨ��3ռ�ձ�
        PWMPara.TimPin.CH3 = PWM2_CH3;        // ����CH3�ܽ� 
    #endif
    
    #if (PWM2CH4_EN == 1)                     // ͨ��4ʹ��
        PWMPara.Flag |= PWMCH4_EN_FLAG;       // ��ʼ��PWM CH4ʹ�ܱ�־
        #if (PWM2CH4_PIN == 1)
        PWMPara.Flag |= PWMCH4_PIN_FLAG;      // ��ʼ��PWM CH4ֹͣģʽ�ܽ������ƽ��־
        #endif
        PWMPara.Rate[PWM_CH4] = PWM2CH4_RATE; // ��ʼ��ͨ��4ռ�ձ�
        PWMPara.TimPin.CH4 = PWM2_CH4;        // ����CH4�ܽ� 
    #endif
    #ifdef PWM2_ETR
    PWMPara.TimPin.ETR = PWM2_ETR;             // ����ETR�ܽ�
    #else
    PWMPara.TimPin.ETR = IO_NONE;              // ����ETR�ܽ�
    #endif

    
    flag = PWM_Init(PWM2_ID, (PWM_PARA *)&PWMPara.Flag);  // PWM2��ʼ��
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
    PWMPara.Flag = 0;                         // ��ʼ��0
    PWMPara.Mode = 0;                         // ��ʼ������ģʽ,Ĭ����0
    PWMPara.Freq = PWM3_FREQ;                 // ��ʼ��PWM3Ƶ��
    PWMPara.TimerID = PWM3_TIM;               // ����PWMʹ�õĶ�ʱ��
    #if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F107XX))
	PWMPara.TimPin.Remap = PWM3_REMAP;         // ����PWM3�ܽ���ӳ��    
    #endif    

    #if (PWM3_ISRHOOK_EN > 0)
    PWMPara.Flag |= PWM_ISRHOOK_EN_FLAG;      // ʹ��PWM_ISRHOOK��������: ��PWM����������ɻ��߳�����øù��Ӻ���
    #endif
    PWMPara.pISRHook = PWM_ISRHook;

    #if (PWM3_MODE == PWM_DMA)
    PWMPara.Flag |= PWM_WRITE_EN_FLAG;         // ʹ��PWM���������PWM_Write()��������
    #endif
    
    #if (PWM3CH1_EN == 1)                     // ͨ��1ʹ��
        PWMPara.Flag |= PWMCH1_EN_FLAG;       // ��ʼ��PWM CH1ʹ�ܱ�־
        #if (PWM3CH1_PIN == 1)
        PWMPara.Flag |= PWMCH1_PIN_FLAG;      // ��ʼ��PWM CH1ֹͣģʽ�ܽ������ƽ��־
        #endif
        PWMPara.Rate[PWM_CH1] = PWM3CH1_RATE; // ��ʼ��ͨ��1ռ�ձ�
        PWMPara.TimPin.CH1 = PWM3_CH1;        // ����CH1�ܽ�         
    #endif
    
    #if (PWM3CH2_EN == 1)                     // ͨ��2ʹ��
        PWMPara.Flag |= PWMCH2_EN_FLAG;       // ��ʼ��PWM CH2ʹ�ܱ�־
        #if (PWM3CH2_PIN == 1)
        PWMPara.Flag |= PWMCH2_PIN_FLAG;      // ��ʼ��PWM CH2ֹͣģʽ�ܽ������ƽ��־
        #endif
        PWMPara.Rate[PWM_CH2] = PWM3CH2_RATE; // ��ʼ��ͨ��2ռ�ձ�
        PWMPara.TimPin.CH2 = PWM3_CH2;        // ����CH2�ܽ� 
    #endif
    
    #if (PWM3CH3_EN == 1)                     // ͨ��3ʹ��
        PWMPara.Flag |= PWMCH3_EN_FLAG;       // ��ʼ��PWM CH3ʹ�ܱ�־
        #if (PWM3CH3_PIN == 1)
        PWMPara.Flag |= PWMCH3_PIN_FLAG;      // ��ʼ��PWM CH3ֹͣģʽ�ܽ������ƽ��־
        #endif
        PWMPara.Rate[PWM_CH3] = PWM3CH3_RATE; // ��ʼ��ͨ��3ռ�ձ�
        PWMPara.TimPin.CH3 = PWM3_CH3;        // ����CH3�ܽ� 
    #endif
    
    #if (PWM3CH4_EN == 1)                     // ͨ��4ʹ��
        PWMPara.Flag |= PWMCH4_EN_FLAG;       // ��ʼ��PWM CH4ʹ�ܱ�־
        #if (PWM3CH4_PIN == 1)
        PWMPara.Flag |= PWMCH4_PIN_FLAG;      // ��ʼ��PWM CH4ֹͣģʽ�ܽ������ƽ��־
        #endif
        PWMPara.Rate[PWM_CH4] = PWM3CH4_RATE; // ��ʼ��ͨ��4ռ�ձ�
        PWMPara.TimPin.CH4 = PWM3_CH4;        // ����CH4�ܽ� 
    #endif
    #ifdef PWM3_ETR
    PWMPara.TimPin.ETR = PWM3_ETR;             // ����ETR�ܽ�
    #else
    PWMPara.TimPin.ETR = IO_NONE;              // ����ETR�ܽ�
    #endif
    
    flag = PWM_Init(PWM3_ID, (PWM_PARA *)&PWMPara.Flag);  // PWM3��ʼ��
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
    PWMPara.Flag = 0;                         // ��ʼ��0
    PWMPara.Mode = 0;                         // ��ʼ������ģʽ,Ĭ����0
    PWMPara.Freq = PWM4_FREQ;                 // ��ʼ��PWM4Ƶ��
    PWMPara.TimerID = PWM4_TIM;               // ����PWMʹ�õĶ�ʱ��
    #if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F107XX))
	PWMPara.TimPin.Remap = PWM4_REMAP;         // ����PWM4�ܽ���ӳ��    
    #endif 

    #if (PWM4_ISRHOOK_EN > 0)
    PWMPara.Flag |= PWM_ISRHOOK_EN_FLAG;      // ʹ��PWM_ISRHOOK��������: ��PWM����������ɻ��߳�����øù��Ӻ���
    #endif
    PWMPara.pISRHook = PWM_ISRHook;

    #if (PWM4_MODE == PWM_DMA)
    PWMPara.Flag |= PWM_WRITE_EN_FLAG;         // ʹ��PWM���������PWM_Write()��������
    #endif
    
    #if (PWM4CH1_EN == 1)                     // ͨ��1ʹ��
        PWMPara.Flag |= PWMCH1_EN_FLAG;       // ��ʼ��PWM CH1ʹ�ܱ�־
        #if (PWM4CH1_PIN == 1)
        PWMPara.Flag |= PWMCH1_PIN_FLAG;      // ��ʼ��PWM CH1ֹͣģʽ�ܽ������ƽ��־
        #endif
        PWMPara.Rate[PWM_CH1] = PWM4CH1_RATE; // ��ʼ��ͨ��1ռ�ձ�
        PWMPara.TimPin.CH1 = PWM4_CH1;        // ����CH1�ܽ�         
    #endif
    
    #if (PWM4CH2_EN == 1)                     // ͨ��2ʹ��
        PWMPara.Flag |= PWMCH2_EN_FLAG;       // ��ʼ��PWM CH2ʹ�ܱ�־
        #if (PWM4CH2_PIN == 1)
        PWMPara.Flag |= PWMCH2_PIN_FLAG;      // ��ʼ��PWM CH2ֹͣģʽ�ܽ������ƽ��־
        #endif
        PWMPara.Rate[PWM_CH2] = PWM4CH2_RATE; // ��ʼ��ͨ��2ռ�ձ�
        PWMPara.TimPin.CH2 = PWM4_CH2;        // ����CH2�ܽ� 
    #endif
    
    #if (PWM4CH3_EN == 1)                     // ͨ��3ʹ��
        PWMPara.Flag |= PWMCH3_EN_FLAG;       // ��ʼ��PWM CH3ʹ�ܱ�־
        #if (PWM4CH3_PIN == 1)
        PWMPara.Flag |= PWMCH3_PIN_FLAG;      // ��ʼ��PWM CH3ֹͣģʽ�ܽ������ƽ��־
        #endif
        PWMPara.Rate[PWM_CH3] = PWM4CH3_RATE; // ��ʼ��ͨ��3ռ�ձ�
        PWMPara.TimPin.CH3 = PWM4_CH3;        // ����CH3�ܽ� 
    #endif
    
    #if (PWM4CH4_EN == 1)                     // ͨ��4ʹ��
        PWMPara.Flag |= PWMCH4_EN_FLAG;       // ��ʼ��PWM CH4ʹ�ܱ�־
        #if (PWM4CH4_PIN == 1)
        PWMPara.Flag |= PWMCH4_PIN_FLAG;      // ��ʼ��PWM CH4ֹͣģʽ�ܽ������ƽ��־
        #endif
        PWMPara.Rate[PWM_CH4] = PWM4CH4_RATE; // ��ʼ��ͨ��4ռ�ձ�
        PWMPara.TimPin.CH4 = PWM4_CH4;        // ����CH4�ܽ� 
    #endif
    #ifdef PWM4_ETR
    PWMPara.TimPin.ETR = PWM4_ETR;             // ����ETR�ܽ�
    #else
    PWMPara.TimPin.ETR = IO_NONE;              // ����ETR�ܽ�
    #endif
    
    flag = PWM_Init(PWM4_ID, (PWM_PARA *)&PWMPara.Flag);  // PWM4��ʼ��
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
    PWMPara.Flag = 0;                         // ��ʼ��0
    PWMPara.Mode = 0;                         // ��ʼ������ģʽ,Ĭ����0
    PWMPara.Freq = PWM5_FREQ;                 // ��ʼ��PWM5Ƶ��
    PWMPara.TimerID = PWM5_TIM;               // ����PWMʹ�õĶ�ʱ��

    #if (PWM5_ISRHOOK_EN > 0)
    PWMPara.Flag |= PWM_ISRHOOK_EN_FLAG;      // ʹ��PWM_ISRHOOK��������: ��PWM����������ɻ��߳�����øù��Ӻ���
    #endif
    PWMPara.pISRHook = PWM_ISRHook;

    #if (PWM5_MODE == PWM_DMA)
    PWMPara.Flag |= PWM_WRITE_EN_FLAG;         // ʹ��PWM���������PWM_Write()��������
    #endif
    
    #if (PWM5CH1_EN == 1)                     // ͨ��1ʹ��
        PWMPara.Flag |= PWMCH1_EN_FLAG;       // ��ʼ��PWM CH1ʹ�ܱ�־
        #if (PWM5CH1_PIN == 1)
        PWMPara.Flag |= PWMCH1_PIN_FLAG;      // ��ʼ��PWM CH1ֹͣģʽ�ܽ������ƽ��־
        #endif
        PWMPara.Rate[PWM_CH1] = PWM5CH1_RATE; // ��ʼ��ͨ��1ռ�ձ�
        PWMPara.TimPin.CH1 = PWM5_CH1;        // ����CH1�ܽ�         
    #endif
    
    #if (PWM5CH2_EN == 1)                     // ͨ��2ʹ��
        PWMPara.Flag |= PWMCH2_EN_FLAG;       // ��ʼ��PWM CH2ʹ�ܱ�־
        #if (PWM5CH2_PIN == 1)
        PWMPara.Flag |= PWMCH2_PIN_FLAG;      // ��ʼ��PWM CH2ֹͣģʽ�ܽ������ƽ��־
        #endif
        PWMPara.Rate[PWM_CH2] = PWM5CH2_RATE; // ��ʼ��ͨ��2ռ�ձ�
        PWMPara.TimPin.CH2 = PWM5_CH2;        // ����CH2�ܽ� 
    #endif
    #ifdef PWM5_ETR
    PWMPara.TimPin.ETR = PWM5_ETR;             // ����ETR�ܽ�
    #else
    PWMPara.TimPin.ETR = IO_NONE;              // ����ETR�ܽ�
    #endif
        
    flag = PWM_Init(PWM5_ID, (PWM_PARA *)&PWMPara.Flag);  // PWM5��ʼ��
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
    PWMPara.Flag = 0;                         // ��ʼ��0
    PWMPara.Mode = 0;                         // ��ʼ������ģʽ,Ĭ����0
    PWMPara.Freq = PWM6_FREQ;                 // ��ʼ��PWM6Ƶ��
    PWMPara.TimerID = PWM6_TIM;               // ����PWMʹ�õĶ�ʱ��

    #if (PWM6_ISRHOOK_EN > 0)
    PWMPara.Flag |= PWM_ISRHOOK_EN_FLAG;      // ʹ��PWM_ISRHOOK��������: ��PWM����������ɻ��߳�����øù��Ӻ���
    #endif
    PWMPara.pISRHook = PWM_ISRHook;

    #if (PWM6_MODE == PWM_DMA)
    PWMPara.Flag |= PWM_WRITE_EN_FLAG;         // ʹ��PWM���������PWM_Write()��������
    #endif
    
    #if (PWM6CH1_EN == 1)                     // ͨ��1ʹ��
        PWMPara.Flag |= PWMCH1_EN_FLAG;       // ��ʼ��PWM CH1ʹ�ܱ�־
        #if (PWM6CH1_PIN == 1)
        PWMPara.Flag |= PWMCH1_PIN_FLAG;      // ��ʼ��PWM CH1ֹͣģʽ�ܽ������ƽ��־
        #endif
        PWMPara.Rate[PWM_CH1] = PWM6CH1_RATE; // ��ʼ��ͨ��1ռ�ձ�
        PWMPara.TimPin.CH1 = PWM6_CH1;        // ����CH1�ܽ�         
    #endif
    
    #if (PWM6CH2_EN == 1)                     // ͨ��2ʹ��
        PWMPara.Flag |= PWMCH2_EN_FLAG;       // ��ʼ��PWM CH2ʹ�ܱ�־
        #if (PWM6CH2_PIN == 1)
        PWMPara.Flag |= PWMCH2_PIN_FLAG;      // ��ʼ��PWM CH2ֹͣģʽ�ܽ������ƽ��־
        #endif
        PWMPara.Rate[PWM_CH2] = PWM6CH2_RATE; // ��ʼ��ͨ��2ռ�ձ�
        PWMPara.TimPin.CH2 = PWM6_CH2;        // ����CH2�ܽ� 
    #endif
    #ifdef PWM6_ETR
    PWMPara.TimPin.ETR = PWM6_ETR;             // ����ETR�ܽ�
    #else
    PWMPara.TimPin.ETR = IO_NONE;              // ����ETR�ܽ�
    #endif
        
    flag = PWM_Init(PWM6_ID, (PWM_PARA *)&PWMPara.Flag);  // PWM6��ʼ��
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
    PWMPara.Flag = 0;                         // ��ʼ��0
    PWMPara.Mode = 0;                         // ��ʼ������ģʽ,Ĭ����0
    PWMPara.Freq = PWM7_FREQ;                 // ��ʼ��PWM7Ƶ��
    PWMPara.TimerID = PWM7_TIM;               // ����PWMʹ�õĶ�ʱ��

    #if (PWM7_ISRHOOK_EN > 0)
    PWMPara.Flag |= PWM_ISRHOOK_EN_FLAG;      // ʹ��PWM_ISRHOOK��������: ��PWM����������ɻ��߳�����øù��Ӻ���
    #endif
    PWMPara.pISRHook = PWM_ISRHook;
    
    #if (PWM7_MODE == PWM_DMA)
    PWMPara.Flag |= PWM_WRITE_EN_FLAG;         // ʹ��PWM���������PWM_Write()��������
    #endif    
    
    #if (PWM7CH1_EN == 1)                     // ͨ��1ʹ��
        PWMPara.Flag |= PWMCH1_EN_FLAG;       // ��ʼ��PWM CH1ʹ�ܱ�־
        #if (PWM7CH1_PIN == 1)
        PWMPara.Flag |= PWMCH1_PIN_FLAG;      // ��ʼ��PWM CH1ֹͣģʽ�ܽ������ƽ��־
        #endif
        PWMPara.Rate[PWM_CH1] = PWM7CH1_RATE; // ��ʼ��ͨ��1ռ�ձ�
        PWMPara.TimPin.CH1 = PWM7_CH1;        // ����CH1�ܽ�         
    #endif
    #ifdef PWM7_ETR
    PWMPara.TimPin.ETR = PWM7_ETR;             // ����ETR�ܽ�
    #else
    PWMPara.TimPin.ETR = IO_NONE;              // ����ETR�ܽ�
    #endif
            
    flag = PWM_Init(PWM7_ID, (PWM_PARA *)&PWMPara.Flag);  // PWM7��ʼ��
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
* Description: FCLK����Ӧ�ó�ʼ������;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
#if ((FCLK1_EN>0)||(FCLK2_EN>0)||(FCLK3_EN>0)||(FCLK4_EN>0)||(FCLK5_EN>0)||(FCLK6_EN>0)||(FCLK7_EN>0)||(FCLK8_EN>0)) //FCLK1-FCLK8Ӧ�ó�ʼ��
void FCLK_APPInit(void)
{
    FCLK_PARA FCLKPara;
    INT32S flag;
    
#if (FCLK1_EN>0)    
    FCLKPara.Flag = 0;                            // ��ʼ��0    
    FCLKPara.Mode = FCLK1_MODE;                   // ��ʼ������ģʽ
    FCLKPara.TimerID = FCLK1_TIM;                 // ����FCLKʹ�õĶ�ʱ��
    #if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F107XX))
	FCLKPara.TimPin.Remap = FCLK1_REMAP;          // ����FCLK1�ܽ���ӳ�� 
    #endif
    FCLKPara.MinFreq = FCLK1_MINFREQ; 	          // ģʽ2��3�У�������СƵ���趨, ��λhz
    #ifdef FCLK1_ETR
    FCLKPara.TimPin.ETR = FCLK1_ETR;              // ����ETR�ܽ�
    #else
    FCLKPara.TimPin.ETR = IO_NONE;
    #endif
    #if (FCLK1CH1_EN == 1)                        // ͨ��1ʹ��
        FCLKPara.Flag |= FCLKCH1_EN_FLAG;         // ��ʼ��FCLK CH1ʹ�ܱ�־
        #if (FCLK1CH1_PIN == 1)
        FCLKPara.Flag |= FCLKCH1_PIN_FLAG;        // ��ʼ��FCLK CH1�ܽ������źŴ������أ� 0, ������; 1, �½���
        #endif
        #if (FCLK1CH1_PCS > 0)
        FCLKPara.Flag &= ~FCLKCH1_PCS_FLAG;       // �����־
        FCLKPara.Flag |= (INT32U)FCLK1CH1_PCS<<8; // FCLK CH1�ܽ������ź�Ԥ��Ƶϵ���� 0, ����Ƶ; 1, 2��Ƶ; 2, 4��Ƶ; 3, 8��Ƶ;
        #endif
        FCLKPara.TimPin.CH1 = FCLK1_CH1;          // ����CH1�ܽ� 
        #if ((FCLK1_MODE == 2)||(FCLK1_MODE == 3))
        FCLKPara.BufLen[0] = FCLK1CH1_BUF_SIZE;   // ���ý��ջ��泤��  
        FCLKPara.pBuf[0] = FClk1CH1Buf;           // ���ý������ݻ���ָ��
        #if (FCLK1CH1_DMA_EN > 0)
        FCLKPara.Flag |= FCLKCH1_DMA_FLAG;
        #endif
        #endif
    #endif
    
    #if (FCLK1CH2_EN == 1)                        // ͨ��2ʹ��
        FCLKPara.Flag |= FCLKCH2_EN_FLAG;         // ��ʼ��FCLK CH2ʹ�ܱ�־
        #if (FCLK1CH2_PIN == 1)
        FCLKPara.Flag |= FCLKCH2_PIN_FLAG;        // ��ʼ��FCLK CH2�ܽ������źŴ������أ� 0, ������; 1, �½���
        #endif
        #if (FCLK1CH2_PCS > 0)
        FCLKPara.Flag &= ~FCLKCH2_PCS_FLAG;       // �����־
        FCLKPara.Flag |= (INT32U)FCLK1CH2_PCS<<10;// FCLK CH2�ܽ������ź�Ԥ��Ƶϵ���� 0, ����Ƶ; 1, 2��Ƶ; 2, 4��Ƶ; 3, 8��Ƶ;
        #endif    
        FCLKPara.TimPin.CH2 = FCLK1_CH2;          // ����CH2�ܽ� 
        #if ((FCLK1_MODE == 2)||(FCLK1_MODE == 3))
        FCLKPara.BufLen[1] = FCLK1CH2_BUF_SIZE;   // ���ý��ջ��泤��  
        FCLKPara.pBuf[1] = FClk1CH2Buf;           // ���ý������ݻ���ָ��
        #if (FCLK1CH2_DMA_EN > 0)
        FCLKPara.Flag |= FCLKCH2_DMA_FLAG;
        #endif
        #endif
    #endif
    
    #if (FCLK1CH3_EN == 1)                        // ͨ��3ʹ��
        FCLKPara.Flag |= FCLKCH3_EN_FLAG;         // ��ʼ��FCLK CH3ʹ�ܱ�־
        #if (FCLK1CH3_PIN == 1)
        FCLKPara.Flag |= FCLKCH3_PIN_FLAG;        // ��ʼ��FCLK CH3�ܽ������źŴ������أ� 0, ������; 1, �½���
        #endif 
        #if (FCLK1CH3_PCS > 0)
        FCLKPara.Flag &= ~FCLKCH3_PCS_FLAG;       // �����־
        FCLKPara.Flag |= (INT32U)FCLK1CH3_PCS<<12;// FCLK CH3�ܽ������ź�Ԥ��Ƶϵ���� 0, ����Ƶ; 1, 2��Ƶ; 2, 4��Ƶ; 3, 8��Ƶ;
        #endif       
        FCLKPara.TimPin.CH3 = FCLK1_CH3;          // ����CH3�ܽ� 
        #if ((FCLK1_MODE == 2)||(FCLK1_MODE == 3))
        FCLKPara.BufLen[2] = FCLK1CH3_BUF_SIZE;   // ���ý��ջ��泤��  
        FCLKPara.pBuf[2] = FClk1CH3Buf;           // ���ý������ݻ���ָ��
        #if (FCLK1CH3_DMA_EN > 0)
        FCLKPara.Flag |= FCLKCH3_DMA_FLAG;
        #endif        
        #endif
    #endif
    
    #if (FCLK1CH4_EN == 1)                        // ͨ��4ʹ��
        FCLKPara.Flag |= FCLKCH4_EN_FLAG;         // ��ʼ��FCLK CH4ʹ�ܱ�־
        #if (FCLK1CH4_PIN == 1)
        FCLKPara.Flag |= FCLKCH4_PIN_FLAG;        // ��ʼ��FCLK CH4�ܽ������źŴ������أ� 0, ������; 1, �½���
        #endif   
        #if (FCLK1CH4_PCS > 0)
        FCLKPara.Flag &= ~FCLKCH4_PCS_FLAG;       // �����־
        FCLKPara.Flag |= (INT32U)FCLK1CH4_PCS<<14;// FCLK CH4�ܽ������ź�Ԥ��Ƶϵ���� 0, ����Ƶ; 1, 2��Ƶ; 2, 4��Ƶ; 3, 8��Ƶ;
        #endif   
        FCLKPara.TimPin.CH4 = FCLK1_CH4;          // ����CH4�ܽ�     
        #if ((FCLK1_MODE == 2)||(FCLK1_MODE == 3))
        FCLKPara.BufLen[3] = FCLK1CH4_BUF_SIZE;   // ���ý��ջ��泤��  
        FCLKPara.pBuf[3] = FClk1CH4Buf;           // ���ý������ݻ���ָ��
        #if (FCLK1CH4_DMA_EN > 0)
        FCLKPara.Flag |= FCLKCH4_DMA_FLAG;
        #endif
        #endif
    #endif    
    
    flag = FCLK_Init(FCLK1_ID, (FCLK_PARA *)&FCLKPara.Flag); // FCLK1��ʼ��
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
    FCLKPara.Flag = 0;                            // ��ʼ��0    
    FCLKPara.Mode = FCLK2_MODE;                   // ��ʼ������ģʽ
    FCLKPara.TimerID = FCLK2_TIM;                 // ����FCLKʹ�õĶ�ʱ��
    #if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F107XX))
	FCLKPara.TimPin.Remap = FCLK2_REMAP;          // ����FCLK2�ܽ���ӳ�� 
    #endif
    FCLKPara.MinFreq = FCLK2_MINFREQ; 	          // ģʽ2��3�У�������СƵ���趨, ��λhz
    #ifdef FCLK2_ETR
    FCLKPara.TimPin.ETR = FCLK2_ETR;              // ����ETR�ܽ�
    #else
    FCLKPara.TimPin.ETR = IO_NONE;
    #endif
    
    #if (FCLK2CH1_EN == 1)                        // ͨ��1ʹ��
        FCLKPara.Flag |= FCLKCH1_EN_FLAG;         // ��ʼ��FCLK CH1ʹ�ܱ�־
        #if (FCLK2CH1_PIN == 1)
        FCLKPara.Flag |= FCLKCH1_PIN_FLAG;        // ��ʼ��FCLK CH1�ܽ������źŴ������أ� 0, ������; 1, �½���
        #endif
        #if (FCLK2CH1_PCS > 0)
        FCLKPara.Flag &= ~FCLKCH1_PCS_FLAG;       // �����־
        FCLKPara.Flag |= (INT32U)FCLK1CH1_PCS<<8; // FCLK CH1�ܽ������ź�Ԥ��Ƶϵ���� 0, ����Ƶ; 1, 2��Ƶ; 2, 4��Ƶ; 3, 8��Ƶ;
        #endif
        FCLKPara.TimPin.CH1 = FCLK2_CH1;          // ����CH1�ܽ� 
        #if ((FCLK2_MODE == 2)||(FCLK2_MODE == 3))
        FCLKPara.BufLen[0] = FCLK2CH1_BUF_SIZE;   // ���ý��ջ��泤��  
        FCLKPara.pBuf[0] = FClk2CH1Buf;           // ���ý������ݻ���ָ��
        #if (FCLK2CH1_DMA_EN > 0)
        FCLKPara.Flag |= FCLKCH1_DMA_FLAG;
        #endif
        #endif
    #endif
    
    #if (FCLK2CH2_EN == 1)                        // ͨ��2ʹ��
        FCLKPara.Flag |= FCLKCH2_EN_FLAG;         // ��ʼ��FCLK CH2ʹ�ܱ�־
        #if (FCLK2CH2_PIN == 1)
        FCLKPara.Flag |= FCLKCH2_PIN_FLAG;        // ��ʼ��FCLK CH2�ܽ������źŴ������أ� 0, ������; 1, �½���
        #endif
        #if (FCLK2CH2_PCS > 0)
        FCLKPara.Flag &= ~FCLKCH2_PCS_FLAG;       // �����־
        FCLKPara.Flag |= (INT32U)FCLK2CH2_PCS<<10;// FCLK CH2�ܽ������ź�Ԥ��Ƶϵ���� 0, ����Ƶ; 1, 2��Ƶ; 2, 4��Ƶ; 3, 8��Ƶ;
        #endif
        FCLKPara.TimPin.CH2 = FCLK2_CH2;            // ����CH2�ܽ� 
        #if ((FCLK2_MODE == 2)||(FCLK2_MODE == 3))
        FCLKPara.BufLen[1] = FCLK2CH2_BUF_SIZE;     // ���ý��ջ��泤��  
        FCLKPara.pBuf[1] = FClk2CH2Buf;             // ���ý������ݻ���ָ��
        #if (FCLK2CH2_DMA_EN > 0)
        FCLKPara.Flag |= FCLKCH2_DMA_FLAG;
        #endif        
        #endif    
    #endif
    
    #if (FCLK2CH3_EN == 1)                          // ͨ��3ʹ��
        FCLKPara.Flag |= FCLKCH3_EN_FLAG;           // ��ʼ��FCLK CH3ʹ�ܱ�־
        #if (FCLK2CH3_PIN == 1)
        FCLKPara.Flag |= FCLKCH3_PIN_FLAG;          // ��ʼ��FCLK CH3�ܽ������źŴ������أ� 0, ������; 1, �½���
        #endif 
        #if (FCLK2CH3_PCS > 0)
        FCLKPara.Flag &= ~FCLKCH3_PCS_FLAG;         // �����־
        FCLKPara.Flag |= (INT32U)FCLK2CH3_PCS<<12;  // FCLK CH3�ܽ������ź�Ԥ��Ƶϵ���� 0, ����Ƶ; 1, 2��Ƶ; 2, 4��Ƶ; 3, 8��Ƶ;
        #endif       
        FCLKPara.TimPin.CH3 = FCLK2_CH3;            // ����CH3�ܽ� 
        #if ((FCLK2_MODE == 2)||(FCLK2_MODE == 3))
        FCLKPara.BufLen[2] = FCLK2CH3_BUF_SIZE;     // ���ý��ջ��泤��  
        FCLKPara.pBuf[2] = FClk2CH3Buf;             // ���ý������ݻ���ָ��
        #if (FCLK2CH3_DMA_EN > 0)
        FCLKPara.Flag |= FCLKCH3_DMA_FLAG;
        #endif
        #endif
    #endif
    
    #if (FCLK2CH4_EN == 1)                          // ͨ��4ʹ��
        FCLKPara.Flag |= FCLKCH4_EN_FLAG;           // ��ʼ��FCLK CH4ʹ�ܱ�־
        #if (FCLK2CH4_PIN == 1)
        FCLKPara.Flag |= FCLKCH4_PIN_FLAG;          // ��ʼ��FCLK CH4�ܽ������źŴ������أ� 0, ������; 1, �½���
        #endif   
        #if (FCLK2CH4_PCS > 0)
        FCLKPara.Flag &= ~FCLKCH4_PCS_FLAG;         // �����־
        FCLKPara.Flag |= (INT32U)FCLK2CH4_PCS<<14;  // FCLK CH4�ܽ������ź�Ԥ��Ƶϵ���� 0, ����Ƶ; 1, 2��Ƶ; 2, 4��Ƶ; 3, 8��Ƶ;
        #endif   
        FCLKPara.TimPin.CH4 = FCLK2_CH4;            // ����CH4�ܽ�    
        #if ((FCLK2_MODE == 2)||(FCLK2_MODE == 3))        
        FCLKPara.BufLen[3] = FCLK2CH4_BUF_SIZE;     // ���ý��ջ��泤��  
        FCLKPara.pBuf[3] = FClk2CH4Buf;             // ���ý������ݻ���ָ��
        #if (FCLK2CH4_DMA_EN > 0)
        FCLKPara.Flag |= FCLKCH4_DMA_FLAG;
        #endif
        #endif
    #endif    
    
    flag = FCLK_Init(FCLK2_ID, (FCLK_PARA *)&FCLKPara.Flag); // FCLK2��ʼ��
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
    FCLKPara.Flag = 0;                              // ��ʼ��0    
    FCLKPara.Mode = FCLK3_MODE;                     // ��ʼ������ģʽ
    FCLKPara.TimerID = FCLK3_TIM;                   // ����FCLKʹ�õĶ�ʱ��
    #if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F107XX))
	FCLKPara.TimPin.Remap = FCLK3_REMAP;            // ����FCLK3�ܽ���ӳ�� 
    #endif
    FCLKPara.MinFreq = FCLK3_MINFREQ; 	            // ģʽ2��3�У�������СƵ���趨, ��λhz
    #ifdef FCLK3_ETR
    FCLKPara.TimPin.ETR = FCLK3_ETR;              // ����ETR�ܽ�
    #else
    FCLKPara.TimPin.ETR = IO_NONE;
    #endif
    
    #if (FCLK3CH1_EN == 1)                          // ͨ��1ʹ��
        FCLKPara.Flag |= FCLKCH1_EN_FLAG;           // ��ʼ��FCLK CH1ʹ�ܱ�־
        #if (FCLK3CH1_PIN == 1)
        FCLKPara.Flag |= FCLKCH1_PIN_FLAG;          // ��ʼ��FCLK CH1�ܽ������źŴ������أ� 0, ������; 1, �½���
        #endif
        #if (FCLK3CH1_PCS > 0)
        FCLKPara.Flag &= ~FCLKCH1_PCS_FLAG;         // �����־
        FCLKPara.Flag |= (INT32U)FCLK3CH1_PCS<<8;   // FCLK CH1�ܽ������ź�Ԥ��Ƶϵ���� 0, ����Ƶ; 1, 2��Ƶ; 2, 4��Ƶ; 3, 8��Ƶ;
        #endif
        FCLKPara.TimPin.CH1 = FCLK3_CH1;            // ����CH1�ܽ� 
        #if ((FCLK3_MODE == 2)||(FCLK3_MODE == 3))
        FCLKPara.BufLen[0] = FCLK3CH1_BUF_SIZE;     // ���ý��ջ��泤��  
        FCLKPara.pBuf[0] = FClk3CH1Buf;             // ���ý������ݻ���ָ��
        #if (FCLK3CH1_DMA_EN > 0)
        FCLKPara.Flag |= FCLKCH1_DMA_FLAG;
        #endif
        #endif
    #endif
    
    #if (FCLK3CH2_EN == 1)                          // ͨ��2ʹ��
        FCLKPara.Flag |= FCLKCH2_EN_FLAG;           // ��ʼ��FCLK CH2ʹ�ܱ�־
        #if (FCLK3CH2_PIN == 1)
        FCLKPara.Flag |= FCLKCH2_PIN_FLAG;          // ��ʼ��FCLK CH2�ܽ������źŴ������أ� 0, ������; 1, �½���
        #endif
        #if (FCLK3CH2_PCS > 0)
        FCLKPara.Flag &= ~FCLKCH2_PCS_FLAG;         // �����־
        FCLKPara.Flag |= (INT32U)FCLK3CH2_PCS<<10;  // FCLK CH2�ܽ������ź�Ԥ��Ƶϵ���� 0, ����Ƶ; 1, 2��Ƶ; 2, 4��Ƶ; 3, 8��Ƶ;
        #endif
        FCLKPara.TimPin.CH2 = FCLK3_CH2;            // ����CH2�ܽ� 
        #if ((FCLK3_MODE == 2)||(FCLK3_MODE == 3))
        FCLKPara.BufLen[1] = FCLK3CH2_BUF_SIZE;     // ���ý��ջ��泤��  
        FCLKPara.pBuf[1] = FClk3CH2Buf;             // ���ý������ݻ���ָ��
        #if (FCLK3CH2_DMA_EN > 0)
        FCLKPara.Flag |= FCLKCH2_DMA_FLAG;
        #endif
        #endif    
    #endif
    
    #if (FCLK3CH3_EN == 1)                          // ͨ��3ʹ��
        FCLKPara.Flag |= FCLKCH3_EN_FLAG;           // ��ʼ��FCLK CH3ʹ�ܱ�־
        #if (FCLK3CH3_PIN == 1)
        FCLKPara.Flag |= FCLKCH3_PIN_FLAG;          // ��ʼ��FCLK CH3�ܽ������źŴ������أ� 0, ������; 1, �½���
        #endif 
        #if (FCLK3CH3_PCS > 0)
        FCLKPara.Flag &= ~FCLKCH3_PCS_FLAG;         // �����־
        FCLKPara.Flag |= (INT32U)FCLK3CH3_PCS<<12;  // FCLK CH3�ܽ������ź�Ԥ��Ƶϵ���� 0, ����Ƶ; 1, 2��Ƶ; 2, 4��Ƶ; 3, 8��Ƶ;
        #endif       
        FCLKPara.TimPin.CH3 = FCLK3_CH3;            // ����CH3�ܽ� 
        #if ((FCLK3_MODE == 2)||(FCLK3_MODE == 3))
        FCLKPara.BufLen[2] = FCLK3CH3_BUF_SIZE;     // ���ý��ջ��泤��  
        FCLKPara.pBuf[2] = FClk3CH3Buf;             // ���ý������ݻ���ָ��
        #if (FCLK3CH3_DMA_EN > 0)
        FCLKPara.Flag |= FCLKCH3_DMA_FLAG;
        #endif
        #endif
    #endif
    
    #if (FCLK3CH4_EN == 1)                          // ͨ��4ʹ��
        FCLKPara.Flag |= FCLKCH4_EN_FLAG;           // ��ʼ��FCLK CH4ʹ�ܱ�־
        #if (FCLK3CH4_PIN == 1)
        FCLKPara.Flag |= FCLKCH4_PIN_FLAG;          // ��ʼ��FCLK CH4�ܽ������źŴ������أ� 0, ������; 1, �½���
        #endif   
        #if (FCLK3CH4_PCS > 0)
        FCLKPara.Flag &= ~FCLKCH4_PCS_FLAG;         // �����־
        FCLKPara.Flag |= (INT32U)FCLK3CH4_PCS<<14;  // FCLK CH4�ܽ������ź�Ԥ��Ƶϵ���� 0, ����Ƶ; 1, 2��Ƶ; 2, 4��Ƶ; 3, 8��Ƶ;
        #endif   
        FCLKPara.TimPin.CH4 = FCLK3_CH4;            // ����CH4�ܽ�     
        #if ((FCLK3_MODE == 2)||(FCLK3_MODE == 3))
        FCLKPara.BufLen[3] = FCLK3CH4_BUF_SIZE;     // ���ý��ջ��泤��  
        FCLKPara.pBuf[3] = FClk3CH4Buf;             // ���ý������ݻ���ָ��
        #if (FCLK3CH4_DMA_EN > 0)
        FCLKPara.Flag |= FCLKCH4_DMA_FLAG;
        #endif
        #endif
    #endif    
    
    flag = FCLK_Init(FCLK3_ID, (FCLK_PARA *)&FCLKPara.Flag); // FCLK3��ʼ��
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
    FCLKPara.Flag = 0;                              // ��ʼ��0    
    FCLKPara.Mode = FCLK4_MODE;                     // ��ʼ������ģʽ
    FCLKPara.TimerID = FCLK4_TIM;                   // ����FCLKʹ�õĶ�ʱ��
    #if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F107XX))
	FCLKPara.TimPin.Remap = FCLK4_REMAP;            // ����FCLK4�ܽ���ӳ�� 
    #endif
    FCLKPara.MinFreq = FCLK4_MINFREQ; 	            // ģʽ2��3�У�������СƵ���趨, ��λhz
    #ifdef FCLK4_ETR
    FCLKPara.TimPin.ETR = FCLK4_ETR;              // ����ETR�ܽ�
    #else
    FCLKPara.TimPin.ETR = IO_NONE;
    #endif
    
    #if (FCLK4CH1_EN == 1)                          // ͨ��1ʹ��
        FCLKPara.Flag |= FCLKCH1_EN_FLAG;           // ��ʼ��FCLK CH1ʹ�ܱ�־
        #if (FCLK4CH1_PIN == 1)
        FCLKPara.Flag |= FCLKCH1_PIN_FLAG;          // ��ʼ��FCLK CH1�ܽ������źŴ������أ� 0, ������; 1, �½���
        #endif
        #if (FCLK4CH1_PCS > 0)
        FCLKPara.Flag &= ~FCLKCH1_PCS_FLAG;         // �����־
        FCLKPara.Flag |= (INT32U)FCLK4CH1_PCS<<8;   // FCLK CH1�ܽ������ź�Ԥ��Ƶϵ���� 0, ����Ƶ; 1, 2��Ƶ; 2, 4��Ƶ; 3, 8��Ƶ;
        #endif
        FCLKPara.TimPin.CH1 = FCLK4_CH1;            // ����CH1�ܽ� 
        #if ((FCLK4_MODE == 2)||(FCLK4_MODE == 3))
        FCLKPara.BufLen[0] = FCLK4CH1_BUF_SIZE;     // ���ý��ջ��泤��  
        FCLKPara.pBuf[0] = FClk4CH1Buf;             // ���ý������ݻ���ָ��
        #if (FCLK4CH1_DMA_EN > 0)
        FCLKPara.Flag |= FCLKCH1_DMA_FLAG;
        #endif
        #endif
    #endif
    
    #if (FCLK4CH2_EN == 1)                          // ͨ��2ʹ��
        FCLKPara.Flag |= FCLKCH2_EN_FLAG;           // ��ʼ��FCLK CH2ʹ�ܱ�־
        #if (FCLK4CH2_PIN == 1)
        FCLKPara.Flag |= FCLKCH2_PIN_FLAG;          // ��ʼ��FCLK CH2�ܽ������źŴ������أ� 0, ������; 1, �½���
        #endif
        #if (FCLK4CH2_PCS > 0)
        FCLKPara.Flag &= ~FCLKCH2_PCS_FLAG;         // �����־
        FCLKPara.Flag |= (INT32U)FCLK4CH2_PCS<<10;  // FCLK CH2�ܽ������ź�Ԥ��Ƶϵ���� 0, ����Ƶ; 1, 2��Ƶ; 2, 4��Ƶ; 3, 8��Ƶ;
        #endif
        FCLKPara.TimPin.CH2 = FCLK4_CH2;            // ����CH2�ܽ� 
        #if ((FCLK4_MODE == 2)||(FCLK4_MODE == 3))
        FCLKPara.BufLen[1] = FCLK4CH2_BUF_SIZE;     // ���ý��ջ��泤��  
        FCLKPara.pBuf[1] = FClk4CH2Buf;             // ���ý������ݻ���ָ��
        #if (FCLK4CH2_DMA_EN > 0)
        FCLKPara.Flag |= FCLKCH2_DMA_FLAG;
        #endif
        #endif    
    #endif
    
    #if (FCLK4CH3_EN == 1)                          // ͨ��3ʹ��
        FCLKPara.Flag |= FCLKCH3_EN_FLAG;           // ��ʼ��FCLK CH3ʹ�ܱ�־
        #if (FCLK4CH3_PIN == 1)
        FCLKPara.Flag |= FCLKCH3_PIN_FLAG;          // ��ʼ��FCLK CH3�ܽ������źŴ������أ� 0, ������; 1, �½���
        #endif 
        #if (FCLK4CH3_PCS > 0)
        FCLKPara.Flag &= ~FCLKCH3_PCS_FLAG;         // �����־
        FCLKPara.Flag |= (INT32U)FCLK4CH3_PCS<<12;  // FCLK CH3�ܽ������ź�Ԥ��Ƶϵ���� 0, ����Ƶ; 1, 2��Ƶ; 2, 4��Ƶ; 3, 8��Ƶ;
        #endif       
        FCLKPara.TimPin.CH3 = FCLK4_CH3;            // ����CH3�ܽ� 
        #if ((FCLK4_MODE == 2)||(FCLK4_MODE == 3))
        FCLKPara.BufLen[2] = FCLK4CH3_BUF_SIZE;     // ���ý��ջ��泤��  
        FCLKPara.pBuf[2] = FClk4CH3Buf;             // ���ý������ݻ���ָ��
        #if (FCLK4CH3_DMA_EN > 0)
        FCLKPara.Flag |= FCLKCH3_DMA_FLAG;
        #endif
        #endif
    #endif
    
    #if (FCLK4CH4_EN == 1)                          // ͨ��4ʹ��
        FCLKPara.Flag |= FCLKCH4_EN_FLAG;           // ��ʼ��FCLK CH4ʹ�ܱ�־
        #if (FCLK4CH4_PIN == 1)
        FCLKPara.Flag |= FCLKCH4_PIN_FLAG;          // ��ʼ��FCLK CH4�ܽ������źŴ������أ� 0, ������; 1, �½���
        #endif   
        #if (FCLK4CH4_PCS > 0)
        FCLKPara.Flag &= ~FCLKCH4_PCS_FLAG;         // �����־
        FCLKPara.Flag |= (INT32U)FCLK4CH4_PCS<<14;  // FCLK CH4�ܽ������ź�Ԥ��Ƶϵ���� 0, ����Ƶ; 1, 2��Ƶ; 2, 4��Ƶ; 3, 8��Ƶ;
        #endif   
        FCLKPara.TimPin.CH4 = FCLK4_CH4;            // ����CH4�ܽ�     
        #if ((FCLK4_MODE == 2)||(FCLK4_MODE == 3))
        FCLKPara.BufLen[3] = FCLK4CH4_BUF_SIZE;     // ���ý��ջ��泤��  
        FCLKPara.pBuf[3] = FClk4CH4Buf;             // ���ý������ݻ���ָ��
        #if (FCLK4CH4_DMA_EN > 0)
        FCLKPara.Flag |= FCLKCH4_DMA_FLAG;
        #endif
        #endif
    #endif    
    
    flag = FCLK_Init(FCLK4_ID, (FCLK_PARA *)&FCLKPara.Flag); // FCLK4��ʼ��
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
    FCLKPara.Flag = 0;                              // ��ʼ��0    
    FCLKPara.Mode = FCLK5_MODE;                     // ��ʼ������ģʽ
    FCLKPara.TimerID = FCLK5_TIM;                   // ����FCLKʹ�õĶ�ʱ��
    FCLKPara.MinFreq = FCLK5_MINFREQ; 	            // ģʽ2��3�У�������СƵ���趨, ��λhz
    #ifdef FCLK5_ETR
    FCLKPara.TimPin.ETR = FCLK5_ETR;              // ����ETR�ܽ�
    #else
    FCLKPara.TimPin.ETR = IO_NONE;
    #endif
    
    #if (FCLK5CH1_EN == 1)                          // ͨ��1ʹ��
        FCLKPara.Flag |= FCLKCH1_EN_FLAG;           // ��ʼ��FCLK CH1ʹ�ܱ�־
        #if (FCLK5CH1_PIN == 1)
        FCLKPara.Flag |= FCLKCH1_PIN_FLAG;          // ��ʼ��FCLK CH1�ܽ������źŴ������أ� 0, ������; 1, �½���
        #endif
        #if (FCLK5CH1_PCS > 0)
        FCLKPara.Flag &= ~FCLKCH1_PCS_FLAG;         // �����־
        FCLKPara.Flag |= (INT32U)FCLK5CH1_PCS<<8;   // FCLK CH1�ܽ������ź�Ԥ��Ƶϵ���� 0, ����Ƶ; 1, 2��Ƶ; 2, 4��Ƶ; 3, 8��Ƶ;
        #endif
        FCLKPara.TimPin.CH1 = FCLK5_CH1;            // ����CH1�ܽ� 
        #if ((FCLK5_MODE == 2)||(FCLK5_MODE == 3))
        FCLKPara.BufLen[0] = FCLK5CH1_BUF_SIZE;     // ���ý��ջ��泤��  
        FCLKPara.pBuf[0] = FClk5CH1Buf;             // ���ý������ݻ���ָ��
        #if (FCLK5CH1_DMA_EN > 0)
        FCLKPara.Flag |= FCLKCH1_DMA_FLAG;
        #endif
        #endif
    #endif
    
    #if (FCLK5CH2_EN == 1)                          // ͨ��2ʹ��
        FCLKPara.Flag |= FCLKCH2_EN_FLAG;           // ��ʼ��FCLK CH2ʹ�ܱ�־
        #if (FCLK5CH2_PIN == 1)
        FCLKPara.Flag |= FCLKCH2_PIN_FLAG;          // ��ʼ��FCLK CH2�ܽ������źŴ������أ� 0, ������; 1, �½���
        #endif
        #if (FCLK5CH2_PCS > 0)
        FCLKPara.Flag &= ~FCLKCH2_PCS_FLAG;         // �����־
        FCLKPara.Flag |= (INT32U)FCLK5CH2_PCS<<10;  // FCLK CH2�ܽ������ź�Ԥ��Ƶϵ���� 0, ����Ƶ; 1, 2��Ƶ; 2, 4��Ƶ; 3, 8��Ƶ;
        #endif
        FCLKPara.TimPin.CH2 = FCLK5_CH2;            // ����CH2�ܽ� 
        #if ((FCLK5_MODE == 2)||(FCLK5_MODE == 3))
        FCLKPara.BufLen[1] = FCLK5CH2_BUF_SIZE;     // ���ý��ջ��泤��  
        FCLKPara.pBuf[1] = FClk5CH2Buf;             // ���ý������ݻ���ָ��
        #if (FCLK5CH2_DMA_EN > 0)
        FCLKPara.Flag |= FCLKCH2_DMA_FLAG;
        #endif
        #endif    
    #endif    
       
    flag = FCLK_Init(FCLK5_ID, (FCLK_PARA *)&FCLKPara.Flag); // FCLK5��ʼ��
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
    FCLKPara.Flag = 0;                              // ��ʼ��0    
    FCLKPara.Mode = FCLK6_MODE;                     // ��ʼ������ģʽ
    FCLKPara.TimerID = FCLK6_TIM;                   // ����FCLKʹ�õĶ�ʱ��
    FCLKPara.MinFreq = FCLK6_MINFREQ; 	            // ģʽ2��3�У�������СƵ���趨, ��λhz
    #ifdef FCLK6_ETR
    FCLKPara.TimPin.ETR = FCLK6_ETR;              // ����ETR�ܽ�
    #else
    FCLKPara.TimPin.ETR = IO_NONE;
    #endif
    
    #if (FCLK6CH1_EN == 1)                          // ͨ��1ʹ��
        FCLKPara.Flag |= FCLKCH1_EN_FLAG;           // ��ʼ��FCLK CH1ʹ�ܱ�־
        #if (FCLK6CH1_PIN == 1)
        FCLKPara.Flag |= FCLKCH1_PIN_FLAG;          // ��ʼ��FCLK CH1�ܽ������źŴ������أ� 0, ������; 1, �½���
        #endif
        #if (FCLK6CH1_PCS > 0)
        FCLKPara.Flag &= ~FCLKCH1_PCS_FLAG;         // �����־
        FCLKPara.Flag |= (INT32U)FCLK6CH1_PCS<<8;   // FCLK CH1�ܽ������ź�Ԥ��Ƶϵ���� 0, ����Ƶ; 1, 2��Ƶ; 2, 4��Ƶ; 3, 8��Ƶ;
        #endif
        FCLKPara.TimPin.CH1 = FCLK6_CH1;            // ����CH1�ܽ� 
        #if ((FCLK6_MODE == 2)||(FCLK6_MODE == 3))
        FCLKPara.BufLen[0] = FCLK6CH1_BUF_SIZE;     // ���ý��ջ��泤��  
        FCLKPara.pBuf[0] = FClk6CH1Buf;             // ���ý������ݻ���ָ��
        #if (FCLK6CH1_DMA_EN > 0)
        FCLKPara.Flag |= FCLKCH1_DMA_FLAG;
        #endif
        #endif
    #endif
    
    #if (FCLK6CH2_EN == 1)                          // ͨ��2ʹ��
        FCLKPara.Flag |= FCLKCH2_EN_FLAG;           // ��ʼ��FCLK CH2ʹ�ܱ�־
        #if (FCLK6CH2_PIN == 1)
        FCLKPara.Flag |= FCLKCH2_PIN_FLAG;          // ��ʼ��FCLK CH2�ܽ������źŴ������أ� 0, ������; 1, �½���
        #endif
        #if (FCLK6CH2_PCS > 0)
        FCLKPara.Flag &= ~FCLKCH2_PCS_FLAG;         // �����־
        FCLKPara.Flag |= (INT32U)FCLK6CH2_PCS<<10;  // FCLK CH2�ܽ������ź�Ԥ��Ƶϵ���� 0, ����Ƶ; 1, 2��Ƶ; 2, 4��Ƶ; 3, 8��Ƶ;
        #endif
        FCLKPara.TimPin.CH2 = FCLK6_CH2;            // ����CH2�ܽ� 
        #if ((FCLK6_MODE == 2)||(FCLK6_MODE == 3))
        FCLKPara.BufLen[1] = FCLK6CH2_BUF_SIZE;     // ���ý��ջ��泤��  
        FCLKPara.pBuf[1] = FClk6CH2Buf;             // ���ý������ݻ���ָ��
        #if (FCLK6CH2_DMA_EN > 0)
        FCLKPara.Flag |= FCLKCH2_DMA_FLAG;
        #endif
        #endif    
    #endif    
       
    flag = FCLK_Init(FCLK6_ID, (FCLK_PARA *)&FCLKPara.Flag); // FCLK6��ʼ��
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
    FCLKPara.Flag = 0;                              // ��ʼ��0    
    FCLKPara.Mode = FCLK7_MODE;                     // ��ʼ������ģʽ
    FCLKPara.TimerID = FCLK7_TIM;                   // ����FCLKʹ�õĶ�ʱ��
    FCLKPara.MinFreq = FCLK7_MINFREQ; 	            // ģʽ2��3�У�������СƵ���趨, ��λhz
    #ifdef FCLK7_ETR
    FCLKPara.TimPin.ETR = FCLK7_ETR;                // ����ETR�ܽ�
    #else
    FCLKPara.TimPin.ETR = IO_NONE;
    #endif
    
    #if (FCLK7CH1_EN == 1)                          // ͨ��1ʹ��
        FCLKPara.Flag |= FCLKCH1_EN_FLAG;           // ��ʼ��FCLK CH1ʹ�ܱ�־
        #if (FCLK7CH1_PIN == 1)
        FCLKPara.Flag |= FCLKCH1_PIN_FLAG;          // ��ʼ��FCLK CH1�ܽ������źŴ������أ� 0, ������; 1, �½���
        #endif
        #if (FCLK7CH1_PCS > 0)
        FCLKPara.Flag &= ~FCLKCH1_PCS_FLAG;         // �����־
        FCLKPara.Flag |= (INT32U)FCLK7CH1_PCS<<8;   // FCLK CH1�ܽ������ź�Ԥ��Ƶϵ���� 0, ����Ƶ; 1, 2��Ƶ; 2, 4��Ƶ; 3, 8��Ƶ;
        #endif
        FCLKPara.TimPin.CH1 = FCLK7_CH1;            // ����CH1�ܽ� 
        #if ((FCLK7_MODE == 2)||(FCLK7_MODE == 3))
        FCLKPara.BufLen[0] = FCLK7CH1_BUF_SIZE;     // ���ý��ջ��泤��  
        FCLKPara.pBuf[0] = FClk7CH1Buf;             // ���ý������ݻ���ָ��
        #if (FCLK7CH1_DMA_EN > 0)
        FCLKPara.Flag |= FCLKCH1_DMA_FLAG;
        #endif
        #endif
    #endif
  
    flag = FCLK_Init(FCLK7_ID, (FCLK_PARA *)&FCLKPara.Flag); // FCLK7��ʼ��
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
* Description: SPI FLASH(W25QXX��AT45DBXX)Ӧ�ó�ʼ������;
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
    Para.Flag = 0;              // ������־
    Para.SPI_ID = SPI1_ID;
    #if (SPIFLASH_TYPE == W25QXX)
    Para.CS_Pin = W25QXX_CS;
    Para.Flag |= W25QXX_TYPE_FLAG;
    Para.SectorSize = W25QXX_SECTOR_SIZE;	       // Flash������С(��λ���ֽ�) 
    Para.SectorNum = W25QXX_SECTOR_NUM;	           // Flash�������� 
    Para.FatFSSectorNum = W25QXX_FATFS_SECTORNUM;  // FatFS�ļ�ϵͳռ����������
    #if (SPIFLASH_MODE==1) // ����FATFS�ļ�ϵͳ���ж�д
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
    Para.SectorSize = AT45DBXX_PAGE_SIZE;	       // Flash������С(��λ���ֽ�) 
    Para.SectorNum = AT45DBXX_PAGE_NUM;	           // Flash�������� 
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
* Description: SD��Ӧ�ó�ʼ��;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
#if (SDCARD_EN > 0) // SD��ʹ��
void SD_APPInit(void)
{
    SD_PARA Para;
    INT32S flag;
    
    Para.Flag = 0;
    Para.Mode = SD_SPI_MODE;  // SPI��дģʽ
    Para.SPIx_ID = SPI1_ID;   // ѡ��SPI1
    
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
* Description: DACӦ�ó�ʼ������;
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
void  DAC_APPInit(void)  // DACӦ�ó�ʼ������;
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
* Description: ADCӦ�ó�ʼ������;
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
void  ADC_APPInit(void)  // ADCӦ�ó�ʼ������;
{    
    ADC_PARA ADCPara;
    INT8U n;
    INT32S flag;
    
    ADCPara.Mode = 0;                        // �޶���, Ĭ��0
    ADCPara.Flag = 0; 
    // ѡ��AD�����ʽ
    #if (ADC_OUT_TYPE == ADC_ISROUT)  // �ж����ж����AD����ֵ
    ADCPara.Flag |= ADC_ISROUT_FLAG;  
    #else
    ADCPara.Flag &= ~ADC_ISROUT_FLAG; // ѡ��ADC_Read()������ȡ����ֵ
    #endif
    #if ((MODULE_CLASS == STM32F107XX)||(MODULE_CLASS == STM32F103XX))
    ADCPara.Flag |= ADC_TIM5;         // ��������TIM5��ΪAD������ʱ�� 
    #endif
    #if (MODULE_CLASS == STM32F407XX)
    ADCPara.Flag |= ADC_TIM14;        // ��������TIM14��ΪAD������ʱ�� 
    #endif
    
    ADCPara.AINum = ADC_CHNUM;
    ADCPara.AvgNum = ADC_AVGNUM;
    ADCPara.Freq = ADC_FREQ;                 // AD����Ƶ��, ÿ���Ӳ�������
    ADCPara.SampleTime = ADC_SAMPLE_TIME;    // ADC����ת��ʱ��
    ADCPara.pBuf = (INT16S *)&ADC_Buffer[0][0];
    //ADCPara.isr = ADC_ISRHook;     
    ADCPara.pAITab = AITab;
    
    // ��������AI1-AI10�ɼ�˳��, ��ʼ���ɼ�˳���
    for (n=0; n<16; n++) // Ĭ�ϱ����ʼ����0xFF;
    {
        AITab[n] = AI_ID_NONE; // AI_ID_NONE����0xFF 
    }
    
    #if (AI1_EN == 1)   // �ж�AI1ʹ��
    AITab[AI1_ID] = AI1; // ���òɼ�AI1˳��
    #endif
    #if (AI2_EN == 1)   // �ж�AI2ʹ��
    AITab[AI2_ID] = AI2;     // ���òɼ�AI2˳��
    #endif
    #if (AI3_EN == 1)   // �ж�AI3ʹ��
    AITab[AI3_ID] = AI3;     // ���òɼ�AI3˳��
    #endif
    #if (AI4_EN == 1)   // �ж�AI4ʹ��
    AITab[AI4_ID] = AI4;     // ���òɼ�AI4˳��
    #endif
    #if (AI5_EN == 1)   // �ж�AI5ʹ��
    AITab[AI5_ID] = AI5;     // ���òɼ�AI5˳��
    #endif
    #if (AI6_EN == 1)   // �ж�AI6ʹ��
    AITab[AI6_ID] = AI6;     // ���òɼ�AI6˳��
    #endif
    #if (AI7_EN == 1)   // �ж�AI7ʹ��
    AITab[AI7_ID] = AI7;     // ���òɼ�AI7˳��
    #endif
    #if (AI8_EN == 1)   // �ж�AI8ʹ��
    AITab[AI8_ID] = AI8;     // ���òɼ�AI8˳��
    #endif
    #if (AI9_EN == 1)   // �ж�AI9ʹ��
    AITab[AI9_ID] = AI9;     // ���òɼ�AI9˳��
    #endif
    #if (AI10_EN == 1)  // �ж�AI10ʹ��
    AITab[AI10_ID] = AI10;    // ���òɼ�AI10˳��
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
* Description: USB����ģʽӦ�ó�ʼ������;
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
    Para.Mode = USBHOST_MSC_MODE;   // ����U�̲���ģʽ
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
* Description: USB�豸ģʽӦ�ó�ʼ������;
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
    Para.Mode = USB_DEVICE_MSC_MODE;  // USB Mass Storageģʽ
    Para.lun = USB_MSC_LUN;
    #endif
    
    #if (USB_VCP_EN > 0)
    Para.Mode = USB_DEVICE_CDC_MODE;  // ���⴮��ģʽ
    Para.pRxBuf = USB_RxBuffer;       // �������ݻ���ָ��
    Para.RxBufLen = USB_RXBUF_SIZE;   // ���ջ��泤��
    #endif
    
    Para.Pin.DM = USB_DM;
    Para.Pin.DP = USB_DP;
    Para.Pin.VBUS = USB_VBUS; 
    
    #ifdef USB_CTRL
    IO_Init(USB_CTRL, IO_OUT_PP, IO_SPEED_2MHz); // ͨ���������ģʽ
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
* Description: ϵͳ������Ӧ�ó�ʼ������;
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
    
    SysLibPara.Flag |= SYS_CLK_HSE_FLAG; // ʹ���ⲿ����
    
    #if (UCOS_II_EN > 0)         //UCOS_IIʹ�� 
    SysLibPara.Flag |= SYS_OS_FLAG;
    #endif    
    
    #if (IAP_EN > 0)             // IAP����ʹ��
	SysLibPara.Flag |= SYS_NVIC_VECTORTAB_FLAG;
    SysLibPara.VectorTableAddr = NVIC_VECTOR_TABLE_ADDR;
    #else
    SysLibPara.VectorTableAddr = 0;
    #endif
        
    #if (SYS_TICK_EN > 0)        // ϵͳ��ʱ��ʹ��
	SysLibPara.Flag |= SYS_TICK_FLAG;
    #endif
    
    #if (DEBUG_SD_EN > 0)        // ������SD���������ʹ��
    SysLibPara.Flag |= SYS_DEBUG_SD_FLAG;
    #endif        
    
    #if (DEBUG_USB_EN > 0)       // ������USB�������ʹ��
    SysLibPara.Flag |= SYS_DEBUG_USB_FLAG;
    #endif          
    
    #if (DEBUG_NFLASH_EN > 0)       // ������NFlash�������ʹ��
    SysLibPara.Flag |= SYS_DEBUG_NFLASH_FLAG;
    #endif          
    
    #if (DEBUG_LIB_EN > 0)       // �����������������ʹ��
    SysLibPara.Flag |= SYS_DEBUG_LIB_FLAG;
    #endif          
    
    SysLibPara.Flag |=  SYS_DEBUG_MODBUS_FLAG; // ������MODBUS���������־ 
    //SysLibPara.Flag |= SYS_DEBUG_NET_FLAG;  // ������������������־ 
    
    SysLibPara.ModuleType = MODULE_TYPE;    // ����ģ������
    SysLibPara.OscClk = SYSCLK_HSE;         // �����ⲿʱ�Ӿ���Ƶ��
    SysLibPara.SysClk = SYSCLK;             // ����ϵͳʱ��Ƶ��
    SysLibPara.Tick   = SYS_TICK_T;         // ����ϵͳ��ʱ����ʱʱ��
    SysLibPara.DebugUart = DEBUG_UART;      // ����ѡ��printf�������Uart
    
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
* Description: Modbus�ӻ�(�豸)ģʽӦ�ó�ʼ������;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
#if (MODBUS_SLAVE_EN > 0) // Modbus�豸ģʽʹ��
void ModbusSlave_APPInit(void)
{
    INT16U i;
    
    #if (MODBUS_SLAVE_MODE == 0)           // MODBUS�ӻ�ͨ��ģʽ��0, RTU;  1, ASCII��; 
    ModbusPara.Flag = MODBUS_RTU_FLAG;     // RTUͨ��ģʽ
    #else
    ModbusPara.Flag = MODBUS_ASCII_FLAG    // ASCIIͨ��ģʽ
    #endif

    ModbusPara.CoilsBaseAddr = MODBUS_COILS_BASEADDR;           // ��Ȧ�Ĵ�������ַ;
    ModbusPara.DisInputBaseAddr = MODBUS_DISINPUT_BASEADDR;     // ��ɢ�������Ĵ�������ַ;
    ModbusPara.HoldRegBaseAddr = MODBUS_HOLDREG_BASEADDR;       // ���ּĴ�������ַ;
    ModbusPara.InputRegBaseAddr = MODBUS_INPUTREG_BASEADDR;     // ����Ĵ�������ַ;    
    ModbusPara.MaxCoils = MODBUS_MAX_COILS;                     // MODBUS�ӻ������Ȧ����(��д,���ù�����:1,5,15);
    ModbusPara.MaxDisInput = MODBUS_MAX_DISINPUT;               // MODBUS�ӻ������ɢ������(ֻ��,���ù�����:2);
    ModbusPara.MaxHoldReg = MODBUS_MAX_HOLDREG;                 // MODBUS�ӻ���󱣳ּĴ���(��д,���ù�����:3,6,16,23)����;	 
    ModbusPara.MaxInputReg = MODBUS_MAX_INPUTREG;               // MODBUS�ӻ��������Ĵ���(ֻ��,���ù�����:4)����;
    
    ModbusPara.pCoils = ModbusCoils;           // �����Ȧ�Ĵ���ָ��
    ModbusPara.pDisInput = ModbusDisInput;     // ������ɢ�������Ĵ���ָ��
    ModbusPara.pHoldReg = ModbusHoldReg;       // ���ּĴ���ָ��
    ModbusPara.pInputReg = ModbusInputReg;     // ����Ĵ���ָ��
    
    ModbusPara.pData = (MODBUS_DATA *)&ModbusData.Flag;       // ��������ָ��     
    
    // ��ʼ�������Ȧ����
    for (i=0; i<((MODBUS_MAX_COILS-1)/8 + 1); i++)  
    {
        ModbusPara.pCoils[i] = 0;
    }
    
    // ��ʼ��������ɢ����������
    for (i=0; i<((MODBUS_MAX_DISINPUT-1)/8 + 1); i++)
    {
        ModbusPara.pDisInput[i] = 0;
    }
    
    // ��ʼ�����ּĴ���
    for (i=0; i<MODBUS_MAX_HOLDREG; i++)
    {
        ModbusPara.pHoldReg[i] = 0;
    }
    
    // ��ʼ������Ĵ���
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
* Description: IAPģʽӦ�ó�ʼ������;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
#if (IAP_EN > 0) // IAPģʽʹ��
void IAP_APPInit(void)
{
    INT32S flag, i;
    IAP_PARA Para;
    
	Para.Flag = 0;
    Para.Flag |= IAP_YMODEM_FLAG|IAP_DEBUG_FLAG; // ����ʱ֧�ֳ����ն�YmodemЭ�鼰BOOT����������;
    
	#if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F107XX))
		#if ((DEBUG_UART == UART1_ID)&&(UART1_REMAP == UART_REMAP_1))
		Para.Flag |= IAP_UART_REMAP1_FLAG; // IAP���ڹܽ�REMAP1��־
		#endif
	
		#if ((DEBUG_UART == UART2_ID)&&(UART2_REMAP == UART_REMAP_1))
		Para.Flag |= IAP_UART_REMAP1_FLAG; // IAP���ڹܽ�REMAP1��־ 
		#endif
	
		#if (DEBUG_UART == UART3_ID)
			#if (UART3_REMAP == UART_REMAP_1)
			Para.Flag |= IAP_UART_REMAP1_FLAG; // IAP���ڹܽ�REMAP1��־ 
			#endif
			#if (UART3_REMAP == UART_REMAP_2)
			Para.Flag |= IAP_UART_REMAP2_FLAG; // IAP���ڹܽ�REMAP2��־ 
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
	
    Para.Moduel = MODULE_TYPE;              // ����ģ������
    Para.HSEClk = SYSCLK_HSE; 
    Para.UartID = DEBUG_UART;    // ����ID, Debug��Ϣ�������ѡ��    
    Para.ABPageSize = IAP_AB_PAGESIZE; // ����A/B/AB��ҳ��С    
    Para.BootPin = IO_NONE;
    for (i=0; i<12; i++)
    {    
        Para.FileName[i] = 0;
    }
    
    // A����ʼ��
	Para.Area[IAP_A_ID].StartPage = IAP_A_STARTPAGE;
    Para.Area[IAP_A_ID].PageNum   = IAP_A_PAGENUM;

    // B����ʼ��
	Para.Area[IAP_B_ID].StartPage = IAP_B_STARTPAGE;
    Para.Area[IAP_B_ID].PageNum   = IAP_B_PAGENUM;

    // AB����ʼ��
	Para.Area[IAP_AB_ID].StartPage = IAP_AB_STARTPAGE;
    Para.Area[IAP_AB_ID].PageNum   = IAP_AB_PAGENUM;

    // C����ʼ��
    #if (SPIFLASH_TYPE == W25QXX)
	Para.CPageSize = IAP_C_W25QXX_PAGESIZE;                  // ����C��ҳ��С
    Para.Area[IAP_C_ID].StartPage = IAP_C_W25QXX_STARTPAGE;
    Para.Area[IAP_C_ID].PageNum   = IAP_C_W25QXX_PAGENUM;
    #endif
    #if (SPIFLASH_TYPE == AT45DBXX)
    Para.CPageSize = IAP_C_AT45DBXX_PAGESIZE;                  // ����C��ҳ��С
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
* Description: FSMC���߳�ʼ������;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
#if (FSMC_EN > 0)       // FSMC����ʹ��
void FSMC_APPInit(void) // FSMC���߳�ʼ��
{
    FSMC_PARA Para;
    INT32S flag;
    
    Para.Flag = 0;
    #if (SRAM_EN >0 )
    Para.Flag |= FSMC_SRAM_EN; // ������չRAMʹ�ܱ�־
    #endif
    
    #if (EXBUS_EN >0 )
    Para.Flag |= FSMC_EXBUS_EN;// ������չ����ʹ�ܱ�־
    #endif
    
    #if (NFLASH_EN >0 )
        Para.Flag |= FSMC_NFLASH_EN; // ������չNANDʹ�ܱ�־
        #if (NFLASH_ECCEN >0 )
        Para.Flag |= FSMC_NFLASH_ECCEN; // Nand flash ECCʹ�ܱ�־
        #endif
        #if (NFLASH_RBIT_EN >0 )         // RB�ź��ж�ʹ��
        Para.Flag |= FSMC_NFLASH_ITFLAG; // Nand flash �жϲ�����־
        #endif
    #endif
    
    #if (LWIP_EN >0 )
    Para.Flag |= FSMC_NET_EN;  // ������չNETʹ�ܱ�־
    #endif
    
    Para.ECCSize = NFLASH_ECC_SIZE;    // Nand Flash ECCҳ���С
    Para.SRAMSize = SRAM_SIZE;         // ��չSRAM����;
    Para.EXBusAddrSet = EXBUS_ADDSET;  // �ⲿ���ߵ�ַ����ʱ��(��Χ��0~15)��ʵ�ʽ���ʱ��(EXBUS_ADDSET+1)��HCLK;
    Para.EXBusDataSet = EXBUS_DATAST;  // �ⲿ�������ݱ���ʱ��(��Χ��1~255)��ʵ�ʱ���ʱ�䣺��(EXBUS_DATAST+3)��HCLK, д(DATAST+1)��HCLK;
    Para.EXBusTurn = EXBUS_TURN;       // �ⲿ���߻ָ�ʱ��(��Χ��0~15)��ʵ�ʻָ�ʱ��(EXBUS_TURN+1)��HCLK
      
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
* Description: NAND FLASHӦ�ó�ʼ������;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
#if (NFLASH_EN > 0)       // NAND FLASHʹ��
void NFlash_APPInit(void) // NAND FLASHӦ�ó�ʼ��
{
    NFLASH_PARA Para;
    INT32S flag;
    INT8U *p;
    
    Para.Flag = 0;    
    //#if (NFLASH_ECCEN > 0) // ECCʹ��
    //Para.Flag |= NFLASH_ECCEN_FLAG; // ����ECCʹ�ܱ�־
    //#endif
    //Para.ECCSize = NFLASH_ECC_SIZE;
    
    Para.BlkNum = NFLASH_BLOCK_NUM;       // NAND �ܿ���
    Para.PagePerBlk = NFLASH_BLOCK_SIZE;  // NAND ÿ�������ҳ�� 
    Para.PageSize = NFLASH_PAGE_SIZE;     // ҳ��С 
    Para.PageNum = NFLASH_BLOCK_NUM*NFLASH_BLOCK_SIZE;  // ��ҳ��
    Para.BadBlkNum = NFLASH_MAX_BAD_BLOCK;              // ��������
    Para.pBadBlkFlag = (INT8U *)&NFlashBadBlkFlag[0];   // ������ָ��
    Para.pBadTab = (INT16U *)&NFlashBadTab[0];	        // �����滻��ָ��
    Para.pBlkBuf = (INT8U *)&NFlashBlkBuffer[0][0];     // �黺��ָ��
    
    //#if (NFLASH_ECCEN > 0) // ECCʹ��
    Para.pBlkSpareBuf = (INT8U *)&NFlashBlkSpareBuffer[0][0]; // ��������򻺴�ָ��
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
    
    p = (INT8U *)NFlash_Ctrl(CMD_NFLASH_RDID, 0);           // ��ȡNand Flash ID
    #if (DEBUG_APP_EN > 0)
    if (UserVars.Para.ATFlag&AT_INFO_FLAG)
    {
        printf("AT+INFO=NFLASH ID,%02X %02X %02X %02X %02X\r\n", p[0],p[1],p[2],p[3],p[4]);
    }
    #endif
    
//    flag = NFlash_Ctrl(CMD_NFLASH_BADBLK, 0);  // ��ʼ��Nand Flash�����
//    if (flag == ERR_FALSE)
//    {
//        #if (DEBUG_APP_EN > 0)
//        printf("NFlash: ���鴦��ʧ��\r\n");
//        #endif
//    }
    //#endif
    
}
#endif

/***********************************************************************************
* Function: CH455_APPInit;
*
* Description: CH455Ӧ�ó�ʼ������;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
#if (CH455_EN > 0)       // CH455ʹ��
#include "CH455.h"
void CH455_APPInit(void) // CH455Ӧ�ó�ʼ��
{
    INT32S flag;
    CH455_PARA CH455Para;
    
    CH455Para.Mode = CH455_MODE;    // ѡ��I2Cģʽ
    CH455Para.INTPin = CH455_INT;
    CH455Para.SCLPin = CH455_SCL;
    CH455Para.SDAPin = CH455_SDA;
    CH455Para.I2C    = CH455_I2C;    
    
    CH455_Init(&CH455Para);  // ��������оƬ��ʼ��
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
        printf("* Copyright (c), 2004-2020, ������Ƕ���Ƶ������޹�˾\r\n");
        printf("*            All rights reserved.\r\n");
        printf("*\r\n");
        printf("* �����Ա: EmbedARM\r\n"); 
        printf("* ��Ʒ����: %s\r\n", PRODUCT_NAME);        
        printf("* ��Ʒ�ͺ�: %s\r\n", PRODUCT_MODEL);
        printf("* Ӳ���汾: %d.%d%d\r\n", HW_VERSION/100, (HW_VERSION%100)/10, HW_VERSION%10);
        printf("* ����汾: %d.%d%d\r\n", SW_VERSION/100, (SW_VERSION%100)/10, SW_VERSION%10);
        printf("* �̼�����: %s\r\n", BIN_NAME);
        printf("* ��������: %s\r\n", SW_DATE);

        ver = SysLib_Ctrl(CMD_SYSLIB_READ_VERSION, 0);      // ��ȡ������汾
        printf("*\r\n* ������汾: %d.%d%d\r\n", ver/100, (ver%100)/10, ver%10);			
        p = (INT8U *)SysLib_Ctrl(CMD_SYSLIB_READ_DATE, 0);  // ��ȡ��������������
        printf("* ����������: %s\r\n", p);
        
        #if (UCOS_II_EN > 0)
        printf("*\r\n* ����ϵͳ: UCOS-II V2.86\r\n");
        #else
        printf("*\r\n* ����ϵͳ: ��\r\n");
        #endif
        printf("*\r\n* ����IP�Ͷ˿ں�: %d.%d.%d.%d, %d\r\n", UserVars.Para.LocalIP[0], UserVars.Para.LocalIP[1], UserVars.Para.LocalIP[2], UserVars.Para.LocalIP[3], UserVars.Para.LocalPort);
        printf("* ������IP�Ͷ˿ں�: %d.%d.%d.%d, %d\r\n", UserVars.Para.DscIP[0], UserVars.Para.DscIP[1], UserVars.Para.DscIP[2], UserVars.Para.DscIP[3], UserVars.Para.DscPort);
        printf("* ����IP: %d.%d.%d.%d\r\n", UserVars.Para.Gataway[0], UserVars.Para.Gataway[1], UserVars.Para.Gataway[2], UserVars.Para.Gataway[3]);
        printf("* MAC��ַ: %02X %02X %02X %02X %02X %02X\r\n", UserVars.Para.MACAddr[0], UserVars.Para.MACAddr[1], UserVars.Para.MACAddr[2], UserVars.Para.MACAddr[3], UserVars.Para.MACAddr[4], UserVars.Para.MACAddr[5]);
        
        printf("*\r\n* ��˾����: embedarm@126.com\r\n");
        printf("* ��˾��ַ: www.embedarm.com\r\n");
        printf("*****************************************************\r\n");
    }
	#endif    
}

/***********************************************************************************
* Function: UserVars_Init;
*
* Description: �û�ȫ�ֱ�����ʼ������;
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
    
    UserVars.Flag = 0;          // ���ֱ�־λ
    UserVars.KeyVal = 0;        // ������ʶ����
    UserVars.Key = 0;           // ����ֵ
    //UserVars.DIVal = 0;         // DI�����ʶ����
    UserVars.DI = 0;	        // DIN����
    
    // TIM��ʼ��
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
        UserVars.TIMx_ITFlag[i] = 0;   // TIMx�жϱ�־
    }
    
    UserVars.DO = 0;	        // DOUT���
	//UserVars.Status = 0;   	    // ϵͳ״̬
	UserVars.TaskRunStatus = 0; // ����ϵͳ��������״̬ 
    UserVars.TimerCount = 0;
    
    //UserVars.Para.ATFlag = 0xffff;  // ʹ�����е�����Ϣ���
}

/***********************************************************************************
* Function: DMA_APPInit;
*
* Description: DMA_APPInitӦ�ó�ʼ������;
* 
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
#if ((DMA1_EN > 0)||(DMA2_EN > 0)) // DMA1-DMA2����ʹ��
void DMA_APPInit(void)             // DMA1-DMA2Ӧ�ó�ʼ������;	
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
* Description: �������ʼ������;
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
    SysLib_APPInit();    // ϵͳ������Ӧ�ó�ʼ������;
    
    #if (IWDG_EN > 0)           // IWDG����ʹ��
    IWDG_Init(IWDG_TIME);       // ��ʼ�����Ź�ʱ��
	IWDG_Ctrl(CMD_IWDG_ENA);    // ʹ�ܿ��Ź�
   	IWDG_Ctrl(CMD_IWDG_CLEAR);  // ι��
    #endif
    
    #if ((DMA1_EN > 0)||(DMA2_EN > 0)) // DMA1-DMA2����ʹ��
    DMA_APPInit();      // DMA1-DMA2Ӧ�ó�ʼ������;	
    #endif
        
    UserVars_Init();     // �û�ȫ�ֱ�����ʼ��
    EEPROM_APPInit();    // EEPROMӦ�ó�ʼ������;   
    APP_ParaRead((USER_VARS *)&UserVars.Flag); // ��ȡ�û�����
    
    #if ((UART1_EN > 0)||(UART2_EN > 0)||(UART3_EN > 0)||(UART4_EN > 0)||(UART5_EN > 0)||(UART6_EN > 0)) // UART1-UART6����ʹ��
    Uart_APPInit();      // UART1-UART6Ӧ�ó�ʼ������;	
    #endif    
    
    Logo_Out();          // ���logo��ӡ���
        
    #if ((I2C2_EN > 0)||(I2C3_EN > 0)) // I2C2-I2C3����ʹ��
    I2C_APPInit();      // I2C2-I2C3Ӧ�ó�ʼ������;	
    #endif    

    #if (IAP_EN > 0)    // IAP����ʹ��
    IAP_APPInit();      // IAPӦ�ó�ʼ��
    #endif

    #if (IWDG_EN > 0)           // IWDG����ʹ��
   	IWDG_Ctrl(CMD_IWDG_CLEAR);  // ι��
    #endif

    IO_APPInit();      // ����IO��ʼ��
	EXTI_APPInit();    // �ⲿ�жϺ��¼�Ӧ�ó�ʼ��   
    
    #if (BKP_EN > 0)   // BKP����ʹ��
    BKP_Init();        // BKPӦ�ó�ʼ��
    #endif

    #if (MODBUS_SLAVE_EN > 0)   // Modbus�豸ģʽ����ʹ��
    ModbusSlave_APPInit();      //Modbus�ӻ�(�豸)ģʽӦ�ó�ʼ������;
    #endif

    #if (IWDG_EN > 0)           // IWDG����ʹ��
   	IWDG_Ctrl(CMD_IWDG_CLEAR);  // ι��
    #endif

    #if (RTC_EN > 0)            // RTC����ʹ��
    RTC_APPInit();              // RTCӦ�ó�ʼ������;
    #endif

    #if ((SPI1_EN > 0)||(SPI2_EN > 0)||(SPI3_EN > 0)) // SPI1~SPI3����ʹ��
    SPI_APPInit();	            // SPI����Ӧ�ó�ʼ��
    #endif
     
    #if (ADC_EN>0)              // ADC����ʹ��
    ADC_APPInit();              // ADCӦ�ó�ʼ������;
    #endif 
    
    #if ((DAC1_EN>0)||(DAC2_EN>0)) // DAC1-2����ʹ��
    DAC_APPInit();                 // DACӦ�ó�ʼ��
    #endif
    
    #if ((TIM1_EN > 0)||(TIM2_EN > 0)||(TIM3_EN > 0)||(TIM4_EN > 0)||(TIM5_EN > 0)||(TIM6_EN > 0)||(TIM7_EN > 0)||(TIM8_EN > 0)  \
    ||(TIM9_EN > 0)||(TIM10_EN > 0)||(TIM11_EN > 0)||(TIM12_EN > 0)||(TIM13_EN > 0)||(TIM14_EN > 0)) //TIM1-TIM14����ʹ��
    TIM_APPInit();     // ��ʱ��Ӧ�ó�ʼ��
    #endif
    
    #if ((FCLK1_EN>0)||(FCLK2_EN>0)||(FCLK3_EN>0)||(FCLK4_EN>0)||(FCLK5_EN>0)||(FCLK6_EN>0)||(FCLK7_EN>0)||(FCLK8_EN>0)) //FCLK1-FCLK8����ʹ��
    FCLK_APPInit();    // FCLK����Ӧ�ó�ʼ��
    #endif
    
    #if ((PWM1_EN>0)||(PWM2_EN>0)||(PWM3_EN>0)||(PWM4_EN>0)||(PWM5_EN>0)||(PWM6_EN>0)||(PWM7_EN>0)||(PWM8_EN>0)) //PWM1-PWM8����ʹ��
    PWM_APPInit();     // PWM���Ӧ�ó�ʼ��
    #endif
    
    #if ((CAN1_EN>0)||(CAN2_EN>0)) // CAN1-2����ʹ��
    CAN_APPInit();                 // CAN1-2Ӧ�ó�ʼ��
	#endif
    
    #if (SPIFLASH_EN > 0)   // SPI FLASH����ʹ��
    SPIFlash_APPInit();     // SPI Flash(W25QXX��AT45DBXX)Ӧ�ó�ʼ��
    #endif
   
    
    #if (SDCARD_EN > 0)     // SD������ʹ��
    SD_APPInit();           // SD��Ӧ�ó�ʼ��
    #endif
    
    #if (IWDG_EN > 0)           // IWDG����ʹ��
   	IWDG_Ctrl(CMD_IWDG_CLEAR);  // ι��
    #endif

    #if ((USB_HOST_EN > 0)&&(MODULE_CLASS != STM32F103XX)) // USB����ģʽ����ʹ��
    USBH_APPInit();         // USB����ģʽӦ�ó�ʼ��
    #endif
    
    #if (USB_DEVICE_EN > 0) // USB�豸ģʽ����ʹ��
    USBD_APPInit();         // USB�豸ģʽӦ�ó�ʼ��
    #endif
    
    #if (FSMC_EN > 0)       // FSMC��������ʹ��
    FSMC_APPInit();         // FSMC���߳�ʼ��
    #endif
            
    #if (NFLASH_EN > 0)     // NAND FLASH����ʹ��
    NFlash_APPInit();       // NAND FLASHӦ�ó�ʼ��
    #endif
                        
	#if ((LWIP_EN >0)&&((MODULE_CLASS == STM32F107XX)||(MODULE_CLASS == STM32F407XX))) // ��������ʹ��
	NET_APPInit();	        // ��������ʹ��
    #endif
    
    #if (CH455_EN > 0)      // CH455����ʹ��
    CH455_APPInit();       // CH455Ӧ�ó�ʼ��
    #endif
}


/***********************************************************************************/
// �ļ�����
/***********************************************************************************/
