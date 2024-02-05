#pragma once

#include "SAT.h"
#include "Object.h"

class ObjectCollision
{
private:

	TestObject* pObj;		//test�p�L����
	TestObject* square;		//test�p�L����
	TestObject* circle;		//test�p�L����
	TestObject* triangle;	//test�p�L����
	TestObject* ex;			//test�p�L����
	TestObject* ex1;		//test�p�L����
	TestObject* ex2;		//test�p�L����
	TestObject* ex3;		//test�p�L����

	enum OBJECT
	{
		NONE,
		TRIANGLE,	// �O�p�`
		SQUARE,		// �l�p
		CIRCLE,		// �~
	};

	BOUNDING_CIRCLE p_center; // ���S�_�̍��W
	BOUNDING_CIRCLE p_center2; // ���S�_�̍��W
	std::vector<Vector2> p_verticies; // ���S�_�̍��W
	// �}�`�̊p�x�����邽�߂̕ϐ�
	int RotationJodge = 0;

public:

	void Draw();

	void Update();

	ObjectCollision();

	~ObjectCollision();

	// ���ׂĂ̓����蔻����Ǘ�����
	void objectCollision();

	//------------------//
	//--- �����蔻�� ---//
	//------------------//

	// SAT�ɂ�铖���蔻��i�ʊp�`�Ή��j
	bool SATHit(TestObject* testObj, TestObject* testObj2);

	// ���F�l�p�@�̓����蔻��
	int SqureCollision(TestObject* testObj, TestObject* testObj2);

	// ���F�l�p�@�~�@�@�̓����蔻��
	int SqureAndCircleCollision(TestObject* testObj, TestObject* testObj2);

	// ���F�O�p�@�̓����蔻��
	int TriangleCollision(TestObject* testObj, TestObject* testObj2);

	//--------------------------------------------------//
	//--- �I�u�W�F�N�g���m���G�ꂽ���ɍ��̂�����֐� ---//
	//--------------------------------------------------//

	// �~�Ǝl�p�̂ǂ����𑀍삵�Ă��鎞�̊֐�
	void CombineObjects(int HitNum, TestObject* testObj, TestObject* testObj2);

	// ���F�O�p�@���F�O�p�@
	void CombineTriangleObjects(int HitNum, TestObject* testObj, TestObject* testObj2);

	// ���F�O�p�@���F�l�p�@
	void CombineTriangleAndSqureObjects(int HitNum, TestObject* testObj, TestObject* testObj2);

	// ���F�O�p�@���F�~�@
	void CombineTriangleAndCircleObjects(int HitNum, TestObject* testObj, TestObject* testObj2);

	//------------------------------------------------//
	//--- �}�`�ɂ���ē����蔻���ς��邽�߂̊֐� ---//
	//------------------------------------------------//

	// ���F�l�p�@
	int SquareHit(TestObject* testObj, TestObject* testObj2);

	// ���F�l�p�@�~�@
	int CircleHit(TestObject* testObj, TestObject* testObj2);
	// ���F�~
	int TriangleHit(TestObject* testObj, TestObject* testObj2);

	//------------------------------------------//
	//--- �}�`�̒��_���W��ݒ肷�邽�߂̊֐� ---//
	//------------------------------------------//

	// �O�p�̒��_���W��ݒ�
	std::vector<Vector2> SetTriangle(TestObject* testObj2);

	// �l�p�̒��_���W��ݒ�
	std::vector<Vector2> SetSquare(TestObject* testObj2, float width);

	// �~�̒��_���W��ݒ�
	std::vector<Vector2> SetCircle(TestObject* testObj2, float width, float width2);

	// �}�`����]�����Ƃ��ɓ����悤�ɒ��_���W��ω������邽�߂̊֐�
	void InitialPolygonSAT(BOUNDING_CIRCLE circle1, TestObject* testObj, float rotation);

	// �}�`����]�����Ƃ��ɓ����悤�ɒ��_���W��ω��������֕ϐ���Ԃ��֐�
	std::vector<Vector2> InitialPolygonSATvertices(BOUNDING_CIRCLE circle1, std::vector<Vector2> vertices, float rotation);
};