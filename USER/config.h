#ifndef _CONFIG_H_
#define _CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

#define FIRMWARE_VERSION 1.0.0          //
    
#define CRC16_ENABLE 1            // �����ҪCRC16У�鹦�ܣ��޸Ĵ˺�Ϊ1(��ʱ��Ҫ��VisualTFT��������CRCУ��)
#define COM_CMD_MAX_SIZE 64           // ����ָ���С��������Ҫ�������������ô�һЩ
    
#define COM_QUEUE_MAX_SIZE 512        // ָ����ջ�������С��������Ҫ�������������ô�һЩ   

#ifdef __cplusplus
}
#endif

#endif
