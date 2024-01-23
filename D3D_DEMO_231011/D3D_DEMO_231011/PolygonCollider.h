#pragma once
#include "Collider.h"
#include "Sprite.h"
#include "SatCollider.h"

class BoxCollider;
class SphereCollider;

class PolygonCollider :
    public Collider
{
private:

	DirectX::BoundingBox m_boxCollider;
	DirectX::BoundingSphere m_sphereCollider;
	DirectX::XMFLOAT3 center = {};
	std::vector<Vector2> verticies;
	float radius = 0.0f;

public:

	DirectX::XMFLOAT3 m_center = {};
	DirectX::XMFLOAT3 m_extents = {};
	float m_radius = 0.0f;

public:

	PolygonCollider();

	void InitCollider(DirectX::XMFLOAT3 center, float Radius, COLLISION_TYPE _type);

	void UpdateRadius();

	void UpdatePos();

	void UpdateVerticies();

	/// <summary>
	/// ����Ăяo�����A��Ԃ��X�V����֐�
	/// </summary>
	/// <param name="radius">���a</param>
	void Update() override;

	/// <summary>
	/// �����蔻��
	/// </summary>
	/// <param name="sphereCollider">����</param>
	bool SATBoxHit(BoxCollider* boxCollider);
	bool SATCircleHit(SphereCollider* sphereCollider);

	std::vector<Vector2> SetTriangle(float radius);
	std::vector<Vector2> SetSquare(float _widthX, float _widthY);
	std::vector<Vector2> SetCircle(float radius);

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

