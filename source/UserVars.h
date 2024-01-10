/************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: UserVars.h
* Project  : STM32F1XX/4XXϵ��ģ�����
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.00
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: ���ļ������û�Ӧ�ó��򹫹�ȫ�ֱ�������ͷ�ļ�, �ͻ����԰�Ӧ�õ�ȫ�ֱ������õ�����;
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
#ifndef __USER_VARS_H 
#define __USER_VARS_H 

/************************************************************************************/
// �����ⲿͷ�ļ�
/************************************************************************************/
#include "const.h"	
#include "config.h"	
#include "timer.h"	
	
/************************************************************************************
*
*       ϵͳ״̬��־����
*
*************************************************************************************/
#define SYNC_HEAD         0x5AA5    // ���ò���ͬ��ͷ����
#define CONFIG_PARA_ADDR  0         // ���ò����洢EEPROM��ַ

// ���ò���Flag����
#define SPIFLASH_FORMAT_FLAG  0x0001 // SPI FLASH��ʽ����־
#define NFLASH_FORMAT_FLAG    0x0002 // NAND FLASH��ʽ����־

#define AT_DEBUG_FLAG         0x0004 // ATָ��������ʹ�ܱ�־

#define AT_MODE_TIM           0      // ��ʱ�ɼ����������ģʽ
#define AT_MODE_START         10     // �����ɼ����������ģʽ
typedef struct
{
    INT8U   Mode;     // ����ģʽ
    INT16U  t1;       // ��ʱɨ��ʱ��    
    INT16U  t2;       // ���Է���ʱ��
}AT_PARA;

typedef struct
{
    INT8U   Mode;     // ����ģʽ
    INT16U  val;      // AO����������ֵ    
    INT16U  t;        // ���Է���ʱ��
}AT_AO_PARA;

typedef struct
{
    INT32U  Baud;     // UART������
    INT8U   bits;     // ����λ��
    INT8U   PS;       // У��λ    
    INT8U   Stop;     // ֹͣλ 
}AT_UART_PARA;

typedef struct
{
    INT32U  Baud;        // UART������
    INT8U   IDE;         // ֡����: 0, ��׼֡; 1, ��չ֡;
    INT16U  Filter[14];  // �˲��Ĵ���, ��ʱ����16λ    
}AT_CAN_PARA;


#define AT_DI_FLAG      0x0001   // DI AT�����־
#define AT_DO_FLAG      0x0002   // DO AT�����־
#define AT_AI_FLAG      0x0004   // AI AT�����־
#define AT_AO_FLAG      0x0008   // AO AT�����־
#define AT_PWM_FLAG     0x0010   // PWM AT�����־
#define AT_FCLK_FLAG    0x0020   // FCLK AT�����־

#define AT_UART_FLAG    0x0040   // UART AT�����־
#define AT_CAN_FLAG     0x0080   // CAN AT�����־
#define AT_RTC_FLAG     0x0100   // RTC AT�����־
#define AT_NET_FLAG     0x0200   // NET AT�����־
#define AT_TIM_FLAG     0x0400   // TIMER AT�����־
#define AT_USB_FLAG     0x0800   // USB AT�����־
#define AT_FILE_FLAG    0x1000   // FILE AT�����־

#define AT_INFO_FLAG    0x8000   // ���� AT�����־

#define AT_ALL_FLAG     0x9FFF   // ����AT�����־


