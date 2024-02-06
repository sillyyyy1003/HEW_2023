#include "PolygonCollider.h"
#include "SphereCollider.h"
#include "BoxCollider.h"


PolygonCollider::PolygonCollider()
{
    Collider::InitColliderType(COLLISION_TYPE::TRIANGLE);

}

void PolygonCollider::InitCollider(DirectX::XMFLOAT3 center, Collide Collider)
{
    m_center = center;
    m_extents = Collider.extents;
    m_radius = Collider.radius;

}

std::vector<Vector3> PolygonCollider::GetTriangleVertices(void)
{
    Collider::Triangle triangle = {};
    std::vector<Vector3> vertices;

    switch (m_type)
    {
    case TRIANGLE_TYPE::TRI_RIGHT:
        triangle.A = { m_center.x + m_extents.x, m_center.y + m_extents.y };
        triangle.B = { m_center.x + m_extents.x,m_center.y - m_extents.y };
        triangle.C = { m_center.x - m_extents.x,m_center.y - m_extents.y };

        // 1�ڂ̓ʑ��p�`�̒��_���W���`
        vertices = {
            Vector3(triangle.A.x, triangle.A.y,0),
            Vector3(triangle.B.x, triangle.B.y,0),
            Vector3(triangle.C.x, triangle.C.y,0),
        };

        return vertices;

        break;

    case TRIANGLE_TYPE::TRI_ISO:
        triangle.A = { m_center.x, m_center.y + m_extents.y  };
        triangle.B = { m_center.x + m_extents.x ,m_center.y - m_extents.y  };
        triangle.C = { m_center.x - m_extents.x ,m_center.y - m_extents.y  };

        // 1�ڂ̓ʑ��p�`�̒��_���W���`
        vertices = {
            Vector3(triangle.A.x, triangle.A.y,0),
            Vector3(triangle.B.x, triangle.B.y,0),
            Vector3(triangle.C.x, triangle.C.y,0),
        };
        return vertices;
        break;
    case TRI_IDLE:
        return {};
        break;
 
    default:
        break;
    }
}


void PolygonCollider::UpdatePos(DirectX::XMFLOAT3 m_center)
{
   Collider::m_center = m_center;
}

void PolygonCollider::UpdateRotation(DirectX::XMFLOAT3 rotation)
{

    Collider::Triangle triangle = {};
    std::vector<Vector3> vertices;

    //z���̉�]�}�g���N�X���l��
    DirectX::XMMATRIX rotationMatrix = XMMatrixRotationZ(rotation.z);

    //���_�̃f�[�^��xmfloat2�Ɋi�[
    DirectX::XMFLOAT2 A = { triangle.A.x,triangle.A.y };
    DirectX::XMFLOAT2 B = { triangle.B.x,triangle.B.y };
    DirectX::XMFLOAT2 C = { triangle.C.x,triangle.B.y };

    DirectX::XMVECTOR rotatedA, rotatedB, rotatedC;

    switch (m_type)
    {
    case TRI_RIGHT:
        triangle.A = { m_center.x + m_extents.x, m_center.y + m_extents.y };
        triangle.B = { m_center.x + m_extents.x,m_center.y - m_extents.y };
        triangle.C = { m_center.x - m_extents.x,m_center.y - m_extents.y };

        //�I�u�W�F�N�g�Ɖ�]�}�g���N�X�����킹�āA��]������̒��_Vector���l��
        rotatedA = XMVector2Transform(XMLoadFloat2(&A), rotationMatrix);
        rotatedB = XMVector2Transform(XMLoadFloat2(&B), rotationMatrix);
        rotatedC = XMVector2Transform(XMLoadFloat2(&C), rotationMatrix);

        //���_��Vector������W�ʒu�ɕϊ�
        vertices = {
             Vector3(XMVectorGetX(rotatedA), XMVectorGetY(rotatedA), 0),
             Vector3(XMVectorGetX(rotatedB), XMVectorGetY(rotatedB), 0),
             Vector3(XMVectorGetX(rotatedC), XMVectorGetY(rotatedC), 0)
        };
   
        m_verticies = vertices;


        break;

    case TRI_ISO:
        triangle.A = { m_center.x, m_center.y + m_extents.y };
        triangle.B = { m_center.x + m_extents.x ,m_center.y - m_extents.y };
        triangle.C = { m_center.x - m_extents.x ,m_center.y - m_extents.y };

        //�I�u�W�F�N�g�Ɖ�]�}�g���N�X�����킹�āA��]������̒��_Vector���l��
        rotatedA = XMVector2Transform(XMLoadFloat2(&A), rotationMatrix);
        rotatedB = XMVector2Transform(XMLoadFloat2(&B), rotationMatrix);
        rotatedC = XMVector2Transform(XMLoadFloat2(&C), rotationMatrix);

        //���_��Vector������W�ʒu�ɕϊ�
        vertices = {
             Vector3(XMVectorGetX(rotatedA), XMVectorGetY(rotatedA), 0),
             Vector3(XMVectorGetX(rotatedB), XMVectorGetY(rotatedB), 0),
             Vector3(XMVectorGetX(rotatedC), XMVectorGetY(rotatedC), 0)
        };

        m_verticies = vertices;
        break;

    case TRI_IDLE:
        
        break;


    }
}

void PolygonCollider::UpdateExtents(DirectX::XMFLOAT3 extents)
{
    m_extents = extents;
}

