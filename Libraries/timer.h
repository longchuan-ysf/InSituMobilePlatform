/************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name:timer.h
* Project  : STM32F1XX/4XXϵ��ģ��������
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    20120.8.24			
* Email:   EmbedARM@126.com
* 
* Description: ���ļ���TimerӲ����������(����PWM��FCLK)ͷ�ļ�;
*
* Others: none;
*
* Function List: 
*          1. INT32S Timer_Init(INT8U id, TIM_PARA *pPara);
*          2. INT32S Timer_Ctrl(INT8U id, INT8U Cmd, TIM_CTRL *pPara);
*          3. INT32S PWM_Init(INT8U id, PWM_PARA *pPara);
*          4. INT32S PWM_Ctrl(INT8U id, INT8U Cmd, PWM_CTRL *pPara);
*          5. INT32S PWM_Write(INT8U id, PWM_WRITE *pPara);
*          6. INT32S FCLK_Init(INT8U id, FCLK_PARA *pPara);
*          7. INT32S FCLK_Ctrl(INT8U id, INT8U Cmd, INT8U Chx);
*          8. INT32S FCLK_Read(INT8U id, INT8U Cmd, INT8U Chx, INT32U *p, INT16U len, INT16U TimeOut);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 1.10
*	   Date:         2018.10.1
*      Modification: none
*
*************************************************************************************/
#ifndef __TIMER_H 
#define __TIMER_H 
/************************************************************************************/
// �����ⲿͷ�ļ�
/************************************************************************************/
#include "const.h"
/************************************************************************************/
// ��ʼ��������������
/************************************************************************************/
// Timer��������
#define TIM1_ID       0  
#define TIM2_ID       1
#define TIM3_ID       2
#define TIM4_ID       3
#define TIM5_ID       4
#define TIM6_ID       5
#define TIM7_ID       6
#define TIM8_ID       7		

//������STM32F M4����
#define TIM9_ID       8		
#define TIM10_ID      9		
#define TIM11_ID      10		
#define TIM12_ID      11		
#define TIM13_ID      12		
#define TIM14_ID      13		

// TIMER ����ģʽ
#define TIM_MODE_NONE       0  // ��ʱ������δ����; 
#define TIM_MODE_TIM        1  // ��ʱģʽ(���ⲿ�������); 
#define TIM_MODE_PWM        2  // PWM���(��������)ģʽ(CH1,CH2,CH3,CH4���);
#define TIM_MODE_FCLK       3  // ��������(CH1,CH2,CH3,CH4����);

// TIMER ��������
#define CMD_TIM_ENA       0	  // ʹ�ܶ�ʱ��
#define CMD_TIM_DIS       1	  // �رն�ʱ��
#define CMD_TIM_READ      2   // ��ȡ��ʱ����ֵ
#define CMD_TIM_STATUS    3	  // ��ȡ��ʱ��״̬
#define CMD_TIM_RST       4	  // ��λTIM�Ĵ���Ϊ��ʼ״̬
#define CMD_TIM_CLOSE     5	  // �ر�TIMʱ��,Ҳ���ǹر�TIM����,����ʡ�� 

// TIMͨ������ 
#define TIM_CH1 	0  
#define TIM_CH2 	1  
#define TIM_CH3 	2  
#define TIM_CH4 	3
#define TIM_MAIN 	4
#define TIM_ALL 	5

// TIM�жϱ�־
#define TIM_IT_FLAG            0x0001  // TIM����ʱ���жϱ�־(�����ж�)
#define TIM_CH1IT_FLAG         0x0002  // TIM CH1�Ӷ�ʱ��1�жϱ�־(����/�Ƚ�1�ж�)
#define TIM_CH2IT_FLAG         0x0004  // TIM CH2�Ӷ�ʱ��2�жϱ�־(����/�Ƚ�2�ж�)
#define TIM_CH3IT_FLAG         0x0008  // TIM CH3�Ӷ�ʱ��3�жϱ�־(����/�Ƚ�3�ж�)
#define TIM_CH4IT_FLAG         0x0010  // TIM CH4�Ӷ�ʱ��4�жϱ�־(����/�Ƚ�4�ж�)
#define TIM_COMIT_FLAG         0x0020  // TIM Commutation Interrupts
#define TIM_TRGIT_FLAG         0x0040  // TIM Trigger Interrupts
#define TIM_BRKIT_FLAG         0x0080  // TIM Break Interrupts

// ����������־(Flag)����
#define TIM_EN      0x0001  // ��ʱ��(����ʱ��)ʹ��; �������ʱ��û��ʹ�ܣ����Ӷ�ʱ��1-4ʹ����Ч
#define TIM_CH1EN   0x0002  // ��ʱ��ͨ��1(�Ӷ�ʱ��1)ʹ��
#define TIM_CH2EN   0x0004  // ��ʱ��ͨ��2(�Ӷ�ʱ��1)ʹ��
#define TIM_CH3EN   0x0008  // ��ʱ��ͨ��3(�Ӷ�ʱ��1)ʹ��
#define TIM_CH4EN   0x0010  // ��ʱ��ͨ��4(�Ӷ�ʱ��1)ʹ��



// ��ʱ������ģʽ
#define TIM_WKMODE_INT          0  // ��ʱ�������ڶ�ʱ�ж�ģʽ, ��ʱʱ���ɲ���t,t1-t4����; 
#define TIM_WKMODE_COUNT        1  // ��ʱ�������ڶ�ʱ����ģʽ, �ⲿͨ������Timer_Ctrl��������CMD_TIM_ENA/CMD_TIM_DIS����/ֹͣ��ʱ��,
                                   // ��ͨ������CMD_TIM_READ��ȡ����ֵ

