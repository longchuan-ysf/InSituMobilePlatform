/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: TastADC_DAC.c
* Project  : STM32F1XX/4XX系列模块软件
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.00
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: 本文件负责ADC采集和DAC1/2转换输出任务处理;
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
// DAC1/DAC2测试说明
/************************************************************************************/
/*      
(1). 配置说明: 以下3种模式任选一种  
    手动输出模式配置: DAC1_EN/DAC2_EN配置为1, DAC1_MODE/DAC2_MODE配置0(DAC_MODE_MTOUT)模式,其它按默认配置;
    本例程实现功能: 每隔3秒DAC输出值增加409(0.25V或1V), 通过万用表可测量输出端口电压变化;
    
    连续输出1~N个缓存中的数据后停止模式配置: DAC1_EN/DAC2_EN配置为1, DAC1_MODE/DAC2_MODE配置1(DAC_MODE_ATOUT_N)模式,其它按默认配置;
    本例程实现功能: 每隔3秒DAC输出4个固定频率正玄波形, 通过示波器测量输出端口显示; 
    
    持续输出缓存中的数据模式配置: DAC1_EN/DAC2_EN配置为1, DAC1_MODE/DAC2_MODE配置2(DAC_MODE_ATOUT)模式,其它按默认配置;
    本例程实现功能: 每隔3秒DAC输出数据频率在1KHZ和2khz变化, 连续输出正玄波, 通过示波器测量显示; 
    
(2). 在APP_Init.c中调用DAC_APPInit()函数先初始化;   

(3). 在模式1或2中必须初始化缓存, 本例程中调用设置输出波形类型(DACTyte = SINE_WAVE), 再调用DAC_SetWave(DAC1/2_ID, DACTyte, DAC1_TXBUF_SIZE, 50)填充波形数据到缓存;

(4). 在模式0或2中, 调用DAC_Ctrl(DAC1/2_ID, CMD_DAC_ENA, 0)使能输出; 在模式1中, 调用DAC_Ctrl(DAC1/2_ID, CMD_DAC_ENA, 4)使能输出, 4表示输出4个完整波形;

(5). 每隔3秒更新输出:  
     模式0: 调用DAC_Write(DAC1/2_ID, val)更新输出, val每隔3秒增加409, 最大4095(12位AD最大值4095); 
     
     模式1: 调用DAC_Ctrl(DAC1/2_ID, CMD_DAC_STATUS, 0), 判断上一次使能输出的波形(4个)已经完成输出, 
            再调用DAC_Ctrl(DAC1/2_ID, CMD_DAC_FREQ, DAC1/2_FREQ), 设置新的输出频率DAC1/2_FREQ,
            最后调用DAC_Ctrl(DAC1/2_ID, CMD_DAC_ENA, 4)重新启动输出4个波形
     
     模式2: 设置新的输出频率变量freq1/2, 本例程在1KHZ和2KHZ变化; 再调用DAC_Ctrl(DAC1_ID, CMD_DAC_FREQ, freq1/2)更改输出频率
*/
/************************************************************************************/
// ADC测试说明
/************************************************************************************/
/*
(1). IO配置: 在IO端口配置文件中, 根据板子硬件端口模拟量输入AI1-AI8与模块模拟量AIN0-AIN15对应关系
             设置端口定义, 例如:  
             #define  AI1        AIN0    // 设置AI1<->AIN0(PA0)
             #define  AI2        AIN3    // 设置AI2<->AIN3(PA3)

(2). 配置说明: 
    ADC_EN配置为1; ADC_OUT_TYPE选择0(ADC_ISROUT,利用中断读取数据)或者1(ADC_READOUT, 利用函数AD_Read读取数据)模式; 
    AI1_EN~AI10_EN: 设置板子AD输入通道端口使能, 一般硬件设计几路就使能几路, 必须从AI1_EN开始, 必须连续, 就是例如外部有5路AD输入，必须使能AI1_EN~AI5_EN;
    ADC_CHNUM: 是根据使能AIx_EN情况自动计算外部AD输入通道数量，不用修改; 
    ADC_AVGNUM: 是设置平均滤波数量, 一般设置为4或8即可;
    ADC_FREQ: 设置AD转换输出数据的频率, 设置10就是每秒钟输出10组数据, 客户根据实际需要设置不可太高, 一般1-100;
    ADC_SAMPLE_TIME: 采样间隔, 不用修改, 默认设置即可;
    ADC_TIM5： 设置TIM5及子定时器作为AD采样定时, 默认ADC_TIM5CH1_FLAG就可以了, 不用修改; 
    AI1_RANGE~AI10_RANGE: 设置板子端口输入量程范围;
    
(3). 在APP_Init.c中调用ADC_APPInit()函数先初始化;       

(3). 调用ADC_Ctrl(ADC1_ID, CMD_ADC_ENA, 0) 启动AD转换;	 
    
(4). 在输出方式是0(ADC_ISROUT,利用中断读取数据), 调用pADC = OSMboxPend(OSMboxADC, 10, &err) 读取AD转换数据,并做相应处理; 
     在输出方式是1(ADC_READOUT, 利用函数AD_Read读取数据), 调用AD_Read读取AD转换数据,并做相应处理;  

(5). 通过串口调试输出观察AD采样结果;
*/
/************************************************************************************/

