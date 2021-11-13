/*********************************************************** 
 * 音声操作管理クラス ヘッダファイル
************************************************************/
#include <map>
#include <list>
#include <windows.h>
#include <mmsystem.h>

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

        void SetKeyInfo(std::list<int>);

    private:
        void InitializeScaleMap();
        void InitializeChannelMap();
        unsigned long MakeMIDIMsg(uint8_t st, uint8_t ch, uint8_t d1, uint8_t d2);

    private:
        std::map<int, uint32_t> scaleMap;   // 音階マップ<キー, ABC音階値>
        std::map<int, int> channelMap;      // 使用チャンネル管理<チャンネル番号, キー>

        HMIDIOUT hmidiOut;

        uint8_t velocity;

    };
} // namespace melody