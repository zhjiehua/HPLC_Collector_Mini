#include "Key.h"
#include "usart.h"
#include "CPrintf.h"

#include "management.h"

#define USE_UART_NOKEY	0  //1表示使用调试串口，不使用按键的ENTER和RUNSTOP

Key_Pin_TypeDef KeyPin[8] = 
{
	{GPIOC, GPIO_Pin_12},
	{GPIOC, GPIO_Pin_11},
	{GPIOC, GPIO_Pin_10},
	{GPIOA, GPIO_Pin_15},
	{GPIOD, GPIO_Pin_2},
	{GPIOB, GPIO_Pin_3},
	{GPIOB, GPIO_Pin_4},
	{GPIOB, GPIO_Pin_6},
};


void Key_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  cDebug("Key_Init()...\r\n");
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD, ENABLE);	

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_6;				 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //上拉输入		 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		 //只能2MHz ,相关初始化IIC.c文件里有部分作用
  GPIO_Init(GPIOB, &GPIO_InitStructure);					 
  GPIO_ResetBits(GPIOB, GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_6);						 

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //上拉输入		 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);					 
  GPIO_SetBits(GPIOD, GPIO_Pin_2);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_11|GPIO_Pin_10;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //上拉输入		 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);					 
  GPIO_SetBits(GPIOC, GPIO_Pin_12|GPIO_Pin_11|GPIO_Pin_10);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //上拉输入		 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);					 
  GPIO_SetBits(GPIOA, GPIO_Pin_15);

  cDebug("Key_Init()...Finish\r\n");
}
