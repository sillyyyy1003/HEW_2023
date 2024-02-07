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

#include "xa2.h"

#include "RailManager.h"
#include "DInput.h"
#include <stdio.h>




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
	uiSelect = new CanvasUI();
	uiSound = new CanvasUI();
	uiPauseBg = new CanvasUI();

	uiSoundBg = new CanvasUI();

	for (int i = 0; i < 6; i++)
	{
		uiSoundOp_BGM[i] = new CanvasUI;
		uiSoundOp_SE[i] = new CanvasUI;
	}
	

	uiSelectBg = new CanvasUI();
	uiStageSelect = new CanvasUI();

	uiSelectCursor = new CanvasUI();


	for (int i = 0; i < 3; i++)
	{
		uiSelectStage[i] = new CanvasUI();
		uiSelectChapter[i] = new CanvasUI();

		uiClearMark[i] = new CanvasUI();
	}

	fade = new CanvasUI();

	circle = new GameObject();

	//stage1-1
	stageBg = new StaticObject();
	coconut = new GameObject();
	lamp = new GameObject();
	housePlate = new GameObject();

	testObj = new GameObject();



	//テクスチャ読み込み・モデル作成
	uiTitle->CreateModel(g_Assets->uiTitle, 1280, 300, 1, 1);
	uiTitleBg->CreateModel(g_Assets->uiTitleBg, 1280, 720, 1, 1);
	uiPressEnter->CreateModel(g_Assets->uiPressEnter, 1280, 300, 1, 1);

	uiPauseBg->CreateModel(g_Assets->uiPauseBg, 600, 720, 1, 1);
	uiResume->CreateModel(g_Assets->uiResume, 300, 100, 1, 1);
	uiRestart->CreateModel(g_Assets->uiRestart, 300, 100, 1, 1);
	uiSelect->CreateModel(g_Assets->uiSelect, 300, 100, 1, 1);

	uiSound->CreateModel(g_Assets->uiSound, 300, 100, 1, 1);
	uiSoundBg->CreateModel(g_Assets->uiSoundBg, 1280, 720, 1, 1);//今は薄い灰色


	uiSelectBg->CreateModel(g_Assets->uiSelectBg, 1280, 720, 1, 1);
	uiStageSelect->CreateModel(g_Assets->uiStageSelect, 394, 100, 1, 1);
	uiSelectCursor->CreateModel(g_Assets->uiSelectCursor, 76, 84, 1, 1);

	for (int i = 0; i < 3; i++)
	{
		uiClearMark[i]->CreateModel(g_Assets->uiClear, 300, 300, 1, 1);
	}
	
	
	fade->CreateModel(g_Assets->fade, 256, 256, 1, 1);


	//stage1に使われてる
	stageBg->CreateObject(g_Assets->stageBg, 1280, 720, 1, 1);
	testObj->CreateObject(g_Assets->circle, 200, 200, 1, 1);
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
	uiTitle->m_scale = { 0.8f,0.8f,1.0f };
	uiPressEnter->m_scale = { 0.3f,0.3f,1.0f };
	
	//Select画面
	uiSelectBg->m_pos = { 0.0f,0.0f,0.9f };
	uiStageSelect->m_pos = { -3.5f,3.0f,0.8f };
	
	uiSelectCursor->m_pos = { 4.0f,3.6f,0.8f };//Chapterの横に出るように

	//fade
	fade->m_pos = { 0.0f,0.0f,0.1f };
	fade->m_scale = { 4.0f,3.0f,1.0f };


	for (int i = 0; i < 3; i++)
	{
		uiClearMark[i]->m_pos = { -2.0f,1.3f,0.7f };
		uiClearMark[i]->m_scale = { 0.2f,0.2f,1.0f };
	}


	//uiPause
	uiPauseBg->m_pos={ - 300 / SCREEN_PARA, 0.0f, 0.9f };
	uiResume->m_pos= { -4.0f, 3.0f, 0.8f };
	uiRestart->m_pos= { -4.0f, 1.0f, 0.8f };
	uiSelect->m_pos = { -4.0f, -1.0f, 0.8f };
	//uiSound
	uiSound->m_pos = { -4.0f, -3.0f, 0.8f };
	uiSoundBg->m_pos = { 0.0f, 0.0f, 0.9f };
	uiSoundBg->m_scale = { 0.9f,0.9f,1.0f };

	//配列の初期化と設定
	InitSoundArray();



	//HRESULT hr;
	//hr = XA_Initialize();

	//if (FAILED(hr))// XA_Initialize関数が失敗したか判定
	//{
	//	MessageBoxA(NULL, "サウンド初期化失敗", "エラー", MB_ICONERROR | MB_OK);
	//}


	SceneManager::Get()->SetScene(SCENENAME::TITLE);
	
}

