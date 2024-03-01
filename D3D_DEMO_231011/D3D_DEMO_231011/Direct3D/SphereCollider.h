#pragma once
#include "Collider.h"
#include "Sprite.h"

class BoxCollider;
class PolygonCollider;

/// <summary>
/// 球体コライダー
/// </summary>
class SphereCollider :public Collider
{
private:

	std::vector<Vector3> m_verticies;

public:

	DirectX::BoundingSphere m_sphereCollider;
	
public:

	/// <summary>
	/// 引数１：座標　引数２：半径
	/// </summary>
	/// <param name="center"></param>
	/// <param name="Radius"></param>
	SphereCollider();

	//std::vector<Vector3> SetCircle();

	void InitCollider(DirectX::XMFLOAT3 center, Collide collider) override;

	void UpdateRadius(float radius);
	void UpdatePos(DirectX::XMFLOAT3 m_center);
	void UpdateVerticies(void);

	/// <summary>
	/// 毎回呼び出される、状態を更新する関数
	/// </summary>
	/// <param name="radius">半径</param>
	void Update(DirectX::XMFLOAT3 center, DirectX::XMFLOAT3 rotation, DirectX::XMFLOAT3 extents)override;

	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <param name="BoxCollider">OBB</param>
	bool isCollision(BoxCollider* boxCollider) override;
	
	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <param name="sphereCollider">球体</param>
	bool isCollision(SphereCollider* sphereCollider)override;

	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <param name="sphereCollider">三角形</param>
	bool isCollision(PolygonCollider* polygonCollider)override;

	//
	bool isCollision(Collider* Collider) override;

	//コライダーを返す
	DirectX::BoundingSphere GetCollider() { return m_sphereCollider; };

	//bool isClearCollision(Collider* polygoncollider, float verNum);

	//void SetVerticies(std::vector<Vector3> ver) { m_verticies = ver; };
	//std::vector<Vector3> GetVerticies() override { return m_verticies; };

};