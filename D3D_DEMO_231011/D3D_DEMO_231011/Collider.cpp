#include "Collider.h"
#include "Material.h"

#define SQUAREWIDTH 0.8

Collider::Collider()
{
}

std::vector<Vector3> Collider::GetVerticies()
{
	return std::vector<Vector3>();
}

void Collider::InitColliderType(COLLISION_TYPE _type)
{
	m_collisionType = _type;
	isActive = true;
}



void Collider::Update(DirectX::XMFLOAT3 center, DirectX::XMFLOAT3 rotation, DirectX::XMFLOAT3 extents)
{
    //空にする
}

Collider_Dir Collider::GetCollisionDir(Collider* collider)
{
    Collider_Dir dir = { INI_STATE,INI_STATE };
    //引き算して　オブジェクトの位置決める
    float x_Result = this->m_center.x - collider->m_center.x;
    float y_Result = this->m_center.y - collider->m_center.y;

    if (x_Result > 0)
    {
        dir.horizontal = COLLISION_DIR::COL_LEFT;
    }
    else if (x_Result < 0)
    {
        dir.horizontal = COLLISION_DIR::COL_RIGHT;
    }
    else
    {
        dir.horizontal = COLLISION_DIR::OVERLAP;
    }


    if (y_Result > 0)
    {
        dir.vertical = COLLISION_DIR::COL_DOWN;
    }
    else if (y_Result < 0)
    {
        dir.vertical = COLLISION_DIR::COL_UP;
    }
    else
    {
        dir.vertical = COLLISION_DIR::OVERLAP;
    }
    return dir;

}


Collider::~Collider(void)
{
}

