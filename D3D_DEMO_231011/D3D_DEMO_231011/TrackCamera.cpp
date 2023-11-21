#include "TrackCamera.h"
#include "KBInput.h"


extern KBInput* g_KbInput;

void TrackCamera::Update()
{
	if (m_targetObject != nullptr) //�ǐՂ���ꍇ
	{
		//�J�����̈ʒu���X�V
		DirectX::XMFLOAT3 camPos;
		camPos.x = (m_targetObject->m_sprite->m_pos.x);
		camPos.y = (m_targetObject->m_sprite->m_pos.y);
		camPos.z = (m_targetObject->m_sprite->m_pos.z - 2.0f);	// �B���2.0f�ɃJ������u��
		this->SetCameraPos(camPos);

		//
		DirectX::XMFLOAT3 camFocus;
		camFocus = (m_targetObject->m_sprite->m_pos);
		this->SetFocusPos(camFocus);
	}
	
	

	/*
	*if (g_KbInput->GetKeyPress(VK_UP)) 
	{
		m_CameraPos.z += 0.05f;
	}

	if (g_KbInput->GetKeyPress(VK_DOWN)) {

		m_CameraPos.z -= 0.05f;
	}
	if (g_KbInput->GetKeyPress(VK_LEFT))
	{
		m_CameraPos.y += 0.01f;
	}

	if (g_KbInput->GetKeyPress(VK_RIGHT)) {
		m_CameraPos.y -= 0.01f;
	}


	if (g_KbInput->GetKeyPress(VK_F1)) {
		m_FocusPos.y += 0.01f;
	}

	if (g_KbInput->GetKeyPress(VK_F2)) {
		m_FocusPos.y -= 0.01f;
	}

	if (g_KbInput->GetKeyPress(VK_F3)) {
		m_FocusPos.z += 0.01f;
	}

	if (g_KbInput->GetKeyPress(VK_F4)) {
		m_FocusPos.z -= 0.01f;
	}

*/


	//RESET THE CAMERA
	if (g_KbInput->GetKeyTrigger(VK_RETURN)) 
	{
		//�J�����̈ʒu
		m_CameraPos = XMFLOAT3(0.0f, 0.0f, -7.0f);
		//�����_
		m_FocusPos = XMFLOAT3(0.0f, 0.0f, 2.0f);
	}

	
	Camera::Update();

}

void TrackCamera::SetTarget(Object* _targetObejct)
{
	m_targetObject = _targetObejct;
}
