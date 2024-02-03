#pragma once
#include "driver.h"

typedef struct _PEB_LDR_DATA {
	ULONG                   Length;
	UCHAR					Initialized;
	PVOID                   SsHandle;
	LIST_ENTRY              InLoadOrderModuleList;
	LIST_ENTRY              InMemoryOrderModuleList;
	LIST_ENTRY              InInitializationOrderModuleList;
	PVOID					EntryInProgress;
	UCHAR					ShutdownInProgress;
	PVOID					ShutdownThreadId;
} PEB_LDR_DATA, * PPEB_LDR_DATA;
