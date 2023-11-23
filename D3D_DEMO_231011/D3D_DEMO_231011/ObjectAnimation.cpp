#include "ObjectAnimation.h"

ObjectAnimation::ObjectAnimation(int splitX, int splitY):Animation(splitX,splitY)
{

}

void ObjectAnimation::Update(void)
{
    //�����ŃA�j���[�V�����p�^�[����ύX
    int animeTable[32] = { 0, 0, 1, 2, 2, 1, -1 };

    // �\��������R�}ID���擾
    int animeID = animeTable[(int)Animation::m_animeCounter];

 
    if (Animation::isPlaying)
    {
        // �A�j���[�V�����̃J�E���^�[��i�߂�
        Animation::m_animeCounter += Animation::m_animeSpeed;

        //���[�v����ꍇ
        if (animeTable[(int)Animation::m_animeCounter] == -1) 
        {
            Animation::m_animeCounter = 0.0f;
        }
        
        //���[�v���Ȃ��ꍇ
        if (animeTable[(int)Animation::m_animeCounter] == -2) {
            isPlaying = false;
            Animation::m_animeCounter = 0.0f;
        }

    }

    //�\��������R�}��UV���v�Z
    m_frameX = animeID % m_split.x;


    //UV���W�X�V
    Animation::Update();


}
