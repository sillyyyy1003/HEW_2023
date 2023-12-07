#pragma once
#include "Sprite.h"

// 円の当たり判定領域を表す構造体
struct BOUNDING_CIRCLE
{
	DirectX::XMFLOAT3 center; // 中心点の座標
	float radius; // 半径の長さ
};


//試作
class TestObject :public Sprite
{
public:
	//----------------------------//
	// 変数
	//----------------------------//
	//図形情報を扱われている
	Sprite* m_objSprite;
	Sprite* m_shadowSprite;

	//現在の向きを表すベクトル変数
	DirectX::XMFLOAT3 m_dir = { 0.0f,0.0f,0.0f };

	//操作できるかどうかを扱う変数
	bool isActive = false;


public:

	TestObject();

	//オブジェクト用テクスチャのセッティング
	void SetObjTex(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY);

	//影用のテクスチャのセッティング
	void SetShadowTex(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY);

	


	virtual void Update(void);

	void Draw(void);

	~TestObject();

	// オブジェクトのスケールが大きくなったときの当たり判定用の変数
	float Scale_countX = 0;
	float Scale_countY = 0;
};

