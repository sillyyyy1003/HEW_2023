#pragma once
//Direct Input���g�����L�[�ƃ}�E�X����擾�N���X
#define DIRECTINPUT_VERSION 0x0800
#include	<dinput.h>


class Input
{

private:
	IDirectInput8* mDInput = nullptr;
	IDirectInputDevice8* mDevKeyboad = nullptr;
	IDirectInputDevice8* mDevMouse = nullptr;

	unsigned char mKeyBuffer[256] = {};
	unsigned char mOldKeyBuffer[256] = {};

	DIMOUSESTATE2 mMouseState = {};
	DIMOUSESTATE2 mOldMouseState = {};

	Input() {};

	~Input();
	

public:
	/// <summary>
	/// Singleton Instance���擾����֐�
	/// </summary>
	/// <returns></returns>
	static Input* Get();
	
	/// <summary>
	///	Direct Input�̏��������s���֐�
	/// �Q�[�����[�v���n�߂�O�ɌĂяo��
	/// </summary>
	/// <param name="hWnd"></param>
	/// <param name="hInstance"></param>
	void Initialize(HWND hWnd, HINSTANCE hInstance);
		
	/// <summary>
	/// �Q�[�����[�v�Ŗ���Ăяo���֐�
	/// </summary>
	void Update();

	//key�FDIK_D�Ŏn�܂�萔
	bool GetKeyPress(int key);

	bool GetKeyTrigger(int key);

	/// <summary>
	/// �}�E�X�̃{�^����������Ă��邩����
	/// </summary>
	/// <param name="key"></param>
	/// <returns></returns>
	bool GetMousePress(int key);

	//�}�E�X�̈ړ��ʂ��擾
	POINT GetMouseMove(void);

};

