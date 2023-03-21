#pragma once
#include "window.h"
#include <windows.h>

typedef struct {
    DWORD dwTargetPID;
    HANDLE hTimerQueue;
    Window* window;
} Watchdog;

void watchdog_setup(OUT Watchdog* wd, IN Window* window);
VOID CALLBACK watchdog_timerRoutine(PVOID lpParam, BOOLEAN timerOrWaitFired);
BOOL watchdog_isProcessAlive(DWORD pid);
DWORD watchdog_respawnProcess();

void private_setInterval(IN Watchdog* wd, DWORD ms, WAITORTIMERCALLBACK func);
