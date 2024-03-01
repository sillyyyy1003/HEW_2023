#include "Game.h"
#include "Assets.h"
#include "GameObject.h"
#include "ShadowObject.h"
#include "StaticObject.h"
#include "DebugManager.h"
#include "SceneManager.h"
//#include "Animation.h"
#include "ColliderManager.h"
#include "StaticAnimation.h"
#include "ObjectAnimation.h"
#include "RailManager.h"
#include "DInput.h"
#include "Effect.h"
#include "xa2.h"
#include "CameraShaker.h"
#include <algorithm> // 必要なヘッダーファイル
#include "Result.h"
#include "ResultAnimation.h"
#include "ResultProcess.h"
#include "Fade.h"
#include "UiManager.h"
#include <stdio.h> 

#define MOVE 0.1f
#define INITROTATE	(19.8)

extern Assets* g_Assets;
extern Camera* g_WorldCamera;
extern DebugManager* g_DebugManager;

void Game::Init()
{
	//=============================
	//ゲームオブジェクト作成
	//=============================
	comingSoon = new CanvasUI();
	comingSoonLoop = new CanvasUI();

	//mask&panel
	controlPanel = new CanvasUI();
	stageMask = new CanvasUI();
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

	//EFFECT
	testEffect = new Effect(12);

	//tutorial1 = new CanvasUI();
	////uiTutorial[TUTORIAL1] = new CanvasUI();
	//tutorial2 = new CanvasUI();
	//tutorial2loop = new CanvasUI();
	//tutorial3 = new CanvasUI();
	//tutorial3loop = new CanvasUI();
	//tutorial4 = new CanvasUI();
	//tutorial4loop = new CanvasUI();
	//tutorial5 = new CanvasUI();
	//tutorial5loop = new CanvasUI();


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
	comingSoon->CreateModel(g_Assets->comingSoon, 1280, 720, 6, 6);
	comingSoonLoop->CreateModel(g_Assets->comingSoonLoop, 1280, 720, 6, 2);

	stageMask->CreateModel(g_Assets->stageMask, 1280, 720, 1, 1);
	resultMask->CreateModel(g_Assets->resultMask, 1280, 720, 1, 1);
	controlPanel->CreateModel(g_Assets->controlPanel, 1280, 720, 1, 1);


	//手数表示
	//表示の大きさを変える
	uiStepNum->SetSize(0.5);
	uiStepNum->Init(-7.7f, 3.3f,0.5f,1.0f);//調整いる

	//stage1
	stageBg->CreateObject(g_Assets->stageBg1_1, 1280.0f, 720.0f, 6, 1);
	//stage1-1
	coconut->CreateObject(g_Assets->coconut, 190.0f, 192.0f, 1, 1);
	coconut->CreateShadow(g_Assets->coconutShadow, 158.0f, 159.0f, 1, 1, COLLISION_TYPE::SPHERE);
	lamp->CreateObject(g_Assets->lamp, 216.0f, 579.0f, 1, 1);
	lamp->CreateShadow(g_Assets->lampShadow, 216.0f, 579.0f, 1, 1, COLLISION_TYPE::SQUARE);
	housePlate->CreateObject(g_Assets->housePlate, 110.0f, 216.0f, 1, 1);
	housePlate->CreateShadow(g_Assets->housePlateShadow, 50.0f, 105.0f, 1, 1, COLLISION_TYPE::SQUARE);

	//stage1-2
	lamp1_2->CreateObject(g_Assets->lamp_1_2, 264.0f, 267.0f, 1, 1);
	lamp1_2->CreateShadow(g_Assets->lamp_1_2Shadow, 217.5f, 217.5f, 1, 1, COLLISION_TYPE::SQUARE);
	iphone->CreateObject(g_Assets->iphone, 186.0f, 141.0f, 1, 1);
	iphone->CreateShadow(g_Assets->iphoneShadow, 205.0f, 155.0f, 1, 1, COLLISION_TYPE::SQUARE);
	triangleBlock->CreateObject(g_Assets->triangleBlock, 378.0f, 348.0f, 1, 1);
	//->CreateShadow(g_Assets->triangleBlockShadow, 190.5, 172.5, 1, 1, COLLISION_TYPE::TRIANGLE, TRIANGLE_TYPE::TRI_ISO);
	triangleBlock->CreateShadow(g_Assets->triangleBlockShadow, 190.5f, 172.5f, 1, 1, COLLISION_TYPE::SQUARE);

	//1-3
	sandwich->CreateObject(g_Assets->sandwich, 211.5f, 238.5f, 1, 1);
	sandwich->CreateShadow(g_Assets->sandwichShadow, 126.0f, 144.0f, 1, 1, COLLISION_TYPE::SQUARE);
	newspaper->CreateObject(g_Assets->newspaper, 301.5f, 229.5f, 1, 1);
	newspaper->CreateShadow(g_Assets->newspaperShadow, 361.8f, 300.0f, 1, 1, COLLISION_TYPE::SQUARE);
	bucket->CreateObject(g_Assets->busket, 255.0f, 219.0f, 1, 1);
	bucket->CreateShadow(g_Assets->busketShadow, 306.0f, 262.8f, 1, 1, COLLISION_TYPE::SQUARE);
	picnicbasket->CreateObject(g_Assets->picnicbasket, 306.0f, 240.0f, 1, 1);
	picnicbasket->CreateShadow(g_Assets->picnicbasketShadow, 275.4f, 216.0f, 1, 1, COLLISION_TYPE::SQUARE);
	
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

	//comingSoon->m_pos = { 0.0f,0.0f,0.8f };
	//comingSoon->m_anime->SetAnimeSpeed(0.15f);
	//comingSoon->SetLoop(false);
	//comingSoon->isMultiPattern = false;
	//comingSoonLoop->m_pos = { 0.0f,0.0f,0.9f };
	//comingSoonLoop->m_anime->SetAnimeSpeed(0.15f);
	//comingSoonLoop->SetLoop(true);
	//comingSoonLoop->isMultiPattern = false;

	//coming soon Animation
	comingSoon->InitAnimation(false);
	comingSoonLoop->InitAnimation(false);
	comingSoon->SetAnimeted(true);
	comingSoonLoop->SetAnimeted(true);
	

	//ARROW

	uiArrow->m_pos = { 6.0f,325.0f / SCREEN_PARA,0.1f };
	uiArrow->m_anime->SetAnimeSpeed(0.15f);
	uiArrow->InitAnimation(false);
	static_cast<ObjectAnimation*>(uiArrow->m_anime)->SetLoop(true);

	//controlPanel;
	controlPanel->m_pos = { 0,0,0.2f};//一番手前にする
	controlPanel->m_scale = { 0.96f,0.96f,0.96f };

	//マスクの位置設定
	stageMask->m_pos.z = 0.7f;//hintの後ろ
	resultMask->m_pos.z = 0.9f;

	//配列の初期化と設定
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

	//ゲームツールの設定
	//シーンを設定する
	SceneManager::Get()->SetScene(SCENENAME::TITLE);
	fade = new Fade();
	fade->FadeIn();//最初のFadeIn設定いる

	//レールの初期化
	RailManager::Get()->InitRail();

	//CameraShakerの初期化
	cameraShaker = new CameraShaker();
	cameraShaker->InitCameraShaker(0.1f, 3.0f, 20);	//強度、周波数、継続の時間の初期化を行う
	//リザルトの初期化
	resultGenerator = new Result();
	resultGenerator->Init();
	//リザルトアニメションの初期化
	resultAnimator = new ResultAnimation();
	resultAnimator->Init();
	//UIオブジェクトの初期化とアニメション
	uiManager = new UiManager();
	uiManager->Init();

	//音声を設定する
	XA_Play(SE_TITLE);
	XA_Play(BGM_TITLE);
}

