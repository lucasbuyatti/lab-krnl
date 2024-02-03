#pragma once
#ifndef PROCESS_H
#define PROCESS_H

#include "driver.h"
#include "globals.h"
#include "struct.h"

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

VOID processInfo(
	CONST PCHAR filename
);

#endif // !PROCESS_H