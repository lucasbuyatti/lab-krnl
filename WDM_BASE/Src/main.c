#include "global\globals.h"
#include "proc\process.h"
#include "ioctl\ioctl.h"

DRIVER_INITIALIZE DriverEntry;
DRIVER_UNLOAD UnloadDriver;

NTSTATUS
DriverEntry(
	PDRIVER_OBJECT DriverObject,
	PUNICODE_STRING RegistryPath
)
{
	NTSTATUS status = 0;

	UNREFERENCED_PARAMETER(RegistryPath);

	dbg("[+] Driver\n");

	ProcessInfoByName("Notepad.exe"); // Initialize the process info

	dbg("[+] Process 0x%p\n", proc.targetProcess);
	dbg("[+] Process ID %lu\n", proc.uniqueProcessId);
	dbg("[+] Process name %s\n", proc.imageFileName);
	dbg("[+] Process base address 0x%p\n", proc.imageBaseAddress);
	dbg("[+] Process NTDLL.dll 0x%p\n", GetModuleBase((PEPROCESS)proc.targetProcess, L"ntdll.dll"));

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


	//IoDeleteSymbolicLink(&Win32Name);
	//dbg("[-] SymbolicLink\n");
	//if (DeviceObj != NULL)
	//{
	//	IoDeleteDevice(DeviceObj);
	//	dbg("[-] Device\n");
	//}

	dbg("[-] Driver\n");
}


// _INVERTED_FUNCTION_TABLE_ENTRY