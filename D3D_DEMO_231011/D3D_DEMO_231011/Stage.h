#pragma once

enum STAGEINFO {
	STAGE1_1,
	STAGE1_2,
	STAGE1_3,

	STAGE2_1,
	STAGE2_2,
	STAGE2_3,

	STAGE3_1,
	STAGE3_2,
	STAGE3_3,

};

// ステージクラス （ステージ数だけ）
class Stage
{
private:

	//ステージクリアしたかどうか？
	bool isClear = false;
	
	//Reward Gold
	float m_rewardGold = 0;
	 
	//移動の数
	int m_moveStep=0;

public:

	//ここでステージの初期配置を行う
	void Init(void);

	//毎ループで行う関数
	void Update(void);

	//ステップ数を加算していく
	void StepCount(void);

	int GetStep(void) { return m_moveStep; };
};

