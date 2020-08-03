#include "simplc_io.h"
#include "io.h"
#include "Key.h"

uint8_t IN_State[IN_NUM];//������˲���
/*
	bit8 ��¼�����ƽ
	bit7 ������ʱ�Ŀ���
	bit6 ��ʱʱ�䵽��־
	bit5~0 ��ʱ��ʱ������
*/
static uint8_t IN_Last[(IN_NUM+7)/8];//�������һ״̬
static uint8_t IN[(IN_NUM+7)/8];//�����
static uint8_t IN_Rising[(IN_NUM+7)/8];//�����������
static uint8_t IN_Falling[(IN_NUM+7)/8];//������½���

static uint8_t OUT_Last[(OUT_NUM+7)/8];//�������һ״̬
static uint8_t OUT[(OUT_NUM+7)/8];//�����
static uint8_t OUT_Rising[(OUT_NUM+7)/8];//�����������
static uint8_t OUT_Falling[(OUT_NUM+7)/8];//������½���

static uint8_t RELAY_Last[(RELAY_NUM+7)/8];//�м�̵�����һ״̬
static uint8_t RELAY[(RELAY_NUM+7)/8];//�м�̵���
static uint8_t RELAY_Rising[(RELAY_NUM+7)/8];//�м�̵���������
static uint8_t RELAY_Falling[(RELAY_NUM+7)/8];//�м�̵����½���

//IO����ṹ��
IO_Man_TypeDef IO_Man;

//IO��ʼ��
void SIMPLC_IO_Init(void)
{
    uint8_t i;

    IO_Init();
    
    for(i=0;i<(IN_NUM+7)/8;i++)
    {
        IN_Last[i] = 0;
        IN[i] = 0;
        IN_Rising[i] = 0;
        IN_Falling[i] = 0;
    }
    for(i=0;i<(OUT_NUM+7)/8;i++)
    {
        OUT_Last[i] = 0;
        OUT[i] = 0;
        OUT_Rising[i] = 0;
        OUT_Falling[i] = 0;
    }
    for(i=0;i<(RELAY_NUM+7)/8;i++)
    {
        RELAY_Last[i] = 0;
        RELAY[i] = 0;
        RELAY_Rising[i] = 0;
        RELAY_Falling[i] = 0;
    }

	IO_Man.X_Level = IN;
	IO_Man.Y_Level = OUT;
	IO_Man.M_Level = RELAY;
	
	IO_Man.X_FallingEdge = IN_Falling;
	IO_Man.Y_FallingEdge = OUT_Falling;
	IO_Man.M_FallingEdge = RELAY_Falling;
	
	IO_Man.X_RisingEdge = IN_Rising;
	IO_Man.Y_RisingEdge = OUT_Rising;
	IO_Man.M_RisingEdge = RELAY_Rising;
}

//��ȡ����㣬����������
//static void _GetX(bit X, uint8_t Num)
//{
//	uint8_t cIndex = Num / 8;
//	uint8_t rIndex = Num % 8;
//
//	if(!X != (IN_State[Num]>>7) & 0x01)
//	{
//		//��¼�����ƽ��������ʱ
//		if(!X)
//			IN_State[Num] = 0x80|0x40;
//		else
//			IN_State[Num] = 0x40;
//	}
//	if(IN_State[Num] & 0x20)//��ʱʱ�䵽
//	{
//		IN_State[Num] &= ~0x20;
//		if(!X == (IN_State[Num]>>7) & 0x01)//�������֮ǰ�ĵ�ƽ����ʾ�������Ч
//		{
//			//IN_Last[cIndex] = IN[cIndex];//��¼��һ��״̬����Ҫ��ɨ��ǰ����
//			if(!X)
//				IN[cIndex] |= 0x01<<rIndex;
//			else
//				IN[cIndex] &= ~(0x01<<rIndex);
//		}
//	}
//}

//#define _GetX(X, Num) do{\
//	uint8_t cIndex = Num / 8;\
//	uint8_t rIndex = Num % 8;\
//	if(!X)\
//		IN[cIndex] |= 0x01<<rIndex;\
//	else\
//		IN[cIndex] &= ~(0x01<<rIndex);\
//}while(0)

