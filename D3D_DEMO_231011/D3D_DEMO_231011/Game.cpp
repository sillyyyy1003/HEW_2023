#include "Game.h"

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
#include <stdio.h>

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
	testTree->m_shadow->m_sprite->m_anime = new StaticAnimation(1, 1);	//影
	//オブジェクトの位置を配置
	testTree->m_obj->m_sprite->m_pos = { 2, 2, 0 };
	//オブジェクトのコライダーを配置(To Do)
	//testTree->collider=new Collider();//形によってsphereCollider、polygonColliderなどに変える


	testChara = new GameObject();
	//モデルを作る
	testChara->CreateObject(g_Assets->testChara01, 200, 200, 3, 4);
	testChara->CreateShadow(g_Assets->testChara01, 200, 200, 1, 1);
	
	//アニメションを配置
	testChara->m_obj->m_sprite->m_anime = new ObjectAnimation(3, 4);	//オブジェクト
	testChara->m_shadow->m_sprite->m_anime = new StaticAnimation(1, 1);	//影
	//オブジェクトの位置を配置
	testChara->m_obj->m_sprite->m_pos = { 1, 1, 0 };
	testChara->m_shadow->isLight = false;


	testWall = new StaticObject();
	//モデルを作る/アニメション配置
	testWall->CreateObject(g_Assets->testWall, 1920, 1080, 1, 1);
	//オブジェクトの位置を配置
	testWall->m_sprite->m_pos = { 0.0f,0.0f,2.0 };
	//影の位置を壁の前に設定
	testTree->m_shadow->m_sprite->m_pos.z = testWall->m_sprite->m_pos.z - 0.1f;

	testGround = new StaticObject();
	//モデルを作る/アニメション配置
	testGround->CreateObject(g_Assets->testGround, 1920, 1080, 1, 1);
	//オブジェクトの位置を配置
	testGround->m_sprite->m_pos = { 0.0f,-3.0f,0.0f };
	testGround->m_sprite->m_rotation.x = 90;

	testSide = new StaticObject();
	testSide->CreateObject(g_Assets->testSideBg, 1920, 1080, 1, 1);
	testSide->m_sprite->m_pos = { (float)-1920 / SCREEN_PARA,0.0f,0.0f };
	testSide->m_sprite->m_rotation = {0,-90,0};

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
	//tabキー押して　移動対象を変更
	if (Input::Get()->GetKeyTrigger(DIK_TAB)) {
		
		switch (m_moveTarget) {
		
		case WALL:

			m_moveTarget = GROUND;

			break;

		case GROUND:

			m_moveTarget = LIGHT;


			break;

		case LIGHT:

			m_moveTarget = OBJECT;

			break;

		case OBJECT:

			m_moveTarget = CAMERA;

			break;

		case CAMERA:

			m_moveTarget = WALL;

			break;

		default:

			break;

		}


	}

	//位置更新
	switch (m_moveTarget) {

	case WALL:

		TestMove(testWall);

		//カメラの追跡ターゲットを設定する
		if (Input::Get()->GetKeyTrigger(DIK_RETURN)) 
			dynamic_cast<TrackCamera*>(g_WorldCamera)->SetTarget(testWall);

		break;

	case GROUND:

		//TestMove(testGround);
		TestMove(testSide);
		break;

	case OBJECT:

		TestMove(testTree);
		//dynamic_cast<TrackCamera*>(g_WorldCamera)->SetTarget(testTree->m_obj);
		break;

	case LIGHT:
		
		TestMove(testChara);
		break;

	case CAMERA:

		dynamic_cast<TrackCamera*>(g_WorldCamera)->RomoveTarget();
		//TestMove(m_cameraPos);
		TestMoveCamera();
		g_WorldCamera->SetCameraPos(m_cameraPos);
		g_WorldCamera->SetFocusPos(m_focusPos);
		dynamic_cast<TrackCamera*>(g_WorldCamera)->SetDistance(m_distance);
		break;

	default:

		break;
	}



	//光源の位置をリアルタイムで更新する

	testTree->SetLightPos(testChara->m_obj->m_sprite->m_pos);

	testTree->Update();

	testChara->Update();

	testWall->Update();
	
	//testGround->Update();

	testSide->Update();



	//影のｚ軸の数値を更新
	testTree->m_shadow->m_sprite->m_pos.z = testWall->m_sprite->m_pos.z - 0.1f;

	m_cameraPos = g_WorldCamera->GetCameraPos();
	m_focusPos = g_WorldCamera->GetFocusPos();
	

}

