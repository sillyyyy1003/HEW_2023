#pragma once
#include "Animation.h"

/// <summary>
/// �Î~�摜�Ɏg����
/// </summary>
class StaticAnimation :public Animation
{
public:

	StaticAnimation(int splitX, int splitY);

	void Update(void) override;

};

