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


#if (MODULE_TYPE == EMB8612I)

#include <includes.h>

/* 定义的MAC地址 */   
//#define emacETHADDR0   0x00
//#define emacETHADDR1   0x00
//#define emacETHADDR2   0x00
//#define emacETHADDR3   0x00
//#define emacETHADDR4   0x00
//#define emacETHADDR5   0x01

INT8U MACaddr[6];



/* Define those to better describe your network interface. */
#define IFNAME0 's'
#define IFNAME1 't'

/**
 * Helper struct to hold private data used to operate your ethernet interface.
 * Keeping the ethernet address of the MAC in this struct is not necessary
 * as it is already kept in the struct netif.
 * But this is only an example, anyway...
 */
struct ethernetif
{
  struct eth_addr *ethaddr;
  /* Add whatever per-interface state that is needed here. */
  int unused;
};


/* Private variables ---------------------------------------------------------*/
OS_EVENT* ethernetinput;
//#define  APP_TASK_ETHERNETIF_INPUT_STK_SIZE				 512u
//#define  APP_TASK_ETHERNETIF_INPUT_PRIO  (				   24)
//#define  APP_TASK_BLINK_PRIO          	 (                 25)


static  OS_STK   App_Task_Ethernetif_Input_Stk[LWIP_TASK_ETHERNETIF_INPUT_STK_SIZE];



void Set_MAC_Address(INT8U* macadd)
{
  MACaddr[0] = macadd[0];
  MACaddr[1] = macadd[1];
  MACaddr[2] = macadd[2];
  MACaddr[3] = macadd[3];
  MACaddr[4] = macadd[4];
  MACaddr[5] = macadd[5];

  NET_Ctrl(CMD_NET_SETMACADDR, (INT32U)macadd);
  
  //ETH_MACAddressConfig(ETH_MAC_Address0, macadd);  
}


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
	netif->hwaddr[0] = MACaddr[0];//emacETHADDR0;
	netif->hwaddr[1] = MACaddr[1];//emacETHADDR1;
	netif->hwaddr[2] = MACaddr[2];//emacETHADDR2;
	netif->hwaddr[3] = MACaddr[3];//emacETHADDR3;
	netif->hwaddr[4] = MACaddr[4];//emacETHADDR4;
	netif->hwaddr[5] = MACaddr[5];//emacETHADDR5;
	
	/* maximum transfer unit */
	netif->mtu = 1500;
	
	/* device capabilities */
	/* don't set NETIF_FLAG_ETHARP if this device is not an ethernet one */
	netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_LINK_UP;
	
	SYS_ARCH_PROTECT(sr);
	
	//hw_dm9000_init();
	NET_Init();
	//dm9000_init();	
	
	SYS_ARCH_UNPROTECT(sr);
	#if (TASKEXT_EN == 1)
	os_err = OSTaskCreateExt( (void (*)(void *)) ethernetif_input,				
	                       (void          * ) 0,							
	                       (OS_STK        * )&App_Task_Ethernetif_Input_Stk[LWIP_TASK_ETHERNETIF_INPUT_STK_SIZE - 1],		
	                       (INT8U           ) APP_TASK_ETHERNETIF_INPUT_PRIO,  
						  (INT16U          ) APP_TASK_ETHERNETIF_INPUT_PRIO,
						  (OS_STK        * )&App_Task_Ethernetif_Input_Stk[0],
						  (INT32U          ) LWIP_TASK_ETHERNETIF_INPUT_STK_SIZE,
						  (void          * ) 0,
						  (INT16U          )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR)						   
						   );							
	
	#else
	os_err = OSTaskCreate( (void (*)(void *)) ethernetif_input,				
	                       (void          * ) 0,							
	                       (OS_STK        * )&App_Task_Ethernetif_Input_Stk[LWIP_TASK_ETHERNETIF_INPUT_STK_SIZE - 1],		
	                       (INT8U           ) APP_TASK_ETHERNETIF_INPUT_PRIO  );							
	
	#endif

	#if OS_TASK_NAME_EN > 0
	OSTaskNameSet(APP_TASK_BLINK_PRIO, "Task ethernetif_input", &os_err);
	#endif
	Delay_ms(20);  
//    EXInt_Ctrl(INT7_ID, 1);
//	dm9000_IntEna();
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

  SYS_ARCH_DECL_PROTECT(sr);
  /* Interrupts are disabled through this whole thing to support multi-threading
	   transmit calls. Also this function might be called from an ISR. */
  SYS_ARCH_PROTECT(sr);

  /* Access to the EMAC is guarded using a semaphore. */
  //dm9000_tx( p );
  NET_Write(p);

  SYS_ARCH_UNPROTECT(sr);

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
    struct pbuf *p;
    INT16U len;

	NET_RequestOSSem(0);
	p = NULL;
    len = NET_ReadDateLen();
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

  ethernetif = mem_malloc(sizeof(struct ethernetif));
  if (ethernetif == NULL)
  {
    LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_init: out of memory\n"));
    return ERR_MEM;
  }

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

  ethernetif->ethaddr = (struct eth_addr *)&(netif->hwaddr[0]);

  /* initialize the hardware */
  low_level_init(netif);

  return ERR_OK;
}

