#pragma once
#include "Sprite.h"
#include "SAT.h"

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
	// 図形の頂点座標
	std::vector<Vector2> vertices;
	// 図形の角度
	float rotation = 0;
	// 図形の種類
	int object = 0;
	// 図形の頂点座標を入れる
	std::vector<Vector2> jodgevertices;
	// 図形の座標を入れる
	BOUNDING_CIRCLE p_center2;
	BOUNDING_CIRCLE p_center;
public:

	TestObject();

	//オブジェクト用テクスチャのセッティング
	void SetObjTex(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY);

	//影用のテクスチャのセッティング
	void SetShadowTex(ID3D11ShaderResourceView* texture, float _width, float _height, int splitX, int splitY);

	// 当たり判定
	// 円の座標と半径を取得
	BOUNDING_CIRCLE GetBoundingCircle();
	// 円の座標と半径を設定
	void SetBoundingCircle(BOUNDING_CIRCLE bc);

	void SetRotation(DirectX::XMFLOAT3 m_rotation);

	// 操作するオブジェクトかどうか
	bool isPlayer = false;
	// 三角形かどうか
	bool isTriangle = false;

	virtual void Update(void);

	void Draw(void);

	~TestObject();

	// オブジェクトのスケールが大きくなったときの当たり判定用の変数
	float Scale_countX = 0;
	float Scale_countY = 0;

	std::vector<Vector2> p_verticies2; // 中心点の座標
	std::vector<Vector2> p_verticies;
};

