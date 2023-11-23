#include "ShadowObject.h"
#include "Camera.h"

extern Camera* g_WorldCamera;
ShadowObject::ShadowObject(void)
{
	m_obj = new Sprite();

	m_obj->m_camera = g_WorldCamera;
}

void ShadowObject::CreateShadow(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY)
{
	m_obj->CreateModel(texture, _width, _height, splitX, splitY);
}

void ShadowObject::Update(void)
{
	//�A�j���[�V�����̍X�V
	m_obj->m_anime->Update();
}

BOOL ShadowObject::CheckShadow(void)
{
	return 0;
}

void ShadowObject::Draw(void)
{
	//��������Ƃ������`�悷��
	m_obj->Draw();
	

}

ShadowObject::~ShadowObject(void)
{
	delete m_obj;
}
