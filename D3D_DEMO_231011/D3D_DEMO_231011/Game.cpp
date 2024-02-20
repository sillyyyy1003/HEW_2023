﻿#include "Game.h"
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
#include "Effect.h"
#include "xa2.h"
#include "CameraShaker.h"
#include <stdio.h> 
#include <algorithm> // 必要なヘッダーファイル
#include "Result.h"
#include "ResultAnimation.h"
#include "ResultProcess.h"
#include "Fade.h"



#define MOVE 0.1f
#define INITROTATE	(19.8)

extern Assets* g_Assets;
extern Camera* g_WorldCamera;
extern DebugManager* g_DebugManager;

void Game::Init()
{
	//CameraShakerの初期化
	cameraShaker = new CameraShaker();
	//強度、周波数、継続の時間の初期化を行う
	cameraShaker->InitCameraShaker(0.1f, 3.0f, 20);

	resultGenerator = new Result();
	resultAnimator = new ResultAnimation();
	fade = new Fade();
	fade->FadeIn();

	//=============================
	//オブジェクト作成
	//=============================
	//uiTitle = new CanvasUI();
	uiTitleBg = new CanvasUI();
	uiPressSpace = new CanvasUI();
	comingSoon = new CanvasUI();
	comingSoonLoop = new CanvasUI();

	uiRestart = new CanvasUI();
	uiResume = new CanvasUI();
	uiSelect = new CanvasUI();
	uiSound = new CanvasUI();
	uiPauseBg = new CanvasUI();
	uiSoundCursor = new CanvasUI();

	uiSoundBg = new CanvasUI();
	

	for (int i = 0; i < 6; i++)
	{
		uiSoundOp_BGM[i] = new CanvasUI;
		uiSoundOp_SE[i] = new CanvasUI;
	}

	uiSelectBg = new CanvasUI();
	uiSelectCursor = new CanvasUI();

	for (int i = 0; i < 3; i++)
	{
		uiSelectStage[i] = new CanvasUI();
		uiSelectChapter[i] = new CanvasUI();
		uiClearMark[i] = new CanvasUI();
	}

	//mask&panel
	controlPanel = new CanvasUI();
	stageMask = new CanvasUI();
	pauseMask = new CanvasUI();
	resultMask = new CanvasUI();
	uiArrow = new  CanvasUI();
	//stepの手数
	uiStepNum = new ResultProcess();



	//共通の背景
	stageBg = new StaticObject();

	//stage1-1
	coconut = new GameObject();
	lamp = new GameObject();
	housePlate = new GameObject();

	//STAGE1-2
	lamp1_2 = new GameObject();
	iphone = new GameObject();
	triangleBlock = new GameObject();

	//stage1-3
	sandwich = new GameObject();
	newspaper = new GameObject();
	bucket = new GameObject();
	picnicbasket = new GameObject();

	//result
	resultGenerator->Init();
	resultAnimator->Init();

	//EFFECT
	testEffect = new Effect(12);


	//stage1に使われてる
	//移動のオブジェクトの名前を設定する
	coconut->SetName("coconut");
	lamp->SetName("lamp");
	housePlate->SetName("housePlate");

	//stage2に使われてる
	//移動のオブジェクトの名前を設定する
	lamp1_2->SetName("lamp1_2");
	iphone->SetName("iphone");
	triangleBlock->SetName("triangleBlock");
	//stage3に使われてる

	sandwich->SetName("sandwich");		//直角三角形
	newspaper->SetName("newspaper");		//四角
	bucket->SetName("bucket");			//台形（四角）
	picnicbasket->SetName("picnicbasket");;  //台形（四角）


	//移動のオブジェクトの名前を設定する
	//テクスチャ読み込み・モデル作成
	uiTitleBg->CreateModel(g_Assets->uiTitleBg, 1280, 720, 8, 2);
	comingSoon->CreateModel(g_Assets->comingSoon, 1280, 720, 6, 6);
	comingSoonLoop->CreateModel(g_Assets->comingSoonLoop, 1280, 720, 6, 2);
	uiPressSpace->CreateModel(g_Assets->uiPressSpace, 415, 38, 1, 1);

	uiPauseBg->CreateModel(g_Assets->uiPauseBg, 647, 702, 1, 1);
	uiResume->CreateModel(g_Assets->uiResume, 280, 92, 1, 2);
	uiRestart->CreateModel(g_Assets->uiRestart, 280, 92, 1, 2);
	uiSelect->CreateModel(g_Assets->uiSelect, 280, 92, 1, 2);
	uiSound->CreateModel(g_Assets->uiSound, 280, 92, 1, 2);

	uiSoundBg->CreateModel(g_Assets->uiSoundBg, 687, 550, 1, 1);
	uiSelectBg->CreateModel(g_Assets->uiSelectBg, 1280, 720, 1, 1);
	uiSelectCursor->CreateModel(g_Assets->uiSelectCursor, 76, 84, 1, 1);
	uiSoundCursor->CreateModel(g_Assets->uiSoundCursor, 56, 51, 1, 1);

	uiSelectStage[STAGE1]->CreateModel(g_Assets->uiSelectStage1, 421, 133, 1, 2);
	uiSelectStage[STAGE2]->CreateModel(g_Assets->uiSelectStage2, 421, 142, 1, 2);
	uiSelectStage[STAGE3]->CreateModel(g_Assets->uiSelectStage3, 421, 143, 1, 2);

	uiSelectChapter[CHAPTER1]->CreateModel(g_Assets->uiSelectChapter1, 288, 57, 1, 1);
	uiSelectChapter[CHAPTER2]->CreateModel(g_Assets->uiSelectChapter2, 300, 57, 1, 1);
	uiSelectChapter[CHAPTER3]->CreateModel(g_Assets->uiSelectChapter3, 300, 57, 1, 1);

	for (int i = 0; i < 3; i++)
	{
		uiClearMark[i]->CreateModel(g_Assets->uiClear, 87, 87, 1, 1);
	}

	stageMask->CreateModel(g_Assets->stageMask, 1280, 720, 1, 1);
	pauseMask->CreateModel(g_Assets->resultMask, 1280, 720, 1, 1);
	resultMask->CreateModel(g_Assets->resultMask, 1280, 720, 1, 1);
	controlPanel->CreateModel(g_Assets->controlPanel, 1280, 720, 1, 1);

	//手数表示
	//表示の大きさを変える
	uiStepNum->SetSize(0.5);
	uiStepNum->Init(-7.7, 3.3,0.5,1);//調整いる

	//stage1
	stageBg->CreateObject(g_Assets->stageBg1_1, 1280, 720, 6, 1);
	//stage1-1
	coconut->CreateObject(g_Assets->coconut, 190, 192, 1, 1);
	coconut->CreateShadow(g_Assets->coconutShadow, 158, 159, 1, 1, COLLISION_TYPE::SPHERE);
	lamp->CreateObject(g_Assets->lamp, 216, 579, 1, 1);
	lamp->CreateShadow(g_Assets->lampShadow, 216, 579, 1, 1, COLLISION_TYPE::SQUARE);
	housePlate->CreateObject(g_Assets->housePlate, 110, 216, 1, 1);
	housePlate->CreateShadow(g_Assets->housePlateShadow, 50, 105, 1, 1, COLLISION_TYPE::SQUARE);

	//stage1-2
	lamp1_2->CreateObject(g_Assets->lamp_1_2, 264, 267, 1, 1);
	lamp1_2->CreateShadow(g_Assets->lamp_1_2Shadow, 217.5, 217.5, 1, 1, COLLISION_TYPE::SQUARE);
	iphone->CreateObject(g_Assets->iphone, 186, 141, 1, 1);
	iphone->CreateShadow(g_Assets->iphoneShadow, 205, 155, 1, 1, COLLISION_TYPE::SQUARE);
	triangleBlock->CreateObject(g_Assets->triangleBlock, 378, 348, 1, 1);
	//->CreateShadow(g_Assets->triangleBlockShadow, 190.5, 172.5, 1, 1, COLLISION_TYPE::TRIANGLE, TRIANGLE_TYPE::TRI_ISO);
	triangleBlock->CreateShadow(g_Assets->triangleBlockShadow, 190.5, 172.5, 1, 1, COLLISION_TYPE::SQUARE);

	//1-3
	sandwich->CreateObject(g_Assets->sandwich, 211.5, 238.5, 1, 1);
	sandwich->CreateShadow(g_Assets->sandwichShadow, 126, 144, 1, 1, COLLISION_TYPE::SQUARE);
	newspaper->CreateObject(g_Assets->newspaper, 301.5, 229.5, 1, 1);
	newspaper->CreateShadow(g_Assets->newspaperShadow, 361.8, 300, 1, 1, COLLISION_TYPE::SQUARE);
	bucket->CreateObject(g_Assets->busket, 255, 219, 1, 1);
	bucket->CreateShadow(g_Assets->busketShadow, 306, 262.8, 1, 1, COLLISION_TYPE::SQUARE);
	picnicbasket->CreateObject(g_Assets->picnicbasket, 306, 240, 1, 1);
	picnicbasket->CreateShadow(g_Assets->picnicbasketShadow, 275.4, 216, 1, 1, COLLISION_TYPE::SQUARE);
	
	testEffect->CreateModel(g_Assets->effect1, 256, 256, 3, 4);
	uiArrow->CreateModel(g_Assets->uiArrow, 17, 17, 8, 1);


	//アニメーションの設定
	coconut->InitAnimation();
	lamp->InitAnimation();
	housePlate->InitAnimation();

	lamp1_2->InitAnimation();
	iphone->InitAnimation();
	triangleBlock->InitAnimation();

	sandwich->InitAnimation();	    
	newspaper->InitAnimation();	    //四角
	bucket->InitAnimation();		//台形（四角）
	picnicbasket->InitAnimation();   //台形（四角）


	//----------------------------//
	// ここからはエフェクトの初期化
	//----------------------------//
	testEffect->m_pos.z = 0.0f;
	testEffect->m_anime->SetAnimeSpeed(0.2f);
	testEffect->Effect::SetActive(true);
	testEffect->Effect::SetLoop(true);
	testEffect->m_scale.x = 1.2f;
	testEffect->m_scale.y = 1.2f;
	testEffect->m_rotation.x = 95;


	//----------------------------//
	// ここからはシーンの初期化
	//----------------------------//

	//Title の初期化
	//位置設定
	
	uiTitleBg->m_pos = { 0.0f,0.0f,0.9f };
	uiTitleBg->m_anime->SetAnimePattern(0);
	uiTitleBg->m_anime->SetAnimeSpeed(0.15f);
	uiTitleBg->SetLoop(false);
	uiTitleBg->isMultiPattern = true;

	comingSoon->m_pos = { 0.0f,0.0f,0.8f };
	comingSoon->m_anime->SetAnimeSpeed(0.15f);
	comingSoon->SetLoop(false);
	comingSoon->isMultiPattern = false;
	comingSoonLoop->m_pos = { 0.0f,0.0f,0.9f };
	comingSoonLoop->m_anime->SetAnimeSpeed(0.15f);
	comingSoonLoop->SetLoop(true);
	comingSoonLoop->isMultiPattern = false;

	//Title Animation
	uiTitleBg->InitAnimation(8);
	uiTitleBg->SetAnimeted(true);

	//coming soon Animation
	comingSoon->InitAnimation(36);
	comingSoonLoop->InitAnimation(12);
	comingSoon->SetAnimeted(true);
	comingSoonLoop->SetAnimeted(true);
	
	uiPressSpace->m_pos = { 0.0f,-2.5f,0.2f };
	uiPressSpace->SetActive(false);	//最初で隠す

	//ARROW

	uiArrow->m_pos = { 6,325 / SCREEN_PARA,0.1 };
	uiArrow->m_anime->SetAnimeSpeed(0.15f);

	//Title Animation
	uiArrow->InitAnimation(8);
	uiArrow->SetAnimeted(true);
	uiArrow->SetLoop(true);


	//Select画面
	uiSelectBg->m_pos = { 0.0f,0.04f,0.9f };
	uiSelectBg->m_scale = { 0.98f,0.98f,0.9f };
	uiSelectCursor->m_pos = { 5.2f,3.6f,0.8f };//Chapterの横に出るように
	float posy = 2.3;
	uiClearMark[0]->m_pos = { 4.5f,posy,0.7f };
	posy = 2.3 - 2.5;
	uiClearMark[1]->m_pos = { 5.0f,posy,0.7f };
	posy = 2.3 - 2.5 * 2;
	uiClearMark[2]->m_pos = { 4.8f,posy,0.7f };


	//uiPause
	uiPauseBg->m_pos = { -300 / SCREEN_PARA, 0.0f, 0.8f };
	uiResume->m_pos = { -6.0f, 1.7f, 0.7f };
	uiRestart->m_pos = { -6.0f, 0.35f, 0.7f };
	uiSelect->m_pos = { -6.0f, -1.0f, 0.7f };
	uiSound->m_pos = { -6.0f, -2.35f, 0.7f };

	//uiSound
	uiSoundBg->m_pos = { 1.0f, 0.2f, 0.6f };
	uiSoundBg->m_scale = { 1.0f,1.0f,1.0f };//サウンドのPOSZ ->0.5f

	//controlPanel;
	controlPanel->m_pos = { 0,0,0.2};//一番手前にする
	controlPanel->m_scale = { 0.96,0.96,0.96 };

	//マスクの位置設定
	stageMask->m_pos.z = 0.7f;//hintの後ろ
	pauseMask->m_pos.z = 0.9f;
	resultMask->m_pos.z = 0.9f;

	uiSoundCursor->m_pos = { -2.0f, 0.65f, 0.5f };

	//配列の初期化と設定
	InitSoundArray();
	InitSelectArray();
	InitHintArray();


	// サウンド初期化
	HRESULT hr;
	hr = XA_Initialize();
	if (FAILED(hr))
	{
		MessageBoxA(NULL, "サウンド初期化失敗", "エラー", MB_OK | MB_ICONERROR);
	}

	// リザルト初期化
	clear1_1 = new CanvasUI();
	clear1_2 = new CanvasUI();
	clear1_3 = new CanvasUI();

	//テクスチャ読み込み・モデル作成
	clear1_1->CreateModel(g_Assets->resultComic1_1_2, 707, 503, 1, 1);
	clear1_2->CreateModel(g_Assets->resultComic1_1_3, 650, 476, 1, 1);
	clear1_3->CreateModel(g_Assets->resultComic1_1_1, 502, 642, 1, 1);

	// 画像１～３の移動前の初期位置
	clear1_1->m_pos = { 12.0f,7.6f,0.4f };   //右上　z座標　真ん中 
	clear1_2->m_pos = { -12.1f,7.6f,0.3f };  //左上　z座標　手前
	clear1_3->m_pos = { 0.0f,-8.6f,0.5f };   //下　　z座標　奥

	clear2_1 = new CanvasUI();
	clear2_2 = new CanvasUI();
	clear2_3 = new CanvasUI();

	//テクスチャ読み込み・モデル作成
	clear2_1->CreateModel(g_Assets->resultComic1_2_2, 707, 503, 1, 1);
	clear2_2->CreateModel(g_Assets->resultComic1_2_3, 502, 642, 1, 1);
	clear2_3->CreateModel(g_Assets->resultComic1_2_1, 650, 476, 1, 1);

	// 画像１～３の移動前の初期位置
	clear2_1->m_pos = { 12.0f,7.6f,0.4f };   //右上　z座標　真ん中 
	clear2_2->m_pos = { -12.1f,7.6f,0.3f };  //左上　z座標　手前
	clear2_3->m_pos = { 0.0f,-8.6f,0.5f };   //下　　z座標　奥

	clear3_1 = new CanvasUI();
	clear3_2 = new CanvasUI();
	clear3_3 = new CanvasUI();

	//テクスチャ読み込み・モデル作成
	clear3_1->CreateModel(g_Assets->resultComic1_3_2, 707, 503, 1, 1);
	clear3_2->CreateModel(g_Assets->resultComic1_3_3, 650, 476, 1, 1);
	clear3_3->CreateModel(g_Assets->resultComic1_3_1, 502, 642, 1, 1);

	// 画像１～３の移動前の初期位置
	clear3_1->m_pos = { 12.0f,7.6f,0.4f };   //右上　z座標　真ん中 
	clear3_2->m_pos = { -12.1f,7.6f,0.3f };  //左上　z座標　手前
	clear3_3->m_pos = { 0.0f,-8.6f,0.5f };   //下　　z座標　奥


	SceneManager::Get()->SetScene(SCENENAME::TITLE);
	RailManager::Get()->InitRail();
	
}


