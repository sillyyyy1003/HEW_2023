#include "ColliderManager.h"
class BoxCollider;
class SphereCollider;
class PolygonCollider;

ColliderManager::ColliderManager()
{

}

ColliderManager::~ColliderManager()
{
}

void ColliderManager::Update(Collider* collider)
{
}

void ColliderManager::Collision(GameObject* object)
{
	//for (int j = 0; j < sizeof(object) / sizeof(object[0]); ++j)
	//{
	//	for (int i = 1 + j; i < sizeof(object) / sizeof(object[0]); ++i)
	//	{
	//		if (object[i]->m_objCollider->GetColliderType() == SQUARE)
	//		{
	//			if (object[j]->m_objCollider->isBoxCollision(object[i]->m_objCollider))
	//			{
	//				if (object[i]->isPlayer)
	//				{
	//					object[j]->m_objCollider->isActive = false;
	//				}
	//				else
	//				{
	//					object[i]->m_objCollider->isActive = false;
	//				}
	//			}
	//		}
	//		else if (object[i]->m_objCollider->GetColliderType() == SPHERE)
	//		{
	//			if (object[j]->m_objCollider->isSphereCollision(object[i]->m_objCollider))
	//			{
	//				if (object[i]->isPlayer)
	//				{
	//					object[j]->m_objCollider->isActive = false;
	//				}
	//				else
	//				{
	//					object[i]->m_objCollider->isActive = false;
	//				}
	//			}
	//		}
	//		else if (object[i]->m_objCollider->GetColliderType() == POLYGON)
	//		{
	//			if (object[j]->m_objCollider->isPolygonCollision(object[i]->m_objCollider))
	//			{
	//				if (object[i]->isPlayer)
	//				{
	//					object[j]->m_objCollider->isActive = false;
	//				}
	//				else
	//				{
	//					object[i]->m_objCollider->isActive = false;
	//				}
	//			}
	//		}
	//	}
	//}
}
