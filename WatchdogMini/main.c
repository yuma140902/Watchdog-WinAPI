#include "watchdog.h"
#include <windows.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow);
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    const wchar_t CLASS_NAME[] = L"Watchdog Window Class";

    int targetPid = _wtoi(pCmdLine);
    g_dwTargetPID = targetPid;

    // Window Classを登録する
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    // ウィンドウを作る
    HWND hwnd = CreateWindowExW(
        0,
        CLASS_NAME,
        L"Watchdog",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        110,
        80,
        NULL, // parent window
        NULL, // menu
        hInstance, // instance handle
        NULL // application data
    );
    if (!hwnd) {
        // ウィンドウ作成失敗
        return 0;
    }
    HWND label = CreateWindowExW(
        WS_EX_LEFT,
        L"STATIC",
        L"some text",
        WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        0,
        0,
        110,
        80,
        hwnd,
        NULL,
        hInstance,
        NULL);
    if (!label) {
        return 0;
    }

    WCHAR buf[256] = { 0 };
    wsprintf(buf, L"Target: %d", g_dwTargetPID);
    SetWindowTextW(label, buf);

    setupWatchDog(label);

    ShowWindow(hwnd, nCmdShow);

    // メッセージループ
    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
