#include "management.h"
#include "miscellaneous.h"

#include "ComQueue.h"
#include "ComProcess.h"

#include "config.h"

#include "CPrintf.h"

#include "24cxx.h"

#include "ComDriver.h"

#include "math.h"
#include "stdlib.h"

#include "wdg.h"
#include "Key.h"
#include "simplc_io.h"

Man_TypeDef man;

void InitMan(void)
{
    uint8_t eepromDefaultData;
    uint8_t i;
    //uint32_t temp;

    IWDG_Feed();
  
    cDebug("InitMan()...\r\n");
    
    //得到芯片唯一码做网口物理地址
    GetChipID(man.chipID);
    
    eepromDefaultData = AT24CXX_ReadOneByte(EEPROM_ADDR_DEFAULT);    
    if(eepromDefaultData != EEPROM_DEFAULT_DATA)//读3次
    {
        eepromDefaultData = AT24CXX_ReadOneByte(EEPROM_ADDR_DEFAULT);  
    }
    if(eepromDefaultData != EEPROM_DEFAULT_DATA)
    {
        eepromDefaultData = AT24CXX_ReadOneByte(EEPROM_ADDR_DEFAULT);  
    }
    //if(eepromDefaultData != EEPROM_DEFAULT_DATA && eepromDefaultData != EEPROM_FACTORY_DATA)//第一次初始化EEPROM
    if(eepromDefaultData != EEPROM_DEFAULT_DATA)
    //if(1)
    {
        cDebug("Reset to default data---First power on!--0x%X\r\n", eepromDefaultData);
        
        IWDG_Feed();
      
        man.machineAddress = 0x01;
        man.model = 0x00; //10ml
        strcpy((char*)man.modelString, (const char*)"PUP0010");
        
        man.comType = 0; //选择串口
        man.localIP[0] = 192;
        man.localIP[1] = 168;
        man.localIP[2] = 1;
        man.localIP[3] = 200;
        man.localPort = 5550;
        man.remoteIP[0] = 192;
        man.remoteIP[1] = 168;
        man.remoteIP[2] = 1;
        man.remoteIP[3] = 100;
        man.remotePort = 5560;
        man.brightness = 20;
        man.alarmSound = 1;
        man.language = 0;
        man.protocol = 0;//塬锐通信协议
        
        strcpy((char*)man.serialNumber, (const char*)"111111");
        strcpy((char*)man.productDate, (const char*)"20191020");
        strcpy((char*)man.superPassword, (const char*)"123456");
        
        man.usefulDays = 1;
        man.isCracked = 1;
        man.eepromDate.year = 0;
        man.eepromDate.month = 0;
        man.eepromDate.day = 0;
        
        man.deviceTotalUsedTime = 0;

        IWDG_Feed();
        
        //cDebug("Init success0\r\n");
        
        AT24CXX_WriteOneByte(EEPROM_ADDR_MACHINEADDRESS, man.machineAddress); 
        AT24CXX_WriteOneByte(EEPROM_ADDR_MODEL, man.model);
        AT24CXX_Write(EEPROM_ADDR_MODELSTRING, (uint8_t*)&man.modelString, strlen((const char*)man.modelString)+1);
        
        AT24CXX_WriteOneByte(EEPROM_ADDR_COMTYPE, man.comType);
        AT24CXX_Write(EEPROM_ADDR_LOCALIP, man.localIP, 4);
        AT24CXX_Write(EEPROM_ADDR_LOCALPORT, (uint8_t*)&man.localPort, 2);
        AT24CXX_Write(EEPROM_ADDR_REMOTEIP, man.remoteIP, 4);
        AT24CXX_Write(EEPROM_ADDR_REMOTEPORT, (uint8_t*)&man.remotePort, 2);
        AT24CXX_WriteOneByte(EEPROM_ADDR_BRIGHTNESS, man.brightness);
        AT24CXX_WriteOneByte(EEPROM_ADDR_LANGUAGE, man.language);
        AT24CXX_WriteOneByte(EEPROM_ADDR_ALARMSOUND, man.alarmSound);      
        AT24CXX_WriteOneByte(EEPROM_ADDR_PROTOCOL, man.protocol);
        
        IWDG_Feed();
        
        //cDebug("Init success1\r\n");
        
        //字符串的EEPROM读写需要注意
        AT24CXX_Write(EEPROM_ADDR_SERIALNUMBER, (uint8_t*)&man.serialNumber, strlen((const char*)man.serialNumber)+1);
        AT24CXX_Write(EEPROM_ADDR_PRODUCTDATE, (uint8_t*)&man.productDate, strlen((const char*)man.productDate)+1);
        AT24CXX_Write(EEPROM_ADDR_SUPERPASSWORD, (uint8_t*)&man.superPassword, strlen((const char*)man.superPassword)+1);
        
        IWDG_Feed();

        AT24CXX_Write(EEPROM_ADDR_USEFULDAYS, (uint8_t*)&man.usefulDays, 2); 
        AT24CXX_WriteOneByte(EEPROM_ADDR_ISCRACKED, man.isCracked);
        
        AT24CXX_Write(EEPROM_ADDR_DEVICETOTALUSEDTIME, (uint8_t*)&man.deviceTotalUsedTime, 4);
        
        AT24CXX_WriteOneByte(EEPROM_ADDR_DEFAULT, EEPROM_DEFAULT_DATA);  
    }
//    else if(eepromDefaultData == EEPROM_FACTORY_DATA)//恢复出厂设置
//    {
//        cDebug("Reset to default data!\r\n");
//    }
    
    else//读取EEPROM内容
    {
        cDebug("Read data from EEPROM!\r\n");

        man.machineAddress = AT24CXX_ReadOneByte(EEPROM_ADDR_MACHINEADDRESS); 
        man.model = AT24CXX_ReadOneByte(EEPROM_ADDR_MODEL);
        AT24CXX_Read(EEPROM_ADDR_MODELSTRING, (uint8_t*)&man.modelString, MODELSTRING_SIZE);
        
        man.comType = AT24CXX_ReadOneByte(EEPROM_ADDR_COMTYPE);
        AT24CXX_Read(EEPROM_ADDR_LOCALIP, man.localIP, 4);
        AT24CXX_Read(EEPROM_ADDR_LOCALPORT, (uint8_t*)&man.localPort, 2);
        AT24CXX_Read(EEPROM_ADDR_REMOTEIP, man.remoteIP, 4);
        AT24CXX_Read(EEPROM_ADDR_REMOTEPORT, (uint8_t*)&man.remotePort, 2);
        man.brightness = AT24CXX_ReadOneByte(EEPROM_ADDR_BRIGHTNESS);
        man.alarmSound = AT24CXX_ReadOneByte(EEPROM_ADDR_ALARMSOUND);
        man.language = AT24CXX_ReadOneByte(EEPROM_ADDR_LANGUAGE);  
        man.protocol = AT24CXX_ReadOneByte(EEPROM_ADDR_PROTOCOL);
      
        AT24CXX_Read(EEPROM_ADDR_SERIALNUMBER, (uint8_t*)&man.serialNumber, SERIALNUMBER_SIZE);
        AT24CXX_Read(EEPROM_ADDR_PRODUCTDATE, (uint8_t*)&man.productDate, PRODUCTDATE_SIZE);
        AT24CXX_Read(EEPROM_ADDR_SUPERPASSWORD, (uint8_t*)&man.superPassword, SUPERPASSWORD_SIZE);

        AT24CXX_Read(EEPROM_ADDR_USEFULDAYS, (uint8_t*)&man.usefulDays, 2);
        man.isCracked = AT24CXX_ReadOneByte(EEPROM_ADDR_ISCRACKED);
        
        AT24CXX_Read(EEPROM_ADDR_DATE, (uint8_t*)(&man.eepromDate), 3*4);
//        AT24CXX_Read(EEPROM_ADDR_DATE, (uint8_t*)&man.eepromDate.year, 4);
//        AT24CXX_Read(EEPROM_ADDR_DATE+4, (uint8_t*)&man.eepromDate.month, 4);
//        AT24CXX_Read(EEPROM_ADDR_DATE+8, (uint8_t*)&man.eepromDate.day, 4);
        
        AT24CXX_Read(EEPROM_ADDR_DEVICETOTALUSEDTIME, (uint8_t*)&man.deviceTotalUsedTime, 4);
        
    }
    
    IWDG_Feed();
		
		//man.comType = 1;
		
    cDebug("man.machineAddress = %d\r\n", man.machineAddress);
    cDebug("man.model = %d\r\n", man.model);
    cDebug("man.modelString = %s\r\n", man.modelString);
    
    cDebug("man.comType = %d\r\n", man.comType);
    cDebug("man.localIP = %d.%d.%d.%d\r\n", man.localIP[0], man.localIP[1], man.localIP[2], man.localIP[3]);
    cDebug("man.localPort = %d\r\n", man.localPort);
    cDebug("man.remoteIP = %d.%d.%d.%d\r\n", man.remoteIP[0], man.remoteIP[1], man.remoteIP[2], man.remoteIP[3]);
    cDebug("man.remotePort = %d\r\n", man.remotePort);
    cDebug("man.brightness = %d\r\n", man.brightness);
    cDebug("man.language = %d\r\n", man.language);
    cDebug("man.alarmSound = %d\r\n", man.alarmSound);

    cDebug("man.serialNumber = %s\r\n", man.serialNumber);
    cDebug("man.productDate = %s\r\n", man.productDate);
    //cDebug("man.superPassword = %s\r\n", man.superPassword);
    
    
    cDebug("man.usefulDays = %d\r\n", man.usefulDays);
    cDebug("man.isCracked = %d\r\n", man.isCracked);
    cDebug("man.eepromDate.year = %d\r\n", man.eepromDate.year);
    cDebug("man.eepromDate.month = %d\r\n", man.eepromDate.month);
    cDebug("man.eepromDate.day = %d\r\n", man.eepromDate.day);
    
    cDebug("man.deviceTotalUsedTime = %d\r\n", man.deviceTotalUsedTime);
    
		cDebug("EEPROM_ADDR_RESERVE = %d\r\n", EEPROM_ADDR_RESERVE);
		cDebug("EEPROM_ADDR_PULSECOMPENTABLESIZE = %d\r\n", EEPROM_ADDR_PULSECOMPENTABLESIZE);
    cDebug("EEPROM_ADDR_FACTORYDATA = %d\r\n", EEPROM_ADDR_FACTORYDATA);
    cDebug("EEPROM_ADDR_FACTORYDATA_REAL = %d\r\n", EEPROM_ADDR_FACTORYDATA_REAL); 
    cDebug("EEPROM_ADDR_DEVICEONLY = %d\r\n", EEPROM_ADDR_DEVICEONLY);
    cDebug("EEPROM_ADDR_END = %d\r\n", EEPROM_ADDR_END);
    cDebug("EEPROM_ADDR_MAX = %d\r\n", EE_TYPE);//EEPROM最大地址
    
    man.controlState = Controller_All;

    man.prevInput = 0x03;
    man.curInput = 0x03;
    
    srand(TIM2->CNT);
    man.randomCode = rand();
    
    switch(man.protocol)
    {
      case 0://塬锐协议
        man.ProtocolComQueue_FindCmd = ComQueue_FindCmd;
				man.ProtocolComProcessFrame = ComProcessFrame;
				cDebug("This is YuanRui protocol!\r\n");
      break;
      default:
        man.ProtocolComQueue_FindCmd = ComQueue_FindCmd;
				man.ProtocolComProcessFrame = ComProcessFrame;
				cDebug("This is Default protocol--YuanRui!\r\n");
      break;
    }
    
    cDebug("InitMan()...Finish\r\n");
}

