#include "global\globals.h"
#include "proc\process.h"
#include "ioctl\ioctl.h"

DRIVER_INITIALIZE DriverEntry;
DRIVER_UNLOAD UnloadDriver;

VOID loadProcess() 
{
	ProcessInfoByName("Notepad.exe");
	//dbg("Target Process EPROCESS: 0x%p\n", proc.targetProcess);
	//dbg("Source process EPROCESS: 0x%p\n", proc.sourceProcess);
	//dbg("ImageBaseAddress: 0x%p\n", proc.imageBaseAddress);
	//dbg("UniqueProcessId: %d\n", proc.uniqueProcessId);
}

VOID loadTest()
{

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

	loadProcess();


	//BreakPoint;

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

	// PAGED_CODE();

	//IoDeleteSymbolicLink(&Win32Name);
	//dbg("[-] SymbolicLink\n");

	//if (DeviceObj != NULL)
	//{
	//	IoDeleteDevice(DeviceObj);
	//	dbg("[-] Device\n");
	//}

	dbg("[-] Driver\n");
}
