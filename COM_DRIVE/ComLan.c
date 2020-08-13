#include "management.h"
#include "ComLAN.h"
#include <string.h>
#include "ComQueue.h"

#include "CPrintf.h"

/*******************************************************************************
* ������  : Load_Net_Parameters
* ����    : װ���������
* ����    : ��
* ���    : ��
* ����ֵ  : ��
* ˵��    : ���ء����롢�����ַ������IP��ַ���˿ںš�Ŀ��IP��ַ��Ŀ�Ķ˿ںš��˿ڹ���ģʽ
*******************************************************************************/
void Load_Net_Parameters(void)
{
	Gateway_IP[0] = man.localIP[0];//�������ز���
	Gateway_IP[1] = man.localIP[1];
	Gateway_IP[2] = man.localIP[2];
	Gateway_IP[3] = 1;

	Sub_Mask[0]=255;//������������
	Sub_Mask[1]=255;
	Sub_Mask[2]=255;
	Sub_Mask[3]=0;

    {
        uint32_t mac = man.chipID[0]^man.chipID[1]^man.chipID[2];
        Phy_Addr[0]=(uint8_t)((mac&0x000000FF)>>0);//���������ַ
        Phy_Addr[1]=(uint8_t)((mac&0x0000FF00)>>8);
        Phy_Addr[2]=(uint8_t)((mac&0x00FF0000)>>16);
        Phy_Addr[3]=(uint8_t)((mac&0xFF000000)>>24);
        Phy_Addr[4]=0x00;
        Phy_Addr[5]=0x02;
        
        cDebug("MAC Address:%02X %02X %02X %02X %02X %02X\r\n", 
            Phy_Addr[0], Phy_Addr[1], Phy_Addr[2], Phy_Addr[3], Phy_Addr[4], Phy_Addr[5]);
    }
    //	Phy_Addr[0]=0x0c;//���������ַ
    //	Phy_Addr[1]=0x29;
    //	Phy_Addr[2]=0xab;
    //	Phy_Addr[3]=0x7c;
    //	Phy_Addr[4]=0x00;
    //	Phy_Addr[5]=0x01;

	IP_Addr[0]=man.localIP[0];//���ر���IP��ַ
	IP_Addr[1]=man.localIP[1];
	IP_Addr[2]=man.localIP[2];
	IP_Addr[3]=man.localIP[3];

	S0_Port[0] = (uint8_t)((man.localPort&0xFF00)>>8);//��λ��ǰ
	S0_Port[1] = (uint8_t)((man.localPort&0x00FF)>>0);

    
    //S0_Mode=UDP_MODE;//���ض˿�0�Ĺ���ģʽ,UDPģʽ
    //S0_Mode=TCP_SERVER;//���ض˿�0�Ĺ���ģʽ,TCP������ģʽ
    //S0_Mode=TCP_CLIENT;//���ض˿�0�Ĺ���ģʽ,TCP�ͻ���ģʽ
 
//    if(man.comType == 1 && man.mode == 6)//���� MASTERģʽ
//    {
//        S0_Mode=TCP_CLIENT;//����
//        cDebug("W5500 mode is TCP_CLIENT\r\n");
//    }
//    else
    {
        S0_Mode=TCP_SERVER;
        cDebug("W5500 mode is TCP_SERVER\r\n");
    }
    
    
    if(S0_Mode == TCP_CLIENT)
    {
        S0_DIP[0]=man.remoteIP[0];//���ض˿�0��Ŀ��IP��ַ
        S0_DIP[1]=man.remoteIP[1];
        S0_DIP[2]=man.remoteIP[2];
        S0_DIP[3]=man.remoteIP[3];
        
        S0_DPort[0] = (uint8_t)((man.remotePort&0xFF00)>>8);//��λ��ǰ
        S0_DPort[1] = (uint8_t)((man.remotePort&0x00FF)>>0);
    }



    //	S0_DIP[0]=192;//���ض˿�0��Ŀ��IP��ַ
    //	S0_DIP[1]=168;
    //	S0_DIP[2]=1;
    //	S0_DIP[3]=190;
    //	
    //	S0_DPort[0] = 0x17;//���ض˿�0��Ŀ�Ķ˿ں�6000
    //	S0_DPort[1] = 0x70;

    UDP_DIPR[0] = man.remoteIP[0];	//UDP(�㲥)ģʽ,Ŀ������IP��ַ
	UDP_DIPR[1] = man.remoteIP[1];
	UDP_DIPR[2] = man.remoteIP[2];
	UDP_DIPR[3] = man.remoteIP[3];

	UDP_DPORT[0] = (uint8_t)((man.remotePort&0xFF00)>>8);	//UDP(�㲥)ģʽ,Ŀ�������˿ں�
	UDP_DPORT[1] = (uint8_t)((man.remotePort&0x00FF)>>0);


    //	UDP_DIPR[0] = 192;	//UDP(�㲥)ģʽ,Ŀ������IP��ַ
    //	UDP_DIPR[1] = 168;
    //	UDP_DIPR[2] = 1;
    //	UDP_DIPR[3] = 190;
    //
    //	UDP_DPORT[0] = 0x17;	//UDP(�㲥)ģʽ,Ŀ�������˿ں�
    //	UDP_DPORT[1] = 0x70;

	
}

