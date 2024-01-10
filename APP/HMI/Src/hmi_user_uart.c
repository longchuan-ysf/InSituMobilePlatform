/************************************版权申明********************************************
**                             广州大彩光电科技有限公司
**                             http://www.gz-dc.com
**-----------------------------------文件信息--------------------------------------------
** 文件名称:   hmi_user_uart.c
** 修改时间:   2018-05-18
** 文件说明:   用户MCU串口驱动函数库
** 技术支持：  Tel: 020-82186683  Email: hmi@gz-dc.com Web:www.gz-dc.com
--------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------
使用必读
hmi_user_uart.c中的串口发送接收函数共3个函数：若移植到其他平台，需要修改,
但禁止修改函数名称，否则无法与HMI驱动库(hmi_driver.c)匹配。
--------------------------------------------------------------------------------------



----------------------------------------------------------------------------------------
1. 基于STM32平台串口驱动
----------------------------------------------------------------------------------------*/
#include "hmi_user_uart.h"
#include "cmd_queue.h"
//在中嵌凌云的EMB2628I上包含的头文件
#include "STM32Fxxx.h"
#include "UserVars.h"

/*!
*   \brief   串口初始化
*   \param   BaudRate-波特率设置
*/
void HMI_UartInit(uint32 BaudRate)
{
   //只要在配置头文件中打开Uart5就在Uart_APPInit初始化完成了，所以这个函数不需要实现
}

/*!
*   \brief  发送1个字节
*   \param  t 发送的字节
*/
void  HMI_SendChar(uchar t)
{
	Uart_Write(HMI_UART,&t,1);
}
/*!
*   \brief  从串口口中接收数据到命令队列中,可以放在串口中断中或者周期性轮询
*   \param  t 发送的字节
*/
void  HMI_UartRecieve(void)
{
	static uint32 rUart1Len;
	uint32 i,len;	
	
	len = Uart_Ctrl(HMI_UART, CMD_UART_GetCharsRxBuf,0); // 读取接收数据长度
	if ((len == rUart1Len)&&(len>0))                     // 间隔20ms读取, 如果2次读取接收数据长度大于0, 但还相等,说明缓存中已经收到完整一包数据，可以读取了  
	 {
		
		if (len>DATABUF_SIZE)                           // 如果接收数据长度大于DATABUF_SIZE(UserVars.buf)长度, 则赋值len = DATABUF_SIZE;
		{
		  len = DATABUF_SIZE;
		}
		Uart_Read(HMI_UART, UserVars.buf, len);         // 将数据读取到UserVars.buf中
	
		queue_pushString(UserVars.buf,len);
		UserVars.buf[len] = 0;

		rUart1Len -= len;                               // 调整最新接收缓存数据长度
	 }
	 else
	 {
		  rUart1Len	= len;                                // 赋值最新接收缓存数据长度
	 }

	
}
