/************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: rtc.h
* Project  : STM32F1XX/4XXϵ��ģ��������
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: ���ļ���RTCӲ����������ͷ�ļ�;
*
* Others: none;
*
* Function List: 
*          1. INT32S RTC_Init(void);
*          2. INT32S RTC_Read(RTC_TIME *rtc);
*          3. INT32S RTC_Write(RTC_TIME *rtc);
*          4. INT32U RTC_Ctrl(INT8U Cmd, INT32U Para, RTC_TIME *rtc);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/
#ifndef __RTC_H 
#define __RTC_H 

/************************************************************************************/
// �����ⲿͷ�ļ�
/************************************************************************************/
#include "const.h"
#include "config.h"

/*************************************************************************************/
//  ����ʱ�����ݽṹ����, ���¶�����Բ����޸�
/*************************************************************************************/
typedef struct
{
	INT8U  year;
	INT8U  month;
	INT8U  day;
	INT8U  hour;
	INT8U  minute;
	INT8U  second;
	INT8U  week;
    INT8U  flag;   // ������־λ
    INT16U ss;     // ��������ֵ, Modify 2019.11.30
}RTC_TIME;

/************************************************************************************/
// STM32F4_M4 ��������
/************************************************************************************/
#if (MODULE_CLASS == STM32F407XX)
#define RTC_IT_ALRA       0x0001  // RTC����A�ж�(ʹ�ܱ�־)
#define RTC_IT_ALRB       0x0002  // RTC����B�ж�(ʹ�ܱ�־)
#define RTC_IT_WKUPIT     0x0004  // RTC�����ж�(ʹ�ܱ�־)
#define RTC_IT_TSF        0x0008  // RTCʱ����ж�(ʹ�ܱ�־)
#define RTC_IT_TSFOVF     0x0010  // RTCʱ�������ж�(ʹ�ܱ�־)
#define RTC_IT_TAMP1      0x0020  // RTC���ּ��1�ж�(ʹ�ܱ�־)
#define RTC_IT_TAMP2      0x0040  // RTC���ּ��2�ж�(ʹ�ܱ�־)

// Flag��־λ����
#define RTC_OUT_BCD_FLAG        0x80000000     // RTC��д���������ں�ʱ�����ݸ�ʽ: BIT31=1,����BCD��ʽ���; BIT31=0,����BIN��ʽ���

// RTCʱ��Դѡ��, ����4��ֻ��ѡ��һ��
#define RTC_CLK_LSE_FLAG        0x40000000     // RTCʱ��ѡ��LSE��־, �ⲿ������32768HZ��Դ����
#define RTC_CLK_LSI_FLAG        0x20000000     // RTCʱ��ѡ��LSI��־
#define RTC_CLK_HSEDIV_FLAG     0x10000000     // RTCʱ��ѡ��HSE��Ƶ��־
#define RTC_CLK_LSEBYP_FLAG     0x08000000     // RTCʱ��ѡ��LSE��Դʱ�ӱ�־,���1MHZ, �ڲ�������·LSE����

