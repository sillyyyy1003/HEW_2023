#pragma once
#include"Object.h"

//ui�Ɏg���Ă�I�u�W�F�N�g
class UiObject:public Object
{
public:
	//������
	UiObject(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY);

	//
};

