#include "Game.h"

#include "Assets.h"
#include "TrackCamera.h"

#include "GameObject.h"
#include "ShadowObject.h"
#include "StaticObject.h"

#include "DebugManager.h"

#include "Animation.h"
#include "StaticAnimation.h"
#include "ObjectAnimation.h"

#include "DInput.h"
#include <stdio.h>

#include "SceneManager.h"

extern Assets* g_Assets;
extern Camera* g_WorldCamera;
extern DebugManager* g_DebugManager;


void Game::Init()
{
	//----------------------------//
	// ここからはオブジェクトの初期化を行う
	//----------------------------//
	//カメラの追跡ターゲットを設定する
	//dynamic_cast<TrackCamera*>(g_WorldCamera)->SetTarget(testWall);

	
	//----------------------------//
	// ここからはエフェクトの初期化
	//----------------------------//


	//----------------------------//
	// ここからはシーンの初期化
	//----------------------------//
	
}

void Game::InitStage()
{
	//ステージの初期化
	switch (SceneManager::Get()->GetScene()) {

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

void Game::InitStage1_1(void)
{
}

void Game::GameUpdate(void)
{
	//入力処理　XXキー押して、移動させるオブジェクトをスイッチ

	//オブジェクトUpdate


}

void Game::TitleUpdate(void)
{	
	//プロトタイプ用
	
}


Game::~Game()
{


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
	
	

	

	//============ ここまで描画処理 ============//
	 
	//ダブルバッファの切り替えを行い画面を更新する
	GetD3D_DATA()->SwapChain->Present(0, 0);
}

void Game::TitleDraw(void)
{
	//TestDraw();
}


void Game::ResultDraw(void)
{
}

//void Game::SetGameScene(GAMESCENE scene)
//{
//	m_gameScene = scene;
//}

/*
void Game::TestUpdate(void)
{
	/*
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
	/*
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



}

void Game::TestDraw(void)
{



	float posX = (-SCREEN_WIDTH / 2 + 40.0f) / SCREEN_PARA;//デバッグ表示の横座標設定
	float posY = ((SCREEN_HEIGHT / 2) - 40.0f) / SCREEN_PARA;//デバッグ表示の縦座標設定


	char targetName[16];	//移動対象の名前
	DirectX::XMFLOAT3 targetPos = {};	//移動対象の位置
	float targetRotate = 0.0f;		//移動対象の角度

	/*
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
*/