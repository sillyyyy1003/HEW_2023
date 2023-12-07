#include "TrackCamera.h"

void TrackCamera::Update()
{
	if (m_targetObject != nullptr) //追跡する場合
	{
		////カメラの位置を更新
		//DirectX::XMFLOAT3 camPos;
		//camPos.x = (m_targetObject->m_sprite->m_pos.x);
		//camPos.y = (m_targetObject->m_sprite->m_pos.y);
		//camPos.z = (m_targetObject->m_sprite->m_pos.z - 2.0f);	// ③後ろ2.0fにカメラを置く
		//this->SetCameraPos(camPos);

		////
		//DirectX::XMFLOAT3 camFocus;
		//camFocus = (m_targetObject->m_sprite->m_pos);
		//this->SetFocusPos(camFocus);

		
		float angle = m_targetObject->m_sprite->m_rotation.x;




	}
	
	
	
	Camera::Update();

}

void TrackCamera::SetTarget(Object* _targetObejct)
{
	m_targetObject = _targetObejct;
}
