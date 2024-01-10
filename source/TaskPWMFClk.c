/************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: TastPWMCLK.c
* Project  : STM32F1XX/4XXϵ��ģ�����
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.00
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: ���ļ�����TIM��ʱ��, PWM�ź������FCLK��������������;
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
1. PWM����: 
   (1). IO����˵��: ��IO�����ļ�������PWM_CH1~CH4�ܽ�, ��PWM1Ϊ�� IO����: 
        // PWM1(TIM3) �ܽŹ���ӳ������: 
        #define PWM1_REMAP      TIM_REMAP_3 // PWM1(TIM3)�ܽ���ӳ��(ֻ֧��STM32F107VC/103VE/103ZE����ģ��)
        #define PWM1_CH1        PC6         // PWM1(TIM3) CH1�ܽŶ���,��ѡ���¶˿�: PA6, PB4, PC6
        #define PWM1_CH2        PC7         // PWM1(TIM3) CH2�ܽŶ���,��ѡ���¶˿�: PA7, PB5, PC7
        #define PWM1_CH3        PC8         // PWM1(TIM3) CH3�ܽŶ���,��ѡ���¶˿�: PB0, PC8
        #define PWM1_CH4        PC9         // PWM1(TIM3) CH4�ܽŶ���,��ѡ���¶˿�: PB1, PC9
        #define PWM1_ETR        IO_NONE     // PWM1(TIM3) ETR�ܽŶ���,��ѡ���¶˿�: PD2
 
        ��ЩIO����ֻ�谴����ģ�����Ĭ�����ü���, ����Ҫ����;
   
   (2). ���ܲ�������˵��: �������ļ�������������, ��PWM1Ϊ��:       
        #define PWM1_EN             1		   // PWM1ʹ��, 1����ʹ�ܣ� 0���ر�
        // ����PWM���ģʽ����
        #define PWM1_MODE           PWM_FREQ   // ����ѡ��: 0(PWM_FREQ):   ��������Ƶ�����, �������
                                               //           1(PWM_FREQ_N): �������Ƶ�����, ������趨����������ֹͣ
                                               //           2(PWM_RATE):   �̶�Ƶ��ռ�ձȿɵ������������: ���PWM, Ƶ�ʹ̶�,ռ�ձ�0%-100%�ɵ�, �������
                                               //           3(PWM_DMA):    ��������ģʽ, ����PWM_Write()����ʵ��DMA�������ģʽ, ������Ʒ�ʽ�ɺ��������� 
        
        #define PWM1_FREQ		    1000  	   // ��ʼƵ��
        #define PWM1_TIM            TIM3_ID    // ѡ��ʱ��, ������ò��ɸ���
        // ͨ��ʹ��
        #define PWM1CH1_EN		    1		   // PWM1CH1��1, ʹ��; 0, �ر�
        #define PWM1CH2_EN		    1		   // PWM1CH2��1, ʹ��; 0, �ر�
        #define PWM1CH3_EN		    1		   // PWM1CH3��1, ʹ��; 0, �ر�
        #define PWM1CH4_EN		    1		   // PWM1CH4��1, ʹ��; 0, �ر�   
   
        ����Щ������һ��ֻ�����PWM1_MODEģʽ��ͨ��ʹ�ܼȿɣ�������Ĭ������;
        
   (3). ������ʵ�����¹���(��PWM1Ϊ��):   
        ������������Ƶ�����ģʽ(PWM1_MODE����0):
        ��ʾ��������PWM����˿�: �������, ����ÿ��3������1KHZ, Ƶ�ʱ仯��Χ��1KHZ~10KHZ;
         
        ���Զ������Ƶ�����ģʽ(PWM1_MODE����1):
        ��ʾ����PWM����˿�: �������, Ƶ��1KHZ, ÿ��3�뷢��FREQ_N(8)������;      
   
        ���Թ̶�Ƶ��ռ�ձȿɵ������������ģʽ(PWM1_MODE����2): 
        ��ʾ������PWM����˿ڲ����ź�: ���PWM, Ƶ��1KHZ,ռ�ձ�0%-100%�ɵ�, ÿ��3��ռ�ձ�����10%;         
   
        �������ú���PWM_Write()ʵ��DMA��ʽ����������Ƶ��ģʽ(PWM1_MODE����3):
        ��ʾ����PWM����˿�: ���3S,�������18������;      
   
   (4). ��������(1)(2)����, ��APP_Init.c�е���PWM_APPInit()������ʼ��; 
   
   (5). �ڱ��ļ��е���PWM_Start(PWM1_ID, PWM1_MODE, (PWM_CTRL *)&UserVars.PWMPara[PWM1_ID].Mode), ����PWM1���;
        ���3�����PWM_Test(PWM1_ID, PWM1_MODE, (PWM_CTRL *)&UserVars.PWMPara[PWM1_ID].Mode), ����PWM1����ź�;
        
                     
2. FCLK����: 
   (1). IO����˵��: ��IO�����ļ�������FCLK1_CH1~CH4�ܽ�, ��FCLK1Ϊ�� IO����: 
        // FCLK1(TIM4)�ܽŹ���ӳ������: 
        #define FCLK1_REMAP    TIM_REMAP_1  // FCLK1(TIM4)�ܽ���ӳ��(ֻ֧��STM32F107VC/103VE/103ZE����ģ��)
        #define FCLK1_CH1      PD12         // FCLK1(TIM4) CH1�ܽŶ���,��ѡ���¶˿�: PB6,  PD12
        #define FCLK1_CH2      PD13         // FCLK1(TIM4) CH2�ܽŶ���,��ѡ���¶˿�: PB7,  PD13
        #define FCLK1_CH3      PD14         // FCLK1(TIM4) CH3�ܽŶ���,��ѡ���¶˿�: PB8,  PD14
        #define FCLK1_CH4      PD15         // FCLK1(TIM4) CH4�ܽŶ���,��ѡ���¶˿�: PB9,  PD15
        #define FCLK1_ETR      IO_NONE      // FCLK1(TIM4) ETR�ܽŶ���,��ѡ���¶˿�: PE0      
         
        ��ЩIO����ֻ�谴����ģ�����Ĭ�����ü���, ����Ҫ����;
   
   (2). ���ܲ�������˵��: �������ļ�������������, ��FCLK1Ϊ��:       
        #define FCLK1_EN           1	       // FCLK1ʹ��, 1����ʹ�ܣ� 0���ر�
        #define FCLK1_MODE	       2		   // ģʽѡ��: 0(FCLK_MODE_COUNT), ����ģʽ(1·, CH1������Ч); 
                                               //           1(FCLK_MODE_DECODE), ��������������(CH1��A��CH2��B);
                                               //           2(FCLK_MODE_FREQ), ��Ƶģʽ(4·, CH1, CH2, CH3, CH4���붼��Ч); 
                                               //           3(FCLK_MODE_PWMRATE), ��PWMռ�ձ�ģʽ(1·, CH1������Ч); 
        #define FCLK1_TIM          TIM4_ID     // ѡ��ʱ��, ������ò��ɸ���

        #define FCLK1CH1_EN		   1	       // FCLK1��1, ʹ��; 0, �ر�
        #define FCLK1CH2_EN		   1		   // FCLK2��1, ʹ��; 0, �ر�
        #define FCLK1CH3_EN		   1	       // FCLK3��1, ʹ��; 0, �ر�
        #define FCLK1CH4_EN		   1		   // FCLK4��1, ʹ��; 0, �ر�
   
        ����Щ������һ��ֻ�����FCLK1_MODEģʽ��FCLK1CH1_EN~FCLK1CH4_EN�ȿɣ�������Ĭ������;
        
   (3). ������ʵ�����¹���(��FCLK1Ϊ��):   
        ���Լ���ģʽ(FCLK1_MODE����0): 
        ��FCLK1CH1�˿ڼ�1KHZ(������Ƶ��)��������ź�: ÿ��3���������������;
   
        ������������������ģʽ(FCLK1_MODE����1): 
        ��FCLK1CH1,FCLK1CH2�˿ڼ�������������(A��B)�����ź�: ʵʱ���������������������;     

        ���Բ�Ƶģʽ(FCLK1_MODE����2): 
        ��FCLK1CH1~CH4�˿ڼ�1KHZ(������Ƶ��)��������ź�: ÿ��3���������������Ƶ��;
        
        ����PWMռ�ձ�ģʽ(FCLK1_MODE����3): 
        ��FCLK1CH1�˿ڼ�1KHZ(������Ƶ��)��������ź�, ��������ɵ�: ÿ��3������������źŵ�ռ�ձ�;     
   
   (4). ��������(1)(2)����, ��APP_Init.c�е���FCLK_APPInit()������ʼ��; 
   
   (5). �ڱ��ļ��е���FCLK_Ctrl(FCLK1_ID, CMD_FCLK_ENA, FCLK1CH_EN), ʹ��FCLK1����;
        ���3�����FCLK_Test(FCLK1_ID, FCLK1_MODE), ʵ��FCLK1ģʽ0,2,3����;
        ���20�������FCLK_Read(id, CMD_FCLK_DECODE, 0, (INT32U *)&cnt1, 1, 0), ʵ��FCLK1ģʽ1����;
   
   (6). ͨ�����ڵ�������۲�������; 
 
3. TIMER��ʱ������: 
   (1). ���ܲ�������˵��: �������ļ�������������, ��TIM1Ϊ��:       
        #define TIM1_EN       1		  // TIM1ʹ��, 1����ʹ�ܣ� 0���ر�
        #define TIM1_MODE     1		  // TIM1����ģʽ: 0, TIM_WKMODE_INT, ��ʱ�������ڶ�ʱ�ж�ģʽ, ��ʱʱ���ɲ���TIM1_T,TIM1_T1-TIM1_T4����; 
                                      //               1, TIM_WKMODE_COUNT, ��ʱ�������ڶ�ʱ����ģʽ, �ⲿͨ������Timer_Ctrl��������CMD_TIM_ENA/CMD_TIM_DIS����/ֹͣ��ʱ��,
                                      // ��ͨ������CMD_TIM_READ��ȡ����ֵ
        #define TIM1CH1_EN    1		  // TIM1�Ӷ�ʱ��1ʹ��, 1����ʹ�ܣ� 0���ر�
        #define TIM1CH2_EN    0		  // TIM1�Ӷ�ʱ��2ʹ��, 1����ʹ�ܣ� 0���ر�
        #define TIM1CH3_EN    0		  // TIM1�Ӷ�ʱ��3ʹ��, 1����ʹ�ܣ� 0���ر�
        #define TIM1CH4_EN    0		  // TIM1�Ӷ�ʱ��4ʹ��, 1����ʹ�ܣ� 0���ر�

        // TIM1���ж�ʱ��(�����Ӷ�ʱ��)ʹ�� 
        #define TIM1CH_EN	   (TIM1_EN|(TIM1CH1_EN<<1)|(TIM1CH2_EN<<2)|(TIM1CH3_EN<<3)|(TIM1CH4_EN<<4))  // TIM1���ж�ʱ��(�����Ӷ�ʱ��)��BIT0:TIM1(����ʱ��);BIT1:CH1;BIT2:CH2;BIT3:CH3;BIT4:CH4;

        // ��ʼ��ʱʱ���趨 (ע��: �Ӷ�ʱ��1��2��3��4��ʱʱ�����С������ʱ����ʱʱ��)
        #define TIM1_T        1000000	  // TIM1����ʱ����ʱʱ��, ��λus
                              
        #define TIM1_T1       1000000     // TIM1�Ӷ�ʱ��1��ʱʱ��, ��λus
        #define TIM1_T2       1000000	  // TIM1�Ӷ�ʱ��2��ʱʱ��, ��λus
        #define TIM1_T3       1000000	  // TIM1�Ӷ�ʱ��3��ʱʱ��, ��λus
        #define TIM1_T4       500000	  // TIM1�Ӷ�ʱ��4��ʱʱ��, ��λus

        #define TIM1_PSC      (SYSCLK/1000000)  // ��Ƶϵ��, ������ģʽ����ΪTIM_WKMODE_COUNT, ���������;
                                                // Ĭ�ϼ�����λ��1us
   
        ����Щ������һ��ֻ�����TIM1_MODEģʽ, TIM1CH1_EN~TIM1CH4_EN, TIM1_T, TIM1_T1~T4�ȿɣ�������Ĭ������;
        
   (3). ������ʵ�����¹���(��TIM1Ϊ��):  
        ���Զ�ʱ�ж�ģʽ(TIM1_MODE����0):
        ʵ�ֹ���: ���1��, ��ISRHook.c�� TIM1_UP_ISRHook, TIM1_CC_ISRHook������Ӧ�ж�, ��ͨ�����Դ��ڴ�ӡ�жϽ��;
   
        ���Զ�ʱ����ģʽ(TIM1_MODE����1): 
        ʵ�ֹ���: ���3��, ������ʱ����Delay_ms(20)�ļ���ֵ, ��ʱ��Ĭ������1us����ֵ, һ��20ms����ֵ����20000����;

   (4). ��������(1)(2)����, ��APP_Init.c�е���TIM_APPInit()������ʼ��; 

   (5). �ڶ�ʱ�ж�ģʽ��, ����TIM_Start()�������ж�ʱ������;
        
        �ڶ�ʱ����ģʽ, ���3�����TIM_ReadCount(), Ӧ���������ʵ�ֲ���20ms�������ֵ
        Timer_Ctrl(TIM2_ID, CMD_TIM_ENA, 0);   // ʹ�ܶ�ʱ��
        Delay_ms(20);                          // ��ʱ20ms
        Timer_Ctrl(TIM2_ID, CMD_TIM_DIS, 0);   // �رն�ʱ�� 
        cnt = Timer_Ctrl(TIM2_ID, CMD_TIM_READ, 0); // ��ȡ20ms����ֵ
   
   (6). ͨ�����ڵ�������۲���;         
*/
/************************************************************************************/
// �����ⲿͷ�ļ�
#include "config.h"
#if (TASK_PWMFCLK_EN == 1)
#include "UserVars.h"
#include "STM32Fxxx.h"
#include "motor.h"

