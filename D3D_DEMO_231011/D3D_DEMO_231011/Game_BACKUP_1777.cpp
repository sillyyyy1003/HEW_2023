#include "Game.h"
#include "Direct3D/Direct3D.h"
#include "Assets.h"
#include "ObjectAnimation.h"
#include "StaticAnimation.h"
#include "TrackCamera.h"
#include "DebugManager.h"
#include "DInput.h"

#include "SAT.h"
#include <algorithm> // •K—v‚Èƒwƒbƒ_[ƒtƒ@ƒCƒ‹
#define SQUREWIDTH 1.2
#define TRIANGLEWIDTH 0.8
#define M_PI 3.14159265358979323846
#define M_PIX 0.1//1.5
#define M_PIY 0.0333333333// 0.5

extern Assets* g_Assets;
extern Camera* g_WorldCamera;
extern DebugManager* g_DebugManager;

<<<<<<< .merge_file_zvS5Zi

void Game::Init()
{
	//ã‚ªãƒ–ã‚¸ã‚§ã‚¯ãƒˆä½œæˆ
	testWall = new Object(g_Assets->testWallbg, 1280, 720, 1, 1);
	testGround = new Object(g_Assets->testGroundbg, 1280, 720, 1, 1);
	testWall->m_sprite->m_scale = { 1.0, 1.0, 1.0 };

	//ã‚ªãƒ–ã‚¸ã‚§ã‚¯ãƒˆã®åˆæœŸè¨­å®šãƒ»ãƒ†ã‚¯ã‚¹ãƒãƒ£ã®èª­ã¿è¾¼ã¿
	testChara = new Object(g_Assets->testChara01, 32, 32, 3, 4);
	
	testTree = new GameObject();
	testTree->CreateObject(g_Assets->testObj, 300, 300, 1, 1);
	testTree->CreateShadow(g_Assets->testShadow, 300, 300, 1, 1);

	uitest = new CanvasUI();
	uitest->CreateModel(g_Assets->testWallbg, 128, 72, 1, 1);
=======
Game::Game()
{
	////ƒIƒuƒWƒFƒNƒg‰Šú‰»
	//testObject = new Object(g_Assets->testchar01, 96, 96, 3, 4);
	////ƒAƒjƒ[ƒVƒ‡ƒ“ƒNƒ‰ƒX‰Šú‰»->‚Ç‚ÌƒAƒjƒ[ƒVƒ‡ƒ“‚É‚·‚é
	//testObject->m_sprite->m_anime = new ObjectAnimation(3, 4);
	////ƒAƒjƒ[ƒVƒ‡ƒ“‘¬“x‚ğİ’è
	//testObject->m_sprite->m_anime->SetAnimeSpeed(0.1f);
	////ƒAƒjƒ[ƒVƒ‡ƒ“ƒpƒ^[ƒ“‚ğİ’è
	//testObject->m_sprite->m_anime->SetAnimePattern(0);

	// ƒIƒuƒWƒFƒNƒg1
	testObj = new TestObject();
	//ƒIƒuƒWƒFƒNƒg‚Ì‰Šúİ’è
	testObj->SetObjTex(g_Assets->triangle, 200, 200, 1, 1);
	testObj->m_objSprite->m_anime = new ObjectAnimation(1, 1);
	testObj->m_objSprite->m_anime->SetAnimeSpeed(0.0f);
	testObj->m_objSprite->m_anime->SetAnimePattern(0);
	testObj->m_objSprite->InitPos(-4, -1.16, 0.2f);
	DirectX::XMFLOAT3 rotation = testObj->m_objSprite->m_rotation;
	testObj->isPlayer = true;// ƒL[ƒ{[ƒh‚Å‘€ì‰Â”\
	BOUNDING_CIRCLE circle1 = testObj->GetBoundingCircle();// ‘€ì‚µ‚Ä‚¢‚È‚¢ƒIƒuƒWƒFƒNƒg 
	testObj->vertices = SetTriangle(circle1, testObj);

	// ƒIƒuƒWƒFƒNƒg2
	testObj2 = new TestObject();
	//ƒIƒuƒWƒFƒNƒg‚Ì‰Šúİ’è
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

	// ƒIƒuƒWƒFƒNƒg3
	testObj3 = new TestObject();
	//ƒIƒuƒWƒFƒNƒg‚Ì‰Šúİ’è
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

>>>>>>> .merge_file_tnJJ8S

	uitest->m_pos.z = 0.2f;
	
	//å½±ã®åˆæœŸè¨­å®š


<<<<<<< .merge_file_zvS5Zi

	//ã‚¢ãƒ‹ãƒ¡ãƒ¼ã‚·ãƒ§ãƒ³ã®è¨­å®š
	testWall->m_sprite->m_anime = new StaticAnimation(1, 1);
	testGround->m_sprite->m_anime = new ObjectAnimation(1, 1);
	testChara->m_sprite->m_anime = new ObjectAnimation(3, 4);
	testChara->m_sprite->m_anime->SetAnimeSpeed(0.2f);

	testTree->m_obj->m_anime = new StaticAnimation(1, 1);
	testTree->m_shadow->m_obj->m_anime = new StaticAnimation(1, 1);



	//åˆæœŸä½ç½®è¨­å®š
	testWall->m_sprite->m_pos = { 0.0f, 1.5f, 2.0f };
	testGround->m_sprite->m_pos = { 0.0f, 1.5f, 2.0f };

	testGround->m_sprite->m_rotation.x = 90;
	testGround->m_sprite->m_pos.y = -360 / SCREEN_PARA + 1.5f;

	testChara->m_sprite->m_pos.y = (-360 + 96) / SCREEN_PARA + 1.5f;
	testChara->m_sprite->m_pos.z = -0.5f;
	testChara->m_sprite->m_scale = { 3.0f,3.0f,3.0f };

	//å½±ã®ä½ç½®è¨­å®š
	testTree->m_shadow->m_obj->m_pos.z = 1.99f;

	//dynamic_cast<TrackCamera*>(g_WorldCamera)->SetTarget(testWall);

	
=======
	//ƒIƒuƒWƒFƒNƒg‰Šú‰»
	testBg = new Object(g_Assets->testbgbox, 1280, 720, 1, 1);
	testBg->m_sprite->m_pos.z = 0.9;//‘OŒã‚ÌˆÊ’uİ’è‚ğƒNƒ‰ƒX‰»‚Ås‚¤
	//ƒAƒjƒ[ƒVƒ‡ƒ“ƒNƒ‰ƒX‰Šú‰»->‚Ç‚ÌƒAƒjƒ[ƒVƒ‡ƒ“‚É‚·‚é
	testBg->m_sprite->m_anime = new ObjectAnimation(1, 1);
	//ƒAƒjƒ[ƒVƒ‡ƒ“‘¬“x‚ğİ’è
	testBg->m_sprite->m_anime->SetAnimeSpeed(0.0f);
	//ƒAƒjƒ[ƒVƒ‡ƒ“ƒpƒ^[ƒ“‚ğİ’è
	testBg->m_sprite->m_anime->SetAnimePattern(0);
>>>>>>> .merge_file_tnJJ8S
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
<<<<<<< .merge_file_zvS5Zi
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

	//èƒŒæ™¯
	testGround->Update();
	

	testTree->Update(testChara->m_sprite->m_pos);

	testChara->Update();

	uitest->Update();



	

=======
{
	// “–‚½‚è”»’èˆ—
	TestCollision();

	testBg->Update();
	testObj->Update();
	testObj2->Update();
	testObj3->Update();
	testObj4->Update();
	//testObject->Update();
>>>>>>> .merge_file_tnJJ8S
}

void Game::StageUpdate(void)
{
}


void Game::ResultUpdate(void)
{

}

Game::~Game()
{
<<<<<<< .merge_file_zvS5Zi
	delete testChara;
	delete testWall;
	delete testGround;

	delete testTree;
	delete uitest;
}

Game* Game::Get()
{
	static Game instance;
	return &instance;
=======
	//delete testObject;
	delete testObj;
	delete testObj2;
	delete testObj3;
	delete testObj4;
	delete testBg;
>>>>>>> .merge_file_tnJJ8S
}

void Game::GameDraw()
{

	D3D_ClearScreen();

<<<<<<< .merge_file_zvS5Zi
	//============ ã“ã“ã‹ã‚‰æç”»å‡¦ç† ============//
	
	
=======
	//============ ‚±‚±‚©‚ç•`‰æˆ— ============//


>>>>>>> .merge_file_tnJJ8S
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

<<<<<<< .merge_file_zvS5Zi
	//============ ã“ã“ã¾ã§æç”»å‡¦ç† ============//
	 
	//ãƒ€ãƒ–ãƒ«ãƒãƒƒãƒ•ã‚¡ã®åˆ‡ã‚Šæ›¿ãˆã‚’è¡Œã„ç”»é¢ã‚’æ›´æ–°ã™ã‚‹
=======
	//============ ‚±‚±‚Ü‚Å•`‰æˆ— ============//

	//ƒ_ƒuƒ‹ƒoƒbƒtƒ@‚ÌØ‚è‘Ö‚¦‚ğs‚¢‰æ–Ê‚ğXV‚·‚é
>>>>>>> .merge_file_tnJJ8S
	GetD3D_DATA()->SwapChain->Present(0, 0);
}

void Game::TitleDraw(void)
{
	//testWall->Draw();

	//testGround->Draw();

<<<<<<< .merge_file_zvS5Zi
	testTree->Draw();

	testChara->Draw();
=======
	testObj->Draw();
	testObj2->Draw();
	testObj3->Draw();
	testObj4->Draw();
>>>>>>> .merge_file_tnJJ8S


	//ãƒ‡ãƒãƒƒã‚°è¡¨ç¤º 
	//40->ä¸€æ–‡å­—ã®å¹…/é«˜ã•ã®äºŒå€
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

<<<<<<< .merge_file_zvS5Zi
=======
void Game::TestCollision()
{
	BOUNDING_CIRCLE circle1 = testObj->GetBoundingCircle();// ‘€ì‚µ‚Ä‚¢‚éƒIƒuƒWƒFƒNƒg
	BOUNDING_CIRCLE circle2 = testObj2->GetBoundingCircle();// ‘€ì‚µ‚Ä‚¢‚È‚¢ƒIƒuƒWƒFƒNƒg 
	BOUNDING_CIRCLE circle3 = testObj3->GetBoundingCircle();// ‘€ì‚µ‚Ä‚¢‚È‚¢ƒIƒuƒWƒFƒNƒg 
	BOUNDING_CIRCLE circle4 = testObj4->GetBoundingCircle();// ‘€ì‚µ‚Ä‚¢‚È‚¢ƒIƒuƒWƒFƒNƒg 
	//Triangle triangle, triangle2;
	//std::vector<Vector2> verticesA,verticesB;

	// ‚±‚±‚Å“–‚½‚è”»’è‚ğØ‚è‘Ö‚¦‚é
	//‰~“¯m
	//MoveObjects(CircleHit(circle1, circle2), Combine, circle1, circle2);

	if (!testObj3->isPlayer)// ƒIƒuƒWƒFƒNƒg“¯m‚ªG‚ê‚½‚ç“–‚½‚è”»’è‚ğÁ‚·
	{
		// ‰~‚ÆlŠp 1lŠp@‚QlŠp@‚R‰~
		// SqureandCircleŠÖ”@ˆø”‚PF‰~@‚QFlŠp 3:lŠp‚ÌƒeƒNƒXƒ`ƒƒ‚ª“ü‚Á‚Ä‚¢‚é•û‚ğ“ü‚ê‚é
		// MoveObjectsŠÖ”@ˆø”‚PFƒIƒuƒWƒFƒNƒg‚ª‚Ç‚±‚É“–‚½‚Á‚½‚Ì‚©‚Ì–ß‚è’l@ˆø”‚QF‡‘Ì‚³‚¹‚éŒ³‚ÌƒIƒuƒWƒFƒNƒg‚ÌÀ•W
		// @@@@@@     ˆø”‚R,‚S,‚TFMoveObjectsŠÖ”‚Ìˆø”‚Æ“¯‚¶
		//CombineObjects(SqureandCircle(circle1, circle3, testObj3),circle1, circle3, testObj3);

		//CombineObjects(SqureandCircle(circle2, circle3, testObj3), circle2, circle3, testObj3);

		// OŠp‚Æ‰~
		//CombineTriangleObjects(CheckTriangleAndCircleHit(circle1, circle3, testObj, testObj3), circle1, circle3, testObj,testObj3);
	}

	if (!testObj2->isPlayer)// ƒIƒuƒWƒFƒNƒg“¯m‚ªG‚ê‚½‚ç“–‚½‚è”»’è‚ğÁ‚·
	{
		// lŠp‚ÆlŠp ˆø”‚PF‘€ì‚µ‚Ä‚¢‚éƒIƒuƒWƒFƒNƒg@ˆø”‚QF‘€ì‚µ‚Ä‚¢‚È‚¢ƒIƒuƒWƒFƒNƒg
		//CombineObjects(SqureHit(circle1, circle2, testObj, testObj2),circle1, circle2, testObj2);

		//CombineObjects(SqureandCircle(circle3, circle2, testObj2), circle3, circle2, testObj2);

		// OŠp‚ÆlŠp@‚POŠp@‚SOŠp@‚QlŠp
		CombineTriangleObjects(CheckTriangleAndSqureHit(circle1, circle2, testObj, testObj2), circle1, circle2, testObj, testObj2);

		//CombineTriangleObjects(CheckTriangleAndSqureHit(circle4, circle2, testObj4, testObj2), circle4, circle2, testObj4, testObj2);
	}

	if (!testObj4->isPlayer)
	{
		// OŠp“¯m
		//CombineObjects(CheckTriangleHit(circle1, circle4, testObj, testObj4), circle1, circle4, testObj, testObj4);

		//CombineObjects(CheckTriangleAndSqureHit(circle2, circle4, testObj2, testObj4), circle2, circle4, testObj4);

		CombineTriangleObjects(CheckTriangleHit(circle1, circle4, testObj, testObj4), circle1, circle4, testObj, testObj4);

	}

}

int Game::CircleHit(BOUNDING_CIRCLE bc1, BOUNDING_CIRCLE bc2)
{
	//bc1 ‰~@bc2 ‰~
	float teihen = bc2.center.x - bc1.center.x;// ’ê•Ó‚Ì’·‚³
	float takasa = bc2.center.y - bc1.center.y;// ‚‚³
	float r2 = bc1.radius + bc2.radius; // ‰~1‚Ì”¼Œa{‰~2‚Ì”¼Œa

	if (teihen * teihen + takasa * takasa <= r2 * r2)
	{
		// ã‰º¶‰E‚Ì“–‚½‚è”»’è‚Å•Ê‚Ì–ß‚è’l‚ğ•Ô‚·
		return SideCollision(bc1, bc2);
	}

	return 0;
}

bool Game::CheckHit(const BOX& t_box, const BOUNDING_CIRCLE bc1)
{
	bool nResult = false;

	// lŠpŒ`‚Ìl•Ó‚É‘Î‚µ‚Ä‰~‚Ì”¼Œa•ª‚¾‚¯‘«‚µ‚½‚Æ‚«‰~‚ªd‚È‚Á‚Ä‚¢‚½‚ç
	if ((bc1.center.x > t_box.fLeft - bc1.radius) &&
		(bc1.center.x < t_box.fRight + bc1.radius) &&
		(bc1.center.y > t_box.fTop - bc1.radius) &&
		(bc1.center.y < t_box.fBottom + bc1.radius))
	{
		// “–‚½‚Á‚Ä‚¢‚é
		nResult = true;
	}

	return nResult;
}

int Game::SqureandCircle(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj)
{
	BOX squre; // lŠpŒ`‚Ìl•Ó‚ğ“ü‚ê‚é•Ï”‚ğæ“¾‚·‚é

	// lŠpŒ`‚Ì¶‰E‚ÉG‚ê‚½ê‡‚Ìl•Ó‚ÌÀ•W
	float X_posx1 = 1.4 + circle2.center.x + testObj->Scale_countX;
	float X_posx2 = -1.4 + circle2.center.x - testObj->Scale_countX;
	float X_posy1 = 1 + circle2.center.y + testObj->Scale_countY;
	float X_posy2 = -1 + circle2.center.y - testObj->Scale_countY;

	// lŠpŒ`‚Ìã‰º‚ÉG‚ê‚½ê‡‚Ìl•Ó‚ÌÀ•W
	float Y_posx1 = 1.4 + circle2.center.y + testObj->Scale_countX;
	float Y_posx2 = -1.4 + circle2.center.y - testObj->Scale_countX;
	float Y_posy1 = 1 + circle2.center.x + testObj->Scale_countX;
	float Y_posy2 = -1 + circle2.center.x - testObj->Scale_countX;
	//testObj2->m_objSprite->InitBox(-1, -1.4, 1, -1.4);

	// ¶‰E
	// lŠpŒ`‚Ì¶‘¤‚É‰~‚ªG‚ê‚½ê‡‚Ì“–‚½‚è”»’è
	if (CheckHit(squre = { X_posx2, X_posy2, X_posx2, X_posy1 }, circle1))// ¶
	{
		return 1;
	}
	// lŠpŒ`‚Ì‰E‘¤‚É‰~‚ªG‚ê‚½ê‡‚Ì“–‚½‚è”»’è
	else if (CheckHit(squre = { X_posx1, X_posy2, X_posx1, X_posy1 }, circle1))// ‰E
	{
		return 4;
	}
	// ã‰º
	// lŠpŒ`‚Ì‰º‘¤‚É‰~‚ªG‚ê‚½ê‡‚Ì“–‚½‚è”»’è
	else if (CheckHit(squre = { Y_posy2, Y_posx2, Y_posy1, Y_posx2 }, circle1))// ‰º
	{
		return 2;
	}
	// lŠpŒ`‚Ìã‘¤‚É‰~‚ªG‚ê‚½ê‡‚Ì“–‚½‚è”»’è
	else if (CheckHit(squre = { Y_posy2, Y_posx1, Y_posy1, Y_posx1 }, circle1))// ã
	{
		return 3;
	}

	return 0;
}

int Game::SqureHit(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj, TestObject* testObj2)
{
	// lŠpŒ`“¯m‚Ì“–‚½‚è”»’è
	if ((circle1.center.x + circle1.radius >= circle2.center.x - circle2.radius) &&
		(circle2.center.x + circle2.radius >= circle1.center.x - circle1.radius) &&
		(circle1.center.y + circle1.radius >= circle2.center.y - circle2.radius) &&
		(circle2.center.y + circle2.radius >= circle1.center.y - circle1.radius))
	{
		// ã‰º¶‰E‚Ì“–‚½‚è”»’è‚Å•Ê‚Ì–ß‚è’l‚ğ•Ô‚·
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
	BOUNDING_CIRCLE Combine = circle1;// ‰~‚ÌÀ•W‚ğ‹L˜^‚·‚é
	DirectX::XMFLOAT3 rotation = testObj->m_objSprite->m_rotation;
	DirectX::XMFLOAT3 rotation2 = testObj2->m_objSprite->m_rotation;


	switch (HitNum)
	{
	case 1:
		// ¶
		// ‘€ì‚µ‚Ä‚¢‚éƒIƒuƒWƒFƒNƒg‚Ì‰¡‚ÌÀ•W‚ğŒvZ‚·‚é
		Combine.center.x = circle1.center.x + circle1.radius + circle2.radius;
		// ‚Ô‚Â‚©‚Á‚½ƒIƒuƒWƒFƒNƒg‚ğ‘€ì‚µ‚Ä‚¢‚éƒIƒuƒWƒFƒNƒg‚Ì^‰¡‚ÉˆÚ“®‚³‚¹‚é
		testObj2->SetBoundingCircle(Combine);
		// ‘€ì‚µ‚Ä‚¢‚éƒIƒuƒWƒFƒNƒg‚Æ“¯‚¶‚æ‚¤‚ÉˆÚ“®‚·‚é
		testObj2->isPlayer = true;
		break;
	case 2:
		// ‰º
		// ‘€ì‚µ‚Ä‚¢‚éƒIƒuƒWƒFƒNƒg‚Ì‰¡‚ÌÀ•W‚ğŒvZ‚·‚é
		Combine.center.y = circle1.center.y + circle1.radius + circle2.radius;
		// ‚Ô‚Â‚©‚Á‚½ƒIƒuƒWƒFƒNƒg‚ğ‘€ì‚µ‚Ä‚¢‚éƒIƒuƒWƒFƒNƒg‚Ì^‰¡‚ÉˆÚ“®‚³‚¹‚é
		testObj2->SetBoundingCircle(Combine);
		// ‘€ì‚µ‚Ä‚¢‚éƒIƒuƒWƒFƒNƒg‚Æ“¯‚¶‚æ‚¤‚ÉˆÚ“®‚·‚é
		testObj2->isPlayer = true;
		break;
	case 3:
		// ã
		// ‘€ì‚µ‚Ä‚¢‚éƒIƒuƒWƒFƒNƒg‚Ì‰¡‚ÌÀ•W‚ğŒvZ‚·‚é
		Combine.center.y = circle1.center.y - circle1.radius - circle2.radius;
		// ‚Ô‚Â‚©‚Á‚½ƒIƒuƒWƒFƒNƒg‚ğ‘€ì‚µ‚Ä‚¢‚éƒIƒuƒWƒFƒNƒg‚Ì^‰¡‚ÉˆÚ“®‚³‚¹‚é
		testObj2->SetBoundingCircle(Combine);
		// ‘€ì‚µ‚Ä‚¢‚éƒIƒuƒWƒFƒNƒg‚Æ“¯‚¶‚æ‚¤‚ÉˆÚ“®‚·‚é
		testObj2->isPlayer = true;
		break;
	case 4:
		// ‰E
		// ‘€ì‚µ‚Ä‚¢‚éƒIƒuƒWƒFƒNƒg‚Ì‰¡‚ÌÀ•W‚ğŒvZ‚·‚é
		Combine.center.x = circle1.center.x - circle1.radius - circle2.radius;
		// ‚Ô‚Â‚©‚Á‚½ƒIƒuƒWƒFƒNƒg‚ğ‘€ì‚µ‚Ä‚¢‚éƒIƒuƒWƒFƒNƒg‚Ì^‰¡‚ÉˆÚ“®‚³‚¹‚é
		testObj2->SetBoundingCircle(Combine);
		// ‘€ì‚µ‚Ä‚¢‚éƒIƒuƒWƒFƒNƒg‚Æ“¯‚¶‚æ‚¤‚ÉˆÚ“®‚·‚é
		testObj2->isPlayer = true;
		break;

	default:
		// “–‚½‚Á‚Ä‚¢‚È‚¢
		break;
	}
}

void Game::CombineTriangleObjects(int HitNum, BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj, TestObject* testObj2)
{
	std::vector<Vector2> Combineobj = testObj2->vertices;// ‰~‚ÌÀ•W‚ğ‹L˜^‚·‚é
	BOUNDING_CIRCLE Combine2 = circle2;// ‰~‚ÌÀ•W‚ğ‹L˜^‚·‚é
	DirectX::XMFLOAT3 rotation = testObj->m_objSprite->m_rotation;
	DirectX::XMFLOAT3 rotation2 = testObj2->m_objSprite->m_rotation;
	// OŠpŒ`‚Ì’¸“_À•W‚ÆƒeƒXƒg‘ÎÛ‚Ì“_‚ğİ’è
	switch (HitNum)
	{
		//[[[OŠpŒ`‚ÌƒIƒuƒWƒFƒNƒg‚Ì‡‘Ì[[[

	case 5:
		// ¶
		// ‘€ì‚µ‚Ä‚¢‚éƒIƒuƒWƒFƒNƒg‚Ì‰¡‚ÌÀ•W‚ğŒvZ‚·‚é
		// }Œ`‚ªˆÚ“®‚µ‚Ä‚¢‚½ê‡‰Šú’l‚É‚·‚é
		testObj2->m_objSprite->InitPos(0, 0, 0.1f);
		testObj2->vertices = SetTriangle(testObj2->GetBoundingCircle(), testObj2);
		// }Œ`‚ÌŠp“x‚ª•Ï‚í‚Á‚Ä‚¢‚½ê‡‰Šú’l‚É‚·‚é
		testObj2->rotation = 0;
		// }Œ`‚ÌˆÚ“®‚ğ‚µ‚½Œã‚É}Œ`‚Ì‰ñ“]‚ğ‚·‚é
		Combineobj = testObj2->vertices;
		Combineobj = InitialPolygonSATvertices(testObj2->GetBoundingCircle(), Combineobj, M_PI / 6.0f - testObj2->rotation);
		circle2.center.x = -Combineobj[1].x / 1.6 + circle1.center.x;
		circle2.center.y = -Combineobj[2].y / 2.9 + circle1.center.y;
		InitialPolygonSAT(circle2, testObj2, -M_PI / 6.0f - testObj2->rotation);//32
		// ‚Ô‚Â‚©‚Á‚½ƒIƒuƒWƒFƒNƒg‚ğ‘€ì‚µ‚Ä‚¢‚éƒIƒuƒWƒFƒNƒg‚Ì^‰¡‚ÉˆÚ“®‚³‚¹‚é
		testObj2->m_objSprite->InitPos(circle2.center.x, circle2.center.y, 0.1f);
		rotation2.z = -60 + rotation.z;
		testObj2->SetRotation(rotation2);
		// ‘€ì‚µ‚Ä‚¢‚éƒIƒuƒWƒFƒNƒg‚Æ“¯‚¶‚æ‚¤‚ÉˆÚ“®‚·‚é
		testObj2->isPlayer = true;
		break;
	case 6:
		// ‰E
		// ‘€ì‚µ‚Ä‚¢‚éƒIƒuƒWƒFƒNƒg‚Ì‰¡‚ÌÀ•W‚ğŒvZ‚·‚é
		testObj2->m_objSprite->InitPos(0, 0, 0.1f);
		testObj2->vertices = SetTriangle(testObj2->GetBoundingCircle(), testObj2);
		testObj2->rotation = 0;
		Combineobj = testObj2->vertices;
		Combineobj = InitialPolygonSATvertices(testObj2->GetBoundingCircle(), Combineobj, M_PI / 6.0f - testObj2->rotation);
		circle2.center.x = Combineobj[1].x / 1.6 + circle1.center.x;
		circle2.center.y = -Combineobj[2].y / 2.9 + circle1.center.y;
		InitialPolygonSAT(circle2, testObj2, M_PI / 6.0f - testObj2->rotation);
		// ‚Ô‚Â‚©‚Á‚½ƒIƒuƒWƒFƒNƒg‚ğ‘€ì‚µ‚Ä‚¢‚éƒIƒuƒWƒFƒNƒg‚Ì^‰¡‚ÉˆÚ“®‚³‚¹‚é
		testObj2->m_objSprite->InitPos(circle2.center.x, circle2.center.y, 0.1f);
		rotation2.z = 60 + rotation.z;
		testObj2->SetRotation(rotation2);
		// ‘€ì‚µ‚Ä‚¢‚éƒIƒuƒWƒFƒNƒg‚Æ“¯‚¶‚æ‚¤‚ÉˆÚ“®‚·‚é
		testObj2->isPlayer = true;
		break;
	case 7:
		// ‰º
		// ‘€ì‚µ‚Ä‚¢‚éƒIƒuƒWƒFƒNƒg‚Ì‰¡‚ÌÀ•W‚ğŒvZ‚·‚é
		testObj2->m_objSprite->InitPos(0, 0, 0.1f);
		testObj2->vertices = SetTriangle(testObj2->GetBoundingCircle(), testObj2);
		testObj2->rotation = 0;
		Combineobj = testObj2->vertices;
		Combineobj = InitialPolygonSATvertices(testObj2->GetBoundingCircle(), Combineobj, M_PI / 2.0f - testObj2->rotation);
		circle2.center.x = circle1.center.x;
		circle2.center.y = -Combineobj[2].y * 2.15 + circle1.center.y;
		InitialPolygonSAT(circle2, testObj2, M_PI / 2.0f - testObj2->rotation);
		// ‚Ô‚Â‚©‚Á‚½ƒIƒuƒWƒFƒNƒg‚ğ‘€ì‚µ‚Ä‚¢‚éƒIƒuƒWƒFƒNƒg‚Ì^‰¡‚ÉˆÚ“®‚³‚¹‚é
		testObj2->m_objSprite->InitPos(circle2.center.x, circle2.center.y, 0.1f);
		rotation2.z = 180 + rotation.z;
		testObj2->SetRotation(rotation2);
		// ‘€ì‚µ‚Ä‚¢‚éƒIƒuƒWƒFƒNƒg‚Æ“¯‚¶‚æ‚¤‚ÉˆÚ“®‚·‚é
		testObj2->isPlayer = true;
		break;

		//	// [[[lŠp‚ÆOŠp[[[

	case 8:
		// ¶
		// ‘€ì‚µ‚Ä‚¢‚éƒIƒuƒWƒFƒNƒg‚Ì‰¡‚ÌÀ•W‚ğŒvZ‚·‚é
		// }Œ`‚ªˆÚ“®‚µ‚Ä‚¢‚½ê‡‰Šú’l‚É‚·‚é
		testObj2->m_objSprite->InitPos(0, 0, 0.1f);
		testObj2->vertices = SetSqureWithTriangle(testObj2->GetBoundingCircle(), testObj2, SQUREWIDTH);
		// }Œ`‚ÌŠp“x‚ª•Ï‚í‚Á‚Ä‚¢‚½ê‡‰Šú’l‚É‚·‚é
		testObj2->rotation = 0;
		// }Œ`‚ÌˆÚ“®‚ğ‚µ‚½Œã‚É}Œ`‚Ì‰ñ“]‚ğ‚·‚é
		Combineobj = testObj2->vertices;
		Combineobj = InitialPolygonSATvertices(testObj2->GetBoundingCircle(), Combineobj, M_PI / 12.0f - testObj2->rotation);
		circle2.center.x = -Combineobj[1].x * 0.98 + circle1.center.x;
		circle2.center.y = -Combineobj[2].y / 2.5 + circle1.center.y;
		InitialPolygonSAT(circle2, testObj2, -M_PI / 12.0f - testObj2->rotation);//32
		// ‚Ô‚Â‚©‚Á‚½ƒIƒuƒWƒFƒNƒg‚ğ‘€ì‚µ‚Ä‚¢‚éƒIƒuƒWƒFƒNƒg‚Ì^‰¡‚ÉˆÚ“®‚³‚¹‚é
		testObj2->m_objSprite->InitPos(circle2.center.x, circle2.center.y, 0.1f);
		rotation2.z = -30 + rotation.z;
		testObj2->SetRotation(rotation2);
		// ‘€ì‚µ‚Ä‚¢‚éƒIƒuƒWƒFƒNƒg‚Æ“¯‚¶‚æ‚¤‚ÉˆÚ“®‚·‚é
		testObj2->isPlayer = true;
	case 9:
		//// ‰E
		//// ‘€ì‚µ‚Ä‚¢‚éƒIƒuƒWƒFƒNƒg‚Ì‰¡‚ÌÀ•W‚ğŒvZ‚·‚é
		//float X1, Y2;
		//deaseX = 0.05 + 0.005 * rotation.z, deaseY = -0.15 - 0.03 * rotation.z;
		//X1 = (triangle.B.x + triangle.C.x) / 2;
		//Y2 = (triangle.B.y + triangle.C.y) / 2;
		//Combine.center.x = X1 + (X1 - triangle.A.x) + deaseX;//+ (X1 - triangle.A.x)+0.3
		//Combine.center.y = Y2 + (Y2 - triangle.A.y) + deaseY;// (Y2 - triangle.A.y)-1.9
		//// ‚Ô‚Â‚©‚Á‚½ƒIƒuƒWƒFƒNƒg‚ğ‘€ì‚µ‚Ä‚¢‚éƒIƒuƒWƒFƒNƒg‚Ì^‰¡‚ÉˆÚ“®‚³‚¹‚é
		//testObj2->m_objSprite->InitPos(Combine.center.x, Combine.center.y, 0.1f);
		//rotation2.z = 30 - rotation.z;
		//testObj2->SetRotation(rotation2);
		// ‘€ì‚µ‚Ä‚¢‚éƒIƒuƒWƒFƒNƒg‚Æ“¯‚¶‚æ‚¤‚ÉˆÚ“®‚·‚é
		//testObj2->isPlayer = true;
		break;
	case 10:
		//// ‰º
		//// ‘€ì‚µ‚Ä‚¢‚éƒIƒuƒWƒFƒNƒg‚Ì‰¡‚ÌÀ•W‚ğŒvZ‚·‚é
		//Combine.center.x = circle1.center.x;
		//Combine.center.y = circle1.center.y - circle1.radius - circle1.radius / 2 - testObj2->Scale_countX;
		//// ‚Ô‚Â‚©‚Á‚½ƒIƒuƒWƒFƒNƒg‚ğ‘€ì‚µ‚Ä‚¢‚éƒIƒuƒWƒFƒNƒg‚Ì^‰¡‚ÉˆÚ“®‚³‚¹‚é
		//testObj2->m_objSprite->InitPos(Combine.center.x, Combine.center.y, 0.1f);
		////rotation.z = 60;
		//testObj2->SetRotation(rotation2);
		//// ‘€ì‚µ‚Ä‚¢‚éƒIƒuƒWƒFƒNƒg‚Æ“¯‚¶‚æ‚¤‚ÉˆÚ“®‚·‚é
		//testObj2->isPlayer = true;
		break;
	case 11:
		break;
	}
}

int Game::SideCollision(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2)
{
	if (circle1.center.x + circle1.radius < circle2.center.x)// ¶
	{
		return 1;
	}
	else if (circle1.center.x - circle1.radius > circle2.center.x)// ‰E
	{
		return 4;
	}
	else if (circle1.center.y < circle2.center.y)// ‰º
	{
		return 2;
	}
	else if (circle1.center.y > circle2.center.y)// ã
	{
		return 3;
	}
}

int Game::SqureCollision(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj, TestObject* testObj2)
{
	SQUREBOX squre1, squre2; // lŠpŒ`‚Ìl•Ó‚ğ“ü‚ê‚é•Ï”‚ğæ“¾‚·‚é

	// lŠpŒ`‚Ìl•Ó‚ğæ“¾
	squre1 = Squre(circle1, testObj2);//(!(p_center.x < circle1.center.x || p_center.x > circle1.center.x)&& !(p_center.y > circle1.center.y || p_center.y < circle1.center.y))
	squre2 = Squre(circle2, testObj);// circle1.center.y - circle1.radius < circle2.center.y + circle2.radius&& circle1.center.y + circle1.radius > circle2.center.y - circle2.radius

	// lŠpŒ`‚ªã‰º‚Ì‚Ç‚¿‚ç‚©‚©‚ç‚Ô‚Â‚©‚Á‚½‚É¶‰E‚Ì“–‚½‚è”»’è‚ª‹@”\‚µ‚È‚¢‚æ‚¤‚É‚·‚é‚½‚ß‚Ìˆ—
	if (p_center.y - circle1.radius < circle2.center.y + circle2.radius
		&& p_center.y + circle1.radius > circle2.center.y - circle2.radius)
	{
		// ¶‰E
		// lŠpŒ`‚É“–‚½‚é’¼‘O‚É‰E•ûŒü‚É“ü—Í‚³‚ê‚Ä‚¢‚é‚©
		if (circle1.center.x < circle2.center.x && p_center.x < circle1.center.x)
		{
			// lŠpŒ`‚Ì¶‘¤‚É‰~‚ªG‚ê‚½ê‡‚Ì“–‚½‚è”»’è
			if (CheckSqureHit(squre1.Left, squre2.Right))// ¶
			{
				return 1;
			}
		}
		// lŠpŒ`‚É“–‚½‚é’¼‘O‚É¶•ûŒü‚É“ü—Í‚³‚ê‚Ä‚¢‚é‚©
		else if (circle1.center.x > circle2.center.x && p_center.x > circle1.center.x)
		{
			// lŠpŒ`‚Ì‰E‘¤‚É‰~‚ªG‚ê‚½ê‡‚Ì“–‚½‚è”»’è
			if (CheckSqureHit(squre1.Right, squre2.Left))// ‰E
			{
				return 4;
			}
		}
	}

	// ã‰º
	// lŠpŒ`‚É“–‚½‚é’¼‘O‚É‰º•ûŒü‚É“ü—Í‚³‚ê‚Ä‚¢‚é‚©
	if (circle1.center.y > circle2.center.y && p_center.y > circle1.center.y)
	{
		// lŠpŒ`‚Ìã‘¤‚É‰~‚ªG‚ê‚½ê‡‚Ì“–‚½‚è”»’è
		if (CheckSqureHit(squre1.Top, squre2.Bottom))// ã
		{
			return 3;
		}
	}
	// lŠpŒ`‚É“–‚½‚é’¼‘O‚Éã•ûŒü‚É“ü—Í‚³‚ê‚Ä‚¢‚é‚©
	else if (circle1.center.y < circle2.center.y && p_center.y < circle1.center.y)
	{
		// lŠpŒ`‚Ì‰º‘¤‚É‰~‚ªG‚ê‚½ê‡‚Ì“–‚½‚è”»’è
		if (CheckSqureHit(squre1.Bottom, squre2.Top))// ‰º
		{
			return 2;
		}
	}

	return 0;
}

bool Game::CheckSqureHit(const BOX& t_box, const BOX& t_box2)
{
	// lŠpŒ`‚Ì¶‰E‚Ç‚¿‚ç‚©‚Ì•Ó‚ªd‚È‚Á‚Ä‚¢‚é
	if ((t_box.fRight > t_box2.fLeft) ||
		(t_box.fLeft < t_box2.fRight))
	{
		// lŠpŒ`‚Ìã‰º‚Ç‚¿‚ç‚©‚Ì•Ó‚ªd‚È‚Á‚Ä‚¢‚é
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
	SQUREBOX squre; // lŠpŒ`‚Ìl•Ó‚ğ“ü‚ê‚é•Ï”‚ğæ“¾‚·‚é

	// lŠpŒ`‚Ì¶‰E‚ÉG‚ê‚½ê‡‚Ìl•Ó‚ÌÀ•W
	float X_posx1 = 1.4 + circle2.center.x + testObj->Scale_countX;
	float X_posx2 = -1.4 + circle2.center.x - testObj->Scale_countX;
	float X_posy1 = 1 + circle2.center.y + testObj->Scale_countY;
	float X_posy2 = -1 + circle2.center.y - testObj->Scale_countY;

	// lŠpŒ`‚Ìã‰º‚ÉG‚ê‚½ê‡‚Ìl•Ó‚ÌÀ•W
	float Y_posx1 = 1.4 + circle2.center.y + testObj->Scale_countX;
	float Y_posx2 = -1.4 + circle2.center.y - testObj->Scale_countX;
	float Y_posy1 = 1 + circle2.center.x + testObj->Scale_countX;
	float Y_posy2 = -1 + circle2.center.x - testObj->Scale_countX;

	// lŠpŒ`‚Ì•Ó‚É‚»‚ê‚¼‚êl‚Â‚ÌÀ•W‚ğ‚¢‚ê‚é
	squre.Left = { X_posx2, X_posy2, X_posx2, X_posy1 };   // ¶
	squre.Right = { X_posx1, X_posy2, X_posx1, X_posy1 };  // ‰E
	squre.Bottom = { Y_posy2, Y_posx2, Y_posy1, Y_posx2 }; // ‰º
	squre.Top = { Y_posy2, Y_posx1, Y_posy1, Y_posx1 };    // ã

	// lŠpŒ`‚Ìl•Ó‚ğ•Ô‚·
	return squre;
}

std::vector<Vector2> Game::SetTriangle(BOUNDING_CIRCLE circle1, TestObject* testObj2)
{
	Triangle triangle;
	triangle.A = { 0                                , 0.9f + testObj2->Scale_countY };
	triangle.B = { 1.1f + testObj2->Scale_countX, -0.9f - testObj2->Scale_countY };
	triangle.C = { -1.1f - testObj2->Scale_countX, -0.9f - testObj2->Scale_countY };


	// 1‚Â–Ú‚Ì“Ê‘½ŠpŒ`‚Ì’¸“_À•W‚ğ’è‹`
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
	// lŠp‚Ì‰º‚ÌOŠp
	squre.A = { width + testObj2->Scale_countX,
				width + testObj2->Scale_countY };
	squre.B = { width + testObj2->Scale_countX,
				-width + -testObj2->Scale_countY };
	squre.C = { -width - testObj2->Scale_countX,
				-width + -testObj2->Scale_countY };
	squre.D = { -width - testObj2->Scale_countX,
				 width + testObj2->Scale_countY };

	// 1‚Â–Ú‚Ì“Ê‘½ŠpŒ`‚Ì’¸“_À•W‚ğ’è‹`
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
	// lŠp‚Ì‰º‚ÌOŠp
	circle.A = { circle1.center.x , width + circle1.center.y + testObj2->Scale_countY };
	circle.B = { -width + circle1.center.x - testObj2->Scale_countX,circle1.center.y };
	circle.C = { circle1.center.x , -width + circle1.center.y - testObj2->Scale_countY };
	circle.D = { width + circle1.center.x + testObj2->Scale_countX,circle1.center.y };
	return circle;
}

bool Game::isPointInTriangle(Point A, Point B, Point C, Point P)
{
	// ƒoƒŠƒAÀ•W‚ÌŒvZ
	float denominator = (B.y - C.y) * (A.x - C.x) + (C.x - B.x) * (A.y - C.y);
	float alpha = ((B.y - C.y) * (P.x - C.x) + (C.x - B.x) * (P.y - C.y)) / denominator;
	float beta = ((C.y - A.y) * (P.x - C.x) + (A.x - C.x) * (P.y - C.y)) / denominator;
	float gamma = 1.0 - alpha - beta;

	// À•W“à•ï«‚ÌŠm”F
	return alpha >= 0.0 && alpha <= 1.0 && beta >= 0.0 && beta <= 1.0 && gamma >= 0.0 && gamma <= 1.0;
}

int Game::CheckTriangleHit(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj, TestObject* testObj2)
{
	// OŠpŒ`‚Ì’¸“_À•W‚ÆƒeƒXƒg‘ÎÛ‚Ì“_‚ğİ’è
	// ‘€ì‚µ‚Ä‚¢‚éOŠpŒ`
	testObj->vertices = SetTriangle(circle1, testObj);
	// ‘€ì‚µ‚Ä‚¢‚È‚¢OŠpŒ`
	testObj2->vertices = SetTriangle(circle2, testObj2);

	// OŠp“¯m‚ªG‚ê‚Ä‚¢‚é
	if (TriangleHit(testObj, testObj2))
	{
		if (testObj2->vertices[0].y > circle1.center.y)
		{
			// ‰Eã‚É‚ ‚é‚Æ‚«
			if (testObj->vertices[0].x < circle2.center.x)
			{
				// ‰E
				return 6;
			}
			// ¶ã‚É‚ ‚é‚Æ‚«
			else if (testObj->vertices[0].x > circle2.center.x)
			{
				// ¶
				return 5;
			}
		}
		// ã‚É‚ ‚é‚Æ‚«
		else
		{
			// ã
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
	// lŠp
	for (auto& vertex : testObj2->vertices) {
		vertex.x += circle1.center.x;
		vertex.y += circle1.center.y;
	}

	Triangle2.vertices = testObj2->vertices;

	bool collisionResult = Collide(Triangle1, Triangle2);

	// Œ‹‰Ê‚ğ•\¦
	if (collisionResult)
	{
		return true;
	}
	return false;
}

void Game::InitialPolygonSAT(BOUNDING_CIRCLE circle1, TestObject* testObj, float rotation)
{
	//BOUNDING_CIRCLE circle4 = testObj->GetBoundingCircle();// ‘€ì‚µ‚Ä‚¢‚È‚¢ƒIƒuƒWƒFƒNƒg 
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
	// OŠpŒ`‚Ì’¸“_À•W‚ÆƒeƒXƒg‘ÎÛ‚Ì“_‚ğİ’è
	// ‘€ì‚µ‚Ä‚¢‚éOŠpŒ`
	testObj->vertices = SetTriangle(circle1, testObj);
	// ‘€ì‚µ‚Ä‚¢‚È‚¢lŠpŒ`
	testObj2->vertices = SetSqureWithTriangle(circle2, testObj2, SQUREWIDTH);

	// OŠp“¯m‚ªG‚ê‚Ä‚¢‚é
	if (TriangleHit(testObj, testObj2))
	{
		if (testObj2->vertices[0].y > circle1.center.y)
		{
			// ‰Eã‚É‚ ‚é‚Æ‚«
			if (testObj->vertices[0].x < circle2.center.x)
			{
				// ‰E
				return 9;
			}
			// ¶ã‚É‚ ‚é‚Æ‚«
			else if (testObj->vertices[0].x > circle2.center.x)
			{
				// ¶
				return 8;
			}
		}
		// ã‚É‚ ‚é‚Æ‚«
		else
		{
			// ã
			return 10;
		}
	}

	return 0;
}

int Game::CheckTriangleAndCircleHit(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj, TestObject* testObj2)
{
	// OŠpŒ`‚Ì’¸“_À•W‚ÆƒeƒXƒg‘ÎÛ‚Ì“_‚ğİ’è
	std::vector<Vector2> triangle;
	SQURE circle;
	std::vector<Vector2> squre;

	// ‘€ì‚µ‚Ä‚¢‚éOŠpŒ`
	triangle = SetTriangle(circle1, testObj);
	squre = SetSqureWithTriangle(circle2, testObj2, TRIANGLEWIDTH);
	circle = SetCircleWithTriangle(circle2, testObj2, SQUREWIDTH);

	// ’†S“_
	Point squrecenter = { circle2.center.x ,circle2.center.y };

	////// “–‚½‚è”»’è‚ğs‚¤
	//if     (isPointInTriangle(squrecenter, circle.D, squre.C, triangle.A)
	//	||  isPointInTriangle(squrecenter, squre.C, circle.C, triangle.A)
	//	|| (isPointInTriangle(triangle.A, triangle.B, triangle.C, squre.C)))
	//{
	//	// ‰E
	//	return 8;
	//}
	//else if (isPointInTriangle(squrecenter, circle.B, squre.A, triangle.B)
	//	  || isPointInTriangle(squrecenter, squre.A, circle.C, triangle.B)
	//	  || isPointInTriangle(triangle.A, triangle.B, triangle.C, squre.A))
	//{
	//	// ¶
	//	return 9;
	//}
	//// ‰º
	//else if (isPointInTriangle(circle.B, squre.A, squrecenter, triangle.C)
	//	  || isPointInTriangle(squre.A, circle.C, squrecenter, triangle.C))
	//{
	//	// ¶
	//	return 9;
	//}
	//else if (isPointInTriangle(circle.D, squre.C, squrecenter, triangle.C)
	//	  || isPointInTriangle(squre.C, circle.C, squrecenter, triangle.C))
	//{
	//	// ‰E
	//	return 8;
	//}
	//else if ((isPointInTriangle(circle.B, squre.D, squrecenter, triangle.B)
	//	   || isPointInTriangle(squre.D, circle.A, squrecenter, triangle.B)
	//	   || isPointInTriangle(circle.A, squrecenter, squre.B, triangle.A)
	//	   || isPointInTriangle(squre.B, squrecenter, circle.D, triangle.A)))
	//{
	//	// ã
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
>>>>>>> .merge_file_tnJJ8S
