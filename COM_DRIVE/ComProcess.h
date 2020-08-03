/*! 
*  \file hmi_driver.h
*  \brief ָ����ദ��
*  \version 1.0
*  \date 2012-2018
*  \copyright ���ݴ�ʹ��Ƽ����޹�˾
*/


#ifndef _COM_PROCESS_H_
#define _COM_PROCESS_H_

#include "ComDriver.h"
#include "stm32f10x.h"
#include <stdio.h>
#include "ComQueue.h"
#include "ComUart.h"
#include "usart.h"

#define SYSTEM_COMMUNICATE_HEAD ':'//0x3A                                    //֡ͷ
#define SYSTEM_COMMUNICATE_TAIL '!'//0x21                                    //֡β
#define SYSTEM_COMMUNICATE_ACK '#' //0x23
#define SYSTEM_COMMUNICATE_NACK '$' //0x24

//����ͨ��֡������*******************************************
//ͨ�ù�����*************************************************
#define PFC_GLOBAL_DEVICE_ADDRESS                   0X00  //�豸��ַ
#define PFC_GLOBAL_SOFTWARE_VERSION                 0X01  //����汾
#define PFC_GLOBAL_HARDWARE_VERSION                 0X02  //Ӳ���汾
#define PFC_GLOBAL_PRODUCT_DATE                     0X03  //��������
#define PFC_GLOBAL_SERIAL_NUMBER                    0X04  //���к�
#define PFC_GLOBAL_MODEL                            0X05  //�ͺ�
#define PFC_GLOBAL_USED_TIME                        0X06  //��ʹ��ʱ��
#define PFC_GLOBAL_SYNC_TIME                        0X07  //ͬ��ʱ��
#define PFC_GLOBAL_INPUT                            0X08  //�����
#define PFC_GLOBAL_OUTPUT                           0X09  //�����
#define PFC_GLOBAL_TICK								              0X0A  //������
//
#define PFC_GLOBAL_ERROR							              0X2D  //ϵͳ����
#define PFC_GLOBAL_EXT_SYSTEM                       0X2E  //ͨ��ϵͳ����
#define PFC_GLOBAL_EXT_USER                         0X2F  //ͨ���û��Զ������

//�����������***********************************************
#define PFC_CHECK_WAVE                             0X30  //����
#define PFC_CHECK_WAVE2                            0X31  //����2
#define PFC_CHECK_TIMECONST                        0X32  //ʱ�䳣��
#define PFC_CHECK_RANGE                            0X33  //����
#define PFC_CHECK_LAMP_TYPE                        0X34  //������
#define PFC_CHECK_CHANNEL                          0X35  //ͨ��
#define PFC_CHECK_LAMP                             0X36  //��״̬
#define PFC_CHECK_ZERO                             0X37  //���߹���
#define PFC_CHECK_HOME                             0X38  //�����
#define PFC_CHECK_AU_UPLOAD_FREQ                   0X39  //AUֵ�ϴ�Ƶ��
#define PFC_CHECK_AU                               0X3A  //AUֵ
#define PFC_CHECK_WAVE_REF_SAM                     0X3B  //�α�-����ֵ
#define PFC_CHECK_WAVE2_REF_SAM                    0X3C  //����2�α�-����ֵ
#define PFC_CHECK_SCAN_CMD                         0X3D  //����ɨ��ʹ��
#define PFC_CHECK_SCAN_AU                          0X3E  //����ɨ��AUֵ
#define PFC_CHECK_SCAN_PARA                        0X3F  //����ɨ�����
#define PFC_CHECK_LAMP_USED_TIME                   0X40  //��Դʹ��ʱ��
#define PFC_CHECK_START_STOP					             0X41  //����/ֹͣ�ɼ�
//
#define PFC_CHECK_EXT_SYSTEM                       0X4E  //�����ϵͳ����
#define PFC_CHECK_EXT_USER                         0X4F  //������û��Զ������

