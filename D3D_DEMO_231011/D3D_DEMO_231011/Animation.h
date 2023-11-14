#pragma once
#include "Direct3D/Direct3D.h"



class Animation
{
protected:
	//----------------------------//
	// 変数
	//----------------------------//
	// UVアニメーション用オフセット
	DirectX::XMFLOAT2 m_offsetUV = { 0.0f,0.0f };

	//横・縦フレーム何番目
	int m_frameX = 0;	//横何番目
	int m_frameY = 0;	//縦何番目→アニメパターン

	//テクスチャの縦横分割
	DirectX::XMINT2 m_split = { 1,1 };

	//横フレームの何番目からスタート
	int m_StartFrame = 0;

	//横フレームの何番目まで終わる
	int m_endFrame = 0;

	// アニメーションのカウンター
	float m_animeCounter = 0.0f;

	//再生速度
	float m_animeSpeed = 0.0f;

public:

	//現在再生中かを表す変数
	bool isPlaying = true;


public:
	/// <summary>
	/// 初期化　縦横分割を設定する
	/// </summary>
	/// <param name="splitX">横分割数</param>
	/// <param name="splitY">縦分割数</param>
	Animation(int splitX,int splitY);

	/// <summary>
	/// 縦横分割の初期設定
	/// </summary>
	/// <param name="_split">縦横分割 SPRITEと一致する</param>
	void SetSplit(XMINT2 _split);


	DirectX::XMINT2 GetSplit(void);
		
	/// <summary>
	/// UV座標の更新を行う関数
	/// </summary>
	/// NOTE:継承クラスでアニメテーブルの設定と縦横のアニメ更新を行う
	virtual void Update(void);

	/// <summary>
	/// 再生速度を設定する関数
	/// </summary>
	/// <param name="_speed">再生速度</param>
	void SetAnimeSpeed(float _speed);

	/// <summary>
	/// アニメーションパターンを設定する関数
	/// </summary>
	/// <param name="_animePattern">縦フレーム何番目 アニメーションのパターン</param>
	void SetAnimePattern(int _animePattern);

	/// <summary>
	/// UV座標を返す関数
	/// </summary>
	/// <returns>更新されたUV座標</returns>
	DirectX::XMFLOAT2 GetUVOffset(void);

};

