#pragma once
#ifndef DEBUG_H
#define DEBUG_H

#include "globals.h"


#ifdef _DEBUG
#define dbg(...) DbgPrintEx(DPFLTR_IHVDRIVER_ID,DPFLTR_ERROR_LEVEL, __VA_ARGS__);
#endif // DEBUG

#define offsetof(type, member) ((size_t) &(((type *)0)->member))


#endif // DEBUG_H