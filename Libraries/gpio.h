/************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: gpio.h
* Project  : STM32F1XX/4XXϵ��ģ��������
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: ���ļ���GPIO�˿�Ӳ����������ͷ�ļ�;
*
* Others: none;
*
* Function List: 
*          1. INT32S IO_Init(INT32U IOx, INT8U Mode, INT8U Speed);
*          2. INT32U IO_Read(INT32U IOx);
*          3. void IO_Write(INT32U IOx, INT16U val);
*          4. INT32S IO_Ctrl(INT32U IOx, INT8U Cmd, INT32U Para);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/
#ifndef __GPIO_H 
#define __GPIO_H 
/************************************************************************************/
// �����ⲿͷ�ļ�
/************************************************************************************/
#include "const.h" 
/************************************************************************************/
//  IO���������������� 
/************************************************************************************/
// ����ģʽ
#define IO_IN_FLOATING   0x00	// ��������ģʽ(��λ���״̬)
#define IO_IN_IPU        0x40	// �ڲ���������ģʽ 
#define IO_IN_IPD        0x80	// �ڲ���������ģʽ

// ͨ�����ģʽ
#define IO_OUT_PP        0x01	// ͨ���������ģʽ
#define IO_OUT_OD        0x21	// ͨ�ÿ�©���ģʽ	

// ģ������ģʽ
#define IO_AIN           0x03	// ģ������ģʽ

// STM32F4_M4оƬ����ģʽ����(һ�㲻��)
#define IO_OUT_PP_IPU    0x41	// ͨ���������ģʽ, �ڲ�����
#define IO_OUT_PP_IPD    0x81	// ͨ���������ģʽ, �ڲ�����

#define IO_OUT_OD_IPU    0x61	// ͨ�ÿ�©���ģʽ, �ڲ�����
#define IO_OUT_OD_IPD    0xA1	// ͨ�ÿ�©���ģʽ, �ڲ�����


// ������STM32F1XX_M3оƬGPIO�ٶȶ���
#define IO_INPUT         0x00   // ����ģʽ(��λ���״̬), �������ٶ�
#define IO_SPEED_10MHz   0x01   // ���ģʽ������ٶ�10MHz
#define IO_SPEED_2MHz    0x02   // ���ģʽ������ٶ�2MHz
#define IO_SPEED_50MHz   0x03   // ���ģʽ������ٶ�50MHz

// ������STM32F4XX_M4оƬGPIO�ٶȶ���
#define IO_SPEED_2MHz    0x02   // ���ģʽ������ٶ�2MHz
#define IO_SPEED_50MHz   0x03   // ���ģʽ������ٶ�50MHz
#define IO_SPEED_25MHz   0x04   // ���ģʽ������ٶ�25MHz
#define IO_SPEED_100MHz  0x05   // ���ģʽ������ٶ�100MHz(30pf)


#define IO_NONE 0xff		    // ��Чֵ

// ��1�飺PA0-PA15
#define PA0      0	
#define PA1      1	
#define PA2      2	
#define PA3      3	
#define PA4      4	
#define PA5      5	
#define PA6      6	
#define PA7      7	
#define PA8      8	
#define PA9      9	
#define PA10     10	
#define PA11     11	
#define PA12     12	
#define PA13     13	
#define PA14     14	
#define PA15     15

// ��2�飺PB0-PB15
#define PB0      16	
#define PB1      17	
#define PB2      18
#define PB3      19	
#define PB4      20	
#define PB5      21	
#define PB6      22	
#define PB7      23	
#define PB8      24	
#define PB9      25	
#define PB10     26	
#define PB11     27	
#define PB12     28	
#define PB13     29	
#define PB14     30	
#define PB15     31

// ��3��: PC0-PC15
#define PC0      32	
#define PC1      33	
#define PC2      34
#define PC3      35	
#define PC4      36	
#define PC5      37	
#define PC6      38	
#define PC7      39	
#define PC8      40	
#define PC9      41	
#define PC10     42	
#define PC11     43	
#define PC12     44	
#define PC13     45	
#define PC14     46	
#define PC15     47

