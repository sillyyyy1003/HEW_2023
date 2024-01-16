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
	/// 毎回呼び出される、状態を更新する関数
	/// </summary>
	/// <param name="radius">半径</param>
	void Update() override;

	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <param name="sphereCollider">球体</param>
	bool isCollision(SphereCollider* sphereCollider);
	bool isCollision(BoxCollider* boxCollider);
	bool isCollision(PolygonCollider* polygonCollider);

	DirectX::BoundingBox GetCollider(void) { return m_boxCollider; };



};

