#include "includes.hpp"

void lastError(DWORD error)
{
	LPWSTR buffer;

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		0,
		error,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPWSTR)&buffer,
		0,
		NULL
	);

	wprintf(L"%s\n", buffer);

	LocalFree(buffer);
}

int main()
{
	
	HANDLE hDevice;
	BOOL ioctl = FALSE;
	ULONG bytesReturned = NULL;

	//char inputBuffer[100];
	char outputBuffer[100];

	hDevice = CreateFileA(
		"\\\\.\\IOCTLtest", // SymbolicLink
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);

	
	DWORD hDeviceError = GetLastError();

	if (hDevice == INVALID_HANDLE_VALUE)
	{
		std::cout << "hDevice: ";
		lastError(hDeviceError);
;		Sleep(5000);
		return 1;
	}

	

	ioctl = DeviceIoControl(
		hDevice,
		FIRST_IOCTL_BUFFERED,
		NULL,
		0,
		&outputBuffer, 
		sizeof(outputBuffer),
		&bytesReturned,
		NULL
		);

	DWORD DeviceIoControlError = GetLastError();

	if (!ioctl)
	{
		std::cout << "DeviceIoControl: ";
		lastError(DeviceIoControlError);
		Sleep(5000);
		CloseHandle(hDevice);
		return 1;
	}

	std::cout << "KERNEL DICE: \"" << outputBuffer << "\"" << std::endl;
	Sleep(5000);

	CloseHandle(hDevice);

	return 0;
}