#include "ComProcess.h"
#include "IO.h"
#include "delay.h"
#include "ComDriver.h"

#include "24cxx.h"

#include "management.h"
#include "CPrintf.h"

void ComProcessFrame( void *buffer, uint16 size )
{
  ComFrame_TypeDef *msg = buffer;
	uint8_t address = msg->address;
	uint8_t pfc = msg->pfc;
	uint8_t *data = msg->data;
    uint8_t write = pfc&0x80;
    pfc &= 0x7F;
    
	//if(address == man.machineAddress || (address == 0xFF && pfc == PFC_GLOBAL_DEVICE_ADDRESS))
    if(address == man.machineAddress)
	{
        if(!man.isConnect)
        {
#if USED_UARTLCD		
            SetButtonValue(RUNPAGE_INDEX, RUNPAGE_CONNECT_BUTTON, 1);
#endif
            cDebug("Connected!\r\n");
        }
        man.isConnect = 1;
        man.tickLostCnt = 0;
        
		switch(pfc)
		{  
			//ͨ�ù�����*********************************************************
			case PFC_GLOBAL_DEVICE_ADDRESS://�豸��ַ
                Com_NAck();
			break;                                                 
			case PFC_GLOBAL_SOFTWARE_VERSION://����汾               
				if(write)
                {
                    Com_NAck();
                }
                else
                {
                    Com_Ack();
                    Com_SetSoftwareVersion((uint8_t*)SOFTWARE_VERSION);
                    cDebug("Read : SOFTWARE_VERSION = %s\r\n", (uint8_t*)SOFTWARE_VERSION);
                }
			break;
			case PFC_GLOBAL_HARDWARE_VERSION://Ӳ���汾                                                                    
				if(write)
                {
                    Com_NAck();
                }
                else
                {
                    Com_Ack();
                    Com_SetHardwareVersion((uint8_t*)HARDWARE_VERSION);
                    cDebug("Read : HARDWARE_VERSION = %s\r\n", (uint8_t*)HARDWARE_VERSION);
                }
			break;   
			case PFC_GLOBAL_PRODUCT_DATE://��������                                                                   
				if(write)
                {
                    Com_NAck();
                }
                else
                {
                    Com_Ack();
                    Com_SetProductDate(man.productDate);
                    cDebug("Read : man.productDate = %s\r\n", man.productDate);
                }
			break;   
			case PFC_GLOBAL_SERIAL_NUMBER://���к�                                                                      
				if(write)
                {
                    Com_NAck();
                }
                else
                {
                    Com_Ack();
                    Com_SetSerialNumber(man.serialNumber);
                    cDebug("Read : man.serialNumber = %s\r\n", man.serialNumber);
                }
			break;                 
			case PFC_GLOBAL_MODEL://�ͺţ�������ֻ�ܶ������ص�Ϊ�ַ���                
				if(write)
                {
                    Com_NAck();
                }
                else
                {
                    Com_Ack();
                    Com_SetModel(man.modelString);
                    cDebug("Read : man.modelString = %s\r\n", man.modelString);
                }
			break; 
            case PFC_GLOBAL_SYNC_TIME://ͬ��ʱ��                                                    
                Com_NAck();
			break;  
			case PFC_GLOBAL_USED_TIME://��ʹ��ʱ��                                                     
                if(write)
                {
                    Com_NAck();
                }
                else
                {
                    Com_Ack();
                    Com_SetTotalUsedTime(man.deviceTotalUsedTime);
                    cDebug("Read : man.deviceTotalUsedTime = %d\r\n", man.deviceTotalUsedTime);
                }
			break;   
			 
			case PFC_GLOBAL_INPUT://�����                                                     
                if(write)
                {
                    Com_NAck();
                }
                else
                {
                    Com_Ack();
                    Com_SetInput(0, man.curInput&0x01);//ֻ��һ������㣬MI_EXT
                    cDebug("Read : man.curInput = 0x%02X\r\n", man.curInput);
                }
			break; 
			case PFC_GLOBAL_OUTPUT://�����
                Com_Ack();
                if(write)
                {
                    if(data[0] == 0)
                        MO_EXT = !!data[1];
                    cDebug("Write : Output-%d = %d\r\n", data[0], data[1]);
                }
                else
                {
                    if(data[0] == 0)
                    {
                        Com_SetOutput(0, !!MO_EXT);//ֻ��һ������㣬MO_EXT
                        cDebug("Read : MO_EXT = %d\r\n", (uint8_t)MO_EXT);
                    }
                }
			break;
            case PFC_GLOBAL_TICK://������                                                    
                if(write)
                {
                    //Com_Ack();
                    if(!man.isConnect)
                    {
#if USED_UARTLCD		
                        SetButtonValue(RUNPAGE_INDEX, RUNPAGE_CONNECT_BUTTON, 1);
#endif
                        cDebug("Connected!");
                    }
                    man.isConnect = 1;
//                    man.tickLostCnt = 0;
                    
                }
                else
                    Com_NAck();
			break; 
			case PFC_GLOBAL_ERROR://ϵͳ����                                                    
                if(write)
                {
                    ComProcessFrame_SystemError(data[0]);
                }
                else
                {
                    Com_Ack();
                    cDebug("Read : PFC_GLOBAL_ERROR\r\n");
                }
			break;
            
            case PFC_GLOBAL_EXT_SYSTEM://ͨ��ϵͳ����
                if (write)
                    ComProcessFrame_WriteGlobalExternSystem(msg, size);
                else
                    ComProcessFrame_ReadGlobalExternSystem(msg, size);
                break;
            case PFC_GLOBAL_EXT_USER://ͨ���û��Զ������
								if (write)
                    ComProcessFrame_WriteGlobalExternUser(msg, size);
                else
                    ComProcessFrame_ReadGlobalExternUser(msg, size);
                break;
          
			default:
                Com_NAck();
				cDebug("\r\n '%02x' Error Function Code !!\r\n", pfc);//cDebug("\r\n Function Code Error !!\r\n");
			break;   
		}       
	}
	else
    {
        Com_NAck();
		cDebug("\r\n '%02x' Error address code !!\r\n", address);//cDebug("\r\n Address code error !!\r\n");
    }        

}




