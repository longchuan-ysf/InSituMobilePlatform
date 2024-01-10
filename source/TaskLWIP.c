/************************************************************************************
*  Copyright (c), 2004-2019, ������Ƕ���Ƶ������޹�˾
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: TastLWIP.c
* Project  : STM32F1XX/4XXϵ��ģ�����
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.00
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: ���ļ���������Э��ջLWIP����;
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
// ����˵��
/************************************************************************************/
/*
1. ����IP��ַ���˿ں�:
   �����IP(DSC_IP)��192.168.1.2, �˿ں�(DSC_PORT): 5001
   ���ذ�IP(LOCAL_IP)��192.168.1.3, �˿ں�(LOCAL_PORT): 5000
   ����ʵ����������������������޸�

2. �ͻ���(TCP)ģʽ������Է���(���ذ���Ϊ�ͻ����������ӷ������������):
(1) ����:
    #define TASK_LWIP_EN      	1	                // TCPIP�������� 0, �ر�; 1, ʹ������;
    #define LWIP_EN             TASK_LWIP_EN        // TCPIP(LWIP)Э��ջʹ�ܣ�1, ʹ��;  0, �ر�;
    #define LWIP_WKMODE		    LWIP_SOCKET_CLIENT  // LWIP_SOCKET_CLIENT  //LWIP_HTTP// ����ģʽ, ѡ��LWIP_SOCKET_CLIENT��LWIP_SOCKET_SERVER��LWIP_HTTP 
    #define LWIP_NETYPE			LWIP_NETYPE_TCP     // ͨ������, ѡ��LWIP_NETYPE_UDP��LWIP_NETYPE_TCP 
    #define LWIP_CONFIG_EN      1                   // ����ѡ��: 1, ��������������; 0, ��EEPROM�洢��Ϣ��������
    ������Ĭ������ 
(2) ��TCPIP���Թ��߽����˿ں�Ϊ5001�ķ���������������;
(3) ���벢�����������У����ذ���Ϊ�ͻ��˻��������ӷ�����;
(4) ��TCPIP���Թ��߿������ӵĹ��ذ��豸�����������ݲ���,  ���ذ��յ����ݻὫ����ԭ�����ط�����

3. ������(TCP)ģʽ������Է���(���ذ���Ϊ���������������Ϊ�ͻ����������ӹ��ذ�):
(1) ����:
    #define TASK_LWIP_EN      	1	                // TCPIP�������� 0, �ر�; 1, ʹ������;
    #define LWIP_EN             TASK_LWIP_EN        // TCPIP(LWIP)Э��ջʹ�ܣ�1, ʹ��;  0, �ر�;
    #define LWIP_WKMODE		    LWIP_SOCKET_CLIENT  //LWIP_SOCKET_CLIENT  // LWIP_HTTP// ����ģʽ, ѡ��LWIP_SOCKET_CLIENT��LWIP_SOCKET_SERVER��LWIP_HTTP 
    #define LWIP_NETYPE			LWIP_NETYPE_TCP     // ͨ������, ѡ��LWIP_NETYPE_UDP��LWIP_NETYPE_TCP 
    #define LWIP_CONFIG_EN      1                   // ����ѡ��: 1, ��������������; 0, ��EEPROM�洢��Ϣ��������
    ������Ĭ������ 
(2) ���벢�����������У����ذ彨����5000�˿ڵķ�����, ����������ȴ�����;
(3) ��TCPIP���Թ��߽����ͻ��˲����Ӷ˿ں�Ϊ5000�Ĺ��ذ������;
(4) ���ӳɹ���, ��TCPIP���Թ��߷������ݲ���, ���ذ��յ����ݻὫ����ԭ�����ؼ����

4. HTTP������ģʽ������Է���(���ذ���ΪHTTP���������������Ϊ�ͻ�����IE����):
(1) ����:
    #define TASK_LWIP_EN      	1	                // TCPIP�������� 0, �ر�; 1, ʹ������;
    #define LWIP_EN             TASK_LWIP_EN        // TCPIP(LWIP)Э��ջʹ�ܣ�1, ʹ��;  0, �ر�;
    #define LWIP_WKMODE		    LWIP_HTTP           //LWIP_SOCKET_CLIENT  // LWIP_HTTP// ����ģʽ, ѡ��LWIP_SOCKET_CLIENT��LWIP_SOCKET_SERVER��LWIP_HTTP 
    #define LWIP_NETYPE			LWIP_NETYPE_TCP     // ͨ������, ѡ��LWIP_NETYPE_UDP��LWIP_NETYPE_TCP 
    #define LWIP_CONFIG_EN      1                   // ����ѡ��: 1, ��������������; 0, ��EEPROM�洢��Ϣ��������
    ������Ĭ������ 
(2) ���벢�����������У����ذ彨����80�˿ڵ�HTTP������, ����������ȴ�����;
(3) ��IE, ����192.168.1.3, ���ʷ�����;

5. Modbus TCP ͨ�Ų���(���ذ���ΪModbus TCP������, �������Ϊ�ͻ��ˣ���Modbus Poll����������Ӳ���):
(1) ����:
    #define TASK_LWIP_EN      	1	                // TCPIP�������� 0, �ر�; 1, ʹ������;
    #define LWIP_EN             TASK_LWIP_EN        // TCPIP(LWIP)Э��ջʹ�ܣ�1, ʹ��;  0, �ر�;
    #define LWIP_WKMODE		    LWIP_SOCKET_SERVER  //LWIP_SOCKET_CLIENT  // LWIP_HTTP// ����ģʽ, ѡ��LWIP_SOCKET_CLIENT��LWIP_SOCKET_SERVER��LWIP_HTTP 
    #define LWIP_NETYPE			LWIP_NETYPE_TCP     // ͨ������, ѡ��LWIP_NETYPE_UDP��LWIP_NETYPE_TCP 
    
    
    ������Ĭ������ 
(2) ���벢�����������У����ذ彨����502�˿ڵķ�����, ����������ȴ�����;
(3) ��Modbus Poll���Թ���, ���Connection��ѡ��TCP/IP, IP Address��192.168.1.3, Port: 502,�������ӽ��в���;
(4) ע�⣺������ȫ�ֱ�������������ã�
          #define MODBUS_TCP_EN      1 // 1, ִ��Modbus TCP����ʹ��; 0, ִ�з�����ģʽ�������
    �ر�Modbus����      
          #define TASK_MODBUS_EN      0	  // MODBUS��������0, �ر�; 1, ʹ������;
*/


