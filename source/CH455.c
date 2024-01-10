/************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: CH455.h
* Project  : STM32F1XX/4XXϵ��ģ��������
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: ���ļ���CH455��д���������ͷ�ļ�;
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
// �����ⲿͷ�ļ�
/************************************************************************************/
#include "const.h"	 
#include "config.h"	 
#include "ch455.h"
#include "i2c.h"
#if CH455_EN     

// ��������ѡ��CH455���Ʒ�ʽ
#define CH455_I2C_MODE	 	// CH455��I2C���߿���
//#define CH455_IO_MODE	 	// CH455��IO(ģ��I2C����)����


#ifdef CH455_I2C_MODE
#define I2C_ID   I2C3_ID    // ѡ��I2C ID 
#endif

// CH455���Ʊ������� 
#define CH455_BIT_ENABLE	0x01		// ����/�ر�λ
#define CH455_BIT_SLEEP		0x04		// ˯�߿���λ
#define CH455_BIT_7SEG		0x08		// 7�ο���λ

#define CH455_BIT_INTENS1	0x10		// 1������
#define CH455_BIT_INTENS2	0x20		// 2������
#define CH455_BIT_INTENS3	0x30		// 3������
#define CH455_BIT_INTENS4	0x40		// 4������
#define CH455_BIT_INTENS5	0x50		// 5������
#define CH455_BIT_INTENS6	0x60		// 6������
#define CH455_BIT_INTENS7	0x70		// 7������
#define CH455_BIT_INTENS8	0x00		// 8������

#define CH455_SYSOFF	0x0400			// �ر���ʾ���رռ���
#define CH455_SYSON		( CH455_SYSOFF | CH455_BIT_ENABLE )	// ������ʾ������
#define CH455_SLEEPOFF	CH455_SYSOFF	// �ر�˯��
#define CH455_SLEEPON	( CH455_SYSOFF | CH455_BIT_SLEEP )	// ����˯��
#define CH455_7SEG_ON	( CH455_SYSON | CH455_BIT_7SEG )	// �����߶�ģʽ
#define CH455_8SEG_ON	( CH455_SYSON | 0x00 )	// �����˶�ģʽ
#define CH455_SYSON_4	( CH455_SYSON | CH455_BIT_INTENS4 )	// ������ʾ�����̡�4������
#define CH455_SYSON_8	( CH455_SYSON | CH455_BIT_INTENS8 )	// ������ʾ�����̡�8������


// ��������������
#define CH455_DIG0		0x1400			// �����λ0��ʾ,�����8λ����
#define CH455_DIG1		0x1500			// �����λ1��ʾ,�����8λ����
#define CH455_DIG2		0x1600			// �����λ2��ʾ,�����8λ����
#define CH455_DIG3		0x1700			// �����λ3��ʾ,�����8λ����

// ��ȡ������������
#define CH455_GET_KEY	0x4F			// ��ȡ����,���ذ�������

// ��������
#define CH455_SET	    0x48			// ��������
#define CH455_INIT	    CH455_BIT_ENABLE //(CH455_BIT_ENABLE|CH455_BIT_SLEEP)   			// ��ʼ������

// CH455�ӿڶ���
#define	 CH455_I2C_ADDR		0x40			// CH455�ĵ�ַ
#define	 CH455_I2C_MASK		0x3E			// CH455�ĸ��ֽ���������




/**************************************************************************************/
// CH455��IO(ģ��I2C����)����
/**************************************************************************************/
#include "gpio.h"
#include "delay.h"


/************************************************************************************
// ������ȫ�ֱ�������
*************************************************************************************/
#define  IIC_WRITE      0                 // WRITE direction bit
#define  IIC_READ       1                 // READ direction bit



#define SDA(x) IO_Write(CH455_SDA, x)
#define SCL(x) IO_Write(CH455_SCL, x)
#define GETSDA IO_Read(CH455_SDA)	

