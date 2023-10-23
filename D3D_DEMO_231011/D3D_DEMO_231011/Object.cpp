#include "Object.h"
#include "ObjectAnimation.h"

extern Camera* g_WorldCamera;

Object::Object(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY) 
{
	//�}�`������
	m_sprite = new Sprite(texture, _width, _height, splitX, splitY);
	
	//�A�j���[�V�����N���X������
	m_anime = new ObjectAnimation(splitX,splitY);
	m_sprite->m_anime = m_anime;

	//�J����������
	m_sprite->m_camera = g_WorldCamera;
}

void Object::Update(void)
{
	m_anime->Update();

}

Object::~Object(void)
{
	delete m_sprite;
	
	//delete m_anime;
}
