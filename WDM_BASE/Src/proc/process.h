#pragma once
#ifndef PROCESS_H
#define PROCESS_H

#include "..\global\globals.h"
#include "..\global\struct.h"

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


ULONG GetUniqueProcessId(
	PEPROCESS process
);
PUCHAR GetImageFileName(
	PEPROCESS process
);
PVOID GetImageBaseAddress(
	PEPROCESS process
);
PVOID GetModuleBase(
	PEPROCESS process,
	CONST PCHAR modname
);

PVOID GetKernelModuleBase(
	PEPROCESS process, 
	CONST PCHAR modname
);

VOID ProcessInfoByName(
	CONST PCHAR filename
);

#endif // !PROCESS_H