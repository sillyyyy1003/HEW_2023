#pragma once
#include <vector>
class GameObject;

// �X�e�[�W�N���X �i�X�e�[�W�������j
class Stage
{
private:


	//�X�e�[�W�N���A�������ǂ����H
	bool isClear = false;

	//���N���A������
	bool isisCompleted = false;
	
	//Reward Gold
	float m_rewardGold = 0;
	 
	//�ړ��̐�
	int m_moveStep=0;

	//�X�e�[�W�͍쓮�����ǂ����H
	bool isActive = false;

	std::vector<GameObject*> m_objectList;

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
	void SetCompleted(bool isCompleted) { this->isisCompleted = isCompleted; };
	bool GetCompleted(void) { return isisCompleted; };



	//�X�e�b�v�������Z���Ă���
	void StepCount(void);
	int GetStep(void) { return m_moveStep; };

public:

	
};

