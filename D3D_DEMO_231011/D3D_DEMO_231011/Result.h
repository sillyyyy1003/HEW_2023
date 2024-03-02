#pragma once
#include "ResultProcess.h"

class StaticObject;
class ResultProcess;

class Result 
{
private:

    //�X�^�[���Ǘ��p
    enum {
        ZERO,
        STARONE,
        STARTWO,
        STARTHREE,
        STARFOUR,
        STARFIVE,
    };
    //�X�^�[�\���p�֐�
    int ResultScore(int resultStep, std::vector<int> StarNum);

    //Result�{�^���J�ڗp
    enum {
     
        AGAIN,  //������x�����X�e�[�W�ɒ��킷��
        RETURN, //�^�C�g����
        NEXT,   //���̃X�e�[�W�ɐi��
        NONE,
    };


    int resultCounter = 0;

    //�{�^���Ǘ����邽�߂̕ϐ�
    int buttonnum = NEXT;

    //�X�^�[�̕\�����鐔���Ǘ�����ϐ�
    int AllStar = 0;

    //�X�^�[���Ǘ����邽�߂̔z��ϐ�
    //Starnum[0]����5�̃X�e�b�v��
    //Starnum[1]����4�̃X�e�b�v��
    //Starnum[2]����3�̃X�e�b�v��
    //Starnum[3]����2�̃X�e�b�v��
    std::vector<int> Starnum;

    // result
    CanvasUI* uiResult;		    //���U���g����
    CanvasUI* resultBg;	        //���U���g�w�i
    CanvasUI* Button[3];	    //���g���C�{�^��
    CanvasUI* Result_score;	    //���U���g�̃X�R�A
    CanvasUI* Result_stepcount;	//���U���g�̃X�e�b�v��
    CanvasUI* star[5];	        //���U���g�̐�
    CanvasUI* starShadow[5];	//���U���g�̐��̈Â��o�[�W����
    ResultProcess* processor;

    bool isGetNextStage = false;

    //�L�[���������̏���
    void DoResultKeyEvent();
    //�{�^���̏���
    void ButtonEvent();
    //�X�^�[�̏���
    void StarEvent(int StarScore);

    void ObjectMove(CanvasUI* ui, float moveSpeed, float moveHeight);

public:


    Result();

    ~Result();

    void Init();

    void Update();

    void Draw();

    //Starnum[0]����5�̃X�e�b�v��
    //Starnum[1]����4�̃X�e�b�v��
    //Starnum[2]����3�̃X�e�b�v��
    //Starnum[3]����2�̃X�e�b�v��
    void SetStarNum(std::vector<int> _starnum) {

        if (_starnum.size() == 4)
        {
            Starnum = _starnum;
        }
    }

    std::vector<int> GetStarNum() {
        return Starnum;
    }

    void SetButton(int num) { buttonnum = num; };
};

