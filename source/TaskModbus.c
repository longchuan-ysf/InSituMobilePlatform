/************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: TastModbus.c
* Project  : STM32F1XX/4XXϵ��ģ�����
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.00
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: ���ļ���ModbusЭ��, ����ģʽ�ʹӻ�ģʽ��������;
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
// Modbus�ӻ�ģʽ����˵��
/************************************************************************************/
/*
// Modbus�ӻ�(�豸)ģʽ����: 

1. Modbus�ӻ��豸ģʽ, ����Ӧ�����ļ�����������:
    #define MODBUS_SLAVE_EN        1           // MODBUS�ӻ�ͨ��ʹ�ܣ�1, ʹ��;  0, �ر�;

    #define MODBUS_SLAVE_MODE      0           // MODBUS�ӻ�ͨ��ģʽ��0, RTU;  1, ASCII��; 
    #define MODBUS_SLAVE_CH        UART4_ID    // MODBUS�ӻ�ͨ��ͨ����0: UART1_ID, 1: UART2_ID, 2: UART3_ID, 3: UART4_ID, 4: UART5_ID; 
    #define MODBUS_SLAVE_ID        1           // MODBUS�ӻ�ͨ�ŵ�ַ��, ��Χ��1~255;

    #define MODBUS_COILS_BASEADDR 	  10000        // ��Ȧ�Ĵ�������ַ;
    #define MODBUS_DISINPUT_BASEADDR  10000        // ��ɢ�������Ĵ�������ַ;
    #define MODBUS_HOLDREG_BASEADDR   10000        // ���ּĴ�������ַ;
    #define MODBUS_INPUTREG_BASEADDR  10000        // ����Ĵ�������ַ;

    #define MODBUS_MAX_COILS       32          // MODBUS�ӻ������Ȧ����(��д,���ù�����:1,5,15);
    #define MODBUS_MAX_DISINPUT    32          // MODBUS�ӻ������ɢ������(ֻ��,���ù�����:2);
    #define MODBUS_MAX_HOLDREG     16          // MODBUS�ӻ���󱣳ּĴ���(��д,���ù�����:3,6,16,23)����;	 
    #define MODBUS_MAX_INPUTREG    16          // MODBUS�ӻ��������Ĵ���(ֻ��,���ù�����:4)����;

    #define MODBUS_DATA_LEN        64          // ����Э�黺��, Ĭ��64(���30���Ĵ�����д),�û����Ը���MODBUS_MAX_HOLDREG��MODBUS_MAX_INPUTREG�����ֵ��2���ټ�4����

2. Ӧ�÷�ʽ 
     (1) �ڴӻ�ͨ��ͨ��(MODBUS_SLAVE_CH)��ȡ����, ������Modbus_Proc()��������ModbusЭ�����;
         ע��: �ں���Modbus_Proc()�н���Э��, ��д�ļĴ�����vars.c�е�ModbusCoils[], ModbusDisInput[], ModbusHoldReg[],ModbusInputReg[]�Ĵ���;
         ��ʼ��ַĬ��Ϊ0; �����ʼ��ʼ��ַ��Ϊ0, ����Ҫ�������ļ����û���ַ: MODBUS_COILS_BASEADDR,MODBUS_DISINPUT_BASEADDR,MODBUS_HOLDREG_BASEADDR,MODBUS_INPUTREG_BASEADDR
         
     (2) ����Ӧ�ó���, ֻ��Ҫ����Ҫ������д���ȡModbusCoils[], ModbusDisInput[], ModbusHoldReg[],ModbusInputReg[]�Ĵ������ɣ�
         ������Բο���TaskIO.c��TaskADC.c�е�IO���������AD�ɼ���д��Modbus�Ĵ�������:
         DI������д��ModbusDisInput[]��, DO�����д��ModbusCoils[]��, AD����д�뵽ModbusInputReg[]��
     
     (3) ͨ�������Modbus����������Զ�д���ذ�Ĵ���
            
3. ͨ�����ڵ�������۲���; 

4. ע�⣺�������ռ�����ĸ�UART(RS232��RS485)�˿ڣ��뽫TaskUart.c�е���ӦUART���Գ���ȡ��;
*/

