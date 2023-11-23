#pragma once
#include "Animation.h"

/// <summary>
/// Ã~‰æ‘œ‚Ég‚í‚ê‚é
/// </summary>
class StaticAnimation :public Animation
{
public:

	StaticAnimation(int splitX, int splitY);

	void Update(void) override;

};

