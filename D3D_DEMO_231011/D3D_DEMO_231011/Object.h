#pragma once
#include "Sprite.h"

//�I�u�W�F�N�g���
class Object
{
public:
	//----------------------------//
	// �ϐ�
	//----------------------------//
	//�}�`���������Ă���
	Sprite* m_sprite;



public:
	
	// �R���X�g���N�^���������s��
	Object(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY);

	//�A�j���[�V�����̍X�V���s��
	virtual void Update(void);
	
	// �Еt������
	~Object(void);
};

