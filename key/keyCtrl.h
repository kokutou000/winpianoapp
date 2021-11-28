/*********************************************************** 
 * キー操作管理クラス ヘッダファイル
************************************************************/
#ifndef _KEYCTRL
#define _KEYCTRL

#include <windows.h>

#include "keyBase.h"
#include "keyInfo.h"

namespace key
{
    /************************************************************
     * キー操作管理クラス
    ************************************************************/
    class keyCtrl
    {
    // 生成/破棄
    public:
        keyCtrl();
        ~keyCtrl();

    public:
        void SetKeyInfo(key::keyInfo*);

        void EventKeyDown(WPARAM wp);
        void EventKeyUp(WPARAM wp);
        
    private:
        void UpdateKeyState(WPARAM wp, bool);

    private:

        key::keyInfo* pKeyInfo;
    };
} // namespace key

#endif // _KEYCTRL