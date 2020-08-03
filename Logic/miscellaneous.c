#include "miscellaneous.h"
#include "management.h"
#include "string.h"
#include "io.h"
#include "24cxx.h"
#include "CPrintf.h"
#include "ComProcess.h"
#include "wdg.h"

#include "ComLAN.h"

/*! 
*  \brief  检查数据是否符合CRC16校验
*  \param buffer 待校验的数据
*  \param n 数据长度，包含CRC16
*  \param pcrc 校验码
*/
void AddCRC16(uint8_t *buffer,uint16_t n,uint16_t *pcrc)
{
    uint16_t i,j,carry_flag,a;

    for (i=0; i<n; i++)
    {
        *pcrc=*pcrc^buffer[i];
        for (j=0; j<8; j++)
        {
            a=*pcrc;
            carry_flag=a&0x0001;
            *pcrc=*pcrc>>1;
            if (carry_flag==1)
                *pcrc=*pcrc^0xa001;
        }
    }
}
/*! 
*  \brief  检查数据是否符合CRC16校验
*  \param buffer 待校验的数据，末尾存储CRC16
*  \param n 数据长度，包含CRC16
*  \return 校验通过返回1，否则返回0
*/
uint16_t CheckCRC16(uint8_t *buffer,uint16_t n)
{
    uint16_t crc0 = 0x0;
    uint16_t crc1 = 0xffff;

    if(n>=2)
    {
        crc0 = ((buffer[n-2]<<8)|buffer[n-1]);
        AddCRC16(buffer,n-2,&crc1);
    }

    return (crc0==crc1);
}

//len为HEX缓冲区长度，ASCII缓冲区长度为2*len+1，最后需要一个字符串结束符
void Hex2Ascii(uint8_t *outBuffer, uint8_t *inBuffer, uint8_t len)
{
	uint8_t i, temp;
	for(i=0;i<len;i++)
	{
		temp = (inBuffer[i]&0xF0)>>4;
		if(temp < 0x0A)
			outBuffer[2*i] = temp + 0x30;
		else
			outBuffer[2*i] = temp - 0x0A + 0x41;
		
		temp = inBuffer[i]&0x0F;
		if(temp < 0x0A)
			outBuffer[2*i+1] = temp + 0x30;
		else
			outBuffer[2*i+1] = temp - 0x0A + 0x41;
	}
	outBuffer[2*i] = '\0';
}

//长度len为HEX缓冲区的长度，也是ASCII缓冲区长度/2
void Ascii2Hex(uint8_t *outBuffer, uint8_t *inBuffer, uint8_t len)
{
	uint8_t i, temp;
	for(i=0;i<len;i++)
	{
		temp = inBuffer[2*i];
		if(temp < 0x40)
			outBuffer[i] = (temp-0x30)<<4;
		else
			outBuffer[i] = (temp-0x41+0x0A)<<4;
		
		temp = inBuffer[2*i+1];
		if(temp < 0x40)
			outBuffer[i] |= (temp-0x30)&0x0F;
		else
			outBuffer[i] |= (temp-0x41+0x0A)&0x0F;
    
//    //下面的有问题，对有些输入，输出不对
//    temp = inBuffer[2*i+1];
//		if(temp < 0x40)
//			outBuffer[i] |= (temp-0x30);
//		else
//			outBuffer[i] |= (temp-0x41+0x0A);
	}
}

//BCD码转10进制,len表示BCD码的长度
uint8_t BCD2Int(uint32_t *outNum, uint8_t *inBuffer, uint8_t len)
{
  uint8_t i;
  uint32_t temp = 0;
	for(i=0;i<len;i++)
	{
		temp *= 10;
		if(inBuffer[i] >= '0' && inBuffer[i] <= '9')
			temp += (inBuffer[i] - '0');
		else
			return 1;
  }
  *outNum = temp;  
  return 0;
}

//Int转BCD码,len表示BCD码的长度
void Int2BCD(uint8_t *outBuffer, uint32_t inNum, uint8_t len)
{
	uint8_t i, temp;
	for (i = 0; i < len; i++)
	{
		temp = inNum%10;
		outBuffer[len-1-i] = temp+0x30;
		inNum /= 10;
	}
}

