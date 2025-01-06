#include "mem.h"

NTSTATUS ReadMemory(PVOID address, PVOID buffer, ULONG size)
{
	NTSTATUS status = STATUS_SUCCESS;

	if (!address) {
		return STATUS_INVALID_ADDRESS;
	}

	__try
	{
		ProbeForRead(address, size, sizeof(UCHAR));
		RtlCopyMemory(buffer, address, size);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		status = GetExceptionCode();
	}
	return status;
}

NTSTATUS WriteMemory(PVOID address, PVOID buffer, ULONG size)
{
	NTSTATUS status = STATUS_SUCCESS;

	if (!address) {
		return STATUS_INVALID_ADDRESS;
	}


	__try
	{

		ProbeForWrite(address, size, sizeof(UCHAR));
		RtlCopyMemory(address, buffer, size);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		status = GetExceptionCode();
	}
	return status;
}