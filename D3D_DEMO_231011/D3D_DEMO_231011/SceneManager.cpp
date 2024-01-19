#include "SceneManager.h"
#include "Game.h"

//���݂̃X�e�[�W��
#define STAGE_NUM	(9)


SceneManager* SceneManager::Get()
{
	static SceneManager IniInstance;
	return &IniInstance;
}

void SceneManager::Init()
{
	//�����őS���̃Q�[���I�u�W�F�N�g�̏���������������
	Game::Get()->Init();
	
	//�X�e�[�W��������
	for (int i = 0; i < STAGE_NUM; i++)
	{
		m_stageHolder[i] = new Stage();
	}
	
}

void SceneManager::InitStage()
{
	//�X�e�[�W�̏�����
	switch (GetScene()) {
	
	case STAGE1_1:

		InitStage1_1();

		break;

	case STAGE1_2:

		InitStage1_2();

		break;

	case STAGE1_3:

		InitStage1_3();

		break;

	case STAGE2_1:

		InitStage1_1();

		break;

	case STAGE2_2:

		InitStage2_2();

		break;

	case STAGE2_3:

		InitStage2_3();

		break;

	case STAGE3_1:

		InitStage3_1();

		break;
	case STAGE3_2:

		InitStage3_2();

		break;

	case STAGE3_3:

		InitStage3_3();

		break;

	default:

		break;
	}

}

void SceneManager::InitStage1_1(void)
{
	//�X�e�[�W���������ɂ���
	m_stageHolder[STAGEINFO::STAGE1_1]->Init();
	
	//�w�i�ݒu


	//�I�u�W�F�N�g�ݒu

}

void SceneManager::InitStage1_2(void)
{
	//�X�e�[�W���������ɂ���
	m_stageHolder[STAGEINFO::STAGE1_2]->Init();

	//�w�i�ݒu


	//�I�u�W�F�N�g�ݒu
	
	//�I�u�W�F�N�g�̈ʒu

	//�I�u�W�F�N�g�̏�Ԃ�

}

void SceneManager::InitStage1_3(void)
{
}

void SceneManager::InitStage2_1(void)
{
}

void SceneManager::InitStage2_2(void)
{
}

void SceneManager::InitStage2_3(void)
{
}

void SceneManager::InitStage3_1(void)
{
}

void SceneManager::InitStage3_2(void)
{
}

void SceneManager::InitStage3_3(void)
{
}


void SceneManager::Update()
{
	switch (GetScene()) {
	case SCENENAME::TITLE:
		TitleUpdate();
		break;

	case SCENENAME::STAGESELECT:
		StageSelect();
		break;

	case SCENENAME::STAGE1_1:
		UpdateStage1_1();
		break;

	case SCENENAME::STAGE1_2:
		UpdateStage1_2();
		break;

	case SCENENAME::STAGE1_3:
		UpdateStage1_3();
		break;

	}


	

}

void SceneManager::TitleUpdate()
{
}

void SceneManager::StageSelect()
{
}

void SceneManager::UpdateStage1_1(void)
{
	//���͏����@XX�L�[�����āA�ړ�������I�u�W�F�N�g���X�C�b�`

	//�I�u�W�F�N�gUpdate

}

void SceneManager::UpdateStage1_2(void)
{
}

void SceneManager::UpdateStage1_3(void)
{
}

void SceneManager::UpdateStage2_1(void)
{
}

void SceneManager::UpdateStage2_2(void)
{
}

void SceneManager::UpdateStage2_3(void)
{
}

void SceneManager::UpdateStage3_1(void)
{
}

void SceneManager::UpdateStage3_2(void)
{
}

void SceneManager::UpdateStage3_3(void)
{
}



void SceneManager::Draw()
{

	
}
