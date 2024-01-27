#pragma once
#include "PolygonCollider.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "Game.h"

class ColliderManager
{

public:

	ColliderManager();

	~ColliderManager();

	void Update(Collider* collider);

	static void Collision(GameObject* object);
};

