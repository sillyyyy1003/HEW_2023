#include "BoxCollider.h"
#include "SphereCollider.h"

BoxCollider::BoxCollider(DirectX::XMFLOAT3 center, DirectX::XMFLOAT3 extents)
{
    InitCollider(center, extents);
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

void BoxCollider::UpdatePos(DirectX::XMFLOAT3 m_center)
{
    m_boxCollider.Center = m_center;
}


void BoxCollider::Update(DirectX::XMFLOAT3 m_center, DirectX::XMFLOAT3 m_rotation)
{
    if (!isActive) 
    { 
        return;
    }
    else 
    {
        
        UpdatePos(m_center);
    }

}

bool BoxCollider::isSphereCollision(Collider* sphereCollider)
{
    if (m_boxCollider.Intersects(sphereCollider->GetSphereCollider())) 
    {
        return true;
    }
    else {
        return false;
    }
  
}

bool BoxCollider::isBoxCollision(Collider* boxCollider)
{
    if (m_boxCollider.Intersects(boxCollider->GetBoxCollider()))
    {
        return true;
    }
    else {
        return false;
    }
}
