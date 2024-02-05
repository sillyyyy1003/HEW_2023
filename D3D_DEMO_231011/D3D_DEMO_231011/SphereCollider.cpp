#include "SphereCollider.h"
#include "BoxCollider.h"

SphereCollider::SphereCollider(DirectX::XMFLOAT3 center, float RadiusDirectX::XMFLOAT3 center, float Radius)
{
    //Collider 
    InitCollider(center, Radius);
    InitCollider(center, Radius);
}

void SphereCollider::InitCollider(DirectX::XMFLOAT3 center, float Radius)
{
    Collider::InitCollider(COLLISION_TYPE::SPHERE);

    m_sphereCollider.Center = center;
    m_sphereCollider.Radius = Radius;

}

void SphereCollider::UpdateRadius(float Radiusfloat Radius)
{
    m_sphereCollider.Radius = m_radius;
}

void SphereCollider::UpdatePos(DirectX::XMFLOAT3 m_centerDirectX::XMFLOAT3 m_center)
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
bool SphereCollider::isBoxCollision(Collider* boxCollider)
{
    if (m_sphereCollider.Intersects(boxCollider->GetBoxCollider()))
    if (m_sphereCollider.Intersects(boxCollider->GetBoxCollider()))
    {
        return true;
    }
    else {
        return false;
    }
   
}

bool SphereCollider::isClearCollision(Collider* polygoncollider, float verNum)
{
    PolygonSAT3D* Polygon = new PolygonSAT3D;
    PolygonSAT3D* EPolygon = new PolygonSAT3D;
    verticies = SetCircle(m_sphereCollider.Radius);
    BoundingSphere SCollider;
    BoundingBox BCollider;

    Polygon->vertices = SetSquare(0.5f, 0.5f);

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

    //Polygon->rotation = Quaternion::FromEulerAngles(0, rotation.x, 0);  // 回転なし
    //Sphere->rotation = Quaternion::FromEulerAngles(1, rotation.x,1);  // 45度回転

    std::vector<Vector3> Polygonverticies = Polygon->GetRotatedVertices();
    std::vector<Vector3> EPolygonverticies = EPolygon->GetRotatedVertices();

    for (auto& vertex : verticies) {
        vertex.x += m_sphereCollider.Center.x;
        vertex.y += m_sphereCollider.Center.y;
        //vertex.z += center.z;
    }

    // 四角
    for (auto& vertex : Polygonverticies) {
        vertex.x += verticies[verNum].x;
        vertex.y += verticies[verNum].y;
        //vertex.z += center.z;
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
    //SetVerticies(EPolygonverticies);

    bool collisionResult = SAT::Collide3D(*Polygon, *EPolygon);

    // 結果を表示
    if (collisionResult)
    {
        return true;
    }
    return false;
}

void SphereCollider::Update(DirectX::XMFLOAT3 m_center, DirectX::XMFLOAT3 m_rotationDirectX::XMFLOAT3 m_center, DirectX::XMFLOAT3 m_rotation)
{
    if (!isActive) 
    {
        return; 
    }
    else {

        UpdatePos(m_center);

        //UpdateRadius();
        UpdatePos(m_center);

        //UpdateRadius();
    }

}
