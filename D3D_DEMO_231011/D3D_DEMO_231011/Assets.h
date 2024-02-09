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

	ID3D11ShaderResourceView* tree;
	ID3D11ShaderResourceView* shadow;
	
	// 図形

	//タイトル用のリソース
	ID3D11ShaderResourceView* uiTitleBg;	
	ID3D11ShaderResourceView* uiTitle;
	ID3D11ShaderResourceView* uiPressEnter;

	//ステージセレクト用
	ID3D11ShaderResourceView* uiSelectBg;
	ID3D11ShaderResourceView* uiStageSelect;

	ID3D11ShaderResourceView* uiSelectCursor;
	ID3D11ShaderResourceView* uiSelectStage1;
	ID3D11ShaderResourceView* uiSelectStage2;
	ID3D11ShaderResourceView* uiSelectStage3;

	ID3D11ShaderResourceView* uiSelectChapter1;
	ID3D11ShaderResourceView* uiSelectChapter2;
	ID3D11ShaderResourceView* uiSelectChapter3;
	
	ID3D11ShaderResourceView* uiClear;


	//stage1-1用リソース
	ID3D11ShaderResourceView* stageBg;

	ID3D11ShaderResourceView* coconut;
	ID3D11ShaderResourceView* coconutShadow;
	ID3D11ShaderResourceView* lamp;
	ID3D11ShaderResourceView* lampShadow;
	ID3D11ShaderResourceView* housePlate;
	ID3D11ShaderResourceView* housePlateShadow;
	


	//ポーズ画面用
	ID3D11ShaderResourceView* uiPauseBg;
	ID3D11ShaderResourceView* uiResume;
	ID3D11ShaderResourceView* uiRestart;

	ID3D11ShaderResourceView* uiSelect;
	ID3D11ShaderResourceView* uiSound;
	
	//サウンド画面用
	ID3D11ShaderResourceView* uiSoundBg;//サウンド背景
	ID3D11ShaderResourceView* uiSoundOp_BGM;//サウンド調節
	ID3D11ShaderResourceView* uiSoundOp_SE;//サウンド調節


	ID3D11ShaderResourceView* fade;

	//エフェクト用
	ID3D11ShaderResourceView* effect1;	//炎
	ID3D11ShaderResourceView* effect2;	//白いカーソル

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

