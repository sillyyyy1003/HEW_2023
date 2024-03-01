#pragma once
#include "CanvasUI.h"
#include <map>
#include <string>

enum  TUTORIAL_SKILL
{
	INTRODUCE,
	MOVE1,
	MOVE2,
	MOVE3,
	MOVE4,
	SIZECHANGE,
	COMBINITION,
	END,
};

class CanvasUI;

//UIを管理する
class UiManager
{

private:
	int stageNum = 3;
	int chapterNum = 3;


	//チュートリアル用アニメが終了したかどうか？
	bool isOver = false;

	//StageSelect
	bool isSelectStage = true;
	int selectCounter = 0;//上下移動用

	//stage
	bool isSound = false;
	int pauseNum = 4;
	bool isSelectBgm = true;

	//============ オブジェクト ==============//

	typedef std::map<std::string, CanvasUI*> UiList;
	
	//タイトル
	UiList* titleList;
	CanvasUI* uiTitleBg;

	//チュートリアル
	UiList* tutorialList;


	CanvasUI** uiTutorial;
	CanvasUI** uiPageIn;
	TUTORIAL_SKILL tutorial = INTRODUCE;
	int tutorialNum = 8;

	//セレクト
	enum SELECTSTAGE {
		STAGE1,
		STAGE2,
		STAGE3,
		STAGE_IDLE,
	};

	enum SELECTCHAPTER {
		CHAPTER1,
		CHAPTER2,
		CHAPTER3,
		CHAPTER_IDLE,
	};

	SELECTSTAGE selectStage = STAGE_IDLE;
	SELECTCHAPTER selectChapter = CHAPTER_IDLE;

	UiList* selectList;
	CanvasUI* uiSelectBg;//背景
	CanvasUI* uiSelectCursor;//ステージセレクトのカーソル
	CanvasUI** uiSelectStage;//ステージ
	CanvasUI** uiSelectChapter;//チャプター
	CanvasUI** uiClearMark;//クリアの印

	//PAUSE
	UiList* pauseList;
	enum PAUSESELECT {
		RESUME,
		RESTART,
		BACKSELECT,
		SOUND,
		PAUSE_IDLE,
	};
	PAUSESELECT pauseSelect = PAUSE_IDLE;

	CanvasUI* uiPauseBg;		//PAUSEの背景
	CanvasUI** uiPauseButton;

	CanvasUI* uiResume;			//PAUSEのボタン
	CanvasUI* uiRestart;		//ステージのボタン
	CanvasUI* uiBackSelect;		//セレクト画面に戻る
	CanvasUI* uiSound;
	CanvasUI* pauseMask;		//pauseの時画面を全体的に暗くなるmask

	CanvasUI* uiSoundCursor;	//サウンド用カーソル
	CanvasUI* uiSoundBg;		//SOUNDの背景
	CanvasUI* uiSoundOp_BGM[5];	//BGM設定
	CanvasUI* uiSoundOp_SE[5];	//SE設定

	UiList* soundList;

public:
	//コンストラクタ&デストラクタ
	/*UiManager() {};*/
	~UiManager();

public:

	//SINGLETONにする
	/*static UiManager* Get();*/

	//オブジェクト初期化
	void Init();


	//ツール
	void Update();

	//描画
	void Draw();

	//位置とアニメションの初期化
	void InitUi();


private:
public:

	//アニメションと位置設定
	void InitTitle();//タイトル
	void InitTutorial();//チュートリアル
	void InitStageSelect();//選択画面
	void InitStage();

	//Update
	void TitleUpdate();
	void TutorialUpdate();

	void SelectUpdate();
	void ObjectMove(CanvasUI* pObject, float moveSpeed, float bounceHeight);
	void DoSelectKey();
	void SetSelectStatus();

	void StageUpdate();
	void DoStageKey();


	//描画
	void TitleDraw();
	void TutorialDraw();
	void SelectDraw();
	void StageDraw();
};