void Game::TestDraw(void)
{
	//壁の描画
	testWall->Draw();

	//地面の描画
	//testGround->Draw();

	testSide->Draw();

	testChara->Draw();

	//オブジェクトを描画する
	testTree->Draw();

	




	//デバッグ表示 
	//40->一文字の幅/高さの二倍
	float posX = (-SCREEN_WIDTH / 2 + 40.0f) / SCREEN_PARA;//デバッグ表示の横座標設定
	float posY = ((SCREEN_HEIGHT / 2) - 40.0f) / SCREEN_PARA;//デバッグ表示の縦座標設定
	
	
	char targetName[16];	//移動対象の名前
	DirectX::XMFLOAT3 targetPos = {};	//移動対象の位置
	float targetRotate = 0.0f;		//移動対象の角度
	
	switch (m_moveTarget) {
	case WALL:
		strcpy_s(targetName, "WALL");
		targetPos = testWall->m_sprite->m_pos;
		targetRotate = testWall->m_sprite->m_rotation.x;
		break;
	case GROUND:
		strcpy_s(targetName, "GROUND");
		targetPos = testGround->m_sprite->m_pos;
		targetRotate = testGround->m_sprite->m_rotation.x;
		break;
	case OBJECT:
		strcpy_s(targetName, "OBJECT");
		targetPos = testTree->m_obj->m_sprite->m_pos;
		targetRotate = testTree->m_obj->m_sprite->m_rotation.x;
		break;
	case LIGHT:
		strcpy_s(targetName, "LIGHT");
		targetPos = testChara->m_obj->m_sprite->m_pos;
		break;
	case CAMERA:
		strcpy_s(targetName, "CAMERA");
		targetPos = m_cameraPos;
		break;
	}
	
	g_DebugManager->PrintDebugLog(posX, posY, targetName);//名前表示
	
	//回転角度
	strcpy_s(targetName, "Rotation");
	posY = ((SCREEN_HEIGHT / 2) - 40 * 2) / SCREEN_PARA;//デバッグ表示の縦座標設定
	g_DebugManager->PrintDebugLog(posX, posY, targetName);//名前表示

	posY = ((SCREEN_HEIGHT / 2) - 40 * 3) / SCREEN_PARA;//デバッグ表示の縦座標設定
	g_DebugManager->PrintDebugLog(posX, posY, targetRotate);

	//位置を出力する x,y,z
	strcpy_s(targetName, "Position");
	posY = ((SCREEN_HEIGHT / 2) - 40 * 4) / SCREEN_PARA;//デバッグ表示の縦座標設定
	g_DebugManager->PrintDebugLog(posX, posY, targetName);//名前表示

	posY = ((SCREEN_HEIGHT / 2) - 40 * 5) / SCREEN_PARA;//デバッグ表示の縦座標設定
	g_DebugManager->PrintDebugLog(posX, posY, targetPos.x);
	
	posY = ((SCREEN_HEIGHT / 2) - 40 * 6) / SCREEN_PARA;//デバッグ表示の縦座標設定
	g_DebugManager->PrintDebugLog(posX, posY, targetPos.y);

	posY = ((SCREEN_HEIGHT / 2) - 40 * 7) / SCREEN_PARA;//デバッグ表示の縦座標設定
	g_DebugManager->PrintDebugLog(posX, posY, targetPos.z);

}

void Game::TestMove(GameObject* _target)
{
	//移動入力
	//WASD上下左右移動
	if (Input::Get()->GetKeyPress(DIK_W)) {

		_target->m_obj->m_sprite->m_pos.y += 0.1f;

	}

	if (Input::Get()->GetKeyPress(DIK_A)) {

		_target->m_obj->m_sprite->m_pos.x -= 0.1f;

	}

	if (Input::Get()->GetKeyPress(DIK_D)) {

		_target->m_obj->m_sprite->m_pos.x += 0.1f;

	}

	if (Input::Get()->GetKeyPress(DIK_S)) {

		_target->m_obj->m_sprite->m_pos.y -= 0.1f;

	}
	//↑キー/↓キーで前後移動

	if (Input::Get()->GetKeyPress(DIK_UPARROW))
	{
		_target->m_obj->m_sprite->m_pos.z += 0.1f;
	}

	if (Input::Get()->GetKeyPress(DIK_DOWNARROW))
	{
		_target->m_obj->m_sprite->m_pos.z -= 0.1f;
	}


	if (Input::Get()->GetKeyPress(DIK_LEFTARROW))
	{
		_target->m_obj->m_sprite->m_rotation.x += 1.0f;
	}

	//←キー/→キーで角度の調整
	if (Input::Get()->GetKeyPress(DIK_RIGHTARROW))
	{
		_target->m_obj->m_sprite->m_rotation.x -= 1.0f;
	}


	//RESET
	if (Input::Get()->GetKeyTrigger(DIK_SPACE)) {
		
		_target->m_obj->m_sprite->m_rotation.x = 0.0f;
		_target->m_obj->m_sprite->m_pos.x = 0.0f;
	}
}