//清博华的BCD码转10进制，len表示BCD码的长度，一个BCD码如果不够6位，则前面为空格（0x20）
uint8_t QBH_BCD2Int(uint32_t* outNum, uint8_t* inBuffer, uint8_t len)
{
	uint8_t i, flag = 0;
	uint32_t temp = 0;
	for (i = 0;i < len;i++)
	{	
		if (flag == 0)
		{
			if (inBuffer[i] == 0x20)
				continue;
			else if (inBuffer[i] >= '0' && inBuffer[i] <= '9')
				flag = 1;
			else
				return 1;
		}

		temp *= 10;
		if (inBuffer[i] >= '0' && inBuffer[i] <= '9')
			temp += (inBuffer[i] - '0');
		else
			return 1;
	}
	*outNum = temp;
	return 0;
}

//清博华的Int转BCD码,len表示BCD码的长度，如果一个int转成BCD码后不够6位，则前面补空格（0x20）
void QBH_Int2BCD(uint8_t* outBuffer, uint32_t inNum, uint8_t len)
{
	uint8_t i, temp;
	for (i = 0; i < len; i++)
	{
		if (inNum > 0)
		{
			temp = inNum % 10;
			outBuffer[len - 1 - i] = temp + 0x30;
			inNum /= 10;
		}
		else
			outBuffer[len - 1 - i] = 0x20;//前面补空格
	}
}


void Sort(uint32_t *pBuffer, uint8_t count)
{
	uint8_t i, j;
	uint32_t temp;
	for(i=0;i<count-1;i++)
	{
		for(j=i+1;j<count;j++)
		{
			if(pBuffer[i] > pBuffer[j])
			{
				temp = pBuffer[j];
				pBuffer[j] = pBuffer[i];
				pBuffer[i] = temp;
			}
		}
	}
}

uint32_t GetAverage(uint32_t *pBuffer, uint8_t count, uint8_t discardCount)
{
	uint8_t i;
	uint32_t average = 0;

	for(i=discardCount;i<(count-discardCount);i++)
		average += pBuffer[i];

	average /= (count-2*discardCount);
	return average;
}

uint32_t GetWeightedAverage(uint32_t *pBuffer, uint8_t len, uint8_t discardCount)
{
	uint64_t average = 0;
	uint16_t averageCnt = 0;
    uint8_t startIndex = discardCount;
	//uint8_t startIndex = len/4;
	//uint8_t startIndex = 0;
    uint8_t i, j;
    uint32_t temp;

	//排序
	for(i = 0; i < len-1; i++)
	{
		for(j = i+1; j < len; j++)
		{
			if(pBuffer[i] < pBuffer[j])
			{
				temp = pBuffer[i];
				pBuffer[i] = pBuffer[j];
				pBuffer[j] = temp;
			}
		}
	}

	//加权平均
	for(i = startIndex; i < len - startIndex; i++)
	{
		if(i <= len/2)
		{
			average += pBuffer[i]*(i - startIndex + 1);
			averageCnt += (i - startIndex + 1);
		}
		else
		{
			average += pBuffer[i]*(len - startIndex - i);
			averageCnt += (len - startIndex - i);
		}
	}
	average /= averageCnt;

	return (uint32_t)average;
}

uint32_t OrderFilter(uint32_t *pData, uint8_t len, uint8_t order)
{
	uint64_t average = 0;
	uint16_t averageCnt = 0;
    uint8_t i;
	for(i=0;i<len;i++)
	{
		average += (pData[i] * (i + 1));
		averageCnt += (i + 1);
	}
	average /= averageCnt;
	return (uint32_t)average;
}

void SortFloat(float *pBuffer, uint8_t count)
{
	uint8_t i, j;
	float temp;
	for(i=0;i<count-1;i++)
	{
		for(j=i+1;j<count;j++)
		{
			if(pBuffer[i] > pBuffer[j])
			{
				temp = pBuffer[j];
				pBuffer[j] = pBuffer[i];
				pBuffer[i] = temp;
			}
		}
	}
}

