#pragma once
#include "Sprite.h"
#include "Collider.h"

//基本オブジェクト
class Object
{
public:
	//----------------------------//
	// 変数
	//----------------------------//
	//図形情報を扱う
	Sprite* m_sprite;

	Collider* m_collider = nullptr;

public:
	
	Object(void);
	
	/// <summary>
	/// 初期化を行う関数
	/// </summary>
	/// <param name="texture"></param>
	/// <param name="_width">width</param>
	/// <param name="_height">height</param>
	/// <param name="splitX"></param>
	/// <param name="splitY"></param>
	void CreateObject(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY);

	//毎ループ呼び出される
	virtual void Update(void);

	//描画
	virtual void Draw(void);
	
	//Constructor
	~Object(void);
};