// TIMER�����ṹ 
typedef struct
{
    INT32U Flag;    // ��������������־
    INT8U  Mode;    // ����ģʽ
    INT16U Prescaler;// ��Ƶϵ��, ������ģʽ��TIM_WKMODE_COUNTʱ, �������÷�Ƶϵ��
    //INT32U t;       // ����ʱ����ʱʱ��, ��λus
    //INT32U t1;      // �Ӷ�ʱ��1(����ʱ��CH1)��ʱʱ��, ��λus; ע�⣺��ʱʱ��ҪС������ʱ��
    //INT32U t2;      // �Ӷ�ʱ��2(����ʱ��CH2)��ʱʱ��, ��λus; ע�⣺��ʱʱ��ҪС������ʱ��
    //INT32U t3;      // �Ӷ�ʱ��3(����ʱ��CH3)��ʱʱ��, ��λus; ע�⣺��ʱʱ��ҪС������ʱ��
    //INT32U t4;      // �Ӷ�ʱ��4(����ʱ��CH4)��ʱʱ��, ��λus; ע�⣺��ʱʱ��ҪС������ʱ��
    //void (* isr) (INT8U flag, void *p);    // ����ʱ�����Ӷ�ʱ����ʱ�жϺ������Ӻ�?
}TIM_PARA;


// TIMER���Ʋ����ṹ 
typedef struct
{
    INT16U Chx;     // �����������Ӷ�ʱ��ѡ��:TIM_CH1EN~TIM_CH4EN,TIM_MAINEN    
    INT32U t;       // ����ʱ����ʱʱ��, ��λus
    INT32U t1;      // �Ӷ�ʱ��1(����ʱ��CH1)��ʱʱ��, ��λus; ע�⣺��ʱʱ��ҪС������ʱ��
    INT32U t2;      // �Ӷ�ʱ��2(����ʱ��CH2)��ʱʱ��, ��λus; ע�⣺��ʱʱ��ҪС������ʱ��
    INT32U t3;      // �Ӷ�ʱ��3(����ʱ��CH3)��ʱʱ��, ��λus; ע�⣺��ʱʱ��ҪС������ʱ��
    INT32U t4;      // �Ӷ�ʱ��4(����ʱ��CH4)��ʱʱ��, ��λus; ע�⣺��ʱʱ��ҪС������ʱ��
}TIM_CTRL;

/************************************************************************************************************************/
// ����2�����ǹ���ģ��STM32F107VC,STM32F103VE,STM32F103ZE��ʱ���ܽ�ӳ���, ��������ӳ�䷽ʽ����
/************************************************************************************************************************/
// TIM1(�ܽ�)������ӳ���
/*
|---------------------------------------------------------------------------------------------------------------|
| ��Ŀ  |  ��ӳ��  | CH1�ܽ� | CH2�ܽ� | CH3�ܽ� | CH4�ܽ� | CH1N�ܽ� | CH2N�ܽ� | CH3N�ܽ� | ETR�ܽ� | BKIN�ܽ�|
|---------------------------------------------------------------------------------------------------------------|
|       |   û��   |   PA8   |   PA9   |   PA10  |   PA11  |   PB13   |   PB14   |   PB15   |  PA12   |  PB12   |
|       |-------------------------------------------------------------------------------------------------------|
| TIM1  |  ��ӳ��1 |   PA8   |   PA9   |   PA10  |   PA11  |   PA7    |   PB0    |   PB1    |  PA12   |  PA6    |
|       |-------------------------------------------------------------------------------------------------------|
|       |  ��ӳ��3 |   PE9   |   PE11  |   PE13  |   PE14  |   PE8    |   PE10   |   PE12   |  PE7    |  PE15   |
|---------------------------------------------------------------------------------------------------------------|
*/

// TIM2-TIM5(�ܽ�)������ӳ���
/*
|--------------------------------------------------------------------|
| ��Ŀ  |  ��ӳ��  | CH1�ܽ� | CH2�ܽ� | CH3�ܽ� | CH4�ܽ� | ETR�ܽ� |
|--------------------------------------------------------------------|
|       |   û��   |PA0(ETR) |   PA1   |   PA2   |   PA3   |ͬCH1�ܽ�|
|       |------------------------------------------------------------|
|       |  ��ӳ��1 |PA15(ETR)|   PB3   |   PA2   |   PA3   |ͬCH1�ܽ�|
| TIM2  |------------------------------------------------------------|
|       |  ��ӳ��2 |PA0(ETR) |   PA1   |   PB10  |   PB11  |ͬCH1�ܽ�|
|       |------------------------------------------------------------|
|       |  ��ӳ��3 |PA15(ETR)|   PB3   |   PB10  |   PB11  |ͬCH1�ܽ�|
|--------------------------------------------------------------------|
|       |   û��   |   PA6   |   PA7   |   PB0   |   PB1   |   PD2   |
|       |------------------------------------------------------------|
| TIM3  |  ��ӳ��2 |   PB4   |   PB5   |   PB0   |   PB1   |   PD2   |
|       |------------------------------------------------------------|
|       |  ��ӳ��3 |   PC6   |   PC7   |   PC8   |   PC9   |   PD2   |
|--------------------------------------------------------------------|
|       |   û��   |   PB6   |   PB7   |   PB8   |   PB9   |   PE0   |
| TIM4  |------------------------------------------------------------|
|       |  ��ӳ��1 |   PD12  |   PD13  |   PD14  |   PD15  |   PE0   |
|--------------------------------------------------------------------|
| TIM5  |   û��   |   PA0   |   PA1   |   PA2   |   PA3   |   ��    |
|--------------------------------------------------------------------|
*/