// ��4��: PD0-PD15
#define PD0      48	
#define PD1      49	
#define PD2      50
#define PD3      51	
#define PD4      52	
#define PD5      53	
#define PD6      54	
#define PD7      55	
#define PD8      56	
#define PD9      57	
#define PD10     58	
#define PD11     59	
#define PD12     60	
#define PD13     61	
#define PD14     62	
#define PD15     63

// ��5��: PE0-PE15
#define PE0      64	
#define PE1      65	
#define PE2      66
#define PE3      67	
#define PE4      68	
#define PE5      69	
#define PE6      70	
#define PE7      71	
#define PE8      72	
#define PE9      73	
#define PE10     74	
#define PE11     75	
#define PE12     76	
#define PE13     77	
#define PE14     78	
#define PE15     79

// ��6��: PF0-PF15
#define PF0      80	
#define PF1      81	
#define PF2      82
#define PF3      83	
#define PF4      84	
#define PF5      85	
#define PF6      86	
#define PF7      87	
#define PF8      88	
#define PF9      89	
#define PF10     90	
#define PF11     91	
#define PF12     92	
#define PF13     93	
#define PF14     94	
#define PF15     95

// ��7��: PG0-PG15
#define PG0      96	
#define PG1      97	
#define PG2      98
#define PG3      99	
#define PG4      100	
#define PG5      101
#define PG6      102	
#define PG7      103	
#define PG8      104	
#define PG9      105	
#define PG10     106	
#define PG11     107	
#define PG12     108	
#define PG13     109	
#define PG14     110	
#define PG15     111

// ��8��: PH0-PH15
#define PH0      112	
#define PH1      113	
#define PH2      114
#define PH3      115	
#define PH4      116	
#define PH5      117
#define PH6      118	
#define PH7      119	
#define PH8      120	
#define PH9      121	
#define PH10     122	
#define PH11     123	
#define PH12     124	
#define PH13     125	
#define PH14     126	
#define PH15     127

// ��9��: PI0-PI15
#define PI0      128	
#define PI1      129	
#define PI2      130
#define PI3      131	
#define PI4      132	
#define PI5      133
#define PI6      134	
#define PI7      135	
#define PI8      136	
#define PI9      137	
#define PI10     138	
#define PI11     139	
#define PI12     140	
#define PI13     141	
#define PI14     142	
#define PI15     143

// �˿��鶨��
#define PA       0x10000  // ��1��, PA0-PA15
#define PB       0x20000  // ��2��, PB0-PB15
#define PC       0x30000  // ��3��, PC0-PC15
#define PD       0x40000  // ��4��, PD0-PD15
#define PE       0x50000  // ��5��, PE0-PE15
#define PF       0x60000  // ��6��, PF0-PF15
#define PG       0x70000  // ��7��, PG0-PG15
#define PH       0x80000  // ��8��, PH0-PH15
#define PI       0x90000  // ��9��, PI0-PI15

