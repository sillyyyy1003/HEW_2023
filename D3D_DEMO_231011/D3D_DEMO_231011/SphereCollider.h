#pragma once
#include "Collider.h"
#include "Sprite.h"

class BoxCollider;

/// <summary>
/// ���̃R���C�_�[
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
	/// �����P�F���W�@�����Q�F���a
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
};

