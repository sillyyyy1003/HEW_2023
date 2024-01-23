#pragma once
#include <DirectXCollision.h>


enum COLLISION_TYPE {
	IDLE,			//NULL
	SPHERE,			//����
	SQUARE,			//BOX
	POLYGON,		//�|���S��
};


class Collider
{
protected:

	COLLISION_TYPE m_collisionType = IDLE;

	

public:

	//�R���C�_�[�͋N�����Ă��邩
	bool isActive = false;

public:

	Collider();

	//�R���C�_�[�̏������������s���֐�
	virtual void InitCollider(COLLISION_TYPE _type);

	//�R���C�_�[�̍X�V���s��
	virtual void Update();

	COLLISION_TYPE GetColliderType(void) { return m_collisionType; };

	~Collider(void);

};

