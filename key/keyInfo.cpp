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
        if(key.keyValue == keyNo)
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
// 押下キー情報リスト取得
int keyInfo::GetScaleNo(const unsigned short& keyNo)
{
    for(auto key : keyInfoList)
    {
        if(key.keyValue == keyNo) return key.scaleValue;
    }
    return 0;
}

//---------------------------------------------------------------
// キー情報リスト初期化
void keyInfo::InitializeKeyInfoList()
{
    keyInfoList.clear();
    /* キーボード対応値, キーボード対応名, 押下状態, 鍵盤番号, 音階値, ABC音階名, 画面xywh */
    keyInfoList.push_back({0x5A, "z", false, 0, 0x30, "C3",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x58, "x", false, 1, 0x31, "C3#", {0, 0, 0, 0}});
    keyInfoList.push_back({0x43, "c", false, 2, 0x32, "D3",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x56, "v", false, 3, 0x33, "D3#", {0, 0, 0, 0}});
    keyInfoList.push_back({0x42, "b", false, 4, 0x34, "E3",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x4E, "n", false, 5, 0x35, "F3",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x4D, "m", false, 6, 0x36, "F3#", {0, 0, 0, 0}});
    keyInfoList.push_back({0x41, "a", false, 7, 0x37, "G3",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x53, "s", false, 8, 0x38, "G3#", {0, 0, 0, 0}});
    keyInfoList.push_back({0x44, "d", false, 9, 0x39, "A3",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x46, "f", false, 10, 0x3A, "A3#", {0, 0, 0, 0}});
    keyInfoList.push_back({0x47, "g", false, 11, 0x3B, "B3",  {0, 0, 0, 0}});

    keyInfoList.push_back({0x48, "h", false, 12, 0x3C, "C4",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x4A, "j", false, 13, 0x3D, "C4#", {0, 0, 0, 0}});
    keyInfoList.push_back({0x4B, "k", false, 14, 0x3E, "D4",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x4C, "l", false, 15, 0x3F, "D4#", {0, 0, 0, 0}});
    keyInfoList.push_back({0x51, "q", false, 16, 0x40, "E4",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x57, "w", false, 17, 0x41, "F4",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x45, "e", false, 18, 0x42, "F4#", {0, 0, 0, 0}});
    keyInfoList.push_back({0x52, "r", false, 19, 0x43, "G4",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x54, "t", false, 20, 0x44, "G4#", {0, 0, 0, 0}});
    keyInfoList.push_back({0x59, "y", false, 21, 0x45, "A4",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x55, "u", false, 22, 0x46, "A4#", {0, 0, 0, 0}});
    keyInfoList.push_back({0x49, "i", false, 23, 0x47, "B4",  {0, 0, 0, 0}});

    keyInfoList.push_back({0x4F, "o", false, 24, 0x48, "C5",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x50, "p", false, 25, 0x49, "C5#", {0, 0, 0, 0}});
    keyInfoList.push_back({0x31, "1", false, 26, 0x4A, "D5",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x32, "2", false, 27, 0x4B, "D5#", {0, 0, 0, 0}});
    keyInfoList.push_back({0x33, "3", false, 28, 0x4C, "E5",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x34, "4", false, 29, 0x4D, "F5",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x35, "5", false, 30, 0x4E, "F5#", {0, 0, 0, 0}});
    keyInfoList.push_back({0x36, "6", false, 31, 0x4F, "G5",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x37, "7", false, 32, 0x50, "G5#", {0, 0, 0, 0}});
    keyInfoList.push_back({0x38, "8", false, 33, 0x51, "A5",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x39, "9", false, 34, 0x52, "A5#", {0, 0, 0, 0}});
    keyInfoList.push_back({0x30, "0", false, 35, 0x53, "B5",  {0, 0, 0, 0}});

    keyInfoList.push_back({0x70, "f1",  false, 36, 0x54, "C6",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x71, "f2",  false, 37, 0x55, "C6#", {0, 0, 0, 0}});
    keyInfoList.push_back({0x72, "f3",  false, 38, 0x56, "D6",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x73, "f4",  false, 39, 0x57, "D6#", {0, 0, 0, 0}});
    keyInfoList.push_back({0x74, "f5",  false, 40, 0x58, "E6",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x75, "f6",  false, 41, 0x59, "F6",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x76, "f7",  false, 42, 0x5A, "F6#", {0, 0, 0, 0}});
    keyInfoList.push_back({0x77, "f8",  false, 43, 0x5B, "G6",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x78, "f9",  false, 44, 0x5C, "G6#", {0, 0, 0, 0}});
    keyInfoList.push_back({0x79, "f10", false, 45, 0x5D, "A6",  {0, 0, 0, 0}});
    keyInfoList.push_back({0x7A, "f11", false, 46, 0x5E, "A6#", {0, 0, 0, 0}});
    keyInfoList.push_back({0x7B, "f12", false, 47, 0x5F, "B6",  {0, 0, 0, 0}});
}

} // namespace key