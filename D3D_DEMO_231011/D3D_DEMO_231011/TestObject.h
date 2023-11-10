#pragma once
#include "Sprite.h"

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


public:

	TestObject();

	//�I�u�W�F�N�g�p�e�N�X�`���̃Z�b�e�B���O
	void SetObjTex(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY);

	//�e�p�̃e�N�X�`���̃Z�b�e�B���O
	void SetShadowTex(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY);

	virtual void Update(void);

	void Draw(void);

	~TestObject();



};

