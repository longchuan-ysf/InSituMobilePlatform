/************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: i2c.h
* Project  : STM32F1XX/4XXϵ��ģ��������
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: ���ļ���I2C����Ӳ����������ͷ�ļ�;
*
* Others: none;
*
* Function List: 
*          1. INT32S I2C_Init(INT8U I2Cx, I2C_PARA *pPara);
*          2. INT32S I2C_Read(INT8U id, INT16U I2CAddr, INT16U addr, INT8U *p, INT16U len);
*          3. INT32S I2C_Write(INT8U id, INT16U I2CAddr, INT16U addr, INT8U *p, INT16U len);
*          4. INT32S I2C_Ctrl(INT8U id, INT8U Cmd, INT32U Para);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/
#ifndef __I2C_H 
#define __I2C_H 	 

/************************************************************************************/
// �����ⲿͷ�ļ�
/************************************************************************************/
#include "const.h" 

/************************************************************************************/
// ��ʼ��������������
/************************************************************************************/
// I2C��������
#define I2C1_ID		0 
#define I2C2_ID    	1 
#define I2C3_ID    	2  // ֻ��STM32F407VEģ��֧�� 

// I2C������ַ����
#define I2C_8Bit		0x0000   // I2C������ַ�����8bit
#define I2C_16Bit    	0x8000   // I2C������ַ�����16bit

// I2Cģʽ����
#define I2C_Mode_I2C                    ((INT16U)0x0000)  // I2Cģʽ
#define I2C_Mode_SMBusDevice            ((INT16U)0x0002)  // SMBus�豸ģʽ
#define I2C_Mode_SMBusHost              ((INT16U)0x000A)  // SMBus����ģʽ

// I2C_duty_cycle_in_fast_mode 
#define I2C_DutyCycle_16_9              ((INT16U)0x4000)  // I2C ����ģʽ�� Tlow/Thigh = 16/9 
#define I2C_DutyCycle_2                 ((INT16U)0xBFFF)  // I2C ����ģʽ�� Tlow/Thigh = 2 

// I2C_acknowledgement
#define I2C_Ack_Enable                  ((INT16U)0x0400)  // Ӧ��ȷ��ʹ�ܣ��ڽ��ܵ�һ���ֽڷ���һ��Ӧ��
#define I2C_Ack_Disable                 ((INT16U)0x0000)  // Ӧ��ȷ�Ϲرգ���Ӧ��ʹ��

// I2C_acknowledged_address 
#define I2C_AcknowledgedAddress_7bit    ((INT16U)0x4000)  // 7λ��ַģʽ
#define I2C_AcknowledgedAddress_10bit   ((INT16U)0xC000)  // 10λ��ַģʽ

// I2C(�ܽ�)������ӳ�䶨��
#define I2C_REMAP_0       0    // I2Cû����ӳ��
#define I2C_REMAP_1       1    // I2C��ӳ��
                              
/*
// I2C1(�ܽ�)������ӳ�䶨��
#define I2C1_REMAP_0       0   // I2C1û����ӳ��, ��Ӧ�ܽŶ��壺
                               // I2C1_SCL: PB6; I2C1_SDA: PB7;
                               
#define I2C1_REMAP_1       1   // I2C1��ӳ��, ��Ӧ�ܽŶ��壺
                               // I2C1_SCL: PB8; I2C1_SDA: PB9;

// I2C2(�ܽ�)û�й�����ӳ�䶨��
#define I2C2_REMAP_0       0   // I2C2û����ӳ��, ��Ӧ�ܽŶ��壺
                               // I2C2_SCL: PB10; I2C2_SDA: PB11;
*/                              

/************************************************************************************************************************/
// ���±��ǹ���ģ��STM32F107VC,STM32F103VE,STM32F103ZE I2C1-2�ܽ�ӳ���, ��������ӳ�䷽ʽ����
/************************************************************************************************************************/
// I2C1-I2C2(�ܽ�)������ӳ���
/*
|---------------------------------------|
| ��Ŀ  |  ��ӳ��  | SCL�ܽ� | SDA�ܽ�  |
|---------------------------------------|
|       |   û��   |   PB6   |   PB7    |
| I2C1  |-------------------------------|
|       |  ��ӳ��1 |   PB8   |   PB9    |
|---------------------------------------|
| I2C2  |   û��   |   PB10  |   PB11   |
|---------------------------------------|
*/                               
                 
