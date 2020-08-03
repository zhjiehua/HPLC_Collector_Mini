#include "ComProcess.h"
#include "IO.h"
#include "delay.h"
#include "ComDriver.h"

#include "24cxx.h"

#include "management.h"
#include "CPrintf.h"

#include "Key.h"

#include "wdg.h"
#include "stdlib.h"

void ComProcessFrame_WriteGlobalExternSystem( ComFrame_TypeDef *msg, uint16 size )
{
    uint8_t pfce = msg->data[0];
	uint8_t *data = msg->data + 1;
    
    switch (pfce)
	{
        case PFC_GES_PRIORITY:
//        {
//            uint32_t temp = (uint32_t)PTR2U32(data);//必须有中间变量
//            float flow = *(float*)(&temp);
//        }
//            if(data[0] == 0x55)
//            {
//                Com_Ack();
//                man.priority = data[1];
//            }
//            else
//                Com_NAck();
            break;
		case PFC_GES_RESET:
            Com_Ack();
            SoftReset();
            cDebug("Write : Reset the machine!\r\n");
			break;
		case PFC_GES_RESTORE_DEFAULT://恢复出厂设置
            Com_Ack();
        {
            if(data[0] == 0)
            {
                uint16_t i;
                uint8_t eepromData;
                for(i=0;i<EEPROM_ADDR_FACTORYDATA;i++)
                {
                    eepromData = AT24CXX_ReadOneByte(EEPROM_ADDR_FACTORYDATA_REAL+i);
                    AT24CXX_WriteOneByte(i, eepromData);
										IWDG_Feed();
                }
                
                //检查
                for(i=0;i<EEPROM_ADDR_FACTORYDATA;i++)
                {
                    eepromData = AT24CXX_ReadOneByte(EEPROM_ADDR_FACTORYDATA_REAL+i);
                    if(eepromData != AT24CXX_ReadOneByte(i))
                        AT24CXX_WriteOneByte(i, eepromData);

										IWDG_Feed();
                }
                
                Com_SystemExt_SetRestoreDefault();
                
                cDebug("Write : Restore default!\r\n");
            }
            else
            {
                AT24CXX_WriteOneByte(EEPROM_ADDR_DEFAULT, (uint8_t)(~EEPROM_DEFAULT_DATA));
                cDebug("Write : Restore default-First Power On!\r\n");
            }
        }
			break;
		case PFC_GES_SAVE_AS_DEFAULT://保存为出厂设置 
            Com_Ack();
        {
            uint16_t i;
            uint8_t eepromData;
            for(i=0;i<EEPROM_ADDR_FACTORYDATA;i++)
            {
                eepromData = AT24CXX_ReadOneByte(i);
                AT24CXX_WriteOneByte(EEPROM_ADDR_FACTORYDATA_REAL+i, eepromData);
            }
            
            //检查
            for(i=0;i<EEPROM_ADDR_FACTORYDATA;i++)
            {
                eepromData = AT24CXX_ReadOneByte(i);
                if(eepromData != AT24CXX_ReadOneByte(EEPROM_ADDR_FACTORYDATA_REAL+i))
                    AT24CXX_WriteOneByte(EEPROM_ADDR_FACTORYDATA_REAL+i, eepromData);                        
            }
            
            Com_SystemExt_SetSaveAsDefault();
            
            cDebug("Write : Save as default!\r\n");
        }
			break;
		case PFC_GES_SUPERPASSWORD:       
            Com_Ack();
        {
        
            strcpy((char*)man.superPassword, (char*)data);
            AT24CXX_Write(EEPROM_ADDR_SUPERPASSWORD, (uint8_t*)&man.superPassword, strlen((const char*)man.superPassword)+1);
            cDebug("Write : man.superPassword = %s\r\n", man.superPassword);
                    
//                    uint32_t value = StringToInt32(data);
////                    Evalboards.ch1.SAP(162, 0, value);//blank time
////                    cDebug("TMC5160 blank time = %d\r\n", value);
//                    
////                    if(value)
////                        Evalboards.ch1.SAP(163, 0, 0);// spreadCycle/classic chopper
////                    else
////                        Evalboards.ch1.SAP(163, 0, 1);// spreadCycle/classic chopper
//                    
//                    Evalboards.ch1.SAP(220, 0, value);// TPFD
//                    cDebug("TMC5160 TPFD = %d\r\n", value);
			
        }
        break;
        case PFC_GES_SOFTWARE_VERSION:
            Com_NAck();
            break;
        case PFC_GES_HARDWARE_VERSION:
            Com_NAck();
            break;
        case PFC_GES_PRODUCT_DATE:
            Com_Ack();
            strcpy((char*)man.productDate, (char*)data);
            AT24CXX_Write(EEPROM_ADDR_PRODUCTDATE, (uint8_t*)&man.productDate, strlen((const char*)man.productDate)+1);
            cDebug("Write : man.productDate = %s\r\n", man.productDate);
            break;
        case PFC_GES_SERIAL_NUMBER:
            Com_Ack();
            strcpy((char*)man.serialNumber, (char*)data);
            AT24CXX_Write(EEPROM_ADDR_SERIALNUMBER, (uint8_t*)&man.serialNumber, strlen((const char*)man.serialNumber)+1);
            cDebug("Write : man.serialNumber = %s\r\n", man.serialNumber);
            break;
        case PFC_GES_MODEL:
            Com_Ack();
            man.model = data[0];
            AT24CXX_WriteOneByte(EEPROM_ADDR_MODEL, man.model);
            cDebug("Write : man.model = %d\r\n", man.model);
            break;
        case PFC_GES_MODEL_STRING:
            Com_Ack();
            strcpy((char*)man.modelString, (char*)data);
            AT24CXX_Write(EEPROM_ADDR_MODELSTRING, (uint8_t*)&man.modelString, strlen((const char*)man.modelString)+1);
            cDebug("Write : man.modelString = %s\r\n", man.modelString);
            break;
        case PFC_GES_USED_TIME:
            Com_Ack();
            man.deviceTotalUsedTime = (uint32_t)PTR2U32(data);
            AT24CXX_Write(EEPROM_ADDR_DEVICETOTALUSEDTIME, (uint8_t*)&man.deviceTotalUsedTime, 4);
            cDebug("Write : man.deviceTotalUsedTime = %d\r\n", man.deviceTotalUsedTime);
            break;

        case PFC_GES_PROTOCOL:
            Com_Ack();
            if(man.protocol != data[0])
						{
							man.protocol = data[0];
							AT24CXX_WriteOneByte(EEPROM_ADDR_PROTOCOL, man.protocol);
							
							switch(man.protocol)
							{
								case 0://塬锐协议
									man.ProtocolComQueue_FindCmd = ComQueue_FindCmd;
									man.ProtocolComProcessFrame = ComProcessFrame;
								break;
								default:
									man.ProtocolComQueue_FindCmd = ComQueue_FindCmd;
									man.ProtocolComProcessFrame = ComProcessFrame;
								break;
							}
			
							if(man.comType == 0)
							{
									if(man.protocol == 0)//塬锐
										ComUart_Init(115200);
									else
										ComUart_Init(115200);
							}
						}
						
            cDebug("Write : man.protocol = %d\r\n", man.protocol);
          break;
		default:
            Com_NAck();
            cDebug("\r\n Write : '%02x' Error Function Code Extern!!\r\n", pfce);
			break;
	}
}

