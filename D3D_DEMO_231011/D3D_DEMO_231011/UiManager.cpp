#include "UiManager.h"
#include "Game.h"
#include "Assets.h"
#include "DInput.h"
#include "CanvasUI.h"
#include "SceneManager.h"
#include "xa2.h"
#include <DirectXMath.h>
#include "Fade.h"

extern Assets* g_Assets;

UiManager::~UiManager()
{
	//title
	delete uiTitleBg;

	//tutorial
	for (int i = 0; i < tutorialNum; i++) {
		delete uiTutorial[i];
		delete uiPageIn[i];
	}

	//select
	delete uiSelectBg;//背景
	delete uiSelectCursor;//ステージセレクトのカーソル
	for (int i = 0; i < stageNum; i++) {
		delete uiSelectStage[i];
	}
	for (int i = 0; i < chapterNum; i++) {
		delete uiSelectChapter[i];
		delete uiClearMark[i];
	}
	delete stageMask;
	delete chapterMask;

	//pause
	delete uiPauseBg;		//PAUSEの背景
	for (int i = 0; i < pauseNum; i++) {
		delete uiPauseButton[i];
	}
	delete uiResume;			//PAUSEのボタン
	delete uiRestart;		//ステージのボタン
	delete uiBackSelect;		//セレクト画面に戻る
	delete uiSoundCursor;	//サウンド用カーソル

	delete uiSound;
	delete uiSoundBg;		//SOUNDの背景

	for (int i = 0; i < 5; i++) {
		delete uiSoundOp_BGM[i];	//BGM設定
		delete uiSoundOp_SE[i];	//SE設定
	}
	
	delete pauseMask;

	delete[] uiSelectChapter;
	delete[] uiSelectStage;
	delete[] uiClearMark;
	delete[] uiPageIn;
	delete[] uiPauseButton;

}

//UiManager* UiManager::Get()
//{
//	static UiManager instance;
//	return &instance;
//}

