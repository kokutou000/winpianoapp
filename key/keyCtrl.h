/*********************************************************** 
 * キー操作管理クラス ヘッダファイル
************************************************************/
#ifndef _KEYCTRL
#define _KEYCTRL

#include <windows.h>
#include <map>
#include <list>

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

        std::list<int> GetListKeyON();
        
    private:
        void UpdateKeyState(WPARAM wp, bool);
        void InitializeKeyStateMap();

    private:
        std::map<int, bool> keyState;  // キー状態<キー種別, T:押下/F:非押下>

        key::keyInfo* pKeyInfo;
    };
} // namespace key

#endif // _KEYCTRL