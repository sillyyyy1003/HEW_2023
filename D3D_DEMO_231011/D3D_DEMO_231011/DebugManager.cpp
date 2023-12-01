#include "DebugManager.h"
#include "Assets.h"



DebugManager::DebugManager()
{
	for (auto& pASCII : m_debugASCII) {
		//初期化
		pASCII = new CanvasUI();
		//モデル作成
		pASCII->CreateModel(Assets::debugFont,20.0f, 20.0f, 12, 8);
	}
}


DebugManager::~DebugManager()
{
	for (auto& pASCII : m_debugASCII) {
		delete pASCII;
	}
}

void DebugManager::UpdateChar(char* outputChar)
{
	for (int i = 0; i < strlen(outputChar); i++) 
	{
		//文字の横番目を取得 SPACE ASCII->32
		int frameX = ((int)outputChar[i] - 32) % 12;
		//オブジェクトにセットする
		m_debugASCII[i]->m_anime->SetFrameX(frameX);

		//文字の縦番目を取得
		int frameY = ((int)outputChar[i] - 32) / 12;
		m_debugASCII[i]->m_anime->SetAnimePattern(frameY);

		//文字の位置を設定する
		float posX = 20.0f / SCREEN_PARA * i;
		m_debugASCII[i]->InitPos(m_sPosX + posX, m_sPosY, 0.1);

		//UVOFFSET更新
		m_debugASCII[i]->m_anime->Update();


		//描画
		m_debugASCII[i]->Draw();

	}



}

void DebugManager::SetPosition(float posX, float posY)
{
	m_sPosX = posX;
	m_sPosY = posY;
}

void DebugManager::PrintDebugLog(float _posX, float _posY, const char* word)
{
	//文字列に転換
	char str[256];
	snprintf(str, 255, "%s", word);
	//スタート位置を設定
	SetPosition(_posX, _posY);
	//更新と描画
	UpdateChar(str);
}

void DebugManager::PrintDebugLog(float _posX, float _posY, const float _num)
{
	//文字列に転換
	char str[32];
	snprintf(str, 31, "%f", _num);
	//スタート位置を設定
	SetPosition(_posX, _posY);
	//更新と描画
	UpdateChar(str);
}

void DebugManager::PrintDebugLog(float _posX, float _posY, const int _num)
{
	//文字列に転換
	char str[32];
	snprintf(str, 31, "%d", _num);
	//スタート位置を設定
	SetPosition(_posX, _posY);
	//更新と描画
	UpdateChar(str);
}
