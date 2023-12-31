#include "Object.h"

extern Camera* g_WorldCamera;

Object::Object(void)
{
	//図形初期化
	m_sprite = new Sprite();

	//カメラ初期化
	m_sprite->m_camera = g_WorldCamera;

}

void Object::CreateObject(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY) 
{
	//モデル作成
	m_sprite->CreateModel(texture, _width, _height, splitX, splitY);
}



void Object::Update(void)
{
	//アニメーション更新
	m_sprite->m_anime->Update();

}

void Object::Draw(void)
{
	m_sprite->Draw();
}

Object::~Object(void)
{
	delete m_sprite;
}
