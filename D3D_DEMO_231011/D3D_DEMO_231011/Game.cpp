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
	testObj->SetObjTex(g_Assets->square, 200, 200, 1, 1);
	testObj->m_objSprite->m_anime = new ObjectAnimation(1, 1);
	testObj->m_objSprite->m_anime->SetAnimeSpeed(0.0f);
	testObj->m_objSprite->m_anime->SetAnimePattern(0);
	testObj->m_objSprite->InitPos(-4, -1.16, 0.2f);
	testObj->isPlayer = true;// �L�[�{�[�h�ő���\

	// �I�u�W�F�N�g2
	testObj2 = new TestObject();
	//�I�u�W�F�N�g�̏����ݒ�
	//testObj2->SetObjTex(g_Assets->testShadow, 200, 200, 1, 1);
	testObj2->SetObjTex(g_Assets->square, 200, 200, 1, 1);//square
	testObj2->m_objSprite->m_anime = new ObjectAnimation(1, 1);
	testObj2->m_objSprite->m_anime->SetAnimeSpeed(0.0f);
	testObj2->m_objSprite->m_anime->SetAnimePattern(0);
	testObj2->m_objSprite->InitPos(5, 0, 0.1f);

	// �I�u�W�F�N�g3
	testObj3 = new TestObject();
	//�I�u�W�F�N�g�̏����ݒ�
	//testObj2->SetObjTex(g_Assets->testShadow, 200, 200, 1, 1);
	testObj3->SetObjTex(g_Assets->testObj, 200, 200, 1, 1);//square
	testObj3->m_objSprite->m_anime = new ObjectAnimation(1, 1);
	testObj3->m_objSprite->m_anime->SetAnimeSpeed(0.0f);
	testObj3->m_objSprite->m_anime->SetAnimePattern(0);
	testObj3->m_objSprite->InitPos(2, 3, 0.1f);
	

	//�e�̏����ݒ�
	//testObj->SetShadowTex(g_Assets->testShadow, 200, 200, 1, 1);
	//testObj->m_shadowSprite->m_anime = new ObjectAnimation(1, 1);
	//testObj->m_shadowSprite->m_anime->SetAnimeSpeed(0.0f);
	//testObj->m_shadowSprite->m_anime->SetAnimePattern(0);
	//testObj->m_shadowSprite->InitPos(1.7, 0.712, 0.2f);


	//�I�u�W�F�N�g������
	testBg = new Object(g_Assets->testbgbox, 1280, 720, 1, 1);
	testBg->m_sprite->m_pos.z = 0.9;//�O��̈ʒu�ݒ���N���X���ōs��
	//�A�j���[�V�����N���X������->�ǂ̃A�j���[�V�����ɂ���
	testBg->m_sprite->m_anime = new ObjectAnimation(1, 1);
	//�A�j���[�V�������x��ݒ�
	testBg->m_sprite->m_anime->SetAnimeSpeed(0.0f);
	//�A�j���[�V�����p�^�[����ݒ�
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
	// �����蔻�菈��
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

	//============ ��������`�揈�� ============//
	
	
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

	//============ �����܂ŕ`�揈�� ============//
	 
	//�_�u���o�b�t�@�̐؂�ւ����s����ʂ��X�V����
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
	BOUNDING_CIRCLE circle1 = testObj->GetBoundingCircle();// ���삵�Ă���I�u�W�F�N�g
	BOUNDING_CIRCLE circle2 = testObj2->GetBoundingCircle();// ���삵�Ă��Ȃ��I�u�W�F�N�g 
	BOUNDING_CIRCLE circle3 = testObj3->GetBoundingCircle();// ���삵�Ă��Ȃ��I�u�W�F�N�g 
	BOUNDING_CIRCLE Combine = circle1;// �~�̍��W���L�^����

	// �����œ����蔻���؂�ւ���
	//�~���m
	//MoveObjects(CircleHit(circle1, circle2), Combine, circle1, circle2);

	if (!testObj3->isPlayer)// �I�u�W�F�N�g���m���G�ꂽ�瓖���蔻�������
	{
		// �~�Ǝl�p
		// SqureandCircle�֐��@�����P�F�~�@�Q�F�l�p 3:�l�p�̃e�N�X�`���������Ă����������
		// MoveObjects�֐��@�����P�F�I�u�W�F�N�g���ǂ��ɓ��������̂��̖߂�l�@�����Q�F���̂����錳�̃I�u�W�F�N�g�̍��W
		// �@�@�@�@�@�@     �����R,�S,�T�FMoveObjects�֐��̈����Ɠ���
		CombineObjects(SqureandCircle(circle1, circle3, testObj3), Combine, circle1, circle3, testObj3);
	}


	if (!testObj2->isPlayer)// �I�u�W�F�N�g���m���G�ꂽ�瓖���蔻�������
	{
		// �l�p�Ǝl�p
		CombineObjects(SqureHit(circle1, circle2), Combine, circle1, circle2, testObj2);
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

int Game::SqureHit(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2)
{
	// �l�p�`���m�̓����蔻��
	if ((circle1.center.x + circle1.radius >= circle2.center.x - circle2.radius) &&
		(circle2.center.x + circle2.radius >= circle1.center.x - circle1.radius) &&
		(circle1.center.y + circle1.radius >= circle2.center.y - circle2.radius) &&
		(circle2.center.y + circle2.radius >= circle1.center.y - circle1.radius))
	{
		// �㉺���E�̓����蔻��ŕʂ̖߂�l��Ԃ�
		return SideCollision(circle1, circle2);
	}
	return 0;
}

void Game::CombineObjects(int HitNum, BOUNDING_CIRCLE Combine, BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj)
{
	switch (HitNum)
	{
	case 1:
		// ��
		// ���삵�Ă���I�u�W�F�N�g�̉��̍��W���v�Z����
		Combine.center.x = circle1.center.x + circle1.radius + circle2.radius;
		// �Ԃ������I�u�W�F�N�g�𑀍삵�Ă���I�u�W�F�N�g�̐^���Ɉړ�������
		testObj->SetBoundingCircle(Combine);
		// ���삵�Ă���I�u�W�F�N�g�Ɠ����悤�Ɉړ�����
		testObj->isPlayer = true;
		break;
	case 2:
		// ��
		// ���삵�Ă���I�u�W�F�N�g�̉��̍��W���v�Z����
		Combine.center.y = circle1.center.y + circle1.radius + circle2.radius;
		// �Ԃ������I�u�W�F�N�g�𑀍삵�Ă���I�u�W�F�N�g�̐^���Ɉړ�������
		testObj->SetBoundingCircle(Combine);
		// ���삵�Ă���I�u�W�F�N�g�Ɠ����悤�Ɉړ�����
		testObj->isPlayer = true;
		break;
	case 3:
		// ��
		// ���삵�Ă���I�u�W�F�N�g�̉��̍��W���v�Z����
		Combine.center.y = circle1.center.y - circle1.radius - circle2.radius;
		// �Ԃ������I�u�W�F�N�g�𑀍삵�Ă���I�u�W�F�N�g�̐^���Ɉړ�������
		testObj->SetBoundingCircle(Combine);
		// ���삵�Ă���I�u�W�F�N�g�Ɠ����悤�Ɉړ�����
		testObj->isPlayer = true;
		break;
	case 4:
		// �E
		// ���삵�Ă���I�u�W�F�N�g�̉��̍��W���v�Z����
		Combine.center.x = circle1.center.x - circle1.radius - circle2.radius;
		// �Ԃ������I�u�W�F�N�g�𑀍삵�Ă���I�u�W�F�N�g�̐^���Ɉړ�������
		testObj->SetBoundingCircle(Combine);
		// ���삵�Ă���I�u�W�F�N�g�Ɠ����悤�Ɉړ�����
		testObj->isPlayer = true;
		break;
	default:
		// �������Ă��Ȃ�
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