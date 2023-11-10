#pragma once
#pragma comment (lib, "xinput.lib")
#include <windows.h>
#include <xinput.h>

class Input
{
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

