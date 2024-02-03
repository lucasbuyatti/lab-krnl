#pragma once
#include "driver.h"
#include "globals.h"

#define NT_DEVICE_NAME L"\\Device\\IOCTL"
#define DOS_DEVICE_NAME L"\\DosDevices\\IOCTLtest"
#define FIRST_IOCTL_BUFFERED \
	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x805, METHOD_BUFFERED, FILE_ANY_ACCESS)

DRIVER_DISPATCH ioctlCreateClose;
DRIVER_DISPATCH ioctlDeviceControl;


NTSTATUS createDevice(
	PDRIVER_OBJECT DriverObject,
	NTSTATUS status
);

NTSTATUS symLink(
	NTSTATUS status
);


