#include "timer.h"
#include <windows.h>

BOOL timer_init(OUT Timer* t)
{
    t->hTimerQueue = CreateTimerQueue();
    return t->hTimerQueue != NULL;
}

BOOL timer_setInterval(IN Timer* t, DWORD ms, WAITORTIMERCALLBACK func, PVOID lpParam)
{
    HANDLE hTimer = NULL;
    return CreateTimerQueueTimer(&hTimer, t->hTimerQueue, func, lpParam, ms, 0, 0);
}