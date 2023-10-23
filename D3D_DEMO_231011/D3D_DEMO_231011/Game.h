#pragma once
#include "Object.h"



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

	Object* testObject;

	

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

	//�V�[����ݒ肷��
	void SetGameScene(GAMESCENE scene);

	
};

