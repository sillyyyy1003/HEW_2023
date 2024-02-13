#include "Collider.h"

#define SQUAREWIDTH 0.8

Collider::Collider()
{
}

//std::vector<Vector3> Collider::GetVerticies()
//{
//	return { 0,0,0 };
//}

void Collider::InitColliderType(COLLISION_TYPE _type)
{
    Collider::m_collisionType = _type;
}

void Collider::InitCollider(DirectX::XMFLOAT3 center,Collide collider) {

}

void Collider::Update(DirectX::XMFLOAT3 center, DirectX::XMFLOAT3 rotation, DirectX::XMFLOAT3 extents)
{
}

Collider_Dir Collider::GetCollisionDir(Collider* collider)
{
	Collider_Dir dir = { INI_STATE,INI_STATE };
	int x_Result = this->m_center.x - collider->m_center.x;
	int y_Result = this->m_center.y - collider->m_center.y;

	

	//TargetObject は本体の左
	if (x_Result > 0) {

		if (y_Result > 0) {//TARGET　objectは本体の下
			
			dir = { COL_LEFT,COL_DOWN };
		}
		else if (y_Result < 0) {//TARGET　objectは本体の上
			
			dir = { COL_LEFT,COL_UP };
		}
		else {
			dir = { COL_LEFT,OVERLAP };
		}
	}
	else if (x_Result < 0) {//TargetObject は本体の右

		if (y_Result > 0) {//TARGET　objectは本体の下

			dir = { COL_RIGHT,COL_DOWN };
		}
		else if (y_Result < 0) {//TARGET　objectは本体の上

			dir = { COL_RIGHT,COL_UP };
		}
		else {
			dir = { COL_RIGHT,OVERLAP };
		}
	}
	else {

		if (y_Result > 0) {//TARGET　objectは本体の下

			dir = { OVERLAP,COL_DOWN };
		}
		else if (y_Result < 0) {//TARGET　objectは本体の上

			dir = { OVERLAP,COL_UP };
		}
		else {
			dir = { OVERLAP,OVERLAP };
		}
		
	}



	return dir;
}


Collider::~Collider(void)
{
}