#pragma pack (1)
typedef struct
{
    INT16U	Sync;	        // ����ͷ��5AA5
	INT16U 	Flag;   	    // ��־
	INT8U 	ModbusID; 	    // Modbus ID
    INT8U   NetType;        // ��������
    INT8U   NetMode;        // ���繤��ģʽ
    INT8U   LocalIP[4];     // ����IP
    INT16U  LocalPort;      // �����˿�
    INT8U   SubnetMask[4];  // ������������
    INT8U   Gataway[4];     // ��������
    INT8U   DscIP[4];       // ������IP
    INT16U  DscPort;        // �������˿�         
    INT8U   MACAddr[6];	    // ����MAC��ַ
    
    INT32U  ATFlag;       // ATָ�����ʹ�ܱ�־
    AT_PARA DI;           // DI����
    AT_PARA DO;           // DO����
    AT_PARA AI;           // AI����
    AT_AO_PARA AO;        // AO����
    AT_PARA PWM[PWM_NUM];       // PWM����
    AT_PARA FCLK[FCLK_NUM];     // FCLK����
    AT_UART_PARA Uart[6]; // Uart����
    AT_CAN_PARA  CAN[2];  // CAN����
    INT16U	rev[4];         	//2  ����	
	INT16U	CRC16;         	//2  У��λ			  
}CONFIG_PARA;
#pragma pack()

#define CONFIG_PARA_LEN	 sizeof(CONFIG_PARA)

#define TASK_ADCDAC_FLAG      0x00000004 
#define TASK_MODBUS_FLAG      0x00000008 	 
#define TASK_FILE_FLAG		  0x00000010
#define TASK_IO_FLAG		  0x00000040
#define TASK_UARTCAN_FLAG	  0x00000080
#define TASK_PWMFCLK_FLAG	  0x00000100
#define TASK_LWIP_FLAG		  0x00000200
#define TASK_DTU_FLAG		  0x00000400 

#define TASK_FLAG   (TASK_ADCDAC_FLAG*TASK_ADCDAC_EN + TASK_MODBUS_FLAG*TASK_MODBUS_EN + \
					TASK_FILE_FLAG*TASK_FILE_EN + \
					TASK_IO_FLAG*TASK_IO_EN + TASK_UARTCAN_FLAG*TASK_UARTCAN_EN + \
					TASK_PWMFCLK_FLAG*TASK_PWMFCLK_EN + TASK_LWIP_FLAG*TASK_LWIP_EN + \
					TASK_DTU_FLAG*TASK_DTU_EN)

// �������⼰ϵͳ���ȫ�ֱ�������, �û���Ҫ�޸����
#define  USBD_CONNECT_FLAG      0x01000000  // USB�豸����״̬��־
#define  USBH_CONNECT_FLAG      0x02000000  // USB��������״̬��־
#define  SD_USB_FLAG            0x04000000  // SD���������USB(USB Mass Storage)ռ�ñ�־
#define  SPIFLASH_USB_FLAG      0x08000000  // SPI Flash�������USB(USB Mass Storage)ռ�ñ�־
#define  NFLASH_USB_FLAG        0x10000000  // Nand Flash�������USB(USB Mass Storage)ռ�ñ�־
#define  SD_FATFS_FLAG          0x20000000  // SD����FatFSռ�ñ�־
#define  SPIFLASH_FATFS_FLAG    0x40000000  // SPI Flash��FatFSռ�ñ�־
#define  NFLASH_FATFS_FLAG      0x80000000  // Nand Flash��FatFSռ�ñ�־
typedef struct
{
    INT32U Flag;        // ��־
    INT32U APIWaitFlag; // ������ȴ��¼���־
}LIBSYS_VARS;

// ADC��������
#define ADC_READ_FLAG      0x0001 // ADC��ȡ���ݱ�־
#define ADC_MAX_BUF_SIZE   10     // ADC����buf��С
typedef struct
{
    INT16U   Flag;      // ADC������־
	INT16U   len;       // ADC����ֵ����
	INT16U   buf[ADC_MAX_BUF_SIZE];  // ADC����ֵ
}ADC_VARS;

typedef struct
{
    INT8U    Mode;      // FCLK����ģʽ
	INT16U   Rate;      // ռ�ձ�
	INT32U   Freq[4];   // ����Ƶ��
	INT32S   cnt;       // FCLK����ֵ
    
    INT32S   QEICount;  // 
}FCLK_VARS;

