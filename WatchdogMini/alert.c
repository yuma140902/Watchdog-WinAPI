#include <windows.h>

void alert(LPCWCHAR lpszFeatureName, DWORD dwErrorCode)
{
    WCHAR buf[256] = { 0 };
    wsprintf(buf, L"%s failed (code: %d)", lpszFeatureName, dwErrorCode);
    MessageBoxW(NULL, buf, L"Error", MB_OK);
}