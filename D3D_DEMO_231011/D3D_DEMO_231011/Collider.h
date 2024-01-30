#pragma once
#include <DirectXCollision.h>
#include "SatCollider.h"

enum COLLISION_TYPE {
	POLYGON,		//�|���S��
	SPHERE,			//����
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

	//�R���C�_�[�͋N�����Ă��邩
	bool isActive = false;

	float m_radius = 0.0f;
public:

	Collider();

	virtual std::vector<Vector3> GetVerticies();

	//�R���C�_�[�̏������������s���֐�
	virtual void InitCollider(COLLISION_TYPE _type);

	//�R���C�_�[�̍X�V���s��
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