void Game::InitStage()
{

	//ステージの初期化
	switch (SceneManager::Get()->GetStage()) {

	case STAGE1_1:

		XA_Play(BGM_Stage1);//サウンド再生
		//XA_SetVolume(BGM_Stage1, 0.0f);//お題が出たときのSEを邪魔しないように音量を
		InitStage1_1();

		break;

	case STAGE1_2:

		XA_Play(BGM_Stage2);//サウンド再生
		//XA_SetVolume(BGM_Stage1, 0.0f);
		InitStage1_2();

		break;

	case STAGE1_3:

		XA_Play(BGM_Stage3);//サウンド再生
		//XA_SetVolume(BGM_Stage1, 0.0f);
		InitStage1_3();

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


void Game::InitHintArray()
{
	for (int i = 0; i < 9; i++) {
		stageHint[i] = new CanvasUI();
	}
	
	stageHintBg = new CanvasUI();

	//テクスチャ割り当て
	for (int i = 0; i < 9; i++) {
	
		stageHint[i]->CreateModel(g_Assets->stageHint1_1, 883, 657, 1, 1);
	}
	
	stageHintBg->CreateModel(g_Assets->stageHintBg, 1280, 720, 1, 1);


	stageHint[STAGE1_1]->SetTexture(g_Assets->stageHint1_1);
	stageHint[STAGE1_2]->SetTexture(g_Assets->stageHint1_2);
	stageHint[STAGE1_3]->SetTexture(g_Assets->stageHint1_3);

	//位置設定
	for (int i = 0; i < 9; i++) {
		stageHint[i]->m_pos = { 0,0,0.2f};
	}
	stageHintBg->m_pos = { 0,0,0.4f };
	//位置設定
}


void Game::TitleUpdate(void)
{	
	/*UiManager::Get()->Update();*/
	uiManager->TitleUpdate();

}

void Game::TutorialUpdate(void)
{

	//switch (tutorial)
	//{
	//case Game::TUTORIAL1:
	//	if (!tutorial1->GetAnimated()) {
	//		tutorial1->SetActive(false);
	//		/*uiTutorial[TUTORIAL1]->SetActive(true);*/
	//	}
	//	tutorial1->Update();
	//	/*uiTutorial[TUTORIAL1]->Update();*/
	//	break;
	//case Game::TUTORIAL2:
	//	if (!tutorial2->GetAnimated()) {
	//		tutorial2->SetActive(false);
	//		tutorial2loop->SetActive(true);
	//	}

	//	tutorial2->Update();
	//	tutorial2loop->Update();
	//	break;
	//case Game::TUTORIAL3:
	//	if (!tutorial3->GetAnimated()) {
	//		tutorial3->SetActive(false);
	//		tutorial3loop->SetActive(true);
	//	}

	//	tutorial3->Update();
	//	tutorial3loop->Update();
	//	break;
	//case Game::TUTORIAL4:
	//	if (!tutorial4->GetAnimated()) {
	//		tutorial4->SetActive(false);
	//		tutorial4loop->SetActive(true);
	//	}

	//	tutorial4->Update();
	//	tutorial4loop->Update();
	//	break;
	//case Game::TUTORIAL5:

	//	if (!tutorial5->GetAnimated()) {
	//		tutorial5->SetActive(false);
	//		tutorial5loop->SetActive(true);
	//	}

	//	tutorial5->Update();
	//	tutorial5loop->Update();
	//	break;
	//default:
	//	break;
	//}

	//if (Input::Get()->GetKeyTrigger(DIK_SPACE)) {
	//
	//	int num = tutorial;
	//	num++;
	//	tutorial = static_cast<TUTORIAL>(num);

	//	if (num > 4) {
	//		SceneManager::Get()->SetScene(STAGESELECT);
	//		XA_Stop(BGM_TITLE);
	//		XA_Stop(SE_TITLE);
	//		XA_Play(SE_Press);// テスト用
	//		XA_Play(BGM_SelectStage);//セレクトBGM再生
	//	}
	//
	//}

	uiManager->TutorialUpdate();
}

void Game::SelectUpdate(void)
{
	uiManager->SelectUpdate();
}

void Game::UpdateStage1_1(void)
{
	//背景
	stageBg->Update();

	for (auto& element : objectList) {
		if (!element->GetStill()) {
			isPlaySE = true;
			//ループ中止
			break;
		}
	}

	if (isPlaySE) {

		XA_Play(SE_Plant);
		
		//いったんOFFにしてまた再生されるように
		isPlaySE = false;
	}

	//本体の更新
	for (auto& element : objectList) {
		element->Update();
	}

	//影の更新
	coconut->ShadowUpdate(0, 4.8f);
	lamp->ShadowUpdate(0, 4.5f);
	housePlate->ShadowUpdate(0, 4.5f);

	//クリア判定
 	if (ColliderManager::Get()->ClearCollision({OVERLAP,COL_DOWN }, "coconut", "lamp", ShadowObject::SMALL)&&
		ColliderManager::Get()->ClearCollision({OVERLAP,COL_DOWN},"lamp","housePlate",ShadowObject::LARGE)) {		
		////クリア
		SceneManager::Get()->m_stageHolder[SceneManager::Get()->GetStage()]->SetClear(true);
		SceneManager::Get()->ChangeScene(RESULT);
		isResultAnime = true;
		XA_Play(SE_Interval1);//リザルトに遷移した後、SE再生

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
			isPlaySE = true;
			//ループ中止
			break;
		}
	}

	if (isPlaySE) {
		
		
		XA_Play(SE_Plant);

		//いったんOFFにしてまた再生されるように
		isPlaySE = false;
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
		XA_Play(SE_Interval2);

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
			isPlaySE = true;
			//ループ中止
			break;
		}
	}

	if (isPlaySE) {


		XA_Play(SE_Plant);

		//いったんOFFにしてまた再生されるように
		isPlaySE = false;
	}

	//OBJECT UPDATE
	for (auto& element : objectList) {
		element->Update();
	}

	//TestMove();

	//SHADOW UPDATE
	newspaper->ShadowUpdate(0.0f,3.6f);
	sandwich->ShadowUpdate(1.0f,2.8f);
	picnicbasket->ShadowUpdate(1.5f,3.0f);
	bucket->ShadowUpdate(3.f,3.2f);

		
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

void Game::SwitchObject()
{
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
					
						//次のオブジェクトを移動できる
						XA_Play(SE_Select);//セレクトSE再生
						(*nextIt)->SetActive(true);
						

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
				uiManager->InitStage();
			}
			if (SceneManager::Get()->GetScene() == STAGESELECT) {

				XA_Play(BGM_SelectStage);// セレクト画面に戻った時にBGM再生
				
				/*UiManager::Get()->InitUi();*/
				uiManager->InitStageSelect();
			}
			if (SceneManager::Get()->GetScene() == TUTORIAL) {
				/*UiManager::Get()->InitUi();*/
				uiManager->InitTutorial();
			}
		}
	}

	switch (SceneManager::Get()->GetScene()) {
	case SCENENAME::TITLE:
		TitleUpdate();
		break;
	case SCENENAME::TUTORIAL:
		TutorialUpdate();
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

	delete comingSoon;
	delete comingSoonLoop;

	for (int i = 0; i < 3; i++)
	{
		delete stageHint[i];
	}

	delete stageHintBg;
	delete stageMask;

	delete controlPanel;
	delete resultMask;//リザルト画面のマスク

	//配列の分を解放
	delete stageBg;
	delete coconut;
	delete lamp;
	delete housePlate;

	//1-2
	delete lamp1_2;			//台形
	delete triangleBlock;	//三角形
	delete iphone;			//平行四角形

	//1-3
	delete sandwich;
	delete newspaper;
	delete bucket;
	delete picnicbasket;

	delete testEffect;
	delete cameraShaker;
	delete resultGenerator;	
	delete resultAnimator;
	delete uiManager;
	delete uiStepNum;
	delete uiArrow;
	delete fade;

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


void Game::PauseSwitch(void)
{
	if (isPause)
	{
		isPause = false;
		//画面エフェクトの切り替え
		stageMask->SetActive(true);
		controlPanel->SetActive(true);
		uiArrow->SetActive(false);

	}
	else
	{
		isPause = true;
		//画面エフェクトの切り替え
		stageMask->SetActive(false);
		controlPanel->SetActive(false);
		uiArrow->SetActive(false);
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
	case SCENENAME::TUTORIAL:
		TutorialDraw();
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
	uiManager->TitleDraw();

}

void Game::TutorialDraw(void)
{
	uiManager->TutorialDraw();
}

void Game::SelectDraw(void)
{
	uiManager->SelectDraw();
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

		uiManager->StageDraw();

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
				(*it)->m_obj->m_sprite->m_materialDiffuse = { 1.0f, 1.0f, 1.0f, 0.8f };
				break;
			case 1:
				(*it)->m_obj->m_sprite->m_materialDiffuse = { 1.0f, 1.0f, 1.0f, 0.6f };
				break;
			case 2:
				(*it)->m_obj->m_sprite->m_materialDiffuse = { 1.0f, 1.0f, 1.0f, 0.3f };
				break;
			}	
		}
		else {
			(*it)->m_obj->m_sprite->m_materialDiffuse = { 1.0f, 1.0f, 1.0f, 1.0f };
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

			if (isPause) {
				uiManager->StageUpdate();
			}
			else {
				controlPanel->SetActive(true);
				uiArrow->SetActive(true);

				//入力処理
				if (Input::Get()->GetKeyTrigger(DIK_ESCAPE))
				{
					XA_Play(SE_SelectDecide);//決定SE再生
					PauseSwitch();
				}
				//移動させる目標を設定する
				SwitchObject();

				if (Input::Get()->GetKeyTrigger(DIK_H)) {
					SceneManager::Get()->m_stageHolder[SceneManager::Get()->GetActiveStage()]->SetHint(true);
				}

				//StageUpdate
				switch (SceneManager::Get()->GetStage()) {

				case STAGE1_1:
					XA_Stop(SE_Present);
					UpdateStage1_1();

					break;

				case STAGE1_2:
					XA_Stop(SE_Present);
					UpdateStage1_2();

					break;

				case STAGE1_3:
					XA_Stop(SE_Present);
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
	stageBg->m_sprite->m_rotation.x = 19.8f;//カメラと垂直状態を保持するため
	stageBg->m_sprite->m_scale = { 2.65f,2.65f,1.0f};//固定値
	//y
	float y = 21.626f - 7.0f / ROTATEX;
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

void Game::ApplyVolume()
{

	for (int i = 0; i < 5; i++) {

		SOUND_LABEL sound = static_cast<SOUND_LABEL>(i);
		XA_SetVolume(sound, bgmVolume);
	}

	for (int i = 5; i < 16; i++) {
		SOUND_LABEL sound = static_cast<SOUND_LABEL>(i);
		XA_SetVolume(sound, seVolume);
	}


}

