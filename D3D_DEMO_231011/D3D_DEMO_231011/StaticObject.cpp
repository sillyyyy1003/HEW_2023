#include "StaticObject.h"
#include "StaticAnimation.h"
#include "TrackCamera.h"

extern Camera* g_WorldCamera;

StaticObject::StaticObject(void)
{
	
}

void StaticObject::CreateObject(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY)
{
	//モデル作成
	Object::CreateObject(texture, _width, _height, splitX, splitY);
	//アニメション配置
	m_sprite->m_anime = new StaticAnimation(splitX, splitY);
}

void StaticObject::Update(void)
{
	
	//アニメーション更新
	Object::Update();

}

void StaticObject::Draw(void)
{
	Object::Draw();
}

StaticObject::~StaticObject(void)
{
}
