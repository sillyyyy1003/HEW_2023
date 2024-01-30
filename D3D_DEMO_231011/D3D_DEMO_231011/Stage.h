#pragma once
#include <vector>
class GameObject;

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


	//ステップ数を加算していく
	void StepCount(void);
	int GetStep(void) { return m_moveStep; };

public:

	
};

