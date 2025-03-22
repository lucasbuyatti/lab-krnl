#pragma once
#ifndef MEM_H
#define MEM_H

#include "..\global\globals.h"

typedef enum valueType {
    tInt, // int
    tFloat, // float
    tDouble, // double
    tString // string
}VT;

PVOID ReadMemory(
	PVOID address,
	PVOID buffer,
	VT valueType
);

NTSTATUS WriteMemory(
	PVOID address,
	PVOID buffer,
	ULONG size
);

#endif // !MEM_H