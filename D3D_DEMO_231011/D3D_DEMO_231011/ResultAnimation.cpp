#include "ResultAnimation.h"
#include "CanvasUI.h"
#include "Assets.h"
#include "DInput.h"
#include "SceneManager.h"

extern Assets* g_Assets;
extern ResultAnimation* g_ResultAnimation = new ResultAnimation();

ResultAnimation::ResultAnimation()
{

}

ResultAnimation::~ResultAnimation()
{
	delete clear1_1_1;
	delete clear1_1_2;
	delete clear1_1_3;
}

void ResultAnimation::Init()
{
	clear1_1_1 = new CanvasUI();
	clear1_1_2 = new CanvasUI();
	clear1_1_3 = new CanvasUI();

	//テクスチャ読み込み・モデル作成
	clear1_1_1->CreateModel(g_Assets->clear1_1_1, 485, 319, 1, 1);
	clear1_1_2->CreateModel(g_Assets->clear1_1_2, 483, 316, 1, 1);
	clear1_1_3->CreateModel(g_Assets->clear1_1_3, 538 / 1.1, 692/1.05, 1, 1);

	// 画像１〜３の移動前の初期位置
	clear1_1_1->m_pos = { -3.3f,6.6f,0.3f };
	clear1_1_2->m_pos = { -11.3f,-2.1f,0.3f };
	clear1_1_3->m_pos = { 11.1f,0.0f,0.3f };

	// 画像１〜３の移動後の位置
	//clear1_1_1->m_pos = { -3.3f,2.1f,0.3f };
	//clear1_1_2->m_pos = { -3.3f,-2.1f,0.3f };
	//clear1_1_3->m_pos = { 3.1f,0.0f,0.3f };
}

void ResultAnimation::Update()
{
	if (SceneManager::Get()->m_stageHolder[SceneManager::Get()->GetActiveStage()]->GetClear())
	{
		// 画像の移動が完了したか、一度クリアしたステージかで判定
		if (Move() || SceneManager::Get()->m_stageHolder[SceneManager::Get()->GetActiveStage()]->GetCompleted())
		{
			// スペースを押すとリザルト画面に遷移する
			if (Input::Get()->GetKeyPress(DIK_SPACE))
			{
				// 画像１から３の位置を初期値（画面外）に戻す
				clear1_1_1->m_pos = { -3.3f,6.6f,0.3f };
				clear1_1_2->m_pos = { -11.3f,-2.1f,0.3f };
				clear1_1_3->m_pos = { 11.1f,0.0f,0.3f };

				// ステージを一度クリアした判定にする
				SceneManager::Get()->m_stageHolder[SceneManager::Get()->GetActiveStage()]->SetCompleted(true);

				// リザルトに遷移する
				SceneManager::Get()->SetScene(SCENENAME::RESULT);
			}
		}

		clear1_1_1->Update();
		clear1_1_2->Update();
		clear1_1_3->Update();
	}
}

void ResultAnimation::Draw()
{
	if (SceneManager::Get()->m_stageHolder[SceneManager::Get()->GetActiveStage()]->GetClear())
	{
		clear1_1_1->Draw();
		clear1_1_2->Draw();
		clear1_1_3->Draw();
	}
}

bool ResultAnimation::Move()
{
	// 画像１〜３を順番に移動するようにさせる
	// 画像１が上から下に降りてくる
	clear1_1_1->m_pos.y -= 0.1f;

	if (clear1_1_1->m_pos.y < 2.1f)
	{
		// 画像１を指定の位置に止める
		clear1_1_1->m_pos.y = 2.1f;

		// 画像２を左から右に移動させる
		clear1_1_2->m_pos.x += 0.1f;

		if (clear1_1_2->m_pos.x > -3.3f)
		{
			// 画像２を指定の位置に止める
			clear1_1_2->m_pos.x = -3.3f;

			// 画像３を右から左へ移動させる
			clear1_1_3->m_pos.x -= 0.1f;

			if (clear1_1_3->m_pos.x < 3.1f)
			{
				// 画像３を指定の位置に止める
				clear1_1_3->m_pos.x = 3.1f;

				// 画像の移動が完了
				return true;
			}

		}
	}

	// 画像の移動が途中
	return false;
}
