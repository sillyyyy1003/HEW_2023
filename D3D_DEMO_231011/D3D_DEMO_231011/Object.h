#pragma once
#include "Sprite.h"
#include "ObjectAnimation.h"



//test 
class Object
{
public:
	//----------------------------//
	// �ϐ�
	//----------------------------//
	//�}�`���������Ă���
	Sprite* m_sprite;

	//�A�j���[�V�����������Ă���
	//�I�u�W�F�N�g��ނɂ���āA�N���X�����ς��
	ObjectAnimation* m_anime;

public:
	
	// �R���X�g���N�^���������s��
	Object(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY);

	//�A�j���[�V�����̍X�V���s��
	virtual void Update(void);
	
	// �Еt������
	~Object(void);
};

