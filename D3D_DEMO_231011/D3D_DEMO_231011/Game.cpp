#include "Game.h"
#include "Direct3D/Direct3D.h"
#include "Assets.h"
#include "TrackCamera.h"
#include "GameObject.h"
#include "StaticObject.h"
#include "DebugManager.h"
#include "Animation.h"
#include "StaticAnimation.h"
#include "ObjectAnimation.h"
#include "DInput.h"

#include "SAT.h"
#include <algorithm> // 必要なヘッダーファイル
#define SQUREWIDTH 1.2
#define TRIANGLEWIDTH 0.8
#define M_PI 3.14159265358979323846
#define M_PIX 0.1//1.5
#define M_PIY 0.0333333333// 0.5

extern Assets* g_Assets;
extern Camera* g_WorldCamera;
extern DebugManager* g_DebugManager;


void Game::Init()
{

	//カメラの追跡ターゲットを設定する
	//dynamic_cast<TrackCamera*>(g_WorldCamera)->SetTarget(testWall);

	testTree = new GameObject();
	
	//モデルを作る
	testTree->CreateObject(g_Assets->testObj, 200, 200, 1, 1);
	testTree->CreateShadow(g_Assets->testShadow, 200, 200, 1, 1);
	//アニメションを配置
	testTree->m_obj->m_anime = new StaticAnimation(1,1);
	testTree->m_shadow->m_obj->m_anime = new StaticAnimation(1, 1);
	//オブジェクトを位置を配置する
	testTree->m_obj->m_pos = { 2, 2, -1 };

	
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
	//光源の位置をリアルタイムで更新する
	testTree->Update({ 0, 0, -2 });


}

void Game::StageUpdate(void)
{
}


void Game::ResultUpdate(void)
{

}

Game::~Game()
{
	
	delete testTree;

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

	//オブジェクトを描画する
	testTree->Draw();

	// testChara->Draw();
	// testObj4->Draw();

	//デバッグ表示 
	//40->一文字の幅/高さの二倍
	float posX = (-SCREEN_WIDTH / 2 + 40.0f) / SCREEN_PARA;//デバッグ表示の横座標設定
	float posY = ((SCREEN_HEIGHT / 2) - 40.0f) / SCREEN_PARA;//デバッグ表示の縦座標設定
	//位置を出力する
	g_DebugManager->PrintDebugLog(posX, posY, testTree->m_obj->m_pos.z);

	
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


