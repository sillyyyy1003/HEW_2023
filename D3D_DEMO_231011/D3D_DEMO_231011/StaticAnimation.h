#pragma once
#include "Animation.h"
#include <vector>


/// <summary>
/// アニメーションがない
/// uv座標の更新を行う
/// </summary>
class StaticAnimation :public Animation
{

public:

	//ループしてるかどうか
	bool isLoop = false;

	//アニメテーブル
	std::vector<int> animeTable;

public:

	//アニメションの初期化

	StaticAnimation(int splitX, int splitY);

	void Update(void) override;

	//ループしてるかどうか
	bool GetLoop(void) { return isLoop; };
	void SetLoop(bool isLoop) { this->isLoop = isLoop; };

};

