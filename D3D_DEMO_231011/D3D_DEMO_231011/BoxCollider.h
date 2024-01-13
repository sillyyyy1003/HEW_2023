#pragma once
#include "Collider.h"

class SphereCollider;

class BoxCollider : public Collider
{
private:

	DirectX::BoundingOrientedBox m_boxOrientedCollider;

public:

	DirectX::XMFLOAT3 m_center = {};
	DirectX::XMFLOAT3 m_extents = {};
	DirectX::XMFLOAT3 m_orientation = {};


public:

	BoxCollider();

	void InitCollider(DirectX::XMFLOAT3 center, DirectX::XMFLOAT3 extents,DirectX::XMFLOAT3 orientation, COLLISION_TYPE _type);

	void UpdateExtents();

	void UpdatePos();

	void UpdateOrientation();


	/// <summary>
	/// ����Ăяo�����A��Ԃ��X�V����֐�
	/// </summary>
	/// <param name="radius">���a</param>
	void Update() override;

	/// <summary>
	/// �����蔻��
	/// </summary>
	/// <param name="sphereCollider">����</param>
	bool isCollision(const SphereCollider& sphereCollider);
	bool isCollision(const BoxCollider& boxCollider);

	DirectX::BoundingOrientedBox GetCollider(void) { return m_boxOrientedCollider; };



};

