﻿#pragma once
#include "Object.h"
#include "TestObject.h"
#include "GameObject.h"
#include "CanvasUI.h"

class Game
{
private:
	enum GAMESCENE 
	{
		TITLE,		//タイトル
		STAGE1,		//ゲームシーン
		RESULT,		//リザルトシーン
	};

	GAMESCENE m_gameScene = TITLE;

private:
	Object* testWall;
	Object* testGround;
	Object* testChara;	//プレイヤー

	GameObject* testTree;	//木

	CanvasUI* uitest;


public:
	//コンストラクタ
	Game();

	//ゲーム本体
	void GameUpdate(void);
	void TitleUpdate(void);
	void StageUpdate(void);
	void ResultUpdate(void);


	//後片付け
	~Game();

	//描画
	void GameDraw(void);
	void TitleDraw(void);
	void StageDraw(void);
	void ResultDraw(void);

	
	//シーンを設定する
	void SetGameScene(GAMESCENE scene);

	
};

