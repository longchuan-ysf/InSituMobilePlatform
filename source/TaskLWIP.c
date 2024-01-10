/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: TastLWIP.c
* Project  : STM32F1XX/4XX系列模块软件
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.00
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: 本文件负责网络协议栈LWIP处理;
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
// 测试说明
/************************************************************************************/
/*
1. 关于IP地址及端口号:
   计算机IP(DSC_IP)：192.168.1.2, 端口号(DSC_PORT): 5001
   工控板IP(LOCAL_IP)：192.168.1.3, 端口号(LOCAL_PORT): 5000
   根据实际网络情况可以在配置中修改

2. 客户端(TCP)模式网络测试方法(工控板作为客户端主动连接服务器器计算机):
(1) 配置:
    #define TASK_LWIP_EN      	1	                // TCPIP测试任务： 0, 关闭; 1, 使能运行;
    #define LWIP_EN             TASK_LWIP_EN        // TCPIP(LWIP)协议栈使能：1, 使能;  0, 关闭;
    #define LWIP_WKMODE		    LWIP_SOCKET_CLIENT  // LWIP_SOCKET_CLIENT  //LWIP_HTTP// 工作模式, 选择LWIP_SOCKET_CLIENT、LWIP_SOCKET_SERVER、LWIP_HTTP 
    #define LWIP_NETYPE			LWIP_NETYPE_TCP     // 通信类型, 选择LWIP_NETYPE_UDP、LWIP_NETYPE_TCP 
    #define LWIP_CONFIG_EN      1                   // 配置选择: 1, 按配置设置网络; 0, 按EEPROM存储信息配置网络
    其它按默认配置 
(2) 打开TCPIP测试工具建立端口号为5001的服务器，启动服务;
(3) 编译并下载例程运行，工控板作为客户端会主动连接服务器;
(4) 在TCPIP测试工具看到连接的工控板设备，并发送数据测试,  工控板收到数据会将数据原样发回服务器

3. 服务器(TCP)模式网络测试方法(工控板作为服务器，计算机作为客户端主动连接工控板):
(1) 配置:
    #define TASK_LWIP_EN      	1	                // TCPIP测试任务： 0, 关闭; 1, 使能运行;
    #define LWIP_EN             TASK_LWIP_EN        // TCPIP(LWIP)协议栈使能：1, 使能;  0, 关闭;
    #define LWIP_WKMODE		    LWIP_SOCKET_CLIENT  //LWIP_SOCKET_CLIENT  // LWIP_HTTP// 工作模式, 选择LWIP_SOCKET_CLIENT、LWIP_SOCKET_SERVER、LWIP_HTTP 
    #define LWIP_NETYPE			LWIP_NETYPE_TCP     // 通信类型, 选择LWIP_NETYPE_UDP、LWIP_NETYPE_TCP 
    #define LWIP_CONFIG_EN      1                   // 配置选择: 1, 按配置设置网络; 0, 按EEPROM存储信息配置网络
    其它按默认配置 
(2) 编译并下载例程运行，工控板建立以5000端口的服务器, 并启动服务等待连接;
(3) 打开TCPIP测试工具建立客户端并连接端口号为5000的工控板服务器;
(4) 连接成功后, 在TCPIP测试工具发送数据测试, 工控板收到数据会将数据原样发回计算机

4. HTTP服务器模式网络测试方法(工控板作为HTTP服务器，计算机作为客户端用IE访问):
(1) 配置:
    #define TASK_LWIP_EN      	1	                // TCPIP测试任务： 0, 关闭; 1, 使能运行;
    #define LWIP_EN             TASK_LWIP_EN        // TCPIP(LWIP)协议栈使能：1, 使能;  0, 关闭;
    #define LWIP_WKMODE		    LWIP_HTTP           //LWIP_SOCKET_CLIENT  // LWIP_HTTP// 工作模式, 选择LWIP_SOCKET_CLIENT、LWIP_SOCKET_SERVER、LWIP_HTTP 
    #define LWIP_NETYPE			LWIP_NETYPE_TCP     // 通信类型, 选择LWIP_NETYPE_UDP、LWIP_NETYPE_TCP 
    #define LWIP_CONFIG_EN      1                   // 配置选择: 1, 按配置设置网络; 0, 按EEPROM存储信息配置网络
    其它按默认配置 
(2) 编译并下载例程运行，工控板建立以80端口的HTTP服务器, 并启动服务等待访问;
(3) 打开IE, 输入192.168.1.3, 访问服务器;

5. Modbus TCP 通信测试(工控板作为Modbus TCP服务器, 计算机作为客户端，用Modbus Poll软件进行连接测试):
(1) 配置:
    #define TASK_LWIP_EN      	1	                // TCPIP测试任务： 0, 关闭; 1, 使能运行;
    #define LWIP_EN             TASK_LWIP_EN        // TCPIP(LWIP)协议栈使能：1, 使能;  0, 关闭;
    #define LWIP_WKMODE		    LWIP_SOCKET_SERVER  //LWIP_SOCKET_CLIENT  // LWIP_HTTP// 工作模式, 选择LWIP_SOCKET_CLIENT、LWIP_SOCKET_SERVER、LWIP_HTTP 
    #define LWIP_NETYPE			LWIP_NETYPE_TCP     // 通信类型, 选择LWIP_NETYPE_UDP、LWIP_NETYPE_TCP 
    
    
    其它按默认配置 
(2) 编译并下载例程运行，工控板建立以502端口的服务器, 并启动服务等待连接;
(3) 打开Modbus Poll测试工具, 点击Connection，选择TCP/IP, IP Address：192.168.1.3, Port: 502,建立连接进行测试;
(4) 注意：常量及全局变量定义进行设置：
          #define MODBUS_TCP_EN      1 // 1, 执行Modbus TCP测试使能; 0, 执行服务器模式网络测试
    关闭Modbus任务      
          #define TASK_MODBUS_EN      0	  // MODBUS测试任务：0, 关闭; 1, 使能运行;
*/


