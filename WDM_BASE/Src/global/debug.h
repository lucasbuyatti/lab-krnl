#pragma once
#ifndef DEBUG_H
#define DEBUG_H

#include "globals.h"

#define dbg(...) DbgPrintEx(DPFLTR_IHVDRIVER_ID,DPFLTR_ERROR_LEVEL, __VA_ARGS__);
#define BreakPoint DbgBreakPoint();

#endif // DEBUG_H