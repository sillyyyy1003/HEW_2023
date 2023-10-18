#include "Animation.h"

//----------------------------//
// グローバル変数定義
//----------------------------//


Animation::Animation(XMINT2 _split)
{
    m_split = _split;
}

void Animation::Update(int _frameX, int _frameY)
{
    m_offsetUV.x = 1.0 / m_split.x * _frameX;
    m_offsetUV.y = 1.0 / m_split.y * _frameY;
}

void Animation::SetAnimeSpeed(float _speed)
{
    m_AnimeSpeed = _speed;
}

void Animation::SetAnimePattern(int _animePattern)
{
    m_AnimePattern = _animePattern;
}

DirectX::XMFLOAT2 Animation::GetUVOffset(void)
{
    return m_offsetUV;
}


