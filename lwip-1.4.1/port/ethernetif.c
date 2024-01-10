/**
 * @file
 * Ethernet Interface Skeleton
 *
 */

/*
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 *
 * Author: Adam Dunkels <adam@sics.se>
 *
 */

/*
 * This file is a skeleton for developing Ethernet network interface
 * drivers for lwIP. Add code to the low_level functions and do a
 * search-and-replace for the word "ethernetif" to replace it with
 * something that better describes your network interface.
 */

#include "config.h"

#if (LWIP_EN == 1)

#include "lwip/opt.h"
#include "lwip/def.h"
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include "lwip/sys.h"
#include <lwip/stats.h>
#include <lwip/snmp.h>
#include "netif/etharp.h"
#include "netif/ppp_oe.h"
#include "err.h"
#include "ethernetif.h"
#include <string.h>
#include "net.h"
#include <includes.h>
//#include "LibVars.h"
#include "UserVars.h"

#if ((MODULE_CLASS == STM32F107XX)||(MODULE_CLASS == STM32F407XX))


//#define NET_NEW_VER

///* TCP and ARP timeouts */
//volatile int tcp_end_time, arp_end_time;
//
///* Define those to better describe your network interface. */
#define IFNAME0 's'
#define IFNAME1 't'


OS_EVENT* OSQNetData;
#define NET_DATATBL_SIZE 8
//#ifdef NET_NEW_VER
INT32U OSQNetDataTbl[NET_DATATBL_SIZE];
//#else
//typedef struct
//{
//	INT16U   len;	        // 数据长度
//	INT8U    *p;	        // 数据指针	
//}NET_ISRDATA;	 

//static INT8U NETDataCnt = 0;
//NET_ISRDATA NetIsrData[NET_DATATBL_SIZE];
//NET_ISRDATA *OSQNetDataTbl[NET_DATATBL_SIZE];
//#endif

static  OS_STK   App_Task_Ethernetif_Input_Stk[LWIP_TASK_ETHERNETIF_INPUT_STK_SIZE];


err_t ethernetif_output(void *p_arg);


/**
 * In this function, the hardware should be initialized.
 * Called from ethernetif_init().
 *
 * @param netif the already initialized lwip network interface structure
 *        for this ethernetif
 */

static void low_level_init(struct netif *netif)
{
  	CPU_INT08U  os_err;
	
	os_err = os_err; /* prevent warning... */
  
  /* set MAC hardware address length */
  netif->hwaddr_len = ETHARP_HWADDR_LEN;

  /* set MAC hardware address */
  netif->hwaddr[0] =  UserVars.Para.MACAddr[0];
  netif->hwaddr[1] =  UserVars.Para.MACAddr[1];
  netif->hwaddr[2] =  UserVars.Para.MACAddr[2];
  netif->hwaddr[3] =  UserVars.Para.MACAddr[3];
  netif->hwaddr[4] =  UserVars.Para.MACAddr[4];
  netif->hwaddr[5] =  UserVars.Para.MACAddr[5];

  /* maximum transfer unit */
  netif->mtu = 1500;

  /* device capabilities */
  /* don't set NETIF_FLAG_ETHARP if this device is not an ethernet one */
    netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_LINK_UP;

   

	OSQNetData = OSQCreate((void *)OSQNetDataTbl, NET_DATATBL_SIZE); // 创建写命令消息队列

	os_err = OSTaskCreate( (void (*)(void *)) ethernetif_input,				
	                       (void          * ) 0,							
	                       (OS_STK        * )&App_Task_Ethernetif_Input_Stk[LWIP_TASK_ETHERNETIF_INPUT_STK_SIZE - 1],		
	                       (INT8U           ) APP_TASK_ETHERNETIF_INPUT_PRIO  );							


    NET_Ctrl(CMD_NET_START, 0); // 启动网络                
}

/**
 * This function should do the actual transmission of the packet. The packet is
 * contained in the pbuf that is passed to the function. This pbuf
 * might be chained.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @param p the MAC packet to send (e.g. IP packet including MAC addresses and type)
 * @return ERR_OK if the packet could be sent
 *         an err_t value if the packet couldn't be sent
 *
 * @note Returning ERR_MEM here if a DMA queue of your MAC is full can lead to
 *       strange results. You might consider waiting for space in the DMA queue
 *       to become availale since the stack doesn't retry to send a packet
 *       dropped because of memory failure (except for the TCP timers).
 */