/************************************************************************************/
// �����ⲿͷ�ļ�
#include "config.h"	 
#if (TASK_LWIP_EN == 1)
#include "UserVars.h"
#include "ethernetif.h"
#include "api.h"
#include "tcpip.h"
#include "STM32Fxxx.h"
#include "vars.h"


/************************************************************************************/

/************************************************************************************/
// ������ȫ�ֱ�������
/************************************************************************************/
struct netif netif;

typedef enum
{
	TCPIP_INIT = 0,
	TCPIP_TASK,
	TCPIP_IDLE,
	TCPIP_WAITLINK,
}TCPIP_STATUS;

TCPIP_STATUS TCPIPStatus;

typedef enum
{
	C_INIT = 0,
	C_CONNECT,
	//C_CLOSE,
	//C_DISCONNECT,
	C_IDLE,
	//C_ISLINK,
	//C_ERROR
}Client_STATUS;

Client_STATUS CliStatus;


#include "lwip/opt.h"

#if LWIP_NETCONN

#include "lwip/sys.h"
#include "lwip/api.h"
/*-----------------------------------------------------------------------------------*/


void LwIP_Init(void)
{
  struct ip_addr ipaddr;
  struct ip_addr netmask;
  struct ip_addr gw;
  
  tcpip_init(NULL,NULL);	// TCP IPЭ��ջ��ʼ��

#if LWIP_DHCP
  ipaddr.addr = 0;
  netmask.addr = 0;
  gw.addr = 0;
#else
    IP4_ADDR(&ipaddr, UserVars.Para.LocalIP[0], UserVars.Para.LocalIP[1], UserVars.Para.LocalIP[2], UserVars.Para.LocalIP[3]);  // �趨����IP��ַ
    IP4_ADDR(&netmask, UserVars.Para.SubnetMask[0], UserVars.Para.SubnetMask[1], UserVars.Para.SubnetMask[2], UserVars.Para.SubnetMask[3]); // �趨��������
    IP4_ADDR(&gw, UserVars.Para.Gataway[0], UserVars.Para.Gataway[1], UserVars.Para.Gataway[2], UserVars.Para.Gataway[3]);      // �趨·������ַ
#endif
    //Set_MAC_Address((INT8U *)UserVars.Para.MACAddr);  // �趨MAC��ַ
    //UserVars.Para.MACAddr[0] = 1;
    //UserVars.Para.MACAddr[1] = 0;
    //UserVars.Para.MACAddr[2] = 0;
    //UserVars.Para.MACAddr[3] = 0;
    //UserVars.Para.MACAddr[4] = 0;
    //UserVars.Para.MACAddr[5] = 0;
    
    NET_Ctrl(CMD_NET_MACADDR, (INT32U)&UserVars.Para.MACAddr[0]);
    
    netif_init();
  /* - netif_add(struct netif *netif, struct ip_addr *ipaddr,
            struct ip_addr *netmask, struct ip_addr *gw,
            void *state, err_t (* init)(struct netif *netif),
            err_t (* input)(struct pbuf *p, struct netif *netif))
    
   Adds your network interface to the netif_list. Allocate a struct
  netif and pass a pointer to this structure as the first argument.
  Give pointers to cleared ip_addr structures when using DHCP,
  or fill them with sane numbers otherwise. The state pointer may be NULL.

  The init function pointer must point to a initialization function for
  your ethernet netif interface. The following code illustrates it's use.*/
  

  netif_add(&netif, &ipaddr, &netmask, &gw, NULL, &ethernetif_init, &tcpip_input);  // ��ʼ������
  //NET_Ctrl(CMD_NET_INT, 1);
  /*  Registers the default network interface.*/
  netif_set_default(&netif); // ע������ӿ�
  

#if LWIP_DHCP
  /*  Creates a new DHCP client for this interface on the first call.
  Note: you must call dhcp_fine_tmr() and dhcp_coarse_tmr() at
  the predefined regular intervals after starting the client.
  You can peek in the netif->dhcp struct for the actual DHCP status.*/
  dhcp_start(&netif);   // ����DHCP
#endif

  /*  When the netif is fully configured this function must be called.*/
   netif_set_up(&netif); 
}

/**
  * @brief  Called when a frame is received
  * @param  None
  * @retval None
  */