void ComProcessFrame_ReadGlobalExternSystem( ComFrame_TypeDef *msg, uint16 size )
{
    uint8_t pfce = msg->data[0];
	//uint8_t *data = msg->data + 1;

	switch (pfce)
	{
        case PFC_GES_PRIORITY:
            Com_Ack();
            srand(TIM2->CNT);
			man.randomCode = rand();
            Com_SystemExt_SetRandomCode(man.randomCode);
            cDebug("Read : man.randomCode = %d\r\n", man.randomCode);
            break;
		case PFC_GES_RESET:
            Com_NAck();
			break;
		case PFC_GES_RESTORE_DEFAULT:
            Com_NAck();
			break;
		case PFC_GES_SAVE_AS_DEFAULT:
            Com_NAck();
			break;
		case PFC_GES_SUPERPASSWORD://管理员密码     
            Com_Ack();
            Com_SystemExt_SetSuperPassword(man.superPassword);
            cDebug("Read : man.superPassword = %s\r\n", man.superPassword);
			break;
    case PFC_GES_SOFTWARE_VERSION:
        Com_Ack();
        Com_SystemExt_SetSoftwareVersion((uint8_t*)SOFTWARE_VERSION);
        cDebug("Read : SOFTWARE_VERSION = %s\r\n", (uint8_t*)SOFTWARE_VERSION);
        break;
    case PFC_GES_HARDWARE_VERSION:
        Com_Ack();
        Com_SystemExt_SetHardwareVersion((uint8_t*)HARDWARE_VERSION);
        cDebug("Read : HARDWARE_VERSION = %s\r\n", (uint8_t*)HARDWARE_VERSION);
        break;
    case PFC_GES_PRODUCT_DATE:
        Com_Ack();
        Com_SystemExt_SetProductDate(man.productDate);
        cDebug("Read : man.productDate = %s\r\n", man.productDate);
        break;
    case PFC_GES_SERIAL_NUMBER:
        Com_Ack();
        Com_SystemExt_SetSerialNumber(man.serialNumber);
        cDebug("Read : man.serialNumber = %s\r\n", man.serialNumber);
        break;
    case PFC_GES_MODEL:
        Com_Ack();
        Com_SystemExt_SetModel(man.model);
        cDebug("Read : man.model = %d\r\n", man.model);
        break;
    case PFC_GES_MODEL_STRING:
        Com_Ack();
        Com_SystemExt_SetModelString(man.modelString);
        cDebug("Read : man.modelString = %s\r\n", man.modelString);
        break;
    case PFC_GES_USED_TIME:
        Com_Ack();
        Com_SystemExt_SetTotalUsedTime(man.deviceTotalUsedTime);
        cDebug("Read : man.deviceTotalUsedTime = %d\r\n", man.deviceTotalUsedTime);
        break;
    case PFC_GES_ALL_DATA://读取全部数据
        Com_Ack();
        UploadAllData();
    break;
    case PFC_GES_PROTOCOL:
        Com_Ack();
        Com_SystemExt_SetProtocol(man.protocol);
        cDebug("Read : man.protocol = %d\r\n", man.protocol);
      break;
		default:
        Com_NAck();
        cDebug("\r\n Read : '%02x' Error Function Code Extern!!\r\n", pfce);
			break;
	}
}

