#pragma once
#include "Animation.h"


class ObjectAnimation :public Animation
{
public:

	ObjectAnimation(int splitX, int splitY);


	/// <summary>
	/// ���̒���animeTable��ύX
	/// </summary>
	void Update(void) override;

	
};

