/// @file timer.h
/// @brief タイマー
#pragma once
#include <windows.h>

/// @brief タイマー
///
/// @details timer_setInterval 関数で、一定時間後に特定の関数を実行することができる
typedef struct {
    HANDLE hTimerQueue;
} Timer;

/// @brief Timerを初期化する
/// @param[out] t メモリ確保された Timer
/// @return 成功ならTRUE、失敗ならFALSE。失敗の理由は GetLastError() を呼べばわかる
BOOL timer_init(OUT Timer* t);

/// @brief 指定時間後に特定の関数を実行する。
/// この関数自体はすぐに返る
///
/// @param t タイマー
/// @param ms 待ち時間をミリ秒単位で指定する
/// @param func 実行する関数
/// @param lpParam func への引数
/// @return 失敗ならFALSE。失敗の理由はGetLastError()を参照
BOOL timer_setInterval(IN Timer* t, DWORD ms, WAITORTIMERCALLBACK func, PVOID lpParam);

