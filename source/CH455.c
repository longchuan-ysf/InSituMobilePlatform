/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: CH455.h
* Project  : STM32F1XX/4XX系列模块驱动库
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: 本文件是CH455读写驱动库程序头文件;
*
* Others: none;
*
* Function List: 
*          1. void CH455_Read(void);
*          2. INT8U CH455_Read(void);
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
#include "const.h"	 
#include "config.h"	 
#include "ch455.h"
#include "i2c.h"
#if CH455_EN     

// 请在下面选择CH455控制方式
#define CH455_I2C_MODE	 	// CH455用I2C总线控制
//#define CH455_IO_MODE	 	// CH455用IO(模拟I2C总线)控制


#ifdef CH455_I2C_MODE
#define I2C_ID   I2C3_ID    // 选择I2C ID 
#endif

// CH455控制变量定义 
#define CH455_BIT_ENABLE	0x01		// 开启/关闭位
#define CH455_BIT_SLEEP		0x04		// 睡眠控制位
#define CH455_BIT_7SEG		0x08		// 7段控制位

#define CH455_BIT_INTENS1	0x10		// 1级亮度
#define CH455_BIT_INTENS2	0x20		// 2级亮度
#define CH455_BIT_INTENS3	0x30		// 3级亮度
#define CH455_BIT_INTENS4	0x40		// 4级亮度
#define CH455_BIT_INTENS5	0x50		// 5级亮度
#define CH455_BIT_INTENS6	0x60		// 6级亮度
#define CH455_BIT_INTENS7	0x70		// 7级亮度
#define CH455_BIT_INTENS8	0x00		// 8级亮度

#define CH455_SYSOFF	0x0400			// 关闭显示、关闭键盘
#define CH455_SYSON		( CH455_SYSOFF | CH455_BIT_ENABLE )	// 开启显示、键盘
#define CH455_SLEEPOFF	CH455_SYSOFF	// 关闭睡眠
#define CH455_SLEEPON	( CH455_SYSOFF | CH455_BIT_SLEEP )	// 开启睡眠
#define CH455_7SEG_ON	( CH455_SYSON | CH455_BIT_7SEG )	// 开启七段模式
#define CH455_8SEG_ON	( CH455_SYSON | 0x00 )	// 开启八段模式
#define CH455_SYSON_4	( CH455_SYSON | CH455_BIT_INTENS4 )	// 开启显示、键盘、4级亮度
#define CH455_SYSON_8	( CH455_SYSON | CH455_BIT_INTENS8 )	// 开启显示、键盘、8级亮度


// 加载字数据命令
#define CH455_DIG0		0x1400			// 数码管位0显示,需另加8位数据
#define CH455_DIG1		0x1500			// 数码管位1显示,需另加8位数据
#define CH455_DIG2		0x1600			// 数码管位2显示,需另加8位数据
#define CH455_DIG3		0x1700			// 数码管位3显示,需另加8位数据

// 读取按键代码命令
#define CH455_GET_KEY	0x4F			// 获取按键,返回按键代码

// 设置命令
#define CH455_SET	    0x48			// 设置命令
#define CH455_INIT	    CH455_BIT_ENABLE //(CH455_BIT_ENABLE|CH455_BIT_SLEEP)   			// 初始化设置

// CH455接口定义
#define	 CH455_I2C_ADDR		0x40			// CH455的地址
#define	 CH455_I2C_MASK		0x3E			// CH455的高字节命令掩码




/**************************************************************************************/
// CH455用IO(模拟I2C总线)控制
/**************************************************************************************/
#include "gpio.h"
#include "delay.h"


/************************************************************************************
// 常量及全局变量定义
*************************************************************************************/
#define  IIC_WRITE      0                 // WRITE direction bit
#define  IIC_READ       1                 // READ direction bit



#define SDA(x) IO_Write(CH455_SDA, x)
#define SCL(x) IO_Write(CH455_SCL, x)
#define GETSDA IO_Read(CH455_SDA)	

INT8U CH455_Mode;
/************************************************************************************
//
//                 IO模拟IIC总线硬件驱动程序
//
*************************************************************************************/
/***********************************************************************************
* Function: iic_start;
*
* Description: iic通信起始函数;
*              
* Input:  none;
*
* Output: none;
*
* Return: none;
*
* Note:   none;
************************************************************************************/
void iic_start(void)                    
{  
      SDA(1);
	  Delay_us(2);
      SCL(1);
	  Delay_us(2);
      SDA(0);
	  Delay_us(2);      
}

