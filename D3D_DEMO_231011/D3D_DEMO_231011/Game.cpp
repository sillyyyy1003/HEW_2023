#include "Game.h"

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

#include "RailManager.h"
#include "DInput.h"
#include <stdio.h>

#include "ColliderManager.h"

#define MOVE 0.3f
#define INITROTATE	(19.8)

extern Assets* g_Assets;
extern Camera* g_WorldCamera;
extern DebugManager* g_DebugManager;

// （TODO）
// 正しい大きさと形になった時のクリア判定


void Game::Init()
{
	//オブジェクト作成
	uiTitle = new CanvasUI();
	uiTitleBg = new CanvasUI();
	uiPressEnter = new CanvasUI();
	uiRestart = new CanvasUI();
	uiResume = new CanvasUI();
	uiPauseBg = new CanvasUI();


	circle = new GameObject();

	//stage1-1
	stageBg = new StaticObject();
	coconut = new GameObject();
	lamp = new GameObject();
	housePlate = new GameObject();

	testObj = new GameObject();



	//stage1に使われてる

	//テクスチャ読み込み・モデル作成
	uiTitle->CreateModel(g_Assets->uiTitle, 1280, 300, 1, 1);
	uiTitleBg->CreateModel(g_Assets->uiTitleBg, 1280, 720, 1, 1);
	uiPressEnter->CreateModel(g_Assets->uiPressEnter, 1280, 300, 1, 1);
	uiPauseBg->CreateModel(g_Assets->uiPauseBg, 600, 720, 1, 1);


	stageBg->CreateObject(g_Assets->stageBg, 1280, 720, 1, 1);
	testObj->CreateObject(g_Assets->tree, 200, 200, 1, 1);
	testObj->CreateShadow(g_Assets->shadow, 200, 200, 1, 1);

	coconut->CreateObject(g_Assets->coconut, 190, 190, 1, 1);
	coconut->CreateShadow(g_Assets->coconutShadow, 190, 190, 1, 1);
	
	lamp->CreateObject(g_Assets->lamp, 163, 569, 1, 1);
	lamp->CreateShadow(g_Assets->lampShadow, 163, 569, 1, 1);
	housePlate->CreateObject(g_Assets->housePlate, 216, 110, 1, 1);
	housePlate->CreateShadow(g_Assets->housePlateShadow, 216, 110, 1, 1);


	//アニメーションの設定
	testObj->InitAnimation();
	coconut->InitAnimation();
	lamp->InitAnimation();
	housePlate->InitAnimation();

	//dynamic_cast<TrackCamera*>(g_WorldCamera)->SetTarget(testWall);

	// 追加
	for (int i = 0; i < sizeof(ex) / sizeof(ex[0]); ++i)
	{
		ex[i] = new GameObject();

		//モデルを作る
		ex[i]->CreateObject(g_Assets->ex, 70, 70, 1, 1);
		ex[i]->CreateShadow(g_Assets->ex, 70, 70, 1, 1);
		//アニメションを配置
		ex[i]->InitAnimation();	
	}

	// 引数１：オブジェクトの型　引数２：操作するかどうか
	
	// 三角
	CreateGameobject(POLYGON,true);
	// 円
	CreateGameobject(SPHERE, false);
	// 四角
	CreateGameobject(SQUARE, false);

	CreateGameobject(POLYGON, false);

	// １：三角２：円３：四角の順に並べる
	SortGameobject();
	
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

void Game::CreateGameobject(int TYPE, bool Move)
{
	GameObject* object;

	object = new GameObject();
	//アニメションを配置
	object->InitAnimation();
	//オブジェクトのコライダーを配置
	if (TYPE == POLYGON)
	{
		//三角を作る
		object->CreateObject(g_Assets->triangle, 200, 200, 1, 1);
		object->CreateShadow(g_Assets->triangle, 200, 200, 1, 1);
		object->m_shadowCollider = new PolygonCollider({}, 0.9f);
	}
	else if (TYPE == SQUARE)
	{
		//四角を作る
		object->CreateObject(g_Assets->square, 200, 200, 1, 1);
		object->CreateShadow(g_Assets->square, 200, 200, 1, 1);
		object->m_shadowCollider = new BoxCollider({}, { 1,1,1 });

	}
	else if (TYPE == SPHERE)
	{
		//円を作る
		object->CreateObject(g_Assets->circle, 200, 200, 1, 1);
		object->CreateShadow(g_Assets->circle, 200, 200, 1, 1);
		object->m_shadowCollider = new SphereCollider({}, 1.0f);
	}
	object->SetActive(Move);
	
	Vobject.push_back(object);
}

void Game::SortGameobject()
{
	// 並べ替え用にリストを作る
	std::list<GameObject*> object[3];
	// 元のリストのIDを並べ替え用にリストに入れる
	for (GameObject* game : Vobject)
	{
		if (POLYGON == game->m_shadowCollider->GetColliderType())
		{
			object[0].push_back(game);
			objectNum[POLYGON]++;
		}
		else if (SPHERE == game->m_shadowCollider->GetColliderType())
		{
			object[1].push_back(game);
			objectNum[SPHERE]++;
		}
		else
		{
			object[2].push_back(game);
		}
	}
	objectNum[POLYGON] = objectNum[POLYGON] - 1;
	objectNum[SPHERE] = objectNum[POLYGON] + objectNum[SPHERE]-1;

	for (GameObject* game : object[1])
	{
		object[0].push_back(game);
	}

	for (GameObject* game : object[2])
	{
		object[0].push_back(game);
	}

	Vobject.clear();
	// 並べ替えたIDを元のリストに入れる
	for (GameObject* game : object[0])
	{
		Vobject.push_back(game);
	}

	// 円
	Sphere = SPHERE + objectNum[POLYGON];
	// 四角
	Square = SQUARE + objectNum[SPHERE];
}

void Game::InitStage1_1(void)
{
	//位置設定
	//光源の位置を設定する

	m_lightPos = { 0,0,-10 };
	testObj->SetLightPos(m_lightPos);

	//オブジェクトを設定する
	stageBg->m_sprite->m_pos = { 0,-0.36,1 };//固定!!

	testObj->m_obj->m_sprite->m_pos = { 0,-3,-2 };//y軸固定!!
	testObj->m_shadow->m_sprite->m_pos.z = -1.0f;//影のY/Z軸を固定!!

	coconut->m_obj->m_sprite->m_pos = { -5,-3,-8 };
	coconut->m_shadow->m_sprite->m_pos.z = 0.0f;
	
	lamp->m_obj->m_sprite->m_pos = { 5,-3,-4};
	lamp->m_shadow->m_sprite->m_pos.z = 0.0f;

	housePlate->m_obj->m_sprite->m_pos = { -5,-3,-4 };
	housePlate->m_shadow->m_sprite->m_pos.z = 0.0f;

	Vobject[POLYGON]->m_shadow->m_sprite->m_pos = { 0, 3, -1 };
	Vobject[POLYGON]->m_obj->m_sprite->m_pos = { 0, -5, -2 };

	Vobject[Sphere]->m_shadow->m_sprite->m_pos = { -10, 3, -1 };
	Vobject[Sphere]->m_obj->m_sprite->m_pos = { -10, -5, -2 };

	Vobject[Square]->m_shadow->m_sprite->m_pos = { 10, 3, -1 };
	Vobject[Square]->m_obj->m_sprite->m_pos = { 10, -5, -2 };

	Vobject[POLYGON+1]->m_shadow->m_sprite->m_pos = { 0, 8, -1 };
	Vobject[POLYGON+1]->m_obj->m_sprite->m_pos = { 0, 8, -2 };

	for (int i = 0; i < sizeof(ex) / sizeof(ex[0]); ++i)
	{
		ex[i]->m_shadow->m_sprite->m_pos.z = -1;
	}

	//大きさ設定
	stageBg->m_sprite->m_scale = { 2.725,2.725,1.0 };//固定値

	//回転設定
	stageBg->m_sprite->m_rotation.x = 19.8;//カメラと垂直状態を保持するため

	//レールの設定
	RailInit1_1();

	//ステージ情報を初期化
	for (int i = 0; i < 9; i++) {
		//全部のステージを無効かにする
		SceneManager::Get()->m_stageHolder[i]->Init();

	}
	//使うステージだけ起動
	SceneManager::Get()->m_stageHolder[STAGEINFO::STAGE1_1]->SetActive(true);

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

void Game::RailInit1_1(void)
{
	//空いてるかどうかを設定する
	int posData[15] =
	{
		0,0,1,1,0,
		0,0,1,0,0,
		0,0,0,0,0
	};

	for (int i = 0; i < 15; i++) {

		if (posData[i] == 1) {

			RailManager::Get()->m_info[i].isVacant = true;
		}
		else {

			RailManager::Get()->m_info[i].isVacant = 0;
		}

	}


	bool railData[15][8]{
		//back row
		//up	ru  r	rd d	ld l	lu
		{	0,	0,	0,	0,	0,	0,	0,	0},//0
		{	0,	0,	1,	0,	0,	0,	0,	0},//1
		{	0,	0,	1,	0,	1,	0,	1,	0},//2
		{	0,	0,	1,	0,	0,	0,	1,	0},//3
		{	0,	0,	0,	0,	0,	0,	1,	0},//4

		//mid row
		{	0,	0,	0,	0,	0,	0,	0,	0},
		{	0,	0,	0,	0,	0,	0,	0,	0},
		{	1,	0,	0,	0,	1,	0,	0,	0},
		{	0,	0,	0,	0,	0,	0,	0,	0},
		{	0,	0,	0,	0,	0,	0,	0,	0},

		//front row
		{	0,	0,	0,	0,	0,	0,	0,	0},
		{	0,	0,	0,	0,	0,	0,	0,	0},
		{	1,	0,	0,	0,	0,	0,	0,	0},
		{	0,	0,	0,	0,	0,	0,	0,	0},
		{	0,	0,	0,	0,	0,	0,	0,	0},
	};

	//道を設定する
	for (int i = 0; i < 15; i++) {

		for (int j = 0; j < 8; j++) {

			if (railData[i][j] == 0) {
			
				RailManager::Get()->m_info[i].isMoveable[j] = false;
			
			}
			else {
				RailManager::Get()->m_info[i].isMoveable[j] = true;

			}
			
		}


	}

}

void Game::RailInit1_2(void)
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
			isPause = 0;
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
	for (GameObject* game : Vobject)
	{
		if (game->GetActive())
		{
			TestMove(game);
		}
	}
	
	//移動させる目標を設定する
	if (Input::Get()->GetKeyTrigger(DIK_TAB)) {
		
		if (coconut->GetActive()) {
			coconut->SetActive(false);
			lamp->SetActive(true);
		}
		if (lamp->GetActive()) {
			lamp->SetActive(false);
			housePlate->SetActive(true);
		}
		if (housePlate->GetActive()) {
			housePlate->SetActive(false);
			coconut->SetActive(true);
		}
		
	}

	coconut->Update();
	lamp->Update();
	housePlate->Update();

	stageBg->Update();

	for (GameObject* game : Vobject)
	{
		game->Update();
	}

	// 当たり判定
	ColliderManager::Collision(Vobject);

	// クリアの判定
	if (ColliderManager::ClearCollision(Vobject, POLYGON+1, POLYGON, 0, ShadowObject::SIZE::MEDIUM))
	{
		isPause = 1;
		//SceneManager::Get()->SetScene(SCENENAME::RESULT);
	}

	// 頂点確認用
	std::vector<Vector3> verticies = Vobject[POLYGON+1]->m_shadowCollider->GetVerticies();
	for (int i = 0; i < sizeof(ex) / sizeof(ex[0]); ++i)
	{
		ex[i]->m_shadow->m_sprite->m_pos.x = verticies[i].x;
		ex[i]->m_shadow->m_sprite->m_pos.y = verticies[i].y;
		ex[i]->Update();
	}
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
	delete coconut;
	delete lamp;
	delete housePlate;

	for (int i = 0; i < sizeof(ex) / sizeof(ex[0]); ++i)
	{
		delete ex[i];
	}
	Vobject.clear();
	for (GameObject* game : Vobject)
	{
		delete game;
	}

	delete circle;
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
		ex[i]->m_shadow->Draw();
	}
	//testObj->Draw();

	for (GameObject* game : Vobject)
	{
		if (game->m_shadowCollider->isActive)
		{
			game->Draw();
		}
	}

	coconut->m_shadow->Draw();
	lamp->m_shadow->Draw();
	housePlate->m_shadow->Draw();
	
	coconut->m_obj->Draw();
	lamp->m_obj->Draw();
	housePlate->m_obj->Draw();


	//描画の順番を並び変え


	float posX = (-SCREEN_WIDTH / 2 + 40.0f) / SCREEN_PARA;
	float posY = ((SCREEN_HEIGHT / 2) - 40.0f) / SCREEN_PARA;

	g_DebugManager->PrintDebugLog(posX, posY, testObj->m_obj->m_sprite->m_pos.x);

	posY = ((SCREEN_HEIGHT / 2) - 80.0f) / SCREEN_PARA;
	g_DebugManager->PrintDebugLog(posX, posY, testObj->m_obj->m_sprite->m_pos.y);

	posY = ((SCREEN_HEIGHT / 2) - 120.0f) / SCREEN_PARA;
	g_DebugManager->PrintDebugLog(posX, posY, testObj->m_obj->m_sprite->m_pos.z);
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

void Game::TestMove(GameObject* _target)
{
	if (Input::Get()->GetKeyPress(DIK_E)) {
		_target->m_obj->m_sprite->m_pos.z += MOVE;
	}
	if (Input::Get()->GetKeyPress(DIK_A)) {
		_target->m_obj->m_sprite->m_pos.x -= MOVE;
	}
	if (Input::Get()->GetKeyPress(DIK_D)) {
		_target->m_obj->m_sprite->m_pos.x += MOVE;
	}
	if (Input::Get()->GetKeyPress(DIK_Q)) {
		_target->m_obj->m_sprite->m_pos.z -= MOVE;
	}
	if (Input::Get()->GetKeyPress(DIK_W)) {
		_target->m_obj->m_sprite->m_pos.y += MOVE;
	}
	if (Input::Get()->GetKeyPress(DIK_S)) {
		_target->m_obj->m_sprite->m_pos.y -= MOVE;
	}
	if (Input::Get()->GetKeyTrigger(DIK_SPACE)) {
		_target->m_obj->m_sprite->m_pos = { 0,0,-2 };
	}
}
