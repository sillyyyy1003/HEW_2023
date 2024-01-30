#pragma once
#include <DirectXCollision.h>
#include "SatCollider.h"

enum COLLISION_TYPE {
	POLYGON,		//ポリゴン
	SPHERE,			//球体
	SQUARE,			//BOX
	IDLE,			//NULL
};


class Collider
{
protected:

	COLLISION_TYPE m_collisionType = IDLE;

public:
	DirectX::BoundingSphere m_sphereCollider;

	DirectX::BoundingSphere m_polygonCollider;

	DirectX::BoundingBox m_boxCollider;
	//DirectX::XMFLOAT3 m_extents = {};

public:

	//コライダーは起動しているか
	bool isActive = false;

	float m_radius = 0.0f;
public:

	Collider();

	virtual std::vector<Vector3> GetVerticies();

	//コライダーの初期化処理を行う関数
	virtual void InitCollider(COLLISION_TYPE _type);

	//コライダーの更新を行う
	virtual void Update(DirectX::XMFLOAT3 m_center, DirectX::XMFLOAT3 m_rotation);

	virtual bool isSphereCollision(Collider* collider) { return false; };

	virtual bool isBoxCollision(Collider* collider) { return false; };

	virtual bool isPolygonCollision(Collider* collider) { return false; };

	COLLISION_TYPE GetColliderType(void) { return m_collisionType; };

	DirectX::BoundingSphere GetSphereCollider(void) { return m_sphereCollider; };

	DirectX::BoundingSphere GetPolygonCollider(void) { return m_polygonCollider; };
	//DirectX::BoundingSphere GetCollider(void) { return m_sphereCollider; };
	DirectX::BoundingBox GetBoxCollider(void) { return m_boxCollider; };

	~Collider(void);

};

