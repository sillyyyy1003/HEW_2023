#include "TrackCamera.h"




void TrackCamera::Update()
{
	DirectX::XMFLOAT3 camPos;
	camPos.x = (m_targetObject->m_sprite->m_pos.x);
	camPos.y = (m_targetObject->m_sprite->m_pos.y);
	camPos.z = (m_targetObject->m_sprite->m_pos.z - 2.0f);	// ‡BŒã‚ë2.0f‚ÉƒJƒƒ‰‚ð’u‚­
	this->SetCameraPos(camPos);


	DirectX::XMFLOAT3 camFocus;
	camFocus = (m_targetObject->m_sprite->m_pos);
	this->SetFocusPos(camFocus);

	Camera::Update();


}

void TrackCamera::SetTarget(Object* _targetObejct)
{
	m_targetObject = _targetObejct;
}
