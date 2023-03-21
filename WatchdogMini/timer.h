#pragma once
#include <windows.h>
typedef struct {
    HANDLE hTimerQueue;
} Timer;

BOOL timer_init(OUT Timer* t);
BOOL timer_setInterval(IN Timer* t, DWORD ms, WAITORTIMERCALLBACK func, PVOID lpParam);

