/// @file alert.h
/// @brief �G���[�_�C�A���O
#pragma once
#include <windows.h>

/// @brief �G���[�_�C�A���O��\������
///
/// @details �u{lpszFeatureName} failed (code: {dwErrorCode})�v�̂悤�Ȍ`����
/// ���[�U�[�ɃG���[��`����_�C�A���O���J��
///
/// @param lpszFeatureName ���s�����@�\�̖��O
/// @param dwErrorCode �G���[�R�[�h
void alert(LPCWCHAR lpszFeatureName, DWORD dwErrorCode);