/************************************************************************************/

// 引用外部头文件
#include "config.h"
#if (TASK_ADCDAC_EN == 1)
#include "Vars.h"
#include "UserVars.h"
#include "OSVars.h"
#include "math.h"
#include "STM32Fxxx.h"

/************************************************************************************/

/************************************************************************************/
// 常量及全局变量定义
/************************************************************************************/
// 电压调整公式： K = 实测电压基准/2.5,  V = K*V测量 + 量程*(K-1)
const AI_Range[10] = {AI1_RANGE, AI2_RANGE, AI3_RANGE, AI4_RANGE, AI5_RANGE, AI6_RANGE, AI7_RANGE, AI8_RANGE, AI9_RANGE, AI10_RANGE};
/***************************************************************************/
// DAC1/DAC2参数设置
/***************************************************************************/
#define SINE_WAVE    0   // 正弦波
#define TRI_WAVE     1   // 三角波
#define SQUARE_WAVE  2   // 方波

#define SQUARE_RATE  50  // 方波占空比50%
#define PI_  3.14165926

/***************************************************************************/
/***********************************************************************************
* Function: ADC_Conv;
*
* Description: 根据各通道输入量量程算出实际输入值;
* 
* Input:  Cmd, 量程命令; val,AD采样原始值
*
* Output: none;
*          		
* Return: 返回计算所得AI实际输入值;
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
            rst *= 1.00835;  // 因为输入电路是250欧与30K并联，实际采样电阻是247.93欧
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
* Description: 填充DAC输出波形数据;
* 
* Input:  id, ADC索引(DAC1_ID~DAC2_ID);
*         type, 波形类型: SINE_WAVE,TRI_WAVE,SQUARE_WAVE
*         size, 填充数据的长度
*         rate, 占空比, 当波形类型是SQUARE_WAVE时,这个参数设置方波的占空比, 1-99%可调; 其它波形类型无效.
*
* Output: none;
*          		
* Return: ERR_TRUE: 正确; ERR_FALSE: 失败;
*
* Note:   none;
************************************************************************************/
// rate 变量是方波占空比0~100
void DAC_SetWave(INT8U id, INT8U type, INT16U size, INT16U rate)
{
	INT16U i, val, x;

	if (type == TRI_WAVE)	    // 三角波
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
	else if (type == SINE_WAVE)	// 正弦波
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

	else if (type == SQUARE_WAVE)  // 方波
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
        #if (AI1_EN == 1)   // 判断AI1使能
        printf(",%d", UserVars.ADC.buf[AI1_ID]);
        #endif
        #if (AI2_EN == 1)   // 判断AI2使能
        printf(",%d", UserVars.ADC.buf[AI2_ID]);
        #endif
        #if (AI3_EN == 1)   // 判断AI3使能
        printf(",%d", UserVars.ADC.buf[AI3_ID]);
        #endif
        #if (AI4_EN == 1)   // 判断AI4使能
        printf(",%d", UserVars.ADC.buf[AI4_ID]);
        #endif
        #if (AI5_EN == 1)   // 判断AI5使能
        printf(",%d", UserVars.ADC.buf[AI5_ID]);
        #endif
        #if (AI6_EN == 1)   // 判断AI6使能
        printf(",%d", UserVars.ADC.buf[AI6_ID]);
        #endif
        #if (AI7_EN == 1)   // 判断AI7使能
        printf(",%d", UserVars.ADC.buf[AI7_ID]);
        #endif
        #if (AI8_EN == 1)   // 判断AI8使能
        printf(",%d", UserVars.ADC.buf[AI8_ID]);
        #endif
        #if (AI9_EN == 1)   // 判断AI9使能
        printf(",%d", UserVars.ADC.buf[AI9_ID]);
        #endif
        #if (AI10_EN == 1)  // 判断AI10使能
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
// DAC1/DAC2使能开始工作
/**************************************************************************/
    #if (DAC1_EN==1)     // DAC1使能
        #if	(DAC1_MODE > 0)
        // 设置输出波形类型
        DACTyte = SINE_WAVE;                  // 设置输出正玄波
        //DACTyte = TRI_WAVE;                 // 设置输出三角波
        //DACTyte = SQUARE_WAVE;              // 设置输出方波
        DAC_SetWave(DAC1_ID, DACTyte, DAC1_TXBUF_SIZE, 50);  // DAC1填充波形数据到缓存
        #endif
    
        #if	(DAC1_MODE == 1) // 是模式1
        DAC_Ctrl(DAC1_ID, CMD_DAC_ENA, 4);  // DAC1使能连续输出4个正弦波后停止
        #else
        DAC_Ctrl(DAC1_ID, CMD_DAC_ENA, 0);  // DAC1使能
        #endif
    #endif

    #if (DAC2_EN==1)        // DAC1使能
        #if (DAC2_MODE > 0)                   // 连续输出
        // 设置输出波形类型
        DACTyte = SINE_WAVE;                  // 设置输出正玄波
        //DACTyte = TRI_WAVE;                 // 设置输出三角波
        //DACTyte = SQUARE_WAVE;              // 设置输出方波
        DAC_SetWave(DAC2_ID, DACTyte, DAC2_TXBUF_SIZE, 25);  // DAC2填充波形数据到缓存
        #endif    
        #if	(DAC2_MODE == 1)    // 是模式1
        DAC_Ctrl(DAC2_ID, CMD_DAC_ENA, 4);  // DAC2使能连续输出4个三角波后停止
        #else
        DAC_Ctrl(DAC2_ID, CMD_DAC_ENA, 0);  // DAC2使能
        #endif
	#endif														  
    freq1 = DAC1_FREQ;
    freq2 = DAC2_FREQ;
/**************************************************************************/
// ADC使能开始工作
/**************************************************************************/
	// 启动AD转换定时器
    #if ((MODULE_CLASS == STM32F103XX)||(MODULE_CLASS == STM32F107XX))
    #if ((TIM5_EN == 1)&&(TIM5_MODE == TIM_WKMODE_INT))
        TIMCtrl.Chx = TIM5CH_EN;
        TIMCtrl.t = TIM5_T;            // 设置主定时器定时时间
        TIMCtrl.t1 = TIM5_T1;          // 设置子定时器1定时时间
        TIMCtrl.t2 = TIM5_T2;          // 设置子定时器2定时时间
        TIMCtrl.t3 = TIM5_T3;          // 设置子定时器3定时时间
        TIMCtrl.t4 = TIM5_T4;          // 设置子定时器4定时时间
        
        Timer_Ctrl(TIM5_ID, CMD_TIM_ENA, (TIM_CTRL *)&TIMCtrl.Chx);
    #endif
    #endif
    
    #if (MODULE_CLASS == STM32F407XX)
    #if ((TIM14_EN == 1)&&(TIM14_MODE == TIM_WKMODE_INT))
        TIMCtrl.Chx = TIM14CH_EN;
        TIMCtrl.t = TIM14_T;           // 设置主定时器定时时间
        TIMCtrl.t1 = TIM14_T1;         // 设置子定时器1定时时间
        
        Timer_Ctrl(TIM14_ID, CMD_TIM_ENA, (TIM_CTRL *)&TIMCtrl.Chx);
    #endif
    #endif
    
    // 使能AD转换
    ADC_Ctrl(ADC1_ID, CMD_ADC_ENA, 0);	   // 启动AD转换;	
    
	t = 0;
	while(1)
    {
		UserVars.TaskRunStatus |= TASK_ADCDAC_FLAG;  // 设置本任务运行状态标志
        
        #if (ADC_OUT_TYPE == ADC_ISROUT)             // 判断是中断输出AD采样值
		pADC = OSMboxPend(OSMboxADC, 100, &err);      // 读取AD转换完成
		if (err==OS_ERR_NONE)
		{        
            // 根据量程计算实际输入值
            #if (AI1_EN == 1)   // 判断AI1使能
            UserVars.ADC.buf[AI1_ID] = ADC_Conv(AI_Range[AI1_ID], pADC->pBuf[AI1_ID]); // 读取AI1采样值并计算
            #endif
            #if (AI2_EN == 1)   // 判断AI2使能
            UserVars.ADC.buf[AI2_ID] = ADC_Conv(AI_Range[AI2_ID], pADC->pBuf[AI2_ID]); // 读取AI2采样值并计算
            #endif
            #if (AI3_EN == 1)   // 判断AI3使能
            UserVars.ADC.buf[AI3_ID] = ADC_Conv(AI_Range[AI3_ID], pADC->pBuf[AI3_ID]); // 读取AI3采样值并计算
            #endif
            #if (AI4_EN == 1)   // 判断AI4使能
            UserVars.ADC.buf[AI4_ID] = ADC_Conv(AI_Range[AI4_ID], pADC->pBuf[AI4_ID]); // 读取AI4采样值并计算
            #endif
            #if (AI5_EN == 1)   // 判断AI5使能
            UserVars.ADC.buf[AI5_ID] = ADC_Conv(AI_Range[AI5_ID], pADC->pBuf[AI5_ID]); // 读取AI5采样值并计算
            #endif
            #if (AI6_EN == 1)   // 判断AI6使能
            UserVars.ADC.buf[AI6_ID] = ADC_Conv(AI_Range[AI6_ID], pADC->pBuf[AI6_ID]); // 读取AI6采样值并计算
            #endif
            #if (AI7_EN == 1)   // 判断AI7使能
            UserVars.ADC.buf[AI7_ID] = ADC_Conv(AI_Range[AI7_ID], pADC->pBuf[AI7_ID]); // 读取AI7采样值并计算
            #endif
            #if (AI8_EN == 1)   // 判断AI8使能
            UserVars.ADC.buf[AI8_ID] = ADC_Conv(AI_Range[AI8_ID], pADC->pBuf[AI8_ID]); // 读取AI8采样值并计算
            #endif
            #if (AI9_EN == 1)   // 判断AI9使能
            UserVars.ADC.buf[AI9_ID] = ADC_Conv(AI_Range[AI9_ID], pADC->pBuf[AI9_ID]); // 读取AI9采样值并计算
            #endif
            #if (AI10_EN == 1)  // 判断AI10使能
            UserVars.ADC.buf[AI10_ID] = ADC_Conv(AI_Range[AI10_ID], pADC->pBuf[AI10_ID]); // 读取AI10采样值并计算
            #endif       

            #if (MODBUS_SLAVE_EN > 0)    // Modbus设备模式使能
            for (i=0; i<ADC_MAX_BUF_SIZE; i++)
            {
                ModbusInputReg[i] = UserVars.ADC.buf[i];  // 将AD转换值写入Modbus输入寄存器
            }
            #endif 
            
            #if (DEBUG_APP_EN > 0)
            if ((t%3000)==0) // 间隔3S时间显示输出AI值
            {            
                AI_Printf();  // 打印输出AI数据  
            }
            #endif
            t += 100;
        } 
        //else
        //{
        //    t += 1000;
        //}            
        
        #else    // 利用ADC_Read()函数读取AD转换值
        Delay_ms(100);   // 间隔100ms读取AD值   
        t += 100;         
        // 读取AD数据 
        flag = ADC_Read(ADC1_ID, UserVars.ADC.buf, ADC_MAX_BUF_SIZE);
        if (flag == ERR_TRUE)     // 判断是有效数据
        {
            // 根据量程计算实际输入值
            #if (AI1_EN == 1)   // 判断AI1使能
            UserVars.ADC.buf[AI1_ID] = ADC_Conv(AI_Range[AI1_ID], UserVars.ADC.buf[AI1_ID]); // 读取AI1采样值并计算
            #endif
            #if (AI2_EN == 1)   // 判断AI2使能
            UserVars.ADC.buf[AI2_ID] = ADC_Conv(AI_Range[AI2_ID], UserVars.ADC.buf[AI2_ID]); // 读取AI2采样值并计算
            #endif
            #if (AI3_EN == 1)   // 判断AI3使能
            UserVars.ADC.buf[AI3_ID] = ADC_Conv(AI_Range[AI3_ID], UserVars.ADC.buf[AI3_ID]); // 读取AI3采样值并计算
            #endif
            #if (AI4_EN == 1)   // 判断AI4使能
            UserVars.ADC.buf[AI4_ID] = ADC_Conv(AI_Range[AI4_ID], UserVars.ADC.buf[AI4_ID]); // 读取AI4采样值并计算
            #endif
            #if (AI5_EN == 1)   // 判断AI5使能
            UserVars.ADC.buf[AI5_ID] = ADC_Conv(AI_Range[AI5_ID], UserVars.ADC.buf[AI5_ID]); // 读取AI5采样值并计算
            #endif
            #if (AI6_EN == 1)   // 判断AI6使能
            UserVars.ADC.buf[AI6_ID] = ADC_Conv(AI_Range[AI6_ID], UserVars.ADC.buf[AI6_ID]); // 读取AI6采样值并计算
            #endif
            #if (AI7_EN == 1)   // 判断AI7使能
            UserVars.ADC.buf[AI7_ID] = ADC_Conv(AI_Range[AI7_ID], UserVars.ADC.buf[AI7_ID]); // 读取AI7采样值并计算
            #endif
            #if (AI8_EN == 1)   // 判断AI8使能
            UserVars.ADC.buf[AI8_ID] = ADC_Conv(AI_Range[AI8_ID], UserVars.ADC.buf[AI8_ID]); // 读取AI8采样值并计算
            #endif
            #if (AI9_EN == 1)   // 判断AI9使能
            UserVars.ADC.buf[AI9_ID] = ADC_Conv(AI_Range[AI9_ID], UserVars.ADC.buf[AI9_ID]); // 读取AI9采样值并计算
            #endif
            #if (AI10_EN == 1)  // 判断AI10使能
            UserVars.ADC.buf[AI10_ID] = ADC_Conv(AI_Range[AI10_ID], UserVars.ADC.buf[AI10_ID]); // 读取AI10采样值并计算
            #endif
            
            #if (MODBUS_SLAVE_EN > 0)    // Modbus设备模式使能
            for (i=0; i<ADC_MAX_BUF_SIZE; i++)
            {
                ModbusInputReg[i] = UserVars.ADC.buf[i];  // 将AD转换值写入Modbus输入寄存器
            }
            #endif 
            
            #if (DEBUG_APP_EN > 0)
            if ((t%3000)==0) // 间隔3S时间显示输出AI值
            {            
                AI_Printf();  // 打印输出AI数据  
            }
            #endif
        }    
        #endif        
/***************************************************************************/
// DAC输出测试程序
/***************************************************************************/
        if ((t%3000)==0)     // 每间隔3秒执行一次
        {
            if (freq1 == DAC1_FREQ)                       
            {
                freq1 = DAC1_FREQ*2;                       // 设置为2khz
            }
            else
            {
                freq1 = DAC1_FREQ;                         // 设置为1khz
            }
            
            if (freq2 == DAC2_FREQ)                        
            {
                freq2 = DAC2_FREQ*2;                       // 设置为2khz
            }
            else
            {
                freq2 = DAC2_FREQ;                         // 设置为1khz
            }


        //  DAC1 输出
        #if (DAC1_EN>0)
            #if (DAC1_MODE == 0)                           // 模式0，手动输出
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
            
            #if (DAC1_MODE == 1)                           // 模式1, 连续输出N个波形后停止
            flag = DAC_Ctrl(DAC1_ID, CMD_DAC_STATUS, 0);
            if (flag==0)	                               // 判断输出4个波形完成
            {
                 DAC_Ctrl(DAC1_ID, CMD_DAC_FREQ, DAC1_FREQ); // 更改输出频率
                 DAC_Ctrl(DAC1_ID, CMD_DAC_ENA, 4);	       // 重新开始输出4个波形
            }
            #endif
            
            #if (DAC1_MODE == 2)                           // 模式2, 持续输出不停止 
            DAC_Ctrl(DAC1_ID, CMD_DAC_FREQ, freq1);		   // 更改输出频率
            #endif            
        #endif   
        //  DAC2 输出
        #if (DAC2_EN>0)
            #if (DAC2_MODE == 0)                           // 模式0，手动输出
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

            #if (DAC2_MODE == 1)                            // 模式1, 连续输出N个波形后停止
            flag = DAC_Ctrl(DAC2_ID, CMD_DAC_STATUS, 0);
            if (flag==0)	                               // 判断输出4个波形完成
            {
                 DAC_Ctrl(DAC2_ID, CMD_DAC_FREQ, DAC2_FREQ);	   // 更改输出频率
                 DAC_Ctrl(DAC2_ID, CMD_DAC_ENA, 4);	       // 重新开始输出4个波形
            }
            #endif

            #if (DAC2_MODE == 2)                           // 模式2, 持续输出不停止  
            DAC_Ctrl(DAC2_ID, CMD_DAC_FREQ, freq2);		   // 更改输出频率
            #endif
        #endif  
        }
	}
}
#endif
/***********************************************************************************/
// 文件结束
/***********************************************************************************/