/***********************************************************************************
* Function: iic_stop;
*
* Description: iic通信停止函数;
*              
* Input:  none;
*
* Output: none;
*
* Return: none;
*
* Note:   none;
************************************************************************************/
void iic_stop(void)                     
{
      SDA(0);
	  Delay_us(2);
      SCL(1);
	  Delay_us(2);
      SDA(1);
}
/***********************************************************************************
* Function: iic_ack;
*
* Description: 发送ACK信号函数;
*              
* Input:  none;
*
* Output: none;
*
* Return: none;
*
* Note:   none;
************************************************************************************/
void iic_ack(void)                      
{ 
	  SCL(0);
      SDA(0);
	  Delay_us(2);
      SCL(1);
	  Delay_us(2);  
      SCL(0);
	  Delay_us(1); 
      SDA(1);
}
/***********************************************************************************
* Function: read_ack;
*
* Description: 读取从器件ACK信号函数;
*              
* Input:  none;
*
* Output: none;
*
* Return: 返回TRUE,地址或数据字节已发送收到ACK,否则没收到;
*
* Note:   none;
************************************************************************************/
INT8U read_ack(void)                      
{ 
	  INT8U flag;
	 
      SCL(0);
	  Delay_us(2);    
      SDA(1);
      SCL(1);
	  Delay_us(2);
      flag = GETSDA; 
      SCL(0); 
      
	  return flag;
}

/***********************************************************************************
* Function: iic_nack;
*
* Description: 发送NACK信号函数;
*              
* Input:  none;
*
* Output: none;
*
* Return: none;
*
* Note:   none;
************************************************************************************/
void iic_nack()                     
{   
      SDA(1);
	  Delay_us(2);      
      SCL(1);
	  Delay_us(2);      
	  SCL(0);
}

/***********************************************************************************
* Function: get_byte;
*
* Description: 读取字节数据函数;
*              
* Input:  none;
*
* Output: none;
*
* Return: 字节数据;
*
* Note:   none;
************************************************************************************/
unsigned char get_byte(void)                         //输入一个字节        
{
    unsigned char dd;
    int i;
    
    dd=0;
   	SDA(1);
	for (i=0;i<8;i++)
    {
         SCL(0);
		 Delay_us(3);
         SCL(1);
		 Delay_us(1); 
         dd<<=1;
		 if (GETSDA)
      	      dd|=0x01;
    }         
    SCL(0);
	return(dd);
}

/***********************************************************************************
* Function: out_byte;
*
* Description: 输出字节数据函数;
*              
* Input:  字节数据;
*
* Output: none;
*
* Return: none;
*
* Note:   none;
************************************************************************************/
void out_byte(unsigned char dd)                      //输出一个字节
{
    unsigned char i;

    for(i=0;i<8;i++)
    {  
          SCL(0);
		  Delay_us(0);			
          SDA( ((dd & 0x80)>>7) );
		  Delay_us(2);         
          SCL(1);
		  Delay_us(3);
          dd <<= 1;
    } 
	SCL(0);    
}

/***********************************************************************************
* Function: iic_write_addr;
*
* Description: 向IIC器件写入地址数据函数;
*              
* Input:  addr,器件地址;data_addr,数据地址;
*
* Output: none;
*
* Return: 写入成功;
*
* Note:   none;
************************************************************************************/
INT8U iic_write_addr(unsigned char addr,unsigned char data_addr)
{
	  iic_start();
      out_byte(addr); 
      read_ack();   
      out_byte(data_addr);
      read_ack();
      
      return 1;          
}

/***********************************************************************************
* Function: IICA_Write;
*
* Description: IIC总线写数据函数;
*              
* Input:  id,IIC器件识别地址, addr,写数据的起始地址; *p, 写入数据存储的地址指针;len,要写入数据长度;
*
* Output: none;
*
* Return: none;
*
* Note:   只支持AT24C01/02/04/08/16或地址是8位的器件;
************************************************************************************/
void IICA_Write(unsigned char id, unsigned char addr, unsigned char *p, unsigned int len)
{      
  	  int i;

	  iic_write_addr(id|IIC_WRITE,addr);  
	                                                   
      for (i=0;i<len;i++)
      {
      		out_byte(*p++);
      		read_ack(); 
      }
      iic_stop();      
}
/***********************************************************************************
* Function: IICA_Read;
*
* Description: IIC总线读数据函数;
*              
* Input:  id,IIC器件识别地址, addr,读数据的起始地址; *p, 读出数据存储的地址指针;len,要读出数据长度;
*
* Output: none;
*
* Return: none;
*
* Note:   只支持AT24C01/02/04/08/16或地址是8位的器件;
************************************************************************************/
void IICA_Read(unsigned char id, unsigned char addr, unsigned char *p, unsigned int len)
{                                                    
    int i;

    iic_write_addr(id|IIC_WRITE,addr);  
    iic_start();
    out_byte(id|IIC_READ);
    read_ack();     
    for (i=0;i<len;i++)
    {
       *p++ = get_byte();
       if (i!=(len-1))
            iic_ack();      	   
    }       
    iic_nack();        
    iic_stop();
}