void Game::InitTitle(void)
{
	uiTitleBg->m_pos = { 0.0f,0.0f,0.9f };
	uiTitleBg->m_anime->SetAnimePattern(0);
	uiTitleBg->m_anime->SetAnimeSpeed(0.15f);
	uiTitleBg->SetLoop(false);
	uiTitleBg->isMultiPattern = true;
	uiTitleBg->SetAnimeted(true);
}

void Game::InitStage()
{

	//ステージの初期化
	switch (SceneManager::Get()->GetStage()) {

	case STAGE1_1:

		XA_Play(BGM_Stage1);//サウンド再生
		XA_SetVolume(BGM_Stage1, 0.0f);//お題が出たときのSEを邪魔しないように音量を
		InitStage1_1();

		break;

	case STAGE1_2:

		XA_Play(BGM_Stage1);//サウンド再生
		XA_SetVolume(BGM_Stage1, 0.0f);
		InitStage1_2();

		break;

	case STAGE1_3:

		XA_Play(BGM_Stage1);//サウンド再生
		XA_SetVolume(BGM_Stage1, 0.0f);
		InitStage1_3();

		break;
		
	case STAGE2_1:

		XA_Play(BGM_Stage2);//サウンド再生
		XA_SetVolume(BGM_Stage2, 0.0f);
		InitStage2_1();

		break;

	case STAGE2_2:

		XA_Play(BGM_Stage2);//サウンド再生
		XA_SetVolume(BGM_Stage2, 0.0f);
		InitStage2_2();

		break;

	case STAGE2_3:

		XA_Play(BGM_Stage2);//サウンド再生
		XA_SetVolume(BGM_Stage2, 0.0f);
		InitStage2_3();

		break;

	case STAGE3_1:

		XA_Play(BGM_Stage3);//サウンド再生
		XA_SetVolume(BGM_Stage3, 0.0f);
		InitStage3_1();

		break;
	case STAGE3_2:

		XA_Play(BGM_Stage3);//サウンド再生
		XA_SetVolume(BGM_Stage3, 0.0f);
		InitStage3_2();

		break;

	case STAGE3_3:

		XA_Play(BGM_Stage3);//サウンド再生
		XA_SetVolume(BGM_Stage3, 0.0f);
		InitStage3_3();

		break;
	case STAGE_IDLE:
		//範囲に超えたらタイトルに戻る
		break;
	}

	if (SceneManager::Get()->GetStage() != STAGE_UNDONE) {

		//ヒントの状態を全部inactiveにします。
		for (int i = 0; i < STAGE_NUM; i++) {
			SceneManager::Get()->m_stageHolder[i]->SetHint(false);
		}
		//ヒントを出す
		SceneManager::Get()->m_stageHolder[SceneManager::Get()->GetActiveStage()]->SetHint(true);
	}

	for (int i = 0; i < STAGE_NUM; i++) {
		SceneManager::Get()->m_stageHolder[i]->SetClear(false);
	}


}