void Game::TestMove(StaticObject* _target)
{

	//移動入力
	//WASD上下左右移動
	if (Input::Get()->GetKeyPress(DIK_W)) {

		_target->m_sprite->m_pos.y += 0.1f;

	}

	if (Input::Get()->GetKeyPress(DIK_A)) {

		_target->m_sprite->m_pos.x -= 0.1f;

	}
	//↑キー/↓キーで上下移動
	if (Input::Get()->GetKeyPress(DIK_D)) {

		_target->m_sprite->m_pos.x += 0.1f;

	}
	if (Input::Get()->GetKeyPress(DIK_S)) {

		_target->m_sprite->m_pos.y -= 0.1f;
		
	}

	//↑キー/↓キーで前後移動
	if (Input::Get()->GetKeyPress(DIK_UPARROW))
	{
		_target->m_sprite->m_pos.z += 0.1f;
	}

	if (Input::Get()->GetKeyPress(DIK_DOWNARROW))
	{
		_target->m_sprite->m_pos.z -= 0.1f;
	}

	//←キー/→キーで角度の調整
	if (Input::Get()->GetKeyPress(DIK_LEFTARROW))
	{
		_target->m_sprite->m_rotation.x += 1.0f;
	}

	if (Input::Get()->GetKeyPress(DIK_RIGHTARROW))
	{
		_target->m_sprite->m_rotation.x -= 1.0f;
	}


	if (Input::Get()->GetKeyTrigger(DIK_SPACE)) {

		_target->m_sprite->m_rotation.x = 0.0f;
		_target->m_sprite->m_pos.x = 0.0f;
	}
}

void Game::TestMove(DirectX::XMFLOAT3& _target)
{
	
	if (Input::Get()->GetKeyPress(DIK_W)) {

		_target.y += 0.1f;

	}

	if (Input::Get()->GetKeyPress(DIK_A)) {

		_target.x -= 0.1f;

	}
	//↑キー/↓キーで上下移動
	if (Input::Get()->GetKeyPress(DIK_D)) {

		_target.x += 0.1f;

	}
	if (Input::Get()->GetKeyPress(DIK_S)) {

		_target.y -= 0.1f;
	}

	//↑キー/↓キーで前後移動
	if (Input::Get()->GetKeyPress(DIK_UPARROW))
	{
		_target.z += 0.1f;
	
	}

	if (Input::Get()->GetKeyPress(DIK_DOWNARROW))
	{
		_target.z -= 0.1f;
	}

	if (Input::Get()->GetKeyTrigger(DIK_SPACE)) {

		_target = { 0.0f,0.0f,-2.0f };
		m_lightPos = { 0.0f,0.0f,-2.0f };
	}

}

void Game::TestMoveCamera()
{

	if (Input::Get()->GetKeyPress(DIK_W)) {

		m_cameraPos.z += 0.1f;


	}

	if (Input::Get()->GetKeyPress(DIK_A)) {

		m_cameraPos.x -= 0.1f;
		m_focusPos.x -= 0.1f;

	}
	//↑キー/↓キーで上下移動
	if (Input::Get()->GetKeyPress(DIK_D)) {

		m_cameraPos.x += 0.1f;
		m_focusPos.x += 0.1f;
	}
	if (Input::Get()->GetKeyPress(DIK_S)) {

		m_cameraPos.z -= 0.1f;
	}

	//↑キー/↓キーで回転
	if (Input::Get()->GetKeyPress(DIK_UPARROW))
	{
		m_cameraPos.y += 0.1f;
		m_focusPos.y -= 0.1f;

	}

	if (Input::Get()->GetKeyPress(DIK_DOWNARROW))
	{
		m_cameraPos.y -= 0.1f;
		m_focusPos.y += 0.1f;
	}

	if (Input::Get()->GetKeyTrigger(DIK_SPACE)) {

		//reset
		m_cameraPos = { 0.0f, 0.0f, -9.0f };
		m_focusPos = { 0.0f,0.0f,2.0f };
	}

	m_distance = 0 - m_cameraPos.z;
}

Game::~Game()
{
	
	delete testTree;
	delete testWall;
	delete testGround;
	delete testChara;
	delete testSide;
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

