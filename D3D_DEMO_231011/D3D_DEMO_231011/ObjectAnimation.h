#pragma once
#include "Animation.h"


class ObjectAnimation :public Animation
{
public:

	ObjectAnimation(int splitX, int splitY);


	/// <summary>
	/// ‚±‚Ì’†‚ÉanimeTable‚ğ•ÏX
	/// </summary>
	void Update(void) override;

	
};