static err_t
low_level_output(struct netif *netif, struct pbuf *p)
{
    struct pbuf *q;
    INT8U *buffer;
    int l = 0, i;  
    
    //buffer = (INT8U *)NET_GetTxBuffer();    
    buffer = (INT8U *)NET_Ctrl(CMD_NET_GETTXBUF, 0);
    for(q = p; q != NULL; q = q->next) 
    {
        memcpy((INT8U *)&buffer[l], q->payload, q->len);
        l = l + q->len;
    }
    NET_Write(l);
    
//    printf("NET_TX:%d\r\n", l);
//    
//    printf("TX[%d]:", l);
//    for (i=0; i<l; i++)
//    {
//         printf("%02X ", buffer[i]);
//    }     
//     printf("\r\n");    
    return ERR_OK;
}


/**
 * Should allocate a pbuf and transfer the bytes of the incoming
 * packet from the interface into the pbuf.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return a pbuf filled with the received packet (including MAC header)
 *         NULL on memory error
 */

static struct pbuf *
low_level_input(struct netif *netif)
{
//    struct pbuf *p;
//    INT16U len;

//	//NET_RequestOSSem(0);
//	p = NULL;
//    len = NET_ReadDateLen();
//	if (len > 0)
//	{
//		p = pbuf_alloc(PBUF_LINK, len, PBUF_RAM);
//        //p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);
//		if (p != NULL)
//        {
//			 NET_Read(p);
//		}
//	}
//    //NET_ReleaseOSSem();
//    return p;
    return 0;
}


/**
 * This function should be called when a packet is ready to be read
 * from the interface. It uses the function low_level_input() that
 * should handle the actual reception of bytes from the network
 * interface. Then the type of the received packet is determined and
 * the appropriate input function is called.
 *
 * @param netif the lwip network interface structure for this ethernetif
 */


void ETH_ISRHook(INT32U Flag)
{
    if (Flag&ETH_DMA_IT_R)
    {    
        OSQPost(OSQNetData, (void *)Flag);
    }
}

/**
 * Should be called at the beginning of the program to set up the
 * network interface. It calls the function low_level_init() to do the
 * actual setup of the hardware.
 *
 * This function should be passed as a parameter to netif_add().
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return ERR_OK if the loopif is initialized
 *         ERR_MEM if private data couldn't be allocated
 *         any other err_t on error
 */
err_t
ethernetif_init(struct netif *netif)
{
  struct ethernetif *ethernetif;

  LWIP_ASSERT("netif != NULL", (netif != NULL));

//  ethernetif = mem_malloc(sizeof(struct ethernetif));
//  if (ethernetif == NULL)
//  {
//    LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_init: out of memory\n"));
//    return ERR_MEM;
//  }

#if LWIP_NETIF_HOSTNAME
  /* Initialize interface hostname */
  netif->hostname = "lwip";
#endif /* LWIP_NETIF_HOSTNAME */

  /*
   * Initialize the snmp variables and counters inside the struct netif.
   * The last argument should be replaced with your link speed, in units
   * of bits per second.
   */
  NETIF_INIT_SNMP(netif, snmp_ifType_ethernet_csmacd, 100000000);

  netif->state = ethernetif;
  netif->name[0] = IFNAME0;
  netif->name[1] = IFNAME1;
  /* We directly use etharp_output() here to save a function call.
   * You can instead declare your own function an call etharp_output()
   * from it if you have to do some checks before sending (e.g. if link
   * is available...) */
  netif->output = etharp_output;
  netif->linkoutput = low_level_output;

  //ethernetif->ethaddr = (struct eth_addr *)&(netif->hwaddr[0]);

  /* initialize the hardware */
  low_level_init(netif);

  return ERR_OK;
}




/**
 * This function should be called when a packet is ready to be read
 * from the interface. It uses the function low_level_input() that
 * should handle the actual reception of bytes from the network
 * interface. Then the type of the received packet is determined and
 * the appropriate input function is called.
 *
 * @param netif the lwip network interface structure for this ethernetif
 */

