#pragma once
#include "Sprite.h"

class CanvasUI :public Sprite
{
private:
	//�\���̐؂�ւ�
	bool isActive = true;

public:
	enum STATUS {
		ACTIVE,		//�N�����Ă��鎞
		INACTIVE,	//
	};
	

public:
	CanvasUI();

	~CanvasUI();


	//���f���쐬�E�A�j���[�V�����z�u�E�J�����g�p
	void CreateModel(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY) override;

	//UV���W�X�V
	void Update(void);

	//��Ԃ��l��
	bool GetActive(void) { return isActive; };
	//��Ԃ̐؂�ւ�
	void SetActive(bool status) { isActive = status; };

	void Draw(void) override;

	
};

