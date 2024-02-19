#include "StaticAnimation.h"

StaticAnimation::StaticAnimation(int splitX, int splitY) :Animation(splitX, splitY)
{
	int num = splitX * splitY;

	//アニメショの配列
	for (int i = 0; i < num; i++) {
		animeTable.push_back(i);
	}

	//配列の最後
	animeTable.push_back(-1);



}

void StaticAnimation::Update(void)
{

	int animeID = animeTable[(int)m_animeCounter];

	if (isPlaying)
	{
		// アニメーションのカウンターを進める
		m_animeCounter += m_animeSpeed;

		//ループする場合
		if (isLoop) {

			if (animeTable[(int)m_animeCounter] == -1) {
				m_animeCounter = 0.0f;
			}

		}//ループしない場合
		else {

			if (animeTable[(int)m_animeCounter] == -1) {
				m_animeCounter = 0.0f;
				isPlaying = false;
			}

		}
	}
	
	SetFrameX(animeID % m_split.x);

	Animation::Update();
}
