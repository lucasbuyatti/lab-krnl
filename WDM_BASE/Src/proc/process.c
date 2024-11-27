#pragma warning (disable : 4047 4189)
#include "process.h"

VOID ProcessInfoByName(CONST PCHAR filename)
{
	// PAGED_CODE();
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

		if (proc.imageFileName == NULL)
			return;

		if (strcmp((CONST PCHAR)proc.imageFileName, filename) == 0)
		{
			// Aca llamo a todas las funciones

			proc.targetProcess = processes;
			dbg("Target Process: 0x%p\n", proc.targetProcess);
			proc.uniqueProcessId = GetUniqueProcessId(processes);
			proc.imageFileName = proc.imageFileName;
			proc.imageBaseAddress = GetImageBaseAddress(processes);
			dbg("ImageBaseAddress: 0x%p\n", proc.imageBaseAddress);
			GetModuleBase(processes, NULL);
			return;
		}



		ExFreePool(proc.imageFileName);

		if (entry == NULL)
			return;

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
	PUCHAR imageName = (PUCHAR)ExAllocatePool2(POOL_FLAG_NON_PAGED, imageNameLenght + 1, 'aa'); // Anotación de error: Warning: Allocating executable POOL_FLAGS memory.

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

		if (process == NULL)
			return NULL;

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
		KeUnstackDetachProcess(&apcState);
	}

	/* Ponerlo dentro del __try causa BSOD */
	KeUnstackDetachProcess(&apcState);

	return imageBaseAddress;
}

/* ????? 🤯🤯🤯🤯 ????? */
// No funka, problema para otra hora, dia, mes o año. Incluso para otra persona :p
PVOID GetModuleBase(PEPROCESS process, CONST PCHAR modname)
{
	//UNREFERENCED_PARAMETER(process);
	UNREFERENCED_PARAMETER(modname);

	KAPC_STATE apc;

	if (!process)
		return NULL;

	__try
	{
		KeStackAttachProcess(process, &apc);

		PPEB peb = *(PPEB*)((ULONG_PTR)process + 0x2e0);
		if (!peb)
		{
			dbg("PEB es NULL\n");
			return NULL;
		}
		dbg("PEB: 0x%p\n", peb);

		PPEB_LDR_DATA ldr = peb->Ldr;
		if (!ldr)
		{
			dbg("LDR es NULL\n");
			return NULL;
		}
		dbg("ldr: 0x%p\n", ldr);

#pragma region revisar
		// No se si hace falta separarlos (Misma direccion de memoria)
		PLIST_ENTRY ldrEntry = &ldr->InLoadOrderModuleList->Flink;
		if (!ldrEntry)
		{
			dbg("ldrEntry es NULL\n");
			return NULL;
		}
		dbg("ldrEntry: 0x%p\n", ldrEntry);


#pragma endregion
		

		PLIST_ENTRY currEntry = ldrEntry;
		do
		{
			PLDR_DATA_TABLE_ENTRY ldrTableEntry = CONTAINING_RECORD(currEntry, LDR_DATA_TABLE_ENTRY, InLoadOrderLinks);
			//BreakPoint;
            if (!ldrTableEntry)
            {
				dbg("ldrTableEntry es NULL\n");
                return NULL;
            }

            dbg("ldrTableEntry: 0x%p\n", ldrTableEntry);
			dbg("dllBase: 0x%p\n", ldrTableEntry->DllBase);
			dbg("---\n");

			currEntry = currEntry->Flink;

		} while (currEntry != ldrEntry); 


		//do
		//{
		//	PLDR_DATA_TABLE_ENTRY ldrEntry = CONTAINING_RECORD(modList, LDR_DATA_TABLE_ENTRY, InLoadOrderLinks); // AHORA MISMO EN LA ESTRUCTURA DE PLDR_DATA

		//	dbg("?? : 0x%p\n", ldrEntry->DllBase);

		//	entry = entry->Flink;

		//} while (entry != modList);



	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		dbg("EXCEPTION: 0x%X\n", GetExceptionCode());
		// KeUnstackDetachProcess(&apc);
	}

	KeUnstackDetachProcess(&apc);
	return NULL;
}

PVOID GetKernelModuleBase(PEPROCESS process, CONST PCHAR modname)
{
	UNREFERENCED_PARAMETER(process);
	UNREFERENCED_PARAMETER(modname);
	return NULL;
}