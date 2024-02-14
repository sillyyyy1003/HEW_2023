#include "ResultProcess.h"
#include "CanvasUI.h"
#include "Assets.h"

extern Assets* g_Assets;
extern ResultProcess* g_resultprocess = new ResultProcess;

ResultProcess::ResultProcess()
{

}

ResultProcess::~ResultProcess()
{
	for (auto& stepnum : StepNum) {
		delete stepnum;
	}
	delete[] StepNum;
}

void ResultProcess::Init(float posX, float posY)
{
	//ステップ数の表示のため
	for (auto& stepnum : StepNum) {
		//初期化
		stepnum = new CanvasUI();
		//モデル作成
		//stepnum->CreateModel(Assets::debugFont, 60.0f, 80.0f, 12, 8);
		stepnum->CreateModel(g_Assets->Result_num, 5238 / 70, 1105 / 10, 10, 1);
	}
	//位置調整
	SetPosition(posX,posY);
}

void ResultProcess::SetPosition(float posX, float posY)
{
	m_sPosX = posX;
	m_sPosY = posY;
}

void ResultProcess::UpdateChar(char* outputChar)
{
	for (int i = 0; i < strlen(outputChar); i++)
	{
		//文字の横番目を取得 SPACE ASCII->32
		int frameX = ((int)outputChar[i] - 32) % 16;
		//オブジェクトにセットする
		StepNum[i]->m_anime->SetFrameX(frameX);

		////文字の縦番目を取得
		//int frameY = ((int)outputChar[i] - 32) / 12;
		//StepNum[i]->m_anime->SetAnimePattern(frameY);

		//文字の位置を設定する
		float posX = 20.0f / SCREEN_PARA * 4 * i;
		StepNum[i]->InitPos(m_sPosX + posX, m_sPosY, 0.1);

		//UVOFFSET更新
		StepNum[i]->m_anime->Update();

		//描画
		StepNum[i]->Draw();

	}
}

void ResultProcess::PrintDebugLog(const int _num)
{
	//文字列に転換
	char str[32];
	snprintf(str, 31, "%d", _num);
	//更新と描画
	UpdateChar(str);
}