/*******************************************************************************
* ������  : W5500_Socket_Set
* ����    : W5500�˿ڳ�ʼ������
* ����    : ��
* ���    : ��
* ����ֵ  : ��
* ˵��    : �ֱ�����4���˿�,���ݶ˿ڹ���ģʽ,���˿�����TCP��������TCP�ͻ��˻�UDPģʽ.
*			�Ӷ˿�״̬�ֽ�Socket_State�����ж϶˿ڵĹ������
*******************************************************************************/
void W5500_Socket_Set(void)
{
	if(S0_State==0)//�˿�0��ʼ������
	{
		if(S0_Mode==TCP_SERVER)//TCP������ģʽ 
		{
			if(Socket_Listen(0)==TRUE)
				S0_State=S_INIT;
			else
				S0_State=0;
		}
		else if(S0_Mode==TCP_CLIENT)//TCP�ͻ���ģʽ 
		{
			if(Socket_Connect(0)==TRUE)
				S0_State=S_INIT;
			else
				S0_State=0;
		}
		else//UDPģʽ 
		{
			if(Socket_UDP(0)==TRUE)
				S0_State=S_INIT|S_CONN;
			else
				S0_State=0;
		}
	}
}

/*******************************************************************************
* ������  : Process_Socket_Data
* ����    : W5500���ղ����ͽ��յ�������
* ����    : s:�˿ں�
* ���    : ��
* ����ֵ  : ��
* ˵��    : �������ȵ���S_rx_process()��W5500�Ķ˿ڽ������ݻ�������ȡ����,
*			Ȼ�󽫶�ȡ�����ݴ�Rx_Buffer������Temp_Buffer���������д���
*			������ϣ������ݴ�Temp_Buffer������Tx_Buffer������������S_tx_process()
*			�������ݡ�
*******************************************************************************/
void Process_Socket_Data(SOCKET s)
{
	unsigned short size, i;
	size=Read_SOCK_Data_Buffer(s, Rx_Buffer);
    
    if(S0_Mode==UDP_MODE)
    {
        UDP_DIPR[0] = Rx_Buffer[0];
        UDP_DIPR[1] = Rx_Buffer[1];
        UDP_DIPR[2] = Rx_Buffer[2];
        UDP_DIPR[3] = Rx_Buffer[3];

        UDP_DPORT[0] = Rx_Buffer[4];
        UDP_DPORT[1] = Rx_Buffer[5];
        
        //cDebug("remoteIP is %d.%d.%d.%d:%d\r\n", UDP_DIPR[0], UDP_DIPR[1], UDP_DIPR[2], UDP_DIPR[3], UDP_DPORT[0]*256+UDP_DPORT[1]);
        
        size -= 8;
        
    //	memcpy(Tx_Buffer, Rx_Buffer+8, size);			
    //	Write_SOCK_Data_Buffer(s, Tx_Buffer, size);
        for(i=0;i<size;i++)
            queue_push(&comQueue, Rx_Buffer[8+i]);
    }
    else
    {
        for(i=0;i<size;i++)
            queue_push(&comQueue, Rx_Buffer[i]);
    }
}

/*******************************************************************************
* ������  : ComLAN_Init
* ����    : W5500��ʼ������
* ����    : ��
* ���    : ��
* ����ֵ  : ��
* ˵��    : ��
*******************************************************************************/
void ComLan_Init(void)
{
    cDebug("ComLan_Init()...\r\n");
    
    SPI_Configuration();		//W5500 SPI��ʼ������(STM32 SPI2)
	W5500_GPIO_Configuration();	//W5500 GPIO��ʼ������

    Load_Net_Parameters();		//װ���������
	W5500_Hardware_Reset();		//Ӳ����λW5500
    
    W5500_Init();		//��ʼ��W5500�Ĵ�������
    if(Detect_Gateway() == FALSE)	//������ط����� 
        cDebug("Detect_Gateway Error!\r\n");
    Socket_Init(0);		//ָ��Socket(0~7)��ʼ��,��ʼ���˿�0

    cDebug("ComLan_Init()...Finish\r\n");
}

void ComLan_Loop(void)
{
    W5500_Socket_Set();//W5500�˿ڳ�ʼ������

    //if(W5500_Interrupt)//����W5500�ж�
		if(GPIO_ReadInputDataBit(W5500_INT_PORT, W5500_INT) == Bit_RESET)
    {
        W5500_Interrupt_Process();//W5500�жϴ��������
    }
    if((S0_Data & S_RECEIVE) == S_RECEIVE)//���Socket0���յ�����
    {
        S0_Data&=~S_RECEIVE;
        Process_Socket_Data(0);//W5500���ղ����ͽ��յ�������
    }
}

