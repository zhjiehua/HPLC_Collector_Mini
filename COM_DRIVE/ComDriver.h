/*! 
*  \file hmi_driver.h
*  \brief �����������ļ�
*  \version 1.0
*  \date 2012-2018
*  \copyright ���ݴ�ʹ��Ƽ����޹�˾
*/

#ifndef _COM_DRIVER_
#define _COM_DRIVER_


#include "ComUart.h"
#include "miscellaneous.h"
#include "config.h"

extern uint8_t comTxBufferHex[COM_CMD_MAX_SIZE/2];
extern uint8_t comTxBufferAscii[COM_CMD_MAX_SIZE];
extern uint8_t comTxBufferIndex;

#define COM_TX_8(P1) COM_SEND_DATA((P1)&0xFF)                    //���͵����ֽ�
#define COM_TX_8N(P,N) Com_SendNU8((uint8 *)P,N)                 //����N���ֽ�
#define COM_TX_16(P1) COM_TX_8((P1)>>8);COM_TX_8(P1)                 //����16λ����
#define COM_TX_16N(P,N) Com_SendNU16((uint16 *)P,N)              //����N��16λ����
#define COM_TX_32(P1) COM_TX_16((P1)>>16);COM_TX_16((P1)&0xFFFF)     //����32λ����
#define COM_TX_FLOAT(P1) COM_TX_32(*(uint32*)(&P1))     //���͸�����

void COM_SEND_DATA(uint8 c);
void COM_BEGIN_CMD(void);
void COM_END_CMD(void);
void Com_SendStringsRaw(uchar *str);
void Com_SendStrings(uchar *str);
void Com_SendNU8(uint8 *pData,uint16 nDataLen);
void Com_SendNU16(uint16 *pData,uint16 nDataLen);

//����ָ��========================================
void Com_Ack(void);
void Com_NAck(void);

void Com_SetSoftwareVersion(uint8_t *str);
void Com_SetHardwareVersion(uint8_t *str);
void Com_SetProductDate(uint8_t *str);
void Com_SetSerialNumber(uint8_t *str);
void Com_SetModel(uint8_t *str);
void Com_SetSyncTime(uint32_t time);
void Com_SetTotalUsedTime(uint32_t time);
void Com_SetInput(uint8_t inputNumber, uint8_t level);
void Com_SetOutput(uint8_t inputNumber, uint8_t level);
void Com_SetTick(void);
void Com_SetSystemError(uint8_t errorNum);

//����ռ�������ָ��
void Com_SetCoil(uint8_t num);

//ϵͳ��չ=============================================
void Com_SystemExt_SetRandomCode(uint32_t code);
void Com_SystemExt_SetSuperPassword(uint8_t *str);
void Com_SystemExt_SetSaveAsDefault(void);
void Com_SystemExt_SetRestoreDefault(void);
void Com_SystemExt_SetSoftwareVersion(uint8_t *str);//
void Com_SystemExt_SetHardwareVersion(uint8_t *str);//
void Com_SystemExt_SetProductDate(uint8_t *str);//
void Com_SystemExt_SetSerialNumber(uint8_t *str);//
void Com_SystemExt_SetModel(uint8_t model);
void Com_SystemExt_SetModelString(uint8_t *str);//
void Com_SystemExt_SetTotalUsedTime(uint32_t time);
void Com_SystemExt_SetSaveAllData(void);
void Com_SystemExt_SetProtocol(uint8_t protocol);

#endif      //_HMI_DRIVER_