/************************************************************************************/
// ������ȫ�ֱ�������
/************************************************************************************/


/************************************************************************************/
// PWM�����������
/************************************************************************************/
#define  FREQ_N         8  // �������岨�θ���

/************************************************************************************/
// FCLK����
/************************************************************************************/
/***********************************************************************************
* Function: FCLK_Test;
*
* Description: FCLK��������
* 
* Input:  id, FCLK����(FCLK1_ID, FCLK2_ID, FCLK3_ID, FCLK4_ID, FCLK5_ID, FCLK6_ID, FCLK7_ID, FCLK8_ID);
*         Mode, PWM���ģʽ(FCLK_MODE_COUNT, FCLK_MODE_FREQ, FCLK_MODE_PWMRATE);
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
#if ((FCLK1_EN > 0)||(FCLK2_EN > 0)||(FCLK3_EN > 0)||(FCLK4_EN > 0)||(FCLK5_EN > 0)||(FCLK6_EN > 0)||(FCLK7_EN > 0)||(FCLK8_EN > 0)) 
void FCLK_Test(INT8U id, INT8U Mode)
{
#define MAX_DATA_NUM	4   // ����ȡ��������
    INT32U buf[MAX_DATA_NUM], i, cnt;
	INT32S flag;
    INT8U FClkEn;
	
	if (Mode == FCLK_MODE_PWMRATE)  // ����ռ�ձ�ģʽ
	{   
        UserVars.FCLK[id].Mode = FCLK_MODE_PWMRATE;
        flag = FCLK_Read(id, CMD_FCLK_PWMRATE, FCLK_CH1, buf, MAX_DATA_NUM, 0); // ������ȡMAX_DATA_NUM��ռ�ձ�ֵ����buf
        if (flag == ERR_TRUE)
        {
             UserVars.FCLK[id].Rate = buf[0];
             #if (DEBUG_APP_EN == 1)
             if (UserVars.Para.ATFlag&AT_FCLK_FLAG)
             {                 
                 printf("AT+FCLK%d=D", id+1);            // ��ӡ���ռ�ձ�ֵ
                 for (i=0; i<MAX_DATA_NUM; i++)
                 {
                     printf(",%d.%d", buf[i]/100,(buf[i]%100)/10);
                 }
                 printf("\r\n");
             }
             #endif
        }
        else
        {
             UserVars.FCLK[id].Rate = 0;
             #if (DEBUG_APP_EN == 1) 
             if (UserVars.Para.ATFlag&AT_FCLK_FLAG)
             {
                 printf("AT+ERROR=FCLK%d����PWMռ�ձ�ʧ��\r\n",id+1);
             }
             #endif
        }
    }
	else if (Mode == FCLK_MODE_FREQ)  // ����Ƶ��ģʽ
	{
        UserVars.FCLK[id].Mode = FCLK_MODE_FREQ;        
        if (id == FCLK1_ID)
        {
            #if (FCLK1_EN > 0)
            FClkEn = FCLK1CH_EN;
            #endif
        }
        #if (FCLK2_EN > 0)
        else if (id == FCLK2_ID)
        {
           FClkEn = FCLK2CH_EN;
        }
        #endif
        #if (FCLK3_EN > 0)
        else if (id == FCLK3_ID)
        {
           FClkEn = FCLK3CH_EN;
        }
        #endif
        #if (FCLK4_EN > 0)
        else if (id == FCLK4_ID)
        {
           FClkEn = FCLK4CH_EN;
        }
        #endif
#if (MODULE_CLASS == STM32F407XX)       
        #if (FCLK5_EN > 0)
        else if (id == FCLK5_ID)
        {
           FClkEn = FCLK5CH_EN;
        }
        #endif
        #if (FCLK6_EN > 0)
        else if (id == FCLK6_ID)
        {
           FClkEn = FCLK6CH_EN;
        }
        #endif
        #if (FCLK7_EN > 0)
        else if (id == FCLK7_ID)
        {
           FClkEn = FCLK7CH_EN;
        }
        #endif
        #if (FCLK8_EN > 0)
        else if (id == FCLK8_ID)
        {
           FClkEn = FCLK8CH_EN;
        }
        #endif
#endif        
        if (FClkEn&FCLK_CH1FLAG)             // ͨ��CH1ʹ��
        {
            flag = FCLK_Read(id, CMD_FCLK_FREQ, FCLK_CH1, buf, MAX_DATA_NUM, 0); // ������ȡCH1ͨ��MAX_DATA_NUM��Ƶ��ֵ����buf
            if (flag == ERR_TRUE)
            {
                 UserVars.FCLK[id].Freq[FCLK_CH1] = buf[0];
                 
                 #if (DEBUG_APP_EN == 1)        // ��ӡ���Ƶ��ֵ
                 if (UserVars.Para.ATFlag&AT_FCLK_FLAG)
                 {
                     printf("AT+FCLK%d=F1", id+1); 
                     for (i=0; i<MAX_DATA_NUM; i++)
                     {
                         printf(",%d.%d", buf[i]/100, buf[i]%100/10);
                     }
                     printf("\r\n");
                 }
                 #endif
                 
            }
            else
            {                 
                 UserVars.FCLK[id].Freq[FCLK_CH1] = 0;
                 #if (DEBUG_APP_EN == 1)
                 if (UserVars.Para.ATFlag&AT_FCLK_FLAG)
                 {
                     printf("AT+ERROR=FCLK%dCH1����Ƶ��ʧ��\r\n", id+1);
                 }
                 #endif
            }
        }            
		if (FClkEn&FCLK_CH2FLAG)             // ͨ��CH2ʹ��, �źŴ�DI2����
        {
            flag = FCLK_Read(id, CMD_FCLK_FREQ, FCLK_CH2, buf, MAX_DATA_NUM, 0);    // ������ȡCH2ͨ��MAX_DATA_NUM��Ƶ��ֵ����buf
            if (flag == ERR_TRUE)
            {
                 UserVars.FCLK[id].Freq[FCLK_CH2] = buf[0];
                 
                 #if (DEBUG_APP_EN == 1)            // ��ӡ���Ƶ��ֵ
                 if (UserVars.Para.ATFlag&AT_FCLK_FLAG)
                 {
                     printf("AT+FCLK%d=F2", id+1); 
                     for (i=0; i<MAX_DATA_NUM; i++)
                     {
                         printf(",%d.%d", buf[i]/100, buf[i]%100/10);
                     }
                     printf("\r\n");
                 }
                 #endif
            }
            else
            {                 
                 UserVars.FCLK[id].Freq[FCLK_CH2] = 0;
                 #if (DEBUG_APP_EN == 1)
                 if (UserVars.Para.ATFlag&AT_FCLK_FLAG)
                 {
                     printf("AT+ERROR=FCLK%dCH2����Ƶ��ʧ��\r\n", id+1);
                 }
                 #endif
            }
		}
        
        if (FClkEn&FCLK_CH3FLAG)                // ͨ��CH3ʹ��, �źŴ�DI3����
        {
            flag = FCLK_Read(id, CMD_FCLK_FREQ, FCLK_CH3, buf, MAX_DATA_NUM, 0);    // ������ȡCH3ͨ��MAX_DATA_NUM��Ƶ��ֵ����buf
            if (flag == ERR_TRUE)
            {
                 UserVars.FCLK[id].Freq[FCLK_CH3] = buf[0];
                 
                 #if (DEBUG_APP_EN == 1)            // ��ӡ���Ƶ��ֵ
                 if (UserVars.Para.ATFlag&AT_FCLK_FLAG)
                 {
                     printf("AT+FCLK%d=F3", id+1);
                     for (i=0; i<MAX_DATA_NUM; i++)
                     {
                         printf(",%d.%d", buf[i]/100, buf[i]%100/10);
                     }
                     printf("\r\n");
                 }
                 #endif
                 
            }
            else
            {
                 UserVars.FCLK[id].Freq[FCLK_CH3] = 0;
                 #if (DEBUG_APP_EN == 1)
                 if (UserVars.Para.ATFlag&AT_FCLK_FLAG)
                 {
                     printf("AT+ERROR=FCLK%dCH3����Ƶ��ʧ��\r\n", id+1);
                 }
                 #endif
            }
        }
        
        if (FClkEn&FCLK_CH4FLAG)	                    // ͨ��CH4ʹ��, �źŴ�DI4����        
        {
            flag = FCLK_Read(id, CMD_FCLK_FREQ, FCLK_CH4, buf, MAX_DATA_NUM, 0);    // ������ȡCH4ͨ��MAX_DATA_NUM��Ƶ��ֵ����buf
            if (flag == ERR_TRUE)
            {
                 UserVars.FCLK[id].Freq[FCLK_CH4] = buf[0];
                 
                 #if (DEBUG_APP_EN == 1)            // ��ӡ���Ƶ��ֵ
                 if (UserVars.Para.ATFlag&AT_FCLK_FLAG)
                 {
                     printf("AT+FCLK%d=F4", id+1);
                     for (i=0; i<MAX_DATA_NUM; i++)
                     {
                         printf(",%d.%d", buf[i]/100, buf[i]%100/10);
                     }
                     printf("\r\n");
                 }
                 #endif
                
            }
            else
            {                 
                 UserVars.FCLK[id].Freq[FCLK_CH4] = 0;
                 #if (DEBUG_APP_EN == 1)
                 if (UserVars.Para.ATFlag&AT_FCLK_FLAG)
                 {
                     printf("AT+ERROR=FCLK%dCH4����Ƶ��ʧ��\r\n", id+1);
                 }
                 #endif
            }    
        }
        /*
         #if (DEBUG_APP_EN == 1)            // ��ӡ���Ƶ��ֵ
         if (UserVars.Para.ATFlag&AT_FCLK_FLAG)
         {
             printf("AT+FCLK%d=F", id+1);
             for (i=0; i<4; i++)
             {
                 printf(",%d", UserVars.FCLK[id].Freq[i]/100);
             }
             printf("\r\n");
         }
         #endif
        */
    }
    else if (Mode == FCLK_MODE_COUNT) // ��ȡ����ֵģʽ
	{
        UserVars.FCLK[id].Mode = FCLK_MODE_COUNT;
        flag = FCLK_Read(id, CMD_FCLK_COUNT, FCLK_CH1, &cnt, 0, 0);   // ��ȡ������ֵ
        FCLK_Ctrl(id, CMD_FCLK_CLEAR, 0);   // ��0����ֵ
        if (flag == ERR_TRUE)
        {             
             UserVars.FCLK[id].cnt = cnt;
             #if (DEBUG_APP_EN == 1)
             if (UserVars.Para.ATFlag&AT_FCLK_FLAG)
             {
                 printf("AT+FCLK%d=N,%d\r\n", id+1,cnt);
             }
             #endif
        }
        else
        {
             UserVars.FCLK[id].cnt = 0;
             #if (DEBUG_APP_EN == 1)
             if (UserVars.Para.ATFlag&AT_FCLK_FLAG)
             {
                 printf("AT+ERROR=FCLK%d��������ֵʧ��\r\n", id+1);
             }
             #endif
        }
	}
}
#endif


