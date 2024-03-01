#pragma once
#include <vector>
class GameObject;

// �X�e�[�W�N���X �i�X�e�[�W�������j
class Stage
{
private:
	//�q���g���o���ꂽ���ǂ���
	bool isHint = true;

	//�X�e�[�W�N���A�������ǂ����H
	bool isClear = false;

	//���N���A������
	bool isCompleted = false;

	//Reward Gold
	float m_rewardGold = 0;

	//�ړ��̐�
	int m_moveStep = 0;

	//�X�e�[�W�͍쓮�����ǂ����H
	bool isActive = false;


public:


	//�����ŃX�e�[�W�̏����z�u���s��
	void Init(void);

	//�����[�v�ōs���֐�
	void Update(void);

	//�X�e�[�W���쓮���Ă��邩�ǂ���
	void SetActive(bool isActive) { this->isActive = isActive; };
	bool GetActive(void) { return this->isActive; };

	//�Q�[���N���A���������ǂ����H
	void SetClear(bool isClear) { this->isClear = isClear; };
	bool GetClear(void) { return isClear; };

	//�Q�[���X�e�[�W���N���A�����ǂ����H
	void SetCompleted(bool isCompleted) { this->isCompleted = isCompleted; };
	bool GetCompleted(void) { return isCompleted; };

	//�X�e�b�v�������Z���Ă���
	void StepCount(void);

	void HintPunish(int step) { m_moveStep += step; };
	int GetStep(void) { return m_moveStep; };

	//step�������Z�b�g�@�N���A��Ԃ����Z�b�g
	void ResetStage(void) { m_moveStep = 0; isClear = false; };

	//hint�̔��f
	bool GetHint(void) { return isHint; };
	void SetHint(bool isHint) { this->isHint = isHint; };


};

