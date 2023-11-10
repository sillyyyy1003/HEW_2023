#pragma once

//�L�[���͂��Ǘ�����N���X
//�d�g�݁FWndProc�֐��ŃL�[�������ꂽ/�����ꂽ�C�x���g���ɂ�����L�^���Ă����B
//�L�[�̏�Ԃ𔻒肷��֐����Ă΂ꂽ��A���̋L�^��Ԃ�Ԃ��B

class KBInput
{
private:
	// �L�[��Ԃ̋L�^�̈�
	bool keyState[256] = { false };

	// 1�t���[���O�̃L�[��Ԃ̋L�^�̈�
	bool oldKeyState[256] = { false };

public:


	//----------------------------//
	// �֐��̃v���g�^�C�v�錾
	//----------------------------//

	// �L�[�������ꂽ�̂��L�^����֐�
	void SetKeyDownState(int key);

	// �L�[�������ꂽ�̂��L�^����֐�
	void SetKeyUpState(int key);

	// �L�[�v���X���������Ă��邩�Ԃ��֐�
	bool GetKeyPress(int key);

	// �L�[�g���K�[���������Ă��邩�Ԃ��֐�
	bool GetKeyTrigger(int key);

	// �Q�[�����[�v�̍Ō�ŃL�[��Ԃ�oldKeyState�ɕۑ�����֐�
	void Update();


};