/***********************************************************************************
* Function: PWM_Start;
*
* Description: PWM��������;
* 
* Input:  id, PWM����(PWM1_ID, PWM2_ID, PWM3_ID, PWM4_ID);
*         Mode, PWM���ģʽ(PWM_FREQ, PWM_FREQ_N, PWM_RATE);
*         pPara, PWM����ָ��;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
#if ((PWM1_EN > 0)||(PWM2_EN > 0)||(PWM3_EN > 0)||(PWM4_EN > 0)||(PWM5_EN > 0)||(PWM6_EN > 0)||(PWM7_EN > 0)||(PWM8_EN > 0))
void PWM_Start(INT8U id, INT8U Mode, PWM_CTRL *pPara)
{    
    if (id == PWM1_ID)
    {
        #if (PWM1_EN > 0)
        pPara->Freq = PWM1_FREQ;       // ����Ĭ��Ƶ��
        pPara->Chx = PWM1CH_EN;        // ����ʹ��ͨ�� 

        pPara->Rate[0] = PWM1CH1_RATE;  // ����ÿ��ͨ�����PWMռ�ձ�
        pPara->Rate[1] = PWM1CH2_RATE;
        pPara->Rate[2] = PWM1CH3_RATE;
        pPara->Rate[3] = PWM1CH4_RATE;
        #endif
    } 
    #if (PWM2_EN > 0)    
    else if (id == PWM2_ID)
    {
        pPara->Freq = PWM2_FREQ;       // ����Ĭ��Ƶ��
        pPara->Chx = PWM2CH_EN;        // ����ʹ��ͨ�� 

        pPara->Rate[0] = PWM2CH1_RATE;  // ����ÿ��ͨ�����PWMռ�ձ�
        pPara->Rate[1] = PWM2CH2_RATE;
        pPara->Rate[2] = PWM2CH3_RATE;
        pPara->Rate[3] = PWM2CH4_RATE;
    }   
    #endif    
    #if (PWM3_EN > 0)
    else if (id == PWM3_ID)
    {
        pPara->Freq = PWM3_FREQ;       // ����Ĭ��Ƶ��
        pPara->Chx = PWM3CH_EN;        // ����ʹ��ͨ�� 

        pPara->Rate[0] = PWM3CH1_RATE;  // ����ÿ��ͨ�����PWMռ�ձ�
        pPara->Rate[1] = PWM3CH2_RATE;
        pPara->Rate[2] = PWM3CH3_RATE;
        pPara->Rate[3] = PWM3CH4_RATE;
    }        
    #endif
    #if (PWM4_EN > 0)
    else if (id == PWM4_ID)
    {
        pPara->Freq = PWM4_FREQ;       // ����Ĭ��Ƶ��
        pPara->Chx = PWM4CH_EN;        // ����ʹ��ͨ�� 

        pPara->Rate[0] = PWM4CH1_RATE;  // ����ÿ��ͨ�����PWMռ�ձ�
        pPara->Rate[1] = PWM4CH2_RATE;
        pPara->Rate[2] = PWM4CH3_RATE;
        pPara->Rate[3] = PWM4CH4_RATE;
    }        
    #endif

#if (MODULE_CLASS == STM32F407XX)
    #if (PWM5_EN > 0)
    else if (id == PWM5_ID)
    {
        pPara->Freq = PWM5_FREQ;       // ����Ĭ��Ƶ��
        pPara->Chx = PWM5CH_EN;        // ����ʹ��ͨ�� 

        pPara->Rate[0] = PWM5CH1_RATE;  // ����ÿ��ͨ�����PWMռ�ձ�
        pPara->Rate[1] = PWM5CH2_RATE;
    }        
    #endif

    #if (PWM6_EN > 0)
    else if (id == PWM6_ID)
    {
        pPara->Freq = PWM6_FREQ;       // ����Ĭ��Ƶ��
        pPara->Chx = PWM6CH_EN;        // ����ʹ��ͨ�� 

        pPara->Rate[0] = PWM6CH1_RATE;  // ����ÿ��ͨ�����PWMռ�ձ�
        pPara->Rate[1] = PWM6CH2_RATE;
    }        
    #endif
    
    #if (PWM7_EN > 0)
    else if (id == PWM7_ID)
    {
        pPara->Freq = PWM7_FREQ;       // ����Ĭ��Ƶ��
        pPara->Chx = PWM7CH_EN;        // ����ʹ��ͨ�� 

        pPara->Rate[0] = PWM7CH1_RATE;  // ����ÿ��ͨ�����PWMռ�ձ�
        //pPara->Rate[1] = PWM7CH2_RATE;
    }        
    #endif
#endif
    
    if (Mode == PWM_FREQ)    // ��������Ƶ�����ģʽ, �������
    {
        pPara->Mode = PWM_CTRL_FREQ;   // ���ÿ��Ƹ���PWMƵ�����, ����������� 
    }    
    else if (Mode == PWM_FREQ_N)  // �������Ƶ�����, ������趨����������ֹͣ
    {
        pPara->Mode = PWM_CTRL_FREQ_N; // ���Ƹ���PWMƵ�����, �������N�������ֹͣ
        pPara->Num[0] = FREQ_N;        // ����ÿ��ͨ������������
        pPara->Num[1] = FREQ_N;
        pPara->Num[2] = FREQ_N;
        pPara->Num[3] = FREQ_N;
    }    
    
    else if (Mode == PWM_RATE)     // �̶�Ƶ��ռ�ձȿɵ������������: ���PWM, Ƶ�ʹ̶�, ռ�ձ�0%-100%�ɵ�, �������
    {
        pPara->Mode = PWM_CTRL_RATE;    // ���Ƹ���PWMռ�ձ����
    }    
    PWM_Ctrl(id, CMD_PWM_ENA, pPara);  // ����������ʹ��PWM���      
}
#endif
/***********************************************************************************
* Function: PWM_Test;
*
* Description: PWM���Ժ���, �������ò�ͬ, ����ͬ����;
* 
* Input:  id, PWM����(PWM1_ID, PWM2_ID, PWM3_ID, PWM4_ID);
*         Mode, PWM���ģʽ(PWM_FREQ, PWM_FREQ_N, PWM_RATE);
*         pPara, PWM����ָ��;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/
#if ((PWM1_EN > 0)||(PWM2_EN > 0)||(PWM3_EN > 0)||(PWM4_EN > 0)||(PWM5_EN > 0)||(PWM6_EN > 0)||(PWM7_EN > 0)||(PWM8_EN > 0))
void PWM_Test(INT8U id, INT8U Mode, PWM_CTRL *pPara)
{    
    if (Mode == PWM_FREQ)  // ������������Ƶ�����, ÿ��3�����PWMƵ��
    {      
        pPara->Freq += 1000;         // ÿ������1KHZ
        if (pPara->Freq>10000)         // ����10KHZ
        {
            pPara->Freq = 1000;        // ��������1000HZ
        }	
        PWM_Ctrl(id, CMD_PWM_FREQ, pPara);  // �������޸�PWM���Ƶ��   
        #if (DEBUG_APP_EN == 1)
        if (UserVars.Para.ATFlag&AT_PWM_FLAG)
        {
            printf("AT+PWM%d=%d,500,0\r\n", id+1,pPara->Freq);
        }
        #endif
    }	
    else if (Mode == PWM_FREQ_N)  // ���Զ������Ƶ�����: �������, Ƶ��1KHZ, ÿ�η���8������;
    {
        pPara->Mode = PWM_CTRL_FREQ_N; // ���Ƹ���PWMƵ�����, �������N�������ֹͣ
        
        if (id == PWM1_ID)
        {        
            #if (PWM1_EN > 0)
            pPara->Freq = PWM1_FREQ;       // ����Ĭ��Ƶ��
            pPara->Chx = PWM1CH_EN;        // ����ʹ��ͨ�� 
            #endif
        }
        #if (PWM2_EN > 0)  
        else if (id == PWM2_ID)
        {
            pPara->Freq = PWM2_FREQ;       // ����Ĭ��Ƶ��
            pPara->Chx = PWM2CH_EN;        // ����ʹ��ͨ�� 
        }
        #endif
        #if (PWM3_EN > 0)  
        else if (id == PWM3_ID)
        {
            pPara->Freq = PWM3_FREQ;       // ����Ĭ��Ƶ��
            pPara->Chx = PWM3CH_EN;        // ����ʹ��ͨ�� 
        }
        #endif
        #if (PWM4_EN > 0)  
        else if (id == PWM4_ID)
        {
            pPara->Freq = PWM4_FREQ;       // ����Ĭ��Ƶ��
            pPara->Chx = PWM4CH_EN;        // ����ʹ��ͨ�� 
        }
        #endif
#if (MODULE_CLASS == STM32F407XX)
        #if (PWM5_EN > 0)  
        else if (id == PWM5_ID)
        {
            pPara->Freq = PWM5_FREQ;       // ����Ĭ��Ƶ��
            pPara->Chx = PWM5CH_EN;        // ����ʹ��ͨ�� 
        }
        #endif
        #if (PWM6_EN > 0)  
        else if (id == PWM6_ID)
        {
            pPara->Freq = PWM6_FREQ;       // ����Ĭ��Ƶ��
            pPara->Chx = PWM6CH_EN;        // ����ʹ��ͨ�� 
        }
        #endif
        #if (PWM7_EN > 0)  
        else if (id == PWM7_ID)
        {
            pPara->Freq = PWM7_FREQ;       // ����Ĭ��Ƶ��
            pPara->Chx = PWM7CH_EN;        // ����ʹ��ͨ�� 
        }
        #endif        
#endif        
        
        
        pPara->Num[0] = FREQ_N;        // ����ÿ��ͨ������������
        pPara->Num[1] = FREQ_N;
        pPara->Num[2] = FREQ_N;
        pPara->Num[3] = FREQ_N;
        while(PWM_Ctrl(id, CMD_PWM_STATUS, 0) != 0); // �ȴ�����������
        PWM_Ctrl(id, CMD_PWM_ENA, pPara);  // ����������ʹ��PWM��� 
        #if (DEBUG_APP_EN == 1)
        if (UserVars.Para.ATFlag&AT_PWM_FLAG)
        {
            printf("AT+PWM%d=%d,500,%d\r\n", id+1,pPara->Freq, FREQ_N);
        }
        #endif
    }	
    else if (Mode == PWM_RATE)    // ���Թ̶�Ƶ��ռ�ձȿɵ������������: ���PWM, Ƶ��1KHZ,ռ�ձ�0%-100%�ɵ�, ÿ��3��ռ�ձ�����10%;
    {
        pPara->Rate[0] += 100;       // ����10%ռ�ձ� 
        if (pPara->Rate[0]>1000)     // ����100%
        {
            pPara->Rate[0] = 0;      // ��������0%
        }
        pPara->Rate[1] += 100;       // ����10%ռ�ձ� 
        if (pPara->Rate[1]>1000)     // ����100%
        {
            pPara->Rate[1] = 0;      // ��������0%
        }
        pPara->Rate[2] += 100;       // ����10%ռ�ձ� 
        if (pPara->Rate[2]>1000)     // ����100%
        {
            pPara->Rate[2] = 0;      // ��������0%
        }
        pPara->Rate[3] += 100;       // ����10%ռ�ձ� 
        if (pPara->Rate[3]>1000)     // ����100%
        {
            pPara->Rate[3] = 0;      // ��������0%
        }        
        PWM_Ctrl(id, CMD_PWM_RATE, pPara);  // ����������ʹ��PWM��� 
        #if (DEBUG_APP_EN == 1)
        if (UserVars.Para.ATFlag&AT_PWM_FLAG)
        {
            printf("AT+PWM%d=%d,%d,0\r\n", id+1,pPara->Freq, pPara->Rate[0]);
        }
        #endif
    }
}
#endif

#if ((TIM1_EN > 0)||(TIM2_EN > 0)||(TIM3_EN > 0)||(TIM4_EN > 0)||(TIM5_EN > 0)||(TIM6_EN > 0)||(TIM7_EN > 0)||(TIM8_EN > 0)  \
    ||(TIM9_EN > 0)||(TIM10_EN > 0)||(TIM11_EN > 0)||(TIM12_EN > 0)||(TIM13_EN > 0)||(TIM14_EN > 0))
void TIM_Start(void)
{
    TIM_CTRL TIMCtrl;
    #if ((TIM1_EN == 1)&&(TIM1_MODE == TIM_WKMODE_INT))
        TIMCtrl.Chx = TIM1CH_EN;
        TIMCtrl.t = TIM1_T;            // ��������ʱ����ʱʱ��
        TIMCtrl.t1 = TIM1_T1;          // �����Ӷ�ʱ��1��ʱʱ��
        TIMCtrl.t2 = TIM1_T2;          // �����Ӷ�ʱ��2��ʱʱ��
        TIMCtrl.t3 = TIM1_T3;          // �����Ӷ�ʱ��3��ʱʱ��
        TIMCtrl.t4 = TIM1_T4;          // �����Ӷ�ʱ��4��ʱʱ��
       
        Timer_Ctrl(TIM1_ID, CMD_TIM_ENA, (TIM_CTRL *)&TIMCtrl.Chx);
    #endif
    
    #if ((TIM2_EN == 1)&&(TIM2_MODE == TIM_WKMODE_INT))
        TIMCtrl.Chx = TIM2CH_EN;
        TIMCtrl.t = TIM2_T;            // ��������ʱ����ʱʱ��
        TIMCtrl.t1 = TIM2_T1;          // �����Ӷ�ʱ��1��ʱʱ��
        TIMCtrl.t2 = TIM2_T2;          // �����Ӷ�ʱ��2��ʱʱ��
        TIMCtrl.t3 = TIM2_T3;          // �����Ӷ�ʱ��3��ʱʱ��
        TIMCtrl.t4 = TIM2_T4;          // �����Ӷ�ʱ��4��ʱʱ��
        
        Timer_Ctrl(TIM2_ID, CMD_TIM_ENA, (TIM_CTRL *)&TIMCtrl.Chx);
    #endif
    
    #if ((TIM3_EN == 1)&&(TIM3_MODE == TIM_WKMODE_INT))
        TIMCtrl.Chx = TIM3CH_EN;
        TIMCtrl.t = TIM3_T;            // ��������ʱ����ʱʱ��
        TIMCtrl.t1 = TIM3_T1;          // �����Ӷ�ʱ��1��ʱʱ��
        TIMCtrl.t2 = TIM3_T2;          // �����Ӷ�ʱ��2��ʱʱ��
        TIMCtrl.t3 = TIM3_T3;          // �����Ӷ�ʱ��3��ʱʱ��
        TIMCtrl.t4 = TIM3_T4;          // �����Ӷ�ʱ��4��ʱʱ��
        
        Timer_Ctrl(TIM3_ID, CMD_TIM_ENA, (TIM_CTRL *)&TIMCtrl.Chx);
    #endif
    
    #if ((TIM4_EN == 1)&&(TIM4_MODE == TIM_WKMODE_INT))
        TIMCtrl.Chx = TIM4CH_EN;
        TIMCtrl.t = TIM4_T;            // ��������ʱ����ʱʱ��
        TIMCtrl.t1 = TIM4_T1;          // �����Ӷ�ʱ��1��ʱʱ��
        TIMCtrl.t2 = TIM4_T2;          // �����Ӷ�ʱ��2��ʱʱ��
        TIMCtrl.t3 = TIM4_T3;          // �����Ӷ�ʱ��3��ʱʱ��
        TIMCtrl.t4 = TIM4_T4;          // �����Ӷ�ʱ��4��ʱʱ��
        
        Timer_Ctrl(TIM4_ID, CMD_TIM_ENA, (TIM_CTRL *)&TIMCtrl.Chx);
    #endif    
    
    #if ((TIM5_EN == 1)&&(TIM5_MODE == TIM_WKMODE_INT))
        TIMCtrl.Chx = TIM5CH_EN;
        TIMCtrl.t = TIM5_T;            // ��������ʱ����ʱʱ��
        TIMCtrl.t1 = TIM5_T1;          // �����Ӷ�ʱ��1��ʱʱ��
        TIMCtrl.t2 = TIM5_T2;          // �����Ӷ�ʱ��2��ʱʱ��
        TIMCtrl.t3 = TIM5_T3;          // �����Ӷ�ʱ��3��ʱʱ��
        TIMCtrl.t4 = TIM5_T4;          // �����Ӷ�ʱ��4��ʱʱ��
        
        Timer_Ctrl(TIM5_ID, CMD_TIM_ENA, (TIM_CTRL *)&TIMCtrl.Chx);
    #endif
    
    #if ((TIM6_EN == 1)&&(TIM6_MODE == TIM_WKMODE_INT))
        TIMCtrl.Chx = TIM6_EN;
        TIMCtrl.t = TIM6_T;            // ��������ʱ����ʱʱ��
        Timer_Ctrl(TIM6_ID, CMD_TIM_ENA, (TIM_CTRL *)&TIMCtrl.Chx);
    #endif   
    #if ((TIM7_EN == 1)&&(TIM7_MODE == TIM_WKMODE_INT))
        TIMCtrl.Chx = TIM7_EN;
        TIMCtrl.t = TIM7_T;            // ��������ʱ����ʱʱ��
        Timer_Ctrl(TIM7_ID, CMD_TIM_ENA, (TIM_CTRL *)&TIMCtrl.Chx);
    #endif     

#if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F407XX))
	#if ((TIM8_EN == 1)&&(TIM8_MODE == TIM_WKMODE_INT))
        TIMCtrl.Chx = TIM8CH_EN;
        TIMCtrl.t = TIM8_T;            // ��������ʱ����ʱʱ��
        TIMCtrl.t1 = TIM8_T1;          // �����Ӷ�ʱ��1��ʱʱ��
        TIMCtrl.t2 = TIM8_T2;          // �����Ӷ�ʱ��2��ʱʱ��
        TIMCtrl.t3 = TIM8_T3;          // �����Ӷ�ʱ��3��ʱʱ��
        TIMCtrl.t4 = TIM8_T4;          // �����Ӷ�ʱ��4��ʱʱ��
        
        Timer_Ctrl(TIM8_ID, CMD_TIM_ENA, (TIM_CTRL *)&TIMCtrl.Chx);
    #endif
#endif

#if (MODULE_CLASS == STM32F407XX)
    #if ((TIM9_EN == 1)&&(TIM9_MODE == TIM_WKMODE_INT))
        TIMCtrl.Chx = TIM9CH_EN;
        TIMCtrl.t = TIM9_T;            // ��������ʱ����ʱʱ��
        TIMCtrl.t1 = TIM9_T1;          // �����Ӷ�ʱ��1��ʱʱ��
        TIMCtrl.t2 = TIM9_T2;          // �����Ӷ�ʱ��2��ʱʱ��
        
        Timer_Ctrl(TIM9_ID, CMD_TIM_ENA, (TIM_CTRL *)&TIMCtrl.Chx);
    #endif
    #if ((TIM10_EN == 1)&&(TIM10_MODE == TIM_WKMODE_INT))
        TIMCtrl.Chx = TIM10CH_EN;
        TIMCtrl.t = TIM10_T;           // ��������ʱ����ʱʱ��
        TIMCtrl.t1 = TIM10_T1;         // �����Ӷ�ʱ��1��ʱʱ��
        
        Timer_Ctrl(TIM10_ID, CMD_TIM_ENA, (TIM_CTRL *)&TIMCtrl.Chx);
    #endif
    #if ((TIM11_EN == 1)&&(TIM11_MODE == TIM_WKMODE_INT))
        TIMCtrl.Chx = TIM11CH_EN;
        TIMCtrl.t = TIM11_T;           // ��������ʱ����ʱʱ��
        TIMCtrl.t1 = TIM11_T1;         // �����Ӷ�ʱ��1��ʱʱ��
        
        Timer_Ctrl(TIM11_ID, CMD_TIM_ENA, (TIM_CTRL *)&TIMCtrl.Chx);
    #endif  
    #if ((TIM12_EN == 1)&&(TIM12_MODE == TIM_WKMODE_INT))
        TIMCtrl.Chx = TIM12CH_EN;
        TIMCtrl.t = TIM12_T;            // ��������ʱ����ʱʱ��
        TIMCtrl.t1 = TIM12_T1;          // �����Ӷ�ʱ��1��ʱʱ��
        TIMCtrl.t2 = TIM12_T2;          // �����Ӷ�ʱ��2��ʱʱ��
        
        Timer_Ctrl(TIM12_ID, CMD_TIM_ENA, (TIM_CTRL *)&TIMCtrl.Chx);
    #endif    
    #if ((TIM13_EN == 1)&&(TIM13_MODE == TIM_WKMODE_INT))
        TIMCtrl.Chx = TIM13CH_EN;
        TIMCtrl.t = TIM13_T;           // ��������ʱ����ʱʱ��
        TIMCtrl.t1 = TIM13_T1;         // �����Ӷ�ʱ��1��ʱʱ��
        
        Timer_Ctrl(TIM13_ID, CMD_TIM_ENA, (TIM_CTRL *)&TIMCtrl.Chx);
    #endif
    
    #if ((TIM14_EN == 1)&&(TIM14_MODE == TIM_WKMODE_INT))
        TIMCtrl.Chx = TIM14CH_EN;
        TIMCtrl.t = TIM14_T;           // ��������ʱ����ʱʱ��
        TIMCtrl.t1 = TIM14_T1;         // �����Ӷ�ʱ��1��ʱʱ��
        
        Timer_Ctrl(TIM14_ID, CMD_TIM_ENA, (TIM_CTRL *)&TIMCtrl.Chx);
    #endif
    
#endif
}
#endif

#if ((TIM1_EN > 0)||(TIM2_EN > 0)||(TIM3_EN > 0)||(TIM4_EN > 0)||(TIM5_EN > 0)||(TIM6_EN > 0)||(TIM7_EN > 0)||(TIM8_EN > 0)  \
    ||(TIM9_EN > 0)||(TIM10_EN > 0)||(TIM11_EN > 0)||(TIM12_EN > 0)||(TIM13_EN > 0)||(TIM14_EN > 0)) 
void TIM_ReadCount(void)
{
    INT32U  cnt;
    
    // TIM1��ȡ����ֵ
    #if ((TIM1_EN == 1)&&(TIM1_MODE == TIM_WKMODE_COUNT)) // ��ʱ�������ڶ�ʱ����ģʽ
        Timer_Ctrl(TIM1_ID, CMD_TIM_ENA, 0);   // ʹ�ܶ�ʱ��
        Delay_ms(20);                          // ��ʱ20ms
        Timer_Ctrl(TIM1_ID, CMD_TIM_DIS, 0);   // �رն�ʱ�� 
        cnt = Timer_Ctrl(TIM1_ID, CMD_TIM_READ, 0); // ��ȡ20ms����ֵ
        #if (DEBUG_APP_EN == 1)
        if (UserVars.Para.ATFlag&AT_TIM_FLAG)
        {
            printf("AT+TIM1=%d\r\n", cnt);         // ��ӡ�������ֵ
        }
        #endif
    #endif
    
    // TIM2��ȡ����ֵ
    #if ((TIM2_EN == 1)&&(TIM2_MODE == TIM_WKMODE_COUNT)) // ��ʱ�������ڶ�ʱ����ģʽ
        Timer_Ctrl(TIM2_ID, CMD_TIM_ENA, 0);   // ʹ�ܶ�ʱ��
        Delay_ms(20);                          // ��ʱ20ms
        Timer_Ctrl(TIM2_ID, CMD_TIM_DIS, 0);   // �رն�ʱ�� 
        cnt = Timer_Ctrl(TIM2_ID, CMD_TIM_READ, 0); // ��ȡ20ms����ֵ
        #if (DEBUG_APP_EN == 1)
        //printf("TIM2����ֵ: %d\r\n", cnt);     // ��ӡ�������ֵ
        if (UserVars.Para.ATFlag&AT_TIM_FLAG)
        {
            printf("AT+TIM2=%d\r\n", cnt);         // ��ӡ�������ֵ
        }
        #endif
    #endif
    
    // TIM3��ȡ����ֵ
    #if ((TIM3_EN == 1)&&(TIM3_MODE == TIM_WKMODE_COUNT)) // ��ʱ�������ڶ�ʱ����ģʽ
        Timer_Ctrl(TIM3_ID, CMD_TIM_ENA, 0);   // ʹ�ܶ�ʱ��
        Delay_ms(20);                          // ��ʱ20ms
        Timer_Ctrl(TIM3_ID, CMD_TIM_DIS, 0);   // �رն�ʱ�� 
        cnt = Timer_Ctrl(TIM3_ID, CMD_TIM_READ, 0); // ��ȡ20ms����ֵ
        #if (DEBUG_APP_EN == 1)
        //printf("TIM3����ֵ: %d\r\n", cnt);     // ��ӡ�������ֵ
        if (UserVars.Para.ATFlag&AT_TIM_FLAG)
        {
            printf("AT+TIM3=%d\r\n", cnt);         // ��ӡ�������ֵ
        }
        #endif
    #endif
    
    // TIM4��ȡ����ֵ    
    #if ((TIM4_EN == 1)&&(TIM4_MODE == TIM_WKMODE_COUNT)) // ��ʱ�������ڶ�ʱ����ģʽ
        Timer_Ctrl(TIM4_ID, CMD_TIM_ENA, 0);   // ʹ�ܶ�ʱ��
        Delay_ms(20);                          // ��ʱ20ms
        Timer_Ctrl(TIM4_ID, CMD_TIM_DIS, 0);   // �رն�ʱ�� 
        cnt = Timer_Ctrl(TIM4_ID, CMD_TIM_READ, 0); // ��ȡ20ms����ֵ
        #if (DEBUG_APP_EN == 1)
        //printf("TIM4����ֵ: %d\r\n", cnt);     // ��ӡ�������ֵ
        if (UserVars.Para.ATFlag&AT_TIM_FLAG)
        {
            printf("AT+TIM4=%d\r\n", cnt);         // ��ӡ�������ֵ
        }
        #endif
    #endif
    
    // TIM5��ȡ����ֵ
    #if ((TIM5_EN == 1)&&(TIM5_MODE == TIM_WKMODE_COUNT)) // ��ʱ�������ڶ�ʱ����ģʽ
        Timer_Ctrl(TIM5_ID, CMD_TIM_ENA, 0);   // ʹ�ܶ�ʱ��
        Delay_ms(20);                          // ��ʱ20ms
        Timer_Ctrl(TIM5_ID, CMD_TIM_DIS, 0);   // �رն�ʱ�� 
        cnt = Timer_Ctrl(TIM5_ID, CMD_TIM_READ, 0); // ��ȡ20ms����ֵ
        #if (DEBUG_APP_EN == 1)
        //printf("TIM5����ֵ: %d\r\n", cnt);     // ��ӡ�������ֵ
        if (UserVars.Para.ATFlag&AT_TIM_FLAG)
        {
            printf("AT+TIM5=%d\r\n", cnt);         // ��ӡ�������ֵ
        }
        #endif
    #endif
    
    // TIM6��ȡ����ֵ
    #if ((TIM6_EN == 1)&&(TIM6_MODE == TIM_WKMODE_COUNT)) // ��ʱ�������ڶ�ʱ����ģʽ
        Timer_Ctrl(TIM6_ID, CMD_TIM_ENA, 0);   // ʹ�ܶ�ʱ��
        Delay_ms(20);                          // ��ʱ20ms
        Timer_Ctrl(TIM6_ID, CMD_TIM_DIS, 0);   // �رն�ʱ�� 
        cnt = Timer_Ctrl(TIM6_ID, CMD_TIM_READ, 0); // ��ȡ20ms����ֵ
        #if (DEBUG_APP_EN == 1)
        //printf("TIM6����ֵ: %d\r\n", cnt);     // ��ӡ�������ֵ
        if (UserVars.Para.ATFlag&AT_TIM_FLAG)
        {
            printf("AT+TIM6=%d\r\n", cnt);         // ��ӡ�������ֵ
        }
        #endif
    #endif
    
    // TIM7��ȡ����ֵ
    #if ((TIM7_EN == 1)&&(TIM7_MODE == TIM_WKMODE_COUNT)) // ��ʱ�������ڶ�ʱ����ģʽ
        Timer_Ctrl(TIM7_ID, CMD_TIM_ENA, 0);   // ʹ�ܶ�ʱ��
        Delay_ms(20);                          // ��ʱ20ms
        Timer_Ctrl(TIM7_ID, CMD_TIM_DIS, 0);   // �رն�ʱ�� 
        cnt = Timer_Ctrl(TIM7_ID, CMD_TIM_READ, 0); // ��ȡ20ms����ֵ
        #if (DEBUG_APP_EN == 1)
        //printf("TIM7����ֵ: %d\r\n", cnt);     // ��ӡ�������ֵ
        if (UserVars.Para.ATFlag&AT_TIM_FLAG)
        {
            printf("AT+TIM7=%d\r\n", cnt);         // ��ӡ�������ֵ
        }
        #endif
    #endif    
  
#if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F407XX))
	// TIM8��ȡ����ֵ
    #if ((TIM8_EN == 1)&&(TIM8_MODE == TIM_WKMODE_COUNT)) // ��ʱ�������ڶ�ʱ����ģʽ
        Timer_Ctrl(TIM8_ID, CMD_TIM_ENA, 0);   // ʹ�ܶ�ʱ��
        Delay_ms(20);                          // ��ʱ20ms
        Timer_Ctrl(TIM8_ID, CMD_TIM_DIS, 0);   // �رն�ʱ�� 
        cnt = Timer_Ctrl(TIM8_ID, CMD_TIM_READ, 0); // ��ȡ20ms����ֵ
        #if (DEBUG_APP_EN == 1)
        //printf("TIM8����ֵ: %d\r\n", cnt);     // ��ӡ�������ֵ
        if (UserVars.Para.ATFlag&AT_TIM_FLAG)
        {
            printf("AT+TIM8=%d\r\n", cnt);         // ��ӡ�������ֵ
        }
        #endif
    #endif  
#endif

#if (MODULE_CLASS == STM32F407XX)   
    // TIM9��ȡ����ֵ
    #if ((TIM9_EN == 1)&&(TIM9_MODE == TIM_WKMODE_COUNT)) // ��ʱ�������ڶ�ʱ����ģʽ
        Timer_Ctrl(TIM9_ID, CMD_TIM_ENA, 0);   // ʹ�ܶ�ʱ��
        Delay_ms(20);                          // ��ʱ20ms
        Timer_Ctrl(TIM9_ID, CMD_TIM_DIS, 0);   // �رն�ʱ�� 
        cnt = Timer_Ctrl(TIM9_ID, CMD_TIM_READ, 0); // ��ȡ20ms����ֵ
        #if (DEBUG_APP_EN == 1)
        //printf("TIM9����ֵ: %d\r\n", cnt);     // ��ӡ�������ֵ
        if (UserVars.Para.ATFlag&AT_TIM_FLAG)
        {
            printf("AT+TIM9=%d\r\n", cnt);         // ��ӡ�������ֵ
        }
        #endif
    #endif       
    // TIM10��ȡ����ֵ
    #if ((TIM10_EN == 1)&&(TIM10_MODE == TIM_WKMODE_COUNT)) // ��ʱ�������ڶ�ʱ����ģʽ
        Timer_Ctrl(TIM10_ID, CMD_TIM_ENA, 0);   // ʹ�ܶ�ʱ��
        Delay_ms(20);                          // ��ʱ20ms
        Timer_Ctrl(TIM10_ID, CMD_TIM_DIS, 0);   // �رն�ʱ�� 
        cnt = Timer_Ctrl(TIM10_ID, CMD_TIM_READ, 0); // ��ȡ20ms����ֵ
        #if (DEBUG_APP_EN == 1)
        //printf("TIM10����ֵ: %d\r\n", cnt);     // ��ӡ�������ֵ
        if (UserVars.Para.ATFlag&AT_TIM_FLAG)
        {
            printf("AT+TIM10=%d\r\n", cnt);         // ��ӡ�������ֵ
        }
        #endif
    #endif  
    // TIM11��ȡ����ֵ
    #if ((TIM11_EN == 1)&&(TIM11_MODE == TIM_WKMODE_COUNT)) // ��ʱ�������ڶ�ʱ����ģʽ
        Timer_Ctrl(TIM11_ID, CMD_TIM_ENA, 0);   // ʹ�ܶ�ʱ��
        Delay_ms(20);                          // ��ʱ20ms
        Timer_Ctrl(TIM11_ID, CMD_TIM_DIS, 0);   // �رն�ʱ�� 
        cnt = Timer_Ctrl(TIM11_ID, CMD_TIM_READ, 0); // ��ȡ20ms����ֵ
        #if (DEBUG_APP_EN == 1)
        //printf("TIM11����ֵ: %d\r\n", cnt);     // ��ӡ�������ֵ
        if (UserVars.Para.ATFlag&AT_TIM_FLAG)
        {
            printf("AT+TIM11=%d\r\n", cnt);         // ��ӡ�������ֵ
        }
        #endif
    #endif      
    // TIM12��ȡ����ֵ
    #if ((TIM12_EN == 1)&&(TIM12_MODE == TIM_WKMODE_COUNT)) // ��ʱ�������ڶ�ʱ����ģʽ
        Timer_Ctrl(TIM12_ID, CMD_TIM_ENA, 0);   // ʹ�ܶ�ʱ��
        Delay_ms(20);                          // ��ʱ20ms
        Timer_Ctrl(TIM12_ID, CMD_TIM_DIS, 0);   // �رն�ʱ�� 
        cnt = Timer_Ctrl(TIM12_ID, CMD_TIM_READ, 0); // ��ȡ20ms����ֵ
        #if (DEBUG_APP_EN == 1)
        //printf("TIM12����ֵ: %d\r\n", cnt);     // ��ӡ�������ֵ
        if (UserVars.Para.ATFlag&AT_TIM_FLAG)
        {
            printf("AT+TIM12=%d\r\n", cnt);         // ��ӡ�������ֵ
        }
        #endif
    #endif       
    // TIM13��ȡ����ֵ
    #if ((TIM13_EN == 1)&&(TIM13_MODE == TIM_WKMODE_COUNT)) // ��ʱ�������ڶ�ʱ����ģʽ
        Timer_Ctrl(TIM13_ID, CMD_TIM_ENA, 0);   // ʹ�ܶ�ʱ��
        Delay_ms(20);                          // ��ʱ20ms
        Timer_Ctrl(TIM13_ID, CMD_TIM_DIS, 0);   // �رն�ʱ�� 
        cnt = Timer_Ctrl(TIM13_ID, CMD_TIM_READ, 0); // ��ȡ20ms����ֵ
        #if (DEBUG_APP_EN == 1)
        //printf("TIM13����ֵ: %d\r\n", cnt);     // ��ӡ�������ֵ
        if (UserVars.Para.ATFlag&AT_TIM_FLAG)
        {
            printf("AT+TIM13=%d\r\n", cnt);         // ��ӡ�������ֵ
        }
        #endif
    #endif       
    // TIM14��ȡ����ֵ
    #if ((TIM14_EN == 1)&&(TIM14_MODE == TIM_WKMODE_COUNT)) // ��ʱ�������ڶ�ʱ����ģʽ
        Timer_Ctrl(TIM14_ID, CMD_TIM_ENA, 0);   // ʹ�ܶ�ʱ��
        Delay_ms(20);                          // ��ʱ20ms
        Timer_Ctrl(TIM14_ID, CMD_TIM_DIS, 0);   // �رն�ʱ�� 
        cnt = Timer_Ctrl(TIM14_ID, CMD_TIM_READ, 0); // ��ȡ20ms����ֵ
        #if (DEBUG_APP_EN == 1)
        //printf("TIM14����ֵ: %d\r\n", cnt);     // ��ӡ�������ֵ
        if (UserVars.Para.ATFlag&AT_TIM_FLAG)
        {
            printf("AT+TIM14=%d\r\n", cnt);         // ��ӡ�������ֵ
        }
        #endif
    #endif  
#endif
}
#endif


#if (MODULE_CLASS == STM32F407XX)
#define PWM_MAX_FREQ  200000     // STM32F407XXϵ��ģ����DMAģʽPWM�������Ƶ����200KHZ 
#endif

#if ((MODULE_CLASS == STM32F107XX)||(MODULE_CLASS == STM32F103XX))
#define PWM_MAX_FREQ  100000     // STM32F107XX��STM32F103XXϵ��ģ����DMAģʽPWM�������Ƶ����100KHZ 
#endif

#if ((PWM1_EN > 0)&&(PWM1_MODE==PWM_DMA))
#define PWM1_DATA_LEN   12
PWM_FREQ_TypeDef  PWM1Data[PWM1_DATA_LEN+1];  // PWM1�����������
// PWM1����������ݳ�ʼ��
void PWM1Data_Init(void)
{    
    // �����������4����ͬƵ����������
    PWM1Data[0].val = PWM_CMD01_TYPE+4;  
    PWM1Data[1].val = PWM_MAX_FREQ/5;    // ��1������Ƶ��        
    PWM1Data[2].val = PWM_MAX_FREQ/5*2;  // ��2������Ƶ��
    PWM1Data[3].val = PWM_MAX_FREQ/5*3;  // ��3������Ƶ��
    PWM1Data[4].val = PWM_MAX_FREQ/5*4;  // ��4������Ƶ��
    
    // �����������10����ͬƵ����������
    PWM1Data[5].val = PWM_CMD10_TYPE+10;
    PWM1Data[6].val = PWM_MAX_FREQ;   // ��10��(��5��-��14��)����Ƶ��  

    // �����������4����ͬƵ����������
    PWM1Data[7].val = PWM_CMD01_TYPE+4;  
    PWM1Data[8].val = PWM_MAX_FREQ/5*4;    // ��15������Ƶ��
    PWM1Data[9].val = PWM_MAX_FREQ/5*3;    // ��16������Ƶ��
    PWM1Data[10].val = PWM_MAX_FREQ/5*2;   // ��17������Ƶ��
    PWM1Data[11].val = PWM_MAX_FREQ/5;     // ��18������Ƶ��
    
    // ���һ����������Ϊ0, ��ʾ����
    PWM1Data[PWM1_DATA_LEN].val = 0;
}
#endif

#if ((PWM2_EN > 0)&&(PWM2_MODE==PWM_DMA))
#define PWM2_DATA_LEN   12
PWM_FREQ_TypeDef  PWM2Data[PWM2_DATA_LEN+1];  // PWM2�����������
// PWM2����������ݳ�ʼ��
void PWM2Data_Init(void)
{    
    // �����������4����ͬƵ����������
    PWM2Data[0].val = PWM_CMD01_TYPE+4;  
    PWM2Data[1].val = PWM_MAX_FREQ/5;    // ��1������Ƶ��        
    PWM2Data[2].val = PWM_MAX_FREQ/5*2;  // ��2������Ƶ��
    PWM2Data[3].val = PWM_MAX_FREQ/5*3;  // ��3������Ƶ��
    PWM2Data[4].val = PWM_MAX_FREQ/5*4;  // ��4������Ƶ��
    
    // �����������10����ͬƵ����������
    PWM2Data[5].val = PWM_CMD10_TYPE+10;
    PWM2Data[6].val = PWM_MAX_FREQ;   // ��10��(��5��-��14��)����Ƶ��  

    // �����������4����ͬƵ����������
    PWM2Data[7].val = PWM_CMD01_TYPE+4;  
    PWM2Data[8].val = PWM_MAX_FREQ/5*4;    // ��15������Ƶ��
    PWM2Data[9].val = PWM_MAX_FREQ/5*3;    // ��16������Ƶ��
    PWM2Data[10].val = PWM_MAX_FREQ/5*2;   // ��17������Ƶ��
    PWM2Data[11].val = PWM_MAX_FREQ/5;     // ��18������Ƶ��
    
    // ���һ����������Ϊ0, ��ʾ����
    PWM2Data[PWM2_DATA_LEN].val = 0;
}
#endif

#if ((PWM3_EN > 0)&&(PWM3_MODE==PWM_DMA))
#define PWM3_DATA_LEN   12
PWM_FREQ_TypeDef  PWM3Data[PWM3_DATA_LEN+1];  // PWM3�����������
// PWM3����������ݳ�ʼ��
void PWM3Data_Init(void)
{    
    // �����������4����ͬƵ����������
    PWM3Data[0].val = PWM_CMD01_TYPE+4;  
    PWM3Data[1].val = PWM_MAX_FREQ/5;    // ��1������Ƶ��        
    PWM3Data[2].val = PWM_MAX_FREQ/5*2;  // ��2������Ƶ��
    PWM3Data[3].val = PWM_MAX_FREQ/5*3;  // ��3������Ƶ��
    PWM3Data[4].val = PWM_MAX_FREQ/5*4;  // ��4������Ƶ��
    
    // �����������10����ͬƵ����������
    PWM3Data[5].val = PWM_CMD10_TYPE+10;
    PWM3Data[6].val = PWM_MAX_FREQ;   // ��10��(��5��-��14��)����Ƶ��  

    // �����������4����ͬƵ����������
    PWM3Data[7].val = PWM_CMD01_TYPE+4;  
    PWM3Data[8].val = PWM_MAX_FREQ/5*4;    // ��15������Ƶ��
    PWM3Data[9].val = PWM_MAX_FREQ/5*3;    // ��16������Ƶ��
    PWM3Data[10].val = PWM_MAX_FREQ/5*2;   // ��17������Ƶ��
    PWM3Data[11].val = PWM_MAX_FREQ/5;     // ��18������Ƶ��
    
    // ���һ����������Ϊ0, ��ʾ����
    PWM3Data[PWM3_DATA_LEN].val = 0;
}
#endif

#if ((PWM4_EN > 0)&&(PWM4_MODE==PWM_DMA))
#define PWM4_DATA_LEN   12
PWM_FREQ_TypeDef  PWM4Data[PWM4_DATA_LEN+1];  // PWM4�����������
// PWM4����������ݳ�ʼ��
void PWM4Data_Init(void)
{    
    // �����������4����ͬƵ����������
    PWM4Data[0].val = PWM_CMD01_TYPE+4;  
    PWM4Data[1].val = PWM_MAX_FREQ/5;    // ��1������Ƶ��        
    PWM4Data[2].val = PWM_MAX_FREQ/5*2;  // ��2������Ƶ��
    PWM4Data[3].val = PWM_MAX_FREQ/5*3;  // ��3������Ƶ��
    PWM4Data[4].val = PWM_MAX_FREQ/5*4;  // ��4������Ƶ��
    
    // �����������10����ͬƵ����������
    PWM4Data[5].val = PWM_CMD10_TYPE+10;
    PWM4Data[6].val = PWM_MAX_FREQ;   // ��10��(��5��-��14��)����Ƶ��  

    // �����������4����ͬƵ����������
    PWM4Data[7].val = PWM_CMD01_TYPE+4;  
    PWM4Data[8].val = PWM_MAX_FREQ/5*4;    // ��15������Ƶ��
    PWM4Data[9].val = PWM_MAX_FREQ/5*3;    // ��16������Ƶ��
    PWM4Data[10].val = PWM_MAX_FREQ/5*2;   // ��17������Ƶ��
    PWM4Data[11].val = PWM_MAX_FREQ/5;     // ��18������Ƶ��
    
    // ���һ����������Ϊ0, ��ʾ����
    PWM4Data[PWM4_DATA_LEN].val = 0;
}
#endif


void App_TaskPWMFClk(void *p_arg)
{	 
	INT16U rcnt, val;
	INT32U cnt;
    INT16U cnt1,cnt2,cnt3,cnt4;
    INT32S QEICount1,QEICount2,QEICount3,QEICount4,flag;
	INT32U Dir = 0;
	(void)p_arg;
	
	
	cnt = 0;
	QEICount1 = 0;
    QEICount2 = 0;
    QEICount3 = 0;
    QEICount4 = 0;
	cnt1 = 0;
	cnt2 = 0;
    cnt3 = 0;
    cnt4 = 0;
	
    #if (PWM1_EN > 0)
        #if (PWM1_MODE==PWM_DMA)    // DMA�������ģʽ
        UserVars.PWM1WritePara.Flag = PWM_FREQ_FLAG; // ѡ��ɱ�Ƶ���������
        UserVars.PWM1WritePara.ch = PWM_CH1;         // ѡ��ģʽ
        UserVars.PWM1WritePara.Freq = 0;             // Ƶ������, ���ģʽ��Ĭ��0
        UserVars.PWM1WritePara.Rate = 0;             // ռ�ձ�����, ���ģʽ��Ĭ��0  
        UserVars.PWM1WritePara.len = PWM1_DATA_LEN;  // ���ݳ���
        UserVars.PWM1WritePara.pData = PWM1Data;     // ����PWM����ָ��
        PWM1Data_Init();                             // ��ʼ��PWM����  
        #else
        PWM_Start(PWM1_ID, PWM1_MODE, (PWM_CTRL *)&UserVars.PWMPara[PWM1_ID].Mode);   // ����PWM1���
        #endif
    #endif
    
    #if (PWM2_EN > 0)
        #if (PWM2_MODE==PWM_DMA)   // DMA�������ģʽ
        UserVars.PWM2WritePara.Flag = PWM_FREQ_FLAG; // ѡ��ɱ�Ƶ���������
        UserVars.PWM2WritePara.ch = PWM_CH1;         // ѡ��ģʽ
        UserVars.PWM2WritePara.Freq = 0;             // Ƶ������, ���ģʽ��Ĭ��0
        UserVars.PWM2WritePara.Rate = 0;             // ռ�ձ�����, ���ģʽ��Ĭ��0  
        UserVars.PWM2WritePara.len = PWM2_DATA_LEN;  // ���ݳ���
        UserVars.PWM2WritePara.pData = PWM2Data;     // ����PWM����ָ��
        PWM2Data_Init();                             // ��ʼ��PWM����   
        #else
        PWM_Start(PWM2_ID, PWM2_MODE, (PWM_CTRL *)&UserVars.PWMPara[PWM2_ID].Mode);   // ����PWM2���
        #endif
    #endif
    #if (PWM3_EN > 0)
        #if (PWM3_MODE==PWM_DMA)   // DMA�������ģʽ
        UserVars.PWM3WritePara.Flag = PWM_FREQ_FLAG; // ѡ��ɱ�Ƶ���������
        UserVars.PWM3WritePara.ch = PWM_CH1;         // ѡ��ģʽ
        UserVars.PWM3WritePara.Freq = 0;             // Ƶ������, ���ģʽ��Ĭ��0
        UserVars.PWM3WritePara.Rate = 0;             // ռ�ձ�����, ���ģʽ��Ĭ��0  
        UserVars.PWM3WritePara.len = PWM3_DATA_LEN;  // ���ݳ���
        UserVars.PWM3WritePara.pData = PWM3Data;     // ����PWM����ָ��
        PWM3Data_Init();                             // ��ʼ��PWM����   
        #else
        PWM_Start(PWM3_ID, PWM3_MODE, (PWM_CTRL *)&UserVars.PWMPara[PWM3_ID].Mode);   // ����PWM3���
        #endif   
    #endif
    #if (PWM4_EN > 0)
        #if (PWM4_MODE==PWM_DMA)   // DMA�������ģʽ
        UserVars.PWM4WritePara.Flag = PWM_FREQ_FLAG; // ѡ��ɱ�Ƶ���������
        UserVars.PWM4WritePara.ch = PWM_CH1;         // ѡ��ģʽ
        UserVars.PWM4WritePara.Freq = 0;             // Ƶ������, ���ģʽ��Ĭ��0
        UserVars.PWM4WritePara.Rate = 0;             // ռ�ձ�����, ���ģʽ��Ĭ��0  
        UserVars.PWM4WritePara.len = PWM4_DATA_LEN;  // ���ݳ���
        UserVars.PWM4WritePara.pData = PWM4Data;     // ����PWM����ָ��
        PWM4Data_Init();                             // ��ʼ��PWM����   
        #else
        PWM_Start(PWM4_ID, PWM4_MODE, (PWM_CTRL *)&UserVars.PWMPara[PWM4_ID].Mode);   // ����PWM4���
        #endif    
    #endif
#if (MODULE_CLASS == STM32F407XX)
    #if (PWM5_EN > 0)
    PWM_Start(PWM5_ID, PWM5_MODE, (PWM_CTRL *)&UserVars.PWMPara[PWM5_ID].Mode);   // ����PWM5���
    #endif
    #if (PWM6_EN > 0)
    PWM_Start(PWM6_ID, PWM6_MODE, (PWM_CTRL *)&UserVars.PWMPara[PWM6_ID].Mode);   // ����PWM6���
    #endif
    #if (PWM7_EN > 0)
    PWM_Start(PWM7_ID, PWM7_MODE, (PWM_CTRL *)&UserVars.PWMPara[PWM7_ID].Mode);   // ����PWM7���
    #endif
    #if (PWM8_EN > 0)
    PWM_Start(PWM8_ID, PWM8_MODE, (PWM_CTRL *)&UserVars.PWMPara[PWM8_ID].Mode);   // ����PWM8���
    #endif
#endif   
    
    #if (FCLK1_EN > 0) 
    FCLK_Ctrl(FCLK1_ID, CMD_FCLK_ENA, FCLK1CH_EN);  // ʹ�ܹ���
    #endif
    #if (FCLK2_EN > 0) 
    FCLK_Ctrl(FCLK2_ID, CMD_FCLK_ENA, FCLK2CH_EN);  // ʹ�ܹ���
    #endif
    #if (FCLK3_EN > 0) 
    FCLK_Ctrl(FCLK3_ID, CMD_FCLK_ENA, FCLK3CH_EN);  // ʹ�ܹ���
    #endif
    #if (FCLK4_EN > 0) 
    FCLK_Ctrl(FCLK4_ID, CMD_FCLK_ENA, FCLK4CH_EN);  // ʹ�ܹ���
    #endif
    
#if (MODULE_CLASS == STM32F407XX) 
    #if (FCLK5_EN > 0) 
    FCLK_Ctrl(FCLK5_ID, CMD_FCLK_ENA, FCLK5CH_EN);  // ʹ�ܹ���
    #endif
    #if (FCLK6_EN > 0) 
    FCLK_Ctrl(FCLK6_ID, CMD_FCLK_ENA, FCLK6CH_EN);  // ʹ�ܹ���
    #endif
    #if (FCLK7_EN > 0) 
    FCLK_Ctrl(FCLK7_ID, CMD_FCLK_ENA, FCLK7CH_EN);  // ʹ�ܹ���
    #endif
    #if (FCLK8_EN > 0) 
    FCLK_Ctrl(FCLK8_ID, CMD_FCLK_ENA, FCLK8CH_EN);  // ʹ�ܹ���
    #endif
#endif


    #if ((TIM1_EN > 0)||(TIM2_EN > 0)||(TIM3_EN > 0)||(TIM4_EN > 0)||(TIM5_EN > 0)||(TIM6_EN > 0)||(TIM7_EN > 0)||(TIM8_EN > 0)  \
    ||(TIM9_EN > 0)||(TIM10_EN > 0)||(TIM11_EN > 0)||(TIM12_EN > 0)||(TIM13_EN > 0)||(TIM14_EN > 0)) 
    //TIM_Start(); // �������ж�ʱ������
    #endif    
    //Motor_Enable(StirFryMotor,Dir,0,20);
	while (1) 
	{
		UserVars.TaskRunStatus |= TASK_PWMFCLK_FLAG;  // ���ñ���������״̬��־
		Delay_ms(20);                                 // ��ʱ20ms	
		
        cnt++;
		if ((cnt%150)==0)          // ÿ��3��ִ��һ��
        {
			
            #if (PWM1_EN > 0)
                #if (PWM1_MODE==PWM_DMA)   // DMA�������ģʽ
                //Delay_ms(10);
                PWM_Write(PWM1_ID, &UserVars.PWM1WritePara.Flag);
                #else
//				UserVars.PWMPara[PWM1_ID].Mode = PWM_FREQ_N;
//                PWM_Test(PWM1_ID, PWM1_MODE, (PWM_CTRL *)&UserVars.PWMPara[PWM1_ID].Mode);  // PWM1�������
				
				Motor_Enable(PWM1_ID,Dir,UserVars.PWMPara[PWM1_ID].Freq,10);
				Dir=!Dir;
				UserVars.PWMPara[PWM1_ID].Freq += 1000;         // ÿ������1KHZ
				if (UserVars.PWMPara[PWM1_ID].Freq>10000)         // ����10KHZ
				{
					UserVars.PWMPara[PWM1_ID].Freq = 1000;        // ��������1000HZ
				}	
                #endif
            #endif
            #if (PWM2_EN > 0)
                #if (PWM2_MODE==PWM_DMA)   // DMA�������ģʽ
                //Delay_ms(10);
                PWM_Write(PWM2_ID, &UserVars.PWM2WritePara.Flag);
                #else
                PWM_Test(PWM2_ID, PWM2_MODE, (PWM_CTRL *)&UserVars.PWMPara[PWM2_ID].Mode);  // PWM2�������
                #endif            
            #endif
            #if (PWM3_EN > 0)
                #if (PWM3_MODE==PWM_DMA)   // DMA�������ģʽ
                //Delay_ms(10);
                PWM_Write(PWM3_ID, &UserVars.PWM3WritePara.Flag);
                #else
                PWM_Test(PWM3_ID, PWM3_MODE, (PWM_CTRL *)&UserVars.PWMPara[PWM3_ID].Mode);  // PWM3�������
                #endif              
            #endif
            #if (PWM4_EN > 0)
                #if (PWM4_MODE==PWM_DMA)   // DMA�������ģʽ
                //Delay_ms(10);
                PWM_Write(PWM4_ID, &UserVars.PWM4WritePara.Flag);
                #else
                PWM_Test(PWM4_ID, PWM4_MODE, (PWM_CTRL *)&UserVars.PWMPara[PWM4_ID].Mode);  // PWM4�������
                #endif 
            #endif
            
            #if (MODULE_CLASS == STM32F407XX) 
                #if (PWM5_EN > 0)
                PWM_Test(PWM5_ID, PWM5_MODE, (PWM_CTRL *)&UserVars.PWMPara[PWM5_ID].Mode);  // PWM5�������
                #endif
                #if (PWM6_EN > 0)
                PWM_Test(PWM6_ID, PWM6_MODE, (PWM_CTRL *)&UserVars.PWMPara[PWM6_ID].Mode);  // PWM6�������
                #endif
                #if (PWM7_EN > 0)
                PWM_Test(PWM7_ID, PWM7_MODE, (PWM_CTRL *)&UserVars.PWMPara[PWM7_ID].Mode);  // PWM7�������
                #endif
                #if (PWM8_EN > 0)
                PWM_Test(PWM8_ID, PWM8_MODE, (PWM_CTRL *)&UserVars.PWMPara[PWM8_ID].Mode);  // PWM8�������
                #endif
            #endif
            
            // ���巽��,ʹ�ܹܽż��3���л������ƽ
//            #ifdef PWM1_DIR
//            IO_Ctrl(PWM1_DIR, CMD_IO_NEG, 0);
//            #if (DEBUG_APP_EN == 1)
//            if (UserVars.Para.ATFlag&AT_PWM_FLAG)
//            {
//                printf("AT+PWM1=DIR,%d\r\n", IO_Read(PWM1_DIR));
//            }
//            #endif
//            #endif
//            #ifdef PWM1_ENA
//            IO_Ctrl(PWM1_ENA, CMD_IO_NEG, 0);
//            #if (DEBUG_APP_EN == 1)
//            if (UserVars.Para.ATFlag&AT_PWM_FLAG)
//            {
//                printf("AT+PWM1=ENA,%d\r\n", IO_Read(PWM1_ENA));
//            }
//            #endif
//            #endif
            
//            #ifdef PWM2_DIR
//            IO_Ctrl(PWM2_DIR, CMD_IO_NEG, 0);
//            #if (DEBUG_APP_EN == 1)
//            if (UserVars.Para.ATFlag&AT_PWM_FLAG)
//            {
//                printf("AT+PWM2=DIR,%d\r\n", IO_Read(PWM2_DIR));
//            }
//            #endif
//            #endif
//            #ifdef PWM2_ENA
//            IO_Ctrl(PWM2_ENA, CMD_IO_NEG, 0);
//            #if (DEBUG_APP_EN == 1)
//            if (UserVars.Para.ATFlag&AT_PWM_FLAG)
//            {
//                printf("AT+PWM2=ENA,%d\r\n", IO_Read(PWM2_ENA));
//            }
//            #endif
//            #endif
            
//            #ifdef PWM3_DIR
//            IO_Ctrl(PWM3_DIR, CMD_IO_NEG, 0);
//            #if (DEBUG_APP_EN == 1)
//            if (UserVars.Para.ATFlag&AT_PWM_FLAG)
//            {            
//                printf("AT+PWM3=DIR,%d\r\n", IO_Read(PWM3_DIR));
//            }
//            #endif
//            #endif
//            #ifdef PWM3_ENA
//            IO_Ctrl(PWM3_ENA, CMD_IO_NEG, 0);
//            #if (DEBUG_APP_EN == 1)
//            if (UserVars.Para.ATFlag&AT_PWM_FLAG)
//            {
//                printf("AT+PWM3=ENA,%d\r\n", IO_Read(PWM3_ENA));
//            }
//            #endif
//            #endif
            
//            #ifdef PWM4_DIR
//            IO_Ctrl(PWM4_DIR, CMD_IO_NEG, 0);
//            #if (DEBUG_APP_EN == 1)
//            if (UserVars.Para.ATFlag&AT_PWM_FLAG)
//            {
//                printf("AT+PWM4=DIR,%d\r\n", IO_Read(PWM4_DIR));
//            }
//            #endif
//            #endif
//            #ifdef PWM4_ENA
//            IO_Ctrl(PWM4_ENA, CMD_IO_NEG, 0);
//            #if (DEBUG_APP_EN == 1)
//            if (UserVars.Para.ATFlag&AT_PWM_FLAG)
//            {
//                printf("AT+PWM4=ENA,%d\r\n", IO_Read(PWM4_ENA));
//            }
//            #endif
//            #endif
            
             
            #if (FCLK1_EN > 0)                  
            FCLK_Test(FCLK1_ID, FCLK1_MODE);    // FCLK1�������  
            #endif
            #if (FCLK2_EN > 0)                  
            FCLK_Test(FCLK2_ID, FCLK2_MODE);    // FCLK2�������  
            #endif
            #if (FCLK3_EN > 0)                  
            FCLK_Test(FCLK3_ID, FCLK3_MODE);    // FCLK3�������  
            #endif
            #if (FCLK4_EN > 0)                  
            FCLK_Test(FCLK4_ID, FCLK4_MODE);    // FCLK4�������  
            #endif
            
            #if (MODULE_CLASS == STM32F407XX)
                #if (FCLK5_EN > 0)                  
                FCLK_Test(FCLK5_ID, FCLK5_MODE);    // FCLK5�������  
                #endif
                #if (FCLK6_EN > 0)                  
                FCLK_Test(FCLK6_ID, FCLK6_MODE);    // FCLK6�������  
                #endif
                #if (FCLK7_EN > 0)                  
                FCLK_Test(FCLK7_ID, FCLK7_MODE);    // FCLK7�������  
                #endif
                #if (FCLK8_EN > 0)                  
                FCLK_Test(FCLK8_ID, FCLK8_MODE);    // FCLK8�������  
                #endif
            #endif
            
            #if ((TIM1_EN > 0)||(TIM2_EN > 0)||(TIM3_EN > 0)||(TIM4_EN > 0)||(TIM5_EN > 0)||(TIM6_EN > 0)||(TIM7_EN > 0)||(TIM8_EN > 0)  \
            ||(TIM9_EN > 0)||(TIM10_EN > 0)||(TIM11_EN > 0)||(TIM12_EN > 0)||(TIM13_EN > 0)||(TIM14_EN > 0)) 
            TIM_ReadCount();
            #endif
        }
        
        
        // ÿ��20msִ��һ��
        #if ((FCLK1_EN > 0)&&(FCLK1_MODE == FCLK_MODE_DECODE)) // FCLK1ʹ��������������ģʽ
        flag = FCLK_Read(FCLK1_ID, CMD_FCLK_DECODE, 0, (INT32U *)&rcnt, 1, 0);
        if (flag == ERR_TRUE)
        {
            val = rcnt - cnt1;
            cnt1 = rcnt;
            QEICount1 += (INT16S)val;
            
            UserVars.FCLK[FCLK1_ID].QEICount = QEICount1;
        }
        else
        {
            UserVars.FCLK[FCLK1_ID].QEICount = 0;
        }  
        if ((cnt%50)==0)
        {
            #if (DEBUG_APP_EN == 1)
            if (UserVars.Para.ATFlag&AT_FCLK_FLAG)
            {
                printf("AT+FCLK1=N,%d\r\n", QEICount1);
            }
            #endif
        }  
        #endif
        #if ((FCLK2_EN > 0)&&(FCLK2_MODE == FCLK_MODE_DECODE)) // FCLK2ʹ��������������ģʽ
        flag = FCLK_Read(FCLK2_ID, CMD_FCLK_DECODE, 0, (INT32U *)&rcnt, 1, 0);
        if (flag == ERR_TRUE)
        {
            val = rcnt - cnt2;
            cnt2 = rcnt;
            QEICount2 += (INT16S)val;
            
            UserVars.FCLK[FCLK2_ID].QEICount = QEICount2;
        }
        else
        {
            UserVars.FCLK[FCLK2_ID].QEICount = 0;
        }            
        if ((cnt%50)==0)
        {
            #if (DEBUG_APP_EN == 1)
            if (UserVars.Para.ATFlag&AT_FCLK_FLAG)
            {
                printf("AT+FCLK2=N,%d\r\n", QEICount2);
            }
            #endif
        } 
        #endif
        #if ((FCLK3_EN > 0)&&(FCLK3_MODE == FCLK_MODE_DECODE)) // FCLK3ʹ��������������ģʽ
        flag = FCLK_Read(FCLK3_ID, CMD_FCLK_DECODE, 0, (INT32U *)&rcnt, 1, 0);
        if (flag == ERR_TRUE)
        {
            val = rcnt - cnt3;
            cnt3 = rcnt;
            QEICount3 += (INT16S)val;
            
            UserVars.FCLK[FCLK3_ID].QEICount = QEICount3;
        }
        else
        {
            UserVars.FCLK[FCLK3_ID].QEICount = 0;
        }  
        if ((cnt%50)==0)
        {
            if (UserVars.Para.ATFlag&AT_FCLK_FLAG)
            {            
                printf("AT+FCLK3=N,%d\r\n", QEICount3);
            }
        } 
        #endif
        #if ((FCLK4_EN > 0)&&(FCLK4_MODE == FCLK_MODE_DECODE)) // FCLK4ʹ��������������ģʽ
        flag = FCLK_Read(FCLK4_ID, CMD_FCLK_DECODE, 0, (INT32U *)&rcnt, 1, 0);
        if (flag == ERR_TRUE)
        {
            val = rcnt - cnt4;
            cnt4 = rcnt;
            QEICount4 += (INT16S)val;
            
            UserVars.FCLK[FCLK4_ID].QEICount = QEICount4;
        }
        else
        {
            UserVars.FCLK[FCLK4_ID].QEICount = 0;
        }  
        if ((cnt%50)==0)
        {
            if (UserVars.Para.ATFlag&AT_FCLK_FLAG)
            {
                printf("AT+FCLK4=N,%d\r\n", QEICount4);
            }
        } 
        #endif

    }
}

#endif
/***********************************************************************************/
// �ļ�����
/***********************************************************************************/


