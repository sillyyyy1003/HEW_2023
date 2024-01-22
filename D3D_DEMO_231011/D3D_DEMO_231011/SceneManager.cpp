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



void SceneManager::Update()
{

}


