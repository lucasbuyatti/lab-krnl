#pragma once
#ifndef GLOBALS_H
#define	GLOBALS_H

#include <ntifs.h>
#include <ntddk.h>
#include "debug.h"

extern UNICODE_STRING DevName;
extern UNICODE_STRING Win32Name;
extern PDEVICE_OBJECT DeviceObj;

extern PVOID g_SourceProcess;
extern PVOID g_TargetProcess;
extern ULONG g_UniqueProcessId;
extern PUCHAR g_ImageFileName;
extern PVOID g_ImageBaseAddress;
extern PVOID g_DllBase;

#endif // !GLOBALS_H