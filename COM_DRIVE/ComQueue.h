/*! 
*  \file cmd_queue.h
*  \brief ����ָ�����
*  \version 1.0
*  \date 2012-2018
*  \copyright ���ݴ�ʹ��Ƽ����޹�˾
*/

#ifndef _COM_QUEUE_H_
#define _COM_QUEUE_H_

#include "stdint.h"
#include "Queue.h"
#include "config.h"

typedef unsigned char qdata;
typedef unsigned short qsize;

/*! 
*  \brief  ��ָ�������ȡ��һ��������ָ��
*  \param  cmd ָ����ջ�����
*  \param  buf_len ָ����ջ�������С
*  \return  ָ��ȣ�0��ʾ������������ָ��
*/
qsize ComQueue_FindCmd(qdata *ascii_buffer, qdata *hex_buffer, qsize buf_len, QUEUE *que);

extern qdata comQueueBuffer[];
extern QUEUE comQueue; 

extern uint8_t comCmdBufferHex[]; 
extern uint8_t comCmdBufferAscii[];

#endif