typedef struct
{
    INT8U    ArgcNum;     // 0���������� 1��һ������ 2 ���������� 3 ���������� 4���ĸ�����
	//��������Ĭ��INT32U���ͣ�������������Ϳ���ǿ������ת��
	INT32U   FuncArgc1;   // ��������1
	INT32U   FuncArgc2;   // ��������2
	INT32U   FuncArgc3;   // ��������3
	INT32U   FuncArgc4;   // ��������4
	//����ĺ���Ĭ�Ϸ���INT32U���ͣ�������������Ϳ���ǿ������ת��
	INT32U (*FuncZeroArgc)(void);
	INT32U (*FuncOneArgc)(INT32U);
	INT32U (*FuncTwoArgc)(INT32U,INT32U);
	INT32U (*FuncThreeArgc)(INT32U,INT32U,INT32U);
	INT32U (*FuncFourArgc)(INT32U,INT32U,INT32U,INT32U);
}APP_FuncMboxMsgStruct;


// Flag���ֱ�־λ����
#define  RTC_SECIT_FLAG         0x00000001  // RTC���жϱ�־
#define  RTC_ALRIT_FLAG         0x00000002  // RTC�����жϱ�־
#define  SPIFLASH_WK_FLAG       0x00000004  // SPI FLASH���ڹ����б�־, �������־
#define  SD_WK_FLAG             0x00000008  // SD�����ڹ����б�־
#define  NET_PHY_LINK_FLAG      0x00000010  // ����Ӳ���豸����״̬��־
#define  OS_START_FLAG          0x00000020  // ����ϵͳ�������б�־

// OKFlag ���Ӹ����ܲ��Գɹ���־
#define  SPIFLASH_OK_FLAG       0x00000001  // SPI FLASH���Գɹ���־
#define  NFLASH_OK_FLAG         0x00000002  // NAND FLASH���Գɹ���־
#define  EEPROM_OK_FLAG         0x00000004  // EEPROM���Գɹ���־
#define  SRAM_OK_FLAG           0x00000008  // ��չSRAM���Գɹ���־
#define  SD_OK_FLAG             0x00000010  // SD�����Գɹ���־
#define  UDISK_OK_FLAG          0x00000020  // UDISK���Գɹ���־
#define  USB_OK_FLAG            0x00000040  // USB�豸���Գɹ���־
#define  NET_LINK_OK_FLAG       0x00000080  // �������ӷ�������ͻ��˳ɹ���־
#define  NET_HWLINK_OK_FLAG     0x00000100  // ����Ӳ��(����)���ӳɹ���־



#define  DATABUF_SIZE   512

// EXTIFlag EXTI�жϱ�־
#define  EXTI0_ISR_FLAG         0x00000001  // EXTI0�жϱ�־
#define  EXTI1_ISR_FLAG         0x00000002  // EXTI1�жϱ�־
#define  EXTI2_ISR_FLAG         0x00000004  // EXTI2�жϱ�־
#define  EXTI3_ISR_FLAG         0x00000008  // EXTI3�жϱ�־
#define  EXTI4_ISR_FLAG         0x00000010  // EXTI4�жϱ�־
#define  EXTI5_ISR_FLAG         0x00000020  // EXTI5�жϱ�־
#define  EXTI6_ISR_FLAG         0x00000040  // EXTI6�жϱ�־
#define  EXTI7_ISR_FLAG         0x00000080  // EXTI7�жϱ�־
#define  EXTI8_ISR_FLAG         0x00000100  // EXTI8�жϱ�־
#define  EXTI9_ISR_FLAG         0x00000200  // EXTI9�жϱ�־
#define  EXTI10_ISR_FLAG        0x00000400  // EXTI10�жϱ�־
#define  EXTI11_ISR_FLAG        0x00000800  // EXTI11�жϱ�־
#define  EXTI12_ISR_FLAG        0x00001000  // EXTI12�жϱ�־
#define  EXTI13_ISR_FLAG        0x00002000  // EXTI13�жϱ�־
#define  EXTI14_ISR_FLAG        0x00004000  // EXTI14�жϱ�־
#define  EXTI15_ISR_FLAG        0x00008000  // EXTI15�жϱ�־

