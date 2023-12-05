#pragma once
#include "Animation.h"


class ObjectAnimation :public Animation
{


public:

	ObjectAnimation(int splitX, int splitY);

	/// <summary>
	/// この中にanimeTableを変更
	/// </summary>
	void Update(void) override;

	
};

