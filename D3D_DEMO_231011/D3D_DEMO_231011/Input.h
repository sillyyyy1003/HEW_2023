#pragma once
#pragma comment (lib, "xinput.lib")
#include <windows.h>
#include <xinput.h>

// ��Retro-Bit ���̃T�^�[���p�b�h�͕����p�b�h�����X�e�B�b�N�Ƃ��Ď�������Ă���̂ŁA
// �@wButtons ��ǂނ����ł͓��͂�F�����邱�Ƃ��ł��Ȃ��B
// �@�����ŁAwButtons ��ǂޑO�ɃX�e�B�b�N�̓��͂�����p�b�h�ɕϊ����đΉ����s���B
// �X�e�B�b�N�̓��͂�����p�b�h�t���O�ɕϊ�
WORD ThumbToDPad(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone);

class Input
{
public:
    // �g����p�b�h�̃{�^���̎��
    typedef enum
    {
        NONE,
        A, // �Q�[���p�b�hA
        B, // �Q�[���p�b�hB
        X, // �Q�[���p�b�hX
        Y, // �Q�[���p�b�hY
        R, // �Q�[���p�b�hR
        L, // �Q�[���p�b�hL
        LEFT, // �Q�[���p�b�h�\���L�[��
        RIGHT,// �Q�[���p�b�h�\���L�[�E
        UP,   // �Q�[���p�b�h�\���L�[��
        DOWN, // �Q�[���p�b�h�\���L�[��
        START,// �Q�[���p�b�hSTATRT
        BACK, // �Q�[���p�b�hBACK
        LEFTTRIGGER, // ���g���K�[
        RIGHTTRIGGER,// �E�g���K�[
        LEFTSTICK,   // ���X�e�B�b�N
        RIGHTSTICK,  // �E�X�e�B�b�N
        UPSTICK,     // ��X�e�B�b�N
        DOWNSTICK,   // ���X�e�B�b�N
    }PADBUTTON;

    PADBUTTON PadButton = NONE;

private:

    // �L�[��Ԃ̋L�^�̈�
    bool keyState[256] = { false };

    // 1�t���[���O�̃L�[��Ԃ̋L�^�̈�
    bool oldKeyState[256] = { false };

    // �p�b�h�������ꂽ���̏�����ۑ�����֐�
    bool SetPADButton(PADBUTTON PadButton);

    // �p�b�h��U�������邽�߂̊֐�
    void Vibration(int pattern);

    // �U���̃p�^�[��������ϐ�
    int pattern = 0;

    // �U�����Ԃ��L������ϐ�
    ULONGLONG Vibrationtime = 0;

public:

    // �{�^���̒��������������Ă��邩��Ԃ��֐�
    bool GetPADRepeat(PADBUTTON PadButton);

    // �{�^���̃g���K�[���������Ă��邩��Ԃ��֐�
    bool GetPADTrigger(PADBUTTON PadButton);

    void Update();

    //�U���p�^�[����ݒ肷��֐�
    void SetPattern(int pt)
    {
        pattern = pt;
    }
};

// �B��̎��̕ϐ���extern�錾
extern Input* gInput;


