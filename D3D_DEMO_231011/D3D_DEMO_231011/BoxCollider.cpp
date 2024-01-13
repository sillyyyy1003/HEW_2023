#include "BoxCollider.h"

BoxCollider::BoxCollider()
{
}

void BoxCollider::InitCollider(DirectX::XMFLOAT3 center, DirectX::XMFLOAT3 extents, DirectX::XMFLOAT3 orientation,COLLISION_TYPE _type)
{
    m_boxOrientedCollider.Center = center;
    m_boxOrientedCollider.Extents = extents;
    //èCê≥ïKóv
    m_boxOrientedCollider.Orientation = { orientation.x,orientation.y,orientation.z,0.0f };
}

void BoxCollider::UpdateExtents()
{
    m_boxOrientedCollider.Extents = m_extents;
}

void BoxCollider::UpdatePos()
{
    m_boxOrientedCollider.Center = m_center;
}

void BoxCollider::UpdateOrientation()
{
    //èCê≥ïKóv
    m_boxOrientedCollider.Orientation = m_boxOrientedCollider.Orientation = { m_orientation.x,m_orientation.y,m_orientation.z,0.0f };
}

void BoxCollider::Update()
{
    if (!isActive) 
    { 
        return;
    }
    else 
    {
        UpdateExtents();
        UpdatePos();
        UpdateOrientation();
    }

}

bool BoxCollider::isCollision(const SphereCollider& sphereCollider)
{
    return false;
}

bool BoxCollider::isCollision(const BoxCollider& boxCollider)
{
    return false;
}
