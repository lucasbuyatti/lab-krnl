#include "process.h"

PVOID g_SourceProcess = NULL;
 PVOID g_TargetProcess = NULL;
 ULONG g_UniqueProcessId = 0;
 PUCHAR g_ImageFileName = NULL;
 PVOID g_ImageBaseAddress = NULL;
 PVOID g_DllBase = NULL;

VOID ProcessInfoByName(CONST PCHAR filename)
{
	PAGED_CODE();
	/* Obtengo el puntero a _EPROCESS */
	PEPROCESS currProcess = PsGetCurrentProcess();
	g_SourceProcess = currProcess;

	/* Obtengo el puntero al miembro ActiveProcessLinks de la estructura _EPROCESS */
	PLIST_ENTRY aplList = (PLIST_ENTRY)((ULONG_PTR)currProcess + 0x448);
	PLIST_ENTRY entry;

	entry = aplList;
	do
	{
		/* Obtengo el _EPROCESS de los demas procesos */
		/* Resto 0x448 (ActiveProcessLinks) para obtenerlo */
		PEPROCESS processes = (PEPROCESS)((ULONG_PTR)entry - 0x448);

		g_ImageFileName = GetImageFileName(processes);

		if (strcmp((CONST PCHAR)g_ImageFileName, filename) == 0)
		{
			g_TargetProcess = processes;
			g_UniqueProcessId = GetUniqueProcessId(processes);
			g_ImageFileName = g_ImageFileName;
			g_ImageBaseAddress = GetImageBaseAddress(processes);
			GetDllBase(processes, NULL);
			return;
		}

		ExFreePool(g_ImageFileName);

		entry = entry->Flink;
	} while (entry != aplList);

}

ULONG GetUniqueProcessId(PEPROCESS process)
{
	/* Obtengo el miembro UniqueProcessId */
	ULONG_PTR pid = (ULONG_PTR)((ULONG_PTR)process + 0x440);

	if (!pid)
		return 0;

	ULONG processId = *((ULONG*)pid);

	return processId;
}

/* No entiendo muy bien como funciona */
/* Falta manejar uno que otro error */
PUCHAR GetImageFileName(PEPROCESS process)
{
	/* Obtengo el miembro ImageFileName */
	PUCHAR ImageFileName = (PUCHAR)((ULONG_PTR)process + 0x5A8);

	if (!ImageFileName)
		return NULL;

	/* Obtengo la longitud de ImageFileName */
	SIZE_T imageNameLenght = strlen((CONST PCHAR)ImageFileName);

	/* Asigno un bloque de memoria del tamaño especificado, con el tipo y la proteccion especificados */
	PUCHAR imageName = (PUCHAR)ExAllocatePool2(POOL_FLAG_NON_PAGED_EXECUTE, imageNameLenght + 1, 'aa');

	if (!imageName)
		return NULL;

	/* Copio la memoria (Source) al destino (ExAllocatePool2)*/
	RtlCopyMemory(imageName, ImageFileName, imageNameLenght);
	imageName[imageNameLenght] = '\0';

	return imageName;
}

PVOID GetImageBaseAddress(PEPROCESS process)
{
	/* Obtengo el puntero a _PEB */
	PPEB peb = *(PPEB*)((ULONG_PTR)process + 0x550);
	if (!peb)
		return NULL;

	/* Obtengo el puntero del miembro ImageBaseAddress */
	PVOID ptrImageBaseAddress = (PVOID)((ULONG_PTR)peb + 0x10);
	if (!ptrImageBaseAddress)
		return NULL;

	KAPC_STATE apcState;
	PVOID imageBaseAddress = NULL;
	__try
	{
		/* Obtengo el miembro ImageBaseAddress */
		KeStackAttachProcess((PRKPROCESS)process, &apcState);

		imageBaseAddress = *(PVOID*)ptrImageBaseAddress;
		ProbeForRead((PVOID)imageBaseAddress, sizeof(PVOID), sizeof(ULONG));

		if (!imageBaseAddress)
			return NULL;
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		/* Nada */
	}

	/* Ponerlo dentro del __try causa BSOD */
	KeUnstackDetachProcess(&apcState);

	return imageBaseAddress;
}

/* ????? 🤯🤯🤯🤯 ????? */
PVOID GetDllBase(PEPROCESS process, CONST PCHAR dllname)
{
	UNREFERENCED_PARAMETER(dllname);

	PPEB peb = (PPEB)((ULONG_PTR)process + 0x550);
	dbg("Miembro Peb: 0x%p\n", peb);

	// ???????????????????????
	//PPEB desRefPEB = *(PPEB*)peb;
	//dbg("Estructura _PEB: 0x%p\n", desRefPEB); 

	PPEB_LDR_DATA Ldr = (PPEB_LDR_DATA)((ULONG_PTR)peb + 0x018);
	dbg("Miembro Ldr: 0x%p\n", Ldr);

	KAPC_STATE apc;
	PPEB_LDR_DATA Ldr2 = NULL;
	__try
	{
		KeStackAttachProcess(process, &apc);

		Ldr2 = *(PPEB_LDR_DATA*)((ULONG_PTR)Ldr - 0x550);
		ProbeForRead((PVOID)Ldr2, sizeof(PPEB_LDR_DATA), sizeof(ULONG));
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		/* Nada */

	}

	dbg("Estructura Ldr: %p\n", Ldr2);
	dbg("Miembro SsHandle: %p\n", Ldr2->SsHandle);

	KeUnstackDetachProcess(&apc);







	return NULL;
}
