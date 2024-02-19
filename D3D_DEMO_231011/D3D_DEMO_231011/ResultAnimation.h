#pragma once
#include "Result.h"
#include "CanvasUI.h"

class ResultAnimation
{
private:
	// �摜�P
	CanvasUI* clear1;
	// �摜�Q
	CanvasUI* clear2;
	// �摜�R
	CanvasUI* clear3;
	// �X�L�b�v�{�^��
	CanvasUI* skip;

	//�Q���ڂ̉摜��\������܂ł̑ҋ@���Ԃ��Ǘ�����ϐ�
	float waitcount = 0;
	//�R���ڂ̉摜��\������܂ł̑ҋ@���Ԃ��Ǘ�����ϐ�
	float waitcount2 = 0;

public :
	bool isAnimated = false;
public:
	ResultAnimation();

	~ResultAnimation();

	// �X�e�[�W���ɉ摜��ݒ肷��
	void SetTexture(ID3D11ShaderResourceView* clear1, ID3D11ShaderResourceView* clear2, ID3D11ShaderResourceView* clear3);

	// �C�ӂ̃^�C�~���O�ŏ�����
	void Init();

	void Update();

	void Draw();

	// �摜�̈ړ�
	bool Move();
};

