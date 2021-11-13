#include "keyCtrl.h"
#include <iostream>

namespace key
{

//---------------------------------------------------------------
// コンストラクタ
keyCtrl::keyCtrl()
{
    std::cout << "constructor keyCtrl" << std::endl;
    InitializeKeyStateMap();
}

//---------------------------------------------------------------
// デストラクタ
keyCtrl::~keyCtrl()
{

}

//---------------------------------------------------------------
// キー押下イベント
// [in1]unsigned int: イベント元キー
void keyCtrl:: EventKeyDown(WPARAM wp)
{
    //std::cout << "keydown:" << wp <<  std::endl;
    
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
    //std::cout << "keyup:" <<  wp << std::endl;

    // 離したキーをOFF状態にする
    UpdateKeyState(wp, false);
}

//---------------------------------------------------------------
// 押下キーリスト取得
// MIDIのチャンネル数制限から、最大16個までとする
std::list<int> keyCtrl::GetListKeyON()
{
    const int maxKey = 16;
    std::list<int> listkeyOn;
    for(auto item : keyState)
    {
        if(item.second == true)
        {
            listkeyOn.push_back(item.first);
            if(listkeyOn.size() >= maxKey) break;
        }
    }
    return listkeyOn;
}

//---------------------------------------------------------------
// キー状態更新
void keyCtrl::UpdateKeyState(WPARAM wp, bool state)
{
    try
    {
        keyState.at(wp) = state;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

//---------------------------------------------------------------
// キー状態マップ初期化
void keyCtrl::InitializeKeyStateMap()
{
    keyState.insert(std::make_pair(0x5A, false)); // z
    keyState.insert(std::make_pair(0x58, false)); // x
    keyState.insert(std::make_pair(0x43, false)); // c
    keyState.insert(std::make_pair(0x56, false)); // v
    keyState.insert(std::make_pair(0x42, false)); // b
    keyState.insert(std::make_pair(0x4E, false)); // n
    keyState.insert(std::make_pair(0x4D, false)); // m
    keyState.insert(std::make_pair(0x41, false)); // a
    keyState.insert(std::make_pair(0x53, false)); // s
    keyState.insert(std::make_pair(0x44, false)); // d
    keyState.insert(std::make_pair(0x46, false)); // f
    keyState.insert(std::make_pair(0x47, false)); // g
    keyState.insert(std::make_pair(0x48, false)); // h
    keyState.insert(std::make_pair(0x4A, false)); // j
    keyState.insert(std::make_pair(0x4B, false)); // k
    keyState.insert(std::make_pair(0x4C, false)); // l
    keyState.insert(std::make_pair(0x51, false)); // q
    keyState.insert(std::make_pair(0x57, false)); // w
    keyState.insert(std::make_pair(0x45, false)); // e
    keyState.insert(std::make_pair(0x52, false)); // r
    keyState.insert(std::make_pair(0x54, false)); // t
    keyState.insert(std::make_pair(0x59, false)); // y
    keyState.insert(std::make_pair(0x55, false)); // u
    keyState.insert(std::make_pair(0x49, false)); // i
    keyState.insert(std::make_pair(0x4F, false)); // o
    keyState.insert(std::make_pair(0x50, false)); // p

    keyState.insert(std::make_pair(0x31, false)); // 1
    keyState.insert(std::make_pair(0x32, false)); // 2
    keyState.insert(std::make_pair(0x33, false)); // 3
    keyState.insert(std::make_pair(0x34, false)); // 4
    keyState.insert(std::make_pair(0x35, false)); // 5
    keyState.insert(std::make_pair(0x36, false)); // 6
    keyState.insert(std::make_pair(0x37, false)); // 7
    keyState.insert(std::make_pair(0x38, false)); // 8
    keyState.insert(std::make_pair(0x39, false)); // 9
    keyState.insert(std::make_pair(0x30, false)); // 0
}

} // namespace key