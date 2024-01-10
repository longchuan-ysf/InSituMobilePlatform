/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: gpio.h
* Project  : STM32F1XX/4XX系列模块驱动库
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: 本文件是GPIO端口硬件驱动程序头文件;
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
// 引用外部头文件
/************************************************************************************/
#include "const.h" 
/************************************************************************************/
//  IO操作函数常量定义 
/************************************************************************************/
// 输入模式
#define IO_IN_FLOATING   0x00	// 浮空输入模式(复位后的状态)
#define IO_IN_IPU        0x40	// 内部上拉输入模式 
#define IO_IN_IPD        0x80	// 内部下拉输入模式

// 通用输出模式
#define IO_OUT_PP        0x01	// 通用推挽输出模式
#define IO_OUT_OD        0x21	// 通用开漏输出模式	

// 模拟输入模式
#define IO_AIN           0x03	// 模拟输入模式

// STM32F4_M4芯片新增模式定义(一般不用)
#define IO_OUT_PP_IPU    0x41	// 通用推挽输出模式, 内部上拉
#define IO_OUT_PP_IPD    0x81	// 通用推挽输出模式, 内部下拉

#define IO_OUT_OD_IPU    0x61	// 通用开漏输出模式, 内部上拉
#define IO_OUT_OD_IPD    0xA1	// 通用开漏输出模式, 内部下拉


// 以下是STM32F1XX_M3芯片GPIO速度定义
#define IO_INPUT         0x00   // 输入模式(复位后的状态), 不区分速度
#define IO_SPEED_10MHz   0x01   // 输出模式，最大速度10MHz
#define IO_SPEED_2MHz    0x02   // 输出模式，最大速度2MHz
#define IO_SPEED_50MHz   0x03   // 输出模式，最大速度50MHz

// 以下是STM32F4XX_M4芯片GPIO速度定义
#define IO_SPEED_2MHz    0x02   // 输出模式，最大速度2MHz
#define IO_SPEED_50MHz   0x03   // 输出模式，最大速度50MHz
#define IO_SPEED_25MHz   0x04   // 输出模式，最大速度25MHz
#define IO_SPEED_100MHz  0x05   // 输出模式，最大速度100MHz(30pf)


#define IO_NONE 0xff		    // 无效值

// 第1组：PA0-PA15
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

// 第2组：PB0-PB15
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

// 第3组: PC0-PC15
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

// 第4组: PD0-PD15
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

// 第5组: PE0-PE15
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

// 第6组: PF0-PF15
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

// 第7组: PG0-PG15
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

// 第8组: PH0-PH15
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

// 第9组: PI0-PI15
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

// 端口组定义
#define PA       0x10000  // 第1组, PA0-PA15
#define PB       0x20000  // 第2组, PB0-PB15
#define PC       0x30000  // 第3组, PC0-PC15
#define PD       0x40000  // 第4组, PD0-PD15
#define PE       0x50000  // 第5组, PE0-PE15
#define PF       0x60000  // 第6组, PF0-PF15
#define PG       0x70000  // 第7组, PG0-PG15
#define PH       0x80000  // 第8组, PH0-PH15
#define PI       0x90000  // 第9组, PI0-PI15

// 端口组各IO定义
#define GPIO_PIN_0      ((INT16U)0x0001)  // Pin 0 selected, 函数参数端口IOx的bit0位
#define GPIO_PIN_1      ((INT16U)0x0002)  // Pin 1 selected, 函数参数端口IOx的bit1位    
#define GPIO_PIN_2      ((INT16U)0x0004)  // Pin 2 selected, 函数参数端口IOx的bit2位    
#define GPIO_PIN_3      ((INT16U)0x0008)  // Pin 3 selected, 函数参数端口IOx的bit3位   
#define GPIO_PIN_4      ((INT16U)0x0010)  // Pin 4 selected, 函数参数端口IOx的bit4位  
#define GPIO_PIN_5      ((INT16U)0x0020)  // Pin 5 selected, 函数参数端口IOx的bit5位    
#define GPIO_PIN_6      ((INT16U)0x0040)  // Pin 6 selected, 函数参数端口IOx的bit6位   
#define GPIO_PIN_7      ((INT16U)0x0080)  // Pin 7 selected, 函数参数端口IOx的bit7位  
#define GPIO_PIN_8      ((INT16U)0x0100)  // Pin 8 selected, 函数参数端口IOx的bit8位    
#define GPIO_PIN_9      ((INT16U)0x0200)  // Pin 9 selected, 函数参数端口IOx的bit9位    
#define GPIO_PIN_10     ((INT16U)0x0400)  // Pin 10 selected, 函数参数端口IOx的bit10位  
#define GPIO_PIN_11     ((INT16U)0x0800)  // Pin 11 selected, 函数参数端口IOx的bit11位   
#define GPIO_PIN_12     ((INT16U)0x1000)  // Pin 12 selected, 函数参数端口IOx的bit12位  
#define GPIO_PIN_13     ((INT16U)0x2000)  // Pin 13 selected, 函数参数端口IOx的bit13位   
#define GPIO_PIN_14     ((INT16U)0x4000)  // Pin 14 selected, 函数参数端口IOx的bit14位  
#define GPIO_PIN_15     ((INT16U)0x8000)  // Pin 15 selected, 函数参数端口IOx的bit15位   
#define GPIO_PIN_All    ((INT16U)0xFFFF)  // All pins selected 
#define GPIO_PIN_MASK   ((INT32U)0x0000FFFF) // PIN mask for assert test 

