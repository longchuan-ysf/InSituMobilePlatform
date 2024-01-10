/************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: TastADC_DAC.c
* Project  : STM32F1XX/4XXϵ��ģ�����
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.00
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: ���ļ�����ADC�ɼ���DAC1/2ת�����������;
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
// DAC1/DAC2����˵��
/************************************************************************************/
/*      
(1). ����˵��: ����3��ģʽ��ѡһ��  
    �ֶ����ģʽ����: DAC1_EN/DAC2_EN����Ϊ1, DAC1_MODE/DAC2_MODE����0(DAC_MODE_MTOUT)ģʽ,������Ĭ������;
    ������ʵ�ֹ���: ÿ��3��DAC���ֵ����409(0.25V��1V), ͨ�����ñ�ɲ�������˿ڵ�ѹ�仯;
    
    �������1~N�������е����ݺ�ֹͣģʽ����: DAC1_EN/DAC2_EN����Ϊ1, DAC1_MODE/DAC2_MODE����1(DAC_MODE_ATOUT_N)ģʽ,������Ĭ������;
    ������ʵ�ֹ���: ÿ��3��DAC���4���̶�Ƶ����������, ͨ��ʾ������������˿���ʾ; 
    
    ������������е�����ģʽ����: DAC1_EN/DAC2_EN����Ϊ1, DAC1_MODE/DAC2_MODE����2(DAC_MODE_ATOUT)ģʽ,������Ĭ������;
    ������ʵ�ֹ���: ÿ��3��DAC�������Ƶ����1KHZ��2khz�仯, �������������, ͨ��ʾ����������ʾ; 
    
(2). ��APP_Init.c�е���DAC_APPInit()�����ȳ�ʼ��;   

(3). ��ģʽ1��2�б����ʼ������, �������е������������������(DACTyte = SINE_WAVE), �ٵ���DAC_SetWave(DAC1/2_ID, DACTyte, DAC1_TXBUF_SIZE, 50)��䲨�����ݵ�����;

(4). ��ģʽ0��2��, ����DAC_Ctrl(DAC1/2_ID, CMD_DAC_ENA, 0)ʹ�����; ��ģʽ1��, ����DAC_Ctrl(DAC1/2_ID, CMD_DAC_ENA, 4)ʹ�����, 4��ʾ���4����������;

(5). ÿ��3��������:  
     ģʽ0: ����DAC_Write(DAC1/2_ID, val)�������, valÿ��3������409, ���4095(12λAD���ֵ4095); 
     
     ģʽ1: ����DAC_Ctrl(DAC1/2_ID, CMD_DAC_STATUS, 0), �ж���һ��ʹ������Ĳ���(4��)�Ѿ�������, 
            �ٵ���DAC_Ctrl(DAC1/2_ID, CMD_DAC_FREQ, DAC1/2_FREQ), �����µ����Ƶ��DAC1/2_FREQ,
            ������DAC_Ctrl(DAC1/2_ID, CMD_DAC_ENA, 4)�����������4������
     
     ģʽ2: �����µ����Ƶ�ʱ���freq1/2, ��������1KHZ��2KHZ�仯; �ٵ���DAC_Ctrl(DAC1_ID, CMD_DAC_FREQ, freq1/2)�������Ƶ��
*/
/************************************************************************************/
// ADC����˵��
/************************************************************************************/
/*
(1). IO����: ��IO�˿������ļ���, ���ݰ���Ӳ���˿�ģ��������AI1-AI8��ģ��ģ����AIN0-AIN15��Ӧ��ϵ
             ���ö˿ڶ���, ����:  
             #define  AI1        AIN0    // ����AI1<->AIN0(PA0)
             #define  AI2        AIN3    // ����AI2<->AIN3(PA3)

(2). ����˵��: 
    ADC_EN����Ϊ1; ADC_OUT_TYPEѡ��0(ADC_ISROUT,�����ж϶�ȡ����)����1(ADC_READOUT, ���ú���AD_Read��ȡ����)ģʽ; 
    AI1_EN~AI10_EN: ���ð���AD����ͨ���˿�ʹ��, һ��Ӳ����Ƽ�·��ʹ�ܼ�·, �����AI1_EN��ʼ, ��������, ���������ⲿ��5·AD���룬����ʹ��AI1_EN~AI5_EN;
    ADC_CHNUM: �Ǹ���ʹ��AIx_EN����Զ������ⲿAD����ͨ�������������޸�; 
    ADC_AVGNUM: ������ƽ���˲�����, һ������Ϊ4��8����;
    ADC_FREQ: ����ADת��������ݵ�Ƶ��, ����10����ÿ�������10������, �ͻ�����ʵ����Ҫ���ò���̫��, һ��1-100;
    ADC_SAMPLE_TIME: �������, �����޸�, Ĭ�����ü���;
    ADC_TIM5�� ����TIM5���Ӷ�ʱ����ΪAD������ʱ, Ĭ��ADC_TIM5CH1_FLAG�Ϳ�����, �����޸�; 
    AI1_RANGE~AI10_RANGE: ���ð��Ӷ˿��������̷�Χ;
    
(3). ��APP_Init.c�е���ADC_APPInit()�����ȳ�ʼ��;       

(3). ����ADC_Ctrl(ADC1_ID, CMD_ADC_ENA, 0) ����ADת��;	 
    
(4). �������ʽ��0(ADC_ISROUT,�����ж϶�ȡ����), ����pADC = OSMboxPend(OSMboxADC, 10, &err) ��ȡADת������,������Ӧ����; 
     �������ʽ��1(ADC_READOUT, ���ú���AD_Read��ȡ����), ����AD_Read��ȡADת������,������Ӧ����;  

(5). ͨ�����ڵ�������۲�AD�������;
*/
/************************************************************************************/

