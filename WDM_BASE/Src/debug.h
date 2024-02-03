#pragma once
#include "driver.h"

#define dbg(...) DbgPrintEx(DPFLTR_IHVDRIVER_ID,DPFLTR_ERROR_LEVEL, __VA_ARGS__);
