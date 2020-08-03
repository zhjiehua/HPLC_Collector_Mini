
#ifndef __MANAGEMENT_H_
#define __MANAGEMENT_H_

#include "stdint.h"
#include "miscellaneous.h"
#include "ComQueue.h"

//相关信息
#define HARDWARE_VERSION    "SolValB01"
#define SOFTWARE_VERSION    "V1.0.0"

//泵
#define PULSECOMPENTABLE_SIZE           40
#define FLOWCALIBTABLE_SIZE             15
#define PRESSCALIBTABLE_SIZE            10
#define TIMEPROGRAMTABLE_SIZE           20
#define MOTORCURRENTTABLE_SIZE          20

#define TIMEPROGRAMGROUP_NUMBER         5 //有多少组时间程序

#define PRESSBUFFER_SIZE                50
#define PRESSORDERFILTERBUFFER_SIZE     30
#define PRESSMAXORDERFILTERBUFFER_SIZE  50

//EEPROM元素大小
#define SERIALNUMBER_SIZE               20 //序列号最大长度
#define PRODUCTDATE_SIZE                20 //出厂日期最大长度
#define SUPERPASSWORD_SIZE              10 //出厂日期最大长度
#define MODELSTRING_SIZE                10 //型号字符串最大长度

//工作模式
#define WORKMODE_NORMAL			  0x00
#define WORKMODE_FLOWCALIB		0x01
#define WORKMODE_PRESSCALIB		0x02
#define WORKMODE_MOTORCURRENT	0x04

//EEPROM默认地址的默认数据，如果不是改数据，则在下一次重启后自动回复出厂设置
#define EEPROM_DEFAULT_DATA             0x1A
//#define EEPROM_FACTORY_DATA             0x05 //出厂前会保存一次校正过的数据

//EEPROM数据地址
#define EEPROM_ADDR_BASE                0
#define EEPROM_ADDR_DEFAULT             EEPROM_ADDR_BASE
#define EEPROM_ADDR_MACHINEADDRESS      (EEPROM_ADDR_DEFAULT+1)       
#define EEPROM_ADDR_MODEL               (EEPROM_ADDR_MACHINEADDRESS+1)
#define EEPROM_ADDR_MODELSTRING         (EEPROM_ADDR_MODEL+1)
#define EEPROM_ADDR_COMTYPE             (EEPROM_ADDR_MODELSTRING+MODELSTRING_SIZE)
#define EEPROM_ADDR_LOCALIP             (EEPROM_ADDR_COMTYPE+1)
#define EEPROM_ADDR_LOCALPORT           (EEPROM_ADDR_LOCALIP+4)
#define EEPROM_ADDR_REMOTEIP            (EEPROM_ADDR_LOCALPORT+2)
#define EEPROM_ADDR_REMOTEPORT          (EEPROM_ADDR_REMOTEIP+4)
#define EEPROM_ADDR_BRIGHTNESS          (EEPROM_ADDR_REMOTEPORT+2)
#define EEPROM_ADDR_LANGUAGE            (EEPROM_ADDR_BRIGHTNESS+1)
#define EEPROM_ADDR_ALARMSOUND          (EEPROM_ADDR_LANGUAGE+1)
#define EEPROM_ADDR_SERIALNUMBER        (EEPROM_ADDR_ALARMSOUND+1)
#define EEPROM_ADDR_PRODUCTDATE         (EEPROM_ADDR_SERIALNUMBER+SERIALNUMBER_SIZE)
#define EEPROM_ADDR_SUPERPASSWORD       (EEPROM_ADDR_PRODUCTDATE+PRODUCTDATE_SIZE)

#define EEPROM_ADDR_FLOW                (EEPROM_ADDR_SUPERPASSWORD+SUPERPASSWORD_SIZE)
#define EEPROM_ADDR_FLOWPURGE           (EEPROM_ADDR_FLOW+4)
#define EEPROM_ADDR_FLOWPURGETIME       (EEPROM_ADDR_FLOWPURGE+4)
#define EEPROM_ADDR_PRESSMIN            (EEPROM_ADDR_FLOWPURGETIME+1)
#define EEPROM_ADDR_PRESSMAX            (EEPROM_ADDR_PRESSMIN+4)
#define EEPROM_ADDR_PRESSWARNING        (EEPROM_ADDR_PRESSMAX+4)
#define EEPROM_ADDR_PROGRAMSEL          (EEPROM_ADDR_PRESSWARNING+4)
#define EEPROM_ADDR_MODE                (EEPROM_ADDR_PROGRAMSEL+1)
#define EEPROM_ADDR_PRESSCOMPEN         (EEPROM_ADDR_MODE+1)
#define EEPROM_ADDR_PRESSUPLOADFREQ     (EEPROM_ADDR_PRESSCOMPEN+1)//压力上传频率

