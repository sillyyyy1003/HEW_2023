#include "Animation.h"

//----------------------------//
// O[oĎč`
//----------------------------//

Animation::Animation(int splitX, int splitY)
{
    m_split.x = splitX;
    m_split.y = splitY;
}

void Animation::SetSplit(XMINT2 _split)
{
    m_split = _split;
}

DirectX::XMINT2 Animation::GetSplit(void)
{
    return m_split;
}

void Animation::Update()
{
    m_offsetUV.x = 1.0 / m_split.x * m_frameX;
    m_offsetUV.y = 1.0 / m_split.y * m_frameY;
}

void Animation::SetAnimeSpeed(float _speed)
{
    m_animeSpeed = _speed;
}

void Animation::SetAnimePattern(int _animePattern)
{
    m_frameY = _animePattern;
}

DirectX::XMFLOAT2 Animation::GetUVOffset(void)
{
    return m_offsetUV;
}

void Animation::SetFrameX(int _frameX)
{
    Animation::m_frameX = _frameX;
}