/************************************************************************************************************************/
// ����3������ϵ�й���ģ��STM32F407XX��ʱ���ܽ�ӳ���, �����ùܽŸ��üĴ�������
/************************************************************************************************************************/
// TIM1/8�ܽŹ���ӳ���
/*
|---------------------------------------------------------------------------------------------------------------|
| ��Ŀ  | ����ѡ�� | CH1�ܽ� | CH2�ܽ� | CH3�ܽ� | CH4�ܽ� | CH1N�ܽ� | CH2N�ܽ� | CH3N�ܽ� | ETR�ܽ� | BKIN�ܽ�|
|---------------------------------------------------------------------------------------------------------------|
|       |          |   PA8   |   PA9   |   PA10  |   PA11  |   PB13   |   PB14   |   PB15   |  PA12   |  PB12   |
|       |          |--------------------------------------------------------------------------------------------|
| TIM1  |   AF1    |   PE9   |   PE11  |   PE13  |   PE14  |   PA7    |   PB0    |   PB1    |  PA12   |  PA6    |
|       |          |--------------------------------------------------------------------------------------------|
|       |          |    -    |    -    |    -    |    -    |   PE8    |   PE10   |   PE12   |  PE7    |  PE15   |
|---------------------------------------------------------------------------------------------------------------|
|       |          |   PC6   |   PC7   |   PC8   |   PC9   |   PA5    |   PB0    |   PB1    |  PA0    |  PA6    |
|       |          |--------------------------------------------------------------------------------------------|
| TIM8  |   AF3    |   PI5   |   PI6   |   PI7   |   PI2   |   PA7    |   PB14   |   PB15   |  PI3    |  PI4    |
|       |          |--------------------------------------------------------------------------------------------|
|       |          |    -    |    -    |    -    |    -    |   PH13   |   PH14   |   PH15   |   -     |   -     |
|---------------------------------------------------------------------------------------------------------------|
*/
// TIM2-TIM5�ܽŹ���ӳ���
/*
|--------------------------------------------------------------------|
| ��Ŀ  | ����ѡ�� | CH1�ܽ� | CH2�ܽ� | CH3�ܽ� | CH4�ܽ� | ETR�ܽ� |
|--------------------------------------------------------------------|
|       |          |   PA0   |   PA1   |   PA2   |   PA3   |   PA0   |
|       |          | ------------------------------------------------|
|       |   AF1    |   PA5   |   PB3   |   PB10  |   PB11  |   PA5   |
| TIM2  |          |-------------------------------------------------|
|       |          |   PA15  |    -    |    -    |    -    |   PA15  |
|--------------------------------------------------------------------|
|       |          |   PA6   |   PA7   |   PB0   |   PB1   |   PD2   |
|       |          |-------------------------------------------------|
| TIM3  |   AF2    |   PB4   |   PB5   |    -    |    -    |    -    |
|       |          |-------------------------------------------------|
|       |          |   PC6   |   PC7   |   PC8   |   PC9   |    -    |
|--------------------------------------------------------------------|
|       |          |   PB6   |   PB7   |   PB8   |   PB9   |   PE0   |
| TIM4  |   AF2    | ------------------------------------------------|
|       |          |   PD12  |   PD13  |   PD14  |   PD15  |    -    |
|--------------------------------------------------------------------|
|       |          |   PA0   |   PA1   |   PA2   |   PA3   |   ��    |
| TIM5  |   AF2    |-------------------------------------------------|
|       |          |   PH10  |   PH11  |   PH12  |   PI0   |    -    |
|--------------------------------------------------------------------|
*/
// TIM9-TIM14�ܽŹ���ӳ���
/*
|----------------------------------------------------------|
| ��Ŀ  | ����ѡ�� | CH1�ܽ� | CH2�ܽ� | CH3�ܽ� | CH4�ܽ� | 
|----------------------------------------------------------|
|       |          |   PA2   |   PA3   |    -    |    -    |
| TIM9  |   AF3    | --------------------------------------|
|       |          |   PE5   |   PE6   |    -    |    -    | 
|----------------------------------------------------------|
|       |          |   PB8   |    -    |    -    |    -    |
| TIM10 |   AF3    |---------------------------------------|
|       |          |   PF6   |    -    |    -    |    -    |
|----------------------------------------------------------|
|       |          |   PB9   |    -    |    -    |    -    |
| TIM11 |   AF3    | --------------------------------------|
|       |          |   PF7   |    -    |    -    |    -    |
|----------------------------------------------------------|
|       |          |   PB14  |   PB15  |    -    |    -    |
| TIM12 |   AF9    | --------------------------------------|
|       |          |   PH6   |   PH9   |    -    |    -    |
|----------------------------------------------------------|
|       |          |   PA6   |    -    |    -    |    -    |
| TIM13 |   AF9    | --------------------------------------|
|       |          |   PF8   |    -    |    -    |    -    |
|----------------------------------------------------------|
|       |          |   PA7   |    -    |    -    |    -    |
| TIM14 |   AF9    | --------------------------------------|
|       |          |   PF9   |    -    |    -    |    -    |
|----------------------------------------------------------|
*/

/************************************************************************************************************************/
// TIMER(�ܽ�)������ӳ�䶨��
#define TIM_REMAP_0       0    // TIMERû����ӳ��
#define TIM_REMAP_1       1    // TIMER��ӳ��1
#define TIM_REMAP_2       2    // TIMER��ӳ��2
#define TIM_REMAP_3       3    // TIMER��ӳ��3