//void PWMData_Init(INT8U id)
//{
//    if (id == 0)
//    {    
//        /*
//        PWMData1[0].val = 0;
//        PWMData1[0].Cmd.Type = 1;
//        PWMData1[0].Cmd.Size = 4;
//        
//        PWMData1[1].val = 200000;
//        PWMData1[2].val = 150000;
//        PWMData1[3].val = 100000;
//        PWMData1[4].val = 50000;
//        
//        PWMData1[5].val = 0;
//        PWMData1[5].Cmd.Type = 2;
//        PWMData1[5].Cmd.Size = 5;
//        PWMData1[6].val = 200000;

//        
//        PWMData1[7].val = 0;
//        PWMData1[7].Cmd.Type = 1;
//        PWMData1[7].Cmd.Size = 4;
//        PWMData1[8].val = 50000;
//        PWMData1[9].val = 100000;
//        PWMData1[10].val = 150000;
//        PWMData1[11].val = 200000;
//        */
//        
//        
//        PWMData1[0].val = 0;
//        PWMData1[0].Cmd.Type = 1;
//        PWMData1[0].Cmd.Size = 4;
//        
//        PWMData1[1].val = 100000;
//        PWMData1[2].val = 80000;
//        PWMData1[3].val = 60000;
//        PWMData1[4].val = 50000;
//        
//        PWMData1[5].val = 0;
//        PWMData1[5].Cmd.Type = 2;
//        PWMData1[5].Cmd.Size = 5;
//        PWMData1[6].val = 100000;

