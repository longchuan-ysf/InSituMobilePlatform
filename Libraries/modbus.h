/************************************************************************************
*  Copyright (c), 2004-2019, 北京中嵌凌云电子有限公司
*            All rights reserved.
*
* http:  www.embedarm.com
* Email: embedarm@126.com
*
* File name: moubus.h
* Project  : STM32F1XX/4XX系列模块驱动库
* Processor: STM32F1XX/4XX
* Compiler : RealView MDK-ARM Compiler
* 
* Author:  EmbedARM
* Version: 1.10
* Date:    2018.10.1			
* Email:   EmbedARM@126.com
* 
* Description: 本文件是MODBUS协议通信驱动程序头文件;
*
* Others: none;
*
* Function List: 1-9:是Modbus主机接口函数; 10: 是Modbus从机机接口函数;
*          1. INT32S Modbus_ReadCoils(INT8U ch, INT8U id, INT16U addr, INT16U len, INT8U *p, INT16U TimeOut);
*          2. INT32S Modbus_ReadDisInput(INT8U ch, INT8U id, INT16U addr, INT16U len, INT8U *p, INT16U TimeOut);
*          3. INT32S Modbus_ReadHoldReg(INT8U ch, INT8U id, INT16U addr, INT16U len, INT16U *p, INT16U TimeOut);
*          4. INT32S Modbus_ReadInputReg(INT8U ch, INT8U id, INT16U addr, INT16U len, INT16U *p, INT16U TimeOut);
*          5. INT32S Modbus_WriteSingleCoil(INT8U ch, INT8U id, INT16U addr, INT8U val, INT16U TimeOut);
*          6. INT32S Modbus_WriteSingleReg(INT8U ch, INT8U id, INT16U addr, INT16U val, INT16U TimeOut);
*          7. INT32S Modbus_WriteMulCoils(INT8U ch, INT8U id, INT16U addr, INT16U len, INT8U *p, INT16U TimeOut);
*          8. INT32S Modbus_WriteMulReg(INT8U ch, INT8U id, INT16U addr, INT16U len, INT16U *p, INT16U TimeOut);
*          9. INT32S Modbus_ReadWriteMulReg(INT8U ch, INT8U id, INT16U waddr, INT16U wlen, INT16U raddr, INT16U rlen, INT16U *p, INT16U TimeOut);
*          10. INT32S Modbus_Proc(INT8U ch, INT8U id, INT8U *p, INT16U len);
*		
* History:
*   1. Author:       EmbedARM  
*	   Version: 	 0.90
*	   Date:         2012.1.1
*      Modification: none
*
*************************************************************************************/
#ifndef __MODBUS_H 
#define __MODBUS_H 
/************************************************************************************/
// 引用外部头文件
/************************************************************************************/
#include  "const.h"
//#include  "config.h"
/************************************************************************************
// 常量及全局变量定义
*************************************************************************************/
#define MODBUS_OK_FLAG              0x0001  // 协议解析操作正确
#define MODBUS_READ_DISINPUT_FLAG   0x0002  // 读取离散输入量操作标志
#define MODBUS_READ_COILS_FLAG      0x0004  // 读取离散量操作标志
#define MODBUS_WRITE_COILS_FLAG     0x0008  // 写入离散量操作标志
#define MODBUS_READ_HOLDREG_FLAG    0x0004  // 读取保持寄存器操作
#define MODBUS_WRITE_HOLDREG_FLAG   0x0010  // 写入保持寄存器操作
#define MODBUS_READ_INPUTREG_FLAG   0x0020  // 读取输入寄存器操作
#define MODBUS_EXCEPTION_DATA_FLAG  0x0040  // 不合法数据错误
#define MODBUS_EXCEPTION_ADDR_FLAG  0x0080  // 不合法数据地址错误

