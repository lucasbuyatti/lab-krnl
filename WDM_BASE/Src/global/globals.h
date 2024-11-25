#pragma once
#ifndef GLOBALS_H
#define	GLOBALS_H

#include <ntifs.h>
#include <ntddk.h>
#include "debug.h"

extern UNICODE_STRING DevName;
extern UNICODE_STRING Win32Name;
extern PDEVICE_OBJECT DeviceObj;

struct process { // Nunca use struct, no se como afectaria al proyecto :d
	// En realidad esto no es necesario ponerlo aca
	PVOID sourceProcess;
	PVOID targetProcess;
	//
	ULONG uniqueProcessId;
	PUCHAR imageFileName;
	PVOID imageBaseAddress;
	PVOID dllBase;
}proc;

#endif // !GLOBALS_H