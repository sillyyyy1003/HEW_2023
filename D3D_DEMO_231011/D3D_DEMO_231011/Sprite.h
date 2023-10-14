#pragma once
#include "Material.h"


/// <summary>
/// 頂点データを表す構造体
/// </summary>
struct VERTEX
{

	float x, y, z;		//位置座標
	float u, v;			//テクスチャのUV座標

};

/// <summary>
/// 画像の処理と描画
/// </summary>
class Sprite :public Material
{
private:

	//スプライトの名前を設定、エラーチェックに使う
	//char m_Name[256];



public:
	//----------------------------//
	// 変数
	//----------------------------//
	VERTEX m_BaseData;

	float m_OffsetU = 0.0f;
	float m_OffsetV = 0.0f;




public:

	//----------------------------//
	// 関数のプロトタイプ宣言
	//----------------------------//

	/// <summary>
	/// モデルの作成
	/// </summary>
	/// <param name="texture">テクスチャ</param>
	/// <param name="_width">画面に描画する幅</param>
	/// <param name="_height">画面に描画する高さ</param>
	/// <param name="splitX">横分割</param>
	/// <param name="splitY">縦分割</param>
	Sprite(ID3D11ShaderResourceView* texture, float _width, float _height, float splitX, float splitY);


	virtual void Draw(void);












};

