/***************************************************************************************************
                                   xxxxx公司


文件:   Fifo.h
作者:
说明:   FIFO队列.
***************************************************************************************************/
#ifndef __FIFO_H__                     //防重包含.
#define __FIFO_H__
/**************************************************************************************************/

/***************************************************************************************************
包含:   头文件.
***************************************************************************************************/

#include <stdint.h>

typedef struct
{
  uint32_t len;/*队列长度*/
	uint32_t in;/*入队列变量*/
	uint32_t out;/*出队列变量*/
	uint32_t trial;/*读数据变量*/
	uint8_t *data;/*数据*/
}CFifo;

typedef struct
{
    CFifo  rxFifo;/*接收队列*/
    CFifo  txFifo;/*发送队列*/
}ComFifoStruct;

/***************************************************************************************************
申明:   公有变量.
***************************************************************************************************/


/***************************************************************************************************
申明:   公有方法.
***************************************************************************************************/
extern uint32_t fifo_data_length(CFifo *bp);
extern uint32_t fifo_try_len(CFifo *bp);
extern void fifo_init(CFifo *bp, uint32_t size);
extern void fifo_reset(CFifo *bp);
extern uint32_t fifo_in(CFifo *bp, uint8_t *data, uint32_t len);
extern uint32_t fifo_in_forcibly(CFifo *bp, uint8_t *data, uint32_t len);
extern uint32_t fifo_try(CFifo *bp, uint8_t *data, uint32_t maxlen);
extern uint32_t fifo_out(CFifo *bp, uint8_t *data, uint32_t maxlen);
extern void fifo_out_sync(CFifo *bp);
extern void fifo_untry(CFifo *bp);
extern uint32_t fifo_untried_len(CFifo *bp);
/**************************************************************************************************/
#endif  //__FIFO_H__
/***************************************************************************************************
文件结束.
***************************************************************************************************/