void Game::InitStage1_1(void)
{
	
	//背景を設定する
	SetBackGround(g_Assets->stageBg1_1);

	//オブジェクトを設定する
	//CAUTION! 
	//本体y軸固定->-1
	//Z:FRONT:-10 MIDDLE:-7.5 BACK:-5
	//X:LEFT2:-9 LEFT1:-4.5 MIDDLE:0.0 RIGHT1:4.5 RIGHT2:9

	housePlate->m_obj->m_sprite->m_pos = { -4.5f,-4.0f,-5.0f };
	lamp->m_obj->m_sprite->m_pos = { 0.0f,-4.0f,-5.0f };
	coconut->m_obj->m_sprite->m_pos = { -4.5f,-4.0f,-7.5f };

	coconut->m_shadow->m_sprite->m_pos.z = 0.0f;
	lamp->m_shadow->m_sprite->m_pos.z = -0.1f;
	housePlate->m_shadow->m_sprite->m_pos.z = -0.2f;


	//影のy軸
	coconut->m_shadow->m_sprite->m_pos.y = 7.1f;
	lamp->m_shadow->m_sprite->m_pos.y = 4.3f;
	housePlate->m_shadow->m_sprite->m_pos.y = 2.3f;

	
	//レール上の位置を設定する
	coconut->SetRailPos(1, 1);
	lamp->SetRailPos(2, 0);
	housePlate->SetRailPos(1, 0);

	//objectListを初期化
	objectList.clear();
	objectList.shrink_to_fit();
	objectList.push_back(coconut);
	objectList.push_back(lamp);
	objectList.push_back(housePlate);

	RailManager::Get()->InitRail();
	RailManager::Get()->InitRailPos();
	//レールの初期化
	RailInit1_1();

	//ステージ情報を初期化
	for (int i = 0; i < 9; i++) {
		//全部のステージを無効かにする
		SceneManager::Get()->m_stageHolder[i]->Init();

	}
	//使うステージだけ起動
	SceneManager::Get()->m_stageHolder[STAGEINFO::STAGE1_1]->SetActive(true);
	//STAGE状態をリセット
	SceneManager::Get()->m_stageHolder[STAGEINFO::STAGE1_1]->ResetStage();
	
	//全部のオブジェクトをINACTIVEに設定する
	for (auto& element : objectList) {
		element->SetActive(false);
	}
	//移動ターゲットを設定
	coconut->SetActive(true);

	//自動移動や自動回転の設定
	
	//クリアのレベルを設定
	resultGenerator->SetStarNum({ 12,14,19,22 });

}

void Game::InitStage1_2(void)
{
	//背景を設定
	SetBackGround(g_Assets->stageBg1_2);
	//オブジェクトを設定する
	//CAUTION! 
	//本体y軸固定->-1
	//Z:FRONT:-10 MIDDLE:-7.5 BACK:-5
	//X:LEFT2:-9 LEFT1:-4.5 MIDDLE:0.0 RIGHT1:4.5 RIGHT2:9
	//本体 
	//lamp1_2->m_obj->m_sprite->m_pos = { 0.0f,0.0f,-10.0f };
	lamp1_2->m_obj->m_sprite->m_pos = { 0.0f,-4.0f,-10.0f };
	iphone->m_obj->m_sprite->m_pos = { -4.5f,-4.0f,-10.0f };
	triangleBlock->m_obj->m_sprite->m_pos = {0.0f,-4.0f,-5.0f };

	//影
	lamp1_2->m_shadow->m_sprite->m_pos.z = 0.0f;
	iphone->m_shadow->m_sprite->m_pos.z = -0.1f;
	triangleBlock->m_shadow->m_sprite->m_pos.z = -0.2f;

	lamp1_2->m_shadow->m_sprite->m_pos.y = 3.09f;
	iphone->m_shadow->m_sprite->m_pos.y = 4.275f;
	triangleBlock->m_shadow->m_sprite->m_pos.y =2.2f;


	//レール上の位置を設定する
	lamp1_2->SetRailPos(2, 2);
	iphone->SetRailPos(1, 2);
	triangleBlock->SetRailPos(2, 0);


	//objectListを初期化
	objectList.clear();
	objectList.shrink_to_fit();
	objectList.push_back(lamp1_2);
	objectList.push_back(iphone);
	objectList.push_back(triangleBlock);

	//レールの設定
	//レールの初期化
	RailManager::Get()->InitRail();
	//レールの初期化
	RailInit1_2();

	//ステージ情報を初期化
	for (int i = 0; i < 9; i++) {
		//全部のステージを無効かにする
		SceneManager::Get()->m_stageHolder[i]->Init();

	}
	//使うステージだけ起動
	SceneManager::Get()->m_stageHolder[STAGEINFO::STAGE1_2]->SetActive(true);
	//STAGE状態をリセット
	SceneManager::Get()->m_stageHolder[STAGEINFO::STAGE1_2]->ResetStage();

	//全部のオブジェクトをINACTIVEに設定する
	for (auto& element : objectList) {
		element->SetActive(false);
	}
	//移動ターゲットを設定
	lamp1_2->SetActive(true);

	//自動移動や自動回転の設定

	//クリアのレベルを設定
	resultGenerator->SetStarNum({ 8,10,15,18 });

	//状態のリセット
	for (auto& element : objectList) {
	
		element->ResetMove();
	}
}

