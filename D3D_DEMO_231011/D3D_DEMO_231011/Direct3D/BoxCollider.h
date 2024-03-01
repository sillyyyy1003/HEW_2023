#pragma once
#include "Collider.h"


class SphereCollider;
class PolygonCollider;
class Material;

class BoxCollider : public Collider
{
private:

	//std::vector<Vector3> m_verticies;
	

	//�I�u�W�F�N�g�̉�]������̂�OBB���g��
	DirectX::BoundingOrientedBox m_boxCollider;

public:

	/// <summary>
	/// �����P�F���W�@�����Q�F�l�p�`�̕�
	/// </summary>
	/// <param name="center"></param>
	/// <param name="extents">���S�_�̓��f���쐬�̎��������Ă邩��v��܂���</param>
	BoxCollider();

	void InitCollider(DirectX::XMFLOAT3 center, Collide collider) override;

	//std::vector<Vector3> GetSquareVerticies(void);
	std::vector<DirectX::XMFLOAT3> InitVerticies(void);//�ŏ��̒��_�f�[�^�����

	//�l�p�`�̕����X�V����֐�
	void UpdateExtents(DirectX::XMFLOAT3 extents);
	//�l�p�`�̈ʒu���X�V����֐�
	void UpdatePos(DirectX::XMFLOAT3 m_center);
	//�l�p�`�̉�]���X�V����֐�
	void UpdateRotation(DirectX::XMFLOAT3 rotation);
	//���_�̃f�[�^���l��
	void UpdateVerticies(DirectX::XMFLOAT3 rotation);


	/// <summary>
	/// ����Ăяo�����A��Ԃ��X�V����֐�
	/// </summary>
	/// <param name="radius">���a</param>
	void Update(DirectX::XMFLOAT3 center, DirectX::XMFLOAT3 rotation, DirectX::XMFLOAT3 extents) override;

	/// <summary>
	/// �����蔻��
	/// </summary>
	/// <param name="sphereCollider">����</param>
	bool isCollision(SphereCollider* collider) override;


	/// <summary>
	/// �����蔻��
	/// </summary>
	/// <param name="sphereCollider">�l�p�`</param>
	bool isCollision(BoxCollider* collider) override;

	/// <summary>
	/// �����蔻��
	/// </summary>
	/// <param name="sphereCollider">Polygon</param>
	bool isCollision(PolygonCollider* collider) override;

	bool isCollision(Collider* collider) override;


	DirectX::BoundingOrientedBox GetCollider(void) { return m_boxCollider; };

	//bool isClearCollision(Collider* polygoncollider, float verNum)override;

	//���_�f�[�^
	//void SetVerticies(std::vector<Vector3> ver) { m_verticies = ver; };

	//std::vector<Vector3> GetVerticies() override{ return m_verticies; };
};

