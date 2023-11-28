#include "ObjectAnimation.h"

ObjectAnimation::ObjectAnimation(int splitX, int splitY):Animation(splitX,splitY)
{

}

void ObjectAnimation::Update(void)
{
    //ここでアニメーションパターンを変更
    int animeTable[32] = { 0, 0, 1, 2, 2, 1, -1 };

    // 表示させるコマIDを取得
    int animeID = animeTable[(int)Animation::m_animeCounter];

 
    if (Animation::isPlaying)
    {
        // アニメーションのカウンターを進める
        Animation::m_animeCounter += Animation::m_animeSpeed;

        //ループする場合
        if (animeTable[(int)Animation::m_animeCounter] == -1) 
        {
            Animation::m_animeCounter = 0.0f;
        }
        
        //ループしない場合
        if (animeTable[(int)Animation::m_animeCounter] == -2) {
            isPlaying = false;
            Animation::m_animeCounter = 0.0f;
        }

    }

    //表示させるコマのUVを計算
    m_frameX = animeID % m_split.x;


    //UV座標更新
    Animation::Update();


}