// TIMER �ܽŲ����ṹ 
typedef struct
{
    INT8U  Remap; // TIMER���Ź�����ӳ��
    
    INT8U  CH1;   // ͨ��1�ܽŶ���
    INT8U  CH2;   // ͨ��2�ܽŶ���
    INT8U  CH3;   // ͨ��3�ܽŶ���
    INT8U  CH4;   // ͨ��4�ܽŶ���

    INT8U  CH1N;  // ͨ��1��������ܽŶ���
    INT8U  CH2N;  // ͨ��2��������ܽŶ���
    INT8U  CH3N;  // ͨ��3��������ܽŶ���
    
    INT8U  ETR;   // ETR�ܽŶ���
    INT8U  BKIN;  // BKIN�ܽŶ���    
}TIM_PIN;

/*************************************************************************************/
//
// 						TimerӲ����������������
//
/*************************************************************************************/
/***********************************************************************************
* Function: Timer_Init;
*
* Description: TIMER��ʼ������;
* 
* Input:  id, TIMER����: STM32F1XX: TIM1_ID ~ TIM8_ID; STM32F4XX: TIM1_ID ~ TIM14_ID;  
*         *pPara, ��ʼ������ָ��;
*
* Output: none;
*          		
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   none;
************************************************************************************/
INT32S Timer_Init(INT8U id, TIM_PARA *pPara);

/***********************************************************************************
* Function: Timer_Ctrl;
*
* Description: TIMER���Ʋ���;
* 
* Input:  id, TIMER����: STM32F1XX: TIM1_ID ~ TIM8_ID; STM32F4XX: TIM1_ID ~ TIM14_ID; 
*         Cmd, ��������: CMD_TIM_ENA:  ʹ�ܶ�ʱ��   
*                        CMD_TIM_DIS:  �رն�ʱ��
*                        CMD_TIM_STATUS: ��ȡ��ʱ��״̬
*         pPara, ����ֵ;
*
* Output: none;
*          		
* Return: ����������CMD_TIM_STATUSʱ����TIMER״̬;���������ERR_TRUE, ������ȷ, ERR_TRUE, ����ʧ��;
*
* Note:   ������������CMD_TIM_ENA, 
*         ������������CMD_TIM_STATUS, ������ֵ��0: ��ʱ��ֹͣ; 1����ʱ����������
************************************************************************************/
INT32S Timer_Ctrl(INT8U id, INT8U Cmd, TIM_CTRL *pPara);

/**********************************************************************************************/
// PWM��������
/**********************************************************************************************/
// PWM1-4��������
#define  PWM1_ID		  		0	   	// PWM1����
#define  PWM2_ID		  		1	   	// PWM2����
#define  PWM3_ID		  		2	   	// PWM3����
#define  PWM4_ID		  		3	   	// PWM4����

//������STM32F M4����
#define  PWM5_ID		  		4	   	// PWM5����
#define  PWM6_ID		  		5	   	// PWM6����
#define  PWM7_ID		  		6	   	// PWM7����
#define  PWM8_ID		  		7	   	// PWM8����


// PWMͨ������
#define  PWM_CH1          		0      	// PWMͨ��1
#define  PWM_CH2          		1      	// PWMͨ��2
#define  PWM_CH3          		2  		// PWMͨ��3
#define  PWM_CH4          		3   	// PWMͨ��4

// PWMͨ����־����
#define  PWM_CH1FLAG          	0x01   	// PWMͨ��1��־λ, ���ö�ͨ������ 
#define  PWM_CH2FLAG          	0x02   	// PWMͨ��2��־λ, ���ö�ͨ������ 
#define  PWM_CH3FLAG          	0x04   	// PWMͨ��3��־λ, ���ö�ͨ������ 
#define  PWM_CH4FLAG          	0x08   	// PWMͨ��4��־λ, ���ö�ͨ������ 

// PWM_Ctrl ���������
#define  CMD_PWM_ENA      		0  		// ʹ��, ����PWM���
#define  CMD_PWM_DIS      		1	 	// ֹͣ, �ر�PWM���
#define  CMD_PWM_FREQ     		2	 	// ����Ƶ��
#define  CMD_PWM_RATE     		3	 	// ����ռ�ձ�
#define  CMD_PWM_STATUS   		4	 	// ��ȡ״̬
#define  CMD_PWM_ENAMUL 		5  		// ͬʱʹ�ܶ�ͨ��   
#define  CMD_PWM_DISMUL 		6  		// ͬʱֹͣ��ͨ�� 
#define  CMD_PWM_PULNUM 		7  		// ��ȡ��ǰ�����������
#define  CMD_PWM_PAUSE 		    8  		// ��ʱֹͣPWM���


// Ӧ��PWM_Write()��������PWM�����, ����������ָ����PWM_Ctrl()����
#define  CMD_PWM_STOP      		8  		// ֹͣ



// ����PWM����ģʽ����
#define  PWM_FREQ       0   // ��������Ƶ�����, �������
#define  PWM_FREQ_N     1   // �������Ƶ�����, ������趨����������ֹͣ
#define  PWM_RATE       2   // �̶�Ƶ��ռ�ձȿɵ������������: ���PWM, Ƶ�ʹ̶�,ռ�ձ�0%-100%�ɵ�, �������
#define  PWM_DMA        3   // ��������ģʽ, ����PWM_Write()����ʵ��DMA�������ģʽ, ������Ʒ�ʽ�ɺ����������� 

// ����������־Flag����
#define PWMCH1_EN_FLAG  0x0001  // PWM CH1ʹ�ܱ�־��1, ʹ��; 0, �ر�
#define PWMCH2_EN_FLAG  0x0002  // PWM CH2ʹ�ܱ�־��1, ʹ��; 0, �ر�
#define PWMCH3_EN_FLAG  0x0004  // PWM CH3ʹ�ܱ�־��1, ʹ��; 0, �ر�
#define PWMCH4_EN_FLAG  0x0008  // PWM CH4ʹ�ܱ�־��1, ʹ��; 0, �ر�

