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
        NONE,
        AGAIN,  //������x�����X�e�[�W�ɒ��킷��
        RETURN, //�^�C�g����
        NEXT,   //���̃X�e�[�W�ɐi��
    };

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
    StaticObject* resultBg;	    //���U���g�w�i
    CanvasUI* Button_again;	    //���g���C�{�^��
    CanvasUI* Button_next;	    //���̃X�e�[�W�ւ̃{�^��
    CanvasUI* Button_return;    //�^�C�g���ւ̃{�^��
    CanvasUI* Result_score;	    //���U���g�̃X�R�A
    CanvasUI* Result_stepcount;	//���U���g�̃X�e�b�v��
    CanvasUI* star[5];	        //���U���g�̐�
    CanvasUI* starShadow[5];	//���U���g�̐��̈Â��o�[�W����

    //�L�[���������̏���
    void DoResultKeyEvent();
    //�{�^���̏���
    void ButtonEvent();
    //�X�^�[�̏���
    void StarEvent(int StarScore);

public:

    ResultProcess* processor;

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
};

