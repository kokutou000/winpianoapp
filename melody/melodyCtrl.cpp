#include "melodyCtrl.h"

#include <iostream>

namespace melody
{

//---------------------------------------------------------------
// コンストラクタ
melodyCtrl::melodyCtrl()
{
    std::cout << "constructor melodyCtrl" << std::endl;
    InitializeScaleMap();
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
// [in] keyInfo: 押下キーリスト
void melodyCtrl::SetKeyInfo(std::list<int> pressKeyList)
{
    // 暫定処置------------------------------------
    const int maxno = 16;
    pressKeyList.clear();
    auto keylist = pKeyInfo->GetKeyInfoPressed();
    for(auto key : keylist)
    {
        if(key.isPressed)
        {
            pressKeyList.push_back(key.keyNo);
            if(pressKeyList.size() >= maxno) break;
        }
    }
    // 暫定処置------------------------------------

    // チャンネルクリア
    for(auto& ch : channelMap)
    {
        if(ch.second == 0) continue;  // 未使用チャンネルはスキップ
        bool isKeyPressContinue = false;
        for(auto key : pressKeyList)
        {
            if(key == ch.second) isKeyPressContinue = true;
        }
        if(isKeyPressContinue) continue;
        
        // 音消去
        midiOutShortMsg(hmidiOut, MakeMIDIMsg(0x8, ch.first, scaleMap[ch.second], 0));
        // チャンネルクリア
        ch.second = 0;
    }

    // チャンネル設定
    for(auto key : pressKeyList)
    {
        bool isKeyPressed = false;
        for(auto ch : channelMap)
        {
            if(key == ch.second)
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
                ch.second = key;
                // 音生成
                midiOutShortMsg(hmidiOut, MakeMIDIMsg(0x9, ch.first, scaleMap[ch.second], velocity));
                break;
            }
        }

        //std::cout << "check setkeyinfo:" << key << std::endl;
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
    //msg = (DWORD)((st<<4) | ch | (d1<<8) | (d2<<16));
    msg = (DWORD)((st<<4) | ch | (d1<<8) | (d2<<16));
    std::cout << "make msg:" << msg << " based st:" << (int)st << ", ch:" << (int)ch << ", d1:" << (int)d1 << ", d2:" << (int)d2 << std::endl; 
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

//---------------------------------------------------------------
// 音階マップ初期化
void melodyCtrl::InitializeScaleMap()
{
    scaleMap.clear();
    scaleMap.insert(std::make_pair(0x5A, 0x31)); // z, ド＃
    scaleMap.insert(std::make_pair(0x58, 0x32)); // x, レ
    scaleMap.insert(std::make_pair(0x43, 0x33)); // c, レ＃
    scaleMap.insert(std::make_pair(0x56, 0x34)); // v, ミ
    scaleMap.insert(std::make_pair(0x42, 0x35)); // b, ファ
    scaleMap.insert(std::make_pair(0x4E, 0x36)); // n, ファ＃
    scaleMap.insert(std::make_pair(0x4D, 0x37)); // m, ソ
    scaleMap.insert(std::make_pair(0x41, 0x38)); // a, ソ＃
    scaleMap.insert(std::make_pair(0x53, 0x39)); // s, ラ
    scaleMap.insert(std::make_pair(0x44, 0x3A)); // d, ラ＃
    scaleMap.insert(std::make_pair(0x46, 0x3B)); // f, シ
    scaleMap.insert(std::make_pair(0x47, 0x3C)); // g, ド
    scaleMap.insert(std::make_pair(0x48, 0x3D)); // h, ド＃
    scaleMap.insert(std::make_pair(0x4A, 0x3E)); // j, レ
    scaleMap.insert(std::make_pair(0x4B, 0x3F)); // k, レ#
    scaleMap.insert(std::make_pair(0x4C, 0x40)); // l, ミ
    scaleMap.insert(std::make_pair(0x51, 0x41)); // q, ファ
    scaleMap.insert(std::make_pair(0x57, 0x42)); // w, ファ＃
    scaleMap.insert(std::make_pair(0x45, 0x43)); // e, ソ
    scaleMap.insert(std::make_pair(0x52, 0x44)); // r, ソ＃
    scaleMap.insert(std::make_pair(0x54, 0x45)); // t, ラ
    scaleMap.insert(std::make_pair(0x59, 0x46)); // y, ラ＃
    scaleMap.insert(std::make_pair(0x55, 0x47)); // u, シ
    scaleMap.insert(std::make_pair(0x49, 0x48)); // i, ド
    scaleMap.insert(std::make_pair(0x4F, 0x49)); // o, ド＃
    scaleMap.insert(std::make_pair(0x50, 0x4A)); // p, レ

    scaleMap.insert(std::make_pair(0x31, 0x4B)); // 1, レ＃
    scaleMap.insert(std::make_pair(0x32, 0x4C)); // 2, ミ
    scaleMap.insert(std::make_pair(0x33, 0x4D)); // 3, ファ
    scaleMap.insert(std::make_pair(0x34, 0x4E)); // 4, ファ＃
    scaleMap.insert(std::make_pair(0x35, 0x4F)); // 5, ソ
    scaleMap.insert(std::make_pair(0x36, 0x50)); // 6, ソ＃
    scaleMap.insert(std::make_pair(0x37, 0x51)); // 7, ラ
    scaleMap.insert(std::make_pair(0x38, 0x52)); // 8, ラ＃
    scaleMap.insert(std::make_pair(0x39, 0x53)); // 9, シ
    scaleMap.insert(std::make_pair(0x30, 0x54)); // 0, ド
}

} // namespace melody