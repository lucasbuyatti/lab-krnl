#pragma once
#ifndef MEM_H
#define MEM_H

#include "..\global\globals.h"

NTSTATUS ReadMemory(
	PVOID address,
	PVOID buffer,
	ULONG size
);

NTSTATUS WriteMemory(
	PVOID address,
	PVOID buffer,
	ULONG size
);

#endif // !MEM_H