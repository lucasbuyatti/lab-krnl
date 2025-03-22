#pragma once
#ifndef IOCTL_H
#define IOCTL_H

#include "..\global\globals.h"

#define NT_DEVICE_NAME L"\\Device\\IOCTL"
#define DOS_DEVICE_NAME L"\\DosDevices\\IOCTLtest"
#define FIRST_IOCTL_BUFFERED \
	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x805, METHOD_BUFFERED, FILE_ANY_ACCESS)

UNICODE_STRING DevName;
UNICODE_STRING Win32Name;
PDEVICE_OBJECT DeviceObj;

DRIVER_DISPATCH ioctlCreateClose;
DRIVER_DISPATCH ioctlDeviceControl;

NTSTATUS createDevice(
	PDRIVER_OBJECT DriverObject,
	NTSTATUS status
);

NTSTATUS symLink(
	NTSTATUS status
);

#endif // !IOCTL_H
