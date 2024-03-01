#pragma once
#include "Collider.h"
#include "Sprite.h"

class BoxCollider;
class PolygonCollider;

/// <summary>
/// ���̃R���C�_�[
/// </summary>
class SphereCollider :public Collider
{
private:

	std::vector<Vector3> m_verticies;

public:

	DirectX::BoundingSphere m_sphereCollider;
	
public:

	/// <summary>
	/// �����P�F���W�@�����Q�F���a
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
	/// ����Ăяo�����A��Ԃ��X�V����֐�
	/// </summary>
	/// <param name="radius">���a</param>
	void Update(DirectX::XMFLOAT3 center, DirectX::XMFLOAT3 rotation, DirectX::XMFLOAT3 extents)override;

	/// <summary>
	/// �����蔻��
	/// </summary>
	/// <param name="BoxCollider">OBB</param>
	bool isCollision(BoxCollider* boxCollider) override;
	
	/// <summary>
	/// �����蔻��
	/// </summary>
	/// <param name="sphereCollider">����</param>
	bool isCollision(SphereCollider* sphereCollider)override;

	/// <summary>
	/// �����蔻��
	/// </summary>
	/// <param name="sphereCollider">�O�p�`</param>
	bool isCollision(PolygonCollider* polygonCollider)override;

	//
	bool isCollision(Collider* Collider) override;

	//�R���C�_�[��Ԃ�
	DirectX::BoundingSphere GetCollider() { return m_sphereCollider; };

	//bool isClearCollision(Collider* polygoncollider, float verNum);

	//void SetVerticies(std::vector<Vector3> ver) { m_verticies = ver; };
	//std::vector<Vector3> GetVerticies() override { return m_verticies; };

};