/************************************************************************************/

// �����ⲿͷ�ļ�
#include "config.h"
#if (TASK_ADCDAC_EN == 1)
#include "Vars.h"
#include "UserVars.h"
#include "OSVars.h"
#include "math.h"
#include "STM32Fxxx.h"

/************************************************************************************/

/************************************************************************************/
// ������ȫ�ֱ�������
/************************************************************************************/
// ��ѹ������ʽ�� K = ʵ���ѹ��׼/2.5,  V = K*V���� + ����*(K-1)
const AI_Range[10] = {AI1_RANGE, AI2_RANGE, AI3_RANGE, AI4_RANGE, AI5_RANGE, AI6_RANGE, AI7_RANGE, AI8_RANGE, AI9_RANGE, AI10_RANGE};
/***************************************************************************/
// DAC1/DAC2��������
/***************************************************************************/
#define SINE_WAVE    0   // ���Ҳ�
#define TRI_WAVE     1   // ���ǲ�
#define SQUARE_WAVE  2   // ����

#define SQUARE_RATE  50  // ����ռ�ձ�50%
#define PI_  3.14165926

/***************************************************************************/
/***********************************************************************************
* Function: ADC_Conv;
*
* Description: ���ݸ�ͨ���������������ʵ������ֵ;
* 
* Input:  Cmd, ��������; val,AD����ԭʼֵ
*
* Output: none;
*          		
* Return: ���ؼ�������AIʵ������ֵ;
*
* Note:   none;
************************************************************************************/
INT16S ADC_Conv(INT8U Cmd, INT16S val)
{
    INT16S rst;
				
	switch (Cmd)
	{
	    case 1:	   // 0~+10V
			rst = 10000*(INT32U)val/4095;
		    break;
	    case 2:	   // -10V~+10V
			rst = 10000*((INT32S)val-2048)/2048;
		    break;
	    case 3:	   // 0~5V
			rst = 5000*(INT32U)val/4095;;
		    break;
	    case 4:	   // -5V~+5V
			rst = 5000*((INT32S)val-2048)/2048;
		    break;
	    case 5:	   // 0~+20mA
            #if (PRODUCT_TYPE == EMB8600I)
			rst = 20000*(INT32U)val/4095;
            rst *= 1.00835;  // ��Ϊ�����·��250ŷ��30K������ʵ�ʲ���������247.93ŷ
		    #else
            rst = 20000*(INT32U)val/4095;
            #endif
            break;
		case 6:	   // -20mA~+20mA
			rst = 20000*((INT32S)val-2048)/2048;
		    break;
	    default:
			rst = val;
		    break;
	}
	
	return rst;
}

