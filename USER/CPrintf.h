#ifndef _CPRINTF_H_
#define _CPRINTF_H_

#include "stdio.h"
#include "string.h"
#include <stdarg.h>

//�����Ҫ����λ��ģ��STM32оƬ���ܣ���Ҫ�������꣬������Ҫע�������
//#define STM32SIM

//�����Ҫ����λ������STM32оƬ���ܣ�ֻ�а壬�޵���ʹ������ȣ�����Ҫ�������꣬������Ҫע�������
//#define STM32DEBUG

//��λ���ʹ�����֮��ת������Ҫ���ڵ��Դ���������ʱ���Դ���ʹ�ò���
#define USED_PC_X_LCD 0

//ʹ�����⴮��������ʹ��PC�˵Ĵ���������ʱ���Դ��ڸĳ�LCD����
#define USED_VIRTUALLCD	0 

//��ʹ�ô�����
#define USED_UARTLCD	0

#define _CDebug

#ifdef _CDebug
	#ifdef __cplusplus
		void MyCPrintf(const char *fmt, ...);
		#define cDebug(format, ...)     MyCPrintf(format, ##__VA_ARGS__)
		//#define cDebug(format, args...)    printf(format, ##args)
	#else
		#define cDebug printf		//����ģʽ��������
		//#define cDebug(format, args...)    printf(format, ##args) //����ʹ��
		//#define cDebug(format, args...)    do{ char str[100]; sprintf(str, format, ##args); printf("%s", str); }while(0)
		//#define cDebug(format, ...)    do{ char str[100]; sprintf(str, format, ##__VA_ARGS__); printf("%s", str); }while(0)


	//��ӡ��Ϣ�ɶ��嵽�κ�ͨ�ſ�
//	int myDebug(char *format, ...);
//	#define cDebug myDebug	
		
	#endif
#else
	#ifdef __cplusplus
		#define cDebug(format, ...)
	#else
		#define cDebug
	#endif
#endif







#define USER_DEBUG_LEVEL 3
//#define USER_LOG_FILENAME	"log.txt"

#if (USER_DEBUG_LEVEL > 0)
#define USER_UsrLog(...)    cDebug(__VA_ARGS__);\
                            cDebug("\r\n");
#else
#define USER_UsrLog(...)
#endif

#if (USER_DEBUG_LEVEL > 1)

#define USER_ErrLog(...)    cDebug("ERROR: ");\
                            cDebug(__VA_ARGS__);\
                            cDebug("\r\n");
#else
#define USER_ErrLog(...)
#endif

#if (USER_DEBUG_LEVEL > 2)
#define USER_DbgLog(...)    cDebug("DEBUG : ");\
                            cDebug(__VA_ARGS__);\
                            cDebug("\r\n");
#else
#define USER_DbgLog(...)
#endif

//#if (USER_DEBUG_LEVEL > 0)
//#define USER_UsrLog(format, ...)    f_chdir((const TCHAR*)"0:/");\
//                            f_open(&(pProjectMan->file), (const TCHAR*)USER_LOG_FILENAME, FA_OPEN_ALWAYS|FA_WRITE);\
//														f_lseek(&(pProjectMan->file), pProjectMan->file.fsize);\
//														sprintf((char*)(pProjectMan->fsBuffer), "%s", "UsrLog:");\
//														sprintf((char*)(pProjectMan->fsBuffer+7), format, ##__VA_ARGS__);\
//														f_write(&(pProjectMan->file), pProjectMan->fsBuffer, strlen((char*)pProjectMan->fsBuffer), &pProjectMan->br);\
//														f_close(&(pProjectMan->file));
//#else
//#define USER_UsrLog(format, ...)
//#endif

//#if (USER_DEBUG_LEVEL > 1)

//#define USER_ErrLog(format, ...)    f_chdir((const TCHAR*)"0:/");\
//                            f_open(&(pProjectMan->file), (const TCHAR*)USER_LOG_FILENAME, FA_OPEN_ALWAYS|FA_WRITE);\
//														f_lseek(&(pProjectMan->file), pProjectMan->file.fsize);\
//														sprintf((char*)(pProjectMan->fsBuffer), "%s", "ErrorLog:");\
//														sprintf((char*)(pProjectMan->fsBuffer+9), format, ##__VA_ARGS__);\
//														f_write(&(pProjectMan->file), pProjectMan->fsBuffer, strlen((char*)pProjectMan->fsBuffer), &pProjectMan->br);\
//														f_close(&(pProjectMan->file));
//#else
//#define USER_ErrLog(format, ...)
//#endif

//#if (USER_DEBUG_LEVEL > 2)
//#define USER_DbgLog(format, ...)    f_chdir((const TCHAR*)"0:/");\
//                            f_open(&(pProjectMan->file), (const TCHAR*)USER_LOG_FILENAME, FA_OPEN_ALWAYS|FA_WRITE);\
//														f_lseek(&(pProjectMan->file), pProjectMan->file.fsize);\
//														sprintf((char*)(pProjectMan->fsBuffer), "%s", "DebugLog:");\
//														sprintf((char*)(pProjectMan->fsBuffer+9), format, ##__VA_ARGS__);\
//														f_write(&(pProjectMan->file), pProjectMan->fsBuffer, strlen((char*)pProjectMan->fsBuffer), &pProjectMan->br);\
//														f_close(&(pProjectMan->file));
//#else
//#define USER_DbgLog(format, ...)
//#endif

#endif
