#include "BoxCollider.h"
#include "SphereCollider.h"
#include "PolygonCollider.h"

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
        //UpdateExtents();
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

bool BoxCollider::isClearCollision(Collider* polygoncollider, float verNum)
{
    PolygonSAT3D* Polygon = new PolygonSAT3D;
    PolygonSAT3D* EPolygon = new PolygonSAT3D;
    verticies = SetSquare(m_boxCollider.Extents.x, m_boxCollider.Extents.y);
    BoundingSphere SCollider;
    BoundingBox BCollider;

    Polygon->vertices = SetSquare(0.3f, 0.3f);

    if (polygoncollider->GetColliderType() == POLYGON)
    {
        SCollider = polygoncollider->GetPolygonCollider();
        EPolygon->vertices = SetTriangle(SCollider.Radius);
    }
    else if (polygoncollider->GetColliderType() == SQUARE)
    {
        BCollider = polygoncollider->GetBoxCollider();
        EPolygon->vertices = SetSquare(BCollider.Extents.x, BCollider.Extents.y);
    }
    else if (polygoncollider->GetColliderType() == SPHERE)
    {
        SCollider = polygoncollider->GetSphereCollider();
        EPolygon->vertices = SetCircle(SCollider.Radius);
    }

    //Polygon->rotation = Quaternion::FromEulerAngles(0, rotation.x, 0);  // ‰ñ“]‚È‚µ
    //Sphere->rotation = Quaternion::FromEulerAngles(1, rotation.x,1);  // 45“x‰ñ“]

    std::vector<Vector3> Polygonverticies = Polygon->GetRotatedVertices();
    std::vector<Vector3> EPolygonverticies = EPolygon->GetRotatedVertices();

    for (auto& vertex : verticies) {
        vertex.x += m_boxCollider.Center.x;
        vertex.y += m_boxCollider.Center.y;
        //vertex.z += center.z;
    }

    // ŽlŠp
    if (verNum == 0 || verNum == 2)
    {
        for (auto& vertex : Polygonverticies) {
            vertex.x += m_boxCollider.Center.x;
            vertex.y += verticies[verNum].y;
            //vertex.z += center.z;
        }
    }
    else
    {
        for (auto& vertex : Polygonverticies) {
            vertex.x += verticies[verNum].x;
            vertex.y += m_boxCollider.Center.y;
            //vertex.z += center.z;
        }
    }


    if (SCollider.Center.y)
    {
        for (auto& vertex : EPolygonverticies) {
            vertex.x += SCollider.Center.x;
            vertex.y += SCollider.Center.y;
            //vertex.z += Lm_polygonCollider.Center.z;
        }
    }
    if (BCollider.Center.y)
    {
        for (auto& vertex : EPolygonverticies) {
            vertex.x += BCollider.Center.x;
            vertex.y += BCollider.Center.y;
            //vertex.z += Lm_polygonCollider.Center.z;
        }
    }

    Polygon->vertices = Polygonverticies;

    EPolygon->vertices = EPolygonverticies;
    SetVerticies(EPolygonverticies);

    bool collisionResult = SAT::Collide3D(*Polygon, *EPolygon);

    // Œ‹‰Ê‚ð•\Ž¦
    if (collisionResult)
    {
        return true;
    }
    return false;
}
