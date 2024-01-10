/************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: moubus.h
* Project  : STM32F1XX/4XXϵ��ģ��������
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: ���ļ���MODBUSЭ��ͨ����������ͷ�ļ�;
*
* Others: none;
*
* Function List: 1-9:��Modbus�����ӿں���; 10: ��Modbus�ӻ����ӿں���;
*          1. INT32S Modbus_ReadCoils(INT8U ch, INT8U id, INT16U addr, INT16U len, INT8U *p, INT16U TimeOut);
*          2. INT32S Modbus_ReadDisInput(INT8U ch, INT8U id, INT16U addr, INT16U len, INT8U *p, INT16U TimeOut);
*          3. INT32S Modbus_ReadHoldReg(INT8U ch, INT8U id, INT16U addr, INT16U len, INT16U *p, INT16U TimeOut);
*          4. INT32S Modbus_ReadInputReg(INT8U ch, INT8U id, INT16U addr, INT16U len, INT16U *p, INT16U TimeOut);
*          5. INT32S Modbus_WriteSingleCoil(INT8U ch, INT8U id, INT16U addr, INT8U val, INT16U TimeOut);
*          6. INT32S Modbus_WriteSingleReg(INT8U ch, INT8U id, INT16U addr, INT16U val, INT16U TimeOut);
*          7. INT32S Modbus_WriteMulCoils(INT8U ch, INT8U id, INT16U addr, INT16U len, INT8U *p, INT16U TimeOut);
*          8. INT32S Modbus_WriteMulReg(INT8U ch, INT8U id, INT16U addr, INT16U len, INT16U *p, INT16U TimeOut);
*          9. INT32S Modbus_ReadWriteMulReg(INT8U ch, INT8U id, INT16U waddr, INT16U wlen, INT16U raddr, INT16U rlen, INT16U *p, INT16U TimeOut);
*          10. INT32S Modbus_Proc(INT8U ch, INT8U id, INT8U *p, INT16U len);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/
#ifndef __MODBUS_H 
#define __MODBUS_H 
/************************************************************************************/
// �����ⲿͷ�ļ�
/************************************************************************************/
#include  "const.h"
//#include  "config.h"
/************************************************************************************
// ������ȫ�ֱ�������
*************************************************************************************/
#define MODBUS_OK_FLAG              0x0001  // Э�����������ȷ
#define MODBUS_READ_DISINPUT_FLAG   0x0002  // ��ȡ��ɢ������������־
#define MODBUS_READ_COILS_FLAG      0x0004  // ��ȡ��ɢ��������־
#define MODBUS_WRITE_COILS_FLAG     0x0008  // д����ɢ��������־
#define MODBUS_READ_HOLDREG_FLAG    0x0004  // ��ȡ���ּĴ�������
#define MODBUS_WRITE_HOLDREG_FLAG   0x0010  // д�뱣�ּĴ�������
#define MODBUS_READ_INPUTREG_FLAG   0x0020  // ��ȡ����Ĵ�������
#define MODBUS_EXCEPTION_DATA_FLAG  0x0040  // ���Ϸ����ݴ���
#define MODBUS_EXCEPTION_ADDR_FLAG  0x0080  // ���Ϸ����ݵ�ַ����

#define MODBUS_DATA_LEN        64          // ����Э�黺��, Ĭ��64(���30���Ĵ�����д),�û����Ը���MODBUS_MAX_HOLDREG��MODBUS_MAX_INPUTREG�����ֵ��2���ټ�4����
typedef struct
{
	INT16U Flag;
	INT16U len;
    INT8U  swcl[2];  // MODBUS TCP: ���ﴦ���ʶ��
    INT8U  xyid[2];  // MODBUS TCP: Э���ʶ��
    INT8U  dlen[2];  // MODBUS TCP: ����
    INT8U  id;
	INT8U  cmd;
	INT8U  bytes;
	INT8U  buf[MODBUS_DATA_LEN];
}MODBUS_DATA;
#define MODBUS_TCP_ID  10   // MODBUS TCP ͨ��ID��ʶ

