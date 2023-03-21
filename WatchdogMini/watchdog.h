/// @file watchdog.h
/// @brief Watchdog
#pragma once
#include "timer.h"
#include "window.h"
#include <windows.h>

/// @brief Watchdog
typedef struct {
    /// @brief �Ď��Ώۂ�PID
    DWORD dwTargetPID;
    /// @brief �^�C�}�[
    Timer* timer;
    /// @brief �E�B���h�E
    Window* window;
} Watchdog;

/// @brief Watchdog ������������
/// @param wd �������m�ۂ��ꂽWatchdog
/// @param dwTargetPID �Ď��Ώۂ�PID
/// @param timer �^�C�}�[
/// @param window �E�B���h�E
void watchdog_setup(OUT Watchdog* wd, DWORD dwTargetPID, IN Timer* timer, IN Window* window);

/// @brief ��莞�Ԃ��ƂɌĂяo�����֐�
/// @param lpParam Watchdog�ւ̃|�C���^
/// @param timerOrWaitFired 
VOID CALLBACK private_watchdog_timerRoutine(PVOID lpParam, BOOLEAN timerOrWaitFired);

/// @brief �v���Z�X�������Ă��邩�ǂ����m�F����
/// @param pid �Ώۂ�PID
/// @return �����Ă���Ȃ� TRUE�A����ł���E���݂��Ȃ��E�G���[�Ȃ� FALSE
BOOL watchdog_isProcessAlive(DWORD pid);

/// @brief �����̕����̃v���Z�X�����
/// @return �V�����v���Z�X��PID�B���s�Ȃ�0
DWORD watchdog_respawnProcess();

