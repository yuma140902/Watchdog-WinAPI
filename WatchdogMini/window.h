#pragma once
#include <windows.h>

typedef struct {
    HWND hWnd;
    HWND hLabel;
} Window;

BOOL window_init(OUT Window* w, HINSTANCE hInstance);
BOOL window_updateLabel(IN Window* w, DWORD dwTargetPID);
BOOL window_show(IN Window* w, DWORD nCmdShow);
void window_messageLoop(IN Window* w);

LRESULT CALLBACK private_window_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
