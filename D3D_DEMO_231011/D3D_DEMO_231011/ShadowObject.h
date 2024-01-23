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

	//game loopで毎回呼び出される関数
	void Update(void) override;

	//描画関数
	void Draw(void) override;

	~ShadowObject(void);

};

