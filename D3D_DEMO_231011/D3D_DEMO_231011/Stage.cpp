#include "Stage.h"

void Stage::Init(void)
{
	//�X�e�[�W���N���A���ĂȂ���Ԃ��Z�b�g����
	isClear = false;

	//���J���̋��z�����Z�b�g
	m_rewardGold=0;

	//�ړ��������Z�b�g����
	m_moveStep = 0;

}

void Stage::Update(void)
{
	
}

void Stage::StepCount(void)
{
	m_moveStep++;
}
