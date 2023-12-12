#include "Game.h"
#include "Direct3D/Direct3D.h"
#include "Assets.h"
#include "ObjectAnimation.h"
#include "StaticAnimation.h"
#include "TrackCamera.h"
#include "DebugManager.h"
#include "DInput.h"

#include "SAT.h"
#include <algorithm> // 必要なヘッダーファイル
#define SQUREWIDTH 1.2
#define TRIANGLEWIDTH 0.8
#define M_PI 3.14159265358979323846
#define M_PIX 0.1//1.5
#define M_PIY 0.0333333333// 0.5

extern Assets* g_Assets;
extern Camera* g_WorldCamera;
extern DebugManager* g_DebugManager;

Game::Game()
{
	////オブジェクト初期化
	//testObject = new Object(g_Assets->testchar01, 96, 96, 3, 4);
	////アニメーションクラス初期化->どのアニメーションにする
	//testObject->m_sprite->m_anime = new ObjectAnimation(3, 4);
	////アニメーション速度を設定
	//testObject->m_sprite->m_anime->SetAnimeSpeed(0.1f);
	////アニメーションパターンを設定
	//testObject->m_sprite->m_anime->SetAnimePattern(0);

	// オブジェクト1
	testObj = new TestObject();
	//オブジェクトの初期設定
	testObj->SetObjTex(g_Assets->triangle, 200, 200, 1, 1);
	testObj->m_objSprite->m_anime = new ObjectAnimation(1, 1);
	testObj->m_objSprite->m_anime->SetAnimeSpeed(0.0f);
	testObj->m_objSprite->m_anime->SetAnimePattern(0);
	testObj->m_objSprite->InitPos(-4, -1.16, 0.2f);
	DirectX::XMFLOAT3 rotation = testObj->m_objSprite->m_rotation;
	testObj->isPlayer = true;// キーボードで操作可能
	BOUNDING_CIRCLE circle1 = testObj->GetBoundingCircle();// 操作していないオブジェクト 
	testObj->vertices = SetTriangle(circle1, testObj);

	// オブジェクト2
	testObj2 = new TestObject();
	//オブジェクトの初期設定
	//testObj2->SetObjTex(g_Assets->testShadow, 200, 200, 1, 1);
	testObj2->SetObjTex(g_Assets->square, 200, 200, 1, 1);//square
	testObj2->m_objSprite->m_anime = new ObjectAnimation(1, 1);
	testObj2->m_objSprite->m_anime->SetAnimeSpeed(0.0f);
	testObj2->m_objSprite->m_anime->SetAnimePattern(0);
	testObj2->m_objSprite->InitPos(5, 0, 0.1f);
	rotation.z = 60;
	testObj2->SetRotation(rotation);
	testObj2->rotation = M_PI / 6;// 45
	testObj2->vertices = SetSqureWithTriangle(testObj2->GetBoundingCircle(), testObj2, SQUREWIDTH);

	// オブジェクト3
	testObj3 = new TestObject();
	//オブジェクトの初期設定
	//testObj2->SetObjTex(g_Assets->testShadow, 200, 200, 1, 1);
	testObj3->SetObjTex(g_Assets->testObj, 200, 200, 1, 1);//square
	testObj3->m_objSprite->m_anime = new ObjectAnimation(1, 1);
	testObj3->m_objSprite->m_anime->SetAnimeSpeed(0.0f);
	testObj3->m_objSprite->m_anime->SetAnimePattern(0);
	testObj3->m_objSprite->InitPos(6, 6, 0.1f);

	testObj4 = new TestObject();
	testObj4->SetObjTex(g_Assets->triangle, 200, 200, 1, 1);//square
	testObj4->m_objSprite->m_anime = new ObjectAnimation(1, 1);
	testObj4->m_objSprite->m_anime->SetAnimeSpeed(0.0f);
	testObj4->m_objSprite->m_anime->SetAnimePattern(0);
	testObj4->m_objSprite->InitPos(0, 0, 0.1f);
	rotation.z = 0;
	testObj4->SetRotation(rotation);
	testObj4->rotation = 0;// 45 M_PI / 8
	testObj4->vertices = SetTriangle(testObj4->GetBoundingCircle(), testObj4);


	//オブジェクト作成
	testWall = new Object(g_Assets->testWallbg, 1280, 720, 1, 1);
	testGround = new Object(g_Assets->testGroundbg, 1280, 720, 1, 1);
	testWall->m_sprite->m_scale = { 1.0, 1.0, 1.0 };

	//オブジェクトの初期設定・テクスチャの読み込み
	testChara = new Object(g_Assets->testChara01, 32, 32, 3, 4);
	
	testTree = new GameObject();
	testTree->CreateObject(g_Assets->testObj, 300, 300, 1, 1);
	testTree->CreateShadow(g_Assets->testShadow, 300, 300, 1, 1);

	uitest = new CanvasUI();
	uitest->CreateModel(g_Assets->testWallbg, 128, 72, 1, 1);

	uitest->m_pos.z = 0.2f;
	
	//影の初期設定
	//testObj->SetShadowTex(g_Assets->testShadow, 200, 200, 1, 1);
	//testObj->m_shadowSprite->m_anime = new ObjectAnimation(1, 1);
	//testObj->m_shadowSprite->m_anime->SetAnimeSpeed(0.0f);
	//testObj->m_shadowSprite->m_anime->SetAnimePattern(0);
	//testObj->m_shadowSprite->InitPos(1.7, 0.712, 0.2f);


	//オブジェクト初期化
	testBg = new Object(g_Assets->testbgbox, 1280, 720, 1, 1);
	testBg->m_sprite->m_pos.z = 0.9;//前後の位置設定をクラス化で行う
	//アニメーションクラス初期化->どのアニメーションにする
	testBg->m_sprite->m_anime = new ObjectAnimation(1, 1);
	//アニメーション速度を設定
	testBg->m_sprite->m_anime->SetAnimeSpeed(0.0f);
	//アニメーションパターンを設定
	testBg->m_sprite->m_anime->SetAnimePattern(0);



	//アニメーションの設定
	testWall->m_sprite->m_anime = new StaticAnimation(1, 1);
	testGround->m_sprite->m_anime = new ObjectAnimation(1, 1);
	testChara->m_sprite->m_anime = new ObjectAnimation(3, 4);
	testChara->m_sprite->m_anime->SetAnimeSpeed(0.2f);

	testTree->m_obj->m_anime = new StaticAnimation(1, 1);
	testTree->m_shadow->m_obj->m_anime = new StaticAnimation(1, 1);



	//初期位置設定
	testWall->m_sprite->m_pos = { 0.0f, 1.5f, 2.0f };
	testGround->m_sprite->m_pos = { 0.0f, 1.5f, 2.0f };

	testGround->m_sprite->m_rotation.x = 90;
	testGround->m_sprite->m_pos.y = -360 / SCREEN_PARA + 1.5f;

	testChara->m_sprite->m_pos.y = (-360 + 96) / SCREEN_PARA + 1.5f;
	testChara->m_sprite->m_pos.z = -0.5f;
	testChara->m_sprite->m_scale = { 3.0f,3.0f,3.0f };

	//影の位置設定
	testTree->m_shadow->m_obj->m_pos.z = 1.99f;

	//dynamic_cast<TrackCamera*>(g_WorldCamera)->SetTarget(testWall);

	
}

