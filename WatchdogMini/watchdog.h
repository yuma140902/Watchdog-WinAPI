#pragma once
#include <windows.h>

extern DWORD g_dwTargetPID;

void setupWatchDog(HWND hLabel);
DWORD respawnProcess();
