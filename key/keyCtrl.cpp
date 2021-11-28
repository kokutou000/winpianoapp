#include "keyCtrl.h"
#include <iostream>

namespace key
{

//---------------------------------------------------------------
// コンストラクタ
keyCtrl::keyCtrl()
{

}

//---------------------------------------------------------------
// デストラクタ
keyCtrl::~keyCtrl()
{

}

//---------------------------------------------------------------
// キー情報設定
void keyCtrl::SetKeyInfo(key::keyInfo* pkinfo)
{
    pKeyInfo = pkinfo;
}

//---------------------------------------------------------------
// キー押下イベント
// [in1]unsigned int: イベント元キー
void keyCtrl:: EventKeyDown(WPARAM wp)
{    
    // ESC押下時は終了を投げる
    if(wp == VK_ESCAPE)
    {
        std::cout << "end program." << std::endl;
        PostQuitMessage(0);
    }

    // 押下キーをON状態にする
    UpdateKeyState(wp, true);
}

//---------------------------------------------------------------
// キーアップイベント
// [in1]unsigned int: イベント元キー
void keyCtrl::EventKeyUp(WPARAM wp)
{
    // 離したキーをOFF状態にする
    UpdateKeyState(wp, false);
}

//---------------------------------------------------------------
// キー状態更新
// [in1]unsigned int: イベント元キー
// [in2]bool: press/release
void keyCtrl::UpdateKeyState(WPARAM wp, bool state)
{
    pKeyInfo->SetKeyPressState(state, wp);
}

} // namespace key