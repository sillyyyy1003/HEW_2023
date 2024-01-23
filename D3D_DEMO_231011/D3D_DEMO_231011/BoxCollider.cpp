#include "BoxCollider.h"
#include "SphereCollider.h"

BoxCollider::BoxCollider()
{
}

void BoxCollider::InitCollider(DirectX::XMFLOAT3 center, DirectX::XMFLOAT3 extents)
{
    Collider::InitCollider(COLLISION_TYPE::SQUARE);
    m_boxCollider.Center = center;
    m_boxCollider.Extents = extents;
}

void BoxCollider::UpdateExtents()
{
    m_boxCollider.Extents = m_extents;
}

void BoxCollider::UpdatePos()
{
    m_boxCollider.Center = m_center;
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
    }

}

bool BoxCollider::isCollision(SphereCollider* sphereCollider)
{
    if (m_boxCollider.Intersects(sphereCollider->SphereCollider::GetCollider())) 
    {
        return true;
    }
    else {
        return false;
    }
  
}

bool BoxCollider::isCollision(BoxCollider* boxCollider)
{
    if (m_boxCollider.Intersects(boxCollider->BoxCollider::GetCollider()))
    {
        return true;
    }
    else {
        return false;
    }
}

bool BoxCollider::isCollision(PolygonCollider* polygonCollider)
{
    return false;
}