#define _GetX(X, Num) do{\
	if(!X)\
		IN[Num/8] |= 0x01<<(Num%8);\
	else\
		IN[Num/8] &= ~(0x01<<(Num%8));\
}while(0)

//ˢ��IO��
void SIMPLC_IO_Refresh(void)
{
	uint8_t i;	
/*----------------------------�����---------------------------------*/
	//��¼�������һ״̬
	for(i=0;i<(IN_NUM+7)/8;i++)
		IN_Last[i] = IN[i];

	//��ȡ�����
	_GetX(!KEY1, X_KEY1);
	_GetX(!KEY2, X_KEY2);
	_GetX(!KEY3, X_KEY3);
	_GetX(!KEY4, X_KEY4);
	_GetX(!KEY5, X_KEY5);
	_GetX(!KEY6, X_KEY6);
	_GetX(!KEY7, X_KEY7);
	_GetX(!KEY8, X_KEY8);
	_GetX(!MI_EXT, X_EXT);
	
	for(i=0;i<(IN_NUM+7)/8;i++)
	{
		IN_Rising[i] = (IN_Last[i]^IN[i]) & IN[i];
		IN_Falling[i] = (IN_Last[i]^IN[i]) & IN_Last[i];
	}
    
/*----------------------------�����--------------------------------------*/
	//�����ˢ��
	  MO_COIL1 = !!(GYL(Y_COIL1));
    MO_COIL2 = !!(GYL(Y_COIL2));
    MO_COIL3 = !!(GYL(Y_COIL3));
    MO_COIL4 = !!(GYL(Y_COIL4));
		MO_COIL5 = !!(GYL(Y_COIL5));
    MO_COIL6 = !!(GYL(Y_COIL6));
    MO_COIL7 = !!(GYL(Y_COIL7));
    MO_COIL8 = !!(GYL(Y_COIL8));
		MO_COIL_POWER = !!(GYL(Y_COIL_POWER));
		MO_EXT = !!(GYL(Y_EXT));
	
//    MO_COIL1 = !!(OUT[0]&0x01);
//    MO_COIL2 = !!(OUT[0]&0x02);
//    MO_COIL3 = !!(OUT[0]&0x04);
//    MO_COIL4 = !!(OUT[0]&0x08);
//		MO_COIL5 = !!(OUT[0]&0x10);
//    MO_COIL6 = !!(OUT[0]&0x20);
//    MO_COIL7 = !!(OUT[0]&0x40);
//    MO_COIL8 = !!(OUT[0]&0x80);
//		MO_COIL_POWER = !!(OUT[1]&0x01);
//		MO_EXT = !!(OUT[1]&0x02);
	
	for(i=0;i<(OUT_NUM+7)/8;i++)
	{
		OUT_Rising[i] = (OUT_Last[i]^OUT[i]) & OUT[i];
		OUT_Falling[i] = (OUT_Last[i]^OUT[i]) & OUT_Last[i];
		OUT_Last[i] = OUT[i];
	}

/*----------------------------�м�̵���----------------------------------*/
	for(i=0;i<(RELAY_NUM+7)/8;i++)
	{
		RELAY_Rising[i] = (RELAY_Last[i]^RELAY[i]) & RELAY[i];
		RELAY_Falling[i] = (RELAY_Last[i]^RELAY[i]) & RELAY_Last[i];
		RELAY_Last[i] = RELAY[i];
	}
}

//----------------------------IO_API-------------------------------
//��IO
//Componet Ԫ�����ͣ���ȡX_COMPONET Y_COMPONET M_COMPONET
//Index Ԫ����� 
//Type ��ƽ���ͣ���ȡLEVEL FALLING_EDGE RISING_EDGE
uint8_t SIMPLC_IO_Get(uint8_t Component, uint8_t Index, uint8_t Type)
{
	uint8_t **p = &IO_Man.X_Level;
	return (uint8_t)((*(p + Component + 3*Type))[Index/8]>>(Index%8) & 0x01);
}

//дIO
void SIMPLC_IO_Set(uint8_t Component, uint8_t Index, uint8_t Level)
{
	uint8_t **p = &IO_Man.X_Level;
	if(Level)
		(*(p + Component))[Index/8] |= (0x01<<(Index%8));
	else
		(*(p + Component))[Index/8] &= ~(0x01<<(Index%8));
}