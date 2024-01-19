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

void SceneManager::InitStage()
{
	//ステージの初期化
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
	//ステージを初期化にする
	m_stageHolder[STAGEINFO::STAGE1_1]->Init();
	
	//背景設置


	//オブジェクト設置

}

void SceneManager::InitStage1_2(void)
{
	//ステージを初期化にする
	m_stageHolder[STAGEINFO::STAGE1_2]->Init();

	//背景設置


	//オブジェクト設置
	
	//オブジェクトの位置

	//オブジェクトの状態の

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
	//入力処理　XXキー押して、移動させるオブジェクトをスイッチ

	//オブジェクトUpdate

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
