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
    keyOnList_.clear();
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
    for(auto key : keyOnList_)
    {
        if(key == 0) continue;
        RECT keyRect = pKeyInfo_->GetKeyRect(pKeyInfo_->GetScaleNo(key));
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
        for(auto keyOn : keyOnList_)
        {
            if(pKeyInfo_->GetScaleNo(keyOn) == i)
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

    std::vector<int> tmp;   // キーボード押下キー値リスト
    for(auto keyinfo : keyInfoList)
    {
        if(!keyinfo.isPressed) continue;
        if(keyinfo.keyValue == 0) continue;
        tmp.push_back(keyinfo.keyValue);
    }

    if(tmp.size() != keyOnList_.size())
    {
        flagUpdate_ = true;
    }
    else
    {
        bool check = false;
        int tsize = tmp.size();
        for(int i = 0; i < tsize; ++i)
        {
            if(tmp[i] != keyOnList_[i])
            {
                check = true;
                break;
            }
        }
        flagUpdate_ = check;
    }

    if(flagUpdate_ == true)
    {
        keyOnList_ = tmp;
        // 無効リージョンを生成することでWM_PAINTメッセージのポストを呼び出す
        InvalidateRect(windowInfo_, nullptr, true);
    }
}

} // namespace display