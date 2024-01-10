/************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: spi.h
* Project  : STM32F1XX/4XXϵ��ģ��������
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2020.8.24			
* Email:   EmbedARM@126.com
* 
* Description: ���ļ���SPI����Ӳ����������ͷ�ļ�;
*
* Others: none;
*
* Function List: 
*          1. INT32S SPI_Init(INT8U id, SPI_PARA *pPara);
*          2. INT32S SPI_Read(INT8U id, INT8U *p, INT32U len);
*          3. INT32S SPI_Write(INT8U id, INT8U *p, INT32U len);
*          4. INT8U  SPI_ReadWriteByte(INT8U id, INT8U val);
*          5. INT32S SPI_DMAWrite(INT8U id, INT8U *p, INT32U len, SPI_DMA_PARA *pPara);
*          6. INT32S SPI_DMARead(INT8U id, INT8U *p, INT32U len, SPI_DMA_PARA *pPara);
*          7. INT32S SPI_Ctrl(INT8U id, INT8U Cmd, INT32U Para);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 1.10
*	   Date:         2018.10.1
*      Modification: none
*
*************************************************************************************/
#ifndef __SPI_H 
#define __SPI_H 
/************************************************************************************/
// �����ⲿͷ�ļ�
/************************************************************************************/
#include "const.h"
/************************************************************************************/
// SPI��ʼ��������������
/************************************************************************************/
// SPI��������
#define SPI1_ID		0 
#define SPI2_ID    	1 
#define SPI3_ID    	2 


//SPI�������豸ģʽ
#define SPI_Mode_Master                 ((INT16U)0x0104) // ����ģʽ
#define SPI_Mode_Slave                  ((INT16U)0x0000) // �豸ģʽ

// SPI����λ��
#define SPI_DataSize_16b                ((INT16U)0x0800) // 16λ����λ
#define SPI_DataSize_8b                 ((INT16U)0x0000) // 8λ����λ

// SPI����֡��ʽ 
#define SPI_FirstBit_MSB                ((INT16U)0x0000) // �ȷ���MSB(��λ)
#define SPI_FirstBit_LSB                ((INT16U)0x0080) // �ȷ���LSB(��λ)

// SPIʱ�Ӽ���
#define SPI_CPOL_Low                    ((INT16U)0x0000) // ʱ�ӿ��е͵�ƽ
#define SPI_CPOL_High                   ((INT16U)0x0002) // ʱ�ӿ��иߵ�ƽ

// SPIʱ����λ 
#define SPI_CPHA_1Edge                  ((INT16U)0x0000) // ���ݲ����ӵ�һ��ʱ�ӱ��ؿ�ʼ(�½���)
#define SPI_CPHA_2Edge                  ((INT16U)0x0001) // ���ݲ����ӵڶ���ʱ�ӱ��ؿ�ʼ(������) 

// SPI_Slave_Select_management 
#define SPI_NSS_Soft                    ((INT16U)0x0200)
#define SPI_NSS_Hard                    ((INT16U)0x0000)

//SPI ȫ˫����ֻ���� 
#define SPI_2Lines_FullDuplex           ((INT16U)0x0000) // 2��, ȫ˫��
#define SPI_2Lines_RxOnly               ((INT16U)0x0400) // 2�ߣ�ֻ����

//#define SPI_Direction_1Line_Rx          ((INT16U)0x8000)
//#define SPI_Direction_1Line_Tx          ((INT16U)0xC000)
#define SPI_BaudRatePrescaler_2         ((INT16U)0x0000) // 2??
#define SPI_BaudRatePrescaler_4         ((INT16U)0x0008) // 4??
#define SPI_BaudRatePrescaler_8         ((INT16U)0x0010) // 8??
#define SPI_BaudRatePrescaler_16        ((INT16U)0x0018) // 16??
#define SPI_BaudRatePrescaler_32        ((INT16U)0x0020) // 32??
#define SPI_BaudRatePrescaler_64        ((INT16U)0x0028) // 64??
#define SPI_BaudRatePrescaler_128       ((INT16U)0x0030) // 128??
#define SPI_BaudRatePrescaler_256       ((INT16U)0x0038) // 256??



