#pragma once
#include "Direct3D/Direct3D.h"
class Sprite;

//動けないオブジェクト
class StaticObject
{
private:
	//図形情報を扱う
	Sprite* m_sprite;
	
public:

	//コンストラクタ
	StaticObject(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY);

	//game loopで毎回呼び出される関数
	void Update(void);
	
	void Draw(void);

	~StaticObject(void);


};

