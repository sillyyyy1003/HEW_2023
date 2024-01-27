﻿#include "Game.h"

#include "Assets.h"
#include "TrackCamera.h"

#include "GameObject.h"
#include "ShadowObject.h"
#include "StaticObject.h"

#include "DebugManager.h"
#include "SceneManager.h"

#include "Animation.h"
#include "StaticAnimation.h"
#include "ObjectAnimation.h"

#include "DInput.h"
#include <stdio.h> 
#include "ColliderManager.h"

#define INITROTATE	(19.8)

extern Assets* g_Assets;
extern Camera* g_WorldCamera;
extern DebugManager* g_DebugManager;

void Game::Init()
{
	//オブジェクト作成
	uiTitle = new CanvasUI();
	uiTitleBg = new CanvasUI();
	uiPressEnter = new CanvasUI();
	uiRestart = new CanvasUI();
	uiResume = new CanvasUI();
	uiPauseBg = new CanvasUI();


	stageBg = new StaticObject();
	circle = new GameObject();
	triangle = new GameObject();
	square = new GameObject();

	//テクスチャ読み込み・モデル作成
	uiTitle->CreateModel(g_Assets->uiTitle, 1280, 300, 1, 1);
	uiTitleBg->CreateModel(g_Assets->uiTitleBg, 1280, 720, 1, 1);
	uiPressEnter->CreateModel(g_Assets->uiPressEnter, 1280, 300, 1, 1);

	uiPauseBg->CreateModel(g_Assets->uiPauseBg, 600, 720, 1, 1);

	
	stageBg->CreateObject(g_Assets->stageBg, 1280, 720, 1, 1);

	//モデルを作る
	circle->CreateObject(g_Assets->circle, 200, 200, 1, 1);
	circle->CreateShadow(g_Assets->circle, 200, 200, 1, 1);
	//アニメションを配置
	circle->m_shadow->m_sprite->m_anime = new StaticAnimation(1, 1);	//影
	circle->m_obj->m_sprite->m_anime = new StaticAnimation(1, 1);	//影
	//オブジェクトの位置を配置
	//circle->m_shadow->m_sprite->m_pos = { 0, 0, 0 };
	circle->m_obj->m_sprite->m_pos = { 8, 0, -2 };
	//オブジェクトのコライダーを配置
	circle->m_shadowCollider = new SphereCollider({},3.0f);
	circle->m_objCollider = new SphereCollider({}, 3.0f);
	//circle->isPlayer = true;

	//モデルを作る
	triangle->CreateObject(g_Assets->triangle, 200, 200, 1, 1);
	triangle->CreateShadow(g_Assets->triangle, 200, 200, 1, 1);
	//アニメションを配置
	triangle->m_shadow->m_sprite->m_anime = new StaticAnimation(1, 1);	//影
	triangle->m_obj->m_sprite->m_anime = new StaticAnimation(1, 1);	//影
	//オブジェクトの位置を配置
	triangle->m_obj->m_sprite->m_pos = { 0, 0, -2 };
	//オブジェクトのコライダーを配置
	triangle->m_shadowCollider = new PolygonCollider({},2.3f);
	triangle->m_objCollider = new PolygonCollider({}, 2.3f);
	triangle->isPlayer = true;

	//モデルを作る
	square->CreateObject(g_Assets->square, 200, 200, 1, 1);
	square->CreateShadow(g_Assets->square, 200, 200, 1, 1);
	//アニメションを配置
	square->m_shadow->m_sprite->m_anime = new StaticAnimation(1, 1);	//影
	square->m_obj->m_sprite->m_anime = new StaticAnimation(1, 1);	//影
	//オブジェクトの位置を配置
	square->m_obj->m_sprite->m_pos = { -8, 2, -2 };
	//オブジェクトのコライダーを配置
	square->m_shadowCollider = new BoxCollider({}, { 3,3,3 });
	square->m_objCollider = new BoxCollider({}, { 3,3,3 });
	//square->isPlayer = true;

	for (int i = 0; i < sizeof(ex) / sizeof(ex[0]); ++i)
	{
		ex[i] = new GameObject();

		//モデルを作る
		ex[i]->CreateObject(g_Assets->ex, 100, 100, 1, 1);
		ex[i]->CreateShadow(g_Assets->ex, 100, 100, 1, 1);
		//アニメションを配置
		ex[i]->m_shadow->m_sprite->m_anime = new StaticAnimation(1, 1);	//影
		ex[i]->m_obj->m_sprite->m_anime = new StaticAnimation(1, 1);	//影
		//オブジェクトの位置を配置
		ex[i]->m_obj->m_sprite->m_pos = { 0, 0, -4 };
		ex[i]->isEx = true;
		ex[i]->isPlayer = true;
	}

	object[POLYGON] = new GameObject();
	//モデルを作る
	object[POLYGON]->CreateObject(g_Assets->triangle, 200, 200, 1, 1);
	object[POLYGON]->CreateShadow(g_Assets->triangle, 200, 200, 1, 1);
	//アニメションを配置
	object[POLYGON]->m_shadow->m_sprite->m_anime = new StaticAnimation(1, 1);	//影
	object[POLYGON]->m_obj->m_sprite->m_anime = new StaticAnimation(1, 1);	//影
	//オブジェクトの位置を配置
	object[POLYGON]->m_obj->m_sprite->m_pos = { 0, 0, -2 };
	//オブジェクトのコライダーを配置
	object[POLYGON]->m_shadowCollider = new PolygonCollider({}, 2.3f);
	object[POLYGON]->m_objCollider = new PolygonCollider({}, 2.3f);
	object[POLYGON]->isPlayer = true;

	object[SQUARE] = new GameObject();

	object[SQUARE]->CreateObject(g_Assets->square, 200, 200, 1, 1);
	object[SQUARE]->CreateShadow(g_Assets->square, 200, 200, 1, 1);
	//アニメションを配置
	object[SQUARE]->m_shadow->m_sprite->m_anime = new StaticAnimation(1, 1);	//影
	object[SQUARE]->m_obj->m_sprite->m_anime = new StaticAnimation(1, 1);	//影
	//オブジェクトの位置を配置
	object[SQUARE]->m_obj->m_sprite->m_pos = { -8, 2, -2 };
	//オブジェクトのコライダーを配置
	object[SQUARE]->m_shadowCollider = new BoxCollider({}, { 3,3,3 });
	object[SQUARE]->m_objCollider = new BoxCollider({}, { 3,3,3 });
	//object[SQUARE]->isPlayer = true;

	object[SPHERE] = new GameObject();

	object[SPHERE]->CreateObject(g_Assets->circle, 200, 200, 1, 1);
	object[SPHERE]->CreateShadow(g_Assets->circle, 200, 200, 1, 1);
	//アニメションを配置
	object[SPHERE]->m_shadow->m_sprite->m_anime = new StaticAnimation(1, 1);	//影
	object[SPHERE]->m_obj->m_sprite->m_anime = new StaticAnimation(1, 1);	//影
	//オブジェクトの位置を配置
	//circle->m_shadow->m_sprite->m_pos = { 0, 0, 0 };
	object[SPHERE]->m_obj->m_sprite->m_pos = { 8, 0, -2 };
	//オブジェクトのコライダーを配置
	object[SPHERE]->m_shadowCollider = new SphereCollider({}, 3.0f);
	object[SPHERE]->m_objCollider = new SphereCollider({}, 3.0f);
	//object[SPHERE]->isPlayer = true;

	//アニメーションの設定


	//初期位置設定


	//影の位置設定


	//dynamic_cast<TrackCamera*>(g_WorldCamera)->SetTarget(testWall);

	
	//----------------------------//
	// ここからはエフェクトの初期化
	//----------------------------//


	//----------------------------//
	// ここからはシーンの初期化
	//----------------------------//
	
	//Title の初期化
	//位置設定
	uiTitleBg->m_pos = { 0.0f,0.0f,0.2f };
	uiTitle->m_pos = { 0.0f,1.5f,0.1f };
	uiPressEnter->m_pos = { 0.0f,-1.5f,0.0f };

	//大きさの設定
	uiTitle->m_scale = { 0.8,0.8,1.0 };
	uiPressEnter->m_scale = { 0.3,0.3,1.0 };
	

	//uiPause
	uiPauseBg->m_pos={ - 300 / SCREEN_PARA, 0.0, 0.9f };

	SceneManager::Get()->SetScene(SCENENAME::TITLE);
	
}

