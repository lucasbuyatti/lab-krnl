#pragma once
#include "includes.h"

UNICODE_STRING DevName;
UNICODE_STRING Win32Name;
extern PDEVICE_OBJECT DeviceObj = NULL;

extern PVOID g_SourceProcess = NULL;
extern PVOID g_TargetProcess = NULL;
extern ULONG g_UniqueProcessId = 0;
extern PUCHAR g_ImageFileName = NULL;
extern PVOID g_ImageBaseAddress = NULL;
extern PVOID g_DllBase = NULL;