#define  EXTI16_PVD_FLAG            0x00010000  // EXTI16�жϱ�־
#define  EXTI17_RTCAlarm_FLAG       0x00020000  // EXTI17�жϱ�־
#define  EXTI18_USBWakeUp_FLAG      0x00040000  // EXTI18�жϱ�־
#define  EXTI19_NETWakeUp_FLAG      0x00080000  // EXTI19�жϱ�־
#define  EXTI20_USBHSWakeUp_FLAG    0x00100000  // EXTI20�жϱ�־
#define  EXTI21_RTCTSE_FLAG         0x00200000  // EXTI21�жϱ�־
#define  EXTI22_RTCWakeUp_FLAG      0x00400000  // EXTI22�жϱ�־

#define ALL_FF_8 0xff
#define ALL_FF_16 0xffff
#define ALL_FF_32 0xffffffff
//#pragma pack (1)
typedef struct
{ 
    INT32U   Flag;          // ���ֱ�־λ
    INT32U   TaskRunStatus; // ����ϵͳ��������״̬ 
    INT32U   EXTIFlag;      // EXTI�жϱ�־
    INT32U   OKFlag;        // ���Ӹ����ܲ��Գɹ���־
    INT32U   DI;	        // DI����ֵ: DI1=bit0, DI2=bit1; �Դ�����DI32=bit31; ��ֵΪ��MCU�˿ڶ�ȡ��ʵ��ֵ
    INT32U   DI_P;	        // ���ư�˿�����ֵ: DI1_P=bit0, DI2_P=bit1; �Դ�����DI32_P=bit31; ��ֵΪ���ذ�˿������ʵ��ֵ, 
                            // һ������ڲ��й���������NPN�����ܷ���ȵ�·, ��DI_P = ~PI
    INT32U   DO;	        // DO���ֵ: DO1=bit0, DO2=bit1; �Դ�����DO32=bit31; 
    INT16U   SW;            // ���뿪��ֵ: S1=bit0, S2=bit1; �Դ�����S16=bit15; 
    INT8U    Key;           // ����ֵ
    INT32U   KeyVal;        // ������ʶ����
    INT16U   AO[2];         // AO���������־
    ADC_VARS ADC;
    INT32U   PWM_ITFlag[PWM_NUM];   // PWM�жϱ�־
    PWM_CTRL  PWMPara[PWM_NUM];	
    FCLK_VARS FCLK[FCLK_NUM];
	
	INT32U Tim6Pul;
	INT8U Tim6Dir;
    #if (MODULE_CLASS == STM32F107XX)
    INT16U   TIMx_ITFlag[7];   // TIM1-7�жϱ�־
    #endif
    #if (MODULE_CLASS == STM32F103XX)
    INT16U   TIMx_ITFlag[7];   // TIM1-8�жϱ�־
    #endif
    #if (MODULE_CLASS == STM32F407XX)
    INT16U   TIMx_ITFlag[14];  // TIM1-8�жϱ�־
    #endif
    #if (MODULE_TYPE == STM32F103ZE)
    INT16U   FSMC_ITFlag;
    #endif
    
    #if ((PWM1_EN > 0)&&(PWM1_MODE==PWM_DMA))
    PWM_WRITE PWM1WritePara;
    #endif
    #if ((PWM2_EN > 0)&&(PWM2_MODE==PWM_DMA))
    PWM_WRITE PWM2WritePara;
    #endif
    #if ((PWM3_EN > 0)&&(PWM3_MODE==PWM_DMA))
    PWM_WRITE PWM3WritePara;
    #endif
    #if ((PWM4_EN > 0)&&(PWM4_MODE==PWM_DMA))
    PWM_WRITE PWM4WritePara;
    #endif
	
	INT32U   TimerCount;
    INT8U    buf[DATABUF_SIZE+1];  // ��Ļ�������ݽ���buff
    INT16U   UartData;      // Uart��������
    
    LIBSYS_VARS  LibSys;    // 
    CONFIG_PARA  Para;      //���ò���
}USER_VARS;	 
//#pragma pack() 
extern USER_VARS UserVars;	     // �û�����

#endif
/***********************************************************************************/
// �ļ�����
/***********************************************************************************/