//        
//        PWMData1[7].val = 0;
//        PWMData1[7].Cmd.Type = 1;
//        PWMData1[7].Cmd.Size = 4;
//        PWMData1[8].val = 50000;
//        PWMData1[9].val = 70000;
//        PWMData1[10].val = 90000;
//        PWMData1[11].val = 100000;
//        
//    }
//    if (id == 1)
//    {    
//        /*
//        PWMData2[0].val = 0;
//        PWMData2[0].Cmd.Type = 1;
//        PWMData2[0].Cmd.Size = 4;
//        
//        PWMData2[1].val = 1000;
//        PWMData2[2].val = 1500;
//        PWMData2[3].val = 2000;
//        PWMData2[4].val = 3000;
//        
//        PWMData2[5].val = 0;
//        PWMData2[5].Cmd.Type = 2;
//        PWMData2[5].Cmd.Size = 4;
//        PWMData2[6].val = 5000;

//        
//        PWMData2[7].val = 0;
//        PWMData2[7].Cmd.Type = 1;
//        PWMData2[7].Cmd.Size = 4;
//        PWMData2[8].val = 3000;
//        PWMData2[9].val = 2000;
//        PWMData2[10].val = 1500;
//        PWMData2[11].val = 1000;
//        */
//        /*
//        PWMData2[0].val = 0;
//        PWMData2[0].Cmd.Type = 1;
//        PWMData2[0].Cmd.Size = 4;
//        
//        PWMData2[1].val = 10000;
//        PWMData2[2].val = 15000;
//        PWMData2[3].val = 20000;
//        PWMData2[4].val = 30000;
//        
//        PWMData2[5].val = 0;
//        PWMData2[5].Cmd.Type = 2;
//        PWMData2[5].Cmd.Size = 4;
//        PWMData2[6].val = 50000;

