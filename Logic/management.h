
#ifndef __MANAGEMENT_H_
#define __MANAGEMENT_H_

#include "stdint.h"
#include "miscellaneous.h"
#include "ComQueue.h"

//�����Ϣ
#define HARDWARE_VERSION    "SolValB01"
#define SOFTWARE_VERSION    "V1.0.0"

//��
#define PULSECOMPENTABLE_SIZE           40
#define FLOWCALIBTABLE_SIZE             15
#define PRESSCALIBTABLE_SIZE            10
#define TIMEPROGRAMTABLE_SIZE           20
#define MOTORCURRENTTABLE_SIZE          20

#define TIMEPROGRAMGROUP_NUMBER         5 //�ж�����ʱ�����

#define PRESSBUFFER_SIZE                50
#define PRESSORDERFILTERBUFFER_SIZE     30
#define PRESSMAXORDERFILTERBUFFER_SIZE  50

//EEPROMԪ�ش�С
#define SERIALNUMBER_SIZE               20 //���к���󳤶�
#define PRODUCTDATE_SIZE                20 //����������󳤶�
#define SUPERPASSWORD_SIZE              10 //����������󳤶�
#define MODELSTRING_SIZE                10 //�ͺ��ַ�����󳤶�

//����ģʽ
#define WORKMODE_NORMAL			  0x00
#define WORKMODE_FLOWCALIB		0x01
#define WORKMODE_PRESSCALIB		0x02
#define WORKMODE_MOTORCURRENT	0x04

//EEPROMĬ�ϵ�ַ��Ĭ�����ݣ�������Ǹ����ݣ�������һ���������Զ��ظ���������
#define EEPROM_DEFAULT_DATA             0x1A
//#define EEPROM_FACTORY_DATA             0x05 //����ǰ�ᱣ��һ��У����������

//EEPROM���ݵ�ַ
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
#define EEPROM_ADDR_PRESSUPLOADFREQ     (EEPROM_ADDR_PRESSCOMPEN+1)//ѹ���ϴ�Ƶ��

#define EEPROM_ADDR_PROTOCOL            (EEPROM_ADDR_PRESSUPLOADFREQ+1)//ͨ��Э��

//�岩����ѹ��
#define EEPROM_ADDR_RUNMODE             (EEPROM_ADDR_PROTOCOL+1)
#define EEPROM_ADDR_PRESSHOLDFLOWMAX    (EEPROM_ADDR_RUNMODE+4)
#define EEPROM_ADDR_PRESSHOLDFLOWMIN    (EEPROM_ADDR_PRESSHOLDFLOWMAX+4)
#define EEPROM_ADDR_PRESSHOLDPRESSTHR   (EEPROM_ADDR_PRESSHOLDFLOWMIN+4)
#define EEPROM_ADDR_PRESSHOLDPRESS	    (EEPROM_ADDR_PRESSHOLDPRESSTHR+4)

#define EEPROM_ADDR_MEDIUM	    				(EEPROM_ADDR_PRESSHOLDPRESSTHR+4)

#define EEPROM_ADDR_RESERVE             (EEPROM_ADDR_MEDIUM+1)//������

//#define EEPROM_ADDR_PULSECOMPENTABLESIZE  (EEPROM_ADDR_RESERVE+21)//��������
#define EEPROM_ADDR_PULSECOMPENTABLESIZE  0x008F//��������  143
#define EEPROM_ADDR_PULSECOMPENTABLE      (EEPROM_ADDR_PULSECOMPENTABLESIZE+1)
#define EEPROM_ADDR_PULSECOMPENTABLEEND   (EEPROM_ADDR_PULSECOMPENTABLE+2*4*PULSECOMPENTABLE_SIZE)//���40����

#define EEPROM_ADDR_FLOWCALIBTABLESIZE  (EEPROM_ADDR_PULSECOMPENTABLEEND+1)//���ٲ���
#define EEPROM_ADDR_FLOWCALIBTABLE      (EEPROM_ADDR_FLOWCALIBTABLESIZE+1)
#define EEPROM_ADDR_FLOWCALIBTABLEEND   (EEPROM_ADDR_FLOWCALIBTABLE+2*4*FLOWCALIBTABLE_SIZE)//���20����
#define EEPROM_ADDR_FLOWCALIBLOADFLOW   (EEPROM_ADDR_FLOWCALIBTABLEEND+1)
#define EEPROM_ADDR_FLOWCALIBLOADREALFLOW   (EEPROM_ADDR_FLOWCALIBLOADFLOW+4)
#define EEPROM_ADDR_FLOWCALIBLOADPRESS  (EEPROM_ADDR_FLOWCALIBLOADREALFLOW+4)

