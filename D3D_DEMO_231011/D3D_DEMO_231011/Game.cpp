#include "Game.h"

#include "Direct3D/Direct3D.h"
#include "Assets.h"
#include "TrackCamera.h"

#include "Object.h"
#include "GameObject.h"
#include "ShadowObject.h"
#include "StaticObject.h"

#include "DebugManager.h"

#include "Animation.h"
#include "StaticAnimation.h"
#include "ObjectAnimation.h"

#include "DInput.h"

extern Assets* g_Assets;
extern Camera* g_WorldCamera;
extern DebugManager* g_DebugManager;


void Game::Init()
{
	//----------------------------//
	// ここからはテスト用の初期化
	//----------------------------//
	//カメラの追跡ターゲットを設定する
	//dynamic_cast<TrackCamera*>(g_WorldCamera)->SetTarget(testWall);

	testTree = new GameObject();	
	//モデルを作る
	testTree->CreateObject(g_Assets->testObj, 200, 200, 1, 1);
	testTree->CreateShadow(g_Assets->testShadow, 200, 200, 1, 1);
	//アニメションを配置
	testTree->m_obj->m_sprite->m_anime = new StaticAnimation(1, 1);	//オブジェクト
	testTree->m_shadow->m_obj->m_anime = new StaticAnimation(1, 1);	//影
	//オブジェクトの位置を配置
	testTree->m_obj->m_sprite->m_pos = { 2, 2, -1 };

	testWall = new StaticObject();
		//モデルを作る/アニメション配置
	testWall->CreateObject(g_Assets->testWall, 1920, 1080, 1, 1);
	//オブジェクトの位置を配置
	testWall->m_sprite->m_pos = { 0.0f,0.0f,1.0 };

	testGround = new StaticObject();
	//モデルを作る/アニメション配置
	testGround->CreateObject(g_Assets->testGround, 1920, 1080, 1, 1);
	//オブジェクトの位置を配置
	testGround->m_sprite->m_pos = { 0.0f,-3.0f,0.0f };
	
	testGround->m_sprite->m_rotation.x = 90;




	//----------------------------//
	// ここまではテスト用の初期化
	//----------------------------//






	
}

void Game::GameUpdate(void)
{
	switch (m_gameScene)
	{
	case TITLE:

		TitleUpdate();
		break;
		
	case STAGE1:

		StageUpdate();
		break;

	case RESULT:

		ResultUpdate();
		break;

	}
}

void Game::TitleUpdate(void)
{	
	//プロトタイプ用
	TestUpdate();

}

void Game::StageUpdate(void)
{
}


void Game::ResultUpdate(void)
{

}

void Game::TestUpdate(void)
{
	//光源の位置をリアルタイムで更新する
	testTree->Update({ 0, 0, -2 });
}

void Game::TestDraw(void)
{
	testWall->Draw();

	testGround->Draw();


	//オブジェクトを描画する
	testTree->Draw();




	//デバッグ表示 
	//40->一文字の幅/高さの二倍
	float posX = (-SCREEN_WIDTH / 2 + 40.0f) / SCREEN_PARA;//デバッグ表示の横座標設定
	float posY = ((SCREEN_HEIGHT / 2) - 40.0f) / SCREEN_PARA;//デバッグ表示の縦座標設定
	//位置を出力する
	g_DebugManager->PrintDebugLog(posX, posY, testTree->m_obj->m_sprite->m_pos.z);
	posY = ((SCREEN_HEIGHT / 2) - 80.0f) / SCREEN_PARA;//デバッグ表示の縦座標設定
	g_DebugManager->PrintDebugLog(posX, posY, testTree->m_shadow->m_obj->m_pos.z);
}

Game::~Game()
{
	
	delete testTree;
	delete testWall;
	delete testGround;
	delete testChara;

}

Game* Game::Get()
{
	static Game instance;
	return &instance;
}

void Game::GameDraw()
{

	D3D_ClearScreen();

	//============ ここから描画処理 ============//
	
	
	switch (m_gameScene)
		{
		case TITLE:

			TitleDraw();
			break;

		case STAGE1:

			StageDraw();
			break;

		case RESULT:

			ResultDraw();
			break;

		}

	//============ ここまで描画処理 ============//
	 
	//ダブルバッファの切り替えを行い画面を更新する
	GetD3D_DATA()->SwapChain->Present(0, 0);
}

void Game::TitleDraw(void)
{
	TestDraw();
}

void Game::StageDraw(void)
{
}

void Game::ResultDraw(void)
{
}

void Game::SetGameScene(GAMESCENE scene)
{
	m_gameScene = scene;
}