void Game::GameUpdate(void)
{
	switch (m_gameScene)
	{
	case TITLE:

		TitleUpdate();
		break;

	case STAGE1:

		StageUpdate();
		break;

	case RESULT:

		ResultUpdate();
		break;

	}
}

void Game::TitleUpdate(void)
{	

	if (Input::Get()->GetKeyPress(DIK_UPARROW)) {
		//testChara->m_sprite->m_pos.z += 0.1f;
		testChara->m_sprite->m_rotation.x += 0.8f;
	}
	if (Input::Get()->GetKeyPress(DIK_LEFTARROW)) {
		testChara->m_sprite->m_pos.x -= 0.1f;
		testChara->m_sprite->m_rotation.x -= 0.8f;
	}
	if (Input::Get()->GetKeyPress(DIK_RIGHTARROW)) {
		testChara->m_sprite->m_pos.x += 0.1f;
	}
	if (Input::Get()->GetKeyPress(DIK_DOWNARROW)) {
		testChara->m_sprite->m_pos.z -= 0.1f;
	}

	testWall->Update();

	//背景
	testGround->Update();
	

	testTree->Update(testChara->m_sprite->m_pos);

	testChara->Update();

	uitest->Update();



	

}

void Game::StageUpdate(void)
{
}


void Game::ResultUpdate(void)
{

}

Game::~Game()
{
	delete testChara;
	delete testWall;
	delete testGround;

	delete testTree;
	delete uitest;
}

void Game::GameDraw()
{

	D3D_ClearScreen();

	//============ ここから描画処理 ============//


	switch (m_gameScene)
	{
	case TITLE:

		TitleDraw();
		break;

	case STAGE1:

		StageDraw();
		break;

	case RESULT:

		ResultDraw();
		break;

	}

	//============ ここまで描画処理 ============//

	//ダブルバッファの切り替えを行い画面を更新する
	GetD3D_DATA()->SwapChain->Present(0, 0);
}

void Game::TitleDraw(void)
{
	//testWall->Draw();

	//testGround->Draw();

	testTree->Draw();

	testChara->Draw();
	testObj4->Draw();

	//デバッグ表示 
	//40->一文字の幅/高さの二倍
	float posX = (-SCREEN_WIDTH / 2 + 40.0f) / SCREEN_PARA;
	float posY = ((SCREEN_HEIGHT / 2) - 40.0f) / SCREEN_PARA;
	g_DebugManager->PrintDebugLog(posX, posY, testChara->m_sprite->m_pos.x);

	
}

void Game::StageDraw(void)
{
}

