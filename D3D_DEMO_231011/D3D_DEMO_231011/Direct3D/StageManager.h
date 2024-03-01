#pragma once
#include "Stage.h"

class StageManager : public Stage
{
private:
	
	StageManager() {}// コンストラクタ
	
	~StageManager() {}// デストラクタ



	//コピーとかを禁止にする
	StageManager(const StageManager&) = delete;// オブジェクトのコピー
	StageManager& operator=(const StageManager&) = delete;// オブジェクトの代入
	StageManager(StageManager&&) = delete;// オブジェクトのムーブ
	StageManager& operator=(StageManager&&) = delete;// オブジェクトのムーブ代入

		
public:

	//シングルトン
	static StageManager& Get();


	/*Init*/
	void Init();
	/*Update*/
	void Update();
	/*Draw*/
	void Draw();

	



};

