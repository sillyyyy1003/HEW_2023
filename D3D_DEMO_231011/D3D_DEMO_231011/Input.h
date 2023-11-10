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
<<<<<<< HEAD
private:
	//�L�[��Ԃ̋L���̈�
	bool m_KeyState[256] = { false }; 
	// 1�t���[���O�̃L�[��Ԃ̋L�^�̈�
	bool m_OldKeyState[256] = { false };

public:
	//�����o�[�֐�
	
	//�L�[�������ꂽ�̂��L�^����֐�
	void SetKeyDownState(int key);

	//�L�[�������ꂽ�̂��L�^����֐�
	void SetKeyUpState(int key);

	// �L�[�v���X���������Ă��邩�Ԃ��֐�
	bool GetKeyPress(int key);

	//�L�[�g���K�[���������邩�Ԃ��֐�
	bool GetKeyTrigger(int key);

	//�Q�[�����[�v�̍Ō�ŃL�[��Ԃ�m_oldKeyState�ɕۑ�����֐�
	void Upadate();
};

//DWORD XInputGetState(
//    DWORD dwUserIndex,    // �R���g���[���[�̃C���f�b�N�X
//    XINPUT_STATE* pState  // ��Ԃ��󂯎�� XINPUT_STATE �\���̂ւ̃|�C���^�[
//);
////DIJOYSTATE pad_data;
=======
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

>>>>>>> bce30b2a0f792ca953bc5860332ce4bd7480af82

