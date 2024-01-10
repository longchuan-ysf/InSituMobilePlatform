#ifndef __ETHERNETIF_H__
#define __ETHERNETIF_H__

#include "config.h"


#if (MODULE_TYPE == STM32F103ZE)
#include "err.h"
#include "netif.h"

err_t ethernetif_init(struct netif *netif);
err_t ethernetif_input(struct netif *netif);
struct netif *ethernetif_register(void);
int ethernetif_poll(void);
//void Set_MAC_Address(unsigned char* macadd);

#else
#include "lwip/err.h"
#include "lwip/netif.h"

err_t ethernetif_init(struct netif *netif);
//err_t ethernetif_input(struct netif *netif);
err_t ethernetif_input(void *p_arg);
struct netif *ethernetif_register(void);
int ethernetif_poll(void);
#endif

#endif 
