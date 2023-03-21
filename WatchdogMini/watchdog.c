#include "watchdog.h"
#include <windows.h>

void private_setInterval(IN Watchdog *wd, DWORD ms, WAITORTIMERCALLBACK func)
{
    WCHAR buf[256] = { 0 };
    HANDLE hTimer = NULL;
    if (!CreateTimerQueueTimer(&hTimer, wd->hTimerQueue, func, wd, ms, 0, 0)) {
        wsprintf(buf, L"CreateTimerQueueTimer failed (%d)", GetLastError());
        MessageBox(NULL, buf, L"", MB_OK);
        return;
    }
}

void watchdog_setup(OUT Watchdog *wd, HWND hLabel)
{
    WCHAR buf[256] = { 0 };

    wd->hLabel = hLabel;

    wd->hTimerQueue = CreateTimerQueue();
    if (wd->hTimerQueue == NULL) {
        wsprintf(buf, L"CreateTimerQueue failed (%d)", GetLastError());
        MessageBox(NULL, buf, L"", MB_OK);
        return;
    }

    private_setInterval(wd, 1000, watchdog_timerRoutine);
}

VOID CALLBACK watchdog_timerRoutine(PVOID lpParam, BOOLEAN timerOrWaitFired)
{
    Watchdog* wd = (Watchdog*)lpParam;

    if (wd->dwTargetPID == 0 || !watchdog_isProcessAlive(wd->dwTargetPID)) {
        WCHAR buf[256] = { 0 };
        wd->dwTargetPID = watchdog_respawnProcess();
        wsprintf(buf, L"Target: %d", wd->dwTargetPID);
        SetWindowTextW(wd->hLabel, buf);
    }

    private_setInterval(wd, 1000, watchdog_timerRoutine);
}

BOOL watchdog_isProcessAlive(DWORD pid)
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

DWORD watchdog_respawnProcess()
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
