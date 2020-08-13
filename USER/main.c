#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "timer.h"
#include "ComProcess.h"
#include "ComUart.h"
#include "ComLan.h"
#include "management.h"
#include "miscellaneous.h"
#include "CPrintf.h"
#include "math.h"
#include "IO.h"
#include "24cxx.h"
#include "wdg.h"
#include "Key.h"
#include "simplc_io.h"
#include "Project.h"

int main(void)
{
    qsize size = 0;
    uint32_t count = 0;
  
    SCB->VTOR = FLASH_BASE | 0x3000; /* Vector Table Relocation in Internal FLASH. */
    //IWDG_Init(IWDG_Prescaler_128, 625);    //与分频数为128,重载值为625,溢出时间为2s
    IWDG_Feed();
  
    memset(&man, 0, sizeof(man));
    
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 //串口初始化为115200
    
    cDebug("Hello HPLC Pump!\r\n");
    
    queue_init(&comQueue, comQueueBuffer, COM_QUEUE_MAX_SIZE);

		//有些引脚需要重映射，PB3,PB4,PA15
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); //DDC112用
		
#if FLOW_TEST    
    TIM2_Int_Init(9999, 7199); //10KHz时钟，定时1S
    //TIM5_Int_Init(7199, 0);
#endif

    Key_Init(); //按键初始化

    AT24CXX_Init();
    cDebug("AT24CXX_Check()...\r\n");
    count = 0;
    while(AT24CXX_Check() && count++ < 10)
    {
        cDebug("EEPROM is error!\r\n");
        delay_ms(500);
				
        IWDG_Feed();
    }    
    if(count >= 10) //报警
    {
        while(1)
        {

								BEEP = 1;
								delay_ms(500);
								BEEP = 0;
								delay_ms(500);
					
            cDebug("EEPROM is error!\r\n");
          
            IWDG_Feed();
        }
    }
    cDebug("AT24CXX_Check()...Finish\r\n");
    
    InitMan();
 
    //试用期检查
    UsefulDaysCheck();
    
    IO_Init();
		SIMPLC_IO_Init();
		
    TIM2_Int_Init(499, 7199); //10KHz时钟，定时50ms，更新压力用

    if(man.comType == 0)
		{
				if(man.protocol == 0)//塬锐
					ComUart_Init(115200);
				else //默认塬锐协议
					ComUart_Init(115200);
		}
    else
		{
        ComLan_Init();
		}

    IWDG_Feed();
    
    cDebug("System Init...Finish\r\n");
    
		SML(M_POWERON, 1);
		SYL(Y_COIL_POWER, 0);//低电平选择12V电源
		
		SetCoilMutual(Y_COIL8);//默认打开第八个电磁阀
		
	while(1)
	{
      IWDG_Feed();
      
			size = man.ProtocolComQueue_FindCmd(comCmdBufferAscii, comCmdBufferHex, COM_CMD_MAX_SIZE, &comQueue);     //从缓冲区中获取一条指令         
      if(size > 0)  //接收到指令 
      {                                                                           
        man.ProtocolComProcessFrame((void*)comCmdBufferHex, size);                    //指令处理 
      }

			//刷新IO点
			SIMPLC_IO_Refresh();
				
        //网口循环函数
        if(man.comType == 1)
            ComLan_Loop();

				//用户逻辑
				ProjectRunning();
				
				
        if(man.collectorPowerOnTotalSecond%1800 == 0)//半小时保存一次数据
        {
            //保存设备运行时间
            AT24CXX_Write(EEPROM_ADDR_DEVICETOTALUSEDTIME, (uint8_t*)&man.deviceTotalUsedTime, 4);
        }
        
        //心跳包
        if(man.isTickSend)
        {
            man.isTickSend = 0;
					
						if(man.protocol == 0)
							Com_SetTick();
            
            //cDebug("TIM1 pre = %d\r\n", TIM_GetPrescaler(TIM1));
            //cDebug("%d - %d\r\n", stepMotor[0].currentPrescalerFactor, stepMotor[0].currentTimerCounterValue);
        }
        if(man.tickLostCnt >= 3)//通信断
        {
            if(man.isConnect)
            {
                cDebug("Disconnect!\r\n");
            }
            man.isConnect = 0;               
        }

        {
            static uint32_t cnt = 0;
            if(cnt++ > 10000)
            {
                cnt = 0;
                LED = !LED;
            }
        }
	}
}

