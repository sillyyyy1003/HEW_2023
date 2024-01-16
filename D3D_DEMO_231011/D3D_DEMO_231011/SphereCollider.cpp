#include "SphereCollider.h"
#include "BoxCollider.h"

SphereCollider::SphereCollider()
{
}

void SphereCollider::InitCollider(DirectX::XMFLOAT3 center, float Radius, COLLISION_TYPE _type)
{
    Collider::InitCollider(_type);

    m_sphereCollider.Center = center;
    m_sphereCollider.Radius = Radius;

}

void SphereCollider::UpdateRadius()
{
    m_sphereCollider.Radius = m_radius;
}

void SphereCollider::UpdatePos()
{
    m_sphereCollider.Center = m_center;
}



bool SphereCollider::isCollision(SphereCollider* sphereCollider)
{
    if (this->GetCollider().Intersects(sphereCollider->SphereCollider::GetCollider()))
    {
        return true;
    }
    else {
        return false;
    }

    
}

bool SphereCollider::isCollision(BoxCollider* boxCollider)
{
    if (this->GetCollider().Intersects(boxCollider->BoxCollider::GetCollider()))
    {
        return true;
    }
    else {
        return false;
    }
   
}

void SphereCollider::Update()
{
    if (!isActive) 
    {
        return; 
    }
    else {

        UpdatePos();

        UpdateRadius();
        
    }

}
