/// @file window.h
/// @brief ウィンドウに関するもの
#pragma once
#include <windows.h>

/// @brief ウィンドウ
typedef struct {
    /// @brief ウィンドウのハンドル
    HWND hWnd;
    /// @brief ウィンドウ内のラベルへのハンドル
    HWND hLabel;
} Window;

/// @brief ウィンドウを初期化する
/// @details ウィンドウクラスを登録し、ウィンドウを作成する。
/// @param w メモリ確保されたWindow
/// @param hInstance WinMainに渡されたhInstance
/// @return 失敗ならFALSE。失敗の理由はGetLastError()を参照
BOOL window_init(OUT Window* w, HINSTANCE hInstance);

/// @brief ラベルの文字列を更新する
/// @param w Window
/// @param dwTargetPID 監視対象のPID
/// @return 失敗ならFALSE。失敗の理由はGetLastError()を参照
BOOL window_updateLabel(IN Window* w, DWORD dwTargetPID);

/// @brief ウィンドウを表示する
/// @param w Window
/// @param nCmdShow WinMainに渡されたnCmdShow
/// @return 失敗ならFALSE。失敗の理由はGetLastError()を参照
BOOL window_show(IN Window* w, DWORD nCmdShow);

/// @brief ウィンドウのメッセージループを処理する。
/// ウィンドウが閉じられるまで返らない
/// @param w Window
void window_messageLoop(IN Window* w);

LRESULT CALLBACK private_window_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
