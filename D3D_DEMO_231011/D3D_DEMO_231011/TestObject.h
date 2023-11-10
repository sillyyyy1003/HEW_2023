#pragma once
#include "Sprite.h"

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


public:

	TestObject();

	//オブジェクト用テクスチャのセッティング
	void SetObjTex(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY);

	//影用のテクスチャのセッティング
	void SetShadowTex(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY);

	virtual void Update(void);

	void Draw(void);

	~TestObject();



};

