#include "Result.h"
#include "CanvasUI.h"
#include "Assets.h"
#include "StaticObject.h"
#include "DInput.h"
#include "SceneManager.h"
#include "ResultProcess.h"
#include "Game.h"
#include "xa2.h"

#define SIZECHANGE 0.95f

extern Assets* g_Assets;

Result::Result()
{
	processor = new ResultProcess();

	//30以下まで星５
	//31以上40まで星４
	//41以上50まで星３
	//51以上60まで星２
	//61以上から星１
	SetStarNum({ 30,40,50,60 });
}

Result::~Result()
{
	delete processor;
	delete uiResult;
	delete resultBg;
	delete Button_again;
	delete Button_next;
	delete Result_score;
	delete Button_return;
	delete Result_stepcount;
	for (int i = 0; i < 5; i++)
	{
		delete star[i];
		delete starShadow[i];
	}
}
void Result::Init()
{
	//StepNumの初期化
	processor->Init(1.8f * SIZECHANGE, 0.0f, 1.0 * SIZECHANGE, 10);

	uiResult = new CanvasUI();
	resultBg = new CanvasUI();
	Result_score = new CanvasUI();
	Result_stepcount = new CanvasUI();
	Button_again = new CanvasUI();
	Button_next = new CanvasUI();
	Button_return = new CanvasUI();

	//テクスチャ読み込み・モデル作成
	uiResult->CreateModel(g_Assets->result, 430* SIZECHANGE, 104 * SIZECHANGE, 1, 1);
	resultBg->CreateModel(g_Assets->resultBg, 1029 * SIZECHANGE, 713 * SIZECHANGE, 1, 1);
	Result_score->CreateModel(g_Assets->Result_score, 139 * SIZECHANGE, 66 * SIZECHANGE, 1, 1);
	Result_stepcount->CreateModel(g_Assets->Result_stepcount, 375 * SIZECHANGE, 72 * SIZECHANGE, 1, 1);
	Button_again->CreateModel(g_Assets->Button_again, 299 * SIZECHANGE, 96 * SIZECHANGE, 1, 2);
	Button_next->CreateModel(g_Assets->Button_next, 316 * SIZECHANGE, 107 * SIZECHANGE, 1, 2);
	Button_return->CreateModel(g_Assets->Button_return, 311 * SIZECHANGE, 104 * SIZECHANGE, 1, 2);

	//座標
	resultBg->m_pos = { 0.0f,0.0f,0.4f };
	uiResult->m_pos = { 0.0f,3.1f* SIZECHANGE,0.3f };
	Result_score->m_pos = { -4.0f * SIZECHANGE,1.5f * SIZECHANGE,0.3f };
	Result_stepcount->m_pos = { -2.5f * SIZECHANGE,0.0f,0.3f };
	Button_again->m_pos = { 2.0f * SIZECHANGE,-1.5f * SIZECHANGE,0.3f };
	Button_next->m_pos = { -2.3f * SIZECHANGE,-1.5f * SIZECHANGE,0.3f };
	Button_return->m_pos = { 0.0f,-3.0f* SIZECHANGE,0.3f };

	//アニメーション
	Button_again->m_anime->SetAnimePattern(0);
	Button_next->m_anime->SetAnimePattern(0);
	Button_return->m_anime->SetAnimePattern(0);

	for (int i = 0; i < 5; i++)
	{
		star[i] = new CanvasUI();
		starShadow[i] = new CanvasUI();

		//テクスチャ読み込み・モデル作成
		star[i]->CreateModel(g_Assets->star, 88 * SIZECHANGE, 85 * SIZECHANGE, 1, 1);
		starShadow[i]->CreateModel(g_Assets->starShadow, 88 * SIZECHANGE, 85 * SIZECHANGE, 1, 1);

		//座標
		star[i]->m_pos = { -2.1f * SIZECHANGE + 1.5f*i * SIZECHANGE,1.5f * SIZECHANGE,0.3f };
		starShadow[i]->m_pos = { -2.1f * SIZECHANGE + 1.5f * i * SIZECHANGE,1.5f * SIZECHANGE,0.3f };
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
	Button_again->Update();
	Button_next->Update();
	Button_return->Update();
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
	Button_again->Draw();
	Button_next->Draw();
	Button_return->Draw();
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
	if (Input::Get()->GetKeyTrigger(DIK_DOWNARROW))
	{
		buttonnum = RETURN;
	}
	if (Input::Get()->GetKeyTrigger(DIK_RIGHTARROW))
	{
		buttonnum = AGAIN;
	}
	if (Input::Get()->GetKeyTrigger(DIK_LEFTARROW))
	{
		buttonnum = NEXT;
	}
}

void Result::ButtonEvent()
{
	switch (buttonnum)
	{
	case AGAIN://もう一度同じステージへ
		Button_again->m_anime->SetAnimePattern(1);
		Button_next->m_anime->SetAnimePattern(0);
		Button_return->m_anime->SetAnimePattern(0);

		//スペースを押したときにもう一度同じステージに遷移する
		if (Input::Get()->GetKeyTrigger(DIK_SPACE))
		{
			//同じステージだから、直接初期化をもう一回やったらいい
			SceneManager::Get()->ChangeScene(SCENENAME::STAGE);
			//Game::Get()->InitStage();
			buttonnum = NEXT;
		}
		break;
	case RETURN://タイトルへ
		Button_return->m_anime->SetAnimePattern(1);
		Button_again->m_anime->SetAnimePattern(0);
		Button_next->m_anime->SetAnimePattern(0);

		//スペースを押したときにタイトルに遷移する
		if (Input::Get()->GetKeyPress(DIK_SPACE))
		{
			SceneManager::Get()->ChangeScene(SCENENAME::STAGESELECT);
			buttonnum = NEXT;
			XA_Play(BGM_SelectStage);// セレクト画面に戻った時にBGM再生
		}
		break;
	case NEXT://次のステージへ
		Button_next->m_anime->SetAnimePattern(1);
		Button_again->m_anime->SetAnimePattern(0);
		Button_return->m_anime->SetAnimePattern(0);

		//スペースを押したときに次のステージに遷移する
		if (Input::Get()->GetKeyTrigger(DIK_SPACE))
		{
			//ステージに戻る
			SceneManager::Get()->ChangeScene(SCENENAME::STAGE);
	

			//初期化を行う
			//Game::Get()->InitStage();
			
			buttonnum = NEXT;
		}
		break;
	default:
		Button_again->m_anime->SetAnimePattern(0);
		Button_return->m_anime->SetAnimePattern(0);
		Button_next->m_anime->SetAnimePattern(1);
		break;
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