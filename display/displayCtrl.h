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

        void DrawWindow();

    private:
        void InitializeRectMap();
        void InitializeKeyMap();

    private:
        HWND windowInfo_;

        int wWin_;
        int hWin_;

        std::map<int, int> keyKeyMap;   // キーボードvs鍵盤マップ<キー, 鍵盤番号>
        std::map<int, RECT> keyRectMap;   // 鍵盤表示座標マップ<鍵盤番号, 座標情報>
    };
} // namespace display