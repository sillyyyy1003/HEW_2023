#include "StaticAnimation.h"

StaticAnimation::StaticAnimation(int splitX, int splitY) :Animation(splitX, splitY)
{
}

void StaticAnimation::Update(void)
{
	Animation::Update();
}