void PolygonCollider::UpdateVerticies(DirectX::XMFLOAT3 rotation)
{
    //�p�x���烉�W�A���ɕϊ�
    float roll = DirectX::XMConvertToRadians(rotation.x);      //x����]
    float pitch = DirectX::XMConvertToRadians(rotation.y);     //y����]
    float yaw = DirectX::XMConvertToRadians(rotation.z);       //z����]

    PolygonSAT3D* Polygon = new PolygonSAT3D;
    //�|���S���̒��_����
    Polygon->vertices = m_verticies;
    //��]����
    Polygon->rotation = Quaternion::FromEulerAngles(pitch, yaw, roll);
    //��]������̒��_���l��
    m_verticies = Polygon->GetRotatedVertices();

}

std::vector<Vector3> PolygonCollider::GetVerticies()
{
    return m_verticies;
}

void PolygonCollider::SetVerticies(std::vector<Vector3> ver)
{
    m_verticies = ver;
}

void PolygonCollider::Update(DirectX::XMFLOAT3 center, DirectX::XMFLOAT3 rotation, DirectX::XMFLOAT3 extents)
{
    if (!isActive)
    {
        return;
    }
    else {
        
        //�ʒu���l��
        UpdatePos(center);

        //�傫��
        //UpdateExtents(extents);

        //���_���l��
        UpdateRotation(rotation);

        
    }

}

bool PolygonCollider::isCollision(BoxCollider* collider)
{
    PolygonSAT3D* Polygon = new PolygonSAT3D;
    PolygonSAT3D* Box = new PolygonSAT3D;


    //��]��̒��_���l��
    Polygon->vertices = m_verticies;
    Box->vertices = collider->GetVerticies();
   
    bool isCollide= SAT::Collide3D(*Polygon, *Box);

    if (isCollide)
    {
        return true;
    }
    return false;

}

// ---�}�`�̓����蔻��̏��� ---//
/*
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
    Sphere->vertices = SetCircle(Lm_sphereCollider.Radius);

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

    //SetVerticies(Polygonverticies);

    bool collisionResult = SAT::Collide3D(*Polygon, *EPolygon);

    // ���ʂ�\��
    if (collisionResult)
    {
        return true;
    }
    return false;
}

//bool PolygonCollider::isClearCollision(Collider* polygoncollider,float verNum)
//{
//    PolygonSAT3D* Polygon = new PolygonSAT3D;
//    PolygonSAT3D* EPolygon = new PolygonSAT3D;
//    Clearverticies = SetTriangle(m_polygonCollider.Radius);
//    BoundingSphere SCollider;
//    BoundingBox BCollider;
//
//    Polygon->vertices = SetSquare(0.3f,0.3f);
//    
//    if (polygoncollider->GetColliderType() == POLYGON)
//    {
//        SCollider = polygoncollider->GetPolygonCollider();
//        EPolygon->vertices = SetTriangle(SCollider.Radius);
//    }
//    else if (polygoncollider->GetColliderType() == SQUARE)
//    {
//        BCollider = polygoncollider->GetBoxCollider();
//        EPolygon->vertices = SetSquare(BCollider.Extents.x, BCollider.Extents.y);
//    }
//    else if (polygoncollider->GetColliderType() == SPHERE)
//    {
//        SCollider = polygoncollider->GetSphereCollider();
//        EPolygon->vertices = SetCircle(SCollider.Radius);
//    }
//
//    //Polygon->rotation = Quaternion::FromEulerAngles(0, rotation.x, 0);  // ��]�Ȃ�
//    //Sphere->rotation = Quaternion::FromEulerAngles(1, rotation.x,1);  // 45�x��]
//
//    std::vector<Vector3> Polygonverticies = Polygon->GetRotatedVertices();
//    std::vector<Vector3> EPolygonverticies = EPolygon->GetRotatedVertices();
//
//    for (auto& vertex : Clearverticies) {
//        vertex.x += m_polygonCollider.Center.x;
//        vertex.y += m_polygonCollider.Center.y;
//        //vertex.z += center.z;
//    }
//
//    // �l�p
//    for (auto& vertex : Polygonverticies) {
//        vertex.x += Clearverticies[verNum].x;
//        vertex.y += Clearverticies[verNum].y;
//        //vertex.z += center.z;
//    }
//
//    if (SCollider.Center.y)
//    {
//        for (auto& vertex : EPolygonverticies) {
//            vertex.x += SCollider.Center.x;
//            vertex.y += SCollider.Center.y;
//            //vertex.z += Lm_polygonCollider.Center.z;
//        }
//    }
//    if(BCollider.Center.y)
//    {
//        for (auto& vertex : EPolygonverticies) {
//            vertex.x += BCollider.Center.x;
//            vertex.y += BCollider.Center.y;
//            //vertex.z += Lm_polygonCollider.Center.z;
//        }
//    }
//
//    Polygon->vertices = Polygonverticies;
//
//    EPolygon->vertices = EPolygonverticies;
//
//    SetVerticies(Polygonverticies);
//
//    //SetVerticies(Polygonverticies);
//
//    bool collisionResult = SAT::Collide3D(*Polygon, *EPolygon);
//
//    // ���ʂ�\��
//    if (collisionResult)
//    {
//        return true;
//    }
//    return false;
//}

*/