void UiManager::Init()
{
	//=============================
	//オブジェクト作成
	//=============================	

	//ツール作成
	//titleList = new UiList();
	//tutorialList = new UiList();
	//selectList = new UiList();
	//pauseList = new UiList();
	//soundList = new UiList();

	//title
	uiTitleBg = new CanvasUI();


	//tutorial
	uiTutorial = new CanvasUI * [tutorialNum];
	uiPageIn = new CanvasUI * [tutorialNum];
	for (int i = 0; i < tutorialNum; i++) {
		uiTutorial[i] = new CanvasUI();
		uiPageIn[i] = new CanvasUI();
	}

	//select
	uiSelectBg = new CanvasUI();//背景
	uiSelectCursor = new CanvasUI();//ステージセレクトのカーソル
	uiSelectStage = new CanvasUI * [stageNum];
	for (int i = 0; i < stageNum; i++) {
		uiSelectStage[i] = new CanvasUI();
	}
	uiSelectChapter = new CanvasUI * [chapterNum];
	uiClearMark = new CanvasUI * [chapterNum];
	for (int i = 0; i < chapterNum; i++) {
		uiSelectChapter[i] = new CanvasUI();
		uiClearMark[i] = new CanvasUI();
	}
	stageMask = new CanvasUI();
	chapterMask = new CanvasUI();
	//pause
	uiPauseBg = new CanvasUI();		//PAUSEの背景
	uiPauseButton = new CanvasUI * [pauseNum];
	for (int i = 0; i < pauseNum; i++) {
		uiPauseButton[i] = new CanvasUI();
	}
	uiResume= new CanvasUI();			//PAUSEのボタン
	uiRestart= new CanvasUI();		//ステージのボタン
	uiBackSelect= new CanvasUI();		//セレクト画面に戻る
	uiSound= new CanvasUI();

	uiSoundCursor= new CanvasUI();	//サウンド用カーソル
	uiSoundBg= new CanvasUI();		//SOUNDの背景

	for (int i = 0; i < 5; i++) {
		uiSoundOp_BGM[i] = new CanvasUI();
		uiSoundOp_SE[i] = new CanvasUI();
	}

	pauseMask = new CanvasUI();

	//=============================
	//モデル作成
	//=============================	
	//タイトル
	uiTitleBg->CreateModel(g_Assets->uiTitleBg, 1280, 720, 10, 2);

	//チュートリアル
	uiPageIn[INTRODUCE]->CreateModel(g_Assets->uiTutorialAnimation[INTRODUCE], 1280, 720, 8, 1);
	uiTutorial[INTRODUCE]->CreateModel(g_Assets->uiTutorial[INTRODUCE], 1280, 720, 8, 2);
	uiPageIn[MOVE1]->CreateModel(g_Assets->uiTutorialAnimation[MOVE1], 1280, 720, 8, 1);
	uiTutorial[MOVE1]->CreateModel(g_Assets->uiTutorial[MOVE1], 1280, 720, 6, 2);
	uiPageIn[MOVE2]->CreateModel(g_Assets->uiTutorialAnimation[MOVE2], 1280, 720, 7, 1);
	uiTutorial[MOVE2]->CreateModel(g_Assets->uiTutorial[MOVE2], 1280, 720, 9, 1);
	uiPageIn[MOVE3]->CreateModel(g_Assets->uiTutorialAnimation[MOVE3], 1280, 720, 7, 1);
	uiTutorial[MOVE3]->CreateModel(g_Assets->uiTutorial[MOVE3], 1280, 720, 6, 2);
	uiPageIn[MOVE4]->CreateModel(g_Assets->uiTutorialAnimation[MOVE4], 1280, 720, 7, 1);
	uiTutorial[MOVE4]->CreateModel(g_Assets->uiTutorial[MOVE4], 1280, 720, 6, 2);
	uiPageIn[SIZECHANGE]->CreateModel(g_Assets->uiTutorialAnimation[SIZECHANGE], 1280, 720, 8, 1);
	uiTutorial[SIZECHANGE]->CreateModel(g_Assets->uiTutorial[SIZECHANGE], 1280, 720, 11, 2);
	uiPageIn[COMBINITION]->CreateModel(g_Assets->uiTutorialAnimation[COMBINITION], 1280, 720, 8, 1);
	uiTutorial[COMBINITION]->CreateModel(g_Assets->uiTutorial[COMBINITION], 1280, 720, 8, 1);
	uiPageIn[END]->CreateModel(g_Assets->uiTutorialAnimation[END], 1280, 720, 8, 1);
	uiTutorial[END]->CreateModel(g_Assets->uiTutorial[END], 1280, 720, 7, 2);
	
	//セレクト画面
	uiSelectBg->CreateModel(g_Assets->uiSelectBg, 1280, 720, 1, 1);
	uiSelectCursor->CreateModel(g_Assets->uiSelectCursor, 76, 84, 1, 1);
	uiSelectStage[STAGE1]->CreateModel(g_Assets->uiSelectStage[STAGE1], 421, 133, 1, 2);
	uiSelectStage[STAGE2]->CreateModel(g_Assets->uiSelectStage[STAGE2], 421, 142, 1, 2);
	uiSelectStage[STAGE3]->CreateModel(g_Assets->uiSelectStage[STAGE3], 421, 143, 1, 2);
	for (int i = 0; i < chapterNum; i++) {
		uiSelectChapter[i]->CreateModel(g_Assets->uiSelectChapter[i],300, 57, 1, 1);	
	}
	for (int i = 0; i < chapterNum; i++)
	{
		uiClearMark[i]->CreateModel(g_Assets->uiClear, 87, 87, 1, 1);
	}
	
	stageMask->CreateModel(g_Assets->selectMask, 1280, 720, 1, 1);
	chapterMask->CreateModel(g_Assets->chapterMask, 1280, 720, 1, 1);


	//pause
	uiPauseBg->CreateModel(g_Assets->uiPauseBg, 647, 702, 1, 1);

	for (int i = 0; i < pauseNum; i++) {
		uiPauseButton[i]->CreateModel(g_Assets->uiPauseButton[i], 280, 92, 1, 2);
	}

	uiSoundBg->CreateModel(g_Assets->uiSoundBg, 687, 550, 1, 1);
	uiSoundCursor->CreateModel(g_Assets->uiSoundCursor, 56, 51, 1, 1);
	for (int i = 0; i < 5; i++) {
		uiSoundOp_BGM[i]->CreateModel(g_Assets->uiSoundOp_BGM, 313, 324, 1, 1);
		uiSoundOp_SE[i]->CreateModel(g_Assets->uiSoundOp_BGM, 313, 324, 1, 1);
	}

	pauseMask->CreateModel(g_Assets->resultMask, 1280, 720, 1, 1);
	
	//位置とアニメションの初期化
	InitUi();

}