void ComProcessFrame_SystemError(uint8_t errorCode)
{
//    switch(errorCode)
//    {
//        case PEC_PUMP_STOP://主泵需要处理，注意不用回复
//            if(man.programSel != 0)//如果正在执行时间程序，则停止时间程序
//            {
//                man.isTimeProgramFinish = 1;//停止时间程序
//                cDebug("System Error - Pump slave stop!");
//            }
//            break;
//        default:
//            break;
//    }
}


//============================用户命令========================================
void ComProcessFrame_WriteGlobalExternUser( ComFrame_TypeDef *msg, uint16 size )
{
    uint8_t pfce = msg->data[0];
	uint8_t *data = msg->data + 1;
    
    switch (pfce)
	{
        case PFC_GEU_KEY:
            Com_Ack();
				
						//man.key = data[0];
				
            //cDebug("Write : KEY = 0x%02X\r\n", data[0]);
			break;
		case PFC_GEU_LCD:
            Com_NAck();
			break;
		default:
			Com_NAck();
      cDebug("\r\n Write : '%02x' Error Function Code Extern User!!\r\n", pfce);
			break;
	}
}

void ComProcessFrame_ReadGlobalExternUser( ComFrame_TypeDef *msg, uint16 size )
{
    uint8_t pfce = msg->data[0];
	//uint8_t *data = msg->data + 1;
    
    switch (pfce)
	{
        case PFC_GEU_KEY:
            Com_Ack();
            //Com_SystemExt_SetWorkMode(man.workMode);
            //cDebug("Read : man.workMode = 0x%02X\r\n", man.workMode);
			break;
		case PFC_GEU_LCD:
            Com_NAck();
			break;
		default:
			Com_NAck();
      cDebug("\r\n Read : '%02x' Error Function Code Extern User!!\r\n", pfce);
			break;
	}
}
