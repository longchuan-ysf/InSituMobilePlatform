/*
 * Copyright (c) 2001, Swedish Institute of Computer Science.
 * All rights reserved. 
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions 
 * are met: 
 * 1. Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer. 
 * 2. Redistributions in binary form must reproduce the above copyright 
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the distribution. 
 * 3. Neither the name of the Institute nor the names of its contributors 
 *    may be used to endorse or promote products derived from this software 
 *    without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND 
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE 
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS 
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY 
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF 
 * SUCH DAMAGE. 
 *
 * This file is part of the lwIP TCP/IP stack.
 * 
 * Author: Adam Dunkels <adam@sics.se>
 *
 * $Id: sys_arch.c,v 1.1.1.1 2003/05/17 05:06:56 chenyu Exp $
 */
#include "config.h"
#if (LWIP_EN == 1)

#include "../include/lwip/debug.h"

#include "../include/lwip/def.h"
#include "../include/lwip/sys.h"
#include "../include/lwip/mem.h"

//yangye 2003-1-22
#include "sys_arch.h" 
//yangye 2003-1-27
//notice: we use OSTaskQuery in sys_arch_timeouts() !
//#include "ucos_ii.h"
//#include "os_cfg.h"


const void * const pvNullPointer;

static OS_MEM *pQueueMem;

static char pcQueueMemoryPool[MAX_QUEUES * sizeof(TQ_DESCR) ];

//yangye 2003-1-27
//struct sys_timeouts lwip_timeouts[LWIP_TASK_MAX];
//struct sys_timeouts null_timeouts;

static OS_TCB curr_task_pcb;

OS_STK LWIP_TASK_STK[LWIP_TASK_MAX][LWIP_STK_SIZE];
u8_t curr_prio_offset;

/*-----------------------------------------------------------------------------------*/
/*
sys_mbox_t sys_mbox_new(void)
{
    u8_t       ucErr;
    PQ_DESCR    pQDesc;
    
    pQDesc = OSMemGet( pQueueMem, &ucErr );
    if( ucErr == OS_NO_ERR ) {   
        pQDesc->pQ = OSQCreate( &(pQDesc->pvQEntries[0]), MAX_QUEUE_ENTRIES );       
        if( pQDesc->pQ != NULL ) {
            return pQDesc;
        }
    } 
    return SYS_MBOX_NULL;
}
*/

err_t sys_mbox_new(sys_mbox_t *mbox, int size)
{
    u8_t       ucErr;
    TQ_DESCR   *pQDesc;	  
	    
    pQDesc = OSMemGet(pQueueMem, &ucErr);
    if( ucErr == OS_NO_ERR ) 
	{   
        pQDesc->pQ = OSQCreate( &(pQDesc->pvQEntries[0]), MAX_QUEUE_ENTRIES);       
        if(pQDesc->pQ != NULL ) 
		{
            *mbox = pQDesc;
			return ERR_OK;
        }
    } 
	return ERR_MEM;
}

/*-----------------------------------------------------------------------------------*/
void
sys_mbox_free(sys_mbox_t *mbox)
{
    u8_t     ucErr;
    
    //clear OSQ EVENT
    OSQFlush((*mbox)->pQ);
    //del OSQ EVENT
    (void)OSQDel((*mbox)->pQ, OS_DEL_NO_PEND, &ucErr);
    //put mem back to mem queue
    ucErr = OSMemPut(pQueueMem, *mbox);
}

/*-----------------------------------------------------------------------------------*/
void
sys_mbox_post(sys_mbox_t *mbox, void *data)
{
    if( !data ) 
	{
		data = (void*)&pvNullPointer;
	}
    (void)OSQPost((*mbox)->pQ, data);
}

