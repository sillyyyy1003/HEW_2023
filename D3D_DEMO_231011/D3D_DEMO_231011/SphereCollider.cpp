#include "SphereCollider.h"
#include "BoxCollider.h"

SphereCollider::SphereCollider(DirectX::XMFLOAT3 center, float Radius)
{
    //Collider 
    InitCollider(center, Radius);
}

void SphereCollider::InitCollider(DirectX::XMFLOAT3 center, float Radius)
{
    Collider::InitCollider(COLLISION_TYPE::SPHERE);

    m_sphereCollider.Center = center;
    m_sphereCollider.Radius = Radius;

}

void SphereCollider::UpdateRadius(float Radius)
{
    m_sphereCollider.Radius = m_radius;
}

void SphereCollider::UpdatePos(DirectX::XMFLOAT3 m_center)
{
    m_sphereCollider.Center = m_center;
}

bool SphereCollider::isSphereCollision(Collider* sphereCollider)
{
    if (m_sphereCollider.Intersects(sphereCollider->GetSphereCollider()))
    {
        return true;
    }
    else {
        return false;
    }

    
}

bool SphereCollider::isBoxCollision(Collider* boxCollider)
{
    if (m_sphereCollider.Intersects(boxCollider->GetBoxCollider()))
    {
        return true;
    }
    else {
        return false;
    }
   
}

void SphereCollider::Update(DirectX::XMFLOAT3 m_center, DirectX::XMFLOAT3 m_rotation)
{
    if (!isActive) 
    {
        return; 
    }
    else {

        UpdatePos(m_center);

        //UpdateRadius();
    }

}
