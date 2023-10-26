#include "ObjectAnimation.h"

ObjectAnimation::ObjectAnimation(int splitX, int splitY):Animation(splitX,splitY)
{

}

void ObjectAnimation::Update(void)
{
    //�����ŃA�j���[�V�����p�^�[����ύX
    int animeTable[][32] =
    {
        // 0 �����A�j���[�V�������Ȃ��p�^�[��
       {0,-1},// -1��������ŏ��ɖ߂�
        // 1 ������
       { 0, 0, 1, 2, 2, 1, -1 },
       // 2 ������
       { 3, 3, 4, 5, 5, 4, -1 },
       // 3 �E����
       { 6, 6, 7, 8, 8, 7, -1 },
       // 4 �����
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

    //�c���}�X�X�V
    m_frameX = animeID % m_split.x;

    Animation::Update();

}
