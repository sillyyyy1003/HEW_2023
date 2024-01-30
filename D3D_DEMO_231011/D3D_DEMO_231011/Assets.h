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
	
	//================//テスト用//================//

	ID3D11ShaderResourceView* testPause;//ポーズ画面テクスチャ
	ID3D11ShaderResourceView* circle;
	ID3D11ShaderResourceView* shadow;
	// 図形
	//ID3D11ShaderResourceView* circle;
	ID3D11ShaderResourceView* square;
	ID3D11ShaderResourceView* triangle;
	
	//タイトル用のリソース
	ID3D11ShaderResourceView* uiTitleBg;	
	ID3D11ShaderResourceView* uiTitle;
	ID3D11ShaderResourceView* uiPressEnter;

	//stage1-1用リソース
	ID3D11ShaderResourceView* stageBg;

	ID3D11ShaderResourceView* coconut;
	ID3D11ShaderResourceView* coconutShadow;
	ID3D11ShaderResourceView* lamp;
	ID3D11ShaderResourceView* lampShadow;
	ID3D11ShaderResourceView* housePlate;
	ID3D11ShaderResourceView* housePlateShadow;


	ID3D11ShaderResourceView* uiPauseBg;
	ID3D11ShaderResourceView* uiResume;
	ID3D11ShaderResourceView* uiRestart;




	ID3D11ShaderResourceView* ex;

	//デバッグ用
	static ID3D11ShaderResourceView* debugFont;		



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

