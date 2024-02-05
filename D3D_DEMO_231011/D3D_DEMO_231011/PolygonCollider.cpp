#include "PolygonCollider.h"
#include "SphereCollider.h"
#include "BoxCollider.h"

<<<<<<< HEAD
#define SQUAREWIDTH 0.8
=======
>>>>>>> feature/Kkaku

PolygonCollider::PolygonCollider(DirectX::XMFLOAT3 center, float Radius)
{
    InitCollider(center, Radius);
}

void PolygonCollider::InitCollider(DirectX::XMFLOAT3 _center, float _Radius)
{
    Collider::InitCollider(COLLISION_TYPE::POLYGON);

    m_polygonCollider.Center = _center;
    m_polygonCollider.Radius = _Radius;

    verticies = SetTriangle(m_polygonCollider.Radius);
    //SetVerticies(verticies);
}

//void PolygonCollider::UpdateRadius()
//{
//    radius = m_radius;
//}

void PolygonCollider::SetRadius(float m_radius)
{
    m_polygonCollider.Radius = m_radius;
}

void PolygonCollider::UpdatePos(DirectX::XMFLOAT3 m_center)
{
    m_polygonCollider.Center = m_center;
}

void PolygonCollider::UpdateRotation(DirectX::XMFLOAT3 m_rotation)
{
    rotation = m_rotation;
}

void PolygonCollider::UpdateVerticies()
{
    verticies = SetTriangle(m_polygonCollider.Radius);
}

std::vector<Vector3> PolygonCollider::GetVerticies()
{
    return m_verticies;
}

void PolygonCollider::SetVerticies(std::vector<Vector3> ver)
{
    m_verticies = ver;
}

<<<<<<< HEAD
std::vector<Vector3> PolygonCollider::SetTriangle(float _radius)
{
    Triangle triangle;
    triangle.A = { 0 , _radius };
    triangle.B = { _radius , -_radius };
    triangle.C = { -_radius , -_radius };

    // 1�ڂ̓ʑ��p�`�̒��_���W���`
    std::vector<Vector3> vertices = {
        Vector3(triangle.A.x, triangle.A.y,0),
        Vector3(triangle.B.x, triangle.B.y,0),
        Vector3(triangle.C.x, triangle.C.y,0),
    };

    return vertices;
}

std::vector<Vector3> PolygonCollider::SetSquare(float _widthX, float _widthY)
{
    SQURE squre;
    // �l�p�̉��̎O�p
    squre.A = { _widthX,_widthY };
    squre.B = { _widthX,-_widthY };
    squre.C = { -_widthX,-_widthY };
    squre.D = { -_widthX,_widthY };

    // 1�ڂ̓ʑ��p�`�̒��_���W���`
    std::vector<Vector3> vertices = {
        Vector3(squre.A.x, squre.A.y,0),
        Vector3(squre.B.x, squre.B.y,0),
        Vector3(squre.C.x, squre.C.y,0),
        Vector3(squre.D.x, squre.D.y,0),
    };

    return vertices;
}

std::vector<Vector3> PolygonCollider::SetCircle(float radius)
{
    SQURE squre;
    float squarewidth = SQUAREWIDTH;
    // �l�p�̉��̎O�p
    squre.A = { radius* squarewidth,radius * squarewidth };
    squre.B = { radius * squarewidth,-radius * squarewidth };
    squre.C = { -radius * squarewidth,-radius * squarewidth };
    squre.D = { -radius * squarewidth,radius * squarewidth };

    SQURE circle;
    // �l�p�̉��̎O�p
    circle.A = { 0, radius};
    circle.B = { radius,0 };
    circle.C = { 0 , -radius};
    circle.D = { -radius,0 };


    // 1�ڂ̓ʑ��p�`�̒��_���W���`
    std::vector<Vector3> vertices = {
        Vector3(circle.A.x, circle.A.y,0),
        Vector3(squre.A.x, squre.A.y,0),
        Vector3(circle.B.x, circle.B.y,0),
        Vector3(squre.B.x, squre.B.y,0),
        Vector3(circle.C.x, circle.C.y,0),
        Vector3(squre.C.x, squre.C.y,0),
        Vector3(circle.D.x, circle.D.y,0),
        Vector3(squre.D.x, squre.D.y,0),
    };
    return vertices;
}

=======
>>>>>>> feature/Kkaku
void PolygonCollider::Update(DirectX::XMFLOAT3 m_center,DirectX::XMFLOAT3 m_rotation)
{
    if (!isActive)
    {
        return;
    }
    else {

        UpdatePos(m_center);

        UpdateRotation(m_rotation);

        //UpdateRadius(m_radius);

        UpdateVerticies();
    }

}

