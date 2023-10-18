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

	//縦フレーム何番目
	int m_AnimePattern = 0;

	//横フレームの何番目からスタート
	int m_StartFrame = 0;

	//横フレームの何番目まで終わる
	int m_EndFrame = 0;

	//テクスチャの縦横分割
	DirectX::XMINT2 m_split = { 1,1 };

	// アニメーションのカウンター
	float m_AnimeCounter = 0.0f;

	//再生速度
	float m_AnimeSpeed = 0.0f;

public:

	//現在再生中かを表す変数
	bool isPlaying = true;


public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="XMINT2"></param>
	Animation(XMINT2 _split);

	/// <summary>
	/// UV座標の更新を行う関数
	/// </summary>
	/// <param name="_frameX">横何番目 aniTabの値を代入</param>
	/// <param name="_frameY">animePattern 縦フレーム何番目</param>
	virtual void Update(int _frameX,int _frameY);

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