float GetAverageFloat(float *pBuffer, uint8_t count, uint8_t discardCount)
{
	uint8_t i;
	float average = 0;

	for(i=discardCount;i<(count-discardCount);i++)
		average += pBuffer[i];

	average /= (count-2*discardCount);
	return average;
}

uint8_t weightedTable[] = {1, 2, 4, 8, 16, 32, 64};

float GetWeightedAverageFloat(float *pBuffer, uint8_t len, uint8_t discardCount)
{
	float average = 0;
	uint16_t averageCnt = 0;
	uint8_t startIndex = len/4;
	//uint8_t startIndex = 0;
    uint8_t i, j;
//    uint8_t weightedIndex;
    float temp;

	//排序
	for(i = 0; i < len-1; i++)
	{
		for(j = i+1; j < len; j++)
		{
			if(pBuffer[i] < pBuffer[j])
			{
				temp = pBuffer[i];
				pBuffer[i] = pBuffer[j];
				pBuffer[j] = temp;
			}
		}
	}

	//加权平均
	for(i = startIndex; i < len - startIndex; i++)
	{
		if(i <= len/2)
		{
			average += pBuffer[i]*(i - startIndex + 1);
			averageCnt += (i - startIndex + 1);
		}
		else
		{
			average += pBuffer[i]*(len - startIndex - i);
			averageCnt += (len - startIndex - i);
		}
	}
	average /= averageCnt;

//    weightedIndex = 0;
//    for(i = startIndex; i < len - startIndex; i++)
//	{
//		if(i < len/2)
//		{
//			average += pBuffer[i]*weightedTable[weightedIndex];
//			averageCnt += weightedTable[weightedIndex];
//            weightedIndex++;
//		}
//        else
//        {
//            average += pBuffer[i]*weightedTable[weightedIndex];
//			averageCnt += weightedTable[weightedIndex];
//            weightedIndex--;
//        }
//	}
//    average /= averageCnt;
    
	return average;
}

float OrderFilterFloat(float *pData, uint8_t len, uint8_t order)
{
	float average = 0;
	uint16_t averageCnt = 0;
    uint8_t i;
	for(i=0;i<len;i++)
	{
		average += (pData[i] * (i + 1));
		averageCnt += (i + 1);
	}
	average /= averageCnt;
	return average;
}


/**
 * @brief  Reset the mcu by software
 *
 * @param  none
 *
 * @note   use the 3.5 version of the firmware library. 
 */
void SoftReset(void)
{
    __set_FAULTMASK(1); // 关闭所有中断
    NVIC_SystemReset(); // 复位
}


void GetChipID(uint32_t *chipID)
{
//#ifdef STM32SIM
	chipID[0] = *(__IO uint32_t*)(0X1FFFF7F0); //高字节
	chipID[1] = *(__IO uint32_t*)(0X1FFFF7EC);
	chipID[2] = *(__IO uint32_t*)(0X1FFFF7E8); //低字节
//#else
//	chipID[0] = 0X0FFFF7F0;
//	chipID[1] = 0X0FFFF7EC;
//	chipID[2] = 0X1FFFF7E8;
//#endif
	//STM32_FLASH_SIZE = *(__IO uint32_t*)(0X1FFFF7E0);
}

uint32_t RandomString2UInt32(uint8_t *str)
{
    uint8_t strLen = strlen((const char*)str);
    uint8_t i, j = 0;
    uint32_t ret = 0;
    uint8_t *p = (uint8_t*)&ret;
    
    for(i=0;i<strLen;i++)
    {
        p[j] ^= str[i];
        j++;
        if(j >= 4)
            j = 0;
    }
    
    return ret;
}

uint8_t BCDToInt(uint8_t bcd) //BCD转10进制
{
	return (0xff & (bcd>>4))*10 +(0xf & bcd);
}

uint8_t IntToBCD(uint8_t i) //10进制转BCD
{
	return (((i/10)<<4)+((i%10)&0x0f));
}




