#include "Assets.h"
#include "ObjectAnimation.h"

#include "ObjectCollision.h"
#include <algorithm> // 必要なヘッダーファイル
#define SQUREWIDTH 1.2
#define CIRCLEWIDTH 0.8
#define TRIANGLEWIDTH 0.8
#define M_PI 3.14159265358979323846

extern Assets* g_Assets;

ObjectCollision::ObjectCollision()
{
	// オブジェクト1
	pObj = new TestObject();
	// オブジェクトの画像を設定
	pObj->object = SQUARE;
	//オブジェクトの初期設定
	pObj->SetObjTex(g_Assets->square, 200, 200, 1, 1);
	pObj->m_objSprite->m_anime = new ObjectAnimation(1, 1);
	pObj->m_objSprite->m_anime->SetAnimeSpeed(0.0f);
	pObj->m_objSprite->m_anime->SetAnimePattern(0);
	pObj->m_objSprite->InitPos(-4, -1.16, 0.2f);
	DirectX::XMFLOAT3 rotation = pObj->m_objSprite->m_rotation;
	pObj->isPlayer = true;// キーボードで操作可能
	pObj->vertices = SetTriangle(pObj);

	// オブジェクト2
	square = new TestObject();
	square->object = SQUARE;
	square->SetObjTex(g_Assets->square, 200, 200, 1, 1);
	square->m_objSprite->m_anime = new ObjectAnimation(1, 1);
	square->m_objSprite->m_anime->SetAnimeSpeed(0.0f);
	square->m_objSprite->m_anime->SetAnimePattern(0);
	square->m_objSprite->InitPos(1, 1, 0.1f);
	rotation.z = 0;
	square->SetRotation(rotation);
	square->rotation = 0;// 45 M_PI / 2
	square->vertices = SetSquare(square, SQUREWIDTH);

	// オブジェクト3
	circle = new TestObject();
	circle->object = CIRCLE;
	//オブジェクトの初期設定
	circle->SetObjTex(g_Assets->circle, 200, 200, 1, 1);//square
	circle->m_objSprite->m_anime = new ObjectAnimation(1, 1);
	circle->m_objSprite->m_anime->SetAnimeSpeed(0.0f);
	circle->m_objSprite->m_anime->SetAnimePattern(0);
	circle->m_objSprite->InitPos(4, 3, 0.1f);
	rotation.z = 0;
	circle->SetRotation(rotation);
	circle->rotation = 0;// 45 M_PI / 8
	circle->vertices = SetCircle(circle, CIRCLEWIDTH, SQUREWIDTH);

	triangle = new TestObject();
	triangle->object = TRIANGLE;
	triangle->SetObjTex(g_Assets->triangle, 200, 200, 1, 1);//square
	triangle->m_objSprite->m_anime = new ObjectAnimation(1, 1);
	triangle->m_objSprite->m_anime->SetAnimeSpeed(0.0f);
	triangle->m_objSprite->m_anime->SetAnimePattern(0);
	triangle->m_objSprite->InitPos(-3, 3, 0.1f);
	rotation.z = 0;
	triangle->SetRotation(rotation);
	triangle->rotation = 0;// 45 M_PI / 8
	triangle->vertices = SetTriangle(triangle);
	triangle->isTriangle = true;

	ex = new TestObject();
	ex->SetObjTex(g_Assets->ex, 15, 15, 1, 1);//square
	ex->m_objSprite->m_anime = new ObjectAnimation(1, 1);
	ex->m_objSprite->m_anime->SetAnimeSpeed(0.0f);
	ex->m_objSprite->m_anime->SetAnimePattern(0);

	ex1 = new TestObject();
	ex1->SetObjTex(g_Assets->ex, 15, 15, 1, 1);//square
	ex1->m_objSprite->m_anime = new ObjectAnimation(1, 1);
	ex1->m_objSprite->m_anime->SetAnimeSpeed(0.0f);
	ex1->m_objSprite->m_anime->SetAnimePattern(0);

	ex2 = new TestObject();
	ex2->SetObjTex(g_Assets->ex, 15, 15, 1, 1);//square
	ex2->m_objSprite->m_anime = new ObjectAnimation(1, 1);
	ex2->m_objSprite->m_anime->SetAnimeSpeed(0.0f);
	ex2->m_objSprite->m_anime->SetAnimePattern(0);

	ex3 = new TestObject();
	ex3->SetObjTex(g_Assets->ex, 15, 15, 1, 1);//square
	ex3->m_objSprite->m_anime = new ObjectAnimation(1, 1);
	ex3->m_objSprite->m_anime->SetAnimeSpeed(0.0f);
	ex3->m_objSprite->m_anime->SetAnimePattern(0);
}

ObjectCollision::~ObjectCollision()
{
	delete pObj;
	delete square;
	delete circle;
	delete triangle;
	delete ex;
	delete ex1;
	delete ex2;
	delete ex3;
}

void ObjectCollision::Draw()
{
	ex->Draw();
	ex1->Draw();
	ex2->Draw();
	ex3->Draw();
	pObj->Draw();
	square->Draw();
	circle->Draw();
	triangle->Draw();
}

void ObjectCollision::Update()
{
	// 当たり判定
	objectCollision();

	pObj->Update();
	square->Update();
	circle->Update();
	triangle->Update();
	ex->Update();
	ex1->Update();
	ex2->Update();
	ex3->Update();
}

