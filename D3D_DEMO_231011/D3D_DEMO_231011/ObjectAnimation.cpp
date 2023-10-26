#include "ObjectAnimation.h"

ObjectAnimation::ObjectAnimation(int splitX, int splitY):Animation(splitX,splitY)
{

}

void ObjectAnimation::Update(void)
{
    //ここでアニメーションパターンを変更
    int animeTable[][32] =
    {
        // 0 何もアニメーションしないパターン
       {0,-1},// -1が来たら最初に戻る
        // 1 下向き
       { 0, 0, 1, 2, 2, 1, -1 },
       // 2 左向き
       { 3, 3, 4, 5, 5, 4, -1 },
       // 3 右向き
       { 6, 6, 7, 8, 8, 7, -1 },
       // 4 上向き
       { 9, 9, 10, 11, 11, 10, -1 },

    };

    int animeID = animeTable[Animation::m_frameY][(int)Animation::m_animeCounter];

    if (Animation::isPlaying) 
    {
        Animation::m_animeCounter += Animation::m_animeSpeed;

        if (animeID == -1) {

            Animation::m_animeCounter = 0.0f;
        }

    }

    //縦横マス更新
    m_frameX = animeID % m_split.x;

    Animation::Update();

}
