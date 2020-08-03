#include "ComDriver.h"
#include "ComUart.h"
#include "ComProcess.h"
#include "management.h"
#include "miscellaneous.h"
#include "ComLAN.h"

//扩展指令========================================
void Com_SystemExt_SetRandomCode(uint32_t code)
{
    uint8 *temp;
    
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_GLOBAL_EXT_SYSTEM|0x80);
    COM_TX_8(PFC_GES_PRIORITY);
    temp = (uint8*)(&code);
    COM_TX_8(temp[3]);
    COM_TX_8(temp[2]);
    COM_TX_8(temp[1]);
    COM_TX_8(temp[0]);
    COM_END_CMD();
}

void Com_SystemExt_SetSaveAsDefault(void)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_GLOBAL_EXT_SYSTEM|0x80);
    COM_TX_8(PFC_GES_SAVE_AS_DEFAULT);
    COM_END_CMD();
}

void Com_SystemExt_SetRestoreDefault(void)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);  
    COM_TX_8(PFC_GLOBAL_EXT_SYSTEM|0x80);
    COM_TX_8(PFC_GES_RESTORE_DEFAULT);
    COM_END_CMD();
}

void Com_SystemExt_SetSuperPassword(uint8_t *str)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);  
    COM_TX_8(PFC_GLOBAL_EXT_SYSTEM|0x80);
    COM_TX_8(PFC_GES_SUPERPASSWORD);
    Com_SendStringsRaw(str);
    COM_END_CMD();
}

void Com_SystemExt_SetSoftwareVersion(uint8_t *str)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_GLOBAL_EXT_SYSTEM|0x80);
    COM_TX_8(PFC_GES_SOFTWARE_VERSION);
    Com_SendStringsRaw(str);
    COM_END_CMD();
}

void Com_SystemExt_SetHardwareVersion(uint8_t *str)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_GLOBAL_EXT_SYSTEM|0x80);
    COM_TX_8(PFC_GES_HARDWARE_VERSION);
    Com_SendStringsRaw(str);
    COM_END_CMD();
}

void Com_SystemExt_SetProductDate(uint8_t *str)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_GLOBAL_EXT_SYSTEM|0x80);
    COM_TX_8(PFC_GES_PRODUCT_DATE);
    Com_SendStringsRaw(str);
    COM_END_CMD();
}

void Com_SystemExt_SetSerialNumber(uint8_t *str)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_GLOBAL_EXT_SYSTEM|0x80);
    COM_TX_8(PFC_GES_SERIAL_NUMBER);
    Com_SendStringsRaw(str);
    COM_END_CMD();
}


void Com_SystemExt_SetModel(uint8_t model)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_GLOBAL_EXT_SYSTEM|0x80);
    COM_TX_8(PFC_GES_MODEL);
    COM_TX_8(model);
    COM_END_CMD();
}

void Com_SystemExt_SetModelString(uint8_t *str)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);  
    COM_TX_8(PFC_GLOBAL_EXT_SYSTEM|0x80);
    COM_TX_8(PFC_GES_MODEL_STRING);
    Com_SendStringsRaw(str);
    COM_END_CMD();
}

void Com_SystemExt_SetTotalUsedTime(uint32_t time)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_GLOBAL_EXT_SYSTEM|0x80);
    COM_TX_8(PFC_GES_USED_TIME);
    COM_TX_32(time);
    COM_END_CMD();
}

void Com_SystemExt_SetSaveAllData(void)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_GLOBAL_EXT_SYSTEM|0x80);
    COM_TX_8(PFC_GES_ALL_DATA);
    COM_END_CMD();
}

void Com_SystemExt_SetProtocol(uint8_t protocol)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_GLOBAL_EXT_SYSTEM|0x80);
    COM_TX_8(PFC_GES_PROTOCOL);
    COM_TX_8(protocol);
    COM_END_CMD();
}

//泵扩展指令=================================================
void Com_SystemExt_SetWorkMode(uint8_t workMode)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_PUMP_EXT_SYSTEM|0x80);
    COM_TX_8(PFC_PES_WORKMODE);
    COM_TX_8(workMode);
    COM_END_CMD();
}

