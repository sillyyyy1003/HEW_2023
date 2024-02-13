#include "Game.h"
#include "Assets.h"
#include "TrackCamera.h"
#include "GameObject.h"
#include "ShadowObject.h"
#include "StaticObject.h"
#include "DebugManager.h"
#include "SceneManager.h"
#include "Animation.h"
#include "ColliderManager.h"
#include "StaticAnimation.h"
#include "ObjectAnimation.h"
#include "RailManager.h"
#include "DInput.h"
#include "xa2.h"
#include <stdio.h> 
#include <algorithm> // 必要なヘッダーファイル

#define MOVE 0.3f
#define INITROTATE	(19.8)

extern Assets* g_Assets;
extern Camera* g_WorldCamera;
extern DebugManager* g_DebugManager;

void Game::Init()
{
	//=============================
	//オブジェクト作成
	//=============================
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

	//stage1-1
	stageBg = new StaticObject();
	coconut = new GameObject();
	lamp = new GameObject();
	housePlate = new GameObject();
	testObj = new GameObject();

	//stage1に使われてる
	//移動のオブジェクトの名前を設定する
	coconut->SetName("coconut");
	lamp->SetName("lamp");
	housePlate->SetName("housePlate");

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



	stageBg->CreateObject(g_Assets->stageBg, 1280, 720, 1, 1);
	testObj->CreateObject(g_Assets->tree, 200, 200, 1, 1);
	testObj->CreateShadow(g_Assets->shadow, 200, 200, 1, 1);

	coconut->CreateObject(g_Assets->coconut, 190, 190, 1, 1);
	coconut->CreateShadow(g_Assets->coconutShadow, 158, 159, 1, 1);
	lamp->CreateObject(g_Assets->lamp, 163, 569, 1, 1);
	lamp->CreateShadow(g_Assets->lampShadow, 163, 569, 1, 1);
	housePlate->CreateObject(g_Assets->housePlate, 110, 216, 1, 1);
	housePlate->CreateShadow(g_Assets->housePlateShadow, 55, 108, 1, 1);

	//アニメーションの設定
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


	for (int i = 0; i < 3; i++)
	{
		uiClearMark[i]->m_pos = { -2.0f,1.3f,0.7f };
		uiClearMark[i]->m_scale = { 0.2f,0.2f,1.0f };
	}


	//uiPause
	uiPauseBg->m_pos = { -300 / SCREEN_PARA, 0.0f, 0.9f };
	uiResume->m_pos = { -4.0f, 3.0f, 0.8f };
	uiRestart->m_pos = { -4.0f, 1.0f, 0.8f };
	uiSelect->m_pos = { -4.0f, -1.0f, 0.8f };

	//uiSound
	uiSound->m_pos = { -4.0f, -3.0f, 0.8f };
	uiSoundBg->m_pos = { 0.0f, 0.0f, 0.9f };
	uiSoundBg->m_scale = { 0.9f,0.9f,1.0f };

	//fade
	fade->m_pos = { 0.0f,0.0f,-0.9f };
	fade->m_scale = { 4.0f,3.0f,1.0f };




	//配列の初期化と設定
	InitSoundArray();
	InitSelectArray();


	// サウンド初期化
	HRESULT hr;
	hr = XA_Initialize();
	if (FAILED(hr))
	{
		MessageBoxA(NULL, "サウンド初期化失敗", "エラー", MB_OK | MB_ICONERROR);
	}


	SceneManager::Get()->SetScene(SCENENAME::TITLE);
	RailManager::Get()->InitRail();
	
}


void Game::InitStage()
{


	RailManager::Get()->InitRailPos();
	//ステージの初期化
	switch (SceneManager::Get()->GetStage()) {

	case STAGE1_1:

		XA_Play(BGM_Stage1);//サウンド再生
		InitStage1_1();


		break;

	case STAGE1_2:

		XA_Play(BGM_Stage1);//サウンド再生
		InitStage1_2();

		break;

	case STAGE1_3:

		XA_Play(BGM_Stage1);//サウンド再生
		InitStage1_3();

		break;

	case STAGE2_1:

		XA_Play(BGM_Stage2);//サウンド再生
		InitStage2_1();

		break;

	case STAGE2_2:

		XA_Play(BGM_Stage2);//サウンド再生
		InitStage2_2();

		break;

	case STAGE2_3:

		XA_Play(BGM_Stage2);//サウンド再生
		InitStage2_3();

		break;

	case STAGE3_1:

		XA_Play(BGM_Stage3);//サウンド再生
		InitStage3_1();

		break;
	case STAGE3_2:

		XA_Play(BGM_Stage3);//サウンド再生
		InitStage3_2();

		break;

	case STAGE3_3:

		XA_Play(BGM_Stage3);//サウンド再生
		InitStage3_3();


		break;

	}
}