void Game::ResultDraw(void)
{
}

void Game::SetGameScene(GAMESCENE scene)
{
	m_gameScene = scene;
}


void Game::TestCollision()
{
	BOUNDING_CIRCLE circle1 = testObj->GetBoundingCircle();// 操作しているオブジェクト
	BOUNDING_CIRCLE circle2 = testObj2->GetBoundingCircle();// 操作していないオブジェクト 
	BOUNDING_CIRCLE circle3 = testObj3->GetBoundingCircle();// 操作していないオブジェクト 
	BOUNDING_CIRCLE circle4 = testObj4->GetBoundingCircle();// 操作していないオブジェクト 
	//Triangle triangle, triangle2;
	//std::vector<Vector2> verticesA,verticesB;

	// ここで当たり判定を切り替える
	//円同士
	//MoveObjects(CircleHit(circle1, circle2), Combine, circle1, circle2);

	if (!testObj3->isPlayer)// オブジェクト同士が触れたら当たり判定を消す
	{
		// 円と四角 1四角　２四角　３円
		// SqureandCircle関数　引数１：円　２：四角 3:四角のテクスチャが入っている方を入れる
		// MoveObjects関数　引数１：オブジェクトがどこに当たったのかの戻り値　引数２：合体させる元のオブジェクトの座標
		// 　　　　　　     引数３,４,５：MoveObjects関数の引数と同じ
		//CombineObjects(SqureandCircle(circle1, circle3, testObj3),circle1, circle3, testObj3);

		//CombineObjects(SqureandCircle(circle2, circle3, testObj3), circle2, circle3, testObj3);

		// 三角と円
		//CombineTriangleObjects(CheckTriangleAndCircleHit(circle1, circle3, testObj, testObj3), circle1, circle3, testObj,testObj3);
	}

	if (!testObj2->isPlayer)// オブジェクト同士が触れたら当たり判定を消す
	{
		// 四角と四角 引数１：操作しているオブジェクト　引数２：操作していないオブジェクト
		//CombineObjects(SqureHit(circle1, circle2, testObj, testObj2),circle1, circle2, testObj2);

		//CombineObjects(SqureandCircle(circle3, circle2, testObj2), circle3, circle2, testObj2);

		// 三角と四角　１三角　４三角　２四角
		CombineTriangleObjects(CheckTriangleAndSqureHit(circle1, circle2, testObj, testObj2), circle1, circle2, testObj, testObj2);

		//CombineTriangleObjects(CheckTriangleAndSqureHit(circle4, circle2, testObj4, testObj2), circle4, circle2, testObj4, testObj2);
	}

	if (!testObj4->isPlayer)
	{
		// 三角同士
		//CombineObjects(CheckTriangleHit(circle1, circle4, testObj, testObj4), circle1, circle4, testObj, testObj4);

		//CombineObjects(CheckTriangleAndSqureHit(circle2, circle4, testObj2, testObj4), circle2, circle4, testObj4);

		CombineTriangleObjects(CheckTriangleHit(circle1, circle4, testObj, testObj4), circle1, circle4, testObj, testObj4);

	}

}

int Game::CircleHit(BOUNDING_CIRCLE bc1, BOUNDING_CIRCLE bc2)
{
	//bc1 円　bc2 円
	float teihen = bc2.center.x - bc1.center.x;// 底辺の長さ
	float takasa = bc2.center.y - bc1.center.y;// 高さ
	float r2 = bc1.radius + bc2.radius; // 円1の半径＋円2の半径

	if (teihen * teihen + takasa * takasa <= r2 * r2)
	{
		// 上下左右の当たり判定で別の戻り値を返す
		return SideCollision(bc1, bc2);
	}

	return 0;
}

bool Game::CheckHit(const BOX& t_box, const BOUNDING_CIRCLE bc1)
{
	bool nResult = false;

	// 四角形の四辺に対して円の半径分だけ足したとき円が重なっていたら
	if ((bc1.center.x > t_box.fLeft - bc1.radius) &&
		(bc1.center.x < t_box.fRight + bc1.radius) &&
		(bc1.center.y > t_box.fTop - bc1.radius) &&
		(bc1.center.y < t_box.fBottom + bc1.radius))
	{
		// 当たっている
		nResult = true;
	}

	return nResult;
}

