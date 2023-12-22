#pragma once
#include "Sprite.h"

class ShadowObject
{
public:
	//----------------------------//
	// 変数
	//----------------------------//
	
	//図形情報を扱う
	Sprite* m_obj;

	//光に当てられたか
	bool isLight = true;

	
public:
	//Constructor
	ShadowObject(void);

	//影のモデル作成
	void CreateShadow(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY);

	//
	void Update(void);

	//描画関数
	void Draw(void);

	~ShadowObject(void);

};

