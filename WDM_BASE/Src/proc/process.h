#pragma once
#ifndef PROCESS_H
#define PROCESS_H

#include "..\global\globals.h"
#include "..\global\struct.h"

ULONG GetUniqueProcessId(
	PEPROCESS process
);
PUCHAR GetImageFileName(
	PEPROCESS process
);
PVOID GetImageBaseAddress(
	PEPROCESS process
);
PVOID GetDllBase(
	PEPROCESS process,
	CONST PCHAR dllname
);

VOID ProcessInfoByName(
	CONST PCHAR filename
);

#endif // !PROCESS_H