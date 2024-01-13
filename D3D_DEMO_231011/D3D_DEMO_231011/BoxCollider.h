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
	/// 毎回呼び出される、状態を更新する関数
	/// </summary>
	/// <param name="radius">半径</param>
	void Update() override;

	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <param name="sphereCollider">球体</param>
	bool isCollision(const SphereCollider& sphereCollider);
	bool isCollision(const BoxCollider& boxCollider);

	DirectX::BoundingOrientedBox GetCollider(void) { return m_boxOrientedCollider; };



};

