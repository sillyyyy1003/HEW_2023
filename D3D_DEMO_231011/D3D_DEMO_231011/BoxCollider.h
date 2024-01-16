#pragma once
#include "Collider.h"

class SphereCollider;
class PolygonCollider;

class BoxCollider : public Collider
{
private:

	DirectX::BoundingBox m_boxCollider;

public:

	DirectX::XMFLOAT3 m_center = {};
	DirectX::XMFLOAT3 m_extents = {};


public:

	BoxCollider();

	void InitCollider(DirectX::XMFLOAT3 center, DirectX::XMFLOAT3 extents, COLLISION_TYPE _type);

	void UpdateExtents();

	void UpdatePos();

	/// <summary>
	/// ����Ăяo�����A��Ԃ��X�V����֐�
	/// </summary>
	/// <param name="radius">���a</param>
	void Update() override;

	/// <summary>
	/// �����蔻��
	/// </summary>
	/// <param name="sphereCollider">����</param>
	bool isCollision(SphereCollider* sphereCollider);
	bool isCollision(BoxCollider* boxCollider);
	bool isCollision(PolygonCollider* polygonCollider);

	DirectX::BoundingBox GetCollider(void) { return m_boxCollider; };



};

