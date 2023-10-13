#pragma once
#include "Direct3D/Direct3D.h"

struct BASEDATA 
{

	float x, y, z;		//位置座標
	float u, v;			//テクスチャのUV座標

};

struct MODELDATA 
{
	ID3D11Buffer* m_VertexBuffer;			//頂点バッファ
	ID3D11ShaderResourceView* m_Texture;	//テクスチャ

};
class Graphics
{
protected:
	
	BASEDATA	m_graphicData = {};
	MODELDATA	m_modelData = {};

public:

	//----------------------------//
	// 関数のプロトタイプ宣言
	//----------------------------//
	/*
		デストラクタ	
	*/
	~Graphics();

	/*
		@brief	
		@param	
		@return	
	*/
	void SetTexture(ID3D11ShaderResourceView* _texture);

	/*
		@brief	描画の設定と描画
		@param	無し
		@return	無し
	*/
	virtual void Draw(void);


};

