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

void ColliderManager::Collision(std::vector<GameObject*> Vobject)
{
	int i = 0;
	int j = 0;
	for (auto it = Vobject.begin(); it != Vobject.end(); it++)
	{
		i = j + 1;
		for (auto it = Vobject.begin(); it != Vobject.end(); it++)
		{
			if (i == Vobject.size())
			{
				break;
			}
			if (Vobject[i]->m_shadowCollider->GetColliderType() == SQUARE)
			{
				if (Vobject[j]->m_shadowCollider->isBoxCollision(Vobject[i]->m_shadowCollider))
				{
					if (Vobject[i]->GetActive())
					{
						Vobject[j]->m_shadowCollider->isActive = false;
					}
					else
					{
						Vobject[i]->m_shadowCollider->isActive = false;
					}
				}
			}
			else if (Vobject[i]->m_shadowCollider->GetColliderType() == SPHERE)
			{
				if (Vobject[j]->m_shadowCollider->isSphereCollision(Vobject[i]->m_shadowCollider))
				{
					if (Vobject[i]->GetActive())
					{
						Vobject[j]->m_shadowCollider->isActive = false;
					}
					else
					{
						Vobject[i]->m_shadowCollider->isActive = false;
					}
				}
			}
			else if (Vobject[i]->m_shadowCollider->GetColliderType() == POLYGON)
			{
				if (Vobject[j]->m_shadowCollider->isPolygonCollision(Vobject[i]->m_shadowCollider))
				{
					if (Vobject[i]->GetActive())
					{
						Vobject[j]->m_shadowCollider->isActive = false;
					}
					else
					{
						Vobject[i]->m_shadowCollider->isActive = false;
					}
				}
			}
			i++;
		}
		j++;
	}
}

bool ColliderManager::ClearCollision(std::vector<GameObject*> Vobject, float Pobj,float Eobj, float verNum,int sizeJodge)
{
	if (Vobject[Pobj]->m_shadowCollider->isClearCollision(Vobject[Eobj]->m_shadowCollider, verNum))
	{
		if (Vobject[Eobj]->GetSize() == sizeJodge)
		{
			return true;
		}
	}

	return false;
}
