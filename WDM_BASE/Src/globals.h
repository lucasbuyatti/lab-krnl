#pragma once
#include "includes.h"

UNICODE_STRING DevName;
UNICODE_STRING Win32Name;
extern PDEVICE_OBJECT DeviceObj = NULL;

extern ULONG gUniqueProcessId = 0;
extern UCHAR* gImageFileName = NULL;
extern PVOID gImageBaseAddress = NULL;
