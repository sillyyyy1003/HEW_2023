#pragma once
#include "Collider.h"


class SphereCollider;
class PolygonCollider;
class Material;

class BoxCollider : public Collider
{
private:

	//std::vector<Vector3> m_verticies;
	

	//オブジェクトの回転もあるのでOBBを使う
	DirectX::BoundingOrientedBox m_boxCollider;

public:

	/// <summary>
	/// 引数１：座標　引数２：四角形の幅
	/// </summary>
	/// <param name="center"></param>
	/// <param name="extents">中心点はモデル作成の時もうつけてるから要りません</param>
	BoxCollider();

	void InitCollider(DirectX::XMFLOAT3 center, Collide collider) override;

	//std::vector<Vector3> GetSquareVerticies(void);
	std::vector<DirectX::XMFLOAT3> InitVerticies(void);//最初の頂点データを作る

	//四角形の幅を更新する関数
	void UpdateExtents(DirectX::XMFLOAT3 extents);
	//四角形の位置を更新する関数
	void UpdatePos(DirectX::XMFLOAT3 m_center);
	//四角形の回転を更新する関数
	void UpdateRotation(DirectX::XMFLOAT3 rotation);
	//頂点のデータを獲得
	void UpdateVerticies(DirectX::XMFLOAT3 rotation);


	/// <summary>
	/// 毎回呼び出される、状態を更新する関数
	/// </summary>
	/// <param name="radius">半径</param>
	void Update(DirectX::XMFLOAT3 center, DirectX::XMFLOAT3 rotation, DirectX::XMFLOAT3 extents) override;

	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <param name="sphereCollider">球体</param>
	bool isCollision(SphereCollider* collider) override;


	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <param name="sphereCollider">四角形</param>
	bool isCollision(BoxCollider* collider) override;

	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <param name="sphereCollider">Polygon</param>
	bool isCollision(PolygonCollider* collider) override;

	bool isCollision(Collider* collider) override;


	DirectX::BoundingOrientedBox GetCollider(void) { return m_boxCollider; };

	//bool isClearCollision(Collider* polygoncollider, float verNum)override;

	//頂点データ
	//void SetVerticies(std::vector<Vector3> ver) { m_verticies = ver; };

	//std::vector<Vector3> GetVerticies() override{ return m_verticies; };
};