/************************************************************************************/
// Modbus����ģʽ(��д�豸�Ĵ���)����˵��
/************************************************************************************/
/*
1. Modbus����ģʽ, ����Ӧ�����ļ�����������:
    #define MODBUS_EN         1           // MODBUSͨ��ʹ�ܣ�1, ʹ��;  0, �ر�;
    #define MODBUS_MODE       0           // MODBUSͨ��ģʽ��0, RTU;  1, ASCII��; 
    #define MODBUS_CH         UART3_ID    // MODBUSͨ��ͨ����0: UART1_ID, 1: UART2_ID, 2: UART3_ID, 3: UART4_ID, 4: UART5_ID; 
    #define MODBUS_ID         1           // MODBUS�����豸��ͨ�ŵ�ַID, Ĭ��1 
    #define MODBUS_TIMEOUT    1000        // MODBUSͨ�ų�ʱʱ��, ��λms;

2. ���ݱ��ļ�������ȫ�ֱ����ж��壬���������Ŀ���в��ԣ�ע����ʱ��������UART3(RS232����RS485)�ӿ������û���Modbus RTUЭ���豸���߼����;

3. ע�⣺�������ռ�����ĸ�UART(RS232��RS485)�˿ڣ��뽫TaskUart.c�е���ӦUART���Գ���ȡ��;
*/

/************************************************************************************/
// �����ⲿͷ�ļ�
/************************************************************************************/
#include "config.h"
#if (TASK_MODBUS_EN == 1)
#include "Vars.h"
#include "UserVars.h"
#include "OSHook.h"
#include "STM32Fxxx.h"

/************************************************************************************/
// ������ȫ�ֱ�������
/************************************************************************************/
#if (MODBUS_EN > 0)
// ���ذ���ΪModbus����
#define REG_START_ADDR      0         // �Ĵ�����ʼ��ַ

// ���Գ�����������ѡ�� , ��ʹ������ѡ������1����0, ������ر���ز���
#define DIx_READ_EN         1         // ��ȡ�豸DI����������Ĵ���       
#define DOx_WRITE_EN        1         // д���豸D0����������Ĵ���
#define DOx_READ_EN         1         // ��ȡ�豸D0����������Ĵ���
#define AIx_READ_EN         1         // ��ȡ�豸ģ��������Ĵ��� 
#define HOLDREG_WRITE_EN    1         // д���豸���ּĴ���
#define HOLDREG_READ_EN     1         // ��ȡ�豸���ּĴ���
#define HOLDREG_READ_WRITE_EN   0     // ͬʱ��ȡд���豸���ּĴ���

// ��ȡ�Ĵ������ȶ���
#define DI_NUM              8         // �豸DI����
#define DO_NUM              8         // �豸DO����
#define AI_NUM              8         // �豸AI����
#define HOLDREG_NUM         8         // �豸���ּĴ�������

#if (DIx_READ_EN > 0)
INT8U  DI_Buf[(DI_NUM+7)/8];  // �豸DI����
#endif

#if ((DOx_WRITE_EN > 0)||(DOx_READ_EN>0))
INT8U  DO_Buf[(DO_NUM+7)/8];  // �豸DO����
#endif

#if (AIx_READ_EN > 0)
INT16U AI_Buf[AI_NUM];        // �豸AI����
#endif

#if ((HOLDREG_WRITE_EN >0 )||(HOLDREG_READ_EN >0 )||(HOLDREG_READ_WRITE_EN >0 ))
INT16U HoldReg_Buf[HOLDREG_NUM];  // �豸���ּĴ�������
#endif