#define EEPROM_ADDR_PRESSCALIBTABLESIZE (EEPROM_ADDR_FLOWCALIBLOADPRESS+4)//ѹ������
#define EEPROM_ADDR_PRESSCALIBTABLE     (EEPROM_ADDR_PRESSCALIBTABLESIZE+1)
#define EEPROM_ADDR_PRESSCALIBTABLEEND  (EEPROM_ADDR_PRESSCALIBTABLE+2*4*PRESSCALIBTABLE_SIZE)//���20����
#define EEPROM_ADDR_PRESSVOLTAGEOFFSET  (EEPROM_ADDR_PRESSCALIBTABLEEND+1)

#define EEPROM_ADDR_TIMEPROGRAMUPDATESEL  (EEPROM_ADDR_PRESSVOLTAGEOFFSET+4)//�ڲ�ʱ�����
#define EEPROM_ADDR_TIMEPROGRAMTABLESIZE (EEPROM_ADDR_TIMEPROGRAMUPDATESEL+1)
#define EEPROM_ADDR_TIMEPROGRAMTABLE     (EEPROM_ADDR_TIMEPROGRAMTABLESIZE+1*TIMEPROGRAMGROUP_NUMBER)
#define EEPROM_ADDR_TIMEPROGRAMTABLEEND  (EEPROM_ADDR_TIMEPROGRAMTABLE+3*4*TIMEPROGRAMTABLE_SIZE*TIMEPROGRAMGROUP_NUMBER)

#define EEPROM_ADDR_MOTORCURRENTTABLESIZE (EEPROM_ADDR_TIMEPROGRAMTABLEEND+4)//�������
#define EEPROM_ADDR_MOTORCURRENTTABLE     (EEPROM_ADDR_MOTORCURRENTTABLESIZE+1)
#define EEPROM_ADDR_MOTORCURRENTTABLEEND  (EEPROM_ADDR_MOTORCURRENTTABLE+(4+1)*MOTORCURRENTTABLE_SIZE)//���20����

#define EEPROM_ADDR_FACTORYDATA         (EEPROM_ADDR_MOTORCURRENTTABLEEND+4) //���������ݵ���ʼ�����ַ
#define EEPROM_ADDR_FACTORYDATA_REAL      (4000) //����ĳ������ñ����ַΪ2000����������4000�������̶���ַ

//#define EEPROM_ADDR_USEFULDAYS          (EEPROM_ADDR_FACTORYDATA*2+4)//ƫ����2��+4
#define EEPROM_ADDR_DEVICEONLY          (8000) //ÿ̨�豸���в�����ʼ�����ַ���ָ��������ò�������
#define EEPROM_ADDR_USEFULDAYS          (EEPROM_ADDR_DEVICEONLY)//����Ŀ�ʹ������Ϊ4023������̶�Ϊ8000����EEPROM����ַΪ8191��
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
    //�豸����
    uint8_t machineAddress;
    uint8_t model;//�豸�ͺ� 0:10ml 1:50ml 2:100ml 3:200ml 4:500ml 5:1000ml 6:3000ml 7:100ml�����ѹ��
    uint8_t modelString[MODELSTRING_SIZE];
		uint8_t protocol;//ͨ��Э�� 0��ܫ��Ĭ�ϣ� 1���岩��		2���¹�ŵ��
    //Э�麯��ָ��
    qsize (*ProtocolComQueue_FindCmd)(qdata *ascii_buffer, qdata *hex_buffer, qsize buf_len, QUEUE *que);
    void (*ProtocolComProcessFrame)( void *buffer, uint16 size );
  
    //ͨ�Ų���
    uint8_t comType;//ͨ�Žӿ� 0��RS232 1:net
    uint8_t localIP[4];
    uint16_t localPort;
    uint8_t remoteIP[4];
    uint16_t remotePort;
    
    uint8_t brightness;//��Ļ����
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
    uint8_t isValidatedActiveCode;//��������Ч���򱣴�һ�ε�ǰʱ��
    
    uint8_t curInput;
    uint8_t prevInput;
    uint8_t raisingEdgeInput;
    uint8_t fallingEdgeInput;
		
    //ͨ��������
    uint8_t tickTimeCnt;
    uint8_t isTickSend;
    uint8_t tickLostCnt;   
    uint8_t isConnect;
    
    //����Ȩ������ֹͣ״̬��Ϊ0
    ControlState_TypeDef controlState;//0���޿����� 1���豸�˿��� 2����λ������

    //
    uint8_t secTimeoutFlag;//����ʱ��
    uint32_t collectorPowerOnTotalSecond; //�豸�������ʱ
		
    
    /****************************��***************************/
    //������
    uint16_t cnt1S; //ÿ���1
    uint8_t pumpStartFlag;
    uint8_t pumpPauseFlag;//��ͣ
    uint8_t pumpPurgeFlag;

		
    /****************************��������****************************/
    uint8_t workMode; //����ģʽ����Ҫ���ڽ���У��ģʽ
    
    uint8_t factoryMode;
    uint8_t priority;//Ȩ�޼���
		
		
		uint8_t key;
		uint8_t beepFlag;//������һ��,����������
    
}Man_TypeDef;

extern Man_TypeDef man;

void InitMan(void);
void UploadAllData(void);

#endif