//        
//        PWMData2[7].val = 0;
//        PWMData2[7].Cmd.Type = 1;
//        PWMData2[7].Cmd.Size = 4;
//        PWMData2[8].val = 30000;
//        PWMData2[9].val = 20000;
//        PWMData2[10].val = 15000;
//        PWMData2[11].val = 10000;
//        */
//        
//        PWMData2[0].val = 0;
//        PWMData2[0].Cmd.Type = 1;
//        PWMData2[0].Cmd.Size = 4;
//        
//        PWMData2[1].val = 100000;
//        PWMData2[2].val = 80000;
//        PWMData2[3].val = 60000;
//        PWMData2[4].val = 50000;
//        
//        PWMData2[5].val = 0;
//        PWMData2[5].Cmd.Type = 2;
//        PWMData2[5].Cmd.Size = 10;
//        PWMData2[6].val = 100000;

//        
//        PWMData2[7].val = 0;
//        PWMData2[7].Cmd.Type = 1;
//        PWMData2[7].Cmd.Size = 4;
//        PWMData2[8].val = 50000;
//        PWMData2[9].val = 70000;
//        PWMData2[10].val = 90000;
//        PWMData2[11].val = 100000;
//        
//        
//       /*
//        PWMData2[0].val = 0;
//        PWMData2[0].Cmd.Type = 1;
//        PWMData2[0].Cmd.Size = 4;
//        
//        PWMData2[1].val = 200000;
//        PWMData2[2].val = 150000;
//        PWMData2[3].val = 100000;
//        PWMData2[4].val = 50000;
//        
//        PWMData2[5].val = 0;
//        PWMData2[5].Cmd.Type = 2;
//        PWMData2[5].Cmd.Size = 10;
//        PWMData2[6].val = 200000;

//        
//        PWMData2[7].val = 0;
//        PWMData2[7].Cmd.Type = 1;
//        PWMData2[7].Cmd.Size = 4;
//        PWMData2[8].val = 50000;
//        PWMData2[9].val = 100000;
//        PWMData2[10].val = 150000;
//        PWMData2[11].val = 200000;
//        */
//    }
//}

