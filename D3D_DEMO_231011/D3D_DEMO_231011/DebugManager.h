#pragma once
#include "CanvasUI.h"
#include "GameObject.h"

class DebugManager
{
private:
	//�ő�\���\������
	static const int maxChars = 256;

	CanvasUI* m_debugASCII[maxChars];

	//�����ʒu(���̕����̈ʒu)
	float m_sPosX = 0;
	float m_sPosY = 0;


public:
	DebugManager();

	~DebugManager();

	//�������Z�b�g���`��
	void UpdateChar(char* outputChar);
	
	//������̃X�^�[�g�ʒu��ݒ�
	void SetPosition(float posX, float posY);

	//�������o�͂���
	void PrintDebugLog(float _posX, float _posY, const char* word);

	//float�^�������o�͂���
	void PrintDebugLog(float _posX, float _posY, const float _num);

	//int�^�������o�͂���
	void PrintDebugLog(float _posX, float _posY, const int _num);

};

