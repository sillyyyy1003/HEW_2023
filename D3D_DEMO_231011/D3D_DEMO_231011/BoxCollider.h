#pragma once
#include "Collider.h"

class SphereCollider;
class PolygonCollider;

class BoxCollider : public Collider
{
private:
	std::vector<Vector3> verticies;
	std::vector<Vector3> m_verticies;
public:

	//DirectX::XMFLOAT3 m_center = {};
	DirectX::XMFLOAT3 m_extents = {};

public:

	/// <summary>
	/// 引数１：座標　引数２：四角形の幅
	/// </summary>
	/// <param name="center"></param>
	/// <param name="extents"></param>
	BoxCollider(DirectX::XMFLOAT3 center, DirectX::XMFLOAT3 extents);

	void InitCollider(DirectX::XMFLOAT3 center, DirectX::XMFLOAT3 extents);

	void UpdateExtents();

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
	bool isClearCollision(Collider* polygoncollider, float verNum)override;

	//DirectX::BoundingBox GetCollider(void) { return m_boxCollider; };

	void SetVerticies(std::vector<Vector3> ver) { m_verticies = ver; };
	std::vector<Vector3> GetVerticies() override{ return m_verticies; };
};