void UiManager::Update()
{
	switch (SceneManager::Get()->GetScene()) {
	case SCENENAME::TITLE:
		TitleUpdate();
		break;
	case SCENENAME::TUTORIAL:
		TutorialUpdate();
		break;
	case SCENENAME::STAGESELECT:
		SelectUpdate();
		break;
	case SCENENAME::STAGE:
		StageUpdate();
		break;
	case SCENENAME::RESULT:
		break;
	}
}

void UiManager::Draw()
{
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
		break;
	}
	

}

void UiManager::InitUi()
{
	switch (SceneManager::Get()->GetScene()) {
	case SCENENAME::TITLE:
		InitTitle();
		break;
	case SCENENAME::TUTORIAL:
		InitTutorial();
		break;
	case SCENENAME::STAGESELECT:
		InitStageSelect();
		break;
	case SCENENAME::STAGE:
		InitStage();
		break;
	case SCENENAME::RESULT:
		break;
	}
}

void UiManager::InitTitle()
{
	//アニメション設定
	uiTitleBg->InitAnimation(false);
	uiTitleBg->m_anime->SetLoop(true);//最初はループしないように設定
	uiTitleBg->m_anime->SetAnimeSpeed(0.3f);

	//位置設定
	uiTitleBg->m_pos = { 0.0f,0.0f,0.9f };
}

void UiManager::InitTutorial()
{	
	//アニメション設定
	for (int i = 0; i < tutorialNum; i++) {
		uiTutorial[i]->InitAnimation(false);
		uiTutorial[i]->m_anime->SetLoop(true);
		uiTutorial[i]->m_anime->isPlaying = false;
		uiTutorial[i]->m_anime->SetAnimeSpeed(0.08f);
		uiTutorial[i]->m_pos = { 0.0f, 0.0f, 0.9f };
		uiTutorial[i]->m_scale = { 0.97f, 0.97f, 0.9f };
		uiTutorial[i]->SetActive(true);

		uiPageIn[i]->InitAnimation(false);
		uiPageIn[i]->m_anime->SetLoop(false);
		uiPageIn[i]->m_anime->SetAnimeSpeed(0.15f);
		uiPageIn[i]->m_pos = { 0.0f, 0.0f, 0.8f };
		uiPageIn[i]->m_scale = { 0.97f, 0.97f, 0.9f };
		uiPageIn[i]->SetActive(true);
	}

	tutorial = INTRODUCE;
	
	//位置設定
}

void UiManager::InitStageSelect()
{
	//位置&大小
	uiSelectBg->m_pos = { 0.0f,0.04f,0.9f };//背景を一番後ろ
	uiSelectBg->m_scale = { 0.98f,0.98f,1.0f };//大きさ
	uiSelectCursor->m_pos = { 5.2f,3.6f,0.8f };//Chapterの横に出るように

	uiSelectStage[STAGE1]->m_pos = { -3.2f,1.3f,0.8f };
	uiSelectStage[STAGE2]->m_pos = { -2.7f,-0.6f,0.8f };
	uiSelectStage[STAGE3]->m_pos = { -3.1f,-2.5f,0.8f };

	uiSelectChapter[CHAPTER1]->m_pos = { 3.1f,3.2f,0.8f };
	uiSelectChapter[CHAPTER2]->m_pos = { 3.1f,0.8f,0.8f };
	uiSelectChapter[CHAPTER3]->m_pos = { 3.1f,-1.5f,0.8f };
	stageMask->m_pos = { 0.0,0.0,0.2f };
	chapterMask->m_pos = { 0.0,0.0,0.2f };

	//クリアの印の位置設定
	float posy = 2.3f;
	uiClearMark[0]->m_pos = { 4.5f,posy,0.7f };
	posy = 2.3f - 2.5f;
	uiClearMark[1]->m_pos = { 5.0f,posy,0.7f };
	posy = 2.3f - 2.5f * 2.0f;
	uiClearMark[2]->m_pos = { 4.8f,posy,0.7f };

	//アニメション
	for (int i = 0; i < stageNum; i++) {
		uiSelectStage[i]->m_anime->SetAnimePattern(0);
		uiSelectStage[i]->m_anime->SetAnimeSpeed(0.05f);
	}

	//最初はカーソルを隠す
	uiSelectCursor->SetActive(false);

	//ステージを設定
	selectStage = STAGE1;
	selectChapter = CHAPTER1;
	isSelectStage = true;
	stageMask->SetActive(false);
	chapterMask->SetActive(true);
}

