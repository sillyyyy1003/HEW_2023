#pragma once
#include "Object.h"
#include "TestObject.h"
#include "GameObject.h"


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
	Object* testWall;
	Object* testGround;
	Object* testChara;	//プレイヤー

	GameObject* testTree;	//木


public:
	//コンストラクタ
	Game();

	//ゲーム本体
	void GameUpdate(void);
	void TitleUpdate(void);
	void StageUpdate(void);
	void ResultUpdate(void);


	//後片付け
	~Game();

	//描画
	void GameDraw(void);
	void TitleDraw(void);
	void StageDraw(void);
	void ResultDraw(void);

	// 当たり判定
	// 円と円同士の当たり判定
	int CircleHit(BOUNDING_CIRCLE bc1, BOUNDING_CIRCLE bc2);

	// 四角形と円の当たり判定
	int SqureandCircle(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj);
	// 四角形と円の当たり判定に使う関数
	bool CheckHit(const BOX& t_box, const BOUNDING_CIRCLE bc1);

	// 四角形同士の当たり判定
	int SqureHit(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2);

	// オブジェクト同士を合体させる関数
	void CombineObjects(int HitNum, BOUNDING_CIRCLE Combine, BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj);

	// 上下左右で別の当たり判定をとるための関数
	int SideCollision(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2);

	//　すべての当たり判定を管理する
	void TestCollision();

	//シーンを設定する
	void SetGameScene(GAMESCENE scene);

	
};

