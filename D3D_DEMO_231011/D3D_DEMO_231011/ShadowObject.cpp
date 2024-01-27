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
	
	switch (m_size) {
		case IDLE:
			m_sprite->m_scale.x = 1.0f;
			m_sprite->m_scale.y = 1.0f;
			break;

		case SMALL:
			m_sprite->m_scale.x = 1.0f;
			m_sprite->m_scale.y = 1.0f;
			break;

		case MEDIUM:
			m_sprite->m_scale.x = 1.5f;
			m_sprite->m_scale.y = 1.5f;
			break;

		case LARGE:
			m_sprite->m_scale.x = 2.0f;
			m_sprite->m_scale.y = 2.0f;
			break;

	}


	
	//アニメーションの更新
	Object::Update();


}

void ShadowObject::CheckVacancy(void)
{
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