#define EEPROM_ADDR_PROTOCOL            (EEPROM_ADDR_PRESSUPLOADFREQ+1)//通信协议

//清博华恒压泵
#define EEPROM_ADDR_RUNMODE             (EEPROM_ADDR_PROTOCOL+1)
#define EEPROM_ADDR_PRESSHOLDFLOWMAX    (EEPROM_ADDR_RUNMODE+4)
#define EEPROM_ADDR_PRESSHOLDFLOWMIN    (EEPROM_ADDR_PRESSHOLDFLOWMAX+4)
#define EEPROM_ADDR_PRESSHOLDPRESSTHR   (EEPROM_ADDR_PRESSHOLDFLOWMIN+4)
#define EEPROM_ADDR_PRESSHOLDPRESS	    (EEPROM_ADDR_PRESSHOLDPRESSTHR+4)

#define EEPROM_ADDR_MEDIUM	    				(EEPROM_ADDR_PRESSHOLDPRESSTHR+4)

#define EEPROM_ADDR_RESERVE             (EEPROM_ADDR_MEDIUM+1)//保留用

//#define EEPROM_ADDR_PULSECOMPENTABLESIZE  (EEPROM_ADDR_RESERVE+21)//脉动补偿
#define EEPROM_ADDR_PULSECOMPENTABLESIZE  0x008F//脉动补偿  143
#define EEPROM_ADDR_PULSECOMPENTABLE      (EEPROM_ADDR_PULSECOMPENTABLESIZE+1)
#define EEPROM_ADDR_PULSECOMPENTABLEEND   (EEPROM_ADDR_PULSECOMPENTABLE+2*4*PULSECOMPENTABLE_SIZE)//最多40个点

#define EEPROM_ADDR_FLOWCALIBTABLESIZE  (EEPROM_ADDR_PULSECOMPENTABLEEND+1)//流速补偿
#define EEPROM_ADDR_FLOWCALIBTABLE      (EEPROM_ADDR_FLOWCALIBTABLESIZE+1)
#define EEPROM_ADDR_FLOWCALIBTABLEEND   (EEPROM_ADDR_FLOWCALIBTABLE+2*4*FLOWCALIBTABLE_SIZE)//最多20个点
#define EEPROM_ADDR_FLOWCALIBLOADFLOW   (EEPROM_ADDR_FLOWCALIBTABLEEND+1)
#define EEPROM_ADDR_FLOWCALIBLOADREALFLOW   (EEPROM_ADDR_FLOWCALIBLOADFLOW+4)
#define EEPROM_ADDR_FLOWCALIBLOADPRESS  (EEPROM_ADDR_FLOWCALIBLOADREALFLOW+4)

#define EEPROM_ADDR_PRESSCALIBTABLESIZE (EEPROM_ADDR_FLOWCALIBLOADPRESS+4)//压力补偿
#define EEPROM_ADDR_PRESSCALIBTABLE     (EEPROM_ADDR_PRESSCALIBTABLESIZE+1)
#define EEPROM_ADDR_PRESSCALIBTABLEEND  (EEPROM_ADDR_PRESSCALIBTABLE+2*4*PRESSCALIBTABLE_SIZE)//最多20个点
#define EEPROM_ADDR_PRESSVOLTAGEOFFSET  (EEPROM_ADDR_PRESSCALIBTABLEEND+1)

#define EEPROM_ADDR_TIMEPROGRAMUPDATESEL  (EEPROM_ADDR_PRESSVOLTAGEOFFSET+4)//内部时间程序
#define EEPROM_ADDR_TIMEPROGRAMTABLESIZE (EEPROM_ADDR_TIMEPROGRAMUPDATESEL+1)
#define EEPROM_ADDR_TIMEPROGRAMTABLE     (EEPROM_ADDR_TIMEPROGRAMTABLESIZE+1*TIMEPROGRAMGROUP_NUMBER)
#define EEPROM_ADDR_TIMEPROGRAMTABLEEND  (EEPROM_ADDR_TIMEPROGRAMTABLE+3*4*TIMEPROGRAMTABLE_SIZE*TIMEPROGRAMGROUP_NUMBER)

