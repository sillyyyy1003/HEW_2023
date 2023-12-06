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
	
	//テスト用
	ID3D11ShaderResourceView* testchar01;	//キャラ用テクスチャ
	ID3D11ShaderResourceView* testbg01;		//背景用テクスチャ

	//テスト用 Using Shadow
	ID3D11ShaderResourceView* testbgbox;	//箱型用テクスチャ
	ID3D11ShaderResourceView* testObj;		//オブジェクト用テクスチャ
	ID3D11ShaderResourceView* testShadow;	//影用テクスチャ

	ID3D11ShaderResourceView* square;
	ID3D11ShaderResourceView* triangle;



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

