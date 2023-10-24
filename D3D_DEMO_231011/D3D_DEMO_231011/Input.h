#pragma once
#pragma comment (lib, "xinput.lib")
#include <windows.h>
#include <xinput.h>

class Input
{

};

DWORD XInputGetState(
    DWORD dwUserIndex,    // コントローラーのインデックス
    XINPUT_STATE* pState  // 状態を受け取る XINPUT_STATE 構造体へのポインター
);
//DIJOYSTATE pad_data;