/**************************************************************************************
     �ͻ���(TCP)ģʽ����
***************************************************************************************/
#if ((LWIP_WKMODE == LWIP_SOCKET_CLIENT)&&(LWIP_NETYPE == LWIP_NETYPE_TCP)) // ����Ϊ�ͻ���TCPģʽ 
static void Client_TCP_Thread(void *arg)
{
    struct netconn *conn;
    struct netbuf *buf;
	struct ip_addr ipaddr;
    err_t err;
	char *data = NULL;
	INT16U len, i, n;
    INT8U DataBuf[32], DataBufLen;
    
	CliStatus = C_INIT; // �趨��ʼ״̬
    
	while (1)
	{
		switch (CliStatus)
		{
			 case C_INIT:
				if (TCPIPStatus == TCPIP_IDLE)
				{
                    #if (DEBUG_APP_EN == 1)
	                if (UserVars.Para.ATFlag&AT_NET_FLAG)
                    {
                       printf("AT+INFO=NET Client(TCP) Init\r\n");
	                }
                    #endif
					
					conn = netconn_new(NETCONN_TCP);    // ����һ���µ����ӱ�ʶ��
					if (conn != NULL)
                    {
                        conn->recv_timeout = 1000;          // ���ý��ճ�ʱ, ��λms
                        conn->send_timeout = 1000;          // ���÷��ͳ�ʱ, ��λms
                        netconn_bind(conn, NULL, UserVars.Para.LocalPort);  // �󶨱���IP��ַ����
                        CliStatus = C_CONNECT;
                    }
                    else
                    {
                        #if (DEBUG_APP_EN == 1)
                        if (UserVars.Para.ATFlag&AT_NET_FLAG)
                        {
                           printf("AT+ERROR=NET netconn_new error\r\n");
                        }
                        #endif                        
                        Delay_ms(3000);    
                    }
				 }
                 else
                 {
                     Delay_ms(1000);
                 }
				 break;
			 case C_CONNECT: 				
				//if (TCPIPStatus == TCPIP_IDLE) // Modify 2020.8.19
                //{
                    IP4_ADDR(&ipaddr, UserVars.Para.DscIP[0], UserVars.Para.DscIP[1], UserVars.Para.DscIP[2], UserVars.Para.DscIP[3]); // �趨������IP
                    err = netconn_connect(conn, &ipaddr, UserVars.Para.DscPort); // ���ӷ�����IP
                    if (err == ERR_OK)  // ���ӳɹ�
                    {
                         CliStatus = C_IDLE;
                         #if (DEBUG_APP_EN == 1)
                         if (UserVars.Para.ATFlag&AT_NET_FLAG)
                         {
                            printf("AT+INFO=NET Client(TCP) connect OK\r\n");
                         }
                         #endif 					 									 
                    }
                    else  // ����ʧ��
                    { 
                         CliStatus = C_IDLE;
                         #if (DEBUG_APP_EN == 1)
                         if (UserVars.Para.ATFlag&AT_NET_FLAG)
                         {
                            printf("AT+ERROR=NET Client(TCP) connect error: %s\r\n", lwip_strerr(err));
                         }
                         #endif                      	
                         netconn_close(conn);	 // �ر����ӱ�ʶ��
                         netconn_delete(conn);	 // ɾ�����ӱ�ʶ��
                         CliStatus = C_INIT;
                         Delay_ms(1000);
                    }
                //}
				break;
			 case C_IDLE:					
                if (TCPIPStatus == TCPIP_IDLE)
                {	
                    err = netconn_recv(conn, &buf); // �������ݺ���
                    if (err == ERR_OK) // ���ճɹ�
                    {
                        netbuf_first(buf); // �ƶ�����ָ��
                        do 
                        {
                            netbuf_data(buf, &data, &len); // ��ȡ����ָ��ͳ���: data������ָ��, len�����ݳ���									
                            #if (DEBUG_APP_EN == 1)
                            if (UserVars.Para.ATFlag&AT_NET_FLAG)
                            {
                                printf("AT+NET=RH,%d,", len);
                                /*
                                if (len>16)
                                {
                                    n=16;
                                }
                                else
                                {
                                    n=len;
                                }
                                */                            
                                for(i=0; i<(len-1); i++)
                                {
                                    printf("%02x ", *(data+i));
                                }
                                printf("%02x\r\n", *(data+i));    
                            }
                            #endif 
                               
                            
                            //********************************************************************
                            // ���緢������   
                            if (len<32)           // ���÷������ݳ���
                            {
                                DataBufLen = len;
                            }
                            else
                            {
                                DataBufLen = 32;
                            }
                            
                            for(i=0; i<DataBufLen; i++)  // ��ֵ
                            {
                                DataBuf[i] = data[i];
                            }
                            
                            err = netconn_write(conn, DataBuf, DataBufLen, NETCONN_COPY); // ��������
                            if (err != ERR_OK) 
                            {   
                                #if (DEBUG_APP_EN == 1)
                                if (UserVars.Para.ATFlag&AT_NET_FLAG)
                                {
                                   printf("AT+ERROR=NET netconn_write error: %s\r\n", lwip_strerr(err));
                                }
                                #endif 
                            }                                    
                            //********************************************************************
 
                        }while (netbuf_next(buf) >= 0);
                        netbuf_delete(buf);
                    }
                    else	 
                    {
                        if (err != ERR_TIMEOUT)
                        {
                            #if (DEBUG_APP_EN == 1)
                            if (UserVars.Para.ATFlag&AT_NET_FLAG)
                            {
                                printf("AT+ERROR=NET Client error: %s\r\n", lwip_strerr(err));
                            }
                            #endif                             
                            netconn_close(conn);	 
                            netconn_delete(conn);														
                            CliStatus = C_INIT; 						
                        }
                    }
                }	
                else
                {
                    #if (DEBUG_APP_EN == 1)
                    if (UserVars.Para.ATFlag&AT_NET_FLAG)
                    {
                        printf("AT+INFO=NET TCPIPStatus != TCPIP_IDLE\r\n");
                    }
                    #endif                             
                    netconn_close(conn);
                    netconn_delete(conn); 
                    CliStatus = C_INIT;
                }
				break;
			 /*case C_ISLINK:
				if (TCPIPStatus == TCPIP_IDLE)
				{
					printf("TCPIPStatus == TCPIP_IDLE\r\n");
					CliStatus = C_INIT;
				}
				else
				{
					Delay_ms(1000);
				}
				break;
*/
			 default:
					break;
		}
	}  
}
#endif
/**************************************************************************************
     �ͻ���(UDP)ģʽ����
***************************************************************************************/
#if ((LWIP_WKMODE == LWIP_SOCKET_CLIENT)&&(LWIP_NETYPE == LWIP_NETYPE_UDP)) // ����Ϊ�ͻ���UDPģʽ 
static void Client_UDP_Thread(void *arg)
{
    struct netconn *conn;
	err_t err;
	struct netbuf *buf, *SendBuf;
    struct ip_addr ipaddr;
    char *data = NULL;
    char *sendata = NULL;
	INT8U DataBuf[32], DataBufLen;
	INT16U len, i;

	CliStatus = C_INIT; // �趨��ʼ״̬
	while (1)
	{
		switch (CliStatus)
		{
			 case C_INIT:
				if (TCPIPStatus == TCPIP_IDLE)
				{
                    #if (DEBUG_APP_EN == 1)
                    if (UserVars.Para.ATFlag&AT_NET_FLAG)
                    {
                        printf("AT+INFO=NET Client Init\r\n");
                    }
                    #endif 
					
					conn = netconn_new(NETCONN_UDP);    // ����һ���µ����ӱ�ʶ��
					if (conn != NULL)
                    {
                        conn->recv_timeout = 1000;          // ���ý��ճ�ʱ					
                        netconn_bind(conn, NULL, UserVars.Para.LocalPort);  // �󶨱���IP��ַ����
                        CliStatus = C_CONNECT;
                    }
                    else
                    {
                        #if (DEBUG_APP_EN == 1)
                        if (UserVars.Para.ATFlag&AT_NET_FLAG)
                        {
                            printf("AT+ERROR=NET netconn_new error\r\n");
                        }
                        #endif                    
                        Delay_ms(3000);    
                    }   
				 }
                 else
                 {
                     Delay_ms(1000);  // ��ʱ1��   
                 }
				 break;
			 case C_CONNECT: 				
				IP4_ADDR(&ipaddr, UserVars.Para.DscIP[0], UserVars.Para.DscIP[1], UserVars.Para.DscIP[2], UserVars.Para.DscIP[3]); // �趨������IP
				err = netconn_connect(conn, &ipaddr, UserVars.Para.DscPort); // ���ӷ�����IP
				if (err == ERR_OK)  // ���ӳɹ�
				{
					CliStatus = C_IDLE;
                    #if (DEBUG_APP_EN == 1)
                    if (UserVars.Para.ATFlag&AT_NET_FLAG)
                    {
                        printf("AT+INFO=NET Client(UDP) connect OK\r\n");
                    }
                    #endif 							 
					
                    //  UDPģʽ��һ�ν��������ȷ���һ�����ݸ�������, �÷��������������豸
                    SendBuf = netbuf_new();               // ����buf 
                    sendata = netbuf_alloc(SendBuf,10);   // �����ڴ�10�ֽ�
                    for (i=0; i<10; i++)                  // ��ֵ
                    {
                        sendata[i] = i+'0';
                    }
                    netconn_send(conn,SendBuf);           // ��������
                    netbuf_delete(SendBuf);					 
				}
				else  // ����ʧ��
				{ 
                     #if (DEBUG_APP_EN == 1)
                     if (UserVars.Para.ATFlag&AT_NET_FLAG)
                     {
                        printf("AT+ERROR=NET Client udp connect error: %s\r\n", lwip_strerr(err));	
                     }
                     #endif 
                     
					 netconn_close(conn);	 // �ر����ӱ�ʶ��
					 netconn_delete(conn);	 // ɾ�����ӱ�ʶ��
					 CliStatus = C_INIT;
					 Delay_ms(1000);
				}
				break;			 
			 case C_IDLE:					
                err = netconn_recv(conn, &buf);  // ���շ���������������
                if (err == ERR_OK) // ���ճɹ�
                {
                    #if (DEBUG_APP_EN == 1)
                    if (UserVars.Para.ATFlag&AT_NET_FLAG)
                    {
                       printf("AT+INFO=NET Client receive data\r\n");
                    }
                    #endif 
                    
                    netbuf_first(buf);
                    do 
                    {
                        netbuf_data(buf, &data, &len);  // ������
                        #if (DEBUG_APP_EN == 1)
                        if (UserVars.Para.ATFlag&AT_NET_FLAG)
                        {
                           printf("AT+NET=RH,%d,", len);
                            /*
                            if (len>16)
                            {
                                n=16;
                            }
                            else
                            {
                                n=len;
                            }*/

                            for(i=0; i<(len-1); i++)
                            {
                                printf("%02x ", *(data+i));
                            }
                            printf("%02x\r\n", *(data+i)); 
                        }
                        #endif                               
                        //********************************************************************
                        // ���緢������
                        SendBuf = netbuf_new();               // ������������SendBuf 
                        sendata = netbuf_alloc(SendBuf,len);  // �����ڴ�len�ֽ�
                        for (i=0; i<len; i++)                 // ���յ������ݷŵ�����sendata��
                        {
                            sendata[i] = data[i];
                        }
                        netconn_send(conn,SendBuf);           // ��������
                        netbuf_delete(SendBuf);               // ɾ��SendBuf
                        //*********************************************************************
                    } while (netbuf_next(buf) >= 0);
                    netbuf_delete(buf);
                }                   
				break;
			 default:
					break;
		}
	}  
}
#endif
/**************************************************************************************
     �����ģʽ����
***************************************************************************************/
static void tcpecho_thread(void *arg)
{
  struct netconn *conn, *newconn;
  err_t err;
  struct netbuf *buf, *SendBuf;
  char *data;
  u8_t DataBuf[32], DataBufLen;
  u16_t len, i, n;
  u32_t flag;
    
  LWIP_UNUSED_ARG(arg);
    
  conn = netconn_new(NETCONN_TCP);  // ����һ���µ����ӱ�ʶ�� /* Create a new connection identifier. */
  conn->recv_timeout = 100;         // ���ý��ճ�ʱ 
  #if (MODBUS_TCP_EN == 1)          // Modbus TCP����
  netconn_bind(conn, NULL, 502);    // �󶨱��ض˿ں�502 /* Bind connection to well known port number 7. */
  #else                             // ִ�з�����ģʽ�������
  netconn_bind(conn, NULL, UserVars.Para.LocalPort); // �󶨱��ض˿ں� /* Bind connection to well known port number 7. */
  #endif
  netconn_listen(conn);             //���ӽ������ģʽ  /* Tell connection to go into listening mode. */

  while (1) 
  {
    	/* Grab new connection. */
    	while (netconn_accept(conn, &newconn) != ERR_OK);  // ERR_TIMEOUT    
		newconn->recv_timeout = 1000;
		while (TCPIPStatus == TCPIP_IDLE)
        {
			err = netconn_recv(newconn, &buf);  // �������ݺ���
			if (err == ERR_OK)  // ���ճɹ�
			{
                netbuf_first(buf); // �ƶ�����ָ��
				do 
				{
		            netbuf_data(buf, &data, &len); 
                    #if (DEBUG_APP_EN == 1)
                    if (UserVars.Para.ATFlag&AT_NET_FLAG)
                    {
                        printf("AT+NET=RH,%d,", len);
                        /*
                        if (len>16)
                        {
                            n=16;
                        }
                        else
                        {
                            n=len;
                        }*/                            
                        for(i=0; i<(len-1); i++)
                        {
                            printf("%02x ", *(data+i));
                        }
                        printf("%02x\r\n", *(data+i)); 
                    }
                    #endif
                    

                        
                    //********************************************************************
                    // ���緢������               
                    #if (MODBUS_TCP_EN == 1)   // Modbus TCP����
                    flag = Modbus_Proc(MODBUS_TCP_ID, MODBUS_SLAVE_ID, &data[6], len-6, (MODBUS_PARA *)&ModbusPara.Flag); // �ӵ��������ݿ�ʼ��Modbus���ݣ����ô������
                    if (flag == ERR_TRUE) // ������ȷ
                    {
                        if (ModbusPara.pData->Flag&MODBUS_OK_FLAG) // ��ɱ�־
                        {
                             ModbusPara.pData->Flag = 0;
                             ModbusPara.pData->swcl[0] = data[0]; // MODBUS TCP: ���ﴦ���ʶ��
                             ModbusPara.pData->swcl[1] = data[1];
                             ModbusPara.pData->xyid[0] = data[2]; // MODBUS TCP: Э���ʶ��
                             ModbusPara.pData->xyid[1] = data[3];
                            
                             err = netconn_write(newconn,  &ModbusPara.pData->swcl[0], ModbusPara.pData->len, NETCONN_COPY); // ��������
                             if (err != ERR_OK) 
                             {
                                 #if (DEBUG_APP_EN == 1)
                                 if (UserVars.Para.ATFlag&AT_NET_FLAG)
                                 {
                                     printf("AT+ERROR=NET tcpecho: netconn_write: error \"%s\"\n", lwip_strerr(err));
                                 }
                                 #endif                                 
                             }
                         }
                    }
                    #else                 // ִ�з�����ģʽ������� 
                    if (len<32)           // ���÷������ݳ���
                    {
                        DataBufLen = len;
                    }
                    else
                    {
                        DataBufLen = 32;
                    }
                    
                    for(i=0; i<DataBufLen; i++)  // ��ֵ
                    {
                        DataBuf[i] = data[i];
                    }
                    
                    err = netconn_write(newconn, data, len, NETCONN_COPY); // ��������
		            if (err != ERR_OK) 
					{
                         #if (DEBUG_APP_EN == 1)
                         if (UserVars.Para.ATFlag&AT_NET_FLAG)
                         {
                              printf("AT+ERROR=NET tcpecho: netconn_write: error \"%s\"\n", lwip_strerr(err));
                         }
                         #endif                                 
		            }
                    #endif
                    //********************************************************************
		        } while (netbuf_next(buf) >= 0);
	        	netbuf_delete(buf);
			}
			else
			{			    
                if (err != ERR_TIMEOUT)
				{
                    #if (DEBUG_APP_EN == 1)
                    if (UserVars.Para.ATFlag&AT_NET_FLAG)
                    {
                        printf("AT+ERROR=LWIP ERR = %s\r\n", lwip_strerr(err));
                    }
                    #endif                     
					break; 
				}
			}
        }
        /*printf("Got EOF, looping\n");*/ 
        /* Close connection and discard connection identifier. */
        netconn_close(newconn);
        netconn_delete(newconn);
  }
}
/*-----------------------------------------------------------------------------------*/