#define PWMCH1_PIN_FLAG 0x0010  // PWM CH1ֹͣģʽ�ܽ������ƽ��־: 0, �͵�ƽ; 1, �ߵ�ƽ
#define PWMCH2_PIN_FLAG 0x0020  // PWM CH2ֹͣģʽ�ܽ������ƽ��־: 0, �͵�ƽ; 1, �ߵ�ƽ
#define PWMCH3_PIN_FLAG 0x0040  // PWM CH3ֹͣģʽ�ܽ������ƽ��־: 0, �͵�ƽ; 1, �ߵ�ƽ
#define PWMCH4_PIN_FLAG 0x0080  // PWM CH4ֹͣģʽ�ܽ������ƽ��־: 0, �͵�ƽ; 1, �ߵ�ƽ

#define PWM_WRITE_EN_FLAG   0x8000   // ʹ��PWM���������PWM_Write()��������
#define PWM_ISRHOOK_EN_FLAG 0x4000   // ʹ��PWM_ISRHOOK��������: ��PWM����������ɻ��߳�����øù��Ӻ���

// ���Ӻ���ISRHook()��idΪPWM1-8��������: PWM1_ID-PWM8_ID; Flag����ɱ�־�ͳ����־, ��������
#define PWMCH1_OK_FLAG  0x0001  // PWM CH1����������ɱ�־;
#define PWMCH2_OK_FLAG  0x0002  // PWM CH2����������ɱ�־;
#define PWMCH3_OK_FLAG  0x0004  // PWM CH3����������ɱ�־;
#define PWMCH4_OK_FLAG  0x0008  // PWM CH4����������ɱ�־;

#define PWMCH1_ERR_FLAG  0x0010  // PWM CH1��������ʧ�ܱ�־;
#define PWMCH2_ERR_FLAG  0x0020  // PWM CH2��������ʧ�ܱ�־;
#define PWMCH3_ERR_FLAG  0x0040  // PWM CH3��������ʧ�ܱ�־;
#define PWMCH4_ERR_FLAG  0x0080  // PWM CH4��������ʧ�ܱ�־;


// PWM�����ṹ 
typedef struct
{
    INT32U Flag;      // ����������־
    INT8U  Mode;      // PWM����ģʽ
    INT8U  TimerID;   // ѡ��ʱ��
    TIM_PIN TimPin;   // ��ѡ��ʱ���ܽŶ���
    INT32U Freq;      // PWM�����ʼƵ��
    INT16U Rate[4];   // 4��ͨ��,PWM���ռ�ձ�
    void (* pISRHook) (INT8U id, INT32U Flag); // PWM����ж�(�����)�������Ӻ���ָ��
}PWM_PARA;

#define PWM_CTRL_FREQ        0       // ���Ƹ���PWMƵ�����, �����������
#define PWM_CTRL_FREQ_N      1       // ���Ƹ���PWMƵ�����, �������N�������ֹͣ
#define PWM_CTRL_RATE        2       // ���Ƹ���PWMռ�ձ����
#define PWM_CTRL_FREQ_RATE   3       // ͬʱ���Ƹ���PWMƵ�ʺ�ռ�ձ����

// PWM���Ʋ����ṹ 
typedef struct
{
    INT8U  Mode;      // ���Ʋ���ģʽ
    INT8U  Chx;       // ѡ��ͨ��
    INT32U Freq;      // PWM���Ƶ��
    INT16U Rate[4];   // 4��ͨ��,PWM���ռ�ձ�
    INT32U Num[4];    // �����������
}PWM_CTRL;

//-------------------------------------------------------------------------
// Ӧ��PWM_Write()��������PWM�����, ����������ָ����PWM_Ctrl()����
// CMD_PWM_ENA: ʹ��, ����PWM���
// CMD_PWM_DIS: ֹͣ, �ر�PWM���; �رպ�ֻ����PWM_Write()���¿������
// CMD_PWM_STATUS: ��ȡ״̬   
// CMD_PWM_PULNUM: ��ȡ��ǰ�����������
// CMD_PWM_PAUSE:  ��ʱֹͣPWM���, �����ٷ�CMD_PWM_ENAʹ�ܼ������

// ����PWM_Write()��������
// ���弰�������ݸ�ʽ����
#define PWM_CMD_TYPE_MASK           0xC0000000  // ������������λ
#define PWM_CMD01_TYPE              0x40000000  // ���������ͬƵ����������λ
#define PWM_CMD10_TYPE              0x80000000  // ���������ͬƵ����������λ
#define PWM_CMD_SIZE_FLAG           0x00007FFF  // ����������־λ

#define PWM_DATA_TYPE               0x00000000  // ����λ
#define PWM_DATA_FREQ_FLAG          0x000FFFFF  // Ƶ��ֵ��־λ
typedef union 
{
    INT32U  val;     
    struct // �������ݽṹ: Type�̶�Ϊ01����10, revĬ��Ϊ0, SizeΪ�����������; ���Type��00, ���ʾbit19-bit0λ��Ƶ��ֵ
    {
        INT32U Size:                15; // �����������(bit14-bit0), ��Χ:2-32767 

        INT32U rev:                 15; // ����Ĭ����0(bit29-bit15);
        INT32U Type:                2;  // �������Ͷ���(bit31,bit30): 01, ����仯Ƶ������: ����һ�����ݿ�ʼ����, �������Size������, ÿ������Ƶ���ɺ���Size��Freq����ָ��; ע�Ȿ����Size���ַ�Χ������2-32767, һ����������Ƶ�ʼӼ������;
                                        //                            10, ����̶�Ƶ������: �̶�Ƶ������һ��Ƶ������(ֻ�й̶���һ��), �����������Size��;   ע�Ȿ����Size���ַ�Χ������2-32767, ��һ��SizeҪ��һЩ(�������16)�����ָ�ʽ����,
                                        //                                ��������ռ��CPU��Դ; һ�����ڹ̶�Ƶ���������
    }Cmd;
}PWM_FREQ_TypeDef;