void Game::InitStage1_1(void)
{
	//背景設定->関数化処理
	stageBg->m_sprite->m_rotation.x = 19.8;//カメラと垂直状態を保持するため
	stageBg->m_sprite->m_scale = { 2.65,2.65,1.0 };//固定値
	//y
	float y = 21.626 - 7 / ROTATEX;
	y += 1;
	y = y * ROTATEX;
	//y座標の導入
	stageBg->m_sprite->m_pos = { 0.0f,- y,1.0f };

	//位置設定
	//光源の位置を設定する
	m_lightPos = { 0,0,-10 };

	//オブジェクトを設定する
	//CAUTION! 
	//本体y軸固定->-1
	//Z:FRONT:-10 MIDDLE:-7.5 BACK:-5
	//X:LEFT2:-9 LEFT1:-4.5 MIDDLE:0.0 RIGHT1:4.5 RIGHT2:9
	//本体
	coconut->m_obj->m_sprite->m_pos = { -4.5f,-4.0f,-5.0f };
	lamp->m_obj->m_sprite->m_pos = { 0.0f,-4.0f,-5.0f };
	housePlate->m_obj->m_sprite->m_pos = { -4.5f,-4.0f,-7.5f};

	testObj->m_obj->m_sprite->m_pos = { 0,-3,-2 };//y軸固定!!
	testObj->m_shadow->m_sprite->m_pos.z = -1.0f;//影のY/Z軸を固定!!
	
	coconut->m_shadow->m_sprite->m_pos.z = 0.0f;
	lamp->m_shadow->m_sprite->m_pos.z = -0.1f;
	housePlate->m_shadow->m_sprite->m_pos.z = -0.2f;
	
	
	//影のy軸
	coconut->m_shadow->m_sprite->m_pos.y = 3.4;
	lamp->m_shadow->m_sprite->m_pos.y = coconut->m_shadow->m_sprite->m_pos.y - 1.7;
	housePlate->m_shadow->m_sprite->m_pos.y = coconut->m_shadow->m_sprite->m_pos.y - 3.7;
	
	//大きさ設定

	//レール上の位置を設定する
	coconut->SetRailPos(1, 0);
	lamp->SetRailPos(2, 0);
	housePlate->SetRailPos(1, 1);

	//回転設定

	//objectListを初期化
	objectList.clear();
	objectList.shrink_to_fit();
	objectList.push_back(coconut);
	objectList.push_back(lamp);
	objectList.push_back(housePlate);

	//レールの設定
	RailManager::Get()->InitRail();
	RailInit1_1();

	//ステージ情報を初期化
	for (int i = 0; i < 9; i++) {
		//全部のステージを無効かにする
		SceneManager::Get()->m_stageHolder[i]->Init();

	}
	//使うステージだけ起動
	SceneManager::Get()->m_stageHolder[STAGEINFO::STAGE1_1]->SetActive(true);

	//移動ターゲットを設定
	coconut->SetActive(true);

	//自動移動や自動回転の設定

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
	////1-1用
	/*
	bool railData[15][8]{
		//back row
		//up	ru  r	rd d	ld l	lu
		{	0,	0,	1,	0,	0,	0,	0,	0},//0
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
	*/

	//テスト用
	bool railData[15][8]{
		//up	ru  r	rd d	ld l	lu
		{	0,	0,	1,	1,	1,	0,	0,	0},
		{	0,	0,	1,	1,	1,	1,	1,	0},
		{	0,	0,	1,	1,	1,	1,	1,	0},
		{	0,	0,	1,	1,	1,	1,	1,	0},
		{	0,	0,	0,	0,	1,	1,	1,	0},

		{	1,	1,	1,	1,	1,	0,	0,	0},
		{	1,	1,	1,	1,	1,	1,	1,	1},
		{	1,	1,	1,	1,	1,	1,	1,	1},
		{	1,	1,	1,	1,	1,	1,	1,	1},
		{	1,	0,	0,	0,	1,	1,	1,	1},

		{	1,	1,	1,	0,	0,	0,	0,	0},
		{	1,	1,	1,	0,	0,	0,	1,	1},
		{	1,	1,	1,	0,	0,	0,	1,	1},
		{	1,	1,	1,	0,	0,	0,	1,	1},
		{	1,	0,	0,	0,	0,	0,	1,	1},



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

	//オブジェクトいるところの位置情報更新
	RailManager::Get()->InitRailPos();

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
	//テクスチャ割り当て
	uiSelectStage[STAGE1]->CreateModel(g_Assets->uiSelectStage1, 425, 133, 1, 1);
	uiSelectStage[STAGE2]->CreateModel(g_Assets->uiSelectStage2, 408, 142, 1, 1);
	uiSelectStage[STAGE3]->CreateModel(g_Assets->uiSelectStage3, 421, 143, 1, 1);

	uiSelectChapter[CHAPTER1]->CreateModel(g_Assets->uiSelectChapter1, 234, 71, 1, 1);
	uiSelectChapter[CHAPTER2]->CreateModel(g_Assets->uiSelectChapter2, 225, 69, 1, 1);
	uiSelectChapter[CHAPTER3]->CreateModel(g_Assets->uiSelectChapter3, 206, 74, 1, 1);
	
	//位置設定
	uiSelectStage[STAGE1]->m_pos = { -3.5f,1.3f,0.8f };
	uiSelectStage[STAGE2]->m_pos = { -2.7f,-0.8f,0.8f };
	uiSelectStage[STAGE3]->m_pos = { -3.5f,-3.0f,0.8f };

	uiSelectChapter[CHAPTER1]->m_pos = { 2.0f,3.3f,0.8f };
	uiSelectChapter[CHAPTER2]->m_pos = { 2.0f,1.0f,0.8f };
	uiSelectChapter[CHAPTER3]->m_pos = { 2.0f,-1.5f,0.8f };

	//ステージを設定
	selectStage = STAGE1;

}


void Game::TitleUpdate(void)
{	
	/*
	////エンターキーを押すと　ステージセレクト画面に遷移
	//if (Input::Get()->GetKeyTrigger(DIK_RETURN)) {

	//	//SceneManager::Get()->SetScene(STAGESELECT);

	//	//Init SelectScene Data
	//	
	//	//シーン遷移を行う
	//	SceneManager::Get()->SetScene(SCENENAME::STAGE);

	//	//次のシーンを設定する
	//	SceneManager::Get()->SetNextScene(SCENENAME::STAGE);
	//	SceneManager::Get()->SetStage(STAGEINFO::STAGE1_1);
	//	
	//	//ステージ内のオブジェクトを配置
	//	InitStage();

	//}
	*/

	//スペースキーを押すと　ステージセレクト画面に遷移
	if (Input::Get()->GetKeyTrigger(DIK_SPACE)) {

		SceneManager::Get()->SetScene(STAGESELECT);
		
		
		XA_Play(BGM_SelectStage);//セレクトBGM再生


		//タイトルに戻る時全部のクリア判定を無しにする　
		for (int i = 0; i < 9; i++) {
			//封蝋の印を無しにする
			SceneManager::Get()->m_stageHolder[i]->SetCompleted(false);
			//念のため、ステージのクリア判定をfalseにする
			SceneManager::Get()->m_stageHolder[i]->SetClear(false);
		}

	}

	uiPressEnter->Update();
	uiTitle->Update();
	uiTitleBg->Update();
}

void Game::SelectUpdate(void)
{
	//クリア印の判定->関数化
	//今のステージを獲得
	int stageNum = selectStage * 3;
	for (int i = 0; i < 3; i++) {
		//完成下かどうか
		if (SceneManager::Get()->m_stageHolder[stageNum + i]->GetCompleted()) {
			//クリアしたら描画する
			uiClearMark[i]->SetActive(true);
		}
		else {
			//クリアしなかったら描画しない
			uiClearMark[i]->SetActive(false);
		}

	}


	//入力処理
	//
	if (Input::Get()->GetKeyTrigger(DIK_DOWNARROW)) {
		
		XA_Play(SE_Select);//選択SE再生


		//ステージをを選択する場合
		if (isSelectChapter == false) {

			switch (selectStage)
			{
			case Game::SELECTNONE:

				break;
			case Game::STAGE1:
				selectStage = STAGE2;
				break;
			case Game::STAGE2:
				selectStage = STAGE3;
				break;
			case Game::STAGE3:
				selectStage = STAGE1;
				break;
			default:
				break;
			}
		}
		else {
			switch (selectChapter)
			{
			case Game::CHAPTER1:
				selectChapter = CHAPTER2;
				break;
			case Game::CHAPTER2:
				selectChapter = CHAPTER3;
				break;
			case Game::CHAPTER3:
				selectChapter = CHAPTER1;
				break;
			default:
				break;
			}

		}
	}

	if (Input::Get()->GetKeyTrigger(DIK_UPARROW)) {
		
		XA_Play(SE_Select);//選択SE再生
		
		if (isSelectChapter == false) {

			switch (selectStage)
			{
			case Game::SELECTNONE:
				break;
			case Game::STAGE1:
				selectStage = STAGE3;
				break;
			case Game::STAGE2:
				selectStage = STAGE1;
				break;
			case Game::STAGE3:
				selectStage = STAGE2;
				break;
			default:
				break;
			}
		}
		else {
			switch (selectChapter)
			{
			case Game::CHAPTER1:
				selectChapter = CHAPTER3;
				break;
			case Game::CHAPTER2:
				selectChapter = CHAPTER1;
				break;
			case Game::CHAPTER3:
				selectChapter = CHAPTER2;
				break;
			default:
				break;
			}
		}
	}

	//ESC押して戻る
	if (Input::Get()->GetKeyTrigger(DIK_ESCAPE)) {

		XA_Play(SE_SelectDecide);//セレクトSE再生

		if (isSelectChapter)
		{
			isSelectChapter = false;
		}
		else
		{
			//chapterを選択する場合
			SceneManager::Get()->SetScene(SCENENAME::TITLE);

		}
	}

	//スペースキー押して進む
	if (Input::Get()->GetKeyTrigger(DIK_SPACE)) {
		
		XA_Play(SE_SelectDecide);//決定SE再生

		if (!isSelectChapter) {
			isSelectChapter = true;
		}
		else {
			//Chapterを選択
			switch (selectStage)
			{
			case Game::SELECTNONE:
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
			//選択した後　初期化を行う
			InitStage();
			//シーンの切り替えを行う
			SceneManager::Get()->SetScene(STAGE);
		}

	}


	//オブジェクト更新
	//アニメション　状態更新
	UpdateSelectAnimation();

	//カーソルの位置を更新する
	UpdateCursor();

	//アニメション更新

	for (int i = 0; i < 3; i++) {
		uiSelectStage[i]->Update();
		uiSelectChapter[i]->Update();
		uiClearMark[i]->Update();
	}


}

void Game::UpdateSelectAnimation(void)
{
	for (int i = 0; i < 3; i++) {

		if (i == selectStage) {
			//ACTIVE
			uiStageSelect[i].m_anime->SetAnimePattern(CanvasUI::ACTIVE);
		}
		else {
			//INACTIVE
			//uiStageSelect[i].m_anime->SetAnimePattern(CanvasUI::INACTIVE);
			//uiStageSelect[i].m_anime->SetAnimePattern(CanvasUI::ACTIVE);
		}

	}
	
}

void Game::UpdateCursor(void)
{

	switch (selectChapter)
	{
	case Game::CHAPTER1:

		uiSelectCursor->m_pos = { 4.0f, 3.6f, 0.8f };
		break;
	case Game::CHAPTER2:

		uiSelectCursor->m_pos = { 4.0f, 1.3f, 0.8f };

		break;
	case Game::CHAPTER3:
		uiSelectCursor->m_pos = { 4.0f,-1.2f,0.8f };
		break;
	}

}

void Game::SelectStage1(void) {

	switch (selectChapter)
	{
	case Game::CHAPTER1:
		SceneManager::Get()->SetStage(STAGEINFO::STAGE1_1);
		break;
	case Game::CHAPTER2:
		SceneManager::Get()->SetStage(STAGEINFO::STAGE1_2);
		break;
	case Game::CHAPTER3:
		SceneManager::Get()->SetStage(STAGEINFO::STAGE1_3);
		break;
	default:
		break;
	}
}

void Game::SelectStage2(void) {
	switch (selectChapter)
	{
	case Game::CHAPTER1:
		SceneManager::Get()->SetStage(STAGEINFO::STAGE2_1);
		break;
	case Game::CHAPTER2:
		SceneManager::Get()->SetStage(STAGEINFO::STAGE2_2);
		break;
	case Game::CHAPTER3:
		SceneManager::Get()->SetStage(STAGEINFO::STAGE2_3);
		break;
	default:
		break;
	}
}

void Game::SelectStage3(void) {

	switch (selectChapter)
	{
	case Game::CHAPTER1:
		SceneManager::Get()->SetStage(STAGEINFO::STAGE3_1);
		break;
	case Game::CHAPTER2:
		SceneManager::Get()->SetStage(STAGEINFO::STAGE3_2);
		break;
	case Game::CHAPTER3:
		SceneManager::Get()->SetStage(STAGEINFO::STAGE3_3);
		break;
	default:
		break;
	}

}


void Game::StageUpdate(void)
{
	//Input

	if (!isPause) {

		if (Input::Get()->GetKeyTrigger(DIK_ESCAPE)) {

			XA_Play(SE_SelectDecide);//決定SE再生

			PauseSwitch();
		}

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
	
	
	//移動させる目標を設定する
	if (Input::Get()->GetKeyTrigger(DIK_SPACE)) {

		XA_Play(SE_Select);//セレクトSE再生


		for (auto it = objectList.begin(); it != objectList.end(); it++) {
			if ((*it)->GetActive()) 
			{
				(*it)->SetActive(false);
				auto nextIt = std::next(it) != objectList.end() ? std::next(it) : objectList.begin();
				(*nextIt)->SetActive(true);
				break;
			}
		}
	}

	//背景
	stageBg->Update();

	//オブジェクト
	/*for (auto& element : objectList) {
		element->Update();
	}*/

	if (coconut->GetActive() == true || 
		lamp->GetActive()== true || 
		housePlate->GetActive() == true)
	{
		if (Input::Get()->GetKeyTrigger(DIK_DOWN) ||
			Input::Get()->GetKeyTrigger(DIK_UP)   ||
			Input::Get()->GetKeyTrigger(DIK_LEFT) ||
			Input::Get()->GetKeyTrigger(DIK_RIGHT))
		{
			//ここはオブジェクトが動いた時だけSEを出したい
			/*if ()*/  { XA_Play(SE_Move); }//このままだと連打したら毎回音が出る
				
			
			
		}
	}


	coconut->Update();
	lamp->Update();
	housePlate->Update();

	if (ColliderManager::Get()->ClearCollision({ COL_DOWN,COL_RIGHT }, "coconut", "lamp", ShadowObject::MEDIUM)) {
		isPause = true;
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

void Game::ResultUpdate(void)
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

		//セレクトにいくとサウンド停止
		XA_Stop(BGM_Stage1);
		XA_Stop(BGM_Stage2);
		XA_Stop(BGM_Stage3);

		SelectUpdate();
		break;

	case SCENENAME::STAGE:
		
		//ステージにいくとセレクトBGM停止
		XA_Stop(BGM_SelectStage);
		//XA_Stop(SE_Select);
		//XA_Stop(SE_SelectDecide);

		StageUpdate();
		break;

	case SCENENAME::RESULT:
		ResultUpdate();
		break;
	}

}



Game::~Game()
{
	XA_Release();//サウンド解放

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
	//移動
	if (Input::Get()->GetKeyTrigger(DIK_DOWNARROW)) {
		
		XA_Play(SE_Select);//セレクトSE再生

		switch (pauseSelect)
		{
		case Game::RESUME:
			pauseSelect = RESTART;
			break;
		case Game::RESTART:
			pauseSelect = SELECT_STAGE;
			break;
		case Game::SELECT_STAGE:
			pauseSelect = SOUND;
			break;
		case Game::SOUND:
			pauseSelect = RESUME;
			break;

		default:
			break;
		}
	}
	//移動
	if (Input::Get()->GetKeyTrigger(DIK_UPARROW)) {
		
		XA_Play(SE_Select);//セレクトSE再生

		switch (pauseSelect)
		{
		case Game::RESUME:
			pauseSelect = SOUND;
			break;
		case Game::RESTART:
			pauseSelect = RESUME;
			break;
		case Game::SELECT_STAGE:
			pauseSelect = RESTART;
			break;
		case Game::SOUND:
			pauseSelect = SELECT_STAGE;
			break;

		default:
			break;
		}
	}
	//確認
	if (Input::Get()->GetKeyTrigger(DIK_SPACE)) {
		
		XA_Play(SE_SelectDecide);//決定SE再生

		switch (pauseSelect)
		{
		case Game::RESUME:
			PauseSwitch();
			break;
		case Game::RESTART:
			PauseSwitch();
			//ステージ内のオブジェクトを再配置
			InitStage();
			break;
		case Game::SELECT_STAGE:
			//全部初期化
			selectStage = STAGE1;
			selectChapter = CHAPTER1;
			pauseSelect = RESUME;			
			PauseSwitch();

			XA_Play(BGM_SelectStage);// セレクト画面に戻った時にBGM再生

			SceneManager::Get()->SetScene(SCENENAME::STAGESELECT);
			break;
		case Game::SOUND:
			SoundSwitch();// サウンド画面切り替え
			break;
		default:
			break;
		}
	}
	

	if (Input::Get()->GetKeyTrigger(DIK_ESCAPE))
	{
		XA_Play(SE_Select);//セレクトSE再生


		if (isSound) {
			SoundSwitch();
		}
		else {
			PauseSwitch();
		}
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

	uiPauseBg->Update();

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
		if (soundOp==SE)
		{
			soundOp = BGM;
		}
	}
	if (Input::Get()->GetKeyTrigger(DIK_DOWN))
	{
		if (soundOp==BGM)
		{
			soundOp = SE;
		}
	}

	switch (soundOp)
	{
	case BGM:
		SoundOp_BGM();
		break;

	case SE:
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
	
	if (Input::Get()->GetKeyTrigger(DIK_LEFT))
	{
		XA_Play(SE_Select);//セレクトSE再生

		switch (soundVolume_BGM)
		{
		case VOLUME0:
			break;

		case VOLUME1:
			soundVolume_BGM = VOLUME0;
			XA_SetVolume(BGM_SelectStage, 0.0f);
			XA_SetVolume(BGM_Stage1, 0.0f);
			XA_SetVolume(BGM_Stage2, 0.0f);
			XA_SetVolume(BGM_Stage3, 0.0f);
			break;

		case VOLUME2:
			soundVolume_BGM = VOLUME1;
			XA_SetVolume(BGM_SelectStage, 0.2f);
			XA_SetVolume(BGM_Stage1, 0.2f);
			XA_SetVolume(BGM_Stage2, 0.2f);
			XA_SetVolume(BGM_Stage3, 0.2f);
			break;

		case VOLUME3:
			soundVolume_BGM = VOLUME2;
			XA_SetVolume(BGM_SelectStage, 0.4f);
			XA_SetVolume(BGM_Stage1, 0.4f);
			XA_SetVolume(BGM_Stage2, 0.4f);
			XA_SetVolume(BGM_Stage3, 0.4f);
			break;

		case VOLUME4:
			soundVolume_BGM = VOLUME3;
			XA_SetVolume(BGM_SelectStage, 0.6f);
			XA_SetVolume(BGM_Stage1, 0.6f);
			XA_SetVolume(BGM_Stage2, 0.6f);
			XA_SetVolume(BGM_Stage3, 0.6f);
			break;

		case VOLUME5:
			soundVolume_BGM = VOLUME4;
			XA_SetVolume(BGM_SelectStage, 0.8f);
			XA_SetVolume(BGM_Stage1, 0.8f);
			XA_SetVolume(BGM_Stage2, 0.8f);
			XA_SetVolume(BGM_Stage3, 0.8f);
			break;
		}
	}


	if (Input::Get()->GetKeyTrigger(DIK_RIGHT))
	{
		XA_Play(SE_Select);//セレクトSE再生

		switch (soundVolume_BGM)
		{

		case VOLUME0:
			soundVolume_BGM = VOLUME1;
			XA_SetVolume(BGM_SelectStage, 0.2f);
			XA_SetVolume(BGM_Stage1, 0.2f);
			XA_SetVolume(BGM_Stage2, 0.2f);
			XA_SetVolume(BGM_Stage3, 0.2f);
			break;

		case VOLUME1:
			soundVolume_BGM = VOLUME2;
			XA_SetVolume(BGM_SelectStage, 0.4f);
			XA_SetVolume(BGM_Stage1, 0.4f);
			XA_SetVolume(BGM_Stage2, 0.4f);
			XA_SetVolume(BGM_Stage3, 0.4f);
			break;

		case VOLUME2:
			soundVolume_BGM = VOLUME3;
			XA_SetVolume(BGM_SelectStage, 0.6f);
			XA_SetVolume(BGM_Stage1, 0.6f);
			XA_SetVolume(BGM_Stage2, 0.6f);
			XA_SetVolume(BGM_Stage3, 0.6f);
			break;

		case VOLUME3:
			soundVolume_BGM = VOLUME4;
			XA_SetVolume(BGM_SelectStage, 0.8f);
			XA_SetVolume(BGM_Stage1, 0.8f);
			XA_SetVolume(BGM_Stage2, 0.8f);
			XA_SetVolume(BGM_Stage3, 0.8f);
			break;

		case VOLUME4:
			soundVolume_BGM = VOLUME5;
			XA_SetVolume(BGM_SelectStage, 1.0f);
			XA_SetVolume(BGM_Stage1, 1.0f);
			XA_SetVolume(BGM_Stage2, 1.0f);
			XA_SetVolume(BGM_Stage3, 1.0f);
			break;

		case VOLUME5:
			break;
		}
	}

}

void Game::SoundOp_SE(void)
{

	if (Input::Get()->GetKeyTrigger(DIK_LEFT))
	{
		XA_Play(SE_Select);//セレクトSE再生

		switch (soundVolume_SE)
		{
		case VOLUME0:
			break;

		case VOLUME1:
			soundVolume_SE = VOLUME0;
			XA_SetVolume(SE_Select, 0.0f);
			XA_SetVolume(SE_SelectDecide, 0.0f);
			break;

		case VOLUME2:
			soundVolume_SE = VOLUME1;
			XA_SetVolume(SE_Select, 0.2f);
			XA_SetVolume(SE_SelectDecide, 0.2f);
			break;

		case VOLUME3:
			soundVolume_SE = VOLUME2;
			XA_SetVolume(SE_Select, 0.4f);
			XA_SetVolume(SE_SelectDecide, 0.4f);
			break;

		case VOLUME4:
			soundVolume_SE = VOLUME3;
			XA_SetVolume(SE_Select, 0.6f);
			XA_SetVolume(SE_SelectDecide, 0.6f);
			break;

		case VOLUME5:
			soundVolume_SE = VOLUME4;
			XA_SetVolume(SE_Select, 0.8f);
			XA_SetVolume(SE_SelectDecide, 0.8f);
			break;
		}
	}

	if (Input::Get()->GetKeyTrigger(DIK_RIGHT))
	{
		XA_Play(SE_Select);//セレクトSE再生

		switch (soundVolume_SE)
		{
		case VOLUME0:
			soundVolume_SE = VOLUME1;
			XA_SetVolume(SE_Select, 0.2f);
			XA_SetVolume(SE_SelectDecide, 0.2f);
			break;

		case VOLUME1:
			soundVolume_SE = VOLUME2;
			XA_SetVolume(SE_Select, 0.4f);
			XA_SetVolume(SE_SelectDecide, 0.4f);
			break;

		case VOLUME2:
			soundVolume_SE = VOLUME3;
			XA_SetVolume(SE_Select, 0.6f);
			XA_SetVolume(SE_SelectDecide, 0.6f);
			break;

		case VOLUME3:
			soundVolume_SE = VOLUME4;
			XA_SetVolume(SE_Select, 0.8f);
			XA_SetVolume(SE_SelectDecide, 0.8f);
			break;

		case VOLUME4:
			soundVolume_SE = VOLUME5;
			XA_SetVolume(SE_Select, 1.0f);
			XA_SetVolume(SE_SelectDecide, 1.0f);
			break;

		case VOLUME5:
			break;
		}
	}


}


void Game::GameDraw()
{

	D3D_ClearScreen();

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
	case SCENENAME::RESULT:
		ResultDraw();

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

void Game::SelectDraw(void)
{
	uiSelectBg->Draw();
	uiStageSelect->Draw();
	uiSelectCursor->Draw();

	uiSelectDraw();

}

void Game::uiSelectDraw(void)
{
	for (int i = 0; i < 3; i++) {
	
		//ステージボタン描画
		uiSelectStage[i]->Draw();

		//チャプター描画
		uiSelectChapter[i]->Draw();

		//クリア印の描画
		uiClearMark[i]->Draw();
	
	}
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

	//描画の順番を並び変え

	//影
	SortShadowDraw();

	//オブジェクト
	SortObjectDraw();

	float posX = (-SCREEN_WIDTH / 2 + 40.0f) / SCREEN_PARA;
	float posY = ((SCREEN_HEIGHT / 2) - 40.0f) / SCREEN_PARA;
	g_DebugManager->PrintDebugLog(posX, posY, testObj->m_obj->m_sprite->m_pos.x);

	posX = (-SCREEN_WIDTH / 2 + 40.0f) / SCREEN_PARA;
	posY = ((SCREEN_HEIGHT / 2) - 80.0f) / SCREEN_PARA;
	g_DebugManager->PrintDebugLog(posX, posY, testObj->m_obj->m_sprite->m_pos.y);

	posX = (-SCREEN_WIDTH / 2 + 40.0f) / SCREEN_PARA;
	posY = ((SCREEN_HEIGHT / 2) - 120.0f) / SCREEN_PARA;
	g_DebugManager->PrintDebugLog(posX, posY, testObj->m_obj->m_sprite->m_pos.z);

	//レール上どこが空いてるのを可視化
	posX = (-SCREEN_WIDTH / 2 + 40.0f) / SCREEN_PARA;
	posY = ((SCREEN_HEIGHT / 2) - 160.0f) / SCREEN_PARA;
	char pointInfo1[20] = {};
	for (int i = 0; i < 5; i++) {
		if (RailManager::Get()->m_info[i].isVacant) {
			char tempStr[3];
			std::snprintf(tempStr, sizeof(tempStr), " %d", 0);
			strcat_s(pointInfo1, tempStr);
		
		}
		else {
			char tempStr[3];
			std::snprintf(tempStr, sizeof(tempStr), " %d", 1);
			strcat_s(pointInfo1, tempStr);
		}

	}
	char pointInfo2[20] = {};
	for (int i = 5; i < 10; i++) {
		if (RailManager::Get()->m_info[i].isVacant) {
			char tempStr[3];
			std::snprintf(tempStr, sizeof(tempStr), " %d", 0);
			strcat_s(pointInfo2, tempStr);

		}
		else {
			char tempStr[3];
			std::snprintf(tempStr, sizeof(tempStr), " %d", 1);
			strcat_s(pointInfo2, tempStr);
		}

	}
	char pointInfo3[20] = {};
	for (int i = 10; i < 15; i++) {
		if (RailManager::Get()->m_info[i].isVacant) {
			char tempStr[3];
			std::snprintf(tempStr, sizeof(tempStr), " %d", 0);
			strcat_s(pointInfo3, tempStr);

		}
		else {
			char tempStr[3];
			std::snprintf(tempStr, sizeof(tempStr), " %d", 1);
			strcat_s(pointInfo3, tempStr);
		}

	}
	g_DebugManager->PrintDebugLog(posX, posY, pointInfo1);
	posY = ((SCREEN_HEIGHT / 2) - 200.0f) / SCREEN_PARA;
	g_DebugManager->PrintDebugLog(posX, posY, pointInfo2);
	posY = ((SCREEN_HEIGHT / 2) - 240.0f) / SCREEN_PARA;
	g_DebugManager->PrintDebugLog(posX, posY, pointInfo3);

	//今移動しているオブジェクト
	for (auto& element : objectList) {
		
		if (element->GetActive()) {
			posX= 0.0f;
			posY = ((SCREEN_HEIGHT / 2) - 40.0f) / SCREEN_PARA;
			char name[32] = {};
			strcpy_s(name, element->GetName().c_str());
			g_DebugManager->PrintDebugLog(posX, posY, name);
			break;
			
		}

	}
	

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
	else//サウンド画面に入る
	{
		uiSoundBg->Draw();

		//音量調節の描画
		SoundVolumeDraw();

	}
}

void Game::SoundVolumeDraw(void)
{
	if (soundOp == BGM || soundOp == SE)
	{

		//BGM音量調節描画
		switch (soundVolume_BGM)
		{
		case VOLUME0:
			//何も描画しない
			break;

		case VOLUME1:
			uiSoundOp_BGM[1]->Draw();
			break;

		case VOLUME2:
			for (int i = 1; i < 3; i++)
			{
				uiSoundOp_BGM[i]->Draw();//１～２描画
			}	
			break;

		case VOLUME3:
			for (int i = 1; i < 4; i++)
			{
				uiSoundOp_BGM[i]->Draw();//１～３描画
			}
			break;

		case VOLUME4:
			for (int i = 1; i < 5; i++)
			{
				uiSoundOp_BGM[i]->Draw();//１～４描画
			}
			break;

		case VOLUME5:
			for (int i = 1; i < 6; i++)
			{
				uiSoundOp_BGM[i]->Draw();//１～５描画
			}
			break;

		}
		



		
		//SE音量調節描画
		switch (soundVolume_SE)
		{
		case VOLUME0:
			//何も描画しない
			break;

		case VOLUME1:
			uiSoundOp_SE[1]->Draw();
			break;

		case VOLUME2:
			for (int i = 1; i < 3; i++)
			{
				uiSoundOp_SE[i]->Draw();//１～２描画
			}
			break;

		case VOLUME3:
			for (int i = 1; i < 4; i++)//１～３描画
			{
				uiSoundOp_SE[i]->Draw();
			}
			break;

		case VOLUME4:
			for (int i = 1; i < 5; i++)//１～４描画
			{
				uiSoundOp_SE[i]->Draw();
			}
			break;

		case VOLUME5:
			for (int i = 1; i < 6; i++)//１～５描画
			{
				uiSoundOp_SE[i]->Draw();
			}
			break;
		}	
		


	}
}

void Game::SortObjectDraw(void)
{
	std::sort(objectList.begin(), objectList.end(), [](GameObject* obj1, GameObject* obj2) {
		if (obj1->GetRailPos().verticalPos == obj2->GetRailPos().verticalPos) {
			return obj1->GetRailPos().horizontalPos <  obj2->GetRailPos().horizontalPos;
		}
		return obj1->GetRailPos().verticalPos <  obj2->GetRailPos().verticalPos;
		});

	for (auto& element : objectList) {
		element->m_obj->Draw();
	}
}

void Game::SortShadowDraw(void)
{

	std::sort(objectList.begin(), objectList.end(), [](GameObject* obj1, GameObject* obj2) {
		
		return obj1->m_shadow->m_sprite->m_pos.z > obj2->m_shadow->m_sprite->m_pos.z;
	});

	for (auto& element : objectList) {
		
		element->m_shadow->Draw();
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
			fade->SetActive(false);
		}
	}
	else if (fadeState == FADE_OUT)
	{
		fade->m_materialDiffuse.w += 0.01f;

		if (fade->m_materialDiffuse.w >= 1.0f)
		{
			SceneManager::Get()->SetScene(SceneManager::Get()->GetNextScene());
		}
	}
}

//if (!SceneManager::Get()->GetScene())
//{
//	SceneManager::Get()->SetNextScene(SceneManager::Get()->GetNextScene());
//	fadeState = FADE_OUT;
//	fade->SetActive(true);
//}
//else
//{
//	SceneManager::Get()->SetScene(SceneManager::Get()->GetNextScene());
//	fadeState = FADE_IN;
//
//}

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