void Game::InitStage()
{
	//ステージの初期化
	switch (SceneManager::Get()->GetStage()) {

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

	}
}

void Game::InitStage1_1(void)
{
	//位置設定
	stageBg->m_sprite->m_rotation.x = 19.8;

	stageBg->m_sprite->m_scale = { 2.6,2.6,1.0 };
	
	for (int i = 0; i < sizeof(ex) / sizeof(ex[0]); ++i)
	{
		ex[i]->m_obj->m_sprite->m_rotation.x = 19.8;
	}

	for (int i = 0; i < sizeof(object) / sizeof(object[0]); ++i)
	{
		object[i]->m_obj->m_sprite->m_scale = { 2.6,2.6,1.0 };
		object[i]->m_obj->m_sprite->m_rotation.x = 19.8;
	}

	//大きさ設定


	//回転設定

}

void Game::InitStage1_2(void)
{
}

void Game::InitStage1_3(void)
{
}

void Game::InitStage2_1(void)
{
}

void Game::InitStage2_2(void)
{
}

void Game::InitStage2_3(void)
{
}

void Game::InitStage3_1(void)
{
}

void Game::InitStage3_2(void)
{
}

void Game::InitStage3_3(void)
{
}

void Game::TitleUpdate(void)
{	
	//エンターキーを押すと　ステージセレクト画面に遷移
	if (Input::Get()->GetKeyTrigger(DIK_RETURN)) {

		//SceneManager::Get()->SetScene(STAGESELECT);

		//Init SelectScene Data
		
		//シーン遷移を行う
		SceneManager::Get()->SetScene(SCENENAME::STAGE);

		//次のシーンを設定する
		SceneManager::Get()->SetNextScene(SCENENAME::STAGE);


		SceneManager::Get()->SetStage(STAGEINFO::STAGE1_1);
		
		//ステージ内のオブジェクトを配置
		InitStage();

	}

	uiPressEnter->Update();
	uiTitle->Update();
	uiTitleBg->Update();

}

