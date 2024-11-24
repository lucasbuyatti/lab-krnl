#include "process.h"


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


VOID ProcessInfoByName(CONST PCHAR filename)
{
	PAGED_CODE();
	/* Obtengo el puntero a _EPROCESS */
	PEPROCESS currProcess = PsGetCurrentProcess();
	proc.sourceProcess = currProcess;

	/* Obtengo el puntero al miembro ActiveProcessLinks de la estructura _EPROCESS */
	PLIST_ENTRY aplList = (PLIST_ENTRY)((ULONG_PTR)currProcess + 0x1d8);
	PLIST_ENTRY entry;

	entry = aplList;
	do
	{
		/* Obtengo el _EPROCESS de los demas procesos */
		/* Resto 0x448 (ActiveProcessLinks) para obtenerlo */
		PEPROCESS processes = (PEPROCESS)((ULONG_PTR)entry - 0x1d8);

		proc.imageFileName = GetImageFileName(processes); // Creo que falta algo (Manejo de memoria o de resultado ????????????)

		if (strcmp((CONST PCHAR)proc.imageFileName, filename) == 0)
		{
			// Aca llamo a todas las funciones

			proc.targetProcess = processes;
			proc.uniqueProcessId = GetUniqueProcessId(processes);
			proc.imageFileName = proc.imageFileName;
			proc.imageBaseAddress = GetImageBaseAddress(processes);

			// GetDllBase(processes, NULL);
			return;
		}

		ExFreePool(proc.imageFileName);

		entry = entry->Flink;
	} while (entry != aplList);

}

ULONG GetUniqueProcessId(PEPROCESS process)
{
	/* Obtengo el miembro UniqueProcessId */
	ULONG_PTR pid = (ULONG_PTR)((ULONG_PTR)process + 0x1d0);

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
	PUCHAR ImageFileName = (PUCHAR)((ULONG_PTR)process + 0x338);

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
	PPEB peb = *(PPEB*)((ULONG_PTR)process + 0x2e0);
	if (!peb)
		return NULL;

	/* Obtengo el puntero del miembro ImageBaseAddress */
	PVOID ptrImageBaseAddress = (PVOID)((ULONG_PTR)peb + 0x010);
	if (!ptrImageBaseAddress)
		return NULL;

	KAPC_STATE apcState;
	PVOID imageBaseAddress = NULL;
	__try
	{
		/* Obtengo el miembro ImageBaseAddress */
		KeStackAttachProcess((PRKPROCESS)process, &apcState);

		imageBaseAddress = *(PVOID*)ptrImageBaseAddress;
		ProbeForRead((PVOID)imageBaseAddress, sizeof(PVOID), sizeof(ULONG)); // solo chequea el buffer del usuario

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
// No funka, problema para otra hora, dia, mes o año. Incluso para otra persona :p
PVOID GetDllBase(PEPROCESS process, CONST PCHAR dllname)
{
	UNREFERENCED_PARAMETER(dllname);

	PPEB peb = *(PPEB*)((ULONG_PTR)process + 0x550); // Hay que actualizarlo
	dbg("Estructura Peb: 0x%p\n", peb);

	KAPC_STATE apc;
	__try
	{
		KeStackAttachProcess(process, &apc);
		dbg("SsHandle 0x%p\n", peb->Ldr->InMemoryOrderModuleList);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		dbg("EXCEPTION: 0x%X\n", GetExceptionCode());
	}
	KeUnstackDetachProcess(&apc);
	return NULL;
}