/*-----------------------------------------------------------------------------------*/
//u32_t
//sys_arch_mbox_fetch(sys_mbox_t *mbox, void **data, u32_t timeout)
//{
//    u8_t     ucErr;
//    u16_t ucos_timeout;
//  //yangye 2003-1-27
//  //in lwip ,timeout is  millisecond 
//  //in ucosII ,timeout is timer  tick! 
//  //chang timeout from millisecond to ucos tick
//  ucos_timeout = 0;
//  if(timeout != 0){
//  ucos_timeout = (timeout * OS_TICKS_PER_SEC)/1000;
//  if(ucos_timeout < 1)
//  	ucos_timeout = 1;
//  else if(ucos_timeout > 65535)
//  	ucos_timeout = 65535;
//  }  
//    
//  //yangye 2003-1-29
//  //it is very importent!!!! 
//  //sometimes lwip calls sys_mbox_fetch(mbox,NULL)
//  //it is dangrous to return (void *) to NULL ! (from OSQPend())
//  if(data != NULL){
//    *data = OSQPend((*mbox)->pQ, (u16_t)ucos_timeout, &ucErr );        
//  }else{
//    //just discard return value if data==NULL
//    OSQPend((*mbox)->pQ,(u16_t)ucos_timeout,&ucErr);
//  }
//    
//  if( ucErr == OS_TIMEOUT ) {
//        timeout = SYS_ARCH_TIMEOUT;
//    } else {
//      if(*data == (void*)&pvNullPointer ) 
//	  *data = NULL;
//      timeout = 1;
//    }
//  return timeout;
//}

u32_t
sys_arch_mbox_fetch(sys_mbox_t *mbox, void **data, u32_t timeout)
{
    u8_t     ucErr;
    u16_t ucos_timeout;
	u32_t start, end;
  //yangye 2003-1-27
  //in lwip ,timeout is  millisecond 
  //in ucosII ,timeout is timer  tick! 
  //chang timeout from millisecond to ucos tick
  ucos_timeout = 0;
  if(timeout != 0){
  ucos_timeout = (timeout * OS_TICKS_PER_SEC)/1000;
  if(ucos_timeout < 1)
  	ucos_timeout = 1;
  else if(ucos_timeout > 65535)
  	ucos_timeout = 65535;
  }  
    
  //yangye 2003-1-29
  //it is very importent!!!! 
  //sometimes lwip calls sys_mbox_fetch(mbox,NULL)
  //it is dangrous to return (void *) to NULL ! (from OSQPend())
  start = OSTimeGet();
  if(data != NULL){
    *data = OSQPend((*mbox)->pQ, (u16_t)ucos_timeout, &ucErr );        
  }else{
    //just discard return value if data==NULL
    OSQPend((*mbox)->pQ,(u16_t)ucos_timeout,&ucErr);
  }
  
  if(ucErr == OS_TIMEOUT) 
  {
        timeout = SYS_ARCH_TIMEOUT;
  } 
  else if (ucErr == OS_ERR_NONE)
  {
        if(*data == (void*)&pvNullPointer)
	  { 
	  	 *data = NULL;
	  }
      timeout = 1;
//      if((*data == (void*)&pvNullPointer)||(*data == 0))	  //EmbedARM:2014.11.17, *data有可能是0
//	  //if(*data == (void*)&pvNullPointer)
//	  { 
//	  	 *data = NULL;
//		 //printf("*data = NULL\r\n");
//		 //Delay_ms(100);
//		  //timeout = SYS_ARCH_TIMEOUT;  //EmbedARM:2014.11.17
//	  }
//	  //else
//	  //{
//      	  end = OSTimeGet();
//		  timeout = (end - start)*10;
//		  if (timeout<1)
//		  {
//			  timeout =1;
//		  }
//	  //}
  }
  else
  {
	  timeout = SYS_ARCH_TIMEOUT;
  }
  return timeout;
}

u32_t sys_arch_mbox_tryfetch(sys_mbox_t *mbox, void **msg)
{
    u8_t     ucErr;
    //u16_t ucos_timeout;
    
  //yangye 2003-1-29
  //it is very importent!!!! 
  //sometimes lwip calls sys_mbox_fetch(mbox,NULL)
  //it is dangrous to return (void *) to NULL ! (from OSQPend())
  if(msg != NULL)
  {
      *msg = OSQPend((*mbox)->pQ, 1, &ucErr );      
  }
  else
  {
      //just discard return value if data==NULL
      OSQPend((*mbox)->pQ, 1, &ucErr); 
  }
	
	//if (ucErr == OS_ERR_NONE)
  if ((ucErr == OS_ERR_NONE)&&(*msg != (void*)&pvNullPointer)) // 2014.5.5
	{
	    return OS_ERR_NONE;
  }
  else
  {
	    return SYS_MBOX_EMPTY;
  }


}

/** Try to post a message to an mbox - may fail if full or ISR
 * @param mbox mbox to posts the message
 * @param msg message to post (ATTENTION: can be NULL) */
err_t sys_mbox_trypost(sys_mbox_t *mbox, void *msg)
{
    INT8U flag;
	if(!msg) 
	{
		msg = (void*)&pvNullPointer;
	}
	flag = OSQPostFront ((*mbox)->pQ, msg);
	//flag = OSQPost((*mbox)->pQ, msg);  //EmbedARM: 2014.11.17

	return flag;
}

  