// ---�}�`�̓����蔻��̏��� ---//
bool PolygonCollider::isBoxCollision(Collider* boxCollider)
{
    PolygonSAT3D* Polygon = new PolygonSAT3D;
    PolygonSAT3D* Box = new PolygonSAT3D;

    Lm_boxCollider = boxCollider->GetBoxCollider();
    Polygon->vertices = verticies;
    Box->vertices = SetSquare(Lm_boxCollider.Extents.x, Lm_boxCollider.Extents.y);;

    //Polygon->rotation = Quaternion::FromEulerAngles(0, rotation.x, 0);  // ��]�Ȃ�
    //Sphere->rotation = Quaternion::FromEulerAngles(1, rotation.x,1);  // 45�x��]

    std::vector<Vector3> Polygonverticies = Polygon->GetRotatedVertices();
    std::vector<Vector3> Boxverticies = Box->GetRotatedVertices();

    // �l�p
    for (auto& vertex : Polygonverticies) {
        vertex.x += m_polygonCollider.Center.x;
        vertex.y += m_polygonCollider.Center.y;
        //vertex.z += center.z;
    }

    for (auto& vertex : Boxverticies) {
        vertex.x += Lm_boxCollider.Center.x;
        vertex.y += Lm_boxCollider.Center.y;
        //vertex.z += Lm_boxCollider.Center.z;
    }

    Polygon->vertices = Polygonverticies;

    Box->vertices = Boxverticies;
<<<<<<< HEAD
    //SetVerticies(Polygon->vertices);
=======
    //SetVerticies(Boxverticies);
>>>>>>> feature/Kkaku

    bool collisionResult = SAT::Collide3D(*Polygon, *Box);

    // ���ʂ�\��
    if (collisionResult)
    {
        return true;
    }
    return false;
}

bool PolygonCollider::isSphereCollision(Collider* sphereCollider)
{
    PolygonSAT3D* Polygon = new PolygonSAT3D;
    PolygonSAT3D* Sphere = new PolygonSAT3D;

    Lm_sphereCollider = sphereCollider->GetSphereCollider();
    Polygon->vertices = verticies;
    Sphere->vertices = SetCircle(Lm_sphereCollider.Radius);;

    //Polygon->rotation = Quaternion::FromEulerAngles(0, rotation.x, 0);  // ��]�Ȃ�
    //Sphere->rotation = Quaternion::FromEulerAngles(1, rotation.x,1);  // 45�x��]

    std::vector<Vector3> Polygonverticies = Polygon->GetRotatedVertices();
    std::vector<Vector3> Sphereverticies = Sphere->GetRotatedVertices();

    // �l�p
    // �Ȃ���1.5�{����K�v������
    for (auto& vertex : Polygonverticies) {
        vertex.x += m_polygonCollider.Center.x;
        vertex.y += m_polygonCollider.Center.y;
        //vertex.z += center.z;
    }

    for (auto& vertex : Sphereverticies) {
        vertex.x += Lm_sphereCollider.Center.x;
        vertex.y += Lm_sphereCollider.Center.y;
        //vertex.z += Lm_sphereCollider.Center.z;
    }

    Polygon->vertices = Polygonverticies;

    Sphere->vertices = Sphereverticies;
<<<<<<< HEAD
    SetVerticies(Sphereverticies);
=======
    //SetVerticies(Polygonverticies);
>>>>>>> feature/Kkaku

    bool collisionResult = SAT::Collide3D(*Polygon, *Sphere);

    // ���ʂ�\��
    if (collisionResult)
    {
        return true;
    }
    return false;
}

bool PolygonCollider::isPolygonCollision(Collider* polygoncollider)
{
    PolygonSAT3D* Polygon = new PolygonSAT3D;
    PolygonSAT3D* EPolygon = new PolygonSAT3D;

    Lm_polygonCollider = polygoncollider->GetPolygonCollider();
    Polygon->vertices = verticies;
    EPolygon->vertices = SetTriangle(Lm_polygonCollider.Radius);;

    //Polygon->rotation = Quaternion::FromEulerAngles(0, rotation.x, 0);  // ��]�Ȃ�
    //Sphere->rotation = Quaternion::FromEulerAngles(1, rotation.x,1);  // 45�x��]

    std::vector<Vector3> Polygonverticies = Polygon->GetRotatedVertices();
    std::vector<Vector3> EPolygonverticies = EPolygon->GetRotatedVertices();

    // �l�p
    // �Ȃ���1.5�{����K�v������
    for (auto& vertex : Polygonverticies) {
        vertex.x += m_polygonCollider.Center.x;
        vertex.y += m_polygonCollider.Center.y;
        //vertex.z += center.z;
    }

    for (auto& vertex : EPolygonverticies) {
        vertex.x += Lm_polygonCollider.Center.x;
        vertex.y += Lm_polygonCollider.Center.y;
        //vertex.z += Lm_polygonCollider.Center.z;
    }

    Polygon->vertices = Polygonverticies;

    EPolygon->vertices = EPolygonverticies;
<<<<<<< HEAD
    //SetVerticies(EPolygonverticies);

    bool collisionResult = SAT::Collide3D(*Polygon, *EPolygon);

    // ���ʂ�\��
    if (collisionResult)
    {
        return true;
    }
    return false;
}
#include "PolygonCollider.h"
#include "SphereCollider.h"
#include "BoxCollider.h"