void Game::InitStage1_3(void)
{

	//位置設定
	SetBackGround(g_Assets->stageBg1_3);
	//オブジェクトを設定する
	//CAUTION! 
	//本体y軸固定->-1
	//Z:FRONT:-10 MIDDLE:-7.5 BACK:-5
	//X:LEFT2:-9 LEFT1:-4.5 MIDDLE:0.0 RIGHT1:4.5 RIGHT2:9
	//本体 
	bucket->m_obj->m_sprite->m_pos = { -4.5f,-4.0f,-5.0f };
	newspaper->m_obj->m_sprite->m_pos = { 0.0f,-4.0f,-5.0f };
	sandwich->m_obj->m_sprite->m_pos = { 4.5f,-4.0f,-5.0f };
	picnicbasket->m_obj->m_sprite->m_pos = { 4.5f,-4.0f,-10.0f };

	bucket->m_shadow->m_sprite->m_pos.z = 0.5f;
	newspaper->m_shadow->m_sprite->m_pos.z = 0.4f;
	sandwich->m_shadow->m_sprite->m_pos.z = 0.3f;
	picnicbasket->m_shadow->m_sprite->m_pos.z = 0.2f;


	//影のy軸
	bucket->m_shadow->m_sprite->m_pos.y = 5.0f;
	newspaper->m_shadow->m_sprite->m_pos.y = 2.5f;
	sandwich->m_shadow->m_sprite->m_pos.y = 2.46f;
	picnicbasket->m_shadow->m_sprite->m_pos.y = 3.45f;


	//レール上の位置を設定する
	bucket->SetRailPos(1, 0);
	newspaper->SetRailPos(2, 0);
	sandwich->SetRailPos(3, 0);
	picnicbasket->SetRailPos(3, 2);

	//回転設定

	//objectListを初期化
	objectList.clear();
	objectList.shrink_to_fit();
	objectList.push_back(picnicbasket);
	objectList.push_back(sandwich);
	objectList.push_back(newspaper);
	objectList.push_back(bucket);

	//レールの設定
	RailManager::Get()->InitRail();
	RailInit1_3();

	//ステージ情報を初期化
	for (int i = 0; i < 9; i++) {
		//全部のステージを無効かにする
		SceneManager::Get()->m_stageHolder[i]->Init();

	}
	//使うステージだけ起動
	SceneManager::Get()->m_stageHolder[STAGEINFO::STAGE1_3]->SetActive(true);

	//全部のオブジェクトをINACTIVEに設定する
	for (auto& element : objectList) {
		element->SetActive(false);
	}
	//移動ターゲットを設定
	sandwich->SetActive(true);

	//自動移動や自動回転の設定

	resultGenerator->SetStarNum({ 24,26,30,33 });



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

	bool railData[15][8]{
		//back row
		//up	ru  r	rd d	ld l	lu
		{	0,	0,	1,	0,	0,	0,	0,	0},//0
		{	0,	0,	1,	0,	1,	0,	1,	0},//1
		{	0,	0,	1,	0,	0,	0,	1,	0},//2
		{	0,	0,	1,	0,	0,	0,	1,	0},//3
		{	0,	0,	0,	0,	0,	0,	1,	0},//4

		//mid row
		{	0,	0,	0,	0,	0,	0,	0,	0},
		{	1,	0,	0,	0,	1,	0,	0,	0},
		{	0,	0,	0,	0,	0,	0,	0,	0},
		{	0,	0,	0,	0,	0,	0,	0,	0},
		{	0,	0,	0,	0,	0,	0,	0,	0},

		//front row
		{	0,	0,	0,	0,	0,	0,	0,	0},
		{	1,	0,	0,	0,	0,	0,	0,	0},
		{	0,	0,	0,	0,	0,	0,	0,	0},
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
	

	//オブジェクトいるところの位置情報更新
	RailManager::Get()->InitRailPos();

}

void Game::RailInit1_2(void)
{
	bool railData[15][8]{
		//back row
		//up	ru  r	rd d	ld l	lu
		{	0,	0,	0,	0,	0,	0,	0,	0},//0
		{	0,	0,	0,	0,	0,	0,	0,	0},//1
		{	0,	0,	0,	0,	1,	0,	0,	0},//2
		{	0,	0,	0,	0,	0,	0,	0,	0},//3
		{	0,	0,	0,	0,	0,	0,	0,	0},//4

		//mid row
		{	0,	0,	0,	0,	0,	0,	0,	0},
		{	0,	0,	0,	0,	0,	0,	0,	0},
		{	1,	0,	0,	1,	0,	1,	0,	0},
		{	0,	0,	0,	0,	0,	0,	0,	0},
		{	0,	0,	0,	0,	0,	0,	0,	0},

		//front row
		{	0,	0,	0,	0,	0,	0,	0,	0},
		{	0,	1,	1,	0,	0,	0,	0,	0},
		{	0,	0,	1,	0,	0,	0,	1,	0},
		{	0,	0,	0,	0,	0,	0,	1,	1},
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


	//オブジェクトいるところの位置情報更新
	RailManager::Get()->InitRailPos();
}


void Game::RailInit1_3(void)
{
	bool railData[15][8]{
		//back row
		//up	ru  r	rd d	ld l	lu
		{	0,	0,	0,	0,	0,	0,	0,	0},//0
		{	0,	0,	1,	0,	0,	0,	0,	0},//1
		{	0,	0,	1,	0,	0,	1,	1,	0},//2
		{	0,	0,	1,	0,	0,	1,	1,	0},//3
		{	0,	0,	0,	0,	0,	0,	1,	0},//4

		//mid row
		{	0,	0,	0,	0,	0,	0,	0,	0},
		{	0,	1,	0,	1,	0,	0,	0,	0},
		{	0,	1,	0,	0,	0,	0,	0,	0},
		{	0,	0,	0,	0,	0,	0,	0,	0},
		{	0,	0,	0,	0,	0,	0,	0,	0},

		//front row
		{	0,	0,	0,	0,	0,	0,	0,	0},
		{	0,	0,	0,	0,	0,	0,	0,	0},
		{	0,	0,	1,	0,	0,	0,	0,	1},
		{	0,	0,	0,	0,	0,	0,	1,	0},
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


	//オブジェクトいるところの位置情報更新
	RailManager::Get()->InitRailPos();
}


void Game::InitSoundArray()
{
	DirectX::XMFLOAT3 pos = { 1.0f, 0.7f, 0.5f };

	for (int i = 0; i < 6; i++)
	{
		uiSoundOp_BGM[i]->CreateModel(g_Assets->uiSoundOp_BGM, 313, 324, 1, 1);
		uiSoundOp_SE[i]->CreateModel(g_Assets->uiSoundOp_BGM, 313, 324, 1, 1);

		uiSoundOp_BGM[i]->m_pos = { pos.x + i * 0.8f,0.7f, pos.z };
		uiSoundOp_SE[i]->m_pos = { pos.x + i * 0.8f, -0.7f, pos.z };

		uiSoundOp_BGM[i]->m_scale = { 0.2,0.2,0.2 };
		uiSoundOp_SE[i]->m_scale = { 0.2,0.2,0.2 };

	}


}


void Game::InitSelectArray()
{
	//位置設定
	uiSelectStage[STAGE1]->m_pos = { -3.2f,1.3f,0.8f };
	uiSelectStage[STAGE2]->m_pos = { -2.7f,-0.6f,0.8f };
	uiSelectStage[STAGE3]->m_pos = { -3.1f,-2.5f,0.8f };

	uiSelectChapter[CHAPTER1]->m_pos = { 3.1f,3.3f,0.8f };
	uiSelectChapter[CHAPTER2]->m_pos = { 3.1f,1.0f,0.8f };
	uiSelectChapter[CHAPTER3]->m_pos = { 3.1f,-1.5f,0.8f };

	//ステージを設定
	selectStage = STAGE1;
	selectChapter = CHAPTER1;

}

void Game::InitHintArray()
{
	for (int i = 0; i < 9; i++) {
		stageHint[i] = new CanvasUI();
	}
	
	stageHintBg = new CanvasUI();

	//テクスチャ割り当て
	for (int i = 0; i < 9; i++) {
		/*stageHint[i]->CreateModel(g_Assets->stageHint1_1, 1280, 720, 1, 1);*/
		stageHint[i]->CreateModel(g_Assets->stageHint1_1, 883, 657, 1, 1);
	}
	
	stageHintBg->CreateModel(g_Assets->stageHintBg, 1280, 720, 1, 1);


	stageHint[STAGE1_1]->SetTexture(g_Assets->stageHint1_1);
	stageHint[STAGE1_2]->SetTexture(g_Assets->stageHint1_2);
	stageHint[STAGE1_3]->SetTexture(g_Assets->stageHint1_3);

	//位置設定
	for (int i = 0; i < 9; i++) {
		stageHint[i]->m_pos = { 0,0,0.2};
	}
	stageHintBg->m_pos = { 0,0,0.4 };
	//位置設定
}


void Game::TitleUpdate(void)
{	

	//スペースキーを押すと　ステージセレクト画面に遷移
	if (Input::Get()->GetKeyTrigger(DIK_SPACE)) {

		XA_Play(BGM_SelectStage);//セレクトBGM再生

		//タイトルに戻る時全部のクリア判定を無しにする　
		for (int i = 0; i < 9; i++) {
			//封蝋の印を無しにするanimeSpeed

			SceneManager::Get()->m_stageHolder[i]->SetCompleted(false);
			//念のため、ステージのクリア判定をfalseにする
			SceneManager::Get()->m_stageHolder[i]->SetClear(false);
		}
		SceneManager::Get()->ChangeScene(STAGESELECT);
	}

	//アニメション終了
	if (!uiTitleBg->GetAnimated()&&!uiTitleBg->GetLoop()) {
		
		uiTitleBg->SetLoop(true);
		uiTitleBg->SetAnimeted(true);
		uiTitleBg->m_anime->isPlaying = true;
		uiTitleBg->m_anime->SetAnimePattern(1);
		uiPressSpace->SetActive(true);
	}

	uiPressSpace->Update();
	uiTitleBg->Update();
	
}

void Game::TutorialUpdate(void)
{
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
		/*	
			if (selectStage == STAGE1) 
			{
				selectStage = STAGE3;
			}
			else {
				selectStage = static_cast<SELECTSTAGE>(selectStage - 1);
			}*/
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

			/*if (selectChapter == CHAPTER1)
			{
				selectChapter = CHAPTER3;
			}
			else {
				selectChapter = static_cast<SELECTCHAPTER>(selectChapter - 1);
			}
			*/
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
			SceneManager::Get()->ChangeScene(SCENENAME::TITLE);

		}
	}

	//スペースキー押して進む
	if (Input::Get()->GetKeyTrigger(DIK_SPACE)) {
		
		XA_Play(SE_SelectDecide);//決定SE再生

		if (!isSelectChapter) {

			isSelectChapter = true;
		}
		else {
			
			SelectChapter();
			
			//シーンの切り替えを行う
			SceneManager::Get()->ChangeScene(STAGE);

			XA_Play(SE_Present);//ステージに遷移するとお題のSEを再生
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

		if (selectStage==i) {
			//ACTIVE
			uiSelectStage[i]->m_anime->SetAnimePattern(CanvasUI::ACTIVE);
		}
		else {
			//INACTIVE	
			uiSelectStage[i]->m_anime->SetAnimePattern(CanvasUI::INACTIVE);
	
		}

	}
	
}

void Game::UpdateCursor(void)
{

	if (!isSelectChapter) {

		uiSelectCursor->m_pos.z = -0.8f ;

	}else {
		switch (selectChapter)
		{
		case Game::CHAPTER1:

			uiSelectCursor->m_pos = { 1.3f, 3.6f, 0.7f };
			break;
		case Game::CHAPTER2:

			uiSelectCursor->m_pos = { 1.3f, 1.3f, 0.7f };

			break;
		case Game::CHAPTER3:
			uiSelectCursor->m_pos = { 1.3f,-1.2f,0.7f };
			break;
		}
	}

}

void Game::SelectChapter(void) {

	/*switch (selectChapter)
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
	}*/


	int num = selectStage;

	num = num * 3 + selectChapter;

	if (num > 2) {
		SceneManager::Get()->SetStage(STAGEINFO::STAGE_UNDONE);
	}
	else {
		SceneManager::Get()->SetStage(static_cast<STAGEINFO>(num));

	}

}

void Game::UpdateStage1_1(void)
{
	//背景
	stageBg->Update();

	for (auto& element : objectList) {
		if (!element->GetStill()) {
			isPlayMoveSE = true;
			//ループ中止
			break;
		}
	}

	if (isPlayMoveSE) {

		XA_Play(SE_Move);
		
		//いったんOFFにしてまた再生されるように
		isPlayMoveSE = false;
	}

	//本体の更新
	for (auto& element : objectList) {
		element->Update();
	}

	//影の更新
	for (auto& element : objectList) {

		element->ShadowUpdate(0.0f, 4.5f);

	}

	//クリア判定
 	if (ColliderManager::Get()->ClearCollision({OVERLAP,COL_DOWN }, "coconut", "lamp", ShadowObject::SMALL)&&
		ColliderManager::Get()->ClearCollision({OVERLAP,COL_DOWN},"lamp","housePlate",ShadowObject::LARGE)) {		
		////クリア
		SceneManager::Get()->m_stageHolder[SceneManager::Get()->GetStage()]->SetClear(true);
		SceneManager::Get()->ChangeScene(RESULT);
		isResultAnime = true;
		XA_Play(SE_Result);//リザルトに遷移した後、SE再生
	}

	//エフェクト
	testEffect->SetTrace(true);
	testEffect->Update();

}

void Game::UpdateStage1_2(void)
{
	//背景
	stageBg->Update();

	//MOVE SE
	for (auto& element : objectList) {
		if (!element->GetStill()) {
			isPlayMoveSE = true;
			//ループ中止
			break;
		}
	}

	//OBJECT UPDATE
	for (auto& element : objectList) {
		element->Update();
	}
	
	//SHADOW UPDATE
	lamp1_2->ShadowUpdate(0.35f, 4);
	iphone->ShadowUpdate(-1.4f, 4);
	triangleBlock->ShadowUpdate(0, 4);


	//クリア判定     
	if (ColliderManager::Get()->ClearCollision({COL_LEFT,COL_UP }, "triangleBlock", "iphone", ShadowObject::SMALL)&&
		ColliderManager::Get()->ClearCollision({OVERLAP,OVERLAP}, "triangleBlock","lamp1_2",ShadowObject::MEDIUM)) {
		//isPause = true;
		
		//クリア
		int stageNum = SceneManager::Get()->GetStage();
		SceneManager::Get()->m_stageHolder[stageNum]->SetClear(true);
		SceneManager::Get()->ChangeScene(RESULT);
		isResultAnime = true;
	}

	//エフェクト
	testEffect->SetTrace(true);
	testEffect->Update();
}

void Game::UpdateStage1_3(void)
{

	//背景
	stageBg->Update();

	//MOVE SE
	for (auto& element : objectList) {
		if (!element->GetStill()) {
			isPlayMoveSE = true;
			//ループ中止
			break;
		}
	}

	//OBJECT UPDATE
	for (auto& element : objectList) {
		element->Update();
	}

	//TestMove();

	//SHADOW UPDATE
	newspaper->ShadowUpdate(0.0,3.6f);
	sandwich->ShadowUpdate(1.0f,2.8f);
	picnicbasket->ShadowUpdate(1.5,3.0f);
	bucket->ShadowUpdate(3,3.2);

		
	//クリア判定     
	if (ColliderManager::Get()->ClearCollision({ COL_RIGHT,OVERLAP }, "picnicbasket", "sandwich", ShadowObject::LARGE) &&
		ColliderManager::Get()->ClearCollision({ COL_RIGHT,COL_DOWN }, "bucket", "newspaper", ShadowObject::SMALL)) {
		//isPause = true;
		RailPos pos = { 0,3 };
		if (bucket->GetRailPos() == pos) {
			//クリア
			int stageNum = SceneManager::Get()->GetStage();
			SceneManager::Get()->m_stageHolder[stageNum]->SetClear(true);
			SceneManager::Get()->ChangeScene(RESULT);
			isResultAnime = true;
		}
		
	}




	//エフェクト
	testEffect->SetTrace(true);
	testEffect->Update();
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

void Game::UpdateStageUndone(void)
{
	if (!comingSoon->GetAnimated()) {
		comingSoon->SetActive(false);
		comingSoonLoop->SetActive(true);
	}

	comingSoon->Update();
	comingSoonLoop->Update();

	if (Input::Get()->GetKeyTrigger(DIK_SPACE)) {
		SceneManager::Get()->ChangeScene(TITLE);
	}

}

void Game::ResultUpdate(void)
{

	if (isResultAnime) {
		int stageNum = SceneManager::Get()->GetActiveStage();

		switch (stageNum)
		{
		case STAGE1_1:
			resultAnimator->Update(clear1_1, clear1_2, clear1_3);
			break;
		case STAGE1_2:
			resultAnimator->Update(clear2_1, clear2_2, clear2_3);
			break;
		case STAGE1_3:
			resultAnimator->Update(clear3_1, clear3_2, clear3_3);
			break;
		}
	}
	else {
		resultGenerator->Update();

	}
}

void Game::GameUpdate(void)
{
	if (SceneManager::Get()->GetNextScene() != NONE) {

		if (fade->mState != Fade::FADE_OUT)
		{
			SceneManager::Get()->SetScene(SceneManager::Get()->GetNextScene());
			SceneManager::Get()->SetNextScene(NONE);
			fade->FadeIn();
			if (SceneManager::Get()->GetScene() == STAGE) {
				InitStage();
			}

		}
		
		


		//if (SceneManager::Get()->GetScene() == RESULT) {
		//	if (SceneManager::Get()->GetNextScene() == STAGE) {
		//		InitStage();
		//	}
		//
		//	/*if (SceneManager::Get()->GetScene() == STAGE) {
		//		InitStage();
		//	}*/
		//}
		////FADE OUTの途中
		//if (SceneManager::Get()->GetScene() == RESULT) {
		//	
		//}
		
	}	
	
	//if(i)



	switch (SceneManager::Get()->GetScene()) {
	case SCENENAME::TITLE:
		TitleUpdate();
		break;
	case SCENENAME::TUTORIAL:

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
		StageUpdate();
		break;
	case SCENENAME::RESULT:
		XA_Stop(BGM_Stage1);
		XA_Stop(BGM_Stage2);
		XA_Stop(BGM_Stage3);
		ResultUpdate();
		break;
	}

	fade->Update();
}


Game::~Game()
{
	XA_Release();//サウンド解放

	delete uiTitle;		//タイトル文字
	delete uiTitleBg;		//タイトル背景
	delete comingSoon;
	delete comingSoonLoop;
	delete uiPressSpace;	//タイトルエンターキー
	delete uiPauseBg;	//PAUSEのボタン
	delete uiResume;
	delete uiRestart;

	delete uiSelectBg;
	delete uiSelectCursor;
	
	for (int i = 0; i < 3; i++)
	{
		delete uiSelectStage[i];
		delete uiSelectChapter[i];
		delete uiClearMark[i];
		delete stageHint[i];
	}
	delete stageHintBg;
	delete uiSelect;
	delete uiSound;
	delete uiSoundBg;
	delete uiSoundCursor;

	delete stageMask;
	delete controlPanel;
	delete pauseMask; //pauseの時画面を全体的に暗くなるmask
	delete resultMask;//リザルト画面のマスク
	delete fade;

	//配列の分を解放
	for (int i = 0; i < 6; i++)
	{
		delete uiSoundOp_BGM[i];	//BGM設定
		delete uiSoundOp_SE[i];	//SE設定
	}

	delete stageBg;
	delete coconut;
	delete lamp;
	delete housePlate;

	//1-2
	delete lamp1_2;		//台形
	delete triangleBlock;	//三角形
	delete iphone;			//平行四角形

	//1-3
	delete sandwich;
	delete newspaper;
	delete bucket;
	delete picnicbasket;

	delete testEffect;

	delete circle;			//circle
	delete cameraShaker;
	delete resultGenerator;	
	delete resultAnimator;
	delete uiStepNum;
	delete uiArrow;


	delete clear1_1;
	delete clear1_2;
	delete clear1_3;

	delete clear2_1;
	delete clear2_2;

	delete clear2_3;

	delete clear3_1;

	delete clear3_2;
	delete clear3_3;
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
	if (Input::Get()->GetKeyTrigger(DIK_DOWNARROW))
	{

		if (!isSound)
		{
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
		else {

			XA_Play(SE_Select);//セレクトSE再生

			if (soundOp == BGM) {
				soundOp = SE;
			}
			else {
				soundOp = BGM;
			}


		}
	}
	//移動
	if (Input::Get()->GetKeyTrigger(DIK_UPARROW)) {

		if (!isSound)
		{
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
		else {

			XA_Play(SE_Select);//セレクトSE再生

			if (soundOp == BGM) {
				soundOp = SE;
			}
			else {
				soundOp = BGM;
			}

		}
	}
	//確認
	if (Input::Get()->GetKeyTrigger(DIK_SPACE)) {

		if (!isSound)
		{
			XA_Play(SE_SelectDecide);//決定SE再生

			switch (pauseSelect)
			{
			case Game::RESUME:
				PauseSwitch();
				break;
			case Game::RESTART:
				//ステージ内のオブジェクトを再配置
				InitStage();
				PauseSwitch();
				//初期化
				pauseSelect = RESUME;
				break;
			case Game::SELECT_STAGE:
				//全部初期化
				selectStage = STAGE1;
				selectChapter = CHAPTER1;
				pauseSelect = RESUME;
				PauseSwitch();
				XA_Play(BGM_SelectStage);// セレクト画面に戻った時にBGM再生
				SceneManager::Get()->ChangeScene(SCENENAME::STAGESELECT);
				break;
			case Game::SOUND:
				SoundSwitch();// サウンド画面切り替え
				break;
			default:
				break;
			}
		}
	}

	//	ESCAPE押して　戻る
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

	//今どのボタンが選択されたの状態変更(改良必要)
	switch (pauseSelect)
	{
	case Game::RESUME:
		uiResume->SetAnimeActive(CanvasUI::ACTIVE);
		uiRestart->SetAnimeActive(CanvasUI::INACTIVE);
		uiSelect->SetAnimeActive(CanvasUI::INACTIVE);
		uiSound->SetAnimeActive(CanvasUI::INACTIVE);
		uiResume->m_pos.x =  -5.5f;
		uiRestart->m_pos.x = -6.0f;
		uiSelect->m_pos.x = -6.0f;
		uiSound->m_pos.x = -6.0f;
		break;
	case Game::RESTART:
		uiRestart->SetAnimeActive(CanvasUI::ACTIVE);
		uiResume->SetAnimeActive(CanvasUI::INACTIVE);
		uiSelect->SetAnimeActive(CanvasUI::INACTIVE);
		uiSound->SetAnimeActive(CanvasUI::INACTIVE);
		uiResume->m_pos.x = -6.0f;
		uiRestart->m_pos.x = -5.5f;
		uiSelect->m_pos.x = -6.0f;
		uiSound->m_pos.x = -6.0f;
		break;
	case Game::SELECT_STAGE:
		uiRestart->SetAnimeActive(CanvasUI::INACTIVE);
		uiResume->SetAnimeActive(CanvasUI::INACTIVE);
		uiSelect->SetAnimeActive(CanvasUI::ACTIVE);
		uiSound->SetAnimeActive(CanvasUI::INACTIVE);
		uiResume->m_pos.x = -6.0f;
		uiRestart->m_pos.x = -6.0f;
		uiSelect->m_pos.x = -5.5f;
		uiSound->m_pos.x = -6.0f;
		break;
	case Game::SOUND:
		uiRestart->SetAnimeActive(CanvasUI::INACTIVE);
		uiResume->SetAnimeActive(CanvasUI::INACTIVE);
		uiSelect->SetAnimeActive(CanvasUI::INACTIVE);
		uiSound->SetAnimeActive(CanvasUI::ACTIVE);
		uiResume->m_pos.x =  -6.0f;
		uiRestart->m_pos.x = -6.0f;
		uiSelect->m_pos.x = -6.0f;
		uiSound->m_pos.x = -5.5f;
		break;

			
	}

		//Sound画面
	if (!isSound){
		uiPauseBg->Update();
		uiRestart->Update();
		uiResume->Update();
		uiSelect->Update();
		uiSound->Update();
			
			
	}else{
		SoundVolume();		
		SoundCursorUpdate();
		uiSoundBg->Update();
	}

}

void Game::PauseSwitch(void)
{
	if (isPause)
	{
		isPause = false;
		//画面エフェクトの切り替え
		pauseMask->SetActive(false);
		stageMask->SetActive(true);
		controlPanel->SetActive(true);
		uiArrow->SetActive(false);

	}
	else
	{
		isPause = true;
		//画面エフェクトの切り替え
		pauseMask->SetActive(true);
		stageMask->SetActive(false);
		controlPanel->SetActive(false);
		uiArrow->SetActive(false);
	}

}


void Game::SoundCursorUpdate(void)
{
	if (!isSound)
	{
		uiSoundCursor->m_pos.z = -0.8f;

	}
	else {
		switch (soundOp)
		{
		case BGM:
			uiSoundCursor->m_pos = { -2.0f, 0.65f, 0.5f };
			break;

		case SE:
			uiSoundCursor->m_pos = { -2.0f, -0.7f, 0.5f };
			break;
		}
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
		
	if (Input::Get()->GetKeyTrigger(DIK_LEFT))
	{
		XA_Play(SE_Select);//セレクトSE再生
		/*
		switch (soundVolume_BGM)
		{

		case VOLUME0:
			soundVolume_BGM = VOLUME0;
			XA_SetVolume(BGM_SelectStage, 0.0f);
			XA_SetVolume(BGM_Stage1, 0.0f);
			XA_SetVolume(BGM_Stage2, 0.0f);
			XA_SetVolume(BGM_Stage3, 0.0f);

			//VOLUME0の状態のときSound再生しないようにする
			if (soundVolume_SE == VOLUME0)
			{
				XA_SetVolume(SE_Select, 0.0f);
				XA_SetVolume(SE_SelectDecide, 0.0f);
			}

			break;

		case VOLUME1:
			soundVolume_BGM = VOLUME0;
			XA_SetVolume(BGM_SelectStage, 0.0f);
			XA_SetVolume(BGM_Stage1, 0.0f);
			XA_SetVolume(BGM_Stage2, 0.0f);
			XA_SetVolume(BGM_Stage3, 0.0f);

		
			if (soundVolume_SE == VOLUME0)
			{
				XA_SetVolume(SE_Select, 0.0f);
				XA_SetVolume(SE_SelectDecide, 0.0f);
			}

			break;

		case VOLUME2:
			soundVolume_BGM = VOLUME1;
			XA_SetVolume(BGM_SelectStage, 0.2f);
			XA_SetVolume(BGM_Stage1, 0.2f);
			XA_SetVolume(BGM_Stage2, 0.2f);
			XA_SetVolume(BGM_Stage3, 0.2f);

			
			if (soundVolume_SE == VOLUME0)
			{
				XA_SetVolume(SE_Select, 0.0f);
				XA_SetVolume(SE_SelectDecide, 0.0f);
			}

			break;

		case VOLUME3:
			soundVolume_BGM = VOLUME2;
			XA_SetVolume(BGM_SelectStage, 0.4f);
			XA_SetVolume(BGM_Stage1, 0.4f);
			XA_SetVolume(BGM_Stage2, 0.4f);
			XA_SetVolume(BGM_Stage3, 0.4f);

			
			if (soundVolume_SE == VOLUME0)
			{
				XA_SetVolume(SE_Select, 0.0f);
				XA_SetVolume(SE_SelectDecide, 0.0f);
			}

			break;

		case VOLUME4:
			soundVolume_BGM = VOLUME3;
			XA_SetVolume(BGM_SelectStage, 0.6f);
			XA_SetVolume(BGM_Stage1, 0.6f);
			XA_SetVolume(BGM_Stage2, 0.6f);
			XA_SetVolume(BGM_Stage3, 0.6f);

			
			if (soundVolume_SE == VOLUME0)
			{
				XA_SetVolume(SE_Select, 0.0f);
				XA_SetVolume(SE_SelectDecide, 0.0f);
			}

			break;

		case VOLUME5:
			soundVolume_BGM = VOLUME4;
			XA_SetVolume(BGM_SelectStage, 0.8f);
			XA_SetVolume(BGM_Stage1, 0.8f);
			XA_SetVolume(BGM_Stage2, 0.8f);
			XA_SetVolume(BGM_Stage3, 0.8f);

			
			if (soundVolume_SE == VOLUME0)
			{
				XA_SetVolume(SE_Select, 0.0f);
				XA_SetVolume(SE_SelectDecide, 0.0f);
			}

			break;
		}
				*/
		if (bgmVolume <= 0) {
			bgmVolume = 0;
		}
		else {
			bgmVolume--;
			
		}
	
	}


	if (Input::Get()->GetKeyTrigger(DIK_RIGHT))
	{
		XA_Play(SE_Select);//セレクトSE再生

		/*
		switch (soundVolume_BGM)
		{

		case VOLUME0:
			soundVolume_BGM = VOLUME1;
			XA_SetVolume(BGM_SelectStage, 0.2f);
			XA_SetVolume(BGM_Stage1, 0.2f);
			XA_SetVolume(BGM_Stage2, 0.2f);
			XA_SetVolume(BGM_Stage3, 0.2f);

			//VOLUME0の状態のときSound再生しないようにする
			if (soundVolume_SE == VOLUME0)
			{
				XA_SetVolume(SE_Select, 0.0f);
				XA_SetVolume(SE_SelectDecide, 0.0f);
			}

			break;

		case VOLUME1:
			soundVolume_BGM = VOLUME2;
			XA_SetVolume(BGM_SelectStage, 0.4f);
			XA_SetVolume(BGM_Stage1, 0.4f);
			XA_SetVolume(BGM_Stage2, 0.4f);
			XA_SetVolume(BGM_Stage3, 0.4f);


			if (soundVolume_SE == VOLUME0)
			{
				XA_SetVolume(SE_Select, 0.0f);
				XA_SetVolume(SE_SelectDecide, 0.0f);
			}

			break;

		case VOLUME2:
			soundVolume_BGM = VOLUME3;
			XA_SetVolume(BGM_SelectStage, 0.6f);
			XA_SetVolume(BGM_Stage1, 0.6f);
			XA_SetVolume(BGM_Stage2, 0.6f);
			XA_SetVolume(BGM_Stage3, 0.6f);
			

			if (soundVolume_SE == VOLUME0)
			{
				XA_SetVolume(SE_Select, 0.0f);
				XA_SetVolume(SE_SelectDecide, 0.0f);
			}

			break;

		case VOLUME3:
			soundVolume_BGM = VOLUME4;
			XA_SetVolume(BGM_SelectStage, 0.8f);
			XA_SetVolume(BGM_Stage1, 0.8f);
			XA_SetVolume(BGM_Stage2, 0.8f);
			XA_SetVolume(BGM_Stage3, 0.8f);
			

			if (soundVolume_SE == VOLUME0)
			{
				XA_SetVolume(SE_Select, 0.0f);
				XA_SetVolume(SE_SelectDecide, 0.0f);
			}

			break;

		case VOLUME4:
			soundVolume_BGM = VOLUME5;
			XA_SetVolume(BGM_SelectStage, 1.0f);
			XA_SetVolume(BGM_Stage1, 1.0f);
			XA_SetVolume(BGM_Stage2, 1.0f);
			XA_SetVolume(BGM_Stage3, 1.0f);
			

			if (soundVolume_SE == VOLUME0)
			{
				XA_SetVolume(SE_Select, 0.0f);
				XA_SetVolume(SE_SelectDecide, 0.0f);
			}

			break;

		case VOLUME5:
			soundVolume_BGM = VOLUME5;
			XA_SetVolume(BGM_SelectStage, 1.0f);
			XA_SetVolume(BGM_Stage1, 1.0f);
			XA_SetVolume(BGM_Stage2, 1.0f);
			XA_SetVolume(BGM_Stage3, 1.0f);
			

			if (soundVolume_SE == VOLUME0)
			{
				XA_SetVolume(SE_Select, 0.0f);
				XA_SetVolume(SE_SelectDecide, 0.0f);
			}

			break;
		}
		*/

		if (bgmVolume >= 5) {
			bgmVolume = 5;
		}
		else {
			bgmVolume++;
		}

	}	

	XA_SetVolume(BGM_SelectStage, bgmVolume * 0.2f);
	XA_SetVolume(BGM_Stage1, bgmVolume * 0.2f);
	XA_SetVolume(BGM_Stage2, bgmVolume * 0.2f);
	XA_SetVolume(BGM_Stage3, bgmVolume * 0.2f);
}

void Game::SoundOp_SE(void)
{

	if (Input::Get()->GetKeyTrigger(DIK_LEFT))
	{
		XA_Play(SE_Select);//セレクトSE再生
		/*
		switch (soundVolume_SE)
		{
		case VOLUME0:
			soundVolume_SE = VOLUME0;
			XA_SetVolume(SE_Select, 0.0f);
			XA_SetVolume(SE_SelectDecide, 0.0f);
			
			//VOLUME0の状態のときSound再生しないようにする
			if (soundVolume_BGM == VOLUME0)
			{
				XA_SetVolume(BGM_SelectStage, 0.0f);
				XA_SetVolume(BGM_Stage1, 0.0f);
				XA_SetVolume(BGM_Stage2, 0.0f);
				XA_SetVolume(BGM_Stage3, 0.0f);
			}

			break;

		case VOLUME1:
			soundVolume_SE = VOLUME0;
			XA_SetVolume(SE_Select, 0.0f);
			XA_SetVolume(SE_SelectDecide, 0.0f);
			

			if (soundVolume_BGM == VOLUME0)
			{
				XA_SetVolume(BGM_SelectStage, 0.0f);
				XA_SetVolume(BGM_Stage1, 0.0f);
				XA_SetVolume(BGM_Stage2, 0.0f);
				XA_SetVolume(BGM_Stage3, 0.0f);
			}

			break;

		case VOLUME2:
			soundVolume_SE = VOLUME1;
			XA_SetVolume(SE_Select, 0.2f);
			XA_SetVolume(SE_SelectDecide, 0.2f);
			

			if (soundVolume_BGM == VOLUME0)
			{
				XA_SetVolume(BGM_SelectStage, 0.0f);
				XA_SetVolume(BGM_Stage1, 0.0f);
				XA_SetVolume(BGM_Stage2, 0.0f);
				XA_SetVolume(BGM_Stage3, 0.0f);
			}

			break;

		case VOLUME3:
			soundVolume_SE = VOLUME2;
			XA_SetVolume(SE_Select, 0.4f);
			XA_SetVolume(SE_SelectDecide, 0.4f);
			

			if (soundVolume_BGM == VOLUME0)
			{
				XA_SetVolume(BGM_SelectStage, 0.0f);
				XA_SetVolume(BGM_Stage1, 0.0f);
				XA_SetVolume(BGM_Stage2, 0.0f);
				XA_SetVolume(BGM_Stage3, 0.0f);
			}
			break;

		case VOLUME4:
			soundVolume_SE = VOLUME3;
			XA_SetVolume(SE_Select, 0.6f);
			XA_SetVolume(SE_SelectDecide, 0.6f);
			

			if (soundVolume_BGM == VOLUME0)
			{
				XA_SetVolume(BGM_SelectStage, 0.0f);
				XA_SetVolume(BGM_Stage1, 0.0f);
				XA_SetVolume(BGM_Stage2, 0.0f);
				XA_SetVolume(BGM_Stage3, 0.0f);
			}
			break;

		case VOLUME5:
			soundVolume_SE = VOLUME4;
			XA_SetVolume(SE_Select, 0.8f);
			XA_SetVolume(SE_SelectDecide, 0.8f);
			

			if (soundVolume_BGM == VOLUME0)
			{
				XA_SetVolume(BGM_SelectStage, 0.0f);
				XA_SetVolume(BGM_Stage1, 0.0f);
				XA_SetVolume(BGM_Stage2, 0.0f);
				XA_SetVolume(BGM_Stage3, 0.0f);
			}

			break;
		}
		*/
		if (seVolume <= 0) {
			seVolume = 0;
		}
		else {
			seVolume--;
		}

	}

	if (Input::Get()->GetKeyTrigger(DIK_RIGHT))
	{
		XA_Play(SE_Select);//セレクトSE再生
		/*
		switch (soundVolume_SE)
		{

		case VOLUME0:
			soundVolume_SE = VOLUME1;
			XA_SetVolume(SE_Select, 0.2f);
			XA_SetVolume(SE_SelectDecide, 0.2f);
			
			//VOLUME0の状態のときSound再生しないようにする
			if (soundVolume_BGM == VOLUME0)
			{
				XA_SetVolume(BGM_SelectStage, 0.0f);
				XA_SetVolume(BGM_Stage1, 0.0f);
				XA_SetVolume(BGM_Stage2, 0.0f);
				XA_SetVolume(BGM_Stage3, 0.0f);
			}

			break;

		case VOLUME1:
			soundVolume_SE = VOLUME2;
			XA_SetVolume(SE_Select, 0.4f);
			XA_SetVolume(SE_SelectDecide, 0.4f);
			

			if (soundVolume_BGM == VOLUME0)
			{
				XA_SetVolume(BGM_SelectStage, 0.0f);
				XA_SetVolume(BGM_Stage1, 0.0f);
				XA_SetVolume(BGM_Stage2, 0.0f);
				XA_SetVolume(BGM_Stage3, 0.0f);
			}

			break;

		case VOLUME2:
			soundVolume_SE = VOLUME3;
			XA_SetVolume(SE_Select, 0.6f);
			XA_SetVolume(SE_SelectDecide, 0.6f);
			

			if (soundVolume_BGM == VOLUME0)
			{
				XA_SetVolume(BGM_SelectStage, 0.0f);
				XA_SetVolume(BGM_Stage1, 0.0f);
				XA_SetVolume(BGM_Stage2, 0.0f);
				XA_SetVolume(BGM_Stage3, 0.0f);
			}

			break;

		case VOLUME3:
			soundVolume_SE = VOLUME4;
			XA_SetVolume(SE_Select, 0.8f);
			XA_SetVolume(SE_SelectDecide, 0.8f);
			

			if (soundVolume_BGM == VOLUME0)
			{
				XA_SetVolume(BGM_SelectStage, 0.0f);
				XA_SetVolume(BGM_Stage1, 0.0f);
				XA_SetVolume(BGM_Stage2, 0.0f);
				XA_SetVolume(BGM_Stage3, 0.0f);
			}

			break;

		case VOLUME4:
			soundVolume_SE = VOLUME5;
			XA_SetVolume(SE_Select, 1.0f);
			XA_SetVolume(SE_SelectDecide, 1.0f);
			

			if (soundVolume_BGM == VOLUME0)
			{
				XA_SetVolume(BGM_SelectStage, 0.0f);
				XA_SetVolume(BGM_Stage1, 0.0f);
				XA_SetVolume(BGM_Stage2, 0.0f);
				XA_SetVolume(BGM_Stage3, 0.0f);
			}

			break;

		case VOLUME5:
			soundVolume_SE = VOLUME5;
			XA_SetVolume(SE_Select, 1.0f);
			XA_SetVolume(SE_SelectDecide, 1.0f);
			

			if (soundVolume_BGM == VOLUME0)
			{
				XA_SetVolume(BGM_SelectStage, 0.0f);
				XA_SetVolume(BGM_Stage1, 0.0f);
				XA_SetVolume(BGM_Stage2, 0.0f);
				XA_SetVolume(BGM_Stage3, 0.0f);
			}

			break;
		}
		*/
		if (seVolume >= 0) {
			seVolume = 0;
		}
		else {
			seVolume++;
		}
	}
	
	XA_SetVolume(SE_Select, seVolume * 0.2f);
	XA_SetVolume(SE_SelectDecide, seVolume * 0.2f);
	XA_SetVolume(SE_Move, seVolume * 0.2f);
	XA_SetVolume(SE_Present, seVolume * 0.2f);
	XA_SetVolume(SE_Combine, seVolume * 0.2f);
	XA_SetVolume(SE_Result, seVolume * 0.2f);
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

	fade->Draw();

	//============ ここまで描画処理 ============//
	 
	//ダブルバッファの切り替えを行い画面を更新する
	GetD3D_DATA()->SwapChain->Present(0, 0);
}

void Game::TitleDraw(void)
{
	uiTitleBg->Draw();

	uiPressSpace->Draw();	

}

void Game::SelectDraw(void)
{
	uiSelectBg->Draw();
	uiSelectDraw();
	uiSelectCursor->Draw();

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
	if (SceneManager::Get()->GetStage() != STAGE_UNDONE)
	{

		stageBg->Draw();

		//描画の順番を並び変え
		SortShadowDraw();

		//オブジェクト
		SortObjectDraw();

		if (isPause) {
			UiDraw();
		}

		//今のステージのヒントを描画する
		SetBlendState(GetBlendMultiply());
		//ヒントの背景
		stageHintBg->Draw();
		stageMask->Draw();
		SetBlendState(GetBlendAlpha());

		//pauseじゃない時操作方法出る
		controlPanel->Draw();
		

		//ステップ数表示
		if (!isPause) {
			if (!SceneManager::Get()->m_stageHolder[SceneManager::Get()->GetActiveStage()]->GetHint()) {
				//修正待ち //fadeを邪魔しないよう
				uiStepNum->PrintDebugLogCenter(SceneManager::Get()->m_stageHolder[SceneManager::Get()->GetActiveStage()]->GetStep());
				uiArrow->Draw();
			}
		}

		//hint描画
		stageHint[SceneManager::Get()->GetActiveStage()]->Draw();


	}
	else {
	
		StageUndoneDraw();
	}



}

void Game::StageUndoneDraw(void)
{
	comingSoonLoop->Draw();
	comingSoon->Draw();

}


void Game::ResultDraw(void)
{
	stageBg->Draw();
	//maskをつける
	SetBlendState(GetBlendMultiply());
	resultMask->Draw();
	SetBlendState(GetBlendAlpha());

	if (isResultAnime) {
		//リザルトアニメーション待機させる
		int stageNum = SceneManager::Get()->GetStage();

		switch (stageNum)
		{
		case STAGE1_1:// ステージ１
			resultAnimator->Draw(clear1_1, clear1_2, clear1_3);
			break;
		case STAGE1_2:// ステージ２
			resultAnimator->Draw(clear2_1, clear2_2, clear2_3);
			break;
		case STAGE1_3:// ステージ３
			resultAnimator->Draw(clear3_1, clear3_2, clear3_3);
			break;
		}
	}
	else {
		resultGenerator->Draw();
	}


}

void Game::UiDraw(void)
{

	//一番後にマスクが描画される
	SetBlendState(GetBlendMultiply());
	pauseMask->Draw();
	SetBlendState(GetBlendAlpha());
	if (!isSound)
	{
		uiPauseBg->Draw();
		uiResume->Draw();
		uiRestart->Draw();
		uiSelect->Draw();
		uiSound->Draw();
		//uiPauseCursor->Draw();

	}
	else//サウンド画面に入る
	{
		uiPauseBg->Draw();
		uiResume->Draw();
		uiRestart->Draw();
		uiSelect->Draw();
		uiSound->Draw();
		uiSoundBg->Draw();
		//uiPauseCursor->Draw();
		uiSoundCursor->Draw();

		//音量調節の描画
		SoundVolumeDraw();

	}
}

void Game::SoundVolumeDraw(void)
{
	if (isSound) {
		for (int i = 0; i < bgmVolume; i++) {
			uiSoundOp_BGM[i]->Draw();
		}
		
		for (int i = 0; i < seVolume; i++) {
			uiSoundOp_SE[i]->Draw();
		}
	}
}

void Game::SortObjectDraw(void)
{
	//並び替え
	std::sort(objectList.begin(), objectList.end(), [](GameObject* obj1, GameObject* obj2) {
		if (obj1->m_obj->m_sprite->m_pos.z == obj2->m_obj->m_sprite->m_pos.z) {
			return obj1->GetRailPos().horizontalPos <  obj2->GetRailPos().horizontalPos;
		}
		return obj1->m_obj->m_sprite->m_pos.z < obj2->m_obj->m_sprite->m_pos.z;
		});

	
	for (auto it = objectList.begin(); it != objectList.end(); it++) {
		
		bool isOverlap = false;
		
		if (it != objectList.end() - 1) {
			auto nextIt = it + 1;
			while (nextIt != objectList.end()) {
				if ((*it)->GetRailPos().horizontalPos == (*nextIt)->GetRailPos().horizontalPos) {
					isOverlap = true;
				}
				nextIt += 1;
			}
		}

		if (isOverlap) {

			switch ((*it)->GetRailPos().verticalPos) {
			case 0:
				(*it)->m_obj->m_sprite->m_materialDiffuse = { 1.0, 1.0, 1.0, 0.8 };
				break;
			case 1:
				(*it)->m_obj->m_sprite->m_materialDiffuse = { 1.0, 1.0, 1.0, 0.6 };
				break;
			case 2:
				(*it)->m_obj->m_sprite->m_materialDiffuse = { 1.0, 1.0, 1.0, 0.3 };
				break;
			}	
		}
		else {
			(*it)->m_obj->m_sprite->m_materialDiffuse = { 1.0, 1.0, 1.0, 1.0 };
		}
	}
	

	//並び替え
	std::sort(objectList.begin(), objectList.end(), [](GameObject* obj1, GameObject* obj2) {
		if (obj1->m_obj->m_sprite->m_pos.z == obj2->m_obj->m_sprite->m_pos.z) {
			return obj1->GetRailPos().horizontalPos < obj2->GetRailPos().horizontalPos;
		}
		//return obj1->GetRailPos().verticalPos <  obj2->GetRailPos().verticalPos;
		return obj1->m_obj->m_sprite->m_pos.z > obj2->m_obj->m_sprite->m_pos.z;
		});


	//描画
	for (auto& element : objectList) {

		if (element->GetActive()) {

			testEffect->Draw();
		}

		element->Draw();
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

/*
void Game::DebugDisplay(void)
{
	char step[6] = "STEP:";
	float posX = (-SCREEN_WIDTH / 2 + 40.0f) / SCREEN_PARA;
	float posY = ((SCREEN_HEIGHT / 2) - 40.0f) / SCREEN_PARA;
	g_DebugManager->PrintDebugLog(posX, posY, step);

	posX = (-SCREEN_WIDTH / 2 + 40.0f + 120.0f) / SCREEN_PARA;

	g_DebugManager->PrintDebugLog(posX, posY, SceneManager::Get()->m_stageHolder[SceneManager::Get()->GetActiveStage()]->GetStep());
	//posX = (-SCREEN_WIDTH / 2 + 40.0f) / SCREEN_PARA;
	//posY = ((SCREEN_HEIGHT / 2) - 80.0f) / SCREEN_PARA;
	//g_DebugManager->PrintDebugLog(posX, posY, lamp->m_shadowCollider->m_center.y);

	//posX = (-SCREEN_WIDTH / 2 + 40.0f) / SCREEN_PARA;
	//posY = ((SCREEN_HEIGHT / 2) - 120.0f) / SCREEN_PARA;
	//g_DebugManager->PrintDebugLog(posX, posY, lamp->m_shadowCollider->m_center.z);

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
			posX = 0.0f;
			posY = ((SCREEN_HEIGHT / 2) - 40.0f) / SCREEN_PARA;
			char name[32] = {};
			strcpy_s(name, element->GetName().c_str());
			g_DebugManager->PrintDebugLog(posX, posY, name);
			break;

		}

	}
}
*/



void Game::StageUpdate(void)
{
	if (SceneManager::Get()->GetStage() != STAGE_UNDONE) {
		//もしヒント出されていない
		if (SceneManager::Get()->m_stageHolder[SceneManager::Get()->GetActiveStage()]->GetHint()) {

			//スペースキーを押したら
			if (Input::Get()->GetKeyTrigger(DIK_SPACE)) {

				stageHint[SceneManager::Get()->GetActiveStage()]->SetActive(false);
				SceneManager::Get()->m_stageHolder[SceneManager::Get()->GetActiveStage()]->SetHint(false);
				stageHintBg->SetActive(false);
				controlPanel->SetActive(true);
			}
			else {
				stageHint[SceneManager::Get()->GetActiveStage()]->SetActive(true);
				stageHintBg->SetActive(true);

			}

			controlPanel->SetActive(false);
			uiArrow->SetActive(false);
		}
		else {

			if (!isPause) {
				controlPanel->SetActive(true);
				uiArrow->SetActive(true);

				//入力処理
				if (Input::Get()->GetKeyTrigger(DIK_ESCAPE))
				{

					XA_Play(SE_SelectDecide);//決定SE再生

					if (!isSound)
					{
						PauseSwitch();
					}
					else//サウンドに入っている時
					{
						SoundSwitch();
					}
				}
				//移動させる目標を設定する
				if (Input::Get()->GetKeyTrigger(DIK_SPACE)) {

					//オブジェクトが移動してない場合
					if (isControl) {

						for (auto it = objectList.begin(); it != objectList.end(); it++) {
							if ((*it)->GetActive())
							{
								(*it)->SetActive(false);
								auto nextIt = std::next(it);

								//もし次のオブジェクトが自動移動のオブジェクトの場合
								if (nextIt != objectList.end()) {
									if ((*nextIt)->GetAutoMove()) {
										XA_Play(SE_Select);//セレクトSE再生
										nextIt = objectList.begin();
										(*nextIt)->SetActive(true);

									}
									else {
										//次のオブジェクトを移動できる
										XA_Play(SE_Select);//セレクトSE再生
										(*nextIt)->SetActive(true);
									}

								}
								else {
									XA_Play(SE_Select);//セレクトSE再生
									nextIt = objectList.begin();
									//次のオブジェクトを移動できる
									(*nextIt)->SetActive(true);

								}

								break;

							}
						}
					}

				}

				if (Input::Get()->GetKeyTrigger(DIK_H)) {

					SceneManager::Get()->m_stageHolder[SceneManager::Get()->GetActiveStage()]->SetHint(true);
					SceneManager::Get()->m_stageHolder[SceneManager::Get()->GetActiveStage()]->HintPunish(10);

				}

				//StageUpdate
				switch (SceneManager::Get()->GetStage()) {

				case STAGE1_1:

					XA_SetVolume(BGM_Stage1, bgmVolume*0.2);

					UpdateStage1_1();

					break;

				case STAGE1_2:

					XA_SetVolume(BGM_Stage2, bgmVolume * 0.2);

					UpdateStage1_2();

					break;

				case STAGE1_3:

					XA_SetVolume(BGM_Stage3, bgmVolume * 0.2);

					UpdateStage1_3();

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
				case STAGE_UNDONE:
					UpdateStageUndone();

				}

				//CameraUpdate
				cameraShaker->Update(g_WorldCamera);
				uiArrow->Update();
			}
			else {
				//マスクを閉める
				UiUpdate();
			}
		}
	}
	else {
		UpdateStageUndone();
	}
	

}


void Game::TestMove(Effect* _target)
{
	if (Input::Get()->GetKeyPress(DIK_E)) {
		_target->m_pos.z += MOVE;
	}
	if (Input::Get()->GetKeyPress(DIK_0)) {
		_target->m_pos.z -= MOVE;
	}
}

void Game::TestMove(CanvasUI* _target)
{
	if (Input::Get()->GetKeyPress(DIK_A)) {
		_target->m_pos.x -= MOVE;
	}
	if (Input::Get()->GetKeyPress(DIK_D)) {
		_target->m_pos.x += MOVE;
	}
	if (Input::Get()->GetKeyPress(DIK_W)) {
		_target->m_pos.y += MOVE;
	}
	if (Input::Get()->GetKeyPress(DIK_S)) {
		_target->m_pos.y -= MOVE;
	}
}

void Game::TestMove(void)
{
	if (Input::Get()->GetKeyPress(DIK_W)) {

		for (auto& element : objectList) {
			if (element->GetActive()) {
				element->m_shadow->m_sprite->m_pos.y += 0.1f;
				break;
			}
		}

	}

	if (Input::Get()->GetKeyPress(DIK_S)) {

		for (auto& element : objectList) {
			if (element->GetActive()) {
				element->m_shadow->m_sprite->m_pos.y -= 0.1f;
				break;
			}
		}
	}
	if (Input::Get()->GetKeyPress(DIK_A)) {

		for (auto& element : objectList) {
			if (element->GetActive()) {
				element->m_shadow->m_sprite->m_pos.x -= 0.1f;
				break;
			}
		}

	}

	if (Input::Get()->GetKeyPress(DIK_D)) {

		for (auto& element : objectList) {
			if (element->GetActive()) {
				element->m_shadow->m_sprite->m_pos.x += 0.1f;
				break;
			}
		}
	}

	

	
}


void Game::SetBackGround(ID3D11ShaderResourceView* tex) {

	//背景設定->関数化処理
	stageBg->m_sprite->m_rotation.x = 19.8;//カメラと垂直状態を保持するため
	stageBg->m_sprite->m_scale = { 2.65,2.65,1.0 };//固定値
	//y
	float y = 21.626 - 7 / ROTATEX;
	y += 1;
	y = y * ROTATEX;
	//y座標の導入
	stageBg->m_sprite->m_pos = { 0.0f,-y,1.0f };
	stageBg->m_sprite->SetTexture(tex);
	stageBg->m_sprite->m_anime->SetAnimeSpeed(0.05f);
	static_cast<StaticAnimation*>(stageBg->m_sprite->m_anime)->SetLoop(true);

}


void Game::SwitchControlObject()
{
	for (auto it = objectList.begin(); it != objectList.end(); ++it) {
		auto nextIt = std::next(it); 

		if (nextIt == objectList.end()) {
			nextIt = objectList.begin(); 
		}

		(*it)->SetActive(false);
		(*nextIt)->SetActive(true);
	}
}

