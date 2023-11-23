#include "Camera.h"
//Singleton インスタンス定義
Camera* Camera::m_camera;


DirectX::XMMATRIX Camera::GetMatrixView(void)
{
    return m_MatrixView;
}


void Camera::Update()
{
    //XMLoadFloat3 -> XMFLOAT3をXMVECTORに読み込み
    XMVECTOR eye = DirectX::XMLoadFloat3(&m_CameraPos);
    XMVECTOR focus = DirectX::XMLoadFloat3(&m_FocusPos); 
    XMVECTOR up = DirectX::XMLoadFloat3(&m_UpDir);
    
    //ビュー変換行列を計算
    m_MatrixView = XMMatrixLookAtLH(eye, focus, up);

}

void Camera::SetCameraPos(XMFLOAT3 _cameraPos)
{
    m_CameraPos = _cameraPos;
}

DirectX::XMFLOAT3 Camera::GetCameraPos(void)
{
    return m_CameraPos;
}

void Camera::SetFocusPos(XMFLOAT3 _focusPos)
{
    m_FocusPos = _focusPos;
}

DirectX::XMFLOAT3 Camera::GetFocusPos(void)
{
    return m_FocusPos;
}

void Camera::SetUpDir(XMFLOAT3 _Updir)
{
    m_UpDir = _Updir;
}

DirectX::XMFLOAT3 Camera::GetUpDir(void)
{
    return m_UpDir;
}
