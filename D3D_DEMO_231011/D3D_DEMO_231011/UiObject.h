#pragma once
#include"Object.h"

//uiに使われてるオブジェクト
class UiObject: public Object
{
public:
	//初期化
	UiObject(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY);

	//
};

