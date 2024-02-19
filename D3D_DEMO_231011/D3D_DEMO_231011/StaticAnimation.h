#pragma once
#include "Animation.h"
<<<<<<< .merge_file_M3AUCD
=======
#include <vector>
>>>>>>> .merge_file_Rdpxjx

/// <summary>
/// アニメーションがない
/// uv座標の更新を行う
/// </summary>
class StaticAnimation :public Animation
{
<<<<<<< .merge_file_M3AUCD
public:

=======
	//ループしてるかどうか
	bool isLoop = false;

	//アニメテーブル
	std::vector<int> animeTable;

public:

	//アニメションの初期化
>>>>>>> .merge_file_Rdpxjx
	StaticAnimation(int splitX, int splitY);

	void Update(void) override;

<<<<<<< .merge_file_M3AUCD
=======
	//ループしてるかどうか
	bool GetLoop(void) { return isLoop; };
	void SetLoop(bool isLoop) { this->isLoop = isLoop; };

>>>>>>> .merge_file_Rdpxjx
};