err_t ethernetif_input(void *p_arg)
{ 
	struct pbuf *p, *q;
    INT16U l, i, len;	
	INT32S flag;
	INT8U err, *buffer;	
    INT32U sta;
	struct netif *_netif;
	extern struct netif netif;

	(void)p_arg;

	_netif = &netif;

	while(1)
	{
		sta = (INT32U)OSQPend(OSQNetData, 2, &err);
		if ((err == OS_ERR_NONE)||(err == OS_ERR_TIMEOUT))
        {   
             flag = NET_Read((INT32U *)&buffer, &len);
             
             if ((flag == ERR_TRUE)&&(len>0))
             {
                //printf("NET_RX:%08X, %d\r\n", sta, len);
                p = pbuf_alloc(PBUF_LINK, len, PBUF_RAM);
                if (p != NULL)
                {
                    l = 0;
                    
//                    for (i=0; i<len; i++)
//                    {
//                        printf("%02X ", buffer[i]);
//                    }     
//                    printf("\r\n");
                    
                    for (q = p; q != NULL; q = q->next)
                    {
                        memcpy((INT8U *)q->payload, (INT8U *)&buffer[l], q->len);
                        l = l + q->len;
                    }  				
                    err = _netif->input(p, &netif);                
                    if( err != ERR_OK )
                    {
                        LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_input: IP input error\n\r"));
                        pbuf_free(p);
                        p = NULL;
                    }
                    //Delay_ms(100);
                }
             }
		}
	}
}


#endif

#if (MODULE_TYPE == STM32F103ZE)

#include <includes.h>


//INT8U MACaddr[6];



/* Define those to better describe your network interface. */
#define IFNAME0 's'
#define IFNAME1 't'

/**
 * Helper struct to hold private data used to operate your ethernet interface.
 * Keeping the ethernet address of the MAC in this struct is not necessary
 * as it is already kept in the struct netif.
 * But this is only an example, anyway...
 */
//struct ethernetif
//{
//  struct eth_addr *ethaddr;
//  /* Add whatever per-interface state that is needed here. */
//  int unused;
//};


/* Private variables ---------------------------------------------------------*/
//OS_EVENT* ethernetinput;


static  OS_STK   App_Task_Ethernetif_Input_Stk[LWIP_TASK_ETHERNETIF_INPUT_STK_SIZE];



//void Set_MAC_Address(INT8U* macadd)
//{
//  LibVars.Net.MACaddr[0] = macadd[0];
//  LibVars.Net.MACaddr[1] = macadd[1];
//  LibVars.Net.MACaddr[2] = macadd[2];
//  LibVars.Net.MACaddr[3] = macadd[3];
//  LibVars.Net.MACaddr[4] = macadd[4];
//  LibVars.Net.MACaddr[5] = macadd[5];

//  NET_Ctrl(CMD_NET_SETMACADDR, (INT32U)macadd);
//  
//  //ETH_MACAddressConfig(ETH_MAC_Address0, macadd);  
//}


/**
 * In this function, the hardware should be initialized.
 * Called from ethernetif_init().
 *
 * @param netif the already initialized lwip network interface structure
 *        for this ethernetif
 */

static void
low_level_init(struct netif *netif)
{
	CPU_INT08U  os_err;
	
	os_err = os_err; /* prevent warning... */
	
	SYS_ARCH_DECL_PROTECT(sr);
	
	/* set MAC hardware address length */
	netif->hwaddr_len = 6;
	
	/* set MAC hardware address */
	netif->hwaddr[0] = UserVars.Para.MACAddr[0];
	netif->hwaddr[1] = UserVars.Para.MACAddr[1];
	netif->hwaddr[2] = UserVars.Para.MACAddr[2];
	netif->hwaddr[3] = UserVars.Para.MACAddr[3];
	netif->hwaddr[4] = UserVars.Para.MACAddr[4];
	netif->hwaddr[5] = UserVars.Para.MACAddr[5];
	
	/* maximum transfer unit */
	netif->mtu = 1500;
	
	/* device capabilities */
	/* don't set NETIF_FLAG_ETHARP if this device is not an ethernet one */
	netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_LINK_UP;
	
	SYS_ARCH_PROTECT(sr);

	NET_Init();
    //NET_Ctrl(CMD_NET_INT, 1);
	
	SYS_ARCH_UNPROTECT(sr);
	os_err = OSTaskCreate( (void (*)(void *)) ethernetif_input,				
	                       (void          * ) 0,							
	                       (OS_STK        * )&App_Task_Ethernetif_Input_Stk[LWIP_TASK_ETHERNETIF_INPUT_STK_SIZE - 1],		
	                       (INT8U           ) APP_TASK_ETHERNETIF_INPUT_PRIO  );	

	Delay_ms(20);  
}

/**
 * This function should do the actual transmission of the packet. The packet is
 * contained in the pbuf that is passed to the function. This pbuf
 * might be chained.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @param p the MAC packet to send (e.g. IP packet including MAC addresses and type)
 * @return ERR_OK if the packet could be sent
 *         an err_t value if the packet couldn't be sent
 *
 * @note Returning ERR_MEM here if a DMA queue of your MAC is full can lead to
 *       strange results. You might consider waiting for space in the DMA queue
 *       to become availale since the stack doesn't retry to send a packet
 *       dropped because of memory failure (except for the TCP timers).
 */

