#pragma once
#include "ResultProcess.h"

class StaticObject;
class ResultProcess;

class Result 
{
private:

    //スター数管理用
    enum {
        ZERO,
        STARONE,
        STARTWO,
        STARTHREE,
        STARFOUR,
        STARFIVE,
    };
    //スター表示用関数
    int ResultScore(int resultStep, std::vector<int> StarNum);

    //Resultボタン遷移用
    enum {
     
        AGAIN,  //もう一度同じステージに挑戦する
        RETURN, //タイトルへ
        NEXT,   //次のステージに進む
        NONE,
    };


    int resultCounter = 0;

    //ボタン管理するための変数
    int buttonnum = NEXT;

    //スターの表示する数を管理する変数
    int AllStar = 0;

    //スターを管理するための配列変数
    //Starnum[0]→星5のステップ数
    //Starnum[1]→星4のステップ数
    //Starnum[2]→星3のステップ数
    //Starnum[3]→星2のステップ数
    std::vector<int> Starnum;

    // result
    CanvasUI* uiResult;		    //リザルト文字
    CanvasUI* resultBg;	        //リザルト背景
    CanvasUI* Button[3];	    //リトライボタン
    CanvasUI* Result_score;	    //リザルトのスコア
    CanvasUI* Result_stepcount;	//リザルトのステップ数
    CanvasUI* star[5];	        //リザルトの星
    CanvasUI* starShadow[5];	//リザルトの星の暗いバージョン
    ResultProcess* processor;

    bool isGetNextStage = false;

    //キー押した時の処理
    void DoResultKeyEvent();
    //ボタンの処理
    void ButtonEvent();
    //スターの処理
    void StarEvent(int StarScore);

    void ObjectMove(CanvasUI* ui, float moveSpeed, float moveHeight);

public:


    Result();

    ~Result();

    void Init();

    void Update();

    void Draw();

    //Starnum[0]→星5のステップ数
    //Starnum[1]→星4のステップ数
    //Starnum[2]→星3のステップ数
    //Starnum[3]→星2のステップ数
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

