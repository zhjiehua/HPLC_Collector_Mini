#include "Queue.h"

#ifdef __cplusplus
extern "C" {
#endif
	
void queue_init(QUEUE *que, qdata *buffer, qsize size)
{
	que->_head = que->_tail = 0;
	
	que->_data = buffer;
	que->_size = size;
	
	que->_cmd_pos = 0;
}

void queue_push(QUEUE *que, qdata _data)
{
	qsize pos = (que->_head+1)%que->_size;
	if(pos!=que->_tail)//����״̬
	{
		que->_data[que->_head] = _data;
		que->_head = pos;
	}
}

//�Ӷ�����ȡһ������
void queue_pop(QUEUE *que, qdata* _data)
{
	if(que->_tail!=que->_head)//�ǿ�״̬
	{
		*_data = que->_data[que->_tail];
		que->_tail = (que->_tail+1)%que->_size;
	}
}

//��ȡ��������Ч���ݸ���
qsize queue_size(QUEUE *que)
{
	return ((que->_head+que->_size-que->_tail)%que->_size);
}

#ifdef __cplusplus
}
#endif