/** Check if an mbox is valid/allocated: return 1 for valid, 0 for invalid */
int sys_mbox_valid(sys_mbox_t *mbox)
{
    return ((*mbox) != 0 ? 1 : 0);
}

void sys_mbox_set_invalid(sys_mbox_t *mbox)
{
    *mbox = 0;
}

/*-----------------------------------------------------------------------------------*/
/*
sys_sem_t sys_sem_new(u8_t count)
{
    sys_sem_t pSem;
    pSem = OSSemCreate((u16_t)count );
    return pSem;
}
*/
err_t sys_sem_new(sys_sem_t *sem, u8_t count)
{
	*sem = OSSemCreate((u16_t)count);
    if (*sem!=(void *)0)
	{
		return ERR_OK;
	}
	else
	{
		return ERR_MEM;
	}
}

int sys_sem_valid(sys_sem_t *sem)
{
    return ((*sem) != 0 ? 1 : 0);
}
void sys_sem_set_invalid(sys_sem_t *sem)
{
	*sem = 0;
}

/*-----------------------------------------------------------------------------------*/
err_t sys_mutex_new(sys_mutex_t *mutex)
{
    INT8U perr;

	*mutex = OSMutexCreate (APP_MutexLMIP_PRIO, &perr);
	if (perr == OS_ERR_NONE)
	{
		return ERR_OK;
	}
	else
	{
		return ERR_MEM;
	}
}

void sys_sem_signal(sys_sem_t *sem)
{
    u8_t     ucErr;
    ucErr = OSSemPost((OS_EVENT *)*sem);
}

void sys_mutex_lock(sys_mutex_t *mutex)
{
    INT8U perr;

	OSMutexPend (*mutex, 0, &perr);
}

void sys_mutex_unlock(sys_mutex_t *mutex)
{
	OSMutexPost(*mutex);
}

void sys_mutex_free(sys_mutex_t *mutex)
{
	INT8U perr;

	OSMutexDel (*mutex, OS_DEL_ALWAYS, &perr);
} 

/*-----------------------------------------------------------------------------------*/
//yangye 2003-1-25
u32_t sys_arch_sem_wait(sys_sem_t *sem, u32_t timeout)
{
	u8_t err;
	u32_t ucos_timeout;
	//yangye 2003-1-27
	//in lwip ,timeout is  millisecond 
	//in ucosII ,timeout is timer  tick! 
	//chang timeout from millisecond to ucos tick
	ucos_timeout = 0;
	if(timeout != 0)
	{
		ucos_timeout = (timeout * OS_TICKS_PER_SEC)/1000;
		if(ucos_timeout < 1)
		{
			ucos_timeout = 1;
		}
		else if(ucos_timeout > 65535)
		{
			ucos_timeout = 65535;
		}
	}
	
	OSSemPend ((OS_EVENT *)*sem,(u16_t)ucos_timeout, (u8_t *)&err);
	//should not return 0 when wait time is 0, only when timeout!
	//see sys_arch.txt in lwip/doc 
	if(err == OS_TIMEOUT)
	{
		return SYS_ARCH_TIMEOUT;
	}
	else
	{
		return 1;
	}
}

/*-----------------------------------------------------------------------------------*/

void sys_sem_free(sys_sem_t *sem)
{
    u8_t     ucErr;
    (void)OSSemDel((OS_EVENT *)*sem, OS_DEL_NO_PEND, &ucErr );
}

u32_t sys_now(void)
{
    return 0;
}

/*-----------------------------------------------------------------------------------*/
void sys_init(void)
{
    u8_t i;
    //this func is called first in lwip task!
    u8_t   ucErr;
    //init mem used by sys_mbox_t
    //use ucosII functions
    pQueueMem = OSMemCreate( (void*)pcQueueMemoryPool, MAX_QUEUES, sizeof(TQ_DESCR), &ucErr );
    //init lwip task prio offset
    curr_prio_offset = 0;
    //init lwip_timeouts for every lwip task
//    for(i=0;i<LWIP_TASK_MAX;i++){
//    	lwip_timeouts[i].next = NULL;
//    }
}
/*-----------------------------------------------------------------------------------*/