int Game::SqureandCircle(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj)
{
	BOX squre; // 四角形の四辺を入れる変数を取得する

	// 四角形の左右に触れた場合の四辺の座標
	float X_posx1 = 1.4 + circle2.center.x + testObj->Scale_countX;
	float X_posx2 = -1.4 + circle2.center.x - testObj->Scale_countX;
	float X_posy1 = 1 + circle2.center.y + testObj->Scale_countY;
	float X_posy2 = -1 + circle2.center.y - testObj->Scale_countY;

	// 四角形の上下に触れた場合の四辺の座標
	float Y_posx1 = 1.4 + circle2.center.y + testObj->Scale_countX;
	float Y_posx2 = -1.4 + circle2.center.y - testObj->Scale_countX;
	float Y_posy1 = 1 + circle2.center.x + testObj->Scale_countX;
	float Y_posy2 = -1 + circle2.center.x - testObj->Scale_countX;
	//testObj2->m_objSprite->InitBox(-1, -1.4, 1, -1.4);

	// 左右
	// 四角形の左側に円が触れた場合の当たり判定
	if (CheckHit(squre = { X_posx2, X_posy2, X_posx2, X_posy1 }, circle1))// 左
	{
		return 1;
	}
	// 四角形の右側に円が触れた場合の当たり判定
	else if (CheckHit(squre = { X_posx1, X_posy2, X_posx1, X_posy1 }, circle1))// 右
	{
		return 4;
	}
	// 上下
	// 四角形の下側に円が触れた場合の当たり判定
	else if (CheckHit(squre = { Y_posy2, Y_posx2, Y_posy1, Y_posx2 }, circle1))// 下
	{
		return 2;
	}
	// 四角形の上側に円が触れた場合の当たり判定
	else if (CheckHit(squre = { Y_posy2, Y_posx1, Y_posy1, Y_posx1 }, circle1))// 上
	{
		return 3;
	}

	return 0;
}

int Game::SqureHit(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj, TestObject* testObj2)
{
	// 四角形同士の当たり判定
	if ((circle1.center.x + circle1.radius >= circle2.center.x - circle2.radius) &&
		(circle2.center.x + circle2.radius >= circle1.center.x - circle1.radius) &&
		(circle1.center.y + circle1.radius >= circle2.center.y - circle2.radius) &&
		(circle2.center.y + circle2.radius >= circle1.center.y - circle1.radius))
	{
		// 上下左右の当たり判定で別の戻り値を返す
		return SqureCollision(circle1, circle2, testObj, testObj2);
	}
	else
	{
		p_center = circle1.center;
	}
	return 0;
}

void Game::CombineObjects(int HitNum, BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj2)
{
	BOUNDING_CIRCLE Combine = circle1;// 円の座標を記録する
	DirectX::XMFLOAT3 rotation = testObj->m_objSprite->m_rotation;
	DirectX::XMFLOAT3 rotation2 = testObj2->m_objSprite->m_rotation;


	switch (HitNum)
	{
	case 1:
		// 左
		// 操作しているオブジェクトの横の座標を計算する
		Combine.center.x = circle1.center.x + circle1.radius + circle2.radius;
		// ぶつかったオブジェクトを操作しているオブジェクトの真横に移動させる
		testObj2->SetBoundingCircle(Combine);
		// 操作しているオブジェクトと同じように移動する
		testObj2->isPlayer = true;
		break;
	case 2:
		// 下
		// 操作しているオブジェクトの横の座標を計算する
		Combine.center.y = circle1.center.y + circle1.radius + circle2.radius;
		// ぶつかったオブジェクトを操作しているオブジェクトの真横に移動させる
		testObj2->SetBoundingCircle(Combine);
		// 操作しているオブジェクトと同じように移動する
		testObj2->isPlayer = true;
		break;
	case 3:
		// 上
		// 操作しているオブジェクトの横の座標を計算する
		Combine.center.y = circle1.center.y - circle1.radius - circle2.radius;
		// ぶつかったオブジェクトを操作しているオブジェクトの真横に移動させる
		testObj2->SetBoundingCircle(Combine);
		// 操作しているオブジェクトと同じように移動する
		testObj2->isPlayer = true;
		break;
	case 4:
		// 右
		// 操作しているオブジェクトの横の座標を計算する
		Combine.center.x = circle1.center.x - circle1.radius - circle2.radius;
		// ぶつかったオブジェクトを操作しているオブジェクトの真横に移動させる
		testObj2->SetBoundingCircle(Combine);
		// 操作しているオブジェクトと同じように移動する
		testObj2->isPlayer = true;
		break;

	default:
		// 当たっていない
		break;
	}
}

