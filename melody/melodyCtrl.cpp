#include "melodyCtrl.h"

#include <iostream>

namespace melody
{

//---------------------------------------------------------------
// コンストラクタ
melodyCtrl::melodyCtrl()
{
    InitializeChannelMap();

    velocity = 0x60;

    midiOutOpen(&hmidiOut, MIDI_MAPPER, 0, 0, 0);

    midiOutShortMsg(hmidiOut , 0xc0 );    // 音色を定義 アコースティックピアノ0x0(0)
}

//---------------------------------------------------------------
// デストラクタ
melodyCtrl::~melodyCtrl()
{
    midiOutReset(hmidiOut);
    midiOutClose(hmidiOut);
}

//---------------------------------------------------------------
// キー情報設定
void melodyCtrl::SetKeyInfo(key::keyInfo* pkinfo)
{
    pKeyInfo = pkinfo;
}

//---------------------------------------------------------------
// キー情報反映
void melodyCtrl::Update()
{
    auto keyInfolist = pKeyInfo->GetKeyInfoPressed();

    // チャンネルクリア
    for(auto& ch : channelMap)
    {
        if(ch.second == 0) continue;  // 未使用チャンネルはスキップ
        bool isKeyPressContinue = false;
        for(auto key : keyInfolist)
        {
            if(key.keyValue == ch.second) isKeyPressContinue = true;
        }
        if(isKeyPressContinue) continue;

        // 押下キーに対応する音階値取得
        int scaleVal = pKeyInfo->GetScaleValue(ch.second);
        
        // 音消去
        midiOutShortMsg(hmidiOut, MakeMIDIMsg(0x8, ch.first, scaleVal, 0));
        // チャンネルクリア
        ch.second = 0;
    }

    // チャンネル設定
    for(auto key : keyInfolist)
    {
        bool isKeyPressed = false;
        for(auto ch : channelMap)
        {
            if(key.keyValue == ch.second)
            {
                isKeyPressed = true;
                continue;
            }
        }
        // チャンネル設定済み
        if(isKeyPressed) continue;
        // チャンネル登録
        for(auto& ch : channelMap)
        {
            // チャンネル空き有
            if(ch.second == 0)
            {
                // チャンネル設定
                ch.second = key.keyValue;
                // キーに対応する音階値取得
                int scaleVal = pKeyInfo->GetScaleValue(key.keyValue);
                // 音生成
                midiOutShortMsg(hmidiOut, MakeMIDIMsg(0x9, ch.first, scaleVal, velocity));
                break;
            }
        }
    }
}

//---------------------------------------------------------------
// MIDIメッセージ生成
// [in] st: ステータス 0x9 -> 鍵盤押下, 0x8 -> 鍵盤クリア？
// [in] ch: チャンネル 0-15
// [in] d1: データ１
// [in] d2: データ２
unsigned long melodyCtrl::MakeMIDIMsg(uint8_t st, uint8_t ch, uint8_t d1, uint8_t d2)
{
    unsigned long msg = 0;
    msg = (DWORD)((st<<4) | ch | (d1<<8) | (d2<<16));
    //std::cout << "make msg:" << msg << " based st:" << (int)st << ", ch:" << (int)ch << ", d1:" << (int)d1 << ", d2:" << (int)d2 << std::endl; 
    return msg;
}

// make msg:17808 based st:9, ch:0, d1:69, d2:0

//---------------------------------------------------------------
// チャンネルマップ初期化
void melodyCtrl::InitializeChannelMap()
{
    channelMap.clear();
    channelMap.insert(std::make_pair(0, 0));
    channelMap.insert(std::make_pair(1, 0));
    channelMap.insert(std::make_pair(2, 0));
    channelMap.insert(std::make_pair(3, 0));
    channelMap.insert(std::make_pair(4, 0));
    channelMap.insert(std::make_pair(5, 0));
    channelMap.insert(std::make_pair(6, 0));
    channelMap.insert(std::make_pair(7, 0));
    channelMap.insert(std::make_pair(8, 0));
    channelMap.insert(std::make_pair(9, 0));
    channelMap.insert(std::make_pair(10, 0));
    channelMap.insert(std::make_pair(11, 0));
    channelMap.insert(std::make_pair(12, 0));
    channelMap.insert(std::make_pair(13, 0));
    channelMap.insert(std::make_pair(14, 0));
    channelMap.insert(std::make_pair(15, 0));
}

} // namespace melody