/*----------------------------------------------------------------------*/
//struct sys_timeouts * sys_arch_timeouts(void)
//{
//  u8_t curr_prio;
//  s16_t err,offset;
// 
//    
//  null_timeouts.next = NULL;
//  //get current task prio
//  err = OSTaskQuery(OS_PRIO_SELF,&curr_task_pcb);
//  curr_prio = curr_task_pcb.OSTCBPrio;
//  
//  offset = curr_prio - LWIP_START_PRIO;
//  //not called by a lwip task ,return timeouts->NULL
//  if(offset < 0 || offset >= LWIP_TASK_MAX)
//  {
//    return &null_timeouts;
//  }
//
//  return &lwip_timeouts[offset];
//}
/*------------------------------------------------------------------------*/



//sys_thread_t
//sys_thread_new(void (* function)(void *arg), void *arg, int prio)
//{
//
//  if(curr_prio_offset < LWIP_TASK_MAX){
//  
//    OSTaskCreate(function, (void *)0x1111, &LWIP_TASK_STK[curr_prio_offset][LWIP_STK_SIZE-1],LWIP_START_PRIO+curr_prio_offset );
//    curr_prio_offset++; 
//  } else {
//    Uart_Printf(" lwip task prio out of range ! error! ");
//  }
//}

/** The only thread function:
 * Creates a new thread
 * @param name human-readable name for the thread (used for debugging purposes)
 * @param thread thread-function
 * @param arg parameter passed to 'thread'
 * @param stacksize stack size in bytes for the new thread (may be ignored by ports)
 * @param prio priority of the new thread (may be ignored by ports) */

sys_thread_t sys_thread_new(const char *name, lwip_thread_fn thread, void *arg, int stacksize, int prio)
{
  INT8U os_err;
  sys_thread_t flag;

  //flag = ERR_
  if(curr_prio_offset < LWIP_TASK_MAX)
  {
       #if (TASKEXT_EN == 1)
	   flag = OSTaskCreateExt((void (*)(void *))thread, 0, &LWIP_TASK_STK[curr_prio_offset][LWIP_STK_SIZE-1],LWIP_TASK_START_PRIO+curr_prio_offset,
						  (INT16U          ) LWIP_TASK_START_PRIO+curr_prio_offset,
						  (OS_STK        * )&LWIP_TASK_STK[curr_prio_offset][0],
						  (INT32U          ) LWIP_STK_SIZE,
						  (void          * ) 0,
						  (INT16U          )(OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR)
						   );
	   #else
	   flag = OSTaskCreate((void (*)(void *))thread, 0, &LWIP_TASK_STK[curr_prio_offset][LWIP_STK_SIZE-1],LWIP_TASK_START_PRIO+curr_prio_offset);
       #endif
	   
	   OSTaskNameSet((LWIP_TASK_START_PRIO+curr_prio_offset), (INT8U *)name, &os_err); 
	   curr_prio_offset++; 
  } 
  else 
  {
       printf(" lwip task prio out of range ! error! ");
  }

  return flag;
}

