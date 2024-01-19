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
	void InitStage();
	void InitStage1_1(void);
	void InitStage1_2(void);
	void InitStage1_3(void);
	void InitStage2_1(void);
	void InitStage2_2(void);
	void InitStage2_3(void);
	void InitStage3_1(void);
	void InitStage3_2(void);
	void InitStage3_3(void);

	/*Update*/
	void Update();
	void TitleUpdate();
	void StageSelect();

	//STAGEUPDATE
	void UpdateStage1_1(void);
	void UpdateStage1_2(void);
	void UpdateStage1_3(void);
	void UpdateStage2_1(void);
	void UpdateStage2_2(void);
	void UpdateStage2_3(void);
	void UpdateStage3_1(void);
	void UpdateStage3_2(void);
	void UpdateStage3_3(void);
	//RESUTL UPDATE




	
	/*Draw*/
	void Draw();
	//ステージ描画
	void DrawStage1_1();
	void DrawStage1_1();
	void DrawStage1_1();
	void DrawStage1_1();
	void DrawStage1_1();
	void DrawStage1_1();
	void DrawStage1_1();
	void DrawStage1_1();
	void DrawStage1_1();

	//リザルト描画


	



};

