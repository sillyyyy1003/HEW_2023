#pragma once
#include "Object.h"
#include "TestObject.h"
#include "GameObject.h"


class Game
{
private:
	enum GAMESCENE 
	{
		TITLE,		//�^�C�g��
		STAGE1,		//�Q�[���V�[��
		RESULT,		//���U���g�V�[��
	};

	GAMESCENE m_gameScene = TITLE;

private:
	Object* testWall;
	Object* testGround;
	Object* testChara;	//�v���C���[

	GameObject* testTree;	//��


public:
	//�R���X�g���N�^
	Game();

	//�Q�[���{��
	void GameUpdate(void);
	void TitleUpdate(void);
	void StageUpdate(void);
	void ResultUpdate(void);


	//��Еt��
	~Game();

	//�`��
	void GameDraw(void);
	void TitleDraw(void);
	void StageDraw(void);
	void ResultDraw(void);

	// �����蔻��
	// �~�Ɖ~���m�̓����蔻��
	int CircleHit(BOUNDING_CIRCLE bc1, BOUNDING_CIRCLE bc2);

	// �l�p�`�Ɖ~�̓����蔻��
	int SqureandCircle(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj);
	// �l�p�`�Ɖ~�̓����蔻��Ɏg���֐�
	bool CheckHit(const BOX& t_box, const BOUNDING_CIRCLE bc1);

	// �l�p�`���m�̓����蔻��
	int SqureHit(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2);

	// �I�u�W�F�N�g���m�����̂�����֐�
	void CombineObjects(int HitNum, BOUNDING_CIRCLE Combine, BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2, TestObject* testObj);

	// �㉺���E�ŕʂ̓����蔻����Ƃ邽�߂̊֐�
	int SideCollision(BOUNDING_CIRCLE circle1, BOUNDING_CIRCLE circle2);

	//�@���ׂĂ̓����蔻����Ǘ�����
	void TestCollision();

	//�V�[����ݒ肷��
	void SetGameScene(GAMESCENE scene);

	
};

