#pragma once
#include"Direct3D/Direct3D.h"
#include"WICTextureLoader.h"	//テクスチャ読み込みライブラリ

class Assets
{
public:
	//----------------------------//
	// 変数
	//----------------------------//
	ID3D11ShaderResourceView* textureTest;


public:
	//----------------------------//
	// 関数のプロトタイプ宣言
	//----------------------------//

	//コンストラクタ
	Assets();

	//デストラクタ
	~Assets();

	/*
		@brief	ファイル読み込みを行う関数
		@param	ファイル名
		@return SRVのポインター
	*/
	ID3D11ShaderResourceView* LoadTexture(const char* _fileName);

};

