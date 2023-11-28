#pragma once
#include <dinput.h>

class CDInput {
public:
    // コンストラクタ
    CDInput(HINSTANCE hInstance, HWND hWnd);

    // デストラクタ
    ~CDInput();

    // 入力の初期化
    bool Initialize();

    // 入力の更新
    void Update();

    // 指定されたキーコードが押されているかどうかを返す
    bool IsKeyPressed(int keyCode);

private:
    LPDIRECTINPUT8        lpDI;              // DirectInput インターフェース
    LPDIRECTINPUTDEVICE8  lpKeyboard;        // キーボードデバイス
    BYTE                  keyState[256];    // キーボードの状態を格納する配列

    HWND                  hWnd;             // ウィンドウハンドル

    // キーボードデバイスの初期設定
    bool AcquireKeyboard();
};