// �˿����IO����
#define GPIO_PIN_0      ((INT16U)0x0001)  // Pin 0 selected, ���������˿�IOx��bit0λ
#define GPIO_PIN_1      ((INT16U)0x0002)  // Pin 1 selected, ���������˿�IOx��bit1λ    
#define GPIO_PIN_2      ((INT16U)0x0004)  // Pin 2 selected, ���������˿�IOx��bit2λ    
#define GPIO_PIN_3      ((INT16U)0x0008)  // Pin 3 selected, ���������˿�IOx��bit3λ   
#define GPIO_PIN_4      ((INT16U)0x0010)  // Pin 4 selected, ���������˿�IOx��bit4λ  
#define GPIO_PIN_5      ((INT16U)0x0020)  // Pin 5 selected, ���������˿�IOx��bit5λ    
#define GPIO_PIN_6      ((INT16U)0x0040)  // Pin 6 selected, ���������˿�IOx��bit6λ   
#define GPIO_PIN_7      ((INT16U)0x0080)  // Pin 7 selected, ���������˿�IOx��bit7λ  
#define GPIO_PIN_8      ((INT16U)0x0100)  // Pin 8 selected, ���������˿�IOx��bit8λ    
#define GPIO_PIN_9      ((INT16U)0x0200)  // Pin 9 selected, ���������˿�IOx��bit9λ    
#define GPIO_PIN_10     ((INT16U)0x0400)  // Pin 10 selected, ���������˿�IOx��bit10λ  
#define GPIO_PIN_11     ((INT16U)0x0800)  // Pin 11 selected, ���������˿�IOx��bit11λ   
#define GPIO_PIN_12     ((INT16U)0x1000)  // Pin 12 selected, ���������˿�IOx��bit12λ  
#define GPIO_PIN_13     ((INT16U)0x2000)  // Pin 13 selected, ���������˿�IOx��bit13λ   
#define GPIO_PIN_14     ((INT16U)0x4000)  // Pin 14 selected, ���������˿�IOx��bit14λ  
#define GPIO_PIN_15     ((INT16U)0x8000)  // Pin 15 selected, ���������˿�IOx��bit15λ   
#define GPIO_PIN_All    ((INT16U)0xFFFF)  // All pins selected 
#define GPIO_PIN_MASK   ((INT32U)0x0000FFFF) // PIN mask for assert test 

// IO_Ctrl() ���������
#define CMD_IO_NEG     0    // IOȡ��
#define CMD_IO_ON_T    1	// IO��1����ʱһ��ʱ������0
#define CMD_IO_OFF_T   2	// IO��0����ʱһ��ʱ������1
#define CMD_IO_RST     4    // ��λIO�Ĵ���Ϊ��ʼ״̬
#define CMD_IO_CLOSE   5    // �ر�IOʱ��,Ҳ���ǹر�DAC����,����ʡ�� 

/*************************************************************************************/
//
// 							GPIO�˿�Ӳ��������������
//
/*************************************************************************************/

/******************************************************************************************************************
* Function: IO_Init;
*
* Description: IO��ʼ������
*              
* Input:  IOx, ����IO�˿�, �������˿ڳ�ʼ��: PA0~PA15,PB0~PB15,PC0~PC15,PD0~PD15,PE0~PE15,PF0~PF15,PG0~PG15,PH0~PH15,PI0~PI15;
*              ����˿�, ֻ��ʼ��bit0~bit15Ϊ1�Ķ˿�: (PA/PB/PC/PD/PE/PF/PG/PH/PI)+(GPIO_PIN_0|GPIO_PIN_1|...|GPIO_PIN_15) 
*
*         Mode, IOģʽ�������£�
*               ͨ�����ģʽ: IO_OUT_PP, ͨ���������ģʽ; 
*                             IO_OUT_OD, ͨ�ÿ�©���ģʽ;                    
*               ����ģʽ:	  IO_IN_FLOATING, ��������ģʽ(��λ���״̬)
*				        	  IO_IN_IPD, �ڲ���������ģʽ;
*                             IO_IN_IPU, �ڲ���������ģʽ
*               ģ������ģʽ: IO_AIN, ģ������ģʽ;
*         
*         Speed, IO����ٶȣ�   
*                ���IOģʽ������ģʽ, ��ò�������Ϊ��0(IO_INPUT), �������ٶ�
*  				 ���IOģʽ�����ģʽ, ��ò�������Ϊ�ٶ�ѡ��
*		         IO_SPEED_10MHz, ����ٶ�10MHz
*                IO_SPEED_2MHz, ����ٶ�2MHz
*                IO_SPEED_50MHz, ����ٶ�50MHz
*                IO_SPEED_25MHz, ����ٶ�25MHz, ֻ����STM32F4xx
*                IO_SPEED_100MHz, ����ٶ�100MHz, ֻ����STM32F4xx
*
* Output: none;
*
* Return: ERR_TRUE,�����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   none;
*******************************************************************************************************************/
INT32S IO_Init(INT32U IOx, INT8U Mode, INT8U Speed);

