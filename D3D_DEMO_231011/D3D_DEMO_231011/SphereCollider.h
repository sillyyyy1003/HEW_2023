#pragma once
#include "Collider.h"
#include "Sprite.h"

class BoxCollider;

/// <summary>
/// 球体コライダー
/// </summary>
class SphereCollider :public Collider
{
private:
	

	DirectX::BoundingSphere m_sphereCollider;
	

public:

	DirectX::XMFLOAT3 m_center = {};
	float m_radius = 0.0f;

public:

	SphereCollider();

	void InitCollider(DirectX::XMFLOAT3 center, float Radius);

	void UpdateRadius();

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


	DirectX::BoundingSphere GetCollider(void) { return m_sphereCollider; };

	
};

