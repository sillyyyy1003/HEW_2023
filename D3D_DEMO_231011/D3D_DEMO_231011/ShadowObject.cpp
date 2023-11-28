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
	//アニメーションの更新
	m_obj->m_anime->Update();
}

BOOL ShadowObject::CheckShadow(void)
{
	return 0;
}

void ShadowObject::Draw(void)
{
	//光があるときだけ描画する
	m_obj->Draw();
	

}

ShadowObject::~ShadowObject(void)
{
	delete m_obj;
}