// ---図形の当たり判定--- //
void ObjectCollision::objectCollision()
{
	// 頂点座標を表示用
	//ex->m_objSprite->InitPos(circle->vertices[0].x, circle->vertices[0].y, 0.1f);
	//ex1->m_objSprite->InitPos(circle->vertices[1].x, circle->vertices[1].y, 0.1f);
	//ex2->m_objSprite->InitPos(circle->vertices[2].x, circle->vertices[2].y, 0.1f);
	//ex3->m_objSprite->InitPos(circle->vertices[3].x, circle->vertices[3].y, 0.1f);

	//--------------------------------------------------------//
	//--- 自分が操作する図形によって当たり判定を切り替える ---//
	//--------------------------------------------------------//

	if (pObj->object == SQUARE)
	{
		/// 自：自分が操作している図形　他：操作していない当たり判定の対象となる図形
		/// <summary>
		/// 自：四角　の場合の当たり判定
		/// </summary>
		if (!circle->isPlayer)// オブジェクト同士が触れたら当たり判定を消す
		{
			// 自：四角　他：円
			CombineObjects(SquareHit(pObj, circle), pObj, circle);

			// 自図形に合体した図形にも当たり判定を付けるための当たり判定① 円と四角
			// 他：四角　他：円
			//CombineObjects(SquareHit(square, circle), square, circle);
		}
		if (!square->isPlayer)// オブジェクト同士が触れたら当たり判定を消す
		{
			// 自：四角　他：四角
			CombineObjects(SquareHit(pObj, square), pObj, square);

			// 自図形に合体した図形にも当たり判定を付けるための当たり判定② 円と四角
			// 他：円　他：四角
			//CombineObjects(CircleHit(circle, square),circle,square);
		}
		if (!triangle->isPlayer)
		{
			// 自：四角　他：三角
			CombineObjects(SquareHit(pObj, triangle), pObj, triangle);
		}
	}
	else if (pObj->object == CIRCLE)
	{
		/// <summary>
		/// 自：円　の場合の当たり判定
		/// </summary>
		if (!circle->isPlayer)// オブジェクト同士が触れたら当たり判定を消す
		{
			// 自：円　他：円
			CombineObjects(CircleHit(pObj, circle), pObj, circle);
		}
		if (!square->isPlayer)// オブジェクト同士が触れたら当たり判定を消す
		{
			// 自：円　他：四角
			CombineObjects(CircleHit(pObj, square), pObj, square);
		}
		if (!triangle->isPlayer)
		{
			// 自：円　他：三角
			CombineObjects(CircleHit(pObj, triangle), pObj, triangle);
		}
	}
	else if (pObj->object == TRIANGLE)
	{
		/// <summary>
		/// 自：三角　の場合の当たり判定
		/// </summary>
		if (!circle->isPlayer)// オブジェクト同士が触れたら当たり判定を消す
		{
			// 自：三角　他：円
			CombineTriangleAndCircleObjects(TriangleHit(pObj, circle), pObj, circle);
		}
		if (!square->isPlayer)// オブジェクト同士が触れたら当たり判定を消す
		{
			// 自：三角　他：四角
			CombineTriangleAndSqureObjects(TriangleHit(pObj, square), pObj, square);

			// 自図形に合体した図形にも当たり判定を付けるための当たり判定① 三角と四角
			// 他：三角　他：四角
			//CombineTriangleObjects(TriangleHit(triangle, square), triangle, square);
		}
		if (!triangle->isPlayer)
		{
			// 自：三角　他：三角
			CombineTriangleObjects(TriangleHit(pObj, triangle), pObj, triangle);

			// 自図形に合体した図形にも当たり判定を付けるための当たり判定② 三角と四角
			// 他：四角　他：三角
			//CombineObjects(SquareHit(square, triangle), square,triangle);
		}
	}
}
//------------------------//