#endif
/**********************************************************************************************************/
//从lwip官网 http://savannah.nongnu.org/projects/lwip 下载源码包contrib-1.4.0(应用和接口示例)和lwip-1.4.0(协议栈核心).移植主要涉及到两面的工作 一个是操作系统信号量 邮箱 线程的接口 另一个是网络接口卡驱动部分.
//
//一、操作系统部分的移植:
//主要包含四个文件cc.h perf.h sys_arch.c sys_arch.h 可将这四个文件放置在ports/arch 文件夹下。cc.h主要是数据类型的定义和处理器(本人所有处理器为ARM11平台)字节序的定义 具体如下:
//#ifndef __CC_H__
//#define __CC_H__
//
//#ifndef BYTE_ORDER
//#define BYTE_ORDER      LITTLE_ENDIAN
//#endif
//
//#define LWIP_PROVIDE_ERRNO  1   // 在arch.h里需要这个宏
//
//typedef unsigned char   u8_t;
//typedef signed char     s8_t;
//typedef unsigned short  u16_t;
//typedef signed short    s16_t;
//typedef unsigned long   u32_t;
//typedef signed long     s32_t;
//
//typedef u32_t mem_ptr_t;
//
//#define U16_F "hu"
//#define S16_F "hd"
//#define X16_F "hx"
//#define U32_F "u"
//#define S32_F "d"
//#define X32_F "x"
//
//#define PACK_STRUCT_BEGIN // 如果为keil开发平台 只需定义__packed
//#define PACK_STRUCT_STRUCT  __attribute__ ((__packed__)) // 对应于GNU ARM 编译器
//#define PACK_STRUCT_END
//#define PACK_STRUCT_FIELD(x) x
//
//#ifndef LWIP_PLATFORM_DIAG
//#define LWIP_PLATFORM_DIAG(x)
//#endif
//
//#ifndef LWIP_PLATFORM_ASSERT
//#define LWIP_PLATFORM_ASSERT(x)
//#endif
//
//#endif
//
//perf.h 如下:
//#ifndef __PERF_H__
//#define __PERF_H__
//
//#define PERF_START    
//#define PERF_STOP(x)  
//
//#endif
//
//sys_arch.h 和sys_arch.c 为操作系统接口的核心文件具体如下:
//sys_arch.h:
//#ifndef __SYS_ARCH_H__
//#define __SYS_ARCH_H__
//
//#include <fapi/sys_services.h>
//#include <rtos/rtos.h>
//
//// 消息队列中消息的最大个数
//#define MAX_MAIL_QUEUES     128
//// LWIP  MUTEX 使用信号量实现 sys.h里用到此宏
//#define LWIP_COMPAT_MUTEX   1
//
//typedef u32_t           sys_sem_t;
//typedef u32_t           sys_mbox_t;
//typedef RTOS_ThreadT    sys_thread_t;
//typedef u32_t           sys_prot_t;
//
//#define SYS_ARCH_DECL_PROTECT(lev)  sys_prot_t lev
//#define SYS_ARCH_PROTECT(lev) RTOS_EnterCritical(lev)
//#define SYS_ARCH_UNPROTECT(lev) RTOS_LeaveCritical(lev)
//#endif
//
//sys_arch.c为操作系统接口源码 所有函数的申明均在lwip/sys.h中 具体如下：
//#include "lwip/def.h"
//#include "lwip/sys.h"
//#include "lwip/mem.h"
//#include "arch/sys_arch.h"
//// 系统初始化
//void sys_init(void)
//{
//}
//// 创建信号量
//err_t sys_sem_new(sys_sem_t *sem, u8_t count)
//{
//    *sem = (sys_sem_t)RTOS_CreateSemaphore((u32_t)count);
//    if(*sem != 0)
//        return ERR_OK;
//    else
//        return ERR_MEM;
//}
////  释放信号量
//void sys_sem_free(sys_sem_t *sem)
//{
//    RTOS_DestroySemaphore((RTOS_SemaphoreT)(*sem));
//}
//// 给出信号量
//void sys_sem_signal(sys_sem_t *sem)
//{
//    RTOS_SetSemaphore((RTOS_SemaphoreT)(*sem), RTOS_NO_SUSPEND);
//}
//// 获取一个信号量 timeout = 0 表示永久等待
//u32_t sys_arch_sem_wait(sys_sem_t *sem, u32_t timeout)
//{
//    u32_t ret_val;
//
//    if(timeout == 0) { ret_val = RTOS_GetSemaphore((RTOS_SemaphoreT)(*sem), RTOS_SUSPEND); }
//    else { ret_val = RTOS_GetSemaphore((RTOS_SemaphoreT)(*sem), timeout); }
//
//    if(ret_val == 0)
//        return SYS_ARCH_TIMEOUT;
//    else
//        return timeout;
//}
//// 判断一个信号量是否有效
//int sys_sem_valid(sys_sem_t *sem)
//{
//    return (*sem != 0 ? 1 : 0);
//}
////  将信号量设置为无效
//void sys_sem_set_invalid(sys_sem_t *sem)
//{
//    *sem = 0;
//}
//// 创建一个新邮箱(实际创建的是消息队列)
//err_t sys_mbox_new(sys_mbox_t *mbox, int size)
//{
//    *mbox = (sys_mbox_t)RTOS_CreateMailqueue(MAX_MAIL_QUEUES, RTOS_MSG_IS_POINTER);
//    if(*mbox != 0)
//        return ERR_OK;
//    else
//        return ERR_MEM;
//}
//// 释放一个邮箱
//void sys_mbox_free(sys_mbox_t *mbox)
//{
//    RTOS_DestroyMailqueue((RTOS_MailqueueT)(*mbox));
//}
//// 阻塞发送邮件
//void sys_mbox_post(sys_mbox_t *mbox, void *msg)
//{
//    RTOS_SetMailqueue((RTOS_MailqueueT)(*mbox), msg, 0, RTOS_SUSPEND);
//}
//// 非阻塞
//err_t sys_mbox_trypost(sys_mbox_t *mbox, void *msg)
//{
//    if(RTOS_SetMailqueue((RTOS_MailqueueT)(*mbox), msg, 0, RTOS_NO_SUSPEND))
//        return ERR_OK;
//    else
//        return ERR_MEM;
//}
//// 接收邮件
//u32_t sys_arch_mbox_fetch(sys_mbox_t *mbox, void **msg, u32_t timeout)
//{
//    if(RTOS_GetMailqueue((RTOS_MailqueueT)(*mbox), msg, timeout))
//        return timeout;
//    else
//        return SYS_ARCH_TIMEOUT;
//}
//// 非阻塞接收邮件
//u32_t sys_arch_mbox_tryfetch(sys_mbox_t *mbox, void **msg)
//{
//    if(RTOS_GetMailqueue((RTOS_MailqueueT)(*mbox), msg, RTOS_NO_SUSPEND))
//        return 0;
//    else
//        return SYS_MBOX_EMPTY;
//}
//// 释放一个邮箱
//int sys_mbox_valid(sys_mbox_t *mbox)
//{
//    return (*mbox != 0 ? 1 : 0);
//}
//// 邮箱设置为无效状态
//void sys_mbox_set_invalid(sys_mbox_t *mbox)
//{
//    *mbox = 0;
//}
//// 创建一个线程
//sys_thread_t sys_thread_new(const char *name, lwip_thread_fn thread, void *arg, int stacksize, int prio)
//{
//    u32_t rtos_prio = RTOS_PRIORITY_HIGH;
//    if(prio <= 10) { rtos_prio = RTOS_PRIORITY_HIGH; }
//    else if(prio <= 20) { rtos_prio = RTOS_PRIORITY_MEDIUM; }
//    else { rtos_prio = RTOS_PRIORITY_LOW; }
//
//    return RTOS_CreateThread(NULL, stacksize, rtos_prio, (RTOS_ThreadFunctionT)thread, arg, NULL, name);
//}
//以上为操作系统部分
//
//二、网络接口卡部分：
// 网络接口卡主要是在enthernet.c中 lwip 默认将未实现的部分以注释形式留在那里 让用户自己实现
//代码如下:
//#include "lwip/opt.h"
//#include "lwip/def.h"
//#include "lwip/mem.h"
//#include "lwip/pbuf.h"
//#include "lwip/sys.h"
//#include <lwip/stats.h>
//#include <lwip/snmp.h>
//#include "netif/etharp.h"
//#include "netif/ppp_oe.h"
//
//#include "user_config.h"
//#include "lwip/tcpip.h"
//#include "lwip/ip_addr.h"
//#include <fapi/sys_services.h>
//#include <rtos/rtos.h>
//#include <fapi/drv_eth.h>
//
//#define IFNAME0 'e'
//#define IFNAME1 'n'
//#define ETHERNET_DEV_INDEX  0
//
//struct ethernetif {
//  struct eth_addr *ethaddr;
// 
//};
//
//static void  ethernetif_input(struct netif *netif);
//
//void ethernetif_receive(void *arg);
//
//static FAPI_SYS_HandleT eth_handle = 0;
//
//static void
//low_level_init(struct netif *netif)
//{
//
////  struct ethernetif *ethernetif = netif->state;
//  FAPI_ETH_MacT mac_addr;
//
// 
//  netif->hwaddr_len = ETHARP_HWADDR_LEN;
//
// 
//  FAPI_ETH_GetMacAddress(ETHERNET_DEV_INDEX, mac_addr);
//  memcpy(netif->hwaddr, mac_addr, NETIF_MAX_HWADDR_LEN);
//
// 
//  netif->mtu = 1500;
//
// 
// 
//  netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_LINK_UP;
//
// 
//}
//
//
//static err_t
//low_level_output(struct netif *netif, struct pbuf *p)
//{
////  struct ethernetif *ethernetif = netif->state;
//  struct pbuf *q;
//
//#if ETH_PAD_SIZE
//  pbuf_header(p, -ETH_PAD_SIZE);
//#endif
//
//  for(q = p; q != NULL; q = q->next) {
//   
//       if(q->next == NULL) {
//           
//            FAPI_ETH_Write(eth_handle, q->payload, q->len, FAPI_ETH_FRAME_END);
//       }
//       else {
//           
//            FAPI_ETH_Write(eth_handle, q->payload, q->len, FAPI_ETH_FRAME_NOTEND);
//       }
//  }
//#if ETH_PAD_SIZE
//  pbuf_header(p, ETH_PAD_SIZE);
//#endif
/***********************************************************************************************************/
