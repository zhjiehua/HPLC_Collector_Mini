#include "ComDriver.h"
#include "ComUart.h"
#include "ComProcess.h"
#include "management.h"
#include "miscellaneous.h"
#include "ComLAN.h"

//¿©’π÷∏¡Ó========================================
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