// SPI(�ܽ�)������ӳ�䶨��
#define SPI_REMAP_0       0    // SPIû����ӳ��
#define SPI_REMAP_1       1    // SPI��ӳ��
/*
// SPI1(�ܽ�)������ӳ�䶨��
#define SPI1_REMAP_0      0   // SPI1û����ӳ��, ��Ӧ�ܽŶ��壺
                              // SPI1_NSS: PA4; SPI1_SCK: PA5; SPI1_MISO: PA6; SPI1_MOSI: PA7;
                               
#define SPI1_REMAP_1      1   // SPI1��ӳ��, ��Ӧ�ܽŶ��壺
                              // SPI1_NSS: PA15; SPI1_SCK: PB3; SPI1_MISO: PB4; SPI1_MOSI: PB5;

// SPI2(�ܽ�)û�й�����ӳ�䶨��
#define SPI2_REMAP_0      0   // SPI2û����ӳ��, ��Ӧ�ܽŶ��壺
                              // SPI2_NSS: PB12; SPI2_SCK: PB13; SPI2_MISO: PB14; SPI2_MOSI: PB15;
                               
// SPI3(�ܽ�)������ӳ�䶨��
#define SPI3_REMAP_0      0   // SPI3û����ӳ��, ��Ӧ�ܽŶ��壺
                              // SPI3_NSS: PA15; SPI3_SCK: PB3; SPI3_MISO: PB4; SPI3_MOSI: PB5;
                               
#define SPI3_REMAP_1      1   // SPI3��ӳ��, ��Ӧ�ܽŶ��壺
                              // SPI3_NSS: PA4; SPI3_SCK: PC10; SPI3_MISO: PC11; SPI3_MOSI: PC12;
*/
/************************************************************************************************************************/
// ���±��ǹ���ģ��STM32F107VC,STM32F103VE,STM32F103ZE SPI1-3�ܽ�ӳ���, ��������ӳ�䷽ʽ����
/************************************************************************************************************************/
// SPI1-SPI3(�ܽ�)������ӳ���
/*
|-------------------------------------------------------------|
| ��Ŀ  |  ��ӳ��  | NSS�ܽ� | SCK�ܽ�  | MISO�ܽ� | MOSI�ܽ� |
|-------------------------------------------------------------|
|       |   û��   |   PA4   |   PA5    |    PA6   |   PA7    |
| SPI1  |-----------------------------------------------------|
|       |  ��ӳ��1 |   PA15  |   PB3    |    PB4   |   PB5    |
|-------------------------------------------------------------|
| SPI2  |   û��   |   PB12  |   PB13   |    PB14  |   PB15   |
|-------------------------------------------------------------|
|       |   û��   |   PA15  |   PB3    |    PB4   |   PB5    |
| SPI3  |-----------------------------------------------------|
|       |  ��ӳ��1 |   PA4   |   PC10   |    PC11  |   PC12   |
|-------------------------------------------------------------|
*/

/************************************************************************************************************************/
// ���±��ǹ���ģ��STM32F407VE SPI1-3�ܽ�ӳ���, �����ùܽŸ��üĴ�������
/************************************************************************************************************************/
// SPI1-SPI3(�ܽ�)����ӳ���
/*
|-------------------------------------------------------------|
| ��Ŀ  | ����ѡ�� | NSS�ܽ� | SCK�ܽ�  | MISO�ܽ� | MOSI�ܽ� |
|-------------------------------------------------------------|
|       |          |   PA4   |   PA5    |    PA6   |   PA7    |
| SPI1  |   AF5    |------------------------------------------|
|       |          |   PA15  |   PB3    |    PB4   |   PB5    |
|-------------------------------------------------------------|
|       |          |   PB12  |   PB13   |    PB14  |   PB15   |
| SPI2  |   AF5    |------------------------------------------|
|       |          |   PB9   |   PB10   |    PC2   |   PC3    |
|-------------------------------------------------------------|
|       |          |   PA15  |   PB3    |    PB4   |   PB5    |
| SPI3  |   AF6    |------------------------------------------|
|       |          |   PA4   |   PC10   |    PC11  |   PC12   |
|-------------------------------------------------------------|
*/

