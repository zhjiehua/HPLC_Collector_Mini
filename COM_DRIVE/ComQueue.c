/************************************��Ȩ����********************************************
**                             ���ݴ�ʹ��Ƽ����޹�˾
**                             http://www.gz-dc.com
**-----------------------------------�ļ���Ϣ--------------------------------------------
** �ļ�����:   cmd_queue.c
** �޸�ʱ��:   2018-05-18
** �ļ�˵��:   �û�MCU��������������
** ����֧�֣�  Tel: 020-82186683  Email: hmi@gz-dc.com Web:www.gz-dc.com
--------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------
ʹ�ñض�
cmd_queue.c�й�5�����������ָ������queue_reset()���Ӵ������ָ������queue_push()��
�Ӷ�����ȡһ������queue_pop().��ȡ��������Ч���ݸ���queue_size()����ָ�������ȡ��һ��������ָ��queue_find_cmd����
����ֲ������ƽ̨����Ҫ�޸ĵײ�Ĵ�������,����ֹ�޸ĺ������ƣ������޷���HMI������(hmi_driver.c)ƥ�䡣
--------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------*/
#include "Queue.h"
#include "ComQueue.h"
#include "miscellaneous.h"
#include "CPrintf.h"
#include "ComProcess.h"


qdata comQueueBuffer[COM_QUEUE_MAX_SIZE];
QUEUE comQueue; 

uint8_t comCmdBufferHex[COM_CMD_MAX_SIZE/2];                                           //hexָ���
uint8_t comCmdBufferAscii[COM_CMD_MAX_SIZE];                                              //asciiָ���

/*! 
*  \brief  ��ָ�������ȡ��һ��������ָ��
*  \param  cmd ָ����ջ�����
*  \param  buf_len ָ����ջ�������С
*  \return  ָ��ȣ�0��ʾ������������ָ��
*/
qsize ComQueue_FindCmd(qdata *ascii_buffer, qdata *hex_buffer, qsize buf_len, QUEUE *que)
{
	qsize cmd_size = 0;
	qdata _data = 0;
	while(queue_size(que)>0)
	{
		//ȡһ������
		queue_pop(que, &_data);
        
    //cDebug("%c", _data);
        
		if(_data == SYSTEM_COMMUNICATE_HEAD)
		{
			que->_cmd_pos = 0;
		}
	
		if(que->_cmd_pos == 0 && _data != SYSTEM_COMMUNICATE_HEAD) //ָ���һ���ֽڱ�����֡ͷ����������
		{
      Com_NAck();
			cDebug("The CMD first char is not ':'--0x%02X, %c!\r\n", _data, _data); 
			continue;
		}

		if(que->_cmd_pos < buf_len) //��ֹ���������
			ascii_buffer[que->_cmd_pos++] = _data;  //ע�⣺++��������*���������ȼ�����
        
		if(_data == SYSTEM_COMMUNICATE_TAIL)
		{
			char i;
			cmd_size = que->_cmd_pos/2-1 ;                              //ָ���ֽڳ���

			if(que->_cmd_pos%2 == 0)
			{
        if(que->_cmd_pos < COM_CMD_MAX_SIZE-20)
        {
//          cDebug("The cmd Ascii is: ");
//          for(i = 0; i < que->_cmd_pos; i++)
//              cDebug("%c", ascii_buffer[i]);
//          cDebug("\r\n");
          
          Ascii2Hex(hex_buffer, &ascii_buffer[1], cmd_size);
          
//          cDebug("The cmd is: ");
//          for(i = 0; i < cmd_size; i++)
//              cDebug("%02x ", hex_buffer[i]);
//          cDebug("\r\n");
        }
        else //ָ��̫��
				{
            Com_NAck();
            USER_ErrLog("The CMD is too long!"); 								  
            que->_cmd_pos = 0; 
            return 0;
        }
			}
			else //ָ��Ȳ���˫��
			{
        Com_NAck();
				USER_ErrLog("The len of CMD is singular!"); 								  
				que->_cmd_pos = 0; 
				return 0;
			}					

			que->_cmd_pos = 0;                                              //��λָ��ָ��
#if(CRC16_ENABLE)
			//ȥ��ָ��ͷβ��β����2���ֽڣ�ֻ�������ݲ���CRC
			if(!CheckCRC16(hex_buffer, cmd_size))                      //CRCУ��
			{
        Com_NAck();
        USER_ErrLog("The CRC check is wrong!"); 
				return 0;
			}
			cmd_size -= 2;                                            //ȥ��CRC16��2�ֽڣ�
#endif
			return cmd_size;
		}
	}
	return 0;                                                         //û���γ�������һ֡
}
