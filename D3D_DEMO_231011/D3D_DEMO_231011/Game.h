#pragma once
#include <d3d11.h>		// DirectX11を使うためのヘッダーファイル
#include <DirectXMath.h>
#include <map>

class GameObject;
class StaticObject;
class CanvasUI;
class Stage;
class SceneManager;
class Object;

class Game
{

private:

	DirectX::XMFLOAT3 m_lightPos = { 0,0,0 };
	
	//ここでGameObject追加する
	CanvasUI*	uiTitle;		//タイトル文字
	CanvasUI*	uiTitleBg;		//タイトル背景
	CanvasUI*	uiPressEnter;	//タイトルエンターキー



	CanvasUI*	uiPauseBg;		//PAUSEの背景
	CanvasUI*	uiResume;		//PAUSEのボタン
	CanvasUI*	uiRestart;		//PAUSEのボタン
	CanvasUI*	uiSelect;		//PAUSEのボタン
	CanvasUI*	uiSound;		//PAUSEのボタン

	CanvasUI*	uiSoundBg;		//SOUNDの背景

	CanvasUI*	uiSoundOp_BGM[6];	//SOUNDのBGM設定
	CanvasUI*	uiSoundOp_SE[6];	//SOUNDのSE設定


	//stage1-1
	StaticObject* stageBg;		//ステージ背景
	GameObject* testObj;		//移動テスト用のオブジェクト
	GameObject* coconut;		//円
	GameObject* lamp;			//長細の棒
	GameObject* housePlate;			//長方形

	GameObject* circle;			//circle



private:
	

	//SOUND
	bool isSound = false;
	//PAUSE
	bool isPause = false;
	
	//SOUNDOP
	enum SOUNDOP
	{
		MUTE=0,
		ONE,
		TWO,
		THREE,
		FOUR,
		FIVE,

		BGM,
		SE,

	};
	SOUNDOP soundOp = THREE;

private:
	//コンストラクタ&デストラクタ
	Game() {};
	~Game();

public:
	//唯一のインスタンスを返す関数
	static Game* Get();



	//初期化を行う関数 
	void Init();//

	void InitStage();

	//ステージの初期化を行う関数：キャラの位置、大きさなど
	void InitStage1_1(void);
	void InitStage1_2(void);
	void InitStage1_3(void);
	void InitStage2_1(void);
	void InitStage2_2(void);
	void InitStage2_3(void);
	void InitStage3_1(void);
	void InitStage3_2(void);
	void InitStage3_3(void);

	void RailInit1_1(void);
	void RailInit1_2(void);

	//ゲーム本体
	void GameUpdate(void);

	//Title Update
	void TitleUpdate(void);

	//Select Update
	void SelectUpdate(void);

	//Stage Update
	void StageUpdate(void);
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
	void UiUpdate();


	//ポーズ関数
	void PauseSwitch(void);
	//サウンド関数
	void SoundSwitch(void);

	void SoundOption(void);


	//描画
	void GameDraw(void);

	//タイトル描画
	void TitleDraw(void);

	void StageDraw(void);

	void SelectDraw(void);

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

	//ui描画

	void UiDraw(void);
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

