#pragma once
#include "Result.h"
#include "CanvasUI.h"

class ResultAnimation
{
private:
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

	// �C�ӂ̃^�C�~���O�ŏ�����
	void Init();

	void Update(CanvasUI* clear1, CanvasUI* clear2, CanvasUI* clear3);

	void Draw(CanvasUI* clear1, CanvasUI* clear2, CanvasUI* clear3);

	// �摜�̈ړ�
	bool Move(CanvasUI* clear1, CanvasUI* clear2, CanvasUI* clear3);
};

