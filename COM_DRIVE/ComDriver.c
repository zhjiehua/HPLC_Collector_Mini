/************************************��Ȩ����********************************************
**                             ���ݴ�ʹ��Ƽ����޹�˾
**                             http://www.gz-dc.com
**-----------------------------------�ļ���Ϣ--------------------------------------------
** �ļ�����:   hmi_driver.c
** �޸�ʱ��:   2018-05-18
** �ļ�˵��:   �û�MCU��������������
** ����֧�֣�  Tel: 020-82186683  Email: hmi@gz-dc.com Web:www.gz-dc.com
--------------------------------------------------------------------------------------
----------------------------------------------------------------------------------------*/
#include "ComDriver.h"
#include "ComUart.h"
#include "ComProcess.h"
#include "management.h"
#include "miscellaneous.h"
#include "ComLAN.h"

uint8_t comTxBufferHex[COM_CMD_MAX_SIZE/2];
uint8_t comTxBufferAscii[COM_CMD_MAX_SIZE];
uint8_t comTxBufferIndex = 0;

/*! 
*  \brief  ����һ���ֽ�
*  \param  c 
*/
void COM_SEND_DATA(uint8 c)
{
    comTxBufferHex[comTxBufferIndex++] = c;   
}
/*! 
*  \brief  ֡ͷ
*/
void COM_BEGIN_CMD(void)
{
    comTxBufferIndex = 0;
}
/*! 
*  \brief  ֡β
*/
void COM_END_CMD(void)
{
#if(CRC16_ENABLE)
    uint16 crc = 0xFFFF;
	AddCRC16(comTxBufferHex, comTxBufferIndex, &crc);
    comTxBufferHex[comTxBufferIndex++] = (uint8)(crc >> 8);
    comTxBufferHex[comTxBufferIndex++] = (uint8)crc;
#endif

    Hex2Ascii(comTxBufferAscii+1, comTxBufferHex, comTxBufferIndex);
    comTxBufferIndex *= 2;
    
    comTxBufferAscii[0] = SYSTEM_COMMUNICATE_HEAD;
    comTxBufferIndex++;
    comTxBufferAscii[comTxBufferIndex++] = SYSTEM_COMMUNICATE_TAIL;
    
    if(man.comType == 0) //����
    {
        uint8 i;
        for(i=0;i<comTxBufferIndex;i++)
            ComUart_SendChar(comTxBufferAscii[i]);
    }
    else
    {
        if(S0_State&S_CONN)//socket������
            Write_SOCK_Data_Buffer(0, comTxBufferAscii, comTxBufferIndex);
    }
    
    comTxBufferIndex = 0;
}

void Com_SendStringsRaw(uchar *str)
{
    //COM_BEGIN_CMD();
    while(*str)
    {
        COM_TX_8(*str);
        str++;
    }
    COM_TX_8(*str);//�����ַ�����β��
    //COM_END_CMD();
}

/*! 
*  \brief  ���ڷ������ַ���
*  \param  �ַ���
*/
void Com_SendStrings(uchar *str)
{
    COM_BEGIN_CMD();
    while(*str)
    {
        COM_TX_8(*str);
        str++;
    }
    //COM_TX_8(*str);//�����ַ�����β��
    COM_END_CMD();
}
/*! 
*  \brief  ���ڷ�����N���ֽ�
*  \param  ����
*/
void Com_SendNU8(uint8 *pData,uint16 nDataLen)
{
    uint16 i = 0;
    COM_BEGIN_CMD();
    for (;i<nDataLen;++i)
    {
        COM_TX_8(pData[i]);
    }
    COM_END_CMD();
}
/*! 
*  \brief  ���ڷ�����N��16λ������
*  \param  ����
*/
void Com_SendNU16(uint16 *pData,uint16 nDataLen)
{
    uint16 i = 0;
    COM_BEGIN_CMD();
    for (;i<nDataLen;++i)
    {
        COM_TX_16(pData[i]);
    }
    COM_END_CMD();
}


//�ظ�ָ��======================================================
void Com_Ack(void)
{
    comTxBufferHex[0] = SYSTEM_COMMUNICATE_ACK;
    
    if(man.comType == 0) //����
    {
        ComUart_SendChar(comTxBufferHex[0]);
    }
    else
    {
        Write_SOCK_Data_Buffer(0, comTxBufferHex, 1);
    }
    
    comTxBufferIndex = 0;
}

void Com_NAck(void)
{
    comTxBufferHex[0] = SYSTEM_COMMUNICATE_NACK;
    
    if(man.comType == 0) //����
    {
        ComUart_SendChar(comTxBufferHex[0]);
    }
    else
    {
        Write_SOCK_Data_Buffer(0, comTxBufferHex, 1);
    }
    
    comTxBufferIndex = 0;
}


