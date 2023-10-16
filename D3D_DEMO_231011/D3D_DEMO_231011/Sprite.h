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
	//モデルの情報を格納する変数
	VERTEX m_BaseData;

	//回転
	DirectX::XMFLOAT3 m_rotation = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);

	//画像の大きさ(Default Data:1.0)
	DirectX::XMFLOAT3 m_scale = DirectX::XMFLOAT3(1.0, 1.0f, 1.0f);



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

	/// <summary>
	/// シェーダーに渡す行列の処理を行う関数(回転/拡大縮小)
	/// </summary>
	/// <param name="cb">シェーダーに渡す行列</param>
	void GenerateMatrix(CONSTBUFFER& cb);


	virtual void Draw(void);












};