/**************************************************************************************
     HTTP�����ģʽ����
***************************************************************************************/

#ifndef HTTPD_DEBUG
#define HTTPD_DEBUG         LWIP_DBG_ON
#endif

const static char http_html_hdr[] = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n";
const static char http_index_html[] = "<html><head><title>Congrats!</title></head><body><h1>��ӭʹ�ñ�����Ƕ���Ƶ������޹�˾��Ʒ��lwIP HTTP server!</h1><p>This is a small test page, served by httpserver-netconn.</body></html>";

/** Serve one HTTP connection accepted in the http thread */
static void
http_server_netconn_serve(struct netconn *conn)
{
  struct netbuf *inbuf;
  char *buf;
  u16_t buflen;
  err_t err;
  
  /* Read the data from the port, blocking if nothing yet there. 
   We assume the request (the part we care about) is in one netbuf */
  err = netconn_recv(conn, &inbuf);
  
  if (err == ERR_OK) {
    netbuf_data(inbuf, (void**)&buf, &buflen);
    
    /* Is this an HTTP GET command? (only check the first 5 chars, since
    there are other formats for GET, and we're keeping it very simple )*/
    if (buflen>=5 &&
        buf[0]=='G' &&
        buf[1]=='E' &&
        buf[2]=='T' &&
        buf[3]==' ' &&
        buf[4]=='/' ) {
      
      /* Send the HTML header 
             * subtract 1 from the size, since we dont send the \0 in the string
             * NETCONN_NOCOPY: our data is const static, so no need to copy it
       */
      netconn_write(conn, http_html_hdr, sizeof(http_html_hdr)-1, NETCONN_NOCOPY);
      
      /* Send our HTML page */
      netconn_write(conn, http_index_html, sizeof(http_index_html)-1, NETCONN_NOCOPY);
    }
  }
  /* Close the connection (server closes in HTTP) */
  netconn_close(conn);
  
  /* Delete the buffer (netconn_recv gives us ownership,
   so we have to make sure to deallocate the buffer) */
  netbuf_delete(inbuf);
}