/***********************************************************************************
* Function: DAC_SetWave;
*
* Description: ���DAC�����������;
* 
* Input:  id, ADC����(DAC1_ID~DAC2_ID);
*         type, ��������: SINE_WAVE,TRI_WAVE,SQUARE_WAVE
*         size, ������ݵĳ���
*         rate, ռ�ձ�, ������������SQUARE_WAVEʱ,����������÷�����ռ�ձ�, 1-99%�ɵ�; ��������������Ч.
*
* Output: none;
*          		
* Return: ERR_TRUE: ��ȷ; ERR_FALSE: ʧ��;
*
* Note:   none;
************************************************************************************/
// rate �����Ƿ���ռ�ձ�0~100
void DAC_SetWave(INT8U id, INT8U type, INT16U size, INT16U rate)
{
	INT16U i, val, x;

	if (type == TRI_WAVE)	    // ���ǲ�
	{
		x = 4096*2/size;

		for (i=0; i<(size/2); i++)
		{
			val = (i+1)*x;
			if (val>4095)
			{
				val = 4095;
			}
			//DAC_WriteBuffer(id, i, &val, 1);
            #if ((DAC1_EN>0)&&(DAC1_MODE>0))
			if (id == DAC1_ID)
            {
                DAC1_Buffer[i] = val;
            }
            #endif
            #if ((DAC2_EN>0)&&(DAC2_MODE>0))
			if (id == DAC2_ID)
            {
                DAC2_Buffer[i] = val;
            }
            #endif
            
			val = i*x;
			//DAC_WriteBuffer(id, size-i-1, &val, 1);
            #if ((DAC1_EN>0)&&(DAC1_MODE>0))
            if (id == DAC1_ID)
            {                
                DAC1_Buffer[size-i-1] = val;
            }
            #endif
            #if ((DAC2_EN>0)&&(DAC2_MODE>0))
            if (id == DAC2_ID)
            {
                DAC2_Buffer[size-i-1] = val;
            }
            #endif
		}
	}
	else if (type == SINE_WAVE)	// ���Ҳ�
	{
		val = 4096/size;
		for (i=0; i<size; i++)
		{
			val = 2048*sin((float)2*PI*i/size)+2048;
			if (val>=4096)
			{
			    val = 4095;
			}
            #if ((DAC1_EN>0)&&(DAC1_MODE>0))
            if (id == DAC1_ID)
            {
                DAC1_Buffer[i] = val;
            }
            #endif
            
            #if ((DAC2_EN>0)&&(DAC2_MODE>0))
            if (id == DAC2_ID)
            {
                DAC2_Buffer[i] = val;
            }
            #endif
			//DAC_WriteBuffer(id, i, &val, 1);
		}
	}

	else if (type == SQUARE_WAVE)  // ����
	{
	    x = size*rate/100;
		val = 4095;
		for (i=0; i<x; i++)
		{
			//DAC_WriteBuffer(id, i, &val, 1);
            #if ((DAC1_EN>0)&&(DAC1_MODE>0))
            if (id == DAC1_ID)
            {
                DAC1_Buffer[i] = val;
            }
            #endif
            
            #if ((DAC2_EN>0)&&(DAC2_MODE>0))
            if (id == DAC2_ID)
            {
                DAC2_Buffer[i] = val;
            }
            #endif
		}

		val = 0;
	    for (i = x; i<size; i++)
		{
			//DAC_WriteBuffer(id, i, &val, 1);
            #if ((DAC1_EN>0)&&(DAC1_MODE>0))
            if (id == DAC1_ID)
            {
                DAC1_Buffer[i] = val;
            }
            #endif
            #if ((DAC2_EN>0)&&(DAC2_MODE>0))
            if (id == DAC2_ID)
            {
                DAC2_Buffer[i] = val;
            }
            #endif
		}
	}
}