// ---図形同士が触れた時の処理--- //
void ObjectCollision::CombineObjects(int HitNum, TestObject* pObj, TestObject* eObj)
{
	// 操作していない図形の頂点座標を取得する
	std::vector<Vector2> Combineobj = eObj->vertices;
	// 操作している図形の座標を記録する
	BOUNDING_CIRCLE Combine = pObj->GetBoundingCircle();
	// 操作していない図形の座標を記録する
	BOUNDING_CIRCLE Combine2 = eObj->GetBoundingCircle();
	// 図形の角度変えるための変数
	DirectX::XMFLOAT3 rotation = pObj->m_objSprite->m_rotation;
	DirectX::XMFLOAT3 rotation2 = eObj->m_objSprite->m_rotation;

	switch (HitNum)
	{
	case 1:
		// 左
		rotation2.z = 0;
		eObj->SetRotation(rotation2);
		// 図形の角度が変わっていた場合初期値にする
		Combineobj = eObj->vertices;
		// 操作しているオブジェクトの横の座標を計算する
		Combine.center.x = Combine.center.x + Combine.radius + Combine2.radius;
		if (eObj->object == TRIANGLE)
		{
			Combine.center.y = Combine.center.y + Combine2.radius / 2;
		}
		// ぶつかったオブジェクトを操作しているオブジェクトの真横に移動させる
		eObj->SetBoundingCircle(Combine);
		// 操作していない図形のそれぞれの形によった初期化をする
		if (eObj->object == SQUARE)
		{
			// 操作していない四角形
			eObj->vertices = SetSquare(eObj, SQUREWIDTH);
			InitialPolygonSAT(eObj->GetBoundingCircle(), eObj, 0);
		}
		else if (eObj->object == TRIANGLE)
		{
			// 操作していない四角形
			eObj->vertices = SetTriangle(eObj);
			InitialPolygonSAT(eObj->GetBoundingCircle(), eObj, M_PI / 12);
			rotation2.z = 30 + rotation.z;
			eObj->SetRotation(rotation2);
		}
		else if (eObj->object == CIRCLE)
		{
			// 操作していない円
			eObj->vertices = SetCircle(eObj, CIRCLEWIDTH, SQUREWIDTH);
			InitialPolygonSAT(eObj->GetBoundingCircle(), eObj, 0);
		}
		// 操作しているオブジェクトと同じように移動する
		eObj->isPlayer = true;
		break;
	case 2:
		// 下
		rotation2.z = 0;
		eObj->SetRotation(rotation2);
		if (eObj->object == TRIANGLE)
		{
			Combine.center.y = Combine.center.y + Combine.radius + Combine2.radius * 2;
		}
		else
		{
			// 操作しているオブジェクトの横の座標を計算する
			Combine.center.y = Combine.center.y + Combine.radius + Combine2.radius;
		}
		// ぶつかったオブジェクトを操作しているオブジェクトの真横に移動させる
		eObj->SetBoundingCircle(Combine);
		// 操作していない図形のそれぞれの形によった初期化をする
		if (eObj->object == SQUARE)
		{
			// 操作していない四角形
			eObj->vertices = SetSquare(eObj, SQUREWIDTH);
		}
		else if (eObj->object == TRIANGLE)
		{
			// 操作していない四角形
			eObj->vertices = SetTriangle(eObj);
		}
		else if (eObj->object == CIRCLE)
		{
			// 操作していない円
			eObj->vertices = SetCircle(eObj, CIRCLEWIDTH, SQUREWIDTH);
		}
		InitialPolygonSAT(eObj->GetBoundingCircle(), eObj, 0);
		// 操作しているオブジェクトと同じように移動する
		eObj->isPlayer = true;
		break;
	case 3:
		// 上
		rotation2.z = 0;
		eObj->SetRotation(rotation2);
		// 操作しているオブジェクトの横の座標を計算する
		Combine.center.y = Combine.center.y - Combine.radius - Combine2.radius;
		if (eObj->object == TRIANGLE)
		{
			Combine.center.x = Combine.center.x - Combine2.radius / 2;
		}
		// ぶつかったオブジェクトを操作しているオブジェクトの真横に移動させる
		eObj->SetBoundingCircle(Combine);
		// 操作していない図形のそれぞれの形によった初期化をする
		if (eObj->object == SQUARE)
		{
			// 操作していない四角形
			eObj->vertices = SetSquare(eObj, SQUREWIDTH);
			InitialPolygonSAT(eObj->GetBoundingCircle(), eObj, 0);
		}
		else if (eObj->object == TRIANGLE)
		{
			// 操作していない四角形
			eObj->vertices = SetTriangle(eObj);
			InitialPolygonSAT(eObj->GetBoundingCircle(), eObj, M_PI / 6);
			rotation2.z = 60 + rotation.z;
			eObj->SetRotation(rotation2);
		}
		else if (eObj->object == CIRCLE)
		{
			// 操作していない円
			eObj->vertices = SetCircle(eObj, CIRCLEWIDTH, SQUREWIDTH);
			InitialPolygonSAT(eObj->GetBoundingCircle(), eObj, 0);
		}
		// 操作しているオブジェクトと同じように移動する
		eObj->isPlayer = true;
		break;
	case 4:
		// 右
		rotation2.z = 0;
		eObj->SetRotation(rotation2);
		// 操作しているオブジェクトの横の座標を計算する
		Combine.center.x = Combine.center.x - Combine.radius - Combine2.radius;
		if (eObj->object == TRIANGLE)
		{
			Combine.center.y = Combine.center.y + Combine2.radius / 2;
		}
		// ぶつかったオブジェクトを操作しているオブジェクトの真横に移動させる
		eObj->SetBoundingCircle(Combine);
		// 操作していない図形のそれぞれの形によった初期化をする
		if (eObj->object == SQUARE)
		{
			// 操作していない四角形
			eObj->vertices = SetSquare(eObj, SQUREWIDTH);
			InitialPolygonSAT(eObj->GetBoundingCircle(), eObj, 0);
		}
		else if (eObj->object == TRIANGLE)
		{
			// 操作していない四角形
			eObj->vertices = SetTriangle(eObj);
			InitialPolygonSAT(eObj->GetBoundingCircle(), eObj, -M_PI / 12);
			rotation2.z = -30 + rotation.z;
			eObj->SetRotation(rotation2);
		}
		else if (eObj->object == CIRCLE)
		{
			// 操作していない円
			eObj->vertices = SetCircle(eObj, CIRCLEWIDTH, SQUREWIDTH);
			InitialPolygonSAT(eObj->GetBoundingCircle(), eObj, 0);
		}
		// 操作しているオブジェクトと同じように移動する
		eObj->isPlayer = true;
		break;
	default:
		// 当たっていない
		break;
	}
}

