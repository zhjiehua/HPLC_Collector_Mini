#ifndef __KEY_H
#define __KEY_H

#include "sys.h"

//按键引脚定义
#define KEY1 		PCin(12)
#define KEY2   	PCin(11)
#define KEY3   	PCin(10)
#define KEY4 		PAin(15)
#define KEY5   	PDin(2)
#define KEY6   	PBin(3)
#define KEY7   	PBin(4)
#define KEY8	  PBin(6)

typedef struct
{
	GPIO_TypeDef *port;
	uint16_t pin;
}Key_Pin_TypeDef;

void Key_Init(void);

extern Key_Pin_TypeDef KeyPin[];

#endif
