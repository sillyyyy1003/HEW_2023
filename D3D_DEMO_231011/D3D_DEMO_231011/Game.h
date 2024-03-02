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
class Fade;
class UiManager;

class Game
{

private:

	DirectX::XMFLOAT3 m_lightPos = { 0,0,0 };

	//ここでGameObject追加する
	// 
	//Effect
	Effect* testEffect;

	//手数の表示
	ResultProcess* uiStepNum;

	//操作方法表示
	CanvasUI* controlPanel;
	CanvasUI* uiArrow;
	//MASK
	CanvasUI* stageMask; //ステージを両端を暗くするmask
	CanvasUI* resultMask;//リザルト画面のマスク

	//STAGE HINT
	CanvasUI* stageHint[9];
	CanvasUI* stageShapeHint[9];
	CanvasUI* stageHintBg;

	CanvasUI* stageTutorial[3];

	//stage1-1
	StaticObject* stageBg;		//ステージ背景
	GameObject* testObj;		//移動テスト用のオブジェクト
	GameObject* coconut;		//円
	GameObject* lamp;			//長細の棒
	GameObject* housePlate;			//長方形

	//STAGE1-2
	GameObject* lamp1_2;		//台形
	GameObject* triangleBlock;	//三角形
	GameObject* iphone;			//平行四角形

	//stage1-3
	GameObject* sandwich;	    //直角三角形
	GameObject* newspaper;	    //四角
	GameObject* bucket;			//台形（四角）
	GameObject* picnicbasket;   //台形（四角）

	std::vector<GameObject*> objectList;

	CanvasUI* comingSoon;		//stageUndone用素材
	CanvasUI* comingSoonLoop;	//Loop用
	CameraShaker* cameraShaker;
	Result* resultGenerator;
	ResultAnimation* resultAnimator;
	UiManager* uiManager;
	Fade* fade;

	//ステージ１
	// 画像１
	CanvasUI* clear1_1;
	// 画像２
	CanvasUI* clear1_2;
	// 画像３
	CanvasUI* clear1_3;

	//ステージ２
	// 画像１
	CanvasUI* clear2_1;
	// 画像２
	CanvasUI* clear2_2;
	// 画像３
	CanvasUI* clear2_3;

	//ステージ３
	// 画像１
	CanvasUI* clear3_1;
	// 画像２
	CanvasUI* clear3_2;
	// 画像３
	CanvasUI* clear3_3;

	

private:


	enum {

		MOVETUTORIAL = 0,
		SPACETUTORIAL = 1,
		HINTTUTORIAL = 2,
		IDLETUTORIAL = 99,
	};

	int tutorialNum = 0;
	bool isNextTutorial = false;

	//pause
	bool isPause = false;

	//操作できるかどうか
	bool isControl = true;
	//SE出すかどうか？
	bool isPlaySE = false;

	//ヒントを出すかどうか？
	bool isHint = false;

	//リザルト演出
	bool isResultAnime = false;

	int tutorialCounter = 0;


	//初期設定
	float seVolume = 3;
	float bgmVolume = 3;


private:
	//コンストラクタ&デストラクタ
	Game() {};
	~Game();
public:
	//唯一のインスタンスを返す関数

	static Game* Get();

	std::vector<GameObject*> GetObjectList() { return objectList; };


	//初期化を行う関数
	///オブジェクト作成・ツールの初期化
	void Init();

	void InitStage();

	//ステージの初期化を行う関数：キャラの位置、大きさなど
	void InitStage1_1(void);
	void InitStage1_2(void);
	void InitStage1_3(void);
	void InitStage2_1(void);
	void InitStage2_2(void);
	void InitStage2_3(void);

	//レールの情報を初期化->使用方法：railDataの配列だけ更新する
	void RailInit1_1(void);
	void RailInit1_2(void);
	void RailInit1_3(void);

	//ヒントの配列の初期化
	void InitHintArray();

	//ゲーム本体
	void GameUpdate(void);

	//Title Update
	void TitleUpdate(void);

	void TutorialUpdate(void);

	//Select Update
	void SelectUpdate(void);

	//Stage Update
	void StageUpdate(void);
	void StageTutorialUpdate();
	void UpdateStage1_1(void);
	void UpdateStage1_2(void);
	void UpdateStage1_3(void);
	void UpdateStage2_1(void);
	void UpdateStage2_2(void);
	void UpdateStage2_3(void);
	void UpdateStageUndone(void);
	void SwitchObject();

	void DoHintKeyEvent(void);
	void DoShapeKeyEvent(void);

	//result Update
	void ResultUpdate(void);

	//ポーズ関数
	void PauseSwitch(void);

	//描画
	void GameDraw(void);

	//タイトル描画
	void TitleDraw(void);

	void TutorialDraw();

	void StageDraw(void);
	void StageUndoneDraw(void);

	void SelectDraw(void);

	//リザルト描画
	void ResultDraw(void);

	//オブジェクトを並び変え描画する
	void SortObjectDraw(void);

	//影の位置によって並び替え描画する
	void SortShadowDraw(void);

	//デバッグ用
	//void DebugDisplay(void);


	void TestMove(Effect* _target);
	void TestMove(CanvasUI* _target);
	void TestMove(void);

	//背景を入れ替わる
	void SetBackGround(ID3D11ShaderResourceView* tex);

	CameraShaker* GetCameraShaker(void) { return cameraShaker; };
	Fade* GetFade(void) { return fade; };
	Result* GetResult(void) { return resultGenerator; };

	void SetIsControl(bool isControl) { this->isControl = isControl; };
	bool GetControl() { return isControl; };

	bool GetResultAnime() { return this->isResultAnime; };
	void SetResultAnime(bool isAnime) { this->isResultAnime = isAnime; };

	void SwitchControlObject();

	bool GetPause() { return isPause; };
	void SetPause(bool isPuase) { this->isPause = isPause; };

	void SetSEVolume(float num) { seVolume = num; };
	float GetSEVolume() { return seVolume; };
	void SetBGMVolume(float num) { bgmVolume = num; };
	float GetBGMVolume() { return bgmVolume; };

	void ApplyVolume();
};

