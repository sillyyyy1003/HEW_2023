#include "ObjectAnimation.h"

ObjectAnimation::ObjectAnimation(int splitX, int splitY):Animation(splitX,splitY)
{

}

ObjectAnimation::~ObjectAnimation()
{	
	//animeTableが空になっても問題起こさない
	animeTable.clear();
}

void ObjectAnimation::Update(void)
{
	// 表示させるコマIDを取得
	int animeID = 0;
	if (animeTable.size() != 0) {//アニメを設定する場合

		animeID = animeTable[(int)m_animeCounter];
		
		if (isPlaying)
		{
			// アニメーションのカウンターを進める
			m_animeCounter += m_animeSpeed;

			//ループする場合
			if (isLoop) {
				//最後のフレームにいったら
				if (animeTable[(int)m_animeCounter] == -1) {
					m_animeCounter = 0.0f;
				}

			}//ループしない場合
			else {
				//最後のフレームにいったら
				if (animeTable[(int)m_animeCounter] == -1) {
					m_animeCounter = 0.0f;
					isPlaying = false;
				}
			}

			//毎行違うアニメションパターンある場合
			if (isMultiPattern) {
				//表示させるコマのUVを計算
				SetFrameX(animeID % m_split.x);
			}//一種類野アニメションパターンしかない
			else {
				//表示させるコマのUVを計算
				SetFrameX(animeID % m_split.x);
				SetAnimePattern(animeID / m_split.x);
			}
		}
	}
	

    //UV座標更新
    Animation::Update();
}

void ObjectAnimation::InitAnimation(int num)
{
    //ここでアニメーションパターンを変更
    m_frameNum = num;

    for (int i = 0; i < m_frameNum; i++) {
        animeTable.push_back(i);
    }

    //ループしないように
    animeTable.push_back(-1);
}

