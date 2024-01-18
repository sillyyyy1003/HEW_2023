#include "Game.h"
#include "Direct3D/Direct3D.h"
#include "Assets.h"
#include "ObjectAnimation.h"
#include "StaticAnimation.h"
#include "TrackCamera.h"
#include "DebugManager.h"
#include "DInput.h"

extern Assets* g_Assets;
extern Camera* g_WorldCamera;
extern DebugManager* g_DebugManager;


void Game::Init()
{
	//オブジェクト作成
	testWall = new Object(g_Assets->testWallbg, 1280, 720, 1, 1);
	testGround = new Object(g_Assets->testGroundbg, 1280, 720, 1, 1);
	testWall->m_sprite->m_scale = { 1.0, 1.0, 1.0 };

	testPause = new Object(g_Assets->testPause, 1280, 720, 1, 1);
	testPause->m_sprite->m_scale = { 1.0, 1.0, 1.0 };


	//オブジェクトの初期設定・テクスチャの読み込み
	testChara = new Object(g_Assets->testChara01, 32, 32, 3, 4);
	
	testTree = new GameObject();
	testTree->CreateObject(g_Assets->testObj, 300, 300, 1, 1);
	testTree->CreateShadow(g_Assets->testShadow, 300, 300, 1, 1);

	uitest = new CanvasUI();
	uitest->CreateModel(g_Assets->testPause, 128, 72, 1, 1);

	uitest->m_pos.z = 2.0f;
	
	//影の初期設定



	//アニメーションの設定
	testWall->m_sprite->m_anime = new StaticAnimation(1, 1);
	testPause->m_sprite->m_anime = new StaticAnimation(1, 1);// 追加
	testGround->m_sprite->m_anime = new ObjectAnimation(1, 1);
	testChara->m_sprite->m_anime = new ObjectAnimation(3, 4);
	testChara->m_sprite->m_anime->SetAnimeSpeed(0.2f);
	

	testTree->m_obj->m_anime = new StaticAnimation(1, 1);
	testTree->m_shadow->m_obj->m_anime = new StaticAnimation(1, 1);



	//初期位置設定
	testWall->m_sprite->m_pos = { 0.0f, 1.5f, 2.0f };
	testWall->m_sprite->m_scale = { 0.3f,0.3f,0.3f };

	testPause->m_sprite->m_pos = { 0.0f, 1.5f, -2.0f };
	testPause->m_sprite->m_scale = { 0.3f,0.3f,0.3f };

	testGround->m_sprite->m_pos = { 0.0f, 1.5f, 2.0f };
	testGround->m_sprite->m_rotation.x = 90;
	testGround->m_sprite->m_pos.y = -360 / SCREEN_PARA + 1.5f;

	testChara->m_sprite->m_pos.y = (-360 + 96) / SCREEN_PARA + 1.5f;
	testChara->m_sprite->m_pos.z = -0.5f;
	testChara->m_sprite->m_scale = { 3.0f,3.0f,3.0f };

	//影の位置設定
	testTree->m_shadow->m_obj->m_pos.z = 1.99f;

	//dynamic_cast<TrackCamera*>(g_WorldCamera)->SetTarget(testWall);

	
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

	if (isPause == false)
	{
		testTree->Update(testChara->m_sprite->m_pos);

		testChara->Update();
		testPause->Update();
		testWall->Update();
		uitest->Update();
	


	if (Input::Get()->GetKeyPress(DIK_UPARROW)) {
		testChara->m_sprite->m_pos.z += 0.1f;
		//testChara->m_sprite->m_rotation.x += 0.8f;
	}
	if (Input::Get()->GetKeyPress(DIK_LEFTARROW)) {
		testChara->m_sprite->m_pos.x -= 0.1f;
		//testChara->m_sprite->m_rotation.x -= 0.8f;
	}
	if (Input::Get()->GetKeyPress(DIK_RIGHTARROW)) {
		testChara->m_sprite->m_pos.x += 0.1f;
	}
	if (Input::Get()->GetKeyPress(DIK_DOWNARROW)) {
		testChara->m_sprite->m_pos.z -= 0.1f;
	}

	if (Input::Get()->GetKeyTrigger(DIK_SPACE)) {
		/*testChara->m_sprite->m_pos.x += 0.1f;*/
		testChara->m_sprite->SetMoveSpeed(0.05f);// 今後STOPできるようにする
	}
}

	if (Input::Get()->GetKeyTrigger(DIK_ESCAPE))
	{
		if (isPause)
		{
			isPause = false;
		}
		else
		{
			isPause = true;
		}
	}


	//マウスでキャラを回転テスト
	//testChara->m_sprite->RotateObj(testChara->m_sprite->m_rotation);
	

	

	//背景
	testGround->Update();
	





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

	delete testTree;
	delete uitest;
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

	if (isPause)
	{


		testTree->Draw();
		testChara->Draw();
		testChara->m_sprite->m_anime->SetAnimeSpeed(0.0f);
		testPause->Draw();
		return;
	}
	testChara->m_sprite->m_anime->SetAnimeSpeed(0.2f);
	
	//testWall->Draw();

	//testWall->Draw();

	//testGround->Draw();

	testTree->Draw();

	testChara->Draw();


	//デバッグ表示 
	//40->一文字の幅/高さの二倍
	float posX = (-SCREEN_WIDTH / 2 + 40.0f) / SCREEN_PARA;
	float posY = ((SCREEN_HEIGHT / 2) - 40.0f) / SCREEN_PARA;
	g_DebugManager->PrintDebugLog(posX, posY, testChara->m_sprite->m_pos.x);

	



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

