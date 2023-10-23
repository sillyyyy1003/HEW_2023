#pragma once
#include "Sprite.h"
#include "ObjectAnimation.h"



//test 
class Object
{
public:
	//----------------------------//
	// 変数
	//----------------------------//
	//図形情報を扱われている
	Sprite* m_sprite;

	//アニメーションを扱われている
	//オブジェクト種類によって、クラス名が変わる
	ObjectAnimation* m_anime;

public:
	
	// コンストラクタ＝初期化行う
	Object(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY);

	//アニメーションの更新を行う
	virtual void Update(void);
	
	// 片付け処理
	~Object(void);
};

