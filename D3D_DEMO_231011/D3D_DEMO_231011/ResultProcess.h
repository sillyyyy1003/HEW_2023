#pragma once
#include <vector>

class CanvasUI;

class ResultProcess
{
private:
    //�ő�\���\������
    static const int maxChars = 256;

    //�����ʒu(���̕����̈ʒu)
    float m_sPosX = 0;
    float m_sPosY = 0;

public:

    ResultProcess();

    ~ResultProcess();

    //�C�ӂ̃^�C�~���O�ŏ��������邽��
    void Init(float posX, float posY);

    CanvasUI* StepNum[maxChars];//�X�e�b�v���\���p

    //�X�e�b�v���̕\��
    void UpdateChar(char* outputChar);
    void PrintDebugLog(const int _num);

    //������̃X�^�[�g�ʒu��ݒ�
    void SetPosition(float posX, float posY);
};