#else
#include <includes.h>
////#include "main.h"
//#include "stm32_eth.h"
//
//
///* TCP and ARP timeouts */
//volatile int tcp_end_time, arp_end_time;
//
///* Define those to better describe your network interface. */
#define IFNAME0 's'
#define IFNAME1 't'
//
///**
// * Helper struct to hold private data used to operate your ethernet interface.
// * Keeping the ethernet address of the MAC in this struct is not necessary
// * as it is already kept in the struct netif.
// * But this is only an example, anyway...
// */
struct ethernetif
{
  struct eth_addr *ethaddr;
  /* Add whatever per-interface state that is needed here. */
  int unused;
};

INT8U MACaddr[6];

/* Private variables ---------------------------------------------------------*/

OS_EVENT* OSQNetData;
#define NET_DATATBL_SIZE 32

typedef struct
{
	INT16U   len;	        // 数据长度
	INT8U    *p;	        // 数据指针	
}NET_ISRDATA;	 

static INT8U NETDataCnt = 0;
NET_ISRDATA NetIsrData[NET_DATATBL_SIZE];
NET_ISRDATA *OSQNetDataTbl[NET_DATATBL_SIZE];

//#define  APP_TASK_ETHERNETIF_INPUT_STK_SIZE				 512u
//#define  APP_TASK_ETHERNETIF_INPUT_PRIO  (				   24)
//#define  APP_TASK_BLINK_PRIO          	 (                 25)


static  OS_STK   App_Task_Ethernetif_Input_Stk[LWIP_TASK_ETHERNETIF_INPUT_STK_SIZE];


err_t ethernetif_output(void *p_arg);
/**
 * Setting the MAC address.
 *
 * @param netif the already initialized lwip network interface structure
 *        for this ethernetif
 */
void Set_MAC_Address(INT8U* macadd)
{
  MACaddr[0] = macadd[0];
  MACaddr[1] = macadd[1];
  MACaddr[2] = macadd[2];
  MACaddr[3] = macadd[3];
  MACaddr[4] = macadd[4];
  MACaddr[5] = macadd[5];
  
  //ETH_MACAddressConfig(ETH_MAC_Address0, macadd);  
  NET_Ctrl(CMD_NET_SETMACADDR, (INT32U)macadd);
}


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
  
  /* set MAC hardware address length */
  netif->hwaddr_len = ETHARP_HWADDR_LEN;

  /* set MAC hardware address */
  netif->hwaddr[0] =  MACaddr[0];
  netif->hwaddr[1] =  MACaddr[1];
  netif->hwaddr[2] =  MACaddr[2];
  netif->hwaddr[3] =  MACaddr[3];
  netif->hwaddr[4] =  MACaddr[4];
  netif->hwaddr[5] =  MACaddr[5];

  /* maximum transfer unit */
  netif->mtu = 1500;

  /* device capabilities */
  /* don't set NETIF_FLAG_ETHARP if this device is not an ethernet one */
    netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_LINK_UP;

   

	OSQNetData = OSQCreate((void *)OSQNetDataTbl, NET_DATATBL_SIZE); // 创建写命令消息队列
	NET_Init();
	
	printf("aa\r\n");
  	//SYS_ARCH_UNPROTECT(sr);
	#if (TASKEXT_EN == 1)
	os_err = OSTaskCreateExt( (void (*)(void *)) ethernetif_output,				
	                       (void          * ) 0,							
	                       (OS_STK        * )&App_Task_Ethernetif_Input_Stk[LWIP_TASK_ETHERNETIF_INPUT_STK_SIZE - 1],		
	                       (INT8U           ) APP_TASK_ETHERNETIF_INPUT_PRIO,  
						  (INT16U          ) APP_TASK_ETHERNETIF_INPUT_PRIO,
						  (OS_STK        * )&App_Task_Ethernetif_Input_Stk[0],
						  (INT32U          ) LWIP_TASK_ETHERNETIF_INPUT_STK_SIZE,
						  (void          * ) 0,
						  (INT16U          )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR)						   
						   );							
	
	#else
	os_err = OSTaskCreate( (void (*)(void *)) ethernetif_output,				
	                       (void          * ) 0,							
	                       (OS_STK        * )&App_Task_Ethernetif_Input_Stk[LWIP_TASK_ETHERNETIF_INPUT_STK_SIZE - 1],		
	                       (INT8U           ) APP_TASK_ETHERNETIF_INPUT_PRIO  );							
	
	#endif

	#if OS_TASK_NAME_EN > 0
	OSTaskNameSet(APP_TASK_BLINK_PRIO, "Task ethernetif_input", &os_err);
	#endif
	
	Delay_ms(20);  
