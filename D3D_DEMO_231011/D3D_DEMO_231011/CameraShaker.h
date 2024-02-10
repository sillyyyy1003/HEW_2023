#pragma once
#include "Camera.h"
#include <DirectXMath.h>
#include <random>

class CameraShaker  {
public:

    void Update(Camera* m_camera);

    CameraShaker();

    ~CameraShaker();

    // カメラを揺らす判定をとる
    bool GetShaker() {
        return isShake;
    }

    // カメラを揺らす判定を設定
    void SetShaker(bool isshaker) {
        isShake = isshaker;
    }

    // 初期化(強度、周波数、継続時間)
    void InitCameraShaker(float intensity, float frequency,float totalTime) {

        m_Intensity = intensity;
        m_Frequency = frequency;
        m_TotalTime = totalTime;
        // 乱数生成器を初期化
        m_RandomEngine.seed(std::random_device()());
    }

    // オリジナルのカメラの位置と注視点を設定するメソッド
    void SetOriginalCameraParams(const DirectX::XMFLOAT3& cameraPos, const DirectX::XMFLOAT3& cameraFocus) {
        m_OriginalCameraPos = cameraPos;
        m_OriginalCameraFocus = cameraFocus;
    }

    // 新しいカメラの位置を取得するメソッド
    DirectX::XMFLOAT3 GetNewCameraPos() const {
        return m_NewCameraPos;
    }

    // 新しいカメラの注視点を取得するメソッド
    DirectX::XMFLOAT3 GetNewCameraFocus() const {
        return m_NewCameraFocus;
    }

private:

    bool isShake = false; // カメラを揺らす判定

    float elapsedTime=0; // カメラが揺れる時間
    float m_Intensity=0; // カメラの揺れの強度
    float m_Frequency=0; // カメラの揺れの周波数
    float m_ShakeTime=0; // 揺れ効果の残り時間
    float m_TotalTime = 0;  


    DirectX::XMFLOAT3 m_OriginalCameraPos; // オリジナルのカメラの位置
    DirectX::XMFLOAT3 m_OriginalCameraFocus; // オリジナルのカメラの注視点

    DirectX::XMFLOAT3 m_NewCameraPos; // 揺れ後の新しいカメラの位置
    DirectX::XMFLOAT3 m_NewCameraFocus; // 揺れ後の新しいカメラの注視点

    std::default_random_engine m_RandomEngine; // 乱数生成器

    // カメラを揺らすメソッド
    void ShakerUpdate();

    // ランダムな変位を生成する関数
    DirectX::XMFLOAT3 RandomDisplacement() {
        std::uniform_real_distribution<float> distribution(-m_Intensity, m_Intensity);
        float dx = distribution(m_RandomEngine);
        float dy = distribution(m_RandomEngine);
        float dz = distribution(m_RandomEngine);
        return DirectX::XMFLOAT3(dx, dy, dz);
    }
};