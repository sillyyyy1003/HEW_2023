#pragma once
#include "Collider.h"
#include "Sprite.h"

class BoxCollider;
class SphereCollider;
class SAT;

enum TRIANGLE_TYPE {
	TRI_RIGHT,	//���p�O�p�`
	TRI_ISO,	//�񓙕ӎO�p�`
	TRI_IDLE,
};

class PolygonCollider :public Collider
{
private:

	std::vector<Vector3> m_verticies;

	TRIANGLE_TYPE m_type = TRIANGLE_TYPE::TRI_IDLE;

public:

	/// <summary>
	/// �����P�F���W�@�����Q�F���a
	/// </summary>
	/// <param name="center"></param>
	/// <param name="Radius"></param>
	PolygonCollider();

	void InitCollider(DirectX::XMFLOAT3 center,Collide Collider);

	//�O�p�`�̒��_��������
	std::vector<Vector3> GetTriangleVertices(void);


	//void UpdateRadius(float m_radius);
	void SetRadius(float radius) { m_radius = radius; };

	void UpdatePos(DirectX::XMFLOAT3 m_center);

	void UpdateRotation(DirectX::XMFLOAT3 rotation);

	void UpdateExtents(DirectX::XMFLOAT3 extents);

	void UpdateVerticies(DirectX::XMFLOAT3 rotation);

	std::vector<Vector3> GetVerticies() override;

	void SetVerticies(std::vector<Vector3> ver);

	/// <summary>
	/// ����Ăяo�����A��Ԃ��X�V����֐�
	/// </summary>
	/// <param name="radius">���a</param>
	void Update(DirectX::XMFLOAT3 center, DirectX::XMFLOAT3 rotation, DirectX::XMFLOAT3 extents) override;

	bool isCollision(BoxCollider* collider);

	/// <summary>
	/// �����蔻��
	/// </summary>
	/// <param name="sphereCollider">����</param>
	//bool isBoxCollision(Collider* boxCollider) override ;
	//bool isSphereCollision(Collider* sphereCollider) override;
	//bool isPolygonCollision(Collider* polygoncollider) override;

	//bool isClearCollision(Collider* polygoncollider, float verNum) override;


};

