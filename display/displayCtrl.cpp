#include "displayCtrl.h"

#include <iostream>

static constexpr int PIANOKEYBOARDNUMALL  = 56;
static constexpr int PIANOKEYBOARDNUMHALF = 28;
static constexpr int PIANOOCTAVENO = 8;

namespace display
{

//---------------------------------------------------------------
// コンストラクタ
displayCtrl::displayCtrl()
{
    std::cout << "constructor displayCtrl" << std::endl;
    windowInfo_ = nullptr;
    wWin_ = 0;
    hWin_ = 0;
    flagUpdate_ = true;
    pianoKeyOnList_.clear();

    InitializeKeyMap();
}

//---------------------------------------------------------------
// デストラクタ
displayCtrl::~displayCtrl()
{

}

//---------------------------------------------------------------
// キー情報設定
void displayCtrl::SetKeyInfo(key::keyInfo* pkinfo)
{
    pKeyInfo_ = pkinfo;
}

//---------------------------------------------------------------
// ウィンドウ情報設定
void displayCtrl::SetHWinInfo(HWND hw)
{
    std::cout << "set wininfo" << std::endl;
    windowInfo_ = hw;
}

//---------------------------------------------------------------
// ウィンドウ情報設定
void displayCtrl::UpdateWindowInfo()
{
    std::cout << "called UpdateWindowInfo" << std::endl;
    // ウィンドウジオメトリ情報を取得
    RECT rect;
    if(GetWindowRect(windowInfo_, &rect))
    {
        std::cout << "set geo" << std::endl;
        if(&rect != nullptr)
        {
            wWin_ = rect.right - rect.left;
            hWin_ = rect.bottom - rect.top;
            std::cout << "check w,h:" << wWin_ << "," << hWin_ << std::endl;
        }
    }

    if(windowInfo_ == nullptr) return;
    if(wWin_ == 0) return;
    if(hWin_ == 0) return;
    std::cout << "UpdateWindowInfo" << std::endl;

    // 今の画面サイズを元に各キーに対応する鍵盤の座標を計算
    for(int i = 0; i < PIANOKEYBOARDNUMHALF; ++i)
    {
        // 白鍵
        int xwl = i * wWin_ / PIANOKEYBOARDNUMHALF;
        int xwr = (i + 1) * wWin_ / PIANOKEYBOARDNUMHALF;
        int ywt = 0;
        int ywb = hWin_;
        RECT rWhite = {xwl, ywt, xwr, ywb};

        // 黒鍵
        int xbl = i * wWin_ / PIANOKEYBOARDNUMHALF + wWin_ * 0.7 / PIANOKEYBOARDNUMHALF;
        int xbr = (i + 1) * wWin_ / PIANOKEYBOARDNUMHALF + wWin_ * 0.3 / PIANOKEYBOARDNUMHALF;
        int ybt = 0;
        int ybb = hWin_ * 6.0 / 10.0;
        RECT rBlack = {xbl, ybt, xbr, ybb};

        pKeyInfo_->SetKeyRect(rWhite, 2*i);
        pKeyInfo_->SetKeyRect(rBlack, 2*i+1);
    }

    DrawWindow();
}

//---------------------------------------------------------------
// ウィンドウ描画更新
void displayCtrl::DrawWindow()
{
    std::cout << "draw window1" << std::endl;
    HDC hdc;
    PAINTSTRUCT ps;
    HPEN hpen;
    HBRUSH hbrushB, hbrushY;

    // ピアノ鍵盤画面を描画
    hdc = BeginPaint(windowInfo_, &ps);
    hpen = CreatePen(PS_SOLID, 1, 0);
    hbrushB = CreateSolidBrush(RGB(0,0,0));
    hbrushY = CreateSolidBrush(RGB(224,224,0));

    SelectObject(hdc, hpen);

    // ベース鍵盤
    for(int i = 0; i < PIANOKEYBOARDNUMALL; i = i+2)
    {
        // 白鍵
        RECT rw = pKeyInfo_->GetKeyRect(i);
        Rectangle(hdc, rw.left, rw.top, rw.right, rw.bottom);
    }

    // 押下鍵盤
    SelectObject(hdc, hbrushY);
    for(auto key : pianoKeyOnList_)
    {
        if(key == 0) continue;
        RECT keyRect = pKeyInfo_->GetKeyRect(key);
        Rectangle(hdc, keyRect.left, keyRect.top, keyRect.right, keyRect.bottom);
    }

    // 黒鍵盤
    SelectObject(hdc, hbrushB);
    for(int i = 1; i < PIANOKEYBOARDNUMALL; i = i+2)
    {
        // スキップ対象
        if((i-1)/2 % (PIANOOCTAVENO-1) == 2) continue;
        if((i-1)/2 % (PIANOOCTAVENO-1) == 6) continue;
        // 押下鍵盤に含まれているものはスキップ
        bool isPressed = false;
        for(auto keyOn : pianoKeyOnList_)
        {
            if(keyOn == i)
            {
                isPressed = true;
                break;
            }
        }
        if(isPressed) continue;

        // 黒鍵
        RECT rb = pKeyInfo_->GetKeyRect(i);
        Rectangle(hdc, rb.left, rb.top, rb.right, rb.bottom);
    }
    
    EndPaint(windowInfo_, &ps);
    
    DeleteObject(hpen);
    DeleteObject(hbrushB);
    DeleteObject(hbrushY);
}

//---------------------------------------------------------------
// キー押下情報設定
void displayCtrl::Update()
{
    auto keyInfoList = pKeyInfo_->GetKeyInfoPressed();

    std::vector<int> tmp;
    for(auto keyinfo : keyInfoList)
    {
        if(!keyinfo.isPressed) continue;
        int keypiano = keyKeyMap_[keyinfo.keyValue];
        if(keypiano == 0) continue;
        tmp.push_back(keypiano);
    }

    if(tmp.size() != pianoKeyOnList_.size())
    {
        flagUpdate_ = true;
    }
    else
    {
        bool check = false;
        int tsize = tmp.size();
        for(int i = 0; i < tsize; ++i)
        {
            if(tmp[i] != pianoKeyOnList_[i])
            {
                check = true;
                break;
            }
        }
        flagUpdate_ = check;
    }

    if(flagUpdate_ == true)
    {
        pianoKeyOnList_ = tmp;
        // 無効リージョンを生成することでWM_PAINTメッセージのポストを呼び出す
        InvalidateRect(windowInfo_, nullptr, true);
    }
}

//---------------------------------------------------------------
// キーvs鍵盤マップ初期化
void displayCtrl::InitializeKeyMap()
{
    keyKeyMap_.clear();
    keyKeyMap_.insert(std::make_pair(0x5A, 1)); // z, 
    keyKeyMap_.insert(std::make_pair(0x58, 2)); // x, 
    keyKeyMap_.insert(std::make_pair(0x43, 3)); // c, 
    keyKeyMap_.insert(std::make_pair(0x56, 4)); // v, 
    keyKeyMap_.insert(std::make_pair(0x42, 6)); // b, 
    keyKeyMap_.insert(std::make_pair(0x4E, 7)); // n, 
    keyKeyMap_.insert(std::make_pair(0x4D, 8)); // m, 
    keyKeyMap_.insert(std::make_pair(0x41, 9)); // a, 
    keyKeyMap_.insert(std::make_pair(0x53, 10)); // s, 
    keyKeyMap_.insert(std::make_pair(0x44, 11)); // d, 
    keyKeyMap_.insert(std::make_pair(0x46, 12)); // f, 
    keyKeyMap_.insert(std::make_pair(0x47, 14)); // g, 
    keyKeyMap_.insert(std::make_pair(0x48, 15)); // h, 
    keyKeyMap_.insert(std::make_pair(0x4A, 16)); // j, 
    keyKeyMap_.insert(std::make_pair(0x4B, 17)); // k, 
    keyKeyMap_.insert(std::make_pair(0x4C, 18)); // l, 
    keyKeyMap_.insert(std::make_pair(0x51, 20)); // q, 
    keyKeyMap_.insert(std::make_pair(0x57, 21)); // w, 
    keyKeyMap_.insert(std::make_pair(0x45, 22)); // e, 
    keyKeyMap_.insert(std::make_pair(0x52, 23)); // r, 
    keyKeyMap_.insert(std::make_pair(0x54, 24)); // t, 
    keyKeyMap_.insert(std::make_pair(0x59, 25)); // y, 
    keyKeyMap_.insert(std::make_pair(0x55, 26)); // u, 
    keyKeyMap_.insert(std::make_pair(0x49, 28)); // i, 
    keyKeyMap_.insert(std::make_pair(0x4F, 29)); // o, 
    keyKeyMap_.insert(std::make_pair(0x50, 30)); // p, 

    keyKeyMap_.insert(std::make_pair(0x31, 31)); // 1, 
    keyKeyMap_.insert(std::make_pair(0x32, 32)); // 2, 
    keyKeyMap_.insert(std::make_pair(0x33, 34)); // 3, 
    keyKeyMap_.insert(std::make_pair(0x34, 35)); // 4, 
    keyKeyMap_.insert(std::make_pair(0x35, 36)); // 5, 
    keyKeyMap_.insert(std::make_pair(0x36, 37)); // 6, 
    keyKeyMap_.insert(std::make_pair(0x37, 38)); // 7, 
    keyKeyMap_.insert(std::make_pair(0x38, 39)); // 8, 
    keyKeyMap_.insert(std::make_pair(0x39, 40)); // 9, 
    keyKeyMap_.insert(std::make_pair(0x30, 42)); // 0, 
}

} // namespace display