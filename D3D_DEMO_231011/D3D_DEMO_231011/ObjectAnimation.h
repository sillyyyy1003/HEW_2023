#pragma once
#include "Animation.h"
#include <vector>


class ObjectAnimation :public Animation
{
private:

	//フレームの枚数
	int m_frameNum = 0;

	//アニメテーブル
	std::vector<int> animeTable;

	//多種のアニメパターンを持つかどうか
	bool isMultiPattern = false;

	//アニメーション終了したかどうか？
	bool isEnd = false;


public:
	//初期化
	ObjectAnimation(int splitX, int splitY);
	~ObjectAnimation();

	//アニメテーブル作成
	void InitAnimation(int num);

	/// <summary>
	/// この中にanimeTableを変更
	/// </summary>
	void Update(void) override;


	//アニメパターンの状態を取る
	void SetMultiPattern(bool isMultiPattern) { this->isMultiPattern = isMultiPattern; };
	bool GetMultiPattern() { return isMultiPattern; };
};