//Flag: MODBUS�ӻ�������־
//MODBUS�ӻ�ͨ��ģʽ��bit0=0, RTU;  bit0=1, ASCII��; 
#define MODBUS_RTU_FLAG      0x0000      // RTUͨ��ģʽ
#define MODBUS_ASCII_FLAG    0x0001      // ASCIIͨ��ģʽ
typedef struct
{
    INT16U Flag;	          // MODBUS�ӻ�������־
    INT16U CoilsBaseAddr;     // ��Ȧ�Ĵ�������ַ;
    INT16U DisInputBaseAddr;  // ��ɢ�������Ĵ�������ַ;
    INT16U HoldRegBaseAddr;   // ���ּĴ�������ַ;
    INT16U InputRegBaseAddr;  // ����Ĵ�������ַ;    
    INT16U MaxCoils;          // MODBUS�ӻ������Ȧ����(��д,���ù�����:1,5,15);
    INT16U MaxDisInput;       // MODBUS�ӻ������ɢ������(ֻ��,���ù�����:2);
    INT16U MaxHoldReg;        // MODBUS�ӻ���󱣳ּĴ���(��д,���ù�����:3,6,16,23)����;	 
    INT16U MaxInputReg;       // MODBUS�ӻ��������Ĵ���(ֻ��,���ù�����:4)����;
    
    INT8U  *pCoils;           // �����Ȧ�Ĵ���ָ��
    INT8U  *pDisInput;        // ������ɢ�������Ĵ���ָ��
    INT16U *pHoldReg;         // ���ּĴ���ָ��
    INT16U *pInputReg;        // ����Ĵ���ָ��
    
    MODBUS_DATA *pData;       // ��������ָ��
}MODBUS_PARA; 

/************************************************************************************
//
//                 MODBUS����ͨ����������
//
*************************************************************************************/
/***********************************************************************************
* Function: Modbus_ReadCoils;
*
* Description: ��������Ȧ�����������øú������Ͷ���Ȧ����   
*
* Input:  ch, ͨѶ�ܵ���(UART1_ID,UART2_ID,UART3_ID,UART4_ID,UART5_ID)�������һ���������Ĺܵ��������󣬽�������Ч�ܵ����� 
*         id, �ӻ��ĵ�ַ��1~255 
*         addr,��Ȧ��ʼ��ַ��ȡֵ��ΧΪ��0x0000~0xffff 
*         len, ��ȡ��Ȧ������ȡֵ��ΧΪ��0x001~0x07d0 
*         *p, ������Ȧֵ��ָ�룬ָ��ĵ�ַ����Ϊ 8 λ�ַ��͡�*p �ַ��ĵ�0λֵΪ��1����ַ��ֵ��
*         ��7λΪ��8����ַ��ֵ����9����Ȧ��ַ��ֵ��*(p+1)��ַ�ĵ�0λ
*         TimeOut: ִ�г�ʱʱ�䣬��λms; �������ʱ���豸û�з���, ���������س�ʱ�������
*
* Output: none;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   ������ModbusЭ�鹦�ܴ����ǣ�01, ���������Ȧ;
************************************************************************************/
INT32S Modbus_ReadCoils(INT8U ch, INT8U id, INT16U addr, INT16U len, INT8U *p, INT16U TimeOut);
	
/***********************************************************************************
* Function: Modbus_ReadDisInput;
*
* Description: ��������ɢ�����������������øú������Ͷ���ɢ����������  
*
* Input:  ch, ͨѶ�ܵ���(UART1_ID,UART2_ID,UART3_ID,UART4_ID,UART5_ID)�������һ���������Ĺܵ��������󣬽�������Ч�ܵ����� 
*         id, �ӻ��ĵ�ַ��1~255 
*         addr,��ɢ��������ʼ��ַ��ȡֵ��ΧΪ��0x0000~0xffff  
*         len, ��ȡ��ɢ������������ȡֵ��ΧΪ��0x001~0x07d0  
*         *p, ������ɢ������ֵ��ָ�룬ָ��ĵ�ַ����Ϊ 8 λ�ַ��͡�*p �ַ��ĵ�0λֵΪ��1����ַ��ֵ��
*         ��7λΪ��8����ַ��ֵ����9����ɢ��������ַ��ֵ��*(p+1)��ַ�ĵĵ�0λ
*
* Output: none;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   ������ModbusЭ�鹦�ܴ����ǣ�02, ������ɢ������;
************************************************************************************/
INT32S Modbus_ReadDisInput(INT8U ch, INT8U id, INT16U addr, INT16U len, INT8U *p, INT16U TimeOut);