// SPI�ܽŲ����ṹ 
typedef struct
{
    INT8U  Remap;       // SPI���Ź�����ӳ��
    INT8U  SCK;         // SPI_SCK�ܽ�
    INT8U  MISO;        // SPI_MOSI�ܽ�
    INT8U  MOSI;        // SPI_MISO�ܽ�
    INT8U  NSS;         // SPI_NSS�ܽ�
}SPI_PIN;

// ���üĴ�������, ������2�����÷�ʽ: ֱ�Ӹ�reg��ֵ���߸�����b.xλ��ֵ
typedef union 
{
    INT16U   reg;
    struct
    {
        INT16U CPHA:                1; // ʱ����λ: 0,���ݲ����ӵ�һ��ʱ�ӱ��ؿ�ʼ(�½���); 1, ���ݲ����ӵڶ���ʱ�ӱ��ؿ�ʼ(������) 
        INT16U CPOL:                1; // ʱ�Ӽ���: 0,ʱ�ӿ��е͵�ƽ; 1,ʱ�ӿ��иߵ�ƽ;
        INT16U Mode:                1; // ���豸�ʹ��豸ģʽѡ��: 0, ����Ϊ���豸; 1,����Ϊ���豸
        INT16U BaudRatePrescaler:   3; // ��Ƶϵ������: 0,2��Ƶ; 1,4��Ƶ; 2,8��Ƶ; 3,16��Ƶ; 4,32��Ƶ; 5,64��Ƶ; 6,128��Ƶ; 7,256��Ƶ;
        INT16U SPE:                 1; // SPIʹ��: 0,�ر�SPI; 1, ʹ��SPI 
        INT16U Direction:           1; // �ȷ��͸�λ�͵�λѡ��: 0,�ȷ���MSB(��λ); 1,�ȷ���LSB(��λ)
        INT16U SSI:                 1; // �ڲ����豸ѡ��, Ĭ��Ϊ0;
        INT16U SSM:                 1; // ������豸ѡ��, Ĭ��Ϊ0;
        INT16U RxOnly:              1; // ֻ��������, Ĭ��Ϊ0(ȫ˫��)��SPI_2Lines_FullDuplex �� SPI_2Lines_RxOnly
        INT16U DataSize:            1; // ����λ��ѡ��SPI_DataSize_16b �� SPI_DataSize_8b
        INT16U CRCNext:             1; // ��һ������CRC, Ĭ��Ϊ0
        INT16U CRCEN:               1; // CRCУ��ʹ��, Ĭ��Ϊ0
        INT16U BIDIOE:              1; // ˫��ģʽ�����ʹ��, Ĭ��Ϊ0: 0: �����ֹ(ֻ��ģʽ), 1:���ʹ��(ֻ��ģʽ)
        INT16U BIDIMODE:            1; // ˫������ģʽʹ��, Ĭ��0: 0: ѡ��˫��ģʽ, 1:ѡ����ģʽ
    }b;
} SPI_CR1_TypeDef;

// SPI����֡��ʽ 
#define SPI_FirstBit_MSB                ((INT16U)0x0000) // �ȷ���MSB(��λ)
#define SPI_FirstBit_LSB                ((INT16U)0x0080) // �ȷ���LSB(��λ)

// SPIʱ�Ӽ���
#define SPI_CPOL_Low                    ((INT16U)0x0000) // ʱ�ӿ��е͵�ƽ
#define SPI_CPOL_High                   ((INT16U)0x0002) // ʱ�ӿ��иߵ�ƽ

// SPIʱ����λ 
#define SPI_CPHA_1Edge                  ((INT16U)0x0000) // ���ݲ����ӵ�һ��ʱ�ӱ��ؿ�ʼ(�½���)
#define SPI_CPHA_2Edge                  ((INT16U)0x0001) // ���ݲ����ӵڶ���ʱ�ӱ��ؿ�ʼ(������) 

// ������־Flag����
#define SPI_ISRHOOK_FLAG  0x0001  // ����ʹ�ܹ��Ӻ�����־
#define SPI_RXDMA_FLAG    0x0002  // RX����DMAʹ�ܱ�־
#define SPI_TXDMA_FLAG    0x0004  // TX����DMAʹ�ܱ�־;