/************************************************************************************/
// 引用外部头文件
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
// 常量及全局变量定义
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
  
  tcpip_init(NULL,NULL);	// TCP IP协议栈初始化

#if LWIP_DHCP
  ipaddr.addr = 0;
  netmask.addr = 0;
  gw.addr = 0;
#else
    IP4_ADDR(&ipaddr, UserVars.Para.LocalIP[0], UserVars.Para.LocalIP[1], UserVars.Para.LocalIP[2], UserVars.Para.LocalIP[3]);  // 设定本机IP地址
    IP4_ADDR(&netmask, UserVars.Para.SubnetMask[0], UserVars.Para.SubnetMask[1], UserVars.Para.SubnetMask[2], UserVars.Para.SubnetMask[3]); // 设定子网掩码
    IP4_ADDR(&gw, UserVars.Para.Gataway[0], UserVars.Para.Gataway[1], UserVars.Para.Gataway[2], UserVars.Para.Gataway[3]);      // 设定路由器地址
#endif
    //Set_MAC_Address((INT8U *)UserVars.Para.MACAddr);  // 设定MAC地址
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
  

  netif_add(&netif, &ipaddr, &netmask, &gw, NULL, &ethernetif_init, &tcpip_input);  // 初始化参数
  //NET_Ctrl(CMD_NET_INT, 1);
  /*  Registers the default network interface.*/
  netif_set_default(&netif); // 注册网络接口
  

#if LWIP_DHCP
  /*  Creates a new DHCP client for this interface on the first call.
  Note: you must call dhcp_fine_tmr() and dhcp_coarse_tmr() at
  the predefined regular intervals after starting the client.
  You can peek in the netif->dhcp struct for the actual DHCP status.*/
  dhcp_start(&netif);   // 启动DHCP
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
     客户端(TCP)模式任务
