/*********************************************************** 
 * キー基本構造体ファイル
************************************************************/
#ifndef _KEYBASE
#define _KEYBASE

#include "windows.h"
#include <string>

namespace key
{
    /************************************************************
     * キー基本情報構造体
    ************************************************************/
    typedef struct _keyBaseStruct
    {
        unsigned short keyValue;    // キーボード対応値
        std::string keyChar;        // キーボード対応名
        bool isPressed;             // 押下状態
        int scaleNo;                // 鍵盤番号（画面における鍵盤位置番号）
        int scaleValue;             // 音階値（MIDIMSGに渡す音の値）
        std::string scaleName;      // ABC音階名
        RECT scaleDisp;             // 鍵盤座標
    } keyBase;

} // namespace key

#endif // _KEYBASE