// void (* pISRHook) (INT32U flag) ��flag��־


// SPI�����ṹ
typedef struct
{
    INT16U Flag;                // ������־
    SPI_PIN Pin;                // SPI�ܽ� 
    SPI_CR1_TypeDef cfg;        // SPI���ò���
    INT8U   CRCPolynomial;      // CRC����ʽ
    INT8U   DmaID;              // DMA ID
    INT8U   TXDmaCh;            // TX DMA ͨ��
    INT8U   RXDmaCh;            // RX DMA ͨ��
    void (* pISRHook) (INT32U flag); // SPI�жϹ��Ӻ���, ��DMA��ʽ��дʱ�Ƿ�����ģʽ�������ͨ����������ж��Ƿ�д����ɣ�
                                     // ������ģʽ���Բ���, ����Ϊ0
}SPI_PARA;


typedef struct
{
    INT16U Flag;                // ������־, ���޶��壬Ĭ��0
    INT16U TimeOut;             // ���������ʱ, ��λms
}SPI_DMA_PARA;
 
/************************************************************************************/
// ������ƺ�����������
/************************************************************************************/
// SPIʱ�ӷ�Ƶϵ��
#define SPI_DIVCLK_2         ((INT16U)0x0000)   // 2��Ƶ
#define SPI_DIVCLK_4         ((INT16U)0x0008)	// 4��Ƶ
#define SPI_DIVCLK_8         ((INT16U)0x0010)	// 8��Ƶ
#define SPI_DIVCLK_16        ((INT16U)0x0018)	// 16��Ƶ
#define SPI_DIVCLK_32        ((INT16U)0x0020)	// 32��Ƶ
#define SPI_DIVCLK_64        ((INT16U)0x0028)	// 64��Ƶ
#define SPI_DIVCLK_128       ((INT16U)0x0030)	// 128��Ƶ
#define SPI_DIVCLK_256       ((INT16U)0x0038)	// 256��Ƶ

// ʱ����λģʽ
#define SPI_CKMODE0  0	// CPOL = 0, CPHA = 0: ʱ�ӿ��е͵�ƽ, ���ݲ����ӵ�һ��ʱ�ӱ��ؿ�ʼ(������)  
#define SPI_CKMODE1  1	// CPOL = 0, CPHA = 1��ʱ�ӿ��е͵�ƽ, ���ݲ����ӵڶ���ʱ�ӱ��ؿ�ʼ(�½���)  
#define SPI_CKMODE2  2	// CPOL = 1, CPHA = 0��ʱ�ӿ��иߵ�ƽ, ���ݲ����ӵ�һ��ʱ�ӱ��ؿ�ʼ(�½���)  
#define SPI_CKMODE3  3	// CPOL = 1, CPHA = 1��ʱ�ӿ��иߵ�ƽ, ���ݲ����ӵڶ���ʱ�ӱ��ؿ�ʼ(������)   

// SPI ���������
#define CMD_SPI_ENA                    0  // ʹ��SPI����
#define CMD_SPI_DIS                    1  // ����SPI����
#define CMD_SPI_DIVCLK	               2  // ����ʱ�ӷ�Ƶϵ��
#define CMD_SPI_CKMODE	               3  // ʱ����λģʽ��Para������Ϊ0,1,2,3
#define CMD_SPI_RST                    4  // ��λSPI�Ĵ���Ϊ��ʼ״̬
#define CMD_SPI_CLOSE                  5  // �ر�SPIʱ��,Ҳ���ǹر�SPI����,����ʡ�� 

/*************************************************************************************/
//
// 				    SPI������Ӳ��������������
//
/*************************************************************************************/

/***********************************************************************************
* Function: SPI_Init;
*
* Description: SPI��ʼ������;
* 
* Input:  id, SPIʶ���(SPI1_ID,SPI2_ID,SPI3_ID);
*         *pPara, SPI��ʼ������ָ��;
*
* Output: none;
*          		
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   ��ʼ����ɣ�SPI�Ѿ�ʹ�ܿ�ʼ�������������SPI_Ctrl�ٴ�ʹ��;
*         �������������ʼ����SCK/MOSI/MISO, ����SPIƬѡ�ź�GPIO�û����г�ʼ��
************************************************************************************/
INT32S SPI_Init(INT8U id, SPI_PARA *pPara);

