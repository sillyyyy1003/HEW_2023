#pragma once
#include"Direct3D/Direct3D.h"
#include"WICTextureLoader.h"	//テクスチャ読み込みライブラリ

//テクスチャ·サウンドファイル読み込みを行う関数
class Assets
{
public:
	//----------------------------//
	// 変数
	//----------------------------//
	
	
	//テスト用 Using Shadow
	ID3D11ShaderResourceView* testObj;		//オブジェクト用テクスチャ
	ID3D11ShaderResourceView* testShadow;	//影用テクスチャ
	
	ID3D11ShaderResourceView* testWallbg;	//壁用テクスチャ
	ID3D11ShaderResourceView* testGroundbg;	//地面用テクスチャ
	//ID3D11ShaderResourceView* testChara01;	//キャラ用テクスチャ

	ID3D11ShaderResourceView* testChara01;




public:
	//----------------------------//
	// 関数のプロトタイプ宣言
	//----------------------------//

	//コンストラクタ：ファイル読み込み
	Assets();

	//デストラクタ：後片付け
	~Assets();

	/*
		@brief	ファイル読み込みを行う関数
		@param	ファイル名
		@return SRVのポインター
	*/
	ID3D11ShaderResourceView* LoadTexture(const char* _fileName);

};

