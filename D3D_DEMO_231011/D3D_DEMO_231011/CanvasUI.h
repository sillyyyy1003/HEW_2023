#pragma once
#include "Sprite.h"

class CanvasUI :public Sprite
{

public:
	CanvasUI();

	~CanvasUI();

	//モデル作成・アニメーション配置・カメラ使用
	void CreateModel(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY) override;

	//UV座標更新
	void Update(void);

};

