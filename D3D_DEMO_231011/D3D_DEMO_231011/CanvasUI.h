#pragma once
#include "Sprite.h"

class CanvasUI :public Sprite
{

public:
	CanvasUI();

	~CanvasUI();

	//���f���쐬�E�A�j���[�V�����z�u�E�J�����g�p
	void CreateModel(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY) override;

	//UV���W�X�V
	void Update(void);

};

