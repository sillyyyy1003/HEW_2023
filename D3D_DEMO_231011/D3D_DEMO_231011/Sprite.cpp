#include "Sprite.h"

Sprite::Sprite(ID3D11ShaderResourceView* texture, float _width, float _height, float splitX, float splitY)
{
	const float left = -(_width / 2.0f); 
	const float right = _width / 2.0f;
	const float top = _height / 2.0f;;
	const float bottom = -(_height / 2.0f);
	const float z = 0.0f;

	const float u = 1.0 / splitX;
	const float v = 1.0 / splitY;
	

	VERTEX VertexList[] = {

		{left,top,z,0.0f,0.0f},//左上
		{right,bottom,z,u,v};
		{},
		{},
		{},
		{},






	};





	//テクスチャを実装
	SetTexture(texture);
}
