/*! 
 *  \file cmd_queue.h
 *  \brief ����ָ�����
 *  \version 1.0
 *  \date 2012-2015
 *  \copyright ���ݴ�ʹ��Ƽ����޹�˾
 */

#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "Types.h"

typedef struct _QUEUE
{
	qsize _head; //����ͷ
	qsize _tail;  //����β
	
	qsize _cmd_pos; //��ǰָ��ָ��λ��
	
	qsize _size; //���г���
	qdata *_data;	//�������ݻ�����ָ��
}QUEUE;

/*! 
 *  \brief  ���ָ������
 */
void queue_init(QUEUE *que, qdata *buffer, qsize size);

/*! 
 * \brief  ���ָ������
 * \detial ���ڽ��յ����ݣ�ͨ���˺�������ָ����� 
 *  \param  _data ָ������
 */
void queue_push(QUEUE *que, qdata _data);

qsize queue_size(QUEUE *que);

void queue_pop(QUEUE *que, qdata* _data);

#endif