void AI_Printf(void)
{
    if (UserVars.Para.ATFlag&AT_AI_FLAG)
    {               
        printf("AT+AI=%d", AI_NUM);
        #if (AI1_EN == 1)   // �ж�AI1ʹ��
        printf(",%d", UserVars.ADC.buf[AI1_ID]);
        #endif
        #if (AI2_EN == 1)   // �ж�AI2ʹ��
        printf(",%d", UserVars.ADC.buf[AI2_ID]);
        #endif
        #if (AI3_EN == 1)   // �ж�AI3ʹ��
        printf(",%d", UserVars.ADC.buf[AI3_ID]);
        #endif
        #if (AI4_EN == 1)   // �ж�AI4ʹ��
        printf(",%d", UserVars.ADC.buf[AI4_ID]);
        #endif
        #if (AI5_EN == 1)   // �ж�AI5ʹ��
        printf(",%d", UserVars.ADC.buf[AI5_ID]);
        #endif
        #if (AI6_EN == 1)   // �ж�AI6ʹ��
        printf(",%d", UserVars.ADC.buf[AI6_ID]);
        #endif
        #if (AI7_EN == 1)   // �ж�AI7ʹ��
        printf(",%d", UserVars.ADC.buf[AI7_ID]);
        #endif
        #if (AI8_EN == 1)   // �ж�AI8ʹ��
        printf(",%d", UserVars.ADC.buf[AI8_ID]);
        #endif
        #if (AI9_EN == 1)   // �ж�AI9ʹ��
        printf(",%d", UserVars.ADC.buf[AI9_ID]);
        #endif
        #if (AI10_EN == 1)  // �ж�AI10ʹ��
        printf(",%d", UserVars.ADC.buf[AI10_ID]);
        #endif
        printf("\r\n");    
    }
}    

