#pragma once
#include <windows.h>

typedef struct {
    DWORD dwTargetPID;
    HANDLE hTimerQueue;
    HWND hLabel;
} Watchdog;

void watchdog_setup(OUT Watchdog *wd, HWND hLabel);
VOID CALLBACK watchdog_timerRoutine(PVOID lpParam, BOOLEAN timerOrWaitFired);
BOOL watchdog_isProcessAlive(DWORD pid);
DWORD watchdog_respawnProcess();

void private_setInterval(IN Watchdog *wd, DWORD ms, WAITORTIMERCALLBACK func);
