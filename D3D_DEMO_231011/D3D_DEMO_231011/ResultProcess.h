#pragma once
#include <vector>

class CanvasUI;

class ResultProcess
{
private:
    //最大表示可能文字数
    static const int maxChars = 256;

    //初期位置(頭の文字の位置)
    float m_sPosX = 0;
    float m_sPosY = 0;
    
    float m_size = 0;//キャラの設定
    float m_interval = 0;   //間隔を設定する


public:

    ResultProcess();

    ~ResultProcess();


    void SetSize(float size) { m_size = size; };

    //任意のタイミングで初期化するため
    void Init(float posX, float posY, float size, float interval);

    CanvasUI* StepNum[maxChars];//ステップ数表示用

   

    //ステップ数の表示
    void UpdateCharCenter(char* outputChar);//中央揃え
    void UpdateCharLeft(char* outputChar);//左揃え

    void PrintDebugLogCenter(const int _num);//中央揃え
    void PrintDebugLogLeft(const int _num);//左揃え

    //文字列のスタート位置を設定
    void SetPosition(float posX, float posY);
};