/** The main function, never returns! */
static void
http_server_netconn_thread(void *arg)
{
  struct netconn *conn, *newconn;
  err_t err;
  LWIP_UNUSED_ARG(arg);
  
  /* Create a new TCP connection handle */
  conn = netconn_new(NETCONN_TCP);
  LWIP_ERROR("http_server: invalid conn", (conn != NULL), return;);
  
  /* Bind to port 80 (HTTP) with default IP address */
  netconn_bind(conn, NULL, 80);
  
  /* Put the connection into LISTEN state */
  netconn_listen(conn);
  
  do {
    err = netconn_accept(conn, &newconn);
    if (err == ERR_OK) {
      http_server_netconn_serve(newconn);
      netconn_delete(newconn);
    }
  } while(err == ERR_OK);
  LWIP_DEBUGF(HTTPD_DEBUG,
    ("http_server_netconn_thread: netconn_accept received error %d, shutting down",
    err));
  netconn_close(conn);
  netconn_delete(conn);
}

 #endif /* LWIP_NETCONN */


#if ((IAP_EN > 0)&&(IAP_TFTP_EN > 0))  // ����TFTPЭ����¹̼�ʹ��
#if (IAP_FLASH == 3)             // ���¹̼��洢��ѡ��0,2: ��Ч; 1(IAP_B_ID), B��FLASH;  3(IAP_C_ID), C��FLASH; 
#if (SPIFLASH_EN == 0)
#error "ERROR: SPI FLASHû��ʹ��"	 
#endif
#endif

