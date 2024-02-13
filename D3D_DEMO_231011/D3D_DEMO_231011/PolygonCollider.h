#pragma once
#include "Collider.h"
#include "Sprite.h"

class BoxCollider;
class SphereCollider;
class SAT;



class PolygonCollider :public Collider
{
private:

	//std::vector<Vector3> m_verticies;//多辺形に使う
	
	//改良の頂点
	std::vector<DirectX::XMFLOAT3> m_verticies;

	TRIANGLE_TYPE m_type = TRIANGLE_TYPE::TRI_IDLE;

	

public:

	/// <summary>
	/// 引数１：座標　引数２：半径
	/// </summary>
	/// <param name="center"></param>
	/// <param name="Radius"></param>
	PolygonCollider();

	void InitCollider(DirectX::XMFLOAT3 center,Collide Collider, TRIANGLE_TYPE type);

	//三角形の頂点を初期化
	//std::vector<Vector3> GetTriangleVertices(void);
	std::vector<DirectX::XMFLOAT3> InitVerticies();

	//void UpdateRadius(float m_radius);
	void SetRadius(float radius) { m_radius = radius; };

	void UpdatePos(DirectX::XMFLOAT3 m_center);

	void UpdateRotation(DirectX::XMFLOAT3 rotation);

	void UpdateExtents(DirectX::XMFLOAT3 extents);

	//廃棄
	//void UpdateVerticies(DirectX::XMFLOAT3 rotation);

	std::vector<Vector3> GetVerticies();
	std::vector<DirectX::XMFLOAT3> GetXMVerticies() { return m_verticies; };

	void SetVerticies(std::vector<Vector3> ver);

	/// <summary>
	/// 毎回呼び出される、状態を更新する関数
	/// </summary>
	/// <param name="radius">半径</param>
	void Update(DirectX::XMFLOAT3 center, DirectX::XMFLOAT3 rotation, DirectX::XMFLOAT3 extents) override;

	/// <summary>
	/// あたり判定
	/// </summary>
	/// <param name="collider">OBB</param>
	bool isCollision(BoxCollider* collider) override;

	/// <summary>
	///あたり判定
	///</summary>
	///<param name="collider">OBB</param>
	bool isCollision(SphereCollider* collider) override;

	/// <summary>
	///あたり判定
	///</summary>
	///<param name="collider">OBB</param>
	bool isCollision(PolygonCollider* collider) override;

	bool isCollision(Collider* collider) override;

	/// <summary>
	/// 当たり判定
	/// </summary>
	/// <param name="sphereCollider">球体</param>
	//bool isBoxCollision(Collider* boxCollider) override ;
	//bool isSphereCollision(Collider* sphereCollider) override;
	//bool isPolygonCollision(Collider* polygoncollider) override;

	//bool isClearCollision(Collider* polygoncollider, float verNum) override;


};