#define RTC_CR_COE_EN           0x00800000     // ʹ��У׼���(ʹ��512Hz��1Hzʱ�������RTC_AF1)                     
#define RTC_CR_OSEL_A           0x00200000     // ���ʹ��ѡ������A                     
#define RTC_CR_OSEL_B           0x00400000     // ���ʹ��ѡ������B                    
#define RTC_CR_OSEL_WUT         0x00600000     // ���ʹ��ѡ�񣺻������                     
#define RTC_CR_POL_L            0x00100000     // �������: bit20=1,�͵�ƽ; bit20=0, �ߵ�ƽ                           
#define RTC_CR_COSEL_1HZ        0x00080000     // У׼���ѡ��: bit19=1, 1HZ���; bit19=0, 512HZ���; 
#define RTC_CR_TSIE_EN          0x00008000     // ʹ��ʱ����ж�                    
#define RTC_CR_WUTIE_EN         0x00004000     // ʹ�ܻ��Ѷ�ʱ���ж�                     
#define RTC_CR_ALRBIE_EN        0x00002000     // ʹ������B�ж�                    
#define RTC_CR_ALRAIE_EN        0x00001000     // ʹ������A�ж�                  
#define RTC_CR_TSE_EN           0x00000800     // ʹ��ʱ���                        
#define RTC_CR_WUTE_EN          0x00000400     // ʹ�ܻ��Ѷ�ʱ��                      
#define RTC_CR_ALRBE_EN         0x00000200     // ʹ������B                   
#define RTC_CR_ALRAE_EN         0x00000100     // ʹ������A                     
#define RTC_CR_DCE_EN           0x00000080     // ʹ������У׼
#define RTC_CR_BYPSHAD_EN       0x00000020     // ��·Ӱ�ӼĴ���
#define RTC_CR_REFCKON_EN       0x00000010     // ʹ�ܲο�ʱ�Ӽ���          
#define RTC_CR_TSEDGE           0x00000008     // ʱ����¼���Ч����: bit3=1, �½�����; bit3=0, ��������;                         
                  
typedef struct
{
	INT32U Flag;              // ������־
    INT32U LSEVal;            // �����ⲿʱ��Ƶ��   
	//INT8U  WUCKSel;           // ����ʱ��ѡ��: 0, ѡ��RTC/16ʱ��; 1, ѡ��RTC/8ʱ��; 2, ѡ��RTC/4ʱ��; 3, ѡ��RTC/2ʱ��; 4, ѡ��1HZ; 6, ѡ��1HZ, WUT����ֵ����2��16�η�; 
}RTC_PARA;

// RTC_TIME���ݽṹ��, ����Flag��־��������: 
#define RTC_DATA_BCD_FLAG       0x01  // bit0=1, BCD�����ݸ�ʽ; bit0=0, BIN�����ݸ�ʽ;

// ��������(CMD_RTC_SET_ALRMA_RTC/CMD_RTC_SET_ALRMB_RTC), ����Para����
#define RTC_ALARM_SS_FLAG       ((INT32U)0x0001)  // �����������α�־
#define RTC_ALARM_SECOND_FLAG   ((INT32U)0x0002)  // ���������α�־
#define RTC_ALARM_MINUTE_FLAG   ((INT32U)0x0004)  // ���ӷ������α�־
#define RTC_ALARM_HOUR_FLAG     ((INT32U)0x0008)  // ����Сʱ���α�־
#define RTC_ALARM_DAY_FLAG      ((INT32U)0x0010)  // ���������α�־
#define RTC_ALARM_WDSEL_FLAG    ((INT32U)0x0020)  // ��������ѡ���־
#define RTC_ALARM_IT_FLAG       ((INT32U)0x0040)  // ʹ�������жϱ�־
#define RTC_ALARM_OSEL_A_FLAG   ((INT32U)0x0080)  // ѡ������A���
#define RTC_ALARM_OSEL_B_FLAG   ((INT32U)0x0100)  // ѡ������B���
#define RTC_ALARM_OPOL_FLAG     ((INT32U)0x0200)  // �����������ѡ��: Para&(~RTC_ALARM_OPOL_FLAG), �߶�ƽ; Para|RTC_ALARM_OPOL_FLAG, �͵�ƽ; 
#define RTC_ALARM_OTYPE_FLAG    ((INT32U)0x0400)  // �����������ѡ��: Para&(~RTC_ALARM_OTYPE_FLAG), ��©���; Para|RTC_ALARM_OTYPE_FLAG, �������; 
#define RTC_ALARM_MASKSS_FLAG   ((INT32U)0xF000)  // ������������λ; 


