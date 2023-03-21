/// @file alert.h
/// @brief エラーダイアログ
#pragma once
#include <windows.h>

/// @brief エラーダイアログを表示する
///
/// @details 「{lpszFeatureName} failed (code: {dwErrorCode})」のような形式で
/// ユーザーにエラーを伝えるダイアログを開く
///
/// @param lpszFeatureName 失敗した機能の名前
/// @param dwErrorCode エラーコード
void alert(LPCWCHAR lpszFeatureName, DWORD dwErrorCode);
