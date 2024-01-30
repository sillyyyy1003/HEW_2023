#include "Collider.h"


Collider::Collider()
{
}

std::vector<Vector3> Collider::GetVerticies()
{
	return std::vector<Vector3>();
}

void Collider::InitCollider(COLLISION_TYPE _type)
{
	m_collisionType = _type;
	isActive = true;
}

void Collider::Update(DirectX::XMFLOAT3 m_center, DirectX::XMFLOAT3 m_rotation)
{
	

}

Collider::~Collider(void)
{
}
