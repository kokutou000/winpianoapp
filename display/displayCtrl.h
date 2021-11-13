/*********************************************************** 
 * 描画管理クラス ヘッダファイル
************************************************************/
#include <windows.h>
#include <map>

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

    private:
        void InitializeRectMap();

    private:
        HWND windowInfo;

        int wWin;
        int hWin;

        std::map<int, RECT> keyRectMap;   // 鍵盤表示座標マップ<キー, 座標情報>
    };
} // namespace display