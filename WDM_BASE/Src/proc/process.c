#pragma warning (disable : 4047 4189)
#include "process.h"


VOID ProcessInfoByName(CONST PCHAR filename)
{
	PEPROCESS currProcess = PsGetCurrentProcess();
	PVOID sourceProcess = currProcess;

	PLIST_ENTRY aplList = (PLIST_ENTRY)((ULONG_PTR)currProcess + 0x1d8);
	PLIST_ENTRY entry;

	entry = aplList;

	do
	{
		PEPROCESS processes = (PEPROCESS)((ULONG_PTR)entry - 0x1d8);

		proc.imageFileName = GetImageFileName(processes);

		if (!proc.imageFileName) return;

		if (strcmp((CONST PCHAR)proc.imageFileName, filename) == 0)
		{
			proc.targetProcess = processes;
			proc.uniqueProcessId = GetUniqueProcessId(processes);
			proc.imageFileName = proc.imageFileName;
			proc.imageBaseAddress = GetImageBaseAddress(processes);
			return;
		}

		ExFreePool(proc.imageFileName);

		if (!entry) return;

		entry = entry->Flink;
	} while (entry != aplList);

	return;

}

ULONG GetUniqueProcessId(PEPROCESS process)
{
	ULONG_PTR pid = (ULONG_PTR)((ULONG_PTR)process + 0x1d0);

	if (!pid) return 0;

	ULONG processId = *((ULONG*)pid);

	return processId;
}

PUCHAR GetImageFileName(PEPROCESS process)
{
	PUCHAR ImageFileName = (PUCHAR)((ULONG_PTR)process + 0x338);

	if (!ImageFileName) return NULL;

	SIZE_T imageNameLenght = strlen((CONST PCHAR)ImageFileName);

	PUCHAR imageName = (PUCHAR)ExAllocatePool2(POOL_FLAG_NON_PAGED, imageNameLenght + 1, 'aa');

	if (!imageName) return NULL;

	RtlCopyMemory(imageName, ImageFileName, imageNameLenght);
	imageName[imageNameLenght] = '\0';

	return imageName;
}

PVOID GetImageBaseAddress(PEPROCESS process)
{
	if (!process) return NULL;

	PPEB peb = *(PPEB*)((ULONG_PTR)process + 0x2e0);
	if (!peb) return NULL;

	PVOID ptrImageBaseAddress = (PVOID)((ULONG_PTR)peb + 0x010);
	if (!ptrImageBaseAddress) return NULL;

	KAPC_STATE apcState;
	PVOID imageBaseAddress = NULL;

	__try
	{

		KeStackAttachProcess((PRKPROCESS)process, &apcState);

		imageBaseAddress = *(PVOID*)ptrImageBaseAddress;
		ProbeForRead((PVOID)imageBaseAddress, sizeof(PVOID), sizeof(ULONG));

		if (!imageBaseAddress) return NULL;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		dbg("EXCEPTION: 0x%X\n", GetExceptionCode());
	}

	KeUnstackDetachProcess(&apcState);

	return imageBaseAddress;
}

PVOID GetModuleBase(PEPROCESS process, PWCH modname)
{
	KAPC_STATE apc;

	if (!process || !modname)
		return NULL;

	KeStackAttachProcess(process, &apc);

	PVOID dllBase = NULL;

	__try
	{
		PPEB peb = *(PPEB*)((ULONG_PTR)process + 0x2e0);
		if (!peb) return NULL;

		PPEB_LDR_DATA ldr = peb->Ldr;
		if (!ldr) return NULL;

		PLIST_ENTRY ldrEntry = &ldr->InLoadOrderModuleList;
		if (!ldrEntry) return NULL;
		
		PLIST_ENTRY currEntry = ldrEntry->Flink;
		do
		{
			PLDR_DATA_TABLE_ENTRY ldrTableEntry = CONTAINING_RECORD(currEntry, LDR_DATA_TABLE_ENTRY, InLoadOrderLinks);
			
			if (!ldrTableEntry) return NULL;

			if (wcscmp(ldrTableEntry->BaseDllName.Buffer, modname) == 0)
			{

				dllBase = ldrTableEntry->DllBase;
			}

			currEntry = currEntry->Flink;

		} while (currEntry != ldrEntry); 


	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		dbg("EXCEPTION: 0x%X\n", GetExceptionCode());

	}

	KeUnstackDetachProcess(&apc);

	return dllBase;
}

PVOID GetKernelModuleBase(PEPROCESS process, CONST PCHAR modname)
{
	UNREFERENCED_PARAMETER(process);
	UNREFERENCED_PARAMETER(modname);
	return NULL;
}