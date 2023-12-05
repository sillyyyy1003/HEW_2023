#pragma once

//DirectInput���g�����L�[�ƃ}�E�X����擾�N���X
#define DIRECTINPUT_VERSION 0x0800
#include	<dinput.h>

enum KeyCode
{
	DIK_LBUTTON = 0x00,//���}�E�X�{�^��
	DIK_RBUTTON = 0x01,//�E�}�E�X�{�^��
	DIK_MBUTTON = 0x02,//���}�E�X�{�^��
	DIK_SIDEBUTTON1 = 0x03,//�T�C�h�}�E�X�{�^��1
	DIK_SIDEBUTTON2 = 0x04,//�T�C�h�}�E�X�{�^��2
};


class CdInput
{

private:
	IDirectInput8* mDInput = nullptr;
	IDirectInputDevice8* mDevKeyboad = nullptr;
	IDirectInputDevice8* mDevMouse = nullptr;

	unsigned char mKeyBuffer[256] = {};
	unsigned char mOldKeyBuffer[256] = {};

	DIMOUSESTATE2 mMouseState = {};
	DIMOUSESTATE2 mOldMouseState = {};

	CdInput() {};

	
	

public:

	~CdInput();//�f�X�g���N�^

	// �V���O���g���̃C���X�^���X���擾����֐�
	static CdInput* Get();

	// DirectInput�̏��������s���֐�
	// �Q�[�����[�v���n�܂�O�ɌĂяo��
	void Initialize(HWND hWnd, HINSTANCE hInstance);
	
	// �Q�[�����[�v�Ŗ���Ăяo���֐�
	void Update();

	//�L�[�������ꂽ���
	void SetKeyDownState(int key);

	//�L�[�������ꂽ���
	void SetKeyUpState(int key);

	//�}�E�X�{�^���������ꂽ���
	void SetMouseDownState(int key);

	//�}�E�X�{�^���������ꂽ���
	void SetMouseUpState(int key);

	// �L�[��DIK�Ŏn�܂�萔
	//�L�[�v���X
	bool GetKeyPress(int key);

	//�L�[�g���K�[
	bool GetKeyTrigger(int key);

	//�}�E�X�{�^���v���X
	bool GetMousePress(int key);

	//�}�E�X�{�^���g���K�[
	bool GetMouseTrigger(int key);

	// �}�E�X�̈ړ��ʂ��擾����
	POINT GetMouseMove();
};

