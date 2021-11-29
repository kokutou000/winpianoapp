/*********************************************************** 
 * 描画管理クラス ヘッダファイル
************************************************************/
#ifndef _DISPLAYCTRL
#define _DISPLAYCTRL

#include <windows.h>
#include <map>
#include <list>
#include <vector>

#include "../key/keyInfo.h"

namespace display
{
    /************************************************************
     * 描画操作管理クラス
    ************************************************************/
    class displayCtrl
    {
    // 生成/破棄
    public:
        displayCtrl();
        ~displayCtrl();

        void SetHWinInfo(HWND hw);
        void UpdateWindowInfo();

        void DrawWindow();

        void Update();

        void SetKeyInfo(key::keyInfo*);

    private:
        HWND windowInfo_;

        int wWin_;
        int hWin_;
        bool flagUpdate_;

        std::vector<int> keyOnList_;   // 押下キーボードリスト

        key::keyInfo* pKeyInfo_;
    };
} // namespace display

#endif // _DISPLAYCTRL