
#pragma once
#include"Direct3D.h"
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
	ID3D11ShaderResourceView* uiPressSpace;

	//ステージセレクト用
	ID3D11ShaderResourceView* uiSelectBg;

	ID3D11ShaderResourceView* uiSelectCursor;
	ID3D11ShaderResourceView* uiSelectStage1;
	ID3D11ShaderResourceView* uiSelectStage2;
	ID3D11ShaderResourceView* uiSelectStage3;

	ID3D11ShaderResourceView* uiSelectChapter1;
	ID3D11ShaderResourceView* uiSelectChapter2;
	ID3D11ShaderResourceView* uiSelectChapter3;
	
	ID3D11ShaderResourceView* uiClear;

	ID3D11ShaderResourceView* stageMask;
	ID3D11ShaderResourceView* controlPanel;
	ID3D11ShaderResourceView* resultMask;

	//HINT用
	ID3D11ShaderResourceView* stageHint1_1;
	ID3D11ShaderResourceView* stageHint1_2;
	ID3D11ShaderResourceView* stageHint1_3;
	ID3D11ShaderResourceView* stageHintBg;

	//stage1-1用リソース
	ID3D11ShaderResourceView* stageBg1_1;
	ID3D11ShaderResourceView* coconut;
	ID3D11ShaderResourceView* coconutShadow;
	ID3D11ShaderResourceView* lamp;
	ID3D11ShaderResourceView* lampShadow;
	ID3D11ShaderResourceView* housePlate;
	ID3D11ShaderResourceView* housePlateShadow;

	ID3D11ShaderResourceView* stageBg1_2;
	ID3D11ShaderResourceView* lamp_1_2;
	ID3D11ShaderResourceView* lamp_1_2Shadow;
	ID3D11ShaderResourceView* iphone;
	ID3D11ShaderResourceView* iphoneShadow;
	ID3D11ShaderResourceView* triangleBlock;
	ID3D11ShaderResourceView* triangleBlockShadow;

	//Result Comic
	//1-1
	ID3D11ShaderResourceView* resultComic1_1_1;
	ID3D11ShaderResourceView* resultComic1_1_2;
	ID3D11ShaderResourceView* resultComic1_1_3;
	//1-2
	ID3D11ShaderResourceView* resultComic1_2_1;
	ID3D11ShaderResourceView* resultComic1_2_2;
	ID3D11ShaderResourceView* resultComic1_2_3;
	//1-3
	ID3D11ShaderResourceView* resultComic1_3_1;
	ID3D11ShaderResourceView* resultComic1_3_2;
	ID3D11ShaderResourceView* resultComic1_3_3;

	//stage1-3用リソース
	ID3D11ShaderResourceView* stage3Bg;

	ID3D11ShaderResourceView* busket;
	ID3D11ShaderResourceView* busketShadow;
	ID3D11ShaderResourceView* newspaper;
	ID3D11ShaderResourceView* newspaperShadow;
	ID3D11ShaderResourceView* picnicbasket;
	ID3D11ShaderResourceView* picnicbasketShadow;
	ID3D11ShaderResourceView* sandwich;
	ID3D11ShaderResourceView* sandwichShadow;

	//result用
	ID3D11ShaderResourceView* resultBg;
	ID3D11ShaderResourceView* Button_again;
	ID3D11ShaderResourceView* Button_next;
	ID3D11ShaderResourceView* Button_return;
	ID3D11ShaderResourceView* result;
	ID3D11ShaderResourceView* Result_score;
	ID3D11ShaderResourceView* Result_stepcount;
	ID3D11ShaderResourceView* Result_num;
	ID3D11ShaderResourceView* star;
	ID3D11ShaderResourceView* starShadow;

	//clear
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
	ID3D11ShaderResourceView* uiMusic;	//サウンド音楽文字表示
	ID3D11ShaderResourceView* uiSE;		//サウントSE文字表示


	ID3D11ShaderResourceView* fade;

	//エフェクト用
	ID3D11ShaderResourceView* effect1;	//炎
	ID3D11ShaderResourceView* effect2;	//白いカーソル
	ID3D11ShaderResourceView* uiArrow;	

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

