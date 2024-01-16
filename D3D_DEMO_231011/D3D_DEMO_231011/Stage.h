#pragma once

// ステージクラス （ステージ数だけ）
class Stage
{
private:
	
	

public:

	enum class StageInfo//15 必要に応じて増やす
	{
	STAGEA = 11,// 1-1
	STAGEB = 12,// 1-2
	STAGEC = 13,// 1-3

	STAGEBA = 21,// 2-1
	STAGEBB = 22,// 2-2
	STAGEBC = 23,// 2-3

	STAGECA = 31,// 3-1
	STAGECB = 32,// 3-2
	STAGECC = 33,// 3-3

	STAGEDA = 41,// 4-1
	STAGEDB = 42,// 4-2
	STAGEDC = 43,// 4-3

	STAGEEA = 51,// 5-1
	STAGEEB = 52,// 5-2
	STAGEEC = 53,// 5-3

	PAUSE=99,
	};

};

