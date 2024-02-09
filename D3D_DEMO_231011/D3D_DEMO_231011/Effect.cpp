#include "Effect.h"
#include "Game.h"
#include "GameObject.h"

extern Camera* g_WorldCamera;

Effect::Effect(int num)
{   
    //�����ŃA�j���[�V�����p�^�[����ύX
    m_frameNum = num;
    animeTable = new int[m_frameNum + 1];

    for (int i = 0; i < m_frameNum; i++) {
        animeTable[i] = i;
    }
  
}

void Effect::SetLoop(bool isLoop) 
{

    this->isLoop = isLoop;     
    
    //�Ō�̈ʒu�t���[���̏���
    if (isLoop) {

        animeTable[m_frameNum] = -1;
    }
    else {
        animeTable[m_frameNum] = -2;
    }
    
}



Effect::~Effect()
{
    delete[] animeTable;
}

void Effect::CreateModel(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY)
{
    //�J�����̎g�p���ւ���
    //isUseCamera = false;

    //���f���쐬
    Sprite::CreateModel(texture, _width, _height, splitX, splitY);

    //�A�j���[�V������z�u
    m_anime = new Animation(splitX, splitY);

    m_camera = g_WorldCamera;
}

void Effect::Update()
{
    //int animeTable[29] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,-1 };

    // �\��������R�}ID���擾
    int animeID = animeTable[(int)m_anime->m_animeCounter];


    if (m_anime->isPlaying)
    {
        // �A�j���[�V�����̃J�E���^�[��i�߂�
        m_anime->m_animeCounter += m_anime->m_animeSpeed;

        //���[�v����ꍇ
        if (animeTable[(int)m_anime->m_animeCounter] == -1)
        {
            m_anime->m_animeCounter = 0.0f;
        }

        //���[�v���Ȃ��ꍇ
        if (animeTable[(int)m_anime->m_animeCounter] == -2) {
            m_anime->isPlaying = false;
            m_anime->m_animeCounter = 0.0f;
            isActive = false;
        }

    }

    //�\��������R�}��UV���v�Z
    m_anime->SetFrameX(animeID % m_split.x);

    //UV���W�X�V
    m_anime->Update();

    //�ʒu���m��
    if (isTrace) {
    
    //
    DirectX::XMFLOAT3 tracePos = { 0,0,0 };
        
        //�ғ����̃I�u�W�F�N�g��T��
        for (auto& element : Game::Get()->GetObjectList()) {

            if (element->GetActive()) {
             
                //�ʒu���l��
                tracePos = element->m_obj->m_sprite->m_pos;
                m_pos = tracePos;
         
                //y���̈ʒu�����炷
                m_pos.y += element->m_obj->GetExtents().y;
                //z���̈ʒu�����炷
                m_pos.z = tracePos.z - 0.1f;
                break;

            }

        }
        
    }



}

void Effect::Draw()
{
    if (Effect::isActive) {

        Sprite::Draw();
        
    }
  
}
