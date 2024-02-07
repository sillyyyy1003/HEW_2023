#pragma once
#include <d3d11.h>		// DirectX11を使うためのヘッダーファイル
#include <DirectXMath.h>
#include <map>
#include <vector>
#include <list>

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
	//debug用アウトライン

	//ui
	CanvasUI*	uiTitle;		//タイトル文字
	CanvasUI*	uiTitleBg;		//タイトル背景
	CanvasUI*	uiPressEnter;	//タイトルエンターキー
	CanvasUI*	uiPauseBg;		//PAUSEの背景
	CanvasUI*	uiResume;		//PAUSEのボタン
	CanvasUI*	uiRestart;		//ステージのボタン


	CanvasUI* uiSelect;
	CanvasUI* uiSound;
	CanvasUI* uiSoundBg;		//SOUNDの背景

	CanvasUI* uiSoundOp_BGM[6];	//BGM設定
	CanvasUI* uiSoundOp_SE[6];	//SE設定

	CanvasUI* fade;

	//stage select
	CanvasUI* uiSelectBg;
	CanvasUI* uiStageSelect;
	CanvasUI* uiSelectCursor;

	CanvasUI* uiSelectStage[3];
	CanvasUI* uiSelectChapter[3];
	CanvasUI* uiClearMark[3];

	//stage1-1
	StaticObject* stageBg;		//ステージ背景
	GameObject* testObj;		//移動テスト用のオブジェクト
	GameObject* coconut;		//円
	GameObject* lamp;			//長細の棒
	GameObject * housePlate;			//長方形

	std::vector<GameObject*> objectList;
	GameObject* circle;			//circle

private:
	
	//soundSetting
	enum SOUNDOP
	{
		BGM,
		SE,
	};

	//ステージ選択
	enum SELECTSTAGE
	{
	
		STAGE1,
		STAGE2,
		STAGE3,
		SELECTNONE,
	};

	//チャプター選択
	enum SELECTCHAPTER
	{
		CHAPTER1,
		CHAPTER2,
		CHAPTER3,
	};

	//フェード状態
	enum FADE_STATE
	{
		NO_FADE,
		FADE_IN,
		FADE_OUT,
	};


	enum PAUSESELECT {
		RESUME,			//ゲームに戻る
		RESTART,		//ゲーム再開
		SELECT_STAGE,	//ステージセレクトに戻る
		SOUND,			//サウンドの画面
	};



	//sound
	bool isSound = false;
	//pause
	bool isPause = false;
	//Active
	bool isActive = true;
	bool isSelectChapter = false;

	//初期設定
	int m_soundVolume_BGM = 3;
	int m_soundVolume_SE = 3;

	SOUNDOP soundOp = BGM;
	SELECTSTAGE selectStage = SELECTNONE;
	SELECTCHAPTER selectChapter = CHAPTER1;
	FADE_STATE fadeState = NO_FADE;
	PAUSESELECT pauseSelect = RESUME;

private:
	//コンストラクタ&デストラクタ
	Game() {};
	~Game();

public:
	//唯一のインスタンスを返す関数

	static Game* Get();

	std::vector<GameObject*> GetObjectList() { return objectList; };


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

	//レールの情報を初期化->使用方法：railDataの配列だけ更新する
	void RailInit1_1(void);
	void RailInit1_2(void);

	//サウンド配列Init
	void InitSoundArray();

	//セレクトステージ配列Init
	void InitSelectArray();

	//ゲーム本体
	void GameUpdate(void);

	//Title Update
	void TitleUpdate(void);

	//Select Update
	void SelectUpdate(void);
	void UpdateSelectAnimation(void);
	void UpdateCursor(void);

	void SelectChapter(void);
	void SelectStageNone(void);

	void SelectStage1(void);
	void SelectStage2(void);
	void SelectStage3(void);

	void ClearSwitch1(void);
	void ClearSwitch2(void);
	void ClearSwitch3(void);

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
	void ResultUpdate(void);
	void UpdateResult1_1(void);
	void UpdateResult1_2(void);
	void UpdateResult1_3(void);
	void UpdateResult2_1(void);
	void UpdateResult2_2(void);
	void UpdateResult2_3(void);
	void UpdateResult3_1(void);
	void UpdateResult3_2(void);
	void UpdateResult3_3(void);



	//ui Update
	void UiUpdate();


	//ポーズ関数
	void PauseSwitch(void);

	//サウンド関数
	void SoundSwitch(void);
	void SoundVolume(void);
	void SoundOp_BGM(void);	//BGM調節
	void SoundOp_SE(void);	//SE調節

	void FocusSwitch(void);

	//描画
	void GameDraw(void);

	//タイトル描画
	void TitleDraw(void);

	void StageDraw(void);

	void SelectDraw(void);

	void uiSelectDraw(void);

	//音量調節
	void SoundVolumeDraw(void);

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

	//オブジェクトを並び変え描画する
	void SortObjectDraw(void);

	//影の位置によって並び替え描画する
	void SortShadowDraw(void);


	void TestMove(GameObject* _target);

	void FadeUpdate(void);

};

