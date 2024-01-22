#include "SceneManager.h"
#include "Game.h"

//現在のステージ数
#define STAGE_NUM	(9)


SceneManager* SceneManager::Get()
{
	static SceneManager IniInstance;
	return &IniInstance;
}

void SceneManager::Init()
{
	//ここで全部のゲームオブジェクトの初期化を完成する
	Game::Get()->Init();
	
	//ステージを初期化
	for (int i = 0; i < STAGE_NUM; i++)
	{
		m_stageHolder[i] = new Stage();
	}
	
}



void SceneManager::Update()
{

}


