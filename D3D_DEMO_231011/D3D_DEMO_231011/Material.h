#pragma once
#include "Direct3D/Direct3D.h"



/// <summary>
/// 頂点バッファとテクスチャを保存する構造体
/// </summary>
struct MODELDATA 
{
	ID3D11Buffer*				vertexBuffer;			//頂点バッファ
	ID3D11ShaderResourceView*	texture;				//テクスチャ

};

/// <summary>
/// マテリアルを保存する関数
/// </summary>
class Material
{

protected:
	
	//モデル情報
	MODELDATA m_modelData = {};

public:

	//----------------------------//
	// 関数のプロトタイプ宣言
	//----------------------------//

	/*
		デストラクタ	
	*/
	~Material();

	/*
		@brief	読み込み済みのテクスチャを受け取る
		@param	読み込み済みのテクスチャポインター
		@return	無し
	*/
	void SetTexture(ID3D11ShaderResourceView* _texture);














};


