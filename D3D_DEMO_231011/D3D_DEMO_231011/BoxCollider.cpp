#include "BoxCollider.h"
#include "SphereCollider.h"
#include "PolygonCollider.h"
#include "Material.h"

BoxCollider::BoxCollider()
{
   
}

void BoxCollider::InitCollider(DirectX::XMFLOAT3 center, Collide collider)
{
    Collider::InitColliderType(COLLISION_TYPE::SQUARE);

    //���f�[�^���X�V
    m_center = center;
    m_extents = collider.extents;
    m_radius = collider.radius;
    
    //�R���C�_�[�̃f�[�^�X�V
    UpdatePos(m_center);
    UpdateExtents(m_extents);
    m_boxCollider.Orientation = { 0,0,0,0 };

    //���ӌ`����p�̒��_�f�[�^�X�V
    m_verticies = GetSquareVerticies();
}

std::vector<Vector3> BoxCollider::GetSquareVerticies(void)
{
    Collider::SQUARE square;
    square.A = { m_center.x - m_extents.x, m_center.y + m_extents.y };
    square.B = { m_center.x + m_extents.x, m_center.y + m_extents.y };
    square.C = { m_center.x + m_extents.x, m_center.y - m_extents.y };
    square.D = { m_center.x - m_extents.x, m_center.y - m_extents.y };


    //1�ڂ̓ʑ��p�`�̒��_���W���`
    std::vector<Vector3> vertices = {
        Vector3(square.A.x, square.A.y,0),
        Vector3(square.B.x, square.B.y,0),
        Vector3(square.C.x, square.C.y,0),
        Vector3(square.D.x, square.D.y,0),
    };

    return vertices;
}


void BoxCollider::UpdateExtents(DirectX::XMFLOAT3 extents)
{
    m_boxCollider.Extents = extents;
}

void BoxCollider::UpdatePos(DirectX::XMFLOAT3 center)
{
    m_boxCollider.Center = center;
}
 
void BoxCollider::UpdateRotation(DirectX::XMFLOAT3 rotation) {
    
    DirectX::XMFLOAT4 orientation;
    //degree����radians�ɕϊ�
    float roll = DirectX::XMConvertToRadians(rotation.x);      //x����]
    float pitch = DirectX::XMConvertToRadians(rotation.y);     //y����]
    float yaw = DirectX::XMConvertToRadians(rotation.z);       //z����]
    
    //xmfloat4�ɕϊ�����
    DirectX::XMVECTOR vector = DirectX::XMQuaternionRotationRollPitchYaw(pitch, yaw, roll);
    DirectX::XMStoreFloat4(&orientation, vector);
    
    //�v�Z�ł����l����
    m_boxCollider.Orientation = orientation;
    
    //���ӁF
    //z����]�����Ȃ��̂ŁAobb�̉�]��݌v�v�Z�ł͂Ȃ��A�����l�ɂ���Ė�����߂Čv�Z���Ă���B

}



void BoxCollider::UpdateVerticies(DirectX::XMFLOAT3 rotation)
{
    /*
    //�p�x���烉�W�A���ɕϊ�
    float roll = DirectX::XMConvertToRadians(rotation.x);      //x����]
    float pitch = DirectX::XMConvertToRadians(rotation.y);     //y����]
    float yaw = DirectX::XMConvertToRadians(rotation.z);       //z����]

    PolygonSAT3D* Polygon = new PolygonSAT3D;
    //�|���S���̒��_����
    Polygon->vertices = BoxCollider::m_verticies;
    //��]����
    Polygon->rotation = Quaternion::FromEulerAngles(pitch, yaw, roll);
    //��]������̒��_���l��
    m_verticies = Polygon->GetRotatedVertices();
    */
    //std::vector<Vector3> verticies;
    // 
    //���_�̈ʒu�f�[�^���l��
    std::vector<DirectX::XMFLOAT3> verticies(8);
    m_boxCollider.GetCorners(verticies.data());
    
    for (int i = 0; i < m_verticies.size(); i++) {
        m_verticies[i].x = verticies[i].x;
        m_verticies[i].y = verticies[i].y;
        m_verticies[i].z = verticies[i].z;
    }

}

void BoxCollider::Update(DirectX::XMFLOAT3 center, DirectX::XMFLOAT3 rotation, DirectX::XMFLOAT3 extents)
{
    if (!isActive) 
    { 
        return;
    }
    else 
    {
        //��]
        UpdateRotation(rotation);
        //�傫��
        UpdateExtents(extents);
        //�ʒu
        UpdatePos(center);
        //���_   
        //UpdateVerticies(rotation);
    }
}

bool BoxCollider::isCollision(SphereCollider* collider)
{
    if (this->m_boxCollider.Intersects(collider->GetCollider())) {
        return true;
    }
    else {
        return false;
    }
}

bool BoxCollider::isCollision(BoxCollider* collider)
{
    if (this->m_boxCollider.Intersects(collider->GetColldier())) {
        return true;
    }
    else {
        return false;
    }
}

bool BoxCollider::isCollision(PolygonCollider* collider)
{
    return false;
}


//bool BoxCollider::isClearCollision(Collider* polygoncollider, float verNum)
//{
//    PolygonSAT3D* Polygon = new PolygonSAT3D;
//    PolygonSAT3D* EPolygon = new PolygonSAT3D;
//    verticies = SetSquare(m_boxCollider.Extents.x, m_boxCollider.Extents.y);
//    BoundingSphere SCollider;
//    BoundingBox BCollider;
//
//    Polygon->vertices = SetSquare(0.3f, 0.3f);
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
//    std::vector<Vector3> Polygonverticies = Polygon->GetRotatedVerticies();
//    std::vector<Vector3> EPolygonverticies = EPolygon->GetRotatedVerticies();
//
//    for (auto& vertex : verticies) {
//        vertex.x += m_boxCollider.Center.x;
//        vertex.y += m_boxCollider.Center.y;
//        //vertex.z += center.z;
//    }
//
//    // �l�p
//    if (verNum == 0 || verNum == 2)
//    {
//        for (auto& vertex : Polygonverticies) {
//            vertex.x += m_boxCollider.Center.x;
//            vertex.y += verticies[verNum].y;
//            //vertex.z += center.z;
//        }
//    }
//    else
//    {
//        for (auto& vertex : Polygonverticies) {
//            vertex.x += verticies[verNum].x;
//            vertex.y += m_boxCollider.Center.y;
//            //vertex.z += center.z;
//        }
//    }
//
//
//    if (SCollider.Center.y)
//    {
//        for (auto& vertex : EPolygonverticies) {
//            vertex.x += SCollider.Center.x;
//            vertex.y += SCollider.Center.y;
//            //vertex.z += Lm_polygonCollider.Center.z;
//        }
//    }
//    if (BCollider.Center.y)
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
//    SetVerticies(EPolygonverticies);
//
//    bool collisionResult = SAT::Collide3D(*Polygon, *EPolygon);
//
//    //
//    if (collisionResult)
//    {
//        return true;
//    }
//    return false;
//}
