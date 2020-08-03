#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//IIC���� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/9
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////

////IO�������ã��������50MHz
//#define SDA_IN()  {GPIOC->CRH&=0XF0FFFFFF;GPIOC->CRH|=(u32)8<<24;}
//#define SDA_OUT() {GPIOC->CRH&=0XF0FFFFFF;GPIOC->CRH|=(u32)3<<24;}

//IO�������ã������©2MHz
#define SDA_IN()  {GPIOC->CRH&=0XF0FFFFFF;GPIOC->CRH|=(u32)4<<24;}
#define SDA_OUT() {GPIOC->CRH&=0XF0FFFFFF;GPIOC->CRH|=(u32)6<<24;}

//IO��������	 
#define IIC_SCL    PCout(15) 		//SCL
#define IIC_SDA    PCout(14) 		//SDA	 
#define READ_SDA   PCin(14) 	 	//����SDA 

//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�

void IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte(u8 daddr,u8 addr);	  
#endif
















