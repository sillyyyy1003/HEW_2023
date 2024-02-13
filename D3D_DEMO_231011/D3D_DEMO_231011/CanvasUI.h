#pragma once
#include "Sprite.h"

class CanvasUI :public Sprite
{
private:
	//�\���̐؂�ւ�
	bool isActive = true;

public:
	enum STATUS {
		ACTIVE = 0,		//�N�����Ă��鎞
		INACTIVE = 1,	//
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

	void InitPos(float x, float y, float z) { m_pos = DirectX::XMFLOAT3{ x,y,z }; };

	//�A�j���p�^�[���̕ύX
	void SetAnimeActive(STATUS status) { m_anime->SetAnimePattern(status); };
};

