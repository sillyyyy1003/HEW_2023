#pragma once
#include "Result.h"
#include "CanvasUI.h"

class ResultAnimation
{
private:
	// 画像１
	CanvasUI* clear1;
	// 画像２
	CanvasUI* clear2;
	// 画像３
	CanvasUI* clear3;
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

	// ステージ事に画像を設定する
	void SetTexture(ID3D11ShaderResourceView* clear1, ID3D11ShaderResourceView* clear2, ID3D11ShaderResourceView* clear3);

	// 任意のタイミングで初期化
	void Init();

	void Update();

	void Draw();

	// 画像の移動
	bool Move();
};