void UiManager::InitStage()
{
	//位置設定
	//マスクの位置設定
	pauseMask->m_pos.z = 0.9f;
	uiPauseBg->m_pos = { -300 / SCREEN_PARA, 0.0f, 0.8f };
	
	float posY = 1.7f;
	for (int i = 0; i < pauseNum; i++) {
		uiPauseButton[i]->m_pos = { -6.0,posY - i * 1.35f,0.7f };
		if (pauseSelect == i) {
			uiPauseButton[i]->m_anime->SetAnimePattern(1);
			uiPauseButton[i]->m_pos.x = -5.5f;
		}
		else {
			uiPauseButton[i]->m_anime->SetAnimePattern(0);
			uiPauseButton[i]->m_pos.x = -6.0f;
		}
	}

	//uiSound
	uiSoundBg->m_pos = { 1.0f, 0.2f, 0.6f };
	uiSoundBg->m_scale = { 1.0f,1.0f,1.0f };
	uiSoundBg->SetActive(false);

	uiSoundCursor->m_pos = { -2.0f, 0.65f, 0.5f };
	DirectX::XMFLOAT3 pos = { 1.0f, 0.7f, 0.5f };
	
	for (int i = 0; i < 5; i++)
	{
		//位置
		uiSoundOp_BGM[i]->m_pos = { pos.x + i * 0.8f,pos.y, pos.z };
		uiSoundOp_SE[i]->m_pos = { pos.x + i * 0.8f, -pos.y, pos.z };
		//大きさ
		uiSoundOp_BGM[i]->m_scale = { 0.2f,0.2f,0.2f };
		uiSoundOp_SE[i]->m_scale = { 0.2f,0.2f,0.2f };
		//最初は隠す
		uiSoundOp_BGM[i]->SetActive(false);
		uiSoundOp_SE[i]->SetActive(false);
	}
	//PAUSESELECT
	pauseSelect = RESUME;

	//Sound
	isSound = false;
}

void UiManager::TitleUpdate()
{
	//スペースキー押したら、チュートリアルに進む
	if (Input::Get()->GetKeyTrigger(DIK_SPACE)) {
		XA_Play(SE_TITLE);
		SceneManager::Get()->SetScene(SCENENAME::TUTORIAL);
		InitTutorial();
	}
	uiTitleBg->Update();

}

void UiManager::TutorialUpdate()
{
	if (!uiPageIn[tutorial]->m_anime->isPlaying) {
		uiPageIn[tutorial]->SetActive(false);
		uiTutorial[tutorial]->m_anime->isPlaying = true;
	}

	uiTutorial[tutorial]->Update();
	uiPageIn[tutorial]->Update();

	if (Input::Get()->GetKeyTrigger(DIK_SPACE)) {

		XA_Play(SE_TITLE);
		if (tutorial != END) {//最後まで行ってない場合
			int num = tutorial;
			num++;
			//データタイプを転換
			tutorial = static_cast<TUTORIAL_SKILL>(num);
		}
		else {
			//シーンの切り替え
			XA_Play(SE_SelectDecide);
			SceneManager::Get()->ChangeScene(STAGESELECT);

		}
	}

}

