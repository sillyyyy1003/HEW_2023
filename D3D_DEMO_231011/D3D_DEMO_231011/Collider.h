#pragma once
#include <DirectXCollision.h>


enum COLLISION_TYPE {
	IDLE,			//NULL
	SPHERE,			//球体
	SQUARE,			//BOX
	POLYGON,		//ポリゴン
};


class Collider
{
protected:

	COLLISION_TYPE m_collisionType = IDLE;

	

public:

	//コライダーは起動しているか
	bool isActive = false;

public:

	Collider();

	//コライダーの初期化処理を行う関数
	virtual void InitCollider(COLLISION_TYPE _type);

	//コライダーの更新を行う
	virtual void Update();

	COLLISION_TYPE GetColliderType(void) { return m_collisionType; };

	~Collider(void);

};

