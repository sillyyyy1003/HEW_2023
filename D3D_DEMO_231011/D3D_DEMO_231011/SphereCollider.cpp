﻿#include "SphereCollider.h"
#include "BoxCollider.h"
#include "PolygonCollider.h"
#include <cmath>

#define PI (3.14159265358979323846)

SphereCollider::SphereCollider()
{
    
}

std::vector<Vector3> SphereCollider::SetCircle()
{
    Point point[8] = {};

    for (int i = 0; i < 8; ++i) {
        double angle = i * (PI / 4.0); // 每个角度为45度的倍数
        point[i].x = m_center.x + m_radius * cos(angle);
        point[i].y = m_center.y + m_radius * sin(angle);
    }

    // 1つ目の凸多角形の頂点座標を定義
    std::vector<Vector3> vertices = {
        Vector3(point[0].x, point[0].y,0),
        Vector3(point[1].x, point[0].y,0),
        Vector3(point[2].x, point[0].y,0),
        Vector3(point[3].x, point[0].y,0),
        Vector3(point[4].x, point[0].y,0),
        Vector3(point[5].x, point[0].y,0),
        Vector3(point[6].x, point[0].y,0),
        Vector3(point[7].x, point[0].y,0),
    
    };
    return vertices;
}


void SphereCollider::InitCollider(DirectX::XMFLOAT3 center, float Radius)
{
    Collider::InitColliderType(COLLISION_TYPE::SPHERE);

    m_sphereCollider.Center = center;
    m_sphereCollider.Radius = Radius;

    m_verticies = SetCircle();
}

void SphereCollider::UpdateRadius(float radius)
{
    m_sphereCollider.Radius = radius;
}

void SphereCollider::UpdatePos(DirectX::XMFLOAT3 m_center)
{
    m_sphereCollider.Center = m_center;
}

void SphereCollider::UpdateVerticies(void)
{
    m_verticies = SetCircle();
}

void SphereCollider::Update(DirectX::XMFLOAT3 center, DirectX::XMFLOAT3 rotation, DirectX::XMFLOAT3 extents)
{
    if (!isActive)
    {
        return;
    }
    else {
        //位置更新
        UpdatePos(center);
        //UpdateRadius(radius);
        UpdateVerticies();
    }


}



bool SphereCollider::isCollision(BoxCollider* boxCollider)
{
    if (m_sphereCollider.Intersects(boxCollider->GetColldier()))
    {
        return true;
    }
    else {
        return false;
    }
}

bool SphereCollider::isCollision(SphereCollider* sphereCollider)
{

    if (m_sphereCollider.Intersects(sphereCollider->GetCollider()))
    {
        return true;
    }
    else {
        return false;
    }
}

bool SphereCollider::isCollision(PolygonCollider* polygonCollider)
{
    PolygonSAT3D* Sphere = new PolygonSAT3D;
    PolygonSAT3D* Polygon = new PolygonSAT3D;


    //回転後の頂点を獲得
    Sphere->vertices = m_verticies;
    Polygon->vertices = polygonCollider->GetVerticies();

    bool isCollide = SAT::Collide3D(*Sphere, *Polygon);

    delete Polygon;
    delete Sphere;

    return isCollide;
    

}

/*
bool SphereCollider::isClearCollision(Collider* polygoncollider, float verNum)
{
    PolygonSAT3D* Polygon = new PolygonSAT3D;
    PolygonSAT3D* EPolygon = new PolygonSAT3D;
    verticies = SetCircle(m_sphereCollider.Radius);
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
    //SetVerticies(Polygonverticies);

    bool collisionResult = SAT::Collide3D(*Polygon, *EPolygon);

    // 結果を表示
    if (collisionResult)
    {
        return true;
    }
    return false;
}

*/