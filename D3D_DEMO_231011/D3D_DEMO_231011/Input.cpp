#include "Input.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

Input::Input(HINSTANCE hInstance, HWND hWnd)
    : lpDI(nullptr), lpKeyboard(nullptr), hWnd(hWnd)
{
    // DirectInput8の作成
    if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&lpDI, nullptr))) {
        // エラーハンドリング
    }
}


Input::~Input() {
    // キーボードデバイスの解放
    if (lpKeyboard) {
        lpKeyboard->Unacquire();
        lpKeyboard->Release();
    }

    // DirectInputの解放
    if (lpDI) {
        lpDI->Release();
    }
}


bool Input::Initialize() {
    if (!lpDI) {
        return false;
    }

    // キーボードデバイスの作成と初期設定
    if (FAILED(lpDI->CreateDevice(GUID_SysKeyboard, &lpKeyboard, nullptr))) {
        return false;
    }

    if (!AcquireKeyboard()) {
        return false;
    }

    return true;
}


bool Input::AcquireKeyboard() {
    if (lpKeyboard) {
        // 入力データ形式のセット
        if (FAILED(lpKeyboard->SetDataFormat(&c_dfDIKeyboard))) {
            return false;
        }

        // 排他制御のセット
        if (FAILED(lpKeyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY))) {
            return false;
        }

        // 動作開始
        if (FAILED(lpKeyboard->Acquire())) {
            return false;
        }

        return true;
    }

    return false;
}


void Input::Update() {
    if (lpKeyboard) {
        // キーボードの状態を取得
        if (FAILED(lpKeyboard->GetDeviceState(sizeof(keyState), keyState))) {
            // エラーハンドリング、再度キーボードを取得
            AcquireKeyboard();
        }
    }
}


bool Input::IsKeyPressed(int keyCode) {
    // 指定されたキーコードが押されているかどうかを返す
    return (keyState[keyCode] & 0x80) != 0;
}