void ObjectCollision::CombineTriangleObjects(int HitNum, TestObject* pObj, TestObject* eObj)
{
	std::vector<Vector2> Combineobj = eObj->vertices;// 三角の座標を取得する
	BOUNDING_CIRCLE Combine = pObj->GetBoundingCircle();// 円の座標を記録する
	BOUNDING_CIRCLE Combine2 = eObj->GetBoundingCircle();// 円の座標を記録する
	DirectX::XMFLOAT3 rotation = pObj->m_objSprite->m_rotation;
	DirectX::XMFLOAT3 rotation2 = eObj->m_objSprite->m_rotation;

	switch (HitNum)
	{
		//ーーー三角形のオブジェクトの合体ーーー

	case 5:
		// 左
		// 操作しているオブジェクトの横の座標を計算する
		// 図形が移動していた場合初期値にする
		eObj->m_objSprite->InitPos(0, 0, 0.1f);
		eObj->vertices = SetTriangle(eObj);
		// 図形の角度が変わっていた場合初期値にする
		eObj->rotation = 0;
		// 図形の移動をした後に図形の回転をする
		Combineobj = eObj->vertices;
		Combineobj = InitialPolygonSATvertices(eObj->GetBoundingCircle(), Combineobj, M_PI / 6.0f - eObj->rotation);
		Combine2.center.x = -Combineobj[1].x / 1.6 + Combine.center.x;
		Combine2.center.y = -Combineobj[2].y / 2.9 + Combine.center.y;
		InitialPolygonSAT(Combine2, eObj, -M_PI / 6.0f - eObj->rotation);//32
		// ぶつかったオブジェクトを操作しているオブジェクトの真横に移動させる
		eObj->m_objSprite->InitPos(Combine2.center.x, Combine2.center.y, 0.1f);
		rotation2.z = -60 + rotation.z;
		eObj->SetRotation(rotation2);
		// 操作しているオブジェクトと同じように移動する
		eObj->isPlayer = true;
		break;
	case 6:
		// 右
		// 操作しているオブジェクトの横の座標を計算する
		eObj->m_objSprite->InitPos(0, 0, 0.1f);
		eObj->vertices = SetTriangle(eObj);
		eObj->rotation = 0;
		Combineobj = eObj->vertices;
		Combineobj = InitialPolygonSATvertices(eObj->GetBoundingCircle(), Combineobj, M_PI / 6.0f - eObj->rotation);
		Combine2.center.x = Combineobj[1].x / 1.6 + Combine.center.x;
		Combine2.center.y = -Combineobj[2].y / 2.9 + Combine.center.y;
		InitialPolygonSAT(Combine2, eObj, M_PI / 6.0f - eObj->rotation);
		// ぶつかったオブジェクトを操作しているオブジェクトの真横に移動させる
		eObj->m_objSprite->InitPos(Combine2.center.x, Combine2.center.y, 0.1f);
		rotation2.z = 60 + rotation.z;
		eObj->SetRotation(rotation2);
		// 操作しているオブジェクトと同じように移動する
		eObj->isPlayer = true;
		break;
	case 7:
		// 下
		// 操作しているオブジェクトの横の座標を計算する
		eObj->m_objSprite->InitPos(0, 0, 0.1f);
		eObj->vertices = SetTriangle(eObj);
		eObj->rotation = 0;
		Combineobj = eObj->vertices;
		Combineobj = InitialPolygonSATvertices(eObj->GetBoundingCircle(), Combineobj, M_PI / 2.0f - eObj->rotation);
		Combine2.center.x = Combine.center.x;
		Combine2.center.y = -Combineobj[2].y * 2.15 + Combine.center.y;
		InitialPolygonSAT(Combine2, eObj, M_PI / 2.0f - eObj->rotation);
		// ぶつかったオブジェクトを操作しているオブジェクトの真横に移動させる
		eObj->m_objSprite->InitPos(Combine2.center.x, Combine2.center.y, 0.1f);
		rotation2.z = 180 + rotation.z;
		eObj->SetRotation(rotation2);
		// 操作しているオブジェクトと同じように移動する
		eObj->isPlayer = true;
		break;
	}
}

void ObjectCollision::CombineTriangleAndSqureObjects(int HitNum, TestObject* pObj, TestObject* eObj)
{
	std::vector<Vector2> Combineobj = eObj->vertices;// 円の座標を記録する
	BOUNDING_CIRCLE Combine = pObj->GetBoundingCircle();// 円の座標を記録する
	BOUNDING_CIRCLE Combine2 = eObj->GetBoundingCircle();// 円の座標を記録する
	DirectX::XMFLOAT3 rotation = pObj->m_objSprite->m_rotation;
	DirectX::XMFLOAT3 rotation2 = eObj->m_objSprite->m_rotation;

	//	// ーーー四角と三角ーーー
	switch (HitNum)
	{
	case 5:
		// 左
		// 操作しているオブジェクトの横の座標を計算する
		// 図形が移動していた場合初期値にする
		eObj->m_objSprite->InitPos(0, 0, 0.1f);
		eObj->vertices = SetSquare(eObj, SQUREWIDTH);
		// 図形の角度が変わっていた場合初期値にする
		eObj->rotation = 0;
		// 図形の移動をした後に図形の回転をする
		Combineobj = eObj->vertices;
		Combineobj = InitialPolygonSATvertices(eObj->GetBoundingCircle(), Combineobj, M_PI / 12.0f - eObj->rotation);
		Combine2.center.x = -Combineobj[1].x / 0.98 + Combine.center.x;
		Combine2.center.y = -Combineobj[2].y / 2.5 + Combine.center.y;
		InitialPolygonSAT(Combine2, eObj, -M_PI / 12.0f - eObj->rotation);//32
		// ぶつかったオブジェクトを操作しているオブジェクトの真横に移動させる
		eObj->m_objSprite->InitPos(Combine2.center.x, Combine2.center.y, 0.1f);
		rotation2.z = -30 + rotation.z;
		eObj->SetRotation(rotation2);
		// 操作しているオブジェクトと同じように移動する
		eObj->isPlayer = true;
		break;
	case 6:
		//// 右
		// 操作しているオブジェクトの横の座標を計算する
		// 図形が移動していた場合初期値にする
		eObj->m_objSprite->InitPos(0, 0, 0.1f);
		eObj->vertices = SetSquare(eObj, SQUREWIDTH);
		// 図形の角度が変わっていた場合初期値にする
		eObj->rotation = 0;
		// 図形の移動をした後に図形の回転をする
		Combineobj = eObj->vertices;
		Combineobj = InitialPolygonSATvertices(eObj->GetBoundingCircle(), Combineobj, M_PI / 12.0f - eObj->rotation);
		Combine2.center.x = Combineobj[1].x / 0.98 + Combine.center.x;
		Combine2.center.y = -Combineobj[2].y / 2.5 + Combine.center.y;
		InitialPolygonSAT(Combine2, eObj, M_PI / 12.0f - eObj->rotation);//32
		// ぶつかったオブジェクトを操作しているオブジェクトの真横に移動させる
		eObj->m_objSprite->InitPos(Combine2.center.x, Combine2.center.y, 0.1f);
		rotation2.z = 30 + rotation.z;
		eObj->SetRotation(rotation2);
		// 操作しているオブジェクトと同じように移動する
		eObj->isPlayer = true;
		break;
	case 7:
		// 下
		// 操作しているオブジェクトの横の座標を計算する
		eObj->m_objSprite->InitPos(0, 0, 0.1f);
		eObj->vertices = SetSquare(eObj, SQUREWIDTH);
		eObj->rotation = 0;
		Combineobj = eObj->vertices;
		Combineobj = InitialPolygonSATvertices(eObj->GetBoundingCircle(), Combineobj, M_PI / 2.0f - eObj->rotation);
		Combine2.center.x = Combine.center.x;
		Combine2.center.y = -Combineobj[2].y * 1.89f + Combine.center.y;
		InitialPolygonSAT(Combine2, eObj, M_PI / 2.0f - eObj->rotation);
		// ぶつかったオブジェクトを操作しているオブジェクトの真横に移動させる
		eObj->m_objSprite->InitPos(Combine2.center.x, Combine2.center.y, 0.1f);
		rotation2.z = 180 + rotation.z;
		eObj->SetRotation(rotation2);
		// 操作しているオブジェクトと同じように移動する
		eObj->isPlayer = true;
		break;
	}
}

