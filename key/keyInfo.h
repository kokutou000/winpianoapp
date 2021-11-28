/*********************************************************** 
 * キー情報クラス ヘッダファイル
************************************************************/
#ifndef _KEYINFO
#define _KEYINFO

#include <list>
#include "keyBase.h"

namespace key
{
    /************************************************************
     * キー情報クラス
    ************************************************************/
    class keyInfo
    {
    // 生成/破棄
    public:
        keyInfo();
        ~keyInfo();

    public:
        void SetKeyPressState(const bool&, const unsigned short&);
        std::list<keyBase> GetKeyInfoPressed();


    private:
        void InitializeKeyInfoList();

    private:
        std::list<keyBase> keyInfoList; // キー情報リスト
    };
} // namespace key

#endif // _KEYINFO
