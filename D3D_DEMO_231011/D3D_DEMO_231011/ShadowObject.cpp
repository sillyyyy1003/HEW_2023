#include "ShadowObject.h"
#include "Camera.h"
#include "DInput.h"
#include "CDInput.h"

extern Camera* g_WorldCamera;

ShadowObject::ShadowObject(void)
{
	m_sprite->m_spriteType = Sprite::SHADOW;
}

void ShadowObject::Update(void)
{
	
	//アニメーションの更新
	Object::Update();


}


void ShadowObject::Draw(void)
{
	
	if (isLight) 
	{
		//光があるときだけ描画する
		Object::Draw();
	}

	
}

ShadowObject::~ShadowObject(void)
{

}
