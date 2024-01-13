#pragma once
#include "Object.h"

class ShadowObject :public Object
{
public:
	//----------------------------//
	// 変数
	//----------------------------//
	//光に当てられたか
	bool isLight = true;

	
public:
	//Constructor
	ShadowObject(void);

	//影のモデル作成->基底クラスで行う
	/*void CreateShadow(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY)*/;

	//game loopで毎回呼び出される関数
	void Update(void) override;

	//描画関数
	void Draw(void) override;

	~ShadowObject(void);

};

