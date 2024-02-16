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
    
    float m_size = 0;

public:

    ResultProcess();

    ~ResultProcess();

    //任意のタイミングで初期化するため
    void Init(float posX, float posY);

    CanvasUI* StepNum[maxChars];//ステップ数表示用

    void SetSize(float size) { m_size = size; };

    //ステップ数の表示
    void UpdateChar(char* outputChar);
    void PrintDebugLog(const int _num);

    //文字列のスタート位置を設定
    void SetPosition(float posX, float posY);
};

