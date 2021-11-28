/*********************************************************** 
 * 音声操作管理クラス ヘッダファイル
************************************************************/
#ifndef _MELODYCTRL
#define _MELODYCTRL

#include <windows.h>
#include <mmsystem.h>

#include <map>
#include <list>

#include "../key/keyInfo.h"

namespace melody
{
    /************************************************************
     * 音声操作管理クラス
    ************************************************************/
    class melodyCtrl
    {
    // 生成/破棄
    public:
        melodyCtrl();
        ~melodyCtrl();

        void Update();

        void SetKeyInfo(key::keyInfo*);

    private:
        void InitializeChannelMap();
        unsigned long MakeMIDIMsg(uint8_t st, uint8_t ch, uint8_t d1, uint8_t d2);

    private:
        std::map<int, int> channelMap;      // 使用チャンネル管理<チャンネル番号, キー>

        HMIDIOUT hmidiOut;

        uint8_t velocity;

        key::keyInfo* pKeyInfo;

    };
} // namespace melody

#endif // _MELODYCTRL