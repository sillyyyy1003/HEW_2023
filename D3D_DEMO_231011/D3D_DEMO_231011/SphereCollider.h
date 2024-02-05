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

public:

	DirectX::XMFLOAT3 m_center = {};
	//float m_radius = 0.0f;
	//float m_radius = 0.0f;

public:

	/// <summary>
	/// 引数１：座標　引数２：半径
	/// </summary>
	/// <param name="center"></param>
	/// <param name="Radius"></param>
	SphereCollider(DirectX::XMFLOAT3 center, float Radius);

	void InitCollider(DirectX::XMFLOAT3 center, float Radius);

	////void UpdateRadius();
	void UpdateRadius(float Radius);
	void UpdateRadius(float Radius);

	void UpdatePos(DirectX::XMFLOAT3 m_center);

	/// <summary>
	/// 毎回呼び出される、状態を更新する関数
	/// </summary>
	/// <param name="radius">半径</param>
	void Update(DirectX::XMFLOAT3 m_center, DirectX::XMFLOAT3 m_rotation) override;

	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <param name="sphereCollider">球体</param>
	bool isSphereCollision(Collider* sphereCollider) override;
	bool isBoxCollision(Collider* boxCollider) override;
};

