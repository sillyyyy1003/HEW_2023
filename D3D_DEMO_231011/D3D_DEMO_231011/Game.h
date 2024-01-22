#pragma once
#include <d3d11.h>		// DirectX11を使うためのヘッダーファイル
#include <DirectXMath.h>
#include <map>

class GameObject;
class StaticObject;
class CanvasUI;
class Stage;
class SceneManager;

class Game
{

private:


public:


	
private:
	//コンストラクタ&デストラクタ
	Game() {};
	~Game();

public:
	//唯一のインスタンスを返す関数
	static Game* Get();

	//初期化を行う関数 
	void Init();

	void InitStage();
	//ステージの初期化を行う関数
	void InitStage1_1(void);
	void InitStage1_2(void);
	void InitStage1_3(void);
	void InitStage2_1(void);
	void InitStage2_2(void);
	void InitStage2_3(void);
	void InitStage3_1(void);
	void InitStage3_2(void);
	void InitStage3_3(void);

	//ゲーム本体
	void GameUpdate(void);
	void TitleUpdate(void);

	//STAGEUPDATE
	void UpdateStage1_1(void);
	void UpdateStage1_2(void);
	void UpdateStage1_3(void);
	void UpdateStage2_1(void);
	void UpdateStage2_2(void);
	void UpdateStage2_3(void);
	void UpdateStage3_1(void);
	void UpdateStage3_2(void);
	void UpdateStage3_3(void);

	//result Update


	//ui Update



	//描画
	void GameDraw(void);
	void TitleDraw(void);
	//ステージ描画
	void DrawStage1_1();
	void DrawStage1_2();
	void DrawStage1_3();
	void DrawStage2_1();
	void DrawStage2_2();
	void DrawStage2_3();
	void DrawStage3_1();
	void DrawStage3_2();
	void DrawStage3_3();
	
	//リザルト描画
	void ResultDraw(void);

	//うい描画


	/*
	//テスト用
	void TestUpdate(void);
	void TestDraw(void);
	void TestMove(GameObject* _target);
	void TestMove(StaticObject* _target);
	void TestMove(DirectX::XMFLOAT3& _target);
	void TestMoveCamera();


	//シーンを設定する
	//void SetGameScene(GAMESCENE scene);
	*/
};

