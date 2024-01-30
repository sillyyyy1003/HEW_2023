#include "Assets.h"
#include "ObjectAnimation.h"

#include "ObjectCollision.h"
#include <algorithm> // �K�v�ȃw�b�_�[�t�@�C��
#define SQUREWIDTH 1.2
#define CIRCLEWIDTH 0.8
#define TRIANGLEWIDTH 0.8
#define M_PI 3.14159265358979323846

extern Assets* g_Assets;

ObjectCollision::ObjectCollision()
{
	// �I�u�W�F�N�g1
	pObj = new TestObject();
	// �I�u�W�F�N�g�̉摜��ݒ�
	pObj->object = SQUARE;
	//�I�u�W�F�N�g�̏����ݒ�
	pObj->SetObjTex(g_Assets->square, 200, 200, 1, 1);
	pObj->m_objSprite->m_anime = new ObjectAnimation(1, 1);
	pObj->m_objSprite->m_anime->SetAnimeSpeed(0.0f);
	pObj->m_objSprite->m_anime->SetAnimePattern(0);
	pObj->m_objSprite->InitPos(-4, -1.16, 0.2f);
	DirectX::XMFLOAT3 rotation = pObj->m_objSprite->m_rotation;
	pObj->isPlayer = true;// �L�[�{�[�h�ő���\
	pObj->vertices = SetTriangle(pObj);

	// �I�u�W�F�N�g2
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

	// �I�u�W�F�N�g3
	circle = new TestObject();
	circle->object = CIRCLE;
	//�I�u�W�F�N�g�̏����ݒ�
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
	// �����蔻��
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

// ---�}�`�̓����蔻��--- //
void ObjectCollision::objectCollision()
{
	// ���_���W��\���p
	//ex->m_objSprite->InitPos(circle->vertices[0].x, circle->vertices[0].y, 0.1f);
	//ex1->m_objSprite->InitPos(circle->vertices[1].x, circle->vertices[1].y, 0.1f);
	//ex2->m_objSprite->InitPos(circle->vertices[2].x, circle->vertices[2].y, 0.1f);
	//ex3->m_objSprite->InitPos(circle->vertices[3].x, circle->vertices[3].y, 0.1f);

	//--------------------------------------------------------//
	//--- ���������삷��}�`�ɂ���ē����蔻���؂�ւ��� ---//
	//--------------------------------------------------------//

	if (pObj->object == SQUARE)
	{
		/// ���F���������삵�Ă���}�`�@���F���삵�Ă��Ȃ������蔻��̑ΏۂƂȂ�}�`
		/// <summary>
		/// ���F�l�p�@�̏ꍇ�̓����蔻��
		/// </summary>
		if (!circle->isPlayer)// �I�u�W�F�N�g���m���G�ꂽ�瓖���蔻�������
		{
			// ���F�l�p�@���F�~
			CombineObjects(SquareHit(pObj, circle), pObj, circle);

			// ���}�`�ɍ��̂����}�`�ɂ������蔻���t���邽�߂̓����蔻��@ �~�Ǝl�p
			// ���F�l�p�@���F�~
			//CombineObjects(SquareHit(square, circle), square, circle);
		}
		if (!square->isPlayer)// �I�u�W�F�N�g���m���G�ꂽ�瓖���蔻�������
		{
			// ���F�l�p�@���F�l�p
			CombineObjects(SquareHit(pObj, square), pObj, square);

			// ���}�`�ɍ��̂����}�`�ɂ������蔻���t���邽�߂̓����蔻��A �~�Ǝl�p
			// ���F�~�@���F�l�p
			//CombineObjects(CircleHit(circle, square),circle,square);
		}
		if (!triangle->isPlayer)
		{
			// ���F�l�p�@���F�O�p
			CombineObjects(SquareHit(pObj, triangle), pObj, triangle);
		}
	}
	else if (pObj->object == CIRCLE)
	{
		/// <summary>
		/// ���F�~�@�̏ꍇ�̓����蔻��
		/// </summary>
		if (!circle->isPlayer)// �I�u�W�F�N�g���m���G�ꂽ�瓖���蔻�������
		{
			// ���F�~�@���F�~
			CombineObjects(CircleHit(pObj, circle), pObj, circle);
		}
		if (!square->isPlayer)// �I�u�W�F�N�g���m���G�ꂽ�瓖���蔻�������
		{
			// ���F�~�@���F�l�p
			CombineObjects(CircleHit(pObj, square), pObj, square);
		}
		if (!triangle->isPlayer)
		{
			// ���F�~�@���F�O�p
			CombineObjects(CircleHit(pObj, triangle), pObj, triangle);
		}
	}
	else if (pObj->object == TRIANGLE)
	{
		/// <summary>
		/// ���F�O�p�@�̏ꍇ�̓����蔻��
		/// </summary>
		if (!circle->isPlayer)// �I�u�W�F�N�g���m���G�ꂽ�瓖���蔻�������
		{
			// ���F�O�p�@���F�~
			CombineTriangleAndCircleObjects(TriangleHit(pObj, circle), pObj, circle);
		}
		if (!square->isPlayer)// �I�u�W�F�N�g���m���G�ꂽ�瓖���蔻�������
		{
			// ���F�O�p�@���F�l�p
			CombineTriangleAndSqureObjects(TriangleHit(pObj, square), pObj, square);

			// ���}�`�ɍ��̂����}�`�ɂ������蔻���t���邽�߂̓����蔻��@ �O�p�Ǝl�p
			// ���F�O�p�@���F�l�p
			//CombineTriangleObjects(TriangleHit(triangle, square), triangle, square);
		}
		if (!triangle->isPlayer)
		{
			// ���F�O�p�@���F�O�p
			CombineTriangleObjects(TriangleHit(pObj, triangle), pObj, triangle);

			// ���}�`�ɍ��̂����}�`�ɂ������蔻���t���邽�߂̓����蔻��A �O�p�Ǝl�p
			// ���F�l�p�@���F�O�p
			//CombineObjects(SquareHit(square, triangle), square,triangle);
		}
	}
}
//------------------------//

// ---�}�`���m���G�ꂽ���̏���--- //
void ObjectCollision::CombineObjects(int HitNum, TestObject* pObj, TestObject* eObj)
{
	// ���삵�Ă��Ȃ��}�`�̒��_���W���擾����
	std::vector<Vector2> Combineobj = eObj->vertices;
	// ���삵�Ă���}�`�̍��W���L�^����
	BOUNDING_CIRCLE Combine = pObj->GetBoundingCircle();
	// ���삵�Ă��Ȃ��}�`�̍��W���L�^����
	BOUNDING_CIRCLE Combine2 = eObj->GetBoundingCircle();
	// �}�`�̊p�x�ς��邽�߂̕ϐ�
	DirectX::XMFLOAT3 rotation = pObj->m_objSprite->m_rotation;
	DirectX::XMFLOAT3 rotation2 = eObj->m_objSprite->m_rotation;

	switch (HitNum)
	{
	case 1:
		// ��
		rotation2.z = 0;
		eObj->SetRotation(rotation2);
		// �}�`�̊p�x���ς���Ă����ꍇ�����l�ɂ���
		Combineobj = eObj->vertices;
		// ���삵�Ă���I�u�W�F�N�g�̉��̍��W���v�Z����
		Combine.center.x = Combine.center.x + Combine.radius + Combine2.radius;
		if (eObj->object == TRIANGLE)
		{
			Combine.center.y = Combine.center.y + Combine2.radius / 2;
		}
		// �Ԃ������I�u�W�F�N�g�𑀍삵�Ă���I�u�W�F�N�g�̐^���Ɉړ�������
		eObj->SetBoundingCircle(Combine);
		// ���삵�Ă��Ȃ��}�`�̂��ꂼ��̌`�ɂ����������������
		if (eObj->object == SQUARE)
		{
			// ���삵�Ă��Ȃ��l�p�`
			eObj->vertices = SetSquare(eObj, SQUREWIDTH);
			InitialPolygonSAT(eObj->GetBoundingCircle(), eObj, 0);
		}
		else if (eObj->object == TRIANGLE)
		{
			// ���삵�Ă��Ȃ��l�p�`
			eObj->vertices = SetTriangle(eObj);
			InitialPolygonSAT(eObj->GetBoundingCircle(), eObj, M_PI / 12);
			rotation2.z = 30 + rotation.z;
			eObj->SetRotation(rotation2);
		}
		else if (eObj->object == CIRCLE)
		{
			// ���삵�Ă��Ȃ��~
			eObj->vertices = SetCircle(eObj, CIRCLEWIDTH, SQUREWIDTH);
			InitialPolygonSAT(eObj->GetBoundingCircle(), eObj, 0);
		}
		// ���삵�Ă���I�u�W�F�N�g�Ɠ����悤�Ɉړ�����
		eObj->isPlayer = true;
		break;
	case 2:
		// ��
		rotation2.z = 0;
		eObj->SetRotation(rotation2);
		if (eObj->object == TRIANGLE)
		{
			Combine.center.y = Combine.center.y + Combine.radius + Combine2.radius * 2;
		}
		else
		{
			// ���삵�Ă���I�u�W�F�N�g�̉��̍��W���v�Z����
			Combine.center.y = Combine.center.y + Combine.radius + Combine2.radius;
		}
		// �Ԃ������I�u�W�F�N�g�𑀍삵�Ă���I�u�W�F�N�g�̐^���Ɉړ�������
		eObj->SetBoundingCircle(Combine);
		// ���삵�Ă��Ȃ��}�`�̂��ꂼ��̌`�ɂ����������������
		if (eObj->object == SQUARE)
		{
			// ���삵�Ă��Ȃ��l�p�`
			eObj->vertices = SetSquare(eObj, SQUREWIDTH);
		}
		else if (eObj->object == TRIANGLE)
		{
			// ���삵�Ă��Ȃ��l�p�`
			eObj->vertices = SetTriangle(eObj);
		}
		else if (eObj->object == CIRCLE)
		{
			// ���삵�Ă��Ȃ��~
			eObj->vertices = SetCircle(eObj, CIRCLEWIDTH, SQUREWIDTH);
		}
		InitialPolygonSAT(eObj->GetBoundingCircle(), eObj, 0);
		// ���삵�Ă���I�u�W�F�N�g�Ɠ����悤�Ɉړ�����
		eObj->isPlayer = true;
		break;
	case 3:
		// ��
		rotation2.z = 0;
		eObj->SetRotation(rotation2);
		// ���삵�Ă���I�u�W�F�N�g�̉��̍��W���v�Z����
		Combine.center.y = Combine.center.y - Combine.radius - Combine2.radius;
		if (eObj->object == TRIANGLE)
		{
			Combine.center.x = Combine.center.x - Combine2.radius / 2;
		}
		// �Ԃ������I�u�W�F�N�g�𑀍삵�Ă���I�u�W�F�N�g�̐^���Ɉړ�������
		eObj->SetBoundingCircle(Combine);
		// ���삵�Ă��Ȃ��}�`�̂��ꂼ��̌`�ɂ����������������
		if (eObj->object == SQUARE)
		{
			// ���삵�Ă��Ȃ��l�p�`
			eObj->vertices = SetSquare(eObj, SQUREWIDTH);
			InitialPolygonSAT(eObj->GetBoundingCircle(), eObj, 0);
		}
		else if (eObj->object == TRIANGLE)
		{
			// ���삵�Ă��Ȃ��l�p�`
			eObj->vertices = SetTriangle(eObj);
			InitialPolygonSAT(eObj->GetBoundingCircle(), eObj, M_PI / 6);
			rotation2.z = 60 + rotation.z;
			eObj->SetRotation(rotation2);
		}
		else if (eObj->object == CIRCLE)
		{
			// ���삵�Ă��Ȃ��~
			eObj->vertices = SetCircle(eObj, CIRCLEWIDTH, SQUREWIDTH);
			InitialPolygonSAT(eObj->GetBoundingCircle(), eObj, 0);
		}
		// ���삵�Ă���I�u�W�F�N�g�Ɠ����悤�Ɉړ�����
		eObj->isPlayer = true;
		break;
	case 4:
		// �E
		rotation2.z = 0;
		eObj->SetRotation(rotation2);
		// ���삵�Ă���I�u�W�F�N�g�̉��̍��W���v�Z����
		Combine.center.x = Combine.center.x - Combine.radius - Combine2.radius;
		if (eObj->object == TRIANGLE)
		{
			Combine.center.y = Combine.center.y + Combine2.radius / 2;
		}
		// �Ԃ������I�u�W�F�N�g�𑀍삵�Ă���I�u�W�F�N�g�̐^���Ɉړ�������
		eObj->SetBoundingCircle(Combine);
		// ���삵�Ă��Ȃ��}�`�̂��ꂼ��̌`�ɂ����������������
		if (eObj->object == SQUARE)
		{
			// ���삵�Ă��Ȃ��l�p�`
			eObj->vertices = SetSquare(eObj, SQUREWIDTH);
			InitialPolygonSAT(eObj->GetBoundingCircle(), eObj, 0);
		}
		else if (eObj->object == TRIANGLE)
		{
			// ���삵�Ă��Ȃ��l�p�`
			eObj->vertices = SetTriangle(eObj);
			InitialPolygonSAT(eObj->GetBoundingCircle(), eObj, -M_PI / 12);
			rotation2.z = -30 + rotation.z;
			eObj->SetRotation(rotation2);
		}
		else if (eObj->object == CIRCLE)
		{
			// ���삵�Ă��Ȃ��~
			eObj->vertices = SetCircle(eObj, CIRCLEWIDTH, SQUREWIDTH);
			InitialPolygonSAT(eObj->GetBoundingCircle(), eObj, 0);
		}
		// ���삵�Ă���I�u�W�F�N�g�Ɠ����悤�Ɉړ�����
		eObj->isPlayer = true;
		break;
	default:
		// �������Ă��Ȃ�
		break;
	}
}

void ObjectCollision::CombineTriangleObjects(int HitNum, TestObject* pObj, TestObject* eObj)
{
	std::vector<Vector2> Combineobj = eObj->vertices;// �O�p�̍��W���擾����
	BOUNDING_CIRCLE Combine = pObj->GetBoundingCircle();// �~�̍��W���L�^����
	BOUNDING_CIRCLE Combine2 = eObj->GetBoundingCircle();// �~�̍��W���L�^����
	DirectX::XMFLOAT3 rotation = pObj->m_objSprite->m_rotation;
	DirectX::XMFLOAT3 rotation2 = eObj->m_objSprite->m_rotation;

	switch (HitNum)
	{
		//�[�[�[�O�p�`�̃I�u�W�F�N�g�̍��́[�[�[

	case 5:
		// ��
		// ���삵�Ă���I�u�W�F�N�g�̉��̍��W���v�Z����
		// �}�`���ړ����Ă����ꍇ�����l�ɂ���
		eObj->m_objSprite->InitPos(0, 0, 0.1f);
		eObj->vertices = SetTriangle(eObj);
		// �}�`�̊p�x���ς���Ă����ꍇ�����l�ɂ���
		eObj->rotation = 0;
		// �}�`�̈ړ���������ɐ}�`�̉�]������
		Combineobj = eObj->vertices;
		Combineobj = InitialPolygonSATvertices(eObj->GetBoundingCircle(), Combineobj, M_PI / 6.0f - eObj->rotation);
		Combine2.center.x = -Combineobj[1].x / 1.6 + Combine.center.x;
		Combine2.center.y = -Combineobj[2].y / 2.9 + Combine.center.y;
		InitialPolygonSAT(Combine2, eObj, -M_PI / 6.0f - eObj->rotation);//32
		// �Ԃ������I�u�W�F�N�g�𑀍삵�Ă���I�u�W�F�N�g�̐^���Ɉړ�������
		eObj->m_objSprite->InitPos(Combine2.center.x, Combine2.center.y, 0.1f);
		rotation2.z = -60 + rotation.z;
		eObj->SetRotation(rotation2);
		// ���삵�Ă���I�u�W�F�N�g�Ɠ����悤�Ɉړ�����
		eObj->isPlayer = true;
		break;
	case 6:
		// �E
		// ���삵�Ă���I�u�W�F�N�g�̉��̍��W���v�Z����
		eObj->m_objSprite->InitPos(0, 0, 0.1f);
		eObj->vertices = SetTriangle(eObj);
		eObj->rotation = 0;
		Combineobj = eObj->vertices;
		Combineobj = InitialPolygonSATvertices(eObj->GetBoundingCircle(), Combineobj, M_PI / 6.0f - eObj->rotation);
		Combine2.center.x = Combineobj[1].x / 1.6 + Combine.center.x;
		Combine2.center.y = -Combineobj[2].y / 2.9 + Combine.center.y;
		InitialPolygonSAT(Combine2, eObj, M_PI / 6.0f - eObj->rotation);
		// �Ԃ������I�u�W�F�N�g�𑀍삵�Ă���I�u�W�F�N�g�̐^���Ɉړ�������
		eObj->m_objSprite->InitPos(Combine2.center.x, Combine2.center.y, 0.1f);
		rotation2.z = 60 + rotation.z;
		eObj->SetRotation(rotation2);
		// ���삵�Ă���I�u�W�F�N�g�Ɠ����悤�Ɉړ�����
		eObj->isPlayer = true;
		break;
	case 7:
		// ��
		// ���삵�Ă���I�u�W�F�N�g�̉��̍��W���v�Z����
		eObj->m_objSprite->InitPos(0, 0, 0.1f);
		eObj->vertices = SetTriangle(eObj);
		eObj->rotation = 0;
		Combineobj = eObj->vertices;
		Combineobj = InitialPolygonSATvertices(eObj->GetBoundingCircle(), Combineobj, M_PI / 2.0f - eObj->rotation);
		Combine2.center.x = Combine.center.x;
		Combine2.center.y = -Combineobj[2].y * 2.15 + Combine.center.y;
		InitialPolygonSAT(Combine2, eObj, M_PI / 2.0f - eObj->rotation);
		// �Ԃ������I�u�W�F�N�g�𑀍삵�Ă���I�u�W�F�N�g�̐^���Ɉړ�������
		eObj->m_objSprite->InitPos(Combine2.center.x, Combine2.center.y, 0.1f);
		rotation2.z = 180 + rotation.z;
		eObj->SetRotation(rotation2);
		// ���삵�Ă���I�u�W�F�N�g�Ɠ����悤�Ɉړ�����
		eObj->isPlayer = true;
		break;
	}
}

void ObjectCollision::CombineTriangleAndSqureObjects(int HitNum, TestObject* pObj, TestObject* eObj)
{
	std::vector<Vector2> Combineobj = eObj->vertices;// �~�̍��W���L�^����
	BOUNDING_CIRCLE Combine = pObj->GetBoundingCircle();// �~�̍��W���L�^����
	BOUNDING_CIRCLE Combine2 = eObj->GetBoundingCircle();// �~�̍��W���L�^����
	DirectX::XMFLOAT3 rotation = pObj->m_objSprite->m_rotation;
	DirectX::XMFLOAT3 rotation2 = eObj->m_objSprite->m_rotation;

	//	// �[�[�[�l�p�ƎO�p�[�[�[
	switch (HitNum)
	{
	case 5:
		// ��
		// ���삵�Ă���I�u�W�F�N�g�̉��̍��W���v�Z����
		// �}�`���ړ����Ă����ꍇ�����l�ɂ���
		eObj->m_objSprite->InitPos(0, 0, 0.1f);
		eObj->vertices = SetSquare(eObj, SQUREWIDTH);
		// �}�`�̊p�x���ς���Ă����ꍇ�����l�ɂ���
		eObj->rotation = 0;
		// �}�`�̈ړ���������ɐ}�`�̉�]������
		Combineobj = eObj->vertices;
		Combineobj = InitialPolygonSATvertices(eObj->GetBoundingCircle(), Combineobj, M_PI / 12.0f - eObj->rotation);
		Combine2.center.x = -Combineobj[1].x / 0.98 + Combine.center.x;
		Combine2.center.y = -Combineobj[2].y / 2.5 + Combine.center.y;
		InitialPolygonSAT(Combine2, eObj, -M_PI / 12.0f - eObj->rotation);//32
		// �Ԃ������I�u�W�F�N�g�𑀍삵�Ă���I�u�W�F�N�g�̐^���Ɉړ�������
		eObj->m_objSprite->InitPos(Combine2.center.x, Combine2.center.y, 0.1f);
		rotation2.z = -30 + rotation.z;
		eObj->SetRotation(rotation2);
		// ���삵�Ă���I�u�W�F�N�g�Ɠ����悤�Ɉړ�����
		eObj->isPlayer = true;
		break;
	case 6:
		//// �E
		// ���삵�Ă���I�u�W�F�N�g�̉��̍��W���v�Z����
		// �}�`���ړ����Ă����ꍇ�����l�ɂ���
		eObj->m_objSprite->InitPos(0, 0, 0.1f);
		eObj->vertices = SetSquare(eObj, SQUREWIDTH);
		// �}�`�̊p�x���ς���Ă����ꍇ�����l�ɂ���
		eObj->rotation = 0;
		// �}�`�̈ړ���������ɐ}�`�̉�]������
		Combineobj = eObj->vertices;
		Combineobj = InitialPolygonSATvertices(eObj->GetBoundingCircle(), Combineobj, M_PI / 12.0f - eObj->rotation);
		Combine2.center.x = Combineobj[1].x / 0.98 + Combine.center.x;
		Combine2.center.y = -Combineobj[2].y / 2.5 + Combine.center.y;
		InitialPolygonSAT(Combine2, eObj, M_PI / 12.0f - eObj->rotation);//32
		// �Ԃ������I�u�W�F�N�g�𑀍삵�Ă���I�u�W�F�N�g�̐^���Ɉړ�������
		eObj->m_objSprite->InitPos(Combine2.center.x, Combine2.center.y, 0.1f);
		rotation2.z = 30 + rotation.z;
		eObj->SetRotation(rotation2);
		// ���삵�Ă���I�u�W�F�N�g�Ɠ����悤�Ɉړ�����
		eObj->isPlayer = true;
		break;
	case 7:
		// ��
		// ���삵�Ă���I�u�W�F�N�g�̉��̍��W���v�Z����
		eObj->m_objSprite->InitPos(0, 0, 0.1f);
		eObj->vertices = SetSquare(eObj, SQUREWIDTH);
		eObj->rotation = 0;
		Combineobj = eObj->vertices;
		Combineobj = InitialPolygonSATvertices(eObj->GetBoundingCircle(), Combineobj, M_PI / 2.0f - eObj->rotation);
		Combine2.center.x = Combine.center.x;
		Combine2.center.y = -Combineobj[2].y * 1.89f + Combine.center.y;
		InitialPolygonSAT(Combine2, eObj, M_PI / 2.0f - eObj->rotation);
		// �Ԃ������I�u�W�F�N�g�𑀍삵�Ă���I�u�W�F�N�g�̐^���Ɉړ�������
		eObj->m_objSprite->InitPos(Combine2.center.x, Combine2.center.y, 0.1f);
		rotation2.z = 180 + rotation.z;
		eObj->SetRotation(rotation2);
		// ���삵�Ă���I�u�W�F�N�g�Ɠ����悤�Ɉړ�����
		eObj->isPlayer = true;
		break;
	}
}

void ObjectCollision::CombineTriangleAndCircleObjects(int HitNum, TestObject* pObj, TestObject* eObj)
{
	std::vector<Vector2> Combineobj = eObj->vertices;// �~�̍��W���L�^����
	BOUNDING_CIRCLE Combine = pObj->GetBoundingCircle();// �~�̍��W���L�^����
	BOUNDING_CIRCLE Combine2 = eObj->GetBoundingCircle();// �~�̍��W���L�^����
	DirectX::XMFLOAT3 rotation = pObj->m_objSprite->m_rotation;
	DirectX::XMFLOAT3 rotation2 = eObj->m_objSprite->m_rotation;

	//	// �[�[�[�~�ƎO�p�[�[�[
	switch (HitNum)
	{
	case 5:
		// ��
		// ���삵�Ă���I�u�W�F�N�g�̉��̍��W���v�Z����
		// �}�`���ړ����Ă����ꍇ�����l�ɂ���
		eObj->m_objSprite->InitPos(0, 0, 0.1f);
		eObj->vertices = SetCircle(eObj, CIRCLEWIDTH, SQUREWIDTH);
		// �}�`�̊p�x���ς���Ă����ꍇ�����l�ɂ���
		eObj->rotation = 0;
		// �}�`�̈ړ���������ɐ}�`�̉�]������
		Combineobj = eObj->vertices;
		Combineobj = InitialPolygonSATvertices(eObj->GetBoundingCircle(), Combineobj, M_PI / 12.0f - eObj->rotation);
		Combine2.center.x = -Combineobj[3].x / 0.65 + Combine.center.x;
		Combine2.center.y = -Combineobj[5].y / 1.7 + Combine.center.y;
		InitialPolygonSAT(Combine2, eObj, -M_PI / 12.0f - eObj->rotation);//32
		// �Ԃ������I�u�W�F�N�g�𑀍삵�Ă���I�u�W�F�N�g�̐^���Ɉړ�������
		eObj->m_objSprite->InitPos(Combine2.center.x, Combine2.center.y, 0.1f);
		rotation2.z = -30 + rotation.z;
		eObj->SetRotation(rotation2);
		// ���삵�Ă���I�u�W�F�N�g�Ɠ����悤�Ɉړ�����
		eObj->isPlayer = true;
		break;
	case 6:
		//// �E
		// ���삵�Ă���I�u�W�F�N�g�̉��̍��W���v�Z����
		// �}�`���ړ����Ă����ꍇ�����l�ɂ���
		eObj->m_objSprite->InitPos(0, 0, 0.1f);
		eObj->vertices = SetCircle(eObj, CIRCLEWIDTH, SQUREWIDTH);
		// �}�`�̊p�x���ς���Ă����ꍇ�����l�ɂ���
		eObj->rotation = 0;
		// �}�`�̈ړ���������ɐ}�`�̉�]������
		Combineobj = eObj->vertices;
		Combineobj = InitialPolygonSATvertices(eObj->GetBoundingCircle(), Combineobj, M_PI / 12.0f - eObj->rotation);
		Combine2.center.x = Combineobj[3].x / 0.65 + Combine.center.x;
		Combine2.center.y = -Combineobj[5].y / 1.7 + Combine.center.y;
		InitialPolygonSAT(Combine2, eObj, M_PI / 12.0f - eObj->rotation);//32
		// �Ԃ������I�u�W�F�N�g�𑀍삵�Ă���I�u�W�F�N�g�̐^���Ɉړ�������
		eObj->m_objSprite->InitPos(Combine2.center.x, Combine2.center.y, 0.1f);
		rotation2.z = 30 + rotation.z;
		eObj->SetRotation(rotation2);
		// ���삵�Ă���I�u�W�F�N�g�Ɠ����悤�Ɉړ�����
		eObj->isPlayer = true;
		break;
	case 7:
		// ��
		// ���삵�Ă���I�u�W�F�N�g�̉��̍��W���v�Z����
		eObj->m_objSprite->InitPos(0, 0, 0.1f);
		eObj->vertices = SetCircle(eObj, CIRCLEWIDTH, SQUREWIDTH);
		eObj->rotation = 0;
		Combineobj = eObj->vertices;
		Combineobj = InitialPolygonSATvertices(eObj->GetBoundingCircle(), Combineobj, M_PI / 2.0f - eObj->rotation);
		Combine2.center.x = Combine.center.x;
		Combine2.center.y = -Combineobj[5].y * 2.8f + Combine.center.y;
		InitialPolygonSAT(Combine2, eObj, M_PI / 2.0f - eObj->rotation);
		// �Ԃ������I�u�W�F�N�g�𑀍삵�Ă���I�u�W�F�N�g�̐^���Ɉړ�������
		eObj->m_objSprite->InitPos(Combine2.center.x, Combine2.center.y, 0.1f);
		rotation2.z = 180 + rotation.z;
		eObj->SetRotation(rotation2);
		// ���삵�Ă���I�u�W�F�N�g�Ɠ����悤�Ɉړ�����
		eObj->isPlayer = true;
		break;
	}
}
//--------------------------------//

// ---�}�`�ɂ���ē����蔻���ς���--- //
int ObjectCollision::CircleHit(TestObject* pObj, TestObject* eObj)
{
	// �O�p�`�̒��_���W�ƃe�X�g�Ώۂ̓_��ݒ�
	// ���삵�Ă���l�p�`
	pObj->vertices = SetCircle(pObj, CIRCLEWIDTH, SQUREWIDTH);
	pObj->jodgevertices = SetSquare(pObj, SQUREWIDTH);
	int j = 0;
	for (auto& jodgevertices : pObj->jodgevertices)
	{
		jodgevertices = pObj->vertices[j];
		j += 2;
	}

	// ���삵�Ă��Ȃ��}�`�̂��ꂼ��̌`�ɂ����������������
	if (eObj->object == SQUARE)
	{
		// ���삵�Ă��Ȃ��l�p�`
		eObj->vertices = SetSquare(eObj, SQUREWIDTH);
		eObj->jodgevertices = SetSquare(eObj, SQUREWIDTH);
		int j = 0;
		for (auto& jodgevertices : eObj->jodgevertices)
		{
			jodgevertices = eObj->vertices[j];
			j++;
		}
		// �O�p�Ɖ~���G��Ă��鎞
		return SqureAndCircleCollision(pObj, eObj);
	}
	if (eObj->object == TRIANGLE)
	{
		// ���삵�Ă��Ȃ��l�p�`
		eObj->vertices = SetTriangle(eObj);
		eObj->jodgevertices = SetTriangle(eObj);
		int j = 0;
		for (auto& jodgevertices : eObj->jodgevertices)
		{
			jodgevertices = eObj->vertices[j];
			j++;
		}

		// �O�p�Ɖ~���G��Ă��鎞
		return SqureAndCircleCollision(pObj, eObj);
	}
	if (eObj->object == CIRCLE)
	{
		// ���삵�Ă��Ȃ��~
		eObj->vertices = SetCircle(eObj, CIRCLEWIDTH, SQUREWIDTH);
		eObj->jodgevertices = SetSquare(eObj, SQUREWIDTH);
		int j = 0;
		for (auto& jodgevertices : eObj->jodgevertices)
		{
			jodgevertices = eObj->vertices[j];
			j += 2;
		}
		// �O�p�Ɖ~���G��Ă��鎞
		return SqureAndCircleCollision(pObj, eObj);
	}
}

int ObjectCollision::SquareHit(TestObject* pObj, TestObject* eObj)
{
	// �O�p�`�̒��_���W�ƃe�X�g�Ώۂ̓_��ݒ�
	// ���삵�Ă���l�p�`
	pObj->vertices = SetSquare(pObj, SQUREWIDTH);
	pObj->jodgevertices = pObj->vertices;

	// ���삵�Ă��Ȃ��}�`�̂��ꂼ��̌`�ɂ����������������
	if (eObj->object == SQUARE)
	{
		// ���삵�Ă��Ȃ��l�p�`
		eObj->vertices = SetSquare(eObj, SQUREWIDTH);
		eObj->jodgevertices = eObj->vertices;

		// �O�p�Ɖ~���G��Ă��鎞
		return SqureCollision(pObj, eObj);
	}
	if (eObj->object == TRIANGLE)
	{
		// ���삵�Ă��Ȃ��l�p�`
		eObj->vertices = SetTriangle(eObj);
		eObj->jodgevertices = SetSquare(eObj, SQUREWIDTH);

		// �O�p�Ɖ~���G��Ă��鎞
		return SqureCollision(pObj, eObj);
	}
	if (eObj->object == CIRCLE)
	{
		// ���삵�Ă��Ȃ��~
		eObj->vertices = SetCircle(eObj, CIRCLEWIDTH, SQUREWIDTH);

		eObj->jodgevertices = SetSquare(eObj, SQUREWIDTH);
		int j = 0;
		for (auto& jodgevertices : eObj->jodgevertices)
		{
			jodgevertices = eObj->vertices[j];
			j += 2;
		}

		// �O�p�Ɖ~���G��Ă��鎞
		return SqureAndCircleCollision(pObj, eObj);
	}
}

int ObjectCollision::TriangleHit(TestObject* pObj, TestObject* eObj)
{
	// �O�p�`�̒��_���W�ƃe�X�g�Ώۂ̓_��ݒ�
	// ���삵�Ă���O�p�`
	pObj->vertices = SetTriangle(pObj);

	// ���삵�Ă��Ȃ��}�`�̂��ꂼ��̌`�ɂ����������������
	if (eObj->object == SQUARE)
	{
		// ���삵�Ă��Ȃ��l�p�`
		eObj->vertices = SetSquare(eObj, SQUREWIDTH);
	}
	if (eObj->object == TRIANGLE)
	{
		// ���삵�Ă��Ȃ��O�p�`
		eObj->vertices = SetTriangle(eObj);
	}
	if (eObj->object == CIRCLE)
	{
		// ���삵�Ă��Ȃ��l�p�`
		eObj->vertices = SetCircle(eObj, CIRCLEWIDTH, SQUREWIDTH);
	}

	// �O�p���m���G��Ă��鎞
	return TriangleCollision(pObj, eObj);
}
//-------------------------------------//

// ---�}�`�̓����蔻��̏��� ---//
bool ObjectCollision::SATHit(TestObject* pObj, TestObject* eObj)
{
	PolygonSAT Triangle1(pObj->vertices, pObj->rotation);
	PolygonSAT Triangle2(eObj->vertices, eObj->rotation);

	pObj->vertices = Triangle1.GetRotatedVertices();
	eObj->vertices = Triangle2.GetRotatedVertices();

	BOUNDING_CIRCLE circle1 = pObj->GetBoundingCircle();
	BOUNDING_CIRCLE circle2 = eObj->GetBoundingCircle();
	// �l�p
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

	// ���ʂ�\��
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
		// ���삵�Ă��Ȃ��l�p�`
		p_verticies = SetSquare(pObj, SQUREWIDTH);
	}
	else if (eObj->object == TRIANGLE)
	{
		if (eObj->rotation >= 0)
		{
			// ���삵�Ă��Ȃ��l�p�`
			p_verticies = SetSquare(pObj, 0.9);//1.16 �㉺���E�̔��肪������������
		}
		else
		{
			// ���삵�Ă��Ȃ��l�p�`
			p_verticies = SetSquare(pObj, 1.1);//1.16 �㉺���E�̔��肪������������
		}

	}
	p_verticies = InitialPolygonSATvertices(pObj->GetBoundingCircle(), p_verticies, pObj->rotation);

	// �O�p���m���G��Ă��鎞
	if (SATHit(pObj, eObj))
	{
		// �}�`����]�����Ƃ��̍��W�̕ϊ�
		if (eObj->rotation < 0)
		{
			// �}�`�̊p�x��180�x�����̎��̍��W
			RotationJodge = 0;

		}
		else if (eObj->rotation < M_PI / 2)
		{
			// �}�`�̊p�x��180�x�ȏ�̎��̍��W
			RotationJodge = 2;
		}
		else
		{
			// �}�`�̊p�x��180�x�����̎��̍��W
			RotationJodge = 0;
		}

		eObj->jodgevertices = InitialPolygonSATvertices(eObj->GetBoundingCircle(), eObj->jodgevertices, eObj->rotation);

		// �l�p�`���㉺�̂ǂ��炩����Ԃ��������ɍ��E�̓����蔻�肪�@�\���Ȃ��悤�ɂ��邽�߂̏���
		if (p_verticies[0].y > eObj->jodgevertices[0 + RotationJodge].y
			&& p_verticies[2].y < eObj->jodgevertices[2 - RotationJodge].y
			&& eObj->p_verticies2[0].y > eObj->jodgevertices[0 + RotationJodge].y
			&& eObj->p_verticies2[2].y < eObj->jodgevertices[2 - RotationJodge].y)
		{
			// ���E
			// �l�p�`�ɓ����钼�O�ɉE�����ɓ��͂���Ă��邩
			if (circle1.center.x < circle2.center.x && eObj->p_center.center.x < circle1.center.x)
			{
				// �l�p�`�̍����ɉ~���G�ꂽ�ꍇ�̓����蔻��
				if (pObj->vertices[2].x < eObj->vertices[1].x)// ��
				{
					return 1;
				}
			}
			// �l�p�`�ɓ����钼�O�ɍ������ɓ��͂���Ă��邩
			else if (circle1.center.x > circle2.center.x && eObj->p_center.center.x > circle1.center.x)
			{
				// �l�p�`�̉E���ɉ~���G�ꂽ�ꍇ�̓����蔻��
				if (pObj->vertices[1].x > eObj->vertices[2].x)// �E
				{
					return 4;
				}
			}
		}
		// �㉺
		// �l�p�`�ɓ����钼�O�ɉ������ɓ��͂���Ă��邩
		if (circle1.center.y > circle2.center.y && eObj->p_center.center.y > circle1.center.y)
		{
			// �l�p�`�̏㑤�ɉ~���G�ꂽ�ꍇ�̓����蔻��
			if (pObj->vertices[0].y > eObj->vertices[1].y)// ��
			{
				return 3;
			}
		}
		// �l�p�`�ɓ����钼�O�ɏ�����ɓ��͂���Ă��邩
		else if (circle1.center.y < circle2.center.y && eObj->p_center.center.y < circle1.center.y)
		{
			// �l�p�`�̉����ɉ~���G�ꂽ�ꍇ�̓����蔻��
			if (pObj->vertices[1].y < eObj->vertices[0].y)// ��
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

	// �O�p���m���G��Ă��鎞
	if (SATHit(pObj, eObj))
	{
		// �l�p�`���㉺�̂ǂ��炩����Ԃ��������ɍ��E�̓����蔻�肪�@�\���Ȃ��悤�ɂ��邽�߂̏���
		if (eObj->p_center2.center.y - circle1.radius < circle2.center.y + circle2.radius
			&& eObj->p_center2.center.y + circle1.radius > circle2.center.y - circle2.radius)
		{
			// ���E
			// �l�p�`�ɓ����钼�O�ɉE�����ɓ��͂���Ă��邩
			if (circle1.center.x < circle2.center.x && eObj->p_center2.center.x < circle1.center.x)
			{
				// �l�p�`�̍����ɉ~���G�ꂽ�ꍇ�̓����蔻��
				if (pObj->jodgevertices[2].x < eObj->jodgevertices[1].x)// ��
				{
					return 1;
				}
			}
			// �l�p�`�ɓ����钼�O�ɍ������ɓ��͂���Ă��邩
			else if (circle1.center.x > circle2.center.x && eObj->p_center2.center.x > circle1.center.x)
			{
				// �l�p�`�̉E���ɉ~���G�ꂽ�ꍇ�̓����蔻��
				if (pObj->jodgevertices[1].x > eObj->jodgevertices[2].x)// �E
				{
					return 4;
				}
			}
		}
		// �㉺
		// �l�p�`�ɓ����钼�O�ɉ������ɓ��͂���Ă��邩
		if (circle1.center.y > circle2.center.y && eObj->p_center2.center.y > circle1.center.y)
		{
			// �l�p�`�̏㑤�ɉ~���G�ꂽ�ꍇ�̓����蔻��
			if (pObj->jodgevertices[0].y > eObj->jodgevertices[1].y)// ��
			{
				return 3;
			}
		}
		// �l�p�`�ɓ����钼�O�ɏ�����ɓ��͂���Ă��邩
		else if (circle1.center.y < circle2.center.y && eObj->p_center2.center.y < circle1.center.y)
		{
			// �l�p�`�̉����ɉ~���G�ꂽ�ꍇ�̓����蔻��
			if (pObj->jodgevertices[1].y < eObj->jodgevertices[0].y)// ��
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

	// �O�p���m���G��Ă��鎞
	if (SATHit(pObj, eObj))
	{
		if (eObj->vertices[0].y > circle1.center.y)
		{
			// �E��ɂ���Ƃ�
			if (pObj->vertices[0].x < circle2.center.x)
			{
				// �E
				return 6;
			}
			// ����ɂ���Ƃ�
			else if (pObj->vertices[0].x > circle2.center.x)
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
//------------------------------//

// ---�}�`�̒��_���W�̐ݒ�--- //
std::vector<Vector2> ObjectCollision::SetTriangle(TestObject* Obj)
{
	Triangle triangle;
	triangle.A = { 0                                , 0.9f + Obj->Scale_countY };
	triangle.B = { 1.1f + Obj->Scale_countX, -0.9f - Obj->Scale_countY };
	triangle.C = { -1.1f - Obj->Scale_countX, -0.9f - Obj->Scale_countY };


	// 1�ڂ̓ʑ��p�`�̒��_���W���`
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
	// �l�p�̉��̎O�p
	squre.A = { width + Obj->Scale_countX,
				width + Obj->Scale_countY };
	squre.B = { width + Obj->Scale_countX,
				-width + -Obj->Scale_countY };
	squre.C = { -width - Obj->Scale_countX,
				-width + -Obj->Scale_countY };
	squre.D = { -width - Obj->Scale_countX,
				 width + Obj->Scale_countY };

	// 1�ڂ̓ʑ��p�`�̒��_���W���`
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
	// �l�p�̉��̎O�p
	squre.A = { squarewidth + Obj->Scale_countX,
				squarewidth + Obj->Scale_countY };
	squre.B = { squarewidth + Obj->Scale_countX,
				-squarewidth + -Obj->Scale_countY };
	squre.C = { -squarewidth - Obj->Scale_countX,
				-squarewidth + -Obj->Scale_countY };
	squre.D = { -squarewidth - Obj->Scale_countX,
				 squarewidth + Obj->Scale_countY };

	SQURE circle;
	// �l�p�̉��̎O�p
	circle.A = { 0, circlewidth + Obj->Scale_countY };
	circle.B = { circlewidth + Obj->Scale_countX,0 };
	circle.C = { 0 , -circlewidth - Obj->Scale_countY };
	circle.D = { -circlewidth - Obj->Scale_countX,0 };


	// 1�ڂ̓ʑ��p�`�̒��_���W���`
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
	//BOUNDING_CIRCLE circle4 = testObj->GetBoundingCircle();// ���삵�Ă��Ȃ��I�u�W�F�N�g 
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