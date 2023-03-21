/// @file timer.h
/// @brief �^�C�}�[
#pragma once
#include <windows.h>

/// @brief �^�C�}�[
///
/// @details timer_setInterval �֐��ŁA��莞�Ԍ�ɓ���̊֐������s���邱�Ƃ��ł���
typedef struct {
    HANDLE hTimerQueue;
} Timer;

/// @brief Timer������������
/// @param[out] t �������m�ۂ��ꂽ Timer
/// @return �����Ȃ�TRUE�A���s�Ȃ�FALSE�B���s�̗��R�� GetLastError() ���Ăׂ΂킩��
BOOL timer_init(OUT Timer* t);

/// @brief �w�莞�Ԍ�ɓ���̊֐������s����B
/// ���̊֐����̂͂����ɕԂ�
///
/// @param t �^�C�}�[
/// @param ms �҂����Ԃ��~���b�P�ʂŎw�肷��
/// @param func ���s����֐�
/// @param lpParam func �ւ̈���
/// @return ���s�Ȃ�FALSE�B���s�̗��R��GetLastError()���Q��
BOOL timer_setInterval(IN Timer* t, DWORD ms, WAITORTIMERCALLBACK func, PVOID lpParam);

