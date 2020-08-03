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
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		 //只能2MHz ,相关初始化IIC.c文件里有部分作用
	GPIO_Init(GPIOC, &GPIO_InitStructure);					 
	GPIO_SetBits(GPIOC, GPIO_Pin_13);						 
	
	//BEEP
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);					 
	GPIO_ResetBits(GPIOA, GPIO_Pin_1);	//关闭

	/*输出点*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);	 //使能PC,PA端口时钟
	//扩展输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);					
	GPIO_ResetBits(GPIOB, GPIO_Pin_0);		
	//电磁阀MOS电源选择开关
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);					
	GPIO_ResetBits(GPIOA, GPIO_Pin_8);//低电平选择12V电源
	//电磁阀
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_8|GPIO_Pin_7|GPIO_Pin_6;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);					
	GPIO_ResetBits(GPIOC, GPIO_Pin_9|GPIO_Pin_8|GPIO_Pin_7|GPIO_Pin_6);//关闭
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15|GPIO_Pin_14|GPIO_Pin_13|GPIO_Pin_12;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);					
	GPIO_ResetBits(GPIOB, GPIO_Pin_15|GPIO_Pin_14|GPIO_Pin_13|GPIO_Pin_12);//关闭
	
	/*输入点*/	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	//扩展输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	//氘灯返回信号  凸轮传感器输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
    
//    //NVIC 配置
//    NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
//    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;//抢占优先级3
//    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//子优先级3
//    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
//    NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器

//    //外部中断配置
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
//        //感应到凸轮，开始凸轮补偿
//        //LED = !LED;
//		
//				//man.gearOneRotateUsedTimeCount = 0;
////        pStepMotor[0].timerCompensationCounter = 0;                
//        
////        //有凸轮，设置stepmotor.c中断里的需要设置的变量
////        man.gearPos = 0;
////        man.gearOneRotateStepFlag = 1;
//        
//		EXTI_ClearITPendingBit(EXTI_Line11);
//	}
//}
