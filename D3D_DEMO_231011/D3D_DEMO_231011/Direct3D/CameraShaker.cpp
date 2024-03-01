#include "CameraShaker.h"

#define TOTALTIME 90

extern CameraShaker* shaker;

void CameraShaker::Update(Camera* m_camera)
{
    // カメラシェイカーを初期化
    //InitCameraShaker(0.2f, 5.0f); // 強度: 0.2, 周波数: 5.0;

    if(GetShaker())
    {
        // カメラシェイカーを更新
        ShakerUpdate();

        if (elapsedTime > m_TotalTime)
        {
            // カメラを元の位置に戻す
            m_NewCameraPos = m_OriginalCameraPos;
            m_NewCameraFocus = m_OriginalCameraFocus;
        }

        // 新しいカメラの位置と注視点を取得
        DirectX::XMFLOAT3 newCameraPos = GetNewCameraPos();
        DirectX::XMFLOAT3 newCameraFocus =GetNewCameraFocus();

        // ここで新しいカメラの位置と注視点を使用して描画などの処理を行う
        m_camera->SetCameraPos(newCameraPos);
        m_camera->SetFocusPos(newCameraFocus);
        m_camera->Update();

        if (elapsedTime > m_TotalTime)
        {
            isShake = false;
        }

        // 更新時間を加算
        elapsedTime++;

    }
    else
    {
        // 更新時間を初期化
        elapsedTime = 0;
        // カメラの初期位置と注視点を設定
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
    // ランダムな変位を生成
    DirectX::XMFLOAT3 displacement = RandomDisplacement();

    // カメラの位置と注視点を更新
    m_NewCameraPos = DirectX::XMFLOAT3(m_OriginalCameraPos.x + displacement.x,
        m_OriginalCameraPos.y + displacement.y,
        m_OriginalCameraPos.z + displacement.z);
    m_NewCameraFocus = DirectX::XMFLOAT3(m_OriginalCameraFocus.x + displacement.x,
        m_OriginalCameraFocus.y + displacement.y,
        m_OriginalCameraFocus.z + displacement.z);
}