void ObjectCollision::CombineTriangleAndCircleObjects(int HitNum, TestObject* pObj, TestObject* eObj)
{
	std::vector<Vector2> Combineobj = eObj->vertices;// 円の座標を記録する
	BOUNDING_CIRCLE Combine = pObj->GetBoundingCircle();// 円の座標を記録する
	BOUNDING_CIRCLE Combine2 = eObj->GetBoundingCircle();// 円の座標を記録する
	DirectX::XMFLOAT3 rotation = pObj->m_objSprite->m_rotation;
	DirectX::XMFLOAT3 rotation2 = eObj->m_objSprite->m_rotation;

	//	// ーーー円と三角ーーー
	switch (HitNum)
	{
	case 5:
		// 左
		// 操作しているオブジェクトの横の座標を計算する
		// 図形が移動していた場合初期値にする
		eObj->m_objSprite->InitPos(0, 0, 0.1f);
		eObj->vertices = SetCircle(eObj, CIRCLEWIDTH, SQUREWIDTH);
		// 図形の角度が変わっていた場合初期値にする
		eObj->rotation = 0;
		// 図形の移動をした後に図形の回転をする
		Combineobj = eObj->vertices;
		Combineobj = InitialPolygonSATvertices(eObj->GetBoundingCircle(), Combineobj, M_PI / 12.0f - eObj->rotation);
		Combine2.center.x = -Combineobj[3].x / 0.65 + Combine.center.x;
		Combine2.center.y = -Combineobj[5].y / 1.7 + Combine.center.y;
		InitialPolygonSAT(Combine2, eObj, -M_PI / 12.0f - eObj->rotation);//32
		// ぶつかったオブジェクトを操作しているオブジェクトの真横に移動させる
		eObj->m_objSprite->InitPos(Combine2.center.x, Combine2.center.y, 0.1f);
		rotation2.z = -30 + rotation.z;
		eObj->SetRotation(rotation2);
		// 操作しているオブジェクトと同じように移動する
		eObj->isPlayer = true;
		break;
	case 6:
		//// 右
		// 操作しているオブジェクトの横の座標を計算する
		// 図形が移動していた場合初期値にする
		eObj->m_objSprite->InitPos(0, 0, 0.1f);
		eObj->vertices = SetCircle(eObj, CIRCLEWIDTH, SQUREWIDTH);
		// 図形の角度が変わっていた場合初期値にする
		eObj->rotation = 0;
		// 図形の移動をした後に図形の回転をする
		Combineobj = eObj->vertices;
		Combineobj = InitialPolygonSATvertices(eObj->GetBoundingCircle(), Combineobj, M_PI / 12.0f - eObj->rotation);
		Combine2.center.x = Combineobj[3].x / 0.65 + Combine.center.x;
		Combine2.center.y = -Combineobj[5].y / 1.7 + Combine.center.y;
		InitialPolygonSAT(Combine2, eObj, M_PI / 12.0f - eObj->rotation);//32
		// ぶつかったオブジェクトを操作しているオブジェクトの真横に移動させる
		eObj->m_objSprite->InitPos(Combine2.center.x, Combine2.center.y, 0.1f);
		rotation2.z = 30 + rotation.z;
		eObj->SetRotation(rotation2);
		// 操作しているオブジェクトと同じように移動する
		eObj->isPlayer = true;
		break;
	case 7:
		// 下
		// 操作しているオブジェクトの横の座標を計算する
		eObj->m_objSprite->InitPos(0, 0, 0.1f);
		eObj->vertices = SetCircle(eObj, CIRCLEWIDTH, SQUREWIDTH);
		eObj->rotation = 0;
		Combineobj = eObj->vertices;
		Combineobj = InitialPolygonSATvertices(eObj->GetBoundingCircle(), Combineobj, M_PI / 2.0f - eObj->rotation);
		Combine2.center.x = Combine.center.x;
		Combine2.center.y = -Combineobj[5].y * 2.8f + Combine.center.y;
		InitialPolygonSAT(Combine2, eObj, M_PI / 2.0f - eObj->rotation);
		// ぶつかったオブジェクトを操作しているオブジェクトの真横に移動させる
		eObj->m_objSprite->InitPos(Combine2.center.x, Combine2.center.y, 0.1f);
		rotation2.z = 180 + rotation.z;
		eObj->SetRotation(rotation2);
		// 操作しているオブジェクトと同じように移動する
		eObj->isPlayer = true;
		break;
	}
}
//--------------------------------//

