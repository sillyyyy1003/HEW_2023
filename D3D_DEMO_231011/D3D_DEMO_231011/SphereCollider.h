#pragma once
#include "Collider.h"
#include "Sprite.h"

/// <summary>
/// ���̃R���C�_�[
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

	void InitCollider(DirectX::XMFLOAT3 center, float Radius, COLLISION_TYPE _type);

	void UpdateRadius();

	void UpdatePos();

	/// <summary>
	/// ����Ăяo�����A��Ԃ��X�V����֐�
	/// </summary>
	/// <param name="radius">���a</param>
	void Update() override; 

	/// <summary>
	/// �����蔻��
	/// </summary>
	/// <param name="sphereCollider">����</param>
	bool isCollision(const SphereCollider& sphereCollider);


	DirectX::BoundingSphere GetCollider(void) { return m_sphereCollider; };

	
};