static err_t
low_level_output(struct netif *netif, struct pbuf *p)
{
  err_t err;
    
  SYS_ARCH_DECL_PROTECT(sr);
  /* Interrupts are disabled through this whole thing to support multi-threading
	   transmit calls. Also this function might be called from an ISR. */
  SYS_ARCH_PROTECT(sr);

  /* Access to the EMAC is guarded using a semaphore. */
  //dm9000_tx( p );
  err = NET_Write(p);

  SYS_ARCH_UNPROTECT(sr);

  return err;
}

/**
 * Should allocate a pbuf and transfer the bytes of the incoming
 * packet from the interface into the pbuf.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return a pbuf filled with the received packet (including MAC header)
 *         NULL on memory error
 */
static struct pbuf *
low_level_input(struct netif *netif)
{
    struct pbuf *p;
    INT16U len;

	NET_RequestOSSem(0);
	p = NULL;
    //len = NET_ReadDateLen();
	len = NET_Ctrl(CMD_NET_GETRXLEN, 0);
    if (len > 0)
	{
		p = pbuf_alloc(PBUF_LINK, len, PBUF_RAM);
        if (p != NULL)
        {
			 NET_Read(p);
		}
	}
    NET_ReleaseOSSem();
    return p;
}

/**
 * This function should be called when a packet is ready to be read
 * from the interface. It uses the function low_level_input() that
 * should handle the actual reception of bytes from the network
 * interface. Then the type of the received packet is determined and
 * the appropriate input function is called.
 *
 * @param netif the lwip network interface structure for this ethernetif
 */

err_t ethernetif_input(struct netif *_netif)
{ 
	struct pbuf *p;
	INT32S flag;
	
	extern struct netif netif;
	
	_netif = &netif;
	
	//ethernetinput = OSSemCreate(0);	
	NETInt_CreateOSSem();
	
	for(;;)
	{		    
		//INT8U _err;
		
		//OSSemPend(ethernetinput,0,&_err);    
		flag = NET_PendRXIntOSFlag(0);
		if(flag == ERR_TRUE)
		{  	   
			for(;;)
			{	      
				p = low_level_input(_netif);
				if (p != NULL)
				{
					err_t err;
					/* move received packet into a new pbuf */	 
					err = _netif->input(p, &netif);
					if( err != ERR_OK )
					{
						LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_input: IP input error\n\r"));
						pbuf_free(p);
						p = NULL;
					}
				}
				else 
				{
					break;
				}
			}
		}
	}
}

/**
 * Should be called at the beginning of the program to set up the
 * network interface. It calls the function low_level_init() to do the
 * actual setup of the hardware.
 *
 * This function should be passed as a parameter to netif_add().
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return ERR_OK if the loopif is initialized
 *         ERR_MEM if private data couldn't be allocated
 *         any other err_t on error
 */
err_t
ethernetif_init(struct netif *netif)
{
  struct ethernetif *ethernetif;

  LWIP_ASSERT("netif != NULL", (netif != NULL));

//  ethernetif = mem_malloc(sizeof(struct ethernetif));
//  if (ethernetif == NULL)
//  {
//    LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_init: out of memory\n"));
//    return ERR_MEM;
//  }

#if LWIP_NETIF_HOSTNAME
  /* Initialize interface hostname */
  netif->hostname = "lwip";
#endif /* LWIP_NETIF_HOSTNAME */

  /*
   * Initialize the snmp variables and counters inside the struct netif.
   * The last argument should be replaced with your link speed, in units
   * of bits per second.
   */
  NETIF_INIT_SNMP(netif, snmp_ifType_ethernet_csmacd, 100000000);

  netif->state = ethernetif;
  netif->name[0] = IFNAME0;
  netif->name[1] = IFNAME1;
  /* We directly use etharp_output() here to save a function call.
   * You can instead declare your own function an call etharp_output()
   * from it if you have to do some checks before sending (e.g. if link
   * is available...) */
  netif->output = etharp_output;
  netif->linkoutput = low_level_output;

  //ethernetif->ethaddr = (struct eth_addr *)&(netif->hwaddr[0]);

  /* initialize the hardware */
  low_level_init(netif);

  return ERR_OK;
}
#endif




#else
void ETH_ISRHook(INT32U Flag)
{
    
}
#endif