#pragma once
#include "Animation.h"

/// <summary>
/// アニメーションがない
/// uv座標の更新を行う
/// </summary>
class StaticAnimation :public Animation
{
public:

	StaticAnimation(int splitX, int splitY);

	void Update(void) override;

};

