#include "StaticAnimation.h"

StaticAnimation::StaticAnimation(int splitX, int splitY) :Animation(splitX, splitY)
{
}

void StaticAnimation::Update(void)
{
	
	m_frameX = 0;
	
	m_frameY = 0;

	Animation::Update();

}
