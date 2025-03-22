#pragma once
#include <iostream>
#include <Windows.h>
#include <Psapi.h>
#include <strsafe.h>

#define FIRST_IOCTL_BUFFERED \
	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x805, METHOD_BUFFERED, FILE_ANY_ACCESS)