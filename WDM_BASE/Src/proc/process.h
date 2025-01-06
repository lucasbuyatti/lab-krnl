#pragma once
#ifndef PROCESS_H
#define PROCESS_H

#include "..\global\globals.h"
#include "..\global\struct.h"

struct process {
	PVOID targetProcess;
	ULONG uniqueProcessId;
	PUCHAR imageFileName;
	PVOID imageBaseAddress;
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
	PWCH modname
);

PVOID GetKernelModuleBase(
	PEPROCESS process, 
	CONST PCHAR modname
);

VOID ProcessInfoByName(
	CONST PCHAR filename
);

#endif // !PROCESS_H