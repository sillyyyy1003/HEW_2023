#pragma once

<<<<<<< HEAD
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

=======
>>>>>>> feature/Sakamoto
// �X�e�[�W�N���X �i�X�e�[�W�������j
class Stage
{
private:
<<<<<<< HEAD

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
=======
	
	

public:

	enum class StageInfo//15 �K�v�ɉ����đ��₷
	{
	STAGEA = 11,// 1-1
	STAGEB = 12,// 1-2
	STAGEC = 13,// 1-3

	STAGEBA = 21,// 2-1
	STAGEBB = 22,// 2-2
	STAGEBC = 23,// 2-3

	STAGECA = 31,// 3-1
	STAGECB = 32,// 3-2
	STAGECC = 33,// 3-3

	STAGEDA = 41,// 4-1
	STAGEDB = 42,// 4-2
	STAGEDC = 43,// 4-3

	STAGEEA = 51,// 5-1
	STAGEEB = 52,// 5-2
	STAGEEC = 53,// 5-3

	PAUSE=99,
	};

>>>>>>> feature/Sakamoto
};

