/*! 
*  \file hmi_driver.h
*  \brief ���ڳ�ʼ��
*  \version 1.0
*  \date 2012-2018
*  \copyright ���ݴ�ʹ��Ƽ����޹�˾
*/
#ifndef _USER_UART__
#define _USER_UART__

//����Ƕ���Ƶ�EMB2628I�϶����һЩ���ڲ���
#define HMI_UART UART5_ID
#define HMI_BAUD UART5_BAUD

#define uchar    unsigned char
#define uint8    unsigned char
#define uint16   unsigned short 
#define uint32   unsigned int
#define int16    short 
#define int32    int

/****************************************************************************
* ��    �ƣ� HMI_UartInit()
* ��    �ܣ� ���ڳ�ʼ��
* ��ڲ����� ��
* ���ڲ����� ��
****************************************************************************/
extern void HMI_UartInit(uint32 Baudrate);

/*****************************************************************
* ��    �ƣ� HMI_SendChar()
* ��    �ܣ� ����1���ֽ�
* ��ڲ����� t  ���͵��ֽ�
* ���ڲ����� ��
*****************************************************************/
extern void  HMI_SendChar(uchar t);

/*****************************************************************
* ��    �ƣ� HMI_UartRecieve()
* ��    �ܣ� �Ӵ����н�������
* ��ڲ����� ��
* ���ڲ����� ��
*****************************************************************/
extern void  HMI_UartRecieve(void);
#endif