typedef union 
{
    INT16U  val;     
    struct // �������ݽṹ: Type�̶�Ϊ01����10, revĬ��Ϊ0, SizeΪ�����������; ���Type��00, ���ʾbit13-bit0λ��ռ�ձ�ֵ
    {
        INT16U Size:                14; // �����������(bit13-bit0), ��Χ:2-16383 

        INT16U Type:                2;  // �������Ͷ���(bit15,bit14): 01, ����仯ռ�ձ�����: ����һ�����ݿ�ʼ����, �������Size������, ÿ������ռ�ձ��ɺ���Size������ָ��; ע�Ȿ����Size���ַ�Χ������2-16383, һ����������ռ�ձȼӼ������;
                                        //                            10, ����̶�ռ�ձ�����: �̶�ռ�ձ�����һ������(ֻ�й̶���һ��), �����������Size��;   ע�Ȿ����Size���ַ�Χ������2-16383, ��һ��SizeҪ��һЩ(�������16)�����ָ�ʽ����,
                                        //                                ��������ռ��CPU��Դ; һ�����ڹ̶�ռ�ձ��������
    }Cmd;
}PWM_RATE_TypeDef;

#define PWM_FREQ_FLAG       0x0001  // �ɱ�Ƶ�����������־ 
#define PWM_RATE_FLAG       0x0002  // �ɱ�ռ�ձ����������־
#define PWM_DATA_CONV_FLAG  0x8000  // ��������ת����ɱ�־


// PWMд����PWM_Write()�����ṹ 
typedef struct
{
    INT32U  Flag;      // ���Ʊ�־λ
    INT8U   ch;        // ѡ��PWM���ͨ��: PWM_CH1, PWM_CH2, PWM_CH3, PWM_CH4
    INT8U   chx;       // ѡ��PWM���ͨ����־: PWM_CH1FLAG, PWM_CH2FLAG, PWM_CH3FLAG, PWM_CH4FLAG
    INT16U  Rate;      // PWMռ�ձ�, ��ʱδ��
    INT32U  Freq;      // ����Ƶ�� 
    INT32U  len;       // ���ݻ�������
    void *pData;       // ���ݻ���ָ��
}PWM_WRITE;

/*************************************************************************************/
//
// 						PWMӲ����������������
//
/*************************************************************************************/
/***********************************************************************************
* Function: PWM_Init;
*
* Description: PWM��ʼ������;
* 
* Input:  id, PWM����(STM32F1XXϵ��оƬ: PWM1_ID~PWM4_ID; STM32F4XXϵ��оƬ: PWM1_ID~PWM8_ID) 
*         *pPara, ��ʼ������ָ�����ֵ;
*
* Output: none;
*          		
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   none;
************************************************************************************/
INT32S PWM_Init(INT8U id, PWM_PARA *pPara);

/***********************************************************************************
* Function: PWM_Ctrl;
*
* Description: PWM������Ʋ���;
* 
* Input:  id, PWM����(STM32F1XXϵ��оƬ: PWM1_ID~PWM4_ID; STM32F4XXϵ��оƬ: PWM1_ID~PWM8_ID) 
*         Cmd, ��������:  CMD_PWM_ENA, ʹ��;   
*                         CMD_PWM_DIS, ֹͣ;
*                         CMD_PWM_FREQ, ����PWMƵ��;  
*                         CMD_PWM_RATE, ����PWMռ�ձ�;  
*                         CMD_PWM_STATUS, ��ȡPWM״̬;
*                         CMD_PWM_PULNUM, ��ȡ��ǰ�����������
*         pPara, ����ָ��ṹ;
*
* Output: none;
*          		
* Return: ����������CMD_PWM_STATUSʱ����PWM״̬;���������ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   none;
************************************************************************************/
INT32S PWM_Ctrl(INT8U id, INT8U Cmd, PWM_CTRL *pPara);

/***********************************************************************************
* Function: PWM_Write;
*
* Description: PWMд����ƺ���;
* 
* Input:  id, PWM����(STM32F1XXϵ��оƬ: PWM1_ID~PWM4_ID; STM32F4XXϵ��оƬ: PWM1_ID~PWM8_ID)  
*         *pPara, ���Ʋ���ָ�����ֵ;
*
* Output: none;
*          		
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   ������ʹ��DMA��ʽ�������; ����PWM_Init()��ʼ��������PWM_WRITE_EN_FLAG��־λ
************************************************************************************/
INT32S PWM_Write(INT8U id, PWM_WRITE *pPara);

/**********************************************************************************************/
// FCLK��������
/**********************************************************************************************/
#define  FCLK1_ID		  		0	   	// FCLK1����
#define  FCLK2_ID		  		1	   	// FCLK2����
#define  FCLK3_ID		  		2	   	// FCLK3����
#define  FCLK4_ID		  		3	   	// FCLK4����
//������STM32F4XX����
#define  FCLK5_ID		  		4	   	// FCLK5����
#define  FCLK6_ID		  		5	   	// FCLK6����
#define  FCLK7_ID		  		6	   	// FCLK7����
#define  FCLK8_ID		  		7	   	// FCLK8����

// FCLKͨ������
#define  FCLK_CH1          		0      	// FCLKͨ��1
#define  FCLK_CH2          		1      	// FCLKͨ��2
#define  FCLK_CH3          		2  		// FCLKͨ��3
#define  FCLK_CH4          		3   	// FCLKͨ��4

