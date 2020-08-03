/*! 
*  \file hmi_driver.h
*  \brief 串口屏驱动文件
*  \version 1.0
*  \date 2012-2018
*  \copyright 广州大彩光电科技有限公司
*/

#ifndef _COM_DRIVER_
#define _COM_DRIVER_


#include "ComUart.h"
#include "miscellaneous.h"
#include "config.h"

extern uint8_t comTxBufferHex[COM_CMD_MAX_SIZE/2];
extern uint8_t comTxBufferAscii[COM_CMD_MAX_SIZE];
extern uint8_t comTxBufferIndex;

#define COM_TX_8(P1) COM_SEND_DATA((P1)&0xFF)                    //发送单个字节
#define COM_TX_8N(P,N) Com_SendNU8((uint8 *)P,N)                 //发送N个字节
#define COM_TX_16(P1) COM_TX_8((P1)>>8);COM_TX_8(P1)                 //发送16位整数
#define COM_TX_16N(P,N) Com_SendNU16((uint16 *)P,N)              //发送N个16位整数
#define COM_TX_32(P1) COM_TX_16((P1)>>16);COM_TX_16((P1)&0xFFFF)     //发送32位整数
#define COM_TX_FLOAT(P1) COM_TX_32(*(uint32*)(&P1))     //发送浮点数

void COM_SEND_DATA(uint8 c);
void COM_BEGIN_CMD(void);
void COM_END_CMD(void);
void Com_SendStringsRaw(uchar *str);
void Com_SendStrings(uchar *str);
void Com_SendNU8(uint8 *pData,uint16 nDataLen);
void Com_SendNU16(uint16 *pData,uint16 nDataLen);

//基本指令========================================
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

//泵基本指令
void Com_SetFlow(float flow);
void Com_SetFlowPercent(uint8_t percent);
void Com_SetPressMin(float press);
void Com_SetPressMax(float press);
void Com_SetPressWarning(float press);
void Com_SetStartStop(uint8_t flag);
void Com_SetPauseRestore(uint8_t flag);
void Com_SetPurge(uint8_t flag);
void Com_SetPurgeFlow(float flow);
void Com_SetPurgeTime(uint8_t time);
void Com_SetPressZeroVoltage(float voltage);
void Com_SetPressUploadFreq(uint8_t factor);
void Com_SetPressCompen(uint8_t flag);
void Com_SetMode(uint8_t mode);
void Com_SetPress(float press);
void Com_SetRunMode(uint8_t mode);

//系统扩展=============================================
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

//泵扩展指令
void Com_SystemExt_SetWorkMode(uint8_t workMode);
void Com_SystemExt_SetFlowCalibDataCMD(uint8 cmd);
void Com_SystemExt_SetFlowCalibData(float flow, float realFlow);
void Com_SystemExt_SetFlowCalibLoadFlow(float flow);
void Com_SystemExt_SetFlowCalibLoadReadFlow(float flow);
void Com_SystemExt_SetFlowCalibLoadPress(float press);
void Com_SystemExt_SetPressCalibDataCMD(uint8 cmd);
void Com_SystemExt_SetPressCalibData(float press, float realPress);
void Com_SystemExt_SetPulseCompenDataCMD(uint8 cmd);
void Com_SystemExt_SetPulseCompenData(float position, float compenFactor);
void Com_SystemExt_SetPulseCompenDebugCMD(uint8 cmd);
void Com_SystemExt_SetPulseCompenGearPos(int32_t pos);
void Com_SystemExt_SetStepMotorCurrentRun(uint8 current);
void Com_SystemExt_SetMotorCurrentCMD(uint8 cmd);
void Com_SystemExt_SetMotorCurrent(float flow, uint8_t current);

#endif      //_HMI_DRIVER_