void Game::CombineTriangleObjects(int HitNum, BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj, TestObject* testObj2)
{
	std::vector<Vector2> Combineobj = testObj2->vertices;// 円の座標を記録する
	BOUNDING_CIRCLE Combine2 = circle2;// 円の座標を記録する
	DirectX::XMFLOAT3 rotation = testObj->m_objSprite->m_rotation;
	DirectX::XMFLOAT3 rotation2 = testObj2->m_objSprite->m_rotation;
	// 三角形の頂点座標とテスト対象の点を設定
	switch (HitNum)
	{
		//ーーー三角形のオブジェクトの合体ーーー

	case 5:
		// 左
		// 操作しているオブジェクトの横の座標を計算する
		// 図形が移動していた場合初期値にする
		testObj2->m_objSprite->InitPos(0, 0, 0.1f);
		testObj2->vertices = SetTriangle(testObj2->GetBoundingCircle(), testObj2);
		// 図形の角度が変わっていた場合初期値にする
		testObj2->rotation = 0;
		// 図形の移動をした後に図形の回転をする
		Combineobj = testObj2->vertices;
		Combineobj = InitialPolygonSATvertices(testObj2->GetBoundingCircle(), Combineobj, M_PI / 6.0f - testObj2->rotation);
		circle2.center.x = -Combineobj[1].x / 1.6 + circle1.center.x;
		circle2.center.y = -Combineobj[2].y / 2.9 + circle1.center.y;
		InitialPolygonSAT(circle2, testObj2, -M_PI / 6.0f - testObj2->rotation);//32
		// ぶつかったオブジェクトを操作しているオブジェクトの真横に移動させる
		testObj2->m_objSprite->InitPos(circle2.center.x, circle2.center.y, 0.1f);
		rotation2.z = -60 + rotation.z;
		testObj2->SetRotation(rotation2);
		// 操作しているオブジェクトと同じように移動する
		testObj2->isPlayer = true;
		break;
	case 6:
		// 右
		// 操作しているオブジェクトの横の座標を計算する
		testObj2->m_objSprite->InitPos(0, 0, 0.1f);
		testObj2->vertices = SetTriangle(testObj2->GetBoundingCircle(), testObj2);
		testObj2->rotation = 0;
		Combineobj = testObj2->vertices;
		Combineobj = InitialPolygonSATvertices(testObj2->GetBoundingCircle(), Combineobj, M_PI / 6.0f - testObj2->rotation);
		circle2.center.x = Combineobj[1].x / 1.6 + circle1.center.x;
		circle2.center.y = -Combineobj[2].y / 2.9 + circle1.center.y;
		InitialPolygonSAT(circle2, testObj2, M_PI / 6.0f - testObj2->rotation);
		// ぶつかったオブジェクトを操作しているオブジェクトの真横に移動させる
		testObj2->m_objSprite->InitPos(circle2.center.x, circle2.center.y, 0.1f);
		rotation2.z = 60 + rotation.z;
		testObj2->SetRotation(rotation2);
		// 操作しているオブジェクトと同じように移動する
		testObj2->isPlayer = true;
		break;
	case 7:
		// 下
		// 操作しているオブジェクトの横の座標を計算する
		testObj2->m_objSprite->InitPos(0, 0, 0.1f);
		testObj2->vertices = SetTriangle(testObj2->GetBoundingCircle(), testObj2);
		testObj2->rotation = 0;
		Combineobj = testObj2->vertices;
		Combineobj = InitialPolygonSATvertices(testObj2->GetBoundingCircle(), Combineobj, M_PI / 2.0f - testObj2->rotation);
		circle2.center.x = circle1.center.x;
		circle2.center.y = -Combineobj[2].y * 2.15 + circle1.center.y;
		InitialPolygonSAT(circle2, testObj2, M_PI / 2.0f - testObj2->rotation);
		// ぶつかったオブジェクトを操作しているオブジェクトの真横に移動させる
		testObj2->m_objSprite->InitPos(circle2.center.x, circle2.center.y, 0.1f);
		rotation2.z = 180 + rotation.z;
		testObj2->SetRotation(rotation2);
		// 操作しているオブジェクトと同じように移動する
		testObj2->isPlayer = true;
		break;

		//	// ーーー四角と三角ーーー

	case 8:
		// 左
		// 操作しているオブジェクトの横の座標を計算する
		// 図形が移動していた場合初期値にする
		testObj2->m_objSprite->InitPos(0, 0, 0.1f);
		testObj2->vertices = SetSqureWithTriangle(testObj2->GetBoundingCircle(), testObj2, SQUREWIDTH);
		// 図形の角度が変わっていた場合初期値にする
		testObj2->rotation = 0;
		// 図形の移動をした後に図形の回転をする
		Combineobj = testObj2->vertices;
		Combineobj = InitialPolygonSATvertices(testObj2->GetBoundingCircle(), Combineobj, M_PI / 12.0f - testObj2->rotation);
		circle2.center.x = -Combineobj[1].x * 0.98 + circle1.center.x;
		circle2.center.y = -Combineobj[2].y / 2.5 + circle1.center.y;
		InitialPolygonSAT(circle2, testObj2, -M_PI / 12.0f - testObj2->rotation);//32
		// ぶつかったオブジェクトを操作しているオブジェクトの真横に移動させる
		testObj2->m_objSprite->InitPos(circle2.center.x, circle2.center.y, 0.1f);
		rotation2.z = -30 + rotation.z;
		testObj2->SetRotation(rotation2);
		// 操作しているオブジェクトと同じように移動する
		testObj2->isPlayer = true;
	case 9:
		//// 右
		//// 操作しているオブジェクトの横の座標を計算する
		//float X1, Y2;
		//deaseX = 0.05 + 0.005 * rotation.z, deaseY = -0.15 - 0.03 * rotation.z;
		//X1 = (triangle.B.x + triangle.C.x) / 2;
		//Y2 = (triangle.B.y + triangle.C.y) / 2;
		//Combine.center.x = X1 + (X1 - triangle.A.x) + deaseX;//+ (X1 - triangle.A.x)+0.3
		//Combine.center.y = Y2 + (Y2 - triangle.A.y) + deaseY;// (Y2 - triangle.A.y)-1.9
		//// ぶつかったオブジェクトを操作しているオブジェクトの真横に移動させる
		//testObj2->m_objSprite->InitPos(Combine.center.x, Combine.center.y, 0.1f);
		//rotation2.z = 30 - rotation.z;
		//testObj2->SetRotation(rotation2);
		// 操作しているオブジェクトと同じように移動する
		//testObj2->isPlayer = true;
		break;
	case 10:
		//// 下
		//// 操作しているオブジェクトの横の座標を計算する
		//Combine.center.x = circle1.center.x;
		//Combine.center.y = circle1.center.y - circle1.radius - circle1.radius / 2 - testObj2->Scale_countX;
		//// ぶつかったオブジェクトを操作しているオブジェクトの真横に移動させる
		//testObj2->m_objSprite->InitPos(Combine.center.x, Combine.center.y, 0.1f);
		////rotation.z = 60;
		//testObj2->SetRotation(rotation2);
		//// 操作しているオブジェクトと同じように移動する
		//testObj2->isPlayer = true;
		break;
	case 11:
		break;
	}
}

