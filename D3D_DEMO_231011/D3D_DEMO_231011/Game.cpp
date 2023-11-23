#include "Game.h"
#include "Direct3D/Direct3D.h"
#include "Assets.h"
#include "ObjectAnimation.h"
#include "StaticAnimation.h"
#include "TrackCamera.h"
#include "KBInput.h"

extern Assets* g_Assets;
extern KBInput* g_KbInput;
extern TrackCamera* g_WorldCamera;


Game::Game()
{
	//オブジェクト作成
	testWall = new Object(g_Assets->testWallbg, 1280, 720, 1, 1);
	testGround = new Object(g_Assets->testGroundbg, 1280, 720, 1, 1);

	//オブジェクトの初期設定・テクスチャの読み込み
	testChara = new Object(g_Assets->testChara01, 32, 32, 3, 4);

	testTree = new GameObject();
	testTree->CreateObject(g_Assets->testObj, 300, 300, 1, 1);
	testTree->CreateShadow(g_Assets->testShadow, 300, 300, 1, 1);

	

	//影の初期設定



	//アニメーションの設定
	testWall->m_sprite->m_anime = new StaticAnimation(1, 1);
	testGround->m_sprite->m_anime = new ObjectAnimation(1, 1);
	testChara->m_sprite->m_anime = new ObjectAnimation(3, 4);
	testChara->m_sprite->m_anime->SetAnimeSpeed(0.2f);

	testTree->m_obj->m_anime = new StaticAnimation(1, 1);
	testTree->m_shadow->m_obj->m_anime = new StaticAnimation(1, 1);



	//初期位置設定
	testWall->m_sprite->m_pos = { 0.0f, 1.5f, 2.0f };

	testGround->m_sprite->m_pos = { 0.0f, 1.5f,2.0f};

	testGround->m_sprite->m_rotation.x = 90;
	testGround->m_sprite->m_pos.y = -360 * 1.25 / 96 + 1.5f;

	testChara->m_sprite->m_pos.y = (-360 + 96) * 1.25 / 96 + 1.5f;
	testChara->m_sprite->m_pos.z = -0.5f;
	testChara->m_sprite->m_scale = { 3.0f,3.0f,3.0f };

	//影の位置設定
	testTree->m_shadow->m_obj->m_pos.z = 1.99f;

	//g_WorldCamera->TrackCamera::SetTarget(testChara);

	
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

	
	
	
	if (g_KbInput->GetKeyPress(VK_UP))
	{
		testChara->m_sprite->m_pos.z += 0.02f;

	}
	if (g_KbInput->GetKeyPress(VK_DOWN)) {
		testChara->m_sprite->m_pos.z -= 0.02f;
	}

	if (g_KbInput->GetKeyPress(VK_LEFT)) {
		testChara->m_sprite->m_pos.x -= 0.02f;
	}

	if (g_KbInput->GetKeyPress(VK_RIGHT)) {
		testChara->m_sprite->m_pos.x += 0.02f;
	}


	testWall->Update();

	//背景
	testGround->Update();
	testChara->Update();

	testTree->Update(XMFLOAT3{ 0.0f, 0.0f, -2.0f });

}

void Game::StageUpdate(void)
{
}


void Game::ResultUpdate(void)
{

}

Game::~Game()
{
	delete testChara;
	delete testWall;
	delete testGround;

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
	testWall->Draw();

	testGround->Draw();

	testChara->Draw();

	testTree->Draw();


	
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

