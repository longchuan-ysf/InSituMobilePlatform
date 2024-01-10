/*! 
*  \file cmd_queue.h
*  \brief ����ָ�����
*  \version 1.0
*  \date 2012-2018
*  \copyright ���ݴ�ʹ��Ƽ����޹�˾
*/

#ifndef _CMD_QUEUE
#define _CMD_QUEUE
#include "hmi_driver.h"

typedef unsigned char qdata;
typedef unsigned short qsize;

/*! 
*  \brief  ���ָ������
*/
extern void queue_reset(void);

/*! 
* \brief  ���ָ������
* \detial ���ڽ��յ����ݣ�ͨ���˺�������һ���ֽ�ָ����� 
*  \param  _data ָ������
*/
extern void queue_pushChar(qdata _data);

/*! 
* \brief  ���ָ������
* \detial ���ڽ��յ����ݣ�ͨ���˺�������һ��ָ����� 
*  \param  _data ָ������ָ��
*/
extern void queue_pushString(qdata *_pdata,uint32 len);


/*! 
*  \brief  ��ָ�������ȡ��һ��������ָ��
*  \param  cmd ָ����ջ�����
*  \param  buf_len ָ����ջ�������С
*  \return  ָ��ȣ�0��ʾ������������ָ��
*/


extern qsize queue_find_cmd(qdata *cmd,qsize buf_len);

#endif
