﻿#include "Game.h"
#include "Direct3D/Direct3D.h"
#include "Assets.h"
#include "ObjectAnimation.h"
#include "StaticAnimation.h"
#include "TrackCamera.h"
#include "DebugManager.h"
#include "DInput.h"

#include "SAT.h"
#include <algorithm> // �K�v�ȃw�b�_�[�t�@�C��
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
=======
Game::Game()
{
	////�I�u�W�F�N�g������
	//testObject = new Object(g_Assets->testchar01, 96, 96, 3, 4);
	////�A�j���[�V�����N���X������->�ǂ̃A�j���[�V�����ɂ���
	//testObject->m_sprite->m_anime = new ObjectAnimation(3, 4);
	////�A�j���[�V�������x��ݒ�
	//testObject->m_sprite->m_anime->SetAnimeSpeed(0.1f);
	////�A�j���[�V�����p�^�[����ݒ�
	//testObject->m_sprite->m_anime->SetAnimePattern(0);

	// �I�u�W�F�N�g1
	testObj = new TestObject();
	//�I�u�W�F�N�g�̏����ݒ�
	testObj->SetObjTex(g_Assets->triangle, 200, 200, 1, 1);
	testObj->m_objSprite->m_anime = new ObjectAnimation(1, 1);
	testObj->m_objSprite->m_anime->SetAnimeSpeed(0.0f);
	testObj->m_objSprite->m_anime->SetAnimePattern(0);
	testObj->m_objSprite->InitPos(-4, -1.16, 0.2f);
	DirectX::XMFLOAT3 rotation = testObj->m_objSprite->m_rotation;
	testObj->isPlayer = true;// �L�[�{�[�h�ő���\
	BOUNDING_CIRCLE circle1 = testObj->GetBoundingCircle();// ���삵�Ă��Ȃ��I�u�W�F�N�g 
	testObj->vertices = SetTriangle(circle1, testObj);

	// �I�u�W�F�N�g2
	testObj2 = new TestObject();
	//�I�u�W�F�N�g�̏����ݒ�
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

	// �I�u�W�F�N�g3
	testObj3 = new TestObject();
	//�I�u�W�F�N�g�̏����ݒ�
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
	
	//影の初期設定


<<<<<<< .merge_file_zvS5Zi

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

	
=======
	//�I�u�W�F�N�g������
	testBg = new Object(g_Assets->testbgbox, 1280, 720, 1, 1);
	testBg->m_sprite->m_pos.z = 0.9;//�O��̈ʒu�ݒ���N���X���ōs��
	//�A�j���[�V�����N���X������->�ǂ̃A�j���[�V�����ɂ���
	testBg->m_sprite->m_anime = new ObjectAnimation(1, 1);
	//�A�j���[�V�������x��ݒ�
	testBg->m_sprite->m_anime->SetAnimeSpeed(0.0f);
	//�A�j���[�V�����p�^�[����ݒ�
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

	//背景
	testGround->Update();
	

	testTree->Update(testChara->m_sprite->m_pos);

	testChara->Update();

	uitest->Update();



	

=======
{
	// �����蔻�菈��
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
	//============ ここから描画処理 ============//
	
	
=======
	//============ ��������`�揈�� ============//


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
	//============ ここまで描画処理 ============//
	 
	//ダブルバッファの切り替えを行い画面を更新する
=======
	//============ �����܂ŕ`�揈�� ============//

	//�_�u���o�b�t�@�̐؂�ւ����s����ʂ��X�V����
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

<<<<<<< .merge_file_zvS5Zi
=======
void Game::TestCollision()
{
	BOUNDING_CIRCLE circle1 = testObj->GetBoundingCircle();// ���삵�Ă���I�u�W�F�N�g
	BOUNDING_CIRCLE circle2 = testObj2->GetBoundingCircle();// ���삵�Ă��Ȃ��I�u�W�F�N�g 
	BOUNDING_CIRCLE circle3 = testObj3->GetBoundingCircle();// ���삵�Ă��Ȃ��I�u�W�F�N�g 
	BOUNDING_CIRCLE circle4 = testObj4->GetBoundingCircle();// ���삵�Ă��Ȃ��I�u�W�F�N�g 
	//Triangle triangle, triangle2;
	//std::vector<Vector2> verticesA,verticesB;

	// �����œ����蔻���؂�ւ���
	//�~���m
	//MoveObjects(CircleHit(circle1, circle2), Combine, circle1, circle2);

	if (!testObj3->isPlayer)// �I�u�W�F�N�g���m���G�ꂽ�瓖���蔻�������
	{
		// �~�Ǝl�p 1�l�p�@�Q�l�p�@�R�~
		// SqureandCircle�֐��@�����P�F�~�@�Q�F�l�p 3:�l�p�̃e�N�X�`���������Ă����������
		// MoveObjects�֐��@�����P�F�I�u�W�F�N�g���ǂ��ɓ��������̂��̖߂�l�@�����Q�F���̂����錳�̃I�u�W�F�N�g�̍��W
		// �@�@�@�@�@�@     �����R,�S,�T�FMoveObjects�֐��̈����Ɠ���
		//CombineObjects(SqureandCircle(circle1, circle3, testObj3),circle1, circle3, testObj3);

		//CombineObjects(SqureandCircle(circle2, circle3, testObj3), circle2, circle3, testObj3);

		// �O�p�Ɖ~
		//CombineTriangleObjects(CheckTriangleAndCircleHit(circle1, circle3, testObj, testObj3), circle1, circle3, testObj,testObj3);
	}

	if (!testObj2->isPlayer)// �I�u�W�F�N�g���m���G�ꂽ�瓖���蔻�������
	{
		// �l�p�Ǝl�p �����P�F���삵�Ă���I�u�W�F�N�g�@�����Q�F���삵�Ă��Ȃ��I�u�W�F�N�g
		//CombineObjects(SqureHit(circle1, circle2, testObj, testObj2),circle1, circle2, testObj2);

		//CombineObjects(SqureandCircle(circle3, circle2, testObj2), circle3, circle2, testObj2);

		// �O�p�Ǝl�p�@�P�O�p�@�S�O�p�@�Q�l�p
		CombineTriangleObjects(CheckTriangleAndSqureHit(circle1, circle2, testObj, testObj2), circle1, circle2, testObj, testObj2);

		//CombineTriangleObjects(CheckTriangleAndSqureHit(circle4, circle2, testObj4, testObj2), circle4, circle2, testObj4, testObj2);
	}

	if (!testObj4->isPlayer)
	{
		// �O�p���m
		//CombineObjects(CheckTriangleHit(circle1, circle4, testObj, testObj4), circle1, circle4, testObj, testObj4);

		//CombineObjects(CheckTriangleAndSqureHit(circle2, circle4, testObj2, testObj4), circle2, circle4, testObj4);

		CombineTriangleObjects(CheckTriangleHit(circle1, circle4, testObj, testObj4), circle1, circle4, testObj, testObj4);

	}

}

int Game::CircleHit(BOUNDING_CIRCLE bc1, BOUNDING_CIRCLE bc2)
{
	//bc1 �~�@bc2 �~
	float teihen = bc2.center.x - bc1.center.x;// ��ӂ̒���
	float takasa = bc2.center.y - bc1.center.y;// ����
	float r2 = bc1.radius + bc2.radius; // �~1�̔��a�{�~2�̔��a

	if (teihen * teihen + takasa * takasa <= r2 * r2)
	{
		// �㉺���E�̓����蔻��ŕʂ̖߂�l��Ԃ�
		return SideCollision(bc1, bc2);
	}

	return 0;
}

bool Game::CheckHit(const BOX& t_box, const BOUNDING_CIRCLE bc1)
{
	bool nResult = false;

	// �l�p�`�̎l�ӂɑ΂��ĉ~�̔��a�������������Ƃ��~���d�Ȃ��Ă�����
	if ((bc1.center.x > t_box.fLeft - bc1.radius) &&
		(bc1.center.x < t_box.fRight + bc1.radius) &&
		(bc1.center.y > t_box.fTop - bc1.radius) &&
		(bc1.center.y < t_box.fBottom + bc1.radius))
	{
		// �������Ă���
		nResult = true;
	}

	return nResult;
}

int Game::SqureandCircle(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj)
{
	BOX squre; // �l�p�`�̎l�ӂ�����ϐ����擾����

	// �l�p�`�̍��E�ɐG�ꂽ�ꍇ�̎l�ӂ̍��W
	float X_posx1 = 1.4 + circle2.center.x + testObj->Scale_countX;
	float X_posx2 = -1.4 + circle2.center.x - testObj->Scale_countX;
	float X_posy1 = 1 + circle2.center.y + testObj->Scale_countY;
	float X_posy2 = -1 + circle2.center.y - testObj->Scale_countY;

	// �l�p�`�̏㉺�ɐG�ꂽ�ꍇ�̎l�ӂ̍��W
	float Y_posx1 = 1.4 + circle2.center.y + testObj->Scale_countX;
	float Y_posx2 = -1.4 + circle2.center.y - testObj->Scale_countX;
	float Y_posy1 = 1 + circle2.center.x + testObj->Scale_countX;
	float Y_posy2 = -1 + circle2.center.x - testObj->Scale_countX;
	//testObj2->m_objSprite->InitBox(-1, -1.4, 1, -1.4);

	// ���E
	// �l�p�`�̍����ɉ~���G�ꂽ�ꍇ�̓����蔻��
	if (CheckHit(squre = { X_posx2, X_posy2, X_posx2, X_posy1 }, circle1))// ��
	{
		return 1;
	}
	// �l�p�`�̉E���ɉ~���G�ꂽ�ꍇ�̓����蔻��
	else if (CheckHit(squre = { X_posx1, X_posy2, X_posx1, X_posy1 }, circle1))// �E
	{
		return 4;
	}
	// �㉺
	// �l�p�`�̉����ɉ~���G�ꂽ�ꍇ�̓����蔻��
	else if (CheckHit(squre = { Y_posy2, Y_posx2, Y_posy1, Y_posx2 }, circle1))// ��
	{
		return 2;
	}
	// �l�p�`�̏㑤�ɉ~���G�ꂽ�ꍇ�̓����蔻��
	else if (CheckHit(squre = { Y_posy2, Y_posx1, Y_posy1, Y_posx1 }, circle1))// ��
	{
		return 3;
	}

	return 0;
}

int Game::SqureHit(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj, TestObject* testObj2)
{
	// �l�p�`���m�̓����蔻��
	if ((circle1.center.x + circle1.radius >= circle2.center.x - circle2.radius) &&
		(circle2.center.x + circle2.radius >= circle1.center.x - circle1.radius) &&
		(circle1.center.y + circle1.radius >= circle2.center.y - circle2.radius) &&
		(circle2.center.y + circle2.radius >= circle1.center.y - circle1.radius))
	{
		// �㉺���E�̓����蔻��ŕʂ̖߂�l��Ԃ�
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
	BOUNDING_CIRCLE Combine = circle1;// �~�̍��W���L�^����
	DirectX::XMFLOAT3 rotation = testObj->m_objSprite->m_rotation;
	DirectX::XMFLOAT3 rotation2 = testObj2->m_objSprite->m_rotation;


	switch (HitNum)
	{
	case 1:
		// ��
		// ���삵�Ă���I�u�W�F�N�g�̉��̍��W���v�Z����
		Combine.center.x = circle1.center.x + circle1.radius + circle2.radius;
		// �Ԃ������I�u�W�F�N�g�𑀍삵�Ă���I�u�W�F�N�g�̐^���Ɉړ�������
		testObj2->SetBoundingCircle(Combine);
		// ���삵�Ă���I�u�W�F�N�g�Ɠ����悤�Ɉړ�����
		testObj2->isPlayer = true;
		break;
	case 2:
		// ��
		// ���삵�Ă���I�u�W�F�N�g�̉��̍��W���v�Z����
		Combine.center.y = circle1.center.y + circle1.radius + circle2.radius;
		// �Ԃ������I�u�W�F�N�g�𑀍삵�Ă���I�u�W�F�N�g�̐^���Ɉړ�������
		testObj2->SetBoundingCircle(Combine);
		// ���삵�Ă���I�u�W�F�N�g�Ɠ����悤�Ɉړ�����
		testObj2->isPlayer = true;
		break;
	case 3:
		// ��
		// ���삵�Ă���I�u�W�F�N�g�̉��̍��W���v�Z����
		Combine.center.y = circle1.center.y - circle1.radius - circle2.radius;
		// �Ԃ������I�u�W�F�N�g�𑀍삵�Ă���I�u�W�F�N�g�̐^���Ɉړ�������
		testObj2->SetBoundingCircle(Combine);
		// ���삵�Ă���I�u�W�F�N�g�Ɠ����悤�Ɉړ�����
		testObj2->isPlayer = true;
		break;
	case 4:
		// �E
		// ���삵�Ă���I�u�W�F�N�g�̉��̍��W���v�Z����
		Combine.center.x = circle1.center.x - circle1.radius - circle2.radius;
		// �Ԃ������I�u�W�F�N�g�𑀍삵�Ă���I�u�W�F�N�g�̐^���Ɉړ�������
		testObj2->SetBoundingCircle(Combine);
		// ���삵�Ă���I�u�W�F�N�g�Ɠ����悤�Ɉړ�����
		testObj2->isPlayer = true;
		break;

	default:
		// �������Ă��Ȃ�
		break;
	}
}

void Game::CombineTriangleObjects(int HitNum, BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj, TestObject* testObj2)
{
	std::vector<Vector2> Combineobj = testObj2->vertices;// �~�̍��W���L�^����
	BOUNDING_CIRCLE Combine2 = circle2;// �~�̍��W���L�^����
	DirectX::XMFLOAT3 rotation = testObj->m_objSprite->m_rotation;
	DirectX::XMFLOAT3 rotation2 = testObj2->m_objSprite->m_rotation;
	// �O�p�`�̒��_���W�ƃe�X�g�Ώۂ̓_��ݒ�
	switch (HitNum)
	{
		//�[�[�[�O�p�`�̃I�u�W�F�N�g�̍��́[�[�[

	case 5:
		// ��
		// ���삵�Ă���I�u�W�F�N�g�̉��̍��W���v�Z����
		// �}�`���ړ����Ă����ꍇ�����l�ɂ���
		testObj2->m_objSprite->InitPos(0, 0, 0.1f);
		testObj2->vertices = SetTriangle(testObj2->GetBoundingCircle(), testObj2);
		// �}�`�̊p�x���ς���Ă����ꍇ�����l�ɂ���
		testObj2->rotation = 0;
		// �}�`�̈ړ���������ɐ}�`�̉�]������
		Combineobj = testObj2->vertices;
		Combineobj = InitialPolygonSATvertices(testObj2->GetBoundingCircle(), Combineobj, M_PI / 6.0f - testObj2->rotation);
		circle2.center.x = -Combineobj[1].x / 1.6 + circle1.center.x;
		circle2.center.y = -Combineobj[2].y / 2.9 + circle1.center.y;
		InitialPolygonSAT(circle2, testObj2, -M_PI / 6.0f - testObj2->rotation);//32
		// �Ԃ������I�u�W�F�N�g�𑀍삵�Ă���I�u�W�F�N�g�̐^���Ɉړ�������
		testObj2->m_objSprite->InitPos(circle2.center.x, circle2.center.y, 0.1f);
		rotation2.z = -60 + rotation.z;
		testObj2->SetRotation(rotation2);
		// ���삵�Ă���I�u�W�F�N�g�Ɠ����悤�Ɉړ�����
		testObj2->isPlayer = true;
		break;
	case 6:
		// �E
		// ���삵�Ă���I�u�W�F�N�g�̉��̍��W���v�Z����
		testObj2->m_objSprite->InitPos(0, 0, 0.1f);
		testObj2->vertices = SetTriangle(testObj2->GetBoundingCircle(), testObj2);
		testObj2->rotation = 0;
		Combineobj = testObj2->vertices;
		Combineobj = InitialPolygonSATvertices(testObj2->GetBoundingCircle(), Combineobj, M_PI / 6.0f - testObj2->rotation);
		circle2.center.x = Combineobj[1].x / 1.6 + circle1.center.x;
		circle2.center.y = -Combineobj[2].y / 2.9 + circle1.center.y;
		InitialPolygonSAT(circle2, testObj2, M_PI / 6.0f - testObj2->rotation);
		// �Ԃ������I�u�W�F�N�g�𑀍삵�Ă���I�u�W�F�N�g�̐^���Ɉړ�������
		testObj2->m_objSprite->InitPos(circle2.center.x, circle2.center.y, 0.1f);
		rotation2.z = 60 + rotation.z;
		testObj2->SetRotation(rotation2);
		// ���삵�Ă���I�u�W�F�N�g�Ɠ����悤�Ɉړ�����
		testObj2->isPlayer = true;
		break;
	case 7:
		// ��
		// ���삵�Ă���I�u�W�F�N�g�̉��̍��W���v�Z����
		testObj2->m_objSprite->InitPos(0, 0, 0.1f);
		testObj2->vertices = SetTriangle(testObj2->GetBoundingCircle(), testObj2);
		testObj2->rotation = 0;
		Combineobj = testObj2->vertices;
		Combineobj = InitialPolygonSATvertices(testObj2->GetBoundingCircle(), Combineobj, M_PI / 2.0f - testObj2->rotation);
		circle2.center.x = circle1.center.x;
		circle2.center.y = -Combineobj[2].y * 2.15 + circle1.center.y;
		InitialPolygonSAT(circle2, testObj2, M_PI / 2.0f - testObj2->rotation);
		// �Ԃ������I�u�W�F�N�g�𑀍삵�Ă���I�u�W�F�N�g�̐^���Ɉړ�������
		testObj2->m_objSprite->InitPos(circle2.center.x, circle2.center.y, 0.1f);
		rotation2.z = 180 + rotation.z;
		testObj2->SetRotation(rotation2);
		// ���삵�Ă���I�u�W�F�N�g�Ɠ����悤�Ɉړ�����
		testObj2->isPlayer = true;
		break;

		//	// �[�[�[�l�p�ƎO�p�[�[�[

	case 8:
		// ��
		// ���삵�Ă���I�u�W�F�N�g�̉��̍��W���v�Z����
		// �}�`���ړ����Ă����ꍇ�����l�ɂ���
		testObj2->m_objSprite->InitPos(0, 0, 0.1f);
		testObj2->vertices = SetSqureWithTriangle(testObj2->GetBoundingCircle(), testObj2, SQUREWIDTH);
		// �}�`�̊p�x���ς���Ă����ꍇ�����l�ɂ���
		testObj2->rotation = 0;
		// �}�`�̈ړ���������ɐ}�`�̉�]������
		Combineobj = testObj2->vertices;
		Combineobj = InitialPolygonSATvertices(testObj2->GetBoundingCircle(), Combineobj, M_PI / 12.0f - testObj2->rotation);
		circle2.center.x = -Combineobj[1].x * 0.98 + circle1.center.x;
		circle2.center.y = -Combineobj[2].y / 2.5 + circle1.center.y;
		InitialPolygonSAT(circle2, testObj2, -M_PI / 12.0f - testObj2->rotation);//32
		// �Ԃ������I�u�W�F�N�g�𑀍삵�Ă���I�u�W�F�N�g�̐^���Ɉړ�������
		testObj2->m_objSprite->InitPos(circle2.center.x, circle2.center.y, 0.1f);
		rotation2.z = -30 + rotation.z;
		testObj2->SetRotation(rotation2);
		// ���삵�Ă���I�u�W�F�N�g�Ɠ����悤�Ɉړ�����
		testObj2->isPlayer = true;
	case 9:
		//// �E
		//// ���삵�Ă���I�u�W�F�N�g�̉��̍��W���v�Z����
		//float X1, Y2;
		//deaseX = 0.05 + 0.005 * rotation.z, deaseY = -0.15 - 0.03 * rotation.z;
		//X1 = (triangle.B.x + triangle.C.x) / 2;
		//Y2 = (triangle.B.y + triangle.C.y) / 2;
		//Combine.center.x = X1 + (X1 - triangle.A.x) + deaseX;//+ (X1 - triangle.A.x)+0.3
		//Combine.center.y = Y2 + (Y2 - triangle.A.y) + deaseY;// (Y2 - triangle.A.y)-1.9
		//// �Ԃ������I�u�W�F�N�g�𑀍삵�Ă���I�u�W�F�N�g�̐^���Ɉړ�������
		//testObj2->m_objSprite->InitPos(Combine.center.x, Combine.center.y, 0.1f);
		//rotation2.z = 30 - rotation.z;
		//testObj2->SetRotation(rotation2);
		// ���삵�Ă���I�u�W�F�N�g�Ɠ����悤�Ɉړ�����
		//testObj2->isPlayer = true;
		break;
	case 10:
		//// ��
		//// ���삵�Ă���I�u�W�F�N�g�̉��̍��W���v�Z����
		//Combine.center.x = circle1.center.x;
		//Combine.center.y = circle1.center.y - circle1.radius - circle1.radius / 2 - testObj2->Scale_countX;
		//// �Ԃ������I�u�W�F�N�g�𑀍삵�Ă���I�u�W�F�N�g�̐^���Ɉړ�������
		//testObj2->m_objSprite->InitPos(Combine.center.x, Combine.center.y, 0.1f);
		////rotation.z = 60;
		//testObj2->SetRotation(rotation2);
		//// ���삵�Ă���I�u�W�F�N�g�Ɠ����悤�Ɉړ�����
		//testObj2->isPlayer = true;
		break;
	case 11:
		break;
	}
}

int Game::SideCollision(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2)
{
	if (circle1.center.x + circle1.radius < circle2.center.x)// ��
	{
		return 1;
	}
	else if (circle1.center.x - circle1.radius > circle2.center.x)// �E
	{
		return 4;
	}
	else if (circle1.center.y < circle2.center.y)// ��
	{
		return 2;
	}
	else if (circle1.center.y > circle2.center.y)// ��
	{
		return 3;
	}
}

int Game::SqureCollision(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj, TestObject* testObj2)
{
	SQUREBOX squre1, squre2; // �l�p�`�̎l�ӂ�����ϐ����擾����

	// �l�p�`�̎l�ӂ��擾
	squre1 = Squre(circle1, testObj2);//(!(p_center.x < circle1.center.x || p_center.x > circle1.center.x)&& !(p_center.y > circle1.center.y || p_center.y < circle1.center.y))
	squre2 = Squre(circle2, testObj);// circle1.center.y - circle1.radius < circle2.center.y + circle2.radius&& circle1.center.y + circle1.radius > circle2.center.y - circle2.radius

	// �l�p�`���㉺�̂ǂ��炩����Ԃ��������ɍ��E�̓����蔻�肪�@�\���Ȃ��悤�ɂ��邽�߂̏���
	if (p_center.y - circle1.radius < circle2.center.y + circle2.radius
		&& p_center.y + circle1.radius > circle2.center.y - circle2.radius)
	{
		// ���E
		// �l�p�`�ɓ����钼�O�ɉE�����ɓ��͂���Ă��邩
		if (circle1.center.x < circle2.center.x && p_center.x < circle1.center.x)
		{
			// �l�p�`�̍����ɉ~���G�ꂽ�ꍇ�̓����蔻��
			if (CheckSqureHit(squre1.Left, squre2.Right))// ��
			{
				return 1;
			}
		}
		// �l�p�`�ɓ����钼�O�ɍ������ɓ��͂���Ă��邩
		else if (circle1.center.x > circle2.center.x && p_center.x > circle1.center.x)
		{
			// �l�p�`�̉E���ɉ~���G�ꂽ�ꍇ�̓����蔻��
			if (CheckSqureHit(squre1.Right, squre2.Left))// �E
			{
				return 4;
			}
		}
	}

	// �㉺
	// �l�p�`�ɓ����钼�O�ɉ������ɓ��͂���Ă��邩
	if (circle1.center.y > circle2.center.y && p_center.y > circle1.center.y)
	{
		// �l�p�`�̏㑤�ɉ~���G�ꂽ�ꍇ�̓����蔻��
		if (CheckSqureHit(squre1.Top, squre2.Bottom))// ��
		{
			return 3;
		}
	}
	// �l�p�`�ɓ����钼�O�ɏ�����ɓ��͂���Ă��邩
	else if (circle1.center.y < circle2.center.y && p_center.y < circle1.center.y)
	{
		// �l�p�`�̉����ɉ~���G�ꂽ�ꍇ�̓����蔻��
		if (CheckSqureHit(squre1.Bottom, squre2.Top))// ��
		{
			return 2;
		}
	}

	return 0;
}

bool Game::CheckSqureHit(const BOX& t_box, const BOX& t_box2)
{
	// �l�p�`�̍��E�ǂ��炩�̕ӂ��d�Ȃ��Ă���
	if ((t_box.fRight > t_box2.fLeft) ||
		(t_box.fLeft < t_box2.fRight))
	{
		// �l�p�`�̏㉺�ǂ��炩�̕ӂ��d�Ȃ��Ă���
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
	SQUREBOX squre; // �l�p�`�̎l�ӂ�����ϐ����擾����

	// �l�p�`�̍��E�ɐG�ꂽ�ꍇ�̎l�ӂ̍��W
	float X_posx1 = 1.4 + circle2.center.x + testObj->Scale_countX;
	float X_posx2 = -1.4 + circle2.center.x - testObj->Scale_countX;
	float X_posy1 = 1 + circle2.center.y + testObj->Scale_countY;
	float X_posy2 = -1 + circle2.center.y - testObj->Scale_countY;

	// �l�p�`�̏㉺�ɐG�ꂽ�ꍇ�̎l�ӂ̍��W
	float Y_posx1 = 1.4 + circle2.center.y + testObj->Scale_countX;
	float Y_posx2 = -1.4 + circle2.center.y - testObj->Scale_countX;
	float Y_posy1 = 1 + circle2.center.x + testObj->Scale_countX;
	float Y_posy2 = -1 + circle2.center.x - testObj->Scale_countX;

	// �l�p�`�̕ӂɂ��ꂼ��l�̍��W�������
	squre.Left = { X_posx2, X_posy2, X_posx2, X_posy1 };   // ��
	squre.Right = { X_posx1, X_posy2, X_posx1, X_posy1 };  // �E
	squre.Bottom = { Y_posy2, Y_posx2, Y_posy1, Y_posx2 }; // ��
	squre.Top = { Y_posy2, Y_posx1, Y_posy1, Y_posx1 };    // ��

	// �l�p�`�̎l�ӂ�Ԃ�
	return squre;
}

std::vector<Vector2> Game::SetTriangle(BOUNDING_CIRCLE circle1, TestObject* testObj2)
{
	Triangle triangle;
	triangle.A = { 0                                , 0.9f + testObj2->Scale_countY };
	triangle.B = { 1.1f + testObj2->Scale_countX, -0.9f - testObj2->Scale_countY };
	triangle.C = { -1.1f - testObj2->Scale_countX, -0.9f - testObj2->Scale_countY };


	// 1�ڂ̓ʑ��p�`�̒��_���W���`
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
	// �l�p�̉��̎O�p
	squre.A = { width + testObj2->Scale_countX,
				width + testObj2->Scale_countY };
	squre.B = { width + testObj2->Scale_countX,
				-width + -testObj2->Scale_countY };
	squre.C = { -width - testObj2->Scale_countX,
				-width + -testObj2->Scale_countY };
	squre.D = { -width - testObj2->Scale_countX,
				 width + testObj2->Scale_countY };

	// 1�ڂ̓ʑ��p�`�̒��_���W���`
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
	// �l�p�̉��̎O�p
	circle.A = { circle1.center.x , width + circle1.center.y + testObj2->Scale_countY };
	circle.B = { -width + circle1.center.x - testObj2->Scale_countX,circle1.center.y };
	circle.C = { circle1.center.x , -width + circle1.center.y - testObj2->Scale_countY };
	circle.D = { width + circle1.center.x + testObj2->Scale_countX,circle1.center.y };
	return circle;
}

bool Game::isPointInTriangle(Point A, Point B, Point C, Point P)
{
	// �o���A���W�̌v�Z
	float denominator = (B.y - C.y) * (A.x - C.x) + (C.x - B.x) * (A.y - C.y);
	float alpha = ((B.y - C.y) * (P.x - C.x) + (C.x - B.x) * (P.y - C.y)) / denominator;
	float beta = ((C.y - A.y) * (P.x - C.x) + (A.x - C.x) * (P.y - C.y)) / denominator;
	float gamma = 1.0 - alpha - beta;

	// ���W����̊m�F
	return alpha >= 0.0 && alpha <= 1.0 && beta >= 0.0 && beta <= 1.0 && gamma >= 0.0 && gamma <= 1.0;
}

int Game::CheckTriangleHit(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj, TestObject* testObj2)
{
	// �O�p�`�̒��_���W�ƃe�X�g�Ώۂ̓_��ݒ�
	// ���삵�Ă���O�p�`
	testObj->vertices = SetTriangle(circle1, testObj);
	// ���삵�Ă��Ȃ��O�p�`
	testObj2->vertices = SetTriangle(circle2, testObj2);

	// �O�p���m���G��Ă��鎞
	if (TriangleHit(testObj, testObj2))
	{
		if (testObj2->vertices[0].y > circle1.center.y)
		{
			// �E��ɂ���Ƃ�
			if (testObj->vertices[0].x < circle2.center.x)
			{
				// �E
				return 6;
			}
			// ����ɂ���Ƃ�
			else if (testObj->vertices[0].x > circle2.center.x)
			{
				// ��
				return 5;
			}
		}
		// ��ɂ���Ƃ�
		else
		{
			// ��
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
	// �l�p
	for (auto& vertex : testObj2->vertices) {
		vertex.x += circle1.center.x;
		vertex.y += circle1.center.y;
	}

	Triangle2.vertices = testObj2->vertices;

	bool collisionResult = Collide(Triangle1, Triangle2);

	// ���ʂ�\��
	if (collisionResult)
	{
		return true;
	}
	return false;
}

void Game::InitialPolygonSAT(BOUNDING_CIRCLE circle1, TestObject* testObj, float rotation)
{
	//BOUNDING_CIRCLE circle4 = testObj->GetBoundingCircle();// ���삵�Ă��Ȃ��I�u�W�F�N�g 
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
	// �O�p�`�̒��_���W�ƃe�X�g�Ώۂ̓_��ݒ�
	// ���삵�Ă���O�p�`
	testObj->vertices = SetTriangle(circle1, testObj);
	// ���삵�Ă��Ȃ��l�p�`
	testObj2->vertices = SetSqureWithTriangle(circle2, testObj2, SQUREWIDTH);

	// �O�p���m���G��Ă��鎞
	if (TriangleHit(testObj, testObj2))
	{
		if (testObj2->vertices[0].y > circle1.center.y)
		{
			// �E��ɂ���Ƃ�
			if (testObj->vertices[0].x < circle2.center.x)
			{
				// �E
				return 9;
			}
			// ����ɂ���Ƃ�
			else if (testObj->vertices[0].x > circle2.center.x)
			{
				// ��
				return 8;
			}
		}
		// ��ɂ���Ƃ�
		else
		{
			// ��
			return 10;
		}
	}

	return 0;
}

int Game::CheckTriangleAndCircleHit(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj, TestObject* testObj2)
{
	// �O�p�`�̒��_���W�ƃe�X�g�Ώۂ̓_��ݒ�
	std::vector<Vector2> triangle;
	SQURE circle;
	std::vector<Vector2> squre;

	// ���삵�Ă���O�p�`
	triangle = SetTriangle(circle1, testObj);
	squre = SetSqureWithTriangle(circle2, testObj2, TRIANGLEWIDTH);
	circle = SetCircleWithTriangle(circle2, testObj2, SQUREWIDTH);

	// ���S�_
	Point squrecenter = { circle2.center.x ,circle2.center.y };

	////// �����蔻����s��
	//if     (isPointInTriangle(squrecenter, circle.D, squre.C, triangle.A)
	//	||  isPointInTriangle(squrecenter, squre.C, circle.C, triangle.A)
	//	|| (isPointInTriangle(triangle.A, triangle.B, triangle.C, squre.C)))
	//{
	//	// �E
	//	return 8;
	//}
	//else if (isPointInTriangle(squrecenter, circle.B, squre.A, triangle.B)
	//	  || isPointInTriangle(squrecenter, squre.A, circle.C, triangle.B)
	//	  || isPointInTriangle(triangle.A, triangle.B, triangle.C, squre.A))
	//{
	//	// ��
	//	return 9;
	//}
	//// ��
	//else if (isPointInTriangle(circle.B, squre.A, squrecenter, triangle.C)
	//	  || isPointInTriangle(squre.A, circle.C, squrecenter, triangle.C))
	//{
	//	// ��
	//	return 9;
	//}
	//else if (isPointInTriangle(circle.D, squre.C, squrecenter, triangle.C)
	//	  || isPointInTriangle(squre.C, circle.C, squrecenter, triangle.C))
	//{
	//	// �E
	//	return 8;
	//}
	//else if ((isPointInTriangle(circle.B, squre.D, squrecenter, triangle.B)
	//	   || isPointInTriangle(squre.D, circle.A, squrecenter, triangle.B)
	//	   || isPointInTriangle(circle.A, squrecenter, squre.B, triangle.A)
	//	   || isPointInTriangle(squre.B, squrecenter, circle.D, triangle.A)))
	//{
	//	// ��
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
