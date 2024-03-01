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
	//ここで全部のゲームオブジェクトの初期化を完成する
	//Game::Get()->Init();
	
	m_stageHolder = new Stage * [STAGE_NUM];

	//ステージを初期化
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