// ---図形によって当たり判定を変える--- //
int ObjectCollision::CircleHit(TestObject* pObj, TestObject* eObj)
{
	// 三角形の頂点座標とテスト対象の点を設定
	// 操作している四角形
	pObj->vertices = SetCircle(pObj, CIRCLEWIDTH, SQUREWIDTH);
	pObj->jodgevertices = SetSquare(pObj, SQUREWIDTH);
	int j = 0;
	for (auto& jodgevertices : pObj->jodgevertices)
	{
		jodgevertices = pObj->vertices[j];
		j += 2;
	}

	// 操作していない図形のそれぞれの形によった初期化をする
	if (eObj->object == SQUARE)
	{
		// 操作していない四角形
		eObj->vertices = SetSquare(eObj, SQUREWIDTH);
		eObj->jodgevertices = SetSquare(eObj, SQUREWIDTH);
		int j = 0;
		for (auto& jodgevertices : eObj->jodgevertices)
		{
			jodgevertices = eObj->vertices[j];
			j++;
		}
		// 三角と円が触れている時
		return SqureAndCircleCollision(pObj, eObj);
	}
	if (eObj->object == TRIANGLE)
	{
		// 操作していない四角形
		eObj->vertices = SetTriangle(eObj);
		eObj->jodgevertices = SetTriangle(eObj);
		int j = 0;
		for (auto& jodgevertices : eObj->jodgevertices)
		{
			jodgevertices = eObj->vertices[j];
			j++;
		}

		// 三角と円が触れている時
		return SqureAndCircleCollision(pObj, eObj);
	}
	if (eObj->object == CIRCLE)
	{
		// 操作していない円
		eObj->vertices = SetCircle(eObj, CIRCLEWIDTH, SQUREWIDTH);
		eObj->jodgevertices = SetSquare(eObj, SQUREWIDTH);
		int j = 0;
		for (auto& jodgevertices : eObj->jodgevertices)
		{
			jodgevertices = eObj->vertices[j];
			j += 2;
		}
		// 三角と円が触れている時
		return SqureAndCircleCollision(pObj, eObj);
	}
}

int ObjectCollision::SquareHit(TestObject* pObj, TestObject* eObj)
{
	// 三角形の頂点座標とテスト対象の点を設定
	// 操作している四角形
	pObj->vertices = SetSquare(pObj, SQUREWIDTH);
	pObj->jodgevertices = pObj->vertices;

	// 操作していない図形のそれぞれの形によった初期化をする
	if (eObj->object == SQUARE)
	{
		// 操作していない四角形
		eObj->vertices = SetSquare(eObj, SQUREWIDTH);
		eObj->jodgevertices = eObj->vertices;

		// 三角と円が触れている時
		return SqureCollision(pObj, eObj);
	}
	if (eObj->object == TRIANGLE)
	{
		// 操作していない四角形
		eObj->vertices = SetTriangle(eObj);
		eObj->jodgevertices = SetSquare(eObj, SQUREWIDTH);

		// 三角と円が触れている時
		return SqureCollision(pObj, eObj);
	}
	if (eObj->object == CIRCLE)
	{
		// 操作していない円
		eObj->vertices = SetCircle(eObj, CIRCLEWIDTH, SQUREWIDTH);

		eObj->jodgevertices = SetSquare(eObj, SQUREWIDTH);
		int j = 0;
		for (auto& jodgevertices : eObj->jodgevertices)
		{
			jodgevertices = eObj->vertices[j];
			j += 2;
		}

		// 三角と円が触れている時
		return SqureAndCircleCollision(pObj, eObj);
	}
}

int ObjectCollision::TriangleHit(TestObject* pObj, TestObject* eObj)
{
	// 三角形の頂点座標とテスト対象の点を設定
	// 操作している三角形
	pObj->vertices = SetTriangle(pObj);

	// 操作していない図形のそれぞれの形によった初期化をする
	if (eObj->object == SQUARE)
	{
		// 操作していない四角形
		eObj->vertices = SetSquare(eObj, SQUREWIDTH);
	}
	if (eObj->object == TRIANGLE)
	{
		// 操作していない三角形
		eObj->vertices = SetTriangle(eObj);
	}
	if (eObj->object == CIRCLE)
	{
		// 操作していない四角形
		eObj->vertices = SetCircle(eObj, CIRCLEWIDTH, SQUREWIDTH);
	}

	// 三角同士が触れている時
	return TriangleCollision(pObj, eObj);
}
//-------------------------------------//

// ---図形の当たり判定の処理 ---//
bool ObjectCollision::SATHit(TestObject* pObj, TestObject* eObj)
{
	PolygonSAT Triangle1(pObj->vertices, pObj->rotation);
	PolygonSAT Triangle2(eObj->vertices, eObj->rotation);

	pObj->vertices = Triangle1.GetRotatedVertices();
	eObj->vertices = Triangle2.GetRotatedVertices();

	BOUNDING_CIRCLE circle1 = pObj->GetBoundingCircle();
	BOUNDING_CIRCLE circle2 = eObj->GetBoundingCircle();
	// 四角
	for (auto& vertex : pObj->vertices) {
		vertex.x += circle1.center.x;
		vertex.y += circle1.center.y;
	}

	for (auto& vertex : eObj->vertices) {
		vertex.x += circle2.center.x;
		vertex.y += circle2.center.y;
	}

	Triangle1.vertices = pObj->vertices;
	Triangle2.vertices = eObj->vertices;

	bool collisionResult = Collide(Triangle1, Triangle2);

	// 結果を表示
	if (collisionResult)
	{
		return true;
	}
	return false;
}

