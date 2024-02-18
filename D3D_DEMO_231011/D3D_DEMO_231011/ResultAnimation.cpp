#include "ResultAnimation.h"
#include "Assets.h"
#include "DInput.h"
#include "SceneManager.h"
#include "Game.h"

extern Assets* g_Assets;

ResultAnimation::ResultAnimation()
{

}

ResultAnimation::~ResultAnimation()
{
	delete clear1;
	delete clear2;
	delete clear3;
}

void ResultAnimation::SetTexture(ID3D11ShaderResourceView* texture_clear1, ID3D11ShaderResourceView* texture_clear2, ID3D11ShaderResourceView* texture_clear3)
{
	clear1->SetTexture(texture_clear1);
	clear2->SetTexture(texture_clear2);
	clear3->SetTexture(texture_clear3);
}

void ResultAnimation::Init()
{
	clear1 = new CanvasUI();
	clear2 = new CanvasUI();
	clear3 = new CanvasUI();

	//テクスチャ読み込み・モデル作成
	clear1->CreateModel(g_Assets->resultComic1_1_1, 650, 476, 1, 1);
	clear2->CreateModel(g_Assets->resultComic1_1_2, 707, 503, 1, 1);
	clear3->CreateModel(g_Assets->resultComic1_1_3, 502, 642, 1, 1);

	// 画像１～３の移動前の初期位置
	clear1->m_pos = { -3.3f,6.6f,0.3f };
	clear2->m_pos = { -11.3f,-2.1f,0.3f };
	clear3->m_pos = { 11.1f,0.0f,0.3f };
}

void ResultAnimation::Update()
{
	if (SceneManager::Get()->m_stageHolder[SceneManager::Get()->GetStage()]->GetClear())
	{
		// 画像の移動が完了したか、一度クリアしたステージかで判定
		if (Move() || SceneManager::Get()->m_stageHolder[SceneManager::Get()->GetStage()]->GetCompleted())
		{
			// スペースを押すとリザルト画面に遷移する
			if (Input::Get()->GetKeyTrigger(DIK_SPACE))
			{
				// 画像１から３の位置を初期値（画面外）に戻す
				clear1->m_pos = { -3.3f,6.6f,0.3f };
				clear2->m_pos = { -11.3f,-2.1f,0.3f };
				clear3->m_pos = { 11.1f,0.0f,0.3f };

				// ステージを一度クリアした判定にする
				SceneManager::Get()->m_stageHolder[SceneManager::Get()->GetStage()]->SetCompleted(true);
				Game::Get()->SetResultAnime(false);
			}
		}

		clear1->Update();
		clear2->Update();
		clear3->Update();
	}
}

void ResultAnimation::Draw()
{

	if (SceneManager::Get()->m_stageHolder[SceneManager::Get()->GetActiveStage()]->GetClear())
	{
		clear1->Draw();
		clear2->Draw();
		clear3->Draw();
	}

}

bool ResultAnimation::Move()
{
	// 画像１～３を順番に移動するようにさせる
	// 画像３が上から下に降りてくる
	clear3->m_pos.x -= 0.1f;

	if (clear3->m_pos.x < 3.1f)
	{
		// 画像３を指定の位置に止める
		clear3->m_pos.x = 3.1f;

		// 画像1を左から右に移動させる
		clear1->m_pos.y -= 0.1f;

		if (clear1->m_pos.y < 2.1f)
		{
			// 画像１を指定の位置に止める
			clear1->m_pos.y = 2.1f;

			// 画像２を左から右に移動させる
			clear2->m_pos.x += 0.15f;

			if (clear2->m_pos.x > -3.3f)
			{
				// 画像２を指定の位置に止める
				clear2->m_pos.x = -3.3f;

				// 画像の移動が完了
				return true;
			}

		}
	}

	// 画像の移動が途中
	return false;
}