#define TFTP_OPCODE_LEN         2
#define TFTP_BLKNUM_LEN         2
#define TFTP_DATA_LEN_MAX       512
#define TFTP_DATA_PKT_HDR_LEN   (TFTP_OPCODE_LEN + TFTP_BLKNUM_LEN)
#define TFTP_ERR_PKT_HDR_LEN    (TFTP_OPCODE_LEN + TFTP_ERRCODE_LEN)
#define TFTP_ACK_PKT_LEN        (TFTP_OPCODE_LEN + TFTP_BLKNUM_LEN)
#define TFTP_DATA_PKT_LEN_MAX   (TFTP_DATA_PKT_HDR_LEN + TFTP_DATA_LEN_MAX)
#define TFTP_MAX_RETRIES        3
#define TFTP_TIMEOUT_INTERVAL   5

typedef struct
{
   unsigned char  fin;
   unsigned short block;  
}RECEIVE_FLAG;
RECEIVE_FLAG ReceiveFlag;


// TFTP opcodes as specified in RFC1350  
typedef enum {
  TFTP_RRQ = 1,
  TFTP_WRQ = 2,
  TFTP_DATA = 3,
  TFTP_ACK = 4,
  TFTP_ERROR = 5
} tftp_opcode;

// TFTP error codes as specified in RFC1350  
typedef enum {
  TFTP_ERR_NOTDEFINED,       	// δ����
  TFTP_ERR_FILE_NOT_FOUND,   	// �ļ�δ�ҵ�
  TFTP_ERR_ACCESS_VIOLATION, 	// ���ʷǷ�
  TFTP_ERR_DISKFULL,         	// �������򳬹���������
  TFTP_ERR_ILLEGALOP,         	// �Ƿ���TFTP����
  TFTP_ERR_UKNOWN_TRANSFER_ID,  // δ֪�Ĵ���ID
  TFTP_ERR_FILE_ALREADY_EXISTS, // �ļ��Ѿ�����
  TFTP_ERR_NO_SUCH_USER,        // û�����Ƶ��û�
} tftp_errorcode;

static err_t TFTP_SendACK(struct netconn *conn, struct netbuf *buf, unsigned short block)
{
    unsigned char *p;
    err_t err;
	
	p = buf->ptr->payload;
    *p++ = 0;
	*p++ = TFTP_ACK;
	*p++ = block/256;
	*p = block%256;
    buf->ptr->len = 4;
	buf->ptr->tot_len = 4;
	err = netconn_send(conn, buf);
    
    return 	err;
}

