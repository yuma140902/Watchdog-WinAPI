/// @file watchdog.h
/// @brief Watchdog
#pragma once
#include "timer.h"
#include "window.h"
#include <windows.h>

/// @brief Watchdog
typedef struct {
    /// @brief 監視対象のPID
    DWORD dwTargetPID;
    /// @brief タイマー
    Timer* timer;
    /// @brief ウィンドウ
    Window* window;
} Watchdog;

/// @brief Watchdog を初期化する
/// @param wd メモリ確保されたWatchdog
/// @param dwTargetPID 監視対象のPID
/// @param timer タイマー
/// @param window ウィンドウ
void watchdog_setup(OUT Watchdog* wd, DWORD dwTargetPID, IN Timer* timer, IN Window* window);

/// @brief 一定時間ごとに呼び出される関数
/// @param lpParam Watchdogへのポインタ
/// @param timerOrWaitFired 
VOID CALLBACK private_watchdog_timerRoutine(PVOID lpParam, BOOLEAN timerOrWaitFired);

/// @brief プロセスが生きているかどうか確認する
/// @param pid 対象のPID
/// @return 生きているなら TRUE、死んでいる・存在しない・エラーなら FALSE
BOOL watchdog_isProcessAlive(DWORD pid);

/// @brief 自分の複製のプロセスを作る
/// @return 新しいプロセスのPID。失敗なら0
DWORD watchdog_respawnProcess();

