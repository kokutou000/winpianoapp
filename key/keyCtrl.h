/*********************************************************** 
 * キー操作管理クラス ヘッダファイル
************************************************************/
#include <windows.h>
#include <map>
#include <list>

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
        void EventKeyDown(WPARAM wp);
        void EventKeyUp(WPARAM wp);

        std::list<int> GetListKeyON();
        
    private:
        void UpdateKeyState(WPARAM wp, bool);
        void InitializeKeyStateMap();

    private:
        std::map<int, bool> keyState;  // キー状態<キー種別, T:押下/F:非押下>
    };
} // namespace key