#define EEPROM_ADDR_MOTORCURRENTTABLESIZE (EEPROM_ADDR_TIMEPROGRAMTABLEEND+4)//电机电流
#define EEPROM_ADDR_MOTORCURRENTTABLE     (EEPROM_ADDR_MOTORCURRENTTABLESIZE+1)
#define EEPROM_ADDR_MOTORCURRENTTABLEEND  (EEPROM_ADDR_MOTORCURRENTTABLE+(4+1)*MOTORCURRENTTABLE_SIZE)//最多20个点

#define EEPROM_ADDR_FACTORYDATA         (EEPROM_ADDR_MOTORCURRENTTABLEEND+4) //另存出厂数据的起始保存地址
#define EEPROM_ADDR_FACTORYDATA_REAL      (4000) //上面的出厂设置保存地址为2000，这里扩大到4000，给个固定地址

//#define EEPROM_ADDR_USEFULDAYS          (EEPROM_ADDR_FACTORYDATA*2+4)//偏移了2倍+4
#define EEPROM_ADDR_DEVICEONLY          (8000) //每台设备固有参数起始保存地址，恢复出厂设置不起作用
#define EEPROM_ADDR_USEFULDAYS          (EEPROM_ADDR_DEVICEONLY)//上面的可使用天数为4023，这里固定为8000（该EEPROM最大地址为8191）
#define EEPROM_ADDR_ISCRACKED           (EEPROM_ADDR_USEFULDAYS+2)
#define EEPROM_ADDR_DATE                (EEPROM_ADDR_ISCRACKED+1)
#define EEPROM_ADDR_DEVICETOTALUSEDTIME (EEPROM_ADDR_DATE+3*4)

#define EEPROM_ADDR_END                 (EEPROM_ADDR_DEVICETOTALUSEDTIME+4)


typedef enum
{
    Controller_All = 0,
    Controller_Local,
    Controller_Remote,
}ControlState_TypeDef;

//====================================
typedef struct
{
    //设备参数
    uint8_t machineAddress;
    uint8_t model;//设备型号 0:10ml 1:50ml 2:100ml 3:200ml 4:500ml 5:1000ml 6:3000ml 7:100ml吉天恒压泵
    uint8_t modelString[MODELSTRING_SIZE];
		uint8_t protocol;//通信协议 0：塬锐（默认） 1：清博华		2：德国诺尔
    //协议函数指针
    qsize (*ProtocolComQueue_FindCmd)(qdata *ascii_buffer, qdata *hex_buffer, qsize buf_len, QUEUE *que);
    void (*ProtocolComProcessFrame)( void *buffer, uint16 size );
  
    //通信参数
    uint8_t comType;//通信接口 0：RS232 1:net
    uint8_t localIP[4];
    uint16_t localPort;
    uint8_t remoteIP[4];
    uint16_t remotePort;
    
    uint8_t brightness;//屏幕亮度
    uint8_t language;
    uint8_t alarmSound;
    
    uint8_t serialNumber[SERIALNUMBER_SIZE];
    uint8_t productDate[PRODUCTDATE_SIZE];
    uint8_t superPassword[SUPERPASSWORD_SIZE];
    uint32_t deviceTotalUsedTime;
    
    uint32_t chipID[3];
		uint32_t serial;
		uint32_t randomCode;
		uint32_t activeCode;
		uint16_t usefulDays;
    uint8_t isCracked;
    struct date lcdDate;
    struct date eepromDate;
    uint8_t isValidatedActiveCode;//激活码有效，则保存一次当前时间
    
    uint8_t curInput;
    uint8_t prevInput;
    uint8_t raisingEdgeInput;
    uint8_t fallingEdgeInput;
		
    //通信心跳包
    uint8_t tickTimeCnt;
    uint8_t isTickSend;
    uint8_t tickLostCnt;   
    uint8_t isConnect;
    
    //控制权归属，停止状态下为0
    ControlState_TypeDef controlState;//0：无控制者 1：设备端控制 2：上位机控制

    //
    uint8_t secTimeoutFlag;//秒表计时用
    uint32_t collectorPowerOnTotalSecond; //设备启动后计时
		
    
    /****************************泵***************************/
    //测试用
    uint16_t cnt1S; //每秒加1
    uint8_t pumpStartFlag;
    uint8_t pumpPauseFlag;//暂停
    uint8_t pumpPurgeFlag;

		
    /****************************公共变量****************************/
    uint8_t workMode; //调试模式，主要用于进入校正模式
    
    uint8_t factoryMode;
    uint8_t priority;//权限级数
		
		
		uint8_t key;
		uint8_t beepFlag;//按键响一下,报警连续响
    
}Man_TypeDef;

extern Man_TypeDef man;

void InitMan(void);
void UploadAllData(void);

#endif
