#include "Project.h"
#include "stdint.h"
#include "management.h"
#include "Key.h"
#include "string.h"
#include "stdio.h"
#include "CPrintf.h"
#include "24cxx.h"
#include "ComDriver.h"
#include "IO.h"
#include "simplc_io.h"


void ProjectRunning(void)
{
	if(GXF(X_KEY1))
	{
		man.beepFlag = 1;
		
		SetCoilMutual(Y_COIL1);
	}
	
	if(GXF(X_KEY2))
	{
		man.beepFlag = 1;
		
		SetCoilMutual(Y_COIL2);
	}
	
	if(GXF(X_KEY3))
	{
		man.beepFlag = 1;
		
		SetCoilMutual(Y_COIL3);
	}
	
	if(GXF(X_KEY4))
	{
		man.beepFlag = 1;
		
		SetCoilMutual(Y_COIL4);
	}
	
	if(GXF(X_KEY5))
	{
		man.beepFlag = 1;
		
		SetCoilMutual(Y_COIL5);
	}
	
	if(GXF(X_KEY6))
	{
		man.beepFlag = 1;
		
		SetCoilMutual(Y_COIL6);
	}
	
	if(GXF(X_KEY7))
	{
		man.beepFlag = 1;
		
		SetCoilMutual(Y_COIL7);
	}
	
	if(GXF(X_KEY8))
	{
		man.beepFlag = 1;
		
		SetCoilMutual(Y_COIL8);
	}
	
	
	//Õ‚≤ø ‰»Î
	if(GXR(X_EXT))
	{
		cDebug("X_EXT signal\r\n");
		
		if(GYL(Y_EXT))
			SYL(Y_EXT, 0);
		else
			SYL(Y_EXT, 1);
	}
}

