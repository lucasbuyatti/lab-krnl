#include "ioctl.h"

UNICODE_STRING DevName;
UNICODE_STRING Win32Name;
PDEVICE_OBJECT DeviceObj;

NTSTATUS ioctlCreateClose(PDEVICE_OBJECT pDeviceObject, PIRP irp)
{
	UNREFERENCED_PARAMETER(pDeviceObject);

	PAGED_CODE();

	irp->IoStatus.Status = STATUS_SUCCESS;
	irp->IoStatus.Information = 0;

	IoCompleteRequest(irp, IO_NO_INCREMENT);

	return STATUS_SUCCESS;
}

NTSTATUS ioctlDeviceControl(PDEVICE_OBJECT pDeviceObject, PIRP irp)
{
	UNREFERENCED_PARAMETER(pDeviceObject);

	NTSTATUS status = STATUS_SUCCESS;
	PIO_STACK_LOCATION pIoLocation;
	ULONG outputBufferLenght;
	//ULONG inputBufferLenght;
	//PCHAR inputBuffer;
	PCHAR outputBuffer;
	PCHAR data = "HOLA DESDE EL KERNEL";
	size_t datalenght = strlen(data) + 1;

	PAGED_CODE();

	pIoLocation = IoGetCurrentIrpStackLocation(irp);
	outputBufferLenght = pIoLocation->Parameters.DeviceIoControl.OutputBufferLength;
	//inputBufferLenght = pIoLocation->Parameters.DeviceIoControl.InputBufferLength;

	if (!outputBufferLenght)
	{
		status = STATUS_INVALID_PARAMETER;  // Este error da GetLastError(); en el modo usuario
	}
	else
	{
		switch (pIoLocation->Parameters.DeviceIoControl.IoControlCode)
		{
		case FIRST_IOCTL_BUFFERED:

			outputBuffer = irp->AssociatedIrp.SystemBuffer;

			RtlCopyBytes(outputBuffer, data, datalenght);

			if (outputBufferLenght < datalenght)
			{
				irp->IoStatus.Information = outputBufferLenght;
			}
			else 
			{
				irp->IoStatus.Information = datalenght;
			}

			break;

		default:
			status = STATUS_INVALID_DEVICE_REQUEST;

			break;
		}
	}


	irp->IoStatus.Status = status;
	IoCompleteRequest(irp, IO_NO_INCREMENT);

	return status;
}

NTSTATUS createDevice(
	PDRIVER_OBJECT DriverObject,
	NTSTATUS status
)
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
NTSTATUS symLink(
	NTSTATUS status
)
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
		IoDeleteDevice(DeviceObj); // Eliminar la referencia de un puntero posiblemente nulo "DeviceObj" (lifetime.1).
		return status;
	}
	dbg("[+] IoCreateSymbolicLink\n");
	return status;

}