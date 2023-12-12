#include "StaticObject.h"
#include "Sprite.h"
#include "StaticAnimation.h"
#include "TrackCamera.h"

extern Camera* g_WorldCamera;

StaticObject::StaticObject(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY)
{
	//図形初期化
	m_sprite = new Sprite();
	m_sprite->CreateModel(texture, _width, _height, splitX, splitY);

	//アニメーション配置
	m_sprite->m_anime = new StaticAnimation(splitX, splitY);

	//カメラ配置
	m_sprite->m_camera = g_WorldCamera;

}

void StaticObject::Update(void)
{
	//アニメーション更新
	m_sprite->m_anime->Update();

}

void StaticObject::Draw(void)
{

	m_sprite->Draw();
}

StaticObject::~StaticObject(void)
{
	delete m_sprite;

}
