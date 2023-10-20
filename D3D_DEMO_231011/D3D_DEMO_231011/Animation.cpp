#include "Animation.h"

//----------------------------//
// グローバル変数定義
//----------------------------//


Animation::Animation()
{
    
}

void Animation::SetSplit(XMINT2 _split)
{
    m_split = _split;
}

void Animation::Update()
{
    m_offsetUV.x = 1.0 / m_split.x * m_frameX;
    m_offsetUV.y = 1.0 / m_split.y * m_frameY;
}

void Animation::SetAnimeSpeed(float _speed)
{
    m_AnimeSpeed = _speed;
}

void Animation::SetAnimePattern(int _animePattern)
{
    m_frameY = _animePattern;
}

DirectX::XMFLOAT2 Animation::GetUVOffset(void)
{
    return m_offsetUV;
}


