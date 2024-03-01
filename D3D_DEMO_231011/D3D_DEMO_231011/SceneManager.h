#pragma once
#include "Scene.h"
#include "Stage.h"
#include <vector>

class SceneManager : public Scene
{
private:
	
	SceneManager() {}// コンストラクタ
	
	~SceneManager();// デストラクタ

	//コピーとかを禁止にする

public:

	//ステージの情報扱う
	Stage** m_stageHolder;

public:
	
	//シングルトン
	static SceneManager* Get();

	/*Init*/
	void Init();

	/*Update*/
	void Update();

	//今作動中のステージを返す
	int GetActiveStage(void);

};

