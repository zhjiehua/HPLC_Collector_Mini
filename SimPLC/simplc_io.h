/*
	IN_NUM用于配置输入点的个数，输入点的顺序为0~IN_NUM（10进制）.
	对于PLC中的X10 X11等其实就是X8 X9

	OUT_NUM用于配置输出点的个数，输出点的顺序为0~OUT_NUM（10进制）.

	IO_Refresh()函数用于刷新所有IO的状态，包括所有输入输出。所以这个函数需要在while(1)中调用

	核心函数_GetX(uint8_t X, uint8_t Num)用于读取输入点，包括滤波功能。

	滤波时间是SHAKE_TIME*IO_FRE_DOUBLE个定时周期，其中SHAKE_TIME范围为0~31.
	现在的滤波时间是SHAKE_TIME*IO_FRE_DOUBLE个1ms
*/

#ifndef __SIMPLC_IO_H__
#define __SIMPLC_IO_H__

#include "stdint.h"

#define SHAKE_TIME 0//32个定时周期
#define IO_FRE_DOUBLE 0//消抖用的定时倍频

#define IN_NUM 16 //输入点数
#define OUT_NUM 16  //输出点数
#define RELAY_NUM 32 //中间继电器个数

//元件类型
#define X_COMPONET	0
#define Y_COMPONET	1
#define M_COMPONET	2

//电平类型
#define LEVEL			0
#define FALLING_EDGE	1
#define RISING_EDGE		2

//IO点定义管理
typedef struct
{
	//电平
	uint8_t *X_Level;
	uint8_t *Y_Level;
	uint8_t *M_Level;

	//下降沿
	uint8_t *X_FallingEdge;
	uint8_t *Y_FallingEdge;
	uint8_t *M_FallingEdge;

	//上升沿
	uint8_t *X_RisingEdge;
	uint8_t *Y_RisingEdge;
	uint8_t *M_RisingEdge;
}IO_Man_TypeDef;

//M 定义中间继电器功能
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

extern uint8_t IN_State[IN_NUM];//输入点滤波用
/*
	bit8 记录输入电平
	bit7 开启延时的开关
	bit6 延时时间到标志
	bit5~0 延时定时周期数
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