// IO_Ctrl() 控制命令定义
#define CMD_IO_NEG     0    // IO取反
#define CMD_IO_ON_T    1	// IO置1后并延时一段时间再置0
#define CMD_IO_OFF_T   2	// IO置0后并延时一段时间再置1
#define CMD_IO_RST     4    // 复位IO寄存器为初始状态
#define CMD_IO_CLOSE   5    // 关闭IO时钟,也就是关闭DAC功能,可以省电 

/*************************************************************************************/
//
// 							GPIO端口硬件驱动函数定义
//
/*************************************************************************************/

/******************************************************************************************************************
* Function: IO_Init;
*
* Description: IO初始化函数
*              
* Input:  IOx, 单独IO端口, 按单个端口初始化: PA0~PA15,PB0~PB15,PC0~PC15,PD0~PD15,PE0~PE15,PF0~PF15,PG0~PG15,PH0~PH15,PI0~PI15;
*              成组端口, 只初始化bit0~bit15为1的端口: (PA/PB/PC/PD/PE/PF/PG/PH/PI)+(GPIO_PIN_0|GPIO_PIN_1|...|GPIO_PIN_15) 
*
*         Mode, IO模式设置如下：
*               通用输出模式: IO_OUT_PP, 通用推挽输出模式; 
*                             IO_OUT_OD, 通用开漏输出模式;                    
*               输入模式:	  IO_IN_FLOATING, 浮空输入模式(复位后的状态)
*				        	  IO_IN_IPD, 内部下拉输入模式;
*                             IO_IN_IPU, 内部上拉输入模式
*               模拟输入模式: IO_AIN, 模拟输入模式;
*         
*         Speed, IO输出速度：   
*                如果IO模式是输入模式, 则该参数设置为：0(IO_INPUT), 不区分速度
*  				 如果IO模式是输出模式, 则该参数设置为速度选择：
*		         IO_SPEED_10MHz, 最大速度10MHz
*                IO_SPEED_2MHz, 最大速度2MHz
*                IO_SPEED_50MHz, 最大速度50MHz
*                IO_SPEED_25MHz, 最大速度25MHz, 只适用STM32F4xx
*                IO_SPEED_100MHz, 最大速度100MHz, 只适用STM32F4xx
*
* Output: none;
*
* Return: ERR_TRUE,操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
*******************************************************************************************************************/
INT32S IO_Init(INT32U IOx, INT8U Mode, INT8U Speed);

/******************************************************************************************************************
* Function: IO_Read;
*
* Description: 读取IO输入值;
* 
* Input:  IOx, 单独IO端口: PA0~PA15,PB0~PB15,PC0~PC15,PD0~PD15,PE0~PE15,PF0~PF15,PG0~PG15,PH0~PH15,PI0~PI15;
*              成组端口, 只读取bit0~bit15为1的端口: (PA/PB/PC/PD/PE/PF/PG/PH/PI)+(GPIO_PIN_0|GPIO_PIN_1|...|GPIO_PIN_15)
*
* Output: none;
*          		
* Return: IOx是单独IO端口：返回值是1,高电平, 是0,低电平; 
*         IOx是成组端口：  返回值bit0~bit15分别代表Px0~Px15(x为A,B,C,D,E,F,G,H,I), 以bit7为例, 是1则Px7输入高电平, 是0则Px7输入低电平; 
*
* Note:   如果返回值是0x80000000, 则表示出错
*******************************************************************************************************************/
INT32U IO_Read(INT32U IOx);

/******************************************************************************************************************
* Function: IO_Write;
*
* Description: 写入IO输出值;
* 
* Input:  IOx, 单独IO端口: PA0~PA15,PB0~PB15,PC0~PC15,PD0~PD15,PE0~PE15,PF0~PF15,PG0~PG15,PH0~PH15,PI0~PI15;
*              成组端口, 只输出bit0~bit15为1的端口: (PA/PB/PC/PD/PE/PF/PG/PH/PI)+(GPIO_PIN_0|GPIO_PIN_1|...|GPIO_PIN_15)
*       
*         IOx是单独IO端口：val, 1输出高电平, 0,输出低电平; 
*         IOx是成组端口：  val的bit0~bit15分别代表Px0~Px15(x为A,B,C,D,E,F,G,H,I), 以bit7为例, 是1则Px7输出高电平, 是0则Px7输出低电平;
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
* Description: IO命令控制;
* 
* Input:  IOx, 单独IO端口: PA0~PA15,PB0~PB15,PC0~PC15,PD0~PD15,PE0~PE15,PF0~PF15,PG0~PG15,PH0~PH15,PI0~PI15;
*              成组端口, 只控制bit0~bit15为1的端口: (PA/PB/PC/PD/PE/PF/PG/PH/PI)+(GPIO_PIN_0|GPIO_PIN_1|...|GPIO_PIN_15)
*		  Cmd, IO控制命令: 
*              CMD_IO_NEG,   IO取反; 参数Para为0
*              CMD_IO_ON_T,  IO置1后并延时一段时间再置0; 参数Para为延时时间,单位ms;
*              CMD_IO_OFF_T, IO置0后并延时一段时间再置1; 参数Para为延时时间,单位ms;
*              CMD_IO_RST,   复位IO寄存器为初始状态; 参数Para为0; 此时IOx应该PA/PB/PC/PD/PE/PF/PG/PH/PI
*              CMD_IO_CLOSE, 关闭IO时钟,也就是关闭DAC功能,可以省电; 参数Para为0; 此时IOx应该PA/PB/PC/PD/PE/PF/PG/PH/PI
*         Para, 命令参数;
*
* Output: none;
*          		
* Return: ERR_TRUE,操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
*******************************************************************************************************************/
INT32S IO_Ctrl(INT32U IOx, INT8U Cmd, INT32U Para);


#endif
/******************************************************************************************************************/
// 文件结束
/******************************************************************************************************************/