/***********************************************************************************
* Function: Modbus_ReadHoldReg;
*
* Description: ���������ּĴ��������������øú������Ͷ����ּĴ�������   
*
* Input:  ch, ͨѶ�ܵ���(UART1_ID,UART2_ID,UART3_ID,UART4_ID,UART5_ID)�������һ���������Ĺܵ��������󣬽�������Ч�ܵ����� 
*         id, �ӻ��ĵ�ַ��1~255 
*         addr,���ּĴ�����ʼ��ַ��ȡֵ��ΧΪ��0x0000~0xffff  
*         len, ��ȡ���ּĴ���������ȡֵ��ΧΪ��0x01~0x07d   
*         *p, ���汣�ּĴ���ֵ��ָ�룬ָ��ĵ�ַ����Ϊ 16 λ�޷�������;
*         p ָ������ĵ�1���Ĵ���ֵ��ŵĵ�ַ��
*
* Output: none;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   ������ModbusЭ�鹦�ܴ����ǣ�03, �������ּĴ���;
************************************************************************************/
INT32S Modbus_ReadHoldReg(INT8U ch, INT8U id, INT16U addr, INT16U len, INT16U *p, INT16U TimeOut);

/***********************************************************************************
* Function: Modbus_ReadInputReg;
*
* Description: ����������Ĵ��������������øú������Ͷ�����Ĵ�������   
*
* Input:  ch, ͨѶ�ܵ���(UART1_ID,UART2_ID,UART3_ID,UART4_ID,UART5_ID)�������һ���������Ĺܵ��������󣬽�������Ч�ܵ����� 
*         id, �ӻ��ĵ�ַ��1~255 
*         addr,����Ĵ�������ʼ��ַ��ȡֵ��ΧΪ��0x0000~0xffff  
*         len, ��ȡ����Ĵ���������ȡֵ��ΧΪ��0x01~0x07d    
*         *p, ��������Ĵ���ֵ��ָ�룬ָ��ĵ�ַ����Ϊ 16 λ�޷�������;
*         p ָ������ĵ�1���Ĵ���ֵ��ŵĵ�ַ��
*
* Output: none;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   ������ModbusЭ�鹦�ܴ����ǣ�04, ��������Ĵ���;
************************************************************************************/
INT32S Modbus_ReadInputReg(INT8U ch, INT8U id, INT16U addr, INT16U len, INT16U *p, INT16U TimeOut);

/***********************************************************************************
* Function: Modbus_WriteSingleCoil;
*
* Description: ����д������Ȧ�����������øú�������д������Ȧ����    
*
* Input:  ch, ͨѶ�ܵ���(UART1_ID,UART2_ID,UART3_ID,UART4_ID,UART5_ID)�������һ���������Ĺܵ��������󣬽�������Ч��
*         id, �ӻ��ĵ�ַ��1~255 
*         addr, д����Ȧ�ĵ�ַ��ȡֵ��ΧΪ��0x0000~0xffff 
*         val,  д����Ȧ��ֵ��0, �ر���Ȧ; 1, ����Ȧ; 
*
* Output: none;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   ������ModbusЭ�鹦�ܴ����ǣ�05, ���������Ȧ;
************************************************************************************/
INT32S Modbus_WriteSingleCoil(INT8U ch, INT8U id, INT16U addr, INT8U val, INT16U TimeOut);

/***********************************************************************************
* Function: Modbus_WriteSingleReg;
*
* Description: ���øú�������д�������ּĴ�������    
*
* Input:  ch, ͨѶ�ܵ���(UART1_ID,UART2_ID,UART3_ID,UART4_ID,UART5_ID)�������һ���������Ĺܵ��������󣬽�������Ч��
*         id, �ӻ��ĵ�ַ��1~255 
*         addr, д�뱣�ּĴ����ĵ�ַ��ȡֵ��ΧΪ��0x0000~0xffff  
*         val,  д�뱣�ּĴ�����ֵ��ȡֵ��ΧΪ��0x0000~0xffff 
*
* Output: none;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   ������ModbusЭ�鹦�ܴ����ǣ�06, �������ּĴ���;
************************************************************************************/
INT32S Modbus_WriteSingleReg(INT8U ch, INT8U id, INT16U addr, INT16U val, INT16U TimeOut);

