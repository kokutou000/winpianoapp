#include "keyInfo.h"
#include <iostream>

namespace key
{

//---------------------------------------------------------------
// コンストラクタ
keyInfo::keyInfo()
{
    InitializeKeyInfoList();
}

//---------------------------------------------------------------
// デストラクタ
keyInfo::~keyInfo()
{

}

//---------------------------------------------------------------
// キー押下情報設定
void keyInfo::SetKeyPressState(const bool& isPress, const unsigned short& keyNo)
{
    for(auto& key: keyInfoList)
    {
        if(key.keyNo == keyNo)
        {
            key.isPressed = isPress;
        }
    }
}

//---------------------------------------------------------------
// 押下キー情報リスト取得
std::list<keyBase> keyInfo::GetKeyInfoPressed()
{
    const int maxKey = 16;  // チャンネル数の制限
    std::list<keyBase> listRet;
    listRet.clear();

    for(auto key : keyInfoList)
    {
        if(key.isPressed)
        {
            listRet.push_back(key);
            if(listRet.size() >= maxKey) break;
        }
    }
    return listRet;
}


//---------------------------------------------------------------
// キー情報リスト初期化
void keyInfo::InitializeKeyInfoList()
{
    keyInfoList.clear();
    /* キー番号, キーchar, 押下状態, 音階番号, ABC音階名, 画面xywh */
    keyInfoList.push_back({0x5A, "z", false, 0x30, "C3",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x58, "x", false, 0x31, "C3#", {0, 0, 0, 0}});
    keyInfoList.push_back({0x43, "c", false, 0x32, "D3",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x56, "v", false, 0x33, "D3#", {0, 0, 0, 0}});
    keyInfoList.push_back({0x42, "b", false, 0x34, "E3",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x4E, "n", false, 0x35, "F3",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x4D, "m", false, 0x36, "F3#", {0, 0, 0, 0}});
    keyInfoList.push_back({0x41, "a", false, 0x37, "G3",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x53, "s", false, 0x38, "G3#", {0, 0, 0, 0}});
    keyInfoList.push_back({0x44, "d", false, 0x39, "A3",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x46, "f", false, 0x3A, "A3#", {0, 0, 0, 0}});
    keyInfoList.push_back({0x47, "g", false, 0x3B, "B3",  {0, 0, 0, 0}});

    keyInfoList.push_back({0x48, "h", false, 0x3C, "C4",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x4A, "j", false, 0x3D, "C4#", {0, 0, 0, 0}});
    keyInfoList.push_back({0x4B, "k", false, 0x3E, "D4",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x4C, "l", false, 0x3F, "D4#", {0, 0, 0, 0}});
    keyInfoList.push_back({0x51, "q", false, 0x40, "E4",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x57, "w", false, 0x41, "F4",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x45, "e", false, 0x42, "F4#", {0, 0, 0, 0}});
    keyInfoList.push_back({0x52, "r", false, 0x43, "G4",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x54, "t", false, 0x44, "G4#", {0, 0, 0, 0}});
    keyInfoList.push_back({0x59, "y", false, 0x45, "A4",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x55, "u", false, 0x46, "A4#", {0, 0, 0, 0}});
    keyInfoList.push_back({0x49, "i", false, 0x47, "B4",  {0, 0, 0, 0}});

    keyInfoList.push_back({0x4F, "o", false, 0x48, "C5",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x50, "p", false, 0x49, "C5#", {0, 0, 0, 0}});
    keyInfoList.push_back({0x31, "1", false, 0x4A, "D5",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x32, "2", false, 0x4B, "D5#", {0, 0, 0, 0}});
    keyInfoList.push_back({0x33, "3", false, 0x4C, "E5",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x34, "4", false, 0x4D, "F5",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x35, "5", false, 0x4E, "F5#", {0, 0, 0, 0}});
    keyInfoList.push_back({0x36, "6", false, 0x4F, "G5",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x37, "7", false, 0x50, "G5#", {0, 0, 0, 0}});
    keyInfoList.push_back({0x38, "8", false, 0x51, "A5",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x39, "9", false, 0x52, "A5#", {0, 0, 0, 0}});
    keyInfoList.push_back({0x30, "0", false, 0x53, "B5",  {0, 0, 0, 0}});

    keyInfoList.push_back({0x70, "f1",  false, 0x54, "C6",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x71, "f2",  false, 0x55, "C6#", {0, 0, 0, 0}});
    keyInfoList.push_back({0x72, "f3",  false, 0x56, "D6",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x73, "f4",  false, 0x57, "D6#", {0, 0, 0, 0}});
    keyInfoList.push_back({0x74, "f5",  false, 0x58, "E6",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x75, "f6",  false, 0x59, "F6",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x76, "f7",  false, 0x5A, "F6#", {0, 0, 0, 0}});
    keyInfoList.push_back({0x77, "f8",  false, 0x5B, "G6",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x78, "f9",  false, 0x5C, "G6#", {0, 0, 0, 0}});
    keyInfoList.push_back({0x79, "f10", false, 0x5D, "A6",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x7A, "f11", false, 0x5E, "A6#", {0, 0, 0, 0}});
    keyInfoList.push_back({0x7B, "f12", false, 0x5F, "B6",  {0, 0, 0, 0}});
}

} // namespace key