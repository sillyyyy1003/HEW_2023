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
	
	/// <summary>
	/// �R���X�g���N�^���������s��
	/// </summary>
	/// <param name="texture"></param>
	/// <param name="_width">width</param>
	/// <param name="_height">height</param>
	/// <param name="splitX"></param>
	/// <param name="splitY"></param>
	Object(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY);

	//�A�j���[�V�����̍X�V���s��
	virtual void Update(void);

	void Draw(void);
	
	// �Еt������
	~Object(void);
};

