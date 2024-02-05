#pragma once
#include "PolygonCollider.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "Game.h"#include "PolygonCollider.h"
#include "SphereCollider.h"
#include "BoxCollider.h"
#include "Game.h"

class ColliderManager
{

public:

	ColliderManager();

	~ColliderManager();

	void Update(Collider* collider);

	static void Collision(std::vector<GameObject*> Vobject);

	// 引数１：図形のGameObjectが入ったVector 引数２：クリアの元の図形　引数３：相手の図形(操作)　引数４：クリア元の図形のどの頂点に当たり判定を付けるか
	// 引数５：判定する図形の大きさ
	static bool ClearCollision(std::vector<GameObject*> Vobject, float Pobj, float Eobj, float verNum, int sizeJodge);
};

