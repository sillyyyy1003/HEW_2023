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

//UI���Ǘ�����
class UiManager
{

private:
	int stageNum = 3;
	int chapterNum = 3;


	//�`���[�g���A���p�A�j�����I���������ǂ����H
	bool isOver = false;

	//StageSelect
	bool isSelectStage = true;
	int selectCounter = 0;//�㉺�ړ��p

	//stage
	bool isSound = false;
	int pauseNum = 4;
	bool isSelectBgm = true;

	//============ �I�u�W�F�N�g ==============//

	typedef std::map<std::string, CanvasUI*> UiList;
	
	//�^�C�g��
	UiList* titleList;
	CanvasUI* uiTitleBg;

	//�`���[�g���A��
	UiList* tutorialList;


	CanvasUI** uiTutorial;
	CanvasUI** uiPageIn;
	TUTORIAL_SKILL tutorial = INTRODUCE;
	int tutorialNum = 8;

	//�Z���N�g
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
	CanvasUI* uiSelectBg;//�w�i
	CanvasUI* uiSelectCursor;//�X�e�[�W�Z���N�g�̃J�[�\��
	CanvasUI** uiSelectStage;//�X�e�[�W
	CanvasUI** uiSelectChapter;//�`���v�^�[
	CanvasUI** uiClearMark;//�N���A�̈�

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

	CanvasUI* uiPauseBg;		//PAUSE�̔w�i
	CanvasUI** uiPauseButton;

	CanvasUI* uiResume;			//PAUSE�̃{�^��
	CanvasUI* uiRestart;		//�X�e�[�W�̃{�^��
	CanvasUI* uiBackSelect;		//�Z���N�g��ʂɖ߂�
	CanvasUI* uiSound;
	CanvasUI* pauseMask;		//pause�̎���ʂ�S�̓I�ɈÂ��Ȃ�mask

	CanvasUI* uiSoundCursor;	//�T�E���h�p�J�[�\��
	CanvasUI* uiSoundBg;		//SOUND�̔w�i
	CanvasUI* uiSoundOp_BGM[5];	//BGM�ݒ�
	CanvasUI* uiSoundOp_SE[5];	//SE�ݒ�

	UiList* soundList;

public:
	//�R���X�g���N�^&�f�X�g���N�^
	/*UiManager() {};*/
	~UiManager();

public:

	//SINGLETON�ɂ���
	/*static UiManager* Get();*/

	//�I�u�W�F�N�g������
	void Init();


	//�c�[��
	void Update();

	//�`��
	void Draw();

	//�ʒu�ƃA�j���V�����̏�����
	void InitUi();


private:
public:

	//�A�j���V�����ƈʒu�ݒ�
	void InitTitle();//�^�C�g��
	void InitTutorial();//�`���[�g���A��
	void InitStageSelect();//�I�����
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


	//�`��
	void TitleDraw();
	void TutorialDraw();
	void SelectDraw();
	void StageDraw();
};