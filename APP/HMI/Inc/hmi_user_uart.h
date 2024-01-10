/*! 
*  \file hmi_driver.h
*  \brief 串口初始化
*  \version 1.0
*  \date 2012-2018
*  \copyright 广州大彩光电科技有限公司
*/
#ifndef _USER_UART__
#define _USER_UART__

//在中嵌凌云的EMB2628I上定义的一些串口参数
#define HMI_UART UART5_ID
#define HMI_BAUD UART5_BAUD

#define uchar    unsigned char
#define uint8    unsigned char
#define uint16   unsigned short 
#define uint32   unsigned int
#define int16    short 
#define int32    int

/****************************************************************************
* 名    称： HMI_UartInit()
* 功    能： 串口初始化
* 入口参数： 无
* 出口参数： 无
****************************************************************************/
extern void HMI_UartInit(uint32 Baudrate);

/*****************************************************************
* 名    称： HMI_SendChar()
* 功    能： 发送1个字节
* 入口参数： t  发送的字节
* 出口参数： 无
*****************************************************************/
extern void  HMI_SendChar(uchar t);

/*****************************************************************
* 名    称： HMI_UartRecieve()
* 功    能： 从串口中接收数据
* 入口参数： 无
* 出口参数： 无
*****************************************************************/
extern void  HMI_UartRecieve(void);
#endif