void IIC_Write_455H(unsigned char addr, unsigned char data)
{      
	  iic_start();
	  out_byte(addr|IIC_WRITE);
	  iic_nack();
	  out_byte(data);
	  iic_nack();        
      iic_stop();
}
void IIC_Read_455H(unsigned char addr, unsigned char *data)
{                                                    
	  iic_start();
	  out_byte(addr|IIC_READ);
	  iic_nack();
	  *data=get_byte();
	  iic_nack();        
      iic_stop();
}
/***********************************************************************************
* Function: CH455_Init;
*
* Description: CH455初始化函数;
*           
* Input:  none;
*
* Output: none;
*          		
* Return: none;
*
* Note:   none;
************************************************************************************/        
//INT8U CH455_Read(void)
//{
//    INT8U key;
//    
//    if(IO_Read(K_INT)==0)  //查询是否有按键中断
//	{
//        IIC_Read_455H(CH455_GET_KEY, &key);
//		key &= 0x3F;
//    }
//    else
//    {
//        key = KEY_NO;  
//    }
//    return key;
//}       
/***********************************************************************************
* Function: CH455_Read;
*
* Description: CH455读取按键值函数;
*           
* Input:  none;
*
* Output: none;
*          		
* Return: 按键值4-7/12-15/20-23/28-31/36-39/44-47/52-55或无键值0;
*
* Note:   none;
************************************************************************************/
//void CH455_Init(void)
//{  
//    IO_Init(KEY_SCL, IO_OUT_PP, IO_SPEED_2MHz);    
//    IO_Write(KEY_SCL, 0);                          // 输出使能禁止
//    IO_Init(KEY_SDA, IO_OUT_OD_IPU, IO_SPEED_2MHz);    
//    IO_Write(KEY_SDA, 0); 
//    IO_Init(K_INT, IO_IN_IPU, IO_SPEED_2MHz);    
//    IO_Write(K_INT, 1); 

//	IIC_Write_455H(CH455_SET, CH455_INIT);
//}


/**************************************************************************************/
// CH455用I2C总线控制
/**************************************************************************************/

/***********************************************************************************
* Function: CH455_Init;
*
* Description: CH455初始化函数;
*           
* Input:  *pPara: 初始化函数指针;
*
* Output: none;
*          		
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   none;
************************************************************************************/
INT32S CH455_Init(CH455_PARA *pPara)
{
	INT8U val;
    
    CH455_Mode = pPara->Mode;
    
    if (CH455_Mode == CH455_MODE_IO)
    {
        IO_Init(CH455_SCL, IO_OUT_PP, IO_SPEED_2MHz);    
        IO_Write(CH455_SCL, 0);                          // 输出使能禁止
        IO_Init(CH455_SDA, IO_OUT_OD_IPU, IO_SPEED_2MHz);    
        IO_Write(CH455_SDA, 0); 
        IO_Init(CH455_INT, IO_IN_IPU, IO_SPEED_2MHz);    
        IO_Write(CH455_INT, 1); 

        IIC_Write_455H(CH455_SET, CH455_INIT);
    }   
    else
    {    
        IO_Init(CH455_INT, IO_IN_IPU, IO_SPEED_2MHz);    
        IO_Write(CH455_INT, 1); 
        val = CH455_INIT;
        I2C_Read(CH455_I2C, CH455_GET_KEY, 0x41, &val, 1);
    }
}
/***********************************************************************************
* Function: CH455_Read;
*
* Description: CH455读取按键值函数;
*           
* Input:  none;
*
* Output: none;
*          		
* Return: 按键值4-7/12-15/20-23/28-31/36-39/44-47/52-55或无键值0;
*
* Note:   none;
************************************************************************************/
INT8U CH455_Read(void)
{
    INT8U key;
    INT32S flag;    
    
    key = KEY_NO;  
	if(IO_Read(CH455_INT)==0)  //查询是否有按键中断
	{
        if (CH455_Mode == CH455_MODE_IO)
        {    
            IIC_Read_455H(CH455_GET_KEY, &key);
            key &= 0x3F;
        }
        else
        {
            flag = I2C_Read(CH455_I2C, CH455_GET_KEY, 0x41, &key, 1);
            if (flag == ERR_TRUE)
            {
                key &= 0x3F;
            }
        } 
    }    
    return key;
}       

#endif
/***********************************************************************************/
// 文件结束
/***********************************************************************************/

