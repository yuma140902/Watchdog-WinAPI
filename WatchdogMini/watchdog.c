#include "watchdog.h"
#include <windows.h>

HANDLE g_hTimerQueue;
DWORD g_dwTargetPID;
HWND g_hLabel;

void setupWatchDog(HWND hLabel);
VOID CALLBACK TimerRoutine(PVOID lpParam, BOOLEAN timerOrWaitFired);
BOOL isProcessAlive(DWORD pid);

void setInterval(int ms, WAITORTIMERCALLBACK func)
{
    WCHAR buf[256] = { 0 };
    HANDLE hTimer = NULL;
    if (!CreateTimerQueueTimer(&hTimer, g_hTimerQueue, func, NULL, ms, 0, 0)) {
        wsprintf(buf, L"CreateTimerQueueTimer failed (%d)", GetLastError());
        MessageBox(NULL, buf, L"", MB_OK);
        return;
    }
}

void setupWatchDog(HWND hLabel)
{
    WCHAR buf[256] = { 0 };

    g_hLabel = hLabel;

    g_hTimerQueue = CreateTimerQueue();
    if (g_hTimerQueue == NULL) {
        wsprintf(buf, L"CreateTimerQueue failed (%d)", GetLastError());
        MessageBox(NULL, buf, L"", MB_OK);
        return;
    }

    setInterval(1000, TimerRoutine);
}

VOID CALLBACK TimerRoutine(PVOID lpParam, BOOLEAN timerOrWaitFired)
{
    if (g_dwTargetPID == 0 || !isProcessAlive(g_dwTargetPID)) {
        WCHAR buf[256] = { 0 };
        g_dwTargetPID = respawnProcess();
        wsprintf(buf, L"Target: %d", g_dwTargetPID);
        SetWindowTextW(g_hLabel, buf);
    }

    setInterval(1000, TimerRoutine);
}

BOOL isProcessAlive(DWORD pid)
{
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);
    if (hProcess == NULL) {
        return FALSE;
    }

    DWORD dwExitCode;
    if (!GetExitCodeProcess(hProcess, &dwExitCode)) {
        CloseHandle(hProcess);
        return FALSE;
    }

    CloseHandle(hProcess);
    return dwExitCode == STILL_ACTIVE;
}

DWORD respawnProcess()
{
    HANDLE hProcess = GetCurrentProcess();

    DWORD dwProcessId = GetProcessId(hProcess);

    WCHAR processPath[MAX_PATH];
    GetModuleFileNameW(NULL, processPath, MAX_PATH);

    WCHAR commandLine[MAX_PATH];
    wsprintf(commandLine, L"%s %d", processPath, dwProcessId);

    STARTUPINFO si = { 0 };
    si.cb = sizeof(si);
    PROCESS_INFORMATION pi = { 0 };
    BOOL bSuccess = CreateProcessW(
        processPath,
        commandLine,
        NULL,
        NULL,
        FALSE,
        0,
        NULL,
        NULL,
        &si,
        &pi);

    if (!bSuccess) {
        WCHAR buf[256] = { 0 };
        wsprintf(buf, L"CreateProcess failed (%d)", GetLastError());
        MessageBox(NULL, buf, L"", MB_OK);
        return 0;
    }

    CloseHandle(hProcess);

    return pi.dwProcessId;
}
