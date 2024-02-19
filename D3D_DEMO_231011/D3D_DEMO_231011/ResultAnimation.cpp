#include "ResultAnimation.h"
#include "Assets.h"
#include "DInput.h"
#include "SceneManager.h"
#include "Game.h"

extern Assets* g_Assets;

//画像が止まってから次の画像をが来るまでの待機時間
#define WAITLIMITE 90
//画像の回転回数(定位置につくまでに何回転させるか）//２回転
#define ROTATETIME 2
//画像の動く速度
#define MOVESPEED 1.4

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

	skip = new CanvasUI();

	//テクスチャ読み込み・モデル作成
	clear1->CreateModel(g_Assets->resultComic1_1_1, 650, 476, 1, 1);
	clear2->CreateModel(g_Assets->resultComic1_1_2, 707, 503, 1, 1);
	clear3->CreateModel(g_Assets->resultComic1_1_3, 502, 642, 1, 1);

	skip->CreateModel(g_Assets->Button_skip, 892/4, 265/4, 1, 1);

	// 画像１～３の移動前の初期位置
	clear1->m_pos = { 12.0f,7.6f,0.4f };   //右上　z座標　真ん中 
	clear2->m_pos = { -12.1f,7.6f,0.3f };  //左上　z座標　手前
	clear3->m_pos = { 0.0f,-8.6f,0.5f };   //下　　z座標　奥

	skip->m_pos = { 6.53f,3.97f,0.3f }; //スキップボタン
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
				clear1->m_pos = { 12.0f,7.6f,0.4f };   //右上　z座標　真ん中 
				clear2->m_pos = { -12.1f,7.6f,0.3f };  //左上　z座標　手前
				clear3->m_pos = { 0.0f,-8.6f,0.5f };   //下　　z座標　奥
				clear1->m_rotation.z = 0.0f; // 回転角度をリセット
				clear2->m_rotation.z = 0.0f; // 回転角度をリセット
				clear3->m_rotation.z = 0.0f; // 回転角度をリセット
				waitcount2 = 0; //カウントリセット
				waitcount = 0; //カウントリセット

				// ステージを一度クリアした判定にする
				SceneManager::Get()->m_stageHolder[SceneManager::Get()->GetStage()]->SetCompleted(true);
				Game::Get()->SetResultAnime(false);
			}
		}

		clear1->Update();
		clear2->Update();
		clear3->Update();
		skip->Update();
	}
}

void ResultAnimation::Draw()
{

	if (SceneManager::Get()->m_stageHolder[SceneManager::Get()->GetActiveStage()]->GetClear())
	{
		// 一度クリアしていた場合右上にスキップと表示する
		if (SceneManager::Get()->m_stageHolder[SceneManager::Get()->GetStage()]->GetCompleted())
		{
			skip->Draw();
		}

		clear3->Draw();
		clear1->Draw();
		clear2->Draw();
	}

}

bool ResultAnimation::Move()
{
	// 画像１～３を順番に移動するようにさせる
	
	// 画像3を下から真ん中に移動させる
	// clear3だけ動く距離が違うために調整する
	clear3->m_pos.y += 0.1f * (MOVESPEED*1.1f);

	// 画像が定位置につくまでに一周するように計算する（ROTATETIMEで回転数を調整）
	clear3->m_rotation.z += 360/(86/ (MOVESPEED * 1.1f) / ROTATETIME); // 回転速度（度）

	if (clear3->m_pos.y > 0.0f)
	{
		// 画像3を指定の位置に止める
		clear3->m_pos.y = 0.0f;
		clear3->m_rotation.z = 0.0f; // 回転角度をリセット

		// カウント開始
		waitcount++;

		if (waitcount > WAITLIMITE)
		{
			// 画像1が右上から真ん中に降りてくる
			clear1->m_pos.x -= 0.157f * MOVESPEED;
			clear1->m_pos.y -= 0.1f * MOVESPEED;

			// 画像をZ軸を中心に回転させる
			clear1->m_rotation.z += 360 / (76 / MOVESPEED / ROTATETIME); // 回転速度（度）

			if (clear1->m_pos.y < 0.0f)
			{
				// 画像1を指定の位置に止める
				clear1->m_pos.x = 0.0f;
				clear1->m_pos.y = 0.0f;
				clear1->m_rotation.z = 0.0f; // 回転角度をリセット

				// カウント開始
				waitcount2++;

				if (waitcount2 > WAITLIMITE)
				{
					// 画像2を左上から真ん中に移動させる
					clear2->m_pos.x += 0.157f * MOVESPEED;
					clear2->m_pos.y -= 0.1f * MOVESPEED;
					clear2->m_rotation.z += 360 / (76 / MOVESPEED / ROTATETIME); // 回転速度（度）

					if (clear2->m_pos.y < 0.0f)
					{
						// 画像2を指定の位置に止める
						clear2->m_pos.x = 0.0f;
						clear2->m_pos.y = 0.0f;
						clear2->m_rotation.z = 0.0f; // 回転角度をリセット

						// 画像の移動が完了
						return true;
					}
				}
			}
		}
	}


	// 画像の移動が途中
	return false;
}