void UiManager::SelectUpdate()
{
	DoSelectKey();

	SetSelectStatus();
	uiSelectBg->Update();
	uiSelectCursor->Update();


	
	for (int i = 0; i < stageNum; i++) {
		uiSelectStage[i]->Update();
	}

	for (int i = 0; i < chapterNum; i++) {
		uiSelectChapter[i]->Update();
		uiClearMark[i]->Update();
	}

}

void UiManager::ObjectMove(CanvasUI* pObject, float moveSpeed,float bounceHeight)
{
	float rate = 0.1f;
	pObject->m_pos.y = pObject->m_pos.y + bounceHeight * rate * sinf(selectCounter * moveSpeed);
	selectCounter++;
}

void UiManager::DoSelectKey()
{
	if (Game::Get()->GetFade()->mState != Fade::FADE_IN) {
	
	
	//スペースキー押した時
	if (Input::Get()->GetKeyTrigger(DIK_SPACE)) {
		XA_Play(SE_SelectDecide);//決定SE再生

		if (isSelectStage) {//ステージを選択
			isSelectStage = false;//SelectChapterに入る
			selectChapter = CHAPTER1;//チャプターを設定
			uiSelectCursor->SetActive(true);
		}
		else {//チャプターを選択
			//今のステージを計算
			int num = selectStage * 3 + selectChapter;
			//シーンマネージャーに今のステージを伝える
			SceneManager::Get()->SetStage(static_cast<STAGEINFO>(num));
			//シーン遷移に入る
			SceneManager::Get()->ChangeScene(STAGE);

			//XA_Play(SE_Present);//ステージに遷移するとお題のSEを再生
		}
	}

	if (Input::Get()->GetKeyTrigger(DIK_UPARROW)) {
		XA_Play(SE_Select);//選択SE再生
		//Do Select KeyEvents
		if (isSelectStage) {
			//STAGE1の場合制限する
			if (selectStage == STAGE1) {
				selectStage = STAGE3;
			}
			else {
				int num = selectStage;
				num--;
				selectStage = static_cast<SELECTSTAGE>(num);
			}
		}
		else {//ステージセレクト
			//CHAPTER1の場合制限する
			if (selectChapter == CHAPTER1) {
				selectChapter = CHAPTER3;
			}
			else {
				int num = selectChapter;
				num--;
				selectChapter = static_cast<SELECTCHAPTER>(num);
			}
		}
	}

	if (Input::Get()->GetKeyTrigger(DIK_DOWNARROW)) {
		XA_Play(SE_Select);//選択SE再生
		//Do Select KeyEvents
		if (isSelectStage) {
			//STAGE1の場合制限する
			if (selectStage == STAGE3) {
				selectStage = STAGE1;
			}
			else {
				int num = selectStage;
				num++;
				selectStage = static_cast<SELECTSTAGE>(num);
			}
		}
		else {//ステージセレクト
			//CHAPTER1の場合制限する
			if (selectChapter == CHAPTER3) {
				selectChapter = CHAPTER1;
			}
			else {
				int num = selectChapter;
				num++;
				selectChapter = static_cast<SELECTCHAPTER>(num);
			}
		}
	}

	if (Input::Get()->GetKeyTrigger(DIK_ESCAPE)) {
		XA_Play(SE_SelectDecide);//セレクトSE再生
		//ステージ選択の場合→タイトルに戻る
		if (isSelectStage) {
			SceneManager::Get()->ChangeScene(TITLE);
		}
		else {
			isSelectStage = true;
			//カーソルを隠す
			uiSelectCursor->SetActive(false);
			//元の位置に戻る
			selectChapter = CHAPTER1;
		}
	}

	}
}

