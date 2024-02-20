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
class Effect;
class CameraShaker;
class Result;
class ResultProcess;
class ResultAnimation;

class Game
{

private:

	DirectX::XMFLOAT3 m_lightPos = { 0,0,0 };
	
	//ここでGameObject追加する
	//debug用アウトライン

	//ui
	CanvasUI*	uiTitle;		//タイトル文字
	CanvasUI*	uiTitleBg;		//タイトル背景
	CanvasUI*	uiPressSpace;	//タイトルエンターキー
	CanvasUI*	uiPauseBg;		//PAUSEの背景
	CanvasUI*	uiResume;		//PAUSEのボタン
	CanvasUI*	uiRestart;		//ステージのボタン
	CanvasUI*	uiPauseCursor;	//PAUSEのカーソル
	CanvasUI*	uiSoundCursor;

	CanvasUI* uiSelect;
	CanvasUI* uiSound;
	CanvasUI* uiSoundBg;		//SOUNDの背景
	CanvasUI* uiMusic;			//文字表示
	CanvasUI* uiSE;				//SE表示

	CanvasUI* uiSoundOp_BGM[6];	//BGM設定
	CanvasUI* uiSoundOp_SE[6];	//SE設定
	CanvasUI* fade;

	//Effect
	Effect* testEffect;
	


	//stage select
	CanvasUI* uiSelectBg;

	CanvasUI* uiSelectCursor;//ステージセレクトのカーソル

	CanvasUI* uiSelectStage[3];
	CanvasUI* uiSelectChapter[3];
	CanvasUI* uiClearMark[3];

	//手数の表示
	ResultProcess* uiStepNum;

	//操作方法表示
	CanvasUI* controlPanel;
	CanvasUI* uiArrow;
	//MASK
	CanvasUI* stageMask; //ステージを両端を暗くするmask
	CanvasUI* pauseMask; //pauseの時画面を全体的に暗くなるmask
	CanvasUI* resultMask;//リザルト画面のマスク

	//STAGE HINT
	CanvasUI* stageHint[9];
	CanvasUI* stageHintBg;

	//stage1-1
	StaticObject*	stageBg;		//ステージ背景
	GameObject*		testObj;		//移動テスト用のオブジェクト
	GameObject*		coconut;		//円
	GameObject*		lamp;			//長細の棒
	GameObject *	housePlate;			//長方形

	//STAGE1-2
	GameObject*		lamp1_2;		//台形
	GameObject*		triangleBlock;	//三角形
	GameObject*		iphone;			//平行四角形

	//移動できるオブジェクトのリスト

	//stage1-3
	GameObject* sandwich;	    //直角三角形
	GameObject* newspaper;	    //四角
	GameObject* busket;			//台形（四角）
	GameObject* picnicbasket;   //台形（四角）

	std::vector<GameObject*> objectList;
	GameObject* circle;			//circle

	CameraShaker* cameraShaker;
	Result* resultGenerator;
	ResultAnimation* resultAnimator;

private:
	
	//soundSetting
	enum SOUNDOP
	{
		BGM,
		SE,
	};

	// 音量設定
	enum SOUNDVOLUME
	{
		VOLUME0,
		VOLUME1,
		VOLUME2,
		VOLUME3,
		VOLUME4,
		VOLUME5,

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
		CHAPTER_IDLE,
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

	//select
	bool isSelectChapter = false;
	//操作できるかどうか
	bool isControl = true;
	//SE出すかどうか？
	bool isPlaySE = false;

	//ヒントを出すかどうか？
	bool isHint = false;

	//リザルト演出
	bool isResultAnime = false;




	//初期設定
	SOUNDOP soundOp = BGM;
	SOUNDVOLUME soundVolume_BGM = VOLUME3;
	SOUNDVOLUME soundVolume_SE = VOLUME3;

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

	//ヒントの配列の初期化
	void InitHintArray();

	//ゲーム本体
	void GameUpdate(void);

	//Title Update
	void TitleUpdate(void);

	//Select Update
	void SelectUpdate(void);
	void UpdateSelectAnimation(void);
	void UpdateCursor(void);

	void SelectChapter1(void);
	void SelectChapter2(void);
	void SelectChapter3(void);

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

	//ui Update
	void UiUpdate();


	//ポーズ関数
	void PauseSwitch(void);
	void PauseCursorUpdate(void);


	//サウンド関数
	void SoundSwitch(void);
	void SoundVolume(void);
	void SoundOp_BGM(void);	//BGM調節
	void SoundOp_SE(void);	//SE調節
	void SoundCursorUpdate(void);

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

	//デバッグ用
	void DebugDisplay(void);

	void TestMove(Effect* _target);
	void TestMove(CanvasUI* _target);
	void TestMove(void);

	//背景を入れ替わる
	void SetBackGround(ID3D11ShaderResourceView* tex);

	CameraShaker* GetCameraShaker(void) { return cameraShaker; };
	void SetIsControl(bool isControl) { this->isControl = isControl; };

	bool GetResultAnime() { return this->isResultAnime; };
	void SetResultAnime(bool isAnime) { this->isResultAnime = isAnime; };

	void TestFade(void);

	void FadeUpdate(void);// フェード用のアップデート




};

