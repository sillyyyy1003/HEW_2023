#include "Game.h"
#include "Direct3D/Direct3D.h"
#include "Assets.h"
#include "ObjectAnimation.h"
#include "TrackCamera.h"
#include "KBInput.h"

extern Assets* g_Assets;
extern KBInput* g_KbInput;


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
	testObj->SetObjTex(g_Assets->square, 200, 200, 1, 1);
	testObj->m_objSprite->m_anime = new ObjectAnimation(1, 1);
	testObj->m_objSprite->m_anime->SetAnimeSpeed(0.0f);
	testObj->m_objSprite->m_anime->SetAnimePattern(0);
	testObj->m_objSprite->InitPos(-4, -1.16, 0.2f);
	testObj->isPlayer = true;// キーボードで操作可能

	// オブジェクト2
	testObj2 = new TestObject();
	//オブジェクトの初期設定
	//testObj2->SetObjTex(g_Assets->testShadow, 200, 200, 1, 1);
	testObj2->SetObjTex(g_Assets->square, 200, 200, 1, 1);//square
	testObj2->m_objSprite->m_anime = new ObjectAnimation(1, 1);
	testObj2->m_objSprite->m_anime->SetAnimeSpeed(0.0f);
	testObj2->m_objSprite->m_anime->SetAnimePattern(0);
	testObj2->m_objSprite->InitPos(5, 0, 0.1f);

	// オブジェクト3
	testObj3 = new TestObject();
	//オブジェクトの初期設定
	//testObj2->SetObjTex(g_Assets->testShadow, 200, 200, 1, 1);
	testObj3->SetObjTex(g_Assets->testObj, 200, 200, 1, 1);//square
	testObj3->m_objSprite->m_anime = new ObjectAnimation(1, 1);
	testObj3->m_objSprite->m_anime->SetAnimeSpeed(0.0f);
	testObj3->m_objSprite->m_anime->SetAnimePattern(0);
	testObj3->m_objSprite->InitPos(2, 3, 0.1f);
	

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
	// 当たり判定処理
	TestCollision();

	testBg->Update();
	testObj->Update();
	testObj2->Update();
	testObj3->Update();
	//testObject->Update();
}

void Game::StageUpdate(void)
{
}

void Game::ResultUpdate(void)
{

}

Game::~Game()
{
	//delete testObject;
	delete testObj;
	delete testObj2;
	delete testObj3;
	delete testBg;
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
	testBg->m_sprite->Draw();

	testObj->Draw();
	testObj2->Draw();
	testObj3->Draw();


	//testBg->m_sprite->Draw();
	//testObject->m_sprite->Draw();
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
	BOUNDING_CIRCLE Combine = circle1;// 円の座標を記録する

	// ここで当たり判定を切り替える
	//円同士
	//MoveObjects(CircleHit(circle1, circle2), Combine, circle1, circle2);

	if (!testObj3->isPlayer)// オブジェクト同士が触れたら当たり判定を消す
	{
		// 円と四角
		// SqureandCircle関数　引数１：円　２：四角 3:四角のテクスチャが入っている方を入れる
		// MoveObjects関数　引数１：オブジェクトがどこに当たったのかの戻り値　引数２：合体させる元のオブジェクトの座標
		// 　　　　　　     引数３,４,５：MoveObjects関数の引数と同じ
		CombineObjects(SqureandCircle(circle1, circle3, testObj3), Combine, circle1, circle3, testObj3);
	}


	if (!testObj2->isPlayer)// オブジェクト同士が触れたら当たり判定を消す
	{
		// 四角と四角
		CombineObjects(SqureHit(circle1, circle2), Combine, circle1, circle2, testObj2);
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

int Game::SqureHit(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2)
{
	// 四角形同士の当たり判定
	if ((circle1.center.x + circle1.radius >= circle2.center.x - circle2.radius) &&
		(circle2.center.x + circle2.radius >= circle1.center.x - circle1.radius) &&
		(circle1.center.y + circle1.radius >= circle2.center.y - circle2.radius) &&
		(circle2.center.y + circle2.radius >= circle1.center.y - circle1.radius))
	{
		// 上下左右の当たり判定で別の戻り値を返す
		return SideCollision(circle1, circle2);
	}
	return 0;
}

void Game::CombineObjects(int HitNum, BOUNDING_CIRCLE Combine, BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj)
{
	switch (HitNum)
	{
	case 1:
		// 左
		// 操作しているオブジェクトの横の座標を計算する
		Combine.center.x = circle1.center.x + circle1.radius + circle2.radius;
		// ぶつかったオブジェクトを操作しているオブジェクトの真横に移動させる
		testObj->SetBoundingCircle(Combine);
		// 操作しているオブジェクトと同じように移動する
		testObj->isPlayer = true;
		break;
	case 2:
		// 下
		// 操作しているオブジェクトの横の座標を計算する
		Combine.center.y = circle1.center.y + circle1.radius + circle2.radius;
		// ぶつかったオブジェクトを操作しているオブジェクトの真横に移動させる
		testObj->SetBoundingCircle(Combine);
		// 操作しているオブジェクトと同じように移動する
		testObj->isPlayer = true;
		break;
	case 3:
		// 上
		// 操作しているオブジェクトの横の座標を計算する
		Combine.center.y = circle1.center.y - circle1.radius - circle2.radius;
		// ぶつかったオブジェクトを操作しているオブジェクトの真横に移動させる
		testObj->SetBoundingCircle(Combine);
		// 操作しているオブジェクトと同じように移動する
		testObj->isPlayer = true;
		break;
	case 4:
		// 右
		// 操作しているオブジェクトの横の座標を計算する
		Combine.center.x = circle1.center.x - circle1.radius - circle2.radius;
		// ぶつかったオブジェクトを操作しているオブジェクトの真横に移動させる
		testObj->SetBoundingCircle(Combine);
		// 操作しているオブジェクトと同じように移動する
		testObj->isPlayer = true;
		break;
	default:
		// 当たっていない
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