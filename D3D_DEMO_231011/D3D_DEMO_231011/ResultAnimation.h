#pragma once
#include "Result.h"

class ResultAnimation
{
private:
	// ‰æ‘œ‚P
	CanvasUI* clear1_1_1;
	// ‰æ‘œ‚Q
	CanvasUI* clear1_1_2;
	// ‰æ‘œ‚R
	CanvasUI* clear1_1_3;

public :
	bool isAnimated = false;
public:
	ResultAnimation();

	~ResultAnimation();

	// ”CˆÓ‚Ìƒ^ƒCƒ~ƒ“ƒO‚Å‰Šú‰»
	void Init();

	void Update();

	void Draw();

	// ‰æ‘œ‚ÌˆÚ“®
	bool Move();
};

