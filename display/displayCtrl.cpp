#include "displayCtrl.h"

#include <iostream>

namespace display
{

//---------------------------------------------------------------
// コンストラクタ
displayCtrl::displayCtrl()
{
    std::cout << "constructor displayCtrl" << std::endl;
    windowInfo = nullptr;
    wWin = 0;
    hWin = 0;
    InitializeRectMap();
}

//---------------------------------------------------------------
// デストラクタ
displayCtrl::~displayCtrl()
{

}

//---------------------------------------------------------------
// ウィンドウ情報設定
void displayCtrl::SetHWinInfo(HWND hw)
{
    std::cout << "set wininfo" << std::endl;
    windowInfo = hw;
}

//---------------------------------------------------------------
// ウィンドウ情報設定
void displayCtrl::UpdateWindowInfo()
{
    std::cout << "called draw window" << std::endl;
    // ウィンドウジオメトリ情報を取得
    RECT rect;
    if(GetWindowRect(windowInfo, &rect))
    {
        std::cout << "set geo" << std::endl;
        if(&rect != nullptr)
        {
            wWin = rect.right - rect.left;
            hWin = rect.bottom - rect.top;
            std::cout << "check w,h:" << wWin << "," << hWin << std::endl;
        }
    }

    std::cout << "draw window0" << std::endl;
    if(windowInfo == nullptr) return;
    if(wWin == 0) return;
    if(hWin == 0) return;

    std::cout << "draw window1" << std::endl;
    HDC hdc;
    PAINTSTRUCT ps;
    HPEN hpen, hpenB;
    HBRUSH hbrushB;

    // ピアノベース画面を描画
    hdc = BeginPaint(windowInfo, &ps);
    hpen = CreatePen(PS_SOLID, 1, 0);
    SelectObject(hdc, hpen);
    // ベース鍵盤
    int imax = 28;
    for(int i = 0; i < imax; ++i)
    {
        // 白鍵
        int xl = i * wWin / imax;
        int xr = (i + 1) * wWin / imax;
        int yt = 0;
        int yb = hWin;
        Rectangle(hdc, xl, yt, xr, yb);
    }
    hpenB = CreatePen(PS_SOLID, 1, 0);
    SelectObject(hdc, hpenB);
    hbrushB = CreateSolidBrush(RGB(0,0,0));
    SelectObject(hdc, hbrushB);
    for(int i = 0; i < imax; ++i)
    {
        if(i % 7 == 2) continue;
        if(i % 7 == 6) continue;
        // 黒鍵
        int xlb = i * wWin / imax + wWin * 0.7 / imax;
        int xrb = (i + 1) * wWin / imax + wWin * 0.3 / imax;
        int ytb = 0;
        int ybb = hWin * 6.0 / 10.0;
        Rectangle(hdc, xlb, ytb, xrb, ybb);
    }
    EndPaint(windowInfo, &ps);
    DeleteObject(hpen);
    DeleteObject(hpenB);
}

//---------------------------------------------------------------
// 鍵盤位置情報マップ初期化
void displayCtrl::InitializeRectMap()
{
    keyRectMap.clear();
}

} // namespace display