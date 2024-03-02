#include "Result.h"
#include "CanvasUI.h"
#include "Assets.h"
#include "DInput.h"
#include "SceneManager.h"
#include "ResultProcess.h"
#include "Game.h"
#include "xa2.h"

extern Assets* g_Assets;

Result::Result()
{
	processor = new ResultProcess();
	SetStarNum({ 30,40,50,60 });
}

Result::~Result()
{
	delete processor;
	delete uiResult;
	delete resultBg;
	delete Result_score;
	delete Result_stepcount;

	for (int i = 0; i < 3; i++) {
		delete Button[i];
	}

	for (int i = 0; i < 5; i++)
	{
		delete star[i];
		delete starShadow[i];
	}
}
void Result::Init()
{
	//StepNumの初期化
	processor->Init(1.8f, 0.0f, 0.95f, 10);
	uiResult = new CanvasUI();
	resultBg = new CanvasUI();
	Result_score = new CanvasUI();
	Result_stepcount = new CanvasUI();

	for (int i = 0; i < 3; i++) {
		Button[i]=new CanvasUI();
	}
	
	//テクスチャ読み込み・モデル作成
	uiResult->CreateModel(g_Assets->result, 430, 104, 1, 1);
	resultBg->CreateModel(g_Assets->resultBg, 1029, 713, 1, 1);
	Result_score->CreateModel(g_Assets->Result_score, 139, 66, 1, 1);
	Result_stepcount->CreateModel(g_Assets->Result_stepcount, 375, 72, 1, 1);
	Button[AGAIN]->CreateModel(g_Assets->Button_again, 299, 96, 1, 2);
	Button[NEXT]->CreateModel(g_Assets->Button_next, 316, 107, 1, 2);
	Button[RETURN]->CreateModel(g_Assets->Button_return, 624, 114, 1, 2);

	//座標
	resultBg->m_pos = { 0.0f,0.0f,0.4f };
	uiResult->m_pos = { 0.0f,3.1f,0.3f };
	Result_score->m_pos = { -4.0f ,1.5f ,0.3f };
	Result_stepcount->m_pos = { -2.5f ,0.0f,0.3f };
	Button[AGAIN]->m_pos = { 2.0f ,-1.5f ,0.3f };
	Button[NEXT]->m_pos = { -2.3f ,-1.5f ,0.3f };
	Button[RETURN]->m_pos = { 0.0f,-3.0f,0.3f };
	
	resultBg->m_scale = { 0.95f,0.95f,1.0f };
	uiResult->m_scale = { 0.95f,0.95f,1.0f };
	Result_score->m_scale = { 0.95f,0.95f,1.0f };
	Result_stepcount->m_scale = { 0.95f,0.95f,1.0f };
	Button[AGAIN]->m_scale = { 0.95f,0.95f,1.0f };
	Button[NEXT]->m_scale = { 0.95f,0.95f,1.0f };
	Button[RETURN]->m_scale = { 0.95f,0.95f,1.0f };

	//アニメーション

	for (int i = 0; i < 5; i++)
	{
		star[i] = new CanvasUI();
		starShadow[i] = new CanvasUI();

		//テクスチャ読み込み・モデル作成
		star[i]->CreateModel(g_Assets->star, 88 , 85 , 1, 1);
		starShadow[i]->CreateModel(g_Assets->starShadow, 88 , 85 , 1, 1);

		//座標
		star[i]->m_pos = { -2.1f  + 1.5f*i ,1.5f ,0.3f };
		starShadow[i]->m_pos = { -2.1f  + 1.5f * i ,1.5f ,0.3f };
	}

	//背景
	buttonnum = 0;
}

void Result::Update()
{
	//スターの処理
	//引数１：ステージ終了時のステップ数　引数２：ステップ数によって星の数を変更するための制限
	StarEvent(ResultScore(SceneManager::Get()->m_stageHolder[SceneManager::Get()->GetActiveStage()]->GetStep(), Starnum));
	//キーの処理
	DoResultKeyEvent();
	//ボタンの処理
	ButtonEvent();

	uiResult->Update();
	resultBg->Update();
	Result_score->Update();
	Result_stepcount->Update();
	
	for (int i = 0; i < 3; i++) 
	{
		Button[i]->Update();
	}
	for (int i = 0; i < AllStar; i++)
	{
		star[i]->Update();
	}
	for (int i = 4; i+1 > AllStar; i--)
	{
		starShadow[i]->Update();
	}
}

void Result::Draw()
{
	//背景
	resultBg->Draw();
	uiResult->Draw();
	Result_score->Draw();
	Result_stepcount->Draw();
	for (int i = 0; i < 3; i++)
	{
		Button[i]->Draw();
	}
	for (int i = 0; i < AllStar; i++)
	{
		star[i]->Draw();
	}
	for (int i = 4; i + 1 > AllStar; i--)
	{
		starShadow[i]->Draw();
	}

	//ステージ終了時のステップ数を表示
	
	processor->PrintDebugLogLeft(SceneManager::Get()->m_stageHolder[SceneManager::Get()->GetActiveStage()]->GetStep());//
}

