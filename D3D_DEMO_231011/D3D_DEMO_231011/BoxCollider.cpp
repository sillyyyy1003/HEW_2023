#include "BoxCollider.h"

BoxCollider::BoxCollider()
{
}

void BoxCollider::InitCollider(DirectX::XMFLOAT3 center, DirectX::XMFLOAT3 extents, DirectX::XMFLOAT3 orientation,COLLISION_TYPE _type)
{
    m_boxOrientedCollider.Center = center;
    m_boxOrientedCollider.Extents = extents;
    m_boxOrientedCollider.Orientation = { orientation.x,orientation.y,orientation.z,0.0f };
}

void BoxCollider::UpdateExtents()
{
}

void BoxCollider::UpdatePos()
{
}

void BoxCollider::UpdateRotation()
{
}

void BoxCollider::Update()
{
}

bool BoxCollider::isCollision(const SphereCollider& sphereCollider)
{
    return false;
}

bool BoxCollider::isCollision(const BoxCollider& boxCollider)
{
    return false;
}