/************************************************************************************************************************/
// ���±��ǹ���ģ��STM32F407VE I2C1-3�ܽ�ӳ���, �����ùܽŸ��üĴ�������
/************************************************************************************************************************/
// I2C1-I2C2(�ܽ�)����ӳ���
/*
|---------------------------------------|
| ��Ŀ  | ����ѡ�� | SCL�ܽ� | SDA�ܽ�  |
|---------------------------------------|
|       |          |   PB6   |   PB7    |
| I2C1  |   AF4    |--------------------|
|       |          |   PB8   |   PB9    |
|---------------------------------------|
|       |          |   PB10  |   PB11   |
| I2C2  |   AF4    |--------------------|
|       |          |   PF0   |   PF1    |
|---------------------------------------|
|       |          |   PA8   |   PC9    |
| I2C3  |   AF4    |--------------------|
|       |          |   PH7   |   PH8    |
|---------------------------------------|
*/                               
       
                               
// I2C�����ṹ
typedef struct
{
    INT16U Flag;                // ������־
    INT8U  PinRemap;            // I2C���Ź�����ӳ��
    INT8U  SDAPin;              // SDA����
    INT8U  SCLPin;              // SCL����
    
    INT16U Mode;                // I2C����ģʽ:
                                // This parameter can be a value of I2C_mode 
    INT16U DutyCycle;           // Specifies the I2C fast mode duty cycle.
                                // This parameter can be a value of I2C_duty_cycle_in_fast_mode 
    INT16U OwnAddress1;         // Specifies the first device own address.
                                // This parameter can be a 7-bit or 10-bit address. 
    INT16U Ack;                 // Enables or disables the acknowledgement.
                                // This parameter can be a value of I2C_acknowledgement 
    INT16U AcknowledgedAddress; // Specifies if 7-bit or 10-bit address is acknowledged.
                                // This parameter can be a value of @ref I2C_acknowledged_address
    INT32U ClockSpeed;          // I2Cʱ��Ƶ��, ����ֵ����С��400KHz.
}I2C_PARA;

/************************************************************************************/
// ������ƺ�����������
/************************************************************************************/
// I2C�����
#define CMD_I2C                  0  // ����I2C��������I2C���裬������ENABLE��DISABLE	
#define CMD_I2C_RST              4  // ��λI2C�Ĵ���Ϊ��ʼ״̬
#define CMD_I2C_CLOSE            5  // �ر�I2Cʱ��,Ҳ���ǹر�I2C����,����ʡ�� 

/************************************************************************************
//
//                 I2C����Ӳ����������
//
*************************************************************************************/

/***********************************************************************************
* Function: I2C_Init;
*
* Description: I2C��ʼ������;
*              
* Input:  id, I2C������ʶ��I2C1_ID��I2C2_ID��I2C3_ID;
*		  *pPara, I2C������ָ�� 
*
* Output: none;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   ��ʼ����ɣ�I2C�Ѿ�ʹ�ܿ�ʼ�������������I2C_Ctrl�ٴ�ʹ��;
************************************************************************************/
INT32S I2C_Init(INT8U I2Cx, I2C_PARA *pPara);

/***********************************************************************************
* Function: I2C_Read;
*
* Description: I2C���߶����ݺ���;
*              
* Input:  id, I2C������ʶ��I2C1_ID��I2C2_ID��I2C3_ID;
*         I2CAddr, I2C����ʶ���ַ;  
*         addr,�����ݵ���ʼ��ַ; 
*         *p, �������ݴ洢�ĵ�ַָ��;
*         len,Ҫ�������ݳ���;
*
* Output: none;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   ���I2C����������EEPROM��
*         I2CAddr��bit15=0,֧��24C01/02/04/08/16���ַ��8λ������; 
*         I2CAddr��bit15=1,֧��24C32/64/128/256���ַ��16λ������;
************************************************************************************/
INT32S I2C_Read(INT8U id, INT16U I2CAddr, INT16U addr, INT8U *p, INT16U len);

/***********************************************************************************
* Function: I2C_Write;
*
* Description: I2C����д���ݺ���;
*              
* Input:  id, I2C������ʶ��I2C1_ID��I2C2_ID��I2C3_ID;
*         I2CAddr, I2C����ʶ���ַ;
*         addr, д���ݵ���ʼ��ַ; 
*         *p, д�����ݴ洢�ĵ�ַָ��;
*         len,Ҫд�����ݳ���;
*
* Output: none;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   ���I2C����������EEPROM��
*         I2CAddr��bit15=0,֧��24C01/02/04/08/16���ַ��8λ������; 
*         I2CAddr��bit15=1,֧��24C32/64/128/256���ַ��16λ������;
************************************************************************************/
INT32S I2C_Write(INT8U id, INT16U I2CAddr, INT16U addr, INT8U *p, INT16U len);

/***********************************************************************************
* Function: I2C_Ctrl;
*
* Description: I2C�������;
* 
* Input:  id, I2C������ʶ��I2C1_ID��I2C2_ID��I2C3_ID;
*         Cmd,  I2C��������, ���¶��壺
*         CMD_I2C:       ����I2C��������I2C����, Para��ENABLE��DISABLE	
*         CMD_I2C_RST:   ��λI2C�Ĵ���Ϊ��ʼ״̬, ParaΪ0
*         CMD_I2C_CLOSE: �ر�I2Cʱ��,Ҳ���ǹر�I2C����,����ʡ��, ParaΪ0
*
*         Para��I2C������Ʋ���;
*
* Output: none;
*          		
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   none;
************************************************************************************/
INT32S  I2C_Ctrl(INT8U id, INT8U Cmd, INT32U Para);

#endif
