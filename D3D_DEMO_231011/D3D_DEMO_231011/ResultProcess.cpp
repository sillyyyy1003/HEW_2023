#include "ResultProcess.h"
#include "CanvasUI.h"
#include "Assets.h"
#include "Game.h"
#include "Fade.h"

extern Assets* g_Assets;

ResultProcess::ResultProcess()
{

}

ResultProcess::~ResultProcess()
{
	for (auto& stepnum : StepNum) {
		delete stepnum;
	}
}

void ResultProcess::Init(float posX, float posY, float size, float interval)
{
	m_size = size;

	m_interval = interval;

	//ステップ数の表示のため
	for (auto& stepnum : StepNum) {
		//初期化
		stepnum = new CanvasUI();
		//モデル作成
		stepnum->CreateModel(g_Assets->Result_num, m_size * 74.83, m_size * 110.5, 10, 1);

		stepnum->m_pos.z = m_posz;
	}
	//位置調整
	SetPosition(posX,posY);
}

void ResultProcess::SetPosition(float posX, float posY)
{
	m_sPosX = posX;
	m_sPosY = posY;
}

void ResultProcess::UpdateCharCenter(char* outputChar)
{

	int totalCharacters = strlen(outputChar);
	float totalWidth = totalCharacters * (74 / SCREEN_PARA / 2);

	for (int i = 0; i < totalCharacters; i++)
	{
		// 文字の横番目を取得 SPACE ASCII->32
		int frameX = ((int)outputChar[i] - 32) % 16;
		// オブジェクトにセットする
		StepNum[i]->m_anime->SetFrameX(frameX);

		// 文字の位置を設定する（中央に調整）
		float posX = m_sPosX - totalWidth / 2 + i * (74 / SCREEN_PARA / 2) + m_interval;
		
		StepNum[i]->InitPos(posX, m_sPosY, 0.1);

		// UVOFFSET更新
		StepNum[i]->m_anime->Update();

		if (Game::Get()->GetFade()->m_fadePanel->m_materialDiffuse.w <= 0.01) {
			// 描画
			StepNum[i]->Draw();
		}
	}

}

void ResultProcess::UpdateCharLeft(char* outputChar)
{	
	for (int i = 0; i < strlen(outputChar); i++)
	{
		//文字の横番目を取得 SPACE ASCII->32
		int frameX = ((int)outputChar[i] - 32) % 16;
		//オブジェクトにセットする
		StepNum[i]->m_anime->SetFrameX(frameX);

		//文字の位置を設定する
		float posX = ((74 + m_interval) / SCREEN_PARA)* i;
		StepNum[i]->InitPos(m_sPosX + posX, m_sPosY, 0.1);

		//UVOFFSET更新
		StepNum[i]->m_anime->Update();

		if (Game::Get()->GetFade()->m_fadePanel->m_materialDiffuse.w <= 0.01) {
		//描画
		StepNum[i]->Draw();
		}
	}

}

void ResultProcess::PrintDebugLogCenter(const int _num)
{
	//文字列に転換
	char str[32];
	snprintf(str, 31, "%d", _num);
	//更新と描画
	UpdateCharCenter(str);
}

void ResultProcess::PrintDebugLogLeft(const int _num)
{
	//文字列に転換
	char str[32];
	snprintf(str, 31, "%d", _num);
	//更新と描画
	UpdateCharLeft(str);
}
