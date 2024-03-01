#include "CanvasUI.h"
#include "StaticAnimation.h"

extern Camera* g_WorldCamera;

CanvasUI::CanvasUI()
{
}

CanvasUI::~CanvasUI()
{
	//animeTableが空になっても問題起こさない
	animeTable.clear();
}


void CanvasUI::CreateModel(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY)
{
	//カメラの使用を禁じる
	isUseCamera = false;

	//モデル作成
	Sprite::CreateModel(texture, _width, _height, splitX, splitY);

	//アニメーションを配置
	m_anime = new Animation(splitX,splitY);

	m_camera = g_WorldCamera;

}

void CanvasUI::Update(void)
{	
	// 表示させるコマIDを取得

	if (isAnimated) {

		int animeID = animeTable[(int)m_anime->m_animeCounter];

		if (m_anime->isPlaying)
		{
			// アニメーションのカウンターを進める
			m_anime->m_animeCounter += m_anime->m_animeSpeed;

			//ループする場合
			if (isLoop) {
				
				if (animeTable[(int)m_anime->m_animeCounter] == -1) {
					m_anime->m_animeCounter = 0.0f;
				}
			
			}//ループしない場合
			else {

				if (animeTable[(int)m_anime->m_animeCounter] == -1) {
					m_anime->m_animeCounter = 0.0f;
					m_anime->isPlaying = false;
					isAnimated = false;
				}
			
			}
		}

		if (isMultiPattern) {
			//表示させるコマのUVを計算
			m_anime->SetFrameX(animeID % m_split.x);
		}
		else {
			//表示させるコマのUVを計算
			m_anime->SetFrameX(animeID % m_split.x);
			m_anime->SetAnimePattern(animeID / m_split.x);
		}

	}



	//UV座標の更新
	m_anime->Update();

}

void CanvasUI::Draw(void)
{
	if (isActive) {
		Sprite::Draw();
	}


}

void CanvasUI::InitAnimation(int num)
{
	//ここでアニメーションパターンを変更
	m_frameNum = num;

	for (int i = 0; i < m_frameNum; i++) {
		animeTable.push_back(i);
	}

	//ループしないように
	animeTable.push_back(-1);
}
