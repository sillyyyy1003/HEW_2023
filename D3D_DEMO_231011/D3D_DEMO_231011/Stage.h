#pragma once

enum STAGEINFO {
	STAGE1_1,
	STAGE1_2,
	STAGE1_3,

	STAGE2_1,
	STAGE2_2,
	STAGE2_3,

	STAGE3_1,
	STAGE3_2,
	STAGE3_3,

};

// �X�e�[�W�N���X �i�X�e�[�W�������j
class Stage
{
private:

	//�X�e�[�W�N���A�������ǂ����H
	bool isClear = false;
	
	//Reward Gold
	float m_rewardGold = 0;
	 
	//�ړ��̐�
	int m_moveStep=0;

public:

	//�����ŃX�e�[�W�̏����z�u���s��
	void Init(void);

	//�����[�v�ōs���֐�
	void Update(void);

	//�X�e�b�v�������Z���Ă���
	void StepCount(void);

	int GetStep(void) { return m_moveStep; };
};