void Game::SelectUpdate(void)
{
}

void Game::StageUpdate(void)
{
	//Input
	if (Input::Get()->GetKeyTrigger(DIK_ESCAPE)) {
		if (isPause) 
		{
			isPause = false;
		}
		else
		{
			isPause = true;
		}
	}


	if (!isPause) {
		switch (SceneManager::Get()->GetStage()) {

		case STAGE1_1:

			UpdateStage1_1();

			break;

		case STAGE1_2:


			break;

		case STAGE1_3:


			break;

		case STAGE2_1:


			break;

		case STAGE2_2:



			break;

		case STAGE2_3:



			break;

		case STAGE3_1:



			break;
		case STAGE3_2:



			break;

		case STAGE3_3:



			break;

		}

	}
	else {
		UiUpdate();
	}

}

void Game::UpdateStage1_1(void)
{
	stageBg->Update();

	for (int i = 0; i < sizeof(object) / sizeof(object[0]); ++i)
	{
		object[i]->Update();
	}

	for (int j = 0; j < sizeof(object) / sizeof(object[0]); ++j)
	{
		for (int i = 1+j; i < sizeof(object) / sizeof(object[0]); ++i)
		{
			if (object[i]->m_objCollider->GetColliderType() == SQUARE)
			{
				if (object[j]->m_objCollider->isBoxCollision(object[i]->m_objCollider))
				{
					if (object[i]->isPlayer)
					{
						object[j]->m_objCollider->isActive = false;
					}
					else
					{
						object[i]->m_objCollider->isActive = false;
					}
				}
			}
			else if (object[i]->m_objCollider->GetColliderType() == SPHERE)
			{
				if (object[j]->m_objCollider->isSphereCollision(object[i]->m_objCollider))
				{
					if (object[i]->isPlayer)
					{
						object[j]->m_objCollider->isActive = false;
					}
					else
					{
						object[i]->m_objCollider->isActive = false;
					}
				}
			}
			else if (object[i]->m_objCollider->GetColliderType() == POLYGON)
			{
				if (object[j]->m_objCollider->isPolygonCollision(object[i]->m_objCollider))
				{
					if (object[i]->isPlayer)
					{
						object[j]->m_objCollider->isActive = false;
					}
					else
					{
						object[i]->m_objCollider->isActive = false;
					}
				}
			}
		}
	}
	

	//std::vector<Vector3> verticies = triangle->m_objCollider->GetVerticies();
	//for (int i = 0; i < sizeof(ex) / sizeof(ex[0]); ++i)
	//{
	//	ex[i]->m_obj->m_sprite->m_pos.x = verticies[i].x;
	//	ex[i]->m_obj->m_sprite->m_pos.y = verticies[i].y;
	//	ex[i]->Update();
	//}
}

