#include "timer.h"
#include "watchdog.h"
#include "window.h"
#include <windows.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    const wchar_t CLASS_NAME[] = L"Watchdog Window Class";
    Watchdog wd = { 0 };
    Timer t = { 0 };
    Window w = { 0 };

    window_init(&w, hInstance);

    timer_init(&t);

    watchdog_setup(&wd, _wtoi(pCmdLine), &t, &w);

    window_updateLabel(&w, wd.dwTargetPID);

    window_show(&w, nCmdShow);

    window_messageLoop(&w);

    return 0;
}