PolygonCollider::PolygonCollider(DirectX::XMFLOAT3 center, float Radius)
{
    InitCollider(center, Radius);
}

void PolygonCollider::InitCollider(DirectX::XMFLOAT3 _center, float _Radius)
{
    Collider::InitCollider(COLLISION_TYPE::POLYGON);

    m_polygonCollider.Center = _center;
    m_polygonCollider.Radius = _Radius;

    verticies = SetTriangle(m_polygonCollider.Radius);
    //SetVerticies(verticies);
}

//void PolygonCollider::UpdateRadius()
//{
//    radius = m_radius;
//}

void PolygonCollider::SetRadius(float m_radius)
{
    m_polygonCollider.Radius = m_radius;
}

void PolygonCollider::UpdatePos(DirectX::XMFLOAT3 m_center)
{
    m_polygonCollider.Center = m_center;
}

void PolygonCollider::UpdateRotation(DirectX::XMFLOAT3 m_rotation)
{
    rotation = m_rotation;
}

void PolygonCollider::UpdateVerticies()
{
    verticies = SetTriangle(m_polygonCollider.Radius);
}

std::vector<Vector3> PolygonCollider::GetVerticies()
{
    return m_verticies;
}

void PolygonCollider::SetVerticies(std::vector<Vector3> ver)
{
    m_verticies = ver;
}

void PolygonCollider::Update(DirectX::XMFLOAT3 m_center,DirectX::XMFLOAT3 m_rotation)
{
    if (!isActive)
    {
        return;
    }
    else {

        UpdatePos(m_center);

        UpdateRotation(m_rotation);

        //UpdateRadius(m_radius);

        UpdateVerticies();
    }

}

// ---�}�`�̓����蔻��̏��� ---//
bool PolygonCollider::isBoxCollision(Collider* boxCollider)
{
    PolygonSAT3D* Polygon = new PolygonSAT3D;
    PolygonSAT3D* Box = new PolygonSAT3D;

    Lm_boxCollider = boxCollider->GetBoxCollider();
    Polygon->vertices = verticies;
    Box->vertices = SetSquare(Lm_boxCollider.Extents.x, Lm_boxCollider.Extents.y);;

    //Polygon->rotation = Quaternion::FromEulerAngles(0, rotation.x, 0);  // ��]�Ȃ�
    //Sphere->rotation = Quaternion::FromEulerAngles(1, rotation.x,1);  // 45�x��]

    std::vector<Vector3> Polygonverticies = Polygon->GetRotatedVertices();
    std::vector<Vector3> Boxverticies = Box->GetRotatedVertices();

    // �l�p
    for (auto& vertex : Polygonverticies) {
        vertex.x += m_polygonCollider.Center.x;
        vertex.y += m_polygonCollider.Center.y;
        //vertex.z += center.z;
    }

    for (auto& vertex : Boxverticies) {
        vertex.x += Lm_boxCollider.Center.x;
        vertex.y += Lm_boxCollider.Center.y;
        //vertex.z += Lm_boxCollider.Center.z;
    }

    Polygon->vertices = Polygonverticies;

    Box->vertices = Boxverticies;
    //SetVerticies(Boxverticies);

    bool collisionResult = SAT::Collide3D(*Polygon, *Box);

    // ���ʂ�\��
    if (collisionResult)
    {
        return true;
    }
    return false;
}

