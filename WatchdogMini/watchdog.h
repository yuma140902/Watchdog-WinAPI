#pragma once
#include "timer.h"
#include "window.h"
#include <windows.h>

typedef struct {
    DWORD dwTargetPID;
    Timer* timer;
    Window* window;
} Watchdog;

void watchdog_setup(OUT Watchdog* wd, DWORD dwTargetPID, IN Timer* timer, IN Window* window);
VOID CALLBACK watchdog_timerRoutine(PVOID lpParam, BOOLEAN timerOrWaitFired);
BOOL watchdog_isProcessAlive(DWORD pid);
DWORD watchdog_respawnProcess();

void private_setInterval(IN Watchdog* wd, DWORD ms, WAITORTIMERCALLBACK func);