static err_t TFTP_SendERR(struct netconn *conn, struct netbuf *buf, char err)
{
    unsigned char *p;
	
    p = buf->ptr->payload;
	*p++ = 0;
	*p++ = TFTP_ERROR;
	*p++ = 0;
	*p++ = err;
    if (err == TFTP_ERR_ILLEGALOP)
	{
        *p++ = 'E';
		*p++ = 'R';
		*p++ = 'A';
		*p++ = 'S';
		*p++ = 'E';
	}
    *p = 0;
		
   	buf->ptr->len = 10;
	buf->ptr->tot_len = 10;
	
	err = netconn_send(conn, buf);	
    
    return 	err;
}

void TFTPData_Proc(struct netconn *conn, struct netbuf *buf)
{
	char Cmd;
    INT8U *p;
	INT16U len, block;
	INT32S flag;
	
    netbuf_data(buf, &p, &len);
	*p++;
	Cmd = *p++;	  
	switch (Cmd)
	{
        
        case TFTP_WRQ:    // 

                /*extract file name info */
                /*i= 0;
                while (*(p+i)!=0x0)
                {
                    i++;
                }
                strncpy(filename, p, i+1);
                */
                #if (DEBUG_APP_EN == 1)
                if (UserVars.Para.ATFlag&AT_NET_FLAG)
                {
                    printf("AT+INFO=IAP File Name: %s\r\n", p); 
                }
                #endif 
  
                #if (IAP_FLASH == IAP_B_ID) // TFTP�̼�FLASHѡ��, 1(IAP_B_ID), B��FLASH;  3(IAP_C_ID), C��FLASH;
                IAP_Ctrl(IAP_FLASH, CMD_IAP_UNLOCK, 0);           // ����B��FALSH
                #endif
                flag = IAP_Ctrl(IAP_FLASH, CMD_IAP_ERASE, 0);    // ����FALSH
                if (flag == ERR_TRUE)                            // �����ɹ�
                {                    
                    #if (DEBUG_APP_EN == 1)
                    if (UserVars.Para.ATFlag&AT_NET_FLAG)
                    {
                        printf("AT+INFO=IAP Flash erase ok\r\n");
                    }
                    #endif 
                    TFTP_SendACK(conn, buf, 0);                  // ������ȷ��Ϣ
                }
                else
                {
                    #if (DEBUG_APP_EN == 1)
                    if (UserVars.Para.ATFlag&AT_NET_FLAG)
                    {
                        printf("AT+ERROR=IAP Flash erase false\r\n");
                    }
                    #endif                     
                    TFTP_SendERR(conn, buf, TFTP_ERR_ILLEGALOP);  // ���س�����Ϣ
                }	
                ReceiveFlag.block = 0;
                break;
        case TFTP_DATA:    // 
            block = 256*(u16_t)*p++;
            block += *p++;
            #if (DEBUG_APP_EN == 1)
            if (UserVars.Para.ATFlag&AT_NET_FLAG)
            {
                printf("AT+INFO=IAP Write: %d, %d\r\n", block, len);
            }
            #endif              
            if ((block - ReceiveFlag.block)==1)  // ��һ�����ݿ� 
            {
                len -= 4;
                if (len <= 512)
                {
                    flag = IAP_Write(IAP_FLASH, p, (block-1)*512, len);  
                }
                else
                {
                    flag = ERR_FALSE; 
                }								
                        
                if (flag == ERR_TRUE)
                {
                   if (len<512)  // �������
                   {
                        flag = IAP_Ctrl(IAP_FLASH, CMD_IAP_UPDATE, len+((INT32U)block-1)*512);   // ����IAP���±�־                        
                        //IAP_Ctrl(IAP_B_ID,CMD_IAP_LOCK, 0);                                    // ����A,B,AB��FALSH, �������Ҫ����, ���Բ������������������FLASH
                        if (flag == ERR_TRUE)
                        {
                            TFTP_SendACK(conn, buf, block);
                            ReceiveFlag.block = 0;                            
                            #if (DEBUG_APP_EN == 1)
                            if (UserVars.Para.ATFlag&AT_NET_FLAG)
                            {
                                printf("AT+INFO=IAP�����ļ��������, �ȴ�3���ϵͳ��λ�����¹̼�����\r\n");
                            }
                            #endif                             
                            Delay_ms(3000);
                            SysLib_Ctrl(CMD_SYSLIB_RESET, 0);  // ϵͳ��λ
                        }
                        else
                        {
                            TFTP_SendERR(conn, buf, TFTP_ERR_ILLEGALOP);   // ���س�����Ϣ  
                            #if (DEBUG_APP_EN == 1)
                            if (UserVars.Para.ATFlag&AT_NET_FLAG)
                            {
                                printf("AT+INFO=IAP�����ļ�����ʧ��");
                            }
                            #endif   
                        }										    
                    }
                    else
                    {						 
                         TFTP_SendACK(conn, buf, block);
                         ReceiveFlag.block = block;
                    }
                }
                else
                {
                    TFTP_SendERR(conn, buf, TFTP_ERR_ILLEGALOP);   // ���س�����Ϣ               
                    ReceiveFlag.block = block;
                }								
            }
            else
            {
                TFTP_SendACK(conn, buf, block);
            }							
            break;
        case TFTP_RRQ:               
        case TFTP_ACK:    
        case TFTP_ERROR:   
            break;
        default:
              break;
	}
}
#endif
/***********************************************************************************
* Function: TaskReadCmd_Main;
*
* Description: �����������;
*              
* Input:  none;
*
* Return: none;
*
* Note:   none;
************************************************************************************/
void  App_TaskLWIP (void *p_arg)
{
    #if ((IAP_EN > 0)&&(IAP_TFTP_EN > 0))  // ����TFTPЭ����¹̼�ʹ��
    struct netconn *conn, *newconn;
	err_t err;
	struct netbuf *buf;
	void *data;
	INT16U len;
    #endif
    INT32U err_t;

#define MAX_DISCONNECT_T    10 // �Ͽ�����10��, �ٲ�����Ϊ����δ�ж�, ���Լ���ͨ��
    (void)p_arg;
	printf("App_TaskLWIP\r\n");
  	TCPIPStatus = TCPIP_INIT; // ���ó�ʼ������
    while (1) 
	{		 
		 UserVars.TaskRunStatus |= TASK_LWIP_FLAG;   // ���ñ���������״̬��־
		 OSTimeDly(5);                              // ��ʱ100ms
		 switch (TCPIPStatus)
		 {			
			 case TCPIP_INIT:
                     //while((NET_Ctrl(CMD_NET_SYNC, 0)&NET_PHY_LINK)!=NET_PHY_LINK);
                     LwIP_Init();                  // LWIP��ʼ��
                     TCPIPStatus = TCPIP_TASK;     // ����TCPIP����״̬
                     //UserVars.Flag |= NET_PHY_LINK_FLAG; // ��������Ӳ�����ӱ�־
                     #if (DEBUG_APP_EN == 1)
                     if (UserVars.Para.ATFlag&AT_NET_FLAG)
                     {
                         printf("AT+INFO=LWIP Init, OK\r\n\r\n");
	                 }	
                     #endif
                     
                     
				 break;

			 case TCPIP_TASK:
				 #if (LWIP_WKMODE == LWIP_SOCKET_SERVER)  // ����Ϊ������ģʽ
                   	 sys_thread_new("tcpecho_thread", tcpecho_thread, NULL, DEFAULT_THREAD_STACKSIZE, DEFAULT_THREAD_PRIO); // ��������������������
				 #elif (LWIP_WKMODE == LWIP_HTTP)   // ����Ϊhttp����ģʽ
                     sys_thread_new("http_server_netconn", http_server_netconn_thread, NULL, DEFAULT_THREAD_STACKSIZE, DEFAULT_THREAD_PRIO); // ����������http����������
				 #elif (LWIP_WKMODE == LWIP_SOCKET_CLIENT) // ����Ϊ�ͻ���ģʽ 
				 	 #if (LWIP_NETYPE == LWIP_NETYPE_TCP)  // TCPģʽ
                     sys_thread_new("Client_TCP_Thread", Client_TCP_Thread, NULL, DEFAULT_THREAD_STACKSIZE, DEFAULT_THREAD_PRIO); // �����������ͻ�������
				     #endif
                     #if (LWIP_NETYPE == LWIP_NETYPE_UDP)  // UDPģʽ
                     sys_thread_new("Client_UDP_Thread", Client_UDP_Thread, NULL, DEFAULT_THREAD_STACKSIZE, DEFAULT_THREAD_PRIO); // �����������ͻ�������
				     #endif
                 #endif
			     
                 #if ((IAP_EN > 0)&&(IAP_TFTP_EN > 0))  // ����TFTPЭ����¹̼�ʹ��
                 conn = netconn_new(NETCONN_UDP);
                 conn->recv_timeout = 1000;
                 netconn_bind(conn, NULL, 69);
                 #endif               
             
				 TCPIPStatus = TCPIP_WAITLINK;    // ������������״̬
				 break;

		     case TCPIP_IDLE:
				 if ((NET_Ctrl(CMD_NET_SYNC, 0)&NET_PHY_LINK)==0)
                 {
                      err_t++;                      
					  if (err_t > (MAX_DISCONNECT_T*20)) // ����MAX_DISCONNECT_T����Ϊ�Ͽ�
                      {
                          UserVars.Flag &= ~NET_PHY_LINK_FLAG; // ��������Ӳ�����ӶϿ���־
                          #if (DEBUG_APP_EN == 1)
                          if (UserVars.Para.ATFlag&AT_NET_FLAG)
                          {
                              printf("AT+INFO=NETӲ���Ͽ�����\r\n\r\n");
                          }	                 
                          #endif
                          TCPIPStatus = TCPIP_WAITLINK;     // ����Ͽ�, ���õȴ�����״̬
                          err_t  = 0;
                      }
                 } 
                 else
                 {
                      #if ((IAP_EN > 0)&&(IAP_TFTP_EN > 0))  // ����TFTPЭ����¹̼�ʹ��
                      err = netconn_recv(conn, &buf);
                      if (err == ERR_OK)
                      {
                           netbuf_first(buf);
                           do 
                           {		
                                TFTPData_Proc(conn, buf);
                           } while (netbuf_next(buf) >= 0);
                           netbuf_delete(buf);
                      }
                      else
                      {
                           if (err != ERR_TIMEOUT)
                           {
                                break; 
                           }
                      }
                      #endif
                 }
				 break;

		     case TCPIP_WAITLINK:
				 if (NET_Ctrl(CMD_NET_SYNC, 0)&NET_PHY_LINK)
                 {
                      UserVars.Flag |= NET_PHY_LINK_FLAG; // ��������Ӳ�����ӱ�־
                      #if (DEBUG_APP_EN == 1)
	                  if (UserVars.Para.ATFlag&AT_NET_FLAG)
                      {
                         printf("AT+INFO=NETӲ������,OK\r\n");
	                  }
                      #endif
					  TCPIPStatus = TCPIP_IDLE;         // ������������״̬
                      err_t = 0;
                 }
				 break;			
			 default:
				 break;
		 }
    }
}
#endif
/***********************************************************************************/
// �ļ�����
/***********************************************************************************/
