#pragma once
#include "Result.h"
#include "CanvasUI.h"

class ResultAnimation
{
private:
	// スキップボタン
	CanvasUI* skip;

	//２枚目の画像を表示するまでの待機時間を管理する変数
	float waitcount = 0;
	//３枚目の画像を表示するまでの待機時間を管理する変数
	float waitcount2 = 0;

public :
	bool isAnimated = false;
public:
	ResultAnimation();

	~ResultAnimation();

	// 任意のタイミングで初期化
	void Init();

	void Update(CanvasUI* clear1, CanvasUI* clear2, CanvasUI* clear3);

	void Draw(CanvasUI* clear1, CanvasUI* clear2, CanvasUI* clear3);

	// 画像の移動
	bool Move(CanvasUI* clear1, CanvasUI* clear2, CanvasUI* clear3);
};

