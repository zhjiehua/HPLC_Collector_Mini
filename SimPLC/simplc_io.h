/*
	IN_NUM�������������ĸ�����������˳��Ϊ0~IN_NUM��10���ƣ�.
	����PLC�е�X10 X11����ʵ����X8 X9

	OUT_NUM�������������ĸ�����������˳��Ϊ0~OUT_NUM��10���ƣ�.

	IO_Refresh()��������ˢ������IO��״̬��������������������������������Ҫ��while(1)�е���

	���ĺ���_GetX(uint8_t X, uint8_t Num)���ڶ�ȡ����㣬�����˲����ܡ�

	�˲�ʱ����SHAKE_TIME*IO_FRE_DOUBLE����ʱ���ڣ�����SHAKE_TIME��ΧΪ0~31.
	���ڵ��˲�ʱ����SHAKE_TIME*IO_FRE_DOUBLE��1ms
*/

#ifndef __SIMPLC_IO_H__
#define __SIMPLC_IO_H__

#include "stdint.h"

#define SHAKE_TIME 0//32����ʱ����
#define IO_FRE_DOUBLE 0//�����õĶ�ʱ��Ƶ

#define IN_NUM 16 //�������
#define OUT_NUM 16  //�������
#define RELAY_NUM 32 //�м�̵�������

//Ԫ������
#define X_COMPONET	0
#define Y_COMPONET	1
#define M_COMPONET	2

//��ƽ����
#define LEVEL			0
#define FALLING_EDGE	1
#define RISING_EDGE		2

//IO�㶨�����
typedef struct
{
	//��ƽ
	uint8_t *X_Level;
	uint8_t *Y_Level;
	uint8_t *M_Level;

	//�½���
	uint8_t *X_FallingEdge;
	uint8_t *Y_FallingEdge;
	uint8_t *M_FallingEdge;

	//������
	uint8_t *X_RisingEdge;
	uint8_t *Y_RisingEdge;
	uint8_t *M_RisingEdge;
}IO_Man_TypeDef;

//M �����м�̵�������
#define M_POWERON         0
#define M_KEY1      			1
#define M_KEY2      			1
#define M_KEY3      			1
#define M_KEY4      			1
#define M_KEY5      			1
#define M_KEY6      			1
#define M_KEY7      			1
#define M_KEY8      			1
#define M_KEY_POWER      	1

#define M_BEEPER          17

//X
#define X_KEY1      			0
#define X_KEY2			      1
#define X_KEY3      			2
#define X_KEY4        		3
#define X_KEY5   					4
#define X_KEY6   					5
#define X_KEY7          	6
#define X_KEY8          	7
#define X_EXT          		8
//Y
#define Y_COIL1    				0
#define Y_COIL2    				1
#define Y_COIL3    				2
#define Y_COIL4    				3
#define Y_COIL5    				4
#define Y_COIL6    				5
#define Y_COIL7    				6
#define Y_COIL8    				7
#define Y_COIL_POWER    	8
#define Y_EXT          		9

extern uint8_t IN_State[IN_NUM];//������˲���
/*
	bit8 ��¼�����ƽ
	bit7 ������ʱ�Ŀ���
	bit6 ��ʱʱ�䵽��־
	bit5~0 ��ʱ��ʱ������
*/

void SIMPLC_IO_Init(void);
void SIMPLC_IO_Refresh(void);

uint8_t SIMPLC_IO_Get(uint8_t Component, uint8_t Index, uint8_t Type);
void SIMPLC_IO_Set(uint8_t Component, uint8_t Index, uint8_t Level);

#define GML(x)   SIMPLC_IO_Get(M_COMPONET, x, LEVEL)
#define GMR(x)   SIMPLC_IO_Get(M_COMPONET, x, RISING_EDGE)
#define GMF(x)   SIMPLC_IO_Get(M_COMPONET, x, FALLING_EDGE)
#define SML(x, y)   SIMPLC_IO_Set(M_COMPONET, x, y)

#define GXL(x)   SIMPLC_IO_Get(X_COMPONET, x, LEVEL)
#define GXR(x)   SIMPLC_IO_Get(X_COMPONET, x, RISING_EDGE)
#define GXF(x)   SIMPLC_IO_Get(X_COMPONET, x, FALLING_EDGE)

#define SYL(x, y)   SIMPLC_IO_Set(Y_COMPONET, x, y)
#define GYL(x)   SIMPLC_IO_Get(Y_COMPONET, x, LEVEL)

#endif
