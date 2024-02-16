#pragma once
#include "Result.h"

class ResultAnimation
{
private:
	// �摜�P
	CanvasUI* clear1_1_1;
	// �摜�Q
	CanvasUI* clear1_1_2;
	// �摜�R
	CanvasUI* clear1_1_3;

public :
	bool isAnimated = false;
public:
	ResultAnimation();

	~ResultAnimation();

	// �C�ӂ̃^�C�~���O�ŏ�����
	void Init();

	void Update();

	void Draw();

	// �摜�̈ړ�
	bool Move();
};

