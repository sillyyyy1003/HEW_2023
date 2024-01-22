#pragma once
#include "Scene.h"
#include "Stage.h"
#include <vector>

class SceneManager : public Scene
{
private:
	
	SceneManager() {}// コンストラクタ
	
	~SceneManager() {}// デストラクタ

	//コピーとかを禁止にする
	SceneManager(const SceneManager&) = delete;// オブジェクトのコピー
	SceneManager& operator=(const SceneManager&) = delete;// オブジェクトの代入
	SceneManager(SceneManager&&) = delete;// オブジェクトのムーブ
	SceneManager& operator=(SceneManager&&) = delete;// オブジェクトのムーブ代入

	//ステージの情報扱う
	Stage** m_stageHolder;
		
public:
	
	//シングルトン
	static SceneManager* Get();

	/*Init*/
	void Init();


	/*Update*/
	void Update();

};