int ObjectCollision::SqureCollision(TestObject* pObj, TestObject* eObj)
{
	BOUNDING_CIRCLE circle1 = pObj->GetBoundingCircle();
	BOUNDING_CIRCLE circle2 = eObj->GetBoundingCircle();
	if (eObj->object == SQUARE)
	{
		// 操作していない四角形
		p_verticies = SetSquare(pObj, SQUREWIDTH);
	}
	else if (eObj->object == TRIANGLE)
	{
		if (eObj->rotation >= 0)
		{
			// 操作していない四角形
			p_verticies = SetSquare(pObj, 0.9);//1.16 上下左右の判定がおかしいから
		}
		else
		{
			// 操作していない四角形
			p_verticies = SetSquare(pObj, 1.1);//1.16 上下左右の判定がおかしいから
		}

	}
	p_verticies = InitialPolygonSATvertices(pObj->GetBoundingCircle(), p_verticies, pObj->rotation);

	// 三角同士が触れている時
	if (SATHit(pObj, eObj))
	{
		// 図形が回転したときの座標の変換
		if (eObj->rotation < 0)
		{
			// 図形の角度が180度未満の時の座標
			RotationJodge = 0;

		}
		else if (eObj->rotation < M_PI / 2)
		{
			// 図形の角度が180度以上の時の座標
			RotationJodge = 2;
		}
		else
		{
			// 図形の角度が180度未満の時の座標
			RotationJodge = 0;
		}

		eObj->jodgevertices = InitialPolygonSATvertices(eObj->GetBoundingCircle(), eObj->jodgevertices, eObj->rotation);

		// 四角形が上下のどちらかからぶつかった時に左右の当たり判定が機能しないようにするための処理
		if (p_verticies[0].y > eObj->jodgevertices[0 + RotationJodge].y
			&& p_verticies[2].y < eObj->jodgevertices[2 - RotationJodge].y
			&& eObj->p_verticies2[0].y > eObj->jodgevertices[0 + RotationJodge].y
			&& eObj->p_verticies2[2].y < eObj->jodgevertices[2 - RotationJodge].y)
		{
			// 左右
			// 四角形に当たる直前に右方向に入力されているか
			if (circle1.center.x < circle2.center.x && eObj->p_center.center.x < circle1.center.x)
			{
				// 四角形の左側に円が触れた場合の当たり判定
				if (pObj->vertices[2].x < eObj->vertices[1].x)// 左
				{
					return 1;
				}
			}
			// 四角形に当たる直前に左方向に入力されているか
			else if (circle1.center.x > circle2.center.x && eObj->p_center.center.x > circle1.center.x)
			{
				// 四角形の右側に円が触れた場合の当たり判定
				if (pObj->vertices[1].x > eObj->vertices[2].x)// 右
				{
					return 4;
				}
			}
		}
		// 上下
		// 四角形に当たる直前に下方向に入力されているか
		if (circle1.center.y > circle2.center.y && eObj->p_center.center.y > circle1.center.y)
		{
			// 四角形の上側に円が触れた場合の当たり判定
			if (pObj->vertices[0].y > eObj->vertices[1].y)// 上
			{
				return 3;
			}
		}
		// 四角形に当たる直前に上方向に入力されているか
		else if (circle1.center.y < circle2.center.y && eObj->p_center.center.y < circle1.center.y)
		{
			// 四角形の下側に円が触れた場合の当たり判定
			if (pObj->vertices[1].y < eObj->vertices[0].y)// 下
			{
				return 2;
			}
		}
	}
	else
	{
		eObj->p_verticies2 = p_verticies;
		eObj->p_center = pObj->GetBoundingCircle();
	}

	return 0;
}

int ObjectCollision::SqureAndCircleCollision(TestObject* pObj, TestObject* eObj)
{
	BOUNDING_CIRCLE circle1 = pObj->GetBoundingCircle();
	BOUNDING_CIRCLE circle2 = eObj->GetBoundingCircle();

	// 三角同士が触れている時
	if (SATHit(pObj, eObj))
	{
		// 四角形が上下のどちらかからぶつかった時に左右の当たり判定が機能しないようにするための処理
		if (eObj->p_center2.center.y - circle1.radius < circle2.center.y + circle2.radius
			&& eObj->p_center2.center.y + circle1.radius > circle2.center.y - circle2.radius)
		{
			// 左右
			// 四角形に当たる直前に右方向に入力されているか
			if (circle1.center.x < circle2.center.x && eObj->p_center2.center.x < circle1.center.x)
			{
				// 四角形の左側に円が触れた場合の当たり判定
				if (pObj->jodgevertices[2].x < eObj->jodgevertices[1].x)// 左
				{
					return 1;
				}
			}
			// 四角形に当たる直前に左方向に入力されているか
			else if (circle1.center.x > circle2.center.x && eObj->p_center2.center.x > circle1.center.x)
			{
				// 四角形の右側に円が触れた場合の当たり判定
				if (pObj->jodgevertices[1].x > eObj->jodgevertices[2].x)// 右
				{
					return 4;
				}
			}
		}
		// 上下
		// 四角形に当たる直前に下方向に入力されているか
		if (circle1.center.y > circle2.center.y && eObj->p_center2.center.y > circle1.center.y)
		{
			// 四角形の上側に円が触れた場合の当たり判定
			if (pObj->jodgevertices[0].y > eObj->jodgevertices[1].y)// 上
			{
				return 3;
			}
		}
		// 四角形に当たる直前に上方向に入力されているか
		else if (circle1.center.y < circle2.center.y && eObj->p_center2.center.y < circle1.center.y)
		{
			// 四角形の下側に円が触れた場合の当たり判定
			if (pObj->jodgevertices[1].y < eObj->jodgevertices[0].y)// 下
			{
				return 2;
			}
		}
	}
	else
	{
		eObj->p_center2 = pObj->GetBoundingCircle();
	}

	return 0;
}

