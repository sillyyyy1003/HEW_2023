#include "Collider.h"


Collider::Collider()
{
}

void Collider::InitCollider(COLLISION_TYPE _type)
{
	m_collisionType = _type;
	isActive = true;
}

void Collider::Update()
{
	

}

Collider::~Collider(void)
{
}
