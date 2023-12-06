#pragma once
#include "Object.h"
#include"TestObject.h"
#include "SAT.h"



extern Camera* g_WorldCamera;
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

	//const double M_PI = 3.14159265358979323846;
private:

	//Object* testObject;		//test用キャラ
	TestObject* testObj;		//test用キャラ
	TestObject* testObj2;		//test用キャラ
	TestObject* testObj3;		//test用キャラ
	TestObject* testObj4;		//test用キャラ
	TestObject* ex;		//test用キャラ
	TestObject* ex1;		//test用キャラ
	TestObject* ex2;		//test用キャラ
	TestObject* ex3;		//test用キャラ
	Object* testBg;				//test用背景
	PolygonSAT* a;


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
	int SqureHit(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj, TestObject* testObj2);

	// オブジェクト同士を合体させる関数
	void CombineObjects(int HitNum, BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj2);

	void CombineTriangleObjects(int HitNum, BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj, TestObject* testObj2);

	// 上下左右で別の当たり判定をとるための関数
	int SideCollision(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2);

	int SqureCollision(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj, TestObject* testObj2);

	bool CheckSqureHit(const BOX& t_box, const BOX& t_box2);

	SQUREBOX Squre(BOUNDING_CIRCLE circle2, TestObject* testObj);

	std::vector<Vector2> SetTriangle(BOUNDING_CIRCLE circle1, TestObject* testObj2);

	std::vector<Vector2> SetSqureWithTriangle(BOUNDING_CIRCLE circle1, TestObject* testObj2, float width);

	SQURE SetCircleWithTriangle(BOUNDING_CIRCLE circle1, TestObject* testObj2, float width);

	// 点が三角形内にあるかどうかを判定する関数
	bool isPointInTriangle(Point A, Point B, Point C, Point P);

	int CheckTriangleHit(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj, TestObject* testObj2);

	int CheckTriangleAndCircleHit(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj, TestObject* testObj2);

	int CheckTriangleAndSqureHit(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj, TestObject* testObj2);

	bool TriangleAndCircleHit(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj, TestObject* testObj2);

	bool TriangleAndSqureHit(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj, TestObject* testObj2);

	bool TriangleHit(TestObject* testObj, TestObject* testObj2);

	void InitialPolygonSAT(BOUNDING_CIRCLE circle1, TestObject* testObj, float rotation);

	std::vector<Vector2> InitialPolygonSATvertices(BOUNDING_CIRCLE circle1, std::vector<Vector2> vertices, float rotation);

	//　すべての当たり判定を管理する
	void TestCollision();

	//シーンを設定する
	void SetGameScene(GAMESCENE scene);

	DirectX::XMFLOAT3 p_center; // 中心点の座標
};