#define MODBUS_DATA_LEN        64          // 设置协议缓存, 默认64(最大30个寄存器读写),用户可以根据MODBUS_MAX_HOLDREG和MODBUS_MAX_INPUTREG中最大值的2倍再加4即可
typedef struct
{
	INT16U Flag;
	INT16U len;
    INT8U  swcl[2];  // MODBUS TCP: 事物处理标识箱
    INT8U  xyid[2];  // MODBUS TCP: 协议标识符
    INT8U  dlen[2];  // MODBUS TCP: 长度
    INT8U  id;
	INT8U  cmd;
	INT8U  bytes;
	INT8U  buf[MODBUS_DATA_LEN];
}MODBUS_DATA;
#define MODBUS_TCP_ID  10   // MODBUS TCP 通信ID标识

//Flag: MODBUS从机参数标志
//MODBUS从机通信模式：bit0=0, RTU;  bit0=1, ASCII码; 
#define MODBUS_RTU_FLAG      0x0000      // RTU通信模式
#define MODBUS_ASCII_FLAG    0x0001      // ASCII通信模式
typedef struct
{
    INT16U Flag;	          // MODBUS从机参数标志
    INT16U CoilsBaseAddr;     // 线圈寄存器基地址;
    INT16U DisInputBaseAddr;  // 离散输入量寄存器基地址;
    INT16U HoldRegBaseAddr;   // 保持寄存器基地址;
    INT16U InputRegBaseAddr;  // 输入寄存器基地址;    
    INT16U MaxCoils;          // MODBUS从机最大线圈数量(读写,可用功能码:1,5,15);
    INT16U MaxDisInput;       // MODBUS从机最大离散输入量(只读,可用功能码:2);
    INT16U MaxHoldReg;        // MODBUS从机最大保持寄存器(读写,可用功能码:3,6,16,23)数量;	 
    INT16U MaxInputReg;       // MODBUS从机最大输入寄存器(只读,可用功能码:4)数量;
    
    INT8U  *pCoils;           // 输出线圈寄存器指针
    INT8U  *pDisInput;        // 输入离散输入量寄存器指针
    INT16U *pHoldReg;         // 保持寄存器指针
    INT16U *pInputReg;        // 输入寄存器指针
    
    MODBUS_DATA *pData;       // 操作缓存指针
}MODBUS_PARA; 

/************************************************************************************
//
//                 MODBUS主机通信驱动程序
//
*************************************************************************************/
/***********************************************************************************
* Function: Modbus_ReadCoils;
*
* Description: 主机读线圈请求函数，调用该函数发送读线圈请求   
*
* Input:  ch, 通讯管道号(UART1_ID,UART2_ID,UART3_ID,UART4_ID,UART5_ID)，如果向一个非主机的管道发送请求，将返回无效管道出错 
*         id, 从机的地址，1~255 
*         addr,线圈起始地址，取值范围为：0x0000~0xffff 
*         len, 读取线圈个数，取值范围为：0x001~0x07d0 
*         *p, 保存线圈值的指针，指向的地址类型为 8 位字符型。*p 字符的第0位值为第1个地址的值，
*         第7位为第8个地址的值，第9个线圈地址的值在*(p+1)地址的第0位
*         TimeOut: 执行超时时间，单位ms; 超过这个时间设备没有返回, 本函数返回超时错误代码
*
* Output: none;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   本函数Modbus协议功能代码是：01, 操作输出线圈;
************************************************************************************/
INT32S Modbus_ReadCoils(INT8U ch, INT8U id, INT16U addr, INT16U len, INT8U *p, INT16U TimeOut);
	
/***********************************************************************************
* Function: Modbus_ReadDisInput;
*
* Description: 主机读离散输入量请求函数，调用该函数发送读离散输入量请求  
*
* Input:  ch, 通讯管道号(UART1_ID,UART2_ID,UART3_ID,UART4_ID,UART5_ID)，如果向一个非主机的管道发送请求，将返回无效管道出错 
*         id, 从机的地址，1~255 
*         addr,离散输入量起始地址，取值范围为：0x0000~0xffff  
*         len, 读取离散输入量个数，取值范围为：0x001~0x07d0  
*         *p, 保存离散输入量值的指针，指向的地址类型为 8 位字符型。*p 字符的第0位值为第1个地址的值，
*         第7位为第8个地址的值，第9个离散输入量地址的值在*(p+1)地址的的第0位
*
* Output: none;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   本函数Modbus协议功能代码是：02, 操作离散输入量;
************************************************************************************/
INT32S Modbus_ReadDisInput(INT8U ch, INT8U id, INT16U addr, INT16U len, INT8U *p, INT16U TimeOut);