/************************************************************************/
/*    判断闰年函数(4年一润,100年不润,400年再润)                         */
/************************************************************************/
int isPrime(int year)
{
	if ((year%4==0&&year%100!=0)||(year%400==0))
	{
		return 1;
	} 
	else
	{
		return 0;
	}
 
}
 
int dateDiff(struct date mindate,struct date maxdate)
{
    int i, j;
	int days=0, flag=1;
	const int primeMonth[12]={31,29,31,30,31,30,31,31,30,31,30,31};
	const int notPrimeMonth[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	
    struct date tmp;
    
    int maxmonth,minmonth;
    
    int day;
    
	/************************************************************************/
	/*        交换两个日期函数,将小的日期给mindate,将大的日期给maxdate     */
    /************************************************************************/	
	if ((mindate.year>maxdate.year)|| (mindate.year==maxdate.year&&mindate.month>maxdate.month)||(mindate.year==maxdate.year&&mindate.month==maxdate.month&&mindate.day>maxdate.day))
	{
		tmp=mindate;
		mindate=maxdate;
		maxdate=tmp;
	} 
	
	/************************************************************************/
	/* 主要思路:拿2002-8-8   2005-2-22来说                                  */                                         
	/*   将2004-8-8---2005-2-22----2005-7-8                                 */
	/*一前一后刚好N年,算出2005-2-22到2005-7-8的天数,然后用总年*36(5|6)减掉) */
	/*          2002-9-8      2005-11-22                                    */
	/*          2002-9-8-----2005-9-8-----2005-11-22(这次是加上后面天数)    */
	/*如何判断是加还是减呢?年大而月小的,则是减,程序中用flag标示             */
	/************************************************************************/
	if (maxdate.month<mindate.month)
	{
		maxmonth=mindate.month;
		minmonth=maxdate.month;
		flag=-1;
	}
	else
	{
		maxmonth=maxdate.month;
		minmonth=mindate.month;
		flag=1;
	}
	
    /************************************************************************/
    /*  从mindate.year开始累加到maxdate.year                                */
    /************************************************************************/
	for(j=mindate.year;j<maxdate.year;++j)
	{
		if (isPrime(j)==1)
		{
			days+=366;
		}
		else
			days+=365;
	}
	
	/************************************************************************/
	/* 从minmonth累加到maxmonth,分闰年和平年                                */
	/************************************************************************/
	if(isPrime(maxdate.year)==1)
	{
		
		for(i=minmonth;i<maxmonth;i++)
		{
			day=primeMonth[i-1]*flag;
			days=days+day;
		}
		days=days+maxdate.day-mindate.day;
	}
	else
	{
		for (i=minmonth;i<maxmonth;i++)
		{
			day=notPrimeMonth[i-1]*flag;
			days=days+day;
		}
		days=days+maxdate.day-mindate.day;
	}
	return days;
}

void UsefulDaysCheck(void)
{
    //uint8_t flag;
    uint32_t diffd = 0;  

    cDebug("UsefulDaysCheck()...\r\n");
    
    //第一次开机，不检查
    if(man.eepromDate.year == 0 && man.eepromDate.month == 0 && man.eepromDate.day == 0)
    {
        AT24CXX_Write(EEPROM_ADDR_DATE, (uint8_t*)&man.lcdDate, 3*4);
        
        cDebug("UsefulDaysCheck()...Finish---First Power On\r\n");        
        return;
    }
    
    //已破解，则不检查
    if(man.isCracked)
    {
        cDebug("UsefulDaysCheck()...Finish---Cracked\r\n");
        return;
    }
    
    if(man.eepromDate.year > man.lcdDate.year) //eeprom保存的年份比lcd年份大
    {
        diffd = dateDiff(man.lcdDate, man.eepromDate);
        
        man.usefulDays = 0;
        
        //if(diffd > 366)
            cDebug("current date is less more days\r\n");
    }
    else if(man.eepromDate.year == man.lcdDate.year) //年份相同
    {
        if(man.eepromDate.month > man.lcdDate.month)//eeprom保存的月份比lcd月份大
        {
            diffd = dateDiff(man.lcdDate, man.eepromDate);
            
            //man.usefulDays += diffd;
            
            man.usefulDays = 0;
        }
        else if(man.eepromDate.month == man.lcdDate.month)//月份相同
        {
            if(man.eepromDate.day > man.lcdDate.day)//eeprom保存的日期比lcd日期大
            {
                diffd = dateDiff(man.lcdDate, man.eepromDate);
            
                //man.usefulDays += diffd;
                
                man.usefulDays = 0;
            }
            else if(man.eepromDate.day == man.lcdDate.day)//日期相同
            {
            
            }
            else//eeprom保存的日期比lcd日期小
            {
                diffd = dateDiff(man.eepromDate, man.lcdDate);
            
                if(man.usefulDays < diffd)
                    man.usefulDays = 0;
                else
                    man.usefulDays -= diffd;
            }
        }
        else//eeprom保存的月份比lcd月份小
        {
            diffd = dateDiff(man.eepromDate, man.lcdDate);
            
            if(man.usefulDays < diffd)
                man.usefulDays = 0;
            else
                man.usefulDays -= diffd;
        }
    }
    else//eeprom保存的年份比lcd年份小
    {
        diffd = dateDiff(man.eepromDate, man.lcdDate);
            
        if(man.usefulDays < diffd)
            man.usefulDays = 0;
        else
            man.usefulDays -= diffd;
    }
    
    cDebug("diffd = %d\r\n", diffd);
    
    //AT24CXX_Write(EEPROM_ADDR_USEFULDAYS, (uint8_t*)&man.usefulDays, 2);

    //试用期到
    if(man.isCracked == 0 && man.usefulDays == 0)
    {
        qsize size = 0;

        while(man.isCracked == 0 && man.usefulDays == 0)
        {
            size = man.ProtocolComQueue_FindCmd(comCmdBufferAscii, comCmdBufferHex, COM_CMD_MAX_SIZE, &comQueue);     //从缓冲区中获取一条指令         
						if(size > 0)  //接收到指令 
						{                                                                           
							man.ProtocolComProcessFrame((void*)comCmdBufferHex, size);                    //指令处理 
						}
						     
            IWDG_Feed();
        }
    }
    
    cDebug("UsefulDaysCheck()...Finish\r\n");
}

//一个浮点数保留多少位小数
void FloatFormatDecimal(float *pfData, uint8_t decimalNum)
{
	switch(decimalNum)
	{
			case 3://保留3位小数点
					(*pfData) *= 1000;
					(*pfData) = ((uint32_t)(*pfData))/1000.0;
			break;
			case 2://保留2位小数点
					(*pfData) *= 100.0;
					(*pfData) = ((uint32_t)(*pfData))/100.0;
			break;
			default://保留1位小数点
					(*pfData) *= 10.0;
					(*pfData) = ((uint32_t)(*pfData))/10.0;
			break;
	}
}

//一个浮点数转成字符串保留多少位小数
void FloatFormatDecimalString(uint8_t *str, const float *pfData, uint8_t decimalNum)
{
	switch(decimalNum)
	{
			case 3://保留3位小数点
					sprintf((char*)str, "%.03f", *pfData);
			break;
			case 2://保留2位小数点
					sprintf((char*)str, "%.02f", *pfData);
			break;
			default://保留1位小数点
					sprintf((char*)str, "%.01f", *pfData);
			break;
	}
}


static char buffer[100];
int myDebug(char *format, ...)
{
	va_list aptr;
	int ret;
	
	va_start(aptr, format);
	ret = vsprintf(buffer, format, aptr);
	va_end(aptr);

	if(man.comType == 1)//主通信口为网口，所以用串口做调试口
	{
		//printf("%s", buffer);
		uint8_t i;
		for(i=0;i<strlen(buffer);i++)
			ComUart_SendChar(buffer[i]);
	}
	else
	{
		if(S0_State&S_CONN)
			Write_SOCK_Data_Buffer(0, (uint8_t*)buffer, strlen(buffer));
	}
	return ret;
}