#endif
/***********************************************************************************
* Function: App_TaskModbus;
*
* Description: �ӻ�MODBUSЭ�鴦������;
*              
* Input:  none;
*
* Return: none;
*
* Note:   ������UCOS-II����ϵͳ����;
************************************************************************************/
void App_TaskModbus(void *p_arg)
{	 

    INT32S flag, i, cnt;
    INT16U rUartLen, len;
	INT8U err, *pMEM;
    
    (void)p_arg;
    
     while(1)
     {
         UserVars.TaskRunStatus |= TASK_MODBUS_FLAG;    // ���ñ���������״̬��־
         Delay_ms(20);                                  // ��ʱ20ms
/**********************************************************************************************************/
// ���ư���ΪModbus�豸����
/**********************************************************************************************************/          
         #if (MODBUS_SLAVE_EN > 0)  // �ж�Modbus�ӻ�ģʽ�Ƿ�ʹ��
		 len = Uart_Ctrl(MODBUS_SLAVE_CH, CMD_UART_GetCharsRxBuf,0);// ��ȡ�������ݳ���
		 if ((len == rUartLen)&&(len>0))
		 {
              pMEM = (INT8U *)OSMalloc(len);  // �����ڴ�             
			  Uart_Read(MODBUS_SLAVE_CH, pMEM, len); // ��ȡ�������ݵ��ڴ�
              #if (DEBUG_APP_EN > 0)
              printf("AT+MODBUS=RX:");
              for (i=0; i<len; i++)
              {
                  printf("%02X ", *(pMEM+i));
              } 
              printf("\r\n");
              #endif
              flag = Modbus_Proc(MODBUS_SLAVE_CH, MODBUS_SLAVE_ID, pMEM, len, (MODBUS_PARA *)&ModbusPara.Flag); // Modbus���ݴ���
              OSFree(pMEM);                            // ע���ڴ� 
              #if (DEBUG_APP_EN > 0)
              if (flag == ERR_TRUE) 
              {                  
                  printf("AT+MODBUS=TX:");
                  pMEM = (INT8U *)&ModbusPara.pData->id;
                  for (i=0; i<ModbusData.len; i++)
                  {
                      printf("%02X ", *pMEM++);
                  } 
                  printf("\r\n");
              }
              else
              {
                  printf("AT+MODBUS=Э�����ʧ��\r\n");
              }
              #endif
              
	          rUartLen -= len;
		 }
		 else
		 {
			  rUartLen	= len;
		 }
         #endif

/**********************************************************************************************************/
// ���ư���ΪModbus��������
/**********************************************************************************************************/          		 
         #if (MODBUS_EN > 0)  // �ж�Modbus����ģʽ�Ƿ�ʹ��
         cnt++;  
         if ((cnt%150)==0)     // ÿ��3��ִ�� 
         {         
             #if (DIx_READ_EN == 1) // ��ȡ�豸DI����������Ĵ���               
             flag = Modbus_ReadDisInput(MODBUS_CH, MODBUS_ID, REG_START_ADDR, DI_NUM, DI_Buf, MODBUS_TIMEOUT); // ��������ɢ�����������������øú������Ͷ���ɢ���������� 
             if(flag == ERR_TRUE)
             {
                 printf("AT+MODBUS=DI:");
                 for(i=0;i<((DI_NUM+7)/8); i++)
                 {
                     printf(" %02X", DI_Buf[i]);
                 }
                 printf("\r\n");
             }
             else
             {
                 printf("AT+MODBUS=Read DI error: %d\r\n", flag);
             }
             #endif
              
             #if (AIx_READ_EN == 1) // ��ȡ�豸ģ��������Ĵ��� 
             flag = Modbus_ReadInputReg(MODBUS_CH, MODBUS_ID, REG_START_ADDR, AI_NUM, AI_Buf, MODBUS_TIMEOUT); // ����������Ĵ��������������øú������Ͷ�����Ĵ�������
             if(flag == ERR_TRUE)
             {
                 printf("AT+MODBUS=AI:");
                  for (i=0; i<AI_NUM; i++)
                  {
                       printf(" %04X", AI_Buf[i]);
                  }
                  printf("\r\n");
             }
             else
             {
                  printf("AT+MODBUS=Read AI error: %d\r\n", flag);
             }
             #endif
              
             #if (DOx_WRITE_EN == 1) // д���豸D0����������Ĵ���			  
              // д��DO1ֵ1(ON)
             flag = Modbus_WriteSingleCoil(MODBUS_CH,  MODBUS_ID, REG_START_ADDR+0, 1, MODBUS_TIMEOUT);  // ����д������Ȧ�����������øú�������д������Ȧ����
             if(flag == ERR_TRUE)
             {
                  printf("AT+MODBUS=Write DO1 OK\r\n");
             }
             else
             {
                  printf("AT+MODBUS=Write DO1 error: %d\r\n", flag);
             }
             
             // д��DO2ֵ0(OFF)
             flag = Modbus_WriteSingleCoil(MODBUS_CH,  MODBUS_ID, REG_START_ADDR+1, 0, MODBUS_TIMEOUT);  // ����д������Ȧ�����������øú�������д������Ȧ����
             if(flag == ERR_TRUE)
             {
                  printf("AT+MODBUS=Write DO2 OK\r\n");
             }
             else
             {
                  printf("AT+MODBUS=Write DO2 error: %d\r\n", flag);
             }
              
             // һ��д���DO
             for(i=0;i<((DO_NUM+7)/8); i++)  
             {
                 DO_Buf[i] = 0x55;
             }	 			  
             flag = Modbus_WriteMulCoils(MODBUS_CH, MODBUS_ID, REG_START_ADDR, DO_NUM, DO_Buf, MODBUS_TIMEOUT); // ���øú�������д�����Ȧ����
             if(flag == ERR_TRUE)
             {
                 printf("AT+MODBUS=Write DOx OK\r\n");
             }
             else
             {
                  printf("AT+MODBUS=Write DOx error: %d\r\n", flag);
             }
             #endif
              
             #if (DOx_READ_EN == 1) // ��ȡ�豸D0����������Ĵ���
             flag = Modbus_ReadCoils(MODBUS_CH, MODBUS_ID, REG_START_ADDR, DO_NUM, DO_Buf, MODBUS_TIMEOUT); // ��������Ȧ�����������øú������Ͷ���Ȧ����
             if(flag == ERR_TRUE)
             {
                  printf("AT+MODBUS=Read DO:");
                  for(i=0;i<((DO_NUM+7)/8); i++)
                  {
                      printf(" %02X", DO_Buf[i]);
                  }
                  printf("\r\n");
             }
             else
             {
                 printf("AT+MODBUS=Read DO error: %d\r\n", flag);
             }
             #endif

              
             #if (HOLDREG_WRITE_EN == 1) // д���豸���ּĴ���
              // д��ַ1�ı��ּĴ���: 0x55
             flag = Modbus_WriteSingleReg(MODBUS_CH, MODBUS_ID, 1, 0x55, MODBUS_TIMEOUT); // ���øú�������д�������ּĴ�������			  
             if(flag == ERR_TRUE)
             {
                  printf("AT+MODBUS=Write HoldReg OK\r\n");
             }
             else
             {
                  printf("AT+MODBUS=Write HoldReg error: %d\r\n", flag);
             }	
              
             // д������ּĴ���ֵ
             for(i=0;i<HOLDREG_NUM; i++) // �Ĵ������ó�ʼֵ
             {
                  HoldReg_Buf[i] = 0x55+i;
             }	 			  
             flag = Modbus_WriteMulReg(MODBUS_CH, MODBUS_ID, REG_START_ADDR, HOLDREG_NUM, HoldReg_Buf, MODBUS_TIMEOUT); // ���øú�������д����Ĵ�������
             if(flag == ERR_TRUE)
             {
                  printf("AT+MODBUS=Write MulReg OK\r\n");
             }
             else
             {
                  printf("AT+MODBUS=Write MulReg error: %d\r\n", flag);
             }
             #endif
           
             #if (HOLDREG_READ_EN == 1) // ��ȡ�豸���ּĴ���			   
             flag = Modbus_ReadHoldReg(MODBUS_CH,  MODBUS_ID, REG_START_ADDR, HOLDREG_NUM, HoldReg_Buf, MODBUS_TIMEOUT); // ���������ּĴ��������������øú������Ͷ����ּĴ�������
             if(flag == ERR_TRUE)
             {
                  printf("AT+MODBUS=Read HoldReg:");
                  for (i=0; i<HOLDREG_NUM; i++)
                  {
                       printf(" %04X", HoldReg_Buf[i]);
                  }
                  printf("\r\n");
             }
             else
             {
                  printf("AT+MODBUS=Read HoldReg error: %d\r\n", flag);
             }
             #endif
              
             #if (HOLDREG_READ_WRITE_EN == 1) // ͬʱ��ȡд���豸���ּĴ���	
             for(i=0;i<HOLDREG_NUM; i++)   // ��ʼ�����ּĴ���
             {
                  HoldReg_Buf[i] = 0xAA;
             }	 			  
             // д���ַ0��ʼд��HOLDREG_NUM�����ݣ��ٶ�����HOLDREG_NUM������
             flag = Modbus_ReadWriteMulReg(MODBUS_CH, MODBUS_ID, 0, HOLDREG_NUM, 0, HOLDREG_NUM, HoldReg_Buf, MODBUS_TIMEOUT); // ���øú�������д��Ĵ�������ִ�иú���ʱ����д��������
             if(flag == ERR_TRUE)
             {
                  printf("AT+MODBUS=ReadWrite MulReg OK\r\n");
             }
             else
             {
                  printf("AT+MODBUS=ReadWrite MulReg error: %d\r\n", flag);
             }
             #endif
         }
         #endif
     }
}	  
#endif
/***********************************************************************************/
// �ļ�����
/***********************************************************************************/



