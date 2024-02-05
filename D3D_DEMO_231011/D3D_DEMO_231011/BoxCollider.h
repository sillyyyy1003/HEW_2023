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
	/// �����P�F���W�@�����Q�F�l�p�`�̕�
	/// </summary>
	/// <param name="center"></param>
	/// <param name="extents"></param>
	BoxCollider(DirectX::XMFLOAT3 center, DirectX::XMFLOAT3 extents);

	void InitCollider(DirectX::XMFLOAT3 center, DirectX::XMFLOAT3 extents);

	void UpdateExtents();

	void UpdatePos(DirectX::XMFLOAT3 m_center);

	/// <summary>
	/// ����Ăяo�����A��Ԃ��X�V����֐�
	/// </summary>
	/// <param name="radius">���a</param>
	void Update(DirectX::XMFLOAT3 m_center, DirectX::XMFLOAT3 m_rotation) override;

	/// <summary>
	/// �����蔻��
	/// </summary>
	/// <param name="sphereCollider">����</param>
	bool isSphereCollision(Collider* sphereCollider) override;
	bool isBoxCollision(Collider* boxCollider) override;
	bool isClearCollision(Collider* polygoncollider, float verNum)override;

	//DirectX::BoundingBox GetCollider(void) { return m_boxCollider; };

	void SetVerticies(std::vector<Vector3> ver) { m_verticies = ver; };
	std::vector<Vector3> GetVerticies() override{ return m_verticies; };
};