void UploadAllData(void)
{
  uint8_t i;
  
  //设备参数
  Com_SystemExt_SetSoftwareVersion((uint8_t*)SOFTWARE_VERSION);
  Com_SystemExt_SetHardwareVersion((uint8_t*)HARDWARE_VERSION);
  Com_SystemExt_SetProductDate(man.productDate);
  Com_SystemExt_SetSerialNumber(man.serialNumber);
  Com_SystemExt_SetModel(man.model);
  Com_SystemExt_SetModelString(man.modelString);
  Com_SystemExt_SetTotalUsedTime(man.deviceTotalUsedTime);
  Com_SystemExt_SetProtocol(man.protocol);

  Com_SystemExt_SetSaveAllData();//结束
}

void SetCoilMutual(uint8_t num)
{
	uint8_t i;
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	if(num > Y_COIL8 || man.currentKey == num)
		return;
	
	if(!GYL(num))
	{
		for(i=0;i<=Y_COIL8;i++)
		{
			if(num == i)
				SYL(num, 1);
			else
				SYL(num, 0);
		}
	}
	
	//恢复上一按键引脚的输入特性
	GPIO_InitStructure.GPIO_Pin = KeyPin[man.currentKey].pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	//输入 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(KeyPin[man.currentKey].port, &GPIO_InitStructure);					 
  GPIO_SetBits(KeyPin[man.currentKey].port, KeyPin[man.currentKey].pin);
	
	//点亮按键LED灯
	GPIO_InitStructure.GPIO_Pin = KeyPin[num].pin;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	 //输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(KeyPin[num].port, &GPIO_InitStructure);					 
  GPIO_ResetBits(KeyPin[num].port, KeyPin[num].pin);
	
	man.currentKey = num;
}
