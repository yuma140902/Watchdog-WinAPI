#include "watchdog.h"
#include "window.h"
#include <windows.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    const wchar_t CLASS_NAME[] = L"Watchdog Window Class";
    Watchdog wd = { 0 };
    Window w = { 0 };

    int targetPid = _wtoi(pCmdLine);
    wd.dwTargetPID = targetPid;

    window_init(&w, hInstance);
    window_updateLabel(&w, wd.dwTargetPID);

    watchdog_setup(&wd, w.hLabel);

    window_show(&w, nCmdShow);

    window_messageLoop(&w);

    return 0;
}
