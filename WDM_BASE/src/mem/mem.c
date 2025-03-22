#include "mem.h"

PVOID ReadMemory(PVOID address, PVOID buffer, VT valueType)
{
	NTSTATUS status = STATUS_SUCCESS;

	if (!address || !buffer) {
		return STATUS_INVALID_ADDRESS;
	}

	__try
	{
		
		switch (valueType)
		{
		case tInt:
			RtlCopyMemory(buffer, address, sizeof(int));
			return (int*)buffer;
			break;
		case tFloat:
			RtlCopyMemory(buffer, address, sizeof(float));
			return (float*)buffer;
			break;
		case tDouble:
			RtlCopyMemory(buffer, address, sizeof(double));
			return (double*)buffer;
			break;
			
		case tString:
			RtlCopyMemory(buffer, address, sizeof(STRING));
			return (STRING*)buffer;
			break;
		default:
			break;
		}

		
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

	if (!address || !buffer) {
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