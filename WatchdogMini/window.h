/// @file window.h
/// @brief �E�B���h�E�Ɋւ������
#pragma once
#include <windows.h>

/// @brief �E�B���h�E
typedef struct {
    /// @brief �E�B���h�E�̃n���h��
    HWND hWnd;
    /// @brief �E�B���h�E���̃��x���ւ̃n���h��
    HWND hLabel;
} Window;

/// @brief �E�B���h�E������������
/// @details �E�B���h�E�N���X��o�^���A�E�B���h�E���쐬����B
/// @param w �������m�ۂ��ꂽWindow
/// @param hInstance WinMain�ɓn���ꂽhInstance
/// @return ���s�Ȃ�FALSE�B���s�̗��R��GetLastError()���Q��
BOOL window_init(OUT Window* w, HINSTANCE hInstance);

/// @brief ���x���̕�������X�V����
/// @param w Window
/// @param dwTargetPID �Ď��Ώۂ�PID
/// @return ���s�Ȃ�FALSE�B���s�̗��R��GetLastError()���Q��
BOOL window_updateLabel(IN Window* w, DWORD dwTargetPID);

/// @brief �E�B���h�E��\������
/// @param w Window
/// @param nCmdShow WinMain�ɓn���ꂽnCmdShow
/// @return ���s�Ȃ�FALSE�B���s�̗��R��GetLastError()���Q��
BOOL window_show(IN Window* w, DWORD nCmdShow);

/// @brief �E�B���h�E�̃��b�Z�[�W���[�v����������B
/// �E�B���h�E��������܂ŕԂ�Ȃ�
/// @param w Window
void window_messageLoop(IN Window* w);

LRESULT CALLBACK private_window_proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
