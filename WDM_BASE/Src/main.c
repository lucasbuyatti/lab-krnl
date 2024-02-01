#include "includes.h"
#include "globals.h"
#include "process.h"

NTSTATUS createDevice(PDRIVER_OBJECT DriverObject, NTSTATUS status)
{
	PAGED_CODE();
	RtlInitUnicodeString(&DevName, NT_DEVICE_NAME);

	status = IoCreateDevice(
		DriverObject,
		0,
		&DevName,
		FILE_DEVICE_UNKNOWN,
		FILE_DEVICE_SECURE_OPEN,
		FALSE,
		&DeviceObj
	);

	if (!NT_SUCCESS(status))
	{
		dbg("[-] IoCreateDevice\n");
		return status;
	}
	dbg("[+] IoCreateDevice\n");
	return status;


}
NTSTATUS symLink(NTSTATUS status)
{
	PAGED_CODE();
	RtlInitUnicodeString(&Win32Name, DOS_DEVICE_NAME);

	status = IoCreateSymbolicLink(
		&Win32Name,
		&DevName
	);

	if (!NT_SUCCESS(status))
	{
		dbg("[-] IoCreateSymbolicLink\n");
		IoDeleteDevice(DeviceObj);
		return status;
	}
	dbg("[+] IoCreateSymbolicLink\n");
	return status;

}

NTSTATUS
DriverEntry(
	PDRIVER_OBJECT DriverObject,
	PUNICODE_STRING RegistryPath
)
{
	NTSTATUS status = 0;

	UNREFERENCED_PARAMETER(RegistryPath);

	dbg("[+] Driver\n");

	processInfo("Notepad.exe");

	dbg("UniqueProcessId: %u\n", gUniqueProcessId);
	dbg("ImageFileName: %s\n", gImageFileName);
	dbg("ImageBaseAddress: 0x%p\n", gImageBaseAddress);

	/*createDevice(DriverObject, status);
	symLink(status);
	DriverObject->MajorFunction[IRP_MJ_CREATE] = ioctlCreateClose;
	DriverObject->MajorFunction[IRP_MJ_CLOSE] = ioctlCreateClose;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = ioctlDeviceControl;*/



	DriverObject->DriverUnload = UnloadDriver;

	return status;
}


void
UnloadDriver(
	PDRIVER_OBJECT DriverObject
)
{
	UNREFERENCED_PARAMETER(DriverObject);

	PAGED_CODE();

	//IoDeleteSymbolicLink(&Win32Name);
	//dbg("[-] SymbolicLink\n");

	//if (DeviceObj != NULL)
	//{
	//	IoDeleteDevice(DeviceObj);
	//	dbg("[-] Device\n");
	//}

	dbg("[-] Driver\n");
}
