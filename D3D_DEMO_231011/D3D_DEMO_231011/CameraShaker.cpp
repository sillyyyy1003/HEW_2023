#include "CameraShaker.h"

#define TOTALTIME 90

extern CameraShaker* shaker;

void CameraShaker::Update(Camera* m_camera)
{
    // �J�����V�F�C�J�[��������
    //InitCameraShaker(0.2f, 5.0f); // ���x: 0.2, ���g��: 5.0;

    if(GetShaker())
    {
        // �J�����V�F�C�J�[���X�V
        ShakerUpdate();

        if (elapsedTime > m_TotalTime)
        {
            // �J���������̈ʒu�ɖ߂�
            m_NewCameraPos = m_OriginalCameraPos;
            m_NewCameraFocus = m_OriginalCameraFocus;
        }

        // �V�����J�����̈ʒu�ƒ����_���擾
        DirectX::XMFLOAT3 newCameraPos = GetNewCameraPos();
        DirectX::XMFLOAT3 newCameraFocus =GetNewCameraFocus();

        // �����ŐV�����J�����̈ʒu�ƒ����_���g�p���ĕ`��Ȃǂ̏������s��
        m_camera->SetCameraPos(newCameraPos);
        m_camera->SetFocusPos(newCameraFocus);
        m_camera->Update();

        if (elapsedTime > m_TotalTime)
        {
            isShake = false;
        }

        // �X�V���Ԃ����Z
        elapsedTime++;

    }
    else
    {
        // �X�V���Ԃ�������
        elapsedTime = 0;
        // �J�����̏����ʒu�ƒ����_��ݒ�
       SetOriginalCameraParams(m_camera->GetCameraPos(), m_camera->GetFocusPos());
    }
}

CameraShaker::CameraShaker()
{
}

CameraShaker::~CameraShaker()
{
    /*delete shaker;*/
}

void CameraShaker::ShakerUpdate()
{
    // �����_���ȕψʂ𐶐�
    DirectX::XMFLOAT3 displacement = RandomDisplacement();

    // �J�����̈ʒu�ƒ����_���X�V
    m_NewCameraPos = DirectX::XMFLOAT3(m_OriginalCameraPos.x + displacement.x,
        m_OriginalCameraPos.y + displacement.y,
        m_OriginalCameraPos.z + displacement.z);
    m_NewCameraFocus = DirectX::XMFLOAT3(m_OriginalCameraFocus.x + displacement.x,
        m_OriginalCameraFocus.y + displacement.y,
        m_OriginalCameraFocus.z + displacement.z);
}
