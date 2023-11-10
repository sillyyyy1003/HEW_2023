#include "Game.h"
#include "Direct3D/Direct3D.h"
#include "Assets.h"
#include "ObjectAnimation.h"
#include "TrackCamera.h"
#include "KBInput.h"

extern Assets* g_Assets;
extern KBInput* g_KbInput;


Game::Game()
{
	////オブジェクト初期化
	//testObject = new Object(g_Assets->testchar01, 96, 96, 3, 4);
	////アニメーションクラス初期化->どのアニメーションにする
	//testObject->m_sprite->m_anime = new ObjectAnimation(3, 4);
	////アニメーション速度を設定
	//testObject->m_sprite->m_anime->SetAnimeSpeed(0.1f);
	////アニメーションパターンを設定
	//testObject->m_sprite->m_anime->SetAnimePattern(0);

	testObj = new TestObject();
	//オブジェクトの初期設定
	testObj->SetObjTex(g_Assets->testObj, 200, 200, 1, 1);
	testObj->m_objSprite->m_anime = new ObjectAnimation(1, 1);
	testObj->m_objSprite->m_anime->SetAnimeSpeed(0.0f);
	testObj->m_objSprite->m_anime->SetAnimePattern(0);
	testObj->m_objSprite->InitPos(-2, -1.16, 0.1f);
	

	//影の初期設定
	testObj->SetShadowTex(g_Assets->testShadow, 200, 200, 1, 1);
	testObj->m_shadowSprite->m_anime = new ObjectAnimation(1, 1);
	testObj->m_shadowSprite->m_anime->SetAnimeSpeed(0.0f);
	testObj->m_shadowSprite->m_anime->SetAnimePattern(0);
	testObj->m_shadowSprite->InitPos(1.7, 0.712, 0.2f);


	//オブジェクト初期化
	testBg = new Object(g_Assets->testbgbox, 1280, 720, 1, 1);
	testBg->m_sprite->m_pos.z = 0.9;//前後の位置設定をクラス化で行う
	//アニメーションクラス初期化->どのアニメーションにする
	testBg->m_sprite->m_anime = new ObjectAnimation(1, 1);
	//アニメーション速度を設定
	testBg->m_sprite->m_anime->SetAnimeSpeed(0.0f);
	//アニメーションパターンを設定
	testBg->m_sprite->m_anime->SetAnimePattern(0);

	


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
	testBg->Update();
	testObj->Update();
	//testObject->Update();
}

void Game::StageUpdate(void)
{
}

void Game::ResultUpdate(void)
{

}

Game::~Game()
{
	//delete testObject;
	delete testObj;
	delete testBg;
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
	testBg->m_sprite->Draw();

	testObj->Draw();


	//testBg->m_sprite->Draw();
	//testObject->m_sprite->Draw();
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