// Modify 2020.4.8: ��ͨ����־��Ϊbit4-bit7
#define  FCLK_CH1FLAG          	0x01   	// FCLKͨ��1��־λ, ���ö�ͨ������ 
#define  FCLK_CH2FLAG          	0x02   	// FCLKͨ��2��־λ, ���ö�ͨ������ 
#define  FCLK_CH3FLAG          	0x04   	// FCLKͨ��3��־λ, ���ö�ͨ������ 
#define  FCLK_CH4FLAG          	0x08   	// FCLKͨ��4��־λ, ���ö�ͨ������ 

//#define  FCLK_CH1FLAG          	0x10   	// FCLKͨ��1��־λ, ���ö�ͨ������ 
//#define  FCLK_CH2FLAG          	0x20   	// FCLKͨ��2��־λ, ���ö�ͨ������ 
//#define  FCLK_CH3FLAG          	0x40   	// FCLKͨ��3��־λ, ���ö�ͨ������ 
//#define  FCLK_CH4FLAG          	0x80   	// FCLKͨ��4��־λ, ���ö�ͨ������ 

//#define  FCLK_CH1FULL  	       	0x10   	// FCLKͨ��1��������־λ
//#define  FCLK_CH2FULL   	    0x20   	// FCLKͨ��2��������־λ
//#define  FCLK_CH3FULL     	   	0x40   	// FCLKͨ��3��������־λ
//#define  FCLK_CH4FULL       	0x80   	// FCLKͨ��4��������־λ

// FCLK ����ģʽ
#define  FCLK_MODE_COUNT       0  		// ����ģʽ(1·, CH1����); 
#define  FCLK_MODE_DECODE      1  		// ��������������(CH1�����A, CH2�����B);
#define  FCLK_MODE_FREQ        2  		// ��Ƶģʽ(CH1,CH2,CH3,CH4����);
#define  FCLK_MODE_PWMRATE     3  		// ��PWMռ�ձ�ģʽ(CH1����);

// FCLK_Read�������������
#define  CMD_FCLK_FREQ         0  // ��ʱ�������ȡFCLK(CH1~CH4)Ƶ��: Ƶ��ֵ��ʱ���������, ����ȡbuf[0]��Tʱ�ɼ�, ��buf[N]��T-Nʱ�ɼ�; 
                                  // ����Ҫ����������Ƶ�ʶ�Ҫ��ȡʱ�����ָ��, �������̶����ʱ����ϵ�����Ƶ��  
#define  CMD_FCLK_PWMRATE      1  // ��ȡFCLK(CH1) ��ռ�ձ�: 
#define  CMD_FCLK_DECODE       2  // ��ȡFCLK(CH1 CH2)�����������ֵ
#define  CMD_FCLK_COUNT		   3  // ��ȡFCLK(CH1)����ֵ

#define  CMD_FCLK_FREQ_ORDER   4  // ��ʱ�������ȡFCLK(CH1~CH4)Ƶ�ʣ�Ƶ��ֵ��ʱ���������, ����ȡbuf[0]��Tʱ�ɼ�, ��buf[N]��T+Nʱ�ɼ�
                                  // ����Ҫ��ȡȫ������Ƶ��ֵʱ, �����ָ��  

// FCLK_Ctrl ���������
#define   CMD_FCLK_ENA      0  // ʹ�ܵ�һͨ��;   
#define   CMD_FCLK_DIS      1  // ֹͣ��һͨ��;  
#define   CMD_FCLK_STATUS   2  // ��ȡFCLK״̬;
#define   CMD_FCLK_CLEAR    3  // ��ʱ��ֵ����
#define   CMD_FCLK_CNT      4  // ��ȡ��������Ƶ�ʻ���ռ�ձ�����


// ����������־Flag����
#define FCLKCH1_EN_FLAG  0x00000001  // FCLK CH1ʹ�ܱ�־��1, ʹ��; 0, �ر�
#define FCLKCH2_EN_FLAG  0x00000002  // FCLK CH2ʹ�ܱ�־��1, ʹ��; 0, �ر�
#define FCLKCH3_EN_FLAG  0x00000004  // FCLK CH3ʹ�ܱ�־��1, ʹ��; 0, �ر�
#define FCLKCH4_EN_FLAG  0x00000008  // FCLK CH4ʹ�ܱ�־��1, ʹ��; 0, �ر�

#define FCLKCH1_PIN_FLAG 0x00000010  // FCLK CH1�ܽ������źŴ������أ� 0, ������; 1, �½���
#define FCLKCH2_PIN_FLAG 0x00000020  // FCLK CH2�ܽ������źŴ������أ� 0, ������; 1, �½���
#define FCLKCH3_PIN_FLAG 0x00000040  // FCLK CH3�ܽ������źŴ������أ� 0, ������; 1, �½���
#define FCLKCH4_PIN_FLAG 0x00000080  // FCLK CH4�ܽ������źŴ������أ� 0, ������; 1, �½���

#define FCLKCH1_PCS_FLAG 0x00000300  // FCLK CH1�ܽ������ź�Ԥ��Ƶϵ���� 0, ����Ƶ; 1, 2��Ƶ; 2, 4��Ƶ; 3, 8��Ƶ;
#define FCLKCH2_PCS_FLAG 0x00000C00  // FCLK CH2�ܽ������ź�Ԥ��Ƶϵ���� 0, ����Ƶ; 1, 2��Ƶ; 2, 4��Ƶ; 3, 8��Ƶ;
#define FCLKCH3_PCS_FLAG 0x00003000  // FCLK CH3�ܽ������ź�Ԥ��Ƶϵ���� 0, ����Ƶ; 1, 2��Ƶ; 2, 4��Ƶ; 3, 8��Ƶ;
#define FCLKCH4_PCS_FLAG 0x0000C000  // FCLK CH4�ܽ������ź�Ԥ��Ƶϵ���� 0, ����Ƶ; 1, 2��Ƶ; 2, 4��Ƶ; 3, 8��Ƶ;