/******************************************************************************************************************
* Function: IO_Read;
*
* Description: ��ȡIO����ֵ;
* 
* Input:  IOx, ����IO�˿�: PA0~PA15,PB0~PB15,PC0~PC15,PD0~PD15,PE0~PE15,PF0~PF15,PG0~PG15,PH0~PH15,PI0~PI15;
*              ����˿�, ֻ��ȡbit0~bit15Ϊ1�Ķ˿�: (PA/PB/PC/PD/PE/PF/PG/PH/PI)+(GPIO_PIN_0|GPIO_PIN_1|...|GPIO_PIN_15)
*
* Output: none;
*          		
* Return: IOx�ǵ���IO�˿ڣ�����ֵ��1,�ߵ�ƽ, ��0,�͵�ƽ; 
*         IOx�ǳ���˿ڣ�  ����ֵbit0~bit15�ֱ����Px0~Px15(xΪA,B,C,D,E,F,G,H,I), ��bit7Ϊ��, ��1��Px7����ߵ�ƽ, ��0��Px7����͵�ƽ; 
*
* Note:   �������ֵ��0x80000000, ���ʾ����
*******************************************************************************************************************/
INT32U IO_Read(INT32U IOx);

/******************************************************************************************************************
* Function: IO_Write;
*
* Description: д��IO���ֵ;
* 
* Input:  IOx, ����IO�˿�: PA0~PA15,PB0~PB15,PC0~PC15,PD0~PD15,PE0~PE15,PF0~PF15,PG0~PG15,PH0~PH15,PI0~PI15;
*              ����˿�, ֻ���bit0~bit15Ϊ1�Ķ˿�: (PA/PB/PC/PD/PE/PF/PG/PH/PI)+(GPIO_PIN_0|GPIO_PIN_1|...|GPIO_PIN_15)
*       
*         IOx�ǵ���IO�˿ڣ�val, 1����ߵ�ƽ, 0,����͵�ƽ; 
*         IOx�ǳ���˿ڣ�  val��bit0~bit15�ֱ����Px0~Px15(xΪA,B,C,D,E,F,G,H,I), ��bit7Ϊ��, ��1��Px7����ߵ�ƽ, ��0��Px7����͵�ƽ;
*         
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
*******************************************************************************************************************/
void IO_Write(INT32U IOx, INT16U val);

/******************************************************************************************************************
* Function: IO_Ctrl;
*
* Description: IO�������;
* 
* Input:  IOx, ����IO�˿�: PA0~PA15,PB0~PB15,PC0~PC15,PD0~PD15,PE0~PE15,PF0~PF15,PG0~PG15,PH0~PH15,PI0~PI15;
*              ����˿�, ֻ����bit0~bit15Ϊ1�Ķ˿�: (PA/PB/PC/PD/PE/PF/PG/PH/PI)+(GPIO_PIN_0|GPIO_PIN_1|...|GPIO_PIN_15)
*		  Cmd, IO��������: 
*              CMD_IO_NEG,   IOȡ��; ����ParaΪ0
*              CMD_IO_ON_T,  IO��1����ʱһ��ʱ������0; ����ParaΪ��ʱʱ��,��λms;
*              CMD_IO_OFF_T, IO��0����ʱһ��ʱ������1; ����ParaΪ��ʱʱ��,��λms;
*              CMD_IO_RST,   ��λIO�Ĵ���Ϊ��ʼ״̬; ����ParaΪ0; ��ʱIOxӦ��PA/PB/PC/PD/PE/PF/PG/PH/PI
*              CMD_IO_CLOSE, �ر�IOʱ��,Ҳ���ǹر�DAC����,����ʡ��; ����ParaΪ0; ��ʱIOxӦ��PA/PB/PC/PD/PE/PF/PG/PH/PI
*         Para, �������;
*
* Output: none;
*          		
* Return: ERR_TRUE,�����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   none;
*******************************************************************************************************************/
INT32S IO_Ctrl(INT32U IOx, INT8U Cmd, INT32U Para);


#endif
/******************************************************************************************************************/
// �ļ�����
/******************************************************************************************************************/


