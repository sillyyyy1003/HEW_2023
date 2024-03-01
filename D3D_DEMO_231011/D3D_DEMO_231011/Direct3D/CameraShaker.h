#pragma once
#include "Camera.h"
#include <DirectXMath.h>
#include <random>

class CameraShaker  {
public:

    void Update(Camera* m_camera);

    CameraShaker();

    ~CameraShaker();

    // �J������h�炷������Ƃ�
    bool GetShaker() {
        return isShake;
    }

    // �J������h�炷�����ݒ�
    void SetShaker(bool isshaker) {
        isShake = isshaker;
    }

    // ������(���x�A���g���A�p������)
    void InitCameraShaker(float intensity, float frequency,float totalTime) {

        m_Intensity = intensity;
        m_Frequency = frequency;
        m_TotalTime = totalTime;
        // �����������������
        m_RandomEngine.seed(std::random_device()());
    }

    // �I���W�i���̃J�����̈ʒu�ƒ����_��ݒ肷�郁�\�b�h
    void SetOriginalCameraParams(const DirectX::XMFLOAT3& cameraPos, const DirectX::XMFLOAT3& cameraFocus) {
        m_OriginalCameraPos = cameraPos;
        m_OriginalCameraFocus = cameraFocus;
    }

    // �V�����J�����̈ʒu���擾���郁�\�b�h
    DirectX::XMFLOAT3 GetNewCameraPos() const {
        return m_NewCameraPos;
    }

    // �V�����J�����̒����_���擾���郁�\�b�h
    DirectX::XMFLOAT3 GetNewCameraFocus() const {
        return m_NewCameraFocus;
    }

private:

    bool isShake = false; // �J������h�炷����

    float elapsedTime=0; // �J�������h��鎞��
    float m_Intensity=0; // �J�����̗h��̋��x
    float m_Frequency=0; // �J�����̗h��̎��g��
    float m_ShakeTime=0; // �h����ʂ̎c�莞��
    float m_TotalTime = 0;  


    DirectX::XMFLOAT3 m_OriginalCameraPos; // �I���W�i���̃J�����̈ʒu
    DirectX::XMFLOAT3 m_OriginalCameraFocus; // �I���W�i���̃J�����̒����_

    DirectX::XMFLOAT3 m_NewCameraPos; // �h���̐V�����J�����̈ʒu
    DirectX::XMFLOAT3 m_NewCameraFocus; // �h���̐V�����J�����̒����_

    std::default_random_engine m_RandomEngine; // ����������

    // �J������h�炷���\�b�h
    void ShakerUpdate();

    // �����_���ȕψʂ𐶐�����֐�
    DirectX::XMFLOAT3 RandomDisplacement() {
        std::uniform_real_distribution<float> distribution(-m_Intensity, m_Intensity);
        float dx = distribution(m_RandomEngine);
        float dy = distribution(m_RandomEngine);
        float dz = distribution(m_RandomEngine);
        return DirectX::XMFLOAT3(dx, dy, dz);
    }
};