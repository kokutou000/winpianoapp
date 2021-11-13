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
    InitializeKeyMap();
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
    int cnt = keyKeyMap.size();
    for(int i = 1; i < cnt + 1; ++i)
    {
        RECT tmp = {0,0,0,0};
        keyRectMap.insert(std::make_pair(i,tmp));
    }
}

//---------------------------------------------------------------
// キーvs鍵盤マップ初期化
void displayCtrl::InitializeKeyMap()
{
    keyKeyMap.clear();
    keyKeyMap.insert(std::make_pair(0x5A, 1)); // z, 
    keyKeyMap.insert(std::make_pair(0x58, 2)); // x, 
    keyKeyMap.insert(std::make_pair(0x43, 3)); // c, 
    keyKeyMap.insert(std::make_pair(0x56, 4)); // v, 
    keyKeyMap.insert(std::make_pair(0x42, 5)); // b, 
    keyKeyMap.insert(std::make_pair(0x4E, 6)); // n, 
    keyKeyMap.insert(std::make_pair(0x4D, 7)); // m, 
    keyKeyMap.insert(std::make_pair(0x41, 8)); // a, 
    keyKeyMap.insert(std::make_pair(0x53, 9)); // s, 
    keyKeyMap.insert(std::make_pair(0x44, 10)); // d, 
    keyKeyMap.insert(std::make_pair(0x46, 11)); // f, 
    keyKeyMap.insert(std::make_pair(0x47, 12)); // g, 
    keyKeyMap.insert(std::make_pair(0x48, 13)); // h, 
    keyKeyMap.insert(std::make_pair(0x4A, 14)); // j, 
    keyKeyMap.insert(std::make_pair(0x4B, 15)); // k, 
    keyKeyMap.insert(std::make_pair(0x4C, 16)); // l, 
    keyKeyMap.insert(std::make_pair(0x51, 17)); // q, 
    keyKeyMap.insert(std::make_pair(0x57, 18)); // w, 
    keyKeyMap.insert(std::make_pair(0x45, 19)); // e, 
    keyKeyMap.insert(std::make_pair(0x52, 20)); // r, 
    keyKeyMap.insert(std::make_pair(0x54, 21)); // t, 
    keyKeyMap.insert(std::make_pair(0x59, 22)); // y, 
    keyKeyMap.insert(std::make_pair(0x55, 23)); // u, 
    keyKeyMap.insert(std::make_pair(0x49, 24)); // i, 
    keyKeyMap.insert(std::make_pair(0x4F, 25)); // o, 
    keyKeyMap.insert(std::make_pair(0x50, 26)); // p, 

    keyKeyMap.insert(std::make_pair(0x31, 27)); // 1, 
    keyKeyMap.insert(std::make_pair(0x32, 28)); // 2, 
    keyKeyMap.insert(std::make_pair(0x33, 29)); // 3, 
    keyKeyMap.insert(std::make_pair(0x34, 30)); // 4, 
    keyKeyMap.insert(std::make_pair(0x35, 31)); // 5, 
    keyKeyMap.insert(std::make_pair(0x36, 32)); // 6, 
    keyKeyMap.insert(std::make_pair(0x37, 33)); // 7, 
    keyKeyMap.insert(std::make_pair(0x38, 34)); // 8, 
    keyKeyMap.insert(std::make_pair(0x39, 35)); // 9, 
    keyKeyMap.insert(std::make_pair(0x30, 36)); // 0, 
}

} // namespace display