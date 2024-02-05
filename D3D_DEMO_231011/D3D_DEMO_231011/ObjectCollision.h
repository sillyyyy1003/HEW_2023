#pragma once

#include "SAT.h"
#include "Object.h"

class ObjectCollision
{
private:

	TestObject* pObj;		//test用キャラ
	TestObject* square;		//test用キャラ
	TestObject* circle;		//test用キャラ
	TestObject* triangle;	//test用キャラ
	TestObject* ex;			//test用キャラ
	TestObject* ex1;		//test用キャラ
	TestObject* ex2;		//test用キャラ
	TestObject* ex3;		//test用キャラ

	enum OBJECT
	{
		NONE,
		TRIANGLE,	// 三角形
		SQUARE,		// 四角
		CIRCLE,		// 円
	};

	BOUNDING_CIRCLE p_center; // 中心点の座標
	BOUNDING_CIRCLE p_center2; // 中心点の座標
	std::vector<Vector2> p_verticies; // 中心点の座標
	// 図形の角度を入れるための変数
	int RotationJodge = 0;

public:

	void Draw();

	void Update();

	ObjectCollision();

	~ObjectCollision();

	// すべての当たり判定を管理する
	void objectCollision();

	//------------------//
	//--- 当たり判定 ---//
	//------------------//

	// SATによる当たり判定（凸角形対応）
	bool SATHit(TestObject* testObj, TestObject* testObj2);

	// 自：四角　の当たり判定
	int SqureCollision(TestObject* testObj, TestObject* testObj2);

	// 自：四角　円　　の当たり判定
	int SqureAndCircleCollision(TestObject* testObj, TestObject* testObj2);

	// 自：三角　の当たり判定
	int TriangleCollision(TestObject* testObj, TestObject* testObj2);

	//--------------------------------------------------//
	//--- オブジェクト同士が触れた時に合体させる関数 ---//
	//--------------------------------------------------//

	// 円と四角のどちかを操作している時の関数
	void CombineObjects(int HitNum, TestObject* testObj, TestObject* testObj2);

	// 自：三角　他：三角　
	void CombineTriangleObjects(int HitNum, TestObject* testObj, TestObject* testObj2);

	// 自：三角　他：四角　
	void CombineTriangleAndSqureObjects(int HitNum, TestObject* testObj, TestObject* testObj2);

	// 自：三角　他：円　
	void CombineTriangleAndCircleObjects(int HitNum, TestObject* testObj, TestObject* testObj2);

	//------------------------------------------------//
	//--- 図形によって当たり判定を変えるための関数 ---//
	//------------------------------------------------//

	// 自：四角　
	int SquareHit(TestObject* testObj, TestObject* testObj2);

	// 自：四角　円　
	int CircleHit(TestObject* testObj, TestObject* testObj2);
	// 自：円
	int TriangleHit(TestObject* testObj, TestObject* testObj2);

	//------------------------------------------//
	//--- 図形の頂点座標を設定するための関数 ---//
	//------------------------------------------//

	// 三角の頂点座標を設定
	std::vector<Vector2> SetTriangle(TestObject* testObj2);

	// 四角の頂点座標を設定
	std::vector<Vector2> SetSquare(TestObject* testObj2, float width);

	// 円の頂点座標を設定
	std::vector<Vector2> SetCircle(TestObject* testObj2, float width, float width2);

	// 図形が回転したときに同じように頂点座標を変化させるための関数
	void InitialPolygonSAT(BOUNDING_CIRCLE circle1, TestObject* testObj, float rotation);

	// 図形が回転したときに同じように頂点座標を変化させたへ変数を返す関数
	std::vector<Vector2> InitialPolygonSATvertices(BOUNDING_CIRCLE circle1, std::vector<Vector2> vertices, float rotation);
};