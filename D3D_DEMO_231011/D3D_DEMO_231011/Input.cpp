#include "Input.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

Input::Input(HINSTANCE hInstance, HWND hWnd)
    : lpDI(nullptr), lpKeyboard(nullptr), hWnd(hWnd)
{
    // DirectInput8�̍쐬
    if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&lpDI, nullptr))) {
        // �G���[�n���h�����O
    }
}


Input::~Input() {
    // �L�[�{�[�h�f�o�C�X�̉��
    if (lpKeyboard) {
        lpKeyboard->Unacquire();
        lpKeyboard->Release();
    }

    // DirectInput�̉��
    if (lpDI) {
        lpDI->Release();
    }
}


bool Input::Initialize() {
    if (!lpDI) {
        return false;
    }

    // �L�[�{�[�h�f�o�C�X�̍쐬�Ə����ݒ�
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
        // ���̓f�[�^�`���̃Z�b�g
        if (FAILED(lpKeyboard->SetDataFormat(&c_dfDIKeyboard))) {
            return false;
        }

        // �r������̃Z�b�g
        if (FAILED(lpKeyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY))) {
            return false;
        }

        // ����J�n
        if (FAILED(lpKeyboard->Acquire())) {
            return false;
        }

        return true;
    }

    return false;
}


void Input::Update() {
    if (lpKeyboard) {
        // �L�[�{�[�h�̏�Ԃ��擾
        if (FAILED(lpKeyboard->GetDeviceState(sizeof(keyState), keyState))) {
            // �G���[�n���h�����O�A�ēx�L�[�{�[�h���擾
            AcquireKeyboard();
        }
    }
}


bool Input::IsKeyPressed(int keyCode) {
    // �w�肳�ꂽ�L�[�R�[�h��������Ă��邩�ǂ�����Ԃ�
    return (keyState[keyCode] & 0x80) != 0;
}
