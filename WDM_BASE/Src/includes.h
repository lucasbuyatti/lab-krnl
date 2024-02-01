#pragma once
#include <ntifs.h>
#include <ntddk.h>

#define NT_DEVICE_NAME L"\\Device\\IOCTL"
#define DOS_DEVICE_NAME L"\\DosDevices\\IOCTLtest"
#define dbg(...) DbgPrintEx(DPFLTR_IHVDRIVER_ID,DPFLTR_ERROR_LEVEL, __VA_ARGS__);

DRIVER_INITIALIZE DriverEntry;
DRIVER_UNLOAD UnloadDriver;

#define FIRST_IOCTL_BUFFERED \
	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x805, METHOD_BUFFERED, FILE_ANY_ACCESS)

DRIVER_DISPATCH ioctlCreateClose;
DRIVER_DISPATCH ioctlDeviceControl;

//#if DBG
//#define dbg(_x_) \
//	DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, "WDM_BASE: ");\
//	DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, _x_)
//#else
//#define dbg(_x_) \
//	DbgPrintEx(DPFLTR_IHVDRIVER_ID, DPFLTR_ERROR_LEVEL, _x_)
//#endif

