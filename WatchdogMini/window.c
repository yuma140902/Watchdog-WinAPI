#include "window.h"
#include <windows.h>

BOOL window_init(OUT Window* w, HINSTANCE hInstance)
{
    LPCWCHAR CLASS_NAME = L"Watchdog Window Class";

    // Window Classの登録
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = private_window_proc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    // ウィンドウを作る
    w->hWnd = CreateWindowExW(
        0,
        CLASS_NAME,
        L"Watchdog",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        110,
        80,
        NULL,
        NULL,
        hInstance,
        NULL);
    if (!w->hWnd) {
        // ウィンドウ作成失敗
        return FALSE;
    }

    // ラベル
    w->hLabel = CreateWindowExW(
        WS_EX_LEFT,
        L"STATIC",
        L"some text",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        0,
        0,
        110,
        80,
        w->hWnd,
        NULL,
        hInstance,
        NULL);
    if (!w->hLabel) {
        // ラベル作成失敗
        return FALSE;
    }

    return TRUE;
}

BOOL window_updateLabel(IN Window* w, DWORD dwTargetPID)
{
    WCHAR buf[256] = { 0 };
    wsprintf(buf, L"Target: %d", dwTargetPID);
    return SetWindowTextW(w->hLabel, buf);
}

BOOL window_show(IN Window* w, DWORD nCmdShow)
{
    return ShowWindow(w->hWnd, nCmdShow);
}

void window_messageLoop(IN Window* w)
{
    MSG msg = { 0 };
    while (GetMessageW(&msg, w->hWnd, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

LRESULT CALLBACK private_window_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        EndPaint(hwnd, &ps);
    }
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
