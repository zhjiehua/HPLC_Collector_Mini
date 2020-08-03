#include "Key.h"
#include "usart.h"
#include "CPrintf.h"

#include "management.h"

#define USE_UART_NOKEY	0  //1��ʾʹ�õ��Դ��ڣ���ʹ�ð�����ENTER��RUNSTOP

void Key_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  cDebug("Key_Init()...\r\n");
	
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD, ENABLE);	

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_6;				 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //��������		 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		 //ֻ��2MHz ,��س�ʼ��IIC.c�ļ����в�������
  GPIO_Init(GPIOB, &GPIO_InitStructure);					 
  GPIO_ResetBits(GPIOB, GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_6);						 

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //��������		 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOD, &GPIO_InitStructure);					 
  GPIO_SetBits(GPIOD, GPIO_Pin_2);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_11|GPIO_Pin_10;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //��������		 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);					 
  GPIO_SetBits(GPIOC, GPIO_Pin_12|GPIO_Pin_11|GPIO_Pin_10);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //��������		 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);					 
  GPIO_SetBits(GPIOA, GPIO_Pin_15);

  cDebug("Key_Init()...Finish\r\n");
}