void Game::InitStage()
{


	//XA_Stop(SOUND_LABEL_BGM001);
	//XA_Stop(SOUND_LABEL_BGM002);
	//XA_Stop(SOUND_LABEL_BGM003);

	//ステージの初期化
	switch (SceneManager::Get()->GetStage()) {

	case STAGE1_1:
		//XA_Play(SOUND_LABEL_BGM001); //XA_Initialize();で問題有
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

void Game::InitSoundArray()
{

	for (int i = 0; i < 6; i++)
	{
		uiSoundOp_BGM[i]->CreateModel(g_Assets->uiSoundOp_BGM, 300, 100, 1, 1);
		uiSoundOp_SE[i]->CreateModel(g_Assets->uiSoundOp_SE, 300, 100, 1, 1);

		uiSoundOp_BGM[i]->m_scale = { 0.3f,0.3f,0.3f };
		uiSoundOp_SE[i]->m_scale = { 0.3f,0.3f,0.3f };

		switch (i)
		{
		case 1:
			uiSoundOp_BGM[1]->m_pos = { -4.0f, 1.0f, 0.8f };
			uiSoundOp_SE[1]->m_pos = { -4.0f,-1.0f,0.8f };
			break;

		case 2:
			uiSoundOp_BGM[2]->m_pos = { -2.0f, 1.0f, 0.8f };
			uiSoundOp_SE[2]->m_pos = { -2.0f,-1.0f,0.8f };
			break;

		case 3:
			uiSoundOp_BGM[3]->m_pos = { 0.0f, 1.0f, 0.8f };
			uiSoundOp_SE[3]->m_pos = { 0.0f,-1.0f,0.8f };
			break;

		case 4:
			uiSoundOp_BGM[4]->m_pos = { 2.0f, 1.0f, 0.8f };
			uiSoundOp_SE[4]->m_pos = { 2.0f,-1.0f,0.8f };
			break;

		case 5:
			uiSoundOp_BGM[5]->m_pos = { 4.0f, 1.0f, 0.8f };
			uiSoundOp_SE[5]->m_pos = { 4.0f,-1.0f,0.8f };
			break;
		}
	}
}

void Game::InitSelectArray() 
{

	for (int i = 0; i < 3; i++)
	{
		switch (i)
		{
		case 0:
			//テクスチャ割り当て
			uiSelectStage[0]->CreateModel(g_Assets->uiSelectStage1, 425, 133, 1, 1);
			uiSelectChapter[0]->CreateModel(g_Assets->uiSelectChapter1, 234, 71, 1, 1);

			//位置設定
			uiSelectStage[0]->m_pos = { -3.5f,1.3f,0.8f };
			uiSelectChapter[0]->m_pos = { 2.0f,3.3f,0.8f };
			break;
		case 1:
			//テクスチャ割り当て
			uiSelectStage[1]->CreateModel(g_Assets->uiSelectStage2, 408, 142, 1, 1);
			uiSelectChapter[1]->CreateModel(g_Assets->uiSelectChapter2, 225, 69, 1, 1);

			//位置設定
			uiSelectStage[1]->m_pos = { -2.7f,-0.8f,0.8f };
			uiSelectChapter[1]->m_pos = { 2.0f,1.0f,0.8f };
			break;
		case 2:
			//テクスチャ割り当て
			uiSelectStage[2]->CreateModel(g_Assets->uiSelectStage3, 421, 143, 1, 1);
			uiSelectChapter[2]->CreateModel(g_Assets->uiSelectChapter3, 206, 74, 1, 1);

			//位置設定
			uiSelectStage[2]->m_pos = { -3.5f,-3.0f,0.8f };
			uiSelectChapter[2]->m_pos = { 2.0f,-1.5f,0.8f };
			break;

		}
	}

}

void Game::GameUpdate(void)
{
	//入力処理　XXキー押して、移動させるオブジェクトをスイッチ
	
	

	//if (SceneManager::Get()->GetNextScene()!=SceneManager::Get()->GetScene())
	//{
	//	FadeUpdate();
	//	SceneManager::Get()->SetScene(SceneManager::Get()->GetNextScene());
	//	fadeState = FADE_OUT;
	//	isActive = true;
	//}
	//else
	//{
	//	
	//	fadeState = FADE_IN;
	//}

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



void Game::TitleUpdate(void)
{	
	//エンターキーを押すと　ステージセレクト画面に遷移
	if (Input::Get()->GetKeyTrigger(DIK_RETURN)) {

		SceneManager::Get()->SetScene(STAGESELECT);

		//Init SelectScene Data
		InitSelectArray();
	}

	uiPressEnter->Update();
	uiTitle->Update();
	uiTitleBg->Update();

}

void Game::SelectUpdate(void)
{
	if (Input::Get()->GetKeyTrigger(DIK_1))
	{
		selectStage = STAGE1;
	}
	if (Input::Get()->GetKeyTrigger(DIK_2))
	{
		if (isClearStage1)
		{
			selectStage = STAGE2;
		}
		
	}
	if (Input::Get()->GetKeyTrigger(DIK_3))
	{
		if (isClearStage1 && isClearStage2)
		{
			selectStage = STAGE3;
		}
		
	}

	switch (selectStage)
	{
	case Game::SELECTNONE:
		SelectStageNone();
		break;
	case Game::STAGE1:
		SelectStage1();
		break;
	case Game::STAGE2:
		SelectStage2();
		break;
	case Game::STAGE3:
		SelectStage3();
		break;
	}

}

void Game::SelectChapter(void)
{

	switch (selectChapter)
	{
	case Game::CHAPTER1:

		if (Input::Get()->GetKeyTrigger(DIK_DOWN))
		{
			uiSelectCursor->m_pos = { 4.0f,1.3f,0.8f };
			selectChapter = CHAPTER2;
		}

		SelectChapter1();
		break;
	case Game::CHAPTER2:

		if (Input::Get()->GetKeyTrigger(DIK_UP))
		{
			uiSelectCursor->m_pos = { 4.0f, 3.6f, 0.8f };
			selectChapter = CHAPTER1;
		}
		if (Input::Get()->GetKeyTrigger(DIK_DOWN))
		{
			uiSelectCursor->m_pos = { 4.0f,-1.2f,0.8f };
			selectChapter = CHAPTER3;
		}

		SelectChapter2();
		break;
	case Game::CHAPTER3:

		if (Input::Get()->GetKeyTrigger(DIK_UP))
		{
			uiSelectCursor->m_pos = { 4.0f, 1.3f, 0.8f };
			selectChapter = CHAPTER2;
		}

		SelectChapter3();
		break;
	}
}

void Game::SelectStageNone(void)
{
	uiSelectStage[0]->m_pos.y = 1.3f;
	uiSelectStage[1]->m_pos.y = -0.8f;
	uiSelectStage[2]->m_pos.y = -3.0f;
	uiSelectCursor->m_pos.z = 1.0f;
}

void Game::SelectStage1(void)
{
	if (Input::Get()->GetKeyTrigger(DIK_SPACE))
	{
		ClearSwitch1();
	}

	uiSelectStage[0]->m_pos.y = 1.5f;
	uiSelectStage[1]->m_pos.y = -0.8f;
	uiSelectStage[2]->m_pos.y = -3.0f;
	uiSelectCursor->m_pos.z = 0.8f;

	if(isClearStage1)
	{
		uiClearMark[0]->m_pos = {-2.0f,1.5f,0.7f};
	}


	SelectChapter();

	//uiSelectStage[0]->m_materialDiffuse = { 0.0f,1.0f,0.0f,1.0f };
}

void Game::SelectStage2(void)
{
	if (Input::Get()->GetKeyTrigger(DIK_SPACE))
	{
		ClearSwitch2();
	}

	uiSelectStage[0]->m_pos.y = 1.3f;
	uiSelectStage[1]->m_pos.y = -0.6f;
	uiSelectStage[2]->m_pos.y = -3.0f;
	uiSelectCursor->m_pos.z = 0.8f;


	if (isClearStage2)
	{
		uiClearMark[1]->m_pos = {-1.5f,-0.6f,0.7f};
	}

	SelectChapter();
}

void Game::SelectStage3(void)
{
	if (Input::Get()->GetKeyTrigger(DIK_SPACE))
	{
		ClearSwitch3();
	}

	uiSelectStage[0]->m_pos.y = 1.3f;
	uiSelectStage[1]->m_pos.y = -0.8f;
	uiSelectStage[2]->m_pos.y = -2.8f;
	uiSelectCursor->m_pos.z = 0.8f;

 if (isClearStage3)
	{
	 uiClearMark[2]->m_pos = {-2.2f,-2.8f,0.7f};
	}

	SelectChapter();
}

void Game::SelectChapter1(void)
{
	if (Input::Get()->GetKeyTrigger(DIK_RETURN))
	{
		//シーン遷移を行う
		SceneManager::Get()->SetScene(SCENENAME::STAGE);

		//次のシーンを設定する
		SceneManager::Get()->SetNextScene(SCENENAME::STAGE);

		//ステージ内のオブジェクトを配置
		InitStage();

		switch (selectStage)
		{
		case Game::SELECTNONE:
			break;

		case Game::STAGE1:
			SceneManager::Get()->SetStage(STAGEINFO::STAGE1_1);
			break;

		case Game::STAGE2:
			SceneManager::Get()->SetStage(STAGEINFO::STAGE2_1);
			break;

		case Game::STAGE3:
			SceneManager::Get()->SetStage(STAGEINFO::STAGE3_1);
			break;

		}

	}
}

void Game::SelectChapter2(void)
{
	if (Input::Get()->GetKeyTrigger(DIK_RETURN))
	{
		//シーン遷移を行う
		SceneManager::Get()->SetScene(SCENENAME::STAGE);

		//次のシーンを設定する
		SceneManager::Get()->SetNextScene(SCENENAME::STAGE);

		//ステージ内のオブジェクトを配置
		InitStage();

		switch (selectStage)
		{
		case Game::SELECTNONE:
			break;

		case Game::STAGE1:
			SceneManager::Get()->SetStage(STAGEINFO::STAGE1_2);
			break;

		case Game::STAGE2:
			SceneManager::Get()->SetStage(STAGEINFO::STAGE2_2);
			break;

		case Game::STAGE3:
			SceneManager::Get()->SetStage(STAGEINFO::STAGE3_2);
			break;

		}

	}
}

void Game::SelectChapter3(void)
{
	if (Input::Get()->GetKeyTrigger(DIK_RETURN))
	{
		//シーン遷移を行う
		SceneManager::Get()->SetScene(SCENENAME::STAGE);

		//次のシーンを設定する
		SceneManager::Get()->SetNextScene(SCENENAME::STAGE);

		//ステージ内のオブジェクトを配置
		InitStage();

		switch (selectStage)
		{
		case Game::SELECTNONE:
			break;

		case Game::STAGE1:
			SceneManager::Get()->SetStage(STAGEINFO::STAGE1_3);
			break;

		case Game::STAGE2:
			SceneManager::Get()->SetStage(STAGEINFO::STAGE2_3);
			break;

		case Game::STAGE3:
			SceneManager::Get()->SetStage(STAGEINFO::STAGE3_3);
			break;

		}

	}
}

void Game::ClearSwitch1(void)
{
	if (isClearStage1)
	{
		isClearStage1 = false;
	}
	else 
	{
		isClearStage1 = true;
	}
}

void Game::ClearSwitch2(void)
{
	if (isClearStage2)
	{
		isClearStage2 = false;
	}
	else
	{
		isClearStage2 = true;
	}
}

void Game::ClearSwitch3(void)
{
	if (isClearStage3)
	{
		isClearStage3 = false;
	}
	else
	{
		isClearStage3 = true;
	}
}

void Game::StageUpdate(void)
{
	//Input
	if (Input::Get()->GetKeyTrigger(DIK_ESCAPE)) {

		PauseSwitch();
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
	
	
	//moveTest
	if (Input::Get()->GetKeyPress(DIK_W)) {
		testObj->m_obj->m_sprite->m_pos.z += 0.05f;
	}	
	if (Input::Get()->GetKeyPress(DIK_A)) {
		testObj->m_obj->m_sprite->m_pos.x -= 0.05f;
	}
	if (Input::Get()->GetKeyPress(DIK_D)) {
		testObj->m_obj->m_sprite->m_pos.x += 0.05f;
	}
	if (Input::Get()->GetKeyPress(DIK_S)) {
		testObj->m_obj->m_sprite->m_pos.z -= 0.05f;
	}
	if (Input::Get()->GetKeyPress(DIK_R)) {
		testObj->m_obj->m_sprite->m_pos.y += 0.05f;
	}
	if (Input::Get()->GetKeyPress(DIK_F)) {
		testObj->m_obj->m_sprite->m_pos.y -= 0.05f;
	}
	if (Input::Get()->GetKeyTrigger(DIK_SPACE)) {
		testObj->m_obj->m_sprite->m_pos = { 0,0,-2 };
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

	


	//moveTest
	testObj->Update();

	coconut->Update();
	lamp->Update();
	housePlate->Update();

	stageBg->Update();

	

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


Game::~Game()
{
	//XA_Release();// サウンド解放

	delete uiTitle;		//タイトル文字
	delete uiTitleBg;		//タイトル背景
	delete uiPressEnter;	//タイトルエンターキー

	delete uiSelectBg;
	delete uiStageSelect;
	delete uiSelectCursor;



	for (int i = 0; i < 3; i++)
	{
		delete uiSelectStage[i];
		delete uiSelectChapter[i];
		delete uiClearMark[i];
	}


	delete uiPauseBg;	//PAUSEのボタン
	delete uiResume;
	delete uiRestart;
	delete uiSelect;
	delete uiSound;
	delete uiSoundBg;

	//配列の分を解放
	for (int i = 0; i < 6; i++)
	{
		delete uiSoundOp_BGM[i];	//BGM設定
		delete uiSoundOp_SE[i];	//SE設定
	}
	

	delete stageBg;		//ステージ背景
	delete coconut;
	delete lamp;
	delete housePlate;

	delete circle;			//circle

	
}

Game* Game::Get()
{
	static Game instance;
	return &instance;
}

void Game::UiUpdate()
{
	//入力操作
	//今のところ数字で管理

	if (Input::Get()->GetKeyTrigger(DIK_1))
	{
		PauseSwitch();
	}
	if (Input::Get()->GetKeyTrigger(DIK_2))
	{
		PauseSwitch();
		//ステージ内のオブジェクトを再配置
		InitStage();
	}
	if (Input::Get()->GetKeyTrigger(DIK_3))
	{
		selectStage = SELECTNONE;
		uiSelectCursor->m_pos = { 4.0f,3.3f,0.8f };
		PauseSwitch();
		SceneManager::Get()->SetScene(SCENENAME::STAGESELECT);
	}
	if (Input::Get()->GetKeyTrigger(DIK_4))
	{
		SoundSwitch();// サウンド画面切り替え
	}


	if (Input::Get()->GetKeyTrigger(DIK_ESCAPE))
	{
		isSound = false;//Sound設定の画面でESCを押すとリセットされる（またESCを押したときにはPAUSE画面からになる）
	}


	//Sound画面
	if (!isSound)
	{
		uiPauseBg->Update();
		uiRestart->Update();
		uiResume->Update();
		uiSelect->Update();
		uiSound->Update();
	}
	else if (isSound)
	{
		uiSoundBg->Update();
		
		SoundVolume();//BGM,SE音量設定
	}

}

void Game::FadeUpdate()
{
	if (fadeState == FADE_IN)
	{
		fade->m_materialDiffuse.w -= 0.01f;

		if (fade->m_materialDiffuse.w <= 0.0f)
		{
			fadeState = NO_FADE;
			isActive = false;
		}
	}
	else if (fadeState == FADE_OUT)
	{
		fade->m_materialDiffuse.w += 0.01f;

		if (fade->m_materialDiffuse.w >= 1.0f)
		{
			SceneManager::Get()->SetScene(SceneManager::Get()->GetNextScene());
			fadeState = FADE_IN;
		}
	}
}


void Game::PauseSwitch(void)
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

void Game::SoundSwitch(void)
{
	if (isSound)
	{
		isSound = false;
	}
	else
	{
		isSound = true;
	}
}

void Game::SoundVolume(void)
{
	if (Input::Get()->GetKeyTrigger(DIK_UP))
	{
		soundOp = BGM;
	}
	if (Input::Get()->GetKeyTrigger(DIK_DOWN))
	{
		soundOp = SE;
	}

	switch (soundOp)
	{
	case Game::BGM:
		SoundOp_BGM();
		break;

	case Game::SE:
		SoundOp_SE();
		break;
	}
			
	 //Sound調節
	for (int i = 1; i < 6; i++)
	{
		uiSoundOp_BGM[i]->Update();
		uiSoundOp_SE[i]->Update();
	}
}

void Game::SoundOp_BGM(void)
{
	if (m_soundVolume_BGM >= 0)
	{
		if (Input::Get()->GetKeyTrigger(DIK_LEFT))
		{
			m_soundVolume_BGM--;
		}
	}
	if (m_soundVolume_BGM <= 5)
	{
		if (Input::Get()->GetKeyTrigger(DIK_RIGHT))
		{
			m_soundVolume_BGM++;
		}
	}
	else if (m_soundVolume_BGM >= 5)
	{
		m_soundVolume_BGM = 5;
	}
}

void Game::SoundOp_SE(void)
{
	if (m_soundVolume_SE >= 0)
	{
		if (Input::Get()->GetKeyTrigger(DIK_LEFT))
		{
			m_soundVolume_SE--;
		}
	}
	if (m_soundVolume_SE <= 5)
	{
		if (Input::Get()->GetKeyTrigger(DIK_RIGHT))
		{
			m_soundVolume_SE++;
		}
	}
	else if (m_soundVolume_SE >= 5)
	{
		m_soundVolume_SE = 5;
	}
}

void Game::FocusSwitch(void)
{
	if (isFocus)
	{
		isFocus = false;
	}
	else
	{
		isFocus = true;
	}
}

void Game::GameDraw()
{

	D3D_ClearScreen();

	if (!isActive)
	{
		fade->Draw();
	}


	//============ ここから描画処理 ============//
	
	switch (SceneManager::Get()->GetScene()) {
	case SCENENAME::TITLE:
		TitleDraw();
		break;
	case SCENENAME::STAGESELECT:
		SelectDraw();
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

void Game::SelectDraw(void)
{
	uiSelectBg->Draw();
	uiStageSelect->Draw();
	uiSelectCursor->Draw();

	uiSelectDraw();

}

void Game::uiSelectDraw(void)
{
	for (int i = 0; i < 3; i++)
	{
		switch (i)
		{
		case 0:
			uiSelectStage[0]->Draw();
			uiSelectChapter[0]->Draw();

			if (isClearStage1)
			{
				uiClearMark[0]->Draw();
				uiSelectStage[1]->Draw();
			}
			break;
		case 1:
			
			uiSelectChapter[1]->Draw();

			if (isClearStage1 && isClearStage2)
			{
				uiClearMark[0]->Draw();
				uiClearMark[1]->Draw();
				uiSelectStage[2]->Draw();
			}
			break;
		case 2:
			
			uiSelectChapter[2]->Draw();

			if (isClearStage1 && isClearStage2 && isClearStage3)
			{

				uiClearMark[0]->Draw();
				uiClearMark[1]->Draw();
				uiClearMark[2]->Draw();

			}
			break;
		}
	}
}

void Game::SoundVolumeDraw(void)
{
	if (soundOp == BGM || soundOp == SE)
	{

		//BGM音量調節描画
		switch (m_soundVolume_BGM)
		{
		case 0:
			//何も描画しない
			break;

		case 1:
			uiSoundOp_BGM[1]->Draw();
			break;

		case 2:
			for (int i = 1; i < 3; i++)
			{
				uiSoundOp_BGM[i]->Draw();
			}
			break;

		case 3:
			for (int i = 1; i < 4; i++)
			{
				uiSoundOp_BGM[i]->Draw();
			}
			break;

		case 4:
			for (int i = 1; i < 5; i++)
			{
				uiSoundOp_BGM[i]->Draw();
			}
			break;

		case 5:
			for (int i = 1; i < 6; i++)
			{
				uiSoundOp_BGM[i]->Draw();
			}
			break;

		case 6:
			for (int i = 1; i < 6; i++)
			{
				uiSoundOp_BGM[i]->Draw();
			}
			break;

		}

		//SE音量調節描画
		switch (m_soundVolume_SE)
		{
		case 0:
			//何も描画しない
			break;

		case 1:
			uiSoundOp_SE[1]->Draw();
			break;

		case 2:
			for (int i = 1; i < 3; i++)
			{
				uiSoundOp_SE[i]->Draw();
			}
			break;

		case 3:
			for (int i = 1; i < 4; i++)
			{
				uiSoundOp_SE[i]->Draw();
			}
			break;

		case 4:
			for (int i = 1; i < 5; i++)
			{
				uiSoundOp_SE[i]->Draw();
			}
			break;

		case 5:
			for (int i = 1; i < 6; i++)
			{
				uiSoundOp_SE[i]->Draw();
			}
			break;

		case 6:
			for (int i = 1; i < 6; i++)
			{
				uiSoundOp_SE[i]->Draw();
			}
			break;
		}
	}
}

void Game::DrawStage1_1()
{
	stageBg->Draw();
	testObj->Draw();

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
	if (!isSound)
	{
		uiPauseBg->Draw();
		uiResume->Draw();
		uiRestart->Draw();
		uiSelect->Draw();
		uiSound->Draw();

	}
	else if(isSound)//サウンド画面に入る
	{
		uiSoundBg->Draw();

		//音量調節の描画
		SoundVolumeDraw();

	}
	
}
