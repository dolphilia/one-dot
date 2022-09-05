//必要なヘッダーファイルのインクルード
#define STRICT
#include <windows.h>
#include <tchar.h>

//--------------------------------------------
// Name:WinMain()
// Desc:アプリケーションのエントリー関数
//--------------------------------------------
INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR szStr, INT iCmdShow)
{
    MessageBox(NULL, _T(""), _T(""), MB_OK);

    return 0;
}