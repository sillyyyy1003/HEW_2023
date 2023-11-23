#pragma once
#include "Sprite.h"

class ShadowObject
{
public:
	//----------------------------//
	// 変数
	//----------------------------//
	
	Sprite* m_obj;

	bool isActive = false;

	
	
	
public:
	//Constructor
	ShadowObject(void);

	//影のモデル作成
	void CreateShadow(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY);

	//
	void Update(void);

	BOOL CheckShadow(void);

	//描画関数
	void Draw(void);

	~ShadowObject(void);

};

