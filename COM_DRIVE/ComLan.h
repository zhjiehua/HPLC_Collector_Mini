#ifndef _COMLAN_H_
#define _COMLAN_H_

#include "W5500.h"

void Load_Net_Parameters(void);
void W5500_Socket_Set(void);
void Process_Socket_Data(SOCKET s);

void ComLan_Init(void);
void ComLan_Loop(void);

#endif
