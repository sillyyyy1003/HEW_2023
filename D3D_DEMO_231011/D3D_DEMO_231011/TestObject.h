#pragma once
#include "Sprite.h"

// �~�̓����蔻��̈��\���\����
struct BOUNDING_CIRCLE
{
	DirectX::XMFLOAT3 center; // ���S�_�̍��W
	float radius; // ���a�̒���
};


//����
class TestObject :public Sprite
{
public:
	//----------------------------//
	// �ϐ�
	//----------------------------//
	//�}�`���������Ă���
	Sprite* m_objSprite;
	Sprite* m_shadowSprite;

	//���݂̌�����\���x�N�g���ϐ�
	DirectX::XMFLOAT3 m_dir = { 0.0f,0.0f,0.0f };

	//����ł��邩�ǂ����������ϐ�
	bool isActive = false;


public:

	TestObject();

	//�I�u�W�F�N�g�p�e�N�X�`���̃Z�b�e�B���O
	void SetObjTex(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY);

	//�e�p�̃e�N�X�`���̃Z�b�e�B���O
	void SetShadowTex(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY);

	// �����蔻��
	// �~�̍��W�Ɣ��a���擾
	BOUNDING_CIRCLE GetBoundingCircle();
	// �~�̍��W�Ɣ��a��ݒ�
	void SetBoundingCircle(BOUNDING_CIRCLE bc);

	// ���삷��I�u�W�F�N�g���ǂ���
	bool isPlayer = false;

	virtual void Update(void);

	void Draw(void);

	~TestObject();

	// �I�u�W�F�N�g�̃X�P�[�����傫���Ȃ����Ƃ��̓����蔻��p�̕ϐ�
	float Scale_countX = 0;
	float Scale_countY = 0;
};

