#pragma once
#include <dinput.h>

class CDInput {
public:
    // �R���X�g���N�^
    CDInput(HINSTANCE hInstance, HWND hWnd);

    // �f�X�g���N�^
    ~CDInput();

    // ���͂̏�����
    bool Initialize();

    // ���͂̍X�V
    void Update();

    // �w�肳�ꂽ�L�[�R�[�h��������Ă��邩�ǂ�����Ԃ�
    bool IsKeyPressed(int keyCode);

private:
    LPDIRECTINPUT8        lpDI;              // DirectInput �C���^�[�t�F�[�X
    LPDIRECTINPUTDEVICE8  lpKeyboard;        // �L�[�{�[�h�f�o�C�X
    BYTE                  keyState[256];    // �L�[�{�[�h�̏�Ԃ��i�[����z��

    HWND                  hWnd;             // �E�B���h�E�n���h��

    // �L�[�{�[�h�f�o�C�X�̏����ݒ�
    bool AcquireKeyboard();
};