bool PolygonCollider::isSphereCollision(Collider* sphereCollider)
{
    PolygonSAT3D* Polygon = new PolygonSAT3D;
    PolygonSAT3D* Sphere = new PolygonSAT3D;

    Lm_sphereCollider = sphereCollider->GetSphereCollider();
    Polygon->vertices = verticies;
    Sphere->vertices = SetCircle(Lm_sphereCollider.Radius);;

    //Polygon->rotation = Quaternion::FromEulerAngles(0, rotation.x, 0);  // ��]�Ȃ�
    //Sphere->rotation = Quaternion::FromEulerAngles(1, rotation.x,1);  // 45�x��]

    std::vector<Vector3> Polygonverticies = Polygon->GetRotatedVertices();
    std::vector<Vector3> Sphereverticies = Sphere->GetRotatedVertices();

    // �l�p
    // �Ȃ���1.5�{����K�v������
    for (auto& vertex : Polygonverticies) {
        vertex.x += m_polygonCollider.Center.x;
        vertex.y += m_polygonCollider.Center.y;
        //vertex.z += center.z;
    }

    for (auto& vertex : Sphereverticies) {
        vertex.x += Lm_sphereCollider.Center.x;
        vertex.y += Lm_sphereCollider.Center.y;
        //vertex.z += Lm_sphereCollider.Center.z;
    }

    Polygon->vertices = Polygonverticies;

    Sphere->vertices = Sphereverticies;
    //SetVerticies(Polygonverticies);

    bool collisionResult = SAT::Collide3D(*Polygon, *Sphere);

    // ���ʂ�\��
    if (collisionResult)
    {
        return true;
    }
    return false;
}

bool PolygonCollider::isPolygonCollision(Collider* polygoncollider)
{
    PolygonSAT3D* Polygon = new PolygonSAT3D;
    PolygonSAT3D* EPolygon = new PolygonSAT3D;

    Lm_polygonCollider = polygoncollider->GetPolygonCollider();
    Polygon->vertices = verticies;
    EPolygon->vertices = SetTriangle(Lm_polygonCollider.Radius);;

    //Polygon->rotation = Quaternion::FromEulerAngles(0, rotation.x, 0);  // ��]�Ȃ�
    //Sphere->rotation = Quaternion::FromEulerAngles(1, rotation.x,1);  // 45�x��]

    std::vector<Vector3> Polygonverticies = Polygon->GetRotatedVertices();
    std::vector<Vector3> EPolygonverticies = EPolygon->GetRotatedVertices();

    // �l�p
    // �Ȃ���1.5�{����K�v������
    for (auto& vertex : Polygonverticies) {
        vertex.x += m_polygonCollider.Center.x;
        vertex.y += m_polygonCollider.Center.y;
        //vertex.z += center.z;
    }

    for (auto& vertex : EPolygonverticies) {
        vertex.x += Lm_polygonCollider.Center.x;
        vertex.y += Lm_polygonCollider.Center.y;
        //vertex.z += Lm_polygonCollider.Center.z;
    }

    Polygon->vertices = Polygonverticies;

    EPolygon->vertices = EPolygonverticies;
=======
>>>>>>> feature/Kkaku
    //SetVerticies(Polygonverticies);

    bool collisionResult = SAT::Collide3D(*Polygon, *EPolygon);

    // ���ʂ�\��
    if (collisionResult)
    {
        return true;
    }
    return false;
}

bool PolygonCollider::isClearCollision(Collider* polygoncollider,float verNum)
{
    PolygonSAT3D* Polygon = new PolygonSAT3D;
    PolygonSAT3D* EPolygon = new PolygonSAT3D;
    Clearverticies = SetTriangle(m_polygonCollider.Radius);
    BoundingSphere SCollider;
    BoundingBox BCollider;

    Polygon->vertices = SetSquare(0.3f,0.3f);
    
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

    //Polygon->rotation = Quaternion::FromEulerAngles(0, rotation.x, 0);  // ��]�Ȃ�
    //Sphere->rotation = Quaternion::FromEulerAngles(1, rotation.x,1);  // 45�x��]

    std::vector<Vector3> Polygonverticies = Polygon->GetRotatedVertices();
    std::vector<Vector3> EPolygonverticies = EPolygon->GetRotatedVertices();

    for (auto& vertex : Clearverticies) {
        vertex.x += m_polygonCollider.Center.x;
        vertex.y += m_polygonCollider.Center.y;
        //vertex.z += center.z;
    }

    // �l�p
    for (auto& vertex : Polygonverticies) {
        vertex.x += Clearverticies[verNum].x;
        vertex.y += Clearverticies[verNum].y;
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
    if(BCollider.Center.y)
    {
        for (auto& vertex : EPolygonverticies) {
            vertex.x += BCollider.Center.x;
            vertex.y += BCollider.Center.y;
            //vertex.z += Lm_polygonCollider.Center.z;
        }
    }

    Polygon->vertices = Polygonverticies;

    EPolygon->vertices = EPolygonverticies;
<<<<<<< HEAD
    SetVerticies(Polygonverticies);
=======
    //SetVerticies(Polygonverticies);
>>>>>>> feature/Kkaku

    bool collisionResult = SAT::Collide3D(*Polygon, *EPolygon);

    // ���ʂ�\��
    if (collisionResult)
    {
        return true;
    }
    return false;
}
