#include "IO.h"
#include "usart.h"
#include "CPrintf.h"

#include "management.h"

void IO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
//    NVIC_InitTypeDef NVIC_InitStructure;
//    EXTI_InitTypeDef EXTI_InitStructure;
    
    cDebug("IO_Init()...\r\n");
    
	/*LED*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOA, ENABLE);	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		 //ֻ��2MHz ,��س�ʼ��IIC.c�ļ����в�������
	GPIO_Init(GPIOC, &GPIO_InitStructure);					 
	GPIO_SetBits(GPIOC, GPIO_Pin_13);						 
	
	//BEEP
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);	//�ر�

	/*�����*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PC,PA�˿�ʱ��
	//��չ���
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);					
	GPIO_ResetBits(GPIOB, GPIO_Pin_0);		
	//��ŷ�MOS��Դѡ�񿪹�
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);					
	GPIO_ResetBits(GPIOA, GPIO_Pin_8);//�͵�ƽѡ��12V��Դ
	//��ŷ�
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_8|GPIO_Pin_7|GPIO_Pin_6;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);					
	GPIO_ResetBits(GPIOC, GPIO_Pin_9|GPIO_Pin_8|GPIO_Pin_7|GPIO_Pin_6);//�ر�
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15|GPIO_Pin_14|GPIO_Pin_13|GPIO_Pin_12;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);					
	GPIO_ResetBits(GPIOB, GPIO_Pin_15|GPIO_Pin_14|GPIO_Pin_13|GPIO_Pin_12);//�ر�
	
	/*�����*/	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	//��չ����
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	//뮵Ʒ����ź�  ͹�ִ���������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
    
//    //NVIC ����
//    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;//��ռ���ȼ�3
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//�����ȼ�3
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
//    NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���

//    //�ⲿ�ж�����
//    EXTI_ClearITPendingBit(EXTI_Line11);
//    
//    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource11);

//    EXTI_InitStructure.EXTI_Line = EXTI_Line11; 
//    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt; 
//    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //EXTI_Trigger_Rising  EXTI_Trigger_Falling
//    EXTI_InitStructure.EXTI_LineCmd = ENABLE; 
//    EXTI_Init(&EXTI_InitStructure);
    
    cDebug("IO_Init()...Finish\r\n");
}

extern unsigned char W5500_Interrupt;
void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line7) != RESET)
	{
		EXTI_ClearITPendingBit(EXTI_Line7);
		W5500_Interrupt=1;
	}
}

//void EXTI15_10_IRQHandler(void)
//{
//	if(EXTI_GetITStatus(EXTI_Line11) == SET)
//	{
//        //��Ӧ��͹�֣���ʼ͹�ֲ���
//        //LED = !LED;
//		
//				//man.gearOneRotateUsedTimeCount = 0;
////        pStepMotor[0].timerCompensationCounter = 0;                
//        
////        //��͹�֣�����stepmotor.c�ж������Ҫ���õı���
////        man.gearPos = 0;
////        man.gearOneRotateStepFlag = 1;
//        
//		EXTI_ClearITPendingBit(EXTI_Line11);
//	}
//}
