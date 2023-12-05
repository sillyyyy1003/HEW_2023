#include "Object.h"
#include "KBInput.h"

extern Camera* g_WorldCamera;
extern KBInput* g_KbInput;

Object::Object(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY)
{
	//図形初期化
	m_sprite = new Sprite();
	m_sprite->CreateModel(texture, _width, _height, splitX, splitY);

	//カメラ初期化
	m_sprite->m_camera = g_WorldCamera;
}

void Object::Update(void)
{
	//入力
	
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
