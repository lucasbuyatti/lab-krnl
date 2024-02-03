#pragma once
#ifndef GLOBALS_H
#define	GLOBALS_H

#include "driver.h"

static UNICODE_STRING DevName;
static UNICODE_STRING Win32Name;
static PDEVICE_OBJECT DeviceObj = NULL;

static PVOID g_SourceProcess = NULL;
static PVOID g_TargetProcess = NULL;
static ULONG g_UniqueProcessId = 0;
static PUCHAR g_ImageFileName = NULL;
static PVOID g_ImageBaseAddress = NULL;
static PVOID g_DllBase = NULL;

#endif // !GLOBALS_H