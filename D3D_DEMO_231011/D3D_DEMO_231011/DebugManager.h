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
	float SposX, SposY;


public:
	DebugManager();

	~DebugManager();

	void UpdateChar(void);

	void SetPosition(float posX, float posY);




};