//����ָ��======================================================
//ͨ�û���ָ��====================================
void Com_SetSoftwareVersion(uint8_t *str)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);  
    COM_TX_8(PFC_GLOBAL_SOFTWARE_VERSION|0x80);
    Com_SendStringsRaw(str);
    COM_END_CMD();
}

void Com_SetHardwareVersion(uint8_t *str)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);  
    COM_TX_8(PFC_GLOBAL_HARDWARE_VERSION|0x80);
    Com_SendStringsRaw(str);
    COM_END_CMD();
}

void Com_SetProductDate(uint8_t *str)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);  
    COM_TX_8(PFC_GLOBAL_PRODUCT_DATE|0x80);
    Com_SendStringsRaw(str);
    COM_END_CMD();
}

void Com_SetSerialNumber(uint8_t *str)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);  
    COM_TX_8(PFC_GLOBAL_SERIAL_NUMBER|0x80);
    Com_SendStringsRaw(str);
    COM_END_CMD();
}

void Com_SetModel(uint8_t *str)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);  
    COM_TX_8(PFC_GLOBAL_MODEL|0x80);
    Com_SendStringsRaw(str);
    COM_END_CMD();
}

void Com_SetSyncTime(uint32_t time)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_GLOBAL_SYNC_TIME|0x80);
    COM_TX_32(time);
    COM_END_CMD();
}

void Com_SetTotalUsedTime(uint32_t time)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_GLOBAL_USED_TIME|0x80);
    COM_TX_32(time);
    COM_END_CMD();
}

void Com_SetInput(uint8_t inputNumber, uint8_t level)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);  
    COM_TX_8(PFC_GLOBAL_INPUT|0x80);
    COM_TX_8(inputNumber);
    COM_TX_8(level);
    COM_END_CMD();
}

void Com_SetOutput(uint8_t outputNumber, uint8_t level)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);  
    COM_TX_8(PFC_GLOBAL_OUTPUT|0x80);
    COM_TX_8(outputNumber);
    COM_TX_8(level);
    COM_END_CMD();
}

void Com_SetTick(void)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_GLOBAL_TICK|0x80);
    COM_END_CMD();
}

void Com_SetSystemError(uint8_t errorNum)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_GLOBAL_ERROR|0x80);
    COM_TX_8(errorNum);
    COM_END_CMD();
}

//�û���ָ��====================================
void Com_SetFlow(float flow)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_PUMP_FLOW|0x80);
    COM_TX_FLOAT(flow);
    COM_END_CMD();
}

void Com_SetFlowPercent(uint8_t percent)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_PUMP_FLOW_PERCENT|0x80);
    COM_TX_8(percent);
    COM_END_CMD();
}

void Com_SetPressMin(float press)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_PUMP_PRESS_MIN|0x80);
    COM_TX_FLOAT(press);
    COM_END_CMD();
}

void Com_SetPressMax(float press)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_PUMP_PRESS_MAX|0x80);
    COM_TX_FLOAT(press);
    COM_END_CMD();
}

void Com_SetPressWarning(float press)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_PUMP_PRESS_WARNING|0x80);
    COM_TX_FLOAT(press);
    COM_END_CMD();
}

void Com_SetStartStop(uint8_t flag)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_PUMP_START_STOP|0x80);
    COM_TX_8(flag);
    COM_END_CMD();
}

void Com_SetPauseRestore(uint8_t flag)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_PUMP_PAUSE_RESTORE|0x80);
    COM_TX_8(flag);
    COM_END_CMD();
}

void Com_SetPurge(uint8_t flag)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_PUMP_PURGE|0x80);
    COM_TX_8(flag);
    COM_END_CMD();
}

void Com_SetPurgeFlow(float flow)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_PUMP_PURGE_FLOW|0x80);
    COM_TX_FLOAT(flow);
    COM_END_CMD();
}

void Com_SetPurgeTime(uint8_t time)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_PUMP_PURGE_TIME|0x80);
    COM_TX_8(time);
    COM_END_CMD();
}

void Com_SetPressZeroVoltage(float voltage)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_PUMP_PRESS_ZERO|0x80);
    COM_TX_FLOAT(voltage);
    COM_END_CMD();
}

void Com_SetPressUploadFreq(uint8_t factor)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_PUMP_PRESS_UPLOAD_FREQ|0x80);
    COM_TX_8(factor);
    COM_END_CMD();
}

void Com_SetPressCompen(uint8_t flag)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_PUMP_FLOW_PRESS_COMPEN|0x80);
    COM_TX_8(flag);
    COM_END_CMD();
}

void Com_SetMode(uint8_t mode)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_PUMP_MODE|0x80);
    COM_TX_8(mode);
    COM_END_CMD();
}

void Com_SetPress(float press)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_PUMP_PRESS|0x80);
    COM_TX_FLOAT(press);
    COM_END_CMD();
}

void Com_SetRunMode(uint8_t mode)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_PUMP_RUNMODE|0x80);
    COM_TX_8(mode);
    COM_END_CMD();
}