void Result::DoResultKeyEvent()
{
	// ボタン
	if (Input::Get()->GetKeyTrigger(DIK_UPARROW)) {
		XA_Play(SE_Select);
		switch (buttonnum)
		{
		case NEXT:
			buttonnum = RETURN;
			break;
		case AGAIN:
			buttonnum = RETURN;
			break;
		case RETURN:
			buttonnum = NEXT;
			break;
		default:
			break;
		}
	}

	if (Input::Get()->GetKeyTrigger(DIK_DOWNARROW)) {
		XA_Play(SE_Select);
		switch (buttonnum)
		{
		case NEXT:
			buttonnum = RETURN;
			break;
		case AGAIN:
			buttonnum = RETURN;
			break;
		case RETURN:
			buttonnum = NEXT;
			break;
		default:
			break;
		}
	
	}

	if (Input::Get()->GetKeyTrigger(DIK_RIGHTARROW)) {
		XA_Play(SE_Select);
		switch (buttonnum)
		{
		case NEXT:
			buttonnum = AGAIN;
			break;
		case AGAIN:
			buttonnum = NEXT;
			break;
		case RETURN:
			break;
		default:
			break;
		}
	}

	if (Input::Get()->GetKeyTrigger(DIK_LEFTARROW)) {
		XA_Play(SE_Select);
		switch (buttonnum)
		{
		case NEXT:
			buttonnum = AGAIN;
			break;
		case AGAIN:
			buttonnum = NEXT;
			break;
		case RETURN:
			break;
		default:
			break;
		}
	
	}

}

void Result::ButtonEvent()
{
	switch (buttonnum)
	{

	case AGAIN://もう一度同じステージへ
		//スペースを押したときにもう一度同じステージに遷移する
		if (Input::Get()->GetKeyTrigger(DIK_SPACE))
		{
			XA_Play(SE_SelectDecide);
			//同じステージだから、直接初期化をもう一回やったらいい
			SceneManager::Get()->ChangeScene(SCENENAME::STAGE);
			buttonnum = NEXT;
		}
		break;
	case RETURN://タイトルへ
		//スペースを押したときにタイトルに遷移する
		if (Input::Get()->GetKeyPress(DIK_SPACE))
		{
			SceneManager::Get()->ChangeScene(SCENENAME::STAGESELECT);
			buttonnum = NEXT;
			XA_Play(BGM_SelectStage);// セレクト画面に戻った時にBGM再生
		}
		break;
	case NEXT://次のステージへ
		//スペースを押したときに次のステージに遷移する
		if (Input::Get()->GetKeyTrigger(DIK_SPACE))
		{
			XA_Play(SE_SelectDecide);
			//ステージに戻る
			SceneManager::Get()->ChangeScene(SCENENAME::STAGE);
			buttonnum = NONE;
		}
		break;
	default:
		
		break;
	}

	for (int i = 0; i < 3; i++) {
		if (buttonnum == i) {
			Button[i]->m_anime->SetAnimePattern(1);
			ObjectMove(Button[i], 0.1f, 0.03f);
		}
		else {
			Button[i]->m_anime->SetAnimePattern(0);
		}
	}

}

void Result::StarEvent(int StarScore)
{
	switch (StarScore)
	{
	case STARONE://星１
		AllStar = STARONE;
		break;
	case STARTWO://星２
		AllStar = STARTWO;
		break;
	case STARTHREE://星３
		AllStar = STARTHREE;
		break;
	case STARFOUR://星４
		AllStar = STARFOUR;
		break;
	case STARFIVE://星５
		AllStar = STARFIVE;
		break;
	default://最低星1
		AllStar = STARONE;
		break;
	}
}

void Result::ObjectMove(CanvasUI* ui, float moveSpeed, float moveHeight)
{
	float rate = 0.1f;
	ui->m_pos.y = ui->m_pos.y + moveHeight * rate * sinf(resultCounter * moveSpeed);
	resultCounter++;
}

int Result::ResultScore(int resultStep, std::vector<int> StarNum)
{
	//星５の判定
	if (resultStep <= StarNum[0])
	{
		return STARFIVE;//星５
	}
	//星４の判定
	else if (resultStep <= StarNum[1])
	{
		return STARFOUR;//星４
	}
	//星３の判定
	else if (resultStep <= StarNum[2])
	{
		return STARTHREE;//星３
	}
	//星２の判定
	else if (resultStep <= StarNum[3])
	{
		return STARTWO;//星２
	}
	//星１の判定
	else
	{
		return STARONE;//星１
	}

	return 0;
}