int Game::SideCollision(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2)
{
	if (circle1.center.x + circle1.radius < circle2.center.x)// 左
	{
		return 1;
	}
	else if (circle1.center.x - circle1.radius > circle2.center.x)// 右
	{
		return 4;
	}
	else if (circle1.center.y < circle2.center.y)// 下
	{
		return 2;
	}
	else if (circle1.center.y > circle2.center.y)// 上
	{
		return 3;
	}
}

int Game::SqureCollision(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj, TestObject* testObj2)
{
	SQUREBOX squre1, squre2; // 四角形の四辺を入れる変数を取得する

	// 四角形の四辺を取得
	squre1 = Squre(circle1, testObj2);//(!(p_center.x < circle1.center.x || p_center.x > circle1.center.x)&& !(p_center.y > circle1.center.y || p_center.y < circle1.center.y))
	squre2 = Squre(circle2, testObj);// circle1.center.y - circle1.radius < circle2.center.y + circle2.radius&& circle1.center.y + circle1.radius > circle2.center.y - circle2.radius

	// 四角形が上下のどちらかからぶつかった時に左右の当たり判定が機能しないようにするための処理
	if (p_center.y - circle1.radius < circle2.center.y + circle2.radius
		&& p_center.y + circle1.radius > circle2.center.y - circle2.radius)
	{
		// 左右
		// 四角形に当たる直前に右方向に入力されているか
		if (circle1.center.x < circle2.center.x && p_center.x < circle1.center.x)
		{
			// 四角形の左側に円が触れた場合の当たり判定
			if (CheckSqureHit(squre1.Left, squre2.Right))// 左
			{
				return 1;
			}
		}
		// 四角形に当たる直前に左方向に入力されているか
		else if (circle1.center.x > circle2.center.x && p_center.x > circle1.center.x)
		{
			// 四角形の右側に円が触れた場合の当たり判定
			if (CheckSqureHit(squre1.Right, squre2.Left))// 右
			{
				return 4;
			}
		}
	}

	// 上下
	// 四角形に当たる直前に下方向に入力されているか
	if (circle1.center.y > circle2.center.y && p_center.y > circle1.center.y)
	{
		// 四角形の上側に円が触れた場合の当たり判定
		if (CheckSqureHit(squre1.Top, squre2.Bottom))// 上
		{
			return 3;
		}
	}
	// 四角形に当たる直前に上方向に入力されているか
	else if (circle1.center.y < circle2.center.y && p_center.y < circle1.center.y)
	{
		// 四角形の下側に円が触れた場合の当たり判定
		if (CheckSqureHit(squre1.Bottom, squre2.Top))// 下
		{
			return 2;
		}
	}

	return 0;
}

bool Game::CheckSqureHit(const BOX& t_box, const BOX& t_box2)
{
	// 四角形の左右どちらかの辺が重なっている
	if ((t_box.fRight > t_box2.fLeft) ||
		(t_box.fLeft < t_box2.fRight))
	{
		// 四角形の上下どちらかの辺が重なっている
		if ((t_box.fBottom > t_box2.fTop) ||
			(t_box.fTop < t_box2.fBottom))
		{
			return true;
		}
	}

	return false;
}

