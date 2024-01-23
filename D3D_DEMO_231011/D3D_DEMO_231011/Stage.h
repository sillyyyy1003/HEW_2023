#pragma once

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

	

public:

	
};