/***********************************************************************************
* Function: Modbus_ReadHoldReg;
*
* Description: 主机读保持寄存器请求函数，调用该函数发送读保持寄存器请求   
*
* Input:  ch, 通讯管道号(UART1_ID,UART2_ID,UART3_ID,UART4_ID,UART5_ID)，如果向一个非主机的管道发送请求，将返回无效管道出错 
*         id, 从机的地址，1~255 
*         addr,保持寄存器起始地址，取值范围为：0x0000~0xffff  
*         len, 读取保持寄存器个数，取值范围为：0x01~0x07d   
*         *p, 保存保持寄存器值的指针，指向的地址类型为 16 位无符号整型;
*         p 指向读出的第1个寄存器值存放的地址，
*
* Output: none;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   本函数Modbus协议功能代码是：03, 操作保持寄存器;
************************************************************************************/
INT32S Modbus_ReadHoldReg(INT8U ch, INT8U id, INT16U addr, INT16U len, INT16U *p, INT16U TimeOut);

/***********************************************************************************
* Function: Modbus_ReadInputReg;
*
* Description: 主机读输入寄存器请求函数，调用该函数发送读输入寄存器请求   
*
* Input:  ch, 通讯管道号(UART1_ID,UART2_ID,UART3_ID,UART4_ID,UART5_ID)，如果向一个非主机的管道发送请求，将返回无效管道出错 
*         id, 从机的地址，1~255 
*         addr,输入寄存器的起始地址，取值范围为：0x0000~0xffff  
*         len, 读取输入寄存器个数，取值范围为：0x01~0x07d    
*         *p, 保存输入寄存器值的指针，指向的地址类型为 16 位无符号整型;
*         p 指向读出的第1个寄存器值存放的地址，
*
* Output: none;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   本函数Modbus协议功能代码是：04, 操作输入寄存器;
************************************************************************************/
INT32S Modbus_ReadInputReg(INT8U ch, INT8U id, INT16U addr, INT16U len, INT16U *p, INT16U TimeOut);

/***********************************************************************************
* Function: Modbus_WriteSingleCoil;
*
* Description: 主机写单个线圈请求函数，调用该函数发送写单个线圈请求    
*
* Input:  ch, 通讯管道号(UART1_ID,UART2_ID,UART3_ID,UART4_ID,UART5_ID)，如果向一个非主机的管道发送请求，将返回无效管
*         id, 从机的地址，1~255 
*         addr, 写入线圈的地址，取值范围为：0x0000~0xffff 
*         val,  写入线圈的值：0, 关闭线圈; 1, 打开线圈; 
*
* Output: none;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   本函数Modbus协议功能代码是：05, 操作输出线圈;
************************************************************************************/
INT32S Modbus_WriteSingleCoil(INT8U ch, INT8U id, INT16U addr, INT8U val, INT16U TimeOut);

/***********************************************************************************
* Function: Modbus_WriteSingleReg;
*
* Description: 调用该函数发送写单个保持寄存器请求    
*
* Input:  ch, 通讯管道号(UART1_ID,UART2_ID,UART3_ID,UART4_ID,UART5_ID)，如果向一个非主机的管道发送请求，将返回无效管
*         id, 从机的地址，1~255 
*         addr, 写入保持寄存器的地址，取值范围为：0x0000~0xffff  
*         val,  写入保持寄存器的值，取值范围为：0x0000~0xffff 
*
* Output: none;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   本函数Modbus协议功能代码是：06, 操作保持寄存器;
************************************************************************************/
INT32S Modbus_WriteSingleReg(INT8U ch, INT8U id, INT16U addr, INT16U val, INT16U TimeOut);