//��Һ�ù�����********************************************
#define PFC_PUMP_FLOW                              0X50  //����
#define PFC_PUMP_FLOW_PERCENT                      0X51  //���ٰٷֱ�
#define PFC_PUMP_PRESS_MIN                         0X52  //��Сѹ��
#define PFC_PUMP_PRESS_MAX                         0X53  //���ѹ��
#define PFC_PUMP_PRESS_WARNING                     0X54  //Ԥ��ѹ��
#define PFC_PUMP_START_STOP                        0X55  //����/ֹͣ��
#define PFC_PUMP_PAUSE_RESTORE                     0X56  //��ͣ
#define PFC_PUMP_PURGE                             0X57  //��ϴ
#define PFC_PUMP_PURGE_FLOW                        0X58  //��ϴ����
#define PFC_PUMP_PURGE_TIME                        0X59  //��ϴʱ��
#define PFC_PUMP_PRESS_ZERO                        0X5A  //ѹ������,ѹ����������ѹ����
#define PFC_PUMP_PRESS_UPLOAD_FREQ                 0X5B  //ѹ���ϴ�Ƶ��
#define PFC_PUMP_FLOW_PRESS_COMPEN                 0X5C  //ѹ������
#define PFC_PUMP_MODE                              0X5D  //��ģʽ
#define PFC_PUMP_PRESS                             0X5E  //ѹ��
#define PFC_PUMP_RUNMODE                           0X5F  ///������ģʽ
//
#define PFC_PUMP_EXT_SYSTEM						             0X6E  //��Һ��ϵͳ����
#define PFC_PUMP_EXT_USER						               0X6F  //��Һ���û��Զ������

//ϵͳ��չ������*********************************************
//ͨ�ù�����*************************************************
#define PFC_GES_PRIORITY							              0X00  //Ȩ�޼���
#define PFC_GES_RESET								                0X01  //����
#define PFC_GES_RESTORE_DEFAULT						          0X02  //�ָ���������
#define PFC_GES_SAVE_AS_DEFAULT						          0X03  //����Ϊ��������
#define PFC_GES_SUPERPASSWORD						            0X04  //����Ա����
#define PFC_GES_SOFTWARE_VERSION                    0X05  //����汾
#define PFC_GES_HARDWARE_VERSION                    0X06  //Ӳ���汾
#define PFC_GES_PRODUCT_DATE                        0X07  //��������
#define PFC_GES_SERIAL_NUMBER                       0X08  //���к�
#define PFC_GES_MODEL                               0X09  //�ͺ�
#define PFC_GES_MODEL_STRING                        0X0A  //�ͺ��ַ���
#define PFC_GES_USED_TIME                           0X0B  //��ʹ��ʱ��
#define PFC_GES_ALL_DATA                            0X0C  //ȫ������
#define PFC_GES_PROTOCOL                            0X0D  //ͨ��Э��

//�����������***********************************************
#define PFC_CES_COIL								        0X00  //���������/�ɿ�
#define PFC_CES_TIME_INTEGRAL						    0X01  //����ʱ��
#define PFC_CES_RANGE_INTEGRAL						  0X02  //��������
#define PFC_CES_AU_FACTOR						        0X03  //�궨ϵ��
#define PFC_CES_RASTER_STEP							    0X04  //��դת��ָ������
#define PFC_CES_HOME_OFFSET							    0X05  //���ƫ��
#define PFC_CES_WAVE_OFFSET							    0X06  //��������ƫ��
#define PFC_CES_WORKMODE						        0X07  //����ģʽ
#define PFC_CES_WAVECALIB_DATA						  0X08  //����У������
#define PFC_CES_WAVECALIB_DATA_CMD					0X09  //��дУ������ʹ��

