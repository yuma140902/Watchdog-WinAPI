#include "watchdog.h"
#include "alert.h"
#include "timer.h"
#include "window.h"
#include <windows.h>

void watchdog_setup(OUT Watchdog* wd, DWORD dwTargetPID, IN Timer* timer, IN Window* window)
{
    wd->dwTargetPID = dwTargetPID;
    wd->timer = timer;
    wd->window = window;

    BOOL bSuccess = timer_init(wd->timer);
    if (!bSuccess) {
        alert(L"timer_init", GetLastError());
    }

    bSuccess = timer_setInterval(wd->timer, 1000, private_watchdog_timerRoutine, wd);
    if (!bSuccess) {
        alert(L"timer_setInterval", GetLastError());
    }
}

VOID CALLBACK private_watchdog_timerRoutine(PVOID lpParam, BOOLEAN timerOrWaitFired)
{
    Watchdog* wd = (Watchdog*)lpParam;

    if (wd->dwTargetPID == 0 || !watchdog_isProcessAlive(wd->dwTargetPID)) {
        wd->dwTargetPID = watchdog_respawnProcess();
        window_updateLabel(wd->window, wd->dwTargetPID);
    }

    BOOL bSuccess = timer_setInterval(wd->timer, 1000, private_watchdog_timerRoutine, lpParam);
    if (!bSuccess) {
        alert(L"timer_setInterval", GetLastError());
    }
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
        alert(L"CreateProcessW", GetLastError());
        return 0;
    }

    CloseHandle(hProcess);

    return pi.dwProcessId;
}