SQUREBOX Game::Squre(BOUNDING_CIRCLE circle2, TestObject* testObj)
{
	SQUREBOX squre; // 四角形の四辺を入れる変数を取得する

	// 四角形の左右に触れた場合の四辺の座標
	float X_posx1 = 1.4 + circle2.center.x + testObj->Scale_countX;
	float X_posx2 = -1.4 + circle2.center.x - testObj->Scale_countX;
	float X_posy1 = 1 + circle2.center.y + testObj->Scale_countY;
	float X_posy2 = -1 + circle2.center.y - testObj->Scale_countY;

	// 四角形の上下に触れた場合の四辺の座標
	float Y_posx1 = 1.4 + circle2.center.y + testObj->Scale_countX;
	float Y_posx2 = -1.4 + circle2.center.y - testObj->Scale_countX;
	float Y_posy1 = 1 + circle2.center.x + testObj->Scale_countX;
	float Y_posy2 = -1 + circle2.center.x - testObj->Scale_countX;

	// 四角形の辺にそれぞれ四つの座標をいれる
	squre.Left = { X_posx2, X_posy2, X_posx2, X_posy1 };   // 左
	squre.Right = { X_posx1, X_posy2, X_posx1, X_posy1 };  // 右
	squre.Bottom = { Y_posy2, Y_posx2, Y_posy1, Y_posx2 }; // 下
	squre.Top = { Y_posy2, Y_posx1, Y_posy1, Y_posx1 };    // 上

	// 四角形の四辺を返す
	return squre;
}

std::vector<Vector2> Game::SetTriangle(BOUNDING_CIRCLE circle1, TestObject* testObj2)
{
	Triangle triangle;
	triangle.A = { 0                                , 0.9f + testObj2->Scale_countY };
	triangle.B = { 1.1f + testObj2->Scale_countX, -0.9f - testObj2->Scale_countY };
	triangle.C = { -1.1f - testObj2->Scale_countX, -0.9f - testObj2->Scale_countY };


	// 1つ目の凸多角形の頂点座標を定義
	std::vector<Vector2> vertices = {
		Vector2(triangle.A.x, triangle.A.y),
		Vector2(triangle.B.x, triangle.B.y),
		Vector2(triangle.C.x, triangle.C.y),
	};

	return vertices;
}

std::vector<Vector2> Game::SetSqureWithTriangle(BOUNDING_CIRCLE circle1, TestObject* testObj2, float width)
{
	SQURE squre;
	// 四角の下の三角
	squre.A = { width + testObj2->Scale_countX,
				width + testObj2->Scale_countY };
	squre.B = { width + testObj2->Scale_countX,
				-width + -testObj2->Scale_countY };
	squre.C = { -width - testObj2->Scale_countX,
				-width + -testObj2->Scale_countY };
	squre.D = { -width - testObj2->Scale_countX,
				 width + testObj2->Scale_countY };

	// 1つ目の凸多角形の頂点座標を定義
	std::vector<Vector2> vertices = {
		Vector2(squre.A.x, squre.A.y),
		Vector2(squre.B.x, squre.B.y),
		Vector2(squre.C.x, squre.C.y),
		Vector2(squre.D.x, squre.D.y),
	};

	return vertices;
}

SQURE Game::SetCircleWithTriangle(BOUNDING_CIRCLE circle1, TestObject* testObj2, float width)
{
	SQURE circle;
	// 四角の下の三角
	circle.A = { circle1.center.x , width + circle1.center.y + testObj2->Scale_countY };
	circle.B = { -width + circle1.center.x - testObj2->Scale_countX,circle1.center.y };
	circle.C = { circle1.center.x , -width + circle1.center.y - testObj2->Scale_countY };
	circle.D = { width + circle1.center.x + testObj2->Scale_countX,circle1.center.y };
	return circle;
}

bool Game::isPointInTriangle(Point A, Point B, Point C, Point P)
{
	// バリア座標の計算
	float denominator = (B.y - C.y) * (A.x - C.x) + (C.x - B.x) * (A.y - C.y);
	float alpha = ((B.y - C.y) * (P.x - C.x) + (C.x - B.x) * (P.y - C.y)) / denominator;
	float beta = ((C.y - A.y) * (P.x - C.x) + (A.x - C.x) * (P.y - C.y)) / denominator;
	float gamma = 1.0 - alpha - beta;

	// 座標内包性の確認
	return alpha >= 0.0 && alpha <= 1.0 && beta >= 0.0 && beta <= 1.0 && gamma >= 0.0 && gamma <= 1.0;
}

