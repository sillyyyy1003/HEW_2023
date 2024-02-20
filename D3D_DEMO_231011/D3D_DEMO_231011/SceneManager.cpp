#include "SceneManager.h"
#include "Game.h"
#include "Stage.h"

SceneManager::~SceneManager()
{
	for (int i = 0; i < STAGE_NUM; i++) {
		delete m_stageHolder[i];
	}

}

SceneManager* SceneManager::Get()
{
	static SceneManager IniInstance;
	return &IniInstance;
}

void SceneManager::Init()
{
	//�����őS���̃Q�[���I�u�W�F�N�g�̏���������������
	//Game::Get()->Init();
	
	m_stageHolder = new Stage * [STAGE_NUM];

	//�X�e�[�W��������
	for (int i = 0; i < STAGE_NUM; i++)
	{
		m_stageHolder[i] = new Stage();
	}
	
}



void SceneManager::Update()
{

}

int SceneManager::GetActiveStage(void)
{
	//for (int i = 0; i < STAGE_NUM; i++) {

	//	if (m_stageHolder[i]->GetActive()) {

	//		return i;
	//	}
	//	else {
	//		return 0;
	//	}
	//}
	int num = Scene::GetStage();
	return static_cast<STAGEINFO>(num);

}


