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

//ここからの部分はテスト用
private:

	DirectX::XMFLOAT3 m_lightPos = { 0.0f,0.0f,-2.0f };//光の位置を扱る変数
	DirectX::XMFLOAT3 m_cameraPos = { 0.0f, 0.0f, -7.0f };
	DirectX::XMFLOAT3 m_focusPos = { 0.0,0.0,2.0f };
	float m_distance = 10.0f;

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

	//ゲーム本体
	void GameUpdate(void);
	void TitleUpdate(void);
	void StageUpdate(void);
	void ResultUpdate(void);

	//テスト用
	void TestUpdate(void);
	void TestDraw(void);
	void TestMove(GameObject* _target);
	void TestMove(StaticObject* _target);
	void TestMove(DirectX::XMFLOAT3& _target);
	void TestMoveCamera();


	//描画
	void GameDraw(void);
	void TitleDraw(void);
	void StageDraw(void);
	void ResultDraw(void);

	
	//シーンを設定する
	//void SetGameScene(GAMESCENE scene);

	
};

