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
    
    float m_size = 0;//�L�����̐ݒ�
    float m_interval = 0;   //�Ԋu��ݒ肷��


public:

    ResultProcess();

    ~ResultProcess();


    void SetSize(float size) { m_size = size; };

    //�C�ӂ̃^�C�~���O�ŏ��������邽��
    void Init(float posX, float posY, float size, float interval);

    CanvasUI* StepNum[maxChars];//�X�e�b�v���\���p

   

    //�X�e�b�v���̕\��
    void UpdateCharCenter(char* outputChar);//��������
    void UpdateCharLeft(char* outputChar);//������

    void PrintDebugLogCenter(const int _num);//��������
    void PrintDebugLogLeft(const int _num);//������

    //������̃X�^�[�g�ʒu��ݒ�
    void SetPosition(float posX, float posY);
};

