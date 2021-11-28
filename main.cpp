#include <windows.h>
#include <chrono>
#include <list>

#include "display/displayCtrl.h"
#include "key/keyCtrl.h"
#include "key/keyInfo.h"
#include "melody/melodyCtrl.h"

static display::displayCtrl dCtrl = display::displayCtrl();
static key::keyCtrl         kCtrl = key::keyCtrl();
static key::keyInfo         kInfo = key::keyInfo();
static melody::melodyCtrl   mCtrl = melody::melodyCtrl();

/*****************************************************
 * windowプロシージャ
*******************************************************/
LRESULT CALLBACK WndProcMain(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch(msg) 
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_KEYDOWN:    // キープレス時
            kCtrl.EventKeyDown(wp);
            return 0;
        case WM_KEYUP:      // キーリリース時
            kCtrl.EventKeyUp(wp);
            return 0;
        case WM_PAINT:      // システムによるウィンドウ描画時
            dCtrl.UpdateWindowInfo();
            return 0;
    }
    return DefWindowProc(hwnd, msg, wp, lp);
}

/***********************************************
 * windows 画面アプリメイン
 * [in1]instance handle
 * [in2]使用しない
 * [in3]コマンドライン引数
 ***********************************************/
int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int CmdShow)
{
    // ウィンドウクラス定義
    WNDCLASS wincls;
    wincls.style = CS_HREDRAW | CS_VREDRAW;
    //wincls.lpfnWndProc = DefWindowProc;
    wincls.lpfnWndProc = WndProcMain;
    wincls.cbClsExtra = 0;
    wincls.cbWndExtra = 0;
    wincls.hInstance = hInstance;
    //wincls.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wincls.hIcon = nullptr;
    //wincls.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wincls.hCursor = nullptr;
    wincls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wincls.lpszMenuName = nullptr;
    wincls.lpszClassName = TEXT("MAINPROC");

    if(!RegisterClass(&wincls)) return -1;

    // ウィンドウ生成
    HWND hwnd = CreateWindow(
        // ウィンドウクラス名, ウィンドウ名
        TEXT("MAINPROC"), TEXT("test"),
        //TEXT("BUTTON"), TEXT("test"),
        // window style
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        // x, y, w, h
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        // parent , menu
        NULL, NULL,
        hInstance, NULL);
    if(hwnd == NULL) return -1;

    dCtrl.SetHWinInfo(hwnd);

    dCtrl.SetKeyInfo(&kInfo);
    kCtrl.SetKeyInfo(&kInfo);
    mCtrl.SetKeyInfo(&kInfo);


    // ウィンドウを表示
    //ShowWindow(hwnd, SW_SHOW);
    //Sleep(1000);
    //MessageBox(nullptr, TEXT("test"), TEXT("messagebox"), MB_OK | MB_ICONINFORMATION);

    // メイン処理ループ
    MSG msg;
    while(GetMessage(&msg, NULL, 0, 0))
    {
        DispatchMessage(&msg);

        mCtrl.Update();
        dCtrl.Update();
    }

    return msg.wParam;
}