#pragma once
#include <DirectXCollision.h>
#include "SatCollider.h"
#include "SatCollider.h"
#include "Material.h"

enum COLLISION_TYPE {
	TRIANGLE,		//�O�p�`
	SPHERE,			//����
	SQUARE,			//BOX
	IDLE,			//NULL
};

enum COLLISION_DIR {
	INI_STATE,	//�������
	COL_UP,		//��
	COL_DOWN,	//��
	COL_LEFT,	//��
	COL_RIGHT,	//�E
	OVERLAP,	//�d�Ȃ�
	
};

struct Collider_Dir {
	
	COLLISION_DIR horizontal;//���E
	COLLISION_DIR vertical;//�㉺

	bool operator==(const Collider_Dir& other) const {
		return (vertical == other.vertical) && (horizontal == other.horizontal);
	}
};

class BoxCollider;
class SphereCollider;
class PolygonCollider;

class Collider
{
protected:

	COLLISION_TYPE m_collisionType = COLLISION_TYPE::IDLE;

protected:

	struct Point {
		float x, y;
	};

	struct Triangle {//���v����
		Point A;//���_
		Point B;//�E
		Point C;//��
	};

	//���ォ��
	struct SQUARE {//���v����
		Point A;//����
		Point B;//�E��
		Point C;//�E��
		Point D;//����
	};


public:

	//�R���C�_�[�͋N�����Ă��邩
	bool isActive = true;
	//���S�_�̈ʒu
	DirectX::XMFLOAT3 m_center = { 0,0,0 };
	//xyz���̔��Ӓ�
	DirectX::XMFLOAT3 m_extents = { 0,0,0 };
	//���a
	float m_radius = 0.0f;




public:

	Collider();

	//virtual std::vector<Vector3> GetVerticies();

	//�R���C�_�[�̃^�C�v��ݒ�
	virtual void InitColliderType(COLLISION_TYPE _type);

	virtual void InitCollider(XMFLOAT3 center, Collide collider);

	//�R���C�_�[�̏����������Ȃ��ϐ�
	/*virtual void InitCollider(DirectX::XMFLOAT3 center, Collide collider);*/

	COLLISION_TYPE GetColliderType(void) { return m_collisionType; };

	//�R���C�_�[�̍X�V���s��
	virtual void Update(DirectX::XMFLOAT3 center, DirectX::XMFLOAT3 rotation, DirectX::XMFLOAT3 extents);


	virtual bool isCollision(BoxCollider* boxColliser) { return false;};
	virtual bool isCollision(SphereCollider* sphereCollider) { return false;  };
	virtual bool isCollision(PolygonCollider* polygonCollider) { return false;  };
	virtual bool isCollision(Collider* collider) { return false;  };

	//virtual void Update();

	//�ΏۃI�u�W�F�N�g�͂��̃I�u�W�F�N�g�̂ǂ��ɂ��邩
	Collider_Dir GetCollisionDir(Collider* collider);

	//virtual bool isClearCollision(Collider* polygoncollider, float verNum) { return false; };

	//DirectX::BoundingSphere GetSphereCollider(void) { return m_sphereCollider; };
	//void SetSphereCollider(float radius) { m_sphereCollider.Radius = radius; };

	//DirectX::BoundingSphere GetPolygonCollider(void) { return m_polygonCollider; };
	//void SetPolygonCollider(float radius) { m_polygonCollider.Radius = radius; };

	//DirectX::BoundingBox GetBoxCollider(void) { return m_boxCollider; };
	//void SetBoxCollider(DirectX::XMFLOAT3 extens) { m_boxCollider.Extents = extens; };


	~Collider(void);

};

