#ifndef __SYS_ARCH_H__
#define __SYS_ARCH_H__

#include    "os_cpu.h"
#include    "os_cfg.h"
#include    "ucos_ii.h"


#define SYS_MBOX_NULL   (void*)0
#define SYS_SEM_NULL    (void*)0
#define MAX_QUEUES             20
#define MAX_QUEUE_ENTRIES      20

typedef struct {
    OS_EVENT*   pQ;
    void*       pvQEntries[MAX_QUEUE_ENTRIES];
} TQ_DESCR, *PQ_DESCR;
    
typedef OS_EVENT* sys_sem_t;
typedef OS_EVENT* sys_mutex_t;
//typedef PQ_DESCR  sys_mbox_t;
typedef TQ_DESCR*  sys_mbox_t;
typedef INT8U      sys_thread_t;

#endif