// �������ܶ���
#define FCLKCH1_DMA_FLAG 0x00010000  // FCLK CH1 DMA����ʹ��
#define FCLKCH2_DMA_FLAG 0x00020000  // FCLK CH2 DMA����ʹ��
#define FCLKCH3_DMA_FLAG 0x00040000  // FCLK CH3 DMA����ʹ��
#define FCLKCH4_DMA_FLAG 0x00080000  // FCLK CH4 DMA����ʹ��

// ��������־����
#define FCLKCH1_BUFFULL_FLAG 0x01000000  // FCLK CH1 ��������־
#define FCLKCH2_BUFFULL_FLAG 0x02000000  // FCLK CH2 ��������־
#define FCLKCH3_BUFFULL_FLAG 0x04000000  // FCLK CH3 ��������־
#define FCLKCH4_BUFFULL_FLAG 0x08000000  // FCLK CH4 ��������־

#define FCLK_ETR_FLAG    0x80000000  // FCLK��ETR����Ϊʱ������;
#define FCLK_MKY_FLAG    0x40000000  // FCLK��ú��ԺУ׼ʱ��;


// FCLK�����ṹ 
typedef struct
{
    INT32U Flag;      // ����������־
    INT8U  Mode;      // FCLK����ģʽ
    INT8U  TimerID;   // ѡ��ʱ��
    TIM_PIN TimPin;   // ��ѡ��ʱ���ܽŶ���
    INT32U MinFreq;   // PWM�����ʼƵ��
    INT16U *pBuf[4];  // �������ݻ���ָ��
    INT16U BufLen[4]; // ���ջ��泤��   
}FCLK_PARA;

/*************************************************************************************/
//
// 						FCLKӲ����������������
//
/*************************************************************************************/
/***********************************************************************************
* Function: FCLK_Init;
*
* Description: FCLK��ʼ������;
* 
* Input:  id, FCLK����(STM32F1XXϵ��оƬ: FCLK1_ID~FCLK4_ID; STM32F4XXϵ��оƬ: FCLK1_ID~FCLK8_ID) 
*         *pPara, FCLK��ʼ������ָ��;
*
* Output: none;
*          		
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   none;
************************************************************************************/
INT32S FCLK_Init(INT8U id, FCLK_PARA *pPara);

/***********************************************************************************
* Function: FCLK_Ctrl;
*
* Description: FCLK������Ʋ���;
* 
* Input:  id, FCLK����(STM32F1XXϵ��оƬ: FCLK1_ID~FCLK4_ID; STM32F4XXϵ��оƬ: FCLK1_ID~FCLK8_ID) 
*         Cmd, ��������:  CMD_FCLK_ENA, ʹ��;   
*                         CMD_FCLK_DIS, ֹͣ;
*                         CMD_FCLK_STATUS, ��ȡFCLK״̬;
                          CMD_FCLK_CLEAR,  ��ʱ��ֵ���� 
                          CMD_FCLK_CNT,    ��ȡ��������Ƶ�ʻ���ռ�ձ�����
*         Chx, ͨ������FCLK_CH1FLAG~FCLK_CH4FLAG,���Զ�ͨ������; ����ͨ������:FCLK_CH1~FCLK_CH4,ֻ�ܵ�ͨ������; 
*
* Output: none;
*          		
* Return: ����������CMD_PWM_STATUSʱ����FCLK״̬; ����������CMD_FCLK_CNTʱ��������ֵ; 
*        ���������ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   Cmd����������CMD_FCLK_ENA/CMD_FCLK_DIS/CMD_FCLK_STATUSʱͨ����Chx��: FCLK_CH1FLAG~FCLK_CH4FLAG, 
*                      ���Խ��л����, ʵ�ֶ�ͨ������, ����: (FCLK_CH1FLAG|FCLK_CH1FLAG);   
*         Cmd����������CMD_FCLK_CLEAR, ͨ����Chx��Ч,Ĭ��0;
*         Cmd����������CMD_FCLK_CNT, ͨ����Chx��:FCLK_CH1~FCLK_CH4,ֻ�ܵ�ͨ������, ; 
************************************************************************************/
INT32S FCLK_Ctrl(INT8U id, INT8U Cmd, INT8U Chx);

/***********************************************************************************
* Function: FCLK_Read;
*
* Description: FCLK��ȡ��ֵ;
* 
* Input:  id, FCLK����(STM32F1XXϵ��оƬ: FCLK1_ID~FCLK4_ID; STM32F4XXϵ��оƬ: FCLK1_ID~FCLK8_ID) 
*         cmd, ��ȡ����: CMD_FCLK_FREQ, ��ȡFCLK_CH1, FCLK_CH2,FCLK_CH3,FCLK_CH4��Ƶ��, ��λ��0.01hz
*                     	 CMD_FCLK_DECODE, ��ȡ�����������ֵ, �������ݲ�֧��;
*                        CMD_FCLK_PWMRATE, ��ȡFCLK_CH1��ռ�ձ�, ��λ��0.01%; 
*                        CMD_FCLK_COUNT, ��ȡ����ֵ; 
*         chx, ͨ������: FCLK_CH1~FCLK_CH4, ֻ�ܵ�ͨ������; 
*         *p,  ���ݻ���ָ��;
*         len, ���ݳ���; 
*         timeout, ��ʱ����;
*
* Output: none;
*          		
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   none;
************************************************************************************/
INT32S FCLK_Read(INT8U id, INT8U Cmd, INT8U Chx, INT32U *p, INT16U len, INT16U TimeOut);

#endif
/***********************************************************************************/
// �ļ�����
/***********************************************************************************/