void Com_SystemExt_SetFlowCalibDataCMD(uint8 cmd)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_PUMP_EXT_SYSTEM|0x80);
    COM_TX_8(PFC_PES_FLOWCALIB_DATA_CMD);
    COM_TX_8(cmd);
    COM_END_CMD();
}
void Com_SystemExt_SetFlowCalibData(float flow, float realFlow)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_PUMP_EXT_SYSTEM|0x80);
    COM_TX_8(PFC_PES_FLOWCALIB_DATA);   
    COM_TX_FLOAT(flow);
    COM_TX_FLOAT(realFlow);
    COM_END_CMD();
}

void Com_SystemExt_SetFlowCalibLoadFlow(float flow)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_PUMP_EXT_SYSTEM|0x80);
    COM_TX_8(PFC_PES_FLOWCALIB_LOAD_FLOW);
    COM_TX_FLOAT(flow);
    COM_END_CMD();
}

void Com_SystemExt_SetFlowCalibLoadReadFlow(float flow)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_PUMP_EXT_SYSTEM|0x80);
    COM_TX_8(PFC_PES_FLOWCALIB_LOAD_REALFLOW);
    COM_TX_FLOAT(flow);
    COM_END_CMD();
}

void Com_SystemExt_SetFlowCalibLoadPress(float press)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_PUMP_EXT_SYSTEM|0x80);
    COM_TX_8(PFC_PES_FLOWCALIB_LOAD_PRESS);
    COM_TX_FLOAT(press);
    COM_END_CMD();
}

void Com_SystemExt_SetPressCalibDataCMD(uint8 cmd)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_PUMP_EXT_SYSTEM|0x80);
    COM_TX_8(PFC_PES_PRESSCALIB_DATA_CMD);
    COM_TX_8(cmd);
    COM_END_CMD();
}
void Com_SystemExt_SetPressCalibData(float press, float realPress)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_PUMP_EXT_SYSTEM|0x80);
    COM_TX_8(PFC_PES_PRESSCALIB_DATA);
    COM_TX_FLOAT(press);
    COM_TX_FLOAT(realPress);
    COM_END_CMD();
}

void Com_SystemExt_SetPulseCompenDataCMD(uint8 cmd)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_PUMP_EXT_SYSTEM|0x80);
    COM_TX_8(PFC_PES_PULSECOMPEN_DATA_CMD);
    COM_TX_8(cmd);
    COM_END_CMD();
}
void Com_SystemExt_SetPulseCompenData(float position, float compenFactor)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_PUMP_EXT_SYSTEM|0x80);
    COM_TX_8(PFC_PES_PULSECOMPEN_DATA);
    COM_TX_FLOAT(position);
    COM_TX_FLOAT(compenFactor);
    COM_END_CMD();
}

void Com_SystemExt_SetPulseCompenDebugCMD(uint8 cmd)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_PUMP_EXT_SYSTEM|0x80);
    COM_TX_8(PFC_PES_PULSECOMPEN_DEBUG_CMD);
    COM_TX_8(cmd);
    COM_END_CMD();
}

void Com_SystemExt_SetPulseCompenGearPos(int32_t pos)
{
//    uint8 *temp;

    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_PUMP_EXT_SYSTEM|0x80);
    COM_TX_8(PFC_PES_PULSECOMPEN_GEAR_POS);
    COM_TX_32(pos);
//    temp = (uint8*)(&pos);
//    COM_TX_8(temp[3]);
//    COM_TX_8(temp[2]);
//    COM_TX_8(temp[1]);
//    COM_TX_8(temp[0]);
    COM_END_CMD();
}

void Com_SystemExt_SetStepMotorCurrentRun(uint8 current)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_PUMP_EXT_SYSTEM|0x80);
    COM_TX_8(PFC_PES_STEPMOTOR_IRUN);
    COM_TX_8(current);
    COM_END_CMD();
}

void Com_SystemExt_SetMotorCurrentCMD(uint8 cmd)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_PUMP_EXT_SYSTEM|0x80);
    COM_TX_8(PFC_PES_MOTORCURRENT_DATA_CMD);
    COM_TX_8(cmd);
    COM_END_CMD();
}
void Com_SystemExt_SetMotorCurrent(float flow, uint8_t current)
{
    COM_BEGIN_CMD();
    COM_TX_8(man.machineAddress);
    COM_TX_8(PFC_PUMP_EXT_SYSTEM|0x80);
    COM_TX_8(PFC_PES_MOTORCURRENT_DATA);
    COM_TX_FLOAT(flow);
    COM_TX_8(current);
    COM_END_CMD();
}
