#ifndef __IO_H
#define __IO_H

#include "sys.h"

// ‰≥ˆ
#define LED 						PCout(13)
#define BEEP 						PAout(1)

#define MO_EXT 					PBout(0) 

#define MO_COIL_POWER		PAout(8)
#define MO_COIL1				PCout(9)
#define MO_COIL2				PCout(8)
#define MO_COIL3				PCout(7)
#define MO_COIL4				PCout(6)
#define MO_COIL5				PBout(15)
#define MO_COIL6				PBout(14)
#define MO_COIL7				PBout(13)
#define MO_COIL8				PBout(12)

// ‰»Î
#define MI_EXT 					PBin(1)

void IO_Init(void);

#endif