void App_TaskInductionCooker(void *p_arg)
{	 
	INT8U err, DACTyte;
	INT32U  t, flag;
	ADC_VAR *pADC;
	INT16U i, freq1,freq2, val;
    TIM_CTRL TIMCtrl;
        
/**************************************************************************/
// DAC1/DAC2ʹ�ܿ�ʼ����
/**************************************************************************/
    #if (DAC1_EN==1)     // DAC1ʹ��
        #if	(DAC1_MODE > 0)
        // ���������������
        DACTyte = SINE_WAVE;                  // �������������
        //DACTyte = TRI_WAVE;                 // ����������ǲ�
        //DACTyte = SQUARE_WAVE;              // �����������
        DAC_SetWave(DAC1_ID, DACTyte, DAC1_TXBUF_SIZE, 50);  // DAC1��䲨�����ݵ�����
        #endif
    
        #if	(DAC1_MODE == 1) // ��ģʽ1
        DAC_Ctrl(DAC1_ID, CMD_DAC_ENA, 4);  // DAC1ʹ���������4�����Ҳ���ֹͣ
        #else
        DAC_Ctrl(DAC1_ID, CMD_DAC_ENA, 0);  // DAC1ʹ��
        #endif
    #endif

    #if (DAC2_EN==1)        // DAC1ʹ��
        #if (DAC2_MODE > 0)                   // �������
        // ���������������
        DACTyte = SINE_WAVE;                  // �������������
        //DACTyte = TRI_WAVE;                 // ����������ǲ�
        //DACTyte = SQUARE_WAVE;              // �����������
        DAC_SetWave(DAC2_ID, DACTyte, DAC2_TXBUF_SIZE, 25);  // DAC2��䲨�����ݵ�����
        #endif    
        #if	(DAC2_MODE == 1)    // ��ģʽ1
        DAC_Ctrl(DAC2_ID, CMD_DAC_ENA, 4);  // DAC2ʹ���������4�����ǲ���ֹͣ
        #else
        DAC_Ctrl(DAC2_ID, CMD_DAC_ENA, 0);  // DAC2ʹ��
        #endif
	#endif														  
    freq1 = DAC1_FREQ;
    freq2 = DAC2_FREQ;
/**************************************************************************/
// ADCʹ�ܿ�ʼ����
/**************************************************************************/
	// ����ADת����ʱ��
    #if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F107XX))
    #if ((TIM5_EN == 1)&&(TIM5_MODE == TIM_WKMODE_INT))
        TIMCtrl.Chx = TIM5CH_EN;
        TIMCtrl.t = TIM5_T;            // ��������ʱ����ʱʱ��
        TIMCtrl.t1 = TIM5_T1;          // �����Ӷ�ʱ��1��ʱʱ��
        TIMCtrl.t2 = TIM5_T2;          // �����Ӷ�ʱ��2��ʱʱ��
        TIMCtrl.t3 = TIM5_T3;          // �����Ӷ�ʱ��3��ʱʱ��
        TIMCtrl.t4 = TIM5_T4;          // �����Ӷ�ʱ��4��ʱʱ��
        
        Timer_Ctrl(TIM5_ID, CMD_TIM_ENA, (TIM_CTRL *)&TIMCtrl.Chx);
    #endif
    #endif
    
    #if (MODULE_CLASS == STM32F407XX)
    #if ((TIM14_EN == 1)&&(TIM14_MODE == TIM_WKMODE_INT))
        TIMCtrl.Chx = TIM14CH_EN;
        TIMCtrl.t = TIM14_T;           // ��������ʱ����ʱʱ��
        TIMCtrl.t1 = TIM14_T1;         // �����Ӷ�ʱ��1��ʱʱ��
        
        Timer_Ctrl(TIM14_ID, CMD_TIM_ENA, (TIM_CTRL *)&TIMCtrl.Chx);
    #endif
    #endif
    
    // ʹ��ADת��
    ADC_Ctrl(ADC1_ID, CMD_ADC_ENA, 0);	   // ����ADת��;	
    
	t = 0;
	while(1)
    {
		UserVars.TaskRunStatus |= TASK_ADCDAC_FLAG;  // ���ñ���������״̬��־
        
        #if (ADC_OUT_TYPE == ADC_ISROUT)             // �ж����ж����AD����ֵ
		pADC = OSMboxPend(OSMboxADC, 100, &err);      // ��ȡADת�����
		if (err==OS_ERR_NONE)
		{        
            // �������̼���ʵ������ֵ
            #if (AI1_EN == 1)   // �ж�AI1ʹ��
            UserVars.ADC.buf[AI1_ID] = ADC_Conv(AI_Range[AI1_ID], pADC->pBuf[AI1_ID]); // ��ȡAI1����ֵ������
            #endif
            #if (AI2_EN == 1)   // �ж�AI2ʹ��
            UserVars.ADC.buf[AI2_ID] = ADC_Conv(AI_Range[AI2_ID], pADC->pBuf[AI2_ID]); // ��ȡAI2����ֵ������
            #endif
            #if (AI3_EN == 1)   // �ж�AI3ʹ��
            UserVars.ADC.buf[AI3_ID] = ADC_Conv(AI_Range[AI3_ID], pADC->pBuf[AI3_ID]); // ��ȡAI3����ֵ������
            #endif
            #if (AI4_EN == 1)   // �ж�AI4ʹ��
            UserVars.ADC.buf[AI4_ID] = ADC_Conv(AI_Range[AI4_ID], pADC->pBuf[AI4_ID]); // ��ȡAI4����ֵ������
            #endif
            #if (AI5_EN == 1)   // �ж�AI5ʹ��
            UserVars.ADC.buf[AI5_ID] = ADC_Conv(AI_Range[AI5_ID], pADC->pBuf[AI5_ID]); // ��ȡAI5����ֵ������
            #endif
            #if (AI6_EN == 1)   // �ж�AI6ʹ��
            UserVars.ADC.buf[AI6_ID] = ADC_Conv(AI_Range[AI6_ID], pADC->pBuf[AI6_ID]); // ��ȡAI6����ֵ������
            #endif
            #if (AI7_EN == 1)   // �ж�AI7ʹ��
            UserVars.ADC.buf[AI7_ID] = ADC_Conv(AI_Range[AI7_ID], pADC->pBuf[AI7_ID]); // ��ȡAI7����ֵ������
            #endif
            #if (AI8_EN == 1)   // �ж�AI8ʹ��
            UserVars.ADC.buf[AI8_ID] = ADC_Conv(AI_Range[AI8_ID], pADC->pBuf[AI8_ID]); // ��ȡAI8����ֵ������
            #endif
            #if (AI9_EN == 1)   // �ж�AI9ʹ��
            UserVars.ADC.buf[AI9_ID] = ADC_Conv(AI_Range[AI9_ID], pADC->pBuf[AI9_ID]); // ��ȡAI9����ֵ������
            #endif
            #if (AI10_EN == 1)  // �ж�AI10ʹ��
            UserVars.ADC.buf[AI10_ID] = ADC_Conv(AI_Range[AI10_ID], pADC->pBuf[AI10_ID]); // ��ȡAI10����ֵ������
            #endif       

            #if (MODBUS_SLAVE_EN > 0)    // Modbus�豸ģʽʹ��
            for (i=0; i<ADC_MAX_BUF_SIZE; i++)
            {
                ModbusInputReg[i] = UserVars.ADC.buf[i];  // ��ADת��ֵд��Modbus����Ĵ���
            }
            #endif 
            
            #if (DEBUG_APP_EN > 0)
            if ((t%3000)==0) // ���3Sʱ����ʾ���AIֵ
            {            
                AI_Printf();  // ��ӡ���AI����  
            }
            #endif
            t += 100;
        } 
        //else
        //{
        //    t += 1000;
        //}            
        
        #else    // ����ADC_Read()������ȡADת��ֵ
        Delay_ms(100);   // ���100ms��ȡADֵ   
        t += 100;         
        // ��ȡAD���� 
        flag = ADC_Read(ADC1_ID, UserVars.ADC.buf, ADC_MAX_BUF_SIZE);
        if (flag == ERR_TRUE)     // �ж�����Ч����
        {
            // �������̼���ʵ������ֵ
            #if (AI1_EN == 1)   // �ж�AI1ʹ��
            UserVars.ADC.buf[AI1_ID] = ADC_Conv(AI_Range[AI1_ID], UserVars.ADC.buf[AI1_ID]); // ��ȡAI1����ֵ������
            #endif
            #if (AI2_EN == 1)   // �ж�AI2ʹ��
            UserVars.ADC.buf[AI2_ID] = ADC_Conv(AI_Range[AI2_ID], UserVars.ADC.buf[AI2_ID]); // ��ȡAI2����ֵ������
            #endif
            #if (AI3_EN == 1)   // �ж�AI3ʹ��
            UserVars.ADC.buf[AI3_ID] = ADC_Conv(AI_Range[AI3_ID], UserVars.ADC.buf[AI3_ID]); // ��ȡAI3����ֵ������
            #endif
            #if (AI4_EN == 1)   // �ж�AI4ʹ��
            UserVars.ADC.buf[AI4_ID] = ADC_Conv(AI_Range[AI4_ID], UserVars.ADC.buf[AI4_ID]); // ��ȡAI4����ֵ������
            #endif
            #if (AI5_EN == 1)   // �ж�AI5ʹ��
            UserVars.ADC.buf[AI5_ID] = ADC_Conv(AI_Range[AI5_ID], UserVars.ADC.buf[AI5_ID]); // ��ȡAI5����ֵ������
            #endif
            #if (AI6_EN == 1)   // �ж�AI6ʹ��
            UserVars.ADC.buf[AI6_ID] = ADC_Conv(AI_Range[AI6_ID], UserVars.ADC.buf[AI6_ID]); // ��ȡAI6����ֵ������
            #endif
            #if (AI7_EN == 1)   // �ж�AI7ʹ��
            UserVars.ADC.buf[AI7_ID] = ADC_Conv(AI_Range[AI7_ID], UserVars.ADC.buf[AI7_ID]); // ��ȡAI7����ֵ������
            #endif
            #if (AI8_EN == 1)   // �ж�AI8ʹ��
            UserVars.ADC.buf[AI8_ID] = ADC_Conv(AI_Range[AI8_ID], UserVars.ADC.buf[AI8_ID]); // ��ȡAI8����ֵ������
            #endif
            #if (AI9_EN == 1)   // �ж�AI9ʹ��
            UserVars.ADC.buf[AI9_ID] = ADC_Conv(AI_Range[AI9_ID], UserVars.ADC.buf[AI9_ID]); // ��ȡAI9����ֵ������
            #endif
            #if (AI10_EN == 1)  // �ж�AI10ʹ��
            UserVars.ADC.buf[AI10_ID] = ADC_Conv(AI_Range[AI10_ID], UserVars.ADC.buf[AI10_ID]); // ��ȡAI10����ֵ������
            #endif
            
            #if (MODBUS_SLAVE_EN > 0)    // Modbus�豸ģʽʹ��
            for (i=0; i<ADC_MAX_BUF_SIZE; i++)
            {
                ModbusInputReg[i] = UserVars.ADC.buf[i];  // ��ADת��ֵд��Modbus����Ĵ���
            }
            #endif 
            
            #if (DEBUG_APP_EN > 0)
            if ((t%3000)==0) // ���3Sʱ����ʾ���AIֵ
            {            
                AI_Printf();  // ��ӡ���AI����  
            }
            #endif
        }    
        #endif        
/***************************************************************************/
// DAC������Գ���
/***************************************************************************/
        if ((t%3000)==0)     // ÿ���3��ִ��һ��
        {
            if (freq1 == DAC1_FREQ)                       
            {
                freq1 = DAC1_FREQ*2;                       // ����Ϊ2khz
            }
            else
            {
                freq1 = DAC1_FREQ;                         // ����Ϊ1khz
            }
            
            if (freq2 == DAC2_FREQ)                        
            {
                freq2 = DAC2_FREQ*2;                       // ����Ϊ2khz
            }
            else
            {
                freq2 = DAC2_FREQ;                         // ����Ϊ1khz
            }


        //  DAC1 ���
        #if (DAC1_EN>0)
            #if (DAC1_MODE == 0)                           // ģʽ0���ֶ����
            UserVars.AO[0] += (INT32U)UserVars.Para.AO.val*4095/10000;
            if (UserVars.AO[0]>4095)
            {
                UserVars.AO[0] = 0;
            }	
            DAC_Write(DAC1_ID, UserVars.AO[0]);
            #if (DEBUG_APP_EN > 0)
            if (UserVars.Para.ATFlag&AT_AO_FLAG)
            { 
                printf("AT+AO1=%d\r\n", (INT32U)UserVars.AO[0]*10000/4095);
            }
            #endif
            #endif
            
            #if (DAC1_MODE == 1)                           // ģʽ1, �������N�����κ�ֹͣ
            flag = DAC_Ctrl(DAC1_ID, CMD_DAC_STATUS, 0);
            if (flag==0)	                               // �ж����4���������
            {
                 DAC_Ctrl(DAC1_ID, CMD_DAC_FREQ, DAC1_FREQ); // �������Ƶ��
                 DAC_Ctrl(DAC1_ID, CMD_DAC_ENA, 4);	       // ���¿�ʼ���4������
            }
            #endif
            
            #if (DAC1_MODE == 2)                           // ģʽ2, ���������ֹͣ 
            DAC_Ctrl(DAC1_ID, CMD_DAC_FREQ, freq1);		   // �������Ƶ��
            #endif            
        #endif   
        //  DAC2 ���
        #if (DAC2_EN>0)
            #if (DAC2_MODE == 0)                           // ģʽ0���ֶ����
            UserVars.AO[1] += (INT32U)UserVars.Para.AO.val*4095/10000;
            if (UserVars.AO[1]>4095)
            {
                UserVars.AO[1] = 0;
            }
            DAC_Write(DAC2_ID, UserVars.AO[1]);
            #if (DEBUG_APP_EN > 0)
            if (UserVars.Para.ATFlag&AT_AO_FLAG)
            { 
                printf("AT+AO2=%d\r\n", (INT32U)UserVars.AO[1]*10000/4095);
            }
            #endif
            #endif

            #if (DAC2_MODE == 1)                            // ģʽ1, �������N�����κ�ֹͣ
            flag = DAC_Ctrl(DAC2_ID, CMD_DAC_STATUS, 0);
            if (flag==0)	                               // �ж����4���������
            {
                 DAC_Ctrl(DAC2_ID, CMD_DAC_FREQ, DAC2_FREQ);	   // �������Ƶ��
                 DAC_Ctrl(DAC2_ID, CMD_DAC_ENA, 4);	       // ���¿�ʼ���4������
            }
            #endif

            #if (DAC2_MODE == 2)                           // ģʽ2, ���������ֹͣ  
            DAC_Ctrl(DAC2_ID, CMD_DAC_FREQ, freq2);		   // �������Ƶ��
            #endif
        #endif  
        }
	}
}
#endif
/***********************************************************************************/
// �ļ�����
/***********************************************************************************/