//��Һ�ù�����********************************************
#define PFC_PES_WORKMODE							      0X00  //����ģʽ
#define PFC_PES_FLOWCALIB_DATA_CMD					0X01  //д����У������ʹ��
#define PFC_PES_FLOWCALIB_DATA						  0X02  //����У������
#define PFC_PES_FLOWCALIB_LOAD_FLOW					0X03  //����У����������
#define PFC_PES_FLOWCALIB_LOAD_REALFLOW			0X04  //����У������ʵ������
#define PFC_PES_FLOWCALIB_LOAD_PRESS				0X05  //����У������ѹ��
#define PFC_PES_PRESSCALIB_DATA_CMD					0X06  //дѹ��У������ʹ��
#define PFC_PES_PRESSCALIB_DATA						  0X07  //ѹ��У������
#define PFC_PES_PULSECOMPEN_DATA_CMD				0X08  //д������������ʹ��
#define PFC_PES_PULSECOMPEN_DATA					  0X09  //������������
#define PFC_PES_PULSECOMPEN_DEBUG_CMD				0X0A  //������������ʹ��
#define PFC_PES_PULSECOMPEN_GEAR   					0X0B  //��������͹�ָ�Ӧ��
#define PFC_PES_PULSECOMPEN_GEAR_POS				0X0C  //��������͹��λ��
#define PFC_PES_STEPMOTOR_IRUN						  0X0D  //����������е���
#define PFC_PES_MOTORCURRENT_DATA_CMD				0X0E  //д�����������ʹ��
#define PFC_PES_MOTORCURRENT_DATA					  0X0F  //�����������

//ϵͳ������********************************************
//ͨ�ô�����*************************************************

//�����������*************************************************
#define PEC_CHECK_REF_LOW                           0x10  //��α�ֵ������
#define PEC_CHECK_SAM_LOW                           0x11  //������ֵ������
#define PEC_CHECK_REF2_LOW                          0x12  //��α�2ֵ������
#define PEC_CHECK_SAM2_LOW                          0x13  //������2ֵ������
#define PEC_CHECK_REF_OVER                          0x14  //��α�ֵ�������
#define PEC_CHECK_SAM_OVER                          0x15  //������ֵ�������
#define PEC_CHECK_REF2_OVER                         0x16  //��α�2ֵ�������
#define PEC_CHECK_SAM2_OVER                         0x17  //������2ֵ�������

//��Һ�ô�����*************************************************
#define PEC_PUMP_STOP                               0x10  //������ֹͣ
#define PEC_PUMP_RUNNING                            0x11  //���������У�����Ȩ���豸��
#define PEC_PUMP_PRESS_LOW                          0x12  //�õ�ѹ����
#define PEC_PUMP_PRESS_HIGH                         0x13  //�ó�ѹ����


//�û���չ������*********************************************
//ͨ�ù�����*************************************************
#define PFC_GEU_KEY							              			0X00  //����
#define PFC_GEU_LCD								                	0X01  //LCD

#define PTR2U16(PTR) ((((uint8 *)(PTR))[0]<<8)|((uint8 *)(PTR))[1])  //�ӻ�����ȡ16λ����
#define PTR2U32(PTR) ((((uint8 *)(PTR))[0]<<24)|(((uint8 *)(PTR))[1]<<16)|(((uint8 *)(PTR))[2]<<8)|((uint8 *)(PTR))[3])  //�ӻ�����ȡ32λ����

#pragma pack(push)
#pragma pack(1)                           //���ֽڶ���

typedef struct
{
    uint8    address;                    //Ŀ�ĵ�ַ  
    uint8    pfc;                        //������
    uint8    data[20];                   //������Ϣ�Ļ���ID
}ComFrame_TypeDef;

#pragma pack(pop)


void ComProcessFrame( void *buffer, uint16 size );
void ComProcessFrame_WriteGlobalExternSystem( ComFrame_TypeDef *msg, uint16 size );
void ComProcessFrame_ReadGlobalExternSystem( ComFrame_TypeDef *msg, uint16 size );
void ComProcessFrame_WritePumpExternSystem( ComFrame_TypeDef *msg, uint16 size );
void ComProcessFrame_ReadPumpExternSystem( ComFrame_TypeDef *msg, uint16 size );
void ComProcessFrame_SystemError(uint8_t errorCode);

void ComProcessFrame_ReadGlobalExternUser( ComFrame_TypeDef *msg, uint16 size );
void ComProcessFrame_WriteGlobalExternUser( ComFrame_TypeDef *msg, uint16 size );

#endif
