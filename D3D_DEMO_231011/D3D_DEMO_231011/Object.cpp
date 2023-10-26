#include "Object.h"

extern Camera* g_WorldCamera;

Object::Object(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY) 
{
	//図形初期化
	m_sprite = new Sprite(texture, _width, _height, splitX, splitY);
	
	//カメラ初期化
	m_sprite->m_camera = g_WorldCamera;
}

void Object::Update(void)
{
	m_sprite->m_anime->Update();

}

Object::~Object(void)
{
	delete m_sprite;
	
	//delete m_anime;
}
