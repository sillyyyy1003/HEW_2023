#pragma once
#include <vector>
class GameObject;

// ステージクラス （ステージ数だけ）
class Stage
{
private:
	//ヒントが出されたかどうか
	bool isHint = true;

	//ステージクリアしたかどうか？
	bool isClear = false;

	//一回クリアしたか
	bool isCompleted = false;

	//Reward Gold
	float m_rewardGold = 0;

	//移動の数
	int m_moveStep = 0;

	//ステージは作動中かどうか？
	bool isActive = false;


public:


	//ここでステージの初期配置を行う
	void Init(void);

	//毎ループで行う関数
	void Update(void);

	//ステージを作動しているかどうか
	void SetActive(bool isActive) { this->isActive = isActive; };
	bool GetActive(void) { return this->isActive; };

	//ゲームクリア下したかどうか？
	void SetClear(bool isClear) { this->isClear = isClear; };
	bool GetClear(void) { return isClear; };

	//ゲームステージ一回クリア下かどうか？
	void SetCompleted(bool isCompleted) { this->isCompleted = isCompleted; };
	bool GetCompleted(void) { return isCompleted; };

	//ステップ数を加算していく
	void StepCount(void);

	void HintPunish(int step) { m_moveStep += step; };
	int GetStep(void) { return m_moveStep; };

	//step数をリセット　クリア状態をリセット
	void ResetStage(void) { m_moveStep = 0; isClear = false; };

	//hintの判断
	bool GetHint(void) { return isHint; };
	void SetHint(bool isHint) { this->isHint = isHint; };


};