***************************************************************************************/
#if ((LWIP_WKMODE == LWIP_SOCKET_CLIENT)&&(LWIP_NETYPE == LWIP_NETYPE_TCP)) // 配置为客户端TCP模式 
static void Client_TCP_Thread(void *arg)
{
    struct netconn *conn;
    struct netbuf *buf;
	struct ip_addr ipaddr;
    err_t err;
	char *data = NULL;
	INT16U len, i, n;
    INT8U DataBuf[32], DataBufLen;
    
	CliStatus = C_INIT; // 设定初始状态
    
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
					
					conn = netconn_new(NETCONN_TCP);    // 创建一个新的连接标识符
					if (conn != NULL)
                    {
                        conn->recv_timeout = 1000;          // 设置接收超时, 单位ms
                        conn->send_timeout = 1000;          // 设置发送超时, 单位ms
                        netconn_bind(conn, NULL, UserVars.Para.LocalPort);  // 绑定本地IP地址连接
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
                    IP4_ADDR(&ipaddr, UserVars.Para.DscIP[0], UserVars.Para.DscIP[1], UserVars.Para.DscIP[2], UserVars.Para.DscIP[3]); // 设定服务器IP
                    err = netconn_connect(conn, &ipaddr, UserVars.Para.DscPort); // 连接服务器IP
                    if (err == ERR_OK)  // 连接成功
                    {
                         CliStatus = C_IDLE;
                         #if (DEBUG_APP_EN == 1)
                         if (UserVars.Para.ATFlag&AT_NET_FLAG)
                         {
                            printf("AT+INFO=NET Client(TCP) connect OK\r\n");
                         }
                         #endif 					 									 
                    }
                    else  // 连接失败
                    { 
                         CliStatus = C_IDLE;
                         #if (DEBUG_APP_EN == 1)
                         if (UserVars.Para.ATFlag&AT_NET_FLAG)
                         {
                            printf("AT+ERROR=NET Client(TCP) connect error: %s\r\n", lwip_strerr(err));
                         }
                         #endif                      	
                         netconn_close(conn);	 // 关闭连接标识符
                         netconn_delete(conn);	 // 删除连接标识符
                         CliStatus = C_INIT;
                         Delay_ms(1000);
                    }
                //}
				break;
			 case C_IDLE:					
                if (TCPIPStatus == TCPIP_IDLE)
                {	
                    err = netconn_recv(conn, &buf); // 接收数据函数
                    if (err == ERR_OK) // 接收成功
                    {
                        netbuf_first(buf); // 移动数据指针
                        do 
                        {
                            netbuf_data(buf, &data, &len); // 读取数据指针和长度: data是数据指针, len是数据长度									
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
                            // 网络发送数据   
                            if (len<32)           // 设置发送数据长度
                            {
                                DataBufLen = len;
                            }
                            else
                            {
                                DataBufLen = 32;
                            }
                            
                            for(i=0; i<DataBufLen; i++)  // 赋值
                            {
                                DataBuf[i] = data[i];
                            }
                            
                            err = netconn_write(conn, DataBuf, DataBufLen, NETCONN_COPY); // 发送数据
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
     客户端(UDP)模式任务
***************************************************************************************/
#if ((LWIP_WKMODE == LWIP_SOCKET_CLIENT)&&(LWIP_NETYPE == LWIP_NETYPE_UDP)) // 配置为客户端UDP模式 
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

	CliStatus = C_INIT; // 设定初始状态
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
					
					conn = netconn_new(NETCONN_UDP);    // 创建一个新的连接标识符
					if (conn != NULL)
                    {
                        conn->recv_timeout = 1000;          // 设置接收超时					
                        netconn_bind(conn, NULL, UserVars.Para.LocalPort);  // 绑定本地IP地址连接
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
                     Delay_ms(1000);  // 延时1秒   
                 }
				 break;
			 case C_CONNECT: 				
				IP4_ADDR(&ipaddr, UserVars.Para.DscIP[0], UserVars.Para.DscIP[1], UserVars.Para.DscIP[2], UserVars.Para.DscIP[3]); // 设定服务器IP
				err = netconn_connect(conn, &ipaddr, UserVars.Para.DscPort); // 连接服务器IP
				if (err == ERR_OK)  // 连接成功
				{
					CliStatus = C_IDLE;
                    #if (DEBUG_APP_EN == 1)
                    if (UserVars.Para.ATFlag&AT_NET_FLAG)
                    {
                        printf("AT+INFO=NET Client(UDP) connect OK\r\n");
                    }
                    #endif 							 
					
                    //  UDP模式第一次建立连接先发送一串数据给服务器, 让服务器看到连接设备
                    SendBuf = netbuf_new();               // 创建buf 
                    sendata = netbuf_alloc(SendBuf,10);   // 申请内存10字节
                    for (i=0; i<10; i++)                  // 赋值
                    {
                        sendata[i] = i+'0';
                    }
                    netconn_send(conn,SendBuf);           // 发送数据
                    netbuf_delete(SendBuf);					 
				}
				else  // 连接失败
				{ 
                     #if (DEBUG_APP_EN == 1)
                     if (UserVars.Para.ATFlag&AT_NET_FLAG)
                     {
                        printf("AT+ERROR=NET Client udp connect error: %s\r\n", lwip_strerr(err));	
                     }
                     #endif 
                     
					 netconn_close(conn);	 // 关闭连接标识符
					 netconn_delete(conn);	 // 删除连接标识符
					 CliStatus = C_INIT;
					 Delay_ms(1000);
				}
				break;			 
			 case C_IDLE:					
                err = netconn_recv(conn, &buf);  // 接收服务器发来的数据
                if (err == ERR_OK) // 接收成功
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
                        netbuf_data(buf, &data, &len);  // 将数据
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
                        // 网络发送数据
                        SendBuf = netbuf_new();               // 创建发送数据SendBuf 
                        sendata = netbuf_alloc(SendBuf,len);  // 申请内存len字节
                        for (i=0; i<len; i++)                 // 将收到的数据放到发送sendata中
                        {
                            sendata[i] = data[i];
                        }
                        netconn_send(conn,SendBuf);           // 发送数据
                        netbuf_delete(SendBuf);               // 删除SendBuf
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
     服务端模式任务
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
    
  conn = netconn_new(NETCONN_TCP);  // 创建一个新的连接标识符 /* Create a new connection identifier. */
  conn->recv_timeout = 100;         // 设置接收超时 
  #if (MODBUS_TCP_EN == 1)          // Modbus TCP测试
  netconn_bind(conn, NULL, 502);    // 绑定本地端口号502 /* Bind connection to well known port number 7. */
  #else                             // 执行服务器模式网络测试
  netconn_bind(conn, NULL, UserVars.Para.LocalPort); // 绑定本地端口号 /* Bind connection to well known port number 7. */
  #endif
  netconn_listen(conn);             //连接进入监听模式  /* Tell connection to go into listening mode. */

  while (1) 
  {
    	/* Grab new connection. */
    	while (netconn_accept(conn, &newconn) != ERR_OK);  // ERR_TIMEOUT    
		newconn->recv_timeout = 1000;
		while (TCPIPStatus == TCPIP_IDLE)
        {
			err = netconn_recv(newconn, &buf);  // 接收数据函数
			if (err == ERR_OK)  // 接收成功
			{
                netbuf_first(buf); // 移动数据指针
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
                    // 网络发送数据               
                    #if (MODBUS_TCP_EN == 1)   // Modbus TCP测试
                    flag = Modbus_Proc(MODBUS_TCP_ID, MODBUS_SLAVE_ID, &data[6], len-6, (MODBUS_PARA *)&ModbusPara.Flag); // 从第六个数据开始是Modbus数据，调用处理程序
                    if (flag == ERR_TRUE) // 处理正确
                    {
                        if (ModbusPara.pData->Flag&MODBUS_OK_FLAG) // 完成标志
                        {
                             ModbusPara.pData->Flag = 0;
                             ModbusPara.pData->swcl[0] = data[0]; // MODBUS TCP: 事物处理标识箱
                             ModbusPara.pData->swcl[1] = data[1];
                             ModbusPara.pData->xyid[0] = data[2]; // MODBUS TCP: 协议标识符
                             ModbusPara.pData->xyid[1] = data[3];
                            
                             err = netconn_write(newconn,  &ModbusPara.pData->swcl[0], ModbusPara.pData->len, NETCONN_COPY); // 发送数据
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
                    #else                 // 执行服务器模式网络测试 
                    if (len<32)           // 设置发送数据长度
                    {
                        DataBufLen = len;
                    }
                    else
                    {
                        DataBufLen = 32;
                    }
                    
                    for(i=0; i<DataBufLen; i++)  // 赋值
                    {
                        DataBuf[i] = data[i];
                    }
                    
                    err = netconn_write(newconn, data, len, NETCONN_COPY); // 发送数据
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
     HTTP服务端模式任务
***************************************************************************************/

#ifndef HTTPD_DEBUG
#define HTTPD_DEBUG         LWIP_DBG_ON
#endif

const static char http_html_hdr[] = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n";
const static char http_index_html[] = "<html><head><title>Congrats!</title></head><body><h1>欢迎使用北京中嵌凌云电子有限公司产品：lwIP HTTP server!</h1><p>This is a small test page, served by httpserver-netconn.</body></html>";

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


#if ((IAP_EN > 0)&&(IAP_TFTP_EN > 0))  // 网络TFTP协议更新固件使能
#if (IAP_FLASH == 3)             // 更新固件存储器选择：0,2: 无效; 1(IAP_B_ID), B区FLASH;  3(IAP_C_ID), C区FLASH; 
#if (SPIFLASH_EN == 0)
#error "ERROR: SPI FLASH没有使能"	 
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
  TFTP_ERR_NOTDEFINED,       	// 未定义
  TFTP_ERR_FILE_NOT_FOUND,   	// 文件未找到
  TFTP_ERR_ACCESS_VIOLATION, 	// 访问非法
  TFTP_ERR_DISKFULL,         	// 磁盘满或超过分配的配额
  TFTP_ERR_ILLEGALOP,         	// 非法的TFTP操作
  TFTP_ERR_UKNOWN_TRANSFER_ID,  // 未知的传输ID
  TFTP_ERR_FILE_ALREADY_EXISTS, // 文件已经存在
  TFTP_ERR_NO_SUCH_USER,        // 没有类似的用户
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
  
                #if (IAP_FLASH == IAP_B_ID) // TFTP固件FLASH选择, 1(IAP_B_ID), B区FLASH;  3(IAP_C_ID), C区FLASH;
                IAP_Ctrl(IAP_FLASH, CMD_IAP_UNLOCK, 0);           // 解锁B区FALSH
                #endif
                flag = IAP_Ctrl(IAP_FLASH, CMD_IAP_ERASE, 0);    // 擦除FALSH
                if (flag == ERR_TRUE)                            // 擦除成功
                {                    
                    #if (DEBUG_APP_EN == 1)
                    if (UserVars.Para.ATFlag&AT_NET_FLAG)
                    {
                        printf("AT+INFO=IAP Flash erase ok\r\n");
                    }
                    #endif 
                    TFTP_SendACK(conn, buf, 0);                  // 返回正确信息
                }
                else
                {
                    #if (DEBUG_APP_EN == 1)
                    if (UserVars.Para.ATFlag&AT_NET_FLAG)
                    {
                        printf("AT+ERROR=IAP Flash erase false\r\n");
                    }
                    #endif                     
                    TFTP_SendERR(conn, buf, TFTP_ERR_ILLEGALOP);  // 返回出错信息
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
            if ((block - ReceiveFlag.block)==1)  // 下一个数据块 
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
                   if (len<512)  // 传输结束
                   {
                        flag = IAP_Ctrl(IAP_FLASH, CMD_IAP_UPDATE, len+((INT32U)block-1)*512);   // 设置IAP更新标志                        
                        //IAP_Ctrl(IAP_B_ID,CMD_IAP_LOCK, 0);                                    // 锁定A,B,AB区FALSH, 如果不需要加密, 可以不调用这个函数来锁定FLASH
                        if (flag == ERR_TRUE)
                        {
                            TFTP_SendACK(conn, buf, block);
                            ReceiveFlag.block = 0;                            
                            #if (DEBUG_APP_EN == 1)
                            if (UserVars.Para.ATFlag&AT_NET_FLAG)
                            {
                                printf("AT+INFO=IAP网络文件传输完成, 等待3秒后系统复位运行新固件程序\r\n");
                            }
                            #endif                             
                            Delay_ms(3000);
                            SysLib_Ctrl(CMD_SYSLIB_RESET, 0);  // 系统复位
                        }
                        else
                        {
                            TFTP_SendERR(conn, buf, TFTP_ERR_ILLEGALOP);   // 返回出错信息  
                            #if (DEBUG_APP_EN == 1)
                            if (UserVars.Para.ATFlag&AT_NET_FLAG)
                            {
                                printf("AT+INFO=IAP网络文件传输失败");
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
                    TFTP_SendERR(conn, buf, TFTP_ERR_ILLEGALOP);   // 返回出错信息               
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
* Description: 命令处理主函数;
*              
* Input:  none;
*
* Return: none;
*
* Note:   none;
************************************************************************************/
void  App_TaskLWIP (void *p_arg)
{
    #if ((IAP_EN > 0)&&(IAP_TFTP_EN > 0))  // 网络TFTP协议更新固件使能
    struct netconn *conn, *newconn;
	err_t err;
	struct netbuf *buf;
	void *data;
	INT16U len;
    #endif
    INT32U err_t;

#define MAX_DISCONNECT_T    10 // 断开网线10秒, 再插上认为连接未中断, 可以继续通信
    (void)p_arg;
	printf("App_TaskLWIP\r\n");
  	TCPIPStatus = TCPIP_INIT; // 设置初始化操作
    while (1) 
	{		 
		 UserVars.TaskRunStatus |= TASK_LWIP_FLAG;   // 设置本任务运行状态标志
		 OSTimeDly(5);                              // 延时100ms
		 switch (TCPIPStatus)
		 {			
			 case TCPIP_INIT:
                     //while((NET_Ctrl(CMD_NET_SYNC, 0)&NET_PHY_LINK)!=NET_PHY_LINK);
                     LwIP_Init();                  // LWIP初始化
                     TCPIPStatus = TCPIP_TASK;     // 设置TCPIP任务状态
                     //UserVars.Flag |= NET_PHY_LINK_FLAG; // 设置网络硬件连接标志
                     #if (DEBUG_APP_EN == 1)
                     if (UserVars.Para.ATFlag&AT_NET_FLAG)
                     {
                         printf("AT+INFO=LWIP Init, OK\r\n\r\n");
	                 }	
                     #endif
                     
                     
				 break;

			 case TCPIP_TASK:
				 #if (LWIP_WKMODE == LWIP_SOCKET_SERVER)  // 配置为服务器模式
                   	 sys_thread_new("tcpecho_thread", tcpecho_thread, NULL, DEFAULT_THREAD_STACKSIZE, DEFAULT_THREAD_PRIO); // 创建并启动服务器任务
				 #elif (LWIP_WKMODE == LWIP_HTTP)   // 配置为http访问模式
                     sys_thread_new("http_server_netconn", http_server_netconn_thread, NULL, DEFAULT_THREAD_STACKSIZE, DEFAULT_THREAD_PRIO); // 创建并启动http服务器任务
				 #elif (LWIP_WKMODE == LWIP_SOCKET_CLIENT) // 配置为客户端模式 
				 	 #if (LWIP_NETYPE == LWIP_NETYPE_TCP)  // TCP模式
                     sys_thread_new("Client_TCP_Thread", Client_TCP_Thread, NULL, DEFAULT_THREAD_STACKSIZE, DEFAULT_THREAD_PRIO); // 创建并启动客户端任务
				     #endif
                     #if (LWIP_NETYPE == LWIP_NETYPE_UDP)  // UDP模式
                     sys_thread_new("Client_UDP_Thread", Client_UDP_Thread, NULL, DEFAULT_THREAD_STACKSIZE, DEFAULT_THREAD_PRIO); // 创建并启动客户端任务
				     #endif
                 #endif
			     
                 #if ((IAP_EN > 0)&&(IAP_TFTP_EN > 0))  // 网络TFTP协议更新固件使能
                 conn = netconn_new(NETCONN_UDP);
                 conn->recv_timeout = 1000;
                 netconn_bind(conn, NULL, 69);
                 #endif               
             
				 TCPIPStatus = TCPIP_WAITLINK;    // 进入正常工作状态
				 break;

		     case TCPIP_IDLE:
				 if ((NET_Ctrl(CMD_NET_SYNC, 0)&NET_PHY_LINK)==0)
                 {
                      err_t++;                      
					  if (err_t > (MAX_DISCONNECT_T*20)) // 大于MAX_DISCONNECT_T秒认为断开
                      {
                          UserVars.Flag &= ~NET_PHY_LINK_FLAG; // 设置网络硬件连接断开标志
                          #if (DEBUG_APP_EN == 1)
                          if (UserVars.Para.ATFlag&AT_NET_FLAG)
                          {
                              printf("AT+INFO=NET硬件断开连接\r\n\r\n");
                          }	                 
                          #endif
                          TCPIPStatus = TCPIP_WAITLINK;     // 网络断开, 设置等待连接状态
                          err_t  = 0;
                      }
                 } 
                 else
                 {
                      #if ((IAP_EN > 0)&&(IAP_TFTP_EN > 0))  // 网络TFTP协议更新固件使能
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
                      UserVars.Flag |= NET_PHY_LINK_FLAG; // 设置网络硬件连接标志
                      #if (DEBUG_APP_EN == 1)
	                  if (UserVars.Para.ATFlag&AT_NET_FLAG)
                      {
                         printf("AT+INFO=NET硬件连接,OK\r\n");
	                  }
                      #endif
					  TCPIPStatus = TCPIP_IDLE;         // 进入正常工作状态
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
// 文件结束
/***********************************************************************************/
