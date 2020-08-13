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
    //IWDG_Init(IWDG_Prescaler_128, 625);    //���Ƶ��Ϊ128,����ֵΪ625,���ʱ��Ϊ2s
    IWDG_Feed();
  
    memset(&man, 0, sizeof(man));
    
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
    
    cDebug("Hello HPLC Pump!\r\n");
    
    queue_init(&comQueue, comQueueBuffer, COM_QUEUE_MAX_SIZE);

		//��Щ������Ҫ��ӳ�䣬PB3,PB4,PA15
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE); //DDC112��
		
#if FLOW_TEST    
    TIM2_Int_Init(9999, 7199); //10KHzʱ�ӣ���ʱ1S
    //TIM5_Int_Init(7199, 0);
#endif

    Key_Init(); //������ʼ��

    AT24CXX_Init();
    cDebug("AT24CXX_Check()...\r\n");
    count = 0;
    while(AT24CXX_Check() && count++ < 10)
    {
        cDebug("EEPROM is error!\r\n");
        delay_ms(500);
				
        IWDG_Feed();
    }    
    if(count >= 10) //����
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
 
    //�����ڼ��
    UsefulDaysCheck();
    
    IO_Init();
		SIMPLC_IO_Init();
		
    TIM2_Int_Init(499, 7199); //10KHzʱ�ӣ���ʱ50ms������ѹ����

    if(man.comType == 0)
		{
				if(man.protocol == 0)//ܫ��
					ComUart_Init(115200);
				else //Ĭ��ܫ��Э��
					ComUart_Init(115200);
		}
    else
		{
        ComLan_Init();
		}

    IWDG_Feed();
    
    cDebug("System Init...Finish\r\n");
    
		SML(M_POWERON, 1);
		SYL(Y_COIL_POWER, 0);//�͵�ƽѡ��12V��Դ
		
		SetCoilMutual(Y_COIL8);//Ĭ�ϴ򿪵ڰ˸���ŷ�
		
	while(1)
	{
      IWDG_Feed();
      
			size = man.ProtocolComQueue_FindCmd(comCmdBufferAscii, comCmdBufferHex, COM_CMD_MAX_SIZE, &comQueue);     //�ӻ������л�ȡһ��ָ��         
      if(size > 0)  //���յ�ָ�� 
      {                                                                           
        man.ProtocolComProcessFrame((void*)comCmdBufferHex, size);                    //ָ��� 
      }

			//ˢ��IO��
			SIMPLC_IO_Refresh();
				
        //����ѭ������
        if(man.comType == 1)
            ComLan_Loop();

				//�û��߼�
				ProjectRunning();
				
				
        if(man.collectorPowerOnTotalSecond%1800 == 0)//��Сʱ����һ������
        {
            //�����豸����ʱ��
            AT24CXX_Write(EEPROM_ADDR_DEVICETOTALUSEDTIME, (uint8_t*)&man.deviceTotalUsedTime, 4);
        }
        
        //������
        if(man.isTickSend)
        {
            man.isTickSend = 0;
					
						if(man.protocol == 0)
							Com_SetTick();
            
            //cDebug("TIM1 pre = %d\r\n", TIM_GetPrescaler(TIM1));
            //cDebug("%d - %d\r\n", stepMotor[0].currentPrescalerFactor, stepMotor[0].currentTimerCounterValue);
        }
        if(man.tickLostCnt >= 3)//ͨ�Ŷ�
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

