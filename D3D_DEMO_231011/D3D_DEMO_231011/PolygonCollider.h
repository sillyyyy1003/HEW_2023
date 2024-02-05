#pragma once
#include "Collider.h"
#include "Sprite.h"

class BoxCollider;
class SphereCollider;
class SAT;

class PolygonCollider :public Collider
{
private:

	DirectX::BoundingBox Lm_boxCollider;
	DirectX::BoundingSphere Lm_sphereCollider;
	DirectX::BoundingSphere Lm_polygonCollider;
	DirectX::XMFLOAT3 center = {};
	std::vector<Vector3> verticies;
	DirectX::XMFLOAT3 rotation;
	std::vector<Vector3> m_verticies;
	float radius = 0.0f;

public:

	//DirectX::XMFLOAT3 m_center = {};
	//DirectX::XMFLOAT3 m_extents = {};
	//float m_radius = 0.0f;

public:

	/// <summary>
	/// �����P�F���W�@�����Q�F���a
	/// </summary>
	/// <param name="center"></param>
	/// <param name="Radius"></param>
	PolygonCollider(DirectX::XMFLOAT3 center, float Radius);

	void InitCollider(DirectX::XMFLOAT3 center, float Radius);

	//void UpdateRadius(float m_radius);
	void SetRadius(float m_radius);

	void UpdatePos(DirectX::XMFLOAT3 m_center);

	void UpdateRotation(DirectX::XMFLOAT3 m_rotation);

	void UpdateVerticies();

	std::vector<Vector3> GetVerticies() override;

	void SetVerticies(std::vector<Vector3> ver);

	/// <summary>
	/// ����Ăяo�����A��Ԃ��X�V����֐�
	/// </summary>
	/// <param name="radius">���a</param>
	void Update(DirectX::XMFLOAT3 m_center, DirectX::XMFLOAT3 m_rotation) override;

	/// <summary>
	/// �����蔻��
	/// </summary>
	/// <param name="sphereCollider">����</param>
	bool isBoxCollision(Collider* boxCollider) override ;
	bool isSphereCollision(Collider* sphereCollider) override;
	bool isPolygonCollision(Collider* polygoncollider) override;

	std::vector<Vector3> SetTriangle(float radius);
	std::vector<Vector3> SetSquare(float _widthX, float _widthY);
	std::vector<Vector3> SetCircle(float radius);

	struct Point {
		float x, y;
	};

	struct Triangle {
		Point A, B, C;
	};

	struct SQURE {
		Point A, B, C, D;
	};
};

#pragma once
#include "Collider.h"
#include "Sprite.h"

class BoxCollider;
class SphereCollider;
class SAT;

class PolygonCollider :
    public Collider
{
private:

	DirectX::BoundingBox Lm_boxCollider;
	DirectX::BoundingSphere Lm_sphereCollider;
	DirectX::BoundingSphere Lm_polygonCollider;
	DirectX::XMFLOAT3 center = {};
	std::vector<Vector3> verticies;
	std::vector<Vector3> Clearverticies;
	DirectX::XMFLOAT3 rotation;
	std::vector<Vector3> m_verticies;
	float radius = 0.0f;

public:

	//DirectX::XMFLOAT3 m_center = {};
	//DirectX::XMFLOAT3 m_extents = {};
	//float m_radius = 0.0f;

public:

	/// <summary>
	/// �����P�F���W�@�����Q�F���a
	/// </summary>
	/// <param name="center"></param>
	/// <param name="Radius"></param>
	PolygonCollider(DirectX::XMFLOAT3 center, float Radius);

	void InitCollider(DirectX::XMFLOAT3 center, float Radius);

	//void UpdateRadius(float m_radius);
	void SetRadius(float m_radius);

	void UpdatePos(DirectX::XMFLOAT3 m_center);

	void UpdateRotation(DirectX::XMFLOAT3 m_rotation);

	void UpdateVerticies();

	std::vector<Vector3> GetVerticies() override;

	void SetVerticies(std::vector<Vector3> ver);

	/// <summary>
	/// ����Ăяo�����A��Ԃ��X�V����֐�
	/// </summary>
	/// <param name="radius">���a</param>
	void Update(DirectX::XMFLOAT3 m_center, DirectX::XMFLOAT3 m_rotation) override;

	/// <summary>
	/// �����蔻��
	/// </summary>
	/// <param name="sphereCollider">����</param>
	bool isBoxCollision(Collider* boxCollider) override ;
	bool isSphereCollision(Collider* sphereCollider) override;
	bool isPolygonCollision(Collider* polygoncollider) override;

	bool isClearCollision(Collider* polygoncollider, float verNum) override;

	//std::vector<Vector3> SetTriangle(float radius);
	//std::vector<Vector3> SetSquare(float _widthX, float _widthY);
	//std::vector<Vector3> SetCircle(float radius);

	//struct Point {
	//	float x, y;
	//};

	//struct Triangle {
	//	Point A, B, C;
	//};

	//struct SQURE {
	//	Point A, B, C, D;
	//};
};

