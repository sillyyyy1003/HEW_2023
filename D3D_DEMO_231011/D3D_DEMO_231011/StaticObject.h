#pragma once
#include "Direct3D/Direct3D.h"
#include "Object.h"

class Sprite;

//動けないオブジェクト
class StaticObject :public Object 
{
private:
	
	
public:

	//コンストラクタ
	StaticObject(void);

	//モデル作成
	void CreateObject(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY);

	//game loopで毎回呼び出される関数
	void Update(void);
	
	void Draw(void);

	~StaticObject(void);


};