INT8U CH455_Mode;
/************************************************************************************
//
//                 IOģ��IIC����Ӳ����������
//
*************************************************************************************/
/***********************************************************************************
* Function: iic_start;
*
* Description: iicͨ����ʼ����;
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
* Description: iicͨ��ֹͣ����;
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
* Description: ����ACK�źź���;
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
* Description: ��ȡ������ACK�źź���;
*              
* Input:  none;
*
* Output: none;
*
* Return: ����TRUE,��ַ�������ֽ��ѷ����յ�ACK,����û�յ�;
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
* Description: ����NACK�źź���;
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
* Description: ��ȡ�ֽ����ݺ���;
*              
* Input:  none;
*
* Output: none;
*
* Return: �ֽ�����;
*
* Note:   none;
************************************************************************************/
unsigned char get_byte(void)                         //����һ���ֽ�        
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
* Description: ����ֽ����ݺ���;
*              
* Input:  �ֽ�����;
*
* Output: none;
*
* Return: none;
*
* Note:   none;
************************************************************************************/
void out_byte(unsigned char dd)                      //���һ���ֽ�
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
* Description: ��IIC����д���ַ���ݺ���;
*              
* Input:  addr,������ַ;data_addr,���ݵ�ַ;
*
* Output: none;
*
* Return: д��ɹ�;
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
* Description: IIC����д���ݺ���;
*              
* Input:  id,IIC����ʶ���ַ, addr,д���ݵ���ʼ��ַ; *p, д�����ݴ洢�ĵ�ַָ��;len,Ҫд�����ݳ���;
*
* Output: none;
*
* Return: none;
*
* Note:   ֻ֧��AT24C01/02/04/08/16���ַ��8λ������;
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
* Description: IIC���߶����ݺ���;
*              
* Input:  id,IIC����ʶ���ַ, addr,�����ݵ���ʼ��ַ; *p, �������ݴ洢�ĵ�ַָ��;len,Ҫ�������ݳ���;
*
* Output: none;
*
* Return: none;
*
* Note:   ֻ֧��AT24C01/02/04/08/16���ַ��8λ������;
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
* Description: CH455��ʼ������;
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
//    if(IO_Read(K_INT)==0)  //��ѯ�Ƿ��а����ж�
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
* Description: CH455��ȡ����ֵ����;
*           
* Input:  none;
*
* Output: none;
*          		
* Return: ����ֵ4-7/12-15/20-23/28-31/36-39/44-47/52-55���޼�ֵ0;
*
* Note:   none;
************************************************************************************/
//void CH455_Init(void)
//{  
//    IO_Init(KEY_SCL, IO_OUT_PP, IO_SPEED_2MHz);    
//    IO_Write(KEY_SCL, 0);                          // ���ʹ�ܽ�ֹ
//    IO_Init(KEY_SDA, IO_OUT_OD_IPU, IO_SPEED_2MHz);    
//    IO_Write(KEY_SDA, 0); 
//    IO_Init(K_INT, IO_IN_IPU, IO_SPEED_2MHz);    
//    IO_Write(K_INT, 1); 

//	IIC_Write_455H(CH455_SET, CH455_INIT);
//}


/**************************************************************************************/
// CH455��I2C���߿���
/**************************************************************************************/

/***********************************************************************************
* Function: CH455_Init;
*
* Description: CH455��ʼ������;
*           
* Input:  *pPara: ��ʼ������ָ��;
*
* Output: none;
*          		
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
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
        IO_Write(CH455_SCL, 0);                          // ���ʹ�ܽ�ֹ
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
* Description: CH455��ȡ����ֵ����;
*           
* Input:  none;
*
* Output: none;
*          		
* Return: ����ֵ4-7/12-15/20-23/28-31/36-39/44-47/52-55���޼�ֵ0;
*
* Note:   none;
************************************************************************************/
INT8U CH455_Read(void)
{
    INT8U key;
    INT32S flag;    
    
    key = KEY_NO;  
	if(IO_Read(CH455_INT)==0)  //��ѯ�Ƿ��а����ж�
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
// �ļ�����
/***********************************************************************************/

