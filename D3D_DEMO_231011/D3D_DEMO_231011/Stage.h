#pragma once
#include <vector>
class GameObject;

// ステージクラス （ステージ数だけ）
class Stage
{
private:


	//ステージクリアしたかどうか？
	bool isClear = false;

	//一回クリアしたか
	bool isisCompleted = false;
	
	//Reward Gold
	float m_rewardGold = 0;
	 
	//移動の数
	int m_moveStep=0;

	//ステージは作動中かどうか？
	bool isActive = false;

	std::vector<GameObject*> m_objectList;

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
	void SetCompleted(bool isCompleted) { this->isisCompleted = isCompleted; };
	bool GetCompleted(void) { return isisCompleted; };



	//ステップ数を加算していく
	void StepCount(void);
	int GetStep(void) { return m_moveStep; };

public:

	
};