// RTC_Ctrl() Cmd����
#define CMD_RTC_CTRL            0    // ����RTC���Ʋ�������, Para���������
#define CMD_RTC_GET_TSDTR       1    // ��ȡʱ���ʱ�������, ����ֵ��*rtc��
#define CMD_RTC_SET_ALRMA_RTC   2    // ��������A, ���ò�����Para��, ʱ�������*rtc�� 
#define CMD_RTC_SET_ALRMB_RTC   3    // ��������B, ���ò�����Para��, ʱ�������*rtc�� 
#define CMD_RTC_CLR_ALRMA_RTC   4    // �������A  
#define CMD_RTC_CLR_ALRMB_RTC   5    // �������B  

#define CMD_RTC_SET_WUTR        6    // ���û��ѼĴ���, Para������Χ: 1~65535
//#define CMD_RTC_SET_IT          7    // ����RTC�ж�  
//#define CMD_RTC_CLR_IT          8    // ���RTC�ж�  


#define CMD_RTC_SET_ALRMAR      17    // ��������A�Ĵ���, ������Para�� 
#define CMD_RTC_SET_ALRMBR      18    // ��������B�Ĵ���, ������Para��
#define CMD_RTC_GET_ALRMAR      19    // ��ȡ����A�Ĵ���, ������Para�� 
#define CMD_RTC_GET_ALRMBR      20    // ��ȡ����B�Ĵ���, ������Para��
#define CMD_RTC_GET_SSR         21    // ��ȡ����Ĵ���   
#define CMD_RTC_GET_TSSSR       22   // ������ʱ����¼�, ��ȡʱ�������Ĵ���  
#define CMD_RTC_SET_CALIBR      23    // ����У׼�Ĵ���
#define CMD_RTC_SET_CALR        24    // ����У׼�Ĵ���
#define CMD_RTC_GET_CALIBR      25    // ��ȡУ׼�Ĵ���
#define CMD_RTC_GET_CALR        26    // ��ȡУ׼�Ĵ���
#define CMD_RTC_SET_TAFCR       27    // ����RTC���ֺ͸��ù������üĴ���
#define CMD_RTC_GET_TAFCR       28    // ��ȡRTC���ֺ͸��ù������üĴ���
#define CMD_RTC_SET_SHIFTR      29    // ����ƽ�ƼĴ���  


#define CMD_RTC_SET_BKP0R    30
#define CMD_RTC_SET_BKP1R    (CMD_RTC_SET_BKP0R+1)
#define CMD_RTC_SET_BKP2R    (CMD_RTC_SET_BKP0R+2)
#define CMD_RTC_SET_BKP3R    (CMD_RTC_SET_BKP0R+3)
#define CMD_RTC_SET_BKP4R    (CMD_RTC_SET_BKP0R+4)
#define CMD_RTC_SET_BKP5R    (CMD_RTC_SET_BKP0R+5)
#define CMD_RTC_SET_BKP6R    (CMD_RTC_SET_BKP0R+6)
#define CMD_RTC_SET_BKP7R    (CMD_RTC_SET_BKP0R+7)
#define CMD_RTC_SET_BKP8R    (CMD_RTC_SET_BKP0R+8)
#define CMD_RTC_SET_BKP9R    (CMD_RTC_SET_BKP0R+9)
#define CMD_RTC_SET_BKP10R    (CMD_RTC_SET_BKP0R+10)
#define CMD_RTC_SET_BKP11R    (CMD_RTC_SET_BKP0R+11)
#define CMD_RTC_SET_BKP12R    (CMD_RTC_SET_BKP0R+12)
#define CMD_RTC_SET_BKP13R    (CMD_RTC_SET_BKP0R+13)
#define CMD_RTC_SET_BKP14R    (CMD_RTC_SET_BKP0R+14)
#define CMD_RTC_SET_BKP15R    (CMD_RTC_SET_BKP0R+15)
#define CMD_RTC_SET_BKP16R    (CMD_RTC_SET_BKP0R+16)
#define CMD_RTC_SET_BKP17R    (CMD_RTC_SET_BKP0R+17)
#define CMD_RTC_SET_BKP18R    (CMD_RTC_SET_BKP0R+18)
#define CMD_RTC_SET_BKP19R    (CMD_RTC_SET_BKP0R+19)

