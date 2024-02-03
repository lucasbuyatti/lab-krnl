#pragma once
#ifndef DEBUG_H
#define DEBUG_H

#include "driver.h"

#define dbg(...) DbgPrintEx(DPFLTR_IHVDRIVER_ID,DPFLTR_ERROR_LEVEL, __VA_ARGS__);

#endif // DEBUG_H