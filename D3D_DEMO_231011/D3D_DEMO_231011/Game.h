#pragma once

class GameObject;
class StaticObject;
class CanvasUI;

class Game
{
private:
	enum GAMESCENE 
	{
		TITLE,		//タイトル
		STAGE1,		//ゲームシーン
		RESULT,		//リザルトシーン
	};

	GAMESCENE m_gameScene = TITLE;

private:
	
	//テスト用
	GameObject*		testTree;	//移動用オブジェクト	
	StaticObject*	testWall;	//壁
	StaticObject*	testGround;	//地面
	GameObject*		testChara;	//テストキャラ


private:
	//コンストラクタ&デストラクタ
	Game() {};
	~Game();

public:
	//唯一のインスタンスを返す関数
	static Game* Get();

	//初期化を行う関数
	void Init();

	//ゲーム本体
	void GameUpdate(void);
	void TitleUpdate(void);
	void StageUpdate(void);
	void ResultUpdate(void);

	//テスト用
	void TestUpdate(void);
	void TestDraw(void);


	//描画
	void GameDraw(void);
	void TitleDraw(void);
	void StageDraw(void);
	void ResultDraw(void);

	
	//シーンを設定する
	void SetGameScene(GAMESCENE scene);

	
};