#define CMD_RTC_GET_BKP0R    50
#define CMD_RTC_GET_BKP1R    (CMD_RTC_GET_BKP0R+1)
#define CMD_RTC_GET_BKP2R    (CMD_RTC_GET_BKP0R+2)
#define CMD_RTC_GET_BKP3R    (CMD_RTC_GET_BKP0R+3)
#define CMD_RTC_GET_BKP4R    (CMD_RTC_GET_BKP0R+4)
#define CMD_RTC_GET_BKP5R    (CMD_RTC_GET_BKP0R+5)
#define CMD_RTC_GET_BKP6R    (CMD_RTC_GET_BKP0R+6)
#define CMD_RTC_GET_BKP7R    (CMD_RTC_GET_BKP0R+7)
#define CMD_RTC_GET_BKP8R    (CMD_RTC_GET_BKP0R+8)
#define CMD_RTC_GET_BKP9R    (CMD_RTC_GET_BKP0R+9)
#define CMD_RTC_GET_BKP10R    (CMD_RTC_GET_BKP0R+10)
#define CMD_RTC_GET_BKP11R    (CMD_RTC_GET_BKP0R+11)
#define CMD_RTC_GET_BKP12R    (CMD_RTC_GET_BKP0R+12)
#define CMD_RTC_GET_BKP13R    (CMD_RTC_GET_BKP0R+13)
#define CMD_RTC_GET_BKP14R    (CMD_RTC_GET_BKP0R+14)
#define CMD_RTC_GET_BKP15R    (CMD_RTC_GET_BKP0R+15)
#define CMD_RTC_GET_BKP16R    (CMD_RTC_GET_BKP0R+16)
#define CMD_RTC_GET_BKP17R    (CMD_RTC_GET_BKP0R+17)
#define CMD_RTC_GET_BKP18R    (CMD_RTC_GET_BKP0R+18)
#define CMD_RTC_GET_BKP19R    (CMD_RTC_GET_BKP0R+19)

#define CMD_RTC_BKPR_SIZE     20

#endif

/************************************************************************************/
// STM32F1_M3 ��������
/************************************************************************************/
#if ((MODULE_CLASS == STM32F107XX)||(MODULE_CLASS == STM32F103XX))
/************************************************************************************
// ������ȫ�ֱ�������
*************************************************************************************/
// RTCʱ��Դѡ��, ����3��ֻ��ѡ��һ��
#define RTC_CLK_LSE_FLAG        0x40000000     // RTCʱ��ѡ��LSE��־
#define RTC_CLK_LSI_FLAG        0x20000000     // RTCʱ��ѡ��LSI��־
#define RTC_CLK_HSEDIV_FLAG     0x10000000     // RTCʱ��ѡ��HSE��Ƶ��־
#define RTC_CLK_LSEBYP_FLAG     0x08000000     // RTCʱ��ѡ��LSE��Դʱ�ӱ�־,���1MHZ, �ڲ�������·LSE����

#define RTC_IT_SEC     0x0001  // ���жϱ�־
#define RTC_IT_ALARM   0x0002  // �����жϱ�־
#define RTC_IT_OW      0x0004  // ����������ж�

// RTC_Ctrl RTC���ƺ�������
#define CMD_RTC_GET_COUNTER  0    // ��ȡRTC������ֵ����
#define CMD_RTC_SET_COUNTER  1    // ����RTC������ֵ����
#define CMD_RTC_SET_ALMTIM   2    // ��������ʱ��, ����*rtcָ���������������ӵ�ʱ��
#define CMD_RTC_SET_ALMTIM_XS 3   // �����ڵ�ǰʱ���Ӻ�X���������, ���ñ���Para�����Ӻ��ʱ�䵥λ��
#define CMD_RTC_SET_ALMCOUNT 4    // �������Ӽ���ֵ, ���ñ���Para����������ӵļ���ֵ