//    EXInt_Ctrl(INT7_ID, 1);
//	dm9000_IntEna();
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

  //SYS_ARCH_DECL_PROTECT(sr);
  /* Interrupts are disabled through this whole thing to support multi-threading
	   transmit calls. Also this function might be called from an ISR. */
  //SYS_ARCH_PROTECT(sr);

  /* Access to the EMAC is guarded using a semaphore. */
  //dm9000_tx( p );
  NET_Write(p);

  //SYS_ARCH_UNPROTECT(sr);

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
    struct pbuf *p;
    INT16U len;

	//NET_RequestOSSem(0);
	p = NULL;
    len = NET_ReadDateLen();
	if (len > 0)
	{
		p = pbuf_alloc(PBUF_LINK, len, PBUF_RAM);
        //p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);
		if (p != NULL)
        {
			 NET_Read(p);
		}
	}
    //NET_ReleaseOSSem();
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


//err_t ethernetif_input(struct netif *netif)
//{
//  	err_t err;
//  	struct pbuf *p;
//
//  	/* move received packet into a new pbuf */
//  	p = low_level_input(netif);
//
//  	/* no packet could be read, silently ignore this */
//  	if (p == NULL) 
//	{
//		return ERR_MEM;
//	}
//
//	err = OSQPost(OSQNetData, p);
//	if (err != OS_ERR_NONE)
//	{
//		pbuf_free(p);
//    	p = NULL;
//	}
//	return err;
//
//  	/*
//	err = netif->input(p, netif);
//  	if (err != ERR_OK)
//  	{
//    	LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_input: IP input error\n"));
//    	pbuf_free(p);
//    	p = NULL;
//  	}
//  	return err;
//	*/
//}

err_t ethernetif_input(struct netif *netif)
{
  	err_t err;
  	//struct pbuf *p;
	INT32S flag;
	//NET_ISRDATA NetData;
  	/* move received packet into a new pbuf */
  	//p = low_level_input(netif);
	flag = NET_ISRRead((INT32U *)&NetIsrData[NETDataCnt].p, &NetIsrData[NETDataCnt].len);
  	/* no packet could be read, silently ignore this */
	if (flag == ERR_TRUE)
	{
		if ((NetIsrData[NETDataCnt].len>0)&&(NetIsrData[NETDataCnt].p!=0))
		{
			 err = OSQPost(OSQNetData, &NetIsrData[NETDataCnt]);
			 NETDataCnt++;
			 if (NETDataCnt>=NET_DATATBL_SIZE)
			 {
				 NETDataCnt = 0;
			 }
		}
	}
	/*
  	if (p == NULL) 
	{
		return ERR_MEM;
	}

	
	if (err != OS_ERR_NONE)
	{
		pbuf_free(p);
    	p = NULL;
	}
	return err;
	*/
	return 0;
}
//static INT8U NETDataCnt = 0;
//NET_ISRDATA NetIsrData[NET_DATATBL_SIZE];

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

  ethernetif = mem_malloc(sizeof(struct ethernetif));
  if (ethernetif == NULL)
  {
    LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_init: out of memory\n"));
    return ERR_MEM;
  }

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

  ethernetif->ethaddr = (struct eth_addr *)&(netif->hwaddr[0]);

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
//extern void BSP_IntEn(INT32U int_id);
err_t ethernetif_output(void *p_arg)
{ 
	struct pbuf *p, *q;
    INT16U l;	
	INT32S flag;
	INT8U err, *buffer;	
	NET_ISRDATA *NetData;
	struct netif *_netif;
	extern struct netif netif;

	(void)p_arg;

	_netif = &netif;

	while(1)
	{
		NetData = OSQPend(OSQNetData, 10, &err);
		if(err == OS_ERR_NONE)
		{  	   
			p = pbuf_alloc(PBUF_LINK, NetData->len, PBUF_RAM);
        	if (p != NULL)
        	{
				//NET_Read(p);
				l = 0;
				buffer = NetData->p;
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
			}
		}
	}
}
#endif

#endif
//
//struct pbuf *q;
//  INT16U len;
//  int l =0;
//  //FrameTypeDef frame;
//  u8 *buffer;
//  
//  //p = NULL;
//  //ETHFrame = ETH_RxPkt_ChainMode();
//  /* Obtain the size of the packet and put it into the "len"
//     variable. */
//  //len = frame.length;
//  
//  buffer = (u8 *)ETHFrame.buffer;
//
//  /* We allocate a pbuf chain of pbufs from the pool. */
//  //p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);
//
//    for (q = p; q != NULL; q = q->next)
//    {
//	  memcpy((INT8U *)q->payload, (INT8U *)&buffer[l], q->len);
//      l = l + q->len;
//    }    



//  err_t
//ethernetif_input(struct netif *netif)
//{
//  err_t err;
//  struct pbuf *p;
//
//  /* move received packet into a new pbuf */
//  p = low_level_input(netif);
//
//  /* no packet could be read, silently ignore this */
//  if (p == NULL) return ERR_MEM;
//
//  err = netif->input(p, netif);
//  if (err != ERR_OK)
//  {
//    LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_input: IP input error\n"));
//    pbuf_free(p);
//    p = NULL;
//  }
//
//  return err;
//}