void UiManager::SetSelectStatus()
{
	if (isSelectStage) {
		//選択されたステージアニメション起動
		for (int i = 0; i < 3; i++) {
			if (selectStage == i) {
				//ACTIVE
				uiSelectStage[i]->m_anime->SetAnimePattern(CanvasUI::ACTIVE);
				ObjectMove(uiSelectStage[i], 0.2f, 0.1f);
				
			}
			else {
				//INACTIVE
				uiSelectStage[i]->m_anime->SetAnimePattern(CanvasUI::INACTIVE);
				uiSelectStage[i]->m_pos.y = 1.3f - 1.9f * i;
			}
		}
	}
	else {
		int num = selectChapter;
		uiSelectCursor->m_pos = { 1.3f, 3.6f - num * 2.4f, 0.7f };
		ObjectMove(uiSelectCursor, 0.1f, 0.4f);//羽ペンを動かす
	}

	//クリアの印をつける
	int num = selectStage * 3;
	for (int i = 0; i < 3; i++) {
		//完成下かどうか
		if (SceneManager::Get()->m_stageHolder[num + i]->GetCompleted()) {
			//クリアしたら描画する
			uiClearMark[i]->SetActive(true);
		}
		else {
			//クリアしなかったら描画しない
			uiClearMark[i]->SetActive(false);
		}
	}
	if (!isSelectStage) {
		stageMask->SetActive(true);
		chapterMask->SetActive(false);
	}
	else {
		stageMask->SetActive(false);
		chapterMask->SetActive(true);
	}

	
}

void UiManager::StageUpdate()
{
	if (!Game::Get()->GetPause()) { return; }
	else {
		DoStageKey();

		//アニメションの変更
		for (int i = 0; i < pauseNum; i++) {
			if (pauseSelect == i) {
				uiPauseButton[i]->SetAnimeActive(CanvasUI::ACTIVE);
				ObjectMove(uiPauseButton[i], 0.1f, 0.03f);
				uiPauseButton[i]->m_pos.x = -5.5f;
			}
			else {
				uiPauseButton[i]->SetAnimeActive(CanvasUI::INACTIVE);
				uiPauseButton[i]->m_pos.x = -6.0f;
			}
		}

		//元の状態が残さないようにリセット
		for (int i = 0; i < 5; i++) {
		
			uiSoundOp_BGM[i]->SetActive(false);
			uiSoundOp_SE[i]->SetActive(false);
		}

		//表示するかどうかを設定	
		if (isSound) {
			uiSoundBg->SetActive(true);
			uiSoundCursor->SetActive(true);
			//今の状態をアップデート
			for (int i = 0; i < Game::Get()->GetBGMVolume(); i++) {
				uiSoundOp_BGM[i]->SetActive(true);
			}
			for (int i = 0; i < Game::Get()->GetSEVolume(); i++) {
				uiSoundOp_SE[i]->SetActive(true);
			}
			//カーソルの位置を更新する
			if (isSelectBgm) {
				uiSoundCursor->m_pos = { -2.0f, 0.7f, 0.5f };
			}
			else {
				uiSoundCursor->m_pos = { -2.0f, -0.7f, 0.5f };
			}
			
		}
		else {
			uiSoundBg->SetActive(false);
			uiSoundCursor->SetActive(false);
			isSelectBgm = true;//RESET
		}

		//マスクを有効にする
		pauseMask->SetActive(true);

		//Apply Animation
		for (int i = 0; i < pauseNum; i++) {
			uiPauseButton[i]->Update();
		}
	}
}

void UiManager::DoStageKey()
{
	if (isSound) {
	
		if (Input::Get()->GetKeyTrigger(DIK_ESCAPE)) {
			XA_Play(SE_Select);
			isSound = false;
		}

		if (Input::Get()->GetKeyTrigger(DIK_LEFTARROW)) {
			if (isSelectBgm) {
			
				XA_Play(SE_Select);//セレクトSE再生
				if (Game::Get()->GetBGMVolume() <= 0) {
					Game::Get()->SetBGMVolume(0);
				}
				else {
					Game::Get()->SetBGMVolume(Game::Get()->GetBGMVolume() - 1.0f);
				}
			}
			else {
				XA_Play(SE_Select);//セレクトSE再生
				if (Game::Get()->GetSEVolume() <= 0) {
					Game::Get()->SetSEVolume(0);
				}
				else {
					Game::Get()->SetSEVolume(Game::Get()->GetSEVolume() - 1.0f);
				}
			
			}
		}

		if (Input::Get()->GetKeyTrigger(DIK_RIGHTARROW)) {
			if (isSelectBgm) {
				//制限をかける
				XA_Play(SE_Select);//セレクトSE再生
				if (Game::Get()->GetBGMVolume() >= 5) {
					Game::Get()->SetBGMVolume(5);
				}
				else {
					Game::Get()->SetBGMVolume(Game::Get()->GetBGMVolume() + 1.0f);
				}
			}
			else {
				XA_Play(SE_Select);//セレクトSE再生
				//制限をかける
				if (Game::Get()->GetSEVolume() >= 5) {
					Game::Get()->SetSEVolume(5);
				}
				else {
					Game::Get()->SetSEVolume(Game::Get()->GetSEVolume() + 1.0f);
				}
			}
		}

		if (Input::Get()->GetKeyTrigger(DIK_UPARROW)) {
			XA_Play(SE_Select);
			if (isSelectBgm) {
				isSelectBgm = false;
			}
			else {
				isSelectBgm = true;
			}
		}

		if (Input::Get()->GetKeyTrigger(DIK_DOWNARROW)) {
			XA_Play(SE_Select);
			if (isSelectBgm) {
				isSelectBgm = false;
			}
			else {
				isSelectBgm = true;
			}
		}

		//音声をここだけで変更
		Game::Get()->ApplyVolume();
	}
	else {

		if (Input::Get()->GetKeyTrigger(DIK_ESCAPE)) {
			XA_Play(SE_SelectDecide);
			Game::Get()->PauseSwitch();
		}
		if (Input::Get()->GetKeyTrigger(DIK_SPACE)) {
			XA_Play(SE_SelectDecide);
			switch (pauseSelect)
			{
			case UiManager::RESUME:
				Game::Get()->PauseSwitch();
				break;
			case UiManager::RESTART:
				Game::Get()->InitStage();
				Game::Get()->PauseSwitch();
				InitUi();//PAUSE画面の設定を最初に戻る
				break;
			case UiManager::BACKSELECT:
				Game::Get()->PauseSwitch();
				InitUi();//PAUSE画面の設定を最初に戻る
				SceneManager::Get()->ChangeScene(SCENENAME::STAGESELECT);
				
				break;
			case UiManager::SOUND:
				isSound = true;
				break;
			case UiManager::PAUSE_IDLE:
				break;
			default:
				break;
			}
		}
		if (Input::Get()->GetKeyTrigger(DIK_UPARROW)) {
			XA_Play(SE_Select);
			if (pauseSelect == RESUME) {
				pauseSelect = SOUND;
			}
			else {
				int num = pauseSelect;
				num--;
				pauseSelect = static_cast<PAUSESELECT>(num);
			}
		}
		if (Input::Get()->GetKeyTrigger(DIK_DOWNARROW)) {
			XA_Play(SE_Select);
			//制限
			if (pauseSelect ==SOUND) {
				pauseSelect = RESUME;
			}
			else {
				int num = pauseSelect;
				num++;
				pauseSelect = static_cast<PAUSESELECT>(num);
			}
		}
	}
}

void UiManager::TitleDraw()
{
	uiTitleBg->Draw();
}

void UiManager::TutorialDraw()
{
	uiPageIn[tutorial]->Draw();
	uiTutorial[tutorial]->Draw();
	
}

void UiManager::SelectDraw()
{
	uiSelectBg->Draw();
	for (int i = 0; i < stageNum; i++) {
		uiSelectStage[i]->Draw();
	}

	for (int i = 0; i < chapterNum; i++) {
		uiSelectChapter[i]->Draw();
		uiClearMark[i]->Draw();
	}

	uiSelectCursor->Draw();

	SetBlendState(GetBlendMultiply());
	stageMask->Draw();
	chapterMask->Draw();
	SetBlendState(GetBlendAlpha());

}

void UiManager::StageDraw()
{
	if (!Game::Get()->GetPause()) {
	
		return;
	}
	else {
		SetBlendState(GetBlendMultiply());
		pauseMask->Draw();
		SetBlendState(GetBlendAlpha());

		uiPauseBg->Draw();
		for (int i = 0; i < pauseNum; i++) {
			uiPauseButton[i]->Draw();
		}
		uiSoundBg->Draw();
		uiSoundCursor->Draw();
		for (int i = 0; i < 5; i++) {
			uiSoundOp_BGM[i]->Draw();
			uiSoundOp_SE[i]->Draw();
		}

	}
}


