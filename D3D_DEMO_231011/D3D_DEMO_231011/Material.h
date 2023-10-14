#pragma once
#include "Direct3D/Direct3D.h"

/// <summary>
/// 
/// </summary>
struct BASEDATA 
{

	float x, y, z;		//位置座標
	float u, v;			//テクスチャのUV座標

};

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
		@brief	
		@param	
		@return	
	*/
	void SetTexture(ID3D11ShaderResourceView* _texture);












	///*
	//	@brief	描画の設定と描画
	//	@param	無し
	//	@return	無し
	//*/
	//virtual void Draw(void);


};