void Game::UpdateStage1_2(void)
{
}

void Game::UpdateStage1_3(void)
{
}

void Game::UpdateStage2_1(void)
{
}

void Game::UpdateStage2_2(void)
{
}

void Game::UpdateStage2_3(void)
{
}

void Game::UpdateStage3_1(void)
{
}

void Game::UpdateStage3_2(void)
{
}

void Game::UpdateStage3_3(void)
{
}

void Game::GameUpdate(void)
{
	//入力処理　XXキー押して、移動させるオブジェクトをスイッチ

	//オブジェクトUpdate

	switch (SceneManager::Get()->GetScene()) {
	case SCENENAME::TITLE:
		TitleUpdate();
		break;

	case SCENENAME::STAGESELECT:
		SelectUpdate();
		break;

	case SCENENAME::STAGE:
		StageUpdate();
		break;
	}


}



Game::~Game()
{
	delete uiTitle;		//タイトル文字
	delete uiTitleBg;		//タイトル背景
	delete uiPressEnter;	//タイトルエンターキー

	delete uiResume;
	delete uiPauseBg;
	delete uiRestart;	//ステージのボタン

	delete stageBg;		//ステージ背景
	delete circle;		//円
	delete triangle;	//三角
	delete square;		//四角
	for (int i = 0; i < sizeof(ex) / sizeof(ex[0]); ++i)
	{
		delete ex[i];
	}
	for (int i = 0; i < sizeof(object) / sizeof(object[0]); ++i)
	{
		delete object[i];
	}


	//delete circle;			//circle



}

Game* Game::Get()
{
	static Game instance;
	return &instance;
}

void Game::UiUpdate()
{
	//入力操作



	uiPauseBg->Update();
	//uiRestart->Update();
	//uiResume->Update();

}

void Game::GameDraw()
{

	D3D_ClearScreen();

	//============ ここから描画処理 ============//
	
	switch (SceneManager::Get()->GetScene()) {
	case SCENENAME::TITLE:
		TitleDraw();
		break;

	case SCENENAME::STAGE:
		StageDraw();
		break;

	default:
		break;
	}


	//============ ここまで描画処理 ============//
	 
	//ダブルバッファの切り替えを行い画面を更新する
	GetD3D_DATA()->SwapChain->Present(0, 0);
}

void Game::TitleDraw(void)
{
	uiTitleBg->Draw();

	uiTitle->Draw();

	uiPressEnter->Draw();	

	//===================Debug=====================//
	/*
	//デバッグ表示 
	//40->一文字の幅/高さの二倍
	float posX = (-SCREEN_WIDTH / 2 + 40.0f) / SCREEN_PARA;
	float posY = ((SCREEN_HEIGHT / 2) - 40.0f) / SCREEN_PARA;
	g_DebugManager->PrintDebugLog(posX, posY, testChara->m_sprite->m_pos.x);
	*/

}

void Game::StageDraw(void)
{

	switch (SceneManager::Get()->GetStage()) {

	case STAGE1_1:

		DrawStage1_1();

		break;

	case STAGE1_2:


		break;

	case STAGE1_3:


		break;

	case STAGE2_1:


		break;

	case STAGE2_2:



		break;

	case STAGE2_3:



		break;

	case STAGE3_1:



		break;
	case STAGE3_2:



		break;

	case STAGE3_3:



		break;

	}

	if (isPause) {
		UiDraw();
	}
}

void Game::DrawStage1_1()
{
	stageBg->Draw();
	for (int i = 0; i < sizeof(ex) / sizeof(ex[0]); ++i)
	{
		ex[i]->Draw();
	}
	for (int i = 0; i < sizeof(object) / sizeof(object[0]); ++i)
	{
		if (object[i]->m_objCollider->isActive)
		{
			object[i]->Draw();
		}
	}
}



void Game::ResultDraw(void)
{
}

void Game::UiDraw(void)
{
	uiPauseBg->Draw();
	//uiResume->Draw();
	//uiRestart->Draw();
}
