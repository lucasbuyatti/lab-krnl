#include "driver.h"
#include "process.h"

DRIVER_INITIALIZE DriverEntry;
DRIVER_UNLOAD UnloadDriver;

\
NTSTATUS
DriverEntry(
	PDRIVER_OBJECT DriverObject,
	PUNICODE_STRING RegistryPath
)
{
	NTSTATUS status = 0;

	UNREFERENCED_PARAMETER(RegistryPath);

	dbg("[+] Driver\n");

	ProcessInfoByName("Notepad.exe");
	dbg("Source process: 0x%p\n", g_SourceProcess);
	dbg("Target Process: 0x%p\n", g_TargetProcess);
	dbg("ImageBaseAddress: 0x%p\n", g_ImageBaseAddress);

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