/***********************************************************************************
* Function: Modbus_WriteMulCoils;
*
* Description: ���øú�������д�����Ȧ����   
*
* Input:  ch, ͨѶ�ܵ���(UART1_ID,UART2_ID,UART3_ID,UART4_ID,UART5_ID)�������һ���������Ĺܵ��������󣬽�������Ч�ܵ����� 
*         id, �ӻ��ĵ�ַ��1~255 
*         addr,��Ȧ��ʼ��ַ��ȡֵ��ΧΪ��0x0000~0xffff 
*         len, ��д����Ȧ�ĸ�����ȡֵ��ΧΪ��0x01~0x07b0
*         *p, д����Ȧ���ݻ����ָ�룬ָ��ĵ�ַ����Ϊ8λ�ַ��͡�*p �ַ��ĵ�0λֵΪ��1����ַ��ֵ��
*         ��7λΪ��8����ַ��ֵ����9����Ȧ��ַ��ֵ��*(p+1)��ַ�ĵ�0λ
*
* Output: none;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   ������ModbusЭ�鹦�ܴ����ǣ�15, ���������Ȧ;
************************************************************************************/
INT32S Modbus_WriteMulCoils(INT8U ch, INT8U id, INT16U addr, INT16U len, INT8U *p, INT16U TimeOut);

/***********************************************************************************
* Function: Modbus_WriteMulReg;
*
* Description: ���øú�������д����Ĵ�������  
*
* Input:  ch, ͨѶ�ܵ���(UART1_ID,UART2_ID,UART3_ID,UART4_ID,UART5_ID)�������һ���������Ĺܵ��������󣬽�������Ч�ܵ����� 
*         id, �ӻ��ĵ�ַ��1~255 
*         addr, ���ּĴ�����ʼ��ַ��ȡֵ��ΧΪ��0x0000~0xffff 
*         len, ��д�뱣�ּĴ����ĸ�����ȡֵ��ΧΪ��0x01~0x078 
*         *p, ��д�뱣�ּĴ��������ݻ�������ָ�룬ָ������Ϊ16λ
*
* Output: none;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   ������ModbusЭ�鹦�ܴ����ǣ�16, �������ּĴ���;
************************************************************************************/
INT32S Modbus_WriteMulReg(INT8U ch, INT8U id, INT16U addr, INT16U len, INT16U *p, INT16U TimeOut);

/***********************************************************************************
* Function: Modbus_ReadWriteMulReg;
*
* Description: ���øú�������д��Ĵ�������ִ�иú���ʱ����д��������
*
* Input:  ch, ͨѶ�ܵ���(UART1_ID,UART2_ID,UART3_ID,UART4_ID,UART5_ID)�������һ���������Ĺܵ��������󣬽�������Ч�ܵ����� 
*         id, �ӻ��ĵ�ַ��1~255 
*         waddr, д�뱣�ּĴ�������ʼ��ַ��ȡֵ��ΧΪ��0x0000~0xffff 
*         wlen, �������ּĴ����ĸ�����ȡֵ��ΧΪ��1~121 
*         raddr, д�뱣�ּĴ�������ʼ��ַ��ȡֵ��ΧΪ��0x0000~0xffff 
*         rlen, �������ּĴ����ĸ�����ȡֵ��ΧΪ��1~125 
*         *p, ��д�뱣�ּĴ��������ݻ�����ָ�룬ͬʱҲ�Ƕ����Ĵ������ݴ�Ż�������ָ�� 
*
* Output: none;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   ������ModbusЭ�鹦�ܴ����ǣ�23, �������ּĴ���;
************************************************************************************/
INT32S Modbus_ReadWriteMulReg(INT8U ch, INT8U id, INT16U waddr, INT16U wlen, INT16U raddr, INT16U rlen, INT16U *p, INT16U TimeOut);

/************************************************************************************
//
//                 MODBUS�ӻ�ͨ����������
//
*************************************************************************************/
/***********************************************************************************
* Function: Modbus_Proc;
*
* Description: MODBUS�ӻ�ͨ��ָ���������
*
* Input:  ch: ͨ��ͨ��: UART1_ID~UART5_ID(0-4), MODBUS_TCP_ID(10); 
*         id: �����豸ID(���ߵ�ַ), ��Χ:1-250;
*         *p: ����ָ��; len: ���ݳ���
*         *pPara: Modbus�ӻ�ģʽ����;
*
* Output: none;
*
* Return:  ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������; 
*
* Note:   none;
************************************************************************************/
INT32S Modbus_Proc(INT8U ch, INT8U id, INT8U *p, INT16U len, MODBUS_PARA *pPara);
	
#endif
/***********************************************************************************/
// �ļ�����
/***********************************************************************************/
