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
	if(GXR(X_KEY1))
	{
		if(GYL(Y_COIL1))
			SYL(Y_COIL1, 0);
		else
			SYL(Y_COIL1, 1);
	}
	
	if(GXR(X_KEY2))
	{
		if(GYL(Y_COIL2))
			SYL(Y_COIL2, 0);
		else
			SYL(Y_COIL2, 1);
	}
	
	if(GXR(X_KEY3))
	{
		if(GYL(Y_COIL3))
			SYL(Y_COIL3, 0);
		else
			SYL(Y_COIL3, 1);
	}
	
	if(GXR(X_KEY4))
	{
		if(GYL(Y_COIL4))
			SYL(Y_COIL4, 0);
		else
			SYL(Y_COIL4, 1);
	}
	
	if(GXR(X_KEY5))
	{
		if(GYL(Y_COIL5))
			SYL(Y_COIL5, 0);
		else
			SYL(Y_COIL5, 1);
	}
	
	if(GXR(X_KEY6))
	{
		if(GYL(Y_COIL6))
			SYL(Y_COIL6, 0);
		else
			SYL(Y_COIL6, 1);
	}
	
	if(GXR(X_KEY7))
	{
		if(GYL(Y_COIL7))
			SYL(Y_COIL7, 0);
		else
			SYL(Y_COIL7, 1);
	}
	
	if(GXR(X_KEY8))
	{
		if(GYL(Y_COIL8))
			SYL(Y_COIL8, 0);
		else
			SYL(Y_COIL8, 1);
	}
	
	if(GXR(X_EXT))
	{
		cDebug("X_EXT signal\r\n");
		
		if(GYL(Y_EXT))
			SYL(Y_EXT, 0);
		else
			SYL(Y_EXT, 1);
	}
}