int ObjectCollision::TriangleCollision(TestObject* pObj, TestObject* eObj)
{
	BOUNDING_CIRCLE circle1 = pObj->GetBoundingCircle();
	BOUNDING_CIRCLE circle2 = eObj->GetBoundingCircle();

	// 三角同士が触れている時
	if (SATHit(pObj, eObj))
	{
		if (eObj->vertices[0].y > circle1.center.y)
		{
			// 右上にあるとき
			if (pObj->vertices[0].x < circle2.center.x)
			{
				// 右
				return 6;
			}
			// 左上にあるとき
			else if (pObj->vertices[0].x > circle2.center.x)
			{
				// 左
				return 5;
			}
		}
		// 上にあるとき
		else
		{
			// 上
			return 7;
		}
	}

	return 0;
}
//------------------------------//

// ---図形の頂点座標の設定--- //
std::vector<Vector2> ObjectCollision::SetTriangle(TestObject* Obj)
{
	Triangle triangle;
	triangle.A = { 0                                , 0.9f + Obj->Scale_countY };
	triangle.B = { 1.1f + Obj->Scale_countX, -0.9f - Obj->Scale_countY };
	triangle.C = { -1.1f - Obj->Scale_countX, -0.9f - Obj->Scale_countY };


	// 1つ目の凸多角形の頂点座標を定義
	std::vector<Vector2> vertices = {
		Vector2(triangle.A.x, triangle.A.y),
		Vector2(triangle.B.x, triangle.B.y),
		Vector2(triangle.C.x, triangle.C.y),
	};

	return vertices;
}

std::vector<Vector2> ObjectCollision::SetSquare(TestObject* Obj, float width)
{
	SQURE squre;
	// 四角の下の三角
	squre.A = { width + Obj->Scale_countX,
				width + Obj->Scale_countY };
	squre.B = { width + Obj->Scale_countX,
				-width + -Obj->Scale_countY };
	squre.C = { -width - Obj->Scale_countX,
				-width + -Obj->Scale_countY };
	squre.D = { -width - Obj->Scale_countX,
				 width + Obj->Scale_countY };

	// 1つ目の凸多角形の頂点座標を定義
	std::vector<Vector2> vertices = {
		Vector2(squre.A.x, squre.A.y),
		Vector2(squre.B.x, squre.B.y),
		Vector2(squre.C.x, squre.C.y),
		Vector2(squre.D.x, squre.D.y),
	};

	return vertices;
}

std::vector<Vector2> ObjectCollision::SetCircle(TestObject* Obj, float squarewidth, float circlewidth)
{
	SQURE squre;
	// 四角の下の三角
	squre.A = { squarewidth + Obj->Scale_countX,
				squarewidth + Obj->Scale_countY };
	squre.B = { squarewidth + Obj->Scale_countX,
				-squarewidth + -Obj->Scale_countY };
	squre.C = { -squarewidth - Obj->Scale_countX,
				-squarewidth + -Obj->Scale_countY };
	squre.D = { -squarewidth - Obj->Scale_countX,
				 squarewidth + Obj->Scale_countY };

	SQURE circle;
	// 四角の下の三角
	circle.A = { 0, circlewidth + Obj->Scale_countY };
	circle.B = { circlewidth + Obj->Scale_countX,0 };
	circle.C = { 0 , -circlewidth - Obj->Scale_countY };
	circle.D = { -circlewidth - Obj->Scale_countX,0 };


	// 1つ目の凸多角形の頂点座標を定義
	std::vector<Vector2> vertices = {
		Vector2(circle.A.x, circle.A.y),
		Vector2(squre.A.x, squre.A.y),
		Vector2(circle.B.x, circle.B.y),
		Vector2(squre.B.x, squre.B.y),
		Vector2(circle.C.x, circle.C.y),
		Vector2(squre.C.x, squre.C.y),
		Vector2(circle.D.x, circle.D.y),
		Vector2(squre.D.x, squre.D.y),
	};
	return vertices;
}

void ObjectCollision::InitialPolygonSAT(BOUNDING_CIRCLE circle1, TestObject* Obj, float rotation)
{
	//BOUNDING_CIRCLE circle4 = testObj->GetBoundingCircle();// 操作していないオブジェクト 
	PolygonSAT Triangle3(Obj->vertices, rotation);
	Obj->vertices = Triangle3.GetRotatedVertices();
	for (auto& vertex : Obj->vertices) {
		vertex.x = vertex.x + circle1.center.x;
		vertex.y = vertex.y + circle1.center.y;
	}
}

std::vector<Vector2> ObjectCollision::InitialPolygonSATvertices(BOUNDING_CIRCLE circle1, std::vector<Vector2> vertices, float rotation)
{
	PolygonSAT Triangle3(vertices, rotation);
	vertices = Triangle3.GetRotatedVertices();
	for (auto& vertex : vertices) {
		vertex.x = vertex.x + circle1.center.x;
		vertex.y = vertex.y + circle1.center.y;
	}

	return vertices;
}
//----------------------------//