/***********************************************************************************
* Function: Modbus_WriteMulCoils;
*
* Description: 调用该函数发送写多个线圈请求   
*
* Input:  ch, 通讯管道号(UART1_ID,UART2_ID,UART3_ID,UART4_ID,UART5_ID)，如果向一个非主机的管道发送请求，将返回无效管道出错 
*         id, 从机的地址，1~255 
*         addr,线圈起始地址，取值范围为：0x0000~0xffff 
*         len, 需写入线圈的个数，取值范围为：0x01~0x07b0
*         *p, 写入线圈数据缓冲的指针，指向的地址类型为8位字符型。*p 字符的第0位值为第1个地址的值，
*         第7位为第8个地址的值，第9个线圈地址的值在*(p+1)地址的第0位
*
* Output: none;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   本函数Modbus协议功能代码是：15, 操作输出线圈;
************************************************************************************/
INT32S Modbus_WriteMulCoils(INT8U ch, INT8U id, INT16U addr, INT16U len, INT8U *p, INT16U TimeOut);

/***********************************************************************************
* Function: Modbus_WriteMulReg;
*
* Description: 调用该函数发送写多个寄存器请求  
*
* Input:  ch, 通讯管道号(UART1_ID,UART2_ID,UART3_ID,UART4_ID,UART5_ID)，如果向一个非主机的管道发送请求，将返回无效管道出错 
*         id, 从机的地址，1~255 
*         addr, 保持寄存器起始地址，取值范围为：0x0000~0xffff 
*         len, 需写入保持寄存器的个数，取值范围为：0x01~0x078 
*         *p, 需写入保持寄存器的数据缓冲区的指针，指针类型为16位
*
* Output: none;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   本函数Modbus协议功能代码是：16, 操作保持寄存器;
************************************************************************************/
INT32S Modbus_WriteMulReg(INT8U ch, INT8U id, INT16U addr, INT16U len, INT16U *p, INT16U TimeOut);

/***********************************************************************************
* Function: Modbus_ReadWriteMulReg;
*
* Description: 调用该函数读和写多寄存器请求。执行该函数时，先写入后读出。
*
* Input:  ch, 通讯管道号(UART1_ID,UART2_ID,UART3_ID,UART4_ID,UART5_ID)，如果向一个非主机的管道发送请求，将返回无效管道出错 
*         id, 从机的地址，1~255 
*         waddr, 写入保持寄存器的起始地址，取值范围为：0x0000~0xffff 
*         wlen, 读出保持寄存器的个数，取值范围为：1~121 
*         raddr, 写入保持寄存器的起始地址，取值范围为：0x0000~0xffff 
*         rlen, 读出保持寄存器的个数，取值范围为：1~125 
*         *p, 需写入保持寄存器的数据缓冲区指针，同时也是读出寄存器数据存放缓冲区的指针 
*
* Output: none;
*
* Return: ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码;
*
* Note:   本函数Modbus协议功能代码是：23, 操作保持寄存器;
************************************************************************************/
INT32S Modbus_ReadWriteMulReg(INT8U ch, INT8U id, INT16U waddr, INT16U wlen, INT16U raddr, INT16U rlen, INT16U *p, INT16U TimeOut);

/************************************************************************************
//
//                 MODBUS从机通信驱动程序
//
*************************************************************************************/
/***********************************************************************************
* Function: Modbus_Proc;
*
* Description: MODBUS从机通信指令解析函数
*
* Input:  ch: 通信通道: UART1_ID~UART5_ID(0-4), MODBUS_TCP_ID(10); 
*         id: 本机设备ID(总线地址), 范围:1-250;
*         *p: 数据指针; len: 数据长度
*         *pPara: Modbus从机模式参数;
*
* Output: none;
*
* Return:  ERR_TRUE, 操作成功; 其它值, 参见const.h中错误代码; 
*
* Note:   none;
************************************************************************************/
INT32S Modbus_Proc(INT8U ch, INT8U id, INT8U *p, INT16U len, MODBUS_PARA *pPara);
	
#endif
/***********************************************************************************/
// 文件结束
/***********************************************************************************/