/***********************************************************************************
* Function: SPI_Read;
*
* Description: SPI���߶����ݺ���;
*              
* Input:  id,SPIʶ���(SPI1_ID,SPI2_ID,SPI3_ID);
*         *p, �������ݴ洢�ĵ�ַָ��; 
*         len,Ҫ�������ݳ���;
*
* Output: none;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   none;
************************************************************************************/
INT32S SPI_Read(INT8U id, INT8U *p, INT32U len);

/***********************************************************************************
* Function: SPI_DMARead;
*
* Description: SPI��������DMA�����ݺ���;
*              
* Input:  id, SPIʶ���(SPI1_ID,SPI2_ID,SPI3_ID);
*         *p, �������ݴ洢�ĵ�ַָ��; 
*         len,Ҫ�������ݳ���;
*         pPara, ����������  
*
* Output: none;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   none;
************************************************************************************/
INT32S SPI_DMARead(INT8U id, INT8U *p, INT32U len, SPI_DMA_PARA *pPara);

/***********************************************************************************
* Function: _SPI_Write;
*
* Description: SPI����д���ݺ���;
*              
* Input:  id,SPIʶ���(SPI1_ID,SPI2_ID,SPI3_ID);
*         *p, д�����ݵĴ洢�ĵ�ַָ��; 
*         len,Ҫд�����ݳ���;
*
* Output: none;
*
* Return: ֻ�ܷ���ERR_TRUE;
*
* Note:   none;
************************************************************************************/
INT32S SPI_Write(INT8U id, INT8U *p, INT32U len);

/***********************************************************************************
* Function: SPI_DMAWrite;
*
* Description: SPI��������DMAд���ݺ���;
*              
* Input:  id, SPIʶ���(SPI1_ID,SPI2_ID,SPI3_ID);
*         *p, д�����ݵĴ洢�ĵ�ַָ��; 
*         len,Ҫд�����ݳ���;
*         pPara, д��������  
*
* Output: none;
*
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   none;
************************************************************************************/
INT32S SPI_DMAWrite(INT8U id, INT8U *p, INT32U len, SPI_DMA_PARA *pPara);

/***********************************************************************************
* Function: SPI_ReadWriteByte;
*
* Description: SPI���߶�дһ���ֽ����ݺ���;
*              
* Input:  id,SPIʶ���(SPI1_ID,SPI2_ID,SPI3_ID);
*         val, д�������; 
*
* Output: none;
*
* Return: ���ض���������;
*
* Note:   none;
************************************************************************************/
INT8U SPI_ReadWriteByte(INT8U id, INT8U val);

/***********************************************************************************
* Function: SPI_Ctrl;
*
* Description: SPI�������;
* 
* Input:  id, SPIʶ���(SPI1_ID,SPI2_ID,SPI3_ID);
*         Cmd,  SPI�������
*               CMD_SPI_ENA��   ʹ��SPI����, ParaΪ0
*�������������� CMD_SPI_DIS��   ʹ��SPI����, ParaΪ0��������������������
*               CMD_SPI_DIVCLK������ʱ�ӷ�Ƶϵ��, ParaΪSPI_DIVCLK_2~SPI_DIVCLK_256
*               CMD_SPI_CKMODE��ʱ����λģʽ��ParaΪ��SPI_CKMODE0~SPI_CKMODE3
*               CMD_SPI_RST��   ��λSPI�Ĵ���Ϊ��ʼ״̬, ParaΪ0
*               CMD_SPI_CLOSE�� �ر�SPIʱ��,Ҳ���ǹر�SPI����,����ʡ��, ParaΪ0 
*         Para, SPI������Ʋ���;
*
* Output: none;
*          		
* Return: ERR_TRUE, �����ɹ�; ����ֵ, �μ�const.h�д������;
*
* Note:   none;
************************************************************************************/
INT32S SPI_Ctrl(INT8U id, INT8U Cmd, INT32U Para);
  
#endif
/***********************************************************************************/
// �ļ�����
/***********************************************************************************/