#define CMD_RTC_SET_CAL      5    // ����У׼ֵ
#define CMD_RTC_SET_1SPLUS   6    // ����PC13(IO46)���������
#define CMD_RTC_SET_ALARM    7    // ����PC13(IO46)�����������
#define CMD_RTC_SET_COO      8    // ����PC13(IO46)���У׼ʱ������
#define CMD_RTC_STOP_PC13    9    // ֹͣPC13�������

#define CMD_RTC_SECOND_INT   10   // Para��ENABLE�������ж�, Para��DISABLE������ж�
#define CMD_RTC_ALARM_INT    11   // Para��ENABLE���ñ����ж�, Para��DISABLE��������ж�

typedef struct
{
	INT32U Flag;            // ������־
    INT32U LSEVal;          // �����ⲿʱ��Ƶ��   
}RTC_PARA;



#endif
/************************************************************************************
//
//                 RTCӲ����������
//
/*************************************************************************************

/*************************************************************************************
* Function: RTC_Init;
*
* Description: RTC��ʼ������;
*              
* Input:  pPara, ����ָ��;
*                 
* Output: none;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   none;
************************************************************************************/
INT32S RTC_Init(RTC_PARA *pPara);

/***********************************************************************************
* Function: RTC_Read;
*
* Description: ��ʱ��;
*              
* Input:   none;
*
* Output:  *rtc, RTCʱ������ָ��;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   �����ʱ��������ʮ��������������BCD��;
*         ���ڼĴ��������ַ�Χ��0��6��0��ʾ�����գ�1��ʾ����һ��... 6��ʾ��������7�޶���
************************************************************************************/
INT32S RTC_Read(RTC_TIME *rtc);

/***********************************************************************************
* Function: RTC_Write;
*
* Description: дʱ��;
*              
* Input:  *rtc, RTCʱ������ָ��;
*
* Output: none;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   �����ʱ��������ʮ��������������BCD��;
*         ���ڼĴ��������ַ�Χ��0��6��0��ʾ�����գ�1��ʾ����һ��... 6��ʾ��������7�޶���
************************************************************************************/
INT32S RTC_Write(RTC_TIME *rtc);

/***********************************************************************************
* Function: RTC_Ctrl;
*
* Description: RTC���ƺ���;
*              
* Input:  Cmd,  ��������: 
*         CMD_RTC_GET_COUNTER, ��ȡRTC������ֵ����
*         CMD_RTC_SET_COUNTER, ����RTC������ֵ����
*         CMD_RTC_SET_ALMTIM,  ��������ʱ��
*         CMD_RTC_GET_ALMCOUNT ��ȡ���Ӽ�����ֵ����
*         CMD_RTC_SET_ALMCOUNT �������Ӽ���ֵ
*         CMD_RTC_SET_CAL,     ����У׼ֵ
*         CMD_RTC_SET_1SPLUS,  ����PC13(IO46)���������
*         CMD_RTC_SET_ALARM,   ����PC13(IO46)�����������
*         CMD_RTC_SET_COO,     ����PC13(IO46)���У׼ʱ������
*         CMD_RTC_STOP_PC13,   ֹͣPC13�������;
*         CMD_RTC_SECOND_INT,  Para��ENABLE�������ж�, Para��DISABLE������ж�
*         CMD_RTC_ALARM_INT,   Para��ENABLE���ñ����ж�, Para��DISABLE��������ж�
*         Para, �������;
*
* Output: none;
*
* Return: ����������ָ����, ���أ�ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   none;
************************************************************************************/
INT32S RTC_Ctrl(INT8U Cmd, INT32U Para, RTC_TIME *rtc);

#endif
/***********************************************************************************/
// �ļ�����
/***********************************************************************************/