int Game::CheckTriangleHit(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj, TestObject* testObj2)
{
	// 三角形の頂点座標とテスト対象の点を設定
	// 操作している三角形
	testObj->vertices = SetTriangle(circle1, testObj);
	// 操作していない三角形
	testObj2->vertices = SetTriangle(circle2, testObj2);

	// 三角同士が触れている時
	if (TriangleHit(testObj, testObj2))
	{
		if (testObj2->vertices[0].y > circle1.center.y)
		{
			// 右上にあるとき
			if (testObj->vertices[0].x < circle2.center.x)
			{
				// 右
				return 6;
			}
			// 左上にあるとき
			else if (testObj->vertices[0].x > circle2.center.x)
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

bool Game::TriangleHit(TestObject* testObj, TestObject* testObj2)
{
	PolygonSAT Triangle1(testObj->vertices, 0);
	PolygonSAT Triangle2(testObj2->vertices, testObj2->rotation);

	testObj2->vertices = Triangle2.GetRotatedVertices();

	BOUNDING_CIRCLE circle1 = testObj2->GetBoundingCircle();
	BOUNDING_CIRCLE circle2 = testObj2->GetBoundingCircle();
	// 四角
	for (auto& vertex : testObj2->vertices) {
		vertex.x += circle1.center.x;
		vertex.y += circle1.center.y;
	}

	Triangle2.vertices = testObj2->vertices;

	bool collisionResult = Collide(Triangle1, Triangle2);

	// 結果を表示
	if (collisionResult)
	{
		return true;
	}
	return false;
}

void Game::InitialPolygonSAT(BOUNDING_CIRCLE circle1, TestObject* testObj, float rotation)
{
	//BOUNDING_CIRCLE circle4 = testObj->GetBoundingCircle();// 操作していないオブジェクト 
	//testObj->vertices = SetTriangle(circle4, testObj);
	PolygonSAT Triangle3(testObj->vertices, rotation);
	testObj->vertices = Triangle3.GetRotatedVertices();
	for (auto& vertex : testObj->vertices) {
		vertex.x = vertex.x + circle1.center.x;
		vertex.y = vertex.y + circle1.center.y;
	}
}

std::vector<Vector2> Game::InitialPolygonSATvertices(BOUNDING_CIRCLE circle1, std::vector<Vector2> vertices, float rotation)
{
	PolygonSAT Triangle3(vertices, rotation);
	vertices = Triangle3.GetRotatedVertices();
	for (auto& vertex : vertices) {
		vertex.x = vertex.x + circle1.center.x;
		vertex.y = vertex.y + circle1.center.y;
	}

	return vertices;
}

int Game::CheckTriangleAndSqureHit(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj, TestObject* testObj2)
{
	// 三角形の頂点座標とテスト対象の点を設定
	// 操作している三角形
	testObj->vertices = SetTriangle(circle1, testObj);
	// 操作していない四角形
	testObj2->vertices = SetSqureWithTriangle(circle2, testObj2, SQUREWIDTH);

	// 三角同士が触れている時
	if (TriangleHit(testObj, testObj2))
	{
		if (testObj2->vertices[0].y > circle1.center.y)
		{
			// 右上にあるとき
			if (testObj->vertices[0].x < circle2.center.x)
			{
				// 右
				return 9;
			}
			// 左上にあるとき
			else if (testObj->vertices[0].x > circle2.center.x)
			{
				// 左
				return 8;
			}
		}
		// 上にあるとき
		else
		{
			// 上
			return 10;
		}
	}

	return 0;
}

int Game::CheckTriangleAndCircleHit(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj, TestObject* testObj2)
{
	// 三角形の頂点座標とテスト対象の点を設定
	std::vector<Vector2> triangle;
	SQURE circle;
	std::vector<Vector2> squre;

	// 操作している三角形
	triangle = SetTriangle(circle1, testObj);
	squre = SetSqureWithTriangle(circle2, testObj2, TRIANGLEWIDTH);
	circle = SetCircleWithTriangle(circle2, testObj2, SQUREWIDTH);

	// 中心点
	Point squrecenter = { circle2.center.x ,circle2.center.y };

	////// 当たり判定を行う
	//if     (isPointInTriangle(squrecenter, circle.D, squre.C, triangle.A)
	//	||  isPointInTriangle(squrecenter, squre.C, circle.C, triangle.A)
	//	|| (isPointInTriangle(triangle.A, triangle.B, triangle.C, squre.C)))
	//{
	//	// 右
	//	return 8;
	//}
	//else if (isPointInTriangle(squrecenter, circle.B, squre.A, triangle.B)
	//	  || isPointInTriangle(squrecenter, squre.A, circle.C, triangle.B)
	//	  || isPointInTriangle(triangle.A, triangle.B, triangle.C, squre.A))
	//{
	//	// 左
	//	return 9;
	//}
	//// 下
	//else if (isPointInTriangle(circle.B, squre.A, squrecenter, triangle.C)
	//	  || isPointInTriangle(squre.A, circle.C, squrecenter, triangle.C))
	//{
	//	// 左
	//	return 9;
	//}
	//else if (isPointInTriangle(circle.D, squre.C, squrecenter, triangle.C)
	//	  || isPointInTriangle(squre.C, circle.C, squrecenter, triangle.C))
	//{
	//	// 右
	//	return 8;
	//}
	//else if ((isPointInTriangle(circle.B, squre.D, squrecenter, triangle.B)
	//	   || isPointInTriangle(squre.D, circle.A, squrecenter, triangle.B)
	//	   || isPointInTriangle(circle.A, squrecenter, squre.B, triangle.A)
	//	   || isPointInTriangle(squre.B, squrecenter, circle.D, triangle.A)))
	//{
	//	// 上
	//	return 10;
	//}

	return 0;
}

bool Game::TriangleAndCircleHit(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj, TestObject* testObj2)
{
	return 0;
}

bool Game::TriangleAndSqureHit(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj, TestObject* testObj2)
{